include io.inc
include stdio.inc
include stdlib.inc
include string.inc
include tchar.inc

option wstring:on

    .data
    buf dw 4096 dup(?)
    .code

_tmain proc

    lea edi,buf
test_f  macro z,r,s,v:VARARG
    .assert swprintf(edi,s,v) == z
    .assert !wcscmp(edi,r)
    endm
    test_f 6,"hello!","hello%c",'!'
    test_f 1,"1","%d",1
    test_f 2,"99","%02d",99
    test_f 3,"099","%03d",99
    test_f 1,"1","%x",1
    test_f 2,"ff","%02x",255
    test_f 2,"FE","%02X",254
    test_f 4,"ABCD","%X",0ABCDh
    test_f 8,"89ABCDEF","%X",89ABCDEFh
    test_f 8,"89ABCDEF","%p",89ABCDEFh
    test_f 16,"1123456789ABCDEF","%016I64X",89ABCDEFh,11234567h
    test_f 1,"1","%b",1
    test_f 3,"011","%03b",3
    test_f 16,"1000000000000000","%lb",8000h
    test_f 2,"-1","%i",0FFFFFFFFh
    test_f 10,"4294967295","%u",0FFFFFFFFh

    .assert _wtol("247") == 247
    .assert _wfopen("test.fil","w")
    mov esi,eax
    .assert fwprintf(eax,"%03u",3) == 3
    .assert !fclose(esi)
    .assert _wfopen("test.fil","rt") == esi
    .assert fread(addr buf,3,2,esi) == 2
    .assert !fclose(esi)
    .assert !wcsncmp(addr buf,"003",3)
    .assert !_wremove("test.fil")
    ret
_tmain endp

    end
