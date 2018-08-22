;; https://docs.microsoft.com/nb-no/cpp/intrinsics/popcnt16-popcnt-popcnt64
include stdio.inc
include intrin.inc

.code

main proc

  local us[3]:WORD, usr:WORD
  local ui[4]:UINT, uir:UINT

    mov us[0],0
    mov us[2],0xFF
    mov us[4], 0xFFFF
    mov ui[0],0
    mov ui[4],0xFF
    mov ui[8],0xFFFF
    mov ui[12],0xFFFFFFFF

    .for (ebx=0: ebx<3: ebx++)
        mov usr,__popcnt16(us[rbx*2])
        printf("__popcnt16(0x%x) = %d\n", us[rbx*2], usr)
    .endf

    .for (ebx=0: ebx<4: ebx++)
        mov uir,__popcnt(ui[rbx*4])
        printf("__popcnt(0x%x) = %d\n", ui[rbx*4], uir)
    .endf

    ret

main endp

    end main
