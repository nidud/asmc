.pragma list(push, 0)
ifndef __SEGMENT_INC
__SEGMENT_INC equ <>

;; segment related prototypes & externals

GetSegm macro x
    exitm<x._segment>
    endm

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

SIM_CODE		equ 0
SIM_STACK		equ 1
SIM_DATA		equ 2
SIM_DATA_UN		equ 3 ;; .DATA?
SIM_FARDATA		equ 4
SIM_FARDATA_UN		equ 5 ;; .FARDATA?
SIM_CONST		equ 6
SIM_LAST		equ 7


SimGetSegName		proto :int_t
GetCodeClass		proto
ModelSimSegmInit	proto :int_t
ModelSimSegmExit	proto
SetModelDefaultSegNames proto

endif
.pragma list(pop)
