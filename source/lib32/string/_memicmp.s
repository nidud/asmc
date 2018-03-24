include string.inc

    .code

main proc

    .assert _memicmp("abc", "aBc", 3) == 0
    .assert _memicmp("bcd", "abc", 3) == 1
    .assert _memicmp("abc", "abc ", 4) == -1
    .assert _memicmp("abc", "abcd", 4) == -1

    xor eax,eax
    ret

main endp

    end
