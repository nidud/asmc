include io.inc
include cfini.inc
include malloc.inc
include string.inc
include dzlib.inc

    .code

INIRead proc uses esi edi ebx ini:LPINI, file:LPSTR

local i_fh, i_bp, i_i, i_c, o_bp, o_i, o_c

    .if osopen(file, _A_NORMAL, M_RDONLY, A_OPEN) != -1

        mov i_fh,eax
        mov i_bp,alloca(_PAGESIZE_*2)
        add eax,_PAGESIZE_
        mov o_bp,eax
        xor eax,eax
        mov i_i,eax
        mov i_c,eax
        mov o_i,eax
        mov o_c,eax
        .if eax == ini

            mov ini,INIAlloc()
        .endif
        mov ebx,ini

        .while 1

            mov eax,i_i
            .if eax == i_c

                .break .if !osread(i_fh, i_bp, _PAGESIZE_)

                mov i_c,eax
                xor eax,eax
                mov i_i,eax
            .endif

            inc i_i
            add eax,i_bp
            movzx eax,byte ptr [eax]

            mov edi,o_bp
            mov edx,o_i
            inc o_i
            mov [edi+edx],ax

            .if eax == 10 || edx == _PAGESIZE_ - 2

                mov o_i,0
                mov al,[edi]

                .switch al

                  .case 10
                  .case 13
                    .endc
                  .case '['
                    inc edi
                    .if strchr(edi, ']')

                        mov byte ptr [eax],0
                        .break .if !INIAddSection(ini, edi)
                        mov ebx,eax
                    .endif
                    .endc
                  .default
                    INIAddEntry(ebx, edi)
                .endsw
            .endif
        .endw

        _close(i_fh)
        mov eax,ini
    .else

        xor eax,eax
    .endif
    ret

INIRead endp

    END
