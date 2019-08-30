.pragma list(push, 0)
ifndef __CONDASM_INC
__CONDASM_INC equ <>

;; prototypes for conditional assembly and errors

BLOCK_ACTIVE    equ 0 ;; current cond is true
BLOCK_INACTIVE  equ 1 ;; current IF cond is false, looking for elseif
BLOCK_DONE      equ 2 ;; done TRUE section of current if, just nuke
                      ;; everything until we see an endif

CC_NULL         equ 0
CC_NUMARG       equ 1
CC_LITARG       equ 2
CC_BLKARG       equ 3
CC_SYMARG       equ 4
CC_PASS1        equ 5
CC_PASS2        equ 6


externdef       CurrIfState:int_t

CondPrepare     proto :int_t
GetIfNestLevel  proto
SetIfNestLevel  proto :int_t
CondCheckOpen   proto
CondInit        proto

endif
.pragma list(pop)
