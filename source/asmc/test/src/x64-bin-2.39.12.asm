
; v2.39.12 -- @CStr() expansion in .rsrc segment

option dotname
.rsrc segment dword read flat public 'RSRC'
@CStr(L"@CStr() expansion\n")
.rsrc ends

 end

