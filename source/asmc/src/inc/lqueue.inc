; LQUEUE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; v2.11: line queue functions moved from input.asm to lqueue.asm
;
ifndef __LQUEUE_INC
define __LQUEUE_INC

DeleteLineQueue proto
AddLineQueue    proto :string_t
AddLineQueueX   proto __cdecl :string_t, :vararg
RunLineQueue    proto
InsertLineQueue proto

is_linequeue_populated macro
    exitm<ModuleInfo.line_queue.head>
    endm

endif
