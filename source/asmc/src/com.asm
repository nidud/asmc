; COM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include lqueue.inc
include parser.inc

ifdef USE_COMALLOC

; v2.36.16 - link to nearest public class
;
; C1 : public IUnknown
; C2 : public C1
;
; ifndef (C2::Release)
;  ifdef (C1::Release)
;   C2::Release = C1::Release
;  elseifdef (IUnknown::Release)
;   C2::Release = IUnknown::Release
;  else
;   error
;  endif
; endif
;
.template node
    sym  asym_t ?
    next ptr_t ?
   .ends

    .code

    assume rdi:asym_t

AssignVTable proc __ccall private uses rsi rdi rbx name:string_t, sym:asym_t, reg:int_t, i:int_t, level:ptr node

   .new q[256]:char_t
   .new t[256]:char_t
   .new n:node
   .new m:int_t

    ldr rsi,sym

    mov n.sym,rsi
    mov n.next,level

    .if ( [rsi].asym.total_size )

        .for ( rdx = [rsi].asym.structinfo,
               rdi = [rdx].struct_info.head : rdi : rdi = [rdi].next, i++ )

            .if ( [rdi].type )

                mov rdx,[rdi].type
                .if ( [rdx].asym.typekind == TYPE_STRUCT )

                    mov i,AssignVTable(name, rdx, reg, i, &n)

                .else

                    mov m,0
                    .if ( SymFind( tstrcat( tstrcat( tstrcpy( &q, name ), "_" ), [rdi].name ) ) )

                        .if ( [rax].asym.state == SYM_MACRO || [rax].asym.state == SYM_TMACRO )
                            mov m,1
                        .endif

                    .else

                        .for ( rbx = &n : rbx : rbx = [rbx].node.next )

                            mov rcx,[rbx].node.sym
                            .if ( [rcx].asym.name_size > 4 )

                                tstrcpy( &t, [rcx].asym.name )
                                mov rcx,[rbx].node.sym
                                mov edx,[rcx].asym.name_size
                                mov t[rdx-4],'_'
                                mov t[rdx-3],0

                                .if ( SymFind( tstrcat( rax, [rdi].name ) ) )

                                    .if ( [rax].asym.state != SYM_MACRO && [rax].asym.state != SYM_TMACRO )
                                        tstrcpy( &q, &t )
                                    .endif
                                .endif
                            .endif
                        .endf
                    .endif

                    .if ( m == 0 )

                        mov ebx,reg
                        dec ebx
                        AddLineQueueX( "lea %r, %s", ebx, &q )
                        ;
                        ; v2.33.05 - assign member by offset
                        ;
                        movzx eax,MODULE.Ofssize
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


DefaultConstructor proc __ccall uses rsi rdi rbx sym:asym_t, table:string_t

   .new r_di:int_t
   .new size:int_t
   .new wsize:int_t

    ldr rsi,sym
    ldr rbx,table

    movzx eax,MODULE.Ofssize
    shl eax,2
    mov wsize,eax
    mov edi,MODULE.accumulator
    mov ecx,[rsi].asym.total_size

    .if ( rbx )
        mov size,ecx
        AddLineQueueX( "malloc(%d)", ecx )
    .else
        neg eax
        dec ecx
        add ecx,[rsi].asym.total_size
        and ecx,eax
        mov size,ecx
        AddLineQueueX( "malloc(%d + %sVtbl)", size, [rsi].asym.name )
    .endif

    .if ( size > wsize )

        mov ecx,eax
        lea eax,[rdi+T_EDI-T_EAX]
        lea edx,[rdi+T_EDX-T_EAX]
        mov r_di,eax
        AddLineQueueX(
            " mov %r, %r\n"
            " lea %r, [%r+%d]\n"
            " mov ecx, %d-%d\n"
            " xor eax, eax\n"
            " rep stosb\n"
            " lea %r, [%r-%d]\n"
            " xchg %r, %r",
            edx, r_di,
            r_di, edi, ecx,
            size, ecx,
            edi, r_di, size,
            r_di, edx )
    .elseif ( rbx )
        AddLineQueueX( " lea %r, %s", &[rdi+T_EDX-T_EAX], rbx )
    .else
        AddLineQueueX( " lea %r, [%r+%d]", &[rdi+T_EDX-T_EAX], edi, size )
    .endif
    AddLineQueueX( " mov [%r], %r", edi, &[rdi+T_EDX-T_EAX] )
    .if ( !rbx )
        AssignVTable( [rsi].asym.name, [rsi].asym.vtable, &[rdi+T_EDX-T_EAX], 0, 0 )
    .endif
    mov eax,edi
    ret

DefaultConstructor endp

    assume rbx:token_t

ComAlloc proc __ccall uses rsi rdi rbx buffer:string_t, tokenarray:token_t

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
    .if ( !( [rax].asym.hasvtable ) )
        .return 0
    .endif
    mov rsi,rax
    xor edi,edi
    .if ( [rbx+asm_tok].token == T_COMMA && [rbx+asm_tok*3].token == T_CL_BRACKET )
        mov rdi,[rbx+asm_tok*2].string_ptr
    .endif
    .if MODULE.line_queue.head
        RunLineQueue()
    .endif
    mov edi,DefaultConstructor(rsi, rdi)
    InsertLineQueue()
    sub rbx,asm_tok*2
    .if ( rbx != tokenarray )
        tsprintf(buffer, "%r", edi)
    .endif
   .return 1

ComAlloc endp

endif

    end
