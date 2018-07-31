
    .code

    OPTION SWITCH:NOTEST

    .switch rcx
    enum = 0
    repeat  COUNT
%   .case @CatStr(%enum)
        mov eax,enum
        .endc
    enum = enum + 1
    endm
    .endsw
    ret

    end
