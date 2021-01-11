#define de_max(x, y) ((x) > (y) ? (x) : (y))
#define de_min(x, y) ((x) < (y) ? (x) : (y))
/*
define�� ����ϴ� ��� de_min(x, y) (x) < (y) ? (x) : (y)�� �������� ��
2 * de_min(x, y)�� ����ϸ� 2 * (x) < (y) ? (x) : (y)�� ���Ǿ� 2x < y ? x : y�� ���ȴ�.
�׷��Ƿ� ��ü ��ȣ�� �ʼ������� ���ִ� ������ �߿��ϴ�.
*/

#include <stdio.h>

// �ִ밪, �ּҰ� �Լ�
int max(int x, int y);
int min(int x, int y);

// �ִ밪, �ּҰ� �Լ� (�迭)
int max_arr(int arr[], int arr_len);
int min_arr(int arr[], int arr_len);

void main()
{
	int x, y, Max, Min;

	x = 100, y = 200;

	// �ִ밪, �ּҰ� �Լ�
	Max = max(x, y);
	Min = min(x, y);

	printf("Mix : %d, Min : %d\n", Max, Min);
	
	// �ִ밪, �ּҰ� �Լ� (�迭)
	int arr[10] = {2, 4, 5, 3, 1, 10, 8, 9, 6 ,7};

	Max = max_arr(arr, 10);
	Min = min_arr(arr, 10);

	printf("Mix : %d, Min : %d\n", Max, Min);

	// define�� Ȱ���� ���
	printf("Mix : %d, Min : %d\n", de_max(x, y), de_min(x, y));

	x = 200, y = 100; // ���� x, y���� �ٲ۴ٸ�?
	printf("Mix : %d, Min : %d\n", de_max(x, y), de_min(x, y)); // ��½� ���ϴ� ��� �� ���´�.
}

int max(int x, int y)
{
	if (x > y) 
	{
		return x;
	}

	return y;
}

int min(int x, int y)
{
	if (x < y)
	{
		return x;
	}

	return y;
}

int max_arr(int arr[], int arr_len)
{
	int Max = arr[0];
	
	for (int i = 0; i < arr_len - 1; i++)
	{
		if (arr[i + 1] > Max)
		{
			Max = arr[i + 1];
		}
	}

	return Max;
}

int min_arr(int arr[], int arr_len)
{
	int Min = arr[0];

	for (int i = 0; i < arr_len - 1; i++)
	{
		if (Min > arr[i + 1])
		{
			Min = arr[i + 1];
		}
	}

	return Min;
}