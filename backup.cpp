#define _CRT_SECURE_NO_WARNINGS  // 혹시 모를 오류 처리 방지

#include <iostream> // 입출력을 위한 전처리
#include <Windows.h> // gotoxy 를 사용하기 위한 전처리
#include <stdlib.h> // 난수 표현 등을 위한 전처리
#include <time.h> // 난수표현에 있어서 seed 값을 설정하기 위한 전처리
#include <conio.h> // kbhit 등을 사용하기 위한 전처리
#include <stdio.h>
using namespace std;

/*
	전체크기 : 가로 50, 세로 25
*/

// 좌표 처리를 하기 위한 함수
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 전역변수들.
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


// 출력을 담당하는 함수.
// 출력의 원리가 모든 화면을 지웠다가 새로 띄우고 조금이라도 변화 있을시 다시 지우고 하는 것이기에, 이를 고려해서 수정.
void show(void) {
	system("cls");

	cout << "\t 게임 플레이 시간 : " << count_t << " 초" << endl;
	cout << "\t 총알의 수　　　  : " << count_b << " 개" << endl;
	cout << "\t 괴물의 수　　　  : " << count_m << " 마리" << endl;
	cout << "\t 점수  　 　　　  : " << score << " 점" << endl;


	// 괴물 출력
	for (int i = 0; i < (sizeof(loc) / sizeof(int)); i++) {
		if (loc[i] != 0) { gotoxy(loc[i], my); cout << "◎"; }
	}

	// 총알출력
	if (b1 == 1) {
		gotoxy(bx, by); cout << "↑";
	}
	if (b2 == 1) {
		gotoxy(bx2, by2); cout << "↑";
	}

	// 사용자의 비행기
	gotoxy(x, y - 1); cout << "　△　";
	gotoxy(x, y);	cout << "◁□▷";
}


// 사용자에 대한 클래스
class Player {
public:
	void move(int); // 사용자의 위치 변환 함수.
};

void Player::move(int a) { // 사용자의 위치 변환.
	if (x > 0 && x < 47) {
		x += a; // x좌표에만 변화
	}
	else if (x == 0 && a == 1) x += a;
	else if (x == 47 && a == -1) x += a;
}



class bullet {
public:
	void makeB(void); // 총알 생성하는 함수
	void move(void); // 총알의 움직임
};

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

// 괴물에 대한 클래스
class Enemy {
	int count;
public:
	//void show(void);
	Enemy() {
		srand(time(NULL));
		count_m = rand() % 20 + 1; // 몬스터의 수
		count = (sizeof(loc) / sizeof(int));
	}
	void move(void); // 괴물의 이동에 관한 함수 - 시간이 지남에 따라 움직임.
	void location(void); // 괴물의 위치
	void decide(void); // 괴물의 최고점 최저점 판별.

};

// 시간초에 따라 괴물의 위치 이동을 위해 좌표 수정.
// 시간, 괴물에 대한 움직임에 대한 설정은 여기서.
void Enemy::move(void) {
	Sleep(5);
	count_t++;

	if (my == by) { // 총알 1에 괴물이 맞았을 경우.
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

	if (my == by2) { // 총알 2에 괴물이 맞았을 경우.
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
						if (loc[i] == (bx + 1)) {
							loc[i] = 0;
							count_m--;
							score++;
						}
					}
				}
			}

			if (my == by2) { // 총알 2에 괴물이 맞았을 경우.
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
						if (loc[i] == (bx - 1)) {
							loc[i] = 0;
							count_m--;
							score++;
						}
					}
				}
			}

			if (my == by2) { // 총알 2에 괴물이 맞았을 경우.
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

};



// 게임 인터페이스 - 전역변수 설정
int InterFace(void) { // 인터페이스 함수
	cout << endl;
	cout << "\t  ──────────────────────────────" << endl;
	cout << "\t        이름 : 임재도            " << endl;
	cout << "\t        학번 : 32193797          " << endl;
	cout << "\t        중간고사 대체 과제      " << endl;
	cout << "\t        제출일자 : 2020-06-19    " << endl;
	cout << "\t  ──────────────────────────────" << endl << endl << endl << endl;

	cout << endl << endl << "\t    >>>>>>>>>>>>>>>>>>반드시 전체 화면에서 게임할것<<<<<<<<<<<<<<<<<<<<<<    " << endl << endl << endl << endl << endl;

	cout << "\t  ──────────────────────────────" << endl;
	cout << "\t      슈팅게임 - 야매 갤러그    " << endl;
	cout << "\t        1. 시작		          " << endl;
	cout << "\t        2. 종료		          " << endl;
	cout << "\t  ──────────────────────────────" << endl;
	int select = 0; // 명령을 입력받을 변수.
	cout << "\t >> ";
	cin >> select;
	return select;
};


// 메인함수 - 기본적인 기능들 수행
int main(void) {
	int select;
	select = InterFace(); // 인터페이스 실행
	if (select == 1) {
		srand(time(NULL)); // 랜덤 난수 설정
		Player P;
		Enemy E;
		bullet B;
		E.location(); // 처음에 괴물 생성
		show(); // 출력
		char moveP; // 방향키를 입력받기 위한 변수

		while (true) {
			E.move(); // 여기 내부에 delay 등이 존재해서 시간처리도 같이 됨.
			B.move();
			if (_kbhit()) {
				moveP = _getch();
				switch (moveP) {
				case 75: // 왼쪽방향키
					P.move(-1);
					show();
					break;
				case 77: // 오른쪽 방향키
					P.move(1);
					show();
					break;
				case 72: // 위를 누르면 총알발사
					B.makeB();
					show();
					break;
				default:
					show();
					break;
				}
			}
			show();
			if (count_m == 0) { // 승리조건
				system("cls");
				cout << endl << "──────────────────────" << endl;
				cout << endl << "\t 승리!" << endl;
				cout << "\t 게임종료!" << endl;
				cout << endl << "──────────────────────" << endl;
				break;
			}
			if (my == (y - 3)) { // 패배조건, 괴물이 사용자에게 다가왔을떄
				system("cls");
				cout << endl << "──────────────────────" << endl;
				cout << endl << "\t 패배!" << endl;
				cout << "\t 게임종료!" << endl;
				cout << endl << "──────────────────────" << endl;
				break;
			}
		}
	}
	else if (select == 2) {
		cout << endl << endl << "\t > 게임 종료" << endl;
		return 0;
	}
}