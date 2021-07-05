#include <stdio.h>
#include "CMyClient.h"

int main()
{
	
	//192.168.0.94
	//192.168.0.93
	CMyClient Client;
	Client.CreateSocket("192.168.0.94" ,9000);

	

	while (true)
	{
		// 사용자에게 문자열을 입력!
		char buf[256] = "\0";
		printf(">> "); gets_s(buf, sizeof(buf));

		if (strlen(buf) == 0)
		{
			break;
		}

		Client.SendData(buf, strlen(buf));
	}

	
	

	return 0;
}