#define UNICODE
#define _UNICODE
#include <windows.h>

#define IDS_HELLO    64
#define IDS_GOODBYE  65

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    wchar_t hello[256], goodbye[256];
    LoadString(hInstance, IDS_HELLO, hello, 256);
    LoadString(hInstance, IDS_GOODBYE, goodbye, 256);
    MessageBox( NULL, goodbye, hello, MB_OK );
    return 0;
}

