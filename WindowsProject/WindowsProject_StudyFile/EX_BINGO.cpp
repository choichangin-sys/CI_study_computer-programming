// WindowsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#define ON_MAIN
#ifdef ON_MAIN
// WindowsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject.h"

#define MAX_LOADSTRING 100
#define MAX 5




// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    ChildProc(HWND, UINT, WPARAM, LPARAM);
LPCTSTR lpszChildClass = TEXT("ChildWnd");

HWND g_hMainWnd;//부모 윈도우 핸들
BOOL g_bMyTurn = TRUE;//빙고의 턴 모드(나의턴, 너의턴)

#define WM_CHECKBINGO WM_USER+10

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    ///////////////////////////////////////
    // 차일드 윈도우의 클래스 등록.
    wcex.lpfnWndProc = ChildProc;
    wcex.lpszClassName = lpszChildClass;
    wcex.hCursor = LoadCursor(NULL, IDC_CROSS); // 커서 변환
    wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // 배경색
    RegisterClassExW(&wcex);

    return 0;
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    g_hMainWnd = hWnd;

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 내가 선언한 것
enum modeBINGO {
    bingoNONE,
    bingoMINE,
    bingoMyBINGO,
    bingoYOURS,
    bingoYourBINGO
};

//Bingo arrBigo[MAX][MAX];
HWND g_arrBingo[MAX][MAX];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                g_arrBingo[i][j] = CreateWindow(lpszChildClass, NULL,
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    i * 100, j * 100, 100, 100,
                                    hWnd, (HMENU)0, hInst, NULL);
            }
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        if (g_bMyTurn)
        {
            TextOut(hdc, MAX * 100, MAX * 100, _T("My Turn"), 7); 
        }
        else
        {
            TextOut(hdc, MAX * 100, MAX * 100, _T("Your Turn"), 9);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CHECKBINGO:
    {
        g_bMyTurn = !g_bMyTurn;
        InvalidateRect(hWnd, NULL, TRUE);

        //해당 Child의 정보를 구한다.
        HWND hChild = (HWND)wParam;
        int nChildMode = (int)lParam;

        int x, y;
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                if (g_arrBingo[i][j] == hChild)
                {
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        //빙고를 체크한다
        int nBingoCount;
        //1. 가로 체크
        nBingoCount = 0;
        for (int i = 0; i < MAX; i++)
        {
            //1. 가로라인의 윈도의 TEXT("빙고모드") 값을 읽어온다
            int mode = (int)GetProp(g_arrBingo[x][i], TEXT("빙고모드"));//초기화
            //2.읽어온 값이 현재 내 값과 같으면 count 증가
            if(nChildMode == mode)
            {
                nBingoCount++;
            }
        }
     
        if (nBingoCount == MAX)//빙고!!!!!
        {
            for (int i = 0; i < MAX; i++)
            {
                SetProp(g_arrBingo[x][i], TEXT("빙고모드"),(HANDLE)(nChildMode + 1));
                InvalidateRect(g_arrBingo[x][i], NULL, TRUE);
            }
        }
        
        //2. 세로 체크
        nBingoCount = 0;
        for (int i = 0; i < MAX; i++)
        {
            //1. 가로라인의 윈도의 TEXT("빙고모드") 값을 읽어온다
            int mode = (int)GetProp(g_arrBingo[i][y], TEXT("빙고모드"));//초기화
            //2.읽어온 값이 현재 내 값과 같으면 count 증가
            if (nChildMode == mode)
            {
                nBingoCount++;
            }
        }

        if (nBingoCount == MAX)//빙고!!!!!
        {
            for (int i = 0; i < MAX; i++)
            {
                SetProp(g_arrBingo[i][y], TEXT("빙고모드"), (HANDLE)(nChildMode + 1));
                InvalidateRect(g_arrBingo[i][y], NULL, TRUE);
            }
        }
        //3. 대각선 체크
        
        
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit;
    int nProp;

    switch (message)
    {
    case WM_CREATE:
    {
        SetProp(hWnd, TEXT("빙고모드"), (HANDLE)bingoNONE);//초기화
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        nProp = (int)GetProp(hWnd, TEXT("빙고모드"));

        if (nProp == bingoNONE)
        {
            Rectangle(hdc, 10, 10, 90, 90);
        }
        else if (nProp == bingoMINE)
        {
            Ellipse(hdc, 10, 10, 90, 90);   
        }
        else if (nProp == bingoMyBINGO)
        {
            TextOut(hdc, 10, 10, _T("나의 빙고"), 5);
        }
        else if (nProp == bingoYOURS)
        {
            MoveToEx(hdc, 10, 10, NULL);
            LineTo(hdc, 90, 90);
            MoveToEx(hdc, 10, 90, NULL);
            LineTo(hdc, 90, 10);      
        }
        else if (nProp == bingoYourBINGO)
        {
            TextOut(hdc, 10, 10, _T("너의 빙고"), 5);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        nProp = (int)GetProp(hWnd, TEXT("빙고모드"));
        if (nProp == bingoNONE)
        {
            if (g_bMyTurn == TRUE)
                nProp = bingoMINE;
            else
                nProp = bingoYOURS;
            SetProp(hWnd, TEXT("빙고모드"), (HANDLE)nProp);
            InvalidateRect(hWnd, NULL, TRUE);            

            //부모윈도우에게 빙고체크 요청함
            SendMessage(g_hMainWnd, WM_CHECKBINGO, (WPARAM)hWnd, nProp);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MDIDESTROY:
    {
        RemoveProp(hWnd, TEXT("빙고모드"));
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

#endif // DEBUG