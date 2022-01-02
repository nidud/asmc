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
   .ends

GetOperator     proto __ccall :ptr asm_tok
GetOpType       proto __ccall :ptr asm_tok, :string_t
OperatorParam   proto __ccall :ptr asm_tok, :string_t
ProcessOperator proto __ccall :ptr asm_tok
EvalOperator    proto __ccall :ptr expr, :ptr expr, :ptr asm_tok
ParseOperator   proto __ccall :ptr asm_tok, :ptr opinfo
