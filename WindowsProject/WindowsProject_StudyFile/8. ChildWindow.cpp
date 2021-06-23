// WindowsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

//#define ON_MAIN
#ifdef ON_MAIN
// WindowsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 윈도우 프로시저
LRESULT CALLBACK    ChildLeftProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildTopProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildBottomProc(HWND, UINT, WPARAM, LPARAM);

// 윈도우 핸들
HWND hC1, hC2, hC3;

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
    /////////////////////////////////////////////////////////////////////////////////////////
    // 차일드 원도우 등록
    // 1. 왼쪽 Child Class
    static HBRUSH hRed = CreateSolidBrush(RGB(255, 0, 0));
    wcex.hbrBackground = hRed;
    wcex.lpfnWndProc = ChildLeftProc;
    wcex.lpszClassName = _T("ChildLeft");
    RegisterClassExW(&wcex);
    // 2. 위쪽 Child Class
    static HBRUSH hGreen = CreateSolidBrush(RGB(0, 255, 0));
    wcex.hbrBackground = hGreen;
    wcex.lpfnWndProc = ChildTopProc;
    wcex.lpszClassName = _T("ChildTop");
    RegisterClassExW(&wcex);
    // 3. 아래쪽 Child Class
    static HBRUSH hBule = CreateSolidBrush(RGB(0, 0, 255));
    wcex.hbrBackground = hBule;
    wcex.lpfnWndProc = ChildBottomProc;
    wcex.lpszClassName = _T("ChildBottom");
    RegisterClassExW(&wcex);
    /////////////////////////////////////////////////////////////////////////////////////////
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
HWND g_hMainWnd;
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hC1 = CreateWindow(_T("ChildLeft"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
            0, 0, 0, 0, hWnd, (HMENU)0, hInst, NULL);

        hC2 = CreateWindow(_T("ChildTop"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
            0, 0, 0, 0, hWnd, (HMENU)0, hInst, NULL);

        hC3 = CreateWindow(_T("ChildBottom"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
            0, 0, 0, 0, hWnd, (HMENU)0, hInst, NULL);
    }
    break;
    case WM_SIZE:
    {
        if (wParam != SIZE_MINIMIZED)
        {
            RECT crt;

            GetClientRect(hWnd, &crt);
            MoveWindow(hC1, 0, 0, 300, crt.bottom, TRUE);
            MoveWindow(hC2, 300, 0, crt.right - 300, 150, TRUE);
            MoveWindow(hC3, 300, 150, crt.right - 300, crt.bottom - 150, TRUE);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        EndPaint(hWnd, &ps);
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

LRESULT CALLBACK ChildLeftProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit, hBtn;

    switch (message)
    {
    case WM_CREATE:
    {
        hEdit = CreateWindow(TEXT("edit"), NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            10, 10, 80, 25,
            hWnd, (HMENU)1, hInst, NULL);

        hBtn = CreateWindow(TEXT("button"), TEXT("Add"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            10, 50, 80, 25,
            hWnd, (HMENU)2, hInst, NULL);
    }
    break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
            case 2:
            {
                TCHAR str[256];
                // 1. 에디트 창의 글자를 읽는다.
                GetWindowText(hEdit, str, 256);
                // 2. 그 글자를 메인 창에 쓴다.
                SetWindowText(hBtn, str); 
                SetWindowText(g_hMainWnd, str);
                // 3. 에디트 창을 초기화한다.
                SetWindowText(hEdit, _T(""));
            }
            break;
        }
        break;
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK ChildTopProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        SetBkMode(hdc, TRANSPARENT); // 배경색 앞으로 뺴서 나옴. 없으면 글씨의 배경이 흰색인데 이걸 쓰면 색깔에 맞게 됨.
        TextOut(hdc, 10, 10, _T("안녕하세요. 반가워요."), 20);
        EndPaint(hWnd, &ps);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ChildBottomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit;

    switch (message)
    {
    case WM_CREATE:
    {
        hEdit = CreateWindow(TEXT("edit"), NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_MULTILINE,
            10, 10, 500, 500,
            hWnd, (HMENU)1, hInst, NULL);
        SetWindowText(hEdit, TEXT("여러분의 이야기를 써주세요."));
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
#endif // DEBUG