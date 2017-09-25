include ini.inc

.xlist

CFRead		PROTO __file:LPSTR
CFWrite		PROTO __file:LPSTR
CFClose		PROTO
CFGetSection	PROTO :LPSTR
CFGetSectionID	PROTO :LPSTR, :UINT
CFAddSection	PROTO :LPSTR
CFAddSectionX	PROTO _CDecl :LPSTR, :VARARG
CFReadFileName	PROTO :LPINI, :PVOID, :UINT
CFFindSection	PROTO :LPINI, __section:LPSTR, __entry:LPSTR

CFExecute	PROTO :LPINI
CFExpandMac	PROTO __buffer:LPSTR, __file:LPSTR
CFExpandCmd	PROTO __buffer:LPSTR, __file:LPSTR, __section:LPSTR
CFGetComspec	PROTO :UINT
CFError		PROTO :LPSTR, :LPSTR

;;;;;;;;;;;;;;; __

externdef	__CFBase:LPINI

__CFExpandCmd	PROTO :LPINI, :LPSTR, :LPSTR
__CFGetComspec	PROTO :LPINI, :UINT


.list
