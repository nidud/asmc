ifndef _D3DX9XOF_H
_D3DX9XOF_H equ <>
include d3dx9.inc

D3DXF_FILEFORMAT	typedef DWORD
D3DXF_FILEFORMAT_BINARY equ 0
D3DXF_FILEFORMAT_TEXT	equ 1
D3DXF_FILEFORMAT_COMPRESSED equ 2

D3DXF_FILESAVEOPTIONS	typedef DWORD
D3DXF_FILESAVE_TOFILE	equ 0x00
D3DXF_FILESAVE_TOWFILE	equ 0x01

D3DXF_FILELOADOPTIONS	typedef DWORD
D3DXF_FILELOAD_FROMFILE equ 0x00
D3DXF_FILELOAD_FROMWFILE equ 0x01
D3DXF_FILELOAD_FROMRESOURCE equ 0x02
D3DXF_FILELOAD_FROMMEMORY equ 0x03

D3DXF_FILELOADRESOURCE	STRUC
hModule			HMODULE ?
lpName			LPSTR ?
lpType			LPSTR ?
D3DXF_FILELOADRESOURCE	ENDS

D3DXF_FILELOADMEMORY	STRUC
lpMemory		PVOID ?
dSize			SIZE_T ?
D3DXF_FILELOADMEMORY	ENDS


ifndef _NO_COM
DEFINE_GUID(IID_ID3DXFile,	     0xcef08cf9, 0x7b4f, 0x4429, 0x96, 0x24, 0x2a, 0x69, 0x0a, 0x93, 0x32, 0x01);
DEFINE_GUID(IID_ID3DXFileSaveObject, 0xcef08cfa, 0x7b4f, 0x4429, 0x96, 0x24, 0x2a, 0x69, 0x0a, 0x93, 0x32, 0x01);
DEFINE_GUID(IID_ID3DXFileSaveData,   0xcef08cfb, 0x7b4f, 0x4429, 0x96, 0x24, 0x2a, 0x69, 0x0a, 0x93, 0x32, 0x01);
DEFINE_GUID(IID_ID3DXFileEnumObject, 0xcef08cfc, 0x7b4f, 0x4429, 0x96, 0x24, 0x2a, 0x69, 0x0a, 0x93, 0x32, 0x01);
DEFINE_GUID(IID_ID3DXFileData,	     0xcef08cfd, 0x7b4f, 0x4429, 0x96, 0x24, 0x2a, 0x69, 0x0a, 0x93, 0x32, 0x01);
endif ;; _NO_COM


;STDAPI
D3DXFileCreate proto WINAPI \
		  file: ptr ID3DXFile


.comdef ID3DXFile
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateEnumObject	proc :ptr, :D3DXF_FILELOADOPTIONS, :ptr
    CreateSaveObject	proc :ptr, :D3DXF_FILESAVEOPTIONS, :D3DXF_FILEFORMAT, :ptr
    RegisterTemplates	proc :ptr, :SIZE_T
    RegisterEnumTemplates proc :ptr
    .ends

.comdef ID3DXFileSaveObject
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFile		proc :ptr
    AddDataObject	proc :REFGUID, :ptr, :ptr, :SIZE_T, :ptr, :ptr
    Save		proc
    .ends

.comdef ID3DXFileSaveData
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSave		proc :ptr
    GetName		proc :ptr, :ptr
    GetId		proc :LPGUID
    GetType		proc :ptr
    AddDataObject	proc :REFGUID, :ptr, :ptr, :SIZE_T, :ptr, :ptr
    AddDataReference	proc :ptr, :ptr
    .ends


.comdef ID3DXFileEnumObject
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFile		proc :ptr
    GetChildren		proc :ptr
    GetChild		proc :SIZE_T, :ptr
    GetDataObjectById	proc :REFGUID, :ptr
    GetDataObjectByName proc :ptr, :ptr
    .ends

.comdef ID3DXFileData
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetEnum		proc :ptr
    GetName		proc :ptr, :ptr
    GetId		proc :LPGUID
    _Lock		proc :ptr, :ptr
    Unlock		proc
    GetType		proc :ptr
    IsReference		proc
    GetChildren		proc :ptr
    GetChild		proc :SIZE_T, :ptr
    .ends

;; D3DX File errors
_FACD3DXF		equ 0x876

D3DXFERR_BADOBJECT	equ MAKE_HRESULT(1,_FACD3DXF,900)
D3DXFERR_BADVALUE	equ MAKE_HRESULT(1,_FACD3DXF,901)
D3DXFERR_BADTYPE	equ MAKE_HRESULT(1,_FACD3DXF,902)
D3DXFERR_NOTFOUND	equ MAKE_HRESULT(1,_FACD3DXF,903)
D3DXFERR_NOTDONEYET	equ MAKE_HRESULT(1,_FACD3DXF,904)
D3DXFERR_FILENOTFOUND	equ MAKE_HRESULT(1,_FACD3DXF,905)
D3DXFERR_RESOURCENOTFOUND equ MAKE_HRESULT(1,_FACD3DXF,906)
D3DXFERR_BADRESOURCE	equ MAKE_HRESULT(1,_FACD3DXF,907)
D3DXFERR_BADFILETYPE	equ MAKE_HRESULT(1,_FACD3DXF,908)
D3DXFERR_BADFILEVERSION equ MAKE_HRESULT(1,_FACD3DXF,909)
D3DXFERR_BADFILEFLOATSIZE equ MAKE_HRESULT(1,_FACD3DXF,910)
D3DXFERR_BADFILE	equ MAKE_HRESULT(1,_FACD3DXF,911)
D3DXFERR_PARSEERROR	equ MAKE_HRESULT(1,_FACD3DXF,912)
D3DXFERR_BADARRAYSIZE	equ MAKE_HRESULT(1,_FACD3DXF,913)
D3DXFERR_BADDATAREFERENCE equ MAKE_HRESULT(1,_FACD3DXF,914)
D3DXFERR_NOMOREOBJECTS	equ MAKE_HRESULT(1,_FACD3DXF,915)
D3DXFERR_NOMOREDATA	equ MAKE_HRESULT(1,_FACD3DXF,916)
D3DXFERR_BADCACHEFILE	equ MAKE_HRESULT(1,_FACD3DXF,917)

endif
