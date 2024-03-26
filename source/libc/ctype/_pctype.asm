; _PCTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include malloc.inc
ifndef __UNIX__
include winnls.inc
endif

public _pctype ; pointer to table for char's
public _pcumap
public _pclmap

.data
 _pctype ptr ushort_t NULL
 _pcumap string_t NULL
 _pclmap string_t NULL

.code

__pctype_func proc

    mov rax,_pctype
    ret

__pctype_func endp


__initpctype proc private uses rsi rdi
ifndef __UNIX__
    .new lcid:LCID
endif
    .if ( malloc(16+2*256+256+256) == NULL )

        .return
    .endif

    mov rdi,rax
    mov ecx,16/4
    xor eax,eax
    rep stosd
    mov _pctype,rdi
    lea rcx,[rdi+512]
    mov _pcumap,rcx
    add rcx,256
    mov _pclmap,rcx

    mov eax,_CONTROL
    mov ecx,0x08-0x00+1
    rep stosw
    mov eax,_SPACE+_CONTROL
    mov ecx,0x0D-0x09+1
    rep stosw
    mov eax,_CONTROL
    mov ecx,0x1F-0x0E+1
    rep stosw
    mov eax,_SPACE+_BLANK
    stosw
    mov eax,_PUNCT
    mov ecx,0x2F-0x21+1
    rep stosw
    mov eax,_DIGIT+_HEX
    mov ecx,0x39-0x30+1
    rep stosw
    mov eax,_PUNCT
    mov ecx,0x40-0x3A+1
    rep stosw
    mov eax,_UPPER+_HEX
    mov ecx,0x46-0x41+1
    rep stosw
    mov eax,_UPPER
    mov ecx,0x5A-0x47+1
    rep stosw
    mov eax,_PUNCT
    mov ecx,0x60-0x5B+1
    rep stosw
    mov eax,_LOWER+_HEX
    mov ecx,0x66-0x61+1
    rep stosw
    mov eax,_LOWER
    mov ecx,0x7A-0x67+1
    rep stosw
    mov eax,_PUNCT
    mov ecx,0x7E-0x7B+1
    rep stosw
    mov eax,_CONTROL
    stosw
    xor eax,eax
    mov ecx,128/2
    rep stosd

    .for ( rax = _pclmap, ecx = 0 : ecx < 256 : ecx++ )

        mov dl,cl
        .if ( cl >= 'A' && cl <= 'Z' )
            or dl,0x20
        .endif
        mov [rax+rcx],dl
    .endf

    .for ( rax = _pcumap, ecx = 0 : ecx < 256 : ecx++ )

        mov dl,cl
        .if ( cl >= 'a' && cl <= 'z' )
            and dl,0xDF
        .endif
        mov [rax+rcx],dl
    .endf

ifndef __UNIX__

    mov lcid,GetUserDefaultLCID()
    LCMapStringA(lcid, LCMAP_LOWERCASE, _pclmap, 256, _pclmap, 256)
    LCMapStringA(lcid, LCMAP_UPPERCASE, _pcumap, 256, _pcumap, 256)

endif

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
    ret

__initpctype endp

__exitpctype proc

    mov rcx,_pctype
    .if ( rcx )

        free(&[rcx-16])
    .endif
    ret

__exitpctype endp

.pragma(init(__initpctype, 50))
.pragma(exit(__exitpctype, 50))

    end
