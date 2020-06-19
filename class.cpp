#include "Frame.h"


 //전역변수 사용을 위한 선언
int x = 20, y = 25; // 기준이 되는 x좌표와 y 좌표 설정. (중심부)  기본 위치 설정.
int bx, by; // 총알의 좌표
int bx2, by2; //총알의 좌표
int mx = 1, my = 5, loc[20] = { 0, };//, loc2[20]; // 몬스터들의 위치 + 모두 0으로 초기화
int max, min; // 괴물들의 위치를 파악하기 위한 변수
long long count_t = 0; // 시간을 측정하기 위한 함수.
int max_v = 10; // 괴물의 위치를 설정하기 위한 변수
int min_v = 10;
int count_b, b1, b2; // 총알 여부 확인
int count_m; // 괴물의 수
int score = 0; // 점수



// 사용자 파트
void Player::move(int a) { // 사용자의 위치 변환.
	if (x > 0 && x < 47) {
		x += a; // x좌표에만 변화
	}
	else if (x == 0 && a == 1) x += a;
	else if (x == 47 && a == -1) x += a;
}



// 총알파트
void bullet::makeB(void) {
	if (count_b < 2) // 총알 갯수 최대 2개 제한
	{
		if (b1 == 0) { // 첫번째 총알의 여부에 따라 2번쨰 총알이 발사되거나 하도록 설정
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
	if (count_b > 0) // 총알이 존재할 경우
	{
		// 첫번쨰 총알이 존재할 경우
		if (b1 == 1) {
			if (count_t % 5 == 0) by--; // 일정 시간마다 총알은 위로 향함.
			if (by == my) { // 괴물의 y좌표와 동일해졌을때
				for (int i = 0; i < 60; i++) {
					if (loc[i] != 0) {
						if (bx == loc[i]) { // 괴물에 닿는다면
							count_b--; // 총알 소거
							b1 = 0;
						}

					}
				}
			}
			int t = my - 2;
			if (by == 4) { // 총알이 괴물에 비해 적당히 위로 올라가면
				count_b--; // 총알 소거
				b1 = 0; // 
			}
		}
		if (b2 == 1) {
			if (count_t % 5 == 0) by2--; // 일정 시간마다 총알은 위로 향함.
			if (by2 == my) {
				for (int i = 0; i < 60; i++) {
					if (loc[i] != 0) {
						if (bx2 == loc[i]) { // 괴물에 닿는다면
							count_b--; // 총알 소거
							b2 = 0;
						}

					}
				}
			}
			int t = my - 2;
			if (by2 == 4) { // 총알이 괴물에 비해 적당히 위로 올라가면
				count_b--; // 총알 소거
				b2 = 0; // 
			}
		}
	}
}


// 괴물 파트

// 시간초에 따라 괴물의 위치 이동을 위해 좌표 수정.
// 시간, 괴물에 대한 움직임에 대한 설정은 여기서.
Enemy::Enemy() {
	srand(time(NULL));
	count_m = rand() % 20 + 1; // 몬스터의 수
	count = (sizeof(loc) / sizeof(int));
}

void Enemy::move(void) {
	Sleep(3);
	count_t++;

	if (my == by) { // 총알 1에 괴물이 맞았을 경우.
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
	if (my == by2) { // 총알 2에 괴물이 맞았을 경우.
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


	if (count_t % 5 == 0) { // 특정 시간 간격마다 움직일 수 있도록.
		if (my % 2 == 1) { // 몬스터의 y좌표값이 홀수일 경우 오른쪽으로 이동
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
			if (my == by) { // 총알 1에 괴물이 맞았을 경우.
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

			if (my == by2) { // 총알 2에 괴물이 맞았을 경우.
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
		else if (my % 2 == 0) { // y 좌표값이 짝수일 경우 왼쪽으로 이동
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
			if (my == by) { // 총알 1에 괴물이 맞았을 경우.
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

			if (my == by2) { // 총알 2에 괴물이 맞았을 경우.
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

// 괴물의 양옆 끝자락 판단
void Enemy::decide(void) {
	//괴물의 위치를 오름차순으로 정렬.
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
	max_v = loc[19]; // 오른쪽 제일 끝 값
	int dc = 0;
	while (loc[dc] == 0) { dc++; }
	min_v = loc[dc]; // 왼쪽 제일 끝 값
}

// 괴물에게 처음 위치 할당
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