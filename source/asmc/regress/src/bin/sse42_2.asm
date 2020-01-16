; SSE42_2.ASM--

    .x64
    .model flat
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
