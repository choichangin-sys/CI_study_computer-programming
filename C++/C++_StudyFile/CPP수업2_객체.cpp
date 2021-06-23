////////////////////////////////////////
// CPP���� 2 : ��ü���� ���μ��� C++
//  - ��ü
////////////////////////////////////////

#include <iostream>

//#define ON_MAIN
#ifdef ON_MAIN
using namespace std;

int main()
{
    //����ü
    if (0)
    {
        //////////////////////////////////////
        // �������� �ڵ�
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
        // ������� �ڵ�
        USERDATA user = { 20, "ö��" };
        printf("%d, %s\n", user.nAge, user.szName);   // 1�ܰ�
        //PrintData(&user);                                // 2�ܰ�
    }
    //����ü�� ��ȭ
    if (0)    
    {
        // �������� �ڵ�
        typedef struct USERDATA
        {
            int nAge;
            char szName[32];
            void(*Print)(struct USERDATA*);
        } USERDATA;
      
        // USERDATA user = { 20, "ö��", PrintData };
        // printf("%d, %s\n", user.nAge, user.szName);     // 1�ܰ�
        // PrintData(&user);                               // 2�ܰ�
        //user.Print(&user);                                 // 3�ܰ�
    }
    //��ü
    if(0)
    {
        //////////////////////////////////////
        // �������� �ڵ�
        class USERDATA
        {
        public:
            // ��� ���� ����
            int nAge;
            char szName[32];

            // ��� �Լ� ���� �� ����
            void Print(void)
            {
                // nAge�� szName�� Print() �Լ��� ���� ������ �ƴϴ�!
                printf("%d, %s\n", nAge, szName);
            }
        };
        // ������� �ڵ�
        USERDATA user = { 10, "ö��" };
        user.Print();
    }
    return 0;
}

#endif