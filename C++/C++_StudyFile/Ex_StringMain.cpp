#include<iostream>
#include"CMyString.h"
#include"CMyStringEx.h"
using namespace std;

//#define ON_MAIN
#ifdef ON_MAIN 

int main(void)
{
	///////////////////////////////////////////
	//CMyStringEx ���
	{
		CMyStringEx srtTest("I love you"); //�����ڿ��� �ֱ�.
		//cout << srtTest.GetString() << endl;

		//return 0;

		srtTest.Append(". Do you?");
		cout << srtTest.GetString() << endl;
		
		return 0;

		int n;
		n = srtTest.Find("love");
		cout << n << endl;
	
	}
	return 0;


	///////////////////////////////////////////
	//CMyString ���
	/*
	string name = "kkk";
	name = name + "����";
	cout << name << endl;
	*/
	CMyString strData;//����Ʈ ������
	strData.SetString("������");
	cout << strData.GetString() << endl;

	//1 ���ʿ��� �޸� �ذ��ʿ�.
	strData.SetString("�ٺ��ٹ�");
	cout << strData.GetString() << endl;
	
	//2 �������� �ذ� �ʿ� (vs. ��������)
	//CMyString strData2=strData; //���������
	CMyString strData2(strData);
	cout << strData2.GetString() << endl;
	
	//3. ���ڿ��� �־ ����� ������ ����.
	CMyString strData33("ȣ��");
	cout << strData33.GetString() << endl;	

	//4.���Կ�����
	//strData33 = CMyString("�迬��");
	//cout << strData33.GetString() << endl;


	return 0;
}
#endif
