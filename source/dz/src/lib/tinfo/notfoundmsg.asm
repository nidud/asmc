include string.inc
include consx.inc

    .data

externdef       searchstring:byte
cp_search       db 'Search',0
cp_notfoundmsg  db "Search string not found: '%s'",0

    .code

notfoundmsg proc
    mov cp_notfoundmsg[24],' '
    .if strlen(&searchstring) > 28
        mov cp_notfoundmsg[24],10
    .endif
    stdmsg(&cp_search, &cp_notfoundmsg, &searchstring)
    xor eax,eax
    ret
notfoundmsg endp

    END
