#include <windows.h>

#define IDR_MYDIALOG 100

const TCHAR CLASSNAME[] = "MyWindowClass";

static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg ) {
    case WM_CLOSE:
    case WM_COMMAND:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow
)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDR_MYDIALOG), NULL, WndProc);
    return 0;
}

