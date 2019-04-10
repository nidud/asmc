ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __dia2_h__
__dia2_h__ equ <>

ifndef __IDiaLoadCallback_FWD_DEFINED__
__IDiaLoadCallback_FWD_DEFINED__ equ 1
endif
ifndef __IDiaLoadCallback2_FWD_DEFINED__
__IDiaLoadCallback2_FWD_DEFINED__ equ 1
endif
ifndef __IDiaReadExeAtOffsetCallback_FWD_DEFINED__
__IDiaReadExeAtOffsetCallback_FWD_DEFINED__ equ 1
endif
ifndef __IDiaReadExeAtRVACallback_FWD_DEFINED__
__IDiaReadExeAtRVACallback_FWD_DEFINED__ equ 1
endif
ifndef __IDiaDataSource_FWD_DEFINED__
__IDiaDataSource_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumSymbols_FWD_DEFINED__
__IDiaEnumSymbols_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumSymbolsByAddr_FWD_DEFINED__
__IDiaEnumSymbolsByAddr_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumSourceFiles_FWD_DEFINED__
__IDiaEnumSourceFiles_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumInputAssemblyFiles_FWD_DEFINED__
__IDiaEnumInputAssemblyFiles_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumLineNumbers_FWD_DEFINED__
__IDiaEnumLineNumbers_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumInjectedSources_FWD_DEFINED__
__IDiaEnumInjectedSources_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumSegments_FWD_DEFINED__
__IDiaEnumSegments_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumSectionContribs_FWD_DEFINED__
__IDiaEnumSectionContribs_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumFrameData_FWD_DEFINED__
__IDiaEnumFrameData_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumDebugStreamData_FWD_DEFINED__
__IDiaEnumDebugStreamData_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumDebugStreams_FWD_DEFINED__
__IDiaEnumDebugStreams_FWD_DEFINED__ equ 1
endif
ifndef __IDiaAddressMap_FWD_DEFINED__
__IDiaAddressMap_FWD_DEFINED__ equ 1
endif
ifndef __IDiaSession_FWD_DEFINED__
__IDiaSession_FWD_DEFINED__ equ 1
endif
ifndef __IDiaSymbol_FWD_DEFINED__
__IDiaSymbol_FWD_DEFINED__ equ 1
endif
ifndef __IDiaSourceFile_FWD_DEFINED__
__IDiaSourceFile_FWD_DEFINED__ equ 1
endif
ifndef __IDiaInputAssemblyFile_FWD_DEFINED__
__IDiaInputAssemblyFile_FWD_DEFINED__ equ 1
endif
ifndef __IDiaLineNumber_FWD_DEFINED__
__IDiaLineNumber_FWD_DEFINED__ equ 1
endif
ifndef __IDiaSectionContrib_FWD_DEFINED__
__IDiaSectionContrib_FWD_DEFINED__ equ 1
endif
ifndef __IDiaSegment_FWD_DEFINED__
__IDiaSegment_FWD_DEFINED__ equ 1
endif
ifndef __IDiaInjectedSource_FWD_DEFINED__
__IDiaInjectedSource_FWD_DEFINED__ equ 1
endif
ifndef __IDiaStackWalkFrame_FWD_DEFINED__
__IDiaStackWalkFrame_FWD_DEFINED__ equ 1
endif
ifndef __IDiaFrameData_FWD_DEFINED__
__IDiaFrameData_FWD_DEFINED__ equ 1
endif
ifndef __IDiaImageData_FWD_DEFINED__
__IDiaImageData_FWD_DEFINED__ equ 1
endif
ifndef __IDiaTable_FWD_DEFINED__
__IDiaTable_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumTables_FWD_DEFINED__
__IDiaEnumTables_FWD_DEFINED__ equ 1
endif
ifndef __DiaSource_FWD_DEFINED__
__DiaSource_FWD_DEFINED__ equ 1
endif
ifndef __DiaSourceAlt_FWD_DEFINED__
__DiaSourceAlt_FWD_DEFINED__ equ 1
endif
ifndef __DiaStackWalker_FWD_DEFINED__
__DiaStackWalker_FWD_DEFINED__ equ 1
endif
ifndef __IDiaPropertyStorage_FWD_DEFINED__
__IDiaPropertyStorage_FWD_DEFINED__ equ 1
endif
ifndef __IDiaStackFrame_FWD_DEFINED__
__IDiaStackFrame_FWD_DEFINED__ equ 1
endif
ifndef __IDiaEnumStackFrames_FWD_DEFINED__
__IDiaEnumStackFrames_FWD_DEFINED__ equ 1
endif
ifndef __IDiaStackWalkHelper_FWD_DEFINED__
__IDiaStackWalkHelper_FWD_DEFINED__ equ 1
endif
ifndef __IDiaStackWalker_FWD_DEFINED__
__IDiaStackWalker_FWD_DEFINED__ equ 1
endif
ifndef __IDiaStackWalkHelper2_FWD_DEFINED__
__IDiaStackWalkHelper2_FWD_DEFINED__ equ 1
endif
ifndef __IDiaStackWalker2_FWD_DEFINED__
__IDiaStackWalker2_FWD_DEFINED__ equ 1
endif

include objidl.inc
include oaidl.inc
include propidl.inc
include cvconst.inc

.pragma comment(lib, diaguid.lib, msdia80.dll)

NameSearchOptions	typedef SDWORD
nsNone			equ 0
nsfCaseSensitive	equ 0x1
nsfCaseInsensitive	equ 0x2
nsfFNameExt		equ 0x4
nsfRegularExpression	equ 0x8
nsfUndecoratedName	equ 0x10
nsCaseSensitive		equ nsfCaseSensitive
nsCaseInsensitive	equ nsfCaseInsensitive
nsFNameExt		equ ( nsfCaseInsensitive or nsfFNameExt )
nsRegularExpression	equ ( nsfRegularExpression or nsfCaseSensitive )
nsCaseInRegularExpression equ ( nsfRegularExpression or nsfCaseInsensitive )

_MIDL___MIDL_itf_dia2_0000_0000_0001 typedef SDWORD
E_PDB_OK		equ (((( 1 shl 31 ) or ( 0x6d shl 16 )) or 1 ))
E_PDB_USAGE		equ ( E_PDB_OK + 1 )
E_PDB_OUT_OF_MEMORY	equ ( E_PDB_USAGE + 1 )
E_PDB_FILE_SYSTEM	equ ( E_PDB_OUT_OF_MEMORY + 1 )
E_PDB_NOT_FOUND		equ ( E_PDB_FILE_SYSTEM + 1 )
E_PDB_INVALID_SIG	equ ( E_PDB_NOT_FOUND + 1 )
E_PDB_INVALID_AGE	equ ( E_PDB_INVALID_SIG + 1 )
E_PDB_PRECOMP_REQUIRED	equ ( E_PDB_INVALID_AGE + 1 )
E_PDB_OUT_OF_TI		equ ( E_PDB_PRECOMP_REQUIRED + 1 )
E_PDB_NOT_IMPLEMENTED	equ ( E_PDB_OUT_OF_TI + 1 )
E_PDB_V1_PDB		equ ( E_PDB_NOT_IMPLEMENTED + 1 )
E_PDB_FORMAT		equ ( E_PDB_V1_PDB + 1 )
E_PDB_LIMIT		equ ( E_PDB_FORMAT + 1 )
E_PDB_CORRUPT		equ ( E_PDB_LIMIT + 1 )
E_PDB_TI16		equ ( E_PDB_CORRUPT + 1 )
E_PDB_ACCESS_DENIED	equ ( E_PDB_TI16 + 1 )
E_PDB_ILLEGAL_TYPE_EDIT equ ( E_PDB_ACCESS_DENIED + 1 )
E_PDB_INVALID_EXECUTABLE equ ( E_PDB_ILLEGAL_TYPE_EDIT + 1 )
E_PDB_DBG_NOT_FOUND	equ ( E_PDB_INVALID_EXECUTABLE + 1 )
E_PDB_NO_DEBUG_INFO	equ ( E_PDB_DBG_NOT_FOUND + 1 )
E_PDB_INVALID_EXE_TIMESTAMP equ ( E_PDB_NO_DEBUG_INFO + 1 )
E_PDB_RESERVED		equ ( E_PDB_INVALID_EXE_TIMESTAMP + 1 )
E_PDB_DEBUG_INFO_NOT_IN_PDB equ ( E_PDB_RESERVED + 1 )
E_PDB_SYMSRV_BAD_CACHE_PATH equ ( E_PDB_DEBUG_INFO_NOT_IN_PDB + 1 )
E_PDB_SYMSRV_CACHE_FULL equ ( E_PDB_SYMSRV_BAD_CACHE_PATH + 1 )
E_PDB_OBJECT_DISPOSED	equ ( E_PDB_SYMSRV_CACHE_FULL + 1 )
E_PDB_MAX		equ ( E_PDB_OBJECT_DISPOSED + 1 )

CALLBACKC(PfnPDBDebugDirV, :BOOL, :ptr)

ifndef __IDiaLoadCallback_INTERFACE_DEFINED__
__IDiaLoadCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaLoadCallback, "C32ADB82-73F4-421b-95D5-A4706EDF5DBE")

.comdef IDiaLoadCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    NotifyDebugDir	proc :BOOL, :DWORD, :ptr
    NotifyOpenDBG	proc :LPCOLESTR, :HRESULT
    NotifyOpenPDB	proc :LPCOLESTR, :HRESULT
    RestrictRegistryAccess proc
    RestrictSymbolServerAccess proc
    .ends

endif


ifndef __IDiaLoadCallback2_INTERFACE_DEFINED__
__IDiaLoadCallback2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaLoadCallback2, "4688a074-5a4d-4486-aea8-7b90711d9f7c")

.comdef IDiaLoadCallback2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    NotifyDebugDir	proc :BOOL, :DWORD, :ptr
    NotifyOpenDBG	proc :LPCOLESTR, :HRESULT
    NotifyOpenPDB	proc :LPCOLESTR, :HRESULT
    RestrictRegistryAccess proc
    RestrictSymbolServerAccess proc
    RestrictOriginalPathAccess proc
    RestrictReferencePathAccess proc
    RestrictDBGAccess	proc
    RestrictSystemRootAccess proc
    .ends

endif

ifndef __IDiaReadExeAtOffsetCallback_INTERFACE_DEFINED__
__IDiaReadExeAtOffsetCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaReadExeAtOffsetCallback, "587A461C-B80B-4f54-9194-5032589A6319")

.comdef IDiaReadExeAtOffsetCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ReadExecutableAt	proc :DWORDLONG, :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IDiaReadExeAtRVACallback_INTERFACE_DEFINED__
__IDiaReadExeAtRVACallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaReadExeAtRVACallback, "8E3F80CA-7517-432a-BA07-285134AAEA8E")

.comdef IDiaReadExeAtRVACallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ReadExecutableAtRVA proc :DWORD, :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IDiaDataSource_INTERFACE_DEFINED__
__IDiaDataSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaDataSource, "79F1BB5F-B66E-48e5-B6A9-1545C323CA3D")

.comdef IDiaDataSource

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_lastError	proc :ptr
    loadDataFromPdb	proc :LPCOLESTR
    loadAndValidateDataFromPdb proc :LPCOLESTR, :ptr, :DWORD, :DWORD
    loadDataForExe	proc :LPCOLESTR, :LPCOLESTR, :ptr
    loadDataFromIStream proc :ptr
    openSession		proc :ptr
    loadDataFromCodeViewInfo proc :LPCOLESTR, :LPCOLESTR, :DWORD, :ptr, :ptr
    loadDataFromMiscInfo proc :LPCOLESTR, :LPCOLESTR, :DWORD, :DWORD, :DWORD, :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IDiaEnumSymbols_INTERFACE_DEFINED__
__IDiaEnumSymbols_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumSymbols, "CAB72C48-443B-48f5-9B0B-42F0820AB29A")

.comdef IDiaEnumSymbols

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumSymbolsByAddr_INTERFACE_DEFINED__
__IDiaEnumSymbolsByAddr_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumSymbolsByAddr, "624B7D9C-24EA-4421-9D06-3B577471C1FA")

.comdef IDiaEnumSymbolsByAddr

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    symbolByAddr	proc :DWORD, :DWORD, :ptr
    symbolByRVA		proc :DWORD, :ptr
    symbolByVA		proc :ULONGLONG, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Prev		proc :ULONG, :ptr, :ptr
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumSourceFiles_INTERFACE_DEFINED__
__IDiaEnumSourceFiles_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumSourceFiles, "10F3DBD9-664F-4469-B808-9471C7A50538")

.comdef IDiaEnumSourceFiles

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumInputAssemblyFiles_INTERFACE_DEFINED__
__IDiaEnumInputAssemblyFiles_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumInputAssemblyFiles, "1C7FF653-51F7-457E-8419-B20F57EF7E4D")

.comdef IDiaEnumInputAssemblyFiles

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumLineNumbers_INTERFACE_DEFINED__
__IDiaEnumLineNumbers_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumLineNumbers, "FE30E878-54AC-44f1-81BA-39DE940F6052")

.comdef IDiaEnumLineNumbers

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumInjectedSources_INTERFACE_DEFINED__
__IDiaEnumInjectedSources_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumInjectedSources, "D5612573-6925-4468-8883-98CDEC8C384A")

.comdef IDiaEnumInjectedSources

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumSegments_INTERFACE_DEFINED__
__IDiaEnumSegments_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumSegments, "E8368CA9-01D1-419d-AC0C-E31235DBDA9F")

.comdef IDiaEnumSegments

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumSectionContribs_INTERFACE_DEFINED__
__IDiaEnumSectionContribs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumSectionContribs, "1994DEB2-2C82-4b1d-A57F-AFF424D54A68")

.comdef IDiaEnumSectionContribs

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumFrameData_INTERFACE_DEFINED__
__IDiaEnumFrameData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumFrameData, "9FC77A4B-3C1C-44ed-A798-6C1DEEA53E1F")

.comdef IDiaEnumFrameData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    frameByRVA		proc :DWORD, :ptr
    frameByVA		proc :ULONGLONG, :ptr
    .ends

endif

ifndef __IDiaEnumDebugStreamData_INTERFACE_DEFINED__
__IDiaEnumDebugStreamData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumDebugStreamData, "486943E8-D187-4a6b-A3C4-291259FFF60D")

.comdef IDiaEnumDebugStreamData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    get_name		proc :ptr
    Item		proc :DWORD, :DWORD, :ptr, :ptr
    Next		proc :ULONG, :DWORD, :ptr, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDiaEnumDebugStreams_INTERFACE_DEFINED__
__IDiaEnumDebugStreams_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumDebugStreams, "08CBB41E-47A6-4f87-92F1-1C9C87CED044")

.comdef IDiaEnumDebugStreams

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :VARIANT, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

DiaAddressMapEntry	STRUC
rva			dd ?
rvaTo			dd ?
DiaAddressMapEntry	ENDS

ifndef __IDiaAddressMap_INTERFACE_DEFINED__
__IDiaAddressMap_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaAddressMap, "B62A2E7A-067A-4ea3-B598-04C09717502C")

.comdef IDiaAddressMap

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_addressMapEnabled proc :ptr
    put_addressMapEnabled proc :BOOL
    get_relativeVirtualAddressEnabled proc :ptr
    put_relativeVirtualAddressEnabled proc :BOOL
    get_imageAlign	proc :ptr
    put_imageAlign	proc :DWORD
    set_imageHeaders	proc :DWORD, :ptr, :BOOL
    set_addressMap	proc :DWORD, :ptr, :BOOL
    .ends

endif

ifndef __IDiaSession_INTERFACE_DEFINED__
__IDiaSession_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaSession, "2F609EE1-D1C8-4E24-8288-3326BADCD211")

.comdef IDiaSession

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_loadAddress	proc :ptr
    put_loadAddress	proc :ULONGLONG
    get_globalScope	proc :ptr
    getEnumTables	proc :ptr
    getSymbolsByAddr	proc :ptr
    findChildren	proc :ptr, :SymTagEnum, :LPCOLESTR, :DWORD, :ptr
    findChildrenEx	proc :ptr, :SymTagEnum, :LPCOLESTR, :DWORD, :ptr
    findChildrenExByAddr proc :ptr, :SymTagEnum, :LPCOLESTR, :DWORD, :DWORD, :DWORD, :ptr
    findChildrenExByVA	proc :ptr, :SymTagEnum, :LPCOLESTR, :DWORD, :ULONGLONG, :ptr
    findChildrenExByRVA proc :ptr, :SymTagEnum, :LPCOLESTR, :DWORD, :DWORD, :ptr
    findSymbolByAddr	proc :DWORD, :DWORD, :SymTagEnum, :ptr
    findSymbolByRVA	proc :DWORD, :SymTagEnum, :ptr
    findSymbolByVA	proc :ULONGLONG, :SymTagEnum, :ptr
    findSymbolByToken	proc :ULONG, :SymTagEnum, :ptr
    symsAreEquiv	proc :ptr, :ptr
    symbolById		proc :DWORD, :ptr
    findSymbolByRVAEx	proc :DWORD, :SymTagEnum, :ptr, :ptr
    findSymbolByVAEx	proc :ULONGLONG, :SymTagEnum, :ptr, :ptr
    findFile		proc :ptr, :LPCOLESTR, :DWORD, :ptr
    findFileById	proc :DWORD, :ptr
    findLines		proc :ptr, :ptr, :ptr
    findLinesByAddr	proc :DWORD, :DWORD, :DWORD, :ptr
    findLinesByRVA	proc :DWORD, :DWORD, :ptr
    findLinesByVA	proc :ULONGLONG, :DWORD, :ptr
    findLinesByLinenum	proc :ptr, :ptr, :DWORD, :DWORD, :ptr
    findInjectedSource	proc :LPCOLESTR, :ptr
    getEnumDebugStreams proc :ptr
    findInlineFramesByAddr proc :ptr, :DWORD, :DWORD, :ptr
    findInlineFramesByRVA proc :ptr, :DWORD, :ptr
    findInlineFramesByVA proc :ptr, :ULONGLONG, :ptr
    findInlineeLines	proc :ptr, :ptr
    findInlineeLinesByAddr proc :ptr, :DWORD, :DWORD, :DWORD, :ptr
    findInlineeLinesByRVA proc :ptr, :DWORD, :DWORD, :ptr
    findInlineeLinesByVA proc :ptr, :ULONGLONG, :DWORD, :ptr
    findInlineeLinesByLinenum proc :ptr, :ptr, :DWORD, :DWORD, :ptr
    findInlineesByName	proc :LPCOLESTR, :DWORD, :ptr
    findAcceleratorInlineeLinesByLinenum proc :ptr, :ptr, :DWORD, :DWORD, :ptr
    findSymbolsForAcceleratorPointerTag proc :ptr, :DWORD, :ptr
    findSymbolsByRVAForAcceleratorPointerTag proc :ptr, :DWORD, :DWORD, :ptr
    findAcceleratorInlineesByName proc :LPCOLESTR, :DWORD, :ptr
    addressForVA	proc :ULONGLONG, :ptr, :ptr
    addressForRVA	proc :DWORD, :ptr, :ptr
    findILOffsetsByAddr proc :DWORD, :DWORD, :DWORD, :ptr
    findILOffsetsByRVA	proc :DWORD, :DWORD, :ptr
    findILOffsetsByVA	proc :ULONGLONG, :DWORD, :ptr
    findInputAssemblyFiles proc :ptr
    findInputAssembly	proc :DWORD, :ptr
    findInputAssemblyById proc :DWORD, :ptr
    getFuncMDTokenMapSize proc :ptr
    getFuncMDTokenMap	proc :DWORD, :ptr, :ptr
    getTypeMDTokenMapSize proc :ptr
    getTypeMDTokenMap	proc :DWORD, :ptr, :ptr
    getNumberOfFunctionFragments_VA proc :ULONGLONG, :DWORD, :ptr
    getNumberOfFunctionFragments_RVA proc :DWORD, :DWORD, :ptr
    getFunctionFragments_VA proc :ULONGLONG, :DWORD, :DWORD, :ptr, :ptr
    getFunctionFragments_RVA proc :DWORD, :DWORD, :DWORD, :ptr, :ptr
    getExports		proc :ptr
    getHeapAllocationSites proc :ptr
    findInputAssemblyFile proc :ptr, :ptr
    .ends

endif

ifndef __IDiaSymbol_INTERFACE_DEFINED__
__IDiaSymbol_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaSymbol, "cb787b2f-bd6c-4635-ba52-933126bd2dcd")

.comdef IDiaSymbol

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_symIndexId	proc :ptr
    get_symTag		proc :ptr
    get_name		proc :ptr
    get_lexicalParent	proc :ptr
    get_classParent	proc :ptr
    get_type		proc :ptr
    get_dataKind	proc :ptr
    get_locationType	proc :ptr
    get_addressSection	proc :ptr
    get_addressOffset	proc :ptr
    get_relativeVirtualAddress proc :ptr
    get_virtualAddress	proc :ptr
    get_registerId	proc :ptr
    get_offset		proc :ptr
    get_length		proc :ptr
    get_slot		proc :ptr
    get_volatileType	proc :ptr
    get_constType	proc :ptr
    get_unalignedType	proc :ptr
    get_access		proc :ptr
    get_libraryName	proc :ptr
    get_platform	proc :ptr
    get_language	proc :ptr
    get_editAndContinueEnabled proc :ptr
    get_frontEndMajor	proc :ptr
    get_frontEndMinor	proc :ptr
    get_frontEndBuild	proc :ptr
    get_backEndMajor	proc :ptr
    get_backEndMinor	proc :ptr
    get_backEndBuild	proc :ptr
    get_sourceFileName	proc :ptr
    get_unused		proc :ptr
    get_thunkOrdinal	proc :ptr
    get_thisAdjust	proc :ptr
    get_virtualBaseOffset proc :ptr
    get_virtual		proc :ptr
    get_intro		proc :ptr
    get_pure		proc :ptr
    get_callingConvention proc :ptr
    get_value		proc :ptr
    get_baseType	proc :ptr
    get_token		proc :ptr
    get_timeStamp	proc :ptr
    get_guid		proc :ptr
    get_symbolsFileName proc :ptr
    get_reference	proc :ptr
    get_count		proc :ptr
    get_bitPosition	proc :ptr
    get_arrayIndexType	proc :ptr
    get_packed		proc :ptr
    get_constructor	proc :ptr
    get_overloadedOperator proc :ptr
    get_nested		proc :ptr
    get_hasNestedTypes	proc :ptr
    get_hasAssignmentOperator proc :ptr
    get_hasCastOperator proc :ptr
    get_scoped		proc :ptr
    get_virtualBaseClass proc :ptr
    get_indirectVirtualBaseClass proc :ptr
    get_virtualBasePointerOffset proc :ptr
    get_virtualTableShape proc :ptr
    get_lexicalParentId proc :ptr
    get_classParentId	proc :ptr
    get_typeId		proc :ptr
    get_arrayIndexTypeId proc :ptr
    get_virtualTableShapeId proc :ptr
    get_code		proc :ptr
    get_function	proc :ptr
    get_managed		proc :ptr
    get_msil		proc :ptr
    get_virtualBaseDispIndex proc :ptr
    get_undecoratedName proc :ptr
    get_age		proc :ptr
    get_signature	proc :ptr
    get_compilerGenerated proc :ptr
    get_addressTaken	proc :ptr
    get_rank		proc :ptr
    get_lowerBound	proc :ptr
    get_upperBound	proc :ptr
    get_lowerBoundId	proc :ptr
    get_upperBoundId	proc :ptr
    get_dataBytes	proc :DWORD, :ptr, :ptr
    findChildren	proc :SymTagEnum, :LPCOLESTR, :DWORD, :ptr
    findChildrenEx	proc :SymTagEnum, :LPCOLESTR, :DWORD, :ptr
    findChildrenExByAddr proc :SymTagEnum, :LPCOLESTR, :DWORD, :DWORD, :DWORD, :ptr
    findChildrenExByVA	proc :SymTagEnum, :LPCOLESTR, :DWORD, :ULONGLONG, :ptr
    findChildrenExByRVA proc :SymTagEnum, :LPCOLESTR, :DWORD, :DWORD, :ptr
    get_targetSection	proc :ptr
    get_targetOffset	proc :ptr
    get_targetRelativeVirtualAddress proc :ptr
    get_targetVirtualAddress proc :ptr
    get_machineType	proc :ptr
    get_oemId		proc :ptr
    get_oemSymbolId	proc :ptr
    get_types		proc :DWORD, :ptr, :ptr
    get_typeIds		proc :DWORD, :ptr, :ptr
    get_objectPointerType proc :ptr
    get_udtKind		proc :ptr
    get_undecoratedNameEx proc :DWORD, :ptr
    get_noReturn	proc :ptr
    get_customCallingConvention proc :ptr
    get_noInline	proc :ptr
    get_optimizedCodeDebugInfo proc :ptr
    get_notReached	proc :ptr
    get_interruptReturn proc :ptr
    get_farReturn	proc :ptr
    get_isStatic	proc :ptr
    get_hasDebugInfo	proc :ptr
    get_isLTCG		proc :ptr
    get_isDataAligned	proc :ptr
    get_hasSecurityChecks proc :ptr
    get_compilerName	proc :ptr
    get_hasAlloca	proc :ptr
    get_hasSetJump	proc :ptr
    get_hasLongJump	proc :ptr
    get_hasInlAsm	proc :ptr
    get_hasEH		proc :ptr
    get_hasSEH		proc :ptr
    get_hasEHa		proc :ptr
    get_isNaked		proc :ptr
    get_isAggregated	proc :ptr
    get_isSplitted	proc :ptr
    get_container	proc :ptr
    get_inlSpec		proc :ptr
    get_noStackOrdering proc :ptr
    get_virtualBaseTableType proc :ptr
    get_hasManagedCode	proc :ptr
    get_isHotpatchable	proc :ptr
    get_isCVTCIL	proc :ptr
    get_isMSILNetmodule proc :ptr
    get_isCTypes	proc :ptr
    get_isStripped	proc :ptr
    get_frontEndQFE	proc :ptr
    get_backEndQFE	proc :ptr
    get_wasInlined	proc :ptr
    get_strictGSCheck	proc :ptr
    get_isCxxReturnUdt	proc :ptr
    get_isConstructorVirtualBase proc :ptr
    get_RValueReference proc :ptr
    get_unmodifiedType	proc :ptr
    get_framePointerPresent proc :ptr
    get_isSafeBuffers	proc :ptr
    get_intrinsic	proc :ptr
    get_sealed		proc :ptr
    get_hfaFloat	proc :ptr
    get_hfaDouble	proc :ptr
    get_liveRangeStartAddressSection proc :ptr
    get_liveRangeStartAddressOffset proc :ptr
    get_liveRangeStartRelativeVirtualAddress proc :ptr
    get_countLiveRanges proc :ptr
    get_liveRangeLength proc :ptr
    get_offsetInUdt	proc :ptr
    get_paramBasePointerRegisterId proc :ptr
    get_localBasePointerRegisterId proc :ptr
    get_isLocationControlFlowDependent proc :ptr
    get_stride		proc :ptr
    get_numberOfRows	proc :ptr
    get_numberOfColumns proc :ptr
    get_isMatrixRowMajor proc :ptr
    get_numericProperties proc :DWORD, :ptr, :ptr
    get_modifierValues	proc :DWORD, :ptr, :ptr
    get_isReturnValue	proc :ptr
    get_isOptimizedAway proc :ptr
    get_builtInKind	proc :ptr
    get_registerType	proc :ptr
    get_baseDataSlot	proc :ptr
    get_baseDataOffset	proc :ptr
    get_textureSlot	proc :ptr
    get_samplerSlot	proc :ptr
    get_uavSlot		proc :ptr
    get_sizeInUdt	proc :ptr
    get_memorySpaceKind proc :ptr
    get_unmodifiedTypeId proc :ptr
    get_subTypeId	proc :ptr
    get_subType		proc :ptr
    get_numberOfModifiers proc :ptr
    get_numberOfRegisterIndices proc :ptr
    get_isHLSLData	proc :ptr
    get_isPointerToDataMember proc :ptr
    get_isPointerToMemberFunction proc :ptr
    get_isSingleInheritance proc :ptr
    get_isMultipleInheritance proc :ptr
    get_isVirtualInheritance proc :ptr
    get_restrictedType	proc :ptr
    get_isPointerBasedOnSymbolValue proc :ptr
    get_baseSymbol	proc :ptr
    get_baseSymbolId	proc :ptr
    get_objectFileName	proc :ptr
    get_isAcceleratorGroupSharedLocal proc :ptr
    get_isAcceleratorPointerTagLiveRange proc :ptr
    get_isAcceleratorStubFunction proc :ptr
    get_numberOfAcceleratorPointerTags proc :ptr
    get_isSdl		proc :ptr
    get_isWinRTPointer	proc :ptr
    get_isRefUdt	proc :ptr
    get_isValueUdt	proc :ptr
    get_isInterfaceUdt	proc :ptr
    findInlineFramesByAddr proc :DWORD, :DWORD, :ptr
    findInlineFramesByRVA proc :DWORD, :ptr
    findInlineFramesByVA proc :ULONGLONG, :ptr
    findInlineeLines	proc :ptr
    findInlineeLinesByAddr proc :DWORD, :DWORD, :DWORD, :ptr
    findInlineeLinesByRVA proc :DWORD, :DWORD, :ptr
    findInlineeLinesByVA proc :ULONGLONG, :DWORD, :ptr
    findSymbolsForAcceleratorPointerTag proc :DWORD, :ptr
    findSymbolsByRVAForAcceleratorPointerTag proc :DWORD, :DWORD, :ptr
    get_acceleratorPointerTags proc :DWORD, :ptr, :ptr
    getSrcLineOnTypeDefn proc :ptr
    get_isPGO		proc :ptr
    get_hasValidPGOCounts proc :ptr
    get_isOptimizedForSpeed proc :ptr
    get_PGOEntryCount	proc :ptr
    get_PGOEdgeCount	proc :ptr
    get_PGODynamicInstructionCount proc :ptr
    get_staticSize	proc :ptr
    get_finalLiveStaticSize proc :ptr
    get_phaseName	proc :ptr
    get_hasControlFlowCheck proc :ptr
    get_constantExport	proc :ptr
    get_dataExport	proc :ptr
    get_privateExport	proc :ptr
    get_noNameExport	proc :ptr
    get_exportHasExplicitlyAssignedOrdinal proc :ptr
    get_exportIsForwarder proc :ptr
    get_ordinal		proc :ptr
    get_frameSize	proc :ptr
    get_exceptionHandlerAddressSection proc :ptr
    get_exceptionHandlerAddressOffset proc :ptr
    get_exceptionHandlerRelativeVirtualAddress proc :ptr
    get_exceptionHandlerVirtualAddress proc :ptr
    findInputAssemblyFile proc :ptr
    get_characteristics proc :ptr
    get_coffGroup	proc :ptr
    get_bindID		proc :ptr
    get_bindSpace	proc :ptr
    get_bindSlot	proc :ptr
    .ends

endif


ifndef __IDiaSourceFile_INTERFACE_DEFINED__
__IDiaSourceFile_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaSourceFile, "A2EF5353-F5A8-4eb3-90D2-CB526ACB3CDD")

.comdef IDiaSourceFile

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_uniqueId	proc :ptr
    get_fileName	proc :ptr
    get_checksumType	proc :ptr
    get_compilands	proc :ptr
    get_checksum	proc :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IDiaInputAssemblyFile_INTERFACE_DEFINED__
__IDiaInputAssemblyFile_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaInputAssemblyFile, "3BFE56B0-390C-4863-9430-1F3D083B7684")

.comdef IDiaInputAssemblyFile

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_uniqueId	proc :ptr
    get_index		proc :ptr
    get_timestamp	proc :ptr
    get_pdbAvailableAtILMerge proc :ptr
    get_fileName	proc :ptr
    get_version		proc :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IDiaLineNumber_INTERFACE_DEFINED__
__IDiaLineNumber_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaLineNumber, "B388EB14-BE4D-421d-A8A1-6CF7AB057086")

.comdef IDiaLineNumber

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_compiland	proc :ptr
    get_sourceFile	proc :ptr
    get_lineNumber	proc :ptr
    get_lineNumberEnd	proc :ptr
    get_columnNumber	proc :ptr
    get_columnNumberEnd proc :ptr
    get_addressSection	proc :ptr
    get_addressOffset	proc :ptr
    get_relativeVirtualAddress proc :ptr
    get_virtualAddress	proc :ptr
    get_length		proc :ptr
    get_sourceFileId	proc :ptr
    get_statement	proc :ptr
    get_compilandId	proc :ptr
    .ends

endif

ifndef __IDiaSectionContrib_INTERFACE_DEFINED__
__IDiaSectionContrib_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaSectionContrib, "0CF4B60E-35B1-4c6c-BDD8-854B9C8E3857")

.comdef IDiaSectionContrib

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_compiland	proc :ptr
    get_addressSection	proc :ptr
    get_addressOffset	proc :ptr
    get_relativeVirtualAddress proc :ptr
    get_virtualAddress	proc :ptr
    get_length		proc :ptr
    get_notPaged	proc :ptr
    get_code		proc :ptr
    get_initializedData proc :ptr
    get_uninitializedData proc :ptr
    get_remove		proc :ptr
    get_comdat		proc :ptr
    get_discardable	proc :ptr
    get_notCached	proc :ptr
    get_share		proc :ptr
    get_execute		proc :ptr
    get_read		proc :ptr
    get_write		proc :ptr
    get_dataCrc		proc :ptr
    get_relocationsCrc	proc :ptr
    get_compilandId	proc :ptr
    get_code16bit	proc :ptr
    .ends

endif

ifndef __IDiaSegment_INTERFACE_DEFINED__
__IDiaSegment_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaSegment, "0775B784-C75B-4449-848B-B7BD3159545B")

.comdef IDiaSegment

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_frame		proc :ptr
    get_offset		proc :ptr
    get_length		proc :ptr
    get_read		proc :ptr
    get_write		proc :ptr
    get_execute		proc :ptr
    get_addressSection	proc :ptr
    get_relativeVirtualAddress proc :ptr
    get_virtualAddress	proc :ptr
    .ends

endif

ifndef __IDiaInjectedSource_INTERFACE_DEFINED__
__IDiaInjectedSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaInjectedSource, "AE605CDC-8105-4a23-B710-3259F1E26112")

.comdef IDiaInjectedSource

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_crc		proc :ptr
    get_length		proc :ptr
    get_filename	proc :ptr
    get_objectFilename	proc :ptr
    get_virtualFilename proc :ptr
    get_sourceCompression proc :ptr
    get_source		proc :DWORD, :ptr, :ptr
    .ends

endif

_MIDL___MIDL_itf_dia2_0000_0025_0001 typedef SDWORD
E_DIA_INPROLOG		equ ( HRESULT  )(( ( ( ( unsigned long	)1 << 31 )  | ( ( unsigned long	 )( LONG  )0x6d << 16 )	 )  | ( unsigned long  )100 ) )
E_DIA_SYNTAX		equ ( E_DIA_INPROLOG + 1 )
E_DIA_FRAME_ACCESS	equ ( E_DIA_SYNTAX + 1 )
E_DIA_VALUE		equ ( E_DIA_FRAME_ACCESS + 1 )

ifndef __IDiaStackWalkFrame_INTERFACE_DEFINED__
__IDiaStackWalkFrame_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaStackWalkFrame, "07C590C1-438D-4F47-BDCD-4397BC81AD75")

.comdef IDiaStackWalkFrame

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_registerValue	proc :DWORD, :ptr
    put_registerValue	proc :DWORD, :ULONGLONG
    readMemory		proc :MemoryTypeEnum, :ULONGLONG, :DWORD, :ptr, :ptr
    searchForReturnAddress proc :ptr, :ptr
    searchForReturnAddressStart proc :ptr, :ULONGLONG, :ptr
    .ends

endif

ifndef __IDiaFrameData_INTERFACE_DEFINED__
__IDiaFrameData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaFrameData, "A39184B7-6A36-42de-8EEC-7DF9F3F59F33")

.comdef IDiaFrameData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_addressSection	proc :ptr
    get_addressOffset	proc :ptr
    get_relativeVirtualAddress proc :ptr
    get_virtualAddress	proc :ptr
    get_lengthBlock	proc :ptr
    get_lengthLocals	proc :ptr
    get_lengthParams	proc :ptr
    get_maxStack	proc :ptr
    get_lengthProlog	proc :ptr
    get_lengthSavedRegisters proc :ptr
    get_program		proc :ptr
    get_systemExceptionHandling proc :ptr
    get_cplusplusExceptionHandling proc :ptr
    get_functionStart	proc :ptr
    get_allocatesBasePointer proc :ptr
    get_type		proc :ptr
    get_functionParent	proc :ptr
    execute		proc :ptr
    .ends

endif

ifndef __IDiaImageData_INTERFACE_DEFINED__
__IDiaImageData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaImageData, "C8E40ED2-A1D9-4221-8692-3CE661184B44")

.comdef IDiaImageData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_relativeVirtualAddress proc :ptr
    get_virtualAddress	proc :ptr
    get_imageBase	proc :ptr
    .ends

endif

ifndef __IDiaTable_INTERFACE_DEFINED__
__IDiaTable_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaTable, "4A59FB77-ABAC-469b-A30B-9ECC85BFEF14")

.comdef IDiaTable

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    get__NewEnum	proc :ptr
    get_name		proc :ptr
    get_Count		proc :ptr
    Item		proc :DWORD, :ptr
    .ends

endif

ifndef __IDiaEnumTables_INTERFACE_DEFINED__
__IDiaEnumTables_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumTables, "C65C2B0A-1150-4d7a-AFCC-E05BF3DEE81E")

.comdef IDiaEnumTables

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :VARIANT, :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __Dia2Lib_LIBRARY_DEFINED__
__Dia2Lib_LIBRARY_DEFINED__ equ 1

externdef		LIBID_Dia2Lib:IID
DEFINE_GUIDS(CLSID_DiaSource,	   "e6756135-1e65-4d17-8576-610761398c3c")
DEFINE_GUIDS(CLSID_DiaSourceAlt,   "91904831-49ca-4766-b95c-25397e2dd6dc")
DEFINE_GUIDS(CLSID_DiaStackWalker, "ce4a85db-5768-475b-a4e1-c0bca2112a6b")
endif

DiaTable_Symbols	equ <L"Symbols">
DiaTable_Sections	equ <L"Sections">
DiaTable_SrcFiles	equ <L"SourceFiles">
DiaTable_LineNums	equ <L"LineNumbers">
DiaTable_SegMap		equ <L"SegmentMap">
DiaTable_Dbg		equ <L"Dbg">
DiaTable_InjSrc		equ <L"InjectedSource">
DiaTable_FrameData	equ <L"FrameData">
DiaTable_InputAssemblyFiles equ <L"InputAssemblyFiles">

ifndef __IDiaPropertyStorage_INTERFACE_DEFINED__
__IDiaPropertyStorage_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaPropertyStorage, "9d416f9c-e184-45b2-a4f0-ce517f719e9b")

.comdef IDiaPropertyStorage

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ReadMultiple	proc :ULONG, :ptr, :ptr
    ReadPropertyNames	proc :ULONG, :ptr, :ptr
    Enum		proc :ptr
    ReadDWORD		proc :PROPID, :ptr
    ReadLONG		proc :PROPID, :ptr
    ReadBOOL		proc :PROPID, :ptr
    ReadULONGLONG	proc :PROPID, :ptr
    ReadBSTR		proc :PROPID, :ptr
    .ends

endif

ifndef __IDiaStackFrame_INTERFACE_DEFINED__
__IDiaStackFrame_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaStackFrame, "5edbc96d-cdd6-4792-afbe-cc89007d9610")

.comdef IDiaStackFrame

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_type		proc :ptr
    get_base		proc :ptr
    get_size		proc :ptr
    get_returnAddress	proc :ptr
    get_localsBase	proc :ptr
    get_lengthLocals	proc :ptr
    get_lengthParams	proc :ptr
    get_lengthProlog	proc :ptr
    get_lengthSavedRegisters proc :ptr
    get_systemExceptionHandling proc :ptr
    get_cplusplusExceptionHandling proc :ptr
    get_functionStart	proc :ptr
    get_allocatesBasePointer proc :ptr
    get_maxStack	proc :ptr
    get_registerValue	proc :DWORD, :ptr
    .ends

endif

ifndef __IDiaEnumStackFrames_INTERFACE_DEFINED__
__IDiaEnumStackFrames_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaEnumStackFrames, "ec9d461d-ce74-4711-a020-7d8f9a1dd255")

.comdef IDiaEnumStackFrames

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Reset		proc
    .ends

endif

FPODATA			STRUC
ulOffStart		dd ?
cbProcSize		dd ?
cdwLocals		dd ?
cdwParams		dw ?
cdwFlags		dw ?
FPODATA			ENDS

ifndef __IDiaStackWalkHelper_INTERFACE_DEFINED__
__IDiaStackWalkHelper_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaStackWalkHelper, "21F81B1B-C5BB-42A3-BC4F-CCBAA75B9F19")

.comdef IDiaStackWalkHelper

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_registerValue	proc :DWORD, :ptr
    put_registerValue	proc :DWORD, :ULONGLONG
    readMemory		proc :MemoryTypeEnum, :ULONGLONG, :DWORD, :ptr, :ptr
    searchForReturnAddress proc :ptr, :ptr
    searchForReturnAddressStart proc :ptr, :ULONGLONG, :ptr
    frameForVA		proc :ULONGLONG, :ptr
    symbolForVA		proc :ULONGLONG, :ptr
    pdataForVA		proc :ULONGLONG, :DWORD, :ptr, :ptr
    imageForVA		proc :ULONGLONG, :ptr
    addressForVA	proc :ULONGLONG, :ptr, :ptr
    numberOfFunctionFragmentsForVA proc :ULONGLONG, :DWORD, :ptr
    functionFragmentsForVA proc :ULONGLONG, :DWORD, :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IDiaStackWalker_INTERFACE_DEFINED__
__IDiaStackWalker_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaStackWalker, "5485216b-a54c-469f-9670-52b24d5229bb")

.comdef IDiaStackWalker

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    getEnumFrames	proc :ptr, :ptr
    getEnumFrames2	proc :CV_CPU_TYPE_e, :ptr, :ptr
    .ends

endif

ifndef __IDiaStackWalkHelper2_INTERFACE_DEFINED__
__IDiaStackWalkHelper2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaStackWalkHelper2, "8222c490-507b-4bef-b3bd-41dca7b5934c")

.comdef IDiaStackWalkHelper2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_registerValue	proc :DWORD, :ptr
    put_registerValue	proc :DWORD, :ULONGLONG
    readMemory		proc :MemoryTypeEnum, :ULONGLONG, :DWORD, :ptr, :ptr
    searchForReturnAddress proc :ptr, :ptr
    searchForReturnAddressStart proc :ptr, :ULONGLONG, :ptr
    frameForVA		proc :ULONGLONG, :ptr
    symbolForVA		proc :ULONGLONG, :ptr
    pdataForVA		proc :ULONGLONG, :DWORD, :ptr, :ptr
    imageForVA		proc :ULONGLONG, :ptr
    addressForVA	proc :ULONGLONG, :ptr, :ptr
    numberOfFunctionFragmentsForVA proc :ULONGLONG, :DWORD, :ptr
    functionFragmentsForVA proc :ULONGLONG, :DWORD, :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IDiaStackWalker2_INTERFACE_DEFINED__
__IDiaStackWalker2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDiaStackWalker2, "7c185885-a015-4cac-9411-0f4fb39b1f3a")

.comdef IDiaStackWalker2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    getEnumFrames	proc :ptr, :ptr
    getEnumFrames2	proc :CV_CPU_TYPE_e, :ptr, :ptr
    .ends

endif

endif
