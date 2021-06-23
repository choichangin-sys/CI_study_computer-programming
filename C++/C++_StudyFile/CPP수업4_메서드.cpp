////////////////////////////////////////
// CPP���� 4 : ��ü���� ���μ��� C++
//  - �޼���
////////////////////////////////////////

#include <iostream>

//#define ON_MAIN
#ifdef ON_MAIN
using namespace std;

int main()
{
    //��������� �ʱ�ȭ(������ ��)
    if (0)
    {
        // ������ �ڵ�
        class CTest
        {
        public:
            // CTest Ŭ������ '������ �Լ�' ���� �� ����
            CTest()
            {
                // �ν��Ͻ��� �����Ǹ� ��� �����͸� '�ڵ�'���� �ʱ�ȭ�Ѵ�.
                cout << "CTest() : ������ �Լ�" << endl;
                m_nData = 10;
            }

            // ��� ������ ����
            int m_nData;

            // ��� �Լ� ���� �� ����
            void PrintData(void)
            {
                // ��� �����Ϳ� �����ϰ� ���� ����Ѵ�.
                cout << m_nData << endl;
            }
        };
        /*
        // �ܺο� �и��� ��� �Լ� ����
        void CTest::PrintData(void)
        {
            // ��� �����Ϳ� �����ϰ� ���� ����Ѵ�.
            cout << m_nData << endl;
        }
        */
        cout << "main() �Լ� ����" << endl;

        CTest t;
        t.PrintData();

        cout << "main() �Լ� ��" << endl;
    }
    //2�� �̻��� ������� �ʱ�ȭ(�ʱ�ȭ ���)
    if (0)
    {
        // ������ �ڵ�
        class CTest
        {
        public:
            // ������ �ʱ�ȭ ����� �̿��� ��� �ʱ�ȭ
            CTest()
                : m_nData1(10), m_nData2(20)
            { }

            // �� ���� ��� ������ ����
            int m_nData1;
            int m_nData2;
            // C++11���� ����� ���ÿ� ��� ������ �ʱ�ȭ�� �� �ִ�!
            //int m_nData1 = 10;
            //int m_nData2 = 20;

            // ��� �Լ� ���� �� ����
            void PrintData(void)
            {
                // �� ���� ��� �����Ϳ� �����ϰ� ���� ����Ѵ�.
                cout << m_nData1 << endl;
                cout << m_nData2 << endl;
            }
        };
        CTest t;
        t.PrintData();
    }
    //����Լ� �����ε� 1
    if (0)
    {
        // ������ �ڵ�
        class CMyData
        {
        public:
            CMyData() : m_nData(0) { };

            int GetData(void) { return m_nData; }
            void SetData(int nParam) { m_nData = nParam; }

            // �Ű������� double �ڷ����� ���� ���� �����ߴ�.
            void SetData(double dParam) { m_nData = 0; }

        private:
            int m_nData;
        };

        CMyData a;

        // CMyData::SetData(int) �޼��尡 ȣ��ȴ�.
        a.SetData(10);
        cout << a.GetData() << endl;

        CMyData b;

        // CMyData::SetData(double) �޼��尡 ȣ��ȴ�.
        b.SetData(5.5);
        cout << b.GetData() << endl;
    }
    //����Լ� �����ε� 2
    // -> SetData :: �Ǽ��� double �ڷ��� ���μ��� �Ѿ���� ��츦 �����Ѵ�.
    if (0)
    {
        // ������ �ڵ�
        class CMyData
        {
        public:
            CMyData() : m_nData(0) { };

            int GetData(void) { return m_nData; }
            void SetData(int nParam) { m_nData = nParam; }

            // �Ǽ��� double �ڷ��� ���μ��� �Ѿ���� ��츦 �����Ѵ�.
            void SetData(double dParam) = delete;

        private:
            int m_nData;
        };

        CMyData a;

        // CMyData::SetData(int) �޼��尡 ȣ��ȴ�.
        a.SetData(10);
        cout << a.GetData() << endl;

        CMyData b;

        // CMyData::SetData(double) �޼��尡 ȣ��ȴ�.
        //b.SetData(5.5);
        //cout << b.GetData() << endl;
    }
    //������ ���
    if (0)
    {
        // ������ �ڵ�
        class CRefTest
        {
        public:
            // ������ ����� �ݵ�� ������ �ʱ�ȭ ����� �̿��� �ʱ�ȭ�Ѵ�.
            CRefTest(int& rParam) : m_nData(rParam) { };
            int GetData(void) { return m_nData; }

        private:
            // ������ ����� ��ü�� ������ �� �ݵ�� �ʱ�ȭ�ؾ� �Ѵ�.
            int& m_nData;
        };

        int a = 10;
        CRefTest t(a);

        cout << t.GetData() << endl;

        // ���� ������ a�� ���� �����ƴ�.
        a = 20;
        cout << t.GetData() << endl;
    }
    //Static ���
    if (0)
    {
        /*
        class CTest
        {
        public:
            CTest(int nParam) : m_nData(nParam) { m_nCount++; }
            int GetData() { return m_nData; };
            void ResetCount() { m_nCount = 0; };

            // ���� �޼��� ���� �� ����
            static int GetCount()
            {
                return m_nCount;
            };

        private:
            int m_nData;

            // ���� ��� ���� ����(���Ǵ� �ƴϴ�!)
            static int m_nCount;
        };
        */
        // CTest Ŭ������ ���� ��� ���� ����
        //int CTest::m_nCount = 0;

        /*
        CTest a(5), b(10);

        // ���� ����� ����.
        cout << a.GetCount() << endl;
        b.ResetCount();

        // ���� ����� ����. �ν��Ͻ� ���̵� ���� ����!
        cout << CTest::GetCount() << endl;
        */
    }
    //this ������
    if (0)
    {
        class CMyData
        {
        public:
            CMyData(int nParam) : m_nData(nParam) { };
            void PrintData()
            {
                // m_nData�� ���� ����Ѵ�.
                cout << m_nData << endl;

                // CMyData Ŭ������ ����� m_nData�� ���� ����Ѵ�.
                cout << CMyData::m_nData << endl;

                // �޼��带 ȣ���� �ν��Ͻ��� m_nData ��� ���� ����Ѵ�.
                cout << this->m_nData << endl;

                // �޼��带 ȣ���� �ν��Ͻ��� CMyData Ŭ���� ��� m_nData�� ����Ѵ�.
                cout << this->CMyData::m_nData << endl;
            }

        private:
            int m_nData;
        };
        CMyData a(5), b(10);
        a.PrintData();
        b.PrintData();
    }
    return 0;
}

#endif