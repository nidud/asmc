;
; v2.29.02 - 3 byte type as argument
;

    MS3 struct
    _0  db ?
    _1  db ?
    _2  db ?
    MS3 ends

    foo proto :MS3

    .data
    ms2 MS3 <>

    .code

bar proc

  local ms:MS3

    invoke foo, ms
    invoke foo, ms2
    ret

bar endp

    end
