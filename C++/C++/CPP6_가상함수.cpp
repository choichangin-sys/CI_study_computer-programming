#include <iostream>

//#define ON_MAIN
#ifdef ON_MAIN
using namespace std;

class CAnimal//�߻� class
{
public : 
	//���������Լ�(Pure virtual function)
	//  : �������̽� ���踦 ��
	//	: ->�ڽĵ��� �����ؾ� ��
	virtual void Cry() = 0;

	//�����Լ�(virtual function)
	//virtual void Cry()//--> �������ε�
	//{
	//	cout << "���" << endl;
	//}

	void TestFunc()
	{
		cout << "***TestFunc()***" << endl;
		Cry();
		cout << "****************" << endl;
	}
};

class CDog : public CAnimal
{
public:
	void Cry()
	{
		cout << "�۸۸�" << endl;
	}
};

class CCat : public CAnimal
{
public:
	void Cry()
	{
		cout << "�߿˾߿�" << endl;
	}
};

int main()
{
	//virtual class(pure virtual function)
	{
		//�߻� class�� ��ü�� ������ �� ����
		//CAnimal zzz;//Error		
	}
	//Reference + virtual
	if(0)
	{
		CCat a;
		a.Cry();
		
		CAnimal& ref = a;
		ref.Cry();
	}
	
	//������ + virtual => ����(����Ÿ��)���ε�
	{
		CAnimal* p1 = new CCat;
		p1->Cry();		
		delete p1;

		CAnimal* p2 = new CDog;
		p2->Cry();
		delete p2;
	}
	return 0;
	//������
	{
		CCat* a = new CCat;
		a->Cry();
		a->TestFunc();
		delete a;

		CDog* b = new CDog;
		b->Cry();
		b->TestFunc();
		delete b;
	}
	return 0;
}

#endif