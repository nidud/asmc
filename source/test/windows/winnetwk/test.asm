
include stdio.inc
include windows.inc

.code

main proc

  local NetProviderName[256]:sbyte
  local BufferSize:dword

    mov BufferSize,256
    .switch WNetGetProviderName(WNNC_NET_LANMAN, &NetProviderName, &BufferSize)
      .case NO_ERROR
        printf("NetProviderName: %s\n", &NetProviderName)
        .endc
      .case ERROR_MORE_DATA
        printf("The buffer is too small to hold the network provider name.\n")
        .endc
      .case ERROR_NO_NETWORK
        printf("The network is unavailable.\n")
        .endc
      .case ERROR_INVALID_ADDRESS
        printf("The lpProviderName parameter or the lpBufferSize parameter is invalid.\n")
        .endc
    .endsw
    ret

main endp

    end main
