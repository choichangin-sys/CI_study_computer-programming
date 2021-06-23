// WindowsProject.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

//#define ON_MAIN
#ifdef ON_MAIN
// WindowsProject.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "WindowsProject.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
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

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
#define ID_EDIT_NAME  100
#define ID_EDIT_SAVE  101
#define ID_EDIT_PRINT 102
HWND hEdit;
HWND hStatic;
HWND hBtn_Save;
HWND hBtn_Print;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int nTop = 100;

    switch (message)
    {
    case WM_CREATE: // ��ư �� EDIT ����
    {
        hEdit = CreateWindowW(_T("EDIT"), _T("�ٺ���"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            10, nTop, 200, 25,
            hWnd, (HMENU)ID_EDIT_NAME, hInst, NULL);

        hStatic = CreateWindowW(_T("STATIC"), _T("NAME : "),
            WS_CHILD | WS_VISIBLE,
            20, 20, 100, 25,
            hWnd, (HMENU)ID_EDIT_NAME, hInst, NULL);

        hBtn_Save = CreateWindowW(_T("BUTTON"), _T("SAVE"),
            WS_CHILD | WS_VISIBLE |BS_PUSHBUTTON,
            300, 20, 200, 25,
            hWnd, (HMENU)ID_EDIT_SAVE, hInst, NULL);

        hBtn_Print = CreateWindowW(_T("BUTTON"), _T("PRINT"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            300, 50, 100, 25,
            hWnd, (HMENU)ID_EDIT_PRINT, hInst, NULL);
    }
    break;
    case WM_LBUTTONDOWN:
        SetParent(hBtn_Save, GetDesktopWindow());
        SetWindowText(hBtn_Save, _T("������ �� ��."));
        break;
    case WM_RBUTTONDOWN:
        SetParent(hBtn_Save, hWnd);
        SetWindowText(hBtn_Save, _T("������ ���� ���ƿ�."));
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            nTop -= 10;
            break;
        case VK_DOWN:
            nTop += 10;
            break;
        case VK_LEFT:
            static BOOL bShow = TRUE;
            if (bShow == TRUE)
            {
                bShow = FALSE;
                ShowWindow(hEdit, SW_HIDE);
                SetWindowText(hWnd, _T("�������"));
                SetWindowText(hBtn_Save, _T("�������"));
            }
            else
            {
                bShow = TRUE;
                ShowWindow(hEdit, SW_SHOW);
                SetWindowText(hWnd, _T("��Ÿ����"));
                SetWindowText(hBtn_Save, _T("��Ÿ����"));
            }
            break;
        }

        MoveWindow(hEdit, 10, nTop, 200, 25, TRUE);
    }
    break;
    case WM_COMMAND: // ����� ���� �ϴ� ��.
    {
        switch (LOWORD(wParam))
        {
        case ID_EDIT_SAVE:
        {
            MessageBox(hWnd, TEXT("���带 �����մϴ�."),
                             TEXT("Saving"), MB_OK);
        }
        break;
        case ID_EDIT_PRINT:
        {
            MessageBox(hWnd, TEXT("�μ⸦ �����մϴ�."),
                             TEXT("Printing"), MB_OK);
        }
        break;
        case ID_EDIT_NAME:
            if (HIWORD(wParam) == EN_CHANGE)
            {
                TCHAR str[128];
                GetWindowText(hEdit, str, 128);
                SetWindowText(hWnd, str);
                SetWindowText(hStatic, str);
                //SetWindowText(hEdit, str); // ���ѷ����� ����.
            }
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

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

#endif // DEBUG