; NAMESPACE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include asmc.inc
include parser.inc
include types.inc
include memalloc.inc

    .code

    assume rsi:ptr nsp_item

NameSpace proc watcall uses rsi rdi rbx Name:string_t, retval:string_t

    mov rsi,ModuleInfo.NspStack
    .if ( rsi || rax != rdx )

       .new buffer[256]:char_t
        mov rdi,rdx ; retval
        mov rbx,rax ; name

        .if ( !rdi || rdi == rax )
            lea rdi,buffer
        .endif
        mov byte ptr [rdi],0
        .if ( rsi == NULL )
            tstrcpy( rdi, rax )
        .else
            .repeat
                tstrcat( rdi, [rsi].name )
                tstrcat( rdi, "_" )
                mov rsi,[rsi].next
            .until !rsi
            tstrcat( rdi, rbx )
        .endif
        .if ( rdi != retval )
            LclDup( rdi )
        .endif
    .endif
    ret

NameSpace endp


    assume rbx:ptr asm_tok

NameSpaceDirective proc __ccall uses rsi rbx i:int_t, tokenarray:token_t

    mov rbx,tokenarray
    mov rsi,ModuleInfo.NspStack

    .if ( [rbx].tokval == T_DOT_ENDN )

        .if ( rsi == NULL )
            .return asmerr( 1011 )
        .endif

        mov rcx,[rsi].next
        .if ( rcx )

            .while ( [rcx].nsp_item.next )

                mov rcx,[rcx].nsp_item.next
                mov rsi,[rsi].next
            .endw
            mov [rsi].next,NULL
        .else
            mov ModuleInfo.NspStack,NULL
        .endif
        .return NOT_ERROR
    .endif

    mov rsi,LclAlloc( &[tstrlen( [rbx+asm_tok].string_ptr ) + nsp_item + 1] )

    mov [rsi].next,NULL
    mov [rsi].name,&[rax+nsp_item]

    tstrcpy( [rsi].name, [rbx+asm_tok].string_ptr )

    .if ( ModuleInfo.NspStack == NULL )

        mov ModuleInfo.NspStack,rsi

    .else

        mov rax,rsi
        mov rsi,ModuleInfo.NspStack

        .while ( [rsi].next )
            mov rsi,[rsi].next
        .endw
        mov [rsi].next,rax
    .endif
    .return NOT_ERROR

NameSpaceDirective endp

    end
