;
; v2.29.02 - 3 byte type as argument
;
    .386
    .model flat, c

    MS3 struct
    _0  db ?
    _1  db ?
    _2  db ?
    MS3 ends

    .data
    ms2 MS3 <>

    .code

foo proc x:MS3
    ret
foo endp

bar proc

  local ms:MS3

    invoke foo, ms
    invoke foo, ms2
    ret

bar endp

    end
