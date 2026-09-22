
; v2.39.12 -- @CStr() expansion in .rsrc segment

option dotname
.rsrc segment para flat public 'RSRC'
@CStr(L"@CStr() expansion\n")
.rsrc ends

 end

