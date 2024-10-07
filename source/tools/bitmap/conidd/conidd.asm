; CONIDD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Capture the console window to an .IDD file.
;

include stdio.inc
include conio.inc
include winbase.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

    .new written:int_t = 0
    .new rs:RIDD = {0}
    .new p:PCHAR_INFO
    .new q:PCHAR_INFO
    .new bz:COORD
    .new sr:SMALL_RECT
    .new ci:CONSOLE_SCREEN_BUFFER_INFOEX = {CONSOLE_SCREEN_BUFFER_INFOEX}
    .new consh:HANDLE
    .new file:tstring_t = "default.idd"

    .if ( argc > 1 )

        mov rcx,argv
        mov rax,[rcx+size_t]
        .if ( byte ptr [rax] == '-' || byte ptr [rax] == '/' )

            _putts("usage: CONIDD [<idd_file>]\n")
            .return( 0 )
        .endif
        mov file,rax
    .endif

    mov consh,GetStdHandle(STD_OUTPUT_HANDLE)
    .if !GetConsoleScreenBufferInfoEx(consh, &ci)

        _putts("GetConsoleScreenBufferInfoEx failed\n")
        .return( 1 )
    .endif

    mov     rs.rc.col,ci.dwSize.X
    mov     rs.rc.row,ci.dwSize.Y
    mov     rs.flags,W_UNICODE
    mov     p,_rcalloc(rs.rc, rs.flags)
    mov     q,_rcalloc(rs.rc, rs.flags)
    movzx   eax,rs.rc.col
    movzx   edx,rs.rc.row
    movzx   ecx,rs.rc.y
    mov     bz.X,ax
    mov     bz.Y,dx
    mov     sr.Top,cx
    lea     ecx,[rcx+rdx-1]
    mov     sr.Bottom,cx
    movzx   ecx,rs.rc.x
    mov     sr.Left,cx
    lea     eax,[rcx+rax-1]
    mov     sr.Right,ax

    ReadConsoleOutputW(consh, p, bz, 0, &sr)
    mov esi,_rczip(rs.rc, q, p, rs.flags)
    mov rbx,CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)
    WriteFile(rbx, &rs, RIDD, &written, NULL)
    WriteFile(rbx, q, esi, &written, NULL)
    CloseHandle(rbx)
    xor eax,eax
    ret

_tmain endp

    end _tstart
