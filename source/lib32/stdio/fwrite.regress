include io.inc
include stdio.inc
include stdlib.inc
include string.inc

    .data
    buf db 4096 dup(?)
    .code

main proc
    .assert fopen("test.fil","w")
    mov esi,eax
    lea edi,buf
    .assert fwrite("abcdefghijklmnopqr",2,9,esi) == 9
    .assert !fseek(esi,1,SEEK_SET)
    .assert fwrite("abcdefghijklmnopq",1,17,esi) == 17
    .assert !fclose(esi)
    .assert fopen("test.fil","rb") == esi
    .assert fread(edi,2,9,esi) == 9
    .assert !fclose(esi)
    .assert !remove("test.fil")
    .assert !strncmp(edi,"aabcdefghijklmnopq",18)
    ret
main endp

    end
