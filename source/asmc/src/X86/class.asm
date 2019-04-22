include stdio.inc
include string.inc
include asmc.inc
include token.inc
include hll.inc

externdef CurrStruct:LPDSYM
;
; item for .CLASSDEF, .ENDS, and .COMDEF
;
com_item    STRUC
cmd         dd ?
class       LPSTR ?
langtype    dd ?
com_item    ENDS
LPCLASS     typedef ptr com_item

    .code

    assume ebx:ptr asmtok

AddVirtualTable proc private uses esi

  local l_p[16]:SBYTE, l_t[16]:SBYTE

    mov esi,ModuleInfo.ComStack
    AddLineQueueX( "%s ends", [esi].com_item.class )

    .if [esi].com_item.cmd == T_DOT_CLASSDEF

        mov eax,4
        .if ModuleInfo.Ofssize == USE64

            add eax,4
        .endif
        AddLineQueueX( "%sVtbl struct %d", [esi].com_item.class, eax )

        inc ModuleInfo.class_label
        sprintf( &l_t, "T$%04X", ModuleInfo.class_label )
        sprintf( &l_p, "P$%04X", ModuleInfo.class_label )

        .if ( [esi].com_item.langtype )
            AddLineQueueX( "%s typedef proto %r :ptr %s", &l_t, [esi].com_item.langtype, [esi].com_item.class )
        .else
            AddLineQueueX( "%s typedef proto :ptr %s", &l_t, [esi].com_item.class )
        .endif
        AddLineQueueX( "%s typedef ptr %s", &l_p, &l_t )
        AddLineQueueX( "Release %s ?", &l_p )
    .else
        AddLineQueueX( "%sVtbl struct", [esi].com_item.class )
    .endif
    ret

AddVirtualTable endp

ProcType proc uses esi edi ebx i:SINT, tokenarray:ptr asmtok, buffer:LPSTR

  local rc:SINT, l_p[16]:SBYTE, l_t[16]:SBYTE, id:LPSTR, IsCom:BYTE
  local language[32]:SBYTE

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
    mov esi,[eax].asym.name
    .if strlen(esi) > 4
        mov eax,[esi+eax-4]
    .else
        xor eax,eax
    .endif
    mov esi,ModuleInfo.ComStack

    .if eax == "lbtV"

        inc IsCom

    .elseif esi

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
        .if esi && [esi].com_item.cmd == T_DOT_COMDEF

            strcat(eax, " WINAPI")
        .endif

        add ebx,16
        xor esi,esi

        .if [ebx].token != T_FINAL

            .if IsCom

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

                .if [eax].asmtok.token == T_COLON

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

                .if [eax].com_item.cmd == T_DOT_CLASSDEF

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
        AddLineQueueX( "%s typedef ptr %s", &l_p, &l_t )
        AddLineQueueX( "%s %s ?", id, &l_p )

        .if ModuleInfo.list

            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        .if ModuleInfo.line_queue.head

            RunLineQueue()
        .endif
        mov eax,rc
    .until 1
    ret

ProcType endp

ClassDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asmtok

  local rc:SINT, args:SINT, cmd:UINT, buffer[MAX_LINE_LEN]:SBYTE

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,buffer

    mov edx,i
    shl edx,4
    mov eax,[ebx+edx].tokval
    mov cmd,eax
    inc i

    .repeat

        .switch eax
        .case T_DOT_ENDS

            mov esi,ModuleInfo.ComStack
            .if !esi

                mov rc,asmerr(1011)
                .break
            .endif

            mov esi,[esi].com_item.class
            mov eax,CurrStruct
            mov edi,[eax].asym.name
            .if strlen(edi) > 4
                mov eax,[edi+eax-4]
            .else
                xor eax,eax
            .endif
            .if eax != "lbtV"

                AddVirtualTable()
                AddLineQueueX( "%sVtbl ends", esi )
            .else
                AddLineQueueX( "%s ends", edi )
            .endif
            mov ModuleInfo.ComStack,0
            .endc

        .case T_DOT_COMDEF
        .case T_DOT_CLASSDEF

            .if ModuleInfo.ComStack

                mov rc,asmerr(1011)
                .break
            .endif

            mov ModuleInfo.ComStack,LclAlloc( sizeof( com_item ) )
            mov ecx,cmd
            mov [eax].com_item.cmd,ecx
            mov [eax].com_item.langtype,0

            lea ebx,[ebx+edx+16]
            mov esi,[ebx].string_ptr
            .if LclAlloc( &[strlen(esi) + 1] )

                mov ecx,ModuleInfo.ComStack
                mov [ecx].com_item.class,eax
                strcpy(eax, esi)
            .endif

            strcat( strcpy( edi, "LP" ), esi )
            .if ( cmd == T_DOT_CLASSDEF )

                _strupr( eax )
            .endif

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
            .if ( [ebx+16].token != T_FINAL && [ebx+16].tokval >= T_CCALL && [ebx+16].tokval <= T_VECTORCALL )

                mov edx,[ebx+16].tokval
                mov ecx,ModuleInfo.ComStack
                mov [ecx].com_item.langtype,edx
                add eax,16
            .endif
            mov args,eax

            .if ( cmd == T_DOT_CLASSDEF )

                AddLineQueueX( "%s typedef ptr %s", edi, esi )
                AddLineQueueX( "%sVtbl typedef ptr %sVtbl", edi, esi )

                .for edx=0, eax=args : !edx && [eax].asmtok.token != T_FINAL : eax += 16

                    .if [eax].asmtok.token == T_COLON

                        inc edx
                    .endif
                .endf

                mov ebx,args

                mov ecx,ModuleInfo.ComStack
                .if [ecx].com_item.langtype
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
            .endif

            mov eax,4
            .if ModuleInfo.Ofssize == USE64

                add eax,4
            .endif

            .if ( cmd == T_DOT_CLASSDEF )

                AddLineQueueX( "%s struct %d", esi, eax )
                AddLineQueueX( "lpVtbl %sVtbl ?", edi )
            .else
                AddLineQueueX( "%s struct", esi )
                AddLineQueue ( "lpVtbl PVOID ?" )
            .endif

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

    mov ModuleInfo.class_label,0    ; init class label counter
    ret

ClassInit endp

ClassCheckOpen proc

    .if ModuleInfo.ComStack

        asmerr( 1010, ".comdef-.classdef-.ends" )
    .endif
    ret

ClassCheckOpen endp

    END
