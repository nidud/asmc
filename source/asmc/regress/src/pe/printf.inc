; PRINTF.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

option dllimport:<msvcrt.dll>
printf proto c :ptr, :vararg
option dllimport:none

