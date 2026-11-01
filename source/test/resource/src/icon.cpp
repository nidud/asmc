#include <windows.h>

#define IDR_MYICON 100

const TCHAR CLASSNAME[] = "MyWindowClass";

static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg ) {
    case WM_PAINT:
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return( 0 );
    case WM_DESTROY:
        PostQuitMessage(0);
        return( 0 );
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow
)
{

    WNDCLASSEX wc{};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MYICON));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CLASSNAME;
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MYICON));

    RegisterClassEx(&wc);
    CreateWindowEx(0, CLASSNAME, CLASSNAME,
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100, 250, 200, NULL, NULL, hInstance, NULL);
    MSG msg;
    BOOL bRet;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

