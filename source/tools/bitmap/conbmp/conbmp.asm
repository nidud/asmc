; CONBMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Capture the console window to bitmap.
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
   .new color[256]:DWORD
   .new bi:BITMAPINFOHEADER
   .new hWnd:HWND
   .new file:tstring_t = "default.bmp"
   .new bits:int_t = 4
   .new colors:int_t = 16

    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rcx,argv
        mov rcx,[rcx+rbx*size_t]
        mov eax,[rcx]
        .if ( al == '-' || al == '/' )
            shr eax,8
            .switch al
            .case '1'
                .if ( ah == '6' )
                    mov bits,16
                    mov colors,0
                .else
                    mov bits,1
                    mov colors,2
                .endif
                .endc
            .case '2'
                .if ( ah == '4' )
                    mov bits,24
                    mov colors,0
                .else
                    mov bits,2
                    mov colors,4
                .endif
                .endc
            .case '4'
                mov bits,4
                mov colors,16
               .endc
            .case '8'
                mov bits,8
                mov colors,256
               .endc
            .case '3'
                mov bits,32
                mov colors,0
               .endc
            .default
                _putts(
                    "usage: CONBMP [ -<bits_per_pixel> ] [ <bmp_file> ]\n"
                    "\n"
                    "-1        2 colors (monochrome)\n"
                    "-2        4 colors\n"
                    "-4       16 colors (default)\n"
                    "-8      256 colors\n"
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

_tmain endp

    end _tstart
