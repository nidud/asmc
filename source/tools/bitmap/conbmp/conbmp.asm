; CONBMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Capture the console window to (a relatively large) bitmap.
;
include stdio.inc
include windows.inc
include tchar.inc

define MAXRES 2000

.code

_tmain proc argc:int_t, argv:array_t

   .new hdc:HDC
   .new mdc:HDC = NULL
   .new hbm:HBITMAP = NULL
   .new bmp:BITMAP
   .new written:DWORD = 0
   .new dibsize:DWORD = 0
   .new bmpsize:DWORD = 0
   .new retval:DWORD = 1
   .new rc:RECT
   .new bf:BITMAPFILEHEADER
   .new bi:BITMAPINFOHEADER
   .new hWnd:HWND
   .new file:tstring_t = "default.bmp"

    .if ( argc > 1 )

        mov rcx,argv
        mov rbx,[rcx+size_t]
        .if ( byte ptr [rbx] == '-' || byte ptr [rbx] == '/' )
            _putts("usage: CONBMP [<bmp_file>]\n")
            .return( 0 )
        .endif
        mov file,rbx
    .endif

    mov hWnd,GetConsoleWindow()
    GetClientRect(hWnd, &rc)
    mov hdc,GetDC(hWnd)
    ;
    ; Calculate the "actual" size of the console window
    ;
    .for ( ebx = rc.right : ebx < MAXRES : ebx++ )
        .break .ifd ( GetPixel(hdc, ebx, 0) == -1 )
    .endf
    mov rc.right,ebx
    .for ( ebx = rc.bottom : ebx < MAXRES : ebx++ )
        .break .ifd ( GetPixel(hdc, 0, ebx) == -1 )
    .endf
    mov rc.bottom,ebx

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
    .ifd ( BitBlt(mdc, 0, 0, rc.right, rc.bottom, hdc, 0, 0, SRCCOPY) == 0 )

        _putts("BitBlt failed\n")
        jmp done
    .endif
    GetObject(hbm, BITMAP, &bmp)

    mov bi.biSize,BITMAPINFOHEADER
    mov bi.biWidth,bmp.bmWidth
    mov bi.biHeight,bmp.bmHeight
    mov bi.biPlanes,1
    mov bi.biBitCount,32
    mov bi.biCompression,BI_RGB
    mov bi.biSizeImage,0
    mov bi.biXPelsPerMeter,0
    mov bi.biYPelsPerMeter,0
    mov bi.biClrUsed,0
    mov bi.biClrImportant,0

    movzx ecx,bi.biBitCount
    mov eax,bmp.bmWidth
    mul ecx
    add eax,31
    shr eax,5
    shl eax,2
    mul bmp.bmHeight
    mov bmpsize,eax

    mov rsi,GlobalAlloc(GHND, bmpsize)
    mov rdi,GlobalLock(rsi)
    GetDIBits(hdc, hbm, 0, bmp.bmHeight, rdi, &bi, DIB_RGB_COLORS)
    mov rbx,CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)
    mov eax,bmpsize
    add eax,BITMAPFILEHEADER + BITMAPINFOHEADER
    mov dibsize,eax
    mov bf.bfOffBits, BITMAPFILEHEADER + BITMAPINFOHEADER
    mov bf.bfSize,dibsize
    mov bf.bfType,0x4D42 ; BM.
    WriteFile(rbx, &bf, BITMAPFILEHEADER, &written, NULL)
    WriteFile(rbx, &bi, BITMAPINFOHEADER, &written, NULL)
    WriteFile(rbx, rdi, bmpsize, &written, NULL)
    GlobalUnlock(rsi)
    GlobalFree(rsi)
    CloseHandle(rbx)
    mov retval,0
done:
    DeleteObject(hbm)
    DeleteObject(mdc)
    ReleaseDC(hWnd, hdc)
    mov eax,retval
    ret

_tmain endp

    end _tstart
