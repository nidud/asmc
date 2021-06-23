; SEGMENT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __SEGMENT_INC
define __SEGMENT_INC

; segment related prototypes & externals

GetSegm proto fastcall :ptr asym {
    mov eax,[ecx].asym.segm
    }

SetSymSegOfs		proto :ptr asym
GetSymOfssize		proto :ptr asym

; Get current segment's offset

GetCurrOffset		proto
SetCurrOffset		proto :ptr dsym, :uint_t, :int_t, :int_t
CreateIntSegment	proto :string_t, :string_t, :uchar_t, :uchar_t, :int_t

; get symbol's segment index, from the symbol itself

GetSegIdx		proto :ptr asym
SegmentInit		proto :int_t		; init segments
SegmentFini		proto			; exit segments
GetGroup		proto :ptr asym
GetCurrSegAlign		proto
SetOfssize		proto
TypeFromClassName	proto :ptr dsym, :ptr asym
DefineFlatGroup		proto
SegmentModuleExit	proto
DeleteGroup		proto :ptr dsym

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


SimGetSegName		proto :int_t
GetCodeClass		proto
ModelSimSegmInit	proto :int_t
ModelSimSegmExit	proto
SetModelDefaultSegNames proto

endif
