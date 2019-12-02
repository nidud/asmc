include io.inc
include consx.inc
include confirm.inc

extern IDD_ConfirmContinue:dword
extern IDD_ConfirmDelete:dword

public confirmflag

    .data
    confirmflag     dd -1
    cp_delselected  db "   You have selected %d file(s)",10
                    db "Do you want to delete all the files",0
    cp_delflag      db "  Do you still wish to delete it?",0

    .code

confirm_continue proc uses ebx msg
    .if rsopen(IDD_ConfirmContinue)
        mov ebx,eax
        dlshow(eax)
        mov eax,msg
        .if eax
            mov dx,[ebx+4]
            add dx,0204h
            mov cl,dh
            scpath(edx, ecx, 34, eax)
        .endif
        dlmodal(ebx)
    .endif
    ret
confirm_continue endp

;
; ret:  0 Cancel
;       1 Delete
;       2 Delete All
;       3 Jump
;
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
;       beep( 50, 6 )
        rsevent(IDD_ConfirmDelete, ebx)
        dlclose(ebx)
        mov eax,edx
    .endif
    ret
confirm_delete endp

ID_DELETE       equ 1   ; return 1
ID_DELETEALL    equ 2   ; return 1 + update confirmflag
ID_SKIPFILE     equ 3   ; return 0
ID_CANCEL       equ 0   ; return -1

confirm_delete_file proc uses esi fname:LPSTR, flag
    mov eax,flag
    mov edx,confirmflag
    .switch
      .case al & _A_RDONLY && dl & CFREADONY
        mov eax,-1
        mov esi,not (CFREADONY or CFDELETEALL)
        .endc
      .case al & _A_SYSTEM && dl & CFSYSTEM
        mov eax,-2
        mov esi,not (CFSYSTEM or CFDELETEALL)
        .endc
      .case dl & CFDELETEALL
        xor eax,eax
        mov esi,not CFDELETEALL
        .endc
      .default
        .return 1
    .endsw
    .switch confirm_delete(fname, eax)
      .case ID_DELETEALL
        and confirmflag,esi
        mov eax,1
        .endc
      .case ID_SKIPFILE
        xor eax,eax
      .case ID_DELETE
        .endc
      .default
        mov eax,-1
    .endsw
    ret
confirm_delete_file endp

confirm_delete_sub proc path:LPSTR
    mov eax,1
    .if confirmflag & CFDIRECTORY
        .if confirm_delete(path,1) == ID_DELETEALL
            and confirmflag,not (CFDIRECTORY or CFDELETEALL)
            mov eax,1
        .elseif eax == ID_SKIPFILE
            mov eax,-1
        .elseif eax != ID_DELETE
            xor eax,eax
        .endif
    .endif
    ret
confirm_delete_sub endp

    END
