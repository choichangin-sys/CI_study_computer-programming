//app.h

#pragma once
#include "Control.h"

//�帧!
class App
{	
public:
	void Init(); 
	void Run();
	void Exit();

private:
	void Logo();
	char MenuPrint();
	void Ending();	
};

