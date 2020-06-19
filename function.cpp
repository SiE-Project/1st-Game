#include "Frame.h"

// 전역변수 사용을 위한 선언
extern int x, y; // 기준이 되는 x좌표와 y 좌표 설정. (중심부)  기본 위치 설정.
extern int bx, by; // 총알의 좌표
extern int bx2, by2; //총알의 좌표
extern int mx, my, loc[20];//, loc2[20]; // 몬스터들의 위치 + 모두 0으로 초기화
extern int max, min; // 괴물들의 위치를 파악하기 위한 변수
extern long long count_t; // 시간을 측정하기 위한 함수.
extern int max_v; // 괴물의 위치를 설정하기 위한 변수
extern int min_v;
extern int count_b, b1, b2; // 총알 여부 확인
extern int count_m; // 괴물의 수
extern int score; // 점수


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void show(void) {
	system("cls");

	cout << "\t 게임 플레이 시간 : " << count_t << endl;
	cout << "\t 총알의 수　　　  : " << count_b << " 개" << endl;
	cout << "\t 괴물의 수　　　  : " << count_m << " 마리" << endl;
	cout << "\t 점수  　 　　　  : " << score << " 점" << endl;


	// 괴물 출력
	for (int i = 0; i < (sizeof(loc) / sizeof(int)); i++) {
		if (loc[i] != 0) { gotoxy(loc[i], my); cout << "O"; }
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
	cout << "\t						          " << endl;
	cout << "\t    게임 방법		          " << endl;
	cout << "\t    1) 방향키로 조작(좌,우)		          " << endl;
	cout << "\t    2) 방향키 앞버튼 = 미사일		          " << endl;
	cout << "\t    3) 미사일로 적을 다 없애자!		          " << endl;
	cout << "\t  ──────────────────────────────" << endl;
	int select = 0; // 명령을 입력받을 변수.
	cout << "\t >> ";
	cin >> select;
	return select;
}