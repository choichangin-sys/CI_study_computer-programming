////////////////////////////////////////
// CPP수업 2 : 객체지향 언어로서의 C++
//  - 객체
////////////////////////////////////////

#include <iostream>

//#define ON_MAIN
#ifdef ON_MAIN
using namespace std;

int main()
{
    //구조체
    if (0)
    {
        //////////////////////////////////////
        // 제작자의 코드
        typedef struct USERDATA
        {
            int nAge;
            char szName[32];
        } USERDATA;
        /*
        void PrintData(USERDATA* pUser)
        {
            printf("%d, %s\n", pUser->nAge, pUser->szName);
        }
        */
        // 사용자의 코드
        USERDATA user = { 20, "철수" };
        printf("%d, %s\n", user.nAge, user.szName);   // 1단계
        //PrintData(&user);                                // 2단계
    }
    //구조체의 진화
    if (0)    
    {
        // 제작자의 코드
        typedef struct USERDATA
        {
            int nAge;
            char szName[32];
            void(*Print)(struct USERDATA*);
        } USERDATA;
      
        // USERDATA user = { 20, "철수", PrintData };
        // printf("%d, %s\n", user.nAge, user.szName);     // 1단계
        // PrintData(&user);                               // 2단계
        //user.Print(&user);                                 // 3단계
    }
    //객체
    if(0)
    {
        //////////////////////////////////////
        // 제작자의 코드
        class USERDATA
        {
        public:
            // 멤버 변수 선언
            int nAge;
            char szName[32];

            // 멤버 함수 선언 및 정의
            void Print(void)
            {
                // nAge와 szName은 Print() 함수의 지역 변수가 아니다!
                printf("%d, %s\n", nAge, szName);
            }
        };
        // 사용자의 코드
        USERDATA user = { 10, "철수" };
        user.Print();
    }
    return 0;
}

#endif