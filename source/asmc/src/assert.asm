; ASSERT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include memalloc.inc
include condasm.inc
include listing.inc
include hll.inc
include parser.inc
include segment.inc
include lqueue.inc

MAXSAVESTACK equ 124

    .data

    assert_stack db MAXSAVESTACK dup(0)
    assert_stid  dd 0

    .code

    assume rbx:token_t, rsi: ptr hll_item

AssertDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new buffer[MAX_LINE_LEN]:char_t
   .new cmdstr[MAX_LINE_LEN]:char_t
   .new buff[16]:char_t
   .new rc:int_t
   .new cmd:uint_t

    mov rc,NOT_ERROR
    ldr rbx,tokenarray
    lea rdi,buffer
    imul eax,i,asm_tok
    mov eax,[rbx+rax].tokval
    mov cmd,eax
    inc i

    mov rsi,MODULE.HllFree
    .if ( !rsi )
        mov rsi,LclAlloc( hll_item )
    .endif
    ExpandCStrings( tokenarray )
    xor eax,eax
    mov [rsi].labels[LEXIT*4],eax
    mov [rsi].flags,eax
    mov eax,cmd

    .switch eax

    .case T_DOT_ASSERT

        imul edx,i,asm_tok
        mov al,[rbx+rdx].asm_tok.token

        .if ( al == T_COLON )

            add i,2
            mov rdi,[rbx+rdx+asm_tok].asm_tok.string_ptr
            mov al,[rbx+rdx+asm_tok].asm_tok.token

            .if ( al == T_ID )

                .if SymFind(rdi)

                    MemFree( MODULE.assert_proc )
                    mov MODULE.assert_proc,MemDup( rdi )
                   .endc
                .endif
            .endif

            .ifd !tstricmp( rdi, "CODE" )

                .if !( MODULE.assert )

                    CondPrepare( T_IF )
                    mov CurrIfState,BLOCK_DONE
                .endif
                .endc
            .endif

            .ifd !tstricmp( rdi, "ENDS" )
                ;
                ; Converted to ENDIF in Tokenize()
                ;
                .endc
            .endif

            .ifd !tstricmp( rdi, "PUSH" )

                mov eax,MODULE.assert
                mov ecx,MODULE.assert_pushf
                shl ecx,1
                or  eax,ecx
                mov ecx,assert_stid
                .if ( ecx < MAXSAVESTACK )

                    lea rdx,assert_stack
                    mov [rdx+rcx],al
                    inc assert_stid
                .endif
                .endc
            .endif

            .ifd !tstricmp( rdi, "POP" )

                mov ecx,assert_stid
                lea rdx,assert_stack
                mov al,[rdx+rcx]
                .if ( al & 1 )
                    mov MODULE.assert,1
                .endif
                .if ( al & 2 )
                    mov MODULE.assert_pushf,1
                .endif
                .if ecx
                    dec assert_stid
                .endif
                .endc
            .endif

            .ifd !tstricmp( rdi, "ON" )
                mov MODULE.assert,1
               .endc
            .endif
            .ifd !tstricmp( rdi, "OFF" )
                mov MODULE.assert,0
               .endc
            .endif
            .ifd !tstricmp( rdi, "PUSHF" )

                mov MODULE.assert_pushf,1
               .endc
            .endif
            .ifd !tstricmp( rdi, "POPF" )

                mov MODULE.assert_pushf,0
               .endc
            .endif

            asmerr( 2008, rdi )
           .endc

        .elseif ( al == T_FINAL || !( MODULE.assert ) )

            ;.if !Options.quiet
            ;.endif
            .endc
        .endif

        imul edx,i,asm_tok
        tstrcpy( &cmdstr, [rbx+rdx].tokpos )

        .if ( MODULE.assert_pushf )

            .if ( MODULE.Ofssize == USE64 )

                AddLineQueue(
                    " pushfq\n"
                    " sub rsp,28h" )
            .else
                AddLineQueue( " pushfd" )
            .endif
        .endif

        mov [rsi].cmd,HLL_IF
        mov [rsi].labels[LSTART*4],0
        mov [rsi].labels[LTEST*4],GetHllLabel()
        lea rcx,buff
        GetLabelStr( GetHllLabel(), rcx )
        mov rc,EvaluateHllExpression( rsi, &i, rbx, LTEST, 0, rdi )
        .endc .if ( eax != NOT_ERROR )

        QueueTestLines( rdi )

        .if ( MODULE.assert_pushf )

            .if ( MODULE.Ofssize == USE64 )

                AddLineQueue(
                    " add rsp,28h\n"
                    " popfq" )
            .else
                AddLineQueue( " popfd" )
            .endif
        .endif
        AddLineQueueX(
            "jmp %s\n"
            "%s%s", &buff, GetLabelStr( [rsi].labels[LTEST*4], rdi ), LABELQUAL )

        .if ( MODULE.assert_pushf )

            .if ( MODULE.Ofssize == USE64 )

                AddLineQueue(
                    " add rsp,28h\n"
                    " popfq" )
            .else
                AddLineQueue( " popfd" )
            .endif
        .endif

        .endc .if BYTE PTR [rdi] == NULLC
        mov rax,MODULE.assert_proc
        .if ( !rax )

            lea rax,@CStr( "assert_exit" )
            mov MODULE.assert_proc,rax
        .endif

        AddLineQueueX( "%s()", rax )
        AddLineQueue ( "db @CatStr(!\",\%\@FileName,<(>,\%@Line,<): >,!\")" )

        lea rbx,cmdstr
        .while tstrchr( rbx, '"' )

            mov byte ptr [rax],0
            xchg rbx,rax
            inc rbx
            .if byte ptr [rax]

                AddLineQueueX( "db \"%s\",22h", rax )
            .else
                AddLineQueue( "db 22h" )
            .endif
        .endw
        .if byte ptr [rbx]
            AddLineQueueX( "db \"%s\"", rbx )
        .endif
        AddLineQueueX(
            "db 0\n"
            "%s%s", &buff, LABELQUAL )
        .endc
    .case T_DOT_ASSERTD
        mov [rsi].SizeDD,1
       .gotosw(T_DOT_ASSERT)
    .case T_DOT_ASSERTW
        mov [rsi].SizeDW,1
       .gotosw(T_DOT_ASSERT)
    .case T_DOT_ASSERTB
        mov [rsi].SizeDB,1
       .gotosw(T_DOT_ASSERT)
    .endsw

    .if ( MODULE.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( MODULE.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

AssertDirective endp

    END
