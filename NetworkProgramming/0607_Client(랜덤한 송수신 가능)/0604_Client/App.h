// App.h
#pragma once
#include "Control.h"

class App
{
public:
	void Init(); // Logo()를 호출
	void Run(); // MenuPrint()를 호출
	void Exit(); // Ending()를 호출

private:
	void Logo();
	char MenuPrint();
	void Ending();
};

