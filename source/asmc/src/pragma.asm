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
    WarnStack dd MAXSTACK dup(0)
    AsmcStack db MAXSTACK dup(0)

    .code

    assume ebx:token_t

PragmaDirective proc uses esi edi ebx i:int_t, tokenarray:token_t

  local rc:int_t, list_directive:int_t
  local opndx:expr
  local stdlib[256]:char_t
  local dynlib[256]:char_t
  local q:ptr qitem


    mov rc,NOT_ERROR
    mov list_directive,0

    inc i
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    .if ( [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA )
        inc i
        add ebx,16
    .endif

    mov esi,[ebx].string_ptr
    mov eax,[esi]
    or  eax,0x20202020
    inc i
    add ebx,16
    .if ( [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA )
        inc i
        add ebx,16
    .endif

    bswap   eax
    .switch eax

      .case "asmc"

        .if [ebx].tokval == T_POP

            add ebx,16
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif
            .endc .if !AsmcCount

            dec AsmcCount
            mov eax,AsmcCount
            mov al,AsmcStack[eax]
            .if al != ModuleInfo.strict_masm_compat
                mov ModuleInfo.strict_masm_compat,al
                xor eax,1
                AsmcKeywords(eax)
            .endif
            .endc
        .endif

        .endc .if ( [ebx].tokval != T_PUSH )
        .endc .if ( AsmcCount >= MAXSTACK )

        mov edx,AsmcCount
        inc AsmcCount
        mov al,ModuleInfo.strict_masm_compat
        mov AsmcStack[edx],al
        inc i
        .if ( [ebx+16].token == T_OP_BRACKET || [ebx+16].token == T_COMMA )

            inc i
        .endif
        .endc .if EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR

        mov ebx,i
        shl ebx,4
        add ebx,tokenarray
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

        add ebx,16
        .if [ebx].token == T_CL_BRACKET

            add ebx,16
        .endif
        .endc

      .case "warn"

        ;
        ; .pragma warning(pop)
        ;
        .if [ebx].tokval == T_POP

            add ebx,16
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif

            .endc .if !WarnCount

            .for ( WarnCount--,
                   eax = WarnCount,
                   edx = WarnStack[eax*4],
                   esi = &pragma_wtable,
                   ecx = 0 : ecx < wtable_count : ecx++, esi += sizeof(warning) )

                mov al,[edx+ecx]
                mov [esi].warning.state,al
            .endf

            free(edx)
            .endc

        .endif

        ;
        ; .pragma warning(push)
        ;
        .if [ebx].tokval == T_PUSH

            add ebx,16
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif
            mov edi,WarnCount
            inc edi
            .endc .if edi >= MAXSTACK
            mov WarnCount,edi
            .endc .if !malloc(wtable_count)
            .for ( WarnStack[edi*4-4] = eax,
                   esi = &pragma_wtable,
                   ecx = 0 : ecx < wtable_count : ecx++, esi += sizeof(warning) )

                mov dl,[esi].warning.state
                mov [eax+ecx],dl
            .endf
            .endc

        .endif

        ; .pragma warning(disable: <num>)

        mov esi,[ebx].string_ptr
        mov eax,[esi]
        or  eax,0x20202020

        .endc .if eax != 'asid'
        .endc .if [ebx+16].token != T_COLON

        add i,2
        .endc .if EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR

        mov ebx,i
        shl ebx,4
        add ebx,tokenarray
        .if opndx.kind != EXPR_CONST

            asmerr(2026)
            .endc
        .endif

        .for ( eax = opndx.uvalue,
               esi = &pragma_wtable,
               ecx = 0 : ecx < wtable_count : ecx++, esi += sizeof(warning) )

            .if ( [esi].warning.id == ax )

                mov [esi].warning.state,1
                .break
            .endif
        .endf

        add ebx,16
        .if [ebx].token == T_CL_BRACKET
            add ebx,16
        .endif
        .endc

      .case "comm"

        mov eax,[esi+4]
        or  eax,0x202020
        .endc .if eax != 'tne'
        .endc .if [ebx+16].token != T_COMMA

        mov esi,[ebx].string_ptr
        mov eax,[esi]
        or  eax,0x202020
        and eax,0xFFFFFF

        .if eax == 'bil'

            add i,2
            add ebx,32
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

            mov esi,[ebx].string_ptr
            strcpy(&stdlib, esi)

            .while ( [ebx+16].token == T_DOT )

                strcat(&stdlib, [ebx+16].string_ptr)
                strcat(&stdlib, [ebx+32].string_ptr)
                add i,2
                add ebx,32
            .endw

            .if ( byte ptr [esi] == '"' )

                inc esi
                .if strchr(strcpy(&stdlib, esi), '"')

                    mov byte ptr [eax],0
                .endif
            .endif

            .if ( [ebx+16].token == T_COMMA )

                add i,2
                add ebx,32

                mov esi,[ebx].string_ptr
                strcpy(&dynlib, esi)

                .if ( byte ptr [esi] == '"' )

                    inc esi
                    .if strchr(strcpy(&dynlib, esi), '"')

                        mov byte ptr [eax],0
                    .endif
                .endif
            .endif

            lea esi,dynlib
            lea edi,stdlib
            .if ( strrchr(esi, '.') )

                mov ecx,[eax+1]
                or  ecx,0xFFFFFF
                .if ( ecx == 'bil' || ecx == 'lld' )
                    mov byte ptr [eax],0
                .endif
            .endif
            .if ( strrchr(edi, '.') )

                mov ecx,[eax+1]
                or  ecx,0xFFFFFF
                .if ( ecx == 'bil' || ecx == 'lld' )
                    mov byte ptr [eax],0
                .endif
            .endif

            .if ( Options.output_format == OFORMAT_BIN )

                .if ( dynlib == 0 )
                    mov esi,edi
                .endif
                AddLineQueueX(" option dllimport:<%s>", esi)

            .elseif !( byte ptr [esi] )

                AddLineQueueX("includelib %s.lib", edi)

            .else

                .new u[256]:char_t

                tstrupr( strcpy( &u, esi ) )
                .while ( strchr( eax, '-' ) )
                    mov byte ptr [eax],'_'
                .endw

                AddLineQueueX( "ifdef _%s", &u )
                AddLineQueueX( "includelib %s.lib", esi )
                AddLineQueue(  "else" )
                AddLineQueueX( "includelib %s.lib", edi )
                AddLineQueue(  "endif" )
            .endif

        .elseif ( eax == 'nil' )

            mov eax,[esi+3]
            or  eax,0x202020
            and eax,0xFFFFFF
            .endc .if eax != 'rek'

            ;
            ; .pragma comment(linker, "/..")
            ;
            add ebx,32
            mov esi,[ebx].tokpos
            .endc .if byte ptr [esi] != '"'

            inc esi     ; skip first '"'
            lea edi,dynlib
            mov ecx,edi

            .if ( Parse_Pass == PASS_1 ) ;; do all work in pass 1

                .repeat
                    lodsb
                    .if al == '"' && byte ptr [esi] == '"'
                        lodsb
                        add ebx,16
                        .continue(0)
                    .endif
                    .if al == '\' && byte ptr [esi] == '"'
                        movsb
                        .continue(0)
                    .endif
                    .if al == '"'
                        xor eax,eax
                    .endif
                    stosb
                .until !al

                sub edi,ecx
                add edi,qitem
                mov edi,LclAlloc( edi )
                strcpy( &[edi].qitem.value, &dynlib )
                QEnqueue( &ModuleInfo.LinkQueue, edi )
            .else
                .while [ebx].token == T_STRING
                    add ebx,16
                .endw
            .endif
        .endif

        add ebx,16
        .if ( [ebx].token == T_CL_BRACKET )
            add ebx,16
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
        lea esi,@CStr(".CRT$XTA")
        .if edi == "init"
            lea esi,@CStr(".CRT$XIA")
        .endif

        mov eax,2
        mov cl,ModuleInfo.Ofssize
        shl eax,cl
        AddLineQueueX(" %s %r %r(%d) 'CONST'", esi, T_SEGMENT, T_ALIGN, eax)
        mov edx,[ebx].string_ptr
        add ebx,16
        .if [ebx].token == T_COMMA
            add ebx,16
        .endif
        .if ModuleInfo.Ofssize == USE64
            AddLineQueueX(" dd %r %s, %s", T_IMAGEREL, edx, [ebx].string_ptr)
        .else
            AddLineQueueX(" dd %s, %s", edx, [ebx].string_ptr)
        .endif
        AddLineQueueX(" %s %r", esi, T_ENDS)
        add ebx,16
        .if [ebx].token == T_CL_BRACKET
            add ebx,16
        .endif
        .endc

      .case "pack"

        ; .pragma(pack(push, <alignment>))
        ; .pragma(pack(pop))

        .if [ebx].tokval == T_POP

            add ebx,16
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif
            .endc .if !PackCount

            dec PackCount
            mov eax,PackCount
            mov al,PackStack[eax]
            mov ModuleInfo.fieldalign,al
            .endc
        .endif

        .endc .if [ebx].tokval != T_PUSH
        .endc .if PackCount >= MAXSTACK

        mov edx,PackCount
        inc PackCount
        mov al,ModuleInfo.fieldalign
        mov PackStack[edx],al
        add ebx,16
        .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
            add ebx,16
        .endif
        AddLineQueueX("OPTION FIELDALIGN: %s", [ebx].string_ptr)
        add ebx,16
        .if [ebx].token == T_CL_BRACKET
            add ebx,16
        .endif
        .endc

      .case "list"

        ; .pragma(list(push, 0|1))
        ; .pragma(list(pop))

        inc list_directive

        lea ecx,ListCount
        lea edx,ListStack
        lea edi,ModuleInfo.list

        .if [ebx].tokval == T_POP

            .gotosw(T_POP)
        .endif
        .gotosw(T_PUSH)

      .case "cref"

        ; .pragma(cref(push, 0|1))
        ; .pragma(cref(pop))

        inc list_directive

        lea ecx,CrefCount
        lea edx,CrefStack
        lea edi,ModuleInfo.cref

        .if [ebx].tokval == T_POP

            .gotosw(T_POP)
        .endif

      .case T_PUSH

        .endc .if [ebx].tokval != T_PUSH

        mov eax,[ecx]
        inc eax
        .endc .if eax >= MAXSTACK

        mov [ecx],eax
        mov cl,[edi]
        mov [edx+eax-1],cl

        inc i
        .if ( [ebx+16].token == T_COMMA )

            inc i
        .endif
        .endc .if EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR

        mov ebx,i
        shl ebx,4
        add ebx,tokenarray
        .if opndx.kind != EXPR_CONST

            asmerr(2026)
            .endc
        .endif

        mov eax,opndx.uvalue
        .if eax > 1

            asmerr(2084)
            .endc
        .endif

        mov [edi],al
        .if al && list_directive

            or ModuleInfo.line_flags,LOF_LISTED
        .endif
        add ebx,16
        .if [ebx].token == T_CL_BRACKET
            add ebx,16
        .endif
        .endc

      .case T_POP

        mov eax,[ecx]
        .endc .if !eax ; gives an error if nothing pushed
        dec eax
        mov [ecx],eax
        mov al,[edx+eax]
        mov [edi],al
        .if al && list_directive
            or ModuleInfo.line_flags,LOF_LISTED
        .endif
        add ebx,16
        .if [ebx].token == T_CL_BRACKET
            add ebx,16
        .endif
        .endc
    .endsw

    .if [ebx].token == T_CL_BRACKET
        add ebx,16
    .endif
    .if [ebx].token != T_FINAL
        mov rc,asmerr(2008, [ebx].tokpos)
    .endif

    .if !list_directive
        .if ModuleInfo.list
            LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
        .endif
        .if ModuleInfo.line_queue.head
            RunLineQueue()
        .endif
    .endif
    mov eax,rc
    ret

PragmaDirective endp

PragmaInit proc

    mov ListCount,0
    mov PackCount,0
    mov CrefCount,0
    ret

PragmaInit endp

PragmaCheckOpen proc

    .if ListCount || PackCount || CrefCount

        asmerr(1010, ".pragma-push-pop")
    .endif
    ret

PragmaCheckOpen endp

warning_disable proc id:int_t

    .for ( eax = id,
           edx = &pragma_wtable,
           ecx = 0 : ecx < wtable_count : ecx++, edx += sizeof(warning) )

        .if ( ax == [edx].warning.id )

            movzx eax,[edx].warning.state
            .return
        .endif
    .endf
    xor eax,eax
    ret

warning_disable endp

    END

