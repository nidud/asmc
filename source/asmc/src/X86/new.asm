include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include expreval.inc
include atofloat.inc

SIZE_DATAPTR    equ 0x68

SymLCreate      proto :string_t
GetQualifiedType proto :ptr int_t, :tok_t, :ptr qualified_type
SetLocalOffsets proto :proc_t

qualified_type  struc
size            int_t ?
symtype         asym_t ?
mem_type        db ?
is_ptr          db ?
is_far          db ?
Ofssize         db ?
ptr_memtype     db ?
qualified_type  ends

.enum ClType { ClNew, ClMem, ClPtr }

    .code

    assume ebx:tok_t

ConstructorCall proc private uses esi edi ebx \
        name    : string_t,         ; id name
        endtok  : ptr ptr asm_tok,  ; past ')' of call
        argtok  : ptr asm_tok,      ; past '(' of call
        class   : string_t,         ; class name
        type    : string_t          ; name:<type>

  local acc     : int_t,
        reg     : int_t,
        cltype  : ClType,
        cc[256] : char_t            ; class_class

    mov esi,strcat( strcat( strcpy( &cc, class ), "_" ), class )

    SymFind(esi)

    .if Parse_Pass > PASS_1 && eax

        .if [eax].asym.state == SYM_UNDEFINED

            ; x::x proto
            ;
            ; undef x_x
            ; x_x macro this

            mov [eax].asym.state,SYM_MACRO
        .endif
    .endif

    xor ecx,ecx
    mov reg,ecx

    .if eax && [eax].asym.state == SYM_MACRO

        mov ecx,T_ECX
        mov reg,T_ECX

        .if ModuleInfo.Ofssize == USE64

            mov ecx,T_EDI
            mov reg,T_RDI

            .if [eax].asym.langtype != LANG_SYSCALL

                mov ecx,T_ECX
                mov reg,T_RCX
            .endif
        .endif
    .endif

    xor eax,eax
    mov ebx,argtok

    mov edx,ClNew
    .if [ebx-16].token == T_COLON
        mov edx,ClMem
    .elseif type
        mov edx,ClPtr
    .endif
    mov cltype,edx

    .if [ebx-16].token != T_COLON

        inc eax
        .if type == NULL

            inc eax
        .endif
    .endif

    mov edi,[ebx+32].tokpos
    mov edx,endtok
    mov ebx,[edx]
    .if [ebx-32].token != T_OP_BRACKET
        add eax,3
        mov ebx,[ebx-16].tokpos
        mov byte ptr [ebx],0
    .else
        xor ebx,ebx
    .endif
    mov edx,name

    .if ecx
        push eax
        .switch eax
        .case 0, 3
            AddLineQueueX( " %r %r, %s", T_LEA, reg, edx )
            .endc
        .case 1, 2, 4, 5
            AddLineQueueX( " %r %r, %r", T_XOR, ecx, ecx )
        .endsw
        pop eax
        mov edx,name
        mov ecx,reg
        .switch pascal eax
        .case 0 : AddLineQueueX( " %s(%r)",          esi, ecx )
        .case 1 : AddLineQueueX( " %r %s,%s(%r)",    T_MOV, edx, esi, ecx )
        .case 2 : AddLineQueueX( " %s(%r)",          esi, ecx )
        .case 3 : AddLineQueueX( " %s(%r,%s)",       esi, ecx, edi )
        .case 4 : AddLineQueueX( " %r %s,%s(%r,%s)", T_MOV, edx, esi, ecx, edi )
        .case 5 : AddLineQueueX( " %s(%r,%s)",       esi, ecx, edi )
        .endsw
    .else
        .switch pascal eax
        .case 0 : AddLineQueueX( " %s(&%s)",         esi, edx )
        .case 1 : AddLineQueueX( " %r %s,%s(0)",     T_MOV, edx, esi )
        .case 2 : AddLineQueueX( " %s(0)",           esi )
        .case 3 : AddLineQueueX( " %s(&%s,%s)",      esi, edx, edi )
        .case 4 : AddLineQueueX( " %r %s,%s(0,%s)",  T_MOV, edx, esi, edi )
        .case 5 : AddLineQueueX( " %s(0,%s)",        esi, edi )
        .endsw
    .endif

    .if ebx
        mov byte ptr [ebx],')'
    .endif
    mov edx,endtok
    mov ebx,[edx]

    ; added 2.31.44

    .if [ebx].token == T_COLON ; Class() : member(value) [ , member(value) ]

        add ebx,16
        mov acc,T_EAX
        .if ModuleInfo.Ofssize == USE64
            mov acc,T_RAX
        .endif
        .if reg
            mov acc,reg
        .endif
        .while [ebx].token == T_ID && [ebx+16].token == T_OP_BRACKET

            mov edx,[ebx].string_ptr
            add ebx,32
            mov edi,[ebx].tokpos

            .for eax = 1 : [ebx].token != T_FINAL : ebx += 16
                .if [ebx].token == T_OP_BRACKET
                    inc eax
                .elseif [ebx].token == T_CL_BRACKET
                    dec eax
                    .break .ifz
                .endif
            .endf
            .if [ebx].token != T_CL_BRACKET

                .return asmerr( 2008, [ebx].string_ptr )
            .endif

            mov esi,[ebx].tokpos
            mov byte ptr [esi],0

            .if cltype == ClMem
                AddLineQueueX( " %r %s.%s, %s", T_MOV, name, edx, edi )
            .else
                AddLineQueueX( " %r [%r].%s.%s, %s", T_MOV, acc, class, edx, edi )
            .endif
            mov byte ptr [esi],')'
            add ebx,16
            .if [ebx].token == T_COMMA
                add ebx,16
            .endif
        .endw
        mov edx,endtok
        mov [edx],ebx
    .endif
    ret

ConstructorCall endp

; case = {0,2,..}

    assume ebx:nothing

AssignString proc private uses esi edi ebx name:string_t, fp:ptr sfield, string:string_t

  local i:int_t
  local opndx:expr

    mov edx,fp
    mov ebx,[edx].sfield.sym.total_size
    mov edi,[edx].sfield.sym.name

    .repeat

        .break .if ebx <= 4

        imul esi,Token_Count,asm_tok
        add  esi,16
        add  esi,ModuleInfo.tokenarray
        mov  edx,Tokenize( string, 0, esi, TOK_DEFAULT )
        mov  i,0
        .break .if EvalOperand( &i, esi, edx, &opndx, 0 ) == ERROR

       .if opndx.kind == EXPR_FLOAT
            mov opndx.kind,EXPR_CONST
            .if ebx != 16
                quad_resize(&opndx, ebx)
            .endif
        .endif
        .break .if opndx.kind != EXPR_CONST
        .break .if ebx == 8 && opndx.l64_h == 0 && ModuleInfo.Ofssize == USE64
        .switch ebx
        .case 16
            AddLineQueueX( " %r %r %r %s.%s[12], 0x%x", T_MOV, T_DWORD, T_PTR,
                name, edi, opndx.h64_h )
            AddLineQueueX( " %r %r %r %s.%s[8], 0x%x", T_MOV, T_DWORD, T_PTR,
                name, edi, opndx.h64_l )
        .case 10
            .if ebx == 10
                AddLineQueueX( " %r %r %r %s.%s[8], 0x%x", T_MOV, T_WORD, T_PTR,
                    name, edi, opndx.h64_l )
            .endif
        .case 8
            AddLineQueueX( " %r %r %r %s.%s[4], 0x%x", T_MOV, T_DWORD, T_PTR,
                name, edi, opndx.l64_h )
            AddLineQueueX( " %r %r %r %s.%s[0], 0x%x", T_MOV, T_DWORD, T_PTR,
                name, edi, opndx.l64_l )
            .return
        .endsw
    .until 1
    AddLineQueueX( " %r %s.%s, %s", T_MOV, name, edi, string )
    ret

AssignString endp

AssignStruct proc private uses esi edi ebx name:string_t, sym:asym_t, string:string_t

  local val[256]:char_t, array:int_t

    mov array,0
    mov esi,string
    inc esi
    mov eax,sym
    .if eax

        .while [eax].asym.state == SYM_TYPE && [eax].asym.type

            .break .if eax == [eax].asym.type
            mov eax,[eax].asym.type
        .endw

        mov ecx,[eax].esym.structinfo
        mov ebx,[ecx].struct_info.head
    .else
        inc array
    .endif

    .while 1

        lodsb
        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .break .if al == '}'

        dec esi
        .break .if !al

        lea edi,val
        .if byte ptr [esi] == '{'

            strcpy( edi, name )
            mov ecx,[ebx].sfield.sym.name
            .if byte ptr [ecx]
                strcat( edi, "." )
                strcat( edi, [ebx].sfield.sym.name )
            .endif
            mov esi,AssignStruct( edi, [ebx].sfield.sym.type, esi )

            .break .if !eax
            .while byte ptr [esi] == ' ' || byte ptr [esi] == 9

                add esi,1
            .endw

        .else

            xor eax,eax
            mov [edi],al
            lea ecx,[edi+255]

            .while edi < ecx

                mov al,[esi]
                .switch al
                .case 0
                    .break
                .case ','
                .case '}'
                    .break .if !ah
                    .endc
                .case '('
                    inc ah
                    .endc
                .case ')'
                    dec ah
                    .endc
                .endsw
                movsb
            .endw
            mov byte ptr [edi],0

            .for ( ecx=&val : ecx < edi && \
                 ( byte ptr [edi-1] == ' ' || byte ptr [edi-1] == 9 ) : )

                dec edi
                mov byte ptr [edi],0
            .endf

            .if !array && val && val != '{' && [ebx].sfield.sym.flag & S_ISARRAY

                .if SymSearch( &val )

                    .if [eax].asym.state == SYM_TMACRO

                        mov ecx,[eax].asym.string_ptr
                        .if byte ptr [ecx] == '{'

                            mov     edx,eax
                            xor     eax,eax
                            mov     edi,esi
                            mov     ecx,-1
                            repne   scasb
                            not     ecx

                            mov     edi,[edx].asym.total_size
                            lea     eax,[edi+ecx+3]
                            and     eax,-4
                            sub     esp,eax
                            mov     eax,ecx
                            lea     ecx,[edi-1]
                            mov     edi,esp
                            mov     edx,[edx].asym.string_ptr
                            xchg    edx,esi
                            rep     movsb
                            mov     esi,edx
                            mov     ecx,eax
                            rep     movsb
                            mov     esi,esp

                           .continue(0)
                        .endif
                    .endif
                .endif
            .endif

            .if val
                .if val == '"' || ( val == 'L' &&  val[1] == '"')
                    AddLineQueueX( " %r %s.%s, &@CStr(%s)", T_MOV, name, [ebx].sfield.sym.name, &val )
                .elseif array
                    mov eax,[ebx].sfield.sym.total_size
                    xor edx,edx
                    div [ebx].sfield.sym.total_length
                    mov ecx,array
                    dec ecx
                    mul ecx
                    mov ecx,eax
                    AddLineQueueX( " %r %s[%d], %s", T_MOV, name, ecx, &val )
                .else
                    AssignString( name, ebx, &val )
                    ;AddLineQueueX( " %r %s.%s, %s", T_MOV, name, [ebx].sfield.sym.name, &val )
                .endif
            .endif
        .endif

        .break .if byte ptr [esi] == 0
        lodsb
        .break .if al != ',' ; == '}'
        .if array
            inc array
        .else
            mov ebx,[ebx].sfield.next
        .endif
        .break .if !ebx
    .endw
    mov eax,esi
    ret

AssignStruct endp

; case = {...},{...},

AssignId proc private uses esi edi ebx name:string_t, sym:asym_t, type:asym_t, string:string_t

  local Id[128]:char_t, size:int_t, f:sfield

    .if !type
        mov esi,sym
        lea edi,f.sym
        mov ecx,asym
        rep movsb
        mov f.next,NULL
        lea ebx,f
        .return AssignStruct( name, NULL, string )
    .endif

    mov edi,sym
    .if !( [edi].asym.flag & S_ISARRAY )

        .return AssignStruct( name, type, string )
    .endif

    mov esi,string
    inc esi
    .while byte ptr [esi] == ' ' || byte ptr [esi] == 9
        add esi,1
    .endw

    mov eax,[edi].asym.total_size
    mov ebx,[edi].asym.total_length
    xor edx,edx
    div ebx
    mov size,eax
    xor edi,edi

    .for ( : ebx : ebx--, edi += size )

        LSPrintF( &Id, "%s[%d]", name, edi )
        mov esi,AssignStruct( &Id, type, esi )
        lodsb
        .break .if !al
        .repeat
            lodsb
            .continue(0) .if al == ' '
            .continue(0) .if al == 9
            dec esi
        .until 1
        .break .if al != '{'
    .endf
    mov eax,esi
    ret

AssignId endp

    assume ebx:tok_t

; case = {0}

ClearStruct proc private uses esi edi ebx name:string_t, sym:asym_t

    AddLineQueueX( " %r %r, %r", T_XOR, T_EAX, T_EAX )
    mov esi,sym
    mov edi,[esi].asym.total_size
    .if ModuleInfo.Ofssize == USE64

        .if edi > 32

            AddLineQueueX( " %r %r", T_PUSH, T_RDI )
            AddLineQueueX( " %r %r", T_PUSH, T_RCX )
            AddLineQueueX( " %r %r, %s", T_LEA, T_RDI, name )
            AddLineQueueX( " %r %r, %d", T_MOV, T_ECX, edi )
            AddLineQueueX( " %r %r", T_REP, T_STOSB )
            AddLineQueueX( " %r %r", T_POP, T_RCX )
            AddLineQueueX( " %r %r", T_POP, T_RDI )

        .else

            .for ( ebx = 0 : edi >= 8 : edi -= 8, ebx += 8 )

                AddLineQueueX( " %r %r %r %s[%d], %r", T_MOV, T_QWORD, T_PTR, name, ebx, T_RAX )
            .endf

            .for ( : edi : edi--, ebx++ )

                AddLineQueueX( " %r %r %r %s[%d], %r", T_MOV, T_BYTE, T_PTR, name, ebx, T_AL )
            .endf
        .endif

    .elseif edi > 16

        AddLineQueueX( " %r %r", T_PUSH, T_EDI )
        AddLineQueueX( " %r %r", T_PUSH, T_ECX )
        AddLineQueueX( " %r %r, %s", T_LEA, T_EDI, name )
        AddLineQueueX( " %r %r, %d", T_MOV, T_ECX, edi )
        AddLineQueueX( " %r %r", T_REP, T_STOSB )
        AddLineQueueX( " %r %r", T_POP, T_ECX )
        AddLineQueueX( " %r %r", T_POP, T_EDI )

    .else

        .for ( ebx = 0 : edi >= 4 : edi -= 4, ebx += 4 )

            AddLineQueueX( " %r %r %r %s[%d], %r", T_MOV, T_DWORD, T_PTR, name, ebx, T_EAX )
        .endf

        .for ( : edi : edi--, ebx++ )

            AddLineQueueX( " %r %r %r %s[%d], %r", T_MOV, T_BYTE, T_PTR, name, ebx, T_AL )
        .endf
    .endif
    ret

ClearStruct endp

AssignValue proc private uses esi edi ebx name:string_t, i:int_t,
        tokenarray:tok_t, ti:ptr qualified_type

  local cc[256]:char_t
  local l2[256]:char_t
  local flag:byte
  local opndx:expr

    inc i
    imul ebx,i,asm_tok
    add  ebx,tokenarray

    mov flag,[ebx].hll_flags
    mov l2,0

    .if [ebx].token == T_STRING && [ebx].bytval == '{'

        SymSearch( name )
        .return asmerr( 2008, [ebx].tokpos ) .if !eax

        xor edx,edx
        mov ecx,[ebx].string_ptr
        .while byte ptr [ecx] == ' ' || byte ptr [ecx] == 9
            add ecx,1
        .endw
        .if ( byte ptr [ecx] == '0' )

            add ecx,1
            .while byte ptr [ecx] == ' ' || byte ptr [ecx] == 9
                add ecx,1
            .endw
            .if byte ptr [ecx] == 0
                inc edx
            .endif
        .endif
        .if edx
            ClearStruct( name, eax )
        .else
            AssignId( name, eax, [eax].asym.type, [ebx].tokpos )
        .endif
        lea eax,[ebx+16]
        .return
    .endif

    ; .new q:qword = foo()

    mov edi,strcpy( &cc, " mov " )

    mov ecx,ti

    .if [ecx].qualified_type.size == 8 && [ecx].qualified_type.Ofssize == USE32

        .if flag & T_HLL_PROC && \
            ( [ecx].qualified_type.mem_type == MT_QWORD || \
              [ecx].qualified_type.mem_type == MT_SQWORD )

            strcat( edi, "dword ptr " )
            strcpy( &l2, "mov dword ptr " )
            strcat( strcat( eax, name ), "[4], edx" )

        .elseif EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) != ERROR

            .if opndx.kind == EXPR_CONST

                AddLineQueueX( " %r %r %r %s[0], %u", T_MOV, T_DWORD, T_PTR, name, opndx.l64_l )
                AddLineQueueX( " %r %r %r %s[4], %u", T_MOV, T_DWORD, T_PTR, name, opndx.l64_h )
                imul eax,i,asm_tok
                add  eax,tokenarray
                .return
            .endif
        .endif
    .endif

    strcat( strcat( edi, name ), ", " )
    xor esi,esi

    .while 1
        .switch [ebx].token
        .case T_FINAL
            .break
        .case T_COMMA
            .break .if !esi
            .endc
        .case T_OP_BRACKET
            inc esi
            .endc
        .case T_CL_BRACKET
            dec esi
            .endc
        .endsw
        .if ( [ebx].token == T_INSTRUCTION )
            strcat(edi, " ")
        .endif
        .if ( !esi && [ebx].token == T_STRING && [ebx].bytval == '"' )
            .if SymSearch( name )
                .if ( [eax].asym.mem_type & MT_PTR )
                    strcat(edi, "&@CStr(")
                    strcat(edi, [ebx].string_ptr)
                    strcat(edi, ")")
                    add ebx,16
                    .break
                .endif
            .endif
        .endif
        strcat(edi, [ebx].string_ptr)
        .if ( [ebx].token == T_INSTRUCTION ) || \
            ( [ebx].token == T_RES_ID && [ebx].tokval == T_ADDR )
            strcat(edi, " ")
        .endif
        add ebx,16
    .endw
    .if esi
        asmerr( 2157 )
    .endif
    AddLineQueueX( edi )
    .if l2
        AddLineQueueX( &l2 )
    .endif
    mov eax,ebx
    ret

AssignValue endp

AddLocalDir proc private uses esi edi ebx i:int_t, tokenarray:tok_t

  local name  : string_t,
        type  : string_t,
        sym   : dsym_t,
        creat : int_t,
        ti    : qualified_type,
        opndx : expr,
        endtok: tok_t

    inc  i  ; go past directive
    imul ebx,i,asm_tok
    add  ebx,tokenarray

    .while 1

        .if [ebx].token != T_ID

            .return asmerr( 2008, [ebx].string_ptr )
        .endif

        mov name,[ebx].string_ptr
        mov type,NULL

        mov ti.symtype,NULL
        mov ti.is_ptr,0
        mov ti.ptr_memtype,MT_EMPTY

        mov cl,ModuleInfo._model
        mov eax,1
        shl eax,cl
        .if eax & SIZE_DATAPTR
            mov ti.is_far,TRUE
        .else
            mov ti.is_far,FALSE
        .endif
        mov ti.Ofssize,ModuleInfo.Ofssize

        mov creat,0
        .if !SymFind(name)
            SymLCreate(name)
            mov creat,1
        .endif
        .return ERROR .if !eax ; if it failed, an error msg has been written already

        mov sym,eax
        .if creat
            mov [eax].asym.state,SYM_STACK
            or  [eax].asym.flag,S_ISDEFINED
            mov [eax].asym.total_length,1
        .endif

        .if ti.Ofssize == USE16
            .if creat
                mov [eax].esym.sym.mem_type,MT_WORD
            .endif
            mov ti.size,word
        .else
            .if creat
                mov [eax].esym.sym.mem_type,MT_DWORD
            .endif
            mov ti.size,dword
        .endif

        add ebx,16 ; go past name

        ; .new name<[xx]>

        .if [ebx].token == T_OP_SQ_BRACKET

            add ebx,16 ; go past '['
            mov edi,ebx
            sub edi,tokenarray
            shr edi,4
            mov i,edi
            .for esi = ebx : edi < Token_Count: edi++, ebx += 16
                .break .if [ebx].token == T_COMMA || [ebx].token == T_COLON
            .endf
            .return .if EvalOperand( &i, tokenarray, edi, &opndx, 0 ) == ERROR

            .if opndx.kind != EXPR_CONST

                asmerr( 2026 )
                mov opndx.value,1
            .endif

            imul ebx,i,asm_tok
            add  ebx,tokenarray

            mov ecx,sym
            mov [ecx].asym.total_length,opndx.value
            or  [ecx].asym.flag,S_ISARRAY

            .if [ebx].token == T_CL_SQ_BRACKET

                add ebx,16 ; go past ']'
            .else
                asmerr( 2045 )
            .endif
        .endif

        mov esi,sym
        assume esi:asym_t

        ; .new name[xx]:<type>

        .if [ebx].token == T_COLON

            mov type,[ebx+16].string_ptr
            sub ebx,tokenarray
            shr ebx,4
            inc ebx
            mov i,ebx
            .return .if GetQualifiedType(&i, tokenarray, &ti) == ERROR

            imul ebx,i,asm_tok
            add ebx,tokenarray

            mov [esi].mem_type,ti.mem_type
            .if (ti.mem_type == MT_TYPE)
                mov [esi].type,ti.symtype
            .else
                mov [esi].target_type,ti.symtype
            .endif
        .endif

        .if creat
            mov [esi].is_ptr,ti.is_ptr
            .if ti.is_far
                or [esi].sint_flag,SINT_ISFAR
            .endif
            mov [esi].Ofssize,ti.Ofssize
            mov [esi].ptr_memtype,ti.ptr_memtype
            mov eax,ti.size
            mul [esi].total_length
            mov [esi].total_size,eax
        .endif

        assume esi:nothing

        .if creat && Parse_Pass == PASS_1

            mov eax,CurrProc
            mov edx,[eax].esym.procinfo
            .if [edx].proc_info.locallist == NULL
                mov [edx].proc_info.locallist,esi
            .else
                mov ecx,[edx].proc_info.locallist
                .for : [ecx].esym.nextlocal : ecx = [ecx].esym.nextlocal
                .endf
                mov [ecx].esym.nextlocal,esi
            .endif
        .endif

        .if [ebx].token != T_FINAL

            .if [ebx].token == T_COMMA

                mov eax,ebx
                sub eax,tokenarray
                shr eax,4
                inc eax
                .if eax < Token_Count
                    add ebx,16
                .endif

            .elseif [ebx].token == T_OP_BRACKET

                lea edi,[ebx-16]
                mov esi,[ebx-16].string_ptr
                add ebx,16 ; go past '('

                .for eax = 1 : [ebx].token != T_FINAL : ebx += 16
                    .if [ebx].token == T_OP_BRACKET
                        inc eax
                    .elseif [ebx].token == T_CL_BRACKET
                        dec eax
                        .break .ifz
                    .endif
                .endf
                .return asmerr( 2045 ) .if [ebx].token != T_CL_BRACKET

                add ebx,16 ; go past ')'
                mov endtok,ebx
                ConstructorCall( name, &endtok, edi, esi, type )
                mov ebx,endtok
            .elseif [ebx].token == T_DIRECTIVE && [ebx].dirtype == DRT_EQUALSGN
                mov ebx,AssignValue(name, i, tokenarray, &ti)
            .else
                .return asmerr( 2065, "," )
            .endif
        .endif
        mov eax,ebx
        sub eax,tokenarray
        shr eax,4
        .break .if eax >= Token_Count
    .endw

    .if creat && Parse_Pass == PASS_1

        mov eax,CurrProc
        mov ecx,[eax].esym.procinfo
        mov [ecx].proc_info.localsize,0
        SetLocalOffsets(ecx)
    .endif

    mov eax,NOT_ERROR
    ret

AddLocalDir endp

NewDirective proc i:int_t, tokenarray:tok_t

  local rc:int_t, list:int_t

    .return asmerr(2012) .if CurrProc == NULL

    mov rc,AddLocalDir(i, tokenarray)

    if 0
    .if ModuleInfo.list
        LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
    .endif
    endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    mov eax,rc
    ret

NewDirective endp

    END
