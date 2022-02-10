; PSHPACK16.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; This file turns 16 byte packing of structures on.  (That is, it disables
; automatic alignment of structure fields.) For Asmc, this files uses the
; push option to the pack pragma so that the poppack.inc include file can
; restore the previous packing reliably.
;
; The file poppack.inc is the complement to this file.
;
.pragma pack(push, 16)
