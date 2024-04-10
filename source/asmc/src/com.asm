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

AssignVTable proc __ccall private uses rsi rdi rbx name:string_t, sym:ptr dsym, reg:int_t, i:int_t

   .new q[256]:char_t

    ldr rsi,sym

    .if ( [rsi].asym.total_size )

        .for ( rdx = [rsi].dsym.structinfo,
               rdi = [rdx].struct_info.head : rdi : rdi = [rdi].next, i++ )

            .if ( [rdi].type )

                mov rdx,[rdi].type
                .if ( [rdx].asym.typekind == TYPE_STRUCT )

                    mov i,AssignVTable(name, rdx, reg, i)

                .else

                    tstrcat( tstrcpy( &q, name ), "_" )

                    mov ebx,1
                    .if ( SymFind( tstrcat( rax, [rdi].name ) ) )
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

ComAlloc proc __ccall uses rsi rdi rbx buffer:string_t, tokenarray:token_t

   .new adr[16]:sbyte
   .new name:string_t

    ldr rbx,tokenarray
    mov edi,tstricmp( [rbx].string_ptr, "@ComAlloc" )
    .if edi
        .while [rbx].token != T_FINAL
            .if [rbx].token == T_ID
                mov edi,tstricmp( [rbx].string_ptr, "@ComAlloc" )
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

    SymFind( [rbx].string_ptr )
    .if ( rax && [rax].asym.state == SYM_TMACRO )
        SymFind( [rax].asym.string_ptr )
    .endif
    .if ( rax == NULL )
        .return ERROR
    .endif
    .if ( [rax].asym.state == SYM_TYPE )
        .while ( [rax].asym.type )
            mov rax,[rax].asym.type
        .endw
    .endif

    .if ( !( [rax].asym.flags & S_VTABLE ) )
        .return 0
    .endif
    mov rsi,rax
    mov name,[rsi].asym.name

    .new table:string_t = NULL
    .if ( [rbx+asm_tok].token == T_COMMA && [rbx+asm_tok*3].token == T_CL_BRACKET )
        mov table,[rbx+asm_tok*2].string_ptr
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif

    mov edi,ModuleInfo.accumulator
    .if ( table )
        AddLineQueueX( "mov %r,malloc(%s)", &[rdi+T_ECX-T_EAX], name )
    .else
        AddLineQueueX( "mov %r,malloc(%s + %sVtbl)", &[rdi+T_ECX-T_EAX], name, name )
    .endif
    mov eax,4
    .if ( edi == T_RAX )
        mov eax,8
    .endif
    .if ( [rsi].asym.total_size > eax )

        tsprintf( &adr, "[%r]", &[rdi+T_ECX-T_EAX] )
        ClearStruct( &adr, rsi )
        .if ( !table )
            AddLineQueueX( "mov %r, %r", edi, &[rdi+T_ECX-T_EAX] )
        .endif
    .endif

    .if ( table )
        AddLineQueueX( "lea %r, %s", edi, table )
        AddLineQueueX( "mov [%r], %r", &[rdi+T_ECX-T_EAX], edi )
        AddLineQueueX( "mov %r, %r", edi, &[rdi+T_ECX-T_EAX] )
    .else
        AddLineQueueX( "add %r, %s", &[rdi+T_ECX-T_EAX], name )
        AddLineQueueX( "mov [%r], %r", edi, &[rdi+T_ECX-T_EAX] )
        AssignVTable( name, [rsi].asym.vtable, &[rdi+T_ECX-T_EAX], 0 )
        AddLineQueueX( "lea %r, [%r-%s]", edi, &[rdi+T_ECX-T_EAX], name )
    .endif
    InsertLineQueue()

    sub rbx,asm_tok*2
    .if ( rbx != tokenarray )
        tsprintf(buffer, "%r", edi)
    .endif
   .return 1

ComAlloc endp

endif

    end
