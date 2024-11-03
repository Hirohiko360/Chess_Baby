#include <graphics.h> // 引入图形库头文件，以支持图形界面的绘制
#include <stdio.h>    // 引入标准输入输出库，提供printf等输入输出功能
#include <math.h>     // 引入数学库，用于支持数学函数
//DEV BY YBY360
//注释来自于copilot

#define _CRT_SECURE_NO_WARNINGS // 定义以避免在使用某些函数（如sprintf）时的安全警告

// 声明变量
int chessX = 0, chessY = 0; // 当前棋子的屏幕像素坐标
int flag = 0; // 游戏回合标记，0 表示玩家1（黑棋），1 表示玩家2（白棋）
int chessMap[20][20] = { 0 }; // 棋盘状态，初始化为0（空位），20x20 的棋盘
int MapX = 0, MapY = 0; // 当前棋子的棋盘坐标

// 判断当前玩家是否胜利的函数
int judge(int MapX, int MapY) {
	int temp = 2 - flag % 2; // 根据flag的值获取当前玩家的标记（黑棋是2，白棋是1）

	// 判断横向连珠（即在同一行中需要找到5个相同的棋子）
	for (int j = -4; j <= 0; j++) {
		// 检查当前棋子位置及前面4个位置是否都是当前玩家的棋子，并保持在棋盘范围内
		if (MapY + j >= 0 && MapY + j + 4 < 20 && // 确保不越界
			chessMap[MapX][MapY + j] == temp && // 检查当前位置和前4个位置的棋子
			chessMap[MapX][MapY + j + 1] == temp &&
			chessMap[MapX][MapY + j + 2] == temp &&
			chessMap[MapX][MapY + j + 3] == temp &&
			chessMap[MapX][MapY + j + 4] == temp) {
			return 1; // 如果找到5个相同棋子，返回1表示胜利
		}
	}

	// 判断纵向连珠
	for (int j = -4; j <= 0; j++) {
		// 检查当前位置及前面4个位置是否都是当前玩家的棋子，并保持在棋盘范围内
		if (MapX + j >= 0 && MapX + j + 4 < 20 && // 确保不越界
			chessMap[MapX + j][MapY] == temp && // 检查当前列中的棋子
			chessMap[MapX + j + 1][MapY] == temp &&
			chessMap[MapX + j + 2][MapY] == temp &&
			chessMap[MapX + j + 3][MapY] == temp &&
			chessMap[MapX + j + 4][MapY] == temp) {
			return 1; // 如果找到5个相同棋子，返回1表示胜利
		}
	}

	// 判断右斜向连珠
	for (int j = -4; j <= 0; j++) {
		// 检查在右斜方向是否有5个相同棋子，并保持在棋盘范围内
		if (MapX + j >= 0 && MapY + j >= 0 &&
			MapX + j + 4 < 20 && MapY + j + 4 < 20 && // 确保不越界
			chessMap[MapX + j][MapY + j] == temp && // 检查右斜方向的棋子
			chessMap[MapX + j + 1][MapY + j + 1] == temp &&
			chessMap[MapX + j + 2][MapY + j + 2] == temp &&
			chessMap[MapX + j + 3][MapY + j + 3] == temp &&
			chessMap[MapX + j + 4][MapY + j + 4] == temp) {
			return 1; // 如果找到5个相同棋子，返回1表示胜利
		}
	}

	// 判断左斜向连珠
	for (int j = -4; j <= 0; j++) {
		// 检查在左斜方向是否有5个相同棋子，并保持在棋盘范围内
		if (MapX + j >= 0 && MapY - j >= 0 &&
			MapX + j + 4 < 20 && MapY - j - 4 < 20 && // 确保不越界
			chessMap[MapX + j][MapY - j] == temp && // 检查左斜方向的棋子
			chessMap[MapX + j + 1][MapY - (j + 1)] == temp &&
			chessMap[MapX + j + 2][MapY - (j + 2)] == temp &&
			chessMap[MapX + j + 3][MapY - (j + 3)] == temp &&
			chessMap[MapX + j + 4][MapY - (j + 4)] == temp) {
			return 1; // 如果找到5个相同棋子，返回1表示胜利
		}
	}

	return 0; // 如果没有找到任何连珠，返回0表示未胜利
}

// 加载背景图像的函数
void load_img() {
	IMAGE img; // 定义一个图像对象
	loadimage(&img, "bk.jpg"); // 从文件中加载背景图像
	putimage(0, 0, &img); // 将图像绘制到坐标（0,0），覆盖原来的背景
}

// 绘制棋盘的函数
void line_in() {
	setlinecolor(BLACK); // 设置线条的颜色为黑色
	for (int i = 0; i < 20; i++) { // 遍历20个单位以绘制横线和竖线
		line(0, i * 25, 500, i * 25); // 绘制一条横线，y轴以25为单位
		line(i * 25, 0, i * 25, 500); // 绘制一条竖线，x轴以25为单位
	}
	line(500, 0, 500, 500); // 绘制棋盘右边的边界线
}

// 输出文本和提示信息的函数
void text_out() {
	setbkmode(0); // 设置文本的背景模式为透明
	settextcolor(BLACK); // 设置文本颜色为黑色
	outtextxy(515, 60, "玩家1:黑棋"); // 输出玩家1的提示信息
	outtextxy(515, 100, "玩家2:白棋"); // 输出玩家2的提示信息
}

// 处理鼠标输入事件的函数
void mouse_listen() {
	MOUSEMSG Msg; // 定义鼠标消息结构，用于接收鼠标事件
	while (1) { // 无限循环，处理鼠标事件
		Msg = GetMouseMsg(); // 获取最新的鼠标消息

		// 遍历棋盘上的每一个位置，查找鼠标点击的位置
		for (int i = 0; i < 20; i++) { // 遍历棋盘的行
			for (int j = 0; j < 20; j++) { // 遍历棋盘的列
				// 判断鼠标当前位置是否在棋子的位置（25像素为一个单位，点击区域为12像素）
				if (abs(Msg.x - j * 25) < 12 && abs(Msg.y - i * 25) < 25) {
					chessX = j * 25; // 保存计算出来的棋子在屏幕上的X坐标
					chessY = i * 25; // 保存计算出来的棋子在屏幕上的Y坐标
					MapX = i; // 保存棋子在棋盘的行索引
					MapY = j; // 保存棋子在棋盘的列索引
				}
			}
		}

		// 判断鼠标左键是否被点击
		if (Msg.uMsg == WM_LBUTTONDOWN) {
			printf("X的原始坐标:%d,Y的原始坐标:%d\n", Msg.x, Msg.y); // 输出鼠标点击的原始坐标
			printf("X的优化坐标:%d,Y的优化坐标:%d\n", chessX, chessY); // 输出被优化后的坐标

			// 只有当前点击位置是空位时，才允许下棋
			if (chessMap[MapX][MapY] == 0) {
				// 根据当前玩家选择棋子颜色并绘制
				if (flag % 2 == 0) { // 如果是玩家1（黑棋）轮到下棋
					setfillcolor(BLACK); // 设置填充颜色为黑色
					solidcircle(chessX, chessY, 10); // 在当前坐标绘制半径为10的实心圆（黑棋）
					chessMap[MapX][MapY] = 1; // 在棋盘上记录当前位置为黑棋（1）
				}
				else { // 如果是玩家2（白棋）轮到下棋
					setfillcolor(WHITE); // 设置填充颜色为白色
					solidcircle(chessX, chessY, 10); // 在当前坐标绘制半径为10的实心圆（白棋）
					chessMap[MapX][MapY] = 2; // 在棋盘上记录当前位置为白棋（2）
				}
				flag++; // 切换到下一个玩家（更新回合标记）

				// 检查当前玩家是否赢得游戏
				if (judge(MapX, MapY)) { // 检查最新落子是否胜利
					char text[50]; // 用于存储胜利提示文本
					sprintf_s(text, sizeof(text), "玩家%d 胜利！", (flag % 2) + 1); // 构造胜利信息
					outtextxy(200, 250, text); // 在屏幕上输出胜利信息
					getchar(); // 暂停游戏，等待用户按键来结束
					exit(0); // 退出程序
				}
			}
		}
	}
}

// 主函数入口
int main() {
	initgraph(600, 500, SHOWCONSOLE); // 初始化图形窗口，设置窗口大小为600x500，显示控制台
	load_img(); // 加载背景图像
	line_in(); // 绘制棋盘格线
	text_out(); // 输出游戏说明提示
	mouse_listen(); // 监听鼠标点击事件，处理游戏逻辑
	getchar(); // 等待用户按键后关闭程序
}