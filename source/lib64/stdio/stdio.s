include io.inc
include stdio.inc
include stdlib.inc
include string.inc

    .code

main proc

  local buffer[4096]:byte

    lea rdi,buffer

    .assert sprintf(rdi,"hello%c",'!') == 6
    .assert !strcmp(rdi,"hello!")
    .assert sprintf(rdi,"%d",1) == 1
    .assert !strcmp(rdi,"1")
    .assert sprintf(rdi,"%02d",99) == 2
    .assert !strcmp(rdi,"99")
    .assert sprintf(rdi,"%03d",99) == 3
    .assert !strcmp(rdi,"099")
    .assert sprintf(rdi,"%x",1) == 1
    .assert !strcmp(rdi,"1")
    .assert sprintf(rdi,"%02x",255) == 2
    .assert !strcmp(rdi,"ff")
    .assert sprintf(rdi,"%02X",254) == 2
    .assert !strcmp(rdi,"FE")
    .assert sprintf(rdi,"%X",0xABCD) == 4
    .assert !strcmp(rdi,"ABCD")
    .assert sprintf(rdi,"%X",89ABCDEFh) == 8
    .assert !strcmp(rdi,"89ABCDEF")
    .assert sprintf(rdi,"%p",89ABCDEFh) == 16
    .assert !strcmp(rdi,"0000000089ABCDEF")
    mov rax,1123456789ABCDEFh
    .assert sprintf(rdi,"%016I64X",rax) == 16
    .assert !strcmp(rdi,"1123456789ABCDEF")
    .assert sprintf(rdi,"%b",1) == 1
    .assert !strcmp(rdi,"1")
    .assert sprintf(rdi,"%03b",3) == 3
    .assert !strcmp(rdi,"011")
    .assert sprintf(rdi,"%lb",8000h) == 16
    .assert !strcmp(rdi,"1000000000000000")
    mov eax,-1
    .assert sprintf(rdi,"%i",eax) == 2
    .assert !strcmp(rdi,"-1")
    .assert sprintf(rdi,"%u",0xFFFFFFFF) == 10
    .assert !strcmp(rdi,"4294967295")
    .assert atol("247") == 247
    .assert fopen("test.fil","w")
    mov rsi,rax
    .assert fprintf(rax,"%03u",3) == 3
    .assert !fclose(rsi)
    .assert fopen("test.fil","rt") == rsi
    .assert fread(rdi,3,1,rsi) == 1
    .assert !fclose(rsi)
    .assert !strncmp(rdi,"003",3)
    .assert !remove("test.fil")

    ret

main endp

    end
