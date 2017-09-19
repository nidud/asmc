include io.inc
include consx.inc
include stdlib.inc
include confirm.inc

extrn   IDD_ConfirmDelete:dword
;
; ret:	0 Cancel
;	1 Delete
;	2 Delete All
;	3 Jump
;
    .data
    cp_delselected  db "   You have selected %d file(s)",10
            db "Do you want to delete all the files",0
    cp_delflag  db "  Do you still wish to delete it?",0

    .code

confirm_delete proc uses ebx info:LPSTR, selected

    .if rsopen(IDD_ConfirmDelete)

        mov ebx,eax
        dlshow(eax)

        mov dl,[ebx][4]
        mov cl,[ebx][5]
        add cl,2        ; y
        add dl,12       ; x
        mov eax,selected

        .if eax > 1 && eax < 8000h

            scputf(edx, ecx, 0, 0, addr cp_delselected, eax)
        .else
            .if eax == -2
                scputf(edx, ecx, 0, 0,
                    "The following file is marked System.\n\n%s",
                    addr cp_delflag)
            .elseif eax == -1
                sub edx,2
                scputf(edx, ecx, 0, 0,
                    "The following file is marked Read only.\n\n  %s",
                    addr cp_delflag)
            .else
                add edx,6
                scputf(edx, ecx, 0, 0, "Do you wish to delete")
            .endif

            mov dl,[ebx][4]
            add dl,3
            inc ecx
            scenter(edx, ecx, 53, info)
        .endif
;		beep( 50, 6 )
        rsevent(IDD_ConfirmDelete, ebx)
        dlclose(ebx)
        mov eax,edx
    .endif
    ret
confirm_delete endp

    END
