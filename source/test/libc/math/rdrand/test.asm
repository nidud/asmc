
    .686
    .xmm
    .model flat, c

    option dllimport:<msvcrt>
    printf proto :ptr, :vararg
    exit   proto :dword

    .code

main proc

  local i

    .for i = 0 : i < 18: i++

        rdrand eax
        printf("%u\n", eax)
    .endf
    exit(0)

main endp

    end main
