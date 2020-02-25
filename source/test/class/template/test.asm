
include stdio.inc
include tchar.inc
include CPU.inc

    .code

main proc

  .new cpu:CPU()

    printf("Vendor: %s\n", cpu.GetVendor())
    printf("Brand:  %s\n", cpu.GetBrand())
    ret

main endp

    end _tstart
