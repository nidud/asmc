include stdio.inc
include string.inc
include asmc.inc
include symbols.inc
include segment.inc
include parser.inc
include hll.inc
include lqueue.inc
include reswords.inc
include listing.inc
include memalloc.inc
include types.inc
include macro.inc

; item for .CLASS, .ENDS, and .COMDEF

com_item    STRUC
cmd         dd ?
class       string_t ?
langtype    dd ?
sym         asym_t ?    ; .class name : public class
com_item    ENDS
LPCLASS     typedef ptr com_item

    .code

OpenVtbl proc private uses esi this:LPCLASS

  local public_class[64]:char_t

    mov esi,this
    AddLineQueueX( "%sVtbl struct", [esi].com_item.class )

    ; v2.30.32 - : public class

    .return 0 .if ![esi].com_item.sym

    mov edx,[esi].com_item.sym
    .if !SymFind( strcat( strcpy( &public_class, [edx].asym.name ), "Vtbl" ) )

        .return asmerr( 2006, &public_class )
    .endif

    mov ecx,eax
    xor eax,eax

    .if ( [ecx].asym.total_size )
if 1
        AddLineQueueX( "%s <>", &public_class )
else
        .for ( edx = [ecx].esym.structinfo,
               esi = [edx].struct_info.head : esi : esi = [esi].sfield.next )

            mov ecx,[esi].sfield.sym.name
            mov edx,[esi].sfield.sym.type
            .if edx
                AddLineQueueX( "%s %s ?", ecx, [edx].asym.name )
            .else
                .return asmerr( 2006, ecx )
            .endif
        .endf
endif
        mov eax,1
    .endif
    ret

OpenVtbl endp

    assume ebx:tok_t

ProcType proc uses esi edi ebx i:int_t, tokenarray:tok_t, buffer:string_t

  local retval:int_t
  local name:string_t
  local IsCom:uchar_t
  local language[32]:char_t
  local P$[16]:char_t
  local T$[16]:char_t

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    mov edi,buffer

    mov name,[ebx-16].string_ptr
    mov retval,NOT_ERROR

    inc ModuleInfo.class_label

    sprintf( &T$, "T$%04X", ModuleInfo.class_label )
    sprintf( &P$, "P$%04X", ModuleInfo.class_label )

    mov IsCom,0

    mov eax,CurrStruct
    mov esi,[eax].asym.name
    .if strlen(esi) > 4
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
            mov retval,OpenVtbl(esi)
            inc IsCom
        .endif
    .endif

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

        .for ( eax = ebx : [eax].asm_tok.token != T_FINAL : eax += 16 )

            .if ( [eax].asm_tok.token == T_COLON )

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
    ret

ProcType endp

get_operator proc token:int_t

    mov eax,token
    .switch al
    .case '=' : .return T_EQU
    .case '&' : .return T_ANDN .if ah == '~' : .return T_AND
    .case '|' : .return T_OR
    .case '^' : .return T_XOR
    .case '*' : .return T_MUL
    .case '/' : .return T_DIV
    .case '<' : .endc .if ah != '<' : .return T_SHL
    .case '>' : .endc .if ah != '>' : .return T_SHR
    .case '+' : .return T_INC .if ah == '+' : .return T_ADD
    .case '-' : .return T_DEC .if ah == '-' : .return T_SUB
    .case '~' : .return T_NOT
    .case '%' : .return T_MOD
    .endsw
    .return 0

get_operator endp

ClassDirective proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local rc          : int_t,
        args        : int_t,
        cmd         : uint_t,
        public_pos  : string_t,
        class[64]   : char_t

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,class

    mov edx,i
    shl edx,4
    mov eax,[ebx+edx].tokval
    mov cmd,eax
    inc i

    .switch eax
      .case T_DOT_ENDS
        mov edi,ModuleInfo.ComStack
        mov esi,CurrStruct
        .if !edi
            .if esi
                mov rc,asmerr(1011)
            .endif
            .return rc
        .endif
        mov ModuleInfo.ComStack,0
        AddLineQueueX( "%s ends", [esi].asym.name )
        mov edx,[edi].com_item.sym
        .if edx
            .if !strcmp([edi].com_item.class, [esi].asym.name)
                OpenVtbl(edi)
                AddLineQueueX( "%sVtbl ends", [esi].asym.name )
            .endif
        .endif
        .endc

      .case T_DOT_OPERATOR

        mov esi,ModuleInfo.ComStack
        mov eax,CurrStruct
        .if !eax || !esi
            .return asmerr(1011)
        .endif
        ;
        ; .operator + :type, :type
        ;
        ;mov ModuleInfo.dotname,TRUE
        lea ebx,[ebx+edx+16]

        .new is_id:int_t
        .new is_equ:int_t
        .new token[64]:char_t
        .new inline:string_t
        .new name[128]:string_t

        mov is_id,0     ; name proc :qword, :qword
        mov is_equ,0    ; [m|r]add88 proc :qword, :qword

        mov edx,[ebx].tokpos
        mov ecx,[edx]
        push ecx
        .switch get_operator(ecx)
        .case 0
            .if [ebx].token != T_ID
                .return asmerr(1011)
            .endif
            inc is_id
            strcpy(&token, [ebx].string_ptr)
            xor eax,eax
            .endc
        .case T_EQU
            inc is_equ
            .endc
        .case T_ANDN
        .case T_INC
        .case T_DEC
            add ebx,16
            .endc
        .endsw
        .if eax
            mov token,'r'
            lea edx,token[1]
            GetResWName(eax, edx)
        .endif
        add ebx,16
        .if [ebx].token == T_DIRECTIVE && [ebx].tokval == T_EQU
            add ebx,16
            inc is_equ
        .endif
        pop eax
        shr eax,8
        .if al == '=' || ah == '='
            inc is_equ
        .endif
        .if is_equ
            mov token,'m'
        .endif

        mov class,0
        mov inline,0

        push ebx
        .for ( args = 1 : [ebx].token != T_FINAL : ebx += 16 )

            .if ( [ebx].token == T_STRING && [ebx].bytval == '{' )

                mov inline,[ebx].string_ptr
                mov eax,[ebx].tokpos
                mov byte ptr [eax],0
                mov [ebx].token,T_FINAL
                .break
            .endif

            .if ( [ebx].token == T_COLON )

                xor eax,eax
                .if ( [ebx+16].token == T_STYPE )

                    mov ecx,[ebx+16].tokval
                    mov al,GetMemtypeSp(ecx)

                    SizeFromMemtype(al, USE_EMPTY, 0 )

                .elseif ( [ebx+16].token == T_ID )

                    .if SymFind( [ebx+16].string_ptr )

                        SizeFromMemtype( [eax].asym.mem_type, USE_EMPTY, [eax].asym.type )
                    .endif
                .endif
                .if eax == 0 || eax > 64
                    mov eax,4
                    .if ModuleInfo.Ofssize == USE64
                        mov eax,8
                    .endif
                .endif
                .if args < 4
                    add edi,sprintf(edi, "%u", eax)
                .endif
                inc args
            .endif
        .endf
        pop ebx

        .if is_id
            mov class,0
        .endif

        lea edi,name
        sprintf(edi, "%s%s", &token, &class )

        mov edx,ModuleInfo.ComStack
        mov ecx,[edx].com_item.class
        .if [edx].com_item.sym
            mov ecx,[edx].com_item.sym
            mov ecx,[ecx].asym.name
        .endif

        .if !SymFind( strcat( strcpy( &class, ecx ), "Vtbl" ) )
            mov eax,CurrStruct
        .endif
        mov ecx,eax
        .if !SearchNameInStruct( ecx, edi, &i, 0 )
            AddLineQueueX( " %s proc %s", edi, [ebx].tokpos )
        .endif

        .endc .if inline == 0 || Parse_Pass > PASS_1

        ;
        ; .operator + :type, :type {
        ;   add _1,_2
        ;   ...
        ;   exitm<...>
        ; }
        ;
        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        RunLineQueue()

        .new macroargs[256]:char_t
        .for ( esi = 1, edi = &[strcpy(&macroargs, "this")+4] : esi < args : esi++ )
            add edi,sprintf(edi, ", _%u", esi)
        .endf
        mov edi,ModuleInfo.ComStack
        AddLineQueueX( "%s_%s macro %s", [edi].com_item.class, &name, &macroargs )
        .for ( esi = inline : strchr(esi, 10) : )
            mov ebx,eax
            mov byte ptr [ebx],0
            .if byte ptr [esi]
                AddLineQueue(esi)
            .endif
            mov byte ptr [ebx],10
            lea esi,[ebx+1]
        .endf
        .if byte ptr [esi]
            AddLineQueue(esi)
        .endif
        AddLineQueue( "endm" )
        MacroLineQueue()
        .return rc

      .case T_DOT_COMDEF
      .case T_DOT_CLASS
      .case T_DOT_TEMPLATE
        .return asmerr(1011) .if ModuleInfo.ComStack
        lea ebx,[ebx+edx+16]

        mov ModuleInfo.ComStack,LclAlloc( com_item )
        mov ecx,cmd
        mov [eax].com_item.cmd,ecx
        mov [eax].com_item.langtype,0
        mov [eax].com_item.sym,NULL

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

        .if ( cmd != T_DOT_TEMPLATE )

            AddLineQueueX( "%sVtbl typedef ptr %sVtbl", edi, esi )

            .if ( cmd == T_DOT_CLASS )

                AddLineQueueX( "%s typedef ptr %s", edi, esi )
            .endif
        .endif

        mov public_pos,NULL

        .for ( edi = 0, ebx = args : [ebx].token != T_FINAL : ebx += 16 )

            .if ( [ebx].token == T_COLON )

                .if ( [ebx+asm_tok].token  == T_DIRECTIVE && \
                      [ebx+asm_tok].tokval == T_PUBLIC )

                    mov public_pos,[ebx].tokpos
                    mov byte ptr [eax],0
                    mov ebx,[ebx+asm_tok*2].string_ptr
                    .return asmerr( 2006, ebx ) .if !SymFind( ebx )

                    mov ecx,ModuleInfo.ComStack
                    mov [ecx].com_item.sym,eax

                .else

                    inc edi
                .endif
                .break
            .endif
        .endf

        .if ( cmd == T_DOT_CLASS )

            mov ebx,args
            mov ecx,ModuleInfo.ComStack

            .if ( [ecx].com_item.langtype )
                .if edi
                    AddLineQueueX( "%s::%s proto %s %s", esi, esi, [ebx-16].string_ptr, [ebx].tokpos )
                .else
                    AddLineQueueX( "%s::%s proto %s", esi, esi, [ebx-16].string_ptr )
                .endif
            .else
                .if edi
                    AddLineQueueX( "%s::%s proto %s", esi, esi, [ebx].tokpos )
                .else
                    AddLineQueueX( "%s::%s proto", esi, esi )
                .endif
            .endif

            mov eax,public_pos
            .if eax
                mov byte ptr [eax],':'
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

        mov ecx,ModuleInfo.ComStack
        mov eax,[ecx].com_item.sym
        .if eax
            AddLineQueueX( "%s <>", [eax].asym.name )
        .elseif ( cmd != T_DOT_TEMPLATE )
            AddLineQueueX( "lpVtbl %sVtbl ?", &class )
        .endif
    .endsw

    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    mov eax,rc
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
