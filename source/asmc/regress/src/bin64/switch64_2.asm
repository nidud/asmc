ifndef __ASMC64__
    .x64
    .model flat, fastcall
    option switch:REGAX
endif

    .code

foo proc

    .switch r8d
    .case 1
    .case 2
    .case 3
    .case 4
    .case 5
    .case 6
        .endc
    .case 18
    .case 11
    .case 17
    .case 22
    .case 10
    .case 16
    .case 21
    .case 9
    .case 15
    .case 20
        nop
       .endc
    .case 7
    .case 8
    .case 12
    .case 13
    .case 14
    .case 19
    .case 24
    .case 25
    .case 26
    .case 27
    .case 28
    .endsw
    ret

foo endp

    end

