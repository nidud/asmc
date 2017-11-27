include iost.inc
include io.inc
include errno.inc
include confirm.inc
include dzlib.inc

    .code

ogetouth proc filename:LPSTR, mode

    .repeat

        .break .if osopen(filename, _A_NORMAL, mode, A_CREATE) != -1

        .if errno != EEXIST

            eropen(filename) ; -1
            .break
        .endif

        mov eax,1
        .if confirmflag & CFDELETEALL

            confirm_delete(filename, 0)
        .endif

        .switch eax
          .case 2   ; delete all --> clear flag, trunc
            and confirmflag,not CFDELETEALL
          .case 1   ; delete --> trunc
            setfattr(filename, 0)
            openfile(filename, mode, A_TRUNC)
            .endc
          .case 3   ; jump --> return 0
            xor eax,eax
            .endc
          .default  ; Cancel --> return -1
            mov eax,-1
            .endc
        .endsw
    .until 1
    ret

ogetouth endp

    END
