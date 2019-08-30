.pragma list(push, 0)
ifndef __ERRMSG_INC
__ERRMSG_INC equ <>

;; Assembler message output interface.
;; This file is included by asmc.inc.

errout equ <stdout>

NOTE_INCLUDED_BY equ 0
NOTE_MACRO_CALLED_FROM equ 1
NOTE_ITERATION_MACRO_CALLED_FROM equ 2
NOTE_MAIN_LINE_CODE equ 3

PrintNote proto :int_t, :vararg
ErrnoStr proto
WriteError proto

endif
.pragma list(pop)
