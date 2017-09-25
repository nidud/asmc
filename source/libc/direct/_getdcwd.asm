include direct.inc
include errno.inc
include string.inc
include alloc.inc
include winbase.inc

    .code

    option cstack:on

_getdcwd proc uses esi edi ebx drive:SINT, buffer:LPSTR, maxlen:SINT

    mov esi,maxlen
    mov edi,alloca(esi)
    mov ebx,drive

    .repeat

        .if !ebx
            GetCurrentDirectoryA(esi, edi)
        .else
            GetLogicalDrives()
            mov ecx,ebx
            dec ecx
            shr eax,cl
            sbb eax,eax
            and eax,1
            .ifz
                mov oserrno,ERROR_INVALID_DRIVE
                mov errno,EACCES
                .break
            .endif
            mov al,'A' - 1
            add al,bl
            add eax,002E3A00h
            mov drive,eax
            GetFullPathNameA(&drive, esi, edi, 0)
        .endif
        .if eax > esi
            mov errno,ERANGE
            xor eax,eax
        .elseif eax
            mov esi,buffer
            .if !esi
                mov esi,malloc(&[eax+1])
                .break .if !eax
            .endif
            strcpy(esi, edi)
        .endif
    .until 1
    mov esp,ebp
    ret

_getdcwd endp

    END
