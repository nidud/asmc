include io.inc
include direct.inc
include strlib.inc

externdef   envtemp:dword
removefile  proto :LPSTR

    .code

removetemp proc path:LPSTR

  local nbuf[_MAX_PATH]:byte

    removefile(strfcat(addr nbuf, envtemp, path))
    ret

removetemp endp

    END
