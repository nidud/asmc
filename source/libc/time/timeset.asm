; TIMESET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

.data

PST char_t "PST",_TZ_STRINGS_SIZE-3 dup(0)
PDT char_t "PDT",_TZ_STRINGS_SIZE-3 dup(0)

_tzname string_t PST, PDT
_dstbias  int_t -3600     ; DST offset in seconds
_timezone int_t 8*3600    ; Pacific Time Zone
_daylight int_t 1         ; Daylight Saving Time (DST) in timezone

__dnames  char_t "SunMonTueWedThuFriSat",0
__mnames  char_t "JanFebMarAprMayJunJulAugSepOctNovDec",0

    end
