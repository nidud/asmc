; _MSGBOXW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include malloc.inc

define CP_OK        <"&Ok">
define CP_CANCEL    <"&Cancel">
define CP_ABORT     <"&Abort">
define CP_RETRY     <"&Retry">
define CP_IGNORE    <"&Ignore">
define CP_YES       <"&Yes">
define CP_NO        <"&No">
define CP_TRYAGAIN  <"&Try Again">
define CP_CONTINUE  <"C&ontinue">

   .data

   option wstring:on

cp_ok       wchar_t CP_OK,0
cp_cancel   wchar_t CP_CANCEL,0
cp_abort    wchar_t CP_ABORT,0
cp_retry    wchar_t CP_RETRY,0
cp_ignore   wchar_t CP_IGNORE,0
cp_yes      wchar_t CP_YES,0
cp_no       wchar_t CP_NO,0
cp_tryagain wchar_t CP_TRYAGAIN,0
cp_continue wchar_t CP_CONTINUE,0

.template PBINFO
    count   db ?
    col     db 3 dup(?)
    id      db 3 dup(?)
    name    LPWSTR 3 dup(?)
   .ends

INFO PBINFO {
        1, ; MB_OK
        { lengthof(cp_ok) },
        { IDOK },
        { cp_ok }
    },{ 2, ; MB_OKCANCEL
        { lengthof(cp_ok), lengthof(cp_cancel) },
        { IDOK, IDCANCEL },
        { cp_ok, cp_cancel }
    },{ 3, ; MB_ABORTRETRYIGNORE
        { lengthof(cp_abort), lengthof(cp_retry), lengthof(cp_ignore) },
        { IDABORT,  IDRETRY, IDIGNORE },
        { cp_abort, cp_retry, cp_ignore }
    },{ 3, ; MB_YESNOCANCEL
        { lengthof(cp_yes), lengthof(cp_no), lengthof(cp_cancel) },
        { IDYES,  IDNO, IDCANCEL },
        { cp_yes, cp_no, cp_cancel }
    },{ 2, ; MB_YESNO
        { lengthof(cp_yes), lengthof(cp_no) },
        { IDYES,  IDNO },
        { cp_yes, cp_no }
    },{ 2, ; MB_RETRYCANCEL
        { lengthof(cp_retry), lengthof(cp_cancel) },
        { IDRETRY,  IDCANCEL },
        { cp_retry, cp_cancel }
    },{ 3, ; MB_CANCELTRYCONTINUE
        { lengthof(cp_cancel), lengthof(cp_tryagain), lengthof(cp_continue) },
        { IDCANCEL, IDTRYAGAIN, IDCONTINUE },
        { cp_cancel, cp_tryagain, cp_continue }
    }

    .code

WndProc proc private hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch uiMsg
      .case WM_CREATE
        _dlshow(hwnd)
        mov rcx,hwnd
        _dlsetfocus(hwnd, [rcx].TCLASS.index)
        .return 0
      .case WM_CLOSE
        _dlclose(hwnd)
        .return 0
    .endsw
    _defwinproc(hwnd, uiMsg, wParam, lParam)
    ret

WndProc endp

    assume rsi:ptr PBINFO
    assume rbx:THWND

_msgboxW proc uses rsi rdi rbx flags:UINT, title:LPWSTR, format:LPWSTR, argptr:vararg

   .new width:int_t
   .new line:int_t
   .new size:TRECT = { 0, 0, _consize.X, _consize.Y }
   .new rc:TRECT
   .new info:ptr PBINFO
   .new attrib:word = 0

    mov ecx,flags
    and ecx,0x00000007
    imul eax,ecx,PBINFO
    lea rcx,INFO
    add rax,rcx
    mov info,rax

    mov rdi,title
    .if rdi == NULL
        mov edx,flags
        and edx,MB_ICONERROR or MB_ICONQUESTION or MB_ICONWARNING
        .if edx == MB_ICONERROR
            lea rdi,@CStr("Error")
        .elseif edx == MB_ICONWARNING
            lea rdi,@CStr("Warning")
        .else
            lea rdi,@CStr("")
        .endif
    .endif
    lea rsi,_bufin
    mov line,0

    vswprintf(rsi, format, &argptr)
    mov width,wcslen(rdi)

    .if wchar_t ptr [rsi]
        .repeat
            .break .if !wcschr(rsi, 10)
            mov rdx,rax
            sub rdx,rsi
            shr edx,1
            lea rsi,[rax+wchar_t]
            .if edx >= width
                mov width,edx
            .endif
            inc line
        .until line == 17
    .endif
    .ifd wcslen(rsi) >= width
        mov width,eax
    .endif
    mov eax,width

    mov dl,2
    mov dh,76

    .if ( al && al < 70 )

        mov dh,al
        add dh,8
        mov dl,80
        sub dl,dh
        shr dl,1
    .endif

    .if ( dh < 48 )

        mov dl,16
        mov dh,48
    .endif

    mov rc.x,dl
    mov rc.y,7
    mov ecx,line
    add cl,6
    mov rc.row,cl
    mov rc.col,dh
    shr eax,16
    add al,7
    .if ( al > size.row )
        mov rc.y,1
    .endif

    movzx ecx,at_foreground[FG_DIALOG]
    or cl, at_background[BG_DIALOG]
    mov eax,W_MOVEABLE or W_COLOR or W_SHADE
    .if ( flags & MB_USERICON )
        mov eax,W_MOVEABLE or W_COLOR or W_TRANSPARENT
        mov attrib,cx
    .endif
    mov rsi,info
    movzx edx,[rsi].count
    mov rbx,_dlopen(rc, edx, eax, 0)
    .return .if !rax

    mov eax,flags
    and eax,0x00000070
    .if ( eax == MB_ICONERROR || eax == MB_ICONWARNING )

        _rcclear(.rc, .window, _getattrib(FG_DESKTOP, BG_ERROR))
    .endif

    _dltitleW(rbx, rdi)

    mov rc,[rbx].rc
    mov al,rc.row
    mov rc.row,1
    sub al,2
    mov rc.y,al
    mov al,rc.col
    shr al,1
    mov rc.x,al

    movzx eax,[rsi].count
    .new count:SINT = eax

    .for ( edx = 0, ecx = 0 : ecx < count : ecx++ )

        add dl,[rsi].col[rcx]
        add dl,2
    .endf
    dec  ecx
    imul eax,ecx,3
    add  eax,edx
    shr  eax,1
    sub  rc.x,al

    .for ( edi = 0 : edi < count : edi++ )

        mov al,[rsi].col[rdi]
        sub al,2
        add al,4
        mov rc.col,al
        _dlinitW(rbx, edi, rc, O_DEXIT, T_PUSHBUTTON, [rsi].id[rdi], [rsi].name[rdi*LPWSTR])
        mov al,rc.col
        add al,3
        add rc.x,al
    .endf

    mov eax,flags
    and eax,0x00000300
    xor ecx,ecx
    .if ( eax == MB_DEFBUTTON3 )
        mov ecx,2
    .elseif ( eax == MB_DEFBUTTON2 )
        mov ecx,1
    .endif
    mov [rbx].index,cl

    lea rsi,_bufin
    mov rdi,rsi
    mov rc,[rbx].rc
    mov rc.y,2
    mov rc.x,2
    sub rc.col,4

    .repeat

        .break .if !wchar_t ptr [rsi]

        mov rsi,wcschr(rdi, 10)
        .if ( rax != NULL )

            mov wchar_t ptr [rsi],0
            add rsi,wchar_t
        .endif
        _rccenterW([rbx].rc, [rbx].window, rc, attrib, rdi)
        mov rdi,rsi
        inc rc.y
    .until ( rdi == NULL || rc.y == 17+2 )
    .return _dlmodal(rbx, &WndProc)

_msgboxW endp

    end
