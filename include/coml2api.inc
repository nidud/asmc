ifndef _COML2API_H_
define _COML2API_H_

include apiset.inc
include apisetcconv.inc

include combaseapi.inc
include objidl.inc
include propidlbase.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_GAMES)

define CWCSTORAGENAME 32

define STGM_DIRECT             0x00000000
define STGM_TRANSACTED         0x00010000
define STGM_SIMPLE             0x08000000

define STGM_READ               0x00000000
define STGM_WRITE              0x00000001
define STGM_READWRITE          0x00000002

define STGM_SHARE_DENY_NONE    0x00000040
define STGM_SHARE_DENY_READ    0x00000030
define STGM_SHARE_DENY_WRITE   0x00000020
define STGM_SHARE_EXCLUSIVE    0x00000010

define STGM_PRIORITY           0x00040000
define STGM_DELETEONRELEASE    0x04000000
if (WINVER ge 400)
define STGM_NOSCRATCH          0x00100000
endif

define STGM_CREATE             0x00001000
define STGM_CONVERT            0x00020000
define STGM_FAILIFTHERE        0x00000000

define STGM_NOSNAPSHOT         0x00200000
if (_WIN32_WINNT ge 0x0500)
define STGM_DIRECT_SWMR        0x00400000
endif

STGFMT typedef DWORD

define STGFMT_STORAGE          0
define STGFMT_NATIVE           1
define STGFMT_FILE             3
define STGFMT_ANY              4
define STGFMT_DOCFILE          5

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

define STGFMT_DOCUMENT         0

StgCreateDocfile proto WINAPI :ptr, :DWORD, :DWORD, :ptr ptr
StgCreateDocfileOnILockBytes proto WINAPI :ptr, :DWORD, :DWORD, :ptr ptr
StgOpenStorage proto WINAPI :ptr, :ptr, :DWORD, :SNB, :DWORD, :ptr ptr
StgOpenStorageOnILockBytes proto WINAPI :ptr, :ptr, :DWORD, :SNB, :DWORD, :ptr ptr
StgIsStorageFile proto WINAPI :ptr
StgIsStorageILockBytes proto WINAPI :ptr
StgSetTimes proto WINAPI :ptr, :ptr, :ptr, :ptr

if _WIN32_WINNT eq 0x500
define STGOPTIONS_VERSION 1
elseif _WIN32_WINNT gt 0x500
define STGOPTIONS_VERSION 2
else
define STGOPTIONS_VERSION 0
endif

tagSTGOPTIONS           struct
usVersion               USHORT ?
reserved                USHORT ?
ulSectorSize            ULONG ?
if STGOPTIONS_VERSION ge 2
pwcsTemplateFile        ptr WCHAR ?
endif
tagSTGOPTIONS           ends
STGOPTIONS              typedef tagSTGOPTIONS

StgCreateStorageEx proto WINAPI :ptr, :DWORD, :DWORD, :DWORD, :ptr, :PSECURITY_DESCRIPTOR, :REFIID, :ptr ptr
StgOpenStorageEx proto WINAPI :ptr, :DWORD, :DWORD, :DWORD, :ptr, :PSECURITY_DESCRIPTOR, :REFIID, :ptr ptr

ifndef _STGCREATEPROPSTG_DEFINED_

StgCreatePropStg proto WINAPI :ptr, :REFFMTID, :ptr, :DWORD, :DWORD, :ptr ptr
StgOpenPropStg proto WINAPI :ptr, :REFFMTID, :DWORD, :DWORD, :ptr ptr
StgCreatePropSetStg proto WINAPI :ptr, :DWORD, :ptr ptr

define CCH_MAX_PROPSTG_NAME    31

FmtIdToPropStgName proto WINAPI :ptr, :LPOLESTR
PropStgNameToFmtId proto WINAPI :LPOLESTR, :ptr

endif

ReadClassStg proto WINAPI :LPSTORAGE, :ptr
WriteClassStg proto WINAPI :LPSTORAGE, :REFCLSID
ReadClassStm proto WINAPI :LPSTREAM, :ptr
WriteClassStm proto WINAPI :LPSTREAM, :REFCLSID
GetHGlobalFromILockBytes proto WINAPI :LPLOCKBYTES, :ptr
CreateILockBytesOnHGlobal proto WINAPI :HGLOBAL, :BOOL, :ptr
GetConvertStg proto WINAPI :LPSTORAGE

endif

endif
