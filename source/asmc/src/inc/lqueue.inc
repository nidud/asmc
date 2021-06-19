.pragma list(push, 0)
ifndef __LQUEUE_INC
__LQUEUE_INC equ <>

;; v2.11: line queue functions moved from input.asm to lqueue.asm

DeleteLineQueue proto
AddLineQueue    proto :string_t
AddLineQueueX   proto __cdecl :string_t, :vararg
RunLineQueue    proto
InsertLineQueue proto
LSPrintF        proto __cdecl :string_t, :string_t, :vararg
VLSPrintF       proto :string_t, :string_t, :ptr

is_linequeue_populated macro
    exitm<ModuleInfo.line_queue.head>
    endm

endif
.pragma list(pop)
