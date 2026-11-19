; WIDECHARTOMULTIBYTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winerror.inc
include errhandlingapi.inc
include stringapiset.inc

.code

 WideCharToMultiByte proc WINAPI uses rsi rdi rbx \
        CodePage          :UINT,
        dwFlags           :DWORD,
        lpWideCharStr     :LPCWCH,
        cchWideChar       :int_t,
        lpMultiByteStr    :LPSTR,
        cbMultiByte       :int_t,
        lpDefaultChar     :LPCCH,
        lpUsedDefaultChar :LPBOOL

    .new char_count:int_t = 0
    .new is_nul_term:BOOL = FALSE
    .if ( ldr(CodePage) != CP_UTF8 || lpDefaultChar || lpUsedDefaultChar )
        SetLastError( ERROR_INVALID_PARAMETER )
        .return( 0 )
    .endif
    .if ( cchWideChar == 0 )
        SetLastError( ERROR_INVALID_PARAMETER )
        .return( 0 )
    .elseif ( cchWideChar == -1 )
        mov is_nul_term,TRUE
        .for ( rbx = lpWideCharStr, esi = 0 : word ptr [rbx] : )
            _wtoutf([rbx])
            add char_count,ecx
            add rbx,rdx
            shr edx,1
            add esi,edx
        .endf
        mov cchWideChar,esi
        inc char_count
    .else
        .for ( rbx = lpWideCharStr, esi = 0 : esi < cchWideChar : )
            mov eax,cchWideChar
            sub eax,esi
            .if ( eax > 1 )
                mov ecx,[rbx]
            .else
                movzx ecx,word ptr [rbx]
            .endif
            _wtoutf(ecx)
            add char_count,ecx
            add rbx,rdx
            shr edx,1
            add esi,edx
        .endf
    .endif
    .if ( cbMultiByte == 0 )
       .return( char_count )
    .endif
    .if ( char_count > cbMultiByte )
        SetLastError( ERROR_INSUFFICIENT_BUFFER )
        .return( 0 )
    .endif
    .for ( rbx = lpWideCharStr, rsi = lpMultiByteStr : cchWideChar > 0 : )
        .if ( cchWideChar > 1 )
            mov ecx,[rbx]
        .else
            movzx ecx,word ptr [rbx]
        .endif
        _wtoutf(ecx)
        add rbx,rdx
        shr edx,1
        sub cchWideChar,edx
        .while ( ecx )
            mov [rsi],al
            inc rsi
            dec ecx
            shr eax,8
        .endw
    .endf
    .if ( is_nul_term )
        xor eax,eax
        mov [rsi],al
    .endif
    .return( char_count )
    endp

    end
