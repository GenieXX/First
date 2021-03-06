//FakeLink.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "FakeLink.h"
#include "time.h"
#include "POS.h"
using namespace std;

#define MAX_LOADSTRING 100


vector<Color> color(12);
int arr[10][14] = { { 0 } };
int flag = 0;
vector<Pos> point(2);

void initmap();
void initcolor();


// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
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

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FAKELINK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FAKELINK));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FAKELINK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FAKELINK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1300, 850, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hp;
	HBRUSH hb;
	LPCWSTR number = TEXT("剩余个数：");
	LPCWSTR tip = TEXT("S键重新开始");
	LPCWSTR time = TEXT("所用时间：");
	int num = 0;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_LBUTTONDOWN:
		if (flag == 0)
		{
			flag = 1;
		}
		else
			flag = 0;
		point[flag].x = HIWORD(lParam) / 80; //行 纵坐标
		point[flag].y = LOWORD(lParam) / 80; //列 横坐标
											 //判断能否消除
		if (point[flag].match(point[flag], point[1 - flag]))
		{
			num = point[flag].Num();
			InvalidateRect(hWnd, NULL, true);
		}

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'S':
			initmap();
			initcolor();
			point[0].x = 0;
			point[0].y = 0;
			point[1].x = 0;
			point[1].y = 0;
			flag = 0;
			InvalidateRect(hWnd, NULL, true);
			break;
		default:
			break;
		}
    case WM_PAINT:
        {
            //PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

			hp = (HPEN)GetStockObject(BLACK_PEN);
			SelectObject(hdc, hp);
			//绘制伪地图
			for (int i = 1; i < 13; i++)
			{
				for (int j = 1; j < 9; j++)
				{
					hb = (HBRUSH)CreateSolidBrush(RGB(color[arr[j][i]].red, color[arr[j][i]].green, color[arr[j][i]].blue));
					SelectObject(hdc, hb);
					Rectangle(hdc, i + 80 * i, j + 80 * j, i + 80 * i + 80, j + j * 80 + 80);  //单元格宽80
				}
			}
			//LPCWSTR numbernum = TEXT(num);
			TextOut(hdc, 1120, 200, number, lstrlen(number));
			TextOut(hdc, 1120, 400, tip, lstrlen(tip));
			TextOut(hdc, 1120, 250, time, lstrlen(time));
			//TextOut(hdc, 1130, 200, num, lstrlen(number));
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

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



void initcolor() {

	color[0].red = 255;
	color[0].green = 255;
	color[0].blue = 255;

	color[1].red = 81;
	color[1].green = 52;
	color[1].blue = 46;

	color[2].red = 17;
	color[2].green = 73;
	color[2].blue = 130;

	color[3].red = 134;
	color[3].green = 215;
	color[3].blue = 157;

	color[4].red = 240;
	color[4].green = 116;
	color[4].blue = 116;

	color[5].red = 229;
	color[5].green = 134;
	color[5].blue = 215;

	color[6].red = 73;
	color[6].green = 69;
	color[6].blue = 68;

	color[7].red = 157;
	color[7].green = 1;
	color[7].blue = 2;

	color[8].red = 229;
	color[8].green = 210;
	color[8].blue = 134;

	color[9].red = 125;
	color[9].green = 168;
	color[9].blue = 200;

	color[10].red = 223;
	color[10].green = 184;
	color[10].blue = 28;

	color[11].red = 36;
	color[11].green = 167;
	color[11].blue = 10;
}

void initmap() {

	srand(time(NULL));
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			arr[i][j] = 1 + rand() % 11;
		}
	}
	for (int i = 5; i < 9; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			arr[i][j] = arr[i - 4][j];
		}
	}
	for (int i = 0; i < 100; i++)
	{
		int x1 = 1 + rand() % 8;
		int y1 = 1 + rand() % 12;
		int x2 = 1 + rand() % 8;
		int y2 = 1 + rand() % 12;
		int tmp;
		tmp = arr[x1][y1];
		arr[x1][y1] = arr[x2][y2];
		arr[x2][y2] = tmp;
	}
};