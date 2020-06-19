#include "Frame.h"


 //�������� ����� ���� ����
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



// ����� ��Ʈ
void Player::move(int a) { // ������� ��ġ ��ȯ.
	if (x > 0 && x < 47) {
		x += a; // x��ǥ���� ��ȭ
	}
	else if (x == 0 && a == 1) x += a;
	else if (x == 47 && a == -1) x += a;
}



// �Ѿ���Ʈ
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


// ���� ��Ʈ

// �ð��ʿ� ���� ������ ��ġ �̵��� ���� ��ǥ ����.
// �ð�, ������ ���� �����ӿ� ���� ������ ���⼭.
Enemy::Enemy() {
	srand(time(NULL));
	count_m = rand() % 20 + 1; // ������ ��
	count = (sizeof(loc) / sizeof(int));
}

void Enemy::move(void) {
	Sleep(3);
	count_t++;

	if (my == by) { // �Ѿ� 1�� ������ �¾��� ���.
		for (int i = 0; i < count; i++) {
			if (loc[i] != 0) {
				if (loc[i] == bx) {
					loc[i] = 0;
					count_m--;
					score++;
					decide();
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
					decide();
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
						if (loc[i] == (bx)) {
							loc[i] = 0;
							count_m--;
							score++;
							decide();
						}
					}
				}
			}

			if (my == by2) { // �Ѿ� 2�� ������ �¾��� ���.
				for (int i = 0; i < count; i++) {
					if (loc[i] != 0) {
						if (loc[i] == (bx2)) {
							loc[i] = 0;
							count_m--;
							score++;
							decide();
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
						if (loc[i] == (bx)) {
							loc[i] = 0;
							count_m--;
							score++;
							decide();
						}
					}
				}
			}

			if (my == by2) { // �Ѿ� 2�� ������ �¾��� ���.
				for (int i = 0; i < count; i++) {
					if (loc[i] != 0) {
						if (loc[i] == (bx2)) {
							loc[i] = 0;
							count_m--;
							score++;
							decide();
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

}