#include <stdio.h>
#include "CMyClient.h"
#include "App.h"


int main()
{
	App app;
	app.Init();
	app.Run();
	app.Exit();
	

	return 0;
}