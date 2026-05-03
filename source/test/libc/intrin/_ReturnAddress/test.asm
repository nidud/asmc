;; https://msdn.microsoft.com/en-us/library/s975zw7k.aspx
;; compiler_intrinsics_AddressOfReturnAddress.cpp
;; processor: x86, x64
include stdio.inc
include intrin.inc
include tchar.inc

.code

;; This function will print three values:
;;   (1) The address retrieved from _AddressOfReturnAdress
;;   (2) The return address stored at the location returned in (1)
;;   (3) The return address retrieved the _ReturnAddress* intrinsic
;; Note that (2) and (3) should be the same address.
;;__declspec(noinline)

func proc

  local pvAddressOfReturnAddress:PVOID

    mov pvAddressOfReturnAddress,_AddressOfReturnAddress()
    mov rbx,[rax]
    printf("%p\n", pvAddressOfReturnAddress)
    printf("%p\n", rbx)
    printf("%p\n", _ReturnAddress())
    ret

func endp

main proc

    func()
    xor eax,eax
    ret

main endp

    end _tstart
