; ERRMSG.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Assembler message output interface.
; This file is included by asmc.inc.
;
ifndef __ERRMSG_INC
define __ERRMSG_INC

define errout <stdout>

define NOTE_INCLUDED_BY 0
define NOTE_MACRO_CALLED_FROM 1
define NOTE_ITERATION_MACRO_CALLED_FROM 2
define NOTE_MAIN_LINE_CODE 3

PrintNote proto __cdecl :int_t, :vararg
ErrnoStr proto
WriteError proto

endif
