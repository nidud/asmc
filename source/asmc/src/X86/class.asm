include stdio.inc
include string.inc
include asmc.inc
include token.inc
include hll.inc

externdef CurrStruct:LPDSYM
;
; item for .CLASS, .ENDS, and .COMDEF
;
com_item    STRUC
cmd         dd ?
class       LPSTR ?
langtype    dd ?
com_item    ENDS
LPCLASS     typedef ptr com_item

    .code

    assume ebx:ptr asmtok

ProcType proc uses esi edi ebx i:int_t, tokenarray:ptr asmtok, buffer:string_t

  local retval          : int_t,
        P$[16]          : char_t,
        T$[16]          : char_t,
        name            : string_t,
        IsCom           : uchar_t,
        language[32]    : char_t,
        dir             : ptr dsym,
        size            : int_t

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    mov edi,buffer
    mov eax,[ebx-16].string_ptr
    mov name,eax
    mov retval,NOT_ERROR

    inc ModuleInfo.class_label
    sprintf(&T$, "T$%04X", ModuleInfo.class_label )
    sprintf(&P$, "P$%04X", ModuleInfo.class_label )

    mov IsCom,0
    mov eax,CurrStruct
    mov esi,[eax].asym.name
    .if ( strlen(esi) > 4 )
        mov eax,[esi+eax-4]
    .endif
    mov esi,ModuleInfo.ComStack

    .if ( eax == "lbtV" )

        inc IsCom

    .elseif esi

        .if ( Token_Count > 2 && [ebx+16].tokval == T_LOCAL )

            add ebx,16
        .else
            AddLineQueueX( "%s ends", [esi].com_item.class )
            AddLineQueueX( "%sVtbl struct", [esi].com_item.class )
            inc IsCom
        .endif
    .endif

    .repeat

        strcpy(edi, &T$)
        strcat(edi, " typedef proto")

        .if ( esi && [esi].com_item.cmd == T_DOT_COMDEF )

            .if ( ModuleInfo.Ofssize == USE32 && ModuleInfo.langtype != LANG_STDCALL )

                strcat(edi, " stdcall")
            .endif
        .endif

        add ebx,16
        xor esi,esi

        .if ( [ebx].token != T_FINAL )

            .if ( IsCom )

                .if ( [ebx].tokval >= T_CCALL && [ebx].tokval <= T_VECTORCALL )

                    inc esi
                .endif

                .if ( [ebx+16].token == T_FINAL || esi || \
                    ( [ebx].token != T_COLON && [ebx+16].token != T_COLON ) )

                    strcat(edi, " ")
                    strcat(edi, [ebx].string_ptr)
                    add ebx,16

                .elseif !esi && ModuleInfo.ComStack

                    mov ecx,ModuleInfo.ComStack
                    mov edx,[ecx].com_item.langtype
                    .if edx

                        GetResWName(edx, &language)
                        strcat(edi, " ")
                        strcat(edi, &language)
                    .endif
                .endif
                xor esi,esi
            .endif

            .for ( eax = ebx : [eax].asmtok.token != T_FINAL : eax += 16 )

                .if ( [eax].asmtok.token == T_COLON )

                    inc esi
                    .break
                .endif
            .endf

        .elseif IsCom && ModuleInfo.ComStack

            mov ecx,ModuleInfo.ComStack
            mov edx,[ecx].com_item.langtype
            .if edx

                GetResWName(edx, &language)
                strcat(edi, " ")
                strcat(edi, &language)
            .endif
        .endif

        .if IsCom

            strcat(edi, " :ptr")
            mov eax,ModuleInfo.ComStack
            .if eax

                .if ( [eax].com_item.cmd == T_DOT_CLASS )

                    strcat(edi, " ")
                    mov eax,ModuleInfo.ComStack
                    strcat(edi, [eax].com_item.class)
                .endif
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
        AddLineQueueX( "%s typedef ptr %s", &P$, &T$ )
        AddLineQueueX( "%s %s ?", name, &P$ )

        .if ( ModuleInfo.list )
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        .if ( ModuleInfo.line_queue.head )
            RunLineQueue()
        .endif
        mov eax,retval
    .until 1
    ret

ProcType endp

ClassDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asmtok

  local rc:int_t,
        args:int_t,
        cmd:uint_t,
        LPClass[64]:char_t

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,LPClass

    mov edx,i
    shl edx,4
    mov eax,[ebx+edx].tokval
    mov cmd,eax
    inc i

    .repeat

        .switch eax
        .case T_DOT_ENDS
            mov eax,CurrStruct
            .if !ModuleInfo.ComStack
                .if eax
                    mov rc,asmerr(1011)
                .endif
                .break
            .endif
            mov ModuleInfo.ComStack,0
            mov edx,[eax].asym.name
            AddLineQueueX( "%s ends", edx )
            .endc

        .case T_DOT_COMDEF
        .case T_DOT_CLASS
            .if ( ModuleInfo.ComStack )
                mov rc,asmerr(1011)
                .break
            .endif

            lea ebx,[ebx+edx+16]

            mov ModuleInfo.ComStack,LclAlloc( sizeof( com_item ) )
            mov ecx,cmd
            mov [eax].com_item.cmd,ecx
            mov [eax].com_item.langtype,0

            mov esi,[ebx].string_ptr
            .if LclAlloc( &[strlen(esi) + 1] )

                mov ecx,ModuleInfo.ComStack
                mov [ecx].com_item.class,eax
                strcpy(eax, esi)
            .endif
            _strupr( strcat( strcpy( edi, "LP" ), esi ) )

            .if ( [ebx+16].token == T_ID )

                mov eax,[ebx+16].string_ptr
                mov eax,[eax]
                or  al,0x20

                .if ( ax == 'c' )

                    mov [ebx+16].token,T_RES_ID
                    mov [ebx+16].tokval,T_CCALL
                    mov [ebx+16].bytval,1
                .endif
            .endif

            lea eax,[ebx+16]
            mov edx,[ebx+16].tokval
            .if ( [ebx+16].token != T_FINAL && edx >= T_CCALL && edx <= T_VECTORCALL )

                mov ecx,ModuleInfo.ComStack
                mov [ecx].com_item.langtype,edx
                add eax,16
            .endif
            mov args,eax

            AddLineQueueX( "%sVtbl typedef ptr %sVtbl", edi, esi )

            .if ( cmd == T_DOT_CLASS )

                AddLineQueueX( "%s typedef ptr %s", edi, esi )

                .for ( edx = 0,
                       eax = args : !edx && [eax].asmtok.token != T_FINAL : eax += 16 )

                    .if ( [eax].asmtok.token == T_COLON )

                        inc edx
                    .endif
                .endf

                mov ebx,args
                mov ecx,ModuleInfo.ComStack

                .if ( [ecx].com_item.langtype )
                    .if edx
                        AddLineQueueX( "%s::%s proto %s %s", esi, esi, [ebx-16].string_ptr, [ebx].tokpos )
                    .else
                        AddLineQueueX( "%s::%s proto %s", esi, esi, [ebx-16].string_ptr )
                    .endif
                .else
                    .if edx
                        AddLineQueueX( "%s::%s proto %s", esi, esi, [ebx].tokpos )
                    .else
                        AddLineQueueX( "%s::%s proto", esi, esi )
                    .endif
                .endif

                mov eax,8
                .if ( ModuleInfo.Ofssize == USE32 )
                    mov eax,4
                .endif
                mov cl,ModuleInfo.fieldalign
                mov edx,1
                shl edx,cl
                .if ( edx < eax )
                    AddLineQueueX( "%s struct %d", esi, eax )
                .else
                    AddLineQueueX( "%s struct", esi )
                .endif
            .else
                AddLineQueueX( "%s struct", esi )
            .endif
            AddLineQueueX( "lpVtbl %sVtbl ?", &LPClass )
            .endc
        .endsw

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

ClassInit proc

    mov ModuleInfo.class_label,0 ; init class label counter
    ret

ClassInit endp

ClassCheckOpen proc

    .if ModuleInfo.ComStack

        asmerr( 1010, ".comdef-.classdef-.ends" )
    .endif
    ret

ClassCheckOpen endp

    END
