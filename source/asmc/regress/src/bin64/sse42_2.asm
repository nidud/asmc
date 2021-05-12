; SSE42_2.ASM--

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    adox    rax,rcx
    rdseed  rax
    rdrand  rax
    rdrand  rcx
    lzcnt   ecx,eax
    tzcnt   edx,eax
    invpcid rax,[rbx]
    rdpid   rax

    end
