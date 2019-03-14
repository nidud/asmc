; MBTOWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windef.inc
include cruntime.inc
include stdlib.inc
include errno.inc
include dbgint.inc
include ctype.inc
include internal.inc
include locale.inc
include mtdll.inc
include setlocal.inc
include winnls.inc

    .code

_mbtowc_l proc frame uses rsi rdi rbx,
        pwc      : wstring_t,
        s        : string_t,
        n        : size_t,
        plocinfo : _locale_t

  local _loc_update:ptr _LocaleUpdate

    .repeat

        xor eax,eax

        ;; indicate do not have state-dependent encodings,
        ;; handle zero length string
        .break .if ( !rdx || r8 == 0 )

        .if ( [rdx] == al )

            ;; handle NULL char
            .if ( rcx )

                mov [rcx],ax
            .endif
            .break
        .endif

        .break .if !_LocaleUpdate::_LocaleUpdate(&_loc_update, r9)

        .ASSERT (_loc_update.GetLocaleT()->locinfo->mb_cur_max == 1 || _loc_update.GetLocaleT()->locinfo->mb_cur_max == 2);

        _loc_update.GetLocaleT()

        mov rbx,[rax]._locale_tstruct.locinfo
        assume rbx:ptr threadlocinfo

        .if ( [rbx].locale_name[LC_CTYPE*size_t] == NULL )

            mov rcx,pwc
            .if rcx
                mov rdx,s
                movzx eax,byte ptr [rdx]
                mov [rcx],ax
            .endif

            _loc_update.Release()
            mov eax,sizeof(char_t)
            .break
        .endif

        mov rdx,s
        movzx ecx,byte ptr [rdx]

        .if _isleadbyte_l(ecx, rax)

            ;; multi-byte char

            _loc_update.GetLocaleT()
            mov rdx,[rax]._locale_tstruct.locinfo

            mov rax,n
            .ifs ( ( [rbx].mb_cur_max <= 1 ) || ( eax < [rbx].mb_cur_max ) )

                mov eax,1
            .else

                mov rax,pwc
                xor r10d,r10d
                .if rax
                    inc r10d
                .endif

                .ifd MultiByteToWideChar(
                        [rbx].lc_codepage,
                        MB_PRECOMPOSED or MB_ERR_INVALID_CHARS,
                        s,
                        [rbx].mb_cur_max,
                        rax,
                        r10d ) == 0

                    mov eax,1
                .else
                    xor eax,eax
                .endif
            .endif

            .if eax

                ;; validate high byte of mbcs char

                mov rax,n
                mov rdx,s
                .if ( (eax < [rbx].mb_cur_max) || (!byte ptr [rdx+1]) )

                    _loc_update.Release()
                    mov errno,EILSEQ
                    mov eax,-1
                    .break
                .endif

            .endif

            mov eax,[rbx].mb_cur_max

        .else

            ;; single byte char

            mov rax,pwc
            xor r10d,r10d
            .if rax

                inc r10d
            .endif

            .ifd MultiByteToWideChar([rbx].lc_codepage,
                    MB_PRECOMPOSED or MB_ERR_INVALID_CHARS, s, 1, rax, r10d) == 0

                mov errno,EILSEQ
                mov eax,-1

            .else

                mov eax,sizeof(char_t)
            .endif
        .endif

        mov ebx,eax
        _loc_update.Release()
        mov eax,ebx
    .until 1
    ret

_mbtowc_l endp

mbtowc proc frame,
        pwc : wstring_t,
        s   : string_t,
        n   : size_t

    _mbtowc_l(pwc, s, n, NULL)
    ret

mbtowc endp

    end

