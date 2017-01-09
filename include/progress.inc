.xlist

externdef	progress_dobj:WORD
externdef	progress_size:QWORD

progress_open	PROTO :DWORD, :DWORD
progress_close	PROTO
progress_set	PROTO :DWORD, :DWORD, :QWORD
progress_update PROTO :QWORD
test_userabort	PROTO

.list
