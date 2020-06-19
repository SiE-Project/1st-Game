#define _CRT_SECURE_NO_WARNINGS  // 혹시 모를 오류 처리 방지
#define Frame_H

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

/*
	프로그램 작성에 있어서 구분.

	시스템 처리 관련된 부분 : 전역 함수를 바탕으로 설정.
	내부 객체들의 움직임 등에 관련된 부분 : 클래스를 바탕으로 설정.
*/

// 전역변수들 (전역 함수들이나 클래스들간의 데이터를 공유하기 위해 별도로 설정.)

//int x = 20, y = 25; // 기준이 되는 x좌표와 y 좌표 설정. (중심부)  기본 위치 설정.
//int bx, by; // 총알의 좌표
//int bx2, by2; //총알의 좌표
//int mx = 1, my = 5, loc[20] = { 0, };//, loc2[15]; // 몬스터들의 위치 + 모두 0으로 초기화
//int max, min; // 괴물들의 위치를 파악하기 위한 변수
//long long count_t = 0; // 시간을 측정하기 위한 함수.
//int max_v = 10; // 괴물의 위치를 설정하기 위한 변수
//int min_v = 10;
//int count_b, b1, b2; // 총알 여부 확인
//int count_m; // 괴물의 수
//int score = 0; // 점수


// 좌표 처리를 하기 위한 함수
void gotoxy(int x, int y);

// 출력을 담당하는 전역함수
// 출력의 원리가 모든 화면을 지웠다가 새로 띄우고 조금이라도 변화 있을시 다시 지우고 하는 것이기에, 이를 고려해서 전역함수로 설정.
void show(void);

// 게임 인터페이스 - 전역변수 설정
int InterFace(void);





// 사용자에 대한 클래스
// 현재는 위치에 대한 부분만 구현. 이후 사용자에게 특별한 기능을 넣고 싶을 때 활용.
class Player {
public:
	void move(int); // 사용자의 위치 변환 함수.
};

// 총알에 대한 클래스
// 총알의 움직임, 생성, 위치 배치 등을 담당.
class bullet {
public:
	void makeB(void); // 총알 생성하는 함수
	void move(void); // 총알의 움직임
};


// 괴물에 대한 클래스
class Enemy {
	int count;
public:
	//void show(void);
	Enemy();
	void move(void); // 괴물의 이동에 관한 함수 - 시간이 지남에 따라 움직임.
	void location(void); // 괴물의 위치
	void decide(void); // 괴물의 최고점 최저점 판별.

};