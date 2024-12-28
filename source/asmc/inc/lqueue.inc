; LQUEUE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; v2.11: line queue functions moved from input.asm to lqueue.asm
;
ifndef __LQUEUE_INC
define __LQUEUE_INC

DeleteLineQueue proto __ccall
AddLineQueue    proto fastcall :string_t
AddLineQueueX   proto __ccall :string_t, :vararg
RunLineQueue    proto __ccall
InsertLineQueue proto __ccall
QueueTestLines  equ <AddLineQueue>

is_linequeue_populated macro
    exitm<MODULE.line_queue.head>
    endm

endif
