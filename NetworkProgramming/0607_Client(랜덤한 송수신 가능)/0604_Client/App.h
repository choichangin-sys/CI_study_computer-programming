// App.h
#pragma once
#include "Control.h"

class App
{
public:
	void Init(); // Logo()�� ȣ��
	void Run(); // MenuPrint()�� ȣ��
	void Exit(); // Ending()�� ȣ��

private:
	void Logo();
	char MenuPrint();
	void Ending();
};

