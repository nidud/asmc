; _RSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Resource with TLIST sample
;
define _CONIO_RETRO_COLORS
include conio.inc
include stdio.inc
include string.inc
include direct.inc
include tchar.inc

define AT ((BLUE shl 4) or WHITE)

externdef IDD_OpenFile:PIDD

.enum OpenDialog {
    ID_FILE         =  0,
    ID_DIRECTORY    =  1,
    ID_FIRST        =  2,
    ID_LAST         = 14,
    ID_CNT          = 13,
    ID_OK           = 15,
    }


    .code

    option proc: private

paint proc uses rbx

   .new rc:TRECT
   .new fc:TRECT = { 2, 10, 51, 3 }
   .new y:byte

    _cbeginpaint()
    mov rcx,_console
    mov rc,[rcx].TCONSOLE.rc

    _scputa(0, 0, rc.col, 0x47)
    mov cl,rc.col
    shr cl,1
    sub cl,12
    _scputs(cl, 0, "Virtual Terminal Sample")

    _scputs(2, 2, "Resource with TLIST sample")
    _scputs(2, 4, "Flags:")
    _scputs(2, 5, "O_LIST  - Adds TLIST structure to dialog->context->llist")
    _scputs(2, 6, "O_MYBUF - Use external buffer - No TEDIT buffer allocated")

    mov al,rc.row
    sub al,10
    mov fc.y,al
    mov cl,fc.y
    dec cl
    _scputs(fc.x, cl, " Color Table for Windows Terminal ")
    _scframe(fc, BOX_SINGLE_ARC, 0)

    mov al,fc.y
    inc al
    mov y,al

    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        movzx eax,bh
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, y, 2, eax)
    .endf

    add fc.y,5
    mov cl,fc.y
    mov al,cl
    dec cl
    inc al
    mov y,al

    _scputs(fc.x, cl, " Color Table for Linux Terminal ")
    _scframe(fc, BOX_SINGLE_ARC, 0)
    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        movzx eax,bh
        lea rdx,_terminalcolorid
        mov al,[rdx+rax]
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, y, 2, eax)
    .endf

    dec rc.row
    _scputs(1, rc.row, "./_rsopen$")
    _cendpaint()
    _gotoxy(11, rc.row)
    ret

paint endp


    assume rbx:THWND

init_list proc uses rbx hwnd:THWND

   .new lp:PFILENT
   .new fp:PFILENT
   .new ll:PTLIST
   .new focus:THWND
   .new i:int_t = ID_CNT
   .new count:int_t
   .new rc:TRECT

    ldr rbx,hwnd

    mov focus,_dlgetfocus(rbx)
    .if ( rax )
        _sendmessage(rax, WM_KILLFOCUS, 0, 0)
    .endif

    mov rc,[rbx].rc
    mov rcx,[rbx].llist
    mov ll,rcx
    mov [rcx].TLIST.numcel,0
    imul eax,[rcx].TLIST.index,size_t
    add rax,[rcx].TLIST.list
    mov lp,rax
    mov eax,[rcx].TLIST.count
    sub eax,[rcx].TLIST.index
    mov count,eax
    mov rbx,_dlgetid(rbx, [rcx].TLIST.dlgoff)
    mov eax,[rbx].rc
    add al,rc.x
    add ah,rc.y
    mov rc,eax

    .repeat

        _scputc(rc.x, rc.y, rc.col, ' ')

        xor eax,eax
        .if ( count )

            mov rax,lp
            mov rax,[rax]
            add lp,size_t
            dec count
        .endif
        or [rbx].flags,O_STATE

        .if rax

            mov fp,rax
            mov eax,[rax]
            and eax,_F_SUBDIR
            mov eax,TC_BLACK
            .ifnz
                mov al,TC_DARKGRAY
            .endif
            _scputfg(rc.x, rc.y, rc.col, al)
            mov rcx,fp
            _scnputs(rc.x, rc.y, rc.col, [rcx].FILENT.name)

            and [rbx].flags,not O_STATE
            mov rdx,ll
            inc [rdx].TLIST.numcel
            mov rax,fp
         .endif
        inc rc.y
        mov [rbx].buffer,rax
        mov rbx,[rbx].next
        dec i
    .untilz

    mov rbx,focus
    .if ( rbx )

        _dlsetfocus(rbx, [rbx].oindex)
    .endif
    xor eax,eax
    ret

init_list endp


read_list proc uses rbx hwnd:THWND

    ldr rbx,hwnd

    _dread([rbx].buffer)

    mov rdx,[rbx].buffer
    mov rcx,[rbx].llist
    mov [rcx].TLIST.celoff,0              ; cell offset
    mov [rcx].TLIST.numcel,0              ; number of visible cells
    mov [rcx].TLIST.count,eax             ; total number of items in list
    mov [rcx].TLIST.index,0               ; index in list buffer
    mov [rcx].TLIST.list,[rdx].DIRENT.fcb   ; pointer to list buffer

    .if ( [rdx].DIRENT.flags & _D_DOSORT )

        _dsort(rdx)
    .endif
    ret

read_list endp


case_file proc uses rbx hwnd:THWND

    ldr rbx,hwnd

    mov rbx,_dlgetid(rbx, ID_FILE)
    .if ( !_tcspbrk([rbx].buffer, "*?") )
        .return _postquitmsg([rbx].prev, 1)
    .endif
    mov rbx,[rbx].prev
    read_list(rbx)
   .return( init_list(rbx) )

case_file endp


case_files proc uses rbx hwnd:THWND, id:int_t

   .new path[_MAX_PATH]:TCHAR = 0
   .new index:byte = ID_FIRST

    ldr rbx,hwnd
    ldr edx,id

    _dlgetid(rbx, edx)
    mov rdx,[rax].TDIALOG.buffer
    .if ( [rdx].FILENT.attrib & _F_SUBDIR )

        mov eax,'.'
        mov rcx,[rbx].buffer
        .if ( [rdx].FILENT.nbuf[0] == _tal &&
              [rdx].FILENT.nbuf[tchar_t] == _tal &&
              [rdx].FILENT.nbuf[tchar_t*2] == 0 )

            _tcsfn([rcx].DIRENT.path)
            mov rcx,[rbx].buffer
            .if ( rax > [rcx].DIRENT.path )
                mov tchar_t ptr [rax-tchar_t],0
                _tcscpy(&path, rax)
            .endif
        .else
            _tcsfcat([rcx].DIRENT.path, NULL, [rdx].FILENT.name)
        .endif
        read_list(rbx)
        .if ( path )

            .ifd ( _dsearch([rbx].buffer, &path) >= 0 )

                mov rcx,[rbx].llist
                .if ( eax < [rcx].TLIST.dcount )

                    mov [rcx].TLIST.index,0
                    add index,al
                .else

                    sub eax,[rcx].TLIST.dcount
                    inc eax
                    mov [rcx].TLIST.index,eax
                    mov eax,[rcx].TLIST.dcount
                    dec eax
                    add index,al
                .endif
            .endif
        .endif
        init_list(rbx)
        _dlsetfocus(rbx, index)
       .return( 0 )
    .endif

    mov rcx,[rbx].buffer
    _tcscpy([rcx].DIRENT.mask, [rdx].FILENT.name)
    .return _postquitmsg(rbx, 1)

case_files endp


FilesProc proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr rbx,hwnd
    ldr rax,lParam
    ldr rcx,wParam
    ldr edx,uiMsg

    mov rbx,[rbx].prev
    .if ( [rbx].index < ID_FIRST || [rbx].index > ID_LAST )
        .return( 1 )
    .endif

    .if ( edx == WM_KEYDOWN && eax & ENHANCED_KEY )

        mov rdx,[rbx].llist
        .switch ecx
        .case VK_UP
            .if ( [rbx].index == ID_FIRST )

                .if ( [rdx].TLIST.index )

                    dec [rdx].TLIST.index
                   .return( init_list(rbx) )
                .endif
            .endif
            .endc
        .case VK_DOWN
            .if ( [rbx].index == ID_LAST )

                mov eax,[rdx].TLIST.count
                sub eax,[rdx].TLIST.index
                sub eax,[rdx].TLIST.dcount
                .ifs ( eax > 0 )

                    inc [rdx].TLIST.index
                    init_list(rbx)
                .endif
                .return( 0 )
            .endif
            .endc
        .case VK_HOME
            mov [rdx].TLIST.index,0
            _dlsetfocus(rbx, ID_FIRST)
            .return( init_list(rbx) )
        .case VK_END
            mov eax,[rdx].TLIST.count
            .if ( eax < [rdx].TLIST.dcount )

                mov eax,[rdx].TLIST.numcel
                dec eax
                add eax,[rdx].TLIST.dlgoff
                _dlsetfocus(rbx, al)
                .return( 0 )
            .endif
            sub eax,[rdx].TLIST.dcount
            .if ( eax != [rdx].TLIST.index )

                mov [rdx].TLIST.index,eax
                mov eax,[rdx].TLIST.dcount
                dec eax
                add eax,[rdx].TLIST.dlgoff

                _dlsetfocus(rbx, al)
                .return( init_list(rbx) )
            .endif
            .endc
        .case VK_PRIOR
        .case VK_LEFT
            mov eax,[rdx].TLIST.dcount
            .if ( eax <= [rdx].TLIST.index )
                sub [rdx].TLIST.index,eax
            .else
                .gotosw(VK_HOME)
            .endif
            .return( init_list(rbx) )
        .case VK_NEXT
        .case VK_RIGHT
            mov eax,[rdx].TLIST.dcount
            dec eax
            .if ( eax != [rdx].TLIST.celoff )

                mov eax,[rdx].TLIST.numcel
                add eax,[rdx].TLIST.dlgoff
                dec eax
                _dlsetfocus(rbx, al)
                .return( 0 )
            .endif
            add eax,[rdx].TLIST.celoff
            add eax,[rdx].TLIST.index
            inc eax
            .if ( eax >= [rdx].TLIST.count )
                .gotosw(VK_END)
            .endif
            mov eax,[rdx].TLIST.dcount
            add [rdx].TLIST.index,eax
           .return( init_list(rbx) )
        .endsw

    .elseif ( edx == WM_CHAR && ecx == VK_TAB )

        _dlsetfocus(rbx, ID_OK)
        .return( 0 )
    .endif
    .return( _defwinproc(hwnd, uiMsg, wParam, lParam) )

FilesProc endp

WndProc proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr rbx,hwnd
    ldr rax,lParam
    ldr rcx,wParam
    ldr edx,uiMsg

    .switch edx
    .case WM_CREATE
        _dlshow(rbx)
        _tiputs([_dlgetid(rbx, ID_FILE)].TDIALOG.tedit)
        _tiputs([_dlgetid(rbx, ID_DIRECTORY)].TDIALOG.tedit)
        read_list(rbx)
        init_list(rbx)
        .return( 0 )
    .case WM_CLOSE
        _dlclose(rbx)
        .return( 0 )

    .case WM_COMMAND
        .endc .if !( eax == VK_RETURN )
        .switch ecx
        .case ID_FILE
            .return( case_file(rbx) )
        .case ID_DIRECTORY
            read_list(rbx)
            .return( init_list(rbx) )
        .case ID_OK
            mov rcx,[rbx].buffer
            mov rdx,[rbx].llist
            mov eax,[rdx].TLIST.index
            add eax,[rdx].TLIST.celoff
            imul eax,eax,size_t
            add rax,[rdx].TLIST.list
            mov rdx,[rax]
            _tcscpy([rcx].DIRENT.mask, [rdx].FILENT.name)
            _postquitmsg(rbx, 1)
           .return( 0 )
        .default
            .endc .if ( ecx > ID_LAST )
            .return( case_files(rbx, ecx) )
        .endsw
    .endsw
    .return( _defwinproc(rbx, uiMsg, wParam, rax) )

WndProc endp


_tmain proc public argc:int_t, argv:array_t

   .new p:ptr = _conpush()
   .new d:THWND = _rsopen(IDD_OpenFile)
   .new w:PDIRENT = _dopen(NULL, NULL, NULL, _D_SORTTYPE)

    paint()

    mov rbx,d

    mov rcx,_dlgetid(rbx, ID_FIRST)

    .for ( rax = &FilesProc : rcx : rcx = [rcx].TDIALOG.next )

        .break .if !( [rcx].TDIALOG.flags & O_LIST )

        mov [rcx].TDIALOG.winproc,rax
    .endf

    mov rbx,d
    mov [rbx].buffer,w
    mov rcx,[rbx].llist
    mov [rcx].TLIST.dlgoff,ID_FIRST ; start index in dialog
    mov [rcx].TLIST.dcount,ID_CNT   ; number of cells (max)

    mov rcx,_dlgetid(rbx, ID_FILE)
    mov rdx,w
    mov rbx,[rdx].DIRENT.path
    mov [rdx].DIRENT.mask,[rcx].TDIALOG.buffer
    _tcscpy(rax, "*.*")

    mov rcx,_dlgetid(d, ID_DIRECTORY)
    mov [rcx].TDIALOG.buffer,rbx
    mov rcx,[rcx].TDIALOG.tedit
    mov [rcx].TEDIT.base,rbx

    .ifd ( _dlmodal(d, &WndProc) == 1 )

        mov rcx,w
        _msgbox(MB_OK or MB_USERICON, "Open result",
            _tcsfcat([rcx].DIRENT.path, NULL, [rcx].DIRENT.mask))
    .endif
    _dclose(w)
    _conpop(p)
   .return(0)

_tmain endp

    end _tstart
