
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
include input.inc
include tokenize.inc
include expreval.inc

; item for .CLASS, .ENDS, and .COMDEF

com_item    STRUC
cmd         dd ?
class       string_t ?
langtype    dd ?
sym         asym_t ?    ; .class name : public class
type        dd ?
vector      dd ?
com_item    ENDS
LPCLASS     typedef ptr com_item

    .code

    option proc: private

ClassProto proc uses esi edi class:string_t, langtype:int_t, args:string_t, type:int_t

  local pargs[1024]:char_t

    lea edi,pargs ; default args :abs=<val>
    mov esi,args
    mov al,1
    .while al
        lodsb
        .if al == '='
            lodsb
            .while al && al != '>'
                lodsb
            .endw
            .if al
                lodsb
            .endif
        .endif
        stosb
    .endw
    .if langtype
        AddLineQueueX( "%s %r %r %s", class, type, langtype, &pargs )
    .else
        AddLineQueueX( "%s %r %s", class, type, &pargs )
    .endif
    ret

ClassProto endp

ClassProto2 proc class:string_t, method:string_t, item:ptr com_item, args:string_t

  local buffer[128]:char_t
  local langtype:int_t

    strcpy( &buffer, class )
    mov ecx,item
    mov edx,[ecx].com_item.langtype
    mov langtype,edx
    lea edx,@CStr( "::" )
    .if [ecx].com_item.vector
        lea edx,@CStr( "_" )
    .endif
    ClassProto( strcat( strcat( eax, edx ), method ), langtype, args, T_PROTO )
    ret

ClassProto2 endp

OpenVtbl proc uses esi this:LPCLASS

  local public_class[64]:char_t

    mov esi,this
    AddLineQueueX( "%sVtbl struct", [esi].com_item.class )

    ; v2.30.32 - : public class

    .return 0 .if ![esi].com_item.sym

    mov edx,[esi].com_item.sym
    .if !SymFind( strcat( strcpy( &public_class, [edx].asym.name ), "Vtbl" ) )

        .return 1;asmerr( 2006, &public_class )
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

get_operator proc token:string_t

    mov eax,token
    mov eax,[eax]
    .switch al
    .case '=' : .return T_CMP .if ah == al : .return T_EQU
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

size_from_token proc tokenarray:tok_t

    xor eax,eax
    mov edx,tokenarray

    .switch [edx].asm_tok.token
    .case T_STYPE
        mov ecx,[edx].asm_tok.tokval
        mov al,GetMemtypeSp(ecx)
        SizeFromMemtype(al, USE_EMPTY, 0 )
        .endc
    .case T_ID
        .if SymFind( [edx].asm_tok.string_ptr )
            SizeFromMemtype( [eax].asym.mem_type, USE_EMPTY, [eax].asym.type )
        .endif
        .endc
    .case T_REG
        SizeFromRegister( [edx].asm_tok.tokval )
        .endc
    .endsw
    ret

size_from_token endp

get_param_size proc tokenarray:tok_t

    size_from_token( tokenarray )
    .if eax == 0 || eax > 64
        mov eax,2
        mov cl,ModuleInfo.Ofssize
        shl eax,cl
    .endif
    ret

get_param_size endp

get_token_size proc tokenarray:tok_t, class:string_t

    .return .if size_from_token( tokenarray )

    .if SymFind( class )
        SizeFromMemtype( [eax].asym.mem_type, USE_EMPTY, [eax].asym.type )
    .endif
    .if eax == 0 || eax > 64
        mov eax,2
        mov cl,ModuleInfo.Ofssize
        shl eax,cl
    .endif
    ret

get_token_size endp

    assume ebx:tok_t

get_param_name proc uses esi edi ebx tokenarray:tok_t, token:string_t,
        size:string_t, count:ptr, isid:ptr, context:ptr

    mov edi,token
    mov ebx,tokenarray
    mov eax,'r'
    mov [edi],eax
    mov esi,[ebx].tokpos
    xor eax,eax
    mov ecx,context
    mov [ecx],eax
    mov ecx,isid
    mov [ecx],eax
    mov ecx,size
    mov [ecx],al

    .switch get_operator( esi )
    .case 0
        .if [ebx].token != T_ID
            mov ecx,ModuleInfo.ComStack
            .if !( ecx && [ecx].com_item.type && \
                 ( [ebx].token == T_STYPE || [ebx].token == T_INSTRUCTION ) )
                .return asmerr( 1011 )
            .endif
        .endif
        strcpy( edi, [ebx].string_ptr )
        mov eax,1
        mov ecx,isid
        mov [ecx],eax
        dec eax
        .endc
    .case T_EQU
        mov byte ptr [edi],'m'
        .endc
    .case T_ANDN
    .case T_INC
    .case T_DEC
        add ebx,16
        .endc
    .endsw
    .if eax
        lea edx,[edi+1]
        GetResWName(eax, edx)
    .endif
    add ebx,16
    .if [ebx].token == T_DIRECTIVE && [ebx].tokval == T_EQU
        add ebx,16
        mov byte ptr [edi],'m'
    .endif
    mov eax,[esi]
    shr eax,8
    .if al == '=' || ah == '='
        mov byte ptr [edi],'m'
    .endif

    push ebx
    mov  edi,size
    .for esi = 1 : [ebx].token != T_FINAL : ebx += 16
        .if [ebx].token == T_STRING && [ebx].bytval == '{'
            mov ecx,context
            mov [ecx],ebx
            .break
        .elseif [ebx].token == T_COLON
            .if esi < 4
                add edi,sprintf( edi, "%u", get_param_size( &[ebx+asm_tok] ) )
            .endif
            inc esi
        .endif
    .endf
    pop ebx
    mov ecx,count
    mov [ecx],esi
    mov eax,ebx
    ret

get_param_name endp

GetClassVectorSize proc uses esi class:string_t

    .if SymFind( class )

        mov esi,eax
        .switch SizeFromMemtype( [eax].asym.mem_type, USE_EMPTY, [eax].asym.type )
        .case 2
        .case 4
        .case 8
            .if [esi].asym.mem_type & MT_FLOAT
                mov eax,16
            .endif
        .case 1
        .case 16
        .case 32
        .case 64 : .return
        .endsw
        xor eax,eax
    .endif
    ret

GetClassVectorSize endp

GetClassVectorToken proc uses esi class:string_t

    mov esi,GetClassVectorSize( class )
    .switch esi
    .case 1  : mov eax,T_AL   : .endc
    .case 2  : mov eax,T_AX   : .endc
    .case 4  : mov eax,T_EAX  : .endc
    .case 8  : mov eax,T_RAX  : .endc
    .case 16 : mov eax,T_XMM0 : .endc
    .case 32 : mov eax,T_YMM0 : .endc
    .case 64 : mov eax,T_ZMM0 : .endc
    .default
        mov eax,T_XMM0
    .endsw
    mov edx,esi
    ret

GetClassVectorToken endp

GetClassVector proc uses esi edi class:string_t, vector:string_t

    GetClassVectorToken( class )
    mov esi,edx
    mov edi,eax
    GetResWName( eax, vector )
    mov eax,esi
    mov edx,edi
    ret

GetClassVector endp

ParseOperator proc uses esi edi ebx class:string_t, tokenarray:tok_t, buffer:string_t

  local arg_count : int_t
  local id        : int_t
  local context   : string_t
  local name[16]  : char_t
  local size[16]  : char_t
  local curr[256] : char_t
  local oldstat   : input_status
  local vector[64]: char_t
  local brachets  : int_t

    mov ebx,tokenarray

    ; class :: + (...) / (...)

    .while 1

        mov ebx,get_param_name( ebx, &name, &size, &arg_count, &id, &context )
        .return .if eax == ERROR

        mov esi,ebx
        .if [ebx].token == T_OP_BRACKET

            mov brachets,1
            add esi,asm_tok

            .for edx = 0 : [ebx].token != T_FINAL : ebx += 16
                .switch [ebx].token
                .case T_OP_BRACKET
                    inc edx
                    .endc
                .case T_CL_BRACKET
                    dec edx
                    .endc .ifnz
                    .if [ebx-16].token != T_OP_BRACKET
                        inc arg_count
                    .endif
                    add ebx,16
                    .break
                .case T_COMMA
                    .endc .if edx != 1
                    inc arg_count
                    .endc
                .endsw
            .endf

        .else
            .if [ebx].token == T_FINAL
                .return asmerr( 2008, [ebx-16].tokpos )
            .endif
            mov brachets,0
            add ebx,16
            inc arg_count
        .endif

        mov edi,buffer
        .if [ebx].token != T_FINAL
            lea edi,curr
            strcpy( edi, class )
            strcat( edi, "_" )
        .endif
        strcat( edi, &name[1] )
        strcat( edi, "( " )
        .if GetClassVector( class, &vector ) >= 16
            strcat( edi, &vector )
            .if arg_count > 1
                strcat( edi, ", " )
            .endif
        .endif
        .if [ebx].token == T_FINAL
            strcat( edi, [esi].asm_tok.tokpos )
            .if !brachets
                strcat( edi, ")" )
            .endif
            .break
        .endif

        add edi,strlen(edi)
        mov esi,[esi].asm_tok.tokpos
        mov ecx,[ebx].asm_tok.tokpos
        sub ecx,esi
        rep movsb
        .if brachets == 0
            mov byte ptr [edi],')'
            inc edi
        .endif
        mov byte ptr [edi],0

        .if ModuleInfo.line_queue.head
            RunLineQueue()
        .endif
        AddLineQueue( &curr )
        InsertLineQueue()
    .endw
    mov eax,ebx
    ret

ParseOperator endp


    option proc: public

    assume ebx:ptr asm_tok

.enum { Immediat, Float, Register, Memory, Pointer }

GetTypeId PROC USES esi edi ebx buffer:string_t, tokenarray:tok_t

  local i:int_t
  local opnd:expr
  local tokval:int_t
  local id[64]:char_t
  local type:int_t
  local size:int_t
  local void:int_t
  local name[64]:char_t

    mov ebx,tokenarray

    ; find first instance of macro in line

    .while [ebx].token != T_FINAL
        .if [ebx].token == T_ID
            .break .if !_stricmp([ebx].string_ptr, "typeid")
        .endif
        add ebx,16
    .endw
    .if [ebx].token == T_FINAL && [ebx+16].token == T_OP_BRACKET
        add ebx,16
    .elseif [ebx].token != T_FINAL
        add ebx,16
    .else
        mov ebx,tokenarray
    .endif
    .return 0 .if [ebx].token != T_OP_BRACKET

    add ebx,16
    mov id,0
    .if [ebx+16].token == T_COMMA
        strcpy( &id, [ebx].string_ptr )
        add ebx,32
    .endif

    xor esi,esi
    .if [ebx].token == T_RES_ID && [ebx].tokval == T_ADDR
        add ebx,16
        inc esi
    .endif

    mov eax,ebx
    sub eax,tokenarray
    shr eax,4
    mov ecx,eax
    mov i,eax

    .for edx = 1 : [ebx].token != T_FINAL : ebx += 16, ecx++
        .switch [ebx].token
        .case T_OP_BRACKET
            inc edx
            .endc
        .case T_CL_BRACKET
            dec edx
            .endc .ifnz
            .break
        .endsw
    .endf
    .return 0 .if EvalOperand( &i, tokenarray, ecx, &opnd, 0 ) == ERROR

    mov type,0
    mov size,0
    mov name,0
    mov void,0

    mov eax,opnd.kind
    .switch eax

    .case EXPR_REG

        .if !( opnd.flags & E_INDIRECT )

            mov ecx,opnd.base_reg
            SizeFromRegister( [ecx].asm_tok.tokval )
            shl eax,3
            mov size,eax
            mov type,Register
            .endc
        .endif

    .case EXPR_ADDR

        mov type,Memory
        .if esi
            mov type,Pointer
        .endif

        mov edi,opnd.sym
        mov esi,opnd.type
        .if opnd.mbr
            mov edi,opnd.mbr
        .endif

        .if ( !edi || [edi].asym.state == SYM_UNDEFINED )
            mov void,1
            .endc
        .endif

        .if [edi].asym.mem_type == MT_TYPE && [edi].asym.type
            mov edi,[edi].asym.type
        .endif

        .if [edi].asym.target_type && \
            ( [edi].asym.mem_type == MT_PTR || [edi].asym.ptr_memtype == MT_TYPE )

            .if [edi].asym.mem_type == MT_PTR
                mov type,Pointer
            .endif
            mov edi,[edi].asym.target_type
        .endif

        .if [edi].asym.state == SYM_TYPE && [edi].asym.typekind == TYPE_STRUCT

            strcpy( &name, [edi].asym.name )
            .endc
        .endif

        .if esi
            .if [esi].asym.state == SYM_TYPE && [esi].asym.typekind == TYPE_STRUCT

                strcpy( &name, [esi].asym.name )
                .endc
            .endif
        .endif

        .if [edi].asym.state == SYM_INTERNAL || \
            [edi].asym.state == SYM_STACK || \
            [edi].asym.state == SYM_STRUCT_FIELD || \
            [edi].asym.state == SYM_TYPE

            mov cl,[edi].asym.mem_type
            .switch pascal cl
            .case MT_BYTE    : mov eax,T_BYTE
            .case MT_SBYTE   : mov eax,T_SBYTE
            .case MT_WORD    : mov eax,T_WORD
            .case MT_SWORD   : mov eax,T_SWORD
            .case MT_REAL2   : mov eax,T_REAL2
            .case MT_DWORD   : mov eax,T_DWORD
            .case MT_SDWORD  : mov eax,T_SDWORD
            .case MT_REAL4   : mov eax,T_REAL4
            .case MT_FWORD   : mov eax,T_FWORD
            .case MT_QWORD   : mov eax,T_QWORD
            .case MT_SQWORD  : mov eax,T_SQWORD
            .case MT_REAL8   : mov eax,T_REAL8
            .case MT_TBYTE   : mov eax,T_TBYTE
            .case MT_REAL10  : mov eax,T_REAL10
            .case MT_OWORD   : mov eax,T_OWORD
            .case MT_REAL16  : mov eax,T_REAL16
            .case MT_YWORD   : mov eax,T_YWORD
            .case MT_ZWORD   : mov eax,T_ZWORD
            .case MT_PROC    : mov eax,T_PROC
            .case MT_NEAR    : mov eax,T_NEAR
            .case MT_FAR     : mov eax,T_FAR
            .case MT_PTR
                mov type,Pointer
                mov eax,T_PTR
                mov cl,[edi].asym.mem_type
                .if [edi].asym.is_ptr == 1 && cl != [edi].asym.ptr_memtype
                    .if [edi].asym.ptr_memtype == MT_EMPTY
                        mov void,1
                        .endc
                    .endif
                    mov cl,[edi].asym.ptr_memtype
                    .gotosw
                .endif
            .default
                mov void,1
                .endc
            .endsw
            .endc .if void

            lea edx,name
            GetResWName(eax, edx)
            .endc
        .endif
        mov void,1
        .endc
    .case EXPR_CONST
        mov type,Immediat
        mov size,32
        mov eax,dword ptr opnd.hlvalue
        or  eax,dword ptr opnd.hlvalue[4]
        .if eax
            mov size,128
        .elseif opnd.hvalue
            mov size,64
        .endif
        .endc
    .case EXPR_FLOAT
        mov type,Float
        .endc
    .endsw

    .if void
        strcpy( &name, "void" )
    .endif

    .switch type
    .case Immediat
        .if id
            LSPrintF( buffer, "%s?i%d", &id, size)
        .else
            LSPrintF( buffer, "imm_%d", size)
        .endif
        .return 1
    .case Float
        .if id
            LSPrintF( buffer, "%s?flt", &id)
        .else
            strcpy( buffer, "imm_float" )
        .endif
        .return 1
    .case Register
        .if id
            LSPrintF( buffer, "%s?r%d", &id, size)
        .else
            LSPrintF( buffer, "reg_%d", size)
        .endif
        .return 1
    .case Memory
        .if id
            LSPrintF( buffer, "%s?%s", &id, &name )
        .else
            strcpy( buffer, "mem_" )
            strcat( buffer, &name )
        .endif
        .return 1
    .case Pointer
        .if id
            LSPrintF( buffer, "%s?p%s", &id, &name )
        .else
            strcpy( buffer, "ptr_" )
            strcat( buffer, &name )
        .endif
        .return 1
    .endsw
    xor eax,eax
    ret

GetTypeId ENDP

ProcType proc uses esi edi ebx i:int_t, tokenarray:tok_t, buffer:string_t

  local retval:int_t
  local name:string_t
  local IsCom:uchar_t
  local IsType:uchar_t
  local language[32]:char_t
  local P$[16]:char_t
  local T$[16]:char_t
  local constructor:int_t

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    mov constructor,0

    mov name,[ebx-16].string_ptr
    mov retval,NOT_ERROR
    mov esi,ModuleInfo.ComStack
    .if esi
        .if !strcmp(eax, [esi].com_item.class)
            ClassProto2( name, name, esi, [ebx+16].tokpos )
            mov constructor,1
            jmp done
        .endif
    .endif

    mov IsCom,0
    mov IsType,0

    mov eax,CurrStruct
    .if eax
        mov edi,[eax].asym.name
        .if strlen(edi) > 4
            mov eax,[edi+eax-4]
        .endif
    .endif

    mov edi,buffer

    .if ( eax == "lbtV" )

        inc IsCom

    .elseif esi

        .if [esi].com_item.type
            mov IsType,1
        .endif

        .if ( Token_Count > 2 && [ebx+16].tokval == T_LOCAL )

            add ebx,16

        .elseif IsType == 0

            AddLineQueueX( "%s ends", [esi].com_item.class )
            mov retval,OpenVtbl(esi)
            inc IsCom
        .endif
    .endif

    inc ModuleInfo.class_label

    sprintf( &T$, "T$%04X", ModuleInfo.class_label )
    sprintf( &P$, "P$%04X", ModuleInfo.class_label )

    strcat( strcpy( edi, &T$ ), " typedef proto" )

    .if ( esi && [esi].com_item.cmd == T_DOT_COMDEF )

        .if ( ModuleInfo.Ofssize == USE32 && ModuleInfo.langtype != LANG_STDCALL )

            strcat(edi, " stdcall")
        .endif
    .endif

    add ebx,16
    xor esi,esi

    .if ( [ebx].token != T_FINAL )

        .if ( IsCom || IsType )

            .if ( [ebx].tokval >= T_CCALL && [ebx].tokval <= T_WATCALL )

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

    .elseif ( ( IsType || IsCom ) && ModuleInfo.ComStack )

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

    mov ecx,ModuleInfo.ComStack
    .if ecx && [ecx].com_item.type
        AddLineQueueX( "%s::%s %s", [ecx].com_item.class, name, &[edi+15] )
    .else
        AddLineQueue( edi )
        AddLineQueueX( "%s typedef ptr %s", &P$, &T$ )
        AddLineQueueX( "%s %s ?", name, &P$ )
    .endif
done:
    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif
    .if constructor
        strcpy(buffer, name)
        strcat(eax, "_")
        strcat(eax, name)
        .if SymFind( eax )
            or [eax].asym.flag,S_METHOD
        .endif
    .endif
    mov eax,retval
    ret

ProcType endp

    assume esi:tok_t

ParseClass proc uses esi edi ebx j:int_t, tokenarray:tok_t, buffer:string_t

  local i:int_t, q:int_t, class:string_t, name:string_t, tokval:int_t

    mov i,0
    mov edi,buffer
    mov ebx,tokenarray

    mov edx,j
    dec edx
    shl edx,4

    mov ecx,[ebx+edx].tokpos
    sub ecx,[ebx].tokpos
    mov q,ecx
    mov byte ptr[edi+ecx],0
    .if ecx
        mov esi,[ebx].tokpos
        rep movsb
        mov word ptr [edi],' '
        mov edi,buffer
    .endif

    lea esi,[ebx+edx+asm_tok]
    .return 0 .if [esi].token != T_DBL_COLON
    mov class,[esi-16].string_ptr
    mov name,[esi+16].string_ptr

    get_operator( [esi+16].tokpos )
    mov edx,32
    .if eax == T_ANDN || eax == T_INC || eax == T_DEC
        add edx,16
    .endif

    .if eax || [esi+edx].tokval == T_ENDP || [esi+edx].token == T_OP_BRACKET

        mov tokval,eax
        strcat( edi, class )
        strcat( edi, "_" )
        .if tokval
            add esi,asm_tok
            ParseOperator( class, esi, edi )
        .else
            strcat( edi, name )
            strcat( edi, " " )
            strcat( edi, [esi+32].tokpos )
        .endif
        mov Token_Count,Tokenize( edi, 0, ebx, TOK_DEFAULT )

        .return 1
    .endif

    mov tokval,[esi+32].tokval
    .return 0 .if eax != T_PROC && eax != T_PROTO

    ; class :: name proc syscall private uses a b c:dword,

    strcpy( edi, class )
    strcat( edi, "_" )
    strcat( edi, name )
    strcat( edi, " " )
    strcat( edi, [esi+32].string_ptr )
    strcat( edi, " " )

    mov eax,j
    add eax,3
    mov i,eax
    add esi,3*16

    .while [esi].token != T_FINAL && \
           [esi].token != T_COLON && \
           [esi+16].token != T_COLON

        .if [esi].token == T_STRING

            .break .if [esi].string_delim != '<'

            strcat( edi, "<" )
            strcat( edi, [esi].string_ptr )
            strcat( edi, "> " )

        .else

            strcat( edi, [esi].string_ptr )
            strcat( edi, " " )
        .endif
        inc i
        add esi,16
    .endw

    .if [esi].token != T_FINAL && [esi+16].token == T_COLON

        .switch [esi].token
        .case T_INSTRUCTION
        .case T_REG
        .case T_DIRECTIVE
        .case T_STYPE
        .case T_RES_ID
            strcat( edi, [esi].string_ptr )
            strcat( edi, " " )
            inc i
            add esi,16
            .endc
        .case T_ID
            .if tokval == T_PROC
                .if _stricmp( [esi].string_ptr, "PRIVATE" )
                    _stricmp( [esi].string_ptr, "EXPORT" )
                .endif
                .gotosw(T_RES_ID) .if eax == 0
            .endif
            .endc
        .endsw
    .endif

    .if tokval == T_PROC
        strcat( edi, "this" )
    .endif
    strcat( edi, ":" )

    imul eax,j,asm_tok
    movzx eax,[ebx+eax-16].token
    .switch eax
      .case T_INSTRUCTION
      .case T_REG
      .case T_DIRECTIVE
      .case T_STYPE
      .case T_RES_ID
        .endc
      .case T_ID
        .if SymSearch( class )
            .endc .if [eax].asym.state == SYM_TYPE && [eax].asym.typekind == TYPE_TYPEDEF
        .endif
      .default
        strcat( edi, "ptr " )
        .endc
    .endsw
    strcat( edi, class )

    imul eax,i,asm_tok
    add ebx,eax

    .if [ebx].token != T_FINAL
        lea edx,@CStr(", ")
        .if ( [ebx].token == T_STRING && [ebx].string_delim == '{' )
            inc edx
        .endif
        strcat( edi, edx )
        strcat( edi, [ebx].tokpos )
    .endif

    strcpy( CurrSource, edi )
    mov Token_Count,Tokenize( edi, 0, tokenarray, TOK_DEFAULT )
    mov eax,1
    ret

ParseClass endp

    assume esi:nothing

ParseMacroArgs proc uses esi edi ebx buffer:string_t, count:int_t, args:string_t

    .for ebx = args, edi = buffer, esi = 1 : esi < count : esi++

        add edi,sprintf( edi, "_%u, ", esi )

        .if strchr(ebx, ',')
            inc eax
        .else
            strlen(ebx)
            add eax,ebx
        .endif
        xchg ebx,eax

        .if strchr(eax, '=')

            .if eax < ebx

                dec edi
                mov byte ptr [edi-1],':'
                mov ecx,ebx
                sub ecx,eax
                .if byte ptr [ebx-1] == ','
                    dec ecx
                .endif
                mov edx,esi
                mov esi,eax
                rep movsb
                mov esi,edx
                mov dword ptr [edi],' ,'
                add edi,2
            .endif
        .endif
    .endf
    mov eax,edi
    ret

ParseMacroArgs endp

MacroInline proc uses esi edi ebx name:string_t, count:int_t, args:string_t, inline:string_t, vargs:int_t

  local buf[512]:char_t
  local mac[512]:char_t
  local index:int_t

    .return 0 .if ( Parse_Pass > PASS_1 )

    strcpy( &buf, args )

    mov edx,ModuleInfo.ComStack
    .if edx && [edx].com_item.vector
        mov mac,0

        mov edi,ParseMacroArgs( &mac, count, &buf )
        strcat(edi, "this:=<")
        mov edx,ModuleInfo.ComStack
        mov ebx,[edx].com_item.vector
        strcat(edi, GetResWName( ebx, NULL ) )
        strcat(edi, ">")
    .else
        lea edi,[strcpy( &mac, "this" ) + 4]
        .if count > 1
            lea edi,[strcpy(edi, ", ") + 2]
            mov edi,ParseMacroArgs( edi, count, &buf )
            sub edi,2
            mov byte ptr [edi],0
        .endif
    .endif
    .if vargs
        strcpy( edi, ":vararg" )
    .endif
    AddLineQueueX( "%s macro %s", name, &mac )

    .for edi = 0, esi = inline : strchr(esi, 10) :

        mov ebx,eax
        mov byte ptr [ebx],0
        .if byte ptr [esi]
            mov edi,esi
            AddLineQueue(esi)
        .endif
        mov byte ptr [ebx],10
        lea esi,[ebx+1]
    .endf
    .if byte ptr [esi]
        mov edi,esi
        AddLineQueue(esi)
    .endif
    .if edi == 0
        AddLineQueue( "exitm<>" )
    .else
        .if _memicmp( edi, "exitm", 5 )
            _memicmp( edi, "retm", 4 )
        .endif
        .if eax
            AddLineQueue( "exitm<>" )
        .endif
    .endif
    AddLineQueue( "endm" )
    MacroLineQueue()
    ret

MacroInline endp

ClassDirective proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local rc:int_t, args:tok_t, cmd:uint_t, public_pos:string_t,
        class[128]:char_t, constructor:int_t

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,class
    mov constructor,0

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
                mov rc,asmerr( 1011 )
            .endif
            .return rc
        .endif
        mov ModuleInfo.ComStack,0
        .endc .if [edi].com_item.type

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
        .if esi && [esi].com_item.type
        .elseif !eax || !esi
            .return asmerr( 1011 )
        .endif

        ; .operator + [:type] [{..}]

        lea ebx,[ebx+edx+16]

        .new is_id      : int_t
        .new is_vararg  : int_t
        .new context    : string_t
        .new class_ptr  : string_t
        .new token[64]  : char_t
        .new name[512]  : char_t

        mov is_vararg,0

        mov ebx,get_param_name( ebx, &token, edi, &args, &is_id, &context )
        .return .if eax == ERROR

        .if context
            mov ecx,context
            mov context,NULL
            assume ecx:tok_t
            .if [ecx].token == T_STRING && [ecx].bytval == '{'
                .if [ecx-16].token == T_RES_ID && [ecx-16].tokval == T_VARARG
                    inc is_vararg
                .endif
                mov context,[ecx].string_ptr
                mov eax,[ecx].tokpos
                mov byte ptr [eax],0
                .while byte ptr [eax-1] <= ' '
                    .break .if eax <= [ecx-asm_tok].tokpos
                    sub eax,1
                .endw
                mov byte ptr [eax],0
                mov [ecx].token,T_FINAL
            .endif
            assume ecx:nothing
        .endif

        lea edx,token
        .if is_id || [esi].com_item.type
            mov class,0
            .if [esi].com_item.type && is_id == 0
                inc edx
            .endif
        .endif

        lea edi,name
        sprintf( edi, "%s%s", edx, &class )

        mov edx,ModuleInfo.ComStack
        mov ecx,[edx].com_item.class
        mov class_ptr,ecx

        .if [edx].com_item.sym
            mov ecx,[edx].com_item.sym
            mov ecx,[ecx].asym.name
        .endif

        .if !SymFind( strcat( strcpy( &class, ecx ), "Vtbl" ) )
            mov eax,CurrStruct
        .endif
        .if eax
            mov ecx,eax
            .if !SearchNameInStruct( ecx, edi, &i, 0 )
                .if strcmp(edi, class_ptr)
                    ClassProto( edi, [esi].com_item.langtype, [ebx].tokpos, T_PROC )
                .else
                    ClassProto2( class_ptr, edi, esi, [ebx].tokpos )
                    inc constructor
                .endif
            .endif
        .elseif [esi].com_item.type
            ClassProto2( class_ptr, edi, esi, [ebx].tokpos )
            inc constructor
        .endif
        .endc .if context == 0 || Parse_Pass > PASS_1

        ; .operator + :type { ... }

        sprintf( &token, "%s_%s", class_ptr, &name )

        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        RunLineQueue()

        .if constructor
            .if SymFind( &token )
                or [eax].asym.flag,S_METHOD
            .endif
        .endif
        MacroInline( &token, args, [ebx].tokpos , context, is_vararg )
        .return rc

      .case T_DOT_COMDEF
      .case T_DOT_CLASS
      .case T_DOT_TEMPLATE

        .return asmerr( 1011 ) .if ModuleInfo.ComStack
        lea ebx,[ebx+edx+16]

        mov ModuleInfo.ComStack,LclAlloc( com_item )
        mov ecx,cmd
        xor edx,edx
        mov [eax].com_item.cmd,ecx
        mov [eax].com_item.type,edx
        mov [eax].com_item.langtype,edx
        mov [eax].com_item.sym,edx
        mov [eax].com_item.vector,edx

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
        .if ( [ebx+16].token != T_FINAL && edx >= T_CCALL && edx <= T_WATCALL )

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

            mov ebx,tokenarray
            xor edi,edi

            .switch [ebx+16].token
            .case T_DIRECTIVE
            .case T_INSTRUCTION
            .case T_REG
            .case T_RES_ID
            .case T_STYPE
                mov edi,size_from_token( &[ebx+16] )
                mov eax,[ebx+16].tokval
                .endc
            .default
                .if SymFind( esi )
                    .if [eax].asym.state == SYM_TYPE && \
                        [eax].asym.typekind == TYPE_TYPEDEF
                        mov edi,eax
                        SizeFromMemtype( [eax].asym.mem_type, USE_EMPTY, [eax].asym.type )
                        .if eax < 16 && [edi].asym.mem_type & MT_FLOAT
                            mov edi,16
                        .else
                            mov edi,eax
                        .endif
                        mov eax,T_TYPEDEF
                    .else
                        xor eax,eax
                    .endif
                .endif
            .endsw

            mov ecx,ModuleInfo.ComStack

            .if eax

                mov [ecx].com_item.type,eax
                .if edi < 16
                    mov eax,T_RAX
                    .switch edi
                    .case 1 : mov eax,T_AL  : .endc
                    .case 2 : mov eax,T_AX  : .endc
                    .case 4 : mov eax,T_EAX : .endc
                    .endsw
                    mov [ecx].com_item.vector,eax
                .endif
            .else
                AddLineQueueX( "%s struct", esi )
            .endif
        .endif

        mov ecx,ModuleInfo.ComStack
        mov esi,[ecx].com_item.sym
        .if esi
            .if ( cmd != T_DOT_TEMPLATE )
                .if !SearchNameInStruct( esi, "lpVtbl", &cmd, 0 )
                    AddLineQueueX( "lpVtbl %sVtbl ?", &class )
                .endif
            .endif
            AddLineQueueX( "%s <>", [esi].asym.name )
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
