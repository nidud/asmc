; PRAGMADIRECTIVE.ASM--
; Copyright (C) 2018 Asmc Developers
;
; Change history:
; 2024-09-04 - .pragma wstring(push, <0|1>)
;              .pragma wstring(pop)
; 2024-04-12 - removed .pragma asmc
; 2019-04-18 - .pragma asmc(push, <0|1>)
;              .pragma asmc(pop)
; 2019-03-19 - .pragma warning(disable: <num>)
;              .pragma warning(push)
;              .pragma warning(pop)
; 2019-03-17 - .pragma comment(lib, name[, name])
;              .pragma comment(linker, "/..")
; 2018-05-04 - .pragma cref(push, <0|1>)
;              .pragma cref(pop)
; 2018-04-24 - .pragma list(push, <0|1>)
;              .pragma list(pop)
; 2018-04-22 - .pragma pack(push, <alignment>)
;              .pragma pack(pop)
; 2018-03-24 - .pragma init(<proc>, <priority>)
;              .pragma exit(<proc>, <priority>)
; 2024-06-27 - .pragma aux(push, <language>, <fixed>, <regs>)
;              .pragma aux(pop)
;
include malloc.inc
include string.inc

include asmc.inc
include proc.inc
include parser.inc
include segment.inc
include listing.inc
include memalloc.inc
include expreval.inc
include lqueue.inc
include hll.inc

warning struct
id      short_t ?
state   char_t ?
warning ends

MAXSTACK equ 16

    .data

    pragma_wtable warning \
        { 4003, 0 },
        { 4005, 0 },
        { 4006, 0 },
        { 4007, 0 },
        { 4008, 0 },
        { 4011, 0 },
        { 4012, 0 },
        { 4910, 0 },
        { 6003, 0 },
        { 6004, 0 },
        { 6005, 0 },
        { 8000, 0 },
        { 8001, 0 },
        { 8002, 0 },
        { 8003, 0 },
        { 8004, 0 },
        { 8005, 0 },
        { 8006, 0 },
        { 8007, 0 },
        { 8008, 0 },
        { 8009, 0 },
        { 8010, 0 },
        { 8011, 0 },
        { 8012, 0 },
        { 8013, 0 },
        { 8014, 0 },
        { 8015, 0 },
        { 8017, 0 },
        { 8018, 0 },
        { 8019, 0 },
        { 8020, 0 },
        { 8022, 0 },
        { 7000, 0 },
        { 7001, 0 },
        { 7002, 0 },
        { 7003, 0 },
        { 7004, 0 },
        { 7005, 0 },
        { 7006, 0 },
        { 7007, 0 },
        { 7008, 0 }

    wtable_count equ lengthof(pragma_wtable)

    ListCount dd 0
    PackCount dd 0
    CrefCount dd 0
    WarnCount dd 0
    wstringfl dd 0

    PackStack db MAXSTACK dup(0)
    ListStack db MAXSTACK dup(0)
    CrefStack db MAXSTACK dup(0)
    WarnStack intptr_t MAXSTACK dup(0)

    .code

    assume rbx:token_t

PragmaDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local rc:int_t, list_directive:int_t
  local opndx:expr
  local stdlib[256]:char_t
  local dynlib[256]:char_t
  local q:ptr qitem
  local quote_s:char_t


    mov rc,NOT_ERROR
    mov list_directive,0

    inc i
    imul ebx,i,asm_tok
    add rbx,tokenarray
    .if ( [rbx].token == T_OP_BRACKET || [rbx].token == T_COMMA )
        inc i
        add rbx,asm_tok
    .endif

    mov rsi,[rbx].string_ptr
    mov eax,[rsi]
    or  eax,0x20202020
    inc i
    add rbx,asm_tok
    .if ( [rbx].token == T_OP_BRACKET || [rbx].token == T_COMMA )
        inc i
        add rbx,asm_tok
    .endif

    bswap   eax
    .switch eax

    .case "wstr"

        ; .pragma wstring(pop)

        .if ( [rbx].tokval == T_POP )

            add rbx,asm_tok
            .if [rbx].token == T_CL_BRACKET
                add rbx,asm_tok
            .endif
            shr wstringfl,1
            .ifc
                mov MODULE.wstring,1
            .else
                mov MODULE.wstring,0
            .endif
            .endc
        .endif

        ; .pragma wstring(push, bool)

        .if ( [rbx].tokval == T_PUSH )

            inc i
            .if ( [rbx+asm_tok].token == T_COMMA )
                inc i
            .endif
            .endc .ifd EvalOperand(&i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF) == ERROR

            imul ebx,i,asm_tok
            add rbx,tokenarray
            .if ( opndx.kind != EXPR_CONST )
                asmerr( 2026 )
               .endc
            .endif
            mov eax,opndx.uvalue
            .if ( eax > 1 )

                asmerr( 2084 )
               .endc
            .endif
            shl wstringfl,1
            .if ( MODULE.wstring )
                or wstringfl,1
            .endif
            .if ( eax )
                mov MODULE.wstring,1
            .else
                mov MODULE.wstring,0
            .endif
            add rbx,asm_tok
            .if [rbx].token == T_CL_BRACKET
                add rbx,asm_tok
            .endif
        .endif
        .endc

    .case "aux "

        .endc .if ( [rbx].token != T_REG )

        mov rdx,get_fasttype(MODULE.Ofssize, LANG_ASMCALL)
        mov rdi,[rdx].fc_info.regpack
        xor eax,eax
        mov ecx,fc_regs
        rep stosb
        mov rdi,rdx
        mov [rdi].fc_info.maxgpr,0
        mov [rdi].fc_info.regmask,0

        .for ( esi = 0 : esi < 8 && [rbx].token == T_REG : esi++ )

            inc [rdi].fc_info.maxgpr
            get_register([rbx].tokval, 1)
            mov rdx,[rdi].fc_info.regpack
            mov [rdx].fc_regs.gpr_db[rsi],al
            get_register([rbx].tokval, 2)
            mov rdx,[rdi].fc_info.regpack
            mov [rdx].fc_regs.gpr_dw[rsi],al

            .if ( MODULE.Ofssize )

                get_register([rbx].tokval, 4)
                mov rdx,[rdi].fc_info.regpack
                mov [rdx].fc_regs.gpr_dd[rsi],al
            .endif
            .if ( MODULE.Ofssize == USE64 )

                get_register([rbx].tokval, 8)
                mov rdx,[rdi].fc_info.regpack
                mov [rdx].fc_regs.gpr_dq[rsi],al
            .endif

            mov  ecx,[rbx].asm_tok.tokval
            lea  rdx,SpecialTable
            imul eax,ecx,special_item
            mov  cl,[rdx+rax].special_item.bytval
            mov  eax,1
            shl  eax,cl
            or   [rdi].fc_info.regmask,eax
            add  rbx,asm_tok

            .if ( [rbx].token == T_COMMA )
                add rbx,asm_tok
            .endif
        .endf
        add rbx,asm_tok
        .if [rbx].token == T_CL_BRACKET
            add rbx,asm_tok
        .endif
        .endc

    .case "warn"

        ;
        ; .pragma warning(pop)
        ;
        .if [rbx].tokval == T_POP

            add rbx,asm_tok
            .if [rbx].token == T_CL_BRACKET
                add rbx,asm_tok
            .endif

            .endc .if !WarnCount

            lea rcx,WarnStack
            .for ( WarnCount--,
                   eax = WarnCount,
                   rdx = [rcx+rax*intptr_t],
                   rsi = &pragma_wtable,
                   ecx = 0 : ecx < wtable_count : ecx++, rsi += sizeof(warning) )

                mov al,[rdx+rcx]
                mov [rsi].warning.state,al
            .endf

            MemFree(rdx)
           .endc
        .endif

        ; .pragma warning(push)

        .if ( [rbx].tokval == T_PUSH )

            add rbx,asm_tok
            .if ( [rbx].token == T_CL_BRACKET )
                add rbx,asm_tok
            .endif
            mov edi,WarnCount
            inc edi
            .endc .if edi >= MAXSTACK
            mov WarnCount,edi
            MemAlloc(wtable_count)
            lea rcx,WarnStack
            .for ( [rcx+rdi*intptr_t-intptr_t] = rax,
                   rsi = &pragma_wtable,
                   ecx = 0 : ecx < wtable_count : ecx++, rsi += sizeof(warning) )

                mov dl,[rsi].warning.state
                mov [rax+rcx],dl
            .endf
            .endc

        .endif

        ; .pragma warning(disable: <num>)

        mov rsi,[rbx].string_ptr
        mov eax,[rsi]
        or  eax,0x20202020

        .endc .if ( eax != 'asid' )
        .endc .if ( [rbx+asm_tok].token != T_COLON )

        add i,2
        .endc .ifd EvalOperand(&i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF) == ERROR

        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if ( opndx.kind != EXPR_CONST )

            asmerr( 2026 )
           .endc
        .endif

        .for ( eax = opndx.uvalue, rsi = &pragma_wtable,
               ecx = 0 : ecx < wtable_count : ecx++, rsi += sizeof(warning) )

            .if ( [rsi].warning.id == ax )

                mov [rsi].warning.state,1
                .break
            .endif
        .endf

        add rbx,asm_tok
        .if [rbx].token == T_CL_BRACKET
            add rbx,asm_tok
        .endif
        .endc

    .case "comm"

        mov eax,[rsi+4]
        or  eax,0x202020
        .endc .if eax != 'tne'
        .endc .if [rbx+asm_tok].token != T_COMMA

        mov rsi,[rbx].string_ptr
        mov eax,[rsi]
        or  eax,0x202020
        and eax,0xFFFFFF

        .if eax == 'bil'

            add i,2
            add rbx,asm_tok*2
            mov stdlib,0
            mov dynlib,0
            mov quote_s,0

            ;
            ; .pragma comment(lib, "libc.lib", "msvcrt.lib")
            ;
            ;  if (/pe)
            ;   option dllimport:<msvcrt>
            ;  else
            ;   ifdef _MSVCRT
            ;    includelib msvcrt.lib
            ;   else
            ;    includelib libc.lib
            ;   endif
            ;  endif
            ;

            mov rsi,[rbx].string_ptr
            tstrcpy(&stdlib, rsi)

            .while ( [rbx+asm_tok].token == T_DOT )

                tstrcat(&stdlib, [rbx+asm_tok].string_ptr)
                tstrcat(&stdlib, [rbx+asm_tok*2].string_ptr)
                add i,2
                add rbx,asm_tok*2
            .endw

            .if ( byte ptr [rsi] == '"' )

                inc rsi
                inc quote_s
                .if tstrchr(tstrcpy(&stdlib, rsi), '"')

                    mov byte ptr [rax],0
                .endif
            .endif

            .if ( [rbx+asm_tok].token == T_COMMA )

                add i,2
                add rbx,asm_tok*2

                mov rsi,[rbx].string_ptr
                tstrcpy(&dynlib, rsi)

                .while ( [rbx+asm_tok].token == T_DOT )

                    tstrcat(&dynlib, [rbx+asm_tok].string_ptr)
                    tstrcat(&dynlib, [rbx+asm_tok*2].string_ptr)
                    add i,2
                    add rbx,asm_tok*2
                .endw

                .if ( byte ptr [rsi] == '"' )

                    inc rsi
                    .if tstrchr(tstrcpy(&dynlib, rsi), '"')

                        mov byte ptr [rax],0
                    .endif
                .endif
            .endif

            lea rsi,dynlib
            lea rdi,stdlib
            .if ( tstrrchr(rsi, '.') )

                mov ecx,[rax+1]
                and ecx,0xFFFFFF
                .if ( ecx == 'bil' || ecx == 'lld' )
                    mov byte ptr [rax],0
                .endif
            .endif
            .if ( tstrrchr(rdi, '.') )

                mov ecx,[rax+1]
                and ecx,0xFFFFFF
                .if ( ecx == 'bil' || ecx == 'lld' )
                    mov byte ptr [rax],0
                .endif
            .endif

            .if ( Options.output_format == OFORMAT_BIN )

                .if ( dynlib == 0 )
                    mov rsi,rdi
                .endif
                AddLineQueueX(" option dllimport:<%s>", rsi)

            .elseif !( byte ptr [rsi] )

                .if ( quote_s )
                    AddLineQueueX("includelib \"%s.lib\"", rdi)
                .else
                    AddLineQueueX("includelib %s.lib", rdi)
                .endif

            .else

                .new u[256]:char_t

                tstrupr( tstrcpy( &u, rsi ) )
                .while ( tstrchr( rax, '-' ) )
                    mov byte ptr [rax],'_'
                .endw
                .if ( tstrchr( &u, '.' ) )
                    mov byte ptr [rax],0
                .endif

                AddLineQueueX(
                    "ifdef _%s\n"
                    "includelib %s.lib\n"
                    "else\n"
                    "includelib %s.lib\n"
                    "endif", &u, rsi, rdi )
            .endif

        .elseif ( eax == 'nil' )

            mov eax,[rsi+3]
            or  eax,0x202020
            and eax,0xFFFFFF
            .endc .if eax != 'rek'

            ; .pragma comment(linker, "/..")

            add rbx,asm_tok*2
            mov rsi,[rbx].tokpos
            .endc .if byte ptr [rsi] != '"'

            inc rsi     ; skip first '"'
            lea rdi,dynlib
            mov rcx,rdi

            .if ( Parse_Pass == PASS_1 ) ;; do all work in pass 1

                .repeat
                    lodsb
                    .if al == '"' && byte ptr [rsi] == '"'
                        lodsb
                        add rbx,asm_tok
                        .continue(0)
                    .endif
                    .if al == '\' && byte ptr [rsi] == '"'
                        movsb
                        .continue(0)
                    .endif
                    .if al == '"'
                        xor eax,eax
                    .endif
                    stosb
                .until !al

                sub rdi,rcx
                add rdi,qitem
                mov rdi,LclAlloc( edi )
                tstrcpy( &[rdi].qitem.value, &dynlib )
                QEnqueue( &MODULE.LinkQueue, rdi )
            .else
                .while [rbx].token == T_STRING
                    add rbx,asm_tok
                .endw
            .endif
        .endif

        add rbx,asm_tok
        .if ( [rbx].token == T_CL_BRACKET )
            add rbx,asm_tok
        .endif
        .endc

    .case "init"
    .case "exit"

        ; .pragma init(<proc>, <priority>)
        ; .pragma exit(<proc>, <priority>)

        mov edi,eax
        .if !MODULE.dotname
            AddLineQueueX(" %r dotname", T_OPTION)
        .endif
        .if ( Options.output_format == OFORMAT_ELF && Options.mscrt == 0 )

            inc i
            .if ( [rbx+asm_tok].token == T_COMMA )
                inc i
            .endif
            .endc .ifd EvalOperand(&i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF) == ERROR

            AddLineQueueX(" %r dotnamex:on", T_OPTION)
            lea rsi,@CStr(".fini_array")
            .if edi == "init"
                lea rsi,@CStr(".init_array")
            .endif
            tsprintf(&stdlib, "%s.%05d", rsi, opndx.uvalue)
            lea rsi,stdlib
        .else
            lea rsi,@CStr(".CRT$XTA")
            .if edi == "init"
                lea rsi,@CStr(".CRT$XIA")
            .endif
        .endif
        .if ( MODULE.Ofssize == USE16 )
            SetSimSeg( SIM_CONST, rsi )
        .else
            AddLineQueueX( " %s %r %r(8) 'CONST'", rsi, T_SEGMENT, T_ALIGN )
        .endif
        mov rdx,[rbx].string_ptr
        add rbx,asm_tok
        .if [rbx].token == T_COMMA
            add rbx,asm_tok
        .endif
        .if MODULE.Ofssize == USE64
            .if Options.output_format == OFORMAT_ELF
                AddLineQueueX(" dq %r %s", T_IMAGEREL, rdx)
            .else
                AddLineQueueX(" dd %r %s, %s", T_IMAGEREL, rdx, [rbx].string_ptr)
            .endif
        .else
            AddLineQueueX(" dd %s, %s", rdx, [rbx].string_ptr)
        .endif
        AddLineQueueX(" %s %r", rsi, T_ENDS)
        add rbx,asm_tok
        .if [rbx].token == T_CL_BRACKET
            add rbx,asm_tok
        .endif
        .endc

    .case "pack"

        ; .pragma(pack(push, <alignment>))
        ; .pragma(pack(pop))

        .if [rbx].tokval == T_POP

            add rbx,asm_tok
            .if [rbx].token == T_CL_BRACKET
                add rbx,asm_tok
            .endif
            .endc .if !PackCount

            dec PackCount
            mov eax,PackCount
            lea rcx,PackStack
            mov al,[rcx+rax]
            mov MODULE.fieldalign,al
            .endc
        .endif

        .endc .if [rbx].tokval != T_PUSH
        .endc .if PackCount >= MAXSTACK

        mov edx,PackCount
        inc PackCount
        mov al,MODULE.fieldalign
        lea rcx,PackStack
        mov [rcx+rdx],al
        add rbx,asm_tok
        .if [rbx].token == T_OP_BRACKET || [rbx].token == T_COMMA
            add rbx,asm_tok
        .endif
        AddLineQueueX("OPTION FIELDALIGN: %s", [rbx].string_ptr)
        add rbx,asm_tok
        .if [rbx].token == T_CL_BRACKET
            add rbx,asm_tok
        .endif
        .endc

      .case "list"

        ; .pragma(list(push, 0|1))
        ; .pragma(list(pop))

        inc list_directive
        lea rcx,ListCount
        lea rdx,ListStack
        mov edi,1
        .if [rbx].tokval == T_POP
            .gotosw(T_POP)
        .endif
        .gotosw(T_PUSH)

      .case "cref"

        ; .pragma(cref(push, 0|1))
        ; .pragma(cref(pop))

        inc list_directive
        lea rcx,CrefCount
        lea rdx,CrefStack
        xor edi,edi
        .if [rbx].tokval == T_POP
            .gotosw(T_POP)
        .endif

    .case T_PUSH

        .endc .if [rbx].tokval != T_PUSH

        mov eax,[rcx]
        inc eax
        .endc .if eax >= MAXSTACK

        mov [rcx],eax
        .if ( edi )
            mov ecx,MODULE.list
        .else
            mov ecx,MODULE.cref
        .endif
        mov [rdx+rax-1],cl

        inc i
        .if ( [rbx+asm_tok].token == T_COMMA )
            inc i
        .endif
        .endc .ifd EvalOperand(&i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF) == ERROR

        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if opndx.kind != EXPR_CONST
            asmerr(2026)
           .endc
        .endif
        mov eax,opndx.uvalue
        .if eax > 1
            asmerr(2084)
           .endc
        .endif
        .if ( edi )
            mov MODULE.list,eax
        .else
            mov MODULE.cref,eax
        .endif
        .if ( eax && list_directive )
            or MODULE.line_flags,LOF_LISTED
        .endif
        add rbx,asm_tok
        .if [rbx].token == T_CL_BRACKET
            add rbx,asm_tok
        .endif
        .endc

    .case T_POP

        mov eax,[rcx]
        .endc .if !eax ; gives an error if nothing pushed
        dec eax
        mov [rcx],eax
        mov al,[rdx+rax]
        .if ( edi )
            mov MODULE.list,eax
        .else
            mov MODULE.cref,eax
        .endif
        .if ( al && list_directive )
            or MODULE.line_flags,LOF_LISTED
        .endif
        add rbx,asm_tok
        .if [rbx].token == T_CL_BRACKET
            add rbx,asm_tok
        .endif
        .endc
    .endsw

    .if [rbx].token == T_CL_BRACKET
        add rbx,asm_tok
    .endif
    .if [rbx].token != T_FINAL
        mov rc,asmerr(2008, [rbx].tokpos)
    .endif

    .if !list_directive
        .if MODULE.list
            LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
        .endif
        .if MODULE.line_queue.head
            RunLineQueue()
        .endif
    .endif
    .return( rc )

PragmaDirective endp

PragmaInit proc __ccall

    mov ListCount,0
    mov PackCount,0
    mov CrefCount,0
    ret

PragmaInit endp

PragmaCheckOpen proc __ccall

    .if ListCount || PackCount || CrefCount

        asmerr(1010, ".pragma-push-pop")
    .endif
    ret

PragmaCheckOpen endp

warning_disable proc __ccall id:int_t

    .for ( eax = id,
           rdx = &pragma_wtable,
           ecx = 0 : ecx < wtable_count : ecx++, rdx += sizeof(warning) )

        .if ( ax == [rdx].warning.id )

            movzx eax,[rdx].warning.state
            .return
        .endif
    .endf
    .return( 0 )

warning_disable endp

    END

