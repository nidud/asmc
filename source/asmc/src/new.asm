; NEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include expreval.inc
include qfloat.inc
include fastpass.inc

SIZE_DATAPTR    equ 0x68

SymLCreate      proto __ccall :string_t
GetQualifiedType proto __ccall :ptr int_t, :token_t, :ptr qualified_type
SetLocalOffsets proto __ccall :proc_t

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

    assume rbx:token_t

ConstructorCall proc __ccall private uses rsi rdi rbx \
        name    : string_t,         ; id name
        endtok  : ptr ptr asm_tok,  ; past ')' of call
        argtok  : ptr asm_tok,      ; past '(' of call
        class   : string_t,         ; class name
        type    : string_t          ; name:<type>

  local acc     : int_t,
        reg     : int_t,
        cltype  : ClType,
        cc[256] : char_t            ; class_class

    mov rsi,tstrcat( tstrcat( tstrcpy( &cc, class ), "_" ), class )

    SymFind( rsi )

    .if ( Parse_Pass > PASS_1 && rax )

        .if ( [rax].asym.state == SYM_UNDEFINED )

            ; x::x proto
            ;
            ; undef x_x
            ; x_x macro this

            mov [rax].asym.state,SYM_MACRO
        .endif
    .endif

    xor ecx,ecx
    mov reg,ecx

    .if ( rax && [rax].asym.state == SYM_MACRO )

        mov ecx,T_ECX
        mov reg,T_ECX

        .if ( ModuleInfo.Ofssize == USE64 )

            mov ecx,T_EDI
            mov reg,T_RDI

            .if ( [rax].asym.langtype != LANG_SYSCALL )

                mov ecx,T_ECX
                mov reg,T_RCX
            .endif
        .endif
    .endif

    xor eax,eax
    mov rbx,argtok

    mov edx,ClNew
    .if ( [rbx-asm_tok].token == T_COLON )
        mov edx,ClMem
    .elseif ( type )
        mov edx,ClPtr
    .endif
    mov cltype,edx

    .if ( [rbx-asm_tok].token != T_COLON )

        inc eax
        .if ( type == NULL )
            inc eax
        .endif
    .endif

    mov rdi,[rbx+asm_tok*2].tokpos
    mov rdx,endtok
    mov rbx,[rdx]

    .if ( [rbx-asm_tok*2].token != T_OP_BRACKET )

        add eax,3
        mov rbx,[rbx-asm_tok].tokpos
        mov byte ptr [rbx],0
    .else
        xor ebx,ebx
    .endif
    mov rdx,name

    .if rcx
        .new _eax:int_t = eax
        .switch eax
        .case 0, 3
            AddLineQueueX( " lea %r, %s", reg, rdx )
            .endc
        .case 1, 2, 4, 5
            AddLineQueueX( " xor %r, %r", ecx, ecx )
        .endsw
        mov rdx,name
        mov ecx,reg
        mov eax,_eax
        .switch pascal eax
        .case 0 : AddLineQueueX( " %s(%r)",          rsi, ecx )
        .case 1 : AddLineQueueX( " mov %s,%s(%r)",   rdx, rsi, ecx )
        .case 2 : AddLineQueueX( " %s(%r)",          rsi, ecx )
        .case 3 : AddLineQueueX( " %s(%r,%s)",       rsi, ecx, rdi )
        .case 4 : AddLineQueueX( " mov %s,%s(%r,%s)",rdx, rsi, ecx, rdi )
        .case 5 : AddLineQueueX( " %s(%r,%s)",       rsi, ecx, rdi )
        .endsw
    .else
        .switch pascal eax
        .case 0 : AddLineQueueX( " %s(&%s)",         rsi, rdx )
        .case 1 : AddLineQueueX( " mov %s,%s(0)",    rdx, rsi )
        .case 2 : AddLineQueueX( " %s(0)",           rsi )
        .case 3 : AddLineQueueX( " %s(&%s,%s)",      rsi, rdx, rdi )
        .case 4 : AddLineQueueX( " mov %s,%s(0,%s)", rdx, rsi, rdi )
        .case 5 : AddLineQueueX( " %s(0,%s)",        rsi, rdi )
        .endsw
    .endif

    .if rbx
        mov byte ptr [rbx],')'
    .endif
    mov rdx,endtok
    mov rbx,[rdx]

    ; added 2.31.44

    .if ( [rbx].token == T_COLON ) ; Class() : member(value) [ , member(value) ]

        add rbx,asm_tok
        mov acc,T_EAX

        .if ( ModuleInfo.Ofssize == USE64 )
            mov acc,T_RAX
        .endif
        .if ( reg )
            mov acc,reg
        .endif

        .while ( [rbx].token == T_ID && [rbx+asm_tok].token == T_OP_BRACKET )

            mov rdx,[rbx].string_ptr
            add rbx,asm_tok*2
            mov rdi,[rbx].tokpos

            .for ( eax = 1 : [rbx].token != T_FINAL : rbx += asm_tok )
                .if ( [rbx].token == T_OP_BRACKET )
                    inc eax
                .elseif ( [rbx].token == T_CL_BRACKET )
                    dec eax
                   .break .ifz
                .endif
            .endf

            .if ( [rbx].token != T_CL_BRACKET )

                .return asmerr( 2008, [rbx].string_ptr )
            .endif

            mov rsi,[rbx].tokpos
            mov byte ptr [rsi],0

            .if ( cltype == ClMem )
                AddLineQueueX( " mov %s.%s, %s", name, rdx, rdi )
            .else
                AddLineQueueX( " mov [%r].%s.%s, %s", acc, class, rdx, rdi )
            .endif
            mov byte ptr [rsi],')'
            add rbx,asm_tok
            .if ( [rbx].token == T_COMMA )
                add rbx,asm_tok
            .endif
        .endw
        mov rdx,endtok
        mov [rdx],rbx
    .endif
    ret

ConstructorCall endp


; case = {0,2,..}

    assume rbx:nothing

AssignString proc __ccall private uses rsi rdi rbx name:string_t, fp:ptr sfield, string:string_t

  local i:int_t
  local opndx:expr

    ldr rdx,fp
    mov ebx,[rdx].sfield.total_size
    mov rdi,[rdx].sfield.name

    .repeat

        .break .if ebx <= 4

        mov esi,TokenCount
        add esi,1
        mov i,esi
        mov edx,Tokenize( string, esi, TokenArray, TOK_DEFAULT )

        imul eax,esi,asm_tok
        add rax,TokenArray

        .break .if [rax].asm_tok.token != T_NUM && [rax].asm_tok.token != T_FLOAT
        .break .ifd EvalOperand( &i, TokenArray, edx, &opndx, 0 ) == ERROR

        .if ( opndx.kind == EXPR_FLOAT )

            mov opndx.kind,EXPR_CONST
            .if ( ebx != 16 )
                quad_resize(&opndx, ebx)
            .endif
        .endif
        .break .if opndx.kind != EXPR_CONST
        .break .if ebx == 8 && opndx.l64_h == 0 && ModuleInfo.Ofssize == USE64

        .switch ebx
        .case 16
            AddLineQueueX(
                " mov dword ptr %s.%s[12], 0x%x\n"
                " mov dword ptr %s.%s[8], 0x%x", name, rdi, opndx.h64_h, name, rdi, opndx.h64_l )
        .case 10
            .if ebx == 10
                AddLineQueueX( " mov word ptr %s.%s[8], 0x%x", name, rdi, opndx.h64_l )
            .endif
        .case 8
            AddLineQueueX(
                " mov dword ptr %s.%s[4], 0x%x\n"
                " mov dword ptr %s.%s[0], 0x%x", name, rdi, opndx.l64_h, name, rdi, opndx.l64_l )
            .return
        .endsw
    .until 1
    AddLineQueueX( " mov %s.%s, %s", name, rdi, string )
    ret

AssignString endp


AssignStruct proc __ccall private uses rsi rdi rbx name:string_t, sym:asym_t, string:string_t

   .new val[256]:char_t
   .new array:int_t = 0
   .new brackets:byte

    ldr rdx,sym
    ldr rax,string
    lea rsi,[rax+1]

    .if ( rdx )

        .while ( [rdx].asym.state == SYM_TYPE && [rdx].asym.type )

            .break .if ( rdx == [rdx].asym.type )

            mov rdx,[rdx].asym.type
        .endw

        mov rcx,[rdx].dsym.structinfo
        mov rbx,[rcx].struct_info.head
    .else
        inc array
    .endif

    .while 1

        lodsb

        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .break .if al == '}'

        dec rsi
        .break .if !al

        lea rdi,val
        .if ( byte ptr [rsi] == '{' )

            tstrcpy( rdi, name )
            mov rcx,[rbx].sfield.name

            .if ( byte ptr [rcx] )

                tstrcat( rdi, "." )
                tstrcat( rdi, [rbx].sfield.name )
            .endif

            mov rsi,AssignStruct( rdi, [rbx].sfield.type, rsi )

            .break .if !eax
            .while ( byte ptr [rsi] == ' ' || byte ptr [rsi] == 9 )

                add rsi,1
            .endw

        .else

            xor eax,eax
            xor edx,edx
            mov brackets,al
            mov [rdi],al
            lea rcx,[rdi+255]

            .while ( rdi < rcx )

                mov al,[rsi]

                .switch al
                .case 0
                    .break
                .case ','
                .case '}'
                    .break .if !brackets
                    .endc
                .case '('
                    inc brackets
                    .endc
                .case ')'
                    dec brackets
                    .endc
                .endsw
                .if !islabel( eax )
                    inc edx
                .endif
                movsb
            .endw

            xor eax,eax
            mov [rdi],al

            .for ( rcx = &val : rcx < rdi && ( byte ptr [rdi-1] == ' ' || byte ptr [rdi-1] == 9 ) : )

                dec edx
                dec rdi
                mov byte ptr [rdi],0
            .endf

            .if ( edx == 0 )

                mov rdi,rcx

                .if SymSearch( rdi )

                    .if ( [rax].asym.state == SYM_TMACRO )

                        mov rcx,[rax].asym.string_ptr

                        .if ( byte ptr [rcx] == '{' && !array && [rbx].sfield.flags & S_ISARRAY )

                            mov     rdx,rax
                            xor     eax,eax
                            mov     rdi,rsi
                            mov     ecx,-1
                            repne   scasb
                            not     ecx

                            mov     edi,[rdx].asym.total_size
                            lea     rax,[rdi+rcx+15]
                            and     rax,-16
                            sub     rsp,rax
                            mov     eax,ecx
                            lea     rcx,[rdi-1]
                            mov     rdi,rsp
                            mov     rdx,[rdx].asym.string_ptr
                            xchg    rdx,rsi
                            rep     movsb
                            mov     rsi,rdx
                            mov     ecx,eax
                            rep     movsb
                            mov     rsi,rsp
ifdef _WIN64
                            sub     rsp,@ReservedStack
endif
                           .continue(0)

                        .else

                            mov rdx,rsi
                            mov rsi,rcx
                            mov ecx,[rax].asym.total_size
                            inc ecx
                            and ecx,256-1
                            rep movsb
                            mov rsi,rdx
                        .endif
                    .endif
                .endif
            .endif

            .if ( val )

                .if ( array )

                    mov eax,[rbx].sfield.total_size
                    xor edx,edx
                    div [rbx].sfield.total_length
                    mov ecx,array
                    dec ecx
                    mul ecx
                    mov ecx,eax
                .endif

                .if ( val == '"' || ( val == 'L' &&  val[1] == '"' ) )

                    .if ( array )
                        AddLineQueueX( " mov %s[%d], &@CStr(%s)", name, ecx, &val )
                    .else
                        AddLineQueueX( " mov %s.%s, &@CStr(%s)", name, [rbx].sfield.name, &val )
                    .endif

                .elseif ( array )

                    AddLineQueueX( " mov %s[%d], %s", name, ecx, &val )
                .else
                    AssignString( name, rbx, &val )
                .endif
            .endif
        .endif

        .break .if ( byte ptr [rsi] == 0 )
         lodsb
        .break .if ( al != ',' ) ; == '}'

        .if ( array )
            inc array
        .else
            mov rbx,[rbx].sfield.next
        .endif
        .break .if !rbx
    .endw
    .return( rsi )

AssignStruct endp


; case = {...},{...},

AssignId proc __ccall private uses rsi rdi rbx name:string_t, sym:asym_t, type:asym_t, string:string_t

  local Id[128]:char_t, size:int_t, f:sfield

    .if ( type == NULL )

        mov rsi,sym
        lea rdi,f
        mov ecx,asym
        rep movsb
        mov f.next,NULL
        lea rbx,f

       .return AssignStruct( name, NULL, string )
    .endif

    mov rdi,sym
    .if !( [rdi].asym.flags & S_ISARRAY )

        .return AssignStruct( name, type, string )
    .endif

    mov rsi,string
    inc rsi
    .while ( byte ptr [rsi] == ' ' || byte ptr [rsi] == 9 )
        add rsi,1
    .endw

    mov eax,[rdi].asym.total_size
    mov ebx,[rdi].asym.total_length
    xor edx,edx
    div ebx
    mov size,eax
    xor edi,edi

    .for ( : ebx : ebx--, edi += size )

        tsprintf( &Id, "%s[%d]", name, edi )
        mov rsi,AssignStruct( &Id, type, rsi )
        lodsb
        .break .if !al
        .repeat
            lodsb
            .continue(0) .if al == ' '
            .continue(0) .if al == 9
            dec rsi
        .until 1
        .break .if al != '{'
    .endf
    .return( rsi )

AssignId endp


    assume rbx:token_t

; case = {0}

ClearStruct proc __ccall uses rsi rdi rbx name:string_t, sym:asym_t

    ldr rsi,sym

    AddLineQueue( " xor eax, eax" )

    mov edi,[rsi].asym.total_size

    .if ( ModuleInfo.Ofssize == USE64 )

        .if ( edi > 32 )

            AddLineQueueX(
                " push rdi\n"
                " push rcx\n"
                " lea rdi, %s\n"
                " mov ecx, %d\n"
                " rep stosb\n"
                " pop rcx\n"
                " pop rdi", name, edi )

        .else

            .for ( ebx = 0 : edi >= 8 : edi -= 8, ebx += 8 )

                AddLineQueueX( " mov qword ptr %s[%d], rax", name, ebx )
            .endf

            .if ( edi >= 4 )

                AddLineQueueX( " mov dword ptr %s[%d], eax", name, ebx )
                sub edi,4
                add ebx,4
            .endif

            .for ( : edi : edi--, ebx++ )

                AddLineQueueX( " mov byte ptr %s[%d], al", name, ebx )
            .endf
        .endif

    .elseif ( edi > 16 )

        AddLineQueueX(
            " push edi\n"
            " push ecx\n"
            " lea edi, %s\n"
            " mov ecx, %d\n"
            " rep stosb\n"
            " pop ecx\n"
            " pop edi", name, edi )

    .else

        .for ( ebx = 0 : edi >= 4 : edi -= 4, ebx += 4 )

            AddLineQueueX( " mov dword ptr %s[%d], eax", name, ebx )
        .endf

        .for ( : edi : edi--, ebx++ )

            AddLineQueueX( " mov byte ptr %s[%d], al", name, ebx )
        .endf
    .endif
    ret

ClearStruct endp


    assume rsi:ptr qualified_type

AssignValue proc __ccall private uses rsi rdi rbx name:string_t, i:int_t,
        tokenarray:token_t, ti:ptr qualified_type

  local cc[256]:char_t
  local l2[256]:char_t
  local flag:byte
  local opndx:expr

    inc  i
    imul ebx,i,asm_tok
    add  rbx,tokenarray
    ldr  rsi,ti

if 0
    mov rax,[rsi].symtype
    .if ( rax && [rax].asym.flags & S_OPERATOR )

        AddLineQueueX( " %s %s", name, [rbx-asm_tok].tokpos )
        imul eax,TokenCount,asm_tok
        add rax,tokenarray
        .return
    .endif
endif

    mov flag,[rbx].flags
    mov l2,0

    .if ( [rbx].token == T_STRING && [rbx].bytval == '{' )

        .if ( SymSearch( name ) == NULL )

            .return asmerr( 2008, [rbx].tokpos )
        .endif

        xor edx,edx
        mov rcx,[rbx].string_ptr

        .while ( byte ptr [rcx] == ' ' || byte ptr [rcx] == 9 )
            inc rcx
        .endw

        .if ( byte ptr [rcx] == '0' )

            inc rcx
            .while ( byte ptr [rcx] == ' ' || byte ptr [rcx] == 9 )
                inc rcx
            .endw
            .if ( byte ptr [rcx] == 0 )
                inc rdx
            .endif
        .endif

        .if edx
            ClearStruct( name, rax )
        .else
            AssignId( name, rax, [rax].asym.type, [rbx].tokpos )
        .endif
        lea rax,[rbx+asm_tok]
       .return
    .endif

    ; .new q:qword = foo()

    lea rdi,cc
    mov eax,T_MOV

    .if ( [rbx].token != T_FLOAT && [rbx].token != '-' )

        .if ( [rsi].mem_type == MT_REAL4 )
            mov eax,T_MOVSS
        .elseif ( [rsi].mem_type == MT_REAL8 )
            mov eax,T_MOVSD
        .elseif ( [rsi].mem_type == MT_REAL16 )
            mov eax,T_MOVAPS
        .endif
    .endif
    tsprintf( rdi, " %r ", eax )

    mov eax,[rsi].size

    .if ( eax >= 8 )

        mov rdx,[rbx].string_ptr

        .if ( eax == 8 && [rsi].Ofssize == USE32 && flag & T_ISPROC &&
              ( [rsi].mem_type == MT_QWORD || [rsi].mem_type == MT_SQWORD ) )

            tstrcat( rdi, "dword ptr " )
            tstrcpy( &l2, "mov dword ptr " )
            tstrcat( tstrcat( rax, name ), "[4], edx" )

        .elseif ( eax == 8 && [rsi].Ofssize == USE64 &&
                  ( flag & T_ISPROC || word ptr [rdx] == '&' ) )

        .elseifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) != ERROR )

            mov eax,[rsi].size
            .if ( eax == 8 && opndx.kind == EXPR_CONST )

                .if ( [rsi].Ofssize == USE32 ||
                      ( [rbx].token != T_STRING && opndx.hvalue > 0 ) )

                    AddLineQueueX(
                        " mov dword ptr %s[0], %u\n"
                        " mov dword ptr %s[4], %u",
                        name, opndx.l64_l, name, opndx.l64_h )

                    imul eax,i,asm_tok
                    add  rax,tokenarray
                   .return
                .endif

            .elseif ( opndx.kind == EXPR_FLOAT && ( eax == 8 || eax == 10 || eax == 16 ) )

                .if ( eax == 8 )
                    AddLineQueueX(
                        " mov dword ptr %s[0], LOW32(%s)\n"
                        " mov dword ptr %s[4], HIGH32(%s)",
                        name, [rbx].tokpos, name, [rbx].tokpos )

                .elseif ( eax == 10 )

                     __cvtq_ld(&opndx, &opndx)
                    AddLineQueueX(
                        " mov dword ptr %s[0], %u\n"
                        " mov dword ptr %s[4], %u\n"
                        " mov word ptr %s[8], %u",
                        name, opndx.l64_l,
                        name, opndx.l64_h,
                        name, opndx.h64_l )

                .else

                    AddLineQueueX(
                        " mov dword ptr %s[0], %u\n"
                        " mov dword ptr %s[4], %u\n"
                        " mov dword ptr %s[8], %u\n"
                        " mov dword ptr %s[12],%u",
                        name, opndx.l64_l,
                        name, opndx.l64_h,
                        name, opndx.h64_l,
                        name, opndx.h64_h )
                .endif

                imul eax,i,asm_tok
                add  rax,tokenarray
               .return
            .endif
        .endif
    .endif

    tstrcat( tstrcat( rdi, name ), ", " )
    xor esi,esi

    assume rsi:nothing

    .while 1
        .switch [rbx].token
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

        .if ( [rbx].token == T_INSTRUCTION )
            tstrcat(rdi, " ")
        .endif

        .if ( !esi && [rbx].token == T_STRING && [rbx].bytval == '"' )

            .if SymSearch( name )

                .if ( [rax].asym.mem_type & MT_PTR )

                    tstrcat(rdi, "&@CStr(")
                    tstrcat(rdi, [rbx].string_ptr)
                    tstrcat(rdi, ")")
                    add rbx,asm_tok
                    .break
                .endif
            .endif
        .endif

        tstrcat(rdi, [rbx].string_ptr)

        .if ( ( [rbx].token == T_INSTRUCTION ) ||
              ( [rbx].token == T_RES_ID && [rbx].tokval == T_ADDR ) )

            tstrcat(rdi, " ")
        .endif
        add rbx,asm_tok
    .endw
    .if esi
        asmerr( 2157 )
    .endif
    AddLineQueue( rdi )
    .if l2
        AddLineQueue( &l2 )
    .endif
    .return( rbx )

AssignValue endp


AddLocalDir proc __ccall private uses rsi rdi rbx i:int_t, tokenarray:token_t

  local name  : string_t,
        type  : string_t,
        sym   : dsym_t,
        creat : int_t,
        ti    : qualified_type,
        opndx : expr,
        endtok: token_t

    inc  i  ; go past directive
    imul ebx,i,asm_tok
    add  rbx,tokenarray

    .while 1

        .if ( [rbx].token != T_ID )

            .return asmerr( 2008, [rbx].string_ptr )
        .endif

        mov name,[rbx].string_ptr
        mov type,NULL

        mov ti.symtype,NULL
        mov ti.is_ptr,0
        mov ti.ptr_memtype,MT_EMPTY

        mov cl,ModuleInfo._model
        mov eax,1
        shl eax,cl

        .if ( eax & SIZE_DATAPTR )
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
        .return ERROR .if !rax ; if it failed, an error msg has been written already

        mov sym,rax

        .if creat

            mov [rax].asym.state,SYM_STACK
            or  [rax].asym.flags,S_ISDEFINED
            mov [rax].asym.total_length,1
        .elseif ( [rax].asym.state != SYM_STACK && !( [rax].asym.flags & S_CLASS ) )
            .return( asmerr( 2005, [rax].asym.name ) )
        .endif

        .if ti.Ofssize == USE16
            .if creat
                mov [rax].dsym.mem_type,MT_WORD
            .endif
            mov ti.size,word
        .else
            .if creat
                mov [rax].dsym.mem_type,MT_DWORD
            .endif
            mov ti.size,dword
        .endif

        add rbx,asm_tok ; go past name

        ; .new name<[xx]>

        .if [rbx].token == T_OP_SQ_BRACKET

            add rbx,asm_tok ; go past '['
            mov rdi,rbx
            sub rdi,tokenarray
            mov eax,edi
            mov ecx,asm_tok
            xor edx,edx
            div ecx
            mov edi,eax
            mov i,edi

            .for ( rsi = rbx : edi < TokenCount: edi++, rbx += asm_tok )
                .break .if [rbx].token == T_COMMA || [rbx].token == T_COLON
            .endf

            .return .ifd EvalOperand( &i, tokenarray, edi, &opndx, 0 ) == ERROR

            .if ( opndx.kind != EXPR_CONST )

                asmerr( 2026 )
                mov opndx.value,1
            .endif

            imul ebx,i,asm_tok
            add  rbx,tokenarray

            mov rcx,sym
            mov [rcx].asym.total_length,opndx.value
            or  [rcx].asym.flags,S_ISARRAY

            .if ( [rbx].token == T_CL_SQ_BRACKET )

                add rbx,asm_tok ; go past ']'
            .else
                asmerr( 2045 )
            .endif
        .endif

        mov rsi,sym
        assume rsi:asym_t

        ; .new name[xx]:<type>

        .if ( [rbx].token == T_COLON )

            mov type,[rbx+asm_tok].string_ptr
            sub rbx,tokenarray
            mov ecx,asm_tok
            mov eax,ebx
            xor edx,edx
            div ecx
            mov ebx,eax
            inc ebx
            mov i,ebx

            .return .ifd GetQualifiedType(&i, tokenarray, &ti) == ERROR

            imul ebx,i,asm_tok
            add rbx,tokenarray

            mov [rsi].mem_type,ti.mem_type

            .if ( ti.mem_type == MT_TYPE )
                mov [rsi].type,ti.symtype
            .else
                mov [rsi].target_type,ti.symtype
            .endif
        .endif

        .if ( creat )

            mov [rsi].is_ptr,ti.is_ptr
            mov [rsi].is_far,ti.is_far
            mov [rsi].Ofssize,ti.Ofssize
            mov [rsi].ptr_memtype,ti.ptr_memtype
            mov eax,ti.size
            mul [rsi].total_length
            mov [rsi].total_size,eax
        .endif

        assume rsi:nothing

        .if ( creat && Parse_Pass == PASS_1 )

            mov rax,CurrProc
            mov rdx,[rax].dsym.procinfo

            .if ( [rdx].proc_info.locallist == NULL )

                mov [rdx].proc_info.locallist,rsi

            .else

                mov rcx,[rdx].proc_info.locallist

                .for ( : [rcx].dsym.nextlocal : rcx = [rcx].dsym.nextlocal )
                .endf
                mov [rcx].dsym.nextlocal,rsi
            .endif
        .endif

        .if ( [rbx].token != T_FINAL  )

            .if ( [rbx].token == T_COMMA )

                mov rax,rbx
                sub rax,tokenarray
                xor edx,edx
                mov ecx,asm_tok
                div ecx
                inc eax
                .if eax < TokenCount
                    add rbx,asm_tok
                .endif

            .elseif ( [rbx].token == T_OP_BRACKET )

                lea rdi,[rbx-asm_tok]
                mov rsi,[rbx-asm_tok].string_ptr
                add rbx,asm_tok ; go past '('

                .for ( eax = 1 : [rbx].token != T_FINAL : rbx += asm_tok )
                    .if ( [rbx].token == T_OP_BRACKET )
                        inc eax
                    .elseif ( [rbx].token == T_CL_BRACKET )
                        dec eax
                        .break .ifz
                    .endif
                .endf

                .if ( [rbx].token != T_CL_BRACKET )
                    .return asmerr( 2045 )
                .endif

                add rbx,asm_tok ; go past ')'
                mov endtok,rbx
                ConstructorCall( name, &endtok, rdi, rsi, type )
                mov rbx,endtok

            .elseif ( [rbx].token == T_DIRECTIVE && [rbx].dirtype == DRT_EQUALSGN )

                mov rbx,AssignValue(name, i, tokenarray, &ti)
            .else
                .return asmerr( 2065, "," )
            .endif
        .endif

        mov rax,rbx
        sub rax,tokenarray
        xor edx,edx
        mov ecx,asm_tok
        div ecx
       .break .if eax >= TokenCount
    .endw

    .if ( creat && Parse_Pass == PASS_1 )

        mov rax,CurrProc
        mov rcx,[rax].dsym.procinfo
        mov [rcx].proc_info.localsize,0
        SetLocalOffsets(rcx)
    .endif
    .return( NOT_ERROR )

AddLocalDir endp


NewDirective proc __ccall i:int_t, tokenarray:token_t

  local rc:int_t

    .if ( CurrProc == NULL )
        .return asmerr( 2012 )
    .endif

    mov rc,AddLocalDir( i, tokenarray )
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

NewDirective endp

    END
