; EXTERN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; prototypes of extern.asm
;
ifndef __EXTERN_INC
define __EXTERN_INC

MakeExtern proto :string_t, :uchar_t, :ptr asym, :ptr asym, :uchar_t
AddPublicData proto fastcall :ptr asym

FreePubQueue macro
    exitm<mov ModuleInfo.PubQueue.head,NULL>
    endm

endif

