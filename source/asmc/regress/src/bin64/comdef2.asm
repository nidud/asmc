;
; v2.36.16 - link to nearest public class
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
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
malloc endp

IUnknown::QueryInterface proc
    ret
IUnknown::QueryInterface endp

IUnknown::AddRef proc
    ret
IUnknown::AddRef endp

IUnknown::Release proc
    ret
IUnknown::Release endp


I2::AddRef proc
    ret
I2::AddRef endp

I2::p2 proc
    ret
I2::p2 endp

I3::Release proc
    ret
I3::Release endp

I3::p3 proc
    ret
I3::p3 endp

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

foo endp

    end

