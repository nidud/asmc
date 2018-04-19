CFSTR_VFW_FILTERLIST	equ <"Video for Windows 4 Filters">

VFW_FILTERLIST		STRUC
cFilters		UINT ?
aClsId			CLSID 1 dup(<>)
VFW_FILTERLIST		ENDS



