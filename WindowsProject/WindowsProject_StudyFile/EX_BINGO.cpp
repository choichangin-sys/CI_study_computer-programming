// WindowsProject.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#define ON_MAIN
#ifdef ON_MAIN
// WindowsProject.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "WindowsProject.h"

#define MAX_LOADSTRING 100
#define MAX 5




// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    ChildProc(HWND, UINT, WPARAM, LPARAM);
LPCTSTR lpszChildClass = TEXT("ChildWnd");

HWND g_hMainWnd;//�θ� ������ �ڵ�
BOOL g_bMyTurn = TRUE;//������ �� ���(������, ������)

#define WM_CHECKBINGO WM_USER+10

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
    RegisterClassExW(&wcex);

    ///////////////////////////////////////
    // ���ϵ� �������� Ŭ���� ���.
    wcex.lpfnWndProc = ChildProc;
    wcex.lpszClassName = lpszChildClass;
    wcex.hCursor = LoadCursor(NULL, IDC_CROSS); // Ŀ�� ��ȯ
    wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // ����
    RegisterClassExW(&wcex);

    return 0;
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// ���� ������ ��
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
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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

        //�ش� Child�� ������ ���Ѵ�.
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
        //���� üũ�Ѵ�
        int nBingoCount;
        //1. ���� üũ
        nBingoCount = 0;
        for (int i = 0; i < MAX; i++)
        {
            //1. ���ζ����� ������ TEXT("������") ���� �о�´�
            int mode = (int)GetProp(g_arrBingo[x][i], TEXT("������"));//�ʱ�ȭ
            //2.�о�� ���� ���� �� ���� ������ count ����
            if(nChildMode == mode)
            {
                nBingoCount++;
            }
        }
     
        if (nBingoCount == MAX)//����!!!!!
        {
            for (int i = 0; i < MAX; i++)
            {
                SetProp(g_arrBingo[x][i], TEXT("������"),(HANDLE)(nChildMode + 1));
                InvalidateRect(g_arrBingo[x][i], NULL, TRUE);
            }
        }
        
        //2. ���� üũ
        nBingoCount = 0;
        for (int i = 0; i < MAX; i++)
        {
            //1. ���ζ����� ������ TEXT("������") ���� �о�´�
            int mode = (int)GetProp(g_arrBingo[i][y], TEXT("������"));//�ʱ�ȭ
            //2.�о�� ���� ���� �� ���� ������ count ����
            if (nChildMode == mode)
            {
                nBingoCount++;
            }
        }

        if (nBingoCount == MAX)//����!!!!!
        {
            for (int i = 0; i < MAX; i++)
            {
                SetProp(g_arrBingo[i][y], TEXT("������"), (HANDLE)(nChildMode + 1));
                InvalidateRect(g_arrBingo[i][y], NULL, TRUE);
            }
        }
        //3. �밢�� üũ
        
        
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
        SetProp(hWnd, TEXT("������"), (HANDLE)bingoNONE);//�ʱ�ȭ
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        nProp = (int)GetProp(hWnd, TEXT("������"));

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
            TextOut(hdc, 10, 10, _T("���� ����"), 5);
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
            TextOut(hdc, 10, 10, _T("���� ����"), 5);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        nProp = (int)GetProp(hWnd, TEXT("������"));
        if (nProp == bingoNONE)
        {
            if (g_bMyTurn == TRUE)
                nProp = bingoMINE;
            else
                nProp = bingoYOURS;
            SetProp(hWnd, TEXT("������"), (HANDLE)nProp);
            InvalidateRect(hWnd, NULL, TRUE);            

            //�θ������쿡�� ����üũ ��û��
            SendMessage(g_hMainWnd, WM_CHECKBINGO, (WPARAM)hWnd, nProp);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MDIDESTROY:
    {
        RemoveProp(hWnd, TEXT("������"));
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

#endif // DEBUG