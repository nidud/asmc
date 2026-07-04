; EXTERN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; prototypes of extern.asm
;
ifndef _EXTERN_
define _EXTERN_

MakeExtern      proto __ccall :string_t, :uchar_t, :asym_t, :asym_t, :uchar_t
AddPublicData   proto fastcall :asym_t
PublicDirective proto __ccall :int_t, :token_t
CreateExternalFromType proto __ccall :string_t, :asym_t

FreePubQueue macro
    exitm<mov MODULE.PubQueue.head,NULL>
    endm

endif

