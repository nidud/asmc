ifndef MSDAGUID
define MSDAGUID
include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
;undef OLEDBDECLSPEC
if _MSC_VER ge 1100
;OLEDBDECLSPEC equ <__declspec(selectany)>
else
;OLEDBDECLSPEC equ <>
endif
DEFINE_GUID(CLSID_OLEDB_ENUMERATOR,0xc8b522d0,0x5cf3,0x11ce,0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d)
DEFINE_GUID(CLSID_EXTENDEDERRORINFO,0xc8b522cf,0x5cf3,0x11ce,0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d)
DEFINE_GUID(CLSID_MSDAVTM,0x0c733a8e,0x2a1c,0x11ce,0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d)
DEFINE_GUID(CLSID_OLEDB_CONVERSIONLIBRARY,0xc8b522d1,0x5cf3,0x11ce,0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d)
DEFINE_GUID(CLSID_OLEDB_ROWPOSITIONLIBRARY,0x2048eee6,0x7fa2,0x11d0,0x9e,0x6a,0x00,0xa0,0xc9,0x13,0x8c,0x29)
DEFINE_GUID(OLEDB_SVC_DSLPropertyPages,0x51740c02,0x7e8e,0x11d2,0xa0,0x2d,0x00,0xc0,0x4f,0xa3,0x73,0x48)
endif
endif
