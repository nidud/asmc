include time.inc

    .code

main proc

  local ltime

    mov ltime,55C9D859h
    gmtime(addr ltime)
    mov edx,eax
    mov eax,1

    assume edx:ptr tm

    .assert [edx].tm_sec   == 21
    .assert [edx].tm_min   == 11
    .assert [edx].tm_hour  == 11
    .assert [edx].tm_mday  == 11
    .assert [edx].tm_mon   == 7
    .assert [edx].tm_year  == 115
    .assert [edx].tm_wday  == 2
    .assert [edx].tm_yday  == 222
    .assert [edx].tm_isdst == 0
    xor eax,eax
    ret

main endp

    END
