; NOARG.ASM-- stub out CRT's processing of command line arguments
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Asmc will include this file if option -MT is used
; and no main params used
;

include libc.inc

public _argvcrt
public _environcrt
public _wargvcrt
public _wenvironcrt

.data
 _argvcrt       label string_t
 _environcrt    label string_t
 _wargvcrt      label string_t
 _wenvironcrt   wstring_t NULL

 end
