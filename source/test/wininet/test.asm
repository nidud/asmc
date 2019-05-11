include windows.inc
include wininet.inc
include stdio.inc
include tchar.inc

    .code

main proc

  local wsaData:WSADATA
  local hINet:HINTERNET
  local hFile:HANDLE
  local dwNumberOfBytesRead:uint_t
  local fp:LPFILE
  local buffer[1024]:char_t

    .repeat

        .ifd WSAStartup(2, &wsaData)

            printf("WSAStartup failed with error: %d\n", eax)
            mov eax,1
            .break
        .endif

        printf("The Winsock dll was found okay\nDownloading file...\n");

        .if !InternetOpen("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)

            perror("InternetOpen()")
            mov eax,1
            .break
        .endif
        mov hINet,rax

        .if InternetOpenUrl(hINet, "https://github.com/nidud/asmc/raw/master/bin/asmc.exe", NULL, 0, 0, 0)

            mov hFile,rax
            .if fopen("Asmc.exe", "wb")

                mov fp,rax
                .while 1

                    InternetReadFile(hFile, &buffer, 1024, &dwNumberOfBytesRead)
                    .break .if !dwNumberOfBytesRead
                    fwrite(&buffer, dwNumberOfBytesRead, 1, fp)
                .endw
                fclose(fp)
            .else
                perror("Asmc.exe")
            .endif
        .endif
        InternetCloseHandle(hINet)
        WSACleanup()
        xor eax,eax
    .until 1
    ret

main endp

    end _tstart
