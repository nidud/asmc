; CLASS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
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
include operator.inc

    .code

    option proc: private

ClassProto proc uses esi edi class:string_t, langtype:int_t, args:string_t, type:int_t

  local pargs[1024]:char_t

    lea edi,pargs ; default args :abs=<val>
    mov esi,args
    lea ecx,[edi+1023]
    mov al,1

    .while al && edi < ecx
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

    assume esi:ptr com_item

ClassProto2 proc uses esi edi class:string_t, method:string_t, item:ptr com_item, args:string_t

  local name[256]:char_t
  local buffer[256]:char_t

    mov esi,item
    mov edi,args

    tsprintf( &name, "%s_%s", class, method )
    .if ( [esi].method != T_DOT_STATIC )
        .if ( byte ptr [edi] )
            tsprintf( &buffer, ":ptr %s, %s", class, edi )
        .else
            tsprintf( &buffer, ":ptr %s", class )
        .endif
        lea edi,buffer
    .endif
    ClassProto( &name, [esi].langtype, edi, T_PROTO )
    ret

ClassProto2 endp

    assume edi:ptr sfield

AddPublic proc uses esi edi ebx this:ptr com_item, sym:ptr asym

  local q[256]:char_t

    mov esi,this
    mov ebx,sym

    .if ( [ebx].asym.total_size && Parse_Pass == 0 )

        .for ( edx = [ebx].dsym.structinfo,
               edi = [edx].struct_info.head : edi : edi = [edi].next )

            .if [edi].type

                mov edx,[edi].type
                .if [edx].asym.typekind == TYPE_STRUCT

                    AddPublic(esi, edx)
                .else

                    strcpy( &q, [ebx].asym.name )
                    movzx ecx,[ebx].asym.name_size
                    mov word ptr [eax+ecx-4],'_'

                    .if SymFind( strcat( eax, [edi].name ) )

                        mov edx,[eax].asym.name
                        .if [eax].asym.state == SYM_TMACRO
                            mov edx,[eax].asym.string_ptr
                        .endif
                        AddLineQueueX( "%s_%s equ <%s>", [esi].class, [edi].name, edx )
                    .endif
                .endif
            .endif
        .endf
    .endif
    ret

AddPublic endp

OpenVtbl proc uses esi ebx this:ptr com_item

  local q[256]:char_t

    mov esi,this
    AddLineQueueX( "%sVtbl struct", [esi].class )

    ; v2.30.32 - : public class

    mov edx,[esi].publsym
    .return 0 .if !edx
    .return 1 .if !SymFind( strcat( strcpy( &q, [edx].asym.name ), "Vtbl" ) )

    mov ebx,eax
    xor eax,eax
    .if [ebx].asym.total_size

        AddLineQueueX( "%s <>", &q )
        AddPublic(esi, ebx)
        mov eax,1
    .endif
    ret

OpenVtbl endp

    assume esi:nothing
    assume edi:nothing
    assume ebx:ptr asm_tok

get_param_name proc uses esi edi ebx tokenarray:token_t, token:string_t,
        count:ptr int_t, isid:ptr int_t, context:ptr string_t, langtype:ptr int_t

   .new operator:byte = 0

    mov edi,token
    mov ebx,tokenarray
    mov esi,[ebx].tokpos
    xor eax,eax
    mov ecx,context
    mov [ecx],eax
    mov ecx,isid
    mov [ecx],eax

    .if ( GetOpType( ebx, edi ) == ERROR )

        .if ( [ebx].token != T_ID )
            .return asmerr( 1011 )
        .endif
        strcpy( edi, [ebx].string_ptr )
        mov ecx,isid
        inc dword ptr [ecx]
        add ebx,16
    .else
        mov ebx,eax
        inc operator
    .endif

    .if ( [ebx].token == T_RES_ID ) ; fastcall...

        mov ecx,langtype
        mov eax,[ebx].tokval
        mov [ecx],eax
        add ebx,16
    .endif

    mov edi,ebx
    .for ( esi = 1 : [ebx].token != T_FINAL : ebx += 16 )

        .if ( [ebx].token == T_STRING && [ebx].bytval == '{' )

            mov ecx,context
            mov [ecx],ebx
            .break

        .elseif ( [ebx].token == T_COLON )

            inc esi
            .if ( operator )
                OperatorParam( &[ebx+16], token )
            .endif
        .endif
    .endf
    mov ecx,count
    mov [ecx],esi
   .return edi

get_param_name endp

    option proc: public

ProcType proc uses esi edi ebx i:int_t, tokenarray:token_t

  local retval:int_t
  local name:string_t
  local IsCom:uchar_t
  local language[32]:char_t
  local langtype:int_t
  local P$[16]:char_t
  local T$[16]:char_t
  local constructor:int_t
  local buffer:string_t

    mov buffer,alloca(ModuleInfo.max_line_len)

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    mov constructor,0
    mov langtype,0
    mov name,[ebx-16].string_ptr
    mov retval,NOT_ERROR
    mov esi,ModuleInfo.ComStack

    .if ( esi )

        mov langtype,[esi].com_item.langtype
        mov edi,NameSpace( name, name )

        .if ( strcmp( edi, [esi].com_item.class ) == 0 )

            ClassProto2( edi, edi, esi, [ebx+16].tokpos )
            mov constructor,1
            jmp done
        .endif
    .endif

    mov IsCom,0

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

        .if ( Token_Count > 2 && [ebx+16].tokval == T_LOCAL )

            add ebx,16

        .else

            AddLineQueueX( "%s ends", [esi].com_item.class )
            mov retval,OpenVtbl(esi)
            inc IsCom
        .endif
    .endif

    inc ModuleInfo.class_label

    tsprintf( &T$, "T$%04X", ModuleInfo.class_label )
    tsprintf( &P$, "P$%04X", ModuleInfo.class_label )

    strcat( strcpy( edi, &T$ ), " typedef proto" )

    .if ( esi && [esi].com_item.cmd == T_DOT_COMDEF )

        .if ( ModuleInfo.Ofssize == USE32 && ModuleInfo.langtype != LANG_STDCALL )

            strcat(edi, " stdcall")
        .endif
    .endif

    add ebx,16
    xor esi,esi

    .if ( [ebx].token != T_FINAL )

        .if ( IsCom )

            .if ( [ebx].tokval >= T_CCALL && [ebx].tokval <= T_WATCALL )

                inc esi
            .endif

            .if ( [ebx+16].token == T_FINAL || esi || \
                ( [ebx].token != T_COLON && [ebx+16].token != T_COLON ) )

                strcat(edi, " ")
                strcat(edi, [ebx].string_ptr)
                add ebx,16

            .elseif !esi && langtype

                GetResWName(langtype, &language)
                strcat(edi, " ")
                strcat(edi, &language)
            .endif
            xor esi,esi
        .endif

        .for ( eax = ebx : [eax].asm_tok.token != T_FINAL : eax += 16 )

            .if ( [eax].asm_tok.token == T_COLON )

                inc esi
                .break
            .endif
        .endf

    .elseif ( IsCom && ModuleInfo.ComStack )

        mov ecx,ModuleInfo.ComStack
        mov edx,[ecx].com_item.langtype
        .if edx

            GetResWName(edx, &language)
            strcat(edi, " ")
            strcat(edi, &language)
        .endif
    .endif


    mov eax,ModuleInfo.ComStack
    .if ( eax )
        .if ( [eax].com_item.method != T_DOT_STATIC )

            xor eax,eax
        .endif
    .endif

    .if ( IsCom && !eax )

        strcat(edi, " :ptr")
        mov eax,ModuleInfo.ComStack
        .if ( eax )

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

done:
    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif

    .if ( constructor )

        strcpy( buffer, edi )
        strcat( eax, "_" )
        strcat( eax, edi )
        .if SymFind( eax )
            or [eax].asym.flag1,S_METHOD
        .endif
    .endif
    mov eax,retval
    ret

ProcType endp

ParseMacroArgs proc private uses esi edi ebx buffer:string_t, count:int_t, args:string_t

    ; :abs, name:ptr, x:abs=<val>, ...

    .for ( ebx = args, edi = buffer, esi = 1 : esi < count : esi++ )

        mov ebx,ltokstart(ebx)

        .if ( cl == ':' || !( _ltype[ecx+1] & _LABEL) )

            add edi,tsprintf( edi, "_%u, ", esi )
        .else

            .while is_valid_id_char( [ebx] )
                stosb
                inc ebx
            .endw
            mov eax,' ,'
            stosw
            mov byte ptr [edi],0
        .endif

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

    mov mac,0
    lea edi,mac
    mov ebx,ModuleInfo.tokenarray

    .if ( [ebx+16].tokval == T_PROTO )

        ; name proto [name1]:type, ... { ... }
        ; args: _1, _2, ...

        mov edx,count
        .if edx
            inc edx
            mov edi,ParseMacroArgs( edi, edx, &buf )
            sub edi,2
        .endif
        mov byte ptr [edi],0

    .else

        ; .static name this, [name1]:type, ... { ... }
        ; args: this, _1, _2, ...

        lea edi,[strcpy( edi, "this" ) + 4]
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

    mov esi,inline
    .while ( islspace( [esi] ) )
        inc esi
    .endw

    .for ( edi = 0 : strchr(esi, 10) : )

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

ClassDirective proc uses esi edi ebx i:int_t, tokenarray:token_t

   .new rc              : int_t = NOT_ERROR
   .new args            : token_t
   .new cmd             : uint_t
   .new constructor     : int_t = 0
   .new close_directive : int_t = 0 ; added v2.32.55
   .new is_id           : int_t
   .new is_vararg       : int_t
   .new context         : string_t
   .new class_ptr       : string_t
   .new vtable          : asym_t
   .new langtype        : int_t
   .new vector[2]       : ushort_t = 0
   .new class[256]      : char_t
   .new token[256]      : char_t
   .new name[512]       : char_t

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
                mov rc,asmerr( 1011 )
            .endif
            .return rc
        .endif
        .return asmerr( 1011 ) .if !esi

        mov close_directive,1 ; ComStack needs to be active in StructDirective()

        AddLineQueueX( "%s ends", [esi].asym.name )
        mov edx,[edi].com_item.publsym
        .if edx
            .if !strcmp([edi].com_item.class, [esi].asym.name)

                mov edx,[edi].com_item.publsym
                .if SymFind( strcat( strcpy( &class, [edx].asym.name ), "Vtbl" ) )

                    OpenVtbl(edi)
                    AddLineQueueX( "%sVtbl ends", [esi].asym.name )
                .endif
            .endif
        .endif
        .endc

      .case T_DOT_INLINE
      .case T_DOT_STATIC
      .case T_DOT_OPERATOR

        mov esi,ModuleInfo.ComStack
        mov ecx,CurrStruct
        .if ( !ecx || !esi )
            .return asmerr( 1011 )
        .endif
        mov [esi].com_item.method,eax
        mov langtype,[esi].com_item.langtype
        mov is_vararg,0

        mov ebx,get_param_name( &[ebx+edx+16], &token, &args, &is_id, &context, &langtype )
        .return .if eax == ERROR

        .if context ; { inline code }

            mov ecx,context
            mov context,NULL

            assume ecx:token_t

            .if ( [ecx].token == T_STRING && [ecx].bytval == '{' )

                .if ( [ecx-16].token == T_RES_ID && [ecx-16].tokval == T_VARARG )

                    inc is_vararg
                .endif

                mov context,[ecx].string_ptr
                mov eax,[ecx].tokpos
                mov byte ptr [eax],0

                .while ( byte ptr [eax-1] <= ' ' )

                    .break .if eax <= [ecx-asm_tok].tokpos
                    sub eax,1
                .endw
                mov byte ptr [eax],0
                mov [ecx].token,T_FINAL
            .endif
            assume ecx:nothing
        .elseif ( cmd == T_DOT_OPERATOR && Parse_Pass == PASS_1 )
            asmerr( 2008, [ebx].tokpos )
        .endif

        mov edi,strcpy( &name, &token )
        mov ecx,[esi].com_item.class
        mov class_ptr,ecx

        .if ( [esi].com_item.publsym )

            mov ecx,[esi].com_item.publsym
            mov ecx,[ecx].asym.name
        .endif

        mov vtable,SymFind( strcat( strcpy( &class, ecx ), "Vtbl" ) )
        .if ( eax == NULL )
            mov eax,CurrStruct
        .endif

        .if eax

            mov ecx,eax

            .if ( !SearchNameInStruct( ecx, edi, 0, 0 ) || !vtable )

                strcmp(edi, class_ptr) ; constructor ?

                .if ( eax && [esi].com_item.method != T_DOT_OPERATOR )

                    ClassProto( edi, langtype, [ebx].tokpos, T_PROC )

                .else

                    ClassProto2( class_ptr, edi, esi, [ebx].tokpos )
                    .if ( cmd != T_DOT_OPERATOR )
                        inc constructor
                    .endif
                .endif
            .endif
        .endif

        .endc .if ( context == 0 || Parse_Pass > PASS_1 )

        ; .operator + :type { ... }

        tsprintf( &token, "%s_%s", class_ptr, &name )

        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        RunLineQueue()

        .if constructor
            .if SymFind( &token )
                .if ( cmd != T_DOT_STATIC )
                    or [eax].asym.flag1,S_METHOD
                .endif
                .if ( cmd == T_DOT_STATIC && is_vararg == 0 )
                    or [eax].asym.flag2,S_ISSTATIC
                .endif
            .endif
        .elseif ( cmd == T_DOT_OPERATOR )
            mov eax,[esi].com_item.sym
            .if ( eax )
                or [eax].asym.flag2,S_OPERATOR
            .endif
        .endif
        MacroInline( &token, args, [ebx].tokpos , context, is_vararg )
        .if !constructor && ( cmd == T_DOT_STATIC && is_vararg == 0 )
            .if SymFind( &token )
                or [eax].asym.flag2,S_ISSTATIC
            .endif
        .endif
        .return rc

      .case T_DOT_COMDEF
      .case T_DOT_CLASS
      .case T_DOT_TEMPLATE

        .if ModuleInfo.ComStack
            .return asmerr( 1011 )
        .endif
        ;
        ; .template <vector[, type]> T
        ;
        lea ebx,[ebx+edx+16]
        .if ( [ebx].token == T_STRING )
            add ebx,16
            mov vector,[ebx].tokval
            mov vector[2],0
            add ebx,32
            .if ( [ebx-16].token == T_COMMA )
                mov vector[2],[ebx].tokval
                add ebx,32
            .endif
        .endif

        mov ModuleInfo.ComStack,LclAlloc( com_item )
        mov ecx,cmd
        xor edx,edx
        mov [eax].com_item.cmd,ecx
        mov [eax].com_item.langtype,edx
        mov [eax].com_item.publsym,edx
        mov [eax].com_item.method,edx
        mov [eax].com_item.sym,edx

        mov esi,NameSpace([ebx].string_ptr, NULL)
        mov ecx,ModuleInfo.ComStack
        mov [ecx].com_item.class,eax

        ; v2.32.20 - removed typedefs

        strcpy( edi, esi )

        add ebx,16
        .if ( [ebx].token == T_ID )

            mov eax,[ebx].string_ptr
            mov eax,[eax]
            or  al,0x20

            .if ( ax == 'c' )

                mov [ebx].token,T_RES_ID
                mov [ebx].tokval,T_CCALL
                mov [ebx].bytval,1
            .endif
        .endif

        mov edx,[ebx].tokval
        .if ( [ebx].token != T_FINAL && edx >= T_CCALL && edx <= T_WATCALL )

            mov ecx,ModuleInfo.ComStack
            mov [ecx].com_item.langtype,edx
            add ebx,16
        .endif

        .if ( [ebx].token == T_COLON )

            .if ( [ebx+16].token  == T_DIRECTIVE && [ebx+16].tokval == T_PUBLIC )

                mov ebx,[ebx+32].string_ptr
                .if !SymFind( ebx )
                    .return asmerr( 2006, ebx )
                .endif

                mov ecx,ModuleInfo.ComStack
                mov [ecx].com_item.publsym,eax
            .else
                asmerr( 2006, [ebx+16].string_ptr )
            .endif
        .endif

        .if ( cmd == T_DOT_CLASS )

            movzx eax,ModuleInfo.Ofssize
            shl eax,2
            mov cl,ModuleInfo.fieldalign
            mov edx,1
            shl edx,cl
            .if ( eax && edx < eax )
                AddLineQueueX( "%s struct %d", esi, eax )
            .else
                AddLineQueueX( "%s struct", esi )
            .endif
        .else
            AddLineQueueX( "%s struct", esi )
        .endif

        mov ecx,ModuleInfo.ComStack
        mov esi,[ecx].com_item.publsym
        .if esi
            .if ( cmd != T_DOT_TEMPLATE )
                .if !SearchNameInStruct( esi, "lpVtbl", 0, 0 )
                    AddLineQueueX( "lpVtbl ptr %sVtbl ?", &class )
                .endif
            .endif
            AddLineQueueX( "%s <>", [esi].asym.name )
        .elseif ( cmd != T_DOT_TEMPLATE )
            AddLineQueueX( "lpVtbl ptr %sVtbl ?", &class )
        .endif
    .endsw

    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    .if ( vector )
        mov ecx,ModuleInfo.ComStack
        mov esi,[ecx].com_item.sym
        .if ( esi )
            mov dword ptr [esi].asym.regist,dword ptr vector
        .endif
    .endif
    .if close_directive
        mov ModuleInfo.ComStack,0
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
