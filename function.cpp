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


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void show(void) {
	system("cls");

	cout << "\t ���� �÷��� �ð� : " << count_t << endl;
	cout << "\t �Ѿ��� ��������  : " << count_b << " ��" << endl;
	cout << "\t ������ ��������  : " << count_m << " ����" << endl;
	cout << "\t ����  �� ������  : " << score << " ��" << endl;


	// ���� ���
	for (int i = 0; i < (sizeof(loc) / sizeof(int)); i++) {
		if (loc[i] != 0) { gotoxy(loc[i], my); cout << "O"; }
	}

	// �Ѿ����
	if (b1 == 1) {
		gotoxy(bx, by); cout << "��";
	}
	if (b2 == 1) {
		gotoxy(bx2, by2); cout << "��";
	}

	// ������� �����
	gotoxy(x, y - 1); cout << "���⡡";
	gotoxy(x, y);	cout << "���ࢹ";
}


int InterFace(void) { // �������̽� �Լ�
	cout << endl;
	cout << "\t  ������������������������������������������������������������" << endl;
	cout << "\t        �̸� : ���絵            " << endl;
	cout << "\t        �й� : 32193797          " << endl;
	cout << "\t        �߰���� ��ü ����      " << endl;
	cout << "\t        �������� : 2020-06-19    " << endl;
	cout << "\t  ������������������������������������������������������������" << endl << endl << endl << endl;

	cout << endl << endl << "\t    >>>>>>>>>>>>>>>>>>�ݵ�� ��ü ȭ�鿡�� �����Ұ�<<<<<<<<<<<<<<<<<<<<<<    " << endl << endl << endl << endl << endl;

	cout << "\t  ������������������������������������������������������������" << endl;
	cout << "\t      ���ð��� - �߸� ������    " << endl;
	cout << "\t        1. ����		          " << endl;
	cout << "\t        2. ����		          " << endl;
	cout << "\t						          " << endl;
	cout << "\t    ���� ���		          " << endl;
	cout << "\t    1) ����Ű�� ����(��,��)		          " << endl;
	cout << "\t    2) ����Ű �չ�ư = �̻���		          " << endl;
	cout << "\t    3) �̻��Ϸ� ���� �� ������!		          " << endl;
	cout << "\t  ������������������������������������������������������������" << endl;
	int select = 0; // ����� �Է¹��� ����.
	cout << "\t >> ";
	cin >> select;
	return select;
}