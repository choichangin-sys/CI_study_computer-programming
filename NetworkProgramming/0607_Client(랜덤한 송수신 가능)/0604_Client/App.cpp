// App.cpp

#include "App.h"
#include <conio.h>
#include <stdio.h>

void App::Init() // Logo()를 호출
{
	Logo();
}

void App::Run() // MenuPrint()를 호출
{
	Control* pcon = Control::getInstance();
	while (true)
	{
		switch (MenuPrint())
		{
		case '1':
			pcon->InsertMember();
			break;
		case '2':
			pcon->Login();
			break;
		case '3':
			pcon->Logout();
			return;
		default:
			printf("다시 입력하세요.\n");
			break;
		}

		Sleep(2000);
	}

}

void App::Exit() // Ending()를 호출
{
	Ending();
}

void App::Logo()
{
	printf("*******************************************************************\n");
	printf("기업맞춤교육 - WinNet과정\n");
	printf("고정패킷을 사용한 Net 프로그램\n");
	printf("2021-06-07\n");
	printf("홍길동\n");
	printf("*******************************************************************\n");
}

char App::MenuPrint()
{
	printf("*******************************************************************\n");
	printf("[1] 회원가입\n");
	printf("[2] 로그인\n");
	printf("[3] 종료\n");
	printf("*******************************************************************\n");
	return _getch(); // #include <conio.h>
}

void App::Ending()
{
	printf("*******************************************************************\n");
	printf("프로그램을 종료합니다.\n");
	printf("*******************************************************************\n");
}

