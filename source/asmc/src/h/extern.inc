.pragma list(push, 0)
ifndef __EXTERN_INC
__EXTERN_INC equ <>

;; prototypes of extern.asm

MakeExtern	proto :string_t, :uchar_t, :asym_t, :asym_t, :uchar_t
AddPublicData	proto fastcall :asym_t

FreePubQueue macro
    exitm<mov ModuleInfo.PubQueue.head,NULL>
    endm

endif
.pragma list(pop)
