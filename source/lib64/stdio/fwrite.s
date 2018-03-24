include io.inc
include stdio.inc
include string.inc

    .code

main proc

  local buf[4096]:sbyte

    lea rdi,buf
    .assert fopen("test.fil","w")
    mov rsi,rax
    .assert fwrite("abcdefghijklmnopqr",2,9,rsi) == 9
    .assert !fseek(rsi,1,SEEK_SET)
    .assert fwrite("abcdefghijklmnopq",1,17,rsi) == 17
    .assert !fclose(rsi)
    .assert fopen("test.fil","rb") == rsi
    .assert fread(&buf,2,9,rsi) == 9
    .assert !fclose(rsi)
    .assert !remove("test.fil")
    .assert !strncmp(&buf,"aabcdefghijklmnopq",18)
    ret

main endp

    end
