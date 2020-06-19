#define _CRT_SECURE_NO_WARNINGS  // Ȥ�� �� ���� ó�� ����

#include <iostream> // ������� ���� ��ó��
#include <Windows.h> // gotoxy �� ����ϱ� ���� ��ó��
#include <stdlib.h> // ���� ǥ�� ���� ���� ��ó��
#include <time.h> // ����ǥ���� �־ seed ���� �����ϱ� ���� ��ó��
#include <conio.h> // kbhit ���� ����ϱ� ���� ��ó��
#include <stdio.h>
using namespace std;

/*
	��üũ�� : ���� 50, ���� 25
*/

// ��ǥ ó���� �ϱ� ���� �Լ�
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ����������.
int x = 20, y = 25; // ������ �Ǵ� x��ǥ�� y ��ǥ ����. (�߽ɺ�)  �⺻ ��ġ ����.
int bx, by; // �Ѿ��� ��ǥ
int bx2, by2; //�Ѿ��� ��ǥ
int mx = 1, my = 5, loc[20] = { 0, };//, loc2[20]; // ���͵��� ��ġ + ��� 0���� �ʱ�ȭ
int max, min; // �������� ��ġ�� �ľ��ϱ� ���� ����
long long count_t = 0; // �ð��� �����ϱ� ���� �Լ�.
int max_v = 10; // ������ ��ġ�� �����ϱ� ���� ����
int min_v = 10;
int count_b, b1, b2; // �Ѿ� ���� Ȯ��
int count_m; // ������ ��
int score = 0; // ����


// ����� ����ϴ� �Լ�.
// ����� ������ ��� ȭ���� �����ٰ� ���� ���� �����̶� ��ȭ ������ �ٽ� ����� �ϴ� ���̱⿡, �̸� ����ؼ� ����.
void show(void) {
	system("cls");

	cout << "\t ���� �÷��� �ð� : " << count_t << " ��" << endl;
	cout << "\t �Ѿ��� ��������  : " << count_b << " ��" << endl;
	cout << "\t ������ ��������  : " << count_m << " ����" << endl;
	cout << "\t ����  �� ������  : " << score << " ��" << endl;


	// ���� ���
	for (int i = 0; i < (sizeof(loc) / sizeof(int)); i++) {
		if (loc[i] != 0) { gotoxy(loc[i], my); cout << "��"; }
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


// ����ڿ� ���� Ŭ����
class Player {
public:
	void move(int); // ������� ��ġ ��ȯ �Լ�.
};

void Player::move(int a) { // ������� ��ġ ��ȯ.
	if (x > 0 && x < 47) {
		x += a; // x��ǥ���� ��ȭ
	}
	else if (x == 0 && a == 1) x += a;
	else if (x == 47 && a == -1) x += a;
}



class bullet {
public:
	void makeB(void); // �Ѿ� �����ϴ� �Լ�
	void move(void); // �Ѿ��� ������
};

void bullet::makeB(void) {
	if (count_b < 2) // �Ѿ� ���� �ִ� 2�� ����
	{
		if (b1 == 0) { // ù��° �Ѿ��� ���ο� ���� 2���� �Ѿ��� �߻�ǰų� �ϵ��� ����
			b1 = 1;
			bx = x + 2, by = y - 2;
			count_b++;
		}
		else if (b1 == 1) {
			b2 = 1;
			bx2 = x + 2, by2 = y - 2;
			count_b++;
		}
	}
}

void bullet::move(void) {
	if (count_b > 0) // �Ѿ��� ������ ���
	{
		// ù���� �Ѿ��� ������ ���
		if (b1 == 1) {
			if (count_t % 5 == 0) by--; // ���� �ð����� �Ѿ��� ���� ����.
			if (by == my) { // ������ y��ǥ�� ������������
				for (int i = 0; i < 60; i++) {
					if (loc[i] != 0) {
						if (bx == loc[i]) { // ������ ��´ٸ�
							count_b--; // �Ѿ� �Ұ�
							b1 = 0;
						}

					}
				}
			}
			int t = my - 2;
			if (by == 4) { // �Ѿ��� ������ ���� ������ ���� �ö󰡸�
				count_b--; // �Ѿ� �Ұ�
				b1 = 0; // 
			}
		}
		if (b2 == 1) {
			if (count_t % 5 == 0) by2--; // ���� �ð����� �Ѿ��� ���� ����.
			if (by2 == my) {
				for (int i = 0; i < 60; i++) {
					if (loc[i] != 0) {
						if (bx2 == loc[i]) { // ������ ��´ٸ�
							count_b--; // �Ѿ� �Ұ�
							b2 = 0;
						}

					}
				}
			}
			int t = my - 2;
			if (by2 == 4) { // �Ѿ��� ������ ���� ������ ���� �ö󰡸�
				count_b--; // �Ѿ� �Ұ�
				b2 = 0; // 
			}
		}
	}
}

// ������ ���� Ŭ����
class Enemy {
	int count;
public:
	//void show(void);
	Enemy() {
		srand(time(NULL));
		count_m = rand() % 20 + 1; // ������ ��
		count = (sizeof(loc) / sizeof(int));
	}
	void move(void); // ������ �̵��� ���� �Լ� - �ð��� ������ ���� ������.
	void location(void); // ������ ��ġ
	void decide(void); // ������ �ְ��� ������ �Ǻ�.

};

// �ð��ʿ� ���� ������ ��ġ �̵��� ���� ��ǥ ����.
// �ð�, ������ ���� �����ӿ� ���� ������ ���⼭.
void Enemy::move(void) {
	Sleep(5);
	count_t++;

	if (my == by) { // �Ѿ� 1�� ������ �¾��� ���.
		for (int i = 0; i < count; i++) {
			if (loc[i] != 0) {
				if (loc[i] == bx) {
					loc[i] = 0;
					count_m--;
					score++;
				}
			}
		}
	}

	if (my == by2) { // �Ѿ� 2�� ������ �¾��� ���.
		for (int i = 0; i < count; i++) {
			if (loc[i] != 0) {
				if (loc[i] == bx2) {
					loc[i] = 0;
					count_m--;
					score++;
				}
			}
		}
	}


	if (count_t % 5 == 0) { // Ư�� �ð� ���ݸ��� ������ �� �ֵ���.
		if (my % 2 == 1) { // ������ y��ǥ���� Ȧ���� ��� ���������� �̵�
			for (int i = 0; i < count; i++) {
				if (max_v == 49) {
					my++;
					break;
				}
				if (loc[i] != 0) {
					loc[i]++;
				}
			}
			if (max_v < 49) { max_v++; min_v++; }
			if (my == by) { // �Ѿ� 1�� ������ �¾��� ���.
				for (int i = 0; i < count; i++) {
					if (loc[i] != 0) {
						if (loc[i] == (bx + 1)) {
							loc[i] = 0;
							count_m--;
							score++;
						}
					}
				}
			}

			if (my == by2) { // �Ѿ� 2�� ������ �¾��� ���.
				for (int i = 0; i < count; i++) {
					if (loc[i] != 0) {
						if (loc[i] == (bx2 + 1)) {
							loc[i] = 0;
							count_m--;
							score++;
						}
					}
				}
			}
		}
		else if (my % 2 == 0) { // y ��ǥ���� ¦���� ��� �������� �̵�
			for (int i = 0; i < count; i++) {
				if (min_v == 1) {
					my++;
					break;
				}
				if (loc[i] != 0) {
					loc[i]--;
				}
			}
			if (min_v > 1) { min_v--; max_v--; }
			if (my == by) { // �Ѿ� 1�� ������ �¾��� ���.
				for (int i = 0; i < count; i++) {
					if (loc[i] != 0) {
						if (loc[i] == (bx - 1)) {
							loc[i] = 0;
							count_m--;
							score++;
						}
					}
				}
			}

			if (my == by2) { // �Ѿ� 2�� ������ �¾��� ���.
				for (int i = 0; i < count; i++) {
					if (loc[i] != 0) {
						if (loc[i] == (bx2 - 1)) {
							loc[i] = 0;
							count_m--;
							score++;
						}
					}
				}
			}
		}
	}

}

// ������ �翷 ���ڶ� �Ǵ�
void Enemy::decide(void) {
	//������ ��ġ�� ������������ ����.
	int temp;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - 1; j++) {
			if (loc[j] > loc[j + 1]) {
				temp = loc[j];
				loc[j] = loc[j + 1];
				loc[j + 1] = temp;
			}
		}
	}
	max_v = loc[19]; // ������ ���� �� ��
	int dc = 0;
	while (loc[dc] == 0) { dc++; }
	min_v = loc[dc]; // ���� ���� �� ��
}

// �������� ó�� ��ġ �Ҵ�
void Enemy::location(void) {
	for (int i = 0; i < count_m; i++) {
		loc[i] = rand() % 39 + 1;
		for (int j = 0; j < i; j++) {
			if (loc[i] == loc[j]) {
				i--; break;
			}
		}
	}

	decide();

};



// ���� �������̽� - �������� ����
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
	cout << "\t  ������������������������������������������������������������" << endl;
	int select = 0; // ����� �Է¹��� ����.
	cout << "\t >> ";
	cin >> select;
	return select;
};


// �����Լ� - �⺻���� ��ɵ� ����
int main(void) {
	int select;
	select = InterFace(); // �������̽� ����
	if (select == 1) {
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