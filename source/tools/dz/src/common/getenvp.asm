include string.inc
include malloc.inc
include winbase.inc

    .code

getenvp proc uses ecx edx enval:LPSTR

  local buf[2048]:byte

    .if GetEnvironmentVariable(enval, &buf, 2048)

	_strdup(&buf)
    .endif
    ret

getenvp endp

    END
