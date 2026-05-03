ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __msdasc_h__
define __msdasc_h__
ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include oledb.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifdef _WIN64
COMPATIBLE_LONG typedef LONGLONG
else
COMPATIBLE_LONG typedef LONG
endif

.enum tagEBindInfoOptions {
    BIO_BINDER	= 0x1
    }

STGM_COLLECTION		equ 0x00002000
STGM_OUTPUT		equ 0x00008000
STGM_OPEN		equ 0x80000000
STGM_RECURSIVE		equ 0x01000000
STGM_STRICTOPEN		equ 0x40000000

ifndef __IService_INTERFACE_DEFINED__
define __IService_INTERFACE_DEFINED__

DEFINE_IIDX(IService, "06210E88-01F5-11D1-B512-0080C781C384")

.comdef IService : public IUnknown

    InvokeService	proc :ptr
   .ends

endif

DBPROMPTOPTIONS typedef DWORD

.enum DBPROMPTOPTIONSENUM {
    DBPROMPTOPTIONS_NONE	= 0,
    DBPROMPTOPTIONS_WIZARDSHEET = 0x1,
    DBPROMPTOPTIONS_PROPERTYSHEET = 0x2,
    DBPROMPTOPTIONS_BROWSEONLY	= 0x8,
    DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION = 0x10,
    DBPROMPTOPTIONS_DISABLESAVEPASSWORD = 0x20
    }


ifndef __IDBPromptInitialize_INTERFACE_DEFINED__
define __IDBPromptInitialize_INTERFACE_DEFINED__

DEFINE_IIDX(IDBPromptInitialize, "2206CCB0-19C1-11D1-89E0-00C04FD7A829")

.comdef IDBPromptInitialize : public IUnknown

    PromptDataSource	proc :ptr, :HWND, :DBPROMPTOPTIONS, :ULONG, :ptr, :LPCOLESTR, :REFIID, :ptr
    PromptFileName	proc :HWND, :DBPROMPTOPTIONS, :LPCOLESTR, :LPCOLESTR, :ptr
   .ends

endif

ifndef __IDataInitialize_INTERFACE_DEFINED__
define __IDataInitialize_INTERFACE_DEFINED__

DEFINE_IIDX(IDataInitialize, "2206CCB1-19C1-11D1-89E0-00C04FD7A829")

.comdef IDataInitialize : public IUnknown

    GetDataSource	proc :ptr, :DWORD, :LPCOLESTR, :REFIID, :ptr
    GetInitializationString proc :ptr, :BOOL, :ptr
    CreateDBInstance	proc :REFCLSID, :ptr, :DWORD, :LPOLESTR, :REFIID, :ptr
    CreateDBInstanceEx	proc :REFCLSID, :ptr, :DWORD, :LPOLESTR, :ptr, :ULONG, :ptr
    LoadStringFromStorage proc :LPCOLESTR, :ptr
    WriteStringToStorage proc :LPCOLESTR, :LPCOLESTR, :DWORD
   .ends

endif

ifndef __MSDASC_LIBRARY_DEFINED__
define __MSDASC_LIBRARY_DEFINED__

externdef LIBID_MSDASC:IID

ifndef __IDataSourceLocator_INTERFACE_DEFINED__
define __IDataSourceLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IDataSourceLocator, "2206CCB2-19C1-11D1-89E0-00C04FD7A829")

.comdef IDataSourceLocator : public IDispatch

    get_hWnd		proc :ptr
    put_hWnd		proc :COMPATIBLE_LONG
    PromptNew		proc :ptr
    PromptEdit		proc :ptr, :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_DataLinks, "2206CDB2-19C1-11D1-89E0-00C04FD7A829")
DEFINE_GUIDS(CLSID_MSDAINITIALIZE, "2206CDB0-19C1-11D1-89E0-00C04FD7A829")
DEFINE_GUIDS(CLSID_PDPO, "CCB4EC60-B9DC-11D1-AC80-00A0C9034873")
DEFINE_GUIDS(CLSID_RootBinder, "FF151822-B0BF-11D1-A80D-000000000000")

endif ;; __MSDASC_LIBRARY_DEFINED__
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
