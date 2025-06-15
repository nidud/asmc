; EXTERN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; prototypes of extern.asm
;
ifndef __EXTERN_INC
define __EXTERN_INC

MakeExtern      proto __ccall :string_t, :uchar_t, :asym_t, :asym_t, :uchar_t
AddPublicData   proto fastcall :asym_t

FreePubQueue macro
    exitm<mov MODULE.PubQueue.head,NULL>
    endm

endif

