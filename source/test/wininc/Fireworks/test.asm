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

EXX         equ 4
EXY         equ 8
AIR         equ 12
SPARC       equ 16

.data
hwnd        HANDLE 0
Bitmap1     PVOID 0
Bitmap2     PVOID 0
hFShells    PVOID 0
EventStop   BOOL FALSE
maxx        UINT 123
maxy        UINT 123
lightx      UINT 123
lighty      UINT 123
flash       UINT 123
motion      UINT 16
GMode       UINT 1
CMode       UINT 0
EMode       UINT 1
click       UINT 0
chemtable   UINT 00e0a0ffh, 00f08030h, 00e6c080h, 0040b070h,  00aad580h
bminf       BITMAPINFO <<40,0,0,1,24,0,0,0,0,0,0>>

.code

random proc base:UINT

    .ifd rand() > base
        mov ecx,base
        xor edx,edx
        div ecx
        mov eax,edx
    .endif
    ret

random endp

Blur proc

    mov     r9,Bitmap2
    mov     r8,Bitmap1
    mov     Bitmap1,r9
    mov     Bitmap2,r8
    pxor    xmm7,xmm7
    mov     rax,0x0001000100010001
    movq    xmm6,rax
    mov     eax,maxx
    lea     rax,[rax+rax*2]
    mov     r10,rax
    imul    maxy
    lea     rcx,[rax+r9]
    lea     rdx,[r10-3]
    add     r10,3
    neg     rdx
    sub     r8,3

    .repeat

        movd        xmm0,[r8]
        punpcklbw   xmm0,xmm7
        movd        xmm1,[r8+8]
        movd        xmm2,[r8+16]
        punpcklbw   xmm1,xmm7
        punpcklbw   xmm2,xmm7

        movd        xmm3,[r8+6]
        movd        xmm4,[r8+14]
        movd        xmm5,[r8+22]
        punpcklbw   xmm3,xmm7
        paddw       xmm0,xmm3
        punpcklbw   xmm4,xmm7
        paddw       xmm1,xmm4
        punpcklbw   xmm5,xmm7
        paddw       xmm2,xmm5

        movd        xmm3,[r8+r10]
        punpcklbw   xmm3,xmm7
        paddw       xmm0,xmm3
        movd        xmm4,[r8+r10+8]
        movd        xmm5,[r8+r10+16]
        punpcklbw   xmm4,xmm7
        paddw       xmm1,xmm4
        punpcklbw   xmm5,xmm7
        paddw       xmm2,xmm5

        movd        xmm3,[r8+rdx]
        punpcklbw   xmm3,xmm7
        paddw       xmm0,xmm3
        movd        xmm4,[r8+rdx+8]
        movd        xmm5,[r8+rdx+16]
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
        movd        [r9],xmm0
        movd        [r9+8],xmm1
        movd        [r9+16],xmm2
        add         r8,12
        add         r9,12

    .until r9 > rcx
    ret

Blur endp

Recycle proc uses rdi rbx hb:ptr, x:UINT, y:UINT

    mov rdi,rcx
    mov [rdi+EXX],edx
    mov [rdi+EXY],r8d
    mov lightx,edx
    mov lighty,r8d
    add flash,3200

    inc random(20)
    mov ecx,500
    mul ecx
    mov ebx,eax
    mov eax,[rdi]
    xor edx,edx
    div ecx
    add edx,ebx
    mov [rdi],edx

    add      random(30),10
    cvtsi2ss xmm1,eax
    mov      eax,10000.0
    movd     xmm2,eax
    mov      eax,1.0
    movd     xmm0,eax
    divss    xmm1,xmm2
    subss    xmm0,xmm1
    movss    [rdi+AIR],xmm0
    add      rdi,SPARC
    cvtsi2ss xmm4,y
    cvtsi2ss xmm3,x
    mov      eax,1000.0
    movd     xmm2,eax
    inc      random(5)
    cvtsi2ss xmm1,eax
    mov      ebx,(400 - 1) * SPARC

    .repeat

        random(2000)
        cvtsi2ss xmm0,eax
        subss xmm0,xmm2
        divss xmm0,xmm2
        mulss xmm0,xmm1
        movss [rdi+rbx+4],xmm0
        movss xmm5,xmm1
        mulss xmm5,xmm5
        mulss xmm0,xmm0
        subss xmm5,xmm0
        sqrtss xmm0,xmm5
        random(2000)
        cvtsi2ss xmm5,eax
        subss xmm5,xmm2
        divss xmm5,xmm2
        mulss xmm0,xmm5
        movss [rdi+rbx+12],xmm0
        movss [rdi+rbx],xmm3
        movss [rdi+rbx+8],xmm4
        sub ebx,16
    .untilb
    ret

Recycle endp

ThrdProc proc uses rsi rdi rbx

  local hdc:HDC, pHeap:PVOID, color:UINT

    mov hdc,GetDC(hwnd)
    mov pHeap,HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x800000*2 + (5 * ((400 shl 4) + SPARC)))

    lea rdx,[rax+0x800000+4096]
    lea rcx,[rax+0x1000000]
    mov hFShells,rcx
    add rax,4096
    mov Bitmap1,rax
    mov Bitmap2,rdx

    .while !EventStop

        mov edi,motion

        .repeat

            mov color,5
            mov rsi,hFShells

            .repeat

                lea rcx,[rsi+SPARC]
                mov edx,color
                dec rdx
                mov r8,hFShells
                add r8,32
                .if !CMode
                    lea r8,chemtable
                .endif
                mov r8d,[r8+rdx*4]
                mov r9d,(400 - 1) * SPARC
                mov r10,Bitmap1

                .repeat

                    movss   xmm0,[rcx+r9+4]
                    pcmpeqw xmm1,xmm1
                    psrld   xmm1,1
                    andps   xmm0,xmm1
                    mov     eax,0.00064
                    movd    xmm1,eax

                    .repeat

                        ucomiss xmm1,xmm0
                        .break .ifnb

                        cvtss2si r11d,[rcx+r9]
                        cvtss2si eax,[rcx+r9+8]
                        .break .if eax >= maxy
                        .break .if r11d >= maxx

                        imul maxx
                        add eax,r11d
                        lea rax,[rax+rax*2]
                        mov edx,r8d
                        mov [r10+rax],dx
                        shr edx,16
                        mov [r10+rax+2],dl
                    .until 1
                    sub r9d,16
                .untilb

                lea rcx,[rsi+SPARC]
                mov eax,(400 - 1) * SPARC

                .if GMode

                    mov   edx,0.00024
                    movd  xmm2,edx
                    movss xmm1,[rcx+AIR-SPARC]
                    .repeat
                        movss xmm0,[rcx+rax+4]
                        mulss xmm0,xmm1
                        movss [rcx+rax+4],xmm0
                        addss xmm0,[rcx+rax]
                        movss [rcx+rax],xmm0
                        movss xmm0,[rcx+rax+12]
                        mulss xmm0,xmm1
                        addss xmm0,xmm2
                        movss [rcx+rax+12],xmm0
                        addss xmm0,[rcx+rax+8]
                        movss [rcx+rax+8],xmm0
                        sub eax,16
                    .untilb

                .else

                    .repeat
                        movss xmm0,[rcx+rax]
                        addss xmm0,[rcx+rax+4]
                        movss [rcx+rax],xmm0
                        movss xmm0,[rcx+rax+8]
                        addss xmm0,[rcx+rax+12]
                        movss [rcx+rax+8],xmm0
                        sub eax,16
                    .untilb
                .endif

                dec dword ptr [rcx-SPARC]
                mov eax,[rcx-SPARC]

                test eax,eax
                .ifs
                    mov ebx,random(maxy)
                    mov ecx,maxx
                    add ecx,ecx
                    random(ecx)
                    mov edx,maxx
                    shr edx,1
                    sub eax,edx
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
                        mov      eax,1.0
                        movd     xmm0,eax
                        subss    xmm0,xmm2
                        mulss    xmm0,xmm0
                        mulss    xmm0,xmm0
                        mov      eax,255.0
                        movd     xmm1,eax
                        mulss    xmm0,xmm1
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
        mov         eax,0.92
        movd        xmm1,eax
        mulss       xmm0,xmm1
        cvtss2si    eax,xmm0
        mov         flash,eax

        Sleep(5)
    .endw

    ReleaseDC(hwnd, hdc)
    HeapFree(GetProcessHeap(), 0, pHeap)
    ret

ThrdProc endp

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .repeat

        .switch edx

        .case WM_MOUSEMOVE
            .endc .if r8d != MK_CONTROL
            xor edx,edx
            mov flash,2400
            mov eax,r9d
            movzx r9d,r9w
            shr eax,16
            mov lightx,r9d
            mov lighty,eax
            .endc

        .case WM_SIZE
            .endc .if r8d == SIZE_MINIMIZED
            mov eax,r9d
            movzx edx,ax
            shr eax,16
            and edx,-4
            mov maxx,edx
            mov maxy,eax
            mov bminf.bmiHeader.biWidth,edx
            neg eax
            mov bminf.bmiHeader.biHeight,eax
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
            .endsw
            .endc

        .case WM_RBUTTONDOWN
            MessageBox(hWnd,
                "SPACE & ENTER keys toggles 'Gravity and Air' and\n"
                "'Light and Smoke' effects respectively.\n"
                "And clicks explode..! close clicks produce more light\n"
                "UP/DOWN & RIGHT for motion speed and color shift.\n"
                "Use ESC to exit.",
                "Fireworks", MB_OK)
            .endc

        .case WM_LBUTTONDOWN
            xor     r10d,r10d
            mov     r10w,r9w
            shr     r9d,16
            mov     r8d,5 - 1
            mov     ecx,click
            dec     ecx
            cmovs   ecx,r8d
            mov     click,ecx
            mov     eax,((400 shl 4) + SPARC)
            imul    ecx
            add     rax,hFShells
            Recycle(rax, r10d, r9d)
            .endc

        .case WM_CLOSE
        .case WM_DESTROY
            mov EventStop,1
            Sleep(10)
            PostQuitMessage(0)
            .endc

        .default
            DefWindowProc( rcx, edx, r8, r9 )
            .break
        .endsw
        xor eax,eax
    .until 1
    ret

WndProc endp

WinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nShowCmd:SINT

  local wc:WNDCLASSEX
  local msg:MSG
  local idThread:UINT
  local rc:RECT

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW or CS_BYTEALIGNCLIENT
    lea rax,WndProc
    mov wc.lpfnWndProc,rax

    xor rax,rax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov wc.hInstance,rcx
    mov wc.hbrBackground,COLOR_MENUTEXT
    mov wc.lpszMenuName,rax

    lea rax,@CStr("WndClass")
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0, 500)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)

    .repeat

        .break .ifd !RegisterClassEx( &wc )

        .break .if !CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, "WndClass", "Fireworks",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, 0 )

        mov hwnd,rax
        GetClientRect( hwnd, &rc )
        mov eax,rc.right
        sub eax,rc.left
        mov edx,rc.bottom
        sub edx,rc.top
        and edx,-4
        mov maxx,edx
        mov maxy,eax
        mov bminf.bmiHeader.biWidth,edx
        neg eax
        mov bminf.bmiHeader.biHeight,eax

        ShowWindow(hwnd, SW_SHOWNORMAL)
        UpdateWindow(hwnd)
        CreateThread(NULL, NULL, &ThrdProc, NULL, NORMAL_PRIORITY_CLASS, &idThread)
        CloseHandle(rax)

        .while GetMessage(&msg,0,0,0)

            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .endw
        mov rax,msg.wParam
    .until 1
    ret

WinMain endp

    end _tstart
