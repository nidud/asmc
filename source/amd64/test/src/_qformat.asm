include intn.inc
include stdio.inc
include stdlib.inc
include string.inc

compval macro result, format, value
    local q
    .data
    q real16 value
    .code
    sprintf(rdi,format,q)
;    printf("%s\n%s\n", edi, result)
    exitm<.assert strcmp(rdi,result)==0>
    endm

.code

main proc

  local buf[4096]:byte
    lea rdi,buf

    compval( "123.123",    "%.3llf",    123.123 )
    compval( "123.123000", "%llf",      123.123 )
    compval( "2147483647", "%#.16llg",  2147483647.0 )
    compval( "-2147483648","%#.16llg",  -2147483648.0 )
    compval( "1000000000000000","%#.16llg",1.E15 )
    compval( "0.0000000000000000000000000000001","%.31llf",0.0000000000000000000000000000001 )
    compval( "1.0000000000000000000000000000001","%.31llf",1.0000000000000000000000000000001 )

    ret
main endp

    end
