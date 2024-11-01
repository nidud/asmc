; CONFONT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Capture the console window to bitmap using the installed font.
;
include stdio.inc
include windows.inc
include conio.inc
include tchar.inc

define MAXRES 2000

.code

CaptureConsole proc uses rsi rdi rbx file:tstring_t, bits:int_t

    .new hdc:HDC
    .new mdc:HDC = NULL
    .new hbm:HBITMAP = NULL
    .new bmp:BITMAP
    .new written:DWORD = 0
    .new dibsize:DWORD = 0
    .new bmpsize:DWORD = 0
    .new retval:DWORD = 1
    .new rc:RECT = {0}
    .new bf:BITMAPFILEHEADER
    .new color[256]:DWORD
    .new bi:BITMAPINFOHEADER
    .new hWnd:HWND
    .new hFont:HFONT
    .new p:PCHAR_INFO
    .new sr:SMALL_RECT
    .new ci:CONSOLE_SCREEN_BUFFER_INFOEX = {CONSOLE_SCREEN_BUFFER_INFOEX}
    .new cf:CONSOLE_FONT_INFOEX = {CONSOLE_FONT_INFOEX}
    .new consh:HANDLE
    .new x:int_t
    .new y:int_t
    .new colors:int_t = 0

    mov eax,bits
    .switch eax
    .case 1
        mov colors,2
       .endc
    .case 2
        mov colors,4
       .endc
    .case 4
        mov colors,16
       .endc
    .case 8
        mov colors,256
       .endc
    .endsw

    mov consh,GetStdHandle(STD_OUTPUT_HANDLE)
    .if !GetConsoleScreenBufferInfoEx(consh, &ci)

        _putts("GetConsoleScreenBufferInfoEx failed\n")
        .return( 1 )
    .endif
    .if !GetCurrentConsoleFontEx(consh, ci.bFullscreenSupported, &cf)

        _putts("GetCurrentConsoleFontEx failed\n")
        .return( 1 )
    .endif

    movzx   eax,cf.dwFontSize.X
    mov     x,eax
    movzx   ecx,ci.dwSize.X
    mul     ecx
    mov     rc.right,eax

    movzx   eax,cf.dwFontSize.Y
    mov     y,eax
    movzx   ecx,ci.dwSize.Y
    mul     ecx
    mov     rc.bottom,eax

    movzx   eax,ci.dwSize.X
    movzx   ecx,ci.dwSize.Y
    mov     sr.Top,0
    mov     sr.Left,0
    dec     eax
    dec     ecx
    mov     sr.Bottom,cx
    mov     sr.Right,ax
    inc     eax
    inc     ecx
    mul     ecx
    shl     eax,2
    mov     ebx,eax
    mov     p,HeapAlloc(GetProcessHeap(), 0, rbx)
    ReadConsoleOutputW(consh, p, ci.dwSize, 0, &sr)

    mov hWnd,GetConsoleWindow()
    mov hdc,GetDC(hWnd)

    .if ( CreateCompatibleDC(hdc) == NULL )

        _putts("CreateCompatibleDC failed\n")
        jmp done
    .endif
    mov mdc,rax
    .if ( CreateCompatibleBitmap(hdc, rc.right, rc.bottom) == NULL )

        _putts("CreateCompatibleBitmap failed\n")
        jmp done
    .endif
    mov hbm,rax
    SelectObject(mdc, hbm)
    mov hFont,CreateFontW(cf.dwFontSize.Y, cf.dwFontSize.X, 0, 0, cf.FontWeight, 0, 0, 0, DEFAULT_CHARSET,
            OUT_TT_PRECIS, CLIP_STROKE_PRECIS, CLEARTYPE_QUALITY, cf.FontFamily, &cf.FaceName)
    SelectObject(mdc, hFont)

    .for ( rbx = p, esi = 0 : si < ci.dwSize.Y : esi++ )

        .for ( edi = 0 : di < ci.dwSize.X : edi++, rbx+=4 )

            movzx ecx,[rbx].CHAR_INFO.Attributes
            and ecx,0x0F
            SetTextColor(mdc, ci.ColorTable[rcx*4])
            movzx ecx,[rbx].CHAR_INFO.Attributes
            and ecx,0xF0
            shr ecx,4
            SetBkColor(mdc, ci.ColorTable[rcx*4])

            mov eax,esi
            mul y
            mov ecx,eax
            mov eax,edi
            mul x
            mov edx,eax
            TextOutW(mdc, edx, ecx, &[rbx].CHAR_INFO.Char.UnicodeChar, 1)
        .endf
    .endf
    HeapFree(GetProcessHeap(), 0, p)

    GetObjectW(hbm, BITMAP, &bmp)

    mov bi.biSize,BITMAPINFOHEADER
    mov bi.biWidth,bmp.bmWidth
    mov bi.biHeight,bmp.bmHeight
    mov bi.biPlanes,1
    mov bi.biBitCount,bits
    mov bi.biCompression,BI_RGB
    mov bi.biSizeImage,0
    mov bi.biXPelsPerMeter,0
    mov bi.biYPelsPerMeter,0
    mov bi.biClrUsed,colors
    mov bi.biClrImportant,0

    .ifd GetDIBits(hdc, hbm, 0, bmp.bmHeight, 0, &bi, DIB_RGB_COLORS)

        mov bmpsize,bi.biSizeImage

        mov rsi,GlobalAlloc(GHND, bmpsize)
        mov rdi,GlobalLock(rsi)

        .ifd GetDIBits(hdc, hbm, 0, bmp.bmHeight, rdi, &bi, DIB_RGB_COLORS)

            mov rbx,CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)
            mov eax,bmpsize
            add eax,BITMAPFILEHEADER + BITMAPINFOHEADER
            mov dibsize,eax
            mov bf.bfOffBits, BITMAPFILEHEADER + BITMAPINFOHEADER
            mov bf.bfSize,dibsize
            mov bf.bfType,0x4D42 ; BM.
            WriteFile(rbx, &bf, BITMAPFILEHEADER, &written, NULL)
            WriteFile(rbx, &bi, BITMAPINFOHEADER, &written, NULL)
            .if ( colors )
                imul ecx,colors,4
                WriteFile(rbx, &color, ecx, &written, NULL)
            .endif
            WriteFile(rbx, rdi, bmpsize, &written, NULL)
            CloseHandle(rbx)
            mov retval,0
        .else
            _putts("GetDIBits failed\n")
        .endif
        GlobalUnlock(rsi)
        GlobalFree(rsi)
    .else
        _putts("GetDIBits failed\n")
    .endif
done:
    DeleteObject(hbm)
    DeleteObject(mdc)
    ReleaseDC(hWnd, hdc)
    mov eax,retval
    ret

CaptureConsole endp


_tmain proc argc:int_t, argv:array_t

    .new file:tstring_t = "default.bmp"
    .new bits:int_t = 8

    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rcx,argv
        mov rcx,[rcx+rbx*size_t]
        movzx eax,TCHAR ptr [rcx]

        .if ( eax == '-' || eax == '/' )

            movzx eax,TCHAR ptr [rcx+TCHAR]
            .switch eax
            .case '1'
                .if ( TCHAR ptr [rcx+TCHAR*2] == '6' )
                    mov bits,16
                .else
                    mov bits,1
                .endif
                .endc
            .case '2'
                .if ( TCHAR ptr [rcx+TCHAR*2] == '4' )
                    mov bits,24
                .else
                    mov bits,2
                .endif
                .endc
            .case '4'
                mov bits,4
               .endc
            .case '8'
                mov bits,8
               .endc
            .case '3'
                mov bits,32
               .endc
            .default
                _putts(
                    "usage: CONFONT [ -<bits_per_pixel> ] [ <bmp_file> ]\n"
                    "\n"
                    "-1        2 colors (monochrome)\n"
                    "-2        4 colors\n"
                    "-4       16 colors\n"
                    "-8      256 colors (default)\n"
                    "-16    2^16 colors\n"
                    "-24    2^24 colors\n"
                    "-32    2^32 colors\n"
                    "\n" )
                .return( 0 )
            .endsw
        .else
            mov file,rcx
        .endif
    .endf
    CaptureConsole(file, bits)
    ret

_tmain endp

    end _tstart
