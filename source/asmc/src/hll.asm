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

define B <BYTE PTR>
define W <WORD PTR>
define D <DWORD PTR>


.pragma warning(disable: 6004)

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

GetCOp proc fastcall private item:ptr asm_tok

    mov edx,[ecx].asm_tok.string_ptr
    xor eax,eax
    .if [ecx].asm_tok.token == T_STRING

        mov eax,[ecx].asm_tok.stringlen
    .endif

    .switch

      .case eax == 2
        mov ax,[edx]
        .switch eax
          .case CHARS_EQ:  .return COP_EQ
          .case CHARS_NE:  .return COP_NE
          .case CHARS_GE:  .return COP_GE
          .case CHARS_LE:  .return COP_LE
          .case CHARS_AND: .return COP_AND
          .case CHARS_OR:  .return COP_OR
        .endsw
        .endc

      .case eax == 1
        mov al,[edx]
        .switch eax
          .case '>': .return COP_GT
          .case '<': .return COP_LT
          .case '&': .return COP_ANDB
          .case '!': .return COP_NEG
        .endsw
        .endc

      .case [ecx].asm_tok.token != T_ID
        .endc
        ;
        ; a valid "flag" string must end with a question mark
        ;
      .case B[edx + strlen(edx) - 1] == '?'

        mov ecx,[edx]
        and ecx,not 0x20202020

        .switch eax
          .case 5
            .return COP_ZERO .if ecx == "OREZ"
            .return COP_SIGN .if ecx == "NGIS"
            .endc
          .case 6
            mov al,[edx+4]
            and eax,not 0x20
            .return COP_CARRY .if eax == "Y" && ecx == "RRAC"
            .endc
          .case 7
            mov ax,[edx+4]
            and eax,not 0x2020
            .return COP_PARITY .if eax == "YT" && ecx == "IRAP"
            .endc
          .case 9
            mov eax,[edx+4]
            and eax,not 20202020h
            .return COP_OVERFLOW .if eax == "WOLF" && ecx == "REVO"
            .endc
          .endsw
          .endc
    .endsw
    mov eax,COP_NONE
    ret

GetCOp  endp

;
; render an instruction
;

    assume ebx:ptr asm_tok

RenderInstr proc private uses esi edi ebx dst:string_t, inst:string_t, start1:uint_t,
        end1:uint_t, start2:uint_t, end2:uint_t, tokenarray:ptr asm_tok

  local reg:string_t

    mov reg,0

    mov edi,dst
    mov ebx,tokenarray

    ; v2.30 - test if second operand starts with '&'

    mov ecx,start2
    .if ecx != EMPTY && ModuleInfo.Ofssize != USE16

        shl ecx,4
        .if [ebx+ecx].token == T_STRING

            mov eax,[ebx+ecx].string_ptr
            .if word ptr [eax] == '&'

                lea eax,@CStr("eax")
                .if ModuleInfo.Ofssize == USE64
                    lea eax,@CStr("rax")
                .endif
                mov reg,eax

                imul edx,end2,asm_tok
                mov esi,[ebx+edx].tokpos
                mov dl,[esi]
                mov byte ptr [esi],0
                push edx
                sprintf(edi, "lea %s, %s\n", eax, [ebx+ecx+16].tokpos)
                add edi,eax
                pop edx
                mov [esi],dl
            .endif
        .endif
    .endif

    ; copy the instruction

    mov esi,inst
    mov ecx,strlen(esi)
    rep movsb
    mov eax,' '
    stosb

    ; copy the first operand's tokens

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

        mov word ptr [edi],' ,'
        add edi,2

        ; copy the second operand's tokens
        .if reg
            mov ecx,3
            mov esi,reg
        .else
            shl ecx,4
            shl eax,4
            mov ecx,[ebx+ecx].asm_tok.tokpos
            mov esi,[ebx+eax].asm_tok.tokpos
            sub ecx,esi
        .endif
        rep movsb

    .elseif ecx != EMPTY

        sprintf(edi, ", %d", ecx)
        add edi,eax
    .endif
    mov W[edi],EOLCHAR
    lea eax,[edi+1]
    ret

RenderInstr endp

GetLabelStr proc l_id:int_t, buff:string_t
    sprintf( buff, "@C%04X", l_id )
    mov eax,buff
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
    mov W[eax-1],EOLCHAR
    ret

RenderJcc endp

;
; a "token" in a C expression actually is an assembly expression
;
LGetToken proc private uses esi edi ebx hll:ptr hll_item, i:int_t, tokenarray:ptr asm_tok, opnd:ptr expr
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

    .for ( : edi < ModuleInfo.token_count,
           GetCOp(ebx) == COP_NONE : edi++, ebx += 16 )
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
    ret
LGetToken endp

GetLabel proto watcall hll:ptr hll_item, index:int_t {
    mov eax,[eax].hll_item.labels[edx*4]
    }

; a "simple" expression is
; 1. two tokens, coupled with a <cmp> operator: == != >= <= > <
; 2. two tokens, coupled with a "&" operator
; 3. unary operator "!" + one token
; 4. one token (short form for "<token> != 0")
;

GetSimpleExpression proc private uses esi edi ebx \
        hll:        ptr hll_item,
        i:          ptr int_t,
        tokenarray: ptr asm_tok,
        ilabel:     int_t,
        is_true:    uint_t,
        buffer:     string_t,
        hllop:      ptr hll_opnd

    mov  esi,i
    mov  edi,[esi]
    imul ebx,edi,asm_tok
    add  ebx,tokenarray

    .for ( eax = [ebx].string_ptr : word ptr [eax] == '!' : eax = [ebx].string_ptr )

        inc edi
        add ebx,16

        mov eax,1
        sub eax,is_true
        mov is_true,eax
    .endf
    mov [esi],edi
    ;
    ; the problem with '()' is that is might enclose just a standard Masm
    ; expression or a "hll" expression. The first case is to be handled
    ; entirely by the expression evaluator, while the latter case is to be
    ; handled HERE!
    ;
    .if ( [ebx].token == T_OP_BRACKET )

        .for ( edi = 1, ebx += 16,
            al = [ebx].token : al != T_FINAL : ebx += 16, al = [ebx].token )
            .if ( al == T_OP_BRACKET )
                inc edi
            .elseif ( al == T_CL_BRACKET )
                dec edi
                .break .ifz ; a standard Masm expression?
            .else
                .break .if ( GetCOp(ebx) != COP_NONE )
            .endif
        .endf

        .if ( edi )

            inc dword ptr [esi]

            .if GetExpression(
                    hll,
                    esi,
                    tokenarray,
                    ilabel,
                    is_true,
                    buffer,
                    hllop) == ERROR
                .return
            .endif

            imul ebx,[esi],asm_tok
            add  ebx,tokenarray
            .if ( [ebx].token != T_CL_BRACKET )
                .return asmerr(2154)
            .endif
            inc dword ptr [esi]
           .return NOT_ERROR
        .endif
    .endif

    mov edi,[esi]
    mov ebx,tokenarray
    ;
    ; get (first) operand
    ;
   .new is_float:byte = 0
   .new inst_cmp:string_t = "cmp"
   .new op1_pos:int_t = edi
   .new op1:expr

    .if LGetToken(hll, esi, ebx, &op1) == ERROR
        .return
    .endif

    .if ( op1.kind == EXPR_REG && !( op1.flags & E_INDIRECT ) )

        mov eax,op1.base_reg

        .if ( eax )

            .if ( GetValueSp( [eax].asm_tok.tokval ) & ( OP_XMM or OP_YMM or OP_ZMM ) )

                lea eax,@CStr( "comisd" )
                .if ( ModuleInfo.flt_size == 4 )
                    lea eax,@CStr( "comiss" )
                .endif
                mov inst_cmp,eax
                inc is_float
            .endif
        .endif
    .endif

    mov edi,[esi]
   .new op1_end:int_t = edi

    lea eax,[edi*8] ; get operator
    lea eax,[ebx+eax*2]
    ;
    ; lower precedence operator ( && or || ) detected?
    ;
    .if ( GetCOp(eax) == COP_AND || eax == COP_OR )
        mov eax,COP_NONE
    .elseif ( eax != COP_NONE )
        inc edi
        mov [esi],edi
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

        mov ecx,hllop
        mov [ecx].hll_opnd.lastjmp,buffer
        movzx ecx,flaginstr[edx - COP_ZERO]
        mov edx,is_true
        xor edx,1

        ; v2.27.30: ZERO? || CARRY? --> LE

        lea eax,[edi+1]
        .if ( eax < ModuleInfo.token_count && ( op == COP_ZERO || op == COP_CARRY ) )

            push ecx
            push edx
            shl eax,4
            add eax,ebx
            GetCOp(eax)
            pop edx
            pop ecx

            .if ( eax == COP_ZERO || eax == COP_CARRY )

                mov ecx,'a'
                xor edx,1
                add edi,2
                mov [esi],edi
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

                lea eax,@CStr( "test" )
                .if ( Options.masm_compat_gencode )
                    lea eax,@CStr( "or" )
                .endif
                RenderInstr( buffer, eax, op1_pos, op1_end,
                    op1_pos, op1_end, ebx )
                mov edx,hllop
                mov [edx].hll_opnd.lastjmp,eax
                RenderJcc( eax, 'z', is_true, jcclabel )
                .endc
            .endif
            ;
            ; no break
            ;
          .case EXPR_ADDR

            RenderInstr( buffer, inst_cmp, op1_pos, op1_end, EMPTY, 0, ebx )
            mov edx,hllop
            mov [edx].hll_opnd.lastjmp,eax
            RenderJcc( eax, 'z', is_true, jcclabel )
            .endc
          .case EXPR_CONST
            .if ( op1.hvalue != 0 && op1.hvalue != -1 )
                .return EmitConstError( &op1 )
            .endif
            mov ecx,hllop
            mov [ecx].hll_opnd.lastjmp,buffer
            mov edx,is_true
            xor edx,1
            .if ( ( is_true && op1.value ) || ( edx && op1.value == 0 ) )
                sprintf( buffer, "jmp @C%04X%s", jcclabel, &EOLSTR )
            .else
                mov B[eax],NULLC
            .endif
            .endc
        .endsw
        .return NOT_ERROR
    .endif

    ;
    ; get second operand for binary operator
    ;
    mov edi,[esi]
   .new op2_pos:int_t = edi

    ; v2.30 - test if second operand starts with '&'

    imul eax,edi,asm_tok
    .if ( [ebx+eax].token == T_STRING )
        mov eax,[ebx+eax].string_ptr
        .if ( word ptr [eax] == '&' )
            inc dword ptr [esi]
        .endif
    .endif

    .new op2:expr
    .return .if LGetToken(hll, esi, ebx, &op2) == ERROR

    mov eax,op2.kind
    .if ( eax != EXPR_CONST && eax != EXPR_ADDR && eax != EXPR_REG )
        .if ( eax == EXPR_FLOAT && is_float )
            mov op2.kind,EXPR_ADDR
        .else
            .return asmerr(2154)
        .endif
    .endif

    mov edi,[esi]
   .new op2_end:int_t = edi

    assume ebx: NOTHING
    ;
    ; now generate ASM code for expression
    ;
    mov ecx,op
    .if ( ecx == COP_ANDB )
        ;
        ; v2.22 - switch /Zg to OR
        ;
        lea eax,@CStr("test")
        .if Options.masm_compat_gencode
            lea eax,@CStr("or")
        .endif
        RenderInstr( buffer, eax, op1_pos, op1_end, op2_pos, op2_end, ebx )
        mov ecx,hllop
        mov [ecx].hll_opnd.lastjmp,eax
        RenderJcc( eax, 'e', is_true, jcclabel )

    .elseif ( ecx <= COP_LE )
        ;
        ; ==, !=, >, <, >= or <= operator
        ;
        ; optimisation: generate 'or EAX,EAX' instead of 'cmp EAX,0'.
        ; v2.11: use op2.value64 instead of op2.value
        ;
        mov eax,DWORD PTR op2.value64
        or  eax,DWORD PTR op2.value64[4]

        .if ( !eax && (ecx == COP_EQ || ecx == COP_NE) && op1.kind == EXPR_REG && \
              !( op1.flags & E_INDIRECT ) && op2.kind == EXPR_CONST && !is_float )
            ;
            ; v2.22 - switch /Zg to OR
            ;
            lea eax,@CStr("test")
            .if ( Options.masm_compat_gencode )
                lea eax,@CStr("or")
            .endif
            RenderInstr( buffer, eax, op1_pos, op1_end, op1_pos, op1_end, ebx )
        .else
            RenderInstr( buffer, inst_cmp,  op1_pos, op1_end, op2_pos, op2_end, ebx )
        .endif
        mov ebx,hllop
        mov [ebx].hll_opnd.lastjmp,eax

        ;
        ; v2.22 - signed compare S, SB, SW, SD
        ;
        mov edx,hll
        xor edi,edi
        mov ecx,[edx].hll_item.flags
        .if ( ecx & HLLF_IFS )
            inc edi
        .endif

        mov ecx,op
        movzx edx,op1.mem_type
        movzx eax,op2.mem_type
        and edx,MT_SPECIAL_MASK
        and eax,MT_SPECIAL_MASK

        .if ( edi || edx == MT_SIGNED || eax == MT_SIGNED )
if 0
            .if ( op1.kind == EXPR_ADDR && op2.kind == EXPR_ADDR )

                mov edx,hll
                .if ( [edx].hll_item.labels[LSTART*4] == 0 )

                    inc ModuleInfo.hll_label
                    mov edi,ModuleInfo.hll_label
                    mov [edx].hll_item.labels[LSTART*4],edi
                .endif
            .endif
endif
            movzx edx,signed_cjmptype[ecx-COP_EQ]
        .else
            movzx edx,unsign_cjmptype[ecx-COP_EQ]
        .endif

        mov eax,is_true
        .if ( !neg_cjmptype[ecx-COP_EQ] )
            xor eax,1
        .endif
        RenderJcc( [ebx].hll_opnd.lastjmp, edx, eax, jcclabel )
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

    .if B[ecx] == NULLC ; v2.11: convert 0 to "jmp"

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
        mov B[ecx+1],al
        mov B[ecx],'n'
        ret
      .case 'n'
        mov B[ecx],ah
        mov B[ecx+1],' '
        ret
      .case 'a'
        mov B[ecx],'b'
        .endc
      .case 'b'
        mov B[ecx],'a'
        .endc
      .case 'g'
        mov B[ecx],'l'
        .endc
      .case 'l'
        mov B[ecx],'g'
        .endc
      .default
        ;
        ; v2.11: convert "jmp" to 0
        ;
        .if al == 'm'

            sub ecx,1
            mov B[ecx],NULLC
        .endif
        ret
    .endsw

    .if ah == 'e'

        mov B[ecx+1],' '
    .else
        mov B[ecx+1],'e'
    .endif
    ret

InvertJump endp


; Replace a label in the source lines generated so far.
; todo: if more than 0xFFFF labels are needed,
; it may happen that length of nlabel > length of olabel!
; then the simple memcpy() below won't work!
;
ReplaceLabel proc private uses esi edi ebx p, olabel, nlabel

local oldlbl[16]:char_t, newlbl[16]:char_t

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

GetAndExpression proc private uses esi edi ebx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
    ilabel:uint_t, is_true:uint_t, buffer:string_t, hllop:ptr hll_opnd

  local truelabel:int_t, nlabel:int_t, olabel:int_t, buff[16]:char_t

    mov edi,hllop
    mov esi,buffer
    mov truelabel,0

    .while 1

        .return .if GetSimpleExpression(hll, i, tokenarray, ilabel, is_true, esi, edi ) == ERROR

        mov ebx,i
        mov eax,[ebx]
        shl eax,4
        add eax,tokenarray

        .break .if GetCOp(eax) != COP_AND

        inc D[ebx]
        mov ebx,[edi].hll_opnd.lastjmp
        .if ebx && is_true

            InvertJump(ebx)

            .if truelabel == 0

                mov truelabel,GetHllLabel()
            .endif

            ;; v2.11: there might be a 0 at lastjmp

            .if B[ebx]

                strcat(GetLabelStr(truelabel, &[ebx+4]), &EOLSTR)
            .endif

                ;; v2.22 .while  (eax || edx) && ecx -- failed
                ;;   .while !(eax || edx) && ecx -- failed

            mov ebx,esi
            .if [edi].hll_opnd.lasttruelabel

                ReplaceLabel(ebx, [edi].hll_opnd.lasttruelabel, truelabel)
            .endif
            mov nlabel,GetHllLabel()
            mov olabel,GetLabel(hll, ilabel)
            strlen(ebx)
            add ebx,eax
            sprintf(ebx, "%s%s%s", GetLabelStr(olabel, &buff), LABELQUAL, &EOLSTR)
            ReplaceLabel(buffer, olabel, nlabel)
            mov [edi].hll_opnd.lastjmp,0
        .endif

        strlen(esi)
        add esi,eax
        mov [edi].hll_opnd.lasttruelabel,0
    .endw

    .if truelabel
        strlen(esi)
        add esi,eax
        strcat(strcat(GetLabelStr(truelabel, esi), LABELQUAL), &EOLSTR)
        mov [edi].hll_opnd.lastjmp,0
    .endif
    mov eax,NOT_ERROR
    ret

GetAndExpression endp

; operator ||, which has the lowest precedence, is handled here

GetExpression proc private uses esi edi ebx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
    ilabel:int_t, is_true:uint_t, buffer:string_t, hllop:ptr hll_opnd

  local truelabel:int_t, nlabel:int_t, olabel:int_t, buff[16]:char_t

    mov esi,buffer
    mov edi,hllop
    mov truelabel,0

    .while 1

        .return .if GetAndExpression(hll, i, tokenarray, ilabel, is_true, esi, edi) == ERROR

        mov ebx,i
        mov eax,[ebx]
        shl eax,4
        add eax,tokenarray
        .break .if GetCOp(eax) != COP_OR
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
        inc D[ebx]
        mov ebx,[edi].hll_opnd.lastjmp

        .if ebx && !is_true

            InvertJump( ebx )

            .if truelabel == 0

                mov truelabel,GetHllLabel()
            .endif

            .if B[ebx]

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

            ReplaceLabel(esi, [edi].hll_opnd.lasttruelabel, truelabel)
            strchr(ebx, EOLCHAR)
            mov B[eax+1],0
        .endif

        strlen(esi)
        add esi,eax
        strcat( strcat(GetLabelStr( truelabel, esi), LABELQUAL), &EOLSTR)
        mov eax,truelabel
        mov [edi].hll_opnd.lasttruelabel,eax
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

GenerateFloat proto :int_t, :ptr asm_tok

    assume ebx:ptr asm_tok

ExpandCStrings proc uses edi ebx tokenarray:ptr asm_tok

    xor eax,eax
    .return .if ( ModuleInfo.strict_masm_compat == 1 )

    .for ( edi = 0, ebx = tokenarray: [ebx].token != T_FINAL: ebx += 16, edi++ )

        .if [ebx].hll_flags & T_HLL_PROC

            .return .if GenerateCString( edi, tokenarray )

            ; id[..]
            .if [ebx].token == T_ID && [ebx+16].token == T_OP_SQ_BRACKET

                add ebx,16
                inc edi
            .endif

            .if [ebx].token == T_OP_SQ_BRACKET

                ; invoke [...][.type].x(...)

                mov eax,1
                .repeat
                    add ebx,16
                    .if [ebx].token == T_CL_SQ_BRACKET
                        dec eax
                        .break .ifz
                    .elseif [ebx].token == T_OP_SQ_BRACKET
                        inc eax
                    .endif
                .until [ebx].token == T_FINAL
                add ebx,16
                .if [ebx].token == T_DOT
                    add ebx,16
                .endif
            .endif
            .while [ebx+16].token == T_DOT
                add ebx,32
            .endw
            mov ecx,1
            add ebx,32

            .if ( [ebx-16].token != T_OP_BRACKET )

                asmerr( 3018, [ebx-32].string_ptr, [ebx-16].string_ptr )
                .break
            .endif

            .for : [ebx].token != T_FINAL : ebx += 16

                mov edx,[ebx].string_ptr
                movzx eax,B[edx]

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
    ret

ExpandCStrings endp

GetProcVtbl proc private sym:ptr asym, name:ptr sbyte

    mov ecx,sym
    xor eax,eax
    .if [ecx].asym.mem_type == MT_TYPE && [ecx].asym.type
        mov ecx,[ecx].asym.type
    .endif
    .if [ecx].asym.target_type && \
        ( [ecx].asym.mem_type == MT_PTR || [ecx].asym.ptr_memtype == MT_TYPE )
        mov ecx,[ecx].asym.target_type
    .endif
    .if ( [ecx].asym.flag2 & S_VTABLE )
        SearchNameInStruct( [ecx].asym.vtable, name, 0, 0 )
    .endif
    ret

GetProcVtbl endp

GetProc proc private uses esi edi ebx i:int_t, tokenarray:ptr asm_tok, opnd:ptr expr

    imul ebx,i,16
    add ebx,tokenarray

    .if ( [ebx].token == T_OP_SQ_BRACKET )

        .for ( ecx = i : [ebx].token != T_FINAL : ebx+=16, ecx++ )
            .break .if ( [ebx].token == T_CL_SQ_BRACKET )
        .endf
        add ecx,3
        add ebx,32
        .return 0 .if ( [ebx+16].token !=  T_DOT )
        .return 0 .if EvalOperand( &i, tokenarray, ecx, opnd, 0 ) == ERROR
        mov ecx,opnd
        mov eax,[ecx].expr.type

    .elseif [ebx].token == T_REG
        GetStdAssume( GetRegNo( [ebx].tokval) )
    .else
        SymFind( [ebx].string_ptr )
    .endif
    .return .if !eax
    .return .if [eax].asym.flag1 & S_ISPROC

    .if [ebx].token == T_ID && \
        [ebx+16].token == T_DOT && \
        [ebx+32].token == T_ID
        .return GetProcVtbl( eax, [ebx+32].string_ptr )
    .endif

    mov ecx,[eax].asym.target_type
    mov dl,[eax].asym.mem_type
    .return ecx .if dl == MT_PTR && ecx && [ecx].asym.flag1 & S_ISPROC

    .if dl == MT_PTR && ecx && [ecx].asym.mem_type == MT_PROC

        mov eax,[eax].asym.target_type
        jmp isfnproto
    .endif

    mov ecx,[eax].asym.type
    .if dl == MT_TYPE && ( [ecx].asym.mem_type == MT_PTR || [ecx].asym.mem_type == MT_PROC )

        ; second case: symbol is a (function?) pointer

        mov eax,ecx
        .if [eax].asym.mem_type != MT_PROC
            jmp isfnptr
        .endif
    .endif

isfnproto:

    ; pointer target must be a PROTO typedef

    .return 0 .if [eax].asym.mem_type != MT_PROC

isfnptr:

    ; get the pointer target

    mov eax,[eax].asym.target_type
    ret

GetProc endp

GetParamId proc private uses esi edi id:int_t, sym:asym_t

    mov edi,sym
    mov edx,[edi].dsym.procinfo
    mov eax,[edx].proc_info.paralist
    movzx edi,[edi].asym.langtype
    .if ( edi == LANG_STDCALL || edi == LANG_C || edi == LANG_SYSCALL || \
          edi == LANG_VECTORCALL || ( edi == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) )
        .while eax && [eax].dsym.nextparam
            mov eax,[eax].dsym.nextparam
        .endw
    .endif
    mov esi,eax
    .while eax && id
        .if ( edi == LANG_STDCALL || edi == LANG_C || edi == LANG_SYSCALL || \
              edi == LANG_VECTORCALL || ( edi == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) )
            .for ( eax = [edx].proc_info.paralist : eax && [eax].dsym.nextparam != esi,
                 : eax = [eax].dsym.nextparam )
            .endf
            mov esi,eax
        .else
            mov eax,[eax].dsym.nextparam
        .endif
        dec id
    .endw
    ret

GetParamId endp

GetMacroReturn proc private uses esi ebx i:int_t, tokenarray:ptr asm_tok

  local mac_name[128]:char_t
  local opnd:expr

    ;
    ; v2.32.43 - test return value from inline function
    ;
    ; if the last line is retm<..> use this as return value
    ;

   .return .if !GetProc( i, tokenarray, &opnd )

    .if ( [eax].asym.state == SYM_STRUCT_FIELD )

        mov esi,eax

        imul ebx,i,16
        add ebx,tokenarray

        .if ( [ebx].token == T_OP_SQ_BRACKET )
            mov ecx,opnd.type
        .else
           .return .if !SymFind( [ebx].string_ptr )
            xor ecx,ecx
            .if ( [eax].asym.mem_type == MT_TYPE )
                mov ecx,[eax].asym.type
            .elseif ( [eax].asym.mem_type == MT_PTR )
                mov ecx,[eax].asym.target_type
            .endif
        .endif
        .return 0 .if ( !ecx || [ecx].asym.typekind != TYPE_STRUCT )

        strcpy( &mac_name, [ecx].asym.name )
        strcat( eax, "_" )
        strcat( eax, [esi].asym.name )
        .return .if !SymFind( eax )

        .if ( [eax].asym.state == SYM_TMACRO )
            .return .if !SymSearch( [eax].asym.string_ptr )
        .endif

        or  [esi].asym.flag2,S_VMACRO
        mov [esi].asym.vmacro,eax ; vtable method is inline - sym->vmacro set
        mov ecx,eax
        xor eax,eax

    .else

        mov ecx,[eax].asym.target_type
        mov edx,eax
        xor eax,eax

        .return .if !( [edx].asym.state == SYM_EXTERNAL || [edx].asym.state == SYM_STACK )
        .return .if !ecx

    .endif

   .return .if [ecx].asym.state != SYM_MACRO

    mov ecx,[ecx].dsym.macroinfo
    mov ecx,[ecx].macro_info.lines
   .return .if !ecx

   .while [ecx].srcline.next
        mov ecx,[ecx].srcline.next
   .endw

    lea ecx,[ecx].srcline.line
    mov edx,[ecx]
   .return .if edx != 'mter'

    add ecx,4
    mov dl,[ecx]
   .while 1
       .break .if !dl || dl == '<'
        inc ecx
        mov dl,[ecx]
   .endw
   .return .if dl != '<'
   .repeat
        inc ecx
        mov dl,[ecx]
       .continue(0) .if dl == ' '
       .continue(0) .if dl == 9
   .until 1
   .return .if !dl
   .return .if dl == '>'
    mov eax,ecx
    ret

GetMacroReturn endp

StripSource proc private uses esi edi ebx i:uint_t, e:uint_t, tokenarray:ptr asm_tok

  local sym:dsym_t
  local mac:string_t
  local curr:asym_t
  local proc_id:ptr asm_tok ; foo( 1, bar(...), ...)
  local parg_id:int_t ; foo.paralist[1] = return type[al|ax|eax|[edx::eax|rax|xmm0]]
  local opnd:expr
  local bracket:int_t
  local reg2:int_t
  local b[MAX_LINE_LEN]:char_t

    xor eax,eax
    mov mac,     eax
    mov reg2,    eax
    mov proc_id, eax
    mov parg_id, eax
    mov bracket, eax

    .for ( edi = &b, ebx = tokenarray, edx = 0 : edx < i : edx++, ebx += 16 )

        .if edx
            .if [ebx].hll_flags & T_HLL_PROC
                mov proc_id,ebx
                mov parg_id,0
            .endif
            .switch [ebx].token
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
        mov esi,[ebx].tokpos
        mov ecx,[ebx+16].tokpos
        sub ecx,esi
        rep movsb
    .endf
    mov byte ptr [edi],0

    mov edi,tokenarray
    xor esi,esi
    .if ( bracket == 0 )
        mov proc_id,esi
    .endif

    .if GetMacroReturn( i, edi )
        mov mac,eax
        jmp macro_args
    .endif

    mov ecx,proc_id
    .if ecx ;&& [ecx].asm_tok.token != T_OP_SQ_BRACKET

        sub ecx,tokenarray
        shr ecx,4
        .if GetProc( ecx, tokenarray, &opnd )

            mov sym,eax
            mov ecx,GetParamId( parg_id, eax )
            .if ecx
                mov eax,[ecx].asym.total_size
                .switch eax
                  .case 1: mov esi,T_AL : .endc
                  .case 2: mov esi,T_AX : .endc
                  .case 4:
                    mov esi,T_EAX
                    .if ModuleInfo.Ofssize == USE64 && [ecx].asym.mem_type & MT_FLOAT
                        mov esi,T_XMM0
                    .endif
                    .endc
                  .case 8
                    .if ModuleInfo.Ofssize == USE64
                        .if [ecx].asym.mem_type & MT_FLOAT
                            mov esi,T_XMM0
                        .else
                            mov esi,T_RAX
                        .endif
                    .else
                        mov esi,T_EDX
                        mov reg2,T_EAX
                    .endif
                    .endc
                  .case 16:
                    .if [ecx].asym.mem_type & MT_FLOAT
                        mov esi,T_XMM0
                    .elseif ModuleInfo.Ofssize == USE64
                        mov esi,T_RDX
                        mov reg2,T_RAX
                    .endif
                    .endc
                  .case 32:
                    .if [ecx].asym.mem_type == MT_YWORD
                        mov esi,T_YMM0
                    .endif
                    .endc
                  .case 64:
                    .if [ecx].asym.mem_type == MT_ZWORD
                        mov esi,T_ZMM0
                    .endif
                    .endc
                .endsw
            .endif
        .endif
    .endif

    .if !esi

ifndef __ASMC64__
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
        .if !proc_id && eax > 1

            shl eax,4
            lea ebx,[edi+eax-32]

            .if [ebx+16].token == T_COMMA && [ebx].token != T_CL_SQ_BRACKET

                ;
                ; <op> <reg|id> <,> <proc>
                ;
                xor eax,eax
                .if [ebx].token == T_REG

                    SizeFromRegister( [ebx].tokval )

                .elseif SymFind( [ebx].string_ptr )

                    ; movsd id,cos(..)

                    .if ( ModuleInfo.Ofssize == USE64 && \
                        ( [eax].asym.mem_type == MT_REAL4 || \
                          [eax].asym.mem_type == MT_REAL8 ) )
                        mov eax,16
                    .else
                        SizeFromMemtype( [eax].asym.mem_type, USE_EMPTY, [eax].asym.type )
                    .endif

                .elseif [ebx-16].token == T_DOT

                    ; <op> <struct>.id, rax

                    mov edx,i
                    sub i,4
                    sub ebx,32
                    .if [ebx-16].token == T_DOT
                        sub ebx,32
                        sub i,2
                    .endif

                size_from_ptr:

                    .if [ebx].token == T_CL_SQ_BRACKET
                        .while i && [ebx].token != T_OP_SQ_BRACKET
                            dec i
                            sub ebx,16
                        .endw
                    .endif
                    .if [ebx-16].tokval == T_PTR
                        sub ebx,32
                        sub i,2
                    .endif

                    sub edx,i
                    .if EvalOperand( &i, tokenarray, edx, &opnd, EXPF_NOERRMSG ) != ERROR

                        xor eax,eax
                        .if opnd.kind == EXPR_ADDR || ( opnd.flags & E_INDIRECT )
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

            .elseif [ebx+16].token == T_COMMA && [ebx].token == T_CL_SQ_BRACKET

                mov edx,i
                sub i,2
                jmp size_from_ptr
            .endif
        .endif
    .endif
    mov ebx,GetResWName(esi, 0)

macro_args:
    lea esi,b
    strcat(esi, " ")
    .if mac
        lea edi,[esi+strlen(esi)]
        mov esi,mac
        .while 1
            lodsb
            mov ah,[esi]
            .break .if !al
            .continue .if ax == '<!'
            .continue .if ax == '>!'
            stosb
        .endw
        mov [edi-1],al
        lea esi,b
        mov edi,tokenarray
    .else
        strcat(esi, ebx)
    .endif
    .if reg2
        strcat(esi, "::")
        strcat(esi, GetResWName(reg2, 0))
    .endif

    mov ebx,e
    shl ebx,4
    .if [ebx+edi].token != T_FINAL

        strcat( esi, " " )
        strcat( esi, [ebx+edi].tokpos )
    .endif

    .if ModuleInfo.list
        LstSetPosition()
    .endif

    strcpy(ModuleInfo.currsource, esi)
    Tokenize(eax, 0, edi, TOK_DEFAULT)
    mov ModuleInfo.token_count,eax
    mov eax,STRING_EXPANDED
    ret

StripSource endp


LKRenderHllProc proc private uses esi edi ebx dst:string_t, i:uint_t, tokenarray:ptr asm_tok

  local opnd:expr
  local b[MAX_LINE_LEN]:char_t
  local name:string_t
  local id:ptr asm_tok
  local args:ptr asm_tok
  local dots[10]:ptr asm_tok
  local static_struct:int_t
  local ClassVtbl[256]:char_t
  local sym:asym_t
  local type:string_t
  local method:asym_t
  local sym1:asym_t
  local comptr:string_t
  local constructor:int_t ; Class(..)
  local vtable:int_t
  local brcount:int_t
  local sqcount:int_t
  local dotcount:int_t
  local sqbrend:ptr asm_tok
  local j:int_t
  local vparray:asym_t

    xor eax,eax
    mov brcount,        eax
    mov sqcount,        eax
    mov dotcount,       eax
    mov sqbrend,        eax
    mov static_struct,  eax
    mov sym,            eax
    mov type,           eax
    mov method,         eax
    mov comptr,         eax
    mov constructor,    eax
    mov vtable,         eax
    mov vparray,        eax
    mov j,              i

    shl eax,4
    add eax,tokenarray
    mov id,eax
    mov ebx,eax

    .for ( : [ebx].token != T_FINAL : ebx+=16, j++ )

        .if [ebx].token == T_OP_SQ_BRACKET

            .for ( sqcount++, ebx+=16, j++ : sqcount && [ebx].token != T_FINAL : ebx+=16, j++ )

                .if [ebx].hll_flags & T_HLL_PROC
                    .return .if LKRenderHllProc( dst, j, tokenarray ) == ERROR
                .elseif [ebx].token == T_OP_BRACKET
                    inc brcount
                .elseif [ebx].token == T_CL_BRACKET
                    dec brcount
                .elseif !brcount && [ebx].token == T_OP_SQ_BRACKET
                    inc sqcount
                .elseif !brcount && [ebx].token == T_CL_SQ_BRACKET
                    dec sqcount
                    .ifz
                        .if !sqbrend
                            mov sqbrend,ebx
                        .endif
                        .break
                    .endif
                .endif
            .endf
        .elseif [ebx].token == T_DOT
            mov eax,dotcount
            mov dots[eax*4],ebx
            inc dotcount
        .elseif [ebx].token == T_OP_BRACKET
            .break
        .endif
    .endf
    .return asmerr(2008, [ebx].string_ptr) .if [ebx].token != T_OP_BRACKET

    mov args,ebx
    mov name,[ebx-16].string_ptr
    mov ebx,id

    .if ( [ebx].token == T_OP_SQ_BRACKET )
        ;
        ; v2.27 - [reg].Class.Method()
        ;       - [reg+foo([rax])].Class.Method()
        ;       - [reg].Method()
        ;
        xor eax,eax
        .if dotcount

            mov edx,dots
            .if dotcount > 1

                ; [reg].Class.Method()

                mov edi,name
                SymFind( [edx+16].asm_tok.string_ptr )

            .elseif [edx+32].asm_tok.token == T_OP_BRACKET

                ; [reg].Method() -- assume reg:ptr Class

                mov edi,[edx+16].asm_tok.string_ptr
                mov eax,i
                mov brcount,eax
                mov edx,dots
                sub edx,tokenarray
                shr edx,4
                .if EvalOperand( &brcount, tokenarray, edx, &opnd, 0 ) != ERROR
                    mov eax,opnd.type
                .else
                    xor eax,eax
                .endif
            .endif

            .if eax
                .if [eax].asym.state == SYM_TYPE && [eax].asym.typekind == TYPE_STRUCT
                    ;
                    ; If Class.Method do not exist assume ClassVtbl.Method do.
                    ;
                    jmp type_struct
                .else
                    xor eax,eax
                .endif
            .endif
        .endif
        mov ecx,eax

    .else

        mov sym1,SymFind( [ebx].string_ptr )
        mov edi,dotcount
        .if edi
            dec edi
        .endif

        .for ( esi = 0 : eax && edi : esi++, edi-- )
            mov ecx,eax
            .if ( [ecx].asym.mem_type == MT_TYPE )
                mov ecx,[ecx].asym.type
            .endif
            .if ( [ecx].asym.mem_type == MT_PTR )
                mov ecx,[ecx].asym.target_type
            .endif
            .break .if !ecx
            mov ebx,dots[esi*4]
            add ebx,16
            mov vparray,SearchNameInStruct( ecx, [ebx].string_ptr, 0, 0 )
        .endf

        mov sym,eax
        xor ecx,ecx
        .if ( vparray )
            mov edx,sym1
            .if ( edx != eax && [edx].asym.mem_type != MT_PTR )
                .if ( dotcount == 2 )
                    mov vparray,NULL  ; static class.ptr.proc()
                .else
                    inc static_struct ; static class.ptr.ptr...proc()
                .endif
            .endif
        .endif

        .if dotcount

            mov edi,name

        .elseif eax && [eax].asym.state == SYM_TYPE && \
                [ebx+16].token == T_OP_BRACKET

            mov edi,[ebx].string_ptr
            mov ecx,eax
            mov type,edi
        .else
            xor eax,eax
        .endif

        mov ebx,id
        .if eax

            .if ( [eax].asym.mem_type == MT_TYPE && [eax].asym.type )

                mov eax,[eax].asym.type

                .if ( [eax].asym.typekind == TYPE_TYPEDEF )

                    mov ecx,[eax].asym.target_type

                .elseif ( [eax].asym.typekind == TYPE_STRUCT )

                    inc static_struct

                    type_struct:

                    mov sym,eax
                    mov ecx,eax
                    xor eax,eax
                    .if ( [ecx].asym.flag2 & S_VTABLE )
                        SearchNameInStruct( [ecx].asym.vtable, edi, 0, 0 )
                    .endif
                    .if ( eax == NULL )
                        .if SearchNameInStruct( sym, edi, 0, 0 )
                            mov method,eax
                            mov sym,0
                        .endif
                    .endif
                    mov ecx,sym
                .endif

            .elseif ( [eax].asym.mem_type == MT_PTR && \
                    ( [eax].asym.state == SYM_STACK || [eax].asym.state == SYM_EXTERNAL ) )

                mov ecx,[eax].asym.target_type
            .endif
        .endif
    .endif

    mov name,edi
    mov edx,ecx
    lea edi,b
    lea esi,@CStr("invoke ")
    mov ecx,7
    rep movsb

    .if ( edx && [edx].asym.state == SYM_TYPE && [edx].asym.typekind == TYPE_STRUCT )

        mov esi,edx
        mov comptr,[esi].asym.name
        .if SearchNameInStruct( esi, name, 0, 0 )
            mov method,eax
        .endif
        .if ( [esi].asym.flag2 & S_VTABLE )

            .if SearchNameInStruct( [esi].asym.vtable, name, 0, 0 )
                inc vtable
                mov method,eax
                mov esi,[esi].asym.vtable
                mov comptr,[esi].asym.name
            .endif
        .endif
        .if ( method == NULL )
            .if ( strcmp( [esi].asym.name, name ) == 0 )
                inc vtable
                inc constructor
            .endif
        .elseif ( vparray )
            mov eax,method
            or [eax].asym.flag2,S_VPARRAY
        .endif
    .endif

    .if ( comptr )

        .if ( ModuleInfo.Ofssize == USE64 && !constructor )

            mov eax,method
            .if eax ; v2.28: Added for undefined symbol error..

                .if [eax].asym.mem_type == MT_TYPE && [eax].asym.type
                    mov eax,[eax].asym.type
                    .if [eax].asym.typekind == TYPE_TYPEDEF
                        mov eax,[eax].asym.target_type
                    .endif
                .endif
                .if [eax].asym.langtype == LANG_SYSCALL
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

        mov esi,comptr
        .while ( byte ptr [esi] )
            movsb
        .endw

        .if ( type )
            mov al,'.'
            .if ( constructor )
                mov al,'_'
            .endif
            stosb
            mov esi,type
            .while ( byte ptr [esi] )
                movsb
            .endw
        .endif

        .if ( [ebx].token == T_OP_SQ_BRACKET )

            .if ( [ebx+32].token == T_CL_SQ_BRACKET )

                mov eax,[ebx+16].string_ptr
            .else
                strcpy( &ClassVtbl, "addr [" )
                .for ( esi = &[ebx+16] : esi < sqbrend : esi += 16 )
                    strcat( eax, [esi].asm_tok.string_ptr )
                .endf
            .endif

        .elseif ( dotcount )

            lea eax,ClassVtbl
            mov esi,[ebx].tokpos
            mov edx,args
            sub edx,2*16
            mov ecx,[edx].asm_tok.tokpos
            sub ecx,esi
            mov edx,edi
            mov edi,eax
            rep movsb
            mov byte ptr [edi],0
            mov edi,edx
        .else
            mov eax,[ebx].string_ptr
        .endif
        mov comptr,eax
        mov eax,method
        .if eax
            or [eax].asym.flag1,S_METHOD
            .if ( !vtable )
                or [eax].asym.flag2,S_VPARRAY
            .endif
        .endif
    .endif

    inc j
    .if ( comptr )
        mov ebx,args
        sub ebx,32
        .if ebx <= id
            add ebx,32
        .endif
    .endif
    mov esi,[ebx].tokpos
    mov ecx,args
    lea ebx,[ecx+16]
    mov ecx,[ecx].asm_tok.tokpos
    sub ecx,esi
    rep movsb
    mov byte ptr [edi],0

    .if type
        mov eax,"0 ,"
        stosd
        dec edi
    .elseif comptr && vtable
        mov eax,' ,'
        stosw
        .if static_struct
            mov eax,'rdda'
            stosd
            mov eax,' '
            stosb
        .endif
        mov esi,comptr
        .while byte ptr [esi]
            lodsb
            .if ( al == '.' && vparray )
                mov vtable,0
                .break
            .endif
            stosb
        .endw
    .endif
    mov byte ptr [edi],0

    .if [ebx].token == T_CL_BRACKET

        inc j
        lea esi,b
        jmp done
    .endif

    mov eax,' ,'
    stosw

    .for ( brcount = 1 : [ebx].token != T_FINAL : )

        .if [ebx].hll_flags & T_HLL_PROC
            .return .if LKRenderHllProc(dst, j, tokenarray) == ERROR
        .endif
        mov al,[ebx].token
        .if al == T_CL_BRACKET
            dec brcount
            .break .ifz
        .elseif al == T_OP_BRACKET
            inc brcount
        .endif
        .if al == '&'
            lea esi,@CStr("addr ")
            mov ecx,5
        .elseif al == T_COMMA && \
                [ebx+16].token == T_CL_BRACKET && brcount == 1
            inc j
            add ebx,16
            .break
        .else
            mov esi,[ebx].tokpos
            mov ecx,[ebx+16].tokpos
            sub ecx,esi
        .endif
        rep movsb
        inc j
        add ebx,16
    .endf
    inc j
    mov byte ptr [edi],0

done:
    .if comptr && !vtable
        mov eax,' ,'
        stosw
        mov esi,comptr
        .while byte ptr [esi]
            movsb
        .endw
        mov byte ptr [edi],0
    .endif

    ; v2.21 -pe dllimport:<dll> external proto <no args> error
    ;
    ; externals need invoke for the [_]_imp_ prefix
    ;
    mov eax,i
    lea ecx,[eax+3]
    inc eax

    .if !comptr && ( ( j == eax && eax > 1 ) || j == ecx )

        xor eax,eax
        mov ecx,sym
        .if ecx

            .if ( [ecx].asym.state == SYM_EXTERNAL )

                .if ( [ecx].asym.dll )

                    mov eax,ecx

                .elseif ( [ecx].asym.flag2 & S_ISINLINE )

                    mov ecx,[ecx].asym.target_type
                    .if ( ecx && [ecx].asym.state == SYM_MACRO )

                        mov eax,ecx
                    .endif
                .endif
            .endif
        .endif

        .if !eax

            strcpy( esi, "call" )
            strcat( esi, &[esi+6] )
        .endif
    .endif

    mov eax,dst
    .if B[eax] != 0
        strcat(eax, &EOLSTR)
    .endif
    strcat(dst, &b)
    StripSource(i, j, tokenarray)
    ret

LKRenderHllProc endp

    assume ebx: NOTHING

RenderHllProc proc private uses esi edi dst:string_t, i:uint_t, tokenarray:ptr asm_tok

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

QueueTestLines proc uses esi edi src:string_t

    mov esi,src

    .while esi

        mov edi,esi
        .if strchr( esi, EOLCHAR )

            mov B[eax],0
            inc eax
        .endif
        mov esi,eax

        .if B[edi]
if 1
            xor edx,edx
            .if esi

                mov eax,[esi]
                mov ecx,[edi]
                ;
                ; jmp ...
                ; jmp ...
                ;
                .if eax == ' pmj' && eax == ecx

                    inc edx
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

ExpandHllProc proc uses esi edi dst:string_t, i:int_t, tokenarray:ptr asm_tok

  local rc:int_t

    mov rc,NOT_ERROR
    mov eax,dst
    mov B[eax],0

    .if ( ModuleInfo.strict_masm_compat == 0 )

        mov esi,i
        mov edi,esi
        shl edi,4
        add edi,tokenarray

        .while esi < ModuleInfo.token_count

            .if [edi].asm_tok.hll_flags & T_HLL_PROC

                ExpandCStrings( tokenarray )
                mov rc,RenderHllProc( dst, esi, tokenarray )
                ;.break
            .endif
            add edi,16
            add esi,1
        .endw
    .endif
    mov eax,rc
    ret

ExpandHllProc endp

ExpandHllProcEx proc uses esi edi buffer:string_t, i:int_t, tokenarray:ptr asm_tok

  local rc:int_t

    mov rc,ExpandHllProc(buffer, i, tokenarray)

    .repeat

        .break .if eax == ERROR

        mov esi,buffer
        .break .if byte ptr [esi] == 0

        strcat(esi, "\n")
        mov ebx,tokenarray
        strcat(esi, [ebx].asm_tok.tokpos)
        QueueTestLines(esi)
        mov rc,STRING_EXPANDED

    .until 1

    .if ModuleInfo.list

        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif

    .if ModuleInfo.line_queue.head

        RunLineQueue()
    .endif
    mov eax,rc
    ret

ExpandHllProcEx endp

EvaluateHllExpression proc uses esi edi ebx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
            ilabel:int_t, is_true:int_t, buffer:string_t

  local hllop:hll_opnd, b[MAX_LINE_LEN]:char_t

    mov esi,i
    mov ebx,tokenarray

    xor eax,eax
    mov hllop.lastjmp,eax
    mov hllop.lasttruelabel,eax

    mov edx,hll
    mov eax,[edx].hll_item.flags
    and eax,HLLF_EXPRESSION

    .if ( ModuleInfo.strict_masm_compat == 0 ) && !eax && [ebx].asm_tok.hll_flags & T_HLL_DELAY

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

                .return NOT_ERROR
            .endif
            add edi,1
        .endw
    .endif

    lea edi,b

    .if ExpandHllProc( edi, [esi], ebx ) != ERROR

        mov ecx,buffer
        mov B[ecx],0

        .if GetExpression( hll, esi, ebx, ilabel, is_true, ecx, &hllop ) != ERROR

            mov eax,[esi]
            shl eax,4
            add ebx,eax

            .return asmerr(2154) .if [ebx].asm_tok.token != T_FINAL

            mov eax,hll
            mov eax,[eax].hll_item.flags
            and eax,HLLF_IFD or HLLF_IFW or HLLF_IFB

            .if eax && B[edi]
                ;
                ; Parse a "cmp ax" or "test ax,ax" and resize
                ; to B/W/D ([r|e]ax).
                ;
                mov edx,buffer
                mov ecx,[edx]
                .while B[edx] > ' '

                    add edx,1
                .endw
                .while B[edx] == ' '

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
                        mov ax,[edx]
ifndef __ASMC64__
                        .if ModuleInfo.Ofssize == USE64
endif
                            mov B[edx],'e'
                            .if !ecx && ax == [ebx] ; v2.27 - .ifd foo() & imm --> test eax,emm

                                mov B[ebx],'e'
                            .endif

ifndef __ASMC64__
                        .elseif ModuleInfo.Ofssize == USE16

                            .if B[edx+2] != ' '

                                .if ecx

                                    mov D[edx-4],'ro '
                                .else
                                    mov D[edx-5],' dna'
                                .endif
                                dec edx
                            .endif
                            mov [edx+1],ax
                            mov B[edx],'e'
                            .if !ecx

                                mov B[ebx-1],'e'
                            .endif
                        .endif
endif
                        .endc

                      .case HLLF_IFW
ifndef __ASMC64__
                        .if ModuleInfo.Ofssize != USE16
endif
                            mov ax,[edx]
                            mov byte ptr [edx],' '
                            .if !ecx && ax == [ebx]

                                mov byte ptr [ebx],' '
                            .endif
ifndef __ASMC64__
                        .endif
endif
                        .endc

                      .case HLLF_IFB
                        mov ax,[edx]
ifndef __ASMC64__
                        .if ModuleInfo.Ofssize == USE16

                            mov byte ptr [edx+1],'l'
                            .if !ecx && ax == [ebx]

                                mov byte ptr [ebx+1],'l'
                            .endif
                        .else
endif
                            mov byte ptr [edx],' '
                            mov byte ptr [edx+2],'l'

                            .if !ecx && ax == [ebx]

                                mov byte ptr [ebx],' '
                                mov byte ptr [ebx+2],'l'
                            .endif
ifndef __ASMC64__
                        .endif
endif
                        .endc
                    .endsw
                .endif
            .endif

            .if B[edi]

                strlen( edi )
                mov W[edi+eax],EOLCHAR
                strcat( edi, buffer )
                strcpy( buffer, edi )
            .endif

            mov eax,NOT_ERROR
        .endif
    .endif
    ret

EvaluateHllExpression endp

ExpandHllExpression proc uses esi edi ebx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
        ilabel:int_t, is_true:int_t, buffer:string_t

  local rc:DWORD,
        oldstat:input_status,
        delayed:BYTE

    mov rc,NOT_ERROR
    mov esi,hll
    mov ebx,tokenarray
    mov edi,buffer
    mov delayed,0

    PushInputStatus(&oldstat)

    .if [esi].hll_item.flags & HLLF_WHILE

        mov edi,[esi].hll_item.condlines
        inc delayed
    .elseif [esi].hll_item.flags & HLLF_DELAYED
        inc delayed
    .else
        mov ecx,i
        mov edx,[ecx]
        shl edx,4
        .if [ebx+edx-16].asm_tok.token == T_DIRECTIVE && \
            [ebx+edx-16].asm_tok.tokval == T_DOT_ELSEIF
            inc delayed
        .endif
    .endif

    strcpy(ModuleInfo.currsource, edi)
    Tokenize(ModuleInfo.currsource, 0, ebx, TOK_DEFAULT)
    mov ModuleInfo.token_count,eax

    .if Parse_Pass == PASS_1

        .if ModuleInfo.line_queue.head
            RunLineQueue()
        .endif
        .if delayed
            mov NoLineStore,1
            ExpandLine( ModuleInfo.currsource, ebx )
            mov NoLineStore,0
            .return .if eax != NOT_ERROR
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

                    mov B[esi+4],'e'
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

RenderUntilXX proc private uses edi hll:ptr hll_item, cmd:uint_t

  local buffer[32]:char_t

    mov eax,cmd
    mov ecx,T_CX - T_AX
ifndef __ASMC64__
    .if ModuleInfo.Ofssize == USE16
        add ecx,T_AX
    .elseif ModuleInfo.Ofssize == USE32
        add ecx,T_EAX
    .else
        add ecx,T_RAX
    .endif
else
    add ecx,T_RAX
endif
    AddLineQueueX( " %r %r", T_DEC, ecx )
    mov edx,hll
    mov ecx,[edx].hll_item.labels[LSTART*4]
    AddLineQueueX( " jnz %s", GetLabelStr( ecx, &buffer ) )
    ret

RenderUntilXX endp

GetJumpString proc private uses edx ecx cmd

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

HllStartDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

local   rc:         int_t,
        cmd:        uint_t,
        buff[16]:   char_t,
        buffer[MAX_LINE_LEN]:char_t

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

        mov esi,LclAlloc(hll_item)
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
            .if B[edi] == NULLC
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

            .elseif cmd != T_DOT_WHILE

                GetLabelStr( [esi].labels[LSTART*4], &[edi+20] )
                strcpy( edi, GetJumpString( cmd ) )
                strcat( edi, " " )
                strcat( edi, &[edi+20] )
                InvertJump( edi )
                mov eax,NOT_ERROR
            .else
                ;
                ; just ".while" without expression is accepted
                ;
                mov B[edi],NULLC
                mov eax,ERROR
            .endif

            .if eax == NOT_ERROR

                strlen(edi)
                inc  eax
                push eax
                LclAlloc(eax)
                pop ecx
                mov [esi].condlines,eax
                memcpy( eax, edi, ecx )
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
    ret

HllStartDir endp

;
; .ENDIF, .ENDW, .UNTIL and .UNTILCXZ directives.
; These directives end a .IF, .WHILE or .REPEAT block.
;
HllEndDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local rc:int_t, cmd:int_t, buffer[MAX_LINE_LEN]:char_t

    mov esi,ModuleInfo.HllStack

    .return asmerr(1011) .if !esi

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

        .return asmerr(1011) .if ecx != HLL_IF
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

        .return asmerr(1011) .if ecx != HLL_WHILE
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
            ExpandHllExpression(esi, &i, tokenarray, LSTART, 1, edi)
        .else
            QueueTestLines([esi].condlines)
        .endif
        .endc

      .case T_DOT_UNTILCXZ

        .return asmerr(1010, [ebx+edx].string_ptr) .if ecx != HLL_REPEAT

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
            .if Options.masm_compat_gencode == 0 && ModuleInfo.strict_masm_compat == 0

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

                .if ( ModuleInfo.strict_masm_compat == 1 || \
                      ( Options.masm_compat_gencode == 1 && cmd == T_DOT_UNTILCXZ ) )

                    mov rc,CheckCXZLines(edi)
                .endif

                .if eax == NOT_ERROR
                    ;
                    ; write condition lines
                    ;
                    QueueTestLines( edi )
                    .if Options.masm_compat_gencode == 0 && ModuleInfo.strict_masm_compat == 0

                        RenderUntilXX( esi, cmd )
                    .endif
                .else
                    asmerr( 2062 )
                .endif
            .endif
        .else
            .if ( ModuleInfo.strict_masm_compat == 1 || Options.masm_compat_gencode == 1 )

                AddLineQueueX( "loop %s",
                    GetLabelStr( [esi].labels[LSTART*4], edi ) )
            .else

                RenderUntilXX( esi, cmd )
            .endif
        .endif
        .endc

      .case T_DOT_UNTILA .. T_DOT_UNTILSD
      .case T_DOT_UNTIL

        .return asmerr(1010, [ebx+edx].string_ptr) .if ecx != HLL_REPEAT

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
    ret

HllEndDir endp

HllContinueIf proc uses esi edi ebx hll:ptr hll_item, i:ptr int_t, tokenarray:ptr asm_tok,
    labelid:int_t, hll1:ptr hll_item, is_true:int_t

  local rc:int_t, buff[16]:char_t
  local buffer[256]:char_t

    lea edi,buffer
    mov rc,NOT_ERROR
    mov ecx,labelid
    mov esi,hll
    mov eax,i
    mov ebx,[eax]
    shl ebx,4
    add ebx,tokenarray

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
                inc D[eax]
                EvaluateHllExpression(esi, eax, tokenarray, labelid, is_true, edi)
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
                inc D[eax]
                GetLabelStr([esi].labels[ecx*4], &buff)
                strcpy(edi, GetJumpString( [ebx].tokval))
                strcat(edi, " ")
                strcat(edi, &buff)
                .if is_true
                    InvertJump(edi)
                .endif
                AddLineQueue(edi)
                .endc
            .endsw
        .endif

    .else

        AddLineQueueX("jmp %s", GetLabelStr([esi].labels[ecx*4], edi))

        mov edx,hll1
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

HllExitDir proc USES esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local rc:     int_t,
        cont0:  int_t,
        cmd:    int_t,
        buff    [16]:char_t,
        buffer  [MAX_LINE_LEN]:char_t,
        hll:    ptr hll_item

    mov esi,ModuleInfo.HllStack
    mov hll,esi

    .return asmerr(1011) .if (esi == 0)
    ExpandCStrings(tokenarray)

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

      .case T_DOT_ELSEIFSD
        or  [esi].flags,HLLF_IFD
      .case T_DOT_ELSEIFS
        or  [esi].flags,HLLF_IFS
      .case T_DOT_ELSEIF
        or  [esi].flags,HLLF_ELSEIF
      .case T_DOT_ELSE

        .return asmerr(1010, [ebx].string_ptr) .if ( [esi].cmd != HLL_IF )
        ;
        ; v2.08: check for multiple ELSE clauses
        ;
        .return asmerr(2142) .if ( [esi].flags & HLLF_ELSEOCCURED )

        push eax
        ;
        ; the exit label is only needed if an .ELSE branch exists.
        ; That's why it is created delayed.
        ;
        .if [esi].labels[LEXIT*4] == 0

            mov [esi].labels[LEXIT*4],GetHllLabel()
        .endif
        AddLineQueueX("jmp %s", GetLabelStr([esi].labels[LEXIT*4], edi))

        .if ( [esi].labels[LTEST*4] > 0 )

            AddLineQueueX("%s%s", GetLabelStr([esi].labels[LTEST*4], edi), LABELQUAL)
            mov [esi].labels[LTEST*4],0
        .endif

        inc i
        pop eax
        .if eax != T_DOT_ELSE
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
            or [esi].flags,HLLF_ELSEOCCURED
        .endif
        .endc

      .case T_DOT_ELSEIFD
        or  [esi].flags,HLLF_IFD
        .gotosw(T_DOT_ELSEIF)

      .case T_DOT_BREAK
      .case T_DOT_CONTINUE

        .if [ebx+16].token == T_OP_BRACKET && [ebx+16*3].token == T_CL_BRACKET

            .if cmd == T_DOT_CONTINUE

                mov eax,[ebx+32].string_ptr
                .if byte ptr [eax] == '0'

                    mov cont0,1
                .endif
            .endif

            mov ecx,atol([ebx+32].string_ptr)
            add i,3
            add ebx,16*3
            mov eax,cmd
        .endif

        .for ( : esi && ( [esi].cmd == HLL_IF || [esi].cmd == HLL_SWITCH ) : esi = [esi].next )

        .endf

        .while ( esi && ecx )
            .for ( esi = [esi].next : esi && ( [esi].cmd == HLL_IF || [esi].cmd == HLL_SWITCH ),
                 : esi = [esi].next )
            .endf
            dec ecx
        .endw

        .return asmerr(1011) .if ( esi == 0 )
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
        mov rc,HllContinueIf(esi, &i, tokenarray, ecx, hll, 1)
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

HllInit proc pass:int_t

    mov ModuleInfo.hll_label,0      ; init hll label counter
    ret

HllInit endp

    END
