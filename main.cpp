#include "Frame.h"

// �������� ����� ���� ����
extern int x, y; // ������ �Ǵ� x��ǥ�� y ��ǥ ����. (�߽ɺ�)  �⺻ ��ġ ����.
extern int bx, by; // �Ѿ��� ��ǥ
extern int bx2, by2; //�Ѿ��� ��ǥ
extern int mx, my, loc[20];//, loc2[20]; // ���͵��� ��ġ + ��� 0���� �ʱ�ȭ
extern int max, min; // �������� ��ġ�� �ľ��ϱ� ���� ����
extern long long count_t; // �ð��� �����ϱ� ���� �Լ�.
extern int max_v; // ������ ��ġ�� �����ϱ� ���� ����
extern int min_v;
extern int count_b, b1, b2; // �Ѿ� ���� Ȯ��
extern int count_m; // ������ ��
extern int score; // ����



// �����Լ� - �⺻���� ��ɵ� ����
int main(void) {

	int select;
	select = InterFace(); // �������̽� ����
	
	if (select == 1) {

		// ���ӿ� ���� ���ʹ� Ŀ���� ������ �ȵ�
		CONSOLE_CURSOR_INFO cursor = { 0, }; // Ŀ���� ����� ���� ��ü ����
		cursor.dwSize = 1; // Ŀ�� ������ ����
		cursor.bVisible = FALSE; // Ŀ�� ������ �ʰ� ����
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor); //������ ���� �ݿ�.

		srand(time(NULL)); // ���� ���� ����
		Player P;
		Enemy E;
		bullet B;
		E.location(); // ó���� ���� ����
		show(); // ���
		char moveP; // ����Ű�� �Է¹ޱ� ���� ����

		while (true) {
			E.move(); // ���� ���ο� delay ���� �����ؼ� �ð�ó���� ���� ��.
			B.move();
			if (_kbhit()) {
				moveP = _getch();
				switch (moveP) {
				case 75: // ���ʹ���Ű
					P.move(-1);
					show();
					break;
				case 77: // ������ ����Ű
					P.move(1);
					show();
					break;
				case 72: // ���� ������ �Ѿ˹߻�
					B.makeB();
					show();
					break;
				default:
					show();
					break;
				}
			}
			show();
			if (count_m == 0) { // �¸�����
				system("cls");
				cout << endl << "��������������������������������������������" << endl;
				cout << endl << "\t �¸�!" << endl;
				cout << "\t ��������!" << endl;
				cout << endl << "��������������������������������������������" << endl;
				break;
			}
			if (my == (y - 3)) { // �й�����, ������ ����ڿ��� �ٰ�������
				system("cls");
				cout << endl << "��������������������������������������������" << endl;
				cout << endl << "\t �й�!" << endl;
				cout << "\t ��������!" << endl;
				cout << endl << "��������������������������������������������" << endl;
				break;
			}
		}
	}
	else if (select == 2) {
		cout << endl << endl << "\t > ���� ����" << endl;
		return 0;
	}
}