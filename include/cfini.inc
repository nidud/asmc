ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_CFBASE		equ 0
_CFSECTION	equ 1
_CFENTRY	equ 2
_CFCOMMENT	equ 4

S_CFINI		STRUC
cf_flag		UINT ?
cf_name		LPSTR ? ; [<Section>]  | <Entry>
cf_info		PVOID ? ; first entry  | value
cf_next		PVOID ? ; next section | next entry
S_CFINI		ENDS

PCFINI		TYPEDEF PTR S_CFINI

CFRead		PROTO __file:LPSTR
CFWrite		PROTO __file:LPSTR
CFClose		PROTO
CFGetSection	PROTO :LPSTR
CFGetSectionID	PROTO :LPSTR, :UINT
CFAddSection	PROTO :LPSTR
CFAddSectionX	PROTO _CDecl :LPSTR, :VARARG
CFGetEntry	PROTO :PCFINI, :LPSTR
CFGetEntryID	PROTO :PCFINI, :UINT
CFDelEntries	PROTO :PCFINI
CFAddEntry	PROTO :PCFINI, :LPSTR
CFAddEntryX	PROTO _CDecl :PCFINI, :LPSTR, :VARARG
CFReadFileName	PROTO :PCFINI, :PVOID, :UINT
CFFindSection	PROTO :PCFINI, __section:LPSTR

CFExecute	PROTO :PCFINI
CFExpandMac	PROTO __buffer:LPSTR, __file:LPSTR
CFExpandCmd	PROTO __buffer:LPSTR, __file:LPSTR, __section:LPSTR
CFGetComspec	PROTO :UINT
CFError		PROTO :LPSTR, :LPSTR

;;;;;;;;;;;;;;; __

externdef	__CFBase:PCFINI

__CFRead	PROTO :PCFINI, __file:LPSTR
__CFWrite	PROTO :PCFINI, __file:LPSTR
__CFClose	PROTO :PCFINI
__CFAlloc	PROTO
__CFGetSection	PROTO :PCFINI, :LPSTR
__CFAddSection	PROTO :PCFINI, :LPSTR
__CFAddSectionX PROTO _CDecl :PCFINI, :LPSTR, :VARARG

__CFExpandCmd	PROTO :PCFINI, :LPSTR, :LPSTR
__CFGetComspec	PROTO :PCFINI, :UINT


.list
