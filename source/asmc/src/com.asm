; COM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include lqueue.inc
include parser.inc

ifdef USE_COMALLOC

    .code

    assume edi:ptr sfield

AssignVTable proc uses esi edi ebx name:string_t, sym:ptr dsym, reg:int_t

  local q[256]:char_t
  local i:int_t

    mov esi,sym

    .if ( [esi].asym.total_size )

        .for ( i = 0, edx = [esi].dsym.structinfo,
               edi = [edx].struct_info.head : edi : edi = [edi].next, i++ )

            .if ( [edi].type )

                mov edx,[edi].type
                .if ( [edx].asym.typekind == TYPE_STRUCT )

                    AssignVTable(name, edx, reg)

                .else

                    strcat( strcpy( &q, name ), "_" )

                    mov ebx,1
                    .if ( SymFind( strcat( eax, [edi].name ) ) )
                        .if ( [eax].asym.state == SYM_MACRO || [eax].asym.state == SYM_TMACRO )
                            xor ebx,ebx
                        .endif
                    .endif
                    .if ( ebx )
                        mov ebx,reg
                        dec ebx
                        AddLineQueueX( "lea %r, %s", ebx, &q )
                        ;
                        ; v2.33.05 - assign member by offset
                        ;
                        movzx eax,ModuleInfo.Ofssize
                        shl eax,2
                        AddLineQueueX( "mov [%r+%d*%d], %r", reg, i, eax, ebx )
                    .endif
                .endif
            .endif
        .endf
    .endif
    ret

AssignVTable endp

    assume ebx:ptr asm_tok

ComAlloc proc uses esi edi ebx buffer:string_t, tokenarray:token_t

    mov ebx,tokenarray
    mov edi,_stricmp([ebx].string_ptr, "@ComAlloc")
    .if edi
        .while [ebx].token != T_FINAL
            .if [ebx].token == T_ID
                mov edi,_stricmp([ebx].string_ptr, "@ComAlloc")
                .break .if !eax
            .endif
            add ebx,16
        .endw
    .endif
    .return 0 .if ( edi )

    add ebx,32
    .if ( [ebx-16].token != T_OP_BRACKET )
        .return 0
    .endif
    .if ( SymFind( [ebx].string_ptr ) == NULL )
        .return ERROR
    .endif
    .if ( !( [eax].asym.flag2 & S_VTABLE ) )
        .return 0
    .endif
    mov esi,eax
    mov edi,T_EAX
    .if (  ModuleInfo.Ofssize == USE64 )
        mov edi,T_RAX
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    AddLineQueueX( "malloc(%s + %sVtbl)", [ebx].string_ptr, [ebx].string_ptr )
    AddLineQueueX( "push %r", &[edi+T_EDI-T_EAX] )
    AddLineQueueX( "mov %r, %r", &[edi+T_EDX-T_EAX], edi )
    AddLineQueueX( "mov %r, %r", &[edi+T_EDI-T_EAX], edi )
    AddLineQueueX( "mov %r, %s shr 2", &[edi+T_ECX-T_EAX], [ebx].string_ptr )
    AddLineQueue ( "xor eax, eax" )
    AddLineQueue ( "rep stosd" )
    AddLineQueueX( "pop %r", &[edi+T_EDI-T_EAX] )
    AddLineQueueX( "mov %r, %r", edi, &[edi+T_EDX-T_EAX] )
    AddLineQueueX( "add %r, %s", &[edi+T_EDX-T_EAX], [ebx].string_ptr )
    AddLineQueueX( "mov [%r], %r", edi, &[edi+T_EDX-T_EAX] )
    AssignVTable( [ebx].string_ptr, [esi].asym.vtable, &[edi+T_EDX-T_EAX] )
    InsertLineQueue()

    sub ebx,32
    .if ( ebx != tokenarray )
        tsprintf(buffer, "%r", edi)
    .endif
   .return 1

ComAlloc endp

endif

    end
