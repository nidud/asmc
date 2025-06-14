; CONTEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Processing of PUSHCONTEXT and POPCONTEXT directives.
;

include asmc.inc
include memalloc.inc
include parser.inc
include assume.inc
include expreval.inc
include fastpass.inc
include listing.inc

; v2.10: static variables moved to ModuleInfo

define contextStack     <MODULE.ContextStack>
define contextFree      <MODULE.ContextFree>
define cntsavedContexts <MODULE.cntSavedContexts>
define savedContexts    <MODULE.SavedContexts>

.enum context_type {
    CONT_ASSUMES   = 0x01,
    CONT_RADIX     = 0x02,
    CONT_LISTING   = 0x04,
    CONT_CPU       = 0x08,
    CONT_ALIGNMENT = 0x10, ; new for v2.0, specific for JWasm
    CONT_ALL       = CONT_ASSUMES or CONT_RADIX or CONT_LISTING or CONT_CPU,
    }

.data

typetab context_type \
    CONT_ASSUMES,
    CONT_RADIX,
    CONT_LISTING,
    CONT_CPU,
    CONT_ALIGNMENT,
    CONT_ALL

contextnames string_t \
    @CStr("ASSUMES"),
    @CStr("RADIX"),
    @CStr("LISTING"),
    @CStr("CPU"),
    @CStr("ALIGNMENT"),
    @CStr("ALL")


define NUM_STDREGS 16

; Masm has a max context nesting level of 10.
; JWasm has no restriction currently.

.template assumes_context
    SegAssumeTable assume_info NUM_SEGREGS dup(<>)
    StdAssumeTable assume_info NUM_STDREGS dup(<>)
    type_content stdassume_typeinfo NUM_STDREGS dup(<>)
   .ends

.template listing_context
    list_macro listmacro ?
    list db ?
    cref db ?
    listif db ?
    list_generated_code db ?
   .ends

.template cpu_context
    cpu int_t ?             ; saved ModuleInfo.cpu
    curr_cpu cpu_info ?     ; saved ModuleInfo.curr_cpu
   .ends

.template radix_context
    radix db ?              ; saved ModuleInfo.radix
   .ends

.template alignment_context
    fieldalign db ?         ; saved ModuleInfo.fieldalign
    procalign db ?          ; saved ModuleInfo.procalign
   .ends


; v2.10: the type-specific data is now declared as a union;
; and PUSH|POPCONTEXT ALL will push/pop 4 single items.
; all items are equal in size, this made it possible to implement
; a "free items" heap.

.template context
    next ptr context ?
    type context_type ?
    union
        rc  radix_context <>
        alc alignment_context <>
        lc  listing_context <>
        cc  cpu_context <>
        ac  assumes_context <>
    ends
   .ends

ifndef ASMC64
extern sym_Cpu:ptr asym
endif

.code

; v2.10: major rewrite of this function

    assume rbx:ptr asm_tok
    assume rdi:ptr context

ContextDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

    imul ebx,i,asm_tok
    add rbx,tokenarray

   .new start:ptr asm_tok = rbx
   .new directive:int_t = [rbx].tokval
   .new k:int_t

    inc i ; skip CONTEXT keyword
    add rbx,asm_tok

    .while ( [rbx].token == T_ID )

        lea rsi,contextnames
        .for ( k = 0, edi = -1: k < lengthof(typetab): k++ )

            mov ecx,k
            .if ( tstricmp( [rsi+rcx*string_t], [rbx].string_ptr ) == 0 )

                mov edx,k
                lea rcx,typetab
                mov edi,[rcx+rdx*4]
                .break
            .endif
        .endf
        .break .if ( edi == -1 )

        ; reject ALIGNMENT if strict masm compat is on

        .if ( Options.strict_masm_compat )
            .if ( edi == CONT_ALIGNMENT )
                .break
            .else
                and edi,not CONT_ALIGNMENT ; in case ALIGNMENT is again included in ALL
            .endif
        .endif
        .new type:context_type = edi

        .if ( directive == T_POPCONTEXT )

            ; for POPCONTEXT, check if appropriate items are on the stack

            .new prev:ptr context = NULL
            .new next:ptr context

            .for ( rdi = contextStack : rdi && type : rdi = next )

                mov next,[rdi].next
                mov ecx,[rdi].type
                .if ( !( ecx & type ) ) ; matching item on the stack?
                    mov prev,rdi
                   .continue
                .endif
                not ecx
                and type,ecx
                .if ( prev )
                    mov rcx,prev
                    mov [rcx].context.next,rax
                .else
                    mov contextStack,rax
                .endif

                mov [rdi].next,contextFree
                mov contextFree,rdi

                ; restore the values

                mov eax,[rdi].type
                .switch pascal eax
                .case CONT_ASSUMES
                    SetSegAssumeTable( &[rdi].ac.SegAssumeTable )
                    SetStdAssumeTable( &[rdi].ac.StdAssumeTable, &[rdi].ac.type_content )
                .case CONT_RADIX
                    mov MODULE.radix,[rdi].rc.radix
                .case CONT_ALIGNMENT
                    mov MODULE.fieldalign,[rdi].alc.fieldalign
                    mov MODULE.procalign,[rdi].alc.procalign
                .case CONT_LISTING
                    mov MODULE.list_macro,[rdi].lc.list_macro
                    movzx eax,[rdi].lc.list
                    mov MODULE.list,eax
                    movzx eax,[rdi].lc.cref
                    mov MODULE.cref,eax
                    movzx eax,[rdi].lc.listif
                    mov MODULE.listif,eax
                    movzx eax,[rdi].lc.list_generated_code
                    mov MODULE.list_generated_code,eax
                .case CONT_CPU
                    mov MODULE.cpu,[rdi].cc.cpu
ifndef ASMC64
                    mov rcx,sym_Cpu
                    .if ( rcx )
                        mov [rcx].asym.value,[rdi].cc.cpu
                    .endif
endif
                    mov MODULE.curr_cpu,[rdi].cc.curr_cpu
                .endsw
            .endf
            .if ( type )
                mov rcx,start
                .return( asmerr( 1010, [rcx].asm_tok.tokpos ) )
            .endif

        .else

            .for ( esi = 0: esi < lengthof(typetab) && type: esi++ )

                lea rcx,typetab
                mov eax,[rcx+rsi*4]

                .if ( type & eax )

                    not eax
                    and type,eax

                    .if ( contextFree )
                        mov rdi,contextFree
                        mov contextFree,[rdi].next
                    .else
                        mov rdi,LclAlloc( sizeof( context ) )
                    .endif

                    mov [rdi].next,contextStack
                    lea rcx,typetab
                    mov [rdi].type,[rcx+rsi*4]
                    mov contextStack,rdi
                    ;mov eax,[rcx+rsi*4]
                    .switch pascal eax
                    .case CONT_ASSUMES
                        GetSegAssumeTable( &[rdi].ac.SegAssumeTable )
                        GetStdAssumeTable( &[rdi].ac.StdAssumeTable, &[rdi].ac.type_content )
                    .case CONT_RADIX
                        mov [rdi].rc.radix,MODULE.radix
                    .case CONT_ALIGNMENT
                        mov [rdi].alc.fieldalign,MODULE.fieldalign
                        mov [rdi].alc.procalign,MODULE.procalign
                    .case CONT_LISTING
                        mov [rdi].lc.list_macro,MODULE.list_macro
                        mov eax,MODULE.list
                        mov [rdi].lc.list,al
                        mov eax,MODULE.cref
                        mov [rdi].lc.cref,1
                        mov eax,MODULE.listif
                        mov [rdi].lc.listif,al
                        mov eax,MODULE.list_generated_code
                        mov [rdi].lc.list_generated_code,al
                    .case CONT_CPU
                        mov [rdi].cc.cpu,MODULE.cpu
                        mov [rdi].cc.curr_cpu,MODULE.curr_cpu
                    .endsw
                .endif
            .endf
        .endif
        add rbx,asm_tok
        .if ( [rbx].token == T_COMMA && [rbx+asm_tok].token != T_FINAL )
            add rbx,asm_tok
        .endif
    .endw
    .if ( [rbx].token != T_FINAL || type == -1 )
        .return( asmerr(2008, [rbx].tokpos ) )
    .endif
    .return( NOT_ERROR )

ContextDirective endp


; save current context status

    assume rdi:ptr context

ContextSaveState proc uses rsi rdi rbx

    .for ( ecx = 0, rdx = contextStack : rdx : ecx++, rdx = [rdx].context.next )
    .endf
    .if ( ecx )
        mov cntsavedContexts,ecx
        imul ecx,ecx,sizeof( context )
        mov savedContexts,LclAlloc( ecx )
        .for ( rsi = contextStack, rdi = rax : rsi : rsi = [rsi].context.next )

            mov rdx,rsi
            mov ecx,sizeof( context )
            rep movsb
            mov rsi,rdx
        .endf
    .endif
    ret

ContextSaveState endp


; restore context status

ContextRestoreState proc private uses rsi rdi rbx

    .for ( ebx = cntsavedContexts : ebx : ebx-- )
        .if ( contextFree )
            mov rdi,contextFree
            mov contextFree,[rdi].next
        .else
            mov rdi,LclAlloc( sizeof( context ) )
        .endif
        lea rax,[rbx-1]
        imul esi,eax,sizeof( context )
        add rsi,savedContexts
        mov ecx,sizeof( context )
        mov rdx,rdi
        rep movsb
        mov rdi,rdx
        mov [rdi].next,contextStack
        mov contextStack,rdi
    .endf
    ret

ContextRestoreState endp


; init context, called once per pass

ContextInit proc __ccall pass:int_t

    ; if ContextStack isn't NULL, then at least one PUSHCONTEXT
    ; didn't have a matching POPCONTEXT. No need to reset it to NULL -
    ; but might be ok to move the items to the ContextFree heap.

    .if ( pass > PASS_1 )
        ContextRestoreState()
    .endif
    ret
ContextInit endp

    end
