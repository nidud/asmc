; SEGMENT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __SEGMENT_INC
define __SEGMENT_INC

; segment related prototypes & externals

GetSegm proto fastcall :ptr asym {
    mov rax,[rcx].asym.segm
    }

SetSymSegOfs		proto __ccall :ptr asym
GetSymOfssize		proto __ccall :ptr asym

; Get current segment's offset

GetCurrOffset		proto __ccall
SetCurrOffset		proto __ccall :ptr dsym, :uint_t, :int_t, :int_t
CreateIntSegment	proto __ccall :string_t, :string_t, :uchar_t, :uchar_t, :int_t

; get symbol's segment index, from the symbol itself

GetSegIdx		proto __ccall :ptr asym
SegmentInit		proto __ccall :int_t		; init segments
SegmentFini		proto __ccall			; exit segments
GetGroup		proto __ccall :ptr asym
GetCurrSegAlign		proto __ccall
SetOfssize		proto __ccall
TypeFromClassName	proto __ccall :ptr dsym, :ptr asym
DefineFlatGroup		proto __ccall
SegmentModuleExit	proto __ccall
DeleteGroup		proto __ccall :ptr dsym

; simplified segment functions

.enum sim_seg {
    SIM_CODE,
    SIM_STACK,
    SIM_DATA,
    SIM_DATA_UN,    ; .DATA?
    SIM_FARDATA,
    SIM_FARDATA_UN, ; .FARDATA?
    SIM_CONST,
    SIM_LAST
    }


SimGetSegName		proto __ccall :int_t
GetCodeClass		proto __ccall
ModelSimSegmInit	proto __ccall :int_t
ModelSimSegmExit	proto __ccall
SetModelDefaultSegNames proto __ccall

endif
