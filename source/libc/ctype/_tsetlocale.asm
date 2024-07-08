; _TSETLOCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *setlocale(int category, const char *locale);
; wchar_t *_wsetlocale(int category, const wchar_t *locale);
;
; This function sets (and retrieve) the run-time locale.
; The "category" argument is ignored and the locale specifier
; has to be a valid locale name ("en-US" or "ru").
; NULL and "" are also valid input.
;
include ctype.inc
include string.inc
include errno.inc
ifdef __UNIX__
include syserr.inc
else
include winnls.inc
include locale.inc
endif
include tchar.inc

define BUFFER_SIZE 512

externdef _pclmap:string_t
externdef _pcumap:string_t

ifndef __UNIX__
.data?
 local_name wchar_t LOCALE_NAME_MAX_LENGTH dup(?)
endif

.code

_tsetlocale proc uses rsi rdi rbx lc:int_t, string:tstring_t

ifdef __UNIX__

    _set_errno( ENOSYS )
    _get_sys_err_msg( ENOSYS )

else

   .new buffer[BUFFER_SIZE]:char_t
   .new cpInfo:CPINFOEX
   .new ctryname[16]:wchar_t = 0
   .new langname[16]:wchar_t = 0
   .new codepage:int_t
   .new lcid:LCID

    ldr rbx,string

    xor eax,eax
    .if ( rbx == NULL || _tal == [rbx] )

        mov local_name,bx
        lea rbx,local_name

        GetUserDefaultLocaleName(rbx, LOCALE_NAME_MAX_LENGTH)

ifndef _UNICODE
    .else

        .for ( rsi = rbx, rdi = &buffer, eax = 1 : eax : )

            lodsb
            stosw
        .endf
        lea rbx,buffer
endif
    .endif


    .ifd ( IsValidLocaleName( rbx ) == FALSE )

        .return
    .endif
    .ifd ( GetLocaleInfoEx(rbx, LOCALE_SISO3166CTRYNAME, &ctryname, lengthof(ctryname)) == 0 )

        .return
    .endif
    .ifd ( GetLocaleInfoEx(rbx, LOCALE_SISO639LANGNAME, &langname, lengthof(langname)) == 0 )

        .return
    .endif
    lea rbx,local_name
    wcscpy(rbx, &langname)
    wcscat(rbx, L"-")
    wcscat(rbx, &ctryname)

    .ifd ( GetLocaleInfoEx(rbx, LOCALE_IDEFAULTCODEPAGE or LOCALE_RETURN_NUMBER, &codepage, 2) == 0 )

        .return
    .endif

    .if GetCPInfoEx(codepage, 0, &cpInfo)

        .if ( cpInfo.MaxCharSize > 1 )

            mov rdx,_pctype
            .for ( rcx = &cpInfo.LeadByte : byte ptr [rcx] && byte ptr [rcx+1] : rcx += 2 )

                .for ( eax = 0, al = [rcx] : al <= [rcx+1] : eax++ )
                    or word ptr [rdx+rax*2],_LEADBYTE
                .endf
            .endf
        .endif
    .endif

    .ifd LocaleNameToLCID(rbx, NULL)

        mov lcid,eax
        .ifd LCMapStringA(lcid, LCMAP_UPPERCASE, _pcumap, 256, _pcumap, 256)

            .ifd LCMapStringA(lcid, LCMAP_LOWERCASE, _pclmap, 256, _pclmap, 256)

                .for ( rdx = _pctype, rsi = _pcumap, rdi = _pclmap, ecx = 0 : ecx < 256 : ecx++ )

                    mov al,[rdx+rcx*2]
                    and al,not (_LOWER or _UPPER)
                    .if ( cl != [rsi+rcx] )
                        or al,_LOWER
                    .elseif ( cl != [rdi+rcx] )
                        or al,_UPPER
                    .endif
                    mov [rdx+rcx*2],al
                .endf
            .endif
        .endif
    .endif

ifndef _UNICODE

    .for ( rsi = rbx, rdi = rbx, eax = 1 : eax : )

        lodsw
        stosb
    .endf
endif

    mov rax,rbx
endif
    ret

_tsetlocale endp

    end
