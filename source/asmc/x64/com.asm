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

    assume rdi:ptr sfield

AssignVTable proc private uses rsi rdi rbx name:string_t, sym:ptr dsym, reg:int_t, i:int_t

  local q[256]:char_t

    mov rsi,sym

    .if ( [rsi].asym.total_size )

        .for ( rdx = [rsi].dsym.structinfo,
               rdi = [rdx].struct_info.head : rdi : rdi = [rdi].next, i++ )

            .if ( [rdi].type )

                mov rdx,[rdi].type
                .if ( [rdx].asym.typekind == TYPE_STRUCT )

                    mov i,AssignVTable(name, rdx, reg, i)

                .else

                    strcat( strcpy( &q, name ), "_" )

                    mov ebx,1
                    .if ( SymFind( strcat( rax, [rdi].name ) ) )
                        .if ( [rax].asym.state == SYM_MACRO || [rax].asym.state == SYM_TMACRO )
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

    assume rbx:ptr asm_tok

ClearStruct proto __ccall :string_t, :asym_t

ComAlloc proc uses rsi rdi rbx buffer:string_t, tokenarray:token_t

  local name[16]:sbyte

    mov rbx,tokenarray
    mov edi,tstricmp([rbx].string_ptr, "@ComAlloc")
    .if edi
        .while [rbx].token != T_FINAL
            .if [rbx].token == T_ID
                mov edi,tstricmp([rbx].string_ptr, "@ComAlloc")
                .break .if !eax
            .endif
            add rbx,asm_tok
        .endw
    .endif
    .return 0 .if ( edi )

    add rbx,asm_tok*2
    .if ( [rbx-asm_tok].token != T_OP_BRACKET )
        .return 0
    .endif
    .if ( SymFind( [rbx].string_ptr ) == NULL )
        .return ERROR
    .endif
    .if ( !( [rax].asym.flag2 & S_VTABLE ) )
        .return 0
    .endif
    mov rsi,rax
    mov edi,T_EAX
    .if (  ModuleInfo.Ofssize == USE64 )
        mov edi,T_RAX
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    AddLineQueueX( "mov %r,malloc(%s + %sVtbl)", &[rdi+T_ECX-T_EAX], [rbx].string_ptr, [rbx].string_ptr )
    mov eax,4
    .if ( edi == T_RAX )
        mov eax,8
    .endif
    .if ( [rsi].asym.total_size > eax )

        tsprintf(&name, "[%r]", &[rdi+T_ECX-T_EAX])
        ClearStruct(&name, rsi)
        AddLineQueueX( "mov %r, %r", edi, &[rdi+T_ECX-T_EAX] )
    .endif

    AddLineQueueX( "add %r, %s", &[rdi+T_ECX-T_EAX], [rbx].string_ptr )
    AddLineQueueX( "mov [%r], %r", edi, &[rdi+T_ECX-T_EAX] )
    AssignVTable( [rbx].string_ptr, [rsi].asym.vtable, &[rdi+T_ECX-T_EAX], 0 )
    AddLineQueueX( "lea %r, [%r-%s]", edi, &[rdi+T_ECX-T_EAX], [rbx].string_ptr )
    InsertLineQueue()

    sub rbx,asm_tok*2
    .if ( rbx != tokenarray )
        tsprintf(buffer, "%r", edi)
    .endif
   .return 1

ComAlloc endp

endif

    end
