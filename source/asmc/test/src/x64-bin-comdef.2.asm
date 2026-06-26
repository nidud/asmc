;
; v2.36.16 - link to nearest public class
;
   .code

    option win64:3

.comdef IUnknown

    QueryInterface  proc
    AddRef          proc
    Release         proc
   .ends

.comdef I2 : public IUnknown
    p2 proc
   .ends

.comdef I3 : public I2
    p3 proc
   .ends

   .code

malloc proc z:dword
    ret
    endp

IUnknown::QueryInterface proc
    ret
    endp
IUnknown::AddRef proc
    ret
    endp
IUnknown::Release proc
    ret
    endp


I2::AddRef proc
    ret
    endp
I2::p2 proc
    ret
    endp

I3::Release proc
    ret
    endp
I3::p3 proc
    ret
    endp

foo proc

    @ComAlloc(IUnknown)

    ; IUnknown::QueryInterface
    ; IUnknown::AddRef
    ; IUnknown::Release

    @ComAlloc(I2)

    ; IUnknown::QueryInterface
    ; I2::AddRef
    ; IUnknown::Release
    ; I2::p2

    @ComAlloc(I3)

    ; IUnknown::QueryInterface
    ; I2::AddRef
    ; I3::Release
    ; I2::p2
    ; I3::p3

    ret
    endp

    end

