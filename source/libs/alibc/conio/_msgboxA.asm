; _MSGBOXA.ASM--
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

cp_ok       char_t CP_OK,0
cp_cancel   char_t CP_CANCEL,0
cp_abort    char_t CP_ABORT,0
cp_retry    char_t CP_RETRY,0
cp_ignore   char_t CP_IGNORE,0
cp_yes      char_t CP_YES,0
cp_no       char_t CP_NO,0
cp_tryagain char_t CP_TRYAGAIN,0
cp_continue char_t CP_CONTINUE,0

.template PBINFO
    count   db ?
    col     db 3 dup(?)
    id      db 3 dup(?)
    name    LPSTR 3 dup(?)
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

    assume rbx:THWND

WndProc proc private uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch esi
      .case WM_CREATE
        mov rbx,rdi
        _dlshow(rdi)
        _dlsetfocus(rbx, [rbx].index)
        .return 0
      .case WM_CLOSE
        _dlclose(rdi)
        .return 0
    .endsw
    _defwinproc(rdi, esi, rdx, rcx)
    ret

WndProc endp

    assume r12:ptr PBINFO

_msgboxA proc uses rbx r12 r13 r14 flags:UINT, title:LPSTR, format:LPSTR, argptr:vararg

   .new width:int_t
   .new line:int_t
   .new size:TRECT
   .new rc:TRECT
   .new info:ptr PBINFO
   .new attrib:word = 0
   .new args:ptr = rax

    mov r12,rdx
    mov rbx,_console
    mov size,[rbx].rc

    mov ecx,edi
    and ecx,0x00000007
    imul eax,ecx,PBINFO
    lea rcx,INFO
    add rax,rcx
    mov info,rax

    mov r13,rsi
    .if r13 == NULL
        mov edx,edi
        and edx,MB_ICONERROR or MB_ICONQUESTION or MB_ICONWARNING
        .if edx == MB_ICONERROR
            lea r13,@CStr("Error")
        .elseif edx == MB_ICONWARNING
            lea r13,@CStr("Warning")
        .else
            lea r13,@CStr("")
        .endif
    .endif
    lea r14,_bufin
    mov line,0

    vsprintf(r14, r12, args)
    mov width,strlen(r13)

    .if char_t ptr [r14]
        .repeat
            .break .if !strchr(r14, 10)
            mov rdx,rax
            sub rdx,r14
            lea r14,[rax+char_t]
            .if edx >= width
                mov width,edx
            .endif
            inc line
        .until line == 17
    .endif
    .ifd strlen(r14) >= width
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

    mov ecx,_getat(0, 7)
    mov eax,W_MOVEABLE or W_SHADE
    .if ( flags & MB_USERICON )
        mov eax,W_MOVEABLE or W_TRANSPARENT
        mov attrib,cx
    .endif
    mov r12,info
    movzx esi,[r12].count
    mov rbx,_dlopen(rc, esi, eax, 0)
    .return .if !rax

    mov eax,flags
    and eax,0x00000070
    .if ( eax == MB_ICONERROR || eax == MB_ICONWARNING )

        _rcclear([rbx].rc, [rbx].window, _getattrib(FG_MENU, BG_ERROR))
    .endif

    _dltitleA(rbx, r13)

    mov rc,[rbx].rc
    mov al,rc.row
    mov rc.row,1
    sub al,2
    mov rc.y,al
    mov al,rc.col
    shr al,1
    mov rc.x,al

    movzx eax,[r12].count
    .new count:SINT = eax

    .for ( edx = 0, ecx = 0 : ecx < count : ecx++ )

        add dl,[r12].col[rcx]
        add dl,2
    .endf
    dec  ecx
    imul eax,ecx,3
    add  eax,edx
    shr  eax,1
    sub  rc.x,al

    .for ( r13d = 0 : r13d < count : r13d++ )

        mov al,[r12].col[r13]
        sub al,2
        add al,4
        mov rc.col,al
        _dlinitA(rbx, r13d, rc, O_DEXIT, T_PUSHBUTTON, [r12].id[r13], [r12].name[r13*LPSTR])
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

    lea r12,_bufin
    mov r13,r12
    mov rc,[rbx].rc
    mov rc.y,2
    mov rc.x,2
    sub rc.col,4

    .repeat

        .break .if !char_t ptr [r12]

        mov r12,strchr(r13, 10)
        .if ( rax != NULL )

            mov char_t ptr [r12],0
            add r12,char_t
        .endif
        _rccenterA([rbx].rc, [rbx].window, rc, attrib, r13)
        mov r13,r12
        inc rc.y
    .until ( r13 == NULL || rc.y == 17+2 )
    .return _dlmodal(rbx, &WndProc)

_msgboxA endp

    end
