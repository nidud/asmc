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

ClassProto proc __ccall uses rsi rdi class:string_t, langtype:int_t, args:string_t, type:int_t

  local pargs[1024]:char_t

    lea rdi,pargs ; default args :abs=<val>
    mov rsi,args
    lea rcx,[rdi+1023]
    mov al,1

    .while ( al && rdi < rcx )
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


    assume rsi:ptr com_item

ClassProto2 proc __ccall uses rsi rdi rbx class:string_t, method:string_t,
        item:ptr com_item, args:string_t, this_ptr:string_t

  local name[256]:char_t
  local this[256]:char_t
  local buffer[512]:char_t

    mov rsi,item
    mov rdi,args
    mov rbx,this_ptr

    .if ( rbx == NULL )

        lea rbx,this
        tsprintf( rbx, "ptr %s", class )
    .endif
    tsprintf( &name, "%s_%s", class, method )
    .if ( [rsi].method != T_DOT_STATIC )
        .if ( byte ptr [rdi] )
            tsprintf( &buffer, ":%s, %s", rbx, rdi )
        .else
            tsprintf( &buffer, ":%s", rbx )
        .endif
        lea rdi,buffer
    .endif
    ClassProto( &name, [rsi].langtype, rdi, T_PROTO )
    ret

ClassProto2 endp


    assume rdi:ptr sfield

AddPublic proc __ccall uses rsi rdi rbx this:ptr com_item, sym:ptr asym

  local q[512]:char_t

    mov rsi,this
    mov rbx,sym

    .if ( [rbx].asym.total_size && Parse_Pass == 0 )

        .for ( rdx = [rbx].dsym.structinfo,
               rdi = [rdx].struct_info.head : rdi : rdi = [rdi].next )

            .if [rdi].type

                mov rdx,[rdi].type
                .if [rdx].asym.typekind == TYPE_STRUCT

                    AddPublic(rsi, rdx)
                .else

                    tstrcpy( &q, [rbx].asym.name )
                    mov ecx,[rbx].asym.name_size
                    mov word ptr [rax+rcx-4],'_'

                    .if SymFind( tstrcat( rax, [rdi].name ) )

                        mov rdx,[rax].asym.name
                        .if [rax].asym.state == SYM_TMACRO
                            mov rdx,[rax].asym.string_ptr
                        .endif
                        AddLineQueueX( "%s_%s equ <%s>", [rsi].class, [rdi].name, rdx )
                    .endif
                .endif
            .endif
        .endf
    .endif
    ret

AddPublic endp


OpenVtbl proc __ccall uses rsi rbx this:ptr com_item

  local q[512]:char_t

    mov rsi,this
    AddLineQueueX( "%sVtbl struct", [rsi].class )

    ; v2.30.32 - : public class

    mov rdx,[rsi].publsym
    .return 0 .if !rdx
    .return 1 .if !SymFind( tstrcat( tstrcpy( &q, [rdx].asym.name ), "Vtbl" ) )

    mov rbx,rax
    xor eax,eax
    .if [rbx].asym.total_size

        AddLineQueueX( "%s <>", &q )
        AddPublic(rsi, rbx)
        mov eax,1
    .endif
    ret

OpenVtbl endp

    assume rsi:nothing
    assume rdi:nothing

    assume rbx:ptr asm_tok

get_param_name proc __ccall uses rsi rdi rbx tokenarray:token_t, token:string_t,
        count:ptr int_t, isid:ptr int_t, context:ptr string_t, langtype:ptr int_t

   .new operator:byte = 0

    mov rdi,token
    mov rbx,tokenarray
    mov rsi,[rbx].tokpos
    xor eax,eax
    mov rcx,context
    mov [rcx],rax
    mov rcx,isid
    mov [rcx],eax

    .ifd ( GetOpType( rbx, rdi ) == ERROR )

        .if ( [rbx].token != T_ID )
            .return asmerr( 1011 )
        .endif
        tstrcpy( rdi, [rbx].string_ptr )
        mov rcx,isid
        inc dword ptr [rcx]
        add rbx,asm_tok
    .else
        mov rbx,rax
        inc operator
    .endif

    .if ( [rbx].token == T_RES_ID ) ; fastcall...

        mov rcx,langtype
        mov eax,[rbx].tokval
        mov [rcx],eax
        add rbx,asm_tok
    .endif

    mov rdi,rbx
    .for ( esi = 1 : [rbx].token != T_FINAL : rbx += asm_tok )

        .if ( [rbx].token == T_STRING && [rbx].bytval == '{' )

            mov rcx,context
            mov [rcx],rbx
            .break

        .elseif ( [rbx].token == T_COLON )

            inc esi
            .if ( operator )
                OperatorParam( &[rbx+asm_tok], token )
            .endif
        .endif
    .endf
    mov rcx,count
    mov [rcx],esi
   .return rdi

get_param_name endp


    option proc: public


ProcType proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

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

    imul ebx,i,asm_tok
    add rbx,tokenarray
    mov constructor,0
    mov langtype,0
    mov name,[rbx-asm_tok].string_ptr
    mov retval,NOT_ERROR
    mov rsi,ModuleInfo.ComStack

    .if ( rsi )

        mov langtype,[rsi].com_item.langtype
        mov rdi,NameSpace( name, name )

        .if ( tstrcmp( rdi, [rsi].com_item.class ) == 0 )

            ClassProto2( rdi, rdi, rsi, [rbx+asm_tok].tokpos, NULL )
            mov constructor,1
            jmp done
        .endif
    .endif

    mov IsCom,0

    mov rax,CurrStruct
    .if rax
        mov rdi,[rax].asym.name
        .if tstrlen(rdi) > 4
            mov eax,[rdi+rax-4]
        .endif
    .endif

    mov rdi,buffer

    .if ( eax == "lbtV" )

        inc IsCom

    .elseif rsi

        .if ( Token_Count > 2 && [rbx+asm_tok].tokval == T_LOCAL )

            add rbx,asm_tok

        .else

            AddLineQueueX( "%s ends", [rsi].com_item.class )
            mov retval,OpenVtbl(rsi)
            inc IsCom
        .endif
    .endif

    inc ModuleInfo.class_label

    tsprintf( &T$, "T$%04X", ModuleInfo.class_label )
    tsprintf( &P$, "P$%04X", ModuleInfo.class_label )

    tstrcat( tstrcpy( rdi, &T$ ), " typedef proto" )

    .if ( rsi && [rsi].com_item.cmd == T_DOT_COMDEF )

        .if ( ModuleInfo.Ofssize == USE32 && ModuleInfo.langtype != LANG_STDCALL )

            tstrcat(rdi, " stdcall")
        .endif
    .endif

    add rbx,asm_tok
    xor esi,esi

    .if ( [rbx].token != T_FINAL )

        .if ( IsCom )

            .if ( [rbx].tokval >= T_CCALL && [rbx].tokval <= T_WATCALL )

                inc esi
            .endif

            .if ( [rbx+asm_tok].token == T_FINAL || esi || \
                ( [rbx].token != T_COLON && [rbx+asm_tok].token != T_COLON ) )

                tstrcat(rdi, " ")
                tstrcat(rdi, [rbx].string_ptr)
                add rbx,asm_tok

            .elseif !esi && langtype

                GetResWName(langtype, &language)
                tstrcat(rdi, " ")
                tstrcat(rdi, &language)
            .endif
            xor esi,esi
        .endif

        .for ( rax = rbx : [rax].asm_tok.token != T_FINAL : rax += asm_tok )

            .if ( [rax].asm_tok.token == T_COLON )

                inc esi
                .break
            .endif
        .endf

    .elseif ( IsCom && ModuleInfo.ComStack )

        mov rax,ModuleInfo.ComStack
        mov ecx,[rax].com_item.langtype
        .if ecx

            GetResWName(ecx, &language)
            tstrcat(rdi, " ")
            tstrcat(rdi, &language)
        .endif
    .endif


    mov rax,ModuleInfo.ComStack
    .if ( rax )
        .if ( [rax].com_item.method != T_DOT_STATIC )

            xor eax,eax
        .endif
    .endif

    .if ( IsCom && !rax )

        tstrcat(rdi, " :ptr")
        mov rax,ModuleInfo.ComStack
        .if ( rax )

            .if ( [rax].com_item.cmd == T_DOT_CLASS )

                tstrcat(rdi, " ")
                mov rax,ModuleInfo.ComStack
                tstrcat(rdi, [rax].com_item.class)
            .endif
        .endif

        .if rsi
            tstrcat(rdi, ",")
        .endif
    .endif
    .if rsi
        tstrcat(rdi, " ")
        tstrcat(rdi, [rbx].tokpos)
    .endif

    AddLineQueue( rdi )
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

        tstrcpy( buffer, rdi )
        tstrcat( rax, "_" )
        tstrcat( rax, rdi )
        .if SymFind( rax )
            or [rax].asym.flags,S_METHOD
        .endif
    .endif
    mov eax,retval
    ret

ProcType endp


ParseMacroArgs proc __ccall private uses rsi rdi rbx buffer:string_t, count:int_t, args:string_t

    ; :abs, name:ptr, x:abs=<val>, ...

    .for ( rbx = args, rdi = buffer, esi = 1 : esi < count : esi++ )

        mov rbx,ltokstart(rbx)
        .if ( !islabel( ecx ) )

            add rdi,tsprintf( rdi, "_%u, ", esi )
        .else

            .while islabel( [rbx] )
                stosb
                inc rbx
            .endw
            mov eax,' ,'
            stosw
            mov byte ptr [rdi],0
        .endif

        .if tstrchr(rbx, ',')
            inc rax
        .else
            tstrlen(rbx)
            add rax,rbx
        .endif
        xchg rbx,rax

        .if tstrchr(rax, '=')

            .if rax < rbx

                dec rdi
                mov byte ptr [rdi-1],':'
                mov rcx,rbx
                sub rcx,rax
                .if byte ptr [rbx-1] == ','
                    dec ecx
                .endif
                mov rdx,rsi
                mov rsi,rax
                rep movsb
                mov rsi,rdx
                mov dword ptr [rdi],' ,'
                add rdi,2
            .endif
        .endif
    .endf
    mov rax,rdi
    ret

ParseMacroArgs endp


MacroInline proc __ccall uses rsi rdi rbx name:string_t, count:int_t, args:string_t, inline:string_t, vargs:int_t

  local buf[512]:char_t
  local mac[512]:char_t
  local index:int_t

    .return 0 .if ( Parse_Pass > PASS_1 )

    tstrcpy( &buf, args )

    mov mac,0
    lea rdi,mac
    mov rbx,ModuleInfo.tokenarray

    .if ( [rbx+asm_tok].tokval == T_PROTO )

        ; name proto [name1]:type, ... { ... }
        ; args: _1, _2, ...

        mov edx,count
        .if edx
            inc edx
            mov rdi,ParseMacroArgs( rdi, edx, &buf )
            sub rdi,2
        .endif
        mov byte ptr [rdi],0

    .else

        ; .static name this, [name1]:type, ... { ... }
        ; args: this, _1, _2, ...

        lea rdi,[tstrcpy( rdi, "this" ) + 4]
        .if count > 1
            lea rdi,[tstrcpy(rdi, ", ") + 2]
            mov rdi,ParseMacroArgs( rdi, count, &buf )
            sub rdi,2
            mov byte ptr [rdi],0
        .endif
    .endif

    .if vargs

        tstrcpy( rdi, ":vararg" )
    .endif

    AddLineQueueX( "%s macro %s", name, &mac )

    mov rsi,inline
    .while ( islspace( [rsi] ) )
        inc rsi
    .endw

    .for ( rdi = 0 : tstrchr(rsi, 10) : )

        mov rbx,rax
        mov byte ptr [rbx],0
        .if byte ptr [rsi]
            mov rdi,rsi
            AddLineQueue(rsi)
        .endif
        mov byte ptr [rbx],10
        lea rsi,[rbx+1]
    .endf
    .if byte ptr [rsi]
        mov rdi,rsi
        AddLineQueue(rsi)
    .endif

    .if rdi == 0
        AddLineQueue( "exitm<>" )
    .else
        .ifd tmemicmp( rdi, "exitm", 5 )
            tmemicmp( rdi, "retm", 4 )
        .endif
        .if eax
            AddLineQueue( "exitm<>" )
        .endif
    .endif
    AddLineQueue( "endm" )
    MacroLineQueue()
    ret

MacroInline endp


ClassDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new rc              : int_t = NOT_ERROR
   .new args            : int_t
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
   .new token[512]      : char_t
   .new name[512]       : char_t
   .new this[256]       : char_t
   .new this_ptr        : string_t

    mov rbx,tokenarray
    lea rdi,class

    imul edx,i,asm_tok
    mov eax,[rbx+rdx].tokval
    mov cmd,eax
    inc i

    .switch eax
      .case T_DOT_ENDS
        mov rdi,ModuleInfo.ComStack
        mov rsi,CurrStruct
        .if !rdi
            .if rsi
                mov rc,asmerr( 1011 )
            .endif
            .return rc
        .endif
        .return asmerr( 1011 ) .if !rsi

        mov close_directive,1 ; ComStack needs to be active in StructDirective()

        AddLineQueueX( "%s ends", [rsi].asym.name )
        mov rdx,[rdi].com_item.publsym
        .if rdx
            .if !tstrcmp([rdi].com_item.class, [rsi].asym.name)

                mov rdx,[rdi].com_item.publsym
                .if SymFind( tstrcat( tstrcpy( &class, [rdx].asym.name ), "Vtbl" ) )

                    OpenVtbl(rdi)
                    AddLineQueueX( "%sVtbl ends", [rsi].asym.name )
                .endif
            .endif
        .endif
        .endc

      .case T_DOT_INLINE
      .case T_DOT_STATIC
      .case T_DOT_OPERATOR

        mov this_ptr,NULL
        mov rsi,ModuleInfo.ComStack
        mov rcx,CurrStruct
        .if ( !rcx || !rsi )
            .return asmerr( 1011 )
        .endif
        mov [rsi].com_item.method,eax
        mov rax,[rsi].com_item.sym
        lea rbx,[rbx+rdx+asm_tok]
        .if ( rax == NULL )
            SymFind( [rsi].com_item.class )
        .endif
        .if ( rax )
            movzx eax,[rax].asym.regist[2]
        .endif
        .if ( eax )
            tsprintf( &this, "%r", eax )
            mov this_ptr,&this
        .endif

        mov langtype,[rsi].com_item.langtype
        mov is_vararg,0

        .if ( [rbx].token == T_STRING )
            .if ( GetOperator(rbx) == 0 )
                mov this_ptr,[rbx].string_ptr
                add rbx,asm_tok
            .endif
        .endif

        mov rbx,get_param_name( rbx, &token, &args, &is_id, &context, &langtype )
        .return .if eax == ERROR

        .if context ; { inline code }

            mov rcx,context
            mov context,NULL

            assume rcx:token_t

            .if ( [rcx].token == T_STRING && [rcx].bytval == '{' )

                .if ( [rcx-asm_tok].token == T_RES_ID && [rcx-asm_tok].tokval == T_VARARG )

                    inc is_vararg
                .endif

                mov context,[rcx].string_ptr
                mov rax,[rcx].tokpos
                mov byte ptr [rax],0

                .while ( byte ptr [rax-1] <= ' ' )

                    .break .if rax <= [rcx-asm_tok].tokpos
                    sub rax,1
                .endw
                mov byte ptr [rax],0
                mov [rcx].token,T_FINAL
            .endif
            assume rcx:nothing
        .elseif ( cmd == T_DOT_OPERATOR && Parse_Pass == PASS_1 )
            asmerr( 2008, [rbx].tokpos )
        .endif

        mov rdi,tstrcpy( &name, &token )
        mov rcx,[rsi].com_item.class
        mov class_ptr,rcx

        .if ( [rsi].com_item.publsym )

            mov rcx,[rsi].com_item.publsym
            mov rcx,[rcx].asym.name
        .endif

        mov vtable,SymFind( tstrcat( tstrcpy( &class, rcx ), "Vtbl" ) )
        .if ( rax == NULL )
            mov rax,CurrStruct
        .endif

        .if rax

            mov rcx,rax

            .if ( !SearchNameInStruct( rcx, rdi, 0, 0 ) || !vtable )

                tstrcmp(rdi, class_ptr) ; constructor ?

                .if ( rax && [rsi].com_item.method != T_DOT_OPERATOR )

                    ClassProto( rdi, langtype, [rbx].tokpos, T_PROC )

                .else

                    ClassProto2( class_ptr, rdi, rsi, [rbx].tokpos, this_ptr )
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
                    or [rax].asym.flags,S_METHOD
                .endif
                .if ( cmd == T_DOT_STATIC && is_vararg == 0 )
                    or [rax].asym.flags,S_ISSTATIC
                .endif
            .endif
        .elseif ( cmd == T_DOT_OPERATOR )
            mov rax,[rsi].com_item.sym
            .if ( rax )
                or [rax].asym.flags,S_OPERATOR
            .endif
        .endif
        MacroInline( &token, args, [rbx].tokpos , context, is_vararg )
        .if !constructor && ( cmd == T_DOT_STATIC && is_vararg == 0 )
            .if SymFind( &token )
                or [rax].asym.flags,S_ISSTATIC
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
        lea rbx,[rbx+rdx+asm_tok]
        .if ( [rbx].token == T_STRING )
            mov vector,[rbx+asm_tok].tokval
            .if ( [rbx+2*asm_tok].token != T_COMMA )
                .return asmerr( 2065, "," )
            .endif
            mov vector[2],[rbx+3*asm_tok].tokval
            add rbx,5*asm_tok
        .endif

        mov ModuleInfo.ComStack,LclAlloc( com_item )
        mov ecx,cmd
        xor edx,edx
        mov [rax].com_item.cmd,ecx
        mov [rax].com_item.langtype,edx
        mov [rax].com_item.publsym,rdx
        mov [rax].com_item.method,edx
        mov [rax].com_item.sym,rdx

        mov rsi,NameSpace([rbx].string_ptr, NULL)
        mov rcx,ModuleInfo.ComStack
        mov [rcx].com_item.class,rax

        ; v2.32.20 - removed typedefs

        tstrcpy( rdi, rsi )

        add rbx,asm_tok
        .if ( [rbx].token == T_ID )

            mov rax,[rbx].string_ptr
            mov eax,[rax]
            or  al,0x20

            .if ( ax == 'c' )

                mov [rbx].token,T_RES_ID
                mov [rbx].tokval,T_CCALL
                mov [rbx].bytval,1
            .endif
        .endif

        mov edx,[rbx].tokval
        .if ( [rbx].token != T_FINAL && edx >= T_CCALL && edx <= T_WATCALL )

            mov rcx,ModuleInfo.ComStack
            mov [rcx].com_item.langtype,edx
            add rbx,asm_tok
        .endif

        .if ( [rbx].token == T_COLON )

            .if ( [rbx+asm_tok].token  == T_DIRECTIVE && [rbx+asm_tok].tokval == T_PUBLIC )

                mov rbx,[rbx+asm_tok*2].string_ptr
                .if !SymFind( rbx )
                    .return asmerr( 2006, rbx )
                .endif

                mov rcx,ModuleInfo.ComStack
                mov [rcx].com_item.publsym,rax
            .else
                asmerr( 2006, [rbx+asm_tok].string_ptr )
            .endif
        .endif

        .if ( cmd == T_DOT_CLASS )

            movzx eax,ModuleInfo.Ofssize
            shl eax,2
            mov cl,ModuleInfo.fieldalign
            mov edx,1
            shl edx,cl
            .if ( eax && edx < eax )
                AddLineQueueX( "%s struct %d", rsi, eax )
            .else
                AddLineQueueX( "%s struct", rsi )
            .endif
        .else
            AddLineQueueX( "%s struct", rsi )
        .endif

        mov rcx,ModuleInfo.ComStack
        mov rsi,[rcx].com_item.publsym
        .if rsi
            .if ( cmd != T_DOT_TEMPLATE )
                .if !SearchNameInStruct( rsi, "lpVtbl", 0, 0 )
                    AddLineQueueX( "lpVtbl ptr %sVtbl ?", &class )
                .endif
            .endif
            AddLineQueueX( "%s <>", [rsi].asym.name )
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
        mov rcx,ModuleInfo.ComStack
        mov rsi,[rcx].com_item.sym
        .if ( rsi )
            movzx eax,vector
            movzx ecx,vector[2]
            mov [rsi].asym.regist[0],ax
            mov [rsi].asym.regist[2],cx
            or  [rsi].asym.sflags,S_ISVECTOR
        .endif
    .endif
    .if close_directive
        mov ModuleInfo.ComStack,0
    .endif
    mov eax,rc
    ret

ClassDirective endp

ClassInit proc __ccall

    mov ModuleInfo.class_label,0 ; init class label counter
    ret

ClassInit endp

ClassCheckOpen proc __ccall

    .if ModuleInfo.ComStack

        asmerr( 1010, ".comdef-.classdef-.ends" )
    .endif
    ret

ClassCheckOpen endp

    END
