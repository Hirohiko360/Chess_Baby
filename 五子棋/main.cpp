#include <graphics.h> // ����ͼ�ο�ͷ�ļ�����֧��ͼ�ν���Ļ���
#include <stdio.h>    // �����׼��������⣬�ṩprintf�������������
#include <math.h>     // ������ѧ�⣬����֧����ѧ����
//DEV BY YBY360
//ע��������copilot

#define _CRT_SECURE_NO_WARNINGS // �����Ա�����ʹ��ĳЩ��������sprintf��ʱ�İ�ȫ����

// ��������
int chessX = 0, chessY = 0; // ��ǰ���ӵ���Ļ��������
int flag = 0; // ��Ϸ�غϱ�ǣ�0 ��ʾ���1�����壩��1 ��ʾ���2�����壩
int chessMap[20][20] = { 0 }; // ����״̬����ʼ��Ϊ0����λ����20x20 ������
int MapX = 0, MapY = 0; // ��ǰ���ӵ���������

// �жϵ�ǰ����Ƿ�ʤ���ĺ���
int judge(int MapX, int MapY) {
	int temp = 2 - flag % 2; // ����flag��ֵ��ȡ��ǰ��ҵı�ǣ�������2��������1��

	// �жϺ������飨����ͬһ������Ҫ�ҵ�5����ͬ�����ӣ�
	for (int j = -4; j <= 0; j++) {
		// ��鵱ǰ����λ�ü�ǰ��4��λ���Ƿ��ǵ�ǰ��ҵ����ӣ������������̷�Χ��
		if (MapY + j >= 0 && MapY + j + 4 < 20 && // ȷ����Խ��
			chessMap[MapX][MapY + j] == temp && // ��鵱ǰλ�ú�ǰ4��λ�õ�����
			chessMap[MapX][MapY + j + 1] == temp &&
			chessMap[MapX][MapY + j + 2] == temp &&
			chessMap[MapX][MapY + j + 3] == temp &&
			chessMap[MapX][MapY + j + 4] == temp) {
			return 1; // ����ҵ�5����ͬ���ӣ�����1��ʾʤ��
		}
	}

	// �ж���������
	for (int j = -4; j <= 0; j++) {
		// ��鵱ǰλ�ü�ǰ��4��λ���Ƿ��ǵ�ǰ��ҵ����ӣ������������̷�Χ��
		if (MapX + j >= 0 && MapX + j + 4 < 20 && // ȷ����Խ��
			chessMap[MapX + j][MapY] == temp && // ��鵱ǰ���е�����
			chessMap[MapX + j + 1][MapY] == temp &&
			chessMap[MapX + j + 2][MapY] == temp &&
			chessMap[MapX + j + 3][MapY] == temp &&
			chessMap[MapX + j + 4][MapY] == temp) {
			return 1; // ����ҵ�5����ͬ���ӣ�����1��ʾʤ��
		}
	}

	// �ж���б������
	for (int j = -4; j <= 0; j++) {
		// �������б�����Ƿ���5����ͬ���ӣ������������̷�Χ��
		if (MapX + j >= 0 && MapY + j >= 0 &&
			MapX + j + 4 < 20 && MapY + j + 4 < 20 && // ȷ����Խ��
			chessMap[MapX + j][MapY + j] == temp && // �����б���������
			chessMap[MapX + j + 1][MapY + j + 1] == temp &&
			chessMap[MapX + j + 2][MapY + j + 2] == temp &&
			chessMap[MapX + j + 3][MapY + j + 3] == temp &&
			chessMap[MapX + j + 4][MapY + j + 4] == temp) {
			return 1; // ����ҵ�5����ͬ���ӣ�����1��ʾʤ��
		}
	}

	// �ж���б������
	for (int j = -4; j <= 0; j++) {
		// �������б�����Ƿ���5����ͬ���ӣ������������̷�Χ��
		if (MapX + j >= 0 && MapY - j >= 0 &&
			MapX + j + 4 < 20 && MapY - j - 4 < 20 && // ȷ����Խ��
			chessMap[MapX + j][MapY - j] == temp && // �����б���������
			chessMap[MapX + j + 1][MapY - (j + 1)] == temp &&
			chessMap[MapX + j + 2][MapY - (j + 2)] == temp &&
			chessMap[MapX + j + 3][MapY - (j + 3)] == temp &&
			chessMap[MapX + j + 4][MapY - (j + 4)] == temp) {
			return 1; // ����ҵ�5����ͬ���ӣ�����1��ʾʤ��
		}
	}

	return 0; // ���û���ҵ��κ����飬����0��ʾδʤ��
}

// ���ر���ͼ��ĺ���
void load_img() {
	IMAGE img; // ����һ��ͼ�����
	loadimage(&img, "bk.jpg"); // ���ļ��м��ر���ͼ��
	putimage(0, 0, &img); // ��ͼ����Ƶ����꣨0,0��������ԭ���ı���
}

// �������̵ĺ���
void line_in() {
	setlinecolor(BLACK); // ������������ɫΪ��ɫ
	for (int i = 0; i < 20; i++) { // ����20����λ�Ի��ƺ��ߺ�����
		line(0, i * 25, 500, i * 25); // ����һ�����ߣ�y����25Ϊ��λ
		line(i * 25, 0, i * 25, 500); // ����һ�����ߣ�x����25Ϊ��λ
	}
	line(500, 0, 500, 500); // ���������ұߵı߽���
}

// ����ı�����ʾ��Ϣ�ĺ���
void text_out() {
	setbkmode(0); // �����ı��ı���ģʽΪ͸��
	settextcolor(BLACK); // �����ı���ɫΪ��ɫ
	outtextxy(515, 60, "���1:����"); // ������1����ʾ��Ϣ
	outtextxy(515, 100, "���2:����"); // ������2����ʾ��Ϣ
}

// ������������¼��ĺ���
void mouse_listen() {
	MOUSEMSG Msg; // ���������Ϣ�ṹ�����ڽ�������¼�
	while (1) { // ����ѭ������������¼�
		Msg = GetMouseMsg(); // ��ȡ���µ������Ϣ

		// ���������ϵ�ÿһ��λ�ã������������λ��
		for (int i = 0; i < 20; i++) { // �������̵���
			for (int j = 0; j < 20; j++) { // �������̵���
				// �ж���굱ǰλ���Ƿ������ӵ�λ�ã�25����Ϊһ����λ���������Ϊ12���أ�
				if (abs(Msg.x - j * 25) < 12 && abs(Msg.y - i * 25) < 25) {
					chessX = j * 25; // ��������������������Ļ�ϵ�X����
					chessY = i * 25; // ��������������������Ļ�ϵ�Y����
					MapX = i; // �������������̵�������
					MapY = j; // �������������̵�������
				}
			}
		}

		// �ж��������Ƿ񱻵��
		if (Msg.uMsg == WM_LBUTTONDOWN) {
			printf("X��ԭʼ����:%d,Y��ԭʼ����:%d\n", Msg.x, Msg.y); // ����������ԭʼ����
			printf("X���Ż�����:%d,Y���Ż�����:%d\n", chessX, chessY); // ������Ż��������

			// ֻ�е�ǰ���λ���ǿ�λʱ������������
			if (chessMap[MapX][MapY] == 0) {
				// ���ݵ�ǰ���ѡ��������ɫ������
				if (flag % 2 == 0) { // ��������1�����壩�ֵ�����
					setfillcolor(BLACK); // ���������ɫΪ��ɫ
					solidcircle(chessX, chessY, 10); // �ڵ�ǰ������ư뾶Ϊ10��ʵ��Բ�����壩
					chessMap[MapX][MapY] = 1; // �������ϼ�¼��ǰλ��Ϊ���壨1��
				}
				else { // ��������2�����壩�ֵ�����
					setfillcolor(WHITE); // ���������ɫΪ��ɫ
					solidcircle(chessX, chessY, 10); // �ڵ�ǰ������ư뾶Ϊ10��ʵ��Բ�����壩
					chessMap[MapX][MapY] = 2; // �������ϼ�¼��ǰλ��Ϊ���壨2��
				}
				flag++; // �л�����һ����ң����»غϱ�ǣ�

				// ��鵱ǰ����Ƿ�Ӯ����Ϸ
				if (judge(MapX, MapY)) { // ������������Ƿ�ʤ��
					char text[50]; // ���ڴ洢ʤ����ʾ�ı�
					sprintf_s(text, sizeof(text), "���%d ʤ����", (flag % 2) + 1); // ����ʤ����Ϣ
					outtextxy(200, 250, text); // ����Ļ�����ʤ����Ϣ
					getchar(); // ��ͣ��Ϸ���ȴ��û�����������
					exit(0); // �˳�����
				}
			}
		}
	}
}

// ���������
int main() {
	initgraph(600, 500, SHOWCONSOLE); // ��ʼ��ͼ�δ��ڣ����ô��ڴ�СΪ600x500����ʾ����̨
	load_img(); // ���ر���ͼ��
	line_in(); // �������̸���
	text_out(); // �����Ϸ˵����ʾ
	mouse_listen(); // ����������¼���������Ϸ�߼�
	getchar(); // �ȴ��û�������رճ���
}