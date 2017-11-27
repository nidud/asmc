include iost.inc
include io.inc
include string.inc

PUBLIC  oupdate
PUBLIC  odecrypt

    .data
    oupdate  dd 0
    odecrypt dd 0

    .code

    assume ebx:ptr S_IOST

ioread proc uses esi edi ebx edx iost:ptr S_IOST

    mov ebx,iost
    sub eax,eax
    mov esi,[ebx].ios_flag

    .repeat

        .break .if esi & IO_MEMBUF

        mov edi,[ebx].ios_c
        sub edi,[ebx].ios_i
        .ifnz

            .if edi == [ebx].ios_c
                xor eax,eax
                .break
            .endif

            mov eax,[ebx].ios_bp
            add eax,[ebx].ios_i
            memcpy([ebx].ios_bp, eax, edi)
            xor eax,eax
        .endif

        mov [ebx].ios_i,eax
        mov [ebx].ios_c,edi
        mov ecx,[ebx].ios_size
        sub ecx,edi
        mov eax,[ebx].ios_bp
        add eax,edi
        osread([ebx].ios_file, eax, ecx)
        add [ebx].ios_c,eax
        add eax,edi
        .break .ifz

        and esi,IO_UPDTOTAL or IO_USECRC or IO_USEUPD or IO_CRYPT
        .break .ifz

        .if esi & IO_CRYPT

            odecrypt()
        .endif

        .if esi & IO_UPDTOTAL

            add dword ptr [ebx].S_IOST.ios_total,eax
            adc dword ptr [ebx].S_IOST.ios_total[4],0
        .endif

        .if esi & IO_USECRC

            mov edx,edi
            mov esi,ebx
            oupdcrc()
            mov esi,[ebx].ios_flag
        .endif

        .if esi & IO_USEUPD

            push eax
            push 0
            oupdate()
            dec eax
            pop eax
            .ifnz
                osmaperr()
                or [ebx].ios_flag,IO_ERROR
                xor eax,eax
            .endif
        .endif

    .until 1
    test eax,eax
    ret

ioread endp

    END
