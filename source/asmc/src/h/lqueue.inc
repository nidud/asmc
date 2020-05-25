.pragma list(push, 0)
ifndef __LQUEUE_INC
__LQUEUE_INC equ <>

;; v2.11: line queue functions moved from input.asm to lqueue.asm

DeleteLineQueue proto
AddLineQueue    proto :string_t
AddLineQueueX   proto :string_t, :vararg
RunLineQueue    proto
InsertLineQueue proto

is_linequeue_populated macro
    exitm<ModuleInfo.line_queue.head>
    endm

endif
.pragma list(pop)
