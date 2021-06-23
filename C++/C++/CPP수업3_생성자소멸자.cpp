////////////////////////////////////////
// CPP���� 3 : ��ü���� ���μ��� C++
// - �����ڿ� �Ҹ���
////////////////////////////////////////

#include <iostream>

//#define ON_MAIN
#ifdef ON_MAIN
using namespace std;

int main()
{
	//cout << "CPP���� 2 : ��ü���� ���μ��� C++\n";
	//�����ڿ� �Ҹ���
	if (0)
	{
		class CTest
		{
		public:
			CTest()
			{
				cout << "CTest::CTest()" << endl;
			}

			~CTest()
			{
				cout << "~CTest::CTest()" << endl;
			}
		};
		/////////////////////////////////////
		//1.��ü����
		cout << "Begin" << endl;
		CTest a;
		cout << "End" << endl;

		/////////////////////////////////////
		//2.��ü�� ��������
		cout << "Begin" << endl;

		// new �����ڸ� �̿��� �������� ��ü�� �����Ѵ�.
		CTest* pData = new CTest;
		cout << "Test" << endl;

		// delete �����ڸ� �̿��� ��ü�� �����Ѵ�.
		delete pData;
		cout << "End" << endl;
	}
	//����Ʈ ������
	if(0)
	{
		class CTest
		{
		public:
			// ����Ʈ ������ ����
			CTest(void) { }
			int m_nData = 5;
		};
		CTest a;
		cout << a.m_nData << endl;
	}
	//�����ڿ� �ʱ�ȭ ���
	if (0)
	{
		class CTest
		{
			// �⺻ ���� ���� �����ڴ� 'private'�̴�.
			int m_nData;

		public:
			// �������� �Ű������� ���޵� ������ ��� ������ �ʱ�ȭ�Ѵ�.
			CTest(int nParam) : m_nData(nParam)
			{
				cout << "CTest::CTest()" << endl;
			}

			~CTest()
			{
				// ������ �� �Ű������� ���� ���� ����Ѵ�.
				cout << "~CTest::CTest() " << m_nData << endl;
			}
		};
		cout << "Begin" << endl;
		CTest a(1);
		cout << "Before b" << endl;
		CTest b(2);
		cout << "End" << endl;
	}
	//������ �����ε� 1
	if (0)
	{
		class CMyData
		{
		public:
			// ����Ʈ �����ڴ� ����.
			// �Ű������� int �ϳ��� ������ �Լ� ���� �� ����
			CMyData(int nParam) : m_nData(nParam) { };

			// �Ű������� int �ڷ��� �� ���� ������ �Լ� ���� ����
			CMyData(int x, int y) : m_nData(x + y) { };

			int GetData(void) { return m_nData; }

		private:
			int m_nData;
		};
		CMyData a(10);
		CMyData b(3, 4);

		cout << a.GetData() << endl;
		cout << b.GetData() << endl;
	}
	//������ �����ε� 2
	if (0)
	{
		class CMyPoint
		{
		public:
			CMyPoint(int x)
			{
				cout << "CMyPoint(int)" << endl;
				// x ���� 100�� �Ѵ��� �˻��ϰ� ������ 100���� �����.
				if (x > 100)
					x = 100;

				m_x = 100;
			}

			CMyPoint(int x, int y)
				// x ���� �˻��ϴ� �ڵ�� �̹� �����ϹǷ� �����Ѵ�.
				: CMyPoint(x)
			{
				cout << "CMyPoint(int, int)" << endl;

				// y ���� 200�� �Ѵ��� �˻��ϰ� ������ 200���� �����.
				if (y > 200)
					y = 200;

				m_y = 200;
			}

			void Print()
			{
				cout << "X:" << m_x << endl;
				cout << "Y:" << m_y << endl;
			}

		private:
			int m_x = 0;
			int m_y = 0;
		};

		// �Ű������� �ϳ��� �����ڸ� ȣ���Ѵ�.
		CMyPoint ptBegin(110);
		ptBegin.Print();

		// �̹����� �� ������ ��� ȣ��ȴ�.
		CMyPoint ptEnd(50, 250);
		ptEnd.Print();
	}
	//Getter/Setter �޼���
	if (0)
	{
		// ������ �ڵ�
		class CMyData
		{
			// �⺻ ���� ���� �����ڴ� 'private'�̴�.
			int m_nData;

		public:
			int GetData(void) { return m_nData; }
			void SetData(int nParam) { m_nData = nParam; }
		};

		CMyData data;
		data.SetData(10);
		cout << data.GetData() << endl;
	}
	
	//����� �޼���
	if(0)
	{
		class CTest
		{
		public:
			CTest(int nParam) : m_nData(nParam) { };
			~CTest() { }

			// ����� �޼���� ���� �� �����ߴ�.
			int GetData() const
			{
				// ��� ������ ���� ���� ���� ������ �� ���� ����.
				return m_nData;
			}

			int SetData(int nParam) { m_nData = nParam; }

		private:
			int m_nData = 0;
		};
		CTest a(10);
		cout << a.GetData() << endl;
	}
	//����� �޼��� + mutable
	if (0)
	{
		class CTest
		{
		public:
			CTest(int nParam) : m_nData(nParam) { };
			~CTest() { }

			// ����� �޼���� ���� �� �����ߴ�.
			int GetData() const
			{
				// ����� �޼���� mutable ��� �������� ���� �� �� �ִ�.
				m_nData = 20;
				return m_nData;
			}

			int SetData(int nParam) { m_nData = nParam; }

		private:
			mutable int m_nData = 0;
		};
		CTest a(10);
		cout << a.GetData() << endl;
	}
    return 0;
}

#endif