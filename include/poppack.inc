; POPPACK.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; This file turns packing of structures off. (That is, it enables
; automatic alignment of structure fields.)
;
; poppack.inc is the complement to pshpack?.inc. An inclusion of poppack.inc
; MUST ALWAYS be preceded by an inclusion of one of pshpack?.inc, in one-to-one
; correspondence.
;
; For Asmc, this file uses the pop option to the pack pragma so that it can
; restore the previous saved by the pshpack?.inc include file.
;
.pragma pack(pop)

