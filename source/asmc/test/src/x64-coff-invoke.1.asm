;
; v2.29.02 - 3 byte type as argument
; v2.34.65 - 5, 6, and 7 byte types
;

    option win64:auto

    MS3 struct
    _3  db 3 dup(?)
    MS3 ends
    MS5 struct
    _5  db 5 dup(?)
    MS5 ends
    MS6 struct
    _6  db 6 dup(?)
    MS6 ends
    MS7 struct
    _7  db 7 dup(?)
    MS7 ends

    .code

foo proc a3:MS3, a5:MS5, a6:MS6, a7:MS7
    ret
foo endp

bar proc

  local s3:MS3, s5:MS5, s6:MS6, s7:MS7

    invoke foo, s3, s5, s6, s7
    ret

bar endp

    end
