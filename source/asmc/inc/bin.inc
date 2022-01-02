; BIN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; header for BIN output format
;
ifndef __BIN_INC
define __BIN_INC

bin_init            proto __ccall :ptr module_info
pe_create_PE_header proto __ccall

endif
