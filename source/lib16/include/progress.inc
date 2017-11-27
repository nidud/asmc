.xlist

externdef progress_dobj:WORD
externdef progress_size:DWORD

progress_open	PROTO _CType :DWORD, :DWORD
progress_close	PROTO _CType
progress_set	PROTO _CType :DWORD, :DWORD, :DWORD
progress_update PROTO _CType :DWORD

.list
