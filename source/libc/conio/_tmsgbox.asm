; _TMSGBOX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include malloc.inc
include tchar.inc

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

cp_ok       TCHAR CP_OK,0
cp_cancel   TCHAR CP_CANCEL,0
cp_abort    TCHAR CP_ABORT,0
cp_retry    TCHAR CP_RETRY,0
cp_ignore   TCHAR CP_IGNORE,0
cp_yes      TCHAR CP_YES,0
cp_no       TCHAR CP_NO,0
cp_tryagain TCHAR CP_TRYAGAIN,0
cp_continue TCHAR CP_CONTINUE,0

.template PBINFO
    count   db ?
    col     db 3 dup(?)
    id      db 3 dup(?)
    name    LPTSTR 3 dup(?)
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

    assume rcx:THWND

WndProc proc private hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch uiMsg
      .case WM_CREATE
        _dlshow(hwnd)
        mov rcx,hwnd
        _dlsetfocus(hwnd, [rcx].index)
        .return 0
      .case WM_CLOSE
        _dlclose(hwnd)
        .return 0
    .endsw
    _defwinproc(hwnd, uiMsg, wParam, lParam)
    ret

WndProc endp

    assume rbx:THWND

_msgbox proc uses rbx flags:UINT, title:LPTSTR, format:LPTSTR, argptr:vararg

   .new width:int_t
   .new line:int_t
   .new size:TRECT
   .new rc:TRECT
   .new hwnd:THWND
   .new pb:PBINFO
   .new p:LPTSTR
   .new q:LPTSTR
   .new attrib:word = 0

    mov rbx,_console
    mov size,[rbx].rc

    mov ecx,flags
    and ecx,0x00000007
    imul eax,ecx,PBINFO
    lea rcx,INFO
    add rcx,rax
    mov pb,[rcx]

    .if ( title == NULL )

        mov edx,flags
        and edx,MB_ICONERROR or MB_ICONQUESTION or MB_ICONWARNING

        .if ( edx == MB_ICONERROR )
            mov title,&@CStr("Error")
        .elseif ( edx == MB_ICONWARNING )
            mov title,&@CStr("Warning")
        .else
            mov title,&@CStr("")
        .endif
    .endif

    mov line,0
    _vstprintf(&_bufin, format, &argptr)
    mov width,_tcslen(title)
    lea rbx,_bufin

    .if TCHAR ptr [rbx]

        .repeat
            .break .if !_tcschr(rbx, 10)
            mov rdx,rax
            sub rdx,rbx
ifdef _UNICODE
            shr edx,1
endif
            lea rbx,[rax+TCHAR]
            .if edx >= width
                mov width,edx
            .endif
            inc line
        .until line == 17
    .endif
    .ifd _tcslen(rbx) >= width
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

    _at 0,7,,ecx
    mov eax,W_MOVEABLE or W_SHADE
    .if ( flags & MB_USERICON )
        mov eax,W_MOVEABLE or W_TRANSPARENT
        mov attrib,cx
    .endif

    movzx ebx,pb.count
    or  eax,O_CURSOR
    mov hwnd,_dlopen(rc, ebx, eax, 0)
    .return .if !rax

    mov rbx,rax
    mov eax,flags
    and eax,0x00000070
    .if ( eax == MB_ICONERROR || eax == MB_ICONWARNING )

        _at BG_ERROR,7,' '
        _rcclear([rbx].rc, [rbx].window, eax)
    .endif

    _dltitle(rbx, title)

    mov rc,[rbx].rc
    mov al,rc.row
    mov rc.row,1
    sub al,2
    mov rc.y,al
    mov al,rc.col
    shr al,1
    mov rc.x,al

    movzx eax,pb.count
    .new count:SINT = eax

    .for ( edx = 0, ecx = 0 : ecx < count : ecx++ )

        add dl,pb.col[rcx]
        add dl,2
    .endf
    dec  ecx
    imul eax,ecx,3
    add  eax,edx
    shr  eax,1
    sub  rc.x,al

    .for ( rbx=[rbx].object, ecx=0 : ecx < count : ecx++, rbx=[rbx].next )

        mov al,pb.col[rcx]
        sub al,2
        add al,4
        mov rc.col,al
        mov [rbx].rc,rc
        mov [rbx].type,T_PUSHBUTTON
        mov [rbx].flags,W_CHILD or W_WNDPROC or O_DEXIT
        mov [rbx].index,pb.id[rcx]
        mov [rbx].buffer,pb.name[rcx*LPTSTR]
        mov [rbx].winproc,&_defwinproc
        mov al,rc.col
        add al,3
        add rc.x,al
    .endf

    .for ( rbx=hwnd, rbx=[rbx].object : rbx : rbx=[rbx].next )

        mov rcx,hwnd
        mov [rbx].window,_rcbprc([rcx].rc, [rbx].rc, [rcx].window)

        _dlinit(rbx, [rbx].buffer)
    .endf

    mov eax,flags
    and eax,0x00000300
    xor ecx,ecx
    .if ( eax == MB_DEFBUTTON3 )
        mov ecx,2
    .elseif ( eax == MB_DEFBUTTON2 )
        mov ecx,1
    .endif
    mov rbx,hwnd
    mov [rbx].index,cl

    mov rc,[rbx].rc
    mov rc.y,2
    mov rc.x,2
    sub rc.col,4
    mov p,&_bufin

    .repeat

        .break .if !TCHAR ptr [rax]
        .if ( _tcschr(rax, 10) != NULL )

            mov TCHAR ptr [rax],0
            add rax,TCHAR
        .endif
        mov q,rax
        _rccenter([rbx].rc, [rbx].window, rc, attrib, p)
        inc rc.y
        mov p,q
    .until ( rax == NULL || rc.y == 17+2 )
    .return _dlmodal(rbx, &WndProc)

_msgbox endp

    end
