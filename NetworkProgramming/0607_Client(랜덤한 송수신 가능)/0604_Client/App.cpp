// App.cpp

#include "App.h"
#include <conio.h>
#include <stdio.h>

void App::Init() // Logo()�� ȣ��
{
	Logo();
}

void App::Run() // MenuPrint()�� ȣ��
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
			printf("�ٽ� �Է��ϼ���.\n");
			break;
		}

		Sleep(2000);
	}

}

void App::Exit() // Ending()�� ȣ��
{
	Ending();
}

void App::Logo()
{
	printf("*******************************************************************\n");
	printf("������㱳�� - WinNet����\n");
	printf("������Ŷ�� ����� Net ���α׷�\n");
	printf("2021-06-07\n");
	printf("ȫ�浿\n");
	printf("*******************************************************************\n");
}

char App::MenuPrint()
{
	printf("*******************************************************************\n");
	printf("[1] ȸ������\n");
	printf("[2] �α���\n");
	printf("[3] ����\n");
	printf("*******************************************************************\n");
	return _getch(); // #include <conio.h>
}

void App::Ending()
{
	printf("*******************************************************************\n");
	printf("���α׷��� �����մϴ�.\n");
	printf("*******************************************************************\n");
}

