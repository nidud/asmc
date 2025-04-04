; CONDASM.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; prototypes for conditional assembly and errors
;
.pragma list(push, 0)
ifndef __CONDASM_INC
define __CONDASM_INC

.enum if_state {
    BLOCK_ACTIVE,    ; current cond is true
    BLOCK_INACTIVE,  ; current IF cond is false, looking for elseif
    BLOCK_DONE       ; done TRUE section of current if, just nuke
    }                ; everything until we see an endif

.enum cond_class {
    CC_NULL,
    CC_NUMARG,
    CC_LITARG,
    CC_BLKARG,
    CC_SYMARG,
    CC_PASS1,
    CC_PASS2,
    }

externdef CurrIfState:if_state

CondPrepare     proto __ccall :int_t
GetIfNestLevel  proto __ccall
SetIfNestLevel  proto __ccall :int_t
CondCheckOpen   proto __ccall
CondInit        proto __ccall

endif
.pragma list(pop)

