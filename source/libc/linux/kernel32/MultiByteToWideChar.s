; MULTIBYTETOWIDECHAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winerror.inc
include errhandlingapi.inc
include stringapiset.inc

.code

 MultiByteToWideChar proc WINAPI uses rbx \
        CodePage        :UINT,
        dwFlags         :DWORD,
        lpMultiByteStr  :LPCCH,
        cbMultiByte     :int_t,
        lpWideCharStr   :LPWSTR,
        cchWideChar     :int_t

    .new i:int_t
    .new char_count:int_t = 0
    .new is_nul_term:BOOL = FALSE
    .if ( ldr(dwFlags) )
        .return( SetLastError( ERROR_INVALID_FLAGS ) )
    .endif
    .if ( ldr(CodePage) != CP_UTF8 || ldr(cbMultiByte) == 0 )
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .elseif ( ldr(cbMultiByte) == -1 )
        mov is_nul_term,TRUE
        mov cbMultiByte,0
        .for ( rbx = ldr(lpMultiByteStr) : char_t ptr [rbx] : )
            _utftow(rbx, -1)
            add rbx,rcx
            add cbMultiByte,ecx
            shr ecx,2
            inc ecx
            add char_count,ecx
        .endf
        inc char_count
    .else
        .for ( rbx = lpMultiByteStr, i = cbMultiByte : i > 0 : )
            _utftow(rbx, i)
            add rbx,rcx
            sub i,ecx
            shr ecx,2
            inc ecx
            add char_count,ecx
        .endf
    .endif
    .if ( cchWideChar == 0 )
       .return( char_count )
    .elseif ( char_count > cchWideChar )
        .return( SetLastError( ERROR_INSUFFICIENT_BUFFER ) )
    .endif
    .for ( rbx = lpWideCharStr : cbMultiByte > 0 : )
        _utftow(lpMultiByteStr, cbMultiByte)
        add lpMultiByteStr,rcx
        sub cbMultiByte,ecx
        mov [rbx],ax
        add rbx,2
        shr ecx,2
        .ifnz
            shr eax,16
            mov [rbx],ax
            add rbx,2
        .endif
    .endf
    .if ( is_nul_term )
        xor eax,eax
        mov [rbx],ax
    .endif
    .return( char_count )
    endp

    end
