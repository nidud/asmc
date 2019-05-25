include string.inc
include malloc.inc
include asmc.inc
include token.inc
include hll.inc

conditional_assembly_prepare proto :dword

MAXSAVESTACK equ 124

    .data

    externdef CurrIfState:DWORD

    assert_stack dw MAXSAVESTACK dup(0)
    assert_stid  dd 0

    .code

    assume ebx: ptr asmtok
    assume esi: ptr hll_item

AssertDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asmtok

local rc:SINT,cmd:UINT,
      buff[16]:SBYTE,
      buffer[MAX_LINE_LEN]:SBYTE,
      cmdstr[MAX_LINE_LEN]:SBYTE

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,buffer
    mov eax,i
    shl eax,4
    mov eax,[ebx+eax].tokval
    mov cmd,eax
    inc i
    mov esi,ModuleInfo.HllFree
    .if !esi

        mov esi,LclAlloc(sizeof(hll_item))
    .endif
    ExpandCStrings(tokenarray)
    xor eax,eax
    mov [esi].labels[LEXIT*4],eax
    mov [esi].flags,eax
    mov eax,cmd

    .switch eax

      .case T_DOT_ASSERT

        mov edx,i
        shl edx,4
        mov al,[ebx+edx].asmtok.token
        .if al == T_COLON

            add i,2
            mov edi,[ebx+edx+16].asmtok.string_ptr
            mov al,[ebx+edx+16].asmtok.token

            .if al == T_ID

                .if SymFind(edi)

                    free(ModuleInfo.assert_proc)
                    _strdup(edi)
                    mov ModuleInfo.assert_proc,eax
                    .endc
                .endif
            .endif

            .if !_stricmp(edi, "CODE")

                .if !(ModuleInfo.xflag & _XF_ASSERT)

                    conditional_assembly_prepare(T_IF)
                    mov CurrIfState,BLOCK_DONE
                .endif
                .endc
            .endif

            .if !_stricmp(edi, "ENDS")
                ;
                ; Converted to ENDIF in Tokenize()
                ;
                .endc
            .endif

            .if !_stricmp(edi, "PUSH")

                mov al,ModuleInfo.aflag
                mov ah,ModuleInfo.xflag
                mov ecx,assert_stid
                .if ecx < MAXSAVESTACK

                    mov assert_stack[ecx*2],ax
                    inc assert_stid
                .endif
                .endc
            .endif

            .if !_stricmp(edi, "POP")

                mov ecx,assert_stid
                mov ax,assert_stack[ecx*2]
                mov ModuleInfo.aflag,al
                mov ModuleInfo.xflag,ah
                .if ecx

                    dec assert_stid
                .endif
                .endc
            .endif

            .if !_stricmp(edi, "ON")

                or  ModuleInfo.xflag,_XF_ASSERT
                .endc
            .endif
            .if !_stricmp(edi, "OFF")

                and ModuleInfo.xflag,NOT _XF_ASSERT
                .endc
            .endif
            .if !_stricmp(edi, "PUSHF")

                or  ModuleInfo.xflag,_XF_PUSHF
                .endc
            .endif
            .if !_stricmp(edi, "POPF")

                and ModuleInfo.xflag,NOT _XF_PUSHF
                .endc
            .endif

            asmerr(2008, edi)
            .endc

        .elseif al == T_FINAL || !(ModuleInfo.xflag & _XF_ASSERT)

            ;.if !Options.quiet
            ;.endif
            .endc
        .endif

        mov edx,i
        shl edx,4
        strcpy( &cmdstr, [ebx+edx].tokpos )

        .if ModuleInfo.xflag & _XF_PUSHF

            .if ModuleInfo.Ofssize == USE64

                AddLineQueueX("%r", T_PUSHFQ)
                AddLineQueueX("%r %r,28h", T_SUB, T_RSP)
            .else
                AddLineQueueX("%r", T_PUSHFD)
            .endif
        .endif

        mov [esi].cmd,HLL_IF
        mov [esi].labels[LSTART*4],0
        mov [esi].labels[LTEST*4],GetHllLabel()
        lea ecx,buff
        GetLabelStr( GetHllLabel(), ecx )
        mov rc,EvaluateHllExpression(esi, &i, ebx, LTEST, 0, edi)
        .endc .if eax != NOT_ERROR

        QueueTestLines(edi)

        .if ModuleInfo.xflag & _XF_PUSHF

            .if ModuleInfo.Ofssize == USE64

                AddLineQueueX("%r %r,28h", T_ADD, T_RSP)
                AddLineQueueX("%r", T_POPFQ)
            .else
                AddLineQueueX("%r", T_POPFD)
            .endif
        .endif

        AddLineQueueX("jmp %s", &buff)
        AddLineQueueX("%s%s", GetLabelStr([esi].labels[LTEST*4], edi), LABELQUAL)

        .if ModuleInfo.xflag & _XF_PUSHF

            .if ModuleInfo.Ofssize == USE64

                AddLineQueueX("%r %r,28h", T_ADD, T_RSP)
                AddLineQueueX("%r", T_POPFQ)
            .else
                AddLineQueueX("%r", T_POPFD)
            .endif
        .endif

        .endc .if BYTE PTR [edi] == NULLC
        mov eax,ModuleInfo.assert_proc
        .if !eax

            lea eax,@CStr("assert_exit")
            mov ModuleInfo.assert_proc,eax
        .endif

        AddLineQueueX("%s()", eax)
        AddLineQueue ("db @CatStr(!\",\%\@FileName,<(>,\%@Line,<): >,!\")")

        lea ebx,cmdstr
        .while strchr(ebx, '"')

            mov byte ptr [eax],0
            xchg ebx,eax
            inc ebx
            .if byte ptr [eax]

                AddLineQueueX("db \"%s\",22h", eax)
            .else
                AddLineQueue("db 22h")
            .endif
        .endw
        .if byte ptr [ebx]

            AddLineQueueX( "db \"%s\"", ebx )
        .endif
        AddLineQueue("db 0")
        AddLineQueueX("%s%s", &buff, LABELQUAL)
        .endc

      .case T_DOT_ASSERTD
        mov [esi].flags,HLLF_IFD
        .gotosw(T_DOT_ASSERT)
      .case T_DOT_ASSERTW
        mov [esi].flags,HLLF_IFW
        .gotosw(T_DOT_ASSERT)
      .case T_DOT_ASSERTB
        mov [esi].flags,HLLF_IFB
        .gotosw(T_DOT_ASSERT)
    .endsw

    .if ModuleInfo.list

        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif

    .if ModuleInfo.line_queue.head

        RunLineQueue()
    .endif

    mov eax,rc
    ret

AssertDirective endp

    END
