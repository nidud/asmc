; MANGLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Symbol name mangling routines.
;

include asmc.inc
include memalloc.inc
include parser.inc
include mangle.inc

    .code

    option proc:private
    assume rcx:asym_t

; VoidMangler: no change to symbol name

VoidMangler proc fastcall sym:asym_t, buffer:string_t

    mov rdi,rdx
    mov rsi,[rcx].name
    mov eax,[rcx].name_size
    lea ecx,[rax+1]
    rep movsb
    ret

VoidMangler endp

; UCaseMangler: convert symbol name to upper case

UCaseMangler proc fastcall sym:asym_t, buffer:string_t

    mov rdi,rdx
    mov rsi,[rcx].name
    mov eax,[rcx].name_size
    lea ecx,[rax+1]
    rep movsb
    mov rsi,rax
    tstrupr( rdx )
    mov rax,rsi
    ret

UCaseMangler endp

; UScoreMangler: add '_' prefix to symbol name

UScoreMangler proc fastcall sym:asym_t, buffer:string_t

    lea rdi,[rdx+1]
    mov rsi,[rcx].name
    mov eax,[rcx].name_size
    inc eax
    mov ecx,eax
    rep movsb
    mov byte ptr [rdx],'_'
    ret

UScoreMangler endp

; StdcallMangler: add '_' prefix and '@size' suffix to proc names
;                 add '_' prefix to other symbols */

StdcallMangler proc fastcall sym:asym_t, buffer:string_t

    .if ( Options.stdcall_decoration == STDCALL_FULL && [rcx].isproc )

        mov rax,rdx
        mov rdx,[rcx].asym.procinfo
        .if rdx
            mov edx,[rdx].proc_info.parasize
        .endif

        tsprintf( rax, "_%s@%d", [rcx].name, edx )
    .else
        call UScoreMangler
    .endif
    ret

StdcallMangler endp

; MS FASTCALL 32bit

ms32_decorate proc fastcall sym:asym_t, buffer:string_t

    .if ( [rcx].isproc )

        ; v2.18: don't assume all symbols are PROCs

        mov rax,rdx
        mov rdx,[rcx].procinfo
        .if rdx
            mov edx,[rdx].proc_info.parasize
        .endif
        tsprintf( rax, "@%s@%u", [rcx].name, edx )
    .else
        UScoreMangler(rcx, rdx)
    .endif
    ret

ms32_decorate endp

; flag values used by the OW fastcall name mangler ( changes )
.enum changes
    NORMAL           = 0,
    USCORE_FRONT     = 1,
    USCORE_BACK      = 2

; FASTCALL OW style:
;  add '_' suffix to proc names and labels
;  add '_' prefix to other symbols

ow_decorate proc fastcall sym:asym_t, buffer:string_t

    mov eax,NORMAL
    .if [rcx].isproc
        or eax,USCORE_BACK
    .else
        .switch [rcx].mem_type
        .case MT_NEAR
        .case MT_FAR
        .case MT_EMPTY
            or eax,USCORE_BACK
            .endc
        .default
            or eax,USCORE_FRONT
        .endsw
    .endif
    mov rdi,rdx
    .if eax & USCORE_FRONT
        mov byte ptr [rdi],'_'
        inc rdi
    .endif
    mov rsi,[rcx].name
    mov ecx,[rcx].name_size
    inc ecx
    rep movsb
    dec rdi
    .if eax & USCORE_BACK
        mov word ptr [rdi],'_'
        inc rdi
    .endif
    sub rdi,rdx
    mov rax,rdi
    ret

ow_decorate endp

; MS FASTCALL 64bit

ms64_decorate proc fastcall sym:asym_t, buffer:string_t

    mov rdi,rdx
    mov rsi,[rcx].name
    mov eax,[rcx].name_size
    lea ecx,[rax+1]
    rep movsb
    ret

ms64_decorate endp

vect_decorate proc fastcall sym:asym_t, buffer:string_t

    mov rdi,rdx
    mov rsi,rcx
    mov eax,1
    .if !( [rcx].isproc )
        xor eax,eax
    .else
        tstricmp( [rcx].name, "main" )
        mov rcx,rsi
    .endif
    .if eax == 0
        tstrcpy( rdi, [rcx].name )
        mov eax,[rsi].asym.name_size
    .else
        mov rdx,[rsi].asym.procinfo
        .if rdx
            mov edx,[rdx].proc_info.parasize
        .endif
        tsprintf( rdi, "%s@@%u", [rcx].name, edx )
    .endif
    ret

vect_decorate endp

    option proc:public

Mangle proc __ccall uses rsi rdi sym:asym_t, buffer:string_t

    ldr rcx,sym
    mov al,[rcx].langtype
    and eax,0x0F
    lea rsi,VoidMangler
    .switch eax
    .case LANG_C
        ; leading underscore for C ?
        .if !Options.no_cdecl_decoration
            lea rsi,UScoreMangler
        .endif
        .endc
    .case LANG_STDCALL
        .if Options.stdcall_decoration != STDCALL_NONE
            lea rsi,StdcallMangler
        .endif
        .endc
    .case LANG_PASCAL
    .case LANG_FORTRAN
    .case LANG_BASIC
        lea rsi,UCaseMangler
        .endc
    .case LANG_WATCALL
        lea rsi,ow_decorate
        .endc
    .case LANG_FASTCALL ; registers passing parameters
        .if ( MODULE.Ofssize == USE64 )
            lea rsi,ms64_decorate
        .elseif ( MODULE.fctype == FCT_WATCOMC )
            lea rsi,ow_decorate
        .else
            lea rsi,ms32_decorate
        .endif
        .endc
    .case LANG_VECTORCALL
        lea rsi,vect_decorate
    .case LANG_NONE
    .case LANG_SYSCALL
    .case LANG_ASMCALL
        .endc
    .endsw
    mov  rdx,buffer
    call rsi
    ret

Mangle endp

; the "mangle_type" is an extension inherited from OW Wasm
; accepted are "C" and "N". It's NULL if MANGLESUPP == 0 (standard)

SetMangler proc __ccall sym:asym_t, langtype:int_t, mangle_type:string_t

    ldr edx,langtype
    .if ( edx != LANG_NONE )

        ldr rcx,sym
        mov [rcx].langtype,dl
    .endif
    ret

SetMangler endp

    end
