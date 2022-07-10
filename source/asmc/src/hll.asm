; HLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include stdio.inc
include stdlib.inc
include malloc.inc

include asmc.inc
include hll.inc
include hllext.inc
include parser.inc
include types.inc
include assume.inc
include fastpass.inc
include proc.inc

define B <BYTE PTR>
define W <WORD PTR>
define D <DWORD PTR>


.pragma warning(disable: 6004)

; c binary ops.
; Order of items COP_EQ - COP_LE  and COP_ZERO - COP_OVERFLOW
; must not be changed.

.enum {
    COP_NONE,
    COP_EQ,       ; ==
    COP_NE,       ; !=
    COP_GT,       ; >
    COP_LT,       ; <
    COP_GE,       ; >=
    COP_LE,       ; <=
    COP_AND,      ; &&
    COP_OR,       ; ||
    COP_ANDB,     ; &
    COP_NEG,      ; !
    COP_ZERO,     ; ZERO?  not really a valid C operator
    COP_CARRY,    ; CARRY?     not really a valid C operator
    COP_SIGN,     ; SIGN?  not really a valid C operator
    COP_PARITY,   ; PARITY?   not really a valid C operator
    COP_OVERFLOW  ; OVERFLOW? not really a valid C operator
    }

.data

EOLSTR          db EOLCHAR,0
;
; items in table below must match order COP_ZERO - COP_OVERFLOW
;
flaginstr       db 'zcspo'
;
; items in tables below must match order COP_EQ - COP_LE
;
unsign_cjmptype db 'zzabba'
signed_cjmptype db 'zzgllg'
neg_cjmptype    db 0,1,0,0,1,1

;
; get a C binary operator from the token stream.
; there is a problem with the '<' because it is a "string delimiter"
; which Tokenize() usually is to remove.
; There has been a hack implemented in Tokenize() so that it won't touch the
; '<' if .IF, .ELSEIF, .WHILE, .UNTIL, .UNTILCXZ or .BREAK/.CONTINUE has been
; detected.
;

define CHARS_EQ    ('=' + ( '=' shl 8 ))
define CHARS_NE    ('!' + ( '=' shl 8 ))
define CHARS_GE    ('>' + ( '=' shl 8 ))
define CHARS_LE    ('<' + ( '=' shl 8 ))
define CHARS_AND   ('&' + ( '&' shl 8 ))
define CHARS_OR    ('|' + ( '|' shl 8 ))

    .code

    option proc:private

GetCOp proc fastcall item:ptr asm_tok

    mov rdx,[rcx].asm_tok.string_ptr

    .if ( [rcx].asm_tok.token == T_STRING )

        .if ( [rcx].asm_tok.stringlen == 2 )

            movzx eax,word ptr [rdx]

            .switch eax
            .case CHARS_EQ:  .return COP_EQ
            .case CHARS_NE:  .return COP_NE
            .case CHARS_GE:  .return COP_GE
            .case CHARS_LE:  .return COP_LE
            .case CHARS_AND: .return COP_AND
            .case CHARS_OR:  .return COP_OR
            .endsw

        .elseif ( [rcx].asm_tok.stringlen == 1 )

            movzx eax,byte ptr [rdx]

            .switch eax
            .case '>': .return COP_GT
            .case '<': .return COP_LT
            .case '&': .return COP_ANDB
            .case '!': .return COP_NEG
            .endsw
        .endif

    .elseif ( [rcx].asm_tok.token != T_ID )

        .return COP_NONE
    .endif

    .for ( eax = 0 : B[rdx+rax] : eax++ )
    .endf

    ;
    ; a valid "flag" string must end with a question mark
    ;
    .if ( B[rdx+rax-1] == '?' )

        mov ecx,[rdx]
        and ecx,not 0x20202020
        .switch pascal eax
        .case 5
            .return COP_ZERO .if ecx == "OREZ"
            .return COP_SIGN .if ecx == "NGIS"
        .case 6
            mov al,[rdx+4]
            and eax,not 0x20
            .return COP_CARRY .if ( eax == "Y" && ecx == "RRAC" )
        .case 7
            mov ax,[rdx+4]
            and eax,not 0x2020
            .return COP_PARITY .if ( eax == "YT" && ecx == "IRAP" )
        .case 9
            mov eax,[rdx+4]
            and eax,not 0x20202020
            .return COP_OVERFLOW .if ( eax == "WOLF" && ecx == "REVO" )
        .endsw
    .endif
    .return COP_NONE

GetCOp endp

;
; render an instruction
;

    assume rbx:ptr asm_tok

RenderInstr proc __ccall uses rsi rdi rbx dst:string_t, inst:string_t, start1:uint_t,
        end1:uint_t, start2:uint_t, end2:uint_t, tokenarray:ptr asm_tok

   .new reg:int_t = 0
   .new b:byte

    mov rdi,dst
    mov rbx,tokenarray

    ; v2.30 - test if second operand starts with '&'

    mov ecx,start2
    .if ( ecx != EMPTY && ModuleInfo.Ofssize != USE16 )

        imul ecx,ecx,asm_tok
        .if ( [rbx+rcx].token == T_STRING )

            mov rax,[rbx+rcx].string_ptr
            .if ( word ptr [rax] == '&' )

                mov eax,T_EAX
                .if ModuleInfo.Ofssize == USE64
                    mov eax,T_RAX
                .endif
                mov reg,eax

                imul edx,end2,asm_tok
                mov rsi,[rbx+rdx].tokpos
                mov dl,[rsi]
                mov b,dl
                mov B[rsi],0
                add rdi,tsprintf(rdi, "lea %r, %s\n", eax, [rbx+rcx+asm_tok].tokpos)
                mov al,b
                mov [rsi],al
            .endif
        .endif
    .endif

    ; copy the instruction

    mov rsi,inst
    mov ecx,tstrlen(rsi)
    rep movsb
    mov eax,' '
    stosb

    ; copy the first operand's tokens

    imul ecx,end1,asm_tok
    imul eax,start1,asm_tok
    mov rcx,[rbx+rcx].asm_tok.tokpos
    mov rsi,[rbx+rax].asm_tok.tokpos
    sub rcx,rsi
    rep movsb

    mov ecx,end2
    mov eax,start2

    .if eax != EMPTY

        ; copy the second operand's tokens
        .if reg
            add rdi,tsprintf(rdi, ", %r", reg)
        .else
            mov word ptr [rdi],' ,'
            add rdi,2
            imul ecx,ecx,asm_tok
            imul eax,eax,asm_tok
            mov rcx,[rbx+rcx].asm_tok.tokpos
            mov rsi,[rbx+rax].asm_tok.tokpos
            sub rcx,rsi
            rep movsb
        .endif

    .elseif ecx != EMPTY
        add rdi,tsprintf(rdi, ", %d", ecx)
    .endif
    mov W[rdi],EOLCHAR
    lea rax,[rdi+1]
    ret

RenderInstr endp


GetLabelStr proc __ccall public l_id:int_t, buffer:string_t

    tsprintf( buffer, "@C%04X", l_id )
   .return buffer

GetLabelStr endp

;
; render a Jcc instruction
;
RenderJcc proc __ccall uses rdi dst:string_t, cc:int_t, _neg:int_t, _label:int_t
    ;
    ; create the jump opcode: j[n]cc
    ;
    mov rdi,dst

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

    tsprintf( rdi, "@C%04X", _label )
    lea rax,[rdi+rax+1]
    mov W[rax-1],EOLCHAR
    ret

RenderJcc endp


;
; a "token" in a C expression actually is an assembly expression
;
LGetToken proc __ccall private uses rsi rdi rbx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok, opnd:ptr expr
    ;
    ; scan for the next C operator in the token array.
    ; because the ASM evaluator may report an error if such a thing
    ; is found ( CARRY?, ZERO? and alikes will be regarded as - not yet defined - labels )
    ;
    mov rsi,i
    mov edi,[rsi]

    imul ebx,edi,asm_tok
    add rbx,tokenarray

    .for ( : edi < ModuleInfo.token_count, GetCOp( rbx ) == COP_NONE : edi++ )
        add rbx,asm_tok
    .endf

    .if ( edi == [rsi] )

        mov rax,opnd
        mov [rax].expr.kind,EXPR_EMPTY
        mov eax,NOT_ERROR

    .elseifd ( EvalOperand( rsi, tokenarray, edi, opnd, 0 ) != ERROR )
        ;
        ; v2.11: emit error 'syntax error in control flow directive'.
        ; May happen for expressions like ".if 1 + CARRY?"
        ;
        mov eax,NOT_ERROR
        .if ( [rsi] > edi )

            asmerr(2154)
        .endif
    .endif
    ret

LGetToken endp


GetLabel proto watcall hll:ptr hll_item, index:int_t {
    mov eax,[rax].hll_item.labels[rdx*4]
    }

; a "simple" expression is
; 1. two tokens, coupled with a <cmp> operator: == != >= <= > <
; 2. two tokens, coupled with a "&" operator
; 3. unary operator "!" + one token
; 4. one token (short form for "<token> != 0")
;

GetSimpleExpression proc __ccall private uses rsi rdi rbx \
        hll:        ptr hll_item,
        i:          ptr int_t,
        tokenarray: ptr asm_tok,
        ilabel:     int_t,
        is_true:    uint_t,
        buffer:     string_t,
        hllop:      ptr hll_opnd

    mov  rsi,i
    mov  edi,[rsi]
    imul ebx,edi,asm_tok
    add  rbx,tokenarray

    .for ( rax = [rbx].string_ptr : word ptr [rax] == '!' : rax = [rbx].string_ptr )

        inc edi
        add rbx,asm_tok
        mov eax,1
        sub eax,is_true
        mov is_true,eax
    .endf
    mov [rsi],edi
    ;
    ; the problem with '()' is that is might enclose just a standard Masm
    ; expression or a "hll" expression. The first case is to be handled
    ; entirely by the expression evaluator, while the latter case is to be
    ; handled HERE!
    ;
    .if ( [rbx].token == T_OP_BRACKET )

        .for ( edi = 1, rbx += asm_tok,
            al = [rbx].token : al != T_FINAL : rbx += asm_tok, al = [rbx].token )
            .if ( al == T_OP_BRACKET )
                inc edi
            .elseif ( al == T_CL_BRACKET )
                dec edi
                .break .ifz ; a standard Masm expression?
            .else
                .break .if ( GetCOp(rbx) != COP_NONE )
            .endif
        .endf

        .if ( edi )

            inc dword ptr [rsi]
            .ifd GetExpression(hll, rsi, tokenarray, ilabel, is_true, buffer, hllop) == ERROR
                .return
            .endif

            imul ebx,[rsi],asm_tok
            add  rbx,tokenarray
            .if ( [rbx].token != T_CL_BRACKET )
                .return asmerr(2154)
            .endif
            inc dword ptr [rsi]
           .return NOT_ERROR
        .endif
    .endif

    mov edi,[rsi]
    mov rbx,tokenarray
    ;
    ; get (first) operand
    ;
   .new is_float:byte = 0
   .new inst_cmp:string_t = "cmp"
   .new op1_pos:int_t = edi
   .new op1:expr

    .ifd LGetToken(hll, rsi, rbx, &op1) == ERROR
        .return
    .endif

    .if ( op1.kind == EXPR_REG && !( op1.flags & E_INDIRECT ) )

        mov rax,op1.base_reg

        .if ( rax )

            .if ( GetValueSp( [rax].asm_tok.tokval ) & ( OP_XMM or OP_YMM or OP_ZMM ) )

                lea rax,@CStr( "comisd" )
                .if ( ModuleInfo.flt_size == 4 )
                    lea rax,@CStr( "comiss" )
                .endif
                mov inst_cmp,rax
                inc is_float
            .endif
        .endif
    .endif

    mov edi,[rsi]
   .new op1_end:int_t = edi

    imul eax,edi,asm_tok ; get operator
    add rax,rbx
    ;
    ; lower precedence operator ( && or || ) detected?
    ;
    .if ( GetCOp(rax) == COP_AND || eax == COP_OR )
        mov eax,COP_NONE
    .elseif ( eax != COP_NONE )
        inc edi
        mov [rsi],edi
    .endif
    .new op:int_t = eax
    .new jcclabel:int_t = GetLabel(hll, ilabel)
    ;
    ; check for special operators with implicite operand:
    ; COP_ZERO, COP_CARRY, COP_SIGN, COP_PARITY, COP_OVERFLOW
    ;
    mov edx,op
    .if ( edx >= COP_ZERO )

        .return asmerr(2154) .if ( op1.kind != EXPR_EMPTY )

        mov rcx,hllop
        mov [rcx].hll_opnd.lastjmp,buffer
        lea rcx,flaginstr
        movzx ecx,byte ptr [rcx+rdx-COP_ZERO]
        mov edx,is_true
        xor edx,1

       .new flag:int_t = ecx
       .new istrue:int_t = edx

        ; v2.27.30: ZERO? || CARRY? --> LE

        lea eax,[rdi+1]
        .if ( eax < ModuleInfo.token_count && ( op == COP_ZERO || op == COP_CARRY ) )

            imul eax,eax,asm_tok
            add rax,rbx
            GetCOp(rax)

            mov ecx,flag
            mov edx,istrue

            .if ( eax == COP_ZERO || eax == COP_CARRY )

                mov ecx,'a'
                xor edx,1
                add edi,2
                mov [rsi],edi
            .endif
        .endif

        RenderJcc( buffer, ecx, edx, jcclabel )
       .return NOT_ERROR
    .endif

    mov eax,op1.kind
    .switch eax
      .case EXPR_EMPTY
        .return asmerr(2154)  ; v2.09: changed from NOT_ERROR to ERROR
      .case EXPR_FLOAT
        .return asmerr(2050)  ; v2.10: added
    .endsw

    .if ( op == COP_NONE )

        .switch eax
          .case EXPR_REG
            .if ( !( op1.flags & E_INDIRECT ) && is_float == 0 )

                lea rdx,@CStr( "test" )
                .if ( Options.masm_compat_gencode )
                    lea rdx,@CStr( "or" )
                .endif
                RenderInstr( buffer, rdx, op1_pos, op1_end,
                    op1_pos, op1_end, rbx )
                mov rdx,hllop
                mov [rdx].hll_opnd.lastjmp,rax
                RenderJcc( rax, 'z', is_true, jcclabel )
                .endc
            .endif
            ;
            ; no break
            ;
          .case EXPR_ADDR

            RenderInstr( buffer, inst_cmp, op1_pos, op1_end, EMPTY, 0, rbx )
            mov rdx,hllop
            mov [rdx].hll_opnd.lastjmp,rax
            RenderJcc( rax, 'z', is_true, jcclabel )
            .endc
          .case EXPR_CONST
            .if ( op1.hvalue != 0 && op1.hvalue != -1 )
                .return EmitConstError( &op1 )
            .endif
            mov rcx,hllop
            mov [rcx].hll_opnd.lastjmp,buffer
            mov edx,is_true
            xor edx,1
            .if ( ( is_true && op1.value ) || ( edx && op1.value == 0 ) )
                tsprintf( buffer, "jmp @C%04X%s", jcclabel, &EOLSTR )
            .else
                mov B[rax],NULLC
            .endif
            .endc
        .endsw
        .return NOT_ERROR
    .endif

    ;
    ; get second operand for binary operator
    ;
    mov edi,[rsi]
   .new op2_pos:int_t = edi

    ; v2.30 - test if second operand starts with '&'

    imul eax,edi,asm_tok
    .if ( [rbx+rax].token == T_STRING )
        mov rax,[rbx+rax].string_ptr
        .if ( word ptr [rax] == '&' )
            inc dword ptr [rsi]
        .endif
    .endif

    .new op2:expr
    .return .ifd LGetToken(hll, rsi, rbx, &op2) == ERROR

    mov eax,op2.kind
    .if ( eax != EXPR_CONST && eax != EXPR_ADDR && eax != EXPR_REG )
        .if ( eax == EXPR_FLOAT )
            .if ( is_float )
                mov op2.kind,EXPR_ADDR
            .elseif ( op1.kind == EXPR_ADDR )
                .if ( op1.mem_type == MT_REAL4 )
                    mov inst_cmp,&@CStr( "comiss" )
                .elseif ( op1.mem_type == MT_REAL8 )
                    mov inst_cmp,&@CStr( "comisd" )
                .endif
            .endif
        .else
            .return asmerr(2154)
        .endif
    .elseif ( eax == EXPR_ADDR && is_float )

        ; ( xmm0 > float/double )

        .if ( op2.mem_type == MT_REAL4 )
            mov inst_cmp,&@CStr( "comiss" )
        .elseif ( op2.mem_type == MT_REAL8 )
            mov inst_cmp,&@CStr( "comisd" )
        .endif
    .endif

    mov edi,[rsi]
   .new op2_end:int_t = edi

    assume rbx: NOTHING
    ;
    ; now generate ASM code for expression
    ;
    mov ecx,op
    .if ( ecx == COP_ANDB )
        ;
        ; v2.22 - switch /Zg to OR
        ;
        lea rdx,@CStr("test")
        .if Options.masm_compat_gencode
            lea rdx,@CStr("or")
        .endif
        RenderInstr( buffer, rdx, op1_pos, op1_end, op2_pos, op2_end, rbx )
        mov rcx,hllop
        mov [rcx].hll_opnd.lastjmp,rax
        RenderJcc( rax, 'e', is_true, jcclabel )

    .elseif ( ecx <= COP_LE )
        ;
        ; ==, !=, >, <, >= or <= operator
        ;
        ; optimisation: generate 'or EAX,EAX' instead of 'cmp EAX,0'.
        ; v2.11: use op2.value64 instead of op2.value
        ;
        .if ( !op2.l64_l && !op2.l64_h && ( ecx == COP_EQ || ecx == COP_NE ) &&
              op1.kind == EXPR_REG && !( op1.flags & E_INDIRECT ) &&
              op2.kind == EXPR_CONST && !is_float )
            ;
            ; v2.22 - switch /Zg to OR
            ;
            lea rdx,@CStr("test")
            .if ( Options.masm_compat_gencode )
                lea rdx,@CStr("or")
            .endif
            RenderInstr( buffer, rdx, op1_pos, op1_end, op1_pos, op1_end, rbx )
        .else
            RenderInstr( buffer, inst_cmp,  op1_pos, op1_end, op2_pos, op2_end, rbx )
        .endif
        mov rbx,hllop
        mov [rbx].hll_opnd.lastjmp,rax

        ;
        ; v2.22 - signed compare S, SB, SW, SD
        ;
        mov rdx,hll
        xor edi,edi
        mov ecx,[rdx].hll_item.flags
        .if ( ecx & HLLF_IFS )
            inc edi
        .endif

        mov     ecx,op
        movzx   edx,op1.mem_type
        movzx   eax,op2.mem_type
        and     edx,MT_SPECIAL_MASK
        and     eax,MT_SPECIAL_MASK

        .if ( edi || edx == MT_SIGNED || eax == MT_SIGNED )
            lea rdi,signed_cjmptype
            movzx edx,byte ptr [rdi+rcx-COP_EQ]
        .else
            lea rdi,unsign_cjmptype
            movzx edx,byte ptr [rdi+rcx-COP_EQ]
        .endif

        mov eax,is_true
        lea rdi,neg_cjmptype
        .if ( !byte ptr [rdi+rcx-COP_EQ] )
            xor eax,1
        .endif
        RenderJcc( [rbx].hll_opnd.lastjmp, edx, eax, jcclabel )
    .else
        .return asmerr(2154)
    .endif
    .return NOT_ERROR

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

InvertJump proc fastcall private p:string_t

    .if ( B[rcx] == NULLC ) ; v2.11: convert 0 to "jmp"

        .return tstrcpy( rcx, "jmp " )
    .endif

    inc rcx
    mov eax,[rcx]

    .switch al
      .case 'e'
      .case 'z'
      .case 'c'
      .case 's'
      .case 'p'
      .case 'o'
        mov B[rcx+1],al
        mov B[rcx],'n'
        ret
      .case 'n'
        mov B[rcx],ah
        mov B[rcx+1],' '
        ret
      .case 'a'
        mov B[rcx],'b'
        .endc
      .case 'b'
        mov B[rcx],'a'
        .endc
      .case 'g'
        mov B[rcx],'l'
        .endc
      .case 'l'
        mov B[rcx],'g'
        .endc
      .default
        ;
        ; v2.11: convert "jmp" to 0
        ;
        .if al == 'm'

            dec rcx
            mov B[rcx],NULLC
        .endif
        ret
    .endsw
    .if ah == 'e'
        mov B[rcx+1],' '
    .else
        mov B[rcx+1],'e'
    .endif
    ret

InvertJump endp


; Replace a label in the source lines generated so far.
; todo: if more than 0xFFFF labels are needed,
; it may happen that length of nlabel > length of olabel!
; then the simple memcpy() below won't work!
;
ReplaceLabel proc __ccall private uses rsi rdi rbx p:ptr, olabel:dword, nlabel:dword

  local oldlbl[16]:char_t, newlbl[16]:char_t

    mov rbx,p
    lea rsi,oldlbl
    lea rdi,newlbl

    GetLabelStr(olabel, rsi)
    GetLabelStr(nlabel, rdi)

    mov ebx,tstrlen(rdi)
    mov rax,p
    .while tstrstr(rax, rsi)
        tmemcpy(rax, rdi, ebx)
        add rax,rbx
    .endw
    ret

ReplaceLabel endp


; operator &&, which has the second lowest precedence, is handled here

GetAndExpression proc __ccall private uses rsi rdi rbx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
    ilabel:uint_t, is_true:uint_t, buffer:string_t, hllop:ptr hll_opnd

  local truelabel:int_t, nlabel:int_t, olabel:int_t, buff[16]:char_t

    mov rdi,hllop
    mov rsi,buffer
    mov truelabel,0

    .while 1

        .return .ifd GetSimpleExpression(hll, i, tokenarray, ilabel, is_true, rsi, rdi ) == ERROR

        mov rbx,i
        mov eax,[rbx]
        imul eax,eax,asm_tok
        add rax,tokenarray

        .break .if GetCOp(rax) != COP_AND

        inc D[rbx]
        mov rbx,[rdi].hll_opnd.lastjmp
        .if rbx && is_true

            InvertJump(rbx)

            .if truelabel == 0

                mov truelabel,GetHllLabel()
            .endif

            ; v2.11: there might be a 0 at lastjmp

            .if B[rbx]

                tstrcat(GetLabelStr(truelabel, &[rbx+4]), &EOLSTR)
            .endif

                ; v2.22 .while  (eax || edx) && ecx -- failed
                ;   .while !(eax || edx) && ecx -- failed

            mov rbx,rsi
            .if [rdi].hll_opnd.lasttruelabel

                ReplaceLabel(rbx, [rdi].hll_opnd.lasttruelabel, truelabel)
            .endif
            mov nlabel,GetHllLabel()
            mov olabel,GetLabel(hll, ilabel)
            tstrlen(rbx)
            add rbx,rax
            mov rcx,GetLabelStr(olabel, &buff)
            tsprintf(rbx, "%s%s%s", rcx, LABELQUAL, &EOLSTR)
            ReplaceLabel(buffer, olabel, nlabel)
            mov [rdi].hll_opnd.lastjmp,0
        .endif

        tstrlen(rsi)
        add rsi,rax
        mov [rdi].hll_opnd.lasttruelabel,0
    .endw

    .if truelabel
        tstrlen(rsi)
        add rsi,rax
        tstrcat(tstrcat(GetLabelStr(truelabel, rsi), LABELQUAL), &EOLSTR)
        mov [rdi].hll_opnd.lastjmp,0
    .endif
    mov eax,NOT_ERROR
    ret

GetAndExpression endp


; operator ||, which has the lowest precedence, is handled here

GetExpression proc __ccall private uses rsi rdi rbx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
    ilabel:int_t, is_true:uint_t, buffer:string_t, hllop:ptr hll_opnd

  local truelabel:int_t, nlabel:int_t, olabel:int_t, buff[16]:char_t

    mov rsi,buffer
    mov rdi,hllop
    mov truelabel,0

    .while 1

        .return .ifd GetAndExpression(hll, i, tokenarray, ilabel, is_true, rsi, rdi) == ERROR

        mov rbx,i
        imul eax,[rbx],asm_tok
        add rax,tokenarray
        .break .if GetCOp(rax) != COP_OR
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
        inc D[rbx]
        mov rbx,[rdi].hll_opnd.lastjmp

        .if ( rbx && !is_true )

            InvertJump(rbx)

            .if ( truelabel == 0 )

                mov truelabel,GetHllLabel()
            .endif

            .if ( B[rbx] )

                tstrcat( GetLabelStr( truelabel, &[rbx+4] ), &EOLSTR )
            .endif

            mov rbx,rsi
            .if ( [rdi].hll_opnd.lasttruelabel )

                ReplaceLabel( rbx, [rdi].hll_opnd.lasttruelabel, truelabel )
            .endif

            mov [rdi].hll_opnd.lastjmp,0
            mov nlabel,GetHllLabel()
            mov olabel,GetLabel(hll, ilabel)
            tstrlen(rbx)
            add rbx,rax
            mov rax,hll
            .if ( [rax].hll_item.cmd == HLL_REPEAT )

                ReplaceLabel(buffer, olabel, nlabel)
                mov rcx,GetLabelStr(nlabel, &buff)
                tsprintf(rbx, "%s%s%s", rcx, LABELQUAL, &EOLSTR)
            .else
                mov rcx,GetLabelStr(olabel, &buff)
                tsprintf(rbx, "%s%s%s", rcx, LABELQUAL, &EOLSTR)
                ReplaceLabel(buffer, olabel, nlabel)
            .endif
        .endif
        tstrlen(rsi)
        add rsi,rax
        mov [rdi].hll_opnd.lasttruelabel,0
    .endw

    .if ( truelabel )

        mov rbx,[rdi].hll_opnd.lastjmp
        .if ( rbx && [rdi].hll_opnd.lasttruelabel )

            ReplaceLabel(rsi, [rdi].hll_opnd.lasttruelabel, truelabel)
            tstrchr(rbx, EOLCHAR)
            mov B[rax+1],0
        .endif

        tstrlen(rsi)
        add rsi,rax
        tstrcat( tstrcat(GetLabelStr( truelabel, rsi), LABELQUAL), &EOLSTR)
        mov eax,truelabel
        mov [rdi].hll_opnd.lasttruelabel,eax
    .endif
    mov eax,NOT_ERROR
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

GenerateFloat proto __ccall :int_t, :ptr asm_tok

    assume rbx:ptr asm_tok

ExpandCStrings proc __ccall public uses rdi rbx tokenarray:ptr asm_tok

    xor eax,eax
    .return .if ( ModuleInfo.strict_masm_compat == 1 )

    .for ( edi = 0, rbx = tokenarray: [rbx].token != T_FINAL: rbx += asm_tok, edi++ )

        .if ( [rbx].hll_flags & T_HLL_PROC )

            .return .if GenerateCString( edi, tokenarray )

            ; id[..]
            .if ( [rbx].token == T_ID && [rbx+asm_tok].token == T_OP_SQ_BRACKET )

                add rbx,asm_tok
                inc edi
            .endif

            .if ( [rbx].token == T_OP_SQ_BRACKET )

                ; invoke [...][.type].x(...)

                mov eax,1
                .repeat
                    add rbx,asm_tok
                    .if [rbx].token == T_CL_SQ_BRACKET
                        dec eax
                        .break .ifz
                    .elseif [rbx].token == T_OP_SQ_BRACKET
                        inc eax
                    .endif
                .until [rbx].token == T_FINAL
                add rbx,asm_tok
                .if [rbx].token == T_DOT
                    add rbx,asm_tok
                .endif
            .endif
            .while ( [rbx+asm_tok].token == T_DOT )
                add rbx,asm_tok*2
            .endw
            mov ecx,1
            add rbx,asm_tok*2

            .if ( [rbx-asm_tok].token != T_OP_BRACKET )

                asmerr( 3018, [rbx-asm_tok*2].string_ptr, [rbx-asm_tok].string_ptr )
                .break
            .endif

            .for ( : [rbx].token != T_FINAL : rbx += asm_tok )

                mov rdx,[rbx].string_ptr
                movzx eax,B[rdx]

                .switch eax
                  .case '"'
                    asmerr(2004, [rbx].string_ptr)
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
    ret

ExpandCStrings endp


GetProcVtbl proc fastcall private sym:ptr asym, name:ptr sbyte

    xor eax,eax
    .if ( [rcx].asym.mem_type == MT_TYPE && [rcx].asym.type )
        mov rcx,[rcx].asym.type
    .endif
    .if ( [rcx].asym.target_type &&
          ( [rcx].asym.mem_type == MT_PTR || [rcx].asym.ptr_memtype == MT_TYPE ) )
        mov rcx,[rcx].asym.target_type
    .endif
    .if ( [rcx].asym.flag2 & S_VTABLE )
        SearchNameInStruct( [rcx].asym.vtable, rdx, 0, 0 )
    .endif
    ret

GetProcVtbl endp


GetProc proc __ccall private uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok, opnd:ptr expr

    imul ebx,i,asm_tok
    add rbx,tokenarray

    .if ( [rbx].token == T_OP_SQ_BRACKET )

        .for ( ecx = i : [rbx].token != T_FINAL : rbx+=asm_tok, ecx++ )
            .break .if ( [rbx].token == T_CL_SQ_BRACKET )
        .endf
        add ecx,3
        add rbx,asm_tok*2
        .return 0 .if ( [rbx+asm_tok].token !=  T_DOT )
        .return 0 .ifd EvalOperand(&i, tokenarray, ecx, opnd, 0) == ERROR
        mov rcx,opnd
        mov rax,[rcx].expr.type

    .elseif [rbx].token == T_REG
        GetStdAssume(GetRegNo([rbx].tokval))
    .else
        SymFind([rbx].string_ptr)
    .endif
    .return .if !rax
    .return .if [rax].asym.flag1 & S_ISPROC

    .if ( [rbx].token == T_ID && [rbx+asm_tok].token == T_DOT &&
          [rbx+asm_tok*2].token == T_ID )

        .return GetProcVtbl(rax, [rbx+asm_tok*2].string_ptr)
    .endif

    mov rcx,[rax].asym.target_type
    mov dl,[rax].asym.mem_type
    .if ( dl == MT_PTR && rcx && [rcx].asym.flag1 & S_ISPROC )
        .return rcx
    .endif

    .if dl == MT_PTR && rcx && [rcx].asym.mem_type == MT_PROC

        mov rax,[rax].asym.target_type
        jmp isfnproto
    .endif

    mov rcx,[rax].asym.type
    .if ( dl == MT_TYPE && ( [rcx].asym.mem_type == MT_PTR || [rcx].asym.mem_type == MT_PROC ) )

        ; second case: symbol is a (function?) pointer

        mov rax,rcx
        .if [rax].asym.mem_type != MT_PROC
            jmp isfnptr
        .endif
    .endif

isfnproto:

    ; pointer target must be a PROTO typedef

    .return 0 .if [rax].asym.mem_type != MT_PROC

isfnptr:

    ; get the pointer target

    mov rax,[rax].asym.target_type
    ret

GetProc endp


GetParamId proc fastcall private uses rsi rdi rbx id:int_t, sym:asym_t

    mov rsi,[rdx].dsym.procinfo
    mov rax,[rsi].proc_info.paralist
    .if ( rax == NULL )
        .return
    .endif
    xor edi,edi
    .while ( [rax].dsym.nextparam )
        mov rax,[rax].dsym.nextparam
        inc edi
    .endw
    .if ( edi < ecx )
        .return NULL
    .endif

    mov bl,[rdx].asym.langtype
    .if ( bl == LANG_STDCALL || bl == LANG_C || bl == LANG_SYSCALL || bl == LANG_VECTORCALL ||
          ( bl == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) )

        mov rbx,rax
        .while ecx
            .for ( rax = [rsi].proc_info.paralist : rbx != [rax].dsym.nextparam : rax = [rax].dsym.nextparam )
            .endf
            mov rbx,rax
            dec ecx
        .endw
    .else
        .for ( rax = [rdi].proc_info.paralist : ecx : rax = [rax].dsym.nextparam )
            dec ecx
        .endf
    .endif

    .if ( rax && [rax].asym.mem_type == MT_TYPE )
        mov rax,[rax].asym.type
    .endif
    ret

GetParamId endp


GetMacroReturn proc __ccall private uses rsi rbx i:int_t, tokenarray:ptr asm_tok

  local mac_name[512]:char_t
  local opnd:expr

    ;
    ; v2.32.43 - test return value from inline function
    ;
    ; if the last line is retm<..> use this as return value
    ;

    .return .if !GetProc( i, tokenarray, &opnd )

    .if ( [rax].asym.state == SYM_STRUCT_FIELD )

        mov rsi,rax

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( [rbx].token == T_OP_SQ_BRACKET )
            mov rcx,opnd.type
        .else
           .return .if !SymFind( [rbx].string_ptr )
            xor ecx,ecx
            .if ( [rax].asym.mem_type == MT_TYPE )
                mov rcx,[rax].asym.type
            .elseif ( [rax].asym.mem_type == MT_PTR )
                mov rcx,[rax].asym.target_type
            .endif
        .endif
        .return 0 .if ( !rcx || [rcx].asym.typekind != TYPE_STRUCT )

        tstrcpy( &mac_name, [rcx].asym.name )
        tstrcat( rax, "_" )
        tstrcat( rax, [rsi].asym.name )
        .return .if !SymFind( rax )

        .if ( [rax].asym.state == SYM_TMACRO )
            .return .if !SymSearch( [rax].asym.string_ptr )
        .endif

        or  [rsi].asym.flag2,S_VMACRO
        mov [rsi].asym.vmacro,rax ; vtable method is inline - sym->vmacro set
        mov rcx,rax
        xor eax,eax

    .else

        mov rcx,[rax].asym.target_type
        mov rdx,rax
        xor eax,eax

        .return .if !( [rdx].asym.state == SYM_EXTERNAL || [rdx].asym.state == SYM_STACK )
        .return .if !rcx

    .endif

   .return .if ( [rcx].asym.state != SYM_MACRO )

    mov rcx,[rcx].dsym.macroinfo
    mov rcx,[rcx].macro_info.lines
   .return .if !rcx

   .while [rcx].srcline.next
        mov rcx,[rcx].srcline.next
   .endw

    lea rcx,[rcx].srcline.line
    mov edx,[rcx]
   .return .if ( edx != 'mter' )

    add rcx,4
    mov dl,[rcx]
   .while 1
       .break .if ( !dl || dl == '<' )
        inc rcx
        mov dl,[rcx]
   .endw
   .return .if ( dl != '<' )
   .repeat
        inc rcx
        mov dl,[rcx]
       .continue(0) .if ( dl == ' ' )
       .continue(0) .if ( dl == 9 )
   .until 1
   .return .if ( !dl )
   .return .if ( dl == '>' )
   .return( rcx )

GetMacroReturn endp


StripSource proc __ccall private uses rsi rdi rbx i:int_t, e:int_t, tokenarray:ptr asm_tok

   .new mac:string_t = NULL
   .new curr:asym_t
   .new proc_id:ptr asm_tok = NULL ; foo( 1, bar(...), ...)
   .new parg_id:int_t = 0 ; foo.paralist[1] = return type[al|ax|eax|[rdx::eax|rax|xmm0]]
   .new opnd:expr
   .new bracket:int_t = 0
   .new reg2:int_t = 0
   .new b[MAX_LINE_LEN]:char_t

    .for ( rdi = &b, rbx = tokenarray, edx = 0 : edx < i : edx++, rbx += asm_tok )

        .if ( edx )
            .if ( [rbx].hll_flags & T_HLL_PROC )
                mov proc_id,rbx
                mov parg_id,0
            .endif
            .switch [rbx].token
              .case T_CL_BRACKET
                dec bracket
                .endc
              .case T_OP_BRACKET
                inc bracket
                .endc
              .case T_COMMA
                .if proc_id
                    inc parg_id
                .endif
                .endc
            .endsw
        .endif
        mov rsi,[rbx].tokpos
        mov rcx,[rbx+asm_tok].tokpos
        sub rcx,rsi
        rep movsb
    .endf
    mov byte ptr [rdi],0

    mov rdi,tokenarray
    xor esi,esi
    .if ( bracket == 0 )
        mov proc_id,rsi
    .endif

    .if GetMacroReturn(i, rdi)
        mov mac,rax
        jmp macro_args
    .endif

    mov rax,proc_id
    .if rax ;&& [rcx].asm_tok.token != T_OP_SQ_BRACKET

        sub rax,tokenarray
        mov ecx,asm_tok
        xor edx,edx
        div ecx
        mov ecx,eax

        .if GetProc( ecx, tokenarray, &opnd )

            .if ( [rax].asym.mem_type == MT_TYPE )
                mov rax,[rax].asym.type
            .endif
            mov rcx,GetParamId( parg_id, rax )
            .if rcx
                mov eax,[rcx].asym.total_size
                .switch eax
                  .case 1: mov esi,T_AL : .endc
                  .case 2: mov esi,T_AX : .endc
                  .case 4
                    mov esi,T_EAX
                    .if ModuleInfo.Ofssize == USE64 && [rcx].asym.mem_type & MT_FLOAT
                        mov esi,T_XMM0
                    .endif
                    .endc
                  .case 8
                    .if ModuleInfo.Ofssize == USE64
                        .if [rcx].asym.mem_type & MT_FLOAT
                            mov esi,T_XMM0
                        .else
                            mov esi,T_RAX
                        .endif
                    .else
                        .if ( [rbx-asm_tok].token == T_DBL_COLON )
                            ; reg::func()
                            mov esi,T_EAX
                        .else
                            mov esi,T_EDX
                            mov reg2,T_EAX
                        .endif
                    .endif
                    .endc
                  .case 16
                    .if [rcx].asym.mem_type & MT_FLOAT
                        mov esi,T_XMM0
                    .elseif ModuleInfo.Ofssize == USE64
                        mov esi,T_RDX
                        mov reg2,T_RAX
                    .endif
                    .endc
                  .case 32
                    .if [rcx].asym.mem_type == MT_YWORD
                        mov esi,T_YMM0
                    .endif
                    .endc
                  .case 64
                    .if [rcx].asym.mem_type == MT_ZWORD
                        mov esi,T_ZMM0
                    .endif
                    .endc
                .endsw
            .endif
        .endif
    .endif

    .if !esi

ifndef ASMC64
        mov esi,T_EAX
        .if ModuleInfo.Ofssize == USE64
            mov esi,T_RAX
        .elseif ModuleInfo.Ofssize == USE16
            mov esi,T_AX
        .endif
else
        mov esi,T_RAX
endif
        mov eax,i
        .if ( !proc_id && eax > 1 )

            imul eax,eax,asm_tok
            lea rbx,[rdi+rax-(asm_tok*2)]

            .if ( [rbx+asm_tok].token == T_COMMA && [rbx].token != T_CL_SQ_BRACKET )

                ;
                ; <op> <reg|id> <,> <proc>
                ;
                xor eax,eax
                .if ( [rbx].token == T_REG )

                    SizeFromRegister( [rbx].tokval )

                .elseif SymFind( [rbx].string_ptr )

                    ; movsd id,cos(..)

                    .if ( ModuleInfo.Ofssize == USE64 &&
                          ( [rax].asym.mem_type == MT_REAL4 || [rax].asym.mem_type == MT_REAL8 ) )
                        mov eax,16
                    .else
                        SizeFromMemtype( [rax].asym.mem_type, USE_EMPTY, [rax].asym.type )
                    .endif

                .elseif ( [rbx-asm_tok].token == T_DOT )

                    ; <op> <struct>.id, rax

                    mov edx,i
                    sub i,4
                    sub rbx,asm_tok*2
                    .if ( [rbx-asm_tok].token == T_DOT )
                        sub rbx,asm_tok*2
                        sub i,2
                    .endif

                size_from_ptr:

                    .if ( [rbx].token == T_CL_SQ_BRACKET )
                        .while ( i && [rbx].token != T_OP_SQ_BRACKET )
                            dec i
                            sub rbx,asm_tok
                        .endw
                    .endif
                    .if ( [rbx-asm_tok].tokval == T_PTR )
                        sub rbx,asm_tok*2
                        sub i,2
                    .endif

                    sub edx,i
                    .ifd EvalOperand( &i, tokenarray, edx, &opnd, EXPF_NOERRMSG ) != ERROR

                        xor eax,eax
                        .if ( opnd.kind == EXPR_ADDR || ( opnd.flags & E_INDIRECT ) )
                            mov cl,opnd.mem_type
                            .switch cl
                            .case MT_BYTE
                            .case MT_SBYTE  : mov eax,1 : .endc
                            .case MT_WORD
                            .case MT_SWORD  : mov eax,2 : .endc
                            .case MT_DWORD
                            .case MT_SDWORD : mov eax,4 : .endc
                            .case MT_OWORD
                            .case MT_REAL2
                            .case MT_REAL4
                            .case MT_REAL8
                            .case MT_REAL10
                            .case MT_REAL16 : mov eax,16 : .endc
                            .case MT_YWORD  : mov eax,32 : .endc
                            .case MT_ZWORD  : mov eax,64 : .endc
                            .endsw
                        .endif
                    .else
                        xor eax,eax
                    .endif
                .endif

                .if eax
                    .switch eax
                      .case 1: mov esi,T_AL  : .endc
                      .case 2: mov esi,T_AX  : .endc
                      .case 4: mov esi,T_EAX : .endc
                      .case 8
                        .if ModuleInfo.Ofssize == USE64
                            mov esi,T_RAX
                        .endif
                        .endc
                      .case 16 : mov esi,T_XMM0 : .endc
                      .case 32 : mov esi,T_YMM0 : .endc
                      .case 64 : mov esi,T_ZMM0 : .endc
                    .endsw
                .endif

            .elseif ( [rbx+asm_tok].token == T_COMMA && [rbx].token == T_CL_SQ_BRACKET )

                mov edx,i
                sub i,2
                jmp size_from_ptr
            .endif
        .endif
    .endif
    mov rbx,GetResWName(esi, 0)

macro_args:

    lea rsi,b
    tstrcat(rsi, " ")
    .if mac
        lea rdi,[rsi+tstrlen(rsi)]
        mov rsi,mac
        .while 1
            lodsb
            mov ah,[rsi]
            .break .if !al
            .continue .if ax == '<!'
            .continue .if ax == '>!'
            stosb
        .endw
        mov [rdi-1],al
        lea rsi,b
        mov rdi,tokenarray
    .else
        tstrcat(rsi, rbx)
    .endif
    .if reg2
        tstrcat(rsi, "::")
        tstrcat(rsi, GetResWName(reg2, 0))
    .endif

    imul ebx,e,asm_tok
    .if [rbx+rdi].token != T_FINAL

        tstrcat( rsi, " " )
        tstrcat( rsi, [rbx+rdi].tokpos )
    .endif

    tstrcpy(ModuleInfo.currsource, rsi)
    Tokenize(rax, 0, rdi, TOK_DEFAULT)
    mov ModuleInfo.token_count,eax
   .return( STRING_EXPANDED )

StripSource endp


LKRenderHllProc proc __ccall private uses rsi rdi rbx dst:string_t, i:uint_t, tokenarray:ptr asm_tok

   .new opnd:expr
   .new b[MAX_LINE_LEN]:char_t
   .new name:string_t
   .new id:ptr asm_tok
   .new args:ptr asm_tok
   .new dots[10]:ptr asm_tok
   .new static_struct:int_t = 0
   .new ClassVtbl[256]:char_t
   .new sym:asym_t = NULL
   .new type:string_t = NULL
   .new method:asym_t = NULL
   .new sym1:asym_t
   .new comptr:string_t = NULL
   .new constructor:int_t = 0 ; Class(..)
   .new vtable:int_t = 0
   .new brcount:int_t = 0
   .new sqcount:int_t = 0
   .new dotcount:int_t = 0
   .new sqbrend:ptr asm_tok = NULL
   .new j:int_t = i
   .new vparray:asym_t = NULL

    imul eax,i,asm_tok
    add  rax,tokenarray
    mov  id,rax
    mov  rbx,rax

    .for ( : [rbx].token != T_FINAL : rbx+=asm_tok, j++ )

        .if ( [rbx].token == T_OP_SQ_BRACKET )

            .for ( sqcount++, rbx+=asm_tok, j++ : sqcount && [rbx].token != T_FINAL : rbx+=asm_tok, j++ )

                .if ( [rbx].hll_flags & T_HLL_PROC )
                    .return .ifd LKRenderHllProc( dst, j, tokenarray ) == ERROR
                .elseif ( [rbx].token == T_OP_BRACKET )
                    inc brcount
                .elseif ( [rbx].token == T_CL_BRACKET )
                    dec brcount
                .elseif ( !brcount && [rbx].token == T_OP_SQ_BRACKET )
                    inc sqcount
                .elseif ( !brcount && [rbx].token == T_CL_SQ_BRACKET )
                    dec sqcount
                    .ifz
                        .if ( !sqbrend )
                            mov sqbrend,rbx
                        .endif
                        .break
                    .endif
                .endif
            .endf
        .elseif ( [rbx].token == T_DOT )
            mov eax,dotcount
            mov dots[rax*size_t],rbx
            inc dotcount
        .elseif ( [rbx].token == T_OP_BRACKET )
            .break
        .endif
    .endf
    .if [rbx].token != T_OP_BRACKET
        .return asmerr( 2008, [rbx].string_ptr )
    .endif

    mov args,rbx
    mov name,[rbx-asm_tok].string_ptr
    mov rbx,id

    .if ( [rbx].token == T_OP_SQ_BRACKET )
        ;
        ; v2.27 - [reg].Class.Method()
        ;       - [reg+foo([rax])].Class.Method()
        ;       - [reg].Method()
        ;
        xor eax,eax
        .if ( dotcount )

            mov rdx,dots
            .if ( dotcount > 1 )

                ; [reg].Class.Method()

                mov rdi,name
                SymFind( [rdx+asm_tok].asm_tok.string_ptr )

            .elseif ( [rdx+asm_tok*2].asm_tok.token == T_OP_BRACKET )

                ; [reg].Method() -- assume reg:ptr Class

                mov rdi,[rdx+asm_tok].asm_tok.string_ptr
                mov eax,i
                mov brcount,eax
                mov rax,dots
                sub rax,tokenarray
                mov ecx,asm_tok
                xor edx,edx
                div ecx
                mov ecx,eax
                .ifd EvalOperand( &brcount, tokenarray, ecx, &opnd, 0 ) != ERROR
                    mov rax,opnd.type
                .else
                    xor eax,eax
                .endif
            .endif

            .if ( rax )
                .if ( [rax].asym.state == SYM_TYPE && [rax].asym.typekind == TYPE_STRUCT )
                    ;
                    ; If Class.Method do not exist assume ClassVtbl.Method do.
                    ;
                    jmp type_struct
                .else
                    xor eax,eax
                .endif
            .endif
        .endif
        mov rcx,rax

    .else

        mov sym1,SymFind( [rbx].string_ptr )
        mov edi,dotcount
        .if edi
            dec edi
        .endif

        .for ( esi = 0 : rax && edi : esi++, edi-- )
            mov rcx,rax
            .if ( [rcx].asym.mem_type == MT_TYPE )
                mov rcx,[rcx].asym.type
            .endif
            .if ( [rcx].asym.mem_type == MT_PTR )
                mov rcx,[rcx].asym.target_type
            .endif
            .break .if !rcx
            mov rbx,dots[rsi*size_t]
            add rbx,asm_tok
            mov vparray,SearchNameInStruct( rcx, [rbx].string_ptr, 0, 0 )
        .endf

        mov sym,rax
        xor ecx,ecx
        .if ( vparray )
            mov rdx,sym1
            .if ( rdx != rax && [rdx].asym.mem_type != MT_PTR )
                .if ( dotcount == 2 )
                    mov vparray,NULL  ; static class.ptr.proc()
                .else
                    inc static_struct ; static class.ptr.ptr...proc()
                .endif
            .endif
        .endif

        .if ( dotcount )

            mov rdi,name

        .elseif ( rax && [rax].asym.state == SYM_TYPE && [rbx+asm_tok].token == T_OP_BRACKET )

            mov rdi,[rbx].string_ptr
            mov rcx,rax
            mov type,rdi
        .else
            xor eax,eax
        .endif

        mov rbx,id
        .if rax

            .if ( [rax].asym.mem_type == MT_TYPE && [rax].asym.type )

                mov rax,[rax].asym.type

                .if ( [rax].asym.typekind == TYPE_TYPEDEF )

                    mov rcx,[rax].asym.target_type

                .elseif ( [rax].asym.typekind == TYPE_STRUCT )

                    inc static_struct

                    type_struct:

                    mov sym,rax
                    mov rcx,rax
                    xor eax,eax
                    .if ( [rcx].asym.flag2 & S_VTABLE )
                        SearchNameInStruct([rcx].asym.vtable, rdi, 0, 0)
                    .endif
                    .if ( rax == NULL )
                        .if SearchNameInStruct(sym, rdi, 0, 0)
                            mov method,rax
                            mov sym,0
                        .endif
                    .endif
                    mov rcx,sym
                .endif

            .elseif ( [rax].asym.mem_type == MT_PTR &&
                    ( [rax].asym.state == SYM_STACK || [rax].asym.state == SYM_EXTERNAL ) )

                mov rcx,[rax].asym.target_type
            .endif
        .endif
    .endif

    mov name,rdi
    mov rdx,rcx
    lea rdi,b
    mov eax,'ovni'
    stosd
    mov eax,' ek'
    stosd
    dec rdi

    .if ( rdx && [rdx].asym.state == SYM_TYPE && [rdx].asym.typekind == TYPE_STRUCT )

        mov rsi,rdx
        mov comptr,[rsi].asym.name
        .if SearchNameInStruct( rsi, name, 0, 0 )
            mov method,rax
        .endif
        .if ( [rsi].asym.flag2 & S_VTABLE )

            .if SearchNameInStruct( [rsi].asym.vtable, name, 0, 0 )
                inc vtable
                mov method,rax
                mov rsi,[rsi].asym.vtable
                mov comptr,[rsi].asym.name
            .endif
        .endif
        .if ( method == NULL )
            .if ( tstrcmp( [rsi].asym.name, name ) == 0 )
                inc vtable
                inc constructor
            .endif
        .elseif ( vparray )
            mov rax,method
            or [rax].asym.flag2,S_VPARRAY
        .endif
    .endif

    .if ( comptr )

        .if ( ModuleInfo.Ofssize == USE64 && !constructor )

            mov rax,method
            .if rax ; v2.28: Added for undefined symbol error..

                .if ( [rax].asym.mem_type == MT_TYPE && [rax].asym.type )
                    mov rax,[rax].asym.type
                    .if ( [rax].asym.typekind == TYPE_TYPEDEF )
                        mov rax,[rax].asym.target_type
                    .endif
                .endif
                .if ( [rax].asym.langtype == LANG_SYSCALL )
                    mov eax,"01r[" ; v2.28: Added for :vararg
                .else
                    mov eax,"xar["
                .endif
            .else
                mov eax,"xar["
            .endif
        .else
            mov eax,"xae["
        .endif

        .if ( !constructor )

            stosd
            mov eax,".]"
            stosw
        .endif

        mov rsi,comptr
        .while ( byte ptr [rsi] )
            movsb
        .endw

        .if ( type )
            mov al,'.'
            .if ( constructor )
                mov al,'_'
            .endif
            stosb
            mov rsi,type
            .while ( byte ptr [rsi] )
                movsb
            .endw
        .endif

        .if ( [rbx].token == T_OP_SQ_BRACKET )

            .if ( [rbx+asm_tok*2].token == T_CL_SQ_BRACKET )

                mov rax,[rbx+asm_tok].string_ptr
            .else
                tstrcpy( &ClassVtbl, "addr [" )
                .for ( rsi = &[rbx+asm_tok] : rsi < sqbrend : rsi += asm_tok )
                    tstrcat( rax, [rsi].asm_tok.string_ptr )
                .endf
            .endif

        .elseif ( dotcount )

            lea rax,ClassVtbl
            mov rsi,[rbx].tokpos
            mov rdx,args
            sub rdx,2*asm_tok
            mov rcx,[rdx].asm_tok.tokpos
            sub rcx,rsi
            mov rdx,rdi
            mov rdi,rax
            rep movsb
            mov byte ptr [rdi],0
            mov rdi,rdx
        .else
            mov rax,[rbx].string_ptr
        .endif
        mov comptr,rax
        mov rax,method
        .if rax
            or [rax].asym.flag1,S_METHOD
            .if ( !vtable )
                or [rax].asym.flag2,S_VPARRAY
            .endif
        .endif
    .endif

    inc j
    .if ( comptr )
        mov rbx,args
        sub rbx,asm_tok*2
        .if rbx <= id
            add rbx,asm_tok*2
        .endif
    .endif
    mov rsi,[rbx].tokpos
    mov rcx,args
    lea rbx,[rcx+asm_tok]
    mov rcx,[rcx].asm_tok.tokpos
    sub rcx,rsi
    rep movsb
    mov byte ptr [rdi],0

    .if ( type )
        mov eax,"0 ,"
        stosd
        dec rdi
    .elseif ( comptr && vtable )
        mov eax,' ,'
        stosw
        .if ( static_struct )
            mov eax,'rdda'
            stosd
            mov eax,' '
            stosb
        .endif
        mov rsi,comptr
        .while ( byte ptr [rsi] )
            lodsb
            .if ( al == '.' && vparray )
                mov vtable,0
                .break
            .endif
            stosb
        .endw
    .endif
    mov byte ptr [rdi],0

    .if ( [rbx].token == T_CL_BRACKET )

        inc j
        lea rsi,b
        jmp done
    .endif

    mov eax,' ,'
    stosw

    .for ( brcount = 1 : [rbx].token != T_FINAL : )

        .if ( [rbx].hll_flags & T_HLL_PROC )
            .return .ifd LKRenderHllProc(dst, j, tokenarray) == ERROR
        .endif

        mov al,[rbx].token
        .if ( al == T_CL_BRACKET )
            dec brcount
            .break .ifz
        .elseif ( al == T_OP_BRACKET )
            inc brcount
        .endif
        .if ( al == '&' )
            lea rsi,@CStr("addr ")
            mov ecx,5
        .elseif ( al == T_COMMA && [rbx+asm_tok].token == T_CL_BRACKET && brcount == 1 )
            inc j
            add rbx,asm_tok
            .break
        .else
            mov rsi,[rbx].tokpos
            mov rcx,[rbx+asm_tok].tokpos
            sub rcx,rsi
        .endif
        rep movsb
        inc j
        add rbx,asm_tok
    .endf
    inc j
    mov byte ptr [rdi],0

done:

    .if ( comptr && !vtable )

        mov eax,' ,'
        stosw
        mov rsi,comptr
        .while byte ptr [rsi]
            movsb
        .endw
        mov byte ptr [rdi],0
    .endif

    ; v2.21 -pe dllimport:<dll> external proto <no args> error
    ;
    ; externals need invoke for the [_]_imp_ prefix
    ;
    mov eax,i
    lea ecx,[rax+3]
    inc eax

    .if ( !comptr && ( ( j == eax && eax > 1 ) || j == ecx ) )

        xor eax,eax
        mov rcx,sym
        .if rcx

            .if ( [rcx].asym.state == SYM_EXTERNAL )

                .if ( [rcx].asym.dll )

                    mov rax,rcx

                .elseif ( [rcx].asym.flag2 & S_ISINLINE )

                    mov rcx,[rcx].asym.target_type
                    .if ( rcx && [rcx].asym.state == SYM_MACRO )

                        mov rax,rcx
                    .endif
                .endif
            .endif
        .endif

        .if ( rax == NULL ) ; convert INVOKE to CALL

            .if ( rcx && ( [rcx].asym.langtype == LANG_FASTCALL ||
                  [rcx].asym.langtype == LANG_VECTORCALL ) &&
                  ModuleInfo.Ofssize == USE64 && ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

                mov rdx,CurrProc
                .if ( rdx )
                    or [rdx].asym.sflags,S_STKUSED
                .endif
            .endif
            lea rdx,b
            mov eax,'llac'
            mov [rdx],eax
            mov rcx,rdi
            lea rdi,[rdx+4]
            lea rsi,[rdx+6]
            sub rcx,rsi
            inc ecx
            rep movsb
        .endif
    .endif

    mov rax,dst
    .if ( B[rax] != 0 )
        tstrcat(rax, &EOLSTR)
    .endif
    tstrcat(dst, &b)
    StripSource(i, j, tokenarray)
    ret

LKRenderHllProc endp


    assume rbx: NOTHING

RenderHllProc proc __ccall private uses rsi rdi dst:string_t, i:uint_t, tokenarray:ptr asm_tok

  local oldstat:input_status

    PushInputStatus( &oldstat )
    mov rsi,LKRenderHllProc( dst, i, tokenarray )
    mov rdi,LclAlloc( MAX_LINE_LEN )
    tstrcpy( rax, ModuleInfo.currsource )
    PopInputStatus( &oldstat )
    Tokenize( rdi, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax
   .return( rsi )

RenderHllProc endp


ExpandHllProc proc __ccall public uses rsi rdi dst:string_t, i:int_t, tokenarray:ptr asm_tok

  local rc:int_t

    mov rc,NOT_ERROR
    mov rax,dst
    mov B[rax],0

    .if ( ModuleInfo.strict_masm_compat == 0 )

        mov esi,i
        mov edi,esi
        imul edi,edi,asm_tok
        add rdi,tokenarray

        .while esi < ModuleInfo.token_count

            .if [rdi].asm_tok.hll_flags & T_HLL_PROC

                ExpandCStrings( tokenarray )
                mov rc,RenderHllProc( dst, esi, tokenarray )
                ;.break
            .endif
            add rdi,asm_tok
            add esi,1
        .endw
    .endif
    .return( rc )

ExpandHllProc endp


ExpandHllProcEx proc __ccall public  uses rsi rdi buffer:string_t, i:int_t, tokenarray:ptr asm_tok

  local rc:int_t

    mov rc,ExpandHllProc(buffer, i, tokenarray)

    .repeat

        .break .if ( eax == ERROR )

        mov rsi,buffer
        .break .if ( byte ptr [rsi] == 0 )

        tstrcat( rsi, "\n" )
        mov rbx,tokenarray
        tstrcat( rsi, [rbx].asm_tok.tokpos )
        QueueTestLines( rsi )
        mov rc,STRING_EXPANDED
    .until 1

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

ExpandHllProcEx endp


EvaluateHllExpression proc __ccall public uses rsi rdi rbx hll:ptr hll_item,
    i:ptr int_t, tokenarray:ptr asm_tok, ilabel:int_t, is_true:int_t, buffer:string_t

  local hllop:hll_opnd, b[MAX_LINE_LEN]:char_t

    mov rsi,i
    mov rbx,tokenarray

    mov hllop.lastjmp,NULL
    mov hllop.lasttruelabel,0

    mov rdx,hll
    mov eax,[rdx].hll_item.flags
    and eax,HLLF_EXPRESSION

    .if ( ( ModuleInfo.strict_masm_compat == 0 ) && !eax && [rbx].asm_tok.hll_flags & T_HLL_DELAY )

        mov edi,[rsi]
        .while ( edi < ModuleInfo.token_count )

            imul eax,edi,asm_tok
            .if ( [rbx+rax].asm_tok.hll_flags & T_HLL_MACRO )

                tstrcpy( buffer, [rbx].asm_tok.tokpos )
                mov rax,hll
                or  [rax].hll_item.flags,HLLF_EXPRESSION

                .if ( [rbx].asm_tok.hll_flags & T_HLL_DELAYED )

                    or [rax].hll_item.flags,HLLF_DELAYED
                .endif

                .return NOT_ERROR
            .endif
            add edi,1
        .endw
    .endif

    lea rdi,b

    .ifd ( ExpandHllProc( rdi, [rsi], rbx ) != ERROR )

        mov rcx,buffer
        mov B[rcx],0

        .ifd ( GetExpression( hll, rsi, rbx, ilabel, is_true, rcx, &hllop ) != ERROR )

            mov eax,[rsi]
            imul eax,eax,asm_tok
            add rbx,rax

            .if ( [rbx].asm_tok.token != T_FINAL )
                .return asmerr( 2154 )
            .endif

            mov rax,hll
            mov eax,[rax].hll_item.flags
            and eax,HLLF_IFD or HLLF_IFW or HLLF_IFB

            .if ( eax && B[rdi] )
                ;
                ; Parse a "cmp ax" or "test ax,ax" and resize
                ; to B/W/D ([r|e]ax).
                ;
                mov rdx,buffer
                mov ecx,[rdx]
                .while ( B[rdx] > ' ' )
                    add rdx,1
                .endw
                .while ( B[rdx] == ' ' )
                    add rdx,1
                .endw

                mov ebx,[rdx]
                .if ( bl == 'e' || bl == 'r' )
                    shr ebx,8
                .endif

                .if ( bh == 'x' )
                    .if ( ecx == 'tset' )
                        xor ecx,ecx
                    .endif
                    ;
                    ; ax , ax   -< eax,eax>
                    ; rax , rax -<  al ,  al>
                    ;
                    lea rbx,[rdx+4]
                    .while ( byte ptr [rbx] == ' ' || byte ptr [rbx] == ',' )
                        inc rbx
                    .endw

                    .switch eax

                      .case HLLF_IFD
                        mov ax,[rdx]
ifndef ASMC64
                        .if ( ModuleInfo.Ofssize == USE64 )
endif
                            mov B[rdx],'e'
                            .if ( !ecx && ax == [rbx] ) ; v2.27 - .ifd foo() & imm --> test eax,emm
                                mov B[rbx],'e'
                            .endif

ifndef ASMC64
                        .elseif ( ModuleInfo.Ofssize == USE16 )

                            .if ( B[rdx+2] != ' ' )

                                .if ecx
                                    mov D[rdx-4],'ro '
                                .else
                                    mov D[rdx-5],' dna'
                                .endif
                                dec rdx
                            .endif
                            mov [rdx+1],ax
                            mov B[rdx],'e'
                            .if ( !ecx )
                                mov B[rbx-1],'e'
                            .endif
                        .endif
endif
                        .endc

                      .case HLLF_IFW
ifndef ASMC64
                        .if ( ModuleInfo.Ofssize != USE16 )
endif
                            mov ax,[rdx]
                            mov byte ptr [rdx],' '
                            .if ( !ecx && ax == [rbx] )
                                mov byte ptr [rbx],' '
                            .endif
ifndef ASMC64
                        .endif
endif
                        .endc

                      .case HLLF_IFB
                        mov ax,[rdx]
ifndef ASMC64
                        .if ( ModuleInfo.Ofssize == USE16 )
                            mov byte ptr [rdx+1],'l'
                            .if ( !ecx && ax == [rbx] )
                                mov byte ptr [rbx+1],'l'
                            .endif
                        .else
endif
                            mov byte ptr [rdx],' '
                            mov byte ptr [rdx+2],'l'

                            .if ( !ecx && ax == [rbx] )
                                mov byte ptr [rbx],' '
                                mov byte ptr [rbx+2],'l'
                            .endif
ifndef ASMC64
                        .endif
endif
                        .endc
                    .endsw
                .endif
            .endif

            .if ( B[rdi] )

                tstrlen(rdi)
                mov W[rdi+rax],EOLCHAR
                tstrcat(rdi, buffer)
                tstrcpy(buffer, rdi)
            .endif
            mov eax,NOT_ERROR
        .endif
    .endif
    ret

EvaluateHllExpression endp


ExpandHllExpression proc __ccall public uses rsi rdi rbx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
        ilabel:int_t, is_true:int_t, buffer:string_t

   .new rc:int_t = NOT_ERROR
   .new oldstat:input_status
   .new delayed:byte = 0

    mov rsi,hll
    mov rbx,tokenarray
    mov rdi,buffer

    PushInputStatus( &oldstat )

    .if ( [rsi].hll_item.flags & HLLF_WHILE )

        mov rdi,[rsi].hll_item.condlines
        inc delayed
    .elseif ( [rsi].hll_item.flags & HLLF_DELAYED )
        inc delayed
    .else

        mov rcx,i
        imul edx,[rcx],asm_tok

        .if ( [rbx+rdx-asm_tok].asm_tok.token == T_DIRECTIVE &&
              [rbx+rdx-asm_tok].asm_tok.tokval == T_DOT_ELSEIF )
            inc delayed
        .endif
    .endif

    tstrcpy( ModuleInfo.currsource, rdi )
    Tokenize( ModuleInfo.currsource, 0, rbx, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax

    .if ( Parse_Pass == PASS_1 )

        .if ( ModuleInfo.line_queue.head )
            RunLineQueue()
        .endif
        .if ( delayed )
            mov NoLineStore,1
            ExpandLine( ModuleInfo.currsource, rbx )
            mov NoLineStore,0
           .return .if ( eax != NOT_ERROR )
        .endif

        and [rsi].hll_item.flags,not HLLF_WHILE
        EvaluateHllExpression( hll, i, rbx, ilabel, is_true, buffer )
        mov rc,eax
        QueueTestLines( buffer )

    .else
        .if ( ModuleInfo.list )
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif

        RunLineQueue()
        ExpandLine( ModuleInfo.currsource, rbx )
        mov rc,eax

        .if ( eax == NOT_ERROR )

            .if ( [rsi].hll_item.flags & HLLF_WHILE )
                and [rsi].hll_item.flags,not HLLF_WHILE
            .endif
            EvaluateHllExpression( rsi, i, rbx, ilabel, is_true, buffer )
            mov rc,eax
            QueueTestLines( buffer )
        .endif
    .endif

    PopInputStatus( &oldstat )
    Tokenize( ModuleInfo.currsource, 0, rbx, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax
    mov rax,hll
    and [rax].hll_item.flags,not HLLF_EXPRESSION
   .return( rc )

ExpandHllExpression endp


CheckCXZLines proc fastcall private uses rsi rdi rbx p:string_t
    ;
    ; for .UNTILCXZ: check if expression is simple enough. what's acceptable
    ; is ONE condition, and just operators == and != Constants (0 or != 0)
    ; are also accepted
    ;
    mov rsi,p
    mov edi,1
    xor ebx,ebx
    ;
    ; syntax ".untilcxz 1" has a problem: there's no "jmp" generated at all
    ; if this syntax is to be supported, activate the #if below.
    ;
    mov eax,[rsi]

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
                    mov edi,2
                .elseif ebx == 1 && (al == 'z' || ax == 'zn')
                    ;
                    ; 3 chars, to replace "jz"/"jnz" by
                    ; "loopz"/"loopnz"
                    ;
                    mov edi,3
                .else
                    ; anything else is "too complex"
                    mov ebx,3
                    .break
                .endif

                tstrlen( rsi )
                .whiles eax >= 0

                    add rsi,rax
                    mov cl,[rsi]
                    mov [rsi+rdi],cl
                    sub rsi,rax
                    dec eax
                .endw
                xor edi,edi

                mov eax,"pool"
                mov [rsi],eax
                .if edx == 2

                    mov B[rsi+4],'e'
                .endif
            .endif
        .endif

        inc rsi
        mov eax,[rsi]
    .endw

    mov eax,NOT_ERROR
    .if ( ebx > 2 )
        mov eax,ERROR
    .endif
    ret

CheckCXZLines endp


RenderUntilXX proc __ccall private uses rdi hll:ptr hll_item, cmd:uint_t

  local buffer[32]:char_t

    mov eax,cmd
    mov ecx,T_CX - T_AX
ifndef ASMC64
    .if ( ModuleInfo.Ofssize == USE16 )
        add ecx,T_AX
    .elseif ( ModuleInfo.Ofssize == USE32 )
        add ecx,T_EAX
    .else
        add ecx,T_RAX
    .endif
else
    add ecx,T_RAX
endif
    AddLineQueueX( " %r %r", T_DEC, ecx )
    mov rdx,hll
    mov ecx,[rdx].hll_item.labels[LSTART*4]
    AddLineQueueX( " jnz %s", GetLabelStr( ecx, &buffer ) )
    ret

RenderUntilXX endp


GetJumpString proc __ccall private cmd:uint_t

  local buffer[32]:char_t

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
        asmerr( 1011 )
    .endsw

    GetResWName( ecx, &buffer )
    .if ( byte ptr [rax+2] == 0 )
        mov word ptr [rax+2],' '
    .endif
    ret

GetJumpString endp


    option proc:public

    assume rbx: ptr asm_tok
    assume rsi: ptr hll_item

; .IF, .WHILE, .SWITCH or .REPEAT directive

HllStartDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  .new rc:int_t = NOT_ERROR
  .new cmd:uint_t
  .new buff[16]:char_t
  .new buffer[MAX_LINE_LEN]:char_t
  .new token:uint_t

    mov rbx,tokenarray
    lea rdi,buffer

    imul eax,i,asm_tok
    ;
    ; added v2.22 to seperate:
    ;
    ; .IFS from .IFS <expression>
    ; .IFB from .IFB <expression>
    ;
    movzx ecx,[rbx+rax+asm_tok].token
    mov token,ecx
    mov eax,[rbx+rax].tokval
    mov cmd,eax
    ;
    ; skip directive
    ;
    inc i
    ;
    ; v2.06: is there an item on the free stack?
    ;
    mov rsi,ModuleInfo.HllFree
    .if !rsi
        mov rsi,LclAlloc( hll_item )
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
    mov [rsi].labels[LEXIT*4],eax
    mov [rsi].flags,eax
    mov eax,cmd
    mov ecx,token

    .switch eax

      .case T_DOT_IF

        mov [rsi].cmd,HLL_IF
        mov [rsi].labels[LSTART*4],0 ; not used by .IF
        mov [rsi].labels[LTEST*4],GetHllLabel()
        ;
        ; get the C-style expression, convert to ASM code lines
        ;
        EvaluateHllExpression(rsi, &i, rbx, LTEST, 0, rdi)
        mov rc,eax
        .if ( eax == NOT_ERROR )

            QueueTestLines( rdi )
            ;
            ; if no lines have been created, the LTEST label isn't needed
            ;
            .if ( B[rdi] == NULLC )
                mov [rsi].labels[LTEST*4],0
            .endif
        .endif
        .endc

      .case T_DOT_WHILE

        or [rsi].flags,HLLF_WHILE
      .case T_DOT_REPEAT
        ;
        ; create the label to start of loop
        ;
        mov [rsi].labels[LSTART*4],GetHllLabel()
        ;
        ; v2.11: test label is created only if needed
        ;
        mov [rsi].labels[LTEST*4],0

        .if ( cmd != T_DOT_REPEAT )

            mov [rsi].cmd,HLL_WHILE
            mov [rsi].condlines,0
            imul eax,i,asm_tok

            .if ( [rbx+rax].asm_tok.token != T_FINAL )

                mov ecx,[rsi].flags
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
                mov [rsi].flags,ecx
                EvaluateHllExpression( rsi, &i, rbx, LSTART, 1, rdi )
                mov rc,eax

            .elseif ( cmd != T_DOT_WHILE )

                GetLabelStr([rsi].labels[LSTART*4], &[rdi+20])
                tstrcpy(rdi, GetJumpString(cmd))
                tstrcat(rdi, " ")
                tstrcat(rdi, &[rdi+20])
                InvertJump(rdi)
                mov eax,NOT_ERROR
            .else
                ;
                ; just ".while" without expression is accepted
                ;
                mov B[rdi],NULLC
                mov eax,ERROR
            .endif

            .if ( eax == NOT_ERROR )

                mov [rsi].condlines,LclDup(rdi)
            .endif

            ; create a jump to test label
            ; optimisation: if line at 'test' label is just a jump,
            ; dont create label and don't jump!
            ;
            .ifd tmemicmp(rdi, "jmp", 3)

                mov [rsi].labels[LTEST],GetHllLabel()
                AddLineQueueX("jmp %s", GetLabelStr([rsi].labels[LTEST*4], &buff))
            .endif
        .else
            mov [rsi].cmd,HLL_REPEAT
        .endif

        mov cl,ModuleInfo.loopalign
        .if cl
            mov eax,1
            shl eax,cl
            AddLineQueueX("ALIGN %d", eax)
        .endif
        AddLineQueueX("%s%s", GetLabelStr([rsi].labels[LSTART*4], &buff), LABELQUAL)
        .endc

      .case T_DOT_IFS
        .if ecx != T_FINAL

            or [rsi].flags,HLLF_IFS
            .gotosw(T_DOT_IF)
        .endif
      .case T_DOT_IFB
      .case T_DOT_IFC
        .if ecx != T_FINAL

            or [rsi].flags,HLLF_IFB
            .gotosw(T_DOT_IF)
        .endif
      .case T_DOT_IFA .. T_DOT_IFNZ
        mov [rsi].cmd,HLL_IF
        mov [rsi].labels[LSTART*4],0
        mov [rsi].labels[LTEST*4],GetHllLabel()
        GetLabelStr([rsi].labels[LTEST*4], &buff)
        .if GetJumpString(cmd)

            tstrcat(tstrcpy(&buffer, rax), " ")
            lea rcx,buff
            AddLineQueue(tstrcat(rax, rcx))
        .endif
        .endc

      .case T_DOT_IFSD
        or  [rsi].flags,HLLF_IFS
      .case T_DOT_IFD
        or  [rsi].flags,HLLF_IFD
        .gotosw(T_DOT_IF)
      .case T_DOT_IFSW
        or  [rsi].flags,HLLF_IFS
      .case T_DOT_IFW
        or  [rsi].flags,HLLF_IFW
        .gotosw(T_DOT_IF)
      .case T_DOT_IFSB
        or  [rsi].flags,HLLF_IFB OR HLLF_IFS
        .gotosw(T_DOT_IF)
      .case T_DOT_WHILEA .. T_DOT_WHILESD
        .gotosw(T_DOT_WHILE)
    .endsw

    imul eax,i,asm_tok
    .if ( ![rsi].flags && ( [rbx+rax].asm_tok.token != T_FINAL && rc == NOT_ERROR ) )
        mov rc,asmerr( 2008, [rbx+rax].asm_tok.tokpos )
    .endif
    ;
    ; v2.06: remove the item from the free stack
    ;
    .if ( rsi == ModuleInfo.HllFree )
        mov rax,[rsi].next
        mov ModuleInfo.HllFree,rax
    .endif
    mov rax,ModuleInfo.HllStack
    mov [rsi].next,rax
    mov ModuleInfo.HllStack,rsi

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( ModuleInfo.line_queue.head ) ; might be NULL! (".if 1")
        RunLineQueue()
    .endif
    .return rc

HllStartDir endp

;
; .ENDIF, .ENDW, .UNTIL and .UNTILCXZ directives.
; These directives end a .IF, .WHILE or .REPEAT block.
;
HllEndDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

   .new rc:int_t = NOT_ERROR
   .new cmd:int_t
   .new buffer[MAX_LINE_LEN]:char_t

    mov rsi,ModuleInfo.HllStack
    .if ( rsi == NULL )
        .return asmerr( 1011 )
    .endif

    mov rax,[rsi].next
    mov rcx,ModuleInfo.HllFree
    mov ModuleInfo.HllStack,rax
    mov [rsi].next,rcx
    mov ModuleInfo.HllFree,rsi

    lea rdi,buffer
    mov rbx,tokenarray
    mov ecx,[rsi].cmd
    imul edx,i,asm_tok
    mov eax,[rbx+rdx].tokval
    mov cmd,eax

    .switch eax

      .case T_DOT_ENDIF

        .if ( ecx != HLL_IF )
            .return asmerr( 1011 )
        .endif
        inc i
        ;
        ; if a test label isn't created yet, create it
        ;
        mov eax,[rsi].labels[LTEST*4]
        .if eax
            AddLineQueueX( "%s%s", GetLabelStr( eax, rdi ), LABELQUAL )
        .endif
        .endc

      .case T_DOT_ENDW

        .if ( ecx != HLL_WHILE )
            .return asmerr( 1011 )
        .endif
        ;
        ; create test label
        ;
        mov eax,[rsi].labels[LTEST*4]
        .if eax
            AddLineQueueX( "%s%s", GetLabelStr( eax, rdi ), LABELQUAL )
        .endif

        inc i
        .if ( [rsi].flags & HLLF_EXPRESSION )
            ExpandHllExpression( rsi, &i, tokenarray, LSTART, 1, rdi )
        .else
            QueueTestLines( [rsi].condlines )
        .endif
        .endc

      .case T_DOT_UNTILCXZ

        .if ( ecx != HLL_REPEAT )
            .return asmerr( 1010, [rbx+rdx].string_ptr )
        .endif

        inc i
        lea rbx,[rbx+rdx+asm_tok]

        mov eax,[rsi].labels[LTEST*4]
        .if eax
            ;
            ; v2.11: LTEST only needed if .CONTINUE has occured
            ;
            AddLineQueueX( "%s%s", GetLabelStr(eax, rdi), LABELQUAL )
        .endif
        ;
        ; read in optional (simple) expression
        ;
        .if ( [rbx].token != T_FINAL )

            mov ecx,LSTART
            .if ( Options.masm_compat_gencode == 0 && ModuleInfo.strict_masm_compat == 0 )

                ;
                ; <expression> ? .BREAK
                ;
                .if ( ![rsi].labels[LEXIT*4] )

                    mov [rsi].labels[LEXIT*4],GetHllLabel()
                .endif
                mov ecx,LEXIT
            .endif

            EvaluateHllExpression(rsi, &i, tokenarray, ecx, 0, rdi)
            mov rc,eax

            .if ( eax == NOT_ERROR )

                .if ( ModuleInfo.strict_masm_compat == 1 ||
                      ( Options.masm_compat_gencode == 1 && cmd == T_DOT_UNTILCXZ ) )

                    mov rc,CheckCXZLines( rdi )
                .endif

                .if ( eax == NOT_ERROR )
                    ;
                    ; write condition lines
                    ;
                    QueueTestLines( rdi )
                    .if ( Options.masm_compat_gencode == 0 && ModuleInfo.strict_masm_compat == 0 )
                        RenderUntilXX( rsi, cmd )
                    .endif
                .else
                    asmerr( 2062 )
                .endif
            .endif
        .else
            .if ( ModuleInfo.strict_masm_compat == 1 || Options.masm_compat_gencode == 1 )

                AddLineQueueX( "loop %s", GetLabelStr( [rsi].labels[LSTART*4], rdi ) )
            .else
                RenderUntilXX( rsi, cmd )
            .endif
        .endif
        .endc

      .case T_DOT_UNTILA .. T_DOT_UNTILSD
      .case T_DOT_UNTIL

        .if ( ecx != HLL_REPEAT )
            .return asmerr( 1010, [rbx+rdx].string_ptr )
        .endif

        inc i
        lea rbx,[rbx+rdx+asm_tok]
        mov eax,[rsi].labels[LTEST*4]

        .if ( eax ) ; v2.11: LTEST only needed if .CONTINUE has occured
            AddLineQueueX( "%s%s", GetLabelStr(eax, rdi), LABELQUAL )
        .endif
        ;
        ; read in (optional) expression
        ; if expression is missing, just generate nothing
        ;
        .if ( [rbx].token != T_FINAL )

            mov ecx,[rsi].flags
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
            mov [rsi].flags,ecx

            EvaluateHllExpression(rsi, &i, tokenarray, LSTART, 0, rdi)
            mov rc,eax
            .if ( eax == NOT_ERROR )
                QueueTestLines( rdi ) ; write condition lines
            .endif

        .elseif ( cmd != T_DOT_UNTIL )

            GetLabelStr([rsi].labels[LSTART*4], &[rdi+20])
            tstrcpy(rdi, GetJumpString(cmd))
            tstrcat(rdi, " ")
            tstrcat(rdi, &[rdi+20])
            AddLineQueue(rdi)
        .endif
        .endc
    .endsw

    ;
    ; create the exit label if it has been referenced
    ;
    mov eax,[rsi].labels[LEXIT*4]
    .if eax
        AddLineQueueX( "%s%s", GetLabelStr( eax, rdi ), LABELQUAL )
    .endif

    imul ebx,i,asm_tok
    add rbx,tokenarray
    .if ( [rbx].token != T_FINAL && rc == NOT_ERROR )

        asmerr( 2008, [rbx].tokpos )
        mov rc,ERROR
    .endif

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    ;
    ; v2.11: always run line-queue if it's not empty.
    ;
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

HllEndDir endp


HllContinueIf proc __ccall uses rsi rdi rbx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
    labelid:int_t, hll1:ptr hll_item, is_true:int_t

   .new rc:int_t = NOT_ERROR
   .new buff[16]:char_t
   .new buffer[256]:char_t

    lea  rdi,buffer
    mov  ecx,labelid
    mov  rsi,hll
    mov  rax,i
    imul ebx,[rax],asm_tok
    add  rbx,tokenarray

    .if ( [rbx].token != T_FINAL )

        .if ( [rbx].token == T_DIRECTIVE )

            xor edx,edx
            mov eax,[rbx].tokval

            .switch eax
              .case T_DOT_IFSD
                or edx,HLLF_IFS
              .case T_DOT_IFD
                or edx,HLLF_IFD
              .case T_DOT_IF

               .new cmd:uint_t = [rsi].cmd
               .new condlines:ptr = [rsi].condlines
               .new flags:uint_t = [rsi].flags
                mov [rsi].flags,edx
                mov [rsi].cmd,HLL_BREAK
                mov rdx,i
                inc D[rdx]
                EvaluateHllExpression(rsi, rdx, tokenarray, labelid, is_true, rdi)
                mov rc,eax
                .if eax == NOT_ERROR
                    QueueTestLines(rdi)
                .endif
                mov [rsi].cmd,cmd
                mov [rsi].condlines,condlines
                mov [rsi].flags,flags
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
                .if ( [rbx+asm_tok].token != T_FINAL )
                    or edx,HLLF_IFS
                   .gotosw(T_DOT_IF)
                .endif
              .case T_DOT_IFB
              .case T_DOT_IFC
                .if ( [rbx+asm_tok].token != T_FINAL )
                    or edx,HLLF_IFB
                   .gotosw(T_DOT_IF)
                .endif
              .case T_DOT_IFA .. T_DOT_IFNZ

                mov rax,i
                inc D[rax]
                GetLabelStr([rsi].labels[rcx*4], &buff)
                tstrcpy(rdi, GetJumpString( [rbx].tokval))
                tstrcat(rdi, " ")
                tstrcat(rdi, &buff)
                .if is_true
                    InvertJump(rdi)
                .endif
                AddLineQueue(rdi)
               .endc
            .endsw
        .endif

    .else

        AddLineQueueX( " jmp %s", GetLabelStr( [rsi].labels[rcx*4], rdi ) )

        mov rdx,hll1
        .if ( [rdx].hll_item.cmd == HLL_SWITCH )
            ;
            ; unconditional jump from .case
            ; - set flag to skip exit-jumps
            ;
            mov rsi,rdx
            mov rax,rsi

            .while [rsi].caselist
                mov rsi,[rsi].caselist
            .endw
            .if ( rax != rsi )
                or [rsi].flags,HLLF_ENDCOCCUR
            .endif
        .endif
    .endif
    .return rc

HllContinueIf endp


;
; .ELSE, .ELSEIF, .CONTINUE and .BREAK directives.
; .ELSE, .ELSEIF:
;    - create a jump to exit label
;    - render test label if it was referenced
;    - for .ELSEIF, create new test label and evaluate expression
; .CONTINUE, .BREAK:
;    - jump to test / exit label of innermost .WHILE/.REPEAT block
;

HllExitDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

   .new rc:int_t = NOT_ERROR
   .new cont0:int_t = 0 ; exit level 0,1,2,3
   .new cmd:int_t
   .new buff[16]:char_t
   .new buffer[MAX_LINE_LEN]:char_t
   .new hll:ptr hll_item = ModuleInfo.HllStack

    mov rsi,rax
    .if ( rsi == NULL )
        .return asmerr( 1011 )
    .endif
    ExpandCStrings( tokenarray )

    lea  rdi,buffer
    imul ebx,i,asm_tok
    add  rbx,tokenarray
    mov  cmd,[rbx].tokval
    xor  ecx,ecx

    .switch eax
    .case T_DOT_ELSEIFSD
        or  [rsi].flags,HLLF_IFD
    .case T_DOT_ELSEIFS
        or  [rsi].flags,HLLF_IFS
    .case T_DOT_ELSEIF
        or  [rsi].flags,HLLF_ELSEIF
    .case T_DOT_ELSE

        .if ( [rsi].cmd != HLL_IF )
            .return asmerr( 1010, [rbx].string_ptr )
        .endif
        ;
        ; v2.08: check for multiple ELSE clauses
        ;
        .if ( [rsi].flags & HLLF_ELSEOCCURED )
            .return asmerr( 2142 )
        .endif

        ;
        ; the exit label is only needed if an .ELSE branch exists.
        ; That's why it is created delayed.
        ;
        .if ( [rsi].labels[LEXIT*4] == 0 )
            mov [rsi].labels[LEXIT*4],GetHllLabel()
        .endif
        AddLineQueueX( "jmp %s", GetLabelStr( [rsi].labels[LEXIT*4], rdi ) )

        .if ( [rsi].labels[LTEST*4] > 0 )

            AddLineQueueX( "%s%s", GetLabelStr( [rsi].labels[LTEST*4], rdi ), LABELQUAL )
            mov [rsi].labels[LTEST*4],0
        .endif

        inc i
        .if ( cmd != T_DOT_ELSE )
            ;
            ; create new labels[LTEST] label
            ;
            mov [rsi].labels[LTEST*4],GetHllLabel()
            EvaluateHllExpression( rsi, &i, tokenarray, LTEST, 0, rdi )
            mov rc,eax

            .if ( eax == NOT_ERROR )

                .if ( [rsi].flags & HLLF_EXPRESSION )

                    ExpandHllExpression( rsi, &i, tokenarray, LTEST, 0, rdi )
                    mov eax,ModuleInfo.token_count
                    mov i,eax
                .else
                    QueueTestLines( rdi )
                .endif
            .endif
        .else
            or [rsi].flags,HLLF_ELSEOCCURED
        .endif
        .endc

      .case T_DOT_ELSEIFD
        or [rsi].flags,HLLF_IFD
        .gotosw(T_DOT_ELSEIF)

      .case T_DOT_BREAK
      .case T_DOT_CONTINUE

        .if ( [rbx+asm_tok].token == T_OP_BRACKET && [rbx+asm_tok*3].token == T_CL_BRACKET )

            mov rcx,[rbx+asm_tok*2].string_ptr
            mov eax,[rcx]
            .if ( cmd == T_DOT_CONTINUE && al == '0' )
                mov cont0,1
            .endif
            xor ecx,ecx
            .while al
                imul    ecx,ecx,10
                sub     al,'0'
                movzx   edx,al
                add     ecx,edx
                shr     eax,8
            .endw
            add i,3
            add rbx,asm_tok*3
            mov eax,cmd
        .endif

        .for ( : rsi && ( [rsi].cmd == HLL_IF || [rsi].cmd == HLL_SWITCH ) : rsi = [rsi].next )

        .endf

        .while ( rsi && ecx )
            .for ( rsi = [rsi].next : rsi && ( [rsi].cmd == HLL_IF || [rsi].cmd == HLL_SWITCH ),
                 : rsi = [rsi].next )
            .endf
            dec ecx
        .endw

        .if ( rsi == 0 )
            .return asmerr( 1011 )
        .endif
        ;
        ; v2.11: create 'exit' and 'test' labels delayed.
        ;
        .if ( eax == T_DOT_BREAK )

            .if ( [rsi].labels[LEXIT*4] == 0 )
                mov [rsi].labels[LEXIT*4],GetHllLabel()
            .endif
            mov ecx,LEXIT
        .else
            ;
            ; 'test' is not created for .WHILE loops here; because
            ; if it doesn't exist, there's no condition to test.
            ;
            .if ( [rsi].cmd == HLL_REPEAT && [rsi].labels[LTEST*4] == 0 )
                mov [rsi].labels[LTEST*4],GetHllLabel()
            .endif

            mov ecx,LTEST
            .if ( cont0 == 1 )
                mov ecx,LSTART
            .elseif ( [rsi].labels[LTEST*4] == 0 )
                mov ecx,LSTART
            .endif
        .endif
        ;
        ; .BREAK .IF ... or .CONTINUE .IF ?
        ;
        inc i
        add rbx,asm_tok
        mov rc,HllContinueIf(rsi, &i, tokenarray, ecx, hll, 1)
       .endc
    .endsw

    imul ebx,i,asm_tok
    add rbx,tokenarray

    .if ( [rbx].token != T_FINAL && rc == NOT_ERROR )

        asmerr( 2008, [rbx].tokpos )
        mov rc,ERROR
    .endif

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    ;
    ; v2.11: always run line-queue if it's not empty.
    ;
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

HllExitDir endp


; check if an hll block has been left open. called after pass 1

HllCheckOpen proc __ccall

    .if ( ModuleInfo.HllStack )
        asmerr( 1010, ".if-.repeat-.while" )
    .endif
    .if ( ModuleInfo.NspStack )
        asmerr( 1010, ".namespace" )
    .endif
    ret

HllCheckOpen endp


; HllInit() is called for each pass

HllInit proc __ccall pass:int_t

    mov ModuleInfo.hll_label,0      ; init hll label counter
    ret

HllInit endp

    END
