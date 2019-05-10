include ctype.inc

    .code

main proc

    .assert isspace(' ') == _SPACE
    .assert isspace(9)	 == _SPACE
    .assert isspace(10)	 == _SPACE
    .assert isspace(13)	 == _SPACE
    .assert isspace('a') == 0
    .assert isspace(100) == 0
    .assert isupper('A') == _UPPER
    .assert isupper('0') == 0
    .assert isupper('a') == 0
    .assert islower('A') == 0
    .assert islower('0') == 0
    .assert islower('a') == _LOWER
    .assert isalpha('A') == _UPPER
    .assert isalpha('z') == _LOWER
    .assert isalpha('0') == 0
    .assert isascii('9') == 1
    .assert isascii('_') == 1
    .assert isascii(128) == 0
    .assert iscntrl(0)	 == _CONTROL
    .assert iscntrl(1Fh) == _CONTROL
    .assert iscntrl(20h) == 0
    .assert isdigit('0') == _DIGIT
    .assert isdigit('9') == _DIGIT
    .assert isdigit(2)	 == 0
    .assert isprint(20h) == 20h
    .assert isprint(7Eh) == 7Eh
    .assert isprint(10h) == 0
    .assert isgraph(20h) == 0
    .assert isgraph(7Eh) == 7Eh
    .assert isgraph(10h) == 0
    .assert ispunct('!') == _PUNCT
    .assert ispunct('/') == _PUNCT
    .assert ispunct(7Eh) == _PUNCT
    .assert ispunct(' ') == 0
    .assert isxdigit('0') == _HEX
    .assert isxdigit('9') == _HEX
    .assert isxdigit('A') == _HEX
    .assert isxdigit('f') == _HEX
    .assert isxdigit('h') == 0
    .assert isxdigit(' ') == 0
    .assert toupper('A') == 'A'
    .assert toupper('a') == 'A'
    .assert toupper('z') == 'Z'
    .assert toupper('9') == '9'
    .assert tolower('a') == 'a'
    .assert tolower('A') == 'a'
    .assert tolower('Z') == 'z'
    .assert tolower('9') == '9'
    .assert _tolower('A') == 'a'
    .assert _tolower('Z') == 'z'
    .assert towupper('A') == 'A'
    .assert towupper('a') == 'A'
    .assert towupper('z') == 'Z'
    .assert towupper('9') == '9'
    .assert towlower('a') == 'a'
    .assert towlower('A') == 'a'
    .assert towlower('Z') == 'z'
    .assert towlower('9') == '9'

    xor rax,rax
    ret

main endp

    end
