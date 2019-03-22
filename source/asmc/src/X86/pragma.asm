; PRAGMADIRECTIVE.ASM--
; Copyright (C) 2018 Asmc Developers
;
; Change history:
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
include hll.inc
include token.inc

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

    PackStack db MAXSTACK dup(0)
    ListStack db MAXSTACK dup(0)
    CrefStack db MAXSTACK dup(0)
    WarnStack dd MAXSTACK dup(0)

    .code

    assume ebx:ptr asmtok

PragmaDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asmtok

  local rc:int_t, list_directive:int_t
  local opndx:expr
  local stdlib[256]:char_t
  local dynlib[256]:char_t

    mov rc,NOT_ERROR
    mov list_directive,0

    inc i
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
        inc i
        add ebx,16
    .endif

    .repeat

        mov esi,[ebx].string_ptr
        mov eax,[esi]
        or  eax,0x20202020
        inc i
        add ebx,16
        .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
            inc i
            add ebx,16
        .endif

        bswap   eax
        .switch eax

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
            .endc .if EvalOperand(&i, tokenarray, ModuleInfo.token_count,
                        &opndx, EXPF_NOUNDEF ) == ERROR

            mov ebx,i
            shl ebx,4
            add ebx,tokenarray
            .if opndx.kind != EXPR_CONST
                asmerr( 2026 )
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

            mov esi,[ebx].string_ptr
            mov eax,[esi]
            or  eax,0x202020
            and eax,0xFFFFFF
            .endc .if eax != 'bil'
            .endc .if [ebx+16].token != T_COMMA

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
            .if ( strchr(esi, '.') )
                mov byte ptr [eax],0
            .endif
            .if ( strchr(edi, '.') )
                mov byte ptr [eax],0
            .endif

            .if ( Options.output_format == OFORMAT_BIN )

                .if !( dynlib )
                    mov esi,edi
                .endif

                AddLineQueueX( " option dllimport:<%s>", esi )

            .elseif !( byte ptr [esi] )

                AddLineQueueX( "includelib %s.lib", edi )

            .else

                AddLineQueueX( "ifdef _%s", _strupr( esi ) )
                AddLineQueueX( "includelib %s.lib", _strlwr(esi) )
                AddLineQueue(  "else" )
                AddLineQueueX( "includelib %s.lib", edi )
                AddLineQueue(  "endif" )
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

            lea edi,@CStr("dw")
            .if ModuleInfo.Ofssize == USE32
                lea edi,@CStr("dd")
            .endif
            .if ModuleInfo.Ofssize == USE64
                lea edi,@CStr("dq")
            .endif
            lea edx,@CStr("EXIT")
            .if eax == "init"
                lea edx,@CStr("INIT")
            .endif
            push edx
            AddLineQueueX( "_%s segment PARA FLAT PUBLIC '%s'", edx, edx )
            AddLineQueueX( " %s %s", edi, [ebx].string_ptr )
            add ebx,16
            .if [ebx].token == T_COMMA
                add ebx,16
            .endif
            AddLineQueueX( " %s %s", edi, [ebx].string_ptr )
            pop edx
            AddLineQueueX( "_%s ends", edx )
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
            AddLineQueueX( "OPTION FIELDALIGN: %s", [ebx].string_ptr )
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
            .if [ebx+16].token == T_COMMA

                inc i
            .endif
            .endc .if EvalOperand(&i, tokenarray, ModuleInfo.token_count,
                        &opndx, EXPF_NOUNDEF ) == ERROR

            mov ebx,i
            shl ebx,4
            add ebx,tokenarray
            .if opndx.kind != EXPR_CONST

                asmerr( 2026 )
                .endc
            .endif

            mov eax,opndx.uvalue
            .if eax > 1

                asmerr( 2084 )
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
            mov rc,asmerr( 2008, [ebx].tokpos )
        .endif

        .if !list_directive
            .if ModuleInfo.list
                LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
            .endif
            .if ModuleInfo.line_queue.head
                RunLineQueue()
            .endif
        .endif
        mov eax,rc
    .until 1
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

        asmerr( 1010, ".pragma-push-pop" )
    .endif
    ret

PragmaCheckOpen endp

warning_disable proc id:int_t

    .repeat

        .for ( eax = id,
               edx = &pragma_wtable,
               ecx = 0 : ecx < wtable_count : ecx++, edx += sizeof(warning) )

            .if ( ax == [edx].warning.id )

                movzx eax,[edx].warning.state
                .break(1)
            .endif
        .endf

        xor eax,eax
    .until 1
    ret

warning_disable endp

    END

