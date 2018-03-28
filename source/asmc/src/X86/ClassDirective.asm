include stdio.inc
include string.inc
include asmc.inc
include token.inc
include hll.inc

externdef CurrStruct:LPDSYM

    .data
    CurrClass LPSTR 0

    .code

    assume ebx:ptr asm_tok

AddVirtualTable proc private

    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    AddLineQueueX( "%s ends", CurrClass )
    RunLineQueue()
    mov eax,4
    .if ModuleInfo.Ofssize == USE64
        add eax,4
    .endif
    AddLineQueueX( "%sVtbl struct %d", CurrClass, eax )
;    AddLineQueue ( "Release proc" )
    ret

AddVirtualTable endp

ProcType proc uses esi edi ebx i:SINT, tokenarray:ptr asm_tok, buffer:LPSTR

  local rc:SINT, l_p[16]:SBYTE, l_t[16]:SBYTE, id:LPSTR, IsCom:BYTE

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    mov edi,buffer
    mov eax,[ebx-16].string_ptr
    mov id,eax
    mov rc,NOT_ERROR

    inc ModuleInfo.class_label
    sprintf(&l_t, "T$%04X", ModuleInfo.class_label )
    sprintf(&l_p, "P$%04X", ModuleInfo.class_label )

    mov IsCom,0
    mov eax,CurrStruct
    mov esi,[eax].asym._name
    mov eax,[esi+strlen(esi)-4]
    .if eax == "lbtV"
        inc IsCom
    .elseif CurrClass
        .if Token_Count > 2 && [ebx+16].tokval == T_LOCAL
            add ebx,16
        .else
            AddVirtualTable()
            inc IsCom
        .endif
    .endif

    .repeat

        strcpy(edi, &l_t)
        strcat(eax, " typedef proto")
        add ebx,16
        xor esi,esi

        .if [ebx].token != T_FINAL

            .if IsCom

                .if ( [ebx+16].token == T_FINAL || \
                    ( [ebx].token != T_COLON && [ebx+16].token != T_COLON ) )

                    strcat(edi, " ")
                    strcat(edi, [ebx].string_ptr)
                    add ebx,16
                .endif
            .endif
            .for eax = ebx : !esi && [eax].asm_tok.token != T_FINAL : eax += 16
                .if [eax].asm_tok.token == T_COLON
                    inc esi
                .endif
            .endf
        .endif

        .if IsCom
            strcat(edi, " :ptr")
            .if CurrClass
                strcat(edi, " ")
                strcat(edi, CurrClass)
            .endif
            .if esi

                strcat(edi, ",")
            .endif
        .endif

        .if esi

            strcat(edi, " ")
            strcat(edi, [ebx].tokpos)
        .endif

        AddLineQueue( edi )
        AddLineQueueX( "%s typedef ptr %s", &l_p, &l_t )
        AddLineQueueX( "%s %s ?", id, &l_p )
        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
            ;and ModuleInfo.line_flags,NOT LOF_LISTED
        .endif
        .if ModuleInfo.line_queue.head
            RunLineQueue()
        .endif
        mov eax,rc
    .until 1
    ret

ProcType endp

ClassDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asm_tok

  local rc:SINT, cmd:UINT, buffer[MAX_LINE_LEN]:SBYTE

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,buffer

    mov edx,i
    shl edx,4
    mov eax,[ebx+edx].tokval
    mov cmd,eax
    inc i

    .repeat

        .if eax == T_DOT_ENDS

            mov esi,CurrClass
            .if !esi

                mov rc,asmerr(1011)
                .break
            .endif
            mov eax,CurrStruct
            mov esi,[eax].asym._name
            AddLineQueueX( "%s ends", esi )
            mov CurrClass,0
        .else

            .if CurrClass

                mov rc,asmerr(1011)
                .break
            .endif

            lea ebx,[ebx+edx+16]
            mov esi,[ebx].string_ptr

            .if LclAlloc( &[strlen(esi) + 1] )

                mov CurrClass,eax
                strcpy(eax, esi)
            .endif

            _strupr( strcat( strcpy( edi, "LP" ), esi ) )
            AddLineQueueX( "%s typedef ptr %s", edi, esi )
            AddLineQueueX( "%sVtbl typedef ptr %sVtbl", edi, esi )
            .for edx=0, eax=ebx : !edx && [eax].asm_tok.token != T_FINAL : eax += 16
                .if [eax].asm_tok.token == T_COLON
                    inc edx
                .endif
            .endf
            .if edx
                AddLineQueueX( "%s::%s proto :ptr %s, %s", esi, esi, esi, [ebx+16].tokpos )
            .else
                AddLineQueueX( "%s::%s proto :ptr %s", esi, esi, esi )
            .endif
            mov eax,4
            .if ModuleInfo.Ofssize == USE64
                add eax,4
            .endif
            AddLineQueueX( "%s struct %d", esi, eax )
            AddLineQueueX( "lpVtbl %sVtbl ?", edi )

        .endif

        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        .if ModuleInfo.line_queue.head
            RunLineQueue()
        .endif
        mov eax,rc
    .until 1
    ret

ClassDirective endp

    END

