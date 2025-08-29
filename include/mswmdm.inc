ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __mswmdm_h__
define __mswmdm_h__

include oaidl.inc
include ocidl.inc
include propidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef _DEFINE_WMDM_DEVICE_PROTOCOL_MTP
define _DEFINE_WMDM_DEVICE_PROTOCOL_MTP
DEFINE_GUID(WMDM_DEVICE_PROTOCOL_MTP, 0x979e54e5, 0xafc, 0x4604, 0x8d, 0x93, 0xdc, 0x79, 0x8a, 0x4b, 0xcf, 0x45)
endif
ifndef _DEFINE_WMDM_DEVICE_PROTOCOL_RAPI
define _DEFINE_WMDM_DEVICE_PROTOCOL_RAPI
DEFINE_GUID(WMDM_DEVICE_PROTOCOL_RAPI, 0x2a11ed91, 0x8c8f, 0x41e4, 0x82, 0xd1, 0x83, 0x86, 0xe0, 0x3, 0x56, 0x1c)
endif
ifndef _DEFINE_WMDM_DEVICE_PROTOCOL_MSC
define _DEFINE_WMDM_DEVICE_PROTOCOL_MSC
DEFINE_GUID(WMDM_DEVICE_PROTOCOL_MSC, 0xa4d2c26c, 0xa881, 0x44bb, 0xbd, 0x5d, 0x1f, 0x70, 0x3c, 0x71, 0xf7, 0xa9)
endif
ifndef _DEFINE_WMDM_SERVICE_PROVIDER_VENDOR_MICROSOFT
define _DEFINE_WMDM_SERVICE_PROVIDER_VENDOR_MICROSOFT
DEFINE_GUID(WMDM_SERVICE_PROVIDER_VENDOR_MICROSOFT, 0x7de8686d, 0x78ee, 0x43ea, 0xa4, 0x96, 0xc6, 0x25, 0xac, 0x91, 0xcc, 0x5d)
endif

.enum WMDM_TAG_DATATYPE {
	WMDM_TYPE_DWORD,
	WMDM_TYPE_STRING,
	WMDM_TYPE_BINARY,
	WMDM_TYPE_BOOL,
	WMDM_TYPE_QWORD,
	WMDM_TYPE_WORD,
	WMDM_TYPE_GUID,
	WMDM_TYPE_DATE
	}

.enum WMDM_SESSION_TYPE {
	WMDM_SESSION_NONE	= 0,
	WMDM_SESSION_TRANSFER_TO_DEVICE = 0x1,
	WMDM_SESSION_TRANSFER_FROM_DEVICE = 0x10,
	WMDM_SESSION_DELETE	= 0x100,
	WMDM_SESSION_CUSTOM	= 0x1000
	}

_WAVEFORMATEX		struct
wFormatTag		WORD ?
nChannels		WORD ?
nSamplesPerSec		DWORD ?
nAvgBytesPerSec		DWORD ?
nBlockAlign		WORD ?
wBitsPerSample		WORD ?
cbSize			WORD ?
_WAVEFORMATEX		ends

_BITMAPINFOHEADER	struct
biSize			DWORD ?
biWidth			LONG ?
biHeight		LONG ?
biPlanes		WORD ?
biBitCount		WORD ?
biCompression		DWORD ?
biSizeImage		DWORD ?
biXPelsPerMeter		LONG ?
biYPelsPerMeter		LONG ?
biClrUsed		DWORD ?
biClrImportant		DWORD ?
_BITMAPINFOHEADER	ends

_VIDEOINFOHEADER	struct
rcSource		RECT <>
rcTarget		RECT <>
dwBitRate		DWORD ?
dwBitErrorRate		DWORD ?
AvgTimePerFrame		LONGLONG ?
bmiHeader		_BITMAPINFOHEADER <>
_VIDEOINFOHEADER	ends

WMFILECAPABILITIES	struct
pwszMimeType		LPWSTR ?
dwReserved		DWORD ?
WMFILECAPABILITIES	ends

OPAQUECOMMAND		struct
guidCommand		GUID <>
dwDataLen		DWORD ?
pData			ptr BYTE ?
abMAC			BYTE 20 dup(?)
OPAQUECOMMAND		ends

define WMDMID_LENGTH	128

WMDMID			struct
cbSize			UINT ?
dwVendorID		DWORD ?
pID			BYTE 128 dup(?)
SerialNumberLength	UINT ?
WMDMID			ends
PWMDMID			typedef ptr WMDMID

WMDMDATETIME		struct
wYear			WORD ?
wMonth			WORD ?
wDay			WORD ?
wHour			WORD ?
wMinute			WORD ?
wSecond			WORD ?
WMDMDATETIME		ends
PWMDMDATETIME		typedef ptr WMDMDATETIME

WMDMRIGHTS		struct
cbSize			UINT ?
dwContentType		DWORD ?
fuFlags			DWORD ?
fuRights		DWORD ?
dwAppSec		DWORD ?
dwPlaybackCount		DWORD ?
ExpirationDate		WMDMDATETIME <>
WMDMRIGHTS		ends
PWMDMRIGHTS		typedef ptr WMDMRIGHTS

WMDMMetadataView	struct
pwszViewName		ptr WCHAR ?
nDepth			UINT ?
ppwszTags		ptr WCHAR ?
WMDMMetadataView	ends

.enum WMDM_STORAGE_ENUM_MODE {
	ENUM_MODE_RAW,
	ENUM_MODE_USE_DEVICE_PREF,
	ENUM_MODE_METADATA_VIEWS
	}

.enum WMDM_FORMATCODE {
	WMDM_FORMATCODE_NOTUSED		= 0,
	WMDM_FORMATCODE_ALLIMAGES	= 0xffffffff,
	WMDM_FORMATCODE_UNDEFINED	= 0x3000,
	WMDM_FORMATCODE_ASSOCIATION	= 0x3001,
	WMDM_FORMATCODE_SCRIPT		= 0x3002,
	WMDM_FORMATCODE_EXECUTABLE	= 0x3003,
	WMDM_FORMATCODE_TEXT		= 0x3004,
	WMDM_FORMATCODE_HTML		= 0x3005,
	WMDM_FORMATCODE_DPOF		= 0x3006,
	WMDM_FORMATCODE_AIFF		= 0x3007,
	WMDM_FORMATCODE_WAVE		= 0x3008,
	WMDM_FORMATCODE_MP3		= 0x3009,
	WMDM_FORMATCODE_AVI		= 0x300a,
	WMDM_FORMATCODE_MPEG		= 0x300b,
	WMDM_FORMATCODE_ASF		= 0x300c,
	WMDM_FORMATCODE_RESERVED_FIRST	= 0x300d,
	WMDM_FORMATCODE_RESERVED_LAST	= 0x37ff,
	WMDM_FORMATCODE_IMAGE_UNDEFINED = 0x3800,
	WMDM_FORMATCODE_IMAGE_EXIF	= 0x3801,
	WMDM_FORMATCODE_IMAGE_TIFFEP	= 0x3802,
	WMDM_FORMATCODE_IMAGE_FLASHPIX	= 0x3803,
	WMDM_FORMATCODE_IMAGE_BMP	= 0x3804,
	WMDM_FORMATCODE_IMAGE_CIFF	= 0x3805,
	WMDM_FORMATCODE_IMAGE_GIF	= 0x3807,
	WMDM_FORMATCODE_IMAGE_JFIF	= 0x3808,
	WMDM_FORMATCODE_IMAGE_PCD	= 0x3809,
	WMDM_FORMATCODE_IMAGE_PICT	= 0x380a,
	WMDM_FORMATCODE_IMAGE_PNG	= 0x380b,
	WMDM_FORMATCODE_IMAGE_TIFF	= 0x380d,
	WMDM_FORMATCODE_IMAGE_TIFFIT	= 0x380e,
	WMDM_FORMATCODE_IMAGE_JP2	= 0x380f,
	WMDM_FORMATCODE_IMAGE_JPX	= 0x3810,
	WMDM_FORMATCODE_IMAGE_RESERVED_FIRST	= 0x3811,
	WMDM_FORMATCODE_IMAGE_RESERVED_LAST	= 0x3fff,
	WMDM_FORMATCODE_UNDEFINEDFIRMWARE	= 0xb802,
	WMDM_FORMATCODE_WBMP		= 0xb803,
	WMDM_FORMATCODE_JPEGXR		= 0xb804,
	WMDM_FORMATCODE_WINDOWSIMAGEFORMAT	= 0xb881,
	WMDM_FORMATCODE_UNDEFINEDAUDIO	= 0xb900,
	WMDM_FORMATCODE_WMA		= 0xb901,
	WMDM_FORMATCODE_OGG		= 0xb902,
	WMDM_FORMATCODE_AAC		= 0xb903,
	WMDM_FORMATCODE_AUDIBLE		= 0xb904,
	WMDM_FORMATCODE_FLAC		= 0xb906,
	WMDM_FORMATCODE_QCELP		= 0xb907,
	WMDM_FORMATCODE_AMR		= 0xb908,
	WMDM_FORMATCODE_UNDEFINEDVIDEO	= 0xb980,
	WMDM_FORMATCODE_WMV		= 0xb981,
	WMDM_FORMATCODE_MP4		= 0xb982,
	WMDM_FORMATCODE_MP2		= 0xb983,
	WMDM_FORMATCODE_3GP		= 0xb984,
	WMDM_FORMATCODE_3G2		= 0xb985,
	WMDM_FORMATCODE_AVCHD		= 0xb986,
	WMDM_FORMATCODE_ATSCTS		= 0xb987,
	WMDM_FORMATCODE_DVBTS		= 0xb988,
	WMDM_FORMATCODE_MKV		= 0xb989,
	WMDM_FORMATCODE_MKA		= 0xb98a,
	WMDM_FORMATCODE_MK3D		= 0xb98b,
	WMDM_FORMATCODE_UNDEFINEDCOLLECTION	= 0xba00,
	WMDM_FORMATCODE_ABSTRACTMULTIMEDIAALBUM = 0xba01,
	WMDM_FORMATCODE_ABSTRACTIMAGEALBUM	= 0xba02,
	WMDM_FORMATCODE_ABSTRACTAUDIOALBUM	= 0xba03,
	WMDM_FORMATCODE_ABSTRACTVIDEOALBUM	= 0xba04,
	WMDM_FORMATCODE_ABSTRACTAUDIOVIDEOPLAYLIST	= 0xba05,
	WMDM_FORMATCODE_ABSTRACTCONTACTGROUP	= 0xba06,
	WMDM_FORMATCODE_ABSTRACTMESSAGEFOLDER	= 0xba07,
	WMDM_FORMATCODE_ABSTRACTCHAPTEREDPRODUCTION	= 0xba08,
	WMDM_FORMATCODE_MEDIA_CAST	= 0xba0b,
	WMDM_FORMATCODE_WPLPLAYLIST	= 0xba10,
	WMDM_FORMATCODE_M3UPLAYLIST	= 0xba11,
	WMDM_FORMATCODE_MPLPLAYLIST	= 0xba12,
	WMDM_FORMATCODE_ASXPLAYLIST	= 0xba13,
	WMDM_FORMATCODE_PLSPLAYLIST	= 0xba14,
	WMDM_FORMATCODE_UNDEFINEDDOCUMENT	= 0xba80,
	WMDM_FORMATCODE_ABSTRACTDOCUMENT	= 0xba81,
	WMDM_FORMATCODE_XMLDOCUMENT	= 0xba82,
	WMDM_FORMATCODE_MICROSOFTWORDDOCUMENT	= 0xba83,
	WMDM_FORMATCODE_MHTCOMPILEDHTMLDOCUMENT = 0xba84,
	WMDM_FORMATCODE_MICROSOFTEXCELSPREADSHEET	= 0xba85,
	WMDM_FORMATCODE_MICROSOFTPOWERPOINTDOCUMENT	= 0xba86,
	WMDM_FORMATCODE_UNDEFINEDMESSAGE	= 0xbb00,
	WMDM_FORMATCODE_ABSTRACTMESSAGE = 0xbb01,
	WMDM_FORMATCODE_UNDEFINEDCONTACT	= 0xbb80,
	WMDM_FORMATCODE_ABSTRACTCONTACT = 0xbb81,
	WMDM_FORMATCODE_VCARD2		= 0xbb82,
	WMDM_FORMATCODE_VCARD3		= 0xbb83,
	WMDM_FORMATCODE_UNDEFINEDCALENDARITEM	= 0xbe00,
	WMDM_FORMATCODE_ABSTRACTCALENDARITEM	= 0xbe01,
	WMDM_FORMATCODE_VCALENDAR1	= 0xbe02,
	WMDM_FORMATCODE_VCALENDAR2	= 0xbe03,
	WMDM_FORMATCODE_UNDEFINEDWINDOWSEXECUTABLE	= 0xbe80,
	WMDM_FORMATCODE_M4A		= 0x4d503441,
	WMDM_FORMATCODE_3GPA		= 0x33475041,
	WMDM_FORMATCODE_3G2A		= 0x33473241,
	WMDM_FORMATCODE_SECTION		= 0xbe82
	}

.enum WMDM_ENUM_PROP_VALID_VALUES_FORM {
	WMDM_ENUM_PROP_VALID_VALUES_ANY,
	WMDM_ENUM_PROP_VALID_VALUES_RANGE,
	WMDM_ENUM_PROP_VALID_VALUES_ENUM
	}

WMDM_PROP_VALUES_RANGE	struct
rangeMin		PROPVARIANT <>
rangeMax		PROPVARIANT <>
rangeStep		PROPVARIANT <>
WMDM_PROP_VALUES_RANGE	ends

WMDM_PROP_VALUES_ENUM	struct
cEnumValues		UINT ?
pValues			ptr PROPVARIANT ?
WMDM_PROP_VALUES_ENUM	ends

WMDM_PROP_DESC		struct
pwszPropName		LPWSTR ?
ValidValuesForm		WMDM_ENUM_PROP_VALID_VALUES_FORM ?
union ValidValues
 ValidValuesRange	WMDM_PROP_VALUES_RANGE <>
 EnumeratedValidValues	WMDM_PROP_VALUES_ENUM <>
ends
WMDM_PROP_DESC		ends

WMDM_PROP_CONFIG	struct
nPreference		UINT ?
nPropDesc		UINT ?
pPropDesc		ptr WMDM_PROP_DESC ?
WMDM_PROP_CONFIG	ends

WMDM_FORMAT_CAPABILITY	struct
nPropConfig		UINT ?
pConfigs		ptr WMDM_PROP_CONFIG ?
WMDM_FORMAT_CAPABILITY	ends

define	WMDM_MAC_LENGTH 8

.enum WMDM_FIND_SCOPE {
	WMDM_FIND_SCOPE_GLOBAL,
	WMDM_FIND_SCOPE_IMMEDIATE_CHILDREN
	}

define WMDM_S_NOT_ALL_PROPERTIES_APPLIED       0x00045001
define WMDM_S_NOT_ALL_PROPERTIES_RETRIEVED     0x00045002
define WMDM_E_BUSY			       0x80045000
define WMDM_E_INTERFACEDEAD		       0x80045001
define WMDM_E_INVALIDTYPE		       0x80045002
define WMDM_E_PROCESSFAILED		       0x80045003
define WMDM_E_NOTSUPPORTED		       0x80045004
define WMDM_E_NOTCERTIFIED		       0x80045005
define WMDM_E_NORIGHTS			       0x80045006
define WMDM_E_CALL_OUT_OF_SEQUENCE	       0x80045007
define WMDM_E_BUFFERTOOSMALL		       0x80045008
define WMDM_E_MOREDATA			       0x80045009
define WMDM_E_MAC_CHECK_FAILED		       0x8004500A
define WMDM_E_USER_CANCELLED		       0x8004500B
define WMDM_E_SDMI_TRIGGER		       0x8004500C
define WMDM_E_SDMI_NOMORECOPIES		       0x8004500D
define WMDM_E_REVOKED			       0x8004500E
define WMDM_E_LICENSE_NOTEXIST		       0x8004500F
define WMDM_E_INCORRECT_APPSEC		       0x80045010
define WMDM_E_INCORRECT_RIGHTS		       0x80045011
define WMDM_E_LICENSE_EXPIRED		       0x80045012
define WMDM_E_CANTOPEN_PMSN_SERVICE_PIPE       0x80045013
define WMDM_E_TOO_MANY_SESSIONS		       0x80045013
define WMDM_WMDM_REVOKED		       0x00000001
define WMDM_APP_REVOKED			       0x00000002
define WMDM_SP_REVOKED			       0x00000004
define WMDM_SCP_REVOKED			       0x00000008
define WMDM_GET_FORMAT_SUPPORT_AUDIO	       0x00000001
define WMDM_GET_FORMAT_SUPPORT_VIDEO	       0x00000002
define WMDM_GET_FORMAT_SUPPORT_FILE	       0x00000004
define WMDM_RIGHTS_PLAYBACKCOUNT	       0x00000001
define WMDM_RIGHTS_EXPIRATIONDATE	       0x00000002
define WMDM_RIGHTS_GROUPID		       0x00000004
define WMDM_RIGHTS_FREESERIALIDS	       0x00000008
define WMDM_RIGHTS_NAMEDSERIALIDS	       0x00000010
define WMDM_DEVICE_TYPE_PLAYBACK	       0x00000001
define WMDM_DEVICE_TYPE_RECORD		       0x00000002
define WMDM_DEVICE_TYPE_DECODE		       0x00000004
define WMDM_DEVICE_TYPE_ENCODE		       0x00000008
define WMDM_DEVICE_TYPE_STORAGE		       0x00000010
define WMDM_DEVICE_TYPE_VIRTUAL		       0x00000020
define WMDM_DEVICE_TYPE_SDMI		       0x00000040
define WMDM_DEVICE_TYPE_NONSDMI		       0x00000080
define WMDM_DEVICE_TYPE_NONREENTRANT	       0x00000100
define WMDM_DEVICE_TYPE_FILELISTRESYNC	       0x00000200
define WMDM_DEVICE_TYPE_VIEW_PREF_METADATAVIEW 0x00000400
define WMDM_POWER_CAP_BATTERY		       0x00000001
define WMDM_POWER_CAP_EXTERNAL		       0x00000002
define WMDM_POWER_IS_BATTERY		       0x00000004
define WMDM_POWER_IS_EXTERNAL		       0x00000008
define WMDM_POWER_PERCENT_AVAILABLE	       0x00000010
define WMDM_STATUS_READY		       0x00000001
define WMDM_STATUS_BUSY			       0x00000002
define WMDM_STATUS_DEVICE_NOTPRESENT	       0x00000004
define WMDM_STATUS_DEVICECONTROL_PLAYING       0x00000008
define WMDM_STATUS_DEVICECONTROL_RECORDING     0x00000010
define WMDM_STATUS_DEVICECONTROL_PAUSED	       0x00000020
define WMDM_STATUS_DEVICECONTROL_REMOTE	       0x00000040
define WMDM_STATUS_DEVICECONTROL_STREAM	       0x00000080
define WMDM_STATUS_STORAGE_NOTPRESENT	       0x00000100
define WMDM_STATUS_STORAGE_INITIALIZING	       0x00000200
define WMDM_STATUS_STORAGE_BROKEN	       0x00000400
define WMDM_STATUS_STORAGE_NOTSUPPORTED	       0x00000800
define WMDM_STATUS_STORAGE_UNFORMATTED	       0x00001000
define WMDM_STATUS_STORAGECONTROL_INSERTING    0x00002000
define WMDM_STATUS_STORAGECONTROL_DELETING     0x00004000
define WMDM_STATUS_STORAGECONTROL_APPENDING    0x00008000
define WMDM_STATUS_STORAGECONTROL_MOVING       0x00010000
define WMDM_STATUS_STORAGECONTROL_READING      0x00020000
define WMDM_DEVICECAP_CANPLAY		       0x00000001
define WMDM_DEVICECAP_CANSTREAMPLAY	       0x00000002
define WMDM_DEVICECAP_CANRECORD		       0x00000004
define WMDM_DEVICECAP_CANSTREAMRECORD	       0x00000008
define WMDM_DEVICECAP_CANPAUSE		       0x00000010
define WMDM_DEVICECAP_CANRESUME		       0x00000020
define WMDM_DEVICECAP_CANSTOP		       0x00000040
define WMDM_DEVICECAP_CANSEEK		       0x00000080
define WMDM_DEVICECAP_HASSECURECLOCK	       0x00000100
define WMDM_SEEK_REMOTECONTROL		       0x00000001
define WMDM_SEEK_STREAMINGAUDIO		       0x00000002
define WMDM_STORAGE_ATTR_FILESYSTEM	       0x00000001
define WMDM_STORAGE_ATTR_REMOVABLE	       0x00000002
define WMDM_STORAGE_ATTR_NONREMOVABLE	       0x00000004
define WMDM_FILE_ATTR_FOLDER		       0x00000008
define WMDM_FILE_ATTR_LINK		       0x00000010
define WMDM_FILE_ATTR_FILE		       0x00000020
define WMDM_FILE_ATTR_VIDEO		       0x00000040
define WMDM_STORAGE_ATTR_CANEDITMETADATA       0x00000080
define WMDM_STORAGE_ATTR_FOLDERS	       0x00000100
define WMDM_FILE_ATTR_AUDIO		       0x00001000
define WMDM_FILE_ATTR_DATA		       0x00002000
define WMDM_FILE_ATTR_CANPLAY		       0x00004000
define WMDM_FILE_ATTR_CANDELETE		       0x00008000
define WMDM_FILE_ATTR_CANMOVE		       0x00010000
define WMDM_FILE_ATTR_CANRENAME		       0x00020000
define WMDM_FILE_ATTR_CANREAD		       0x00040000
define WMDM_FILE_ATTR_MUSIC		       0x00080000
define WMDM_FILE_CREATE_OVERWRITE	       0x00100000
define WMDM_FILE_ATTR_AUDIOBOOK		       0x00200000
define WMDM_FILE_ATTR_HIDDEN		       0x00400000
define WMDM_FILE_ATTR_SYSTEM		       0x00800000
define WMDM_FILE_ATTR_READONLY		       0x01000000
define WMDM_STORAGE_ATTR_HAS_FOLDERS	       0x02000000
define WMDM_STORAGE_ATTR_HAS_FILES	       0x04000000
define WMDM_STORAGE_IS_DEFAULT		       0x08000000
define WMDM_STORAGE_CONTAINS_DEFAULT	       0x10000000
define WMDM_STORAGE_ATTR_VIRTUAL	       0x20000000
define WMDM_STORAGECAP_FOLDERSINROOT	       0x00000001
define WMDM_STORAGECAP_FILESINROOT	       0x00000002
define WMDM_STORAGECAP_FOLDERSINFOLDERS	       0x00000004
define WMDM_STORAGECAP_FILESINFOLDERS	       0x00000008
define WMDM_STORAGECAP_FOLDERLIMITEXISTS       0x00000010
define WMDM_STORAGECAP_FILELIMITEXISTS	       0x00000020
define WMDM_STORAGECAP_NOT_INITIALIZABLE       0x00000040
define WMDM_MODE_BLOCK			       0x00000001
define WMDM_MODE_THREAD			       0x00000002
define WMDM_CONTENT_FILE		       0x00000004
define WMDM_CONTENT_FOLDER		       0x00000008
define WMDM_CONTENT_OPERATIONINTERFACE	       0x00000010
define WMDM_MODE_QUERY			       0x00000020
define WMDM_MODE_PROGRESS		       0x00000040
define WMDM_MODE_TRANSFER_PROTECTED	       0x00000080
define WMDM_MODE_TRANSFER_UNPROTECTED	       0x00000100
define WMDM_STORAGECONTROL_INSERTBEFORE	       0x00000200
define WMDM_STORAGECONTROL_INSERTAFTER	       0x00000400
define WMDM_STORAGECONTROL_INSERTINTO	       0x00000800
define WMDM_MODE_RECURSIVE		       0x00001000
define WMDM_RIGHTS_PLAY_ON_PC		       0x00000001
define WMDM_RIGHTS_COPY_TO_NON_SDMI_DEVICE     0x00000002
define WMDM_RIGHTS_COPY_TO_CD		       0x00000008
define WMDM_RIGHTS_COPY_TO_SDMI_DEVICE	       0x00000010
define WMDM_SEEK_BEGIN			       0x00000001
define WMDM_SEEK_CURRENT		       0x00000002
define WMDM_SEEK_END			       0x00000008
define DO_NOT_VIRTUALIZE_STORAGES_AS_DEVICES   0x00000001
define ALLOW_OUTOFBAND_NOTIFICATION	       0x00000002

.enum WMDMMessage {
	WMDM_MSG_DEVICE_ARRIVAL,
	WMDM_MSG_DEVICE_REMOVAL,
	WMDM_MSG_MEDIA_ARRIVAL,
	WMDM_MSG_MEDIA_REMOVAL
	}

ifndef __IWMDMMetaData_INTERFACE_DEFINED__
define __IWMDMMetaData_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMMetaData, "EC3B0663-0951-460a-9A80-0DCEED3C043C")

.comdef IWMDMMetaData : public IUnknown
    AddItem		proc :WMDM_TAG_DATATYPE, :LPCWSTR, :ptr, :UINT
    QueryByName		proc :LPCWSTR, :ptr, :ptr ptr, :ptr
    QueryByIndex	proc :UINT, :ptr ptr, :ptr, :ptr ptr, :ptr
    GetItemCount	proc :ptr
   .ends

endif

ifndef __IWMDeviceManager_INTERFACE_DEFINED__
define __IWMDeviceManager_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDeviceManager, "1DCB3A00-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDeviceManager : public IUnknown
    GetRevision		proc :ptr
    GetDeviceCount	proc :ptr
    EnumDevices		proc :ptr ptr
   .ends

endif

ifndef __IWMDeviceManager2_INTERFACE_DEFINED__
define __IWMDeviceManager2_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDeviceManager2, "923E5249-8731-4c5b-9B1C-B8B60B6E46AF")

.comdef IWMDeviceManager2 : public IWMDeviceManager
    GetDeviceFromCanonicalName proc :LPCWSTR, :ptr ptr
    EnumDevices2	proc :ptr ptr
    Reinitialize	proc
   .ends

endif

ifndef __IWMDeviceManager3_INTERFACE_DEFINED__
define __IWMDeviceManager3_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDeviceManager3, "af185c41-100d-46ed-be2e-9ce8c44594ef")

.comdef IWMDeviceManager3 : public IWMDeviceManager2
    SetDeviceEnumPreference proc :DWORD
   .ends

endif

ifndef __IWMDMStorageGlobals_INTERFACE_DEFINED__
define __IWMDMStorageGlobals_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorageGlobals, "1DCB3A07-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMStorageGlobals : public IUnknown
    GetCapabilities	proc :ptr
    GetSerialNumber	proc :PWMDMID, :ptr
    GetTotalSize	proc :ptr, :ptr
    GetTotalFree	proc :ptr, :ptr
    GetTotalBad		proc :ptr, :ptr
    GetStatus		proc :ptr
    Initialize		proc :UINT, :ptr
   .ends

endif

ifndef __IWMDMStorage_INTERFACE_DEFINED__
define __IWMDMStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorage, "1DCB3A06-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMStorage : public IUnknown
    SetAttributes	proc :DWORD, :ptr
    GetStorageGlobals	proc :ptr ptr
    GetAttributes	proc :ptr, :ptr
    GetName		proc :LPWSTR, :UINT
    GetDate		proc :PWMDMDATETIME
    GetSize		proc :ptr, :ptr
    GetRights		proc :ptr, :ptr, :ptr
    EnumStorage		proc :ptr ptr
    SendOpaqueCommand	proc :ptr
   .ends

endif

ifndef __IWMDMStorage2_INTERFACE_DEFINED__
define __IWMDMStorage2_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorage2, "1ED5A144-5CD5-4683-9EFF-72CBDB2D9533")

.comdef IWMDMStorage2 : public IWMDMStorage
    GetStorage		proc :LPCWSTR, :ptr ptr
    SetAttributes2	proc :DWORD, :DWORD, :ptr, :ptr
    GetAttributes2	proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IWMDMStorage3_INTERFACE_DEFINED__
define __IWMDMStorage3_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorage3, "97717EEA-926A-464e-96A4-247B0216026E")

.comdef IWMDMStorage3 : public IWMDMStorage2
    GetMetadata		proc :ptr ptr
    SetMetadata		proc :ptr
    CreateEmptyMetadataObject proc :ptr ptr
    SetEnumPreference	proc :ptr, :DWORD, :ptr
   .ends

endif

ifndef __IWMDMStorage4_INTERFACE_DEFINED__
define __IWMDMStorage4_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorage4, "c225bac5-a03a-40b8-9a23-91cf478c64a6")

.comdef IWMDMStorage4 : public IWMDMStorage3
    SetReferences	proc :DWORD, :ptr ptr
    GetReferences	proc :ptr, :ptr ptr
    GetRightsWithProgress proc :ptr, :ptr, :ptr
    GetSpecifiedMetadata proc :DWORD, :ptr, :ptr ptr
    FindStorage		proc :WMDM_FIND_SCOPE, :LPCWSTR, :ptr ptr
    GetParent		proc :ptr ptr
   .ends

endif

ifndef __IWMDMOperation_INTERFACE_DEFINED__
define __IWMDMOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMOperation, "1DCB3A0B-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMOperation : public IUnknown
    BeginRead		proc
    BeginWrite		proc
    GetObjectName	proc :LPWSTR, :UINT
    SetObjectName	proc :LPWSTR, :UINT
    GetObjectAttributes proc :ptr, :ptr
    SetObjectAttributes proc :DWORD, :ptr
    GetObjectTotalSize	proc :ptr, :ptr
    SetObjectTotalSize	proc :DWORD, :DWORD
    TransferObjectData	proc :ptr, :ptr, :ptr
    _End		proc :ptr, :ptr
   .ends

endif

ifndef __IWMDMOperation2_INTERFACE_DEFINED__
define __IWMDMOperation2_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMOperation2, "33445B48-7DF7-425c-AD8F-0FC6D82F9F75")

.comdef IWMDMOperation2 : public IWMDMOperation
    SetObjectAttributes2 proc :DWORD, :DWORD, :ptr, :ptr
    GetObjectAttributes2 proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IWMDMOperation3_INTERFACE_DEFINED__
define __IWMDMOperation3_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMOperation3, "d1f9b46a-9ca8-46d8-9d0f-1ec9bae54919")

.comdef IWMDMOperation3 : public IWMDMOperation
    TransferObjectDataOnClearChannel proc :ptr, :ptr
   .ends

endif

ifndef __IWMDMProgress_INTERFACE_DEFINED__
define __IWMDMProgress_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMProgress, "1DCB3A0C-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMProgress : public IUnknown
    Begin		proc :DWORD
    Progress		proc :DWORD
    _End		proc
   .ends

endif

ifndef __IWMDMProgress2_INTERFACE_DEFINED__
define __IWMDMProgress2_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMProgress2, "3A43F550-B383-4e92-B04A-E6BBC660FEFC")

.comdef IWMDMProgress2 : public IWMDMProgress
    End2		proc :HRESULT
   .ends

endif

ifndef __IWMDMProgress3_INTERFACE_DEFINED__
define __IWMDMProgress3_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMProgress3, "21DE01CB-3BB4-4929-B21A-17AF3F80F658")

.comdef IWMDMProgress3 : public IWMDMProgress2
    Begin3		proc :GUID, :DWORD, :ptr
    Progress3		proc :GUID, :DWORD, :ptr
    End3		proc :GUID, :HRESULT, :ptr
   .ends

endif

ifndef __IWMDMDevice_INTERFACE_DEFINED__
define __IWMDMDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMDevice, "1DCB3A02-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMDevice : public IUnknown
    GetName		proc :LPWSTR, :UINT
    GetManufacturer	proc :LPWSTR, :UINT
    GetVersion		proc :ptr
    GetType		proc :ptr
    GetSerialNumber	proc :PWMDMID, :ptr
    GetPowerSource	proc :ptr, :ptr
    GetStatus		proc :ptr
    GetDeviceIcon	proc :ptr
    EnumStorage		proc :ptr ptr
    GetFormatSupport	proc :ptr ptr, :ptr, :ptr ptr, :ptr
    SendOpaqueCommand	proc :ptr
   .ends

endif

ifndef __IWMDMDevice2_INTERFACE_DEFINED__
define __IWMDMDevice2_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMDevice2, "E34F3D37-9D67-4fc1-9252-62D28B2F8B55")

.comdef IWMDMDevice2 : public IWMDMDevice
    GetStorage		proc :LPCWSTR, :ptr ptr
    GetFormatSupport2	proc :DWORD, :ptr ptr, :ptr, :ptr ptr, :ptr, :ptr ptr, :ptr
    GetSpecifyPropertyPages proc :ptr ptr, :ptr ptr, :ptr
    GetCanonicalName	proc :LPWSTR, :UINT
   .ends

endif

ifndef __IWMDMDevice3_INTERFACE_DEFINED__
define __IWMDMDevice3_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMDevice3, "6c03e4fe-05db-4dda-9e3c-06233a6d5d65")

.comdef IWMDMDevice3 : public IWMDMDevice2
    GetProperty		proc :LPCWSTR, :ptr
    SetProperty		proc :LPCWSTR, :ptr
    GetFormatCapability proc :WMDM_FORMATCODE, :ptr
    DeviceIoControl	proc :DWORD, :ptr, :DWORD, :ptr, :LPDWORD
    FindStorage		proc :WMDM_FIND_SCOPE, :LPCWSTR, :ptr ptr
   .ends

endif

ifndef __IWMDMDeviceSession_INTERFACE_DEFINED__
define __IWMDMDeviceSession_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMDeviceSession, "82af0a65-9d96-412c-83e5-3c43e4b06cc7")

.comdef IWMDMDeviceSession : public IUnknown
    BeginSession	proc :WMDM_SESSION_TYPE, :ptr, :DWORD
    EndSession		proc :WMDM_SESSION_TYPE, :ptr, :DWORD
   .ends

endif

ifndef __IWMDMEnumDevice_INTERFACE_DEFINED__
define __IWMDMEnumDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMEnumDevice, "1DCB3A01-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMEnumDevice : public IUnknown
    Next		proc :ULONG, :ptr ptr, :ptr
    Skip		proc :ULONG, :ptr
    Reset		proc
    Clone		proc :ptr ptr
   .ends

endif

ifndef __IWMDMDeviceControl_INTERFACE_DEFINED__
define __IWMDMDeviceControl_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMDeviceControl, "1DCB3A04-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMDeviceControl : public IUnknown
    GetStatus		proc :ptr
    GetCapabilities	proc :ptr
    Play		proc
    _Record		proc :ptr
    _Pause		proc
    Resume		proc
    Stop		proc
    Seek		proc :UINT, :int_t
   .ends

endif

ifndef __IWMDMEnumStorage_INTERFACE_DEFINED__
define __IWMDMEnumStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMEnumStorage, "1DCB3A05-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMEnumStorage : public IUnknown
    Next		proc :ULONG, :ptr ptr, :ptr
    Skip		proc :ULONG, :ptr
    Reset		proc
    Clone		proc :ptr ptr
   .ends

endif

ifndef __IWMDMStorageControl_INTERFACE_DEFINED__
define __IWMDMStorageControl_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorageControl, "1DCB3A08-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMStorageControl : public IUnknown
    Insert		proc :UINT, :LPWSTR, :ptr, :ptr, :ptr ptr
    Delete		proc :UINT, :ptr
    Rename		proc :UINT, :LPWSTR, :ptr
    Read		proc :UINT, :LPWSTR, :ptr, :ptr
    Move		proc :UINT, :ptr, :ptr
   .ends

endif

ifndef __IWMDMStorageControl2_INTERFACE_DEFINED__
define __IWMDMStorageControl2_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorageControl2, "972C2E88-BD6C-4125-8E09-84F837E637B6")

.comdef IWMDMStorageControl2 : public IWMDMStorageControl
    Insert2		proc :UINT, :LPWSTR, :LPWSTR, :ptr, :ptr, :ptr, :ptr ptr
   .ends

endif

ifndef __IWMDMStorageControl3_INTERFACE_DEFINED__
define __IWMDMStorageControl3_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMStorageControl3, "B3266365-D4F3-4696-8D53-BD27EC60993A")

.comdef IWMDMStorageControl3 : public IWMDMStorageControl2
    Insert3		proc :UINT, :UINT, :LPWSTR, :LPWSTR, :ptr, :ptr, :ptr, :ptr, :ptr ptr
   .ends

endif

ifndef __IWMDMObjectInfo_INTERFACE_DEFINED__
define __IWMDMObjectInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMObjectInfo, "1DCB3A09-33ED-11d3-8470-00C04F79DBC0")

.comdef IWMDMObjectInfo : public IUnknown
    GetPlayLength	proc :ptr
    SetPlayLength	proc :DWORD
    GetPlayOffset	proc :ptr
    SetPlayOffset	proc :DWORD
    GetTotalLength	proc :ptr
    GetLastPlayPosition proc :ptr
    GetLongestPlayPosition proc :ptr
   .ends

endif

ifndef __IWMDMRevoked_INTERFACE_DEFINED__
define __IWMDMRevoked_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMRevoked, "EBECCEDB-88EE-4e55-B6A4-8D9F07D696AA")

.comdef IWMDMRevoked : public IUnknown
    GetRevocationURL	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __IWMDMNotification_INTERFACE_DEFINED__
define __IWMDMNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMNotification, "3F5E95C0-0F43-4ed4-93D2-C89A45D59B81")

.comdef IWMDMNotification : public IUnknown
    WMDMMessage		proc :DWORD, :LPCWSTR
   .ends

endif

define g_wszWMDMFileName <L"WMDM/FileName">
define g_wszWMDMFormatCode <L"WMDM/FormatCode">
define g_wszWMDMLastModifiedDate <L"WMDM/LastModifiedDate">
define g_wszWMDMFileCreationDate <L"WMDM/FileCreationDate">
define g_wszWMDMFileSize <L"WMDM/FileSize">
define g_wszWMDMFileAttributes <L"WMDM/FileAttributes">
define g_wszAudioWAVECodec <L"WMDM/AudioWAVECodec">
define g_wszVideoFourCCCodec <L"WMDM/VideoFourCCCodec">
define g_wszWMDMTitle <L"WMDM/Title">
define g_wszWMDMAuthor <L"WMDM/Author">
define g_wszWMDMDescription <L"WMDM/Description">
define g_wszWMDMIsProtected <L"WMDM/IsProtected">
define g_wszWMDMAlbumTitle <L"WMDM/AlbumTitle">
define g_wszWMDMAlbumArtist <L"WMDM/AlbumArtist">
define g_wszWMDMTrack <L"WMDM/Track">
define g_wszWMDMGenre <L"WMDM/Genre">
define g_wszWMDMTrackMood <L"WMDM/TrackMood">
define g_wszWMDMAlbumCoverFormat <L"WMDM/AlbumCoverFormat">
define g_wszWMDMAlbumCoverSize <L"WMDM/AlbumCoverSize">
define g_wszWMDMAlbumCoverHeight <L"WMDM/AlbumCoverHeight">
define g_wszWMDMAlbumCoverWidth <L"WMDM/AlbumCoverWidth">
define g_wszWMDMAlbumCoverDuration <L"WMDM/AlbumCoverDuration">
define g_wszWMDMAlbumCoverData <L"WMDM/AlbumCoverData">
define g_wszWMDMYear <L"WMDM/Year">
define g_wszWMDMComposer <L"WMDM/Composer">
define g_wszWMDMCodec <L"WMDM/Codec">
define g_wszWMDMDRMId <L"WMDM/DRMId">
define g_wszWMDMBitrate <L"WMDM/Bitrate">
define g_wszWMDMBitRateType <L"WMDM/BitRateType">
define g_wszWMDMSampleRate <L"WMDM/SampleRate">
define g_wszWMDMNumChannels <L"WMDM/NumChannels">
define g_wszWMDMBlockAlignment <L"WMDM/BlockAlignment">
define g_wszWMDMAudioBitDepth <L"WMDM/AudioBitDepth">
define g_wszWMDMTotalBitrate <L"WMDM/TotalBitrate">
define g_wszWMDMVideoBitrate <L"WMDM/VideoBitrate">
define g_wszWMDMFrameRate <L"WMDM/FrameRate">
define g_wszWMDMScanType <L"WMDM/ScanType">
define g_wszWMDMKeyFrameDistance <L"WMDM/KeyFrameDistance">
define g_wszWMDMBufferSize <L"WMDM/BufferSize">
define g_wszWMDMQualitySetting <L"WMDM/QualitySetting">
define g_wszWMDMEncodingProfile <L"WMDM/EncodingProfile">
define g_wszWMDMDuration <L"WMDM/Duration">
define g_wszWMDMAlbumArt <L"WMDM/AlbumArt">
define g_wszWMDMBuyNow <L"WMDM/BuyNow">
define g_wszWMDMNonConsumable <L"WMDM/NonConsumable">
define g_wszWMDMediaClassPrimaryID <L"WMDM/MediaClassPrimaryID">
define g_wszWMDMMediaClassSecondaryID <L"WMDM/MediaClassSecondaryID">
define g_wszWMDMUserEffectiveRating <L"WMDM/UserEffectiveRating">
define g_wszWMDMUserRating <L"WMDM/UserRating">
define g_wszWMDMUserRatingOnDevice <L"WMDM/UserRatingOnDevice">
define g_wszWMDMPlayCount <L"WMDM/PlayCount">
define g_wszWMDMDevicePlayCount <L"WMDM/DevicePlayCount">
define g_wszWMDMAuthorDate <L"WMDM/AuthorDate">
define g_wszWMDMUserLastPlayTime <L"WMDM/UserLastPlayTime">
define g_wszWMDMSubTitle <L"WMDM/SubTitle">
define g_wszWMDMSubTitleDescription <L"WMDM/SubTitleDescription">
define g_wszWMDMMediaCredits <L"WMDM/MediaCredits">
define g_wszWMDMMediaStationName <L"WMDM/MediaStationName">
define g_wszWMDMMediaOriginalChannel <L"WMDM/MediaOriginalChannel">
define g_wszWMDMMediaOriginalBroadcastDateTime <L"WMDM/MediaOriginalBroadcastDateTime">
define g_wszWMDMProviderCopyright <L"WMDM/ProviderCopyright">
define g_wszWMDMSyncID <L"WMDM/SyncID">
define g_wszWMDMPersistentUniqueID <L"WMDM/PersistentUniqueID">
define g_wszWMDMWidth <L"WMDM/Width">
define g_wszWMDMHeight <L"WMDM/Height">
define g_wszWMDMSyncTime <L"WMDM/SyncTime">
define g_wszWMDMParentalRating <L"WMDM/ParentalRating">
define g_wszWMDMMetaGenre <L"WMDM/MetaGenre">
define g_wszWMDMIsRepeat <L"WMDM/IsRepeat">
define g_wszWMDMSupportedDeviceProperties <L"WMDM/SupportedDeviceProperties">
define g_wszWMDMDeviceFriendlyName <L"WMDM/DeviceFriendlyName">
define g_wszWMDMFormatsSupported <L"WMDM/FormatsSupported">
define g_wszWMDMFormatsSupportedAreOrdered <L"WMDM/FormatsSupportedAreOrdered">
define g_wszWMDMSyncRelationshipID <L"WMDM/SyncRelationshipID">
define g_wszWMDMDeviceModelName <L"WMDM/DeviceModelName">
define g_wszWMDMDeviceFirmwareVersion <L"WMDM/DeviceFirmwareVersion">
define g_wszWMDMDeviceVendorExtension <L"WMDM/DeviceVendorExtension">
define g_wszWMDMDeviceProtocol <L"WMDM/DeviceProtocol">
define g_wszWMDMDeviceServiceProviderVendor <L"WMDM/DeviceServiceProviderVendor">
define g_wszWMDMDeviceRevocationInfo <L"WMDM/DeviceRevocationInfo">
define g_wszWMDMCollectionID <L"WMDM/CollectionID">
define g_wszWMDMOwner <L"WMDM/Owner">
define g_wszWMDMEditor <L"WMDM/Editor">
define g_wszWMDMWebmaster <L"WMDM/Webmaster">
define g_wszWMDMSourceURL <L"WMDM/SourceURL">
define g_wszWMDMDestinationURL <L"WMDM/DestinationURL">
define g_wszWMDMCategory <L"WMDM/Category">
define g_wszWMDMTimeBookmark <L"WMDM/TimeBookmark">
define g_wszWMDMObjectBookmark <L"WMDM/ObjectBookmark">
define g_wszWMDMByteBookmark <L"WMDM/ByteBookmark">
define g_wszWMDMDataOffset <L"WMDM/DataOffset">
define g_wszWMDMDataLength <L"WMDM/DataLength">
define g_wszWMDMDataUnits <L"WMDM/DataUnits">
define g_wszWMDMTimeToLive <L"WMDM/TimeToLive">
define g_wszWMDMMediaGuid <L"WMDM/MediaGuid">
define g_wszWPDPassthroughPropertyValues <L"WPD/PassthroughPropertyValues">

WMDMDetermineMaxPropStringLen struct
sz001			WCHAR 36 dup(?)
WMDMDetermineMaxPropStringLen ends

define WMDM_MAXLEN_PROPERTYNAME (sizeof(WMDMDetermineMaxPropStringLen)/sizeof(WCHAR))

define MDSP_READ			       0x00000001
define MDSP_WRITE			       0x00000002
define MDSP_SEEK_BOF			       0x00000001
define MDSP_SEEK_CUR			       0x00000002
define MDSP_SEEK_EOF			       0x00000004

ifndef __IMDServiceProvider_INTERFACE_DEFINED__
define __IMDServiceProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IMDServiceProvider, "1DCB3A10-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDServiceProvider : public IUnknown
    GetDeviceCount	proc :ptr
    EnumDevices		proc :ptr ptr
   .ends

endif

ifndef __IMDServiceProvider2_INTERFACE_DEFINED__
define __IMDServiceProvider2_INTERFACE_DEFINED__

DEFINE_IIDX(IMDServiceProvider2, "B2FA24B7-CDA3-4694-9862-413AE1A34819")

.comdef IMDServiceProvider2 : public IMDServiceProvider
    CreateDevice	proc :LPCWSTR, :ptr, :ptr ptr
   .ends

endif

ifndef __IMDServiceProvider3_INTERFACE_DEFINED__
define __IMDServiceProvider3_INTERFACE_DEFINED__

DEFINE_IIDX(IMDServiceProvider3, "4ed13ef3-a971-4d19-9f51-0e1826b2da57")

.comdef IMDServiceProvider3 : public IMDServiceProvider2
    SetDeviceEnumPreference proc :DWORD
   .ends

endif

ifndef __IMDSPEnumDevice_INTERFACE_DEFINED__
define __IMDSPEnumDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPEnumDevice, "1DCB3A11-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPEnumDevice : public IUnknown
    Next		proc :ULONG, :ptr ptr, :ptr
    Skip		proc :ULONG, :ptr
    Reset		proc
    Clone		proc :ptr ptr
   .ends

endif

ifndef __IMDSPDevice_INTERFACE_DEFINED__
define __IMDSPDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPDevice, "1DCB3A12-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPDevice : public IUnknown
    GetName		proc :LPWSTR, :UINT
    GetManufacturer	proc :LPWSTR, :UINT
    GetVersion		proc :ptr
    GetType		proc :ptr
    GetSerialNumber	proc :PWMDMID, :ptr
    GetPowerSource	proc :ptr, :ptr
    GetStatus		proc :ptr
    GetDeviceIcon	proc :ptr
    EnumStorage		proc :ptr ptr
    GetFormatSupport	proc :ptr ptr, :ptr, :ptr ptr, :ptr
    SendOpaqueCommand	proc :ptr
   .ends

endif

ifndef __IMDSPDevice2_INTERFACE_DEFINED__
define __IMDSPDevice2_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPDevice2, "420D16AD-C97D-4e00-82AA-00E9F4335DDD")

.comdef IMDSPDevice2 : public IMDSPDevice
    GetStorage		proc :LPCWSTR, :ptr ptr
    GetFormatSupport2	proc :DWORD, :ptr ptr, :ptr, :ptr ptr, :ptr, :ptr ptr, :ptr
    GetSpecifyPropertyPages proc :ptr ptr, :ptr ptr, :ptr
    GetCanonicalName	proc :LPWSTR, :UINT
   .ends

endif

ifndef __IMDSPDevice3_INTERFACE_DEFINED__
define __IMDSPDevice3_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPDevice3, "1a839845-fc55-487c-976f-ee38ac0e8c4e")

.comdef IMDSPDevice3 : public IMDSPDevice2
    GetProperty		proc :LPCWSTR, :ptr
    SetProperty		proc :LPCWSTR, :ptr
    GetFormatCapability proc :WMDM_FORMATCODE, :ptr
    DeviceIoControl	proc :DWORD, :ptr, :DWORD, :ptr, :LPDWORD
    FindStorage		proc :WMDM_FIND_SCOPE, :LPCWSTR, :ptr ptr
   .ends

endif

ifndef __IMDSPDeviceControl_INTERFACE_DEFINED__
define __IMDSPDeviceControl_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPDeviceControl, "1DCB3A14-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPDeviceControl : public IUnknown
    GetDCStatus		proc :ptr
    GetCapabilities	proc :ptr
    Play		proc
    _Record		proc :ptr
    _Pause		proc
    Resume		proc
    Stop		proc
    Seek		proc :UINT, :int_t
   .ends

endif

ifndef __IMDSPEnumStorage_INTERFACE_DEFINED__
define __IMDSPEnumStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPEnumStorage, "1DCB3A15-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPEnumStorage : public IUnknown
    Next		proc :ULONG, :ptr ptr, :ptr
    Skip		proc :ULONG, :ptr
    Reset		proc
    Clone		proc :ptr ptr
   .ends

endif

ifndef __IMDSPStorage_INTERFACE_DEFINED__
define __IMDSPStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPStorage, "1DCB3A16-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPStorage : public IUnknown
    SetAttributes	proc :DWORD, :ptr
    GetStorageGlobals	proc :ptr ptr
    GetAttributes	proc :ptr, :ptr
    GetName		proc :LPWSTR, :UINT
    GetDate		proc :PWMDMDATETIME
    GetSize		proc :ptr, :ptr
    GetRights		proc :ptr, :ptr, :ptr
    CreateStorage	proc :DWORD, :ptr, :LPWSTR, :ptr ptr
    EnumStorage		proc :ptr ptr
    SendOpaqueCommand	proc :ptr
   .ends

endif

ifndef __IMDSPStorage2_INTERFACE_DEFINED__
define __IMDSPStorage2_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPStorage2, "0A5E07A5-6454-4451-9C36-1C6AE7E2B1D6")

.comdef IMDSPStorage2 : public IMDSPStorage
    GetStorage		proc :LPCWSTR, :ptr ptr
    CreateStorage2	proc :DWORD, :DWORD, :ptr, :ptr, :LPWSTR, :ULONGLONG, :ptr ptr
    SetAttributes2	proc :DWORD, :DWORD, :ptr, :ptr
    GetAttributes2	proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IMDSPStorage3_INTERFACE_DEFINED__
define __IMDSPStorage3_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPStorage3, "6C669867-97ED-4a67-9706-1C5529D2A414")

.comdef IMDSPStorage3 : public IMDSPStorage2
    GetMetadata		proc :ptr
    SetMetadata		proc :ptr
   .ends

endif

ifndef __IMDSPStorage4_INTERFACE_DEFINED__
define __IMDSPStorage4_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPStorage4, "3133b2c4-515c-481b-b1ce-39327ecb4f74")

.comdef IMDSPStorage4 : public IMDSPStorage3
    SetReferences	proc :DWORD, :ptr ptr
    GetReferences	proc :ptr, :ptr ptr
    CreateStorageWithMetadata proc :DWORD, :LPCWSTR, :ptr, :ULONGLONG, :ptr ptr
    GetSpecifiedMetadata proc :DWORD, :ptr, :ptr
    FindStorage		proc :WMDM_FIND_SCOPE, :LPCWSTR, :ptr ptr
    GetParent		proc :ptr ptr
   .ends

endif

ifndef __IMDSPStorageGlobals_INTERFACE_DEFINED__
define __IMDSPStorageGlobals_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPStorageGlobals, "1DCB3A17-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPStorageGlobals : public IUnknown
    GetCapabilities	proc :ptr
    GetSerialNumber	proc :PWMDMID, :ptr
    GetTotalSize	proc :ptr, :ptr
    GetTotalFree	proc :ptr, :ptr
    GetTotalBad		proc :ptr, :ptr
    GetStatus		proc :ptr
    Initialize		proc :UINT, :ptr
    GetDevice		proc :ptr ptr
    GetRootStorage	proc :ptr ptr
   .ends

endif

ifndef __IMDSPObjectInfo_INTERFACE_DEFINED__
define __IMDSPObjectInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPObjectInfo, "1DCB3A19-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPObjectInfo : public IUnknown
    GetPlayLength	proc :ptr
    SetPlayLength	proc :DWORD
    GetPlayOffset	proc :ptr
    SetPlayOffset	proc :DWORD
    GetTotalLength	proc :ptr
    GetLastPlayPosition proc :ptr
    GetLongestPlayPosition proc :ptr
   .ends

endif

ifndef __IMDSPObject_INTERFACE_DEFINED__
define __IMDSPObject_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPObject, "1DCB3A18-33ED-11d3-8470-00C04F79DBC0")

.comdef IMDSPObject : public IUnknown
    Open		proc :UINT
    Read		proc :ptr, :ptr, :ptr
    Write		proc :ptr, :ptr, :ptr
    Delete		proc :UINT, :ptr
    Seek		proc :UINT, :DWORD
    Rename		proc :LPWSTR, :ptr
    Move		proc :UINT, :ptr, :ptr
    Close		proc
   .ends

endif

ifndef __IMDSPObject2_INTERFACE_DEFINED__
define __IMDSPObject2_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPObject2, "3f34cd3e-5907-4341-9af9-97f4187c3aa5")

.comdef IMDSPObject2 : public IMDSPObject
    ReadOnClearChannel	proc :ptr, :ptr
    WriteOnClearChannel proc :ptr, :ptr
   .ends

endif

ifndef __IMDSPDirectTransfer_INTERFACE_DEFINED__
define __IMDSPDirectTransfer_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPDirectTransfer, "c2fe57a8-9304-478c-9ee4-47e397b912d7")

.comdef IMDSPDirectTransfer : public IUnknown
    TransferToDevice	proc :LPCWSTR, :ptr, :UINT, :LPWSTR, :ptr, :ptr, :ptr ptr
   .ends

endif

ifndef __IMDSPRevoked_INTERFACE_DEFINED__
define __IMDSPRevoked_INTERFACE_DEFINED__

DEFINE_IIDX(IMDSPRevoked, "A4E8F2D4-3F31-464d-B53D-4FC335998184")

.comdef IMDSPRevoked : public IUnknown
    GetRevocationURL	proc :ptr, :ptr
   .ends

endif

define WMDM_SCP_EXAMINE_EXTENSION		  0x00000001
define WMDM_SCP_EXAMINE_DATA			  0x00000002
define WMDM_SCP_DECIDE_DATA			  0x00000008
define WMDM_SCP_PROTECTED_OUTPUT		  0x00000010
define WMDM_SCP_UNPROTECTED_OUTPUT		  0x00000020
define WMDM_SCP_RIGHTS_DATA			  0x00000040
define WMDM_SCP_TRANSFER_OBJECTDATA		  0x00000020
define WMDM_SCP_NO_MORE_CHANGES			  0x00000040
define WMDM_SCP_DRMINFO_NOT_DRMPROTECTED	  0x00000000
define WMDM_SCP_DRMINFO_V1HEADER		  0x00000001
define WMDM_SCP_DRMINFO_V2HEADER		  0x00000002

ifndef _DEFINE_SCP_EVENTID
define _DEFINE_SCP_EVENTID
DEFINE_GUID(SCP_EVENTID_ACQSECURECLOCK, 0x86248cc9, 0x4a59, 0x43e2, 0x91, 0x46, 0x48, 0xa7, 0xf3, 0xf4, 0x14, 0xc)
DEFINE_GUID(SCP_EVENTID_NEEDTOINDIV, 0x87a507c7, 0xb469, 0x4386, 0xb9, 0x76, 0xd5, 0xd1, 0xce, 0x53, 0x8a, 0x6f)
DEFINE_GUID(SCP_EVENTID_DRMINFO, 0x213dd287, 0x41d2, 0x432b, 0x9e, 0x3f, 0x3b, 0x4f, 0x7b, 0x35, 0x81, 0xdd)
DEFINE_GUID(SCP_PARAMID_DRMVERSION, 0x41d0155d, 0x7cc7, 0x4217, 0xad, 0xa9, 0x00, 0x50, 0x74, 0x62, 0x4d, 0xa4)
endif

ifndef __ISCPSecureAuthenticate_INTERFACE_DEFINED__
define __ISCPSecureAuthenticate_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureAuthenticate, "1DCB3A0F-33ED-11d3-8470-00C04F79DBC0")

.comdef ISCPSecureAuthenticate : public IUnknown
    GetSecureQuery	proc :ptr ptr
   .ends

endif

ifndef __ISCPSecureAuthenticate2_INTERFACE_DEFINED__
define __ISCPSecureAuthenticate2_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureAuthenticate2, "B580CFAE-1672-47e2-ACAA-44BBECBCAE5B")

.comdef ISCPSecureAuthenticate2 : public ISCPSecureAuthenticate
    GetSCPSession	proc :ptr ptr
   .ends

endif

ifndef __ISCPSecureQuery_INTERFACE_DEFINED__
define __ISCPSecureQuery_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureQuery, "1DCB3A0D-33ED-11d3-8470-00C04F79DBC0")

.comdef ISCPSecureQuery : public IUnknown
    GetDataDemands	proc :ptr, :ptr, :ptr, :ptr, :ptr
    ExamineData		proc :UINT, :LPWSTR, :ptr, :DWORD, :ptr
    MakeDecision	proc :UINT, :ptr, :DWORD, :DWORD, :ptr, :DWORD, :ptr, :ptr ptr, :ptr
    GetRights		proc :ptr, :DWORD, :ptr, :DWORD, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __ISCPSecureQuery2_INTERFACE_DEFINED__
define __ISCPSecureQuery2_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureQuery2, "EBE17E25-4FD7-4632-AF46-6D93D4FCC72E")

.comdef ISCPSecureQuery2 : public ISCPSecureQuery
    MakeDecision2	proc :UINT, :ptr, :DWORD, :DWORD, :ptr, :DWORD, :ptr, :ptr, :DWORD, :ptr, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr ptr, :ptr
   .ends

endif

ifndef __ISCPSecureExchange_INTERFACE_DEFINED__
define __ISCPSecureExchange_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureExchange, "1DCB3A0E-33ED-11d3-8470-00C04F79DBC0")

.comdef ISCPSecureExchange : public IUnknown
    TransferContainerData proc :ptr, :DWORD, :ptr, :ptr
    ObjectData		proc :ptr, :ptr, :ptr
    TransferComplete	proc
   .ends

endif

ifndef __ISCPSecureExchange2_INTERFACE_DEFINED__
define __ISCPSecureExchange2_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureExchange2, "6C62FC7B-2690-483F-9D44-0A20CB35577C")

.comdef ISCPSecureExchange2 : public ISCPSecureExchange
    TransferContainerData2 proc :ptr, :DWORD, :ptr, :ptr, :ptr
   .ends

endif

ifndef __ISCPSecureExchange3_INTERFACE_DEFINED__
define __ISCPSecureExchange3_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureExchange3, "ab4e77e4-8908-4b17-bd2a-b1dbe6dd69e1")

.comdef ISCPSecureExchange3 : public ISCPSecureExchange2
    TransferContainerDataOnClearChannel proc :ptr, :ptr, :DWORD, :ptr, :ptr
    GetObjectDataOnClearChannel proc :ptr, :ptr, :ptr
    TransferCompleteForDevice proc :ptr
   .ends

endif

ifndef __ISCPSession_INTERFACE_DEFINED__
define __ISCPSession_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSession, "88a3e6ed-eee4-4619-bbb3-fd4fb62715d1")

.comdef ISCPSession : public IUnknown
    BeginSession	proc :ptr, :ptr, :DWORD
    EndSession		proc :ptr, :DWORD
    GetSecureQuery	proc :ptr ptr
   .ends

endif

ifndef __ISCPSecureQuery3_INTERFACE_DEFINED__
define __ISCPSecureQuery3_INTERFACE_DEFINED__

DEFINE_IIDX(ISCPSecureQuery3, "B7EDD1A2-4DAB-484b-B3C5-AD39B8B4C0B1")

.comdef ISCPSecureQuery3 : public ISCPSecureQuery2
    GetRightsOnClearChannel proc :ptr, :DWORD, :ptr, :DWORD, :ptr, :ptr, :ptr, :ptr
    MakeDecisionOnClearChannel proc :UINT, :ptr, :DWORD, :DWORD, :ptr, :DWORD, :ptr, :ptr, :ptr, :DWORD, :ptr, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr ptr
   .ends

endif

define SAC_MAC_LEN 8

ifndef __IComponentAuthenticate_INTERFACE_DEFINED__
define __IComponentAuthenticate_INTERFACE_DEFINED__

DEFINE_IIDX(IComponentAuthenticate, "A9889C00-6D2B-11d3-8496-00C04F79DBC0")

.comdef IComponentAuthenticate : public IUnknown
    SACAuth		proc :DWORD, :DWORD, :ptr, :DWORD, :ptr ptr, :ptr
    SACGetProtocols	proc :ptr ptr, :ptr
   .ends

endif

ifndef __MSWMDMLib_LIBRARY_DEFINED__
define __MSWMDMLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_MSWMDMLib, 0x6EC6C744,0x355F,0x11D3,0x84,0x70,0x00,0xC0,0x4F,0x79,0xDB,0xC0)

DEFINE_GUIDS(CLSID_MediaDevMgrClassFactory, "50040C1D-BDBF-4924-B873-F14D6C5BFD66")
DEFINE_GUIDS(CLSID_MediaDevMgr, "25BAAD81-3560-11D3-8471-00C04F79DBC0")
DEFINE_GUIDS(CLSID_WMDMDevice, "807B3CDF-357A-11d3-8471-00C04F79DBC0")
DEFINE_GUIDS(CLSID_WMDMStorage, "807B3CE0-357A-11d3-8471-00C04F79DBC0")
DEFINE_GUIDS(CLSID_WMDMStorageGlobal, "807B3CE1-357A-11d3-8471-00C04F79DBC0")
DEFINE_GUIDS(CLSID_WMDMDeviceEnum, "430E35AF-3971-11D3-8474-00C04F79DBC0")
DEFINE_GUIDS(CLSID_WMDMStorageEnum, "EB401A3B-3AF7-11d3-8474-00C04F79DBC0")

endif

endif

endif
