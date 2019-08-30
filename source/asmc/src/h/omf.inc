.pragma list(push, 0)
ifndef __OMF_INC
__OMF_INC equ <>

;; interface to OMF format output functions

;; max size of LEDATA data is 1024 - (1+2+1/2+2/4+1) = 1014

MAX_LEDATA_THRESHOLD equ (1024 - 10)

omf_init            proto :ptr module_info
omf_set_filepos     proto
omf_OutSelect       proto :int_t
omf_FlushCurrSeg    proto
omf_check_flush     proto :ptr line_num_info

endif
.pragma list(pop)
