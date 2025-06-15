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

GetOperator     proto __ccall :token_t
GetOpType       proto __ccall :token_t, :string_t
OperatorParam   proto __ccall :token_t, :string_t
ProcessOperator proto __ccall :token_t
EvalOperator    proto __ccall :ptr expr, :ptr expr, :token_t
ParseOperator   proto __ccall :token_t, :ptr opinfo
