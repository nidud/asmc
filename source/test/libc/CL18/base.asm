
    .code
    ;
    ;--- define __ImageBase at the DOS "MZ" header
    ;
public __ImageBase

    org -0x1000
    __ImageBase label byte

    end
