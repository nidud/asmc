include string.inc

    .code

main proc

  local buf[4096]:byte
    lea rdi,buf

    .assert strlen("1") == 1
    .assert strcpy(rdi,"abc") == rdi
    .assert strlen(rdi) == 3
    .assert strcmp(rdi,"abc") == 0
    .assert strcmp(rdi,"abc ") == -1
    .assert _stricmp(rdi,"aBc") == 0
    .assert _stricmp(rdi,"abc ") == -1
    .assert strcmp(rdi,"abcd") == -1
    .assert strcmp(rdi,"ab") == 1
    .assert memcmp(rdi,rdi,3) == 0
    .assert memcmp(rdi,"abd",3) == 1
    .assert memcmp(rdi,"abcd",3) == 0
    .assert strncmp(rdi,"abc",3) == 0
    .assert _strnicmp(rdi,"AbC",3) == 0
    .assert strncmp(rdi,"abc ",4) == -1
    .assert _strnicmp(rdi,"abc ",4) == -1
    .assert strcat(rdi,"\\abc") == rdi
    .assert strcpy(rdi,"%doszip%, C:/doszip, strstr") == rdi
    lea rsi,[rdi+21]
    .assert strstr(rdi,"strstr") == rsi
    sub rsi,2
    .assert strrchr(rdi,',') == rsi
    lea rsi,[rdi+8]
    .assert strchr(rdi,',') == rsi
    lea rsi,[rdi+511]
    .assert memset(rdi,'!',512) == rdi
    .assert memcmp(rsi,"!",1) == 0
    .assert memset(rdi,0,512) == rdi
    .assert memcmp(rsi,rdi,1) == 0
    .assert strcpy(rdi,"String") == rdi
    .assert _strrev(rdi) == rdi
    .assert strstr(rdi,"String") == 0
    .assert _strrev(rdi) == rdi
    .assert strstr(rdi,"String") == rdi

    xor rax,rax
    ret

main endp

    end
