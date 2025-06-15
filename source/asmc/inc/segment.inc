; SEGMENT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __SEGMENT_INC
define __SEGMENT_INC

; segment related prototypes & externals

GetSegm proto fastcall :asym_t {
    mov rax,[rcx].asym.segm
    }

SetSymSegOfs		proto fastcall :asym_t
GetSymOfssize		proto fastcall :asym_t

; Get current segment's offset

GetCurrOffset		proto
SetCurrOffset		proto __ccall :asym_t, :uint_t, :int_t, :int_t
CreateIntSegment	proto __ccall :string_t, :string_t, :uchar_t, :uchar_t, :int_t

; get symbol's segment index, from the symbol itself

GetSegIdx		proto fastcall :asym_t
SegmentInit		proto fastcall :int_t	; init segments
SegmentFini		proto			; exit segments
GetGroup		proto fastcall :asym_t
GetCurrSegAlign		proto
SetOfssize		proto
TypeFromClassName	proto fastcall :asym_t, :asym_t
DefineFlatGroup		proto
SegmentModuleExit	proto
DeleteGroup		proto __ccall :asym_t

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


SimGetSegName		proto fastcall :int_t
GetCodeClass		proto __ccall
ModelSimSegmInit	proto __ccall :int_t
ModelSimSegmExit	proto __ccall
SetModelDefaultSegNames proto __ccall

endif
