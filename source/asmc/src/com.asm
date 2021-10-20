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

AssignVTable proc private uses esi edi ebx name:string_t, sym:ptr dsym, reg:int_t, i:int_t

  local q[256]:char_t

    mov esi,sym

    .if ( [esi].asym.total_size )

        .for ( edx = [esi].dsym.structinfo,
               edi = [edx].struct_info.head : edi : edi = [edi].next, i++ )

            .if ( [edi].type )

                mov edx,[edi].type
                .if ( [edx].asym.typekind == TYPE_STRUCT )

                    mov i,AssignVTable(name, edx, reg, i)

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
    mov eax,i
    dec eax
    ret

AssignVTable endp

    assume ebx:ptr asm_tok

ClearStruct proto :string_t, :asym_t

ComAlloc proc uses esi edi ebx buffer:string_t, tokenarray:token_t

  local name[16]:sbyte

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
    AddLineQueueX( "mov %r,malloc(%s + %sVtbl)", &[edi+T_ECX-T_EAX], [ebx].string_ptr, [ebx].string_ptr )
    mov eax,4
    .if ( edi == T_RAX )
        mov eax,8
    .endif
    .if ( [esi].asym.total_size > eax )

        tsprintf(&name, "[%r]", &[edi+T_ECX-T_EAX])
        ClearStruct(&name, esi)
        AddLineQueueX( "mov %r, %r", edi, &[edi+T_ECX-T_EAX] )
    .endif

    AddLineQueueX( "add %r, %s", &[edi+T_ECX-T_EAX], [ebx].string_ptr )
    AddLineQueueX( "mov [%r], %r", edi, &[edi+T_ECX-T_EAX] )
    AssignVTable( [ebx].string_ptr, [esi].asym.vtable, &[edi+T_ECX-T_EAX], 0 )
    AddLineQueueX( "lea %r, [%r-%s]", edi, &[edi+T_ECX-T_EAX], [ebx].string_ptr )
    InsertLineQueue()

    sub ebx,32
    .if ( ebx != tokenarray )
        tsprintf(buffer, "%r", edi)
    .endif
   .return 1

ComAlloc endp

endif

    end
