; PRAGMADIRECTIVE.ASM--
; Copyright (C) 2018 Asmc Developers
;
; Change history:
; 2019-04-18 - .pragma(asmc(push, <0|1>))
;              .pragma(asmc(pop))
; 2019-03-19 - .pragma(warning(disable: <num>))
;              .pragma(warning(push))
;              .pragma(warning(pop))
; 2019-03-17 - .pragma(comment(lib, name[, name]))
; 2018-05-04 - .pragma(cref(push, <0|1>))
;              .pragma(cref(pop))
; 2018-04-24 - .pragma(list(push, <0|1>))
;              .pragma(list(pop))
; 2018-04-22 - .pragma(pack(push, <alignment>))
;              .pragma(pack(pop))
; 2018-03-24 - .pragma(init(<proc>, <priority>))
;              .pragma(exit(<proc>, <priority>))
;
include malloc.inc
include string.inc

include asmc.inc
include hllext.inc

warning  struct
id       short_t ?
state    char_t ?
warning  ends

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
    AsmcCount dd 0

    PackStack db MAXSTACK dup(0)
    ListStack db MAXSTACK dup(0)
    CrefStack db MAXSTACK dup(0)
    AsmcStack db MAXSTACK dup(0)
    WarnStack intptr_t MAXSTACK dup(0)

    .code

    assume rbx:token_t

PragmaDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local rc:int_t, list_directive:int_t
  local opndx:expr
  local stdlib[256]:char_t
  local dynlib[256]:char_t
  local q:ptr qitem


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

      .case "asmc"

        .if ( [rbx].tokval == T_POP )

            add rbx,asm_tok
            .if ( [rbx].token == T_CL_BRACKET )
                add rbx,asm_tok
            .endif
            .endc .if !AsmcCount

            dec AsmcCount
            mov eax,AsmcCount
            lea rcx,AsmcStack
            mov al,[rcx+rax]

            .if ( al != ModuleInfo.strict_masm_compat )

                mov ModuleInfo.strict_masm_compat,al
                xor eax,1
                AsmcKeywords(eax)
            .endif
            .endc
        .endif

        .endc .if ( [rbx].tokval != T_PUSH )
        .endc .if ( AsmcCount >= MAXSTACK )

        mov edx,AsmcCount
        inc AsmcCount
        mov al,ModuleInfo.strict_masm_compat
        lea rcx,AsmcStack
        mov [rcx+rdx],al
        inc i
        .if ( [rbx+asm_tok].token == T_OP_BRACKET || [rbx+asm_tok].token == T_COMMA )
            inc i
        .endif
        .endc .ifd EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR

        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if ( opndx.kind != EXPR_CONST )

            asmerr( 2026 )
            .endc
        .endif

        mov eax,opndx.uvalue
        .if ( eax > 1 )
            asmerr( 2064 )
            .endc
        .endif

        xor eax,1
        .if al != ModuleInfo.strict_masm_compat

            mov ModuleInfo.strict_masm_compat,al
            xor eax,1
            AsmcKeywords(eax)
        .endif

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

        ;
        ; .pragma warning(push)
        ;
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
        .endc .ifd EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR

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
                .if tstrchr(tstrcpy(&stdlib, rsi), '"')

                    mov byte ptr [rax],0
                .endif
            .endif

            .if ( [rbx+asm_tok].token == T_COMMA )

                add i,2
                add rbx,asm_tok*2

                mov rsi,[rbx].string_ptr
                tstrcpy(&dynlib, rsi)

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
                or  ecx,0xFFFFFF
                .if ( ecx == 'bil' || ecx == 'lld' )
                    mov byte ptr [rax],0
                .endif
            .endif
            .if ( tstrrchr(rdi, '.') )

                mov ecx,[rax+1]
                or  ecx,0xFFFFFF
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

                AddLineQueueX("includelib %s.lib", rdi)

            .else

                .new u[256]:char_t

                tstrupr( tstrcpy( &u, rsi ) )
                .while ( tstrchr( rax, '-' ) )
                    mov byte ptr [rax],'_'
                .endw

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

            ;
            ; .pragma comment(linker, "/..")
            ;
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
                QEnqueue( &ModuleInfo.LinkQueue, rdi )
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

        ; .pragma(init(<proc>, <priority>))
        ; .pragma(exit(<proc>, <priority>))

        mov edi,eax
        .if !ModuleInfo.dotname
            AddLineQueueX(" %r dotname", T_OPTION)
        .endif
        .if Options.output_format == OFORMAT_ELF

            inc i
            .if ( [rbx+asm_tok].token == T_COMMA )
                inc i
            .endif
            .endc .ifd EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR

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

        mov eax,2
        .if ( ModuleInfo.Ofssize >= USE32 )
            mov eax,8
        .endif
        AddLineQueueX( " %s %r %r(%d) 'CONST'", rsi, T_SEGMENT, T_ALIGN, eax )
        mov rdx,[rbx].string_ptr
        add rbx,asm_tok
        .if [rbx].token == T_COMMA
            add rbx,asm_tok
        .endif
        .if ModuleInfo.Ofssize == USE64
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
            mov ModuleInfo.fieldalign,al
            .endc
        .endif

        .endc .if [rbx].tokval != T_PUSH
        .endc .if PackCount >= MAXSTACK

        mov edx,PackCount
        inc PackCount
        mov al,ModuleInfo.fieldalign
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
        lea rdi,ModuleInfo.list

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
        lea rdi,ModuleInfo.cref

        .if [rbx].tokval == T_POP

            .gotosw(T_POP)
        .endif

      .case T_PUSH

        .endc .if [rbx].tokval != T_PUSH

        mov eax,[rcx]
        inc eax
        .endc .if eax >= MAXSTACK

        mov [rcx],eax
        mov cl,[rdi]
        mov [rdx+rax-1],cl

        inc i
        .if ( [rbx+asm_tok].token == T_COMMA )

            inc i
        .endif
        .endc .ifd EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR

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

        mov [rdi],al
        .if al && list_directive

            or ModuleInfo.line_flags,LOF_LISTED
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
        mov [rdi],al
        .if al && list_directive
            or ModuleInfo.line_flags,LOF_LISTED
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
        .if ModuleInfo.list
            LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
        .endif
        .if ModuleInfo.line_queue.head
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

