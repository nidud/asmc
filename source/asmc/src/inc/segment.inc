.pragma list(push, 0)
ifndef __SEGMENT_INC
__SEGMENT_INC equ <>

;; segment related prototypes & externals

GetSegm proto fastcall :ptr asym {
    mov eax,[ecx].asym.segm
    }

SetSymSegOfs		proto :asym_t
GetSymOfssize		proto :asym_t

;; Get current segment's offset

GetCurrOffset		proto
SetCurrOffset		proto :dsym_t, :uint_t, :int_t, :int_t
CreateIntSegment	proto :string_t, :string_t, :uchar_t, :uchar_t, :int_t

;; get symbol's segment index, from the symbol itself

GetSegIdx		proto :asym_t
SegmentInit		proto :int_t		;; init segments
SegmentFini		proto			;; exit segments
GetGroup		proto :asym_t
GetCurrSegAlign		proto
SetOfssize		proto
TypeFromClassName	proto :dsym_t, :asym_t
DefineFlatGroup		proto
SegmentModuleExit	proto
DeleteGroup		proto :dsym_t

;; simplified segment functions

.enum sim_seg {
    SIM_CODE,
    SIM_STACK,
    SIM_DATA,
    SIM_DATA_UN,    ;; .DATA?
    SIM_FARDATA,
    SIM_FARDATA_UN, ;; .FARDATA?
    SIM_CONST,
    SIM_LAST
    }


SimGetSegName		proto :int_t
GetCodeClass		proto
ModelSimSegmInit	proto :int_t
ModelSimSegmExit	proto
SetModelDefaultSegNames proto

endif
.pragma list(pop)
