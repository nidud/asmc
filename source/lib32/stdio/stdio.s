include io.inc
include stdio.inc
include stdlib.inc
include string.inc

    .data
    buf db 4096 dup(?)
    .code

main proc
    lea edi,buf
test_f macro z,r,s,v:VARARG
    .assert sprintf(edi,s,v) == z
    .assert !strcmp(edi,r)
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
    test_f 16,"1123456789ABCDEF","%016llX",89ABCDEFh,11234567h
    test_f 16,"1123456789ABCDEF","%016LX",89ABCDEFh,11234567h
    test_f 1,"1","%b",1
    test_f 3,"011","%03b",3
    test_f 16,"1000000000000000","%lb",8000h
    test_f 2,"-1","%i",0FFFFFFFFh
    test_f 10,"4294967295","%u",0FFFFFFFFh
    .assert atol("247") == 247
    .assert fopen("test.fil","w")
    mov esi,eax
    .assert fprintf(eax,"%03u",3) == 3
    .assert !fclose(esi)
    .assert fopen("test.fil","rt") == esi
    .assert fread(addr buf,3,1,esi) == 1
    .assert !fclose(esi)
    .assert !strncmp(addr buf,"003",3)
    .assert !remove("test.fil")
    ret
main endp

    end
