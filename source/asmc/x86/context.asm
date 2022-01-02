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

;; v2.10: static variables moved to ModuleInfo

define contextStack     <ModuleInfo.ContextStack>
define contextFree      <ModuleInfo.ContextFree>
define cntsavedContexts <ModuleInfo.cntSavedContexts>
define savedContexts    <ModuleInfo.SavedContexts>

.enum context_type {
    CONT_ASSUMES   = 0x01,
    CONT_RADIX     = 0x02,
    CONT_LISTING   = 0x04,
    CONT_CPU       = 0x08,
    CONT_ALIGNMENT = 0x10, ;; new for v2.0, specific for JWasm
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

;; Masm has a max context nesting level of 10.
;; JWasm has no restriction currently.

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
    cpu int_t ?             ;; saved ModuleInfo.cpu
    curr_cpu cpu_info ?     ;; saved ModuleInfo.curr_cpu
   .ends

.template radix_context
    radix db ?              ;; saved ModuleInfo.radix
   .ends

.template alignment_context
    fieldalign db ?         ;; saved ModuleInfo.fieldalign
    procalign db ?          ;; saved ModuleInfo.procalign
   .ends


;; v2.10: the type-specific data is now declared as a union;
;; and PUSH|POPCONTEXT ALL will push/pop 4 single items.
;; all items are equal in size, this made it possible to implement
;; a "free items" heap.

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

;; v2.10: major rewrite of this function

    assume ebx:ptr asm_tok
    assume edi:ptr context

ContextDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

    imul ebx,i,asm_tok
    add ebx,tokenarray

    .new start:int_t = ebx
    .new directive:int_t = [ebx].tokval
    .new type:context_type

    inc i ;; skip CONTEXT keyword
    add ebx,16

    .while ( [ebx].token == T_ID )

        .for ( esi = 0, edi = -1: esi < lengthof(typetab): esi++ )

            .if ( tstricmp( contextnames[esi*4], [ebx].string_ptr ) == 0 )
                mov edi,typetab[esi*4]
                .break
            .endif
        .endf

        .break .if ( edi == -1 )

        ;; reject ALIGNMENT if strict masm compat is on
        .if ( ModuleInfo.strict_masm_compat )
            .if ( edi == CONT_ALIGNMENT )
                .break
            .else
                and edi,not CONT_ALIGNMENT ;; in case ALIGNMENT is again included in ALL
            .endif
        .endif
        mov type,edi

        .if ( directive == T_POPCONTEXT )

            .new prev:ptr context
            .new next:ptr context

            ;; for POPCONTEXT, check if appropriate items are on the stack

            .for ( prev = NULL, edi = contextStack : edi && type : edi = next )

                mov next,[edi].next
                mov ecx,[edi].type
                .if ( !( ecx & type ) ) ;; matching item on the stack?
                    mov prev,edi
                    .continue
                .endif
                not ecx
                and type,ecx
                .if ( prev )
                    mov ecx,prev
                    mov [ecx].context.next,eax
                .else
                    mov contextStack,eax
                .endif

                mov [edi].next,contextFree
                mov contextFree,edi

                ;; restore the values

                mov eax,[edi].type
                .switch pascal eax
                .case CONT_ASSUMES
                    SetSegAssumeTable( &[edi].ac.SegAssumeTable )
                    SetStdAssumeTable( &[edi].ac.StdAssumeTable, &[edi].ac.type_content )
                .case CONT_RADIX
                    mov ModuleInfo.radix,       [edi].rc.radix
                .case CONT_ALIGNMENT
                    mov ModuleInfo.fieldalign,  [edi].alc.fieldalign
                    mov ModuleInfo.procalign,   [edi].alc.procalign
                .case CONT_LISTING
                    mov ModuleInfo.list_macro,  [edi].lc.list_macro
                    mov ModuleInfo.list,        [edi].lc.list
                    mov ModuleInfo.cref,        [edi].lc.cref
                    mov ModuleInfo.listif,      [edi].lc.listif
                    mov ModuleInfo.list_generated_code, [edi].lc.list_generated_code
                .case CONT_CPU
                    mov ModuleInfo.cpu,         [edi].cc.cpu
ifndef ASMC64
                    mov ecx,sym_Cpu
                    .if ( ecx )
                        mov [ecx].asym.value,[edi].cc.cpu
                    .endif
endif
                    mov ModuleInfo.curr_cpu,    [edi].cc.curr_cpu
                .endsw
            .endf
            .if ( type )
                mov ecx,start
                .return( asmerr( 1010, [ecx].asm_tok.tokpos ) )
            .endif

        .else

            .for ( esi = 0: esi < lengthof(typetab) && type: esi++ )

                .if ( type & typetab[esi*4]  )

                    not eax
                    and type,eax

                    .if ( contextFree )
                        mov edi,contextFree
                        mov contextFree,[edi].next
                    .else
                        mov edi,LclAlloc( sizeof( context ) )
                    .endif

                    mov [edi].type,typetab[esi*4]
                    mov [edi].next,contextStack
                    mov contextStack,edi

                    mov eax,typetab[esi*4]
                    .switch pascal eax
                    .case CONT_ASSUMES
                        GetSegAssumeTable( &[edi].ac.SegAssumeTable )
                        GetStdAssumeTable( &[edi].ac.StdAssumeTable, &[edi].ac.type_content )
                    .case CONT_RADIX
                        mov [edi].rc.radix,         ModuleInfo.radix
                    .case CONT_ALIGNMENT
                        mov [edi].alc.fieldalign,   ModuleInfo.fieldalign
                        mov [edi].alc.procalign,    ModuleInfo.procalign
                    .case CONT_LISTING
                        mov [edi].lc.list_macro,    ModuleInfo.list_macro
                        mov [edi].lc.list,          ModuleInfo.list
                        mov [edi].lc.cref,          ModuleInfo.cref
                        mov [edi].lc.listif,        ModuleInfo.listif
                        mov [edi].lc.list_generated_code, ModuleInfo.list_generated_code
                    .case CONT_CPU
                        mov [edi].cc.cpu,           ModuleInfo.cpu
                        mov [edi].cc.curr_cpu,      ModuleInfo.curr_cpu
                    .endsw
                .endif
            .endf
        .endif
        add ebx,16
        .if ( [ebx].token == T_COMMA && [ebx+16].token != T_FINAL )
            add ebx,16
        .endif
    .endw
    .if ( [ebx].token != T_FINAL || type == -1 )
        .return( asmerr(2008, [ebx].tokpos ) )
    .endif
    .return( NOT_ERROR )
ContextDirective endp

;; save current context status

ContextSaveState proc uses esi edi ebx

    .for ( ecx = 0, edx = contextStack : edx : ecx++, edx = [edx].context.next )
    .endf
    .if ( ecx )
        mov cntsavedContexts,ecx
        imul ecx,ecx,sizeof( context )
        mov savedContexts,LclAlloc( ecx )
        .for ( esi = contextStack, edi = eax : esi : esi = [esi].context.next )

            mov edx,esi
            mov ecx,sizeof( context )
            rep movsb
            mov esi,edx
        .endf
    .endif
    ret
ContextSaveState endp

;; restore context status

ContextRestoreState proc private uses esi edi ebx

    .for ( ebx = cntsavedContexts : ebx : ebx-- )
        .if ( contextFree )
            mov edi,contextFree
            mov contextFree,[edi].next
        .else
            mov edi,LclAlloc( sizeof( context ) )
        .endif
        lea eax,[ebx-1]
        imul esi,eax,sizeof( context )
        add esi,savedContexts
        mov ecx,sizeof( context )
        mov edx,edi
        rep movsb
        mov edi,edx
        mov [edi].next,contextStack
        mov contextStack,edi
    .endf
    ret
ContextRestoreState endp

;; init context, called once per pass

ContextInit proc pass:int_t

    ;; if ContextStack isn't NULL, then at least one PUSHCONTEXT
    ;; didn't have a matching POPCONTEXT. No need to reset it to NULL -
    ;; but might be ok to move the items to the ContextFree heap.
    ;;
    .if ( pass > PASS_1 )
        ContextRestoreState()
    .endif
    ret
ContextInit endp

    end
