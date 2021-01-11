#define de_max(x, y) ((x) > (y) ? (x) : (y))
#define de_min(x, y) ((x) < (y) ? (x) : (y))
/*
define을 사용하는 경우 de_min(x, y) (x) < (y) ? (x) : (y)로 정의했을 때
2 * de_min(x, y)로 사용하면 2 * (x) < (y) ? (x) : (y)로 사용되어 2x < y ? x : y로 사용된다.
그러므로 전체 괄호는 필수적으로 써주는 습관이 중요하다.
*/

#include <stdio.h>

// 최대값, 최소값 함수
int max(int x, int y);
int min(int x, int y);

// 최대값, 최소값 함수 (배열)
int max_arr(int arr[], int arr_len);
int min_arr(int arr[], int arr_len);

void main()
{
	int x, y, Max, Min;

	x = 100, y = 200;

	// 최대값, 최소값 함수
	Max = max(x, y);
	Min = min(x, y);

	printf("Mix : %d, Min : %d\n", Max, Min);
	
	// 최대값, 최소값 함수 (배열)
	int arr[10] = {2, 4, 5, 3, 1, 10, 8, 9, 6 ,7};

	Max = max_arr(arr, 10);
	Min = min_arr(arr, 10);

	printf("Mix : %d, Min : %d\n", Max, Min);

	// define은 활용한 방식
	printf("Mix : %d, Min : %d\n", de_max(x, y), de_min(x, y));

	x = 200, y = 100; // 만약 x, y값을 바꾼다면?
	printf("Mix : %d, Min : %d\n", de_max(x, y), de_min(x, y)); // 출력시 원하는 대로 잘 나온다.
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