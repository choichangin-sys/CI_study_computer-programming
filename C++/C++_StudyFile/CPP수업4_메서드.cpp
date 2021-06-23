////////////////////////////////////////
// CPP수업 4 : 객체지향 언어로서의 C++
//  - 메서드
////////////////////////////////////////

#include <iostream>

//#define ON_MAIN
#ifdef ON_MAIN
using namespace std;

int main()
{
    //멤버변수의 초기화(생성자 내)
    if (0)
    {
        // 제작자 코드
        class CTest
        {
        public:
            // CTest 클래스의 '생성자 함수' 선언 및 정의
            CTest()
            {
                // 인스턴스가 생성되면 멤버 데이터를 '자동'으로 초기화한다.
                cout << "CTest() : 생성자 함수" << endl;
                m_nData = 10;
            }

            // 멤버 데이터 선언
            int m_nData;

            // 멤버 함수 선언 및 정의
            void PrintData(void)
            {
                // 멤버 데이터에 접근하고 값을 출력한다.
                cout << m_nData << endl;
            }
        };
        /*
        // 외부에 분리된 멤버 함수 정의
        void CTest::PrintData(void)
        {
            // 멤버 데이터에 접근하고 값을 출력한다.
            cout << m_nData << endl;
        }
        */
        cout << "main() 함수 시작" << endl;

        CTest t;
        t.PrintData();

        cout << "main() 함수 끝" << endl;
    }
    //2개 이상의 멤버변수 초기화(초기화 목록)
    if (0)
    {
        // 제작자 코드
        class CTest
        {
        public:
            // 생성자 초기화 목록을 이용한 멤버 초기화
            CTest()
                : m_nData1(10), m_nData2(20)
            { }

            // 두 개의 멤버 데이터 선언
            int m_nData1;
            int m_nData2;
            // C++11부터 선언과 동시에 멤버 변수를 초기화할 수 있다!
            //int m_nData1 = 10;
            //int m_nData2 = 20;

            // 멤버 함수 선언 및 정의
            void PrintData(void)
            {
                // 두 개의 멤버 데이터에 접근하고 값을 출력한다.
                cout << m_nData1 << endl;
                cout << m_nData2 << endl;
            }
        };
        CTest t;
        t.PrintData();
    }
    //멤버함수 오버로딩 1
    if (0)
    {
        // 제작자 코드
        class CMyData
        {
        public:
            CMyData() : m_nData(0) { };

            int GetData(void) { return m_nData; }
            void SetData(int nParam) { m_nData = nParam; }

            // 매개변수가 double 자료형인 경우로 다중 정의했다.
            void SetData(double dParam) { m_nData = 0; }

        private:
            int m_nData;
        };

        CMyData a;

        // CMyData::SetData(int) 메서드가 호출된다.
        a.SetData(10);
        cout << a.GetData() << endl;

        CMyData b;

        // CMyData::SetData(double) 메서드가 호출된다.
        b.SetData(5.5);
        cout << b.GetData() << endl;
    }
    //멤버함수 오버로딩 2
    // -> SetData :: 실수로 double 자료형 실인수가 넘어오는 경우를 차단한다.
    if (0)
    {
        // 제작자 코드
        class CMyData
        {
        public:
            CMyData() : m_nData(0) { };

            int GetData(void) { return m_nData; }
            void SetData(int nParam) { m_nData = nParam; }

            // 실수로 double 자료형 실인수가 넘어오는 경우를 차단한다.
            void SetData(double dParam) = delete;

        private:
            int m_nData;
        };

        CMyData a;

        // CMyData::SetData(int) 메서드가 호출된다.
        a.SetData(10);
        cout << a.GetData() << endl;

        CMyData b;

        // CMyData::SetData(double) 메서드가 호출된다.
        //b.SetData(5.5);
        //cout << b.GetData() << endl;
    }
    //참조형 멤버
    if (0)
    {
        // 제작자 코드
        class CRefTest
        {
        public:
            // 참조형 멤버는 반드시 생성자 초기화 목록을 이용해 초기화한다.
            CRefTest(int& rParam) : m_nData(rParam) { };
            int GetData(void) { return m_nData; }

        private:
            // 참조형 멤버는 객체가 생성될 때 반드시 초기화해야 한다.
            int& m_nData;
        };

        int a = 10;
        CRefTest t(a);

        cout << t.GetData() << endl;

        // 참조 원본인 a의 값이 수정됐다.
        a = 20;
        cout << t.GetData() << endl;
    }
    //Static 멤버
    if (0)
    {
        /*
        class CTest
        {
        public:
            CTest(int nParam) : m_nData(nParam) { m_nCount++; }
            int GetData() { return m_nData; };
            void ResetCount() { m_nCount = 0; };

            // 정적 메서드 선언 및 정의
            static int GetCount()
            {
                return m_nCount;
            };

        private:
            int m_nData;

            // 정적 멤버 변수 선언(정의는 아니다!)
            static int m_nCount;
        };
        */
        // CTest 클래스의 정적 멤버 변수 정의
        //int CTest::m_nCount = 0;

        /*
        CTest a(5), b(10);

        // 정적 멤버에 접근.
        cout << a.GetCount() << endl;
        b.ResetCount();

        // 정적 멤버에 접근. 인스턴스 없이도 접근 가능!
        cout << CTest::GetCount() << endl;
        */
    }
    //this 포인터
    if (0)
    {
        class CMyData
        {
        public:
            CMyData(int nParam) : m_nData(nParam) { };
            void PrintData()
            {
                // m_nData의 값을 출력한다.
                cout << m_nData << endl;

                // CMyData 클래스의 멤버인 m_nData의 값을 출력한다.
                cout << CMyData::m_nData << endl;

                // 메서드를 호출한 인스턴스의 m_nData 멤버 값을 출력한다.
                cout << this->m_nData << endl;

                // 메서드를 호출한 인스턴스의 CMyData 클래스 멤버 m_nData를 출력한다.
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