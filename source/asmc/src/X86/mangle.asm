
;; Symbol name mangling routines.

include asmc.inc
include memalloc.inc
include parser.inc
include mangle.inc

    .code

    option proc:private
    assume ecx:asym_t

;; VoidMangler: no change to symbol name

VoidMangler proc fastcall sym:asym_t, buffer:string_t

    mov edi,edx
    mov esi,[ecx].name
    movzx eax,[ecx].name_size
    lea ecx,[eax+1]
    rep movsb
    ret

VoidMangler endp

;; UCaseMangler: convert symbol name to upper case

UCaseMangler proc fastcall sym:asym_t, buffer:string_t

    mov edi,edx
    mov esi,[ecx].name
    movzx eax,[ecx].name_size
    lea ecx,[eax+1]
    rep movsb
    mov esi,eax
    _strupr( edx )
    mov eax,esi
    ret

UCaseMangler endp

;; UScoreMangler: add '_' prefix to symbol name

UScoreMangler proc fastcall sym:asym_t, buffer:string_t

    lea edi,[edx+1]
    mov esi,[ecx].name
    movzx eax,[ecx].name_size
    inc eax
    mov ecx,eax
    rep movsb
    mov byte ptr [edx],'_'
    ret

UScoreMangler endp

;; StdcallMangler: add '_' prefix and '@size' suffix to proc names */
;;                 add '_' prefix to other symbols */

StdcallMangler proc fastcall sym:asym_t, buffer:string_t

    .if ( Options.stdcall_decoration == STDCALL_FULL && [ecx].flag1 & S_ISPROC )

        mov eax,ecx
        mov eax,[eax].dsym.procinfo
        sprintf( edx, "_%s@%d", [ecx].name, [eax].proc_info.parasize )
    .else
        jmp UScoreMangler
    .endif
    ret

StdcallMangler endp

;; MS FASTCALL 32bit

ms32_decorate proc fastcall sym:asym_t, buffer:string_t

    mov eax,ecx
    mov eax,[eax].dsym.procinfo
    sprintf( edx, "@%s@%u", [ecx].name, [eax].proc_info.parasize )
    ret

ms32_decorate endp

;; flag values used by the OW fastcall name mangler ( changes )
.enum changes
    NORMAL           = 0,
    USCORE_FRONT     = 1,
    USCORE_BACK      = 2

;; FASTCALL OW style:
;;  add '_' suffix to proc names and labels
;;  add '_' prefix to other symbols

ow_decorate proc fastcall sym:asym_t, buffer:string_t

    mov eax,NORMAL
    .if [ecx].flag1 & S_ISPROC
        or eax,USCORE_BACK
    .else
        .switch [ecx].mem_type
        .case MT_NEAR
        .case MT_FAR
        .case MT_EMPTY
            or eax,USCORE_BACK
            .endc
        .default
            or eax,USCORE_FRONT
        .endsw
    .endif
    mov edi,edx
    .if eax & USCORE_FRONT
        mov byte ptr [edi],'_'
        inc edi
    .endif
    mov esi,[ecx].name
    movzx ecx,[ecx].name_size
    inc ecx
    rep movsb
    dec edi
    .if eax & USCORE_BACK
        mov word ptr [edi],'_'
        inc edi
    .endif
    sub edi,edx
    mov eax,edi
    ret

ow_decorate endp

;; MS FASTCALL 64bit

ms64_decorate proc fastcall sym:asym_t, buffer:string_t

    mov edi,edx
    mov esi,[ecx].name
    movzx eax,[ecx].name_size
    lea ecx,[eax+1]
    rep movsb
    ret

ms64_decorate endp

vect_decorate proc fastcall sym:asym_t, buffer:string_t

    mov edi,edx
    mov esi,ecx
    mov eax,1
    .if !( [ecx].flag1 & S_ISPROC )
        xor eax,eax
    .else
        _stricmp( [ecx].name, "main" )
        mov ecx,esi
    .endif
    .if eax == 0
        strcpy( edi, [ecx].name )
        movzx eax,[esi].asym.name_size
    .else
        mov eax,[esi].dsym.procinfo
        sprintf( edi, "%s@@%u", [ecx].name, [eax].proc_info.parasize )
    .endif
    ret

vect_decorate endp

    option proc:public

Mangle proc uses esi edi sym:asym_t, buffer:string_t

    mov ecx,sym
    mov ax,[ecx].langtype
    and eax,0x0F
    mov esi,VoidMangler
    .switch jmp eax
    .case LANG_C
        ;; leading underscore for C ?
        .if !Options.no_cdecl_decoration
            mov esi,UScoreMangler
        .endif
        .endc
    .case LANG_STDCALL
        .if Options.stdcall_decoration != STDCALL_NONE
            mov esi,StdcallMangler
        .endif
        .endc
    .case LANG_PASCAL
    .case LANG_FORTRAN
    .case LANG_BASIC
        mov esi,UCaseMangler
        .endc
    .case LANG_WATCALL
        mov esi,ow_decorate
        .endc
    .case LANG_FASTCALL ;; registers passing parameters
        .if ( ModuleInfo.Ofssize == USE64 )
            mov esi,ms64_decorate
        .elseif ( ModuleInfo.fctype == FCT_WATCOMC )
            mov esi,ow_decorate
        .else
            mov esi,ms32_decorate
        .endif
        .endc
    .case LANG_VECTORCALL
        mov esi,vect_decorate
    .case LANG_NONE
    .case LANG_SYSCALL
        .endc
    .endsw
    mov  edx,buffer
    call esi
    ret

Mangle endp

;; the "mangle_type" is an extension inherited from OW Wasm
;; accepted are "C" and "N". It's NULL if MANGLESUPP == 0 (standard)

SetMangler proc sym:asym_t, langtype:int_t, mangle_type:string_t

    mov eax,langtype
    .if( eax != LANG_NONE )
        mov ecx,sym
        mov [ecx].langtype,ax
    .endif
    ret

SetMangler endp

    end
