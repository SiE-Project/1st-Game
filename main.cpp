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



// 메인함수 - 기본적인 기능들 수행
int main(void) {

	int select;
	select = InterFace(); // 인터페이스 실행
	
	if (select == 1) {

		// 게임에 들어가고 부터는 커서가 보여선 안됨
		CONSOLE_CURSOR_INFO cursor = { 0, }; // 커서를 숨기기 위한 객체 선언
		cursor.dwSize = 1; // 커서 사이즈 설정
		cursor.bVisible = FALSE; // 커서 보이지 않게 셋팅
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor); //설정한 내용 반영.

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