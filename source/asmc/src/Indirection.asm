; INDIRECTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include memalloc.inc
include parser.inc
include expreval.inc
include lqueue.inc
include assume.inc
include segment.inc
include listing.inc
include mangle.inc
include proc.inc
include atofloat.inc
include regno.inc
include types.inc

RetLineQueue proto

    .code

    assume ebx:ptr asm_tok

SkipSQBackets proc private uses ebx tok:ptr asm_tok

    .for ( ebx = tok,
           edx = 0, ; brackets
           ecx = 1, ; SQ-brackets
           ebx +=16 : ecx && [ebx].token != T_FINAL : ebx += 16 )

        mov al,[ebx].token
        .if ( al == T_OP_BRACKET )
            inc edx
        .elseif ( al == T_CL_BRACKET )
            dec edx
        .elseif ( !edx && al == T_OP_SQ_BRACKET )
            inc ecx
        .elseif ( !edx && al == T_CL_SQ_BRACKET )
            dec ecx
            .ifz
                add ebx,16
                .return ebx
            .endif
        .endif
    .endf
    xor eax,eax
    ret

SkipSQBackets endp

GetSQBackets proc private uses esi edi tok:ptr asm_tok, buffer:string_t

    .if SkipSQBackets(tok)

        mov ecx,[eax].asm_tok.tokpos
        mov edi,buffer
        mov esi,tok
        mov esi,[esi].asm_tok.tokpos
        sub ecx,esi
        rep movsb
        mov byte ptr [edi],0
    .endif
    ret

GetSQBackets endp

FindDotSymbol proc uses esi edi ebx tok:ptr asm_tok

    mov ebx,tok

    .while ( [ebx-16].token != T_COMMA && [ebx-16].token != T_DIRECTIVE )
        sub ebx,asm_tok
    .endw
    .return .if !SymSearch( [ebx].string_ptr )
    mov esi,eax

    add ebx,asm_tok
    .while ( [ebx].token != T_FINAL )

        .return 0 .if ( [ebx].token == T_COMMA )

        .if ( [ebx].token == T_OP_SQ_BRACKET )

            .break .if !SkipSQBackets( ebx )
            mov ebx,eax
        .endif
        xor eax,eax
        .break .if ( [ebx].token != T_DOT )
        add ebx,asm_tok

        .if ( [esi].asym.mem_type == MT_TYPE )
            mov esi,[esi].asym.type
        .endif
        .if ( [esi].asym.mem_type == MT_PTR )
            mov esi,[esi].asym.target_type
        .endif
        .break .if ( !esi )
        .break .if ( [esi].asym.state != SYM_TYPE )

        mov esi,SearchNameInStruct( esi, [ebx].string_ptr, 0, 0 )
        .break .if ( !esi )
        .break .if ( ebx == tok )
        add ebx,asm_tok
    .endw
    ret

FindDotSymbol endp

AssignPointer proc uses esi edi ebx sym:ptr asym, reg:int_t, tok:ptr asm_tok,
        pclass:ptr asym, langtype:int_t, pmacro:ptr asym

  local buffer[128]:sbyte
  local vreg:int_t
  local vtable:byte

    mov ebx,tok
    mov esi,sym

    .if ( esi == NULL )
        .if ( [ebx].token == T_REG )
            .return .if ( [ebx].tokval == reg )
            AddLineQueueX( " mov %r, %r", reg, [ebx].tokval )
        .else
            AddLineQueueX( " mov %r, %s", reg, [ebx].tokpos )
        .endif
        .return
    .endif

    mov vtable,0
    mov edi,pclass
    .if ( edi && [edi].asym.flag2 & S_ISVTABLE )

        .switch ( langtype )
        .case LANG_SYSCALL
            mov eax,T_RDI
            .endc
        .case LANG_FASTCALL
            mov eax,T_ECX
            .if ( ModuleInfo.Ofssize == USE64 )
                mov eax,T_RCX
            .endif
            .endc
        .case LANG_WATCALL
            mov eax,T_EAX
            .if ( ModuleInfo.Ofssize == USE64 )
                mov eax,T_RAX
            .endif
        .endsw

        .if ( eax )

            mov ecx,reg
            mov reg,eax
            mov edi,eax
            mov vreg,ecx

            add ebx,asm_tok
            .if ( [ebx].token == T_OP_SQ_BRACKET )
                .return .if !GetSQBackets( ebx, &buffer )
                mov ebx,eax
                AddLineQueueX( " lea %r, [%r]%s", edi, edi, &buffer )
            .endif
            .return .if ( [ebx].token != T_DOT )
            add ebx,asm_tok
            .if ( [esi].asym.mem_type == MT_TYPE )
                mov esi,[esi].asym.type
            .endif
            .if ( [esi].asym.mem_type == MT_PTR )
                mov esi,[esi].asym.target_type
            .endif
            .return .if ( !esi )
            .return .if ( [esi].asym.state != SYM_TYPE )
            AddLineQueueX( " mov %r, [%r].%s.%s", edi, edi, [esi].asym.name, [ebx].string_ptr )
            mov esi,SearchNameInStruct( esi, [ebx].string_ptr, 0, 0 )
            .return .if ( !esi )
            mov vtable,1
        .endif
    .endif
    .if ( !vtable )
        AddLineQueueX( " mov %r, %s", reg, [esi].asym.name )
    .endif
    add ebx,asm_tok
    .while ( [ebx].token != T_FINAL )

        .break .if ( [ebx].token == T_COMMA )

        .if ( [ebx].token == T_OP_SQ_BRACKET )

            .break .if !GetSQBackets( ebx, &buffer )

            mov ebx,eax
            AddLineQueueX( " lea %r, [%r]%s", reg, reg, &buffer )
        .endif

        .break .if ( [ebx].token != T_DOT )

        add ebx,asm_tok

        .if ( [esi].asym.mem_type == MT_TYPE )
            mov esi,[esi].asym.type
        .endif
        .if ( [esi].asym.mem_type == MT_PTR )
            mov esi,[esi].asym.target_type
        .endif
        .break .if ( !esi )
        .break .if ( [esi].asym.state != SYM_TYPE )

        AddLineQueueX( " mov %r, [%r].%s.%s", reg, reg, [esi].asym.name, [ebx].string_ptr )

        mov esi,SearchNameInStruct( esi, [ebx].string_ptr, 0, 0 )
        .break .if ( !esi )
        add ebx,asm_tok
    .endw
    .if ( vtable && !pmacro )
        AddLineQueueX( " mov %r, [%r]", vreg, reg )
    .endif
    mov eax,esi
    ret

AssignPointer endp

ifdef USE_INDIRECTION

HandleIndirection proc uses esi edi ebx sym:ptr asym, tokenarray:ptr asm_tok

  local reg:uint_t
  local inst:uint_t
  local dest:uint_t
  local buffer[128]:sbyte

    mov ebx,tokenarray
    mov inst,[ebx-3*16].tokval
    mov dest,[ebx-2*16].tokval

    mov reg,T_EAX
    .if ( ModuleInfo.Ofssize == USE64 )
        mov reg,T_RAX
    .endif
    AddLineQueueX( " mov %r, %s", reg, [ebx].string_ptr )

    add ebx,asm_tok
    mov esi,sym

    .while ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )

        .if ( [ebx].token == T_OP_SQ_BRACKET )

            .break .if !GetSQBackets( ebx, &buffer )

            mov ebx,eax
            AddLineQueueX( " lea %r, [%r]%s", reg, reg, &buffer )
        .endif

        .break .if ( [ebx].token != T_DOT )
        add ebx,asm_tok

        .if ( [esi].asym.mem_type == MT_TYPE )
            mov esi,[esi].asym.type
        .endif
        .if ( [esi].asym.mem_type == MT_PTR )
            mov esi,[esi].asym.target_type
        .endif

        .if ( !SearchNameInStruct( esi, [ebx].string_ptr, 0, 0 ) )
            .return asmerr(2166)
        .endif
        mov edi,eax
        add ebx,asm_tok
        .break .if ( [eax].asym.mem_type != MT_TYPE )
        mov eax,[eax].asym.type
        .break .if ( [eax].asym.mem_type != MT_PTR )
        AddLineQueueX( " mov %r, [%r].%s.%s", reg, reg, [esi].asym.name, [ebx-16].string_ptr )
        mov esi,edi
    .endw
    .if ( [esi].asym.mem_type == MT_TYPE )
        mov esi,[esi].asym.type
    .endif
    .if ( [esi].asym.mem_type == MT_PTR )
        mov esi,[esi].asym.target_type
    .endif
    AddLineQueueX( " %r %r, [%r].%s.%s", inst, dest, reg, [esi].asym.name, [ebx-16].tokpos)
    RetLineQueue()
    ret

HandleIndirection endp

endif

    end
