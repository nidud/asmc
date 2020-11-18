include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include expreval.inc

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
        cc[128] : char_t            ; class_class

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
            AddLineQueueX( " lea %r,%s", reg, edx )
            .endc
        .case 1, 2, 4, 5
            AddLineQueueX( " xor %r,%r", ecx, ecx )
        .endsw
        pop eax
        mov edx,name
        mov ecx,reg
        .switch pascal eax
        .case 0 : AddLineQueueX( " %s(%r)",          esi, ecx )
        .case 1 : AddLineQueueX( " mov %s,%s(%r)",   edx, esi, ecx )
        .case 2 : AddLineQueueX( " %s(%r)",          esi, ecx )
        .case 3 : AddLineQueueX( " %s(%r,%s)",       esi, ecx, edi )
        .case 4 : AddLineQueueX( " mov %s,%s(%r,%s)",edx, esi, ecx, edi )
        .case 5 : AddLineQueueX( " %s(%r,%s)",       esi, ecx, edi )
        .endsw
    .else
        .switch pascal eax
        .case 0 : AddLineQueueX( " %s(&%s)",         esi, edx )
        .case 1 : AddLineQueueX( " mov %s,%s(0)",    edx, esi )
        .case 2 : AddLineQueueX( " %s(0)",           esi )
        .case 3 : AddLineQueueX( " %s(&%s,%s)",      esi, edx, edi )
        .case 4 : AddLineQueueX( " mov %s,%s(0,%s)", edx, esi, edi )
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
                AddLineQueueX( " mov %s.%s, %s", name, edx, edi )
            .else
                AddLineQueueX( " mov [%r].%s.%s, %s", acc, class, edx, edi )
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

AssignValue proc private uses esi edi ebx name:string_t, tokenarray:tok_t

  local cc[128]:char_t

    mov ebx,tokenarray
    add ebx,16 ; skip '='
    mov edi,strcat( strcat( strcpy( &cc, " mov " ), name ), ", " )
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
        strcat(edi, [ebx].string_ptr)
        .if [ebx].token == T_RES_ID && [ebx].tokval == T_ADDR
            strcat(edi, " ")
        .endif
        add ebx,16
    .endw
    .if esi
        asmerr( 2157 )
    .endif
    AddLineQueueX( edi )
    mov eax,ebx
    ret

AssignValue endp

AddLocalDir proc uses esi edi ebx i:int_t, tokenarray:tok_t

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
                mov ebx,AssignValue(name, ebx)
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

  local rc:int_t

    .return asmerr(2012) .if CurrProc == NULL

    mov rc,AddLocalDir(i, tokenarray)
    .if ModuleInfo.list
        LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    mov eax,rc
    ret

NewDirective endp

    END
