; OMF.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; interface to OMF format output functions
;
ifndef __OMF_INC
define __OMF_INC

; max size of LEDATA data is 1024 - (1+2+1/2+2/4+1) = 1014

MAX_LEDATA_THRESHOLD equ (1024 - 10)

omf_init            proto
omf_set_filepos     proto
omf_OutSelect       proto fastcall :int_t
omf_FlushCurrSeg    proto
omf_check_flush     proto fastcall :ptr line_num_info

endif

