;
; v2.28:
;  - error in winuser.inc: WS_EX_OVERLAPPEDWINDOW
;  - added rand()/srand()/rand_s()
;
; Source:
;  - http://www.ronybc.com/firecode.php
;

include windows.inc
include tchar.inc

define EXX      4
define EXY      8
define AIR      12
define SPARC    16

.data
 hwnd       HANDLE 0
 rect       RECT <>
 Bitmap1    PVOID 0
 Bitmap2    PVOID 0
 hFShells   PVOID 0
 pHeap      PVOID 0
 ProcessH   PVOID 0
 EventStop  UINT 0
 maxx       UINT 123
 maxy       UINT 123
 lightx     UINT 123
 lighty     UINT 123
 flash      UINT 123
 motion     UINT 16
 GMode      UINT 1
 CMode      UINT 0
 EMode      UINT 1
 click      UINT 0
 FullScreen UINT 0
 chemtable  UINT 00e0a0ffh, 00f08030h, 00e6c080h, 0040b070h,  00aad580h
 bminf      BITMAPINFO <<40,0,0,1,24,0,0,0,0,0,0>>

.code

Blur proc uses rsi rdi rbx

    mov     rdi,Bitmap2
    mov     rsi,Bitmap1
    mov     Bitmap1,rdi
    mov     Bitmap2,rsi
    pxor    xmm7,xmm7
    mov     rax,0x0001000100010001
    movq    xmm6,rax
    mov     eax,maxx
    lea     rax,[rax+rax*2]
    mov     rbx,rax
    imul    maxy
    lea     rcx,[rax+rdi]
    lea     rdx,[rbx-3]
    add     rbx,3
    neg     rdx
    sub     rsi,3

    .repeat

        movd        xmm0,[rsi]
        punpcklbw   xmm0,xmm7
        movd        xmm1,[rsi+8]
        movd        xmm2,[rsi+16]
        punpcklbw   xmm1,xmm7
        punpcklbw   xmm2,xmm7

        movd        xmm3,[rsi+6]
        movd        xmm4,[rsi+14]
        movd        xmm5,[rsi+22]
        punpcklbw   xmm3,xmm7
        paddw       xmm0,xmm3
        punpcklbw   xmm4,xmm7
        paddw       xmm1,xmm4
        punpcklbw   xmm5,xmm7
        paddw       xmm2,xmm5

        movd        xmm3,[rsi+rbx]
        punpcklbw   xmm3,xmm7
        paddw       xmm0,xmm3
        movd        xmm4,[rsi+rbx+8]
        movd        xmm5,[rsi+rbx+16]
        punpcklbw   xmm4,xmm7
        paddw       xmm1,xmm4
        punpcklbw   xmm5,xmm7
        paddw       xmm2,xmm5

        movd        xmm3,[rsi+rdx]
        punpcklbw   xmm3,xmm7
        paddw       xmm0,xmm3
        movd        xmm4,[rsi+rdx+8]
        movd        xmm5,[rsi+rdx+16]
        punpcklbw   xmm4,xmm7
        paddw       xmm1,xmm4
        punpcklbw   xmm5,xmm7
        paddw       xmm2,xmm5

        psrlw       xmm0,2
        psrlw       xmm1,2
        psrlw       xmm2,2
        psubusw     xmm0,xmm6
        psubusw     xmm1,xmm6
        psubusw     xmm2,xmm6
        packuswb    xmm0,xmm7
        packuswb    xmm1,xmm7
        packuswb    xmm2,xmm7
        movd        [rdi],xmm0
        movd        [rdi+8],xmm1
        movd        [rdi+16],xmm2
        add         rsi,12
        add         rdi,12

    .until ( rdi > rcx )
    ret

Blur endp


Recycle proc uses rdi rbx hb:ptr, x:UINT, y:UINT

    ldr     rdi,rcx
    ldr     edx,x
    ldr     eax,y

    mov     [rdi+EXX],edx
    mov     [rdi+EXY],eax
    mov     lightx,edx
    mov     lighty,eax
    add     flash,3200

    rdrand      eax
    xor         ecx,ecx
    and         eax,31
    setz        cl
    add         eax,ecx
    mov         ecx,480
    mul         ecx
    mov         ebx,eax
    mov         eax,[rdi]
    xor         edx,edx
    div         ecx
    add         edx,ebx
    mov         [rdi],edx

    rdrand      eax
    and         eax,31
    add         eax,10
    cvtsi2ss    xmm1,eax
    movss       xmm0,1.0
    divss       xmm1,10000.0
    subss       xmm0,xmm1
    movss       [rdi+AIR],xmm0
    cvtsi2ss    xmm4,y
    cvtsi2ss    xmm3,x

    rdrand      eax
    xor         ecx,ecx
    and         eax,7
    setz        cl
    add         eax,ecx
    cvtsi2ss    xmm1,eax
    movss       xmm2,1000.0
    mov         ebx,(400 - 1) * SPARC
    add         rdi,SPARC

    .repeat

        rdrand      eax
        and         eax,2047
        cvtsi2ss    xmm0,eax
        subss       xmm0,xmm2
        divss       xmm0,xmm2
        mulss       xmm0,xmm1
        movss       [rdi+rbx+4],xmm0
        movss       xmm5,xmm1
        mulss       xmm5,xmm5
        mulss       xmm0,xmm0
        subss       xmm5,xmm0
        sqrtss      xmm0,xmm5

        rdrand      eax
        and         eax,2047
        cvtsi2ss    xmm5,eax
        subss       xmm5,xmm2
        divss       xmm5,xmm2
        mulss       xmm0,xmm5
        movss       [rdi+rbx+12],xmm0
        movss       [rdi+rbx],xmm3
        movss       [rdi+rbx+8],xmm4
        sub         ebx,16
    .untilb
    ret

Recycle endp


ThrdProc proc uses rsi rdi rbx

  local hdc:HDC, color:UINT

    mov hdc,GetDC(hwnd)

    .while !EventStop

        mov edi,motion

        .repeat

            mov color,5
            mov rsi,hFShells

            .repeat

                lea     rcx,[rsi+SPARC]
                mov     edx,color
                dec     rdx
                mov     r8,hFShells
                add     r8,32
                lea     rax,chemtable
                cmp     CMode,0
                cmovz   r8,rax
                mov     r8d,[r8+rdx*4]
                mov     r9d,(400 - 1) * SPARC
                mov     r10,Bitmap1

                .repeat

                    mov eax,[rcx+r9+4]
                    and eax,0x7FFFFFFF
                    movd xmm0,eax
                    .if ( xmm0 > 0.00064 )

                        cvtss2si edx,[rcx+r9]
                        cvtss2si eax,[rcx+r9+8]

                        .if ( eax < maxy && edx < maxx )

                            imul    eax,maxx
                            add     eax,edx
                            lea     rax,[rax+rax*2]
                            mov     edx,r8d
                            mov     [r10+rax],dx
                            shr     edx,16
                            mov     [r10+rax+2],dl
                        .endif
                    .endif
                    sub r9d,16
                .untilb

                lea rcx,[rsi+SPARC]
                mov eax,(400 - 1) * SPARC

                .if GMode

                    movss xmm1,[rcx+AIR-SPARC]
                    .repeat
                        movss   xmm0,[rcx+rax+4]
                        mulss   xmm0,xmm1
                        movss   [rcx+rax+4],xmm0
                        addss   xmm0,[rcx+rax]
                        movss   [rcx+rax],xmm0
                        movss   xmm0,[rcx+rax+12]
                        mulss   xmm0,xmm1
                        addss   xmm0,0.00024
                        movss   [rcx+rax+12],xmm0
                        addss   xmm0,[rcx+rax+8]
                        movss   [rcx+rax+8],xmm0
                        sub     eax,16
                    .untilb

                .else

                    .repeat
                        movss   xmm0,[rcx+rax]
                        addss   xmm0,[rcx+rax+4]
                        movss   [rcx+rax],xmm0
                        movss   xmm0,[rcx+rax+8]
                        addss   xmm0,[rcx+rax+12]
                        movss   [rcx+rax+8],xmm0
                        sub     eax,16
                    .untilb
                .endif

                dec dword ptr [rcx-SPARC]
                .ifs
                    mov ecx,maxy
                    rdrand eax
                    .if ( eax > ecx )
                        xor edx,edx
                        div ecx
                        mov eax,edx
                    .endif
                    mov ebx,eax
                    rdrand eax
                    mov ecx,maxx
                    add ecx,ecx
                    .if ( eax > ecx )
                        xor edx,edx
                        div ecx
                        mov eax,edx
                    .endif
                    shr ecx,2
                    sub eax,ecx
                    Recycle(rsi, eax, ebx)
                .endif
                add rsi,400 * SPARC + SPARC
                dec color
            .untilz
            dec edi
        .untilz

        .if EMode

            .if CMode
                Blur()
            .endif

            mov rsi,Bitmap1
            mov rdi,Bitmap2
            xor r9d,r9d
            mov ecx,maxx

            .repeat

                xor r8d,r8d

                .repeat

                    mov     eax,r9d
                    sub     eax,lighty
                    imul    eax
                    mov     ebx,r8d
                    sub     ebx,lightx
                    imul    ebx,ebx
                    add     eax,ebx
                    mov     edx,flash
                    shr     edx,1
                    imul    edx,edx
                    xor     ebx,ebx

                    .if eax <= edx

                        cvtsi2ss xmm2,eax
                        sqrtss   xmm2,xmm2
                        mov      eax,flash
                        shr      eax,1
                        cvtsi2ss xmm1,eax
                        divss    xmm2,xmm1
                        movss    xmm0,1.0
                        subss    xmm0,xmm2
                        mulss    xmm0,xmm0
                        mulss    xmm0,xmm0
                        mulss    xmm0,255.0
                        cvtss2si ebx,xmm0
                        mov      rax,0x0000010101010101
                        imul     rbx,rax
                    .endif

                    mov     eax,r9d
                    mul     ecx
                    add     eax,r8d
                    lea     rax,[rax+rax*2]
                    lea     rdx,[rcx+rcx*2]
                    add     rdx,rax
                    movq    xmm2,rbx
                    movq    xmm0,[rsi+rax]
                    movq    xmm1,[rsi+rdx]
                    paddusb xmm0,xmm2
                    paddusb xmm1,xmm2
                    movq    [rdi+rax],xmm0
                    movq    [rdi+rdx],xmm1
                    add     r8d,2
                .until r8d > ecx
                add r9d,2
            .until r9d >= maxy

            SetDIBitsToDevice(hdc, 0, 0, maxx, maxy, 0, 0, 0, maxy, Bitmap2, &bminf, DIB_RGB_COLORS)

            .if !CMode
                Blur()
            .endif
        .else

            SetDIBitsToDevice(hdc, 0, 0, maxx, maxy, 0, 0, 0, maxy, Bitmap1, &bminf, DIB_RGB_COLORS)
            mov eax,maxx
            mul maxy
            lea rcx,[rax+rax*2]
            mov rdi,Bitmap1
            xor eax,eax
            rep stosb
        .endif

        cvtsi2ss    xmm0,flash
        mulss       xmm0,0.92
        cvtss2si    eax,xmm0
        mov         flash,eax

        Sleep(5)
    .endw
    ReleaseDC(hwnd, hdc)
    mov EventStop,0
    ret

ThrdProc endp


GoFullScreen proc

   .new hdc:HDC
   .new xSpan:int_t
   .new ySpan:int_t
   .new xBorder:int_t
   .new yCaption:int_t
   .new yBorder:int_t
   .new xOrigin:int_t
   .new yOrigin:int_t

    GetClientRect(hwnd, &rect)

    mov FullScreen,TRUE

    SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong(hwnd, GWL_STYLE,  WS_CAPTION or WS_SYSMENU)

    mov hdc,GetDC(hwnd)
    mov xSpan,GetSystemMetrics(SM_CXSCREEN)
    mov ySpan,GetSystemMetrics(SM_CYSCREEN)
    ReleaseDC(hwnd, hdc)

    ; Calculate the size of system elements.

    mov xBorder,GetSystemMetrics(SM_CXFRAME)
    mov yCaption,GetSystemMetrics(SM_CYCAPTION)
    mov yBorder,GetSystemMetrics(SM_CYFRAME)

    ; Calculate the window origin and span for full-screen mode.

    mov     eax,xBorder
    neg     eax
    mov     xOrigin,eax
    mov     eax,yBorder
    neg     eax
    sub     eax,yCaption
    mov     yOrigin,eax
    imul    eax,xBorder,2
    add     xSpan,eax
    imul    eax,yBorder,2
    add     eax,yCaption
    add     ySpan,eax

    SetWindowPos(hwnd, HWND_TOPMOST, xOrigin, yOrigin, xSpan, ySpan, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

GoFullScreen endp


; Makes the host window resizable and focusable.

GoPartialScreen proc

    mov FullScreen,FALSE
    SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW)
    SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

GoPartialScreen endp


WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch edx
    .case WM_MOUSEMOVE
        .endc .if r8d != MK_CONTROL
        mov     flash,2400
        mov     eax,r9d
        movzx   r9d,r9w
        shr     eax,16
        mov     lightx,r9d
        mov     lighty,eax
       .endc
    .case WM_SIZE
        .endc .if r8d == SIZE_MINIMIZED
        .if ( ProcessH )
            lock inc EventStop
            .while 1
                Sleep(5)
               .break .if ( EventStop == 0 )
            .endw
            HeapFree(ProcessH, 0, pHeap)
        .else
            mov ProcessH,GetProcessHeap()
        .endif
        movzx   edx,word ptr lParam
        movzx   eax,word ptr lParam[2]
        and     edx,-4
        mov     maxx,edx
        mov     maxy,eax
        mov     bminf.bmiHeader.biWidth,edx
        neg     eax
        mov     bminf.bmiHeader.biHeight,eax
        mov     eax,maxy
        mul     maxx
        lea     ebx,[rax*4]
        lea     ecx,[rbx*2][(5 * ((400 shl 4) + SPARC))]
        mov     pHeap,HeapAlloc(ProcessH, HEAP_ZERO_MEMORY, rcx)
        lea     rcx,[rax+rbx*2]
        mov     hFShells,rcx
        imul    ecx,maxx,4
        lea     rdx,[rax+rbx]
        add     rax,rcx
        add     rdx,rcx
        mov     Bitmap1,rax
        mov     Bitmap2,rdx
        CloseHandle(CreateThread(NULL, NULL, &ThrdProc, NULL, NORMAL_PRIORITY_CLASS, NULL))
       .endc
    .case WM_KEYDOWN
        .switch r8d
        .case VK_SPACE
            xor GMode,1
           .endc
        .case VK_RETURN
            xor EMode,1
            mov flash,0
           .endc
        .case VK_ESCAPE
            .gotosw(1:WM_CLOSE)
        .case VK_F1
            .gotosw(1:WM_RBUTTONDOWN)
        .case VK_UP
            .endc .if motion >= 64
            inc motion
           .endc
        .case VK_DOWN
            .endc .if motion == 1
            dec motion
           .endc
        .case VK_RIGHT
            xor CMode,1
           .endc
        .case VK_F11
            .if ( FullScreen )
                GoPartialScreen()
            .else
                GoFullScreen()
            .endif
            .endc
        .endsw
        .endc
    .case WM_RBUTTONDOWN
        MessageBox(hWnd,
            "SPACE & ENTER keys toggles 'Gravity and Air' and\n"
            "'Light and Smoke' effects respectively.\n"
            "And clicks explode..! close clicks produce more light\n"
            "UP/DOWN & RIGHT for motion speed and color shift.\n"
            "Use F11 to toggle full screen and ESC to exit.",
            "Fireworks", MB_OK)
        .endc
    .case WM_LBUTTONDOWN
        movzx   edx,r9w
        shr     r9d,16
        mov     eax,5 - 1
        mov     ecx,click
        dec     ecx
        cmovs   ecx,eax
        mov     click,ecx
        imul    ecx,ecx,((400 shl 4) + SPARC)
        add     rcx,hFShells
        Recycle(rcx, edx, r9d)
       .endc
    .case WM_CLOSE
    .case WM_DESTROY
        lock inc EventStop
        Sleep(10)
        PostQuitMessage(0)
       .endc
    .default
        .return DefWindowProc( rcx, edx, r8, r9 )
    .endsw
    xor eax,eax
    ret

WndProc endp


_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, rc:RECT

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW or CS_BYTEALIGNCLIENT
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hInstance,       rcx
    mov wc.hbrBackground,   COLOR_MENUTEXT
    mov wc.lpszMenuName,    rax
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("WndClass")
    mov wc.hIcon,           LoadIcon(0, 500)
    mov wc.hIconSm,         rax
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)


    .ifd RegisterClassEx( &wc )

        mov hwnd,CreateWindowEx(
                WS_EX_OVERLAPPEDWINDOW,
                "WndClass",
                "Fireworks",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL, NULL, hInstance, 0 )

        .if ( rax )

            ShowWindow( rax, SW_SHOWNORMAL )

            .while GetMessage( &msg, 0, 0, 0 )

                TranslateMessage( &msg )
                DispatchMessage( &msg )
            .endw
            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart
