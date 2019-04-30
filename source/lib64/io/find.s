include io.inc
include string.inc

    .code

main proc

  local ff:_finddata_t

    .assert _findfirst("makefile", &ff) != -1
    .assert !_findclose(rax)
    .assert !strcmp(&ff.name, "makefile")
    .assert _findfirst("?akefile", &ff) != -1
    .assert !_findclose(rax)
    .assert _findfirst("*.mak", &ff) != -1
    mov rbx,rax
    .assert _findnext(rbx, &ff) != -1
    .assert !_findclose(rbx)
    ret

main endp

    end
