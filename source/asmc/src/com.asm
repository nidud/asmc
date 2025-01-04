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

    assume rdi:ptr sfield

AssignVTable proc __ccall private uses rsi rdi rbx name:string_t, sym:ptr dsym, reg:int_t, i:int_t, level:ptr node

   .new q[256]:char_t
   .new t[256]:char_t
   .new n:node
   .new m:int_t

    ldr rsi,sym

    mov n.sym,rsi
    mov n.next,level

    .if ( [rsi].asym.total_size )

        .for ( rdx = [rsi].dsym.structinfo,
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


    assume rbx:ptr asm_tok

ClearStruct proto __ccall :string_t, :asym_t

ComAlloc proc __ccall uses rsi rdi rbx buffer:string_t, tokenarray:token_t

   .new adr[16]:sbyte
   .new name:string_t
   .new r_di:int_t
   .new size:int_t

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
    .if MODULE.line_queue.head
        RunLineQueue()
    .endif

    mov edi,MODULE.accumulator
    .if ( table )
        AddLineQueueX( "malloc(%s)", name )
    .else
        AddLineQueueX( "malloc(%s + %sVtbl)", name, name )
    .endif
    mov ecx,4
    .if ( edi == T_RAX )
        mov ecx,8
    .endif
    mov eax,[rsi].asym.total_size
    .if ( eax > ecx )

        sub eax,ecx
        mov size,eax

        .if ( eax <= 16 )

            mov r_di,ecx

            lea edx,[rdi+T_EDX-T_EAX]
            AddLineQueueX( " xor %r, %r", edx, edx )

            .for ( edi = r_di : edi < size : edi += r_di )

                mov ecx,MODULE.accumulator
                lea edx,[rcx+T_EDX-T_EAX]

                AddLineQueueX(" mov [%r+%d], %r", ecx, edi, edx )
            .endf
            mov edi,MODULE.accumulator

        .else

            lea eax,[rdi+T_EDI-T_EAX]
            lea edx,[rdi+T_EDX-T_EAX]
            mov r_di,eax
            AddLineQueueX(
                " mov %r, %r\n"
                " lea %r, [%r+%d]\n"
                " mov ecx, %d\n"
                " xor eax, eax\n"
                " rep stosb\n"
                " lea %r, [%r-%d]\n"
                " mov %r, %r\n",
                edx, r_di,
                r_di, edi, ecx,
                size,
                edi, r_di, [rsi].asym.total_size,
                r_di, edx )
        .endif
    .endif

    .if ( table )

        AddLineQueueX( "lea %r, %s", &[rdi+T_ECX-T_EAX], table )
        AddLineQueueX( "mov [%r], %r", edi, &[rdi+T_ECX-T_EAX] )
    .else
        AddLineQueueX( "lea %r, [%r+%s]", &[rdi+T_ECX-T_EAX], edi, name )
        AddLineQueueX( "mov [%r], %r", edi, &[rdi+T_ECX-T_EAX] )
        AssignVTable( name, [rsi].asym.vtable, &[rdi+T_ECX-T_EAX], 0, 0 )
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
