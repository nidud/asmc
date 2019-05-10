include string.inc

    .code

main proc

    .assertd _memicmp("abc", "aBc", 3) == 0
    .assertd _memicmp("bcd", "abc", 3) == 1
    .assertd _memicmp("abc", "abc ", 4) == -1
    .assertd _memicmp("abc", "abcd", 4) == -1

    xor eax,eax
    ret

main endp

    end
