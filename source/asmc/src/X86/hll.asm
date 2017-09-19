include string.inc
include stdio.inc
include stdlib.inc
include alloc.inc

include asmc.inc
include token.inc
include hll.inc

; c binary ops.
; Order of items COP_EQ - COP_LE  and COP_ZERO - COP_OVERFLOW
; must not be changed.

COP_NONE        equ 0
COP_EQ          equ 1       ; ==
COP_NE          equ 2       ; !=
COP_GT          equ 3       ; >
COP_LT          equ 4       ; <
COP_GE          equ 5       ; >=
COP_LE          equ 6       ; <=
COP_AND         equ 7       ; &&
COP_OR          equ 8       ; ||
COP_ANDB        equ 9       ; &
COP_NEG         equ 10      ; !
COP_ZERO        equ 11      ; ZERO?  not really a valid C operator
COP_CARRY       equ 12      ; CARRY?     not really a valid C operator
COP_SIGN        equ 13      ; SIGN?  not really a valid C operator
COP_PARITY      equ 14      ; PARITY?   not really a valid C operator
COP_OVERFLOW    equ 15      ; OVERFLOW? not really a valid C operator

.data

EOLSTR          db EOLCHAR,0
;
; items in table below must match order COP_ZERO - COP_OVERFLOW
;
flaginstr       db 'z','c','s','p','o'
;
; items in tables below must match order COP_EQ - COP_LE
;
unsign_cjmptype db 'z','z','a','b','b','a'
signed_cjmptype db 'z','z','g','l','l','g'
neg_cjmptype    db 0,1,0,0,1,1

;
; get a C binary operator from the token stream.
; there is a problem with the '<' because it is a "string delimiter"
; which Tokenize() usually is to remove.
; There has been a hack implemented in Tokenize() so that it won't touch the
; '<' if .IF, .ELSEIF, .WHILE, .UNTIL, .UNTILCXZ or .BREAK/.CONTINUE has been
; detected.
;

CHARS_EQ    equ '=' + ( '=' shl 8 )
CHARS_NE    equ '!' + ( '=' shl 8 )
CHARS_GE    equ '>' + ( '=' shl 8 )
CHARS_LE    equ '<' + ( '=' shl 8 )
CHARS_AND   equ '&' + ( '&' shl 8 )
CHARS_OR    equ '|' + ( '|' shl 8 )

    .code

GetCOp proc fastcall private item;:PTR asm_tok

    mov edx,[ecx].asm_tok.string_ptr
    xor eax,eax
    .if [ecx].asm_tok.token == T_STRING

        mov eax,[ecx].asm_tok.stringlen
    .endif
    .repeat
        .switch
          .case eax == 2
            movzx   eax,WORD PTR [edx]
            .switch eax
              .case CHARS_EQ:  mov eax,COP_EQ:  .break
              .case CHARS_NE:  mov eax,COP_NE:  .break
              .case CHARS_GE:  mov eax,COP_GE:  .break
              .case CHARS_LE:  mov eax,COP_LE:  .break
              .case CHARS_AND: mov eax,COP_AND: .break
              .case CHARS_OR:  mov eax,COP_OR:  .break
            .endsw
            .endc
          .case eax == 1
            mov al,[edx]
            .switch eax
              .case '>': mov eax,COP_GT:   .break
              .case '<': mov eax,COP_LT:   .break
              .case '&': mov eax,COP_ANDB: .break
              .case '!': mov eax,COP_NEG:  .break
            .endsw
            .endc
          .case [ecx].asm_tok.token != T_ID
            .endc
            ;
            ; a valid "flag" string must end with a question mark
            ;
          .case BYTE PTR [edx + strlen(edx) - 1] == '?'

            mov ecx,[edx]
            and ecx,not 20202020h

            .switch eax
              .case 5
                .if ecx == "OREZ"

                    mov eax,COP_ZERO
                    .break
                .endif
                .if ecx == "NGIS"

                    mov eax,COP_SIGN
                    .break
                .endif
                .endc
              .case 6
                movzx eax,BYTE PTR [edx+4]
                and eax,not 20h
                .if eax == "Y" && ecx == "RRAC"

                    mov eax,COP_CARRY
                    .break
                .endif
                .endc
              .case 7
                movzx eax,WORD PTR [edx+4]
                and eax,not 2020h
                .if eax == "YT" && ecx == "IRAP"

                    mov eax,COP_PARITY
                    .break
                .endif
                .endc
              .case 9
                mov eax,[edx+4]
                and eax,not 20202020h
                .if eax == "WOLF" && ecx == "REVO"

                    mov eax,COP_OVERFLOW
                    .break
                .endif
                .endc
            .endsw
            .endc
        .endsw
        mov eax,COP_NONE
    .until  1
    ret

GetCOp  endp

;
; render an instruction
;

RenderInstr proc private uses esi edi ebx,
    dst:        LPSTR,
    inst:       LPSTR,
    start1:     UINT,
    end1:       UINT,
    start2:     UINT,
    end2:       UINT,
    tokenarray: PTR asm_tok

    ;
    ; copy the instruction
    ;
    mov esi,inst
    mov edi,dst
    strlen( esi )

    mov ecx,eax
    rep movsb
    mov eax,' '
    stosb
    ;
    ; copy the first operand's tokens
    ;
    mov ebx,tokenarray
    mov ecx,end1
    mov eax,start1
    shl ecx,4
    shl eax,4
    mov ecx,[ebx+ecx].asm_tok.tokpos
    mov esi,[ebx+eax].asm_tok.tokpos
    sub ecx,esi
    rep movsb

    mov ecx,end2
    mov eax,start2

    .if eax != EMPTY

        mov WORD PTR [edi],' ,'
        add edi,2
        ;
        ; copy the second operand's tokens
        ;
        shl ecx,4
        shl eax,4
        mov ecx,[ebx+ecx].asm_tok.tokpos
        mov esi,[ebx+eax].asm_tok.tokpos
        sub ecx,esi
        rep movsb
    .elseif ecx != EMPTY

        sprintf(edi, ", %d", ecx)
        add edi,eax
    .endif
    mov WORD PTR [edi],EOLCHAR
    lea eax,[edi+1]
    ret
RenderInstr endp

GetLabelStr proc fastcall l_id:SINT, buff:LPSTR
    sprintf( edx, "@C%04X", ecx )
    mov eax,edx
    ret
GetLabelStr endp

;
; render a Jcc instruction
;
RenderJcc proc private uses edi dst, cc, _neg, _label
    ;
    ; create the jump opcode: j[n]cc
    ;
    mov edi,dst

    mov eax,'j'
    stosb
    mov ecx,_neg
    .if ecx

        mov eax,'n'
        stosb
    .endif

    mov eax,cc
    stosb
    mov eax,' '
    .if !ecx

        stosb       ; make sure there's room for the inverse jmp
    .endif
    stosb

    sprintf( edi, "@C%04X", _label )
    lea eax,[edi+eax+1]
    mov WORD PTR [eax-1],EOLCHAR
    ret

RenderJcc endp

;
; a "token" in a C expression actually is an assembly expression
;
LGetToken proc private uses esi edi ebx hll:PTR hll_item, i, tokenarray, opnd:PTR expr
    ;
    ; scan for the next C operator in the token array.
    ; because the ASM evaluator may report an error if such a thing
    ; is found ( CARRY?, ZERO? and alikes will be regarded as - not yet defined - labels )
    ;
    mov esi,i
    mov edi,[esi]

    mov ebx,edi
    shl ebx,4
    add ebx,tokenarray

    .for : edi < ModuleInfo.token_count,
           GetCOp(ebx) == COP_NONE : edi++, ebx += 16
    .endf

    .if edi == [esi]

        mov eax,opnd
        mov [eax].expr.kind,EXPR_EMPTY
        mov eax,NOT_ERROR

    .elseif EvalOperand( esi, tokenarray, edi, opnd, 0 ) != ERROR
        ;
        ; v2.11: emit error 'syntax error in control flow directive'.
        ; May happen for expressions like ".if 1 + CARRY?"
        ;
        mov eax,NOT_ERROR
        .if [esi] > edi

            asmerr(2154)
        .endif
    .endif
toend:
    ret
LGetToken endp

GetLabel proc fastcall hll, index

    mov eax,[ecx].hll_item.labels[edx*4]
    ret

GetLabel endp

; a "simple" expression is
; 1. two tokens, coupled with a <cmp> operator: == != >= <= > <
; 2. two tokens, coupled with a "&" operator
; 3. unary operator "!" + one token
; 4. one token (short form for "<token> != 0")
;

GetSimpleExpression proc private uses esi edi ebx,
    hll:        PTR hll_item,
    i:          PTR SINT,
    tokenarray: PTR asm_tok,
    ilabel:     SINT,
    is_true:    UINT,
    buffer:     LPSTR,
    hllop:      PTR hll_opnd

local   op:         SINT,
        op1_pos:    SINT,
        op1_end:    SINT,
        op2_pos:    SINT,
        op2_end:    SINT,
        op1:        expr,
        op2:        expr,
        _label

    assume ebx: PTR asm_tok

    mov esi,i
    mov edi,[esi]
    mov ebx,edi
    shl ebx,4
    add ebx,tokenarray

    mov eax,[ebx].string_ptr
    .while  WORD PTR [eax] == '!'

        add edi,1
        add ebx,16
        mov eax,1
        sub eax,is_true
        mov is_true,eax
        mov eax,[ebx].string_ptr
    .endw
    mov [esi],edi
    ;
    ; the problem with '()' is that is might enclose just a standard Masm
    ; expression or a "hll" expression. The first case is to be handled
    ; entirely by the expression evaluator, while the latter case is to be
    ; handled HERE!
    ;
    .if [ebx].token == T_OP_BRACKET

        mov esi,1
        add ebx,16
        movzx eax,[ebx].token
        .while eax != T_FINAL

            .if eax == T_OP_BRACKET

                add esi,1
            .elseif eax == T_CL_BRACKET

                sub esi,1
                .break .if ZERO?    ; a standard Masm expression?
            .else
                .break .if GetCOp( ebx ) != COP_NONE
            .endif
            add ebx,16
            movzx eax,[ebx].token
        .endw

        mov eax,esi
        mov esi,i

        .if eax

            inc DWORD PTR [esi]

            GetExpression( hll, esi, tokenarray, ilabel, is_true, buffer, hllop )

            cmp eax,ERROR
            je  toend

            mov ebx,[esi]
            shl ebx,4
            add ebx,tokenarray
            .if [ebx].token != T_CL_BRACKET

                asmerr( 2154 )
                jmp toend
            .endif

            inc DWORD PTR [esi]
            mov eax,NOT_ERROR
            jmp toend
        .endif
    .endif

    mov edi,[esi]
    mov ebx,tokenarray
    ;
    ; get (first) operand
    ;
    mov op1_pos,edi
    LGetToken( hll, esi, ebx, &op1 )
    cmp eax,ERROR
    je  toend

    mov edi,[esi]
    mov op1_end,edi

    mov eax,edi     ; get operator
    shl eax,4
    add eax,ebx
    GetCOp( eax )
    ;
    ; lower precedence operator ( && or || ) detected?
    ;
    .if eax == COP_AND || eax == COP_OR

        mov eax,COP_NONE
    .elseif eax != COP_NONE

        inc edi
        mov [esi],edi
    .endif
    mov op,eax

    GetLabel( hll, ilabel )
    mov _label,eax
    ;
    ; check for special operators with implicite operand:
    ; COP_ZERO, COP_CARRY, COP_SIGN, COP_PARITY, COP_OVERFLOW
    ;
    mov edx,op
    .if edx >= COP_ZERO

        .if op1.kind != EXPR_EMPTY

            asmerr( 2154 )
            jmp toend
        .endif

        mov ecx,hllop
        mov eax,buffer
        mov [ecx].hll_opnd.lastjmp,eax
        movzx ecx,flaginstr[edx - COP_ZERO]
        mov edx,is_true
        xor edx,1
        RenderJcc( eax, ecx, edx, _label )
        mov eax,NOT_ERROR
        jmp toend
    .endif

    mov eax,op1.kind
    .switch eax
      .case EXPR_EMPTY
        asmerr( 2154 )  ; v2.09: changed from NOT_ERROR to ERROR
        jmp toend
      .case EXPR_FLOAT
        asmerr( 2050 )  ; v2.10: added
        jmp toend
    .endsw

    .if op == COP_NONE

        .switch eax
          .case EXPR_REG
            .if !( op1.flags & EXF_INDIRECT )

                mov eax,@CStr( "test" )
                .if Options.masm_compat_gencode

                    mov eax,@CStr( "or" )
                .endif
                RenderInstr( buffer, eax, op1_pos, op1_end,
                    op1_pos, op1_end, ebx )
                mov edx,hllop
                mov [edx].hll_opnd.lastjmp,eax
                RenderJcc( eax, 'z', is_true, _label )
                .endc
            .endif
            ;
            ; no break
            ;
          .case EXPR_ADDR
            RenderInstr( buffer, "cmp", op1_pos, op1_end, EMPTY, 0, ebx )
            mov edx,hllop
            mov [edx].hll_opnd.lastjmp,eax
            RenderJcc( eax, 'z', is_true, _label )
            .endc
          .case EXPR_CONST
            .if op1.hvalue != 0 && op1.hvalue != -1

                EmitConstError( &op1 )
                jmp toend
            .endif

            mov ecx,hllop
            mov eax,buffer
            mov [ecx].hll_opnd.lastjmp,eax
            mov edx,is_true
            xor edx,1

            .if (( is_true && op1.value ) || ( edx && op1.value == 0 ))

                sprintf( buffer, "jmp @C%04X%s", _label, &EOLSTR )
            .else
                mov BYTE PTR [eax],NULLC
            .endif
            .endc
        .endsw

        mov eax,NOT_ERROR
        jmp toend
    .endif

    ;
    ; get second operand for binary operator
    ;
    mov edi,[esi]
    mov op2_pos,edi
    LGetToken( hll, esi, ebx, &op2 )
    cmp eax,ERROR
    je  toend

    mov eax,op2.kind
    .if eax != EXPR_CONST && eax != EXPR_ADDR && eax != EXPR_REG

        asmerr( 2154 )
        jmp toend
    .endif
    mov edi,[esi]
    mov op2_end,edi

    assume ebx: NOTHING
    ;
    ; now generate ASM code for expression
    ;
    mov ecx,op
    .if ecx == COP_ANDB
        ;
        ; v2.22 - switch /Zg to OR
        ;
        mov eax,@CStr( "test" )
        .if Options.masm_compat_gencode

            mov eax,@CStr( "or" )
        .endif
        RenderInstr( buffer, eax, op1_pos, op1_end, op2_pos, op2_end, ebx )

        mov ecx,hllop
        mov [ecx].hll_opnd.lastjmp,eax
        RenderJcc( eax, 'e', is_true, _label )

    .elseif ecx <= COP_LE
        ;
        ; ==, !=, >, <, >= or <= operator
        ;
        ; optimisation: generate 'or EAX,EAX' instead of 'cmp EAX,0'.
        ; v2.11: use op2.value64 instead of op2.value
        ;
        mov eax,DWORD PTR op2.value64
        or  eax,DWORD PTR op2.value64[4]

        .if !eax && (ecx == COP_EQ || ecx == COP_NE) && op1.kind == EXPR_REG && \
            !( op1.flags & EXF_INDIRECT ) && op2.kind == EXPR_CONST
            ;
            ; v2.22 - switch /Zg to OR
            ;
            mov eax,@CStr( "test" )
            .if Options.masm_compat_gencode

                mov eax,@CStr( "or" )
            .endif
            RenderInstr( buffer, eax, op1_pos, op1_end, op1_pos, op1_end, ebx )
        .else
            RenderInstr( buffer, "cmp",  op1_pos, op1_end, op2_pos, op2_end, ebx )
        .endif
        ;
        ; v2.22 - signed compare S, SB, SW, SD
        ;
        mov edx,hll
        xor edi,edi
        mov ecx,[edx].hll_item.flags

        if 0 ; v2.23 removed..
        .if ecx & HLLF_IFS or HLLF_IFB or HLLF_IFW or HLLF_IFD
            ;
            ; assume .ifx proc() --> .ifx reg
            ;
            .if op1.kind != EXPR_REG

                asmerr( 2154 )
                jmp toend
            .endif
        .endif
        endif

        .if ecx & HLLF_IFS

            inc edi
        .endif

        mov ecx,op
        movzx edx,op1.mem_type
        movzx ebx,op2.mem_type
        and edx,MT_SPECIAL_MASK
        and ebx,MT_SPECIAL_MASK

        .if edi || edx == MT_SIGNED || ebx == MT_SIGNED

            movzx edx,signed_cjmptype[ecx - COP_EQ]
        .else
            movzx edx,unsign_cjmptype[ecx - COP_EQ]
        .endif

        mov ebx,hllop
        mov [ebx].hll_opnd.lastjmp,eax
        mov ebx,is_true
        .if !neg_cjmptype[ecx - COP_EQ]

            xor ebx,1
        .endif
        RenderJcc( eax, edx, ebx, _label )
    .else

        asmerr( 2154 )
        jmp toend
    .endif

    mov eax,NOT_ERROR

toend:
    ret

GetSimpleExpression endp

; invert a Jump:
; - Jx   -> JNx (x = e|z|c|s|p|o )
; - JNx -> Jx   (x = e|z|c|s|p|o )
; - Ja   -> Jbe, Jae -> Jb
; - Jb   -> Jae, Jbe -> Ja
; - Jg   -> Jle, Jge -> Jl
; - Jl   -> Jge, Jle -> Jg
; added in v2.11:
; - jmp -> 0
; - 0    -> jmp
;
InvertJump proc fastcall p:LPSTR

    .if BYTE PTR [ecx] == NULLC ; v2.11: convert 0 to "jmp"

        strcpy( ecx, "jmp " )
        ret
    .endif

    add ecx,1
    mov eax,[ecx]

    .switch al
      .case 'e'
      .case 'z'
      .case 'c'
      .case 's'
      .case 'p'
      .case 'o'
        mov BYTE PTR [ecx+1],al
        mov BYTE PTR [ecx],'n'
        ret
      .case 'n'
        mov BYTE PTR [ecx],ah
        mov BYTE PTR [ecx+1],' '
        ret
      .case 'a'
        mov BYTE PTR [ecx],'b'
        .endc
      .case 'b'
        mov BYTE PTR [ecx],'a'
        .endc
      .case 'g'
        mov BYTE PTR [ecx],'l'
        .endc
      .case 'l'
        mov BYTE PTR [ecx],'g'
        .endc
      .default
        ;
        ; v2.11: convert "jmp" to 0
        ;
        .if al == 'm'

            sub ecx,1
            mov BYTE PTR [ecx],NULLC
        .endif
        ret
    .endsw

    .if ah == 'e'

        mov BYTE PTR [ecx+1],' '
    .else
        mov BYTE PTR [ecx+1],'e'
    .endif
    ret

InvertJump endp


; Replace a label in the source lines generated so far.
; todo: if more than 0xFFFF labels are needed,
; it may happen that length of nlabel > length of olabel!
; then the simple memcpy() below won't work!
;
ReplaceLabel proc private uses esi edi ebx p, olabel, nlabel

local oldlbl[16]:SBYTE, newlbl[16]:SBYTE

    mov ebx,p
    lea esi,oldlbl
    lea edi,newlbl

    GetLabelStr(olabel, esi)
    GetLabelStr(nlabel, edi)

    mov ebx,strlen(edi)
    mov eax,p
    .while strstr(eax, esi)

        memcpy(eax, edi, ebx)
        add eax,ebx
    .endw
    ret

ReplaceLabel endp

; operator &&, which has the second lowest precedence, is handled here

GetAndExpression proc private uses esi edi ebx,
    hll:        PTR hll_item,
    i:          PTR SINT,
    tokenarray: PTR asm_tok,
    ilabel:     UINT,
    is_true:    UINT,
    buffer:     LPSTR,
    hllop:      PTR hll_opnd

local   truelabel:  SINT,
        nlabel:     SINT,
        olabel:     SINT,
        buff[16]:   SBYTE

    mov edi,hllop
    mov esi,buffer
    mov truelabel,0

    .while  1

        GetSimpleExpression( hll, i, tokenarray, ilabel, is_true, esi, edi )
        cmp eax,ERROR
        je  toend

        mov ebx,i
        mov eax,[ebx]
        shl eax,4
        add eax,tokenarray

        .break .if GetCOp( eax ) != COP_AND

        inc DWORD PTR [ebx]
        mov ebx,[edi].hll_opnd.lastjmp
        .if ebx && is_true

            InvertJump(ebx)

            .if truelabel == 0

                mov truelabel,GetHllLabel()
            .endif
            ;
            ; v2.11: there might be a 0 at lastjmp
            ;
            .if BYTE PTR [ebx]

                strcat( GetLabelStr( truelabel, &[ebx+4] ), &EOLSTR )
            .endif
            ;
            ; v2.22 .while  (eax || edx) && ecx -- failed
            ;   .while !(eax || edx) && ecx -- failed
            ;
            mov ebx,esi
            .if [edi].hll_opnd.lasttruelabel

                ReplaceLabel( ebx, [edi].hll_opnd.lasttruelabel, truelabel )
            .endif
            mov nlabel,GetHllLabel()
            mov olabel,GetLabel( hll, ilabel )
            strlen(ebx)
            add ebx,eax
            sprintf( ebx, "%s%s%s", GetLabelStr( olabel, &buff ), LABELQUAL, &EOLSTR )
            ReplaceLabel( buffer, olabel, nlabel )
            mov [edi].hll_opnd.lastjmp,0
        .endif

        strlen(esi)
        add esi,eax
        mov [edi].hll_opnd.lasttruelabel,0
    .endw

    .if truelabel

        strlen(esi)
        add esi,eax
        strcat( strcat( GetLabelStr( truelabel, esi ), LABELQUAL ), &EOLSTR )
        mov [edi].hll_opnd.lastjmp,0
    .endif
    mov eax,NOT_ERROR
toend:
    ret
GetAndExpression endp

; operator ||, which has the lowest precedence, is handled here

GetExpression proc private uses esi edi ebx,
    hll:        PTR hll_item,
    i:          PTR SINT,
    tokenarray: PTR asm_tok,
    ilabel:     SINT,
    is_true:    UINT,
    buffer:     LPSTR,
    hllop:      PTR hll_opnd

local   truelabel:  SINT,
        nlabel:     SINT,
        olabel:     SINT,
        buff[16]:   SBYTE

    mov esi,buffer
    mov edi,hllop
    mov truelabel,0

    .while  1

        GetAndExpression( hll, i, tokenarray, ilabel, is_true, esi, edi )
        cmp eax,ERROR
        je  toend

        mov ebx,i
        mov eax,[ebx]
        shl eax,4
        add eax,tokenarray
        .break .if GetCOp( eax ) != COP_OR
        ;
        ; the generated code of last simple expression has to be modified
        ; 1. the last jump must be inverted
        ; 2. a "is_true" label must be created (it's used to jump "behind" the expr)
        ; 3. create a new label
        ; 4. the current "false" label must be generated
        ;
        ; if it is a .REPEAT, step 4 is slightly more difficult, since the "false"
        ; label is already "gone":
        ; 4a. create a new label
        ; 4b. replace the "false" label in the generated code by the new label
        ;
        inc DWORD PTR [ebx]
        mov ebx,[edi].hll_opnd.lastjmp

        .if ebx && !is_true

            InvertJump( ebx )

            .if truelabel == 0

                mov truelabel,GetHllLabel()
            .endif

            .if BYTE PTR [ebx]

                strcat( GetLabelStr( truelabel, &[ebx+4] ), &EOLSTR )
            .endif

            mov ebx,esi
            .if [edi].hll_opnd.lasttruelabel

                ReplaceLabel( ebx, [edi].hll_opnd.lasttruelabel, truelabel )
            .endif

            mov [edi].hll_opnd.lastjmp,0
            mov nlabel,GetHllLabel()
            mov olabel,GetLabel( hll, ilabel )
            strlen(ebx)
            add ebx,eax
            mov eax,hll
            .if [eax].hll_item.cmd == HLL_REPEAT

                ReplaceLabel( buffer, olabel, nlabel )
                sprintf( ebx, "%s%s%s", GetLabelStr( nlabel, &buff ), LABELQUAL, &EOLSTR )
            .else
                sprintf( ebx, "%s%s%s", GetLabelStr( olabel, &buff ), LABELQUAL, &EOLSTR )
                ReplaceLabel( buffer, olabel, nlabel )
            .endif
        .endif
        strlen( esi )
        add esi,eax
        mov [edi].hll_opnd.lasttruelabel,0
    .endw

    .if truelabel

        mov ebx,[edi].hll_opnd.lastjmp
        .if ebx && [edi].hll_opnd.lasttruelabel

            ReplaceLabel( esi, [edi].hll_opnd.lasttruelabel, truelabel )
            strchr( ebx, EOLCHAR )
            mov BYTE PTR [eax+1],0
        .endif

        strlen( esi )
        add esi,eax
        strcat( strcat( GetLabelStr( truelabel, esi ), LABELQUAL ), &EOLSTR )
        mov eax,truelabel
        mov [edi].hll_opnd.lasttruelabel,eax
    .endif

    mov eax,NOT_ERROR

toend:
    ret
GetExpression endp

;
; evaluate the C like boolean expression found in HLL structs
; like .IF, .ELSEIF, .WHILE, .UNTIL and .UNTILCXZ
; might return multiple lines (strings separated by EOLCHAR)
; - i = index for tokenarray[] where expression starts. Is restricted
;    to one source line (till T_FINAL)
; - label: label to jump to if expression is <is_true>!
; is_true:
;   .IF:    FALSE
;   .ELSEIF:    FALSE
;   .WHILE: TRUE
;   .UNTIL: FALSE
;   .UNTILCXZ: FALSE
;   .BREAK .IF:TRUE
;   .CONT .IF: TRUE
;

    assume  ebx: PTR asm_tok

ExpandCStrings proc uses ebx tokenarray:PTR asm_tok

    xor eax,eax

    .repeat

        .break .if !( ModuleInfo.aflag & _AF_ON )

        .for edx = 0, ebx = tokenarray: [ebx].token != T_FINAL: ebx += 16, edx++

            .if [ebx].hll_flags & T_HLL_PROC

                .if Parse_Pass == PASS_1

                    GenerateCString( edx, tokenarray )
                    .break
                .endif

                mov ecx,1
                add ebx,32
                .if [ebx-16].token != T_OP_BRACKET

                    asmerr( 3018, [ebx-32].string_ptr, [ebx-16].string_ptr )
                    .break
                .endif

                .for : [ebx].token != T_FINAL : ebx += 16

                    mov edx,[ebx].string_ptr
                    movzx eax,BYTE PTR [edx]

                    .switch eax
                      .case '"'
                        asmerr(2004, [ebx].string_ptr)
                        .break(1)
                      .case ')'
                        dec ecx
                        .break .ifz
                        .endc
                      .case '('
                        inc ecx
                        .endc
                    .endsw
                .endf
                xor eax,eax
                .break
            .endif
        .endf
    .until  1
toend:
    ret

ExpandCStrings endp


;SymFind proto fastcall :DWORD


GetProc proc private token:LPSTR

    .repeat
        .if !SymFind(token)

            asmerr( 2190 )
            xor eax,eax
            .break
        .endif
        ;
        ; the most simple case: symbol is a PROC
        ;
        .break .if [eax].asym.flag & SFL_ISPROC

        mov ecx,[eax].asym.target_type
        mov dl,[eax].asym.mem_type
        .if dl == MT_PTR && ecx && [ecx].asym.flag & SFL_ISPROC

            mov eax,ecx
            .break
        .endif

        .if dl == MT_PTR && ecx && [ecx].asym.mem_type == MT_PROC

            mov eax,[eax].asym.target_type
            jmp isfnproto
        .endif

        mov ecx,[eax].asym._type
        .if dl == MT_TYPE && ( [ecx].asym.mem_type == MT_PTR || [ecx].asym.mem_type == MT_PROC )
            ;
            ; second case: symbol is a (function?) pointer
            ;
            mov eax,ecx
            .if [eax].asym.mem_type != MT_PROC
                jmp isfnptr
            .endif
        .endif

        isfnproto:
        ;
        ; pointer target must be a PROTO typedef
        ;
        .if [eax].asym.mem_type != MT_PROC

            asmerr( 2190 )
            xor eax,eax
            .break
        .endif

        isfnptr:
        ;
        ; get the pointer target
        ;
        mov eax,[eax].asym.target_type
        .if !eax

            asmerr( 2190 )
            xor eax,eax
            .break
        .endif
    .until  1
    ret

GetProc endp

StripSource proc private uses esi edi ebx,
        i:          UINT,       ; index first token
        e:          UINT,       ; index last token
        tokenarray: ptr asm_tok
local   sym:        ptr asym
local   info:       ptr proc_info
local   curr:       ptr asym
local   proc_id:    ptr asm_tok
local   parg_id:    SINT
local   b[MAX_LINE_LEN]:SBYTE

    xor eax,eax
    mov b,al
    mov proc_id,eax ; foo( 1, bar(...), ...)
    mov parg_id,eax ; foo.paralist[1] = return type[al|ax|eax|[edx::eax|rax]]

    .for eax = &b, ebx = tokenarray, edi = ebx,
         esi = 0: esi < i: esi++, ebx += 16

        .if esi && [ebx].token != T_DOT
            .if [ebx].token == T_COMMA

            .if proc_id

                inc parg_id
            .endif
            .else
            .if [ebx].hll_flags & T_HLL_PROC

                mov proc_id,ebx
                mov parg_id,0
            .endif
            strcat( eax, " " )
            .endif
        .endif
        strcat( eax, [ebx].string_ptr )
    .endf

    mov esi,@CStr( " eax" )
    .if ModuleInfo.Ofssize == USE64

        mov esi,@CStr( " rax" )
    .elseif ModuleInfo.Ofssize == USE16

        mov esi,@CStr( " ax" )
    .endif

    mov eax,proc_id
    .if eax
        .if GetProc([eax].asm_tok.string_ptr)

        mov sym,eax
        mov edx,[eax].nsym.procinfo
        mov info,edx
        mov ecx,[edx].proc_info.paralist

        movzx eax,[eax].asym.langtype
        .if eax == LANG_C || eax == LANG_SYSCALL || eax == LANG_STDCALL || \
           (eax == LANG_FASTCALL && ModuleInfo.Ofssize != USE64)

            .while ecx && [ecx].nsym.nextparam

                mov ecx,[ecx].nsym.nextparam
            .endw
        .endif
        mov curr,ecx

        .while ecx && parg_id
            ;
            ; set paracurr to next parameter
            ;
            mov eax,sym
            movzx eax,[eax].asym.langtype
            .if eax == LANG_C || eax == LANG_SYSCALL || eax == LANG_STDCALL || \
                (eax == LANG_FASTCALL && ModuleInfo.Ofssize != USE64)

                .for eax=curr, ecx=[edx].proc_info.paralist: ecx,
                     [ecx].nsym.nextparam != eax: ecx=[ecx].nsym.nextparam
                .endf
                mov curr,ecx
            .else
                mov ecx,[ecx].nsym.nextparam
            .endif
            dec parg_id
        .endw

        .if ecx
            mov eax,[ecx].asym.total_size
            .switch eax
              .case 1: mov esi,@CStr(" al"):  .endc
              .case 2: mov esi,@CStr(" ax"):  .endc
              .case 4: mov esi,@CStr(" eax"): .endc
              .case 8
                .if ModuleInfo.Ofssize == USE64

                    mov esi,@CStr(" rax")
                .else
                    mov esi,@CStr(" edx::eax")
                .endif
                .endc
               .endsw
        .endif
        .endif
    .endif

    lea eax,b
    strcat(eax, esi)

    mov ebx,e
    shl ebx,4
    .if [ebx+edi].token != T_FINAL

        strcat( eax, " " )
        strcat( eax, [ebx+edi].tokpos )
    .endif

    .if ModuleInfo.list

        push eax
        LstSetPosition()
        pop eax
    .endif
    strcpy(ModuleInfo.currsource, eax)
    Tokenize(eax, 0, edi, TOK_DEFAULT)
    mov ModuleInfo.token_count,eax
    mov eax,STRING_EXPANDED
    ret
StripSource endp

LKRenderHllProc proc private uses esi edi ebx,
        dst:        LPSTR,
        i:          UINT,
        tokenarray: PTR asm_tok
local   b[MAX_LINE_LEN]:SBYTE,
        br_count

    lea esi,b
    mov edi,i
    mov ebx,edi
    shl ebx,4
    add ebx,tokenarray

    strcpy( esi, "invoke " ) ;  assume proc(...)
    strcat( esi, [ebx].string_ptr )

    inc edi
    add ebx,16

    .if [ebx].token == T_OP_BRACKET

        add ebx,16
        add edi,1
        mov br_count,0

        .if [ebx].token != T_CL_BRACKET

            strcat( esi, "," )

            .while  1

                .if [ebx].token == '&'

                    strcat(esi, "addr ")
                    add edi,1
                    add ebx,16
                .endif

                .if [ebx].hll_flags & T_HLL_PROC

                    LKRenderHllProc( dst, edi, tokenarray )
                    cmp eax,ERROR
                    je  toend
                .endif
                movzx eax,[ebx].token
                movzx ecx,[ebx-16].token
                .switch
                  .case eax == T_FINAL
                    .break
                  .case eax == T_OP_BRACKET
                    inc br_count
                    .endc
                  .case eax == T_CL_BRACKET
                    .break .if !br_count
                    dec br_count
                  .case eax == T_COMMA
                  .case eax == T_DOT
                  .case eax == T_OP_SQ_BRACKET
                  .case eax == T_CL_SQ_BRACKET
                  .case ecx == T_OP_SQ_BRACKET
                  .case ecx == T_CL_SQ_BRACKET
                  .case ecx == T_DOT
                    .endc
                  .default
                    strcat(esi, " ")
                    .endc
                .endsw
                strcat(esi, [ebx].string_ptr)
                add edi,1
                add ebx,16
            .endw
        .endif

        .if br_count || [ebx].token != T_CL_BRACKET

            mov eax,ERROR
            jmp toend
        .endif
        add edi,1
    .endif

    ; v2.21 -pe dllimport:<dll> external proto <no args> error
    ;
    ; externals need invoke for the [_]_imp_ prefix
    ;
    mov eax,i
    lea ecx,[eax+3]
    inc eax

    .if edi == eax || ( edi == ecx && br_count == 0 )

        .if SymFind( [ebx-32].string_ptr )

            .if !( [eax].asym.state == SYM_EXTERNAL && [eax].asym.dll )

                xor eax,eax
            .endif
        .endif

        .if !eax

            strcpy( esi, "call" )
            add eax,6
            strcat( esi, eax )
        .endif
    .endif

    mov eax,dst
    .if BYTE PTR [eax] != 0

        strcat( eax, &EOLSTR )
    .endif
    strcat( eax, esi )
    StripSource( i, edi, tokenarray )
toend:
    ret
LKRenderHllProc endp

    assume ebx: NOTHING

RenderHllProc proc private uses esi edi dst:LPSTR,i:UINT,tokenarray:ptr asm_tok

  local oldstat:input_status

    PushInputStatus( &oldstat )
    mov esi,LKRenderHllProc( dst, i, tokenarray )
    mov edi,LclAlloc( MAX_LINE_LEN )
    strcpy( eax, ModuleInfo.currsource )
    PopInputStatus( &oldstat )
    Tokenize( edi, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax
    mov eax,esi
    ret

RenderHllProc endp

;
; write assembly test lines to line queue.
; v2.11: local line buffer removed; src pointer has become a parameter.
;

QueueTestLines proc uses esi edi src:LPSTR

    mov esi,src

    .while esi

        mov edi,esi
        .if strchr( esi, EOLCHAR )

            mov BYTE PTR [eax],0
            inc eax
        .endif
        mov esi,eax

        .if BYTE PTR [edi]
if 0
            xor edx,edx
            .if esi

                mov eax,[esi]
                mov ecx,[edi]
                ;
                ; jmp @C0003
                ; jmp @C0003
                ;
                .if eax == ' pmj' && eax == ecx

                    mov eax,[esi+4]
                    .if eax == [edi+4]
                        mov ax,[esi+8]
                        .if ax == [edi+8]

                            inc edx
                        .endif
                    .endif
                .endif
            .endif

            .if !edx

                AddLineQueue(edi)
            .endif
else
                AddLineQueue(edi)
endif
        .endif
    .endw

    mov eax,NOT_ERROR
    ret

QueueTestLines endp

ExpandHllProc proc uses esi edi dst:LPSTR, i:SINT, tokenarray:PTR asm_tok

    mov eax,dst
    mov BYTE PTR [eax],0

    .if ModuleInfo.aflag & _AF_ON

        mov esi,i
        mov edi,esi
        shl edi,4
        add edi,tokenarray

        .while esi < ModuleInfo.token_count

            .if [edi].asm_tok.hll_flags & T_HLL_PROC

                ExpandCStrings( tokenarray )
                RenderHllProc( dst, esi, tokenarray )
                cmp eax,ERROR
                je  toend
                .break
            .endif
            add edi,16
            add esi,1
        .endw
    .endif
    mov eax,NOT_ERROR
toend:
    ret
ExpandHllProc endp

EvaluateHllExpression proc uses esi edi ebx,
        hll:        ptr hll_item,
        i:          ptr SINT,
        tokenarray: ptr asm_tok,
        ilabel:     SDWORD,
        is_true:    SINT,
        buffer:     LPSTR
local   hllop:      hll_opnd,
        b[MAX_LINE_LEN]:SBYTE

    mov esi,i
    mov ebx,tokenarray

    xor eax,eax
    mov hllop.lastjmp,eax
    mov hllop.lasttruelabel,eax

    mov edx,hll
    mov eax,[edx].hll_item.flags
    and eax,HLLF_EXPRESSION

    .if ModuleInfo.aflag & _AF_ON && !eax && [ebx].asm_tok.hll_flags & T_HLL_DELAY

        mov edi,[esi]
        .while edi < ModuleInfo.token_count

            mov eax,edi
            shl eax,4
            .if [ebx+eax].asm_tok.hll_flags & T_HLL_MACRO

                strcpy( buffer, [ebx].asm_tok.tokpos )
                mov eax,hll
                or  [eax].hll_item.flags,HLLF_EXPRESSION

                .if [ebx].asm_tok.hll_flags & T_HLL_DELAYED

                    or [eax].hll_item.flags,HLLF_DELAYED
                .endif

                mov eax,NOT_ERROR
                jmp toend
            .endif
            add edi,1
        .endw
    .endif

    lea edi,b

    .if ExpandHllProc( edi, [esi], ebx ) != ERROR

        mov ecx,buffer
        mov BYTE PTR [ecx],0

        .if GetExpression( hll, esi, ebx, ilabel, is_true,
                ecx, &hllop ) != ERROR

            mov eax,[esi]
            shl eax,4
            add ebx,eax

            .if [ebx].asm_tok.token != T_FINAL

                asmerr( 2154 )
                jmp toend
            .endif

            mov eax,hll
            mov eax,[eax].hll_item.flags
            and eax,HLLF_IFD or HLLF_IFW or HLLF_IFB

            .if eax && BYTE PTR [edi]
                ;
                ; Parse a "cmp ax" or "test ax,ax" and resize
                ; to B/W/D ([r|e]ax).
                ;
                mov edx,buffer
                mov ecx,[edx]
                .while BYTE PTR [edx] > ' '

                    add edx,1
                .endw
                .while BYTE PTR [edx] == ' '

                    add edx,1
                .endw

                mov ebx,[edx]
                .if bl == 'e' || bl == 'r'

                    shr ebx,8
                .endif

                .if bh == 'x'

                    .if ecx == 'tset'

                        xor ecx,ecx
                    .endif
                    ;
                    ; ax , ax   -< eax,eax>
                    ; rax , rax -<  al ,  al>
                    ;
                    lea ebx,[edx+4]
                    .while  byte ptr [ebx] == ' ' || \
                        byte ptr [ebx] == ','

                        inc ebx
                    .endw

                    .switch eax

                      .case HLLF_IFD
                        .if ModuleInfo.Ofssize == USE64

                            mov BYTE PTR [edx],'e'
                            .if !ecx

                                mov BYTE PTR [ebx],'e'
                            .endif

                        .elseif ModuleInfo.Ofssize == USE16

                            mov ax,[edx]
                            .if BYTE PTR [edx+2] != ' '

                                .if ecx

                                    mov DWORD PTR [edx-4],'ro '
                                .else
                                    mov DWORD PTR [edx-5],' dna'
                                .endif
                                dec edx
                            .endif
                            mov [edx+1],ax
                            mov BYTE PTR [edx],'e'
                            .if !ecx

                                mov BYTE PTR [ebx-1],'e'
                            .endif
                        .endif
                        .endc

                      .case HLLF_IFW
                        .if ModuleInfo.Ofssize != USE16

                            mov eax,' '
                            mov [edx],al
                            .if !ecx

                                mov [ebx],al
                            .endif
                        .endif
                        .endc

                      .case HLLF_IFB
                        mov eax,' l'
                        .if ModuleInfo.Ofssize == USE16

                            mov [edx+1],al
                            .if !ecx

                                mov [ebx+1],al
                            .endif
                        .else
                            mov [edx],ah
                            mov [edx+2],al

                            .if !ecx

                                mov [ebx],ah
                                mov [ebx+2],al
                            .endif
                        .endif
                        .endc
                    .endsw
                .endif
            .endif

            .if BYTE PTR [edi]

                strlen( edi )
                mov WORD PTR [edi+eax],EOLCHAR
                strcat( edi, buffer )
                strcpy( buffer, edi )
            .endif

            mov eax,NOT_ERROR
        .endif
    .endif
toend:
    ret

EvaluateHllExpression endp

ExpandHllExpression proc uses esi edi ebx,
        hll:        PTR hll_item,
        i:          PTR SINT,
        tokenarray: PTR asm_tok,
        ilabel:     SINT,
        is_true:    SINT,
        buffer:     LPSTR
local   rc:         DWORD,
        oldstat:    input_status,
        delayed:    BYTE

    mov rc,NOT_ERROR
    mov esi,hll
    mov ebx,tokenarray
    mov edi,buffer

    PushInputStatus( &oldstat )

    .if [esi].hll_item.flags & HLLF_WHILE

        mov edi,[esi].hll_item.condlines
    .endif

    strcpy( ModuleInfo.currsource, edi )
    Tokenize( ModuleInfo.currsource, 0, ebx, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax

    .if Parse_Pass == PASS_1

        .if ModuleInfo.line_queue.head

            RunLineQueue()
        .endif

        .if [esi].hll_item.flags & HLLF_DELAYED

            mov NoLineStore,1
            ExpandLine( ModuleInfo.currsource, ebx )
            mov NoLineStore,0
            cmp eax,NOT_ERROR
            jne toend
        .endif
        and [esi].hll_item.flags,not HLLF_WHILE
        EvaluateHllExpression( hll, i, ebx, ilabel, is_true, buffer )
        mov rc,eax
        QueueTestLines( buffer )

    .else
        .if ModuleInfo.list

            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif

        RunLineQueue()
        ExpandLine( ModuleInfo.currsource, ebx )
        mov rc,eax

        .if eax == NOT_ERROR

            .if [esi].hll_item.flags & HLLF_WHILE

                and [esi].hll_item.flags,not HLLF_WHILE
            .endif
            EvaluateHllExpression( esi, i, ebx, ilabel, is_true, buffer )
            mov rc,eax
            QueueTestLines( buffer )
        .endif
    .endif

    PopInputStatus( &oldstat )
    Tokenize( ModuleInfo.currsource, 0, ebx, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax
    mov eax,hll
    and [eax].hll_item.flags,not HLLF_EXPRESSION
    mov eax,rc
toend:
    ret
ExpandHllExpression endp

CheckCXZLines proc private uses esi edi ebx p
    ;
    ; for .UNTILCXZ: check if expression is simple enough. what's acceptable
    ; is ONE condition, and just operators == and != Constants (0 or != 0)
    ; are also accepted
    ;
    mov esi,p
    mov edi,1
    xor ebx,ebx
    ;
    ; syntax ".untilcxz 1" has a problem: there's no "jmp" generated at all
    ; if this syntax is to be supported, activate the #if below.
    ;
    mov eax,[esi]

    .while al

        .if al == EOLCHAR

            mov edi,1
            add ebx,edi

        .elseif edi

            xor edi,edi
            .if al == 'j'

                shr eax,8
                .if al == 'm' && !ebx
                    ;
                    ; 2 chars, to replace "jmp" by "loope"
                    ;
                    mov edx,2
                .elseif ebx == 1 && (al == 'z' || ax == 'zn')
                    ;
                    ; 3 chars, to replace "jz"/"jnz" by
                    ; "loopz"/"loopnz"
                    ;
                    mov edx,3
                .else
                    ; anything else is "too complex"
                    mov ebx,3
                    .break
                .endif

                strlen( esi )
                .whiles eax >= 0

                    add esi,eax
                    mov cl,[esi]
                    mov [esi+edx],cl
                    sub esi,eax
                    dec eax
                .endw

                mov eax,"pool"
                mov [esi],eax
                .if edx == 2

                    mov BYTE PTR [esi+4],'e'
                .endif
            .endif
        .endif

        add esi,1
        mov eax,[esi]
    .endw

    mov eax,NOT_ERROR
    .if ebx > 2

        mov eax,ERROR
    .endif
    ret

CheckCXZLines endp

RenderUntilXX proc private uses edi hll:PTR hll_item, cmd:UINT

local   buffer[32]:SBYTE

    mov eax,cmd
    mov ecx,T_CX - T_AX
    .switch eax
      .case T_DOT_UNTILAXZ : mov ecx,T_AX - T_AX : .endc
      .case T_DOT_UNTILBXZ : mov ecx,T_BX - T_AX : .endc
      .case T_DOT_UNTILDXZ : mov ecx,T_DX - T_AX : .endc
    .endsw
    .if ModuleInfo.Ofssize == USE16
        add ecx,T_AX
    .elseif ModuleInfo.Ofssize == USE32
        add ecx,T_EAX
    .else
        add ecx,T_RAX
    .endif
    AddLineQueueX( " %r %r", T_DEC, ecx )
    mov edx,hll
    mov ecx,[edx].hll_item.labels[LSTART*4]
    AddLineQueueX( " jnz %s", GetLabelStr( ecx, &buffer ) )
    ret

RenderUntilXX endp

GetJumpString proc private uses edx ecx cmd

  local buffer[32]:SBYTE

    option switch:table

    mov eax,cmd
    xor ecx,ecx
    .switch eax

      .case T_DOT_IFA
      .case T_DOT_UNTILA
      .case T_DOT_WHILEA
        mov ecx,T_JBE
        .endc
      .case T_DOT_IFB
      .case T_DOT_IFC
      .case T_DOT_UNTILB
      .case T_DOT_WHILEB
        mov ecx,T_JAE
        .endc
      .case T_DOT_IFG
      .case T_DOT_UNTILG
      .case T_DOT_WHILEG
        mov ecx,T_JLE
        .endc
      .case T_DOT_IFL
      .case T_DOT_UNTILL
      .case T_DOT_WHILEL
        mov ecx,T_JGE
        .endc
      .case T_DOT_IFO
      .case T_DOT_UNTILO
      .case T_DOT_WHILEO
        mov ecx,T_JNO
        .endc
      .case T_DOT_IFP
      .case T_DOT_UNTILP
      .case T_DOT_WHILEP
        mov ecx,T_JNP
        .endc
      .case T_DOT_IFS
      .case T_DOT_UNTILS
      .case T_DOT_WHILES
        mov ecx,T_JNS
        .endc
      .case T_DOT_IFZ
      .case T_DOT_WHILEZ
      .case T_DOT_UNTILZ
        mov ecx,T_JNE
        .endc
      .case T_DOT_IFNA
      .case T_DOT_UNTILNA
      .case T_DOT_WHILENA
        mov ecx,T_JA
        .endc
      .case T_DOT_IFNB
      .case T_DOT_IFNC
      .case T_DOT_UNTILNB
      .case T_DOT_WHILENB
        mov ecx,T_JB
        .endc
      .case T_DOT_IFNG
      .case T_DOT_UNTILNG
      .case T_DOT_WHILENG
        mov ecx,T_JG
        .endc
      .case T_DOT_IFNL
      .case T_DOT_UNTILNL
      .case T_DOT_WHILENL
        mov ecx,T_JL
        .endc
      .case T_DOT_IFNO
      .case T_DOT_UNTILNO
      .case T_DOT_WHILENO
        mov ecx,T_JO
        .endc
      .case T_DOT_IFNP
      .case T_DOT_UNTILNP
      .case T_DOT_WHILENP
        mov ecx,T_JP
        .endc
      .case T_DOT_IFNS
      .case T_DOT_UNTILNS
      .case T_DOT_WHILENS
        mov ecx,T_JS
        .endc
      .case T_DOT_IFNZ
      .case T_DOT_WHILENZ
      .case T_DOT_UNTILNZ
        mov ecx,T_JZ
        .endc
      .default
        asmerr(1011)
    .endsw

    GetResWName( ecx, &buffer )
    .if byte ptr [eax+2] == 0

        mov word ptr [eax+2],' '
    .endif
    ret

GetJumpString endp

    assume  ebx: ptr asm_tok
    assume  esi: ptr hll_item

; .IF, .WHILE, .SWITCH or .REPEAT directive

HllStartDir proc uses esi edi ebx i:SINT, tokenarray:ptr asm_tok

local   rc:         SINT,
        cmd:        UINT,
        buff[16]:   SBYTE,
        buffer[MAX_LINE_LEN]:SBYTE

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,buffer

    mov eax,i
    shl eax,4
    ;
    ; added v2.22 to seperate:
    ;
    ; .IFS from .IFS <expression>
    ; .IFB from .IFB <expression>
    ;
    movzx ecx,[ebx+eax+16].token
    push ecx
    mov eax,[ebx+eax].tokval
    mov cmd,eax
    ;
    ; skip directive
    ;
    inc i
    ;
    ; v2.06: is there an item on the free stack?
    ;
    mov esi,ModuleInfo.HllFree
    .if !esi

        mov esi,LclAlloc( sizeof( hll_item ) )
    .endif

    ExpandCStrings( tokenarray )

    ; structure for .IF .ELSE .ENDIF
    ;   cond jump to LTEST-label
    ;   ...
    ;   jmp LEXIT
    ; LTEST:
    ;   ...
    ; LEXIT:

    ; structure for .IF .ELSEIF
    ;   cond jump to LTEST
    ;   ...
    ;   jmp LEXIT
    ; LTEST:
    ;   cond jump to (new) LTEST
    ;   ...
    ;   jmp LEXIT
    ; LTEST:
    ;   ...

    ; structure for .WHILE, .SWITCH and .REPEAT:
    ;  jmp LTEST (for .WHILE and .SWITCH only)
    ; LSTART:
    ; ...
    ; LTEST: (jumped to by .continue)
    ;    a) test end condition, cond jump to LSTART label
    ;    b) unconditional jump to LSTART label
    ; LEXIT: (jumped to by .BREAK)

    xor eax,eax
    mov [esi].labels[LEXIT*4],eax
    mov [esi].flags,eax
    mov eax,cmd
    pop ecx

    .switch eax

      .case T_DOT_IF

        mov [esi].cmd,HLL_IF
        mov [esi].labels[LSTART*4],0 ; not used by .IF
        mov [esi].labels[LTEST*4],GetHllLabel()
        ;
        ; get the C-style expression, convert to ASM code lines
        ;
        EvaluateHllExpression( esi, &i, ebx, LTEST, 0, edi )
        mov rc,eax
        .if eax == NOT_ERROR

            QueueTestLines( edi )
            ;
            ; if no lines have been created, the LTEST label isn't needed
            ;
            .if BYTE PTR [edi] == NULLC
                mov [esi].labels[LTEST*4],0
            .endif
        .endif
        .endc

      .case T_DOT_WHILE

        or  [esi].flags,HLLF_WHILE
      .case T_DOT_REPEAT
        ;
        ; create the label to start of loop
        ;
        mov [esi].labels[LSTART*4],GetHllLabel()
        ;
        ; v2.11: test label is created only if needed
        ;
        mov [esi].labels[LTEST*4],0

        .if cmd != T_DOT_REPEAT

            mov [esi].cmd,HLL_WHILE
            mov [esi].condlines,0
            mov eax,i
            shl eax,4

            .if [ebx+eax].asm_tok.token != T_FINAL

                mov ecx,[esi].flags
                mov eax,cmd

                .switch eax
                  .case T_DOT_WHILESB
                    or ecx,HLLF_IFS
                  .case T_DOT_WHILEB
                    or ecx,HLLF_IFB
                    .endc
                  .case T_DOT_WHILESW
                    or ecx,HLLF_IFS
                  .case T_DOT_WHILEW
                    or ecx,HLLF_IFW
                    .endc
                  .case T_DOT_WHILESD
                    or ecx,HLLF_IFS
                  .case T_DOT_WHILED
                    or ecx,HLLF_IFD
                    .endc
                  .case T_DOT_WHILES
                    or ecx,HLLF_IFS
                    .endc
                .endsw
                mov [esi].flags,ecx
                EvaluateHllExpression( esi, &i, ebx, LSTART, 1, edi )
                mov rc,eax

                .if eax == NOT_ERROR

                    alloc_cond:

                    strlen( edi )
                    inc eax
                    push    eax
                    LclAlloc( eax )
                    pop ecx
                    mov [esi].condlines,eax
                    memcpy( eax, edi, ecx )
                .endif
            .elseif cmd != T_DOT_WHILE

                GetLabelStr( [esi].labels[LSTART*4], &[edi+20] )
                strcpy( edi, GetJumpString( cmd ) )
                strcat( edi, " " )
                strcat( edi, &[edi+20] )
                InvertJump( edi )
                jmp alloc_cond
            .else
                ;
                ; just ".while" without expression is accepted
                ;
                mov BYTE PTR [edi],NULLC
            .endif

            ; create a jump to test label
            ; optimisation: if line at 'test' label is just a jump,
            ; dont create label and don't jump!
            ;
            .if _memicmp( edi, "jmp", 3 )

                mov [esi].labels[LTEST],GetHllLabel()
                AddLineQueueX( "jmp %s", GetLabelStr( [esi].labels[LTEST*4], &buff ) )
            .endif
        .else
            mov [esi].cmd,HLL_REPEAT
        .endif

        mov cl,ModuleInfo.loopalign
        .if cl

            mov eax,1
            shl eax,cl
            AddLineQueueX( "ALIGN %d", eax )
        .endif
        AddLineQueueX( "%s%s", GetLabelStr( [esi].labels[LSTART*4], &buff ), LABELQUAL )
        .endc

      .case T_DOT_IFS
        .if ecx != T_FINAL

            or [esi].flags,HLLF_IFS
            .gotosw(T_DOT_IF)
        .endif
      .case T_DOT_IFB
      .case T_DOT_IFC
        .if ecx != T_FINAL

            or [esi].flags,HLLF_IFB
            .gotosw(T_DOT_IF)
        .endif
      .case T_DOT_IFA .. T_DOT_IFNZ
        mov [esi].cmd,HLL_IF
        mov [esi].labels[LSTART*4],0
        mov [esi].labels[LTEST*4],GetHllLabel()
        GetLabelStr( [esi].labels[LTEST*4], &buff )
        .if GetJumpString( cmd )

            strcat( strcpy( &buffer, eax ), " " )
            lea ecx,buff
            AddLineQueue( strcat( eax, ecx ) )
        .endif
        .endc

      .case T_DOT_IFSD
        or  [esi].flags,HLLF_IFS
      .case T_DOT_IFD
        or  [esi].flags,HLLF_IFD
        .gotosw(T_DOT_IF)
      .case T_DOT_IFSW
        or  [esi].flags,HLLF_IFS
      .case T_DOT_IFW
        or  [esi].flags,HLLF_IFW
        .gotosw(T_DOT_IF)
      .case T_DOT_IFSB
        or  [esi].flags,HLLF_IFB OR HLLF_IFS
        .gotosw(T_DOT_IF)

      .case T_DOT_WHILEA .. T_DOT_WHILESD
        .gotosw(T_DOT_WHILE)
    .endsw

    mov eax,i
    shl eax,4

    .if ![esi].flags && ([ebx+eax].asm_tok.token != T_FINAL && rc == NOT_ERROR)

        asmerr( 2008, [ebx+eax].asm_tok.tokpos )
        mov rc,eax
    .endif
    ;
    ; v2.06: remove the item from the free stack
    ;
    .if esi == ModuleInfo.HllFree

        mov eax,[esi].next
        mov ModuleInfo.HllFree,eax
    .endif
    mov eax,ModuleInfo.HllStack
    mov [esi].next,eax
    mov ModuleInfo.HllStack,esi

    .if ModuleInfo.list

        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif

    .if ModuleInfo.line_queue.head  ; might be NULL! (".if 1")

        RunLineQueue()
    .endif

    mov eax,rc

toend:
    ret
HllStartDir endp

;
; .ENDIF, .ENDW, .UNTIL and .UNTILCXZ directives.
; These directives end a .IF, .WHILE or .REPEAT block.
;
HllEndDir proc uses esi edi ebx i:SINT, tokenarray:PTR asm_tok

  local rc:SINT, cmd:SINT, buffer[MAX_LINE_LEN]:SBYTE

    mov esi,ModuleInfo.HllStack

    .if !esi

        asmerr( 1011 )
        jmp toend
    .endif

    mov eax,[esi].next
    mov ecx,ModuleInfo.HllFree
    mov ModuleInfo.HllStack,eax
    mov [esi].next,ecx
    mov ModuleInfo.HllFree,esi
    mov rc,NOT_ERROR
    lea edi,buffer
    mov ebx,tokenarray
    mov ecx,[esi].cmd
    mov edx,i
    shl edx,4
    mov eax,[ebx+edx].tokval
    mov cmd,eax

    .switch eax

      .case T_DOT_ENDIF
        .if ecx != HLL_IF

            asmerr( 1011 )
            jmp toend
        .endif
        inc i
        ;
        ; if a test label isn't created yet, create it
        ;
        mov eax,[esi].labels[LTEST*4]
        .if eax

            AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
        .endif
        .endc

      .case T_DOT_ENDW

        .if ecx != HLL_WHILE

            asmerr( 1011 )
            jmp toend
        .endif
        ;
        ; create test label
        ;
        mov eax,[esi].labels[LTEST*4]
        .if eax

            AddLineQueueX( "%s%s",
                GetLabelStr( eax, edi ), LABELQUAL )
        .endif

        inc i

        .if [esi].flags & HLLF_EXPRESSION

            ExpandHllExpression(
                esi, &i, tokenarray, LSTART, 1, edi )
        .else
            QueueTestLines( [esi].condlines )
        .endif
        .endc

      .case T_DOT_UNTILAXZ
      .case T_DOT_UNTILBXZ
      .case T_DOT_UNTILCXZ
      .case T_DOT_UNTILDXZ

        .if ecx != HLL_REPEAT

            asmerr( 1010, [ebx+edx].string_ptr )
            jmp toend
        .endif

        inc i
        lea ebx,[ebx+edx+16]

        mov eax,[esi].labels[LTEST*4]
        .if eax
            ;
            ; v2.11: LTEST only needed if .CONTINUE has occured
            ;
            AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
        .endif
        ;
        ; read in optional (simple) expression
        ;
        .if [ebx].token != T_FINAL

            mov ecx,LSTART
            .if !Options.masm_compat_gencode && \
                ModuleInfo.aflag & _AF_ON

                ;
                ; <expression> ? .BREAK
                ;
                .if ![esi].labels[LEXIT*4]

                    mov [esi].labels[LEXIT*4],GetHllLabel()
                .endif
                mov ecx,LEXIT
            .endif

            EvaluateHllExpression( esi, &i, tokenarray, ecx, 0, edi )
            mov rc,eax

            .if eax == NOT_ERROR

                .if !(ModuleInfo.aflag & _AF_ON) || \
                    (Options.masm_compat_gencode && \
                    cmd == T_DOT_UNTILCXZ)

                    mov rc,CheckCXZLines(edi)
                .endif

                .if eax == NOT_ERROR
                    ;
                    ; write condition lines
                    ;
                    QueueTestLines( edi )
                    .if !Options.masm_compat_gencode && \
                        ModuleInfo.aflag & _AF_ON

                        RenderUntilXX( esi, cmd )
                    .endif
                .else
                    asmerr( 2062 )
                .endif
            .endif
        .else
            .if !(ModuleInfo.aflag & _AF_ON) || \
                Options.masm_compat_gencode ;&& cmd == T_DOT_UNTILCXZ

                AddLineQueueX( "loop %s",
                    GetLabelStr( [esi].labels[LSTART*4], edi ) )
            .else

                RenderUntilXX( esi, cmd )
            .endif
        .endif
        .endc

      .case T_DOT_UNTILA .. T_DOT_UNTILSD
      .case T_DOT_UNTIL

        .if ecx != HLL_REPEAT

            asmerr( 1010, [ebx+edx].string_ptr )
            jmp toend
        .endif

        inc i
        lea ebx,[ebx+edx+16]
        mov eax,[esi].labels[LTEST*4]

        .if eax ; v2.11: LTEST only needed if .CONTINUE has occured

            AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
        .endif
        ;
        ; read in (optional) expression
        ; if expression is missing, just generate nothing
        ;
        .if [ebx].token != T_FINAL

            mov ecx,[esi].flags
            mov eax,cmd

            .switch eax
              .case T_DOT_UNTILSB
                or ecx,HLLF_IFS
              .case T_DOT_UNTILB
                or ecx,HLLF_IFB
                .endc
              .case T_DOT_UNTILSW
                or ecx,HLLF_IFS
              .case T_DOT_UNTILW
                or ecx,HLLF_IFW
                .endc
              .case T_DOT_UNTILSD
                or ecx,HLLF_IFS
              .case T_DOT_UNTILD
                or ecx,HLLF_IFD
                .endc
              .case T_DOT_UNTILS
                or ecx,HLLF_IFS
                .endc
            .endsw
            mov [esi].flags,ecx

            EvaluateHllExpression( esi, &i, tokenarray, LSTART, 0, edi )
            mov rc,eax

            .if eax == NOT_ERROR

                QueueTestLines( edi )   ; write condition lines
            .endif
        .elseif cmd != T_DOT_UNTIL

            GetLabelStr( [esi].labels[LSTART*4], &[edi+20] )
            strcpy( edi, GetJumpString( cmd ) )
            strcat( edi, " " )
            strcat( edi, &[edi+20] )
            AddLineQueue( edi )
        .endif
        .endc
    .endsw

    ;
    ; create the exit label if it has been referenced
    ;
    mov eax,[esi].labels[LEXIT*4]
    .if eax

        AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
    .endif

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    .if [ebx].token != T_FINAL && rc == NOT_ERROR
        asmerr(2008, [ebx].tokpos )
        mov rc,ERROR
    .endif

    .if ModuleInfo.list

        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    ;
    ; v2.11: always run line-queue if it's not empty.
    ;
    .if ModuleInfo.line_queue.head

        RunLineQueue()
    .endif
    mov eax,rc
toend:
    ret
HllEndDir endp

_lk_HllContinueIf proc i:ptr sdword, tokenarray:ptr asm_tok

  local rc:SINT, buff[16]:SBYTE

    mov rc,NOT_ERROR

    .if [ebx].token != T_FINAL

        .if [ebx].token == T_DIRECTIVE

            xor edx,edx
            mov eax,[ebx].tokval
            .switch eax
              .case T_DOT_IFSD
                or edx,HLLF_IFS
              .case T_DOT_IFD
                or edx,HLLF_IFD
              .case T_DOT_IF

                push [esi].cmd
                push [esi].condlines
                push [esi].flags
                mov [esi].flags,edx
                mov [esi].cmd,HLL_BREAK
                mov eax,i
                inc dword ptr [eax]
                EvaluateHllExpression(esi, eax, tokenarray, ecx, 1, edi)
                mov rc,eax
                .if eax == NOT_ERROR

                    QueueTestLines( edi )
                .endif
                pop [esi].flags
                pop [esi].condlines
                pop [esi].cmd
                .endc

              .case T_DOT_IFSB
                or edx,HLLF_IFS or HLLF_IFB
                .gotosw(T_DOT_IF)
              .case T_DOT_IFSW
                or edx,HLLF_IFS
              .case T_DOT_IFW
                or edx,HLLF_IFW
                .gotosw(T_DOT_IF)

              .case T_DOT_IFS
                .if [ebx+16].token != T_FINAL

                    or edx,HLLF_IFS
                    .gotosw(T_DOT_IF)
                .endif
              .case T_DOT_IFB
              .case T_DOT_IFC
                .if [ebx+16].token != T_FINAL

                    or edx,HLLF_IFB
                    .gotosw(T_DOT_IF)
                .endif
              .case T_DOT_IFA .. T_DOT_IFNZ

                mov eax,i
                inc dword ptr [eax]
                GetLabelStr([esi].labels[ecx*4], &buff)
                strcpy(edi, GetJumpString( [ebx].tokval))
                strcat(edi, " ")
                strcat(edi, &buff)
                InvertJump(edi)
                AddLineQueue(edi)
                .endc
            .endsw
        .endif
    .else
        push edx
        AddLineQueueX("jmp %s", GetLabelStr([esi].labels[ecx*4], edi))

        pop edx
        .if [edx].hll_item.cmd == HLL_SWITCH
            ;
            ; unconditional jump from .case
            ; - set flag to skip exit-jumps
            ;
            mov esi,edx
            mov eax,esi

            .while [esi].caselist

                mov esi,[esi].caselist
            .endw
            .if eax != esi

                or [esi].flags,HLLF_ENDCOCCUR
            .endif
        .endif
    .endif

    mov eax,rc
    ret

_lk_HllContinueIf endp

;
; .ELSE, .ELSEIF, .CONTINUE and .BREAK directives.
; .ELSE, .ELSEIF:
;    - create a jump to exit label
;    - render test label if it was referenced
;    - for .ELSEIF, create new test label and evaluate expression
; .CONTINUE, .BREAK:
;    - jump to test / exit label of innermost .WHILE/.REPEAT block
;
HllExitDir proc USES esi edi ebx i, tokenarray:ptr asm_tok

local   rc: SINT,
        cont0:  SINT,
        cmd:    SINT,
        buff    [16]:SBYTE,
        buffer  [MAX_LINE_LEN]:SBYTE

    mov esi,ModuleInfo.HllStack
    .if !esi

        asmerr(1011)
        jmp toend
    .endif

    ExpandCStrings( tokenarray )

    lea edi,buffer
    mov rc,NOT_ERROR
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    mov eax,[ebx].tokval
    mov cmd,eax
    xor ecx,ecx     ; exit level 0,1,2,3
    mov cont0,ecx

    .switch eax

      .case T_DOT_ELSEIF
        or [esi].flags,HLLF_ELSEIF
      .case T_DOT_ELSE
        .if [esi].cmd != HLL_IF

            asmerr( 1010, [ebx].string_ptr )
            jmp toend
        .endif
        ;
        ; v2.08: check for multiple ELSE clauses
        ;
        .if [esi].flags & HLLF_ELSEOCCUR

            asmerr( 2142 )
            jmp toend
        .endif
        push    eax
        ;
        ; the exit label is only needed if an .ELSE branch exists.
        ; That's why it is created delayed.
        ;
        .if [esi].labels[LEXIT*4] == 0

            mov [esi].labels[LEXIT*4],GetHllLabel()
        .endif
        AddLineQueueX( "jmp %s", GetLabelStr( [esi].labels[LEXIT*4], edi ) )

        .if [esi].labels[LTEST*4] > 0

            AddLineQueueX( "%s%s", GetLabelStr( [esi].labels[LTEST*4], edi ), LABELQUAL )
            mov [esi].labels[LTEST*4],0
        .endif

        inc i
        pop eax
        .if eax == T_DOT_ELSEIF
            ;
            ; create new labels[LTEST] label
            ;
            mov [esi].labels[LTEST*4],GetHllLabel()
            EvaluateHllExpression( esi, &i, tokenarray, LTEST, 0, edi )
            mov rc,eax

            .if eax == NOT_ERROR

                .if [esi].flags & HLLF_EXPRESSION

                    ExpandHllExpression( esi, &i, tokenarray, LTEST, 0, edi )
                    mov eax,ModuleInfo.token_count
                    mov i,eax
                .else
                    QueueTestLines( edi )
                .endif
            .endif
        .else
            or [esi].flags,HLLF_ELSEOCCUR
        .endif
        .endc

      .case T_DOT_BREAK
      .case T_DOT_CONTINUE

        .if [ebx+16].token == T_OP_BRACKET && [ebx+16*3].token == T_CL_BRACKET

            .if cmd == T_DOT_CONTINUE

                mov eax,[ebx+32].string_ptr
                .if byte ptr [eax] == '0'

                    mov cont0,1
                .endif
            .endif

            push atol([ebx+32].string_ptr)

            strcat(strcpy(edi, [ebx].string_ptr), " ")
            Tokenize( strcat(eax, [ebx+4*16].tokpos), 0, tokenarray, TOK_DEFAULT )
            mov ModuleInfo.token_count,eax

            mov eax,cmd
            mov ebx,tokenarray
            mov i,0
            pop ecx
        .endif

        .for edx = esi: esi,
            ([esi].cmd == HLL_IF || [esi].cmd == HLL_SWITCH): esi=[esi].next
        .endf

        .while esi && ecx
            .for esi = [esi].next: esi,
                ([esi].cmd == HLL_IF || [esi].cmd == HLL_SWITCH): esi=[esi].next
            .endf
            dec  ecx
        .endw

        .if !esi

            asmerr( 1011 )
            jmp toend
        .endif
        ;
        ; v2.11: create 'exit' and 'test' labels delayed.
        ;
        .if eax == T_DOT_BREAK

            .if [esi].labels[LEXIT*4] == 0

                mov [esi].labels[LEXIT*4],GetHllLabel()
            .endif
            mov ecx,LEXIT
        .else
            ;
            ; 'test' is not created for .WHILE loops here; because
            ; if it doesn't exist, there's no condition to test.
            ;
            .if [esi].cmd == HLL_REPEAT && [esi].labels[LTEST*4] == 0

                mov [esi].labels[LTEST*4],GetHllLabel()
            .endif

            mov ecx,LTEST
            .if cont0 == 1

                mov ecx,LSTART
            .elseif [esi].labels[LTEST*4] == 0

                mov ecx,LSTART
            .endif
        .endif
        ;
        ; .BREAK .IF ... or .CONTINUE .IF ?
        ;
        inc i
        add ebx,16
        mov rc,_lk_HllContinueIf(&i, tokenarray)
        .endc
    .endsw

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray

    .if [ebx].token != T_FINAL && rc == NOT_ERROR

        asmerr( 2008, [ebx].tokpos )
        mov rc,ERROR
    .endif

    .if ModuleInfo.list

        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    ;
    ; v2.11: always run line-queue if it's not empty.
    ;
    .if ModuleInfo.line_queue.head

        RunLineQueue()
    .endif

    mov eax,rc
toend:
    ret
HllExitDir endp

; check if an hll block has been left open. called after pass 1

HllCheckOpen proc

    .if ModuleInfo.HllStack

        asmerr( 1010, ".if-.repeat-.while" )
    .endif
    ret

HllCheckOpen endp

; HllInit() is called for each pass

HllInit proc pass

    mov ModuleInfo.hll_label,0  ; init hll label counter
    ret

HllInit endp

    END
