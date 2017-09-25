ifndef __INI_INC
ifndef __LIBC_INC
 include libc.inc
endif
.xlist
__INI_INC equ <>

INI_BASE	equ 0
INI_SECTION	equ 1
INI_ENTRY	equ 2
INI_COMMENT	equ 4

S_INI		STRUC
flags		UINT ?
entry		LPSTR ? ; [<Section>]  | <Entry>
value		PVOID ? ; first entry  | value
next		PVOID ? ; next section | next entry
S_INI		ENDS
LPINI		typedef ptr S_INI

INIRead		proto __cdecl :LPINI, __file:LPSTR
INIWrite	proto __cdecl :LPINI, __file:LPSTR
INIClose	proto __cdecl :LPINI
INIAlloc	proto __cdecl
INIGetSection	proto __cdecl :LPINI, :LPSTR
INIGetEntry	proto __cdecl :LPINI, :LPSTR
INIGetEntryID	proto __cdecl :LPINI, :UINT
INIAddSection	proto __cdecl :LPINI, :LPSTR
INIAddEntry	proto __cdecl :LPINI, :LPSTR
INIDelSection	proto __cdecl :LPINI, :LPSTR
INIDelEntries	proto __cdecl :LPINI
INIAddSectionX	proto c :LPINI, :LPSTR, :VARARG
INIAddEntryX	proto c :LPINI, :LPSTR, :VARARG

.list
endif
