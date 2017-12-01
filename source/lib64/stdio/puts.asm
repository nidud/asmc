include stdio.inc
include io.inc
include string.inc

    .code

puts proc string:LPSTR
    _write(stdout._file, string, strlen(rcx))
    ret
puts endp

    END
