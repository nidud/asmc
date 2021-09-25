; OPERATOR.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

.template opinfo
    next    ptr opinfo ?
    op1     expr <>
    op2     expr <>
    type    int_t ?
    left    int_t ?
   .ends

GetOperator     proto :ptr asm_tok
GetOpType       proto :ptr asm_tok, :string_t
OperatorParam   proto :ptr asm_tok, :string_t
ProcessOperator proto :ptr asm_tok
EvalOperator    proto :ptr expr, :ptr expr, :ptr asm_tok
ParseOperator   proto :ptr asm_tok, :ptr opinfo
