.pragma list(push, 0)

ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 475
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef __iads_h__
define __iads_h__

ifndef __ActiveDs_LIBRARY_DEFINED__
define __ActiveDs_LIBRARY_DEFINED__

ADSTYPEENUM typedef SDWORD
ADSTYPE_INVALID		equ 0
ADSTYPE_DN_STRING	equ ( ADSTYPE_INVALID + 1 )
ADSTYPE_CASE_EXACT_STRING equ ( ADSTYPE_DN_STRING + 1 )
ADSTYPE_CASE_IGNORE_STRING equ ( ADSTYPE_CASE_EXACT_STRING + 1 )
ADSTYPE_PRINTABLE_STRING equ ( ADSTYPE_CASE_IGNORE_STRING + 1 )
ADSTYPE_NUMERIC_STRING	equ ( ADSTYPE_PRINTABLE_STRING + 1 )
ADSTYPE_BOOLEAN		equ ( ADSTYPE_NUMERIC_STRING + 1 )
ADSTYPE_INTEGER		equ ( ADSTYPE_BOOLEAN + 1 )
ADSTYPE_OCTET_STRING	equ ( ADSTYPE_INTEGER + 1 )
ADSTYPE_UTC_TIME	equ ( ADSTYPE_OCTET_STRING + 1 )
ADSTYPE_LARGE_INTEGER	equ ( ADSTYPE_UTC_TIME + 1 )
ADSTYPE_PROV_SPECIFIC	equ ( ADSTYPE_LARGE_INTEGER + 1 )
ADSTYPE_OBJECT_CLASS	equ ( ADSTYPE_PROV_SPECIFIC + 1 )
ADSTYPE_CASEIGNORE_LIST equ ( ADSTYPE_OBJECT_CLASS + 1 )
ADSTYPE_OCTET_LIST	equ ( ADSTYPE_CASEIGNORE_LIST + 1 )
ADSTYPE_PATH		equ ( ADSTYPE_OCTET_LIST + 1 )
ADSTYPE_POSTALADDRESS	equ ( ADSTYPE_PATH + 1 )
ADSTYPE_TIMESTAMP	equ ( ADSTYPE_POSTALADDRESS + 1 )
ADSTYPE_BACKLINK	equ ( ADSTYPE_TIMESTAMP + 1 )
ADSTYPE_TYPEDNAME	equ ( ADSTYPE_BACKLINK + 1 )
ADSTYPE_HOLD		equ ( ADSTYPE_TYPEDNAME + 1 )
ADSTYPE_NETADDRESS	equ ( ADSTYPE_HOLD + 1 )
ADSTYPE_REPLICAPOINTER	equ ( ADSTYPE_NETADDRESS + 1 )
ADSTYPE_FAXNUMBER	equ ( ADSTYPE_REPLICAPOINTER + 1 )
ADSTYPE_EMAIL		equ ( ADSTYPE_FAXNUMBER + 1 )
ADSTYPE_NT_SECURITY_DESCRIPTOR equ ( ADSTYPE_EMAIL + 1 )
ADSTYPE_UNKNOWN		equ ( ADSTYPE_NT_SECURITY_DESCRIPTOR + 1 )
ADSTYPE_DN_WITH_BINARY	equ ( ADSTYPE_UNKNOWN + 1 )
ADSTYPE_DN_WITH_STRING	equ ( ADSTYPE_DN_WITH_BINARY + 1 )

ADSTYPE			typedef ADSTYPEENUM
LPSTRLPBYTE		typedef ptr BYTE
LPSTRPBYTE		typedef ptr BYTE
ADS_DN_STRING		typedef LPWSTR
PADS_DN_STRING		typedef ptr LPWSTR
ADS_CASE_EXACT_STRING	typedef LPWSTR
PADS_CASE_EXACT_STRING	typedef ptr LPWSTR
ADS_CASE_IGNORE_STRING	typedef LPWSTR
PADS_CASE_IGNORE_STRING typedef ptr LPWSTR
ADS_PRINTABLE_STRING	typedef LPWSTR
PADS_PRINTABLE_STRING	typedef ptr LPWSTR
ADS_NUMERIC_STRING	typedef LPWSTR
PADS_NUMERIC_STRING	typedef ptr LPWSTR
ADS_BOOLEAN		typedef DWORD
LPNDS_BOOLEAN		typedef ptr DWORD
ADS_INTEGER		typedef DWORD
PADS_INTEGER		typedef ptr DWORD

ADS_OCTET_STRING	STRUC
dwLength		DWORD ?
lpValue			LPBYTE ?
ADS_OCTET_STRING	ENDS
PADS_OCTET_STRING	typedef ptr ADS_OCTET_STRING

ADS_NT_SECURITY_DESCRIPTOR STRUC
dwLength		DWORD ?
lpValue			LPBYTE ?
ADS_NT_SECURITY_DESCRIPTOR ENDS
PADS_NT_SECURITY_DESCRIPTOR typedef ptr ADS_NT_SECURITY_DESCRIPTOR

ADS_UTC_TIME		typedef SYSTEMTIME
PADS_UTC_TIME		typedef ptr SYSTEMTIME
ADS_LARGE_INTEGER	typedef LARGE_INTEGER
PADS_LARGE_INTEGER	typedef ptr LARGE_INTEGER
ADS_OBJECT_CLASS	typedef LPWSTR
PADS_OBJECT_CLASS	typedef ptr LPWSTR

ADS_PROV_SPECIFIC	STRUC
dwLength		DWORD ?
lpValue			LPBYTE ?
ADS_PROV_SPECIFIC	ENDS
PADS_PROV_SPECIFIC	typedef ptr ADS_PROV_SPECIFIC

ADS_CASEIGNORE_LIST	STRUC
Next			PVOID ?
String			LPWSTR ?
ADS_CASEIGNORE_LIST	ENDS
PADS_CASEIGNORE_LIST	typedef ptr ADS_CASEIGNORE_LIST

ADS_OCTET_LIST		STRUC
Next			PVOID ?
Length			dd ?
Data			LPBYTE ?
ADS_OCTET_LIST		ENDS
PADS_OCTET_LIST		typedef ptr ADS_OCTET_LIST

ADS_PATH		STRUC
Type			DWORD ?
VolumeName		LPWSTR ?
Path			LPWSTR ?
ADS_PATH		ENDS
PADS_PATH		typedef ptr ADS_PATH

ADS_POSTALADDRESS	STRUC
PostalAddress		LPWSTR 6 dup(?)
ADS_POSTALADDRESS	ENDS
PADS_POSTALADDRESS	typedef ptr ADS_POSTALADDRESS

ADS_TIMESTAMP		STRUC
WholeSeconds		dd ?
EventID			dd ?
ADS_TIMESTAMP		ENDS
PADS_TIMESTAMP		typedef ptr ADS_TIMESTAMP

ADS_BACKLINK		STRUC
RemoteID		dd ?
ObjectName		LPWSTR ?
ADS_BACKLINK		ENDS
PADS_BACKLINK		typedef ptr ADS_BACKLINK

ADS_TYPEDNAME		STRUC
ObjectName		LPWSTR ?
Level			dd ?
Interval		dd ?
ADS_TYPEDNAME		ENDS
PADS_TYPEDNAME		typedef ptr ADS_TYPEDNAME

ADS_HOLD		STRUC
ObjectName		LPWSTR ?
Amount			dd ?
ADS_HOLD		ENDS
PADS_HOLD		typedef ptr ADS_HOLD

ADS_NETADDRESS		STRUC
AddressType		DWORD ?
AddressLength		dd ?
Address			LPBYTE ?
ADS_NETADDRESS		ENDS
PADS_NETADDRESS		typedef ptr ADS_NETADDRESS

ADS_REPLICAPOINTER	STRUC
ServerName		LPWSTR ?
ReplicaType		dd ?
ReplicaNumber		dd ?
Count			dd ?
ReplicaAddressHints	PADS_NETADDRESS ?
ADS_REPLICAPOINTER	ENDS
PADS_REPLICAPOINTER	typedef ptr ADS_REPLICAPOINTER

ADS_FAXNUMBER		STRUC
TelephoneNumber		LPWSTR ?
NumberOfBits		dd ?
Parameters		LPBYTE ?
ADS_FAXNUMBER		ENDS
PADS_FAXNUMBER		typedef ptr ADS_FAXNUMBER

ADS_EMAIL		STRUC
Address			LPWSTR ?
Type			dd ?
ADS_EMAIL		ENDS
PADS_EMAIL		typedef ptr ADS_EMAIL

ADS_DN_WITH_BINARY	STRUC
dwLength		DWORD ?
lpBinaryValue		LPBYTE ?
pszDNString		LPWSTR ?
ADS_DN_WITH_BINARY	ENDS
PADS_DN_WITH_BINARY	typedef ptr ADS_DN_WITH_BINARY

ADS_DN_WITH_STRING	STRUC
pszStringValue		LPWSTR ?
pszDNString		LPWSTR ?
ADS_DN_WITH_STRING	ENDS
PADS_DN_WITH_STRING	typedef ptr ADS_DN_WITH_STRING

ADSVALUE		STRUC
dwType			ADSTYPE ?
UNION
DNString		ADS_DN_STRING ?
CaseExactString		ADS_CASE_EXACT_STRING ?
CaseIgnoreString	ADS_CASE_IGNORE_STRING ?
PrintableString		ADS_PRINTABLE_STRING ?
NumericString		ADS_NUMERIC_STRING ?
Boolean			ADS_BOOLEAN ?
Integer			ADS_INTEGER ?
OctetString		ADS_OCTET_STRING <>
UTCTime			ADS_UTC_TIME <>
LargeInteger		ADS_LARGE_INTEGER <>
ClassName		ADS_OBJECT_CLASS ?
ProviderSpecific	ADS_PROV_SPECIFIC <>
pCaseIgnoreList		PADS_CASEIGNORE_LIST ?
pOctetList		PADS_OCTET_LIST ?
pPath			PADS_PATH ?
pPostalAddress		PADS_POSTALADDRESS ?
Timestamp		ADS_TIMESTAMP <>
BackLink		ADS_BACKLINK <>
pTypedName		PADS_TYPEDNAME ?
Hold			ADS_HOLD <>
pNetAddress		PADS_NETADDRESS ?
pReplicaPointer		PADS_REPLICAPOINTER ?
pFaxNumber		PADS_FAXNUMBER ?
Email			ADS_EMAIL <>
SecurityDescriptor	ADS_NT_SECURITY_DESCRIPTOR <>
pDNWithBinary		PADS_DN_WITH_BINARY ?
pDNWithString		PADS_DN_WITH_STRING ?
ENDS
ADSVALUE		ENDS
PADSVALUE		typedef ptr ADSVALUE
LPADSVALUE		typedef ptr ADSVALUE

ADS_ATTR_INFO		STRUC
pszAttrName		LPWSTR ?
dwControlCode		dd ?
dwADsType		ADSTYPE ?
pADsValues		PADSVALUE ?
dwNumValues		dd ?
ADS_ATTR_INFO		ENDS
PADS_ATTR_INFO		typedef ptr ADS_ATTR_INFO

ADS_AUTHENTICATION_ENUM typedef SDWORD
ADS_SECURE_AUTHENTICATION equ 0x1
ADS_USE_ENCRYPTION	equ 0x2
ADS_USE_SSL		equ 0x2
ADS_READONLY_SERVER	equ 0x4
ADS_PROMPT_CREDENTIALS	equ 0x8
ADS_NO_AUTHENTICATION	equ 0x10
ADS_FAST_BIND		equ 0x20
ADS_USE_SIGNING		equ 0x40
ADS_USE_SEALING		equ 0x80
ADS_USE_DELEGATION	equ 0x100
ADS_SERVER_BIND		equ 0x200
ADS_NO_REFERRAL_CHASING equ 0x400
ADS_AUTH_RESERVED	equ 0x80000000

ADS_ATTR_CLEAR		equ ( 1 )
ADS_ATTR_UPDATE		equ ( 2 )
ADS_ATTR_APPEND		equ ( 3 )
ADS_ATTR_DELETE		equ ( 4 )

ADS_OBJECT_INFO		STRUC
pszRDN			LPWSTR ?
pszObjectDN		LPWSTR ?
pszParentDN		LPWSTR ?
pszSchemaDN		LPWSTR ?
pszClassName		LPWSTR ?
ADS_OBJECT_INFO		ENDS
PADS_OBJECT_INFO	typedef ptr ADS_OBJECT_INFO

ADS_STATUSENUM typedef SDWORD
ADS_STATUS_S_OK		equ 0
ADS_STATUS_INVALID_SEARCHPREF equ ( ADS_STATUS_S_OK + 1 )
ADS_STATUS_INVALID_SEARCHPREFVALUE equ ( ADS_STATUS_INVALID_SEARCHPREF + 1 )

ADS_STATUS		typedef ADS_STATUSENUM
PADS_STATUS		typedef ptr ADS_STATUSENUM

ADS_DEREFENUM typedef SDWORD
ADS_DEREF_NEVER		equ 0
ADS_DEREF_SEARCHING	equ 1
ADS_DEREF_FINDING	equ 2
ADS_DEREF_ALWAYS	equ 3

ADS_SCOPEENUM typedef SDWORD
ADS_SCOPE_BASE		equ 0
ADS_SCOPE_ONELEVEL	equ 1
ADS_SCOPE_SUBTREE	equ 2

ADS_PREFERENCES_ENUM typedef SDWORD
ADSIPROP_ASYNCHRONOUS	equ 0
ADSIPROP_DEREF_ALIASES	equ 0x1
ADSIPROP_SIZE_LIMIT	equ 0x2
ADSIPROP_TIME_LIMIT	equ 0x3
ADSIPROP_ATTRIBTYPES_ONLY equ 0x4
ADSIPROP_SEARCH_SCOPE	equ 0x5
ADSIPROP_TIMEOUT	equ 0x6
ADSIPROP_PAGESIZE	equ 0x7
ADSIPROP_PAGED_TIME_LIMIT equ 0x8
ADSIPROP_CHASE_REFERRALS equ 0x9
ADSIPROP_SORT_ON	equ 0xa
ADSIPROP_CACHE_RESULTS	equ 0xb
ADSIPROP_ADSIFLAG	equ 0xc

ADSI_DIALECT_ENUM typedef SDWORD
ADSI_DIALECT_LDAP	equ 0
ADSI_DIALECT_SQL	equ 0x1

ADS_CHASE_REFERRALS_ENUM typedef SDWORD
ADS_CHASE_REFERRALS_NEVER equ 0
ADS_CHASE_REFERRALS_SUBORDINATE equ 0x20
ADS_CHASE_REFERRALS_EXTERNAL equ 0x40
ADS_CHASE_REFERRALS_ALWAYS equ ( ADS_CHASE_REFERRALS_SUBORDINATE OR ADS_CHASE_REFERRALS_EXTERNAL )

ADS_SEARCHPREF_ENUM typedef SDWORD
ADS_SEARCHPREF_ASYNCHRONOUS equ 0
ADS_SEARCHPREF_DEREF_ALIASES equ ( ADS_SEARCHPREF_ASYNCHRONOUS + 1 )
ADS_SEARCHPREF_SIZE_LIMIT equ ( ADS_SEARCHPREF_DEREF_ALIASES + 1 )
ADS_SEARCHPREF_TIME_LIMIT equ ( ADS_SEARCHPREF_SIZE_LIMIT + 1 )
ADS_SEARCHPREF_ATTRIBTYPES_ONLY equ ( ADS_SEARCHPREF_TIME_LIMIT + 1 )
ADS_SEARCHPREF_SEARCH_SCOPE equ ( ADS_SEARCHPREF_ATTRIBTYPES_ONLY + 1 )
ADS_SEARCHPREF_TIMEOUT	equ ( ADS_SEARCHPREF_SEARCH_SCOPE + 1 )
ADS_SEARCHPREF_PAGESIZE equ ( ADS_SEARCHPREF_TIMEOUT + 1 )
ADS_SEARCHPREF_PAGED_TIME_LIMIT equ ( ADS_SEARCHPREF_PAGESIZE + 1 )
ADS_SEARCHPREF_CHASE_REFERRALS equ ( ADS_SEARCHPREF_PAGED_TIME_LIMIT + 1 )
ADS_SEARCHPREF_SORT_ON	equ ( ADS_SEARCHPREF_CHASE_REFERRALS + 1 )
ADS_SEARCHPREF_CACHE_RESULTS equ ( ADS_SEARCHPREF_SORT_ON + 1 )
ADS_SEARCHPREF_DIRSYNC	equ ( ADS_SEARCHPREF_CACHE_RESULTS + 1 )
ADS_SEARCHPREF_TOMBSTONE equ ( ADS_SEARCHPREF_DIRSYNC + 1 )
ADS_SEARCHPREF_VLV	equ ( ADS_SEARCHPREF_TOMBSTONE + 1 )
ADS_SEARCHPREF_ATTRIBUTE_QUERY equ ( ADS_SEARCHPREF_VLV + 1 )
ADS_SEARCHPREF_SECURITY_MASK equ ( ADS_SEARCHPREF_ATTRIBUTE_QUERY + 1 )
ADS_SEARCHPREF_DIRSYNC_FLAG equ ( ADS_SEARCHPREF_SECURITY_MASK + 1 )
ADS_SEARCHPREF_EXTENDED_DN equ ( ADS_SEARCHPREF_DIRSYNC_FLAG + 1 )

ADS_PASSWORD_ENCODING_ENUM typedef SDWORD
ADS_PASSWORD_ENCODE_REQUIRE_SSL equ 0
ADS_PASSWORD_ENCODE_CLEAR equ 1

ADS_SEARCHPREF		typedef ADS_SEARCHPREF_ENUM

ADS_SEARCHPREF_INFO	STRUC
dwSearchPref		ADS_SEARCHPREF ?
vValue			ADSVALUE <>
dwStatus		ADS_STATUS ?
ADS_SEARCHPREF_INFO	ENDS

PADS_SEARCHPREF_INFO	typedef ptr ADS_SEARCHPREF_INFO
LPADS_SEARCHPREF_INFO	typedef ptr ADS_SEARCHPREF_INFO

ADS_DIRSYNC_COOKIE	equ <L"fc8cb04d-311d-406c-8cb9-1ae8b843b418">
ADS_VLV_RESPONSE	equ <L"fc8cb04d-311d-406c-8cb9-1ae8b843b419">

ADS_SEARCH_HANDLE	typedef HANDLE
PADS_SEARCH_HANDLE	typedef ptr HANDLE

ADS_SEARCH_COLUMN	STRUC
pszAttrName		LPWSTR ?
dwADsType		ADSTYPE ?
pADsValues		PADSVALUE ?
dwNumValues		dd ?
hReserved		HANDLE ?
ADS_SEARCH_COLUMN	ENDS
PADS_SEARCH_COLUMN	typedef ptr ADS_SEARCH_COLUMN

ADS_ATTR_DEF		STRUC
pszAttrName		LPWSTR ?
dwADsType		ADSTYPE ?
dwMinRange		dd ?
dwMaxRange		dd ?
fMultiValued		BOOL ?
ADS_ATTR_DEF		ENDS
PADS_ATTR_DEF		typedef ptr ADS_ATTR_DEF

ADS_CLASS_DEF		STRUC
pszClassName		LPWSTR ?
dwMandatoryAttrs	dd ?
ppszMandatoryAttrs	LPWSTR ?
optionalAttrs		dd ?
ppszOptionalAttrs	LPWSTR ?
dwNamingAttrs		dd ?
ppszNamingAttrs		LPWSTR ?
dwSuperClasses		dd ?
ppszSuperClasses	LPWSTR ?
fIsContainer		BOOL ?
ADS_CLASS_DEF		ENDS
PADS_CLASS_DEF		typedef ptr ADS_CLASS_DEF

ADS_SORTKEY		STRUC
pszAttrType		LPWSTR ?
pszReserved		LPWSTR ?
fReverseorder		BOOLEAN ?
ADS_SORTKEY		ENDS
PADS_SORTKEY		typedef ptr ADS_SORTKEY

ADS_VLV			STRUC
dwBeforeCount		dd ?
dwAfterCount		dd ?
dwOffset		dd ?
dwContentCount		dd ?
pszTarget		LPWSTR ?
dwContextIDLength	dd ?
lpContextID		LPBYTE ?
ADS_VLV			ENDS
PADS_VLV		typedef ptr ADS_VLV

ADS_EXT_MINEXTDISPID	equ ( 1 )
ADS_EXT_MAXEXTDISPID	equ ( 16777215 )
ADS_EXT_INITCREDENTIALS equ ( 1 )
ADS_EXT_INITIALIZE_COMPLETE equ ( 2 )

ADS_PROPERTY_OPERATION_ENUM typedef SDWORD
ADS_PROPERTY_CLEAR	equ 1
ADS_PROPERTY_UPDATE	equ 2
ADS_PROPERTY_APPEND	equ 3
ADS_PROPERTY_DELETE	equ 4

ADS_SYSTEMFLAG_ENUM typedef SDWORD
ADS_SYSTEMFLAG_DISALLOW_DELETE equ 0x80000000
ADS_SYSTEMFLAG_CONFIG_ALLOW_RENAME equ 0x40000000
ADS_SYSTEMFLAG_CONFIG_ALLOW_MOVE equ 0x20000000
ADS_SYSTEMFLAG_CONFIG_ALLOW_LIMITED_MOVE equ 0x10000000
ADS_SYSTEMFLAG_DOMAIN_DISALLOW_RENAME equ 0x8000000
ADS_SYSTEMFLAG_DOMAIN_DISALLOW_MOVE equ 0x4000000
ADS_SYSTEMFLAG_CR_NTDS_NC equ 0x1
ADS_SYSTEMFLAG_CR_NTDS_DOMAIN equ 0x2
ADS_SYSTEMFLAG_ATTR_NOT_REPLICATED equ 0x1
ADS_SYSTEMFLAG_ATTR_IS_CONSTRUCTED equ 0x4

ADS_GROUP_TYPE_ENUM typedef SDWORD
ADS_GROUP_TYPE_GLOBAL_GROUP equ 0x2
ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP equ 0x4
ADS_GROUP_TYPE_LOCAL_GROUP equ 0x4
ADS_GROUP_TYPE_UNIVERSAL_GROUP equ 0x8
ADS_GROUP_TYPE_SECURITY_ENABLED equ 0x80000000

ADS_USER_FLAG		typedef SDWORD
ADS_UF_SCRIPT		equ 0x1
ADS_UF_ACCOUNTDISABLE	equ 0x2
ADS_UF_HOMEDIR_REQUIRED equ 0x8
ADS_UF_LOCKOUT		equ 0x10
ADS_UF_PASSWD_NOTREQD	equ 0x20
ADS_UF_PASSWD_CANT_CHANGE equ 0x40
ADS_UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED equ 0x80
ADS_UF_TEMP_DUPLICATE_ACCOUNT equ 0x100
ADS_UF_NORMAL_ACCOUNT	equ 0x200
ADS_UF_INTERDOMAIN_TRUST_ACCOUNT equ 0x800
ADS_UF_WORKSTATION_TRUST_ACCOUNT equ 0x1000
ADS_UF_SERVER_TRUST_ACCOUNT equ 0x2000
ADS_UF_DONT_EXPIRE_PASSWD equ 0x10000
ADS_UF_MNS_LOGON_ACCOUNT equ 0x20000
ADS_UF_SMARTCARD_REQUIRED equ 0x40000
ADS_UF_TRUSTED_FOR_DELEGATION equ 0x80000
ADS_UF_NOT_DELEGATED	equ 0x100000
ADS_UF_USE_DES_KEY_ONLY equ 0x200000
ADS_UF_DONT_REQUIRE_PREAUTH equ 0x400000
ADS_UF_PASSWORD_EXPIRED equ 0x800000
ADS_UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION equ 0x1000000

ADS_RIGHTS_ENUM typedef SDWORD
ADS_RIGHT_DELETE	equ 0x10000
ADS_RIGHT_READ_CONTROL	equ 0x20000
ADS_RIGHT_WRITE_DAC	equ 0x40000
ADS_RIGHT_WRITE_OWNER	equ 0x80000
ADS_RIGHT_SYNCHRONIZE	equ 0x100000
ADS_RIGHT_ACCESS_SYSTEM_SECURITY equ 0x1000000
ADS_RIGHT_GENERIC_READ	equ 0x80000000
ADS_RIGHT_GENERIC_WRITE equ 0x40000000
ADS_RIGHT_GENERIC_EXECUTE equ 0x20000000
ADS_RIGHT_GENERIC_ALL	equ 0x10000000
ADS_RIGHT_DS_CREATE_CHILD equ 0x1
ADS_RIGHT_DS_DELETE_CHILD equ 0x2
ADS_RIGHT_ACTRL_DS_LIST equ 0x4
ADS_RIGHT_DS_SELF	equ 0x8
ADS_RIGHT_DS_READ_PROP	equ 0x10
ADS_RIGHT_DS_WRITE_PROP equ 0x20
ADS_RIGHT_DS_DELETE_TREE equ 0x40
ADS_RIGHT_DS_LIST_OBJECT equ 0x80
ADS_RIGHT_DS_CONTROL_ACCESS equ 0x100

ADS_ACETYPE_ENUM typedef SDWORD
ADS_ACETYPE_ACCESS_ALLOWED equ 0
ADS_ACETYPE_ACCESS_DENIED equ 0x1
ADS_ACETYPE_SYSTEM_AUDIT equ 0x2
ADS_ACETYPE_ACCESS_ALLOWED_OBJECT equ 0x5
ADS_ACETYPE_ACCESS_DENIED_OBJECT equ 0x6
ADS_ACETYPE_SYSTEM_AUDIT_OBJECT equ 0x7
ADS_ACETYPE_SYSTEM_ALARM_OBJECT equ 0x8
ADS_ACETYPE_ACCESS_ALLOWED_CALLBACK equ 0x9
ADS_ACETYPE_ACCESS_DENIED_CALLBACK equ 0xa
ADS_ACETYPE_ACCESS_ALLOWED_CALLBACK_OBJECT equ 0xb
ADS_ACETYPE_ACCESS_DENIED_CALLBACK_OBJECT equ 0xc
ADS_ACETYPE_SYSTEM_AUDIT_CALLBACK equ 0xd
ADS_ACETYPE_SYSTEM_ALARM_CALLBACK equ 0xe
ADS_ACETYPE_SYSTEM_AUDIT_CALLBACK_OBJECT equ 0xf
ADS_ACETYPE_SYSTEM_ALARM_CALLBACK_OBJECT equ 0x10

ADS_ACEFLAG_ENUM typedef SDWORD
ADS_ACEFLAG_INHERIT_ACE equ 0x2
ADS_ACEFLAG_NO_PROPAGATE_INHERIT_ACE equ 0x4
ADS_ACEFLAG_INHERIT_ONLY_ACE equ 0x8
ADS_ACEFLAG_INHERITED_ACE equ 0x10
ADS_ACEFLAG_VALID_INHERIT_FLAGS equ 0x1f
ADS_ACEFLAG_SUCCESSFUL_ACCESS equ 0x40
ADS_ACEFLAG_FAILED_ACCESS equ 0x80

ADS_FLAGTYPE_ENUM typedef SDWORD
ADS_FLAG_OBJECT_TYPE_PRESENT equ 0x1
ADS_FLAG_INHERITED_OBJECT_TYPE_PRESENT equ 0x2

ADS_SD_CONTROL_ENUM typedef SDWORD
ADS_SD_CONTROL_SE_OWNER_DEFAULTED equ 0x1
ADS_SD_CONTROL_SE_GROUP_DEFAULTED equ 0x2
ADS_SD_CONTROL_SE_DACL_PRESENT equ 0x4
ADS_SD_CONTROL_SE_DACL_DEFAULTED equ 0x8
ADS_SD_CONTROL_SE_SACL_PRESENT equ 0x10
ADS_SD_CONTROL_SE_SACL_DEFAULTED equ 0x20
ADS_SD_CONTROL_SE_DACL_AUTO_INHERIT_REQ equ 0x100
ADS_SD_CONTROL_SE_SACL_AUTO_INHERIT_REQ equ 0x200
ADS_SD_CONTROL_SE_DACL_AUTO_INHERITED equ 0x400
ADS_SD_CONTROL_SE_SACL_AUTO_INHERITED equ 0x800
ADS_SD_CONTROL_SE_DACL_PROTECTED equ 0x1000
ADS_SD_CONTROL_SE_SACL_PROTECTED equ 0x2000
ADS_SD_CONTROL_SE_SELF_RELATIVE equ 0x8000

ADS_SD_REVISION_ENUM typedef SDWORD
ADS_SD_REVISION_DS	equ 4

ADS_NAME_TYPE_ENUM typedef SDWORD
ADS_NAME_TYPE_1779	equ 1
ADS_NAME_TYPE_CANONICAL equ 2
ADS_NAME_TYPE_NT4	equ 3
ADS_NAME_TYPE_DISPLAY	equ 4
ADS_NAME_TYPE_DOMAIN_SIMPLE equ 5
ADS_NAME_TYPE_ENTERPRISE_SIMPLE equ 6
ADS_NAME_TYPE_GUID	equ 7
ADS_NAME_TYPE_UNKNOWN	equ 8
ADS_NAME_TYPE_USER_PRINCIPAL_NAME equ 9
ADS_NAME_TYPE_CANONICAL_EX equ 10
ADS_NAME_TYPE_SERVICE_PRINCIPAL_NAME equ 11
ADS_NAME_TYPE_SID_OR_SID_HISTORY_NAME equ 12

ADS_NAME_INITTYPE_ENUM typedef SDWORD
ADS_NAME_INITTYPE_DOMAIN equ 1
ADS_NAME_INITTYPE_SERVER equ 2
ADS_NAME_INITTYPE_GC	equ 3

ADS_OPTION_ENUM typedef SDWORD
ADS_OPTION_SERVERNAME	equ 0
ADS_OPTION_REFERRALS	equ ( ADS_OPTION_SERVERNAME + 1 )
ADS_OPTION_PAGE_SIZE	equ ( ADS_OPTION_REFERRALS + 1 )
ADS_OPTION_SECURITY_MASK equ ( ADS_OPTION_PAGE_SIZE + 1 )
ADS_OPTION_MUTUAL_AUTH_STATUS equ ( ADS_OPTION_SECURITY_MASK + 1 )
ADS_OPTION_QUOTA	equ ( ADS_OPTION_MUTUAL_AUTH_STATUS + 1 )
ADS_OPTION_PASSWORD_PORTNUMBER equ ( ADS_OPTION_QUOTA + 1 )
ADS_OPTION_PASSWORD_METHOD equ ( ADS_OPTION_PASSWORD_PORTNUMBER + 1 )
ADS_OPTION_ACCUMULATIVE_MODIFICATION equ ( ADS_OPTION_PASSWORD_METHOD + 1 )
ADS_OPTION_SKIP_SID_LOOKUP equ ( ADS_OPTION_ACCUMULATIVE_MODIFICATION + 1 )

ADS_SECURITY_INFO_ENUM typedef SDWORD
ADS_SECURITY_INFO_OWNER equ 0x1
ADS_SECURITY_INFO_GROUP equ 0x2
ADS_SECURITY_INFO_DACL	equ 0x4
ADS_SECURITY_INFO_SACL	equ 0x8

ADS_SETTYPE_ENUM typedef SDWORD
ADS_SETTYPE_FULL	equ 1
ADS_SETTYPE_PROVIDER	equ 2
ADS_SETTYPE_SERVER	equ 3
ADS_SETTYPE_DN		equ 4

ADS_FORMAT_ENUM typedef SDWORD
ADS_FORMAT_WINDOWS	equ 1
ADS_FORMAT_WINDOWS_NO_SERVER equ 2
ADS_FORMAT_WINDOWS_DN	equ 3
ADS_FORMAT_WINDOWS_PARENT equ 4
ADS_FORMAT_X500		equ 5
ADS_FORMAT_X500_NO_SERVER equ 6
ADS_FORMAT_X500_DN	equ 7
ADS_FORMAT_X500_PARENT	equ 8
ADS_FORMAT_SERVER	equ 9
ADS_FORMAT_PROVIDER	equ 10
ADS_FORMAT_LEAF		equ 11

ADS_DISPLAY_ENUM typedef SDWORD
ADS_DISPLAY_FULL	equ 1
ADS_DISPLAY_VALUE_ONLY	equ 2

ADS_ESCAPE_MODE_ENUM typedef SDWORD
ADS_ESCAPEDMODE_DEFAULT equ 1
ADS_ESCAPEDMODE_ON	equ 2
ADS_ESCAPEDMODE_OFF	equ 3
ADS_ESCAPEDMODE_OFF_EX	equ 4

ADS_PATHTYPE_ENUM typedef SDWORD
ADS_PATH_FILE		equ 1
ADS_PATH_FILESHARE	equ 2
ADS_PATH_REGISTRY	equ 3

ADS_SD_FORMAT_ENUM typedef SDWORD
ADS_SD_FORMAT_IID	equ 1
ADS_SD_FORMAT_RAW	equ 2
ADS_SD_FORMAT_HEXSTRING equ 3

externdef		LIBID_ActiveDs:IID

ifndef __IADs_INTERFACE_DEFINED__
define __IADs_INTERFACE_DEFINED__

DEFINE_IIDX(IADs, "fd8256d0-fd15-11ce-abc4-02608c9e7553")

.comdef IADs : public IDispatch

    get_Name		proc :ptr
    get_Class		proc :ptr
    get_GUID		proc :ptr
    get_ADsPath		proc :ptr
    get_Parent		proc :ptr
    get_Schema		proc :ptr
    GetInfo		proc
    SetInfo		proc
    Get			proc :BSTR, :ptr
    Put			proc :BSTR, :VARIANT
    GetEx		proc :BSTR, :ptr
    PutEx		proc :LONG, :BSTR, :VARIANT
    GetInfoEx		proc :VARIANT, :LONG
   .ends
endif

ifndef __IADsContainer_INTERFACE_DEFINED__
define __IADsContainer_INTERFACE_DEFINED__

DEFINE_IIDX(IADsContainer, "001677d0-fd16-11ce-abc4-02608c9e7553")

.comdef IADsContainer : public IDispatch

    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    get_Filter		proc :ptr
    put_Filter		proc :VARIANT
    get_Hints		proc :ptr
    put_Hints		proc :VARIANT
    GetObject		proc :BSTR, :BSTR, :ptr
    Create		proc :BSTR, :BSTR, :ptr
    Delete		proc :BSTR, :BSTR
    CopyHere		proc :BSTR, :BSTR, :ptr
    MoveHere		proc :BSTR, :BSTR, :ptr
   .ends
endif

ifndef __IADsCollection_INTERFACE_DEFINED__
define __IADsCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IADsCollection, "72b945e0-253b-11cf-a988-00aa006bc149")

.comdef IADsCollection : public IDispatch

    get__NewEnum	proc :ptr
    _Add		proc :BSTR, :VARIANT
    Remove		proc :BSTR
    GetObject		proc :BSTR, :ptr
   .ends
endif

ifndef __IADsMembers_INTERFACE_DEFINED__
define __IADsMembers_INTERFACE_DEFINED__

DEFINE_IIDX(IADsMembers, "451a0030-72ec-11cf-b03b-00aa006e0975")

.comdef IADsMembers : public IDispatch

    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    get_Filter		proc :ptr
    put_Filter		proc :VARIANT
   .ends
endif

ifndef __IADsPropertyList_INTERFACE_DEFINED__
define __IADsPropertyList_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPropertyList, "c6f602b6-8f69-11d0-8528-00c04fd8d503")

.comdef IADsPropertyList : public IDispatch

    get_PropertyCount	proc :ptr
    Next		proc :ptr
    Skip		proc :LONG
    Reset		proc
    Item		proc :VARIANT, :ptr
    GetPropertyItem	proc :BSTR, :LONG, :ptr
    PutPropertyItem	proc :VARIANT
    ResetPropertyItem	proc :VARIANT
    PurgePropertyList	proc
   .ends
endif

ifndef __IADsPropertyEntry_INTERFACE_DEFINED__
define __IADsPropertyEntry_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPropertyEntry, "05792c8e-941f-11d0-8529-00c04fd8d503")

.comdef IADsPropertyEntry : public IDispatch

    Clear		proc
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_ADsType		proc :ptr
    put_ADsType		proc :LONG
    get_ControlCode	proc :ptr
    put_ControlCode	proc :LONG
    get_Values		proc :ptr
    put_Values		proc :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_PropertyEntry, "72d3edc2-a4c4-11d0-8533-00c04fd8d503")

ifndef __IADsPropertyValue_INTERFACE_DEFINED__
define __IADsPropertyValue_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPropertyValue, "79fa9ad0-a97c-11d0-8534-00c04fd8d503")

.comdef IADsPropertyValue : public IDispatch

    Clear		proc
    get_ADsType		proc :ptr
    put_ADsType		proc :LONG
    get_DNString	proc :ptr
    put_DNString	proc :BSTR
    get_CaseExactString proc :ptr
    put_CaseExactString proc :BSTR
    get_CaseIgnoreString proc :ptr
    put_CaseIgnoreString proc :BSTR
    get_PrintableString proc :ptr
    put_PrintableString proc :BSTR
    get_NumericString	proc :ptr
    put_NumericString	proc :BSTR
    get_Boolean		proc :ptr
    put_Boolean		proc :LONG
    get_Integer		proc :ptr
    put_Integer		proc :LONG
    get_OctetString	proc :ptr
    put_OctetString	proc :VARIANT
    get_SecurityDescriptor proc :ptr
    put_SecurityDescriptor proc :ptr
    get_LargeInteger	proc :ptr
    put_LargeInteger	proc :ptr
    get_UTCTime		proc :ptr
    put_UTCTime		proc :DATE
   .ends
endif

ifndef __IADsPropertyValue2_INTERFACE_DEFINED__
define __IADsPropertyValue2_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPropertyValue2, "306e831c-5bc7-11d1-a3b8-00c04fb950dc")

.comdef IADsPropertyValue2 : public IDispatch

    GetObjectProperty	proc :ptr, :ptr
    PutObjectProperty	proc :LONG, :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_PropertyValue, "7b9e38b0-a97c-11d0-8534-00c04fd8d503")

ifndef __IPrivateDispatch_INTERFACE_DEFINED__
define __IPrivateDispatch_INTERFACE_DEFINED__

DEFINE_IIDX(IPrivateDispatch, "86ab4bbe-65f6-11d1-8c13-00c04fd8d503")

.comdef IPrivateDispatch : public IUnknown

    ADSIInitializeDispatchManager proc :LONG
    ADSIGetTypeInfoCount proc :ptr
    ADSIGetTypeInfo	proc :UINT, :LCID, :ptr
    ADSIGetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    ADSIInvoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
   .ends
endif

ifndef __IPrivateUnknown_INTERFACE_DEFINED__
define __IPrivateUnknown_INTERFACE_DEFINED__

DEFINE_IIDX(IPrivateUnknown, "89126bab-6ead-11d1-8c18-00c04fd8d503")

.comdef IPrivateUnknown : public IUnknown

    ADSIInitializeObject proc :BSTR, :BSTR, :LONG
    ADSIReleaseObject	proc
   .ends
endif

ifndef __IADsExtension_INTERFACE_DEFINED__
define __IADsExtension_INTERFACE_DEFINED__

DEFINE_IIDX(IADsExtension, "3d35553c-d2b0-11d1-b17b-0000f87593a0")

.comdef IADsExtension : public IUnknown

    Operate		proc :DWORD, :VARIANT, :VARIANT, :VARIANT
    PrivateGetIDsOfNames proc :REFIID, :ptr, :SINT, :LCID, :ptr
    PrivateInvoke	proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
   .ends
endif

ifndef __IADsDeleteOps_INTERFACE_DEFINED__
define __IADsDeleteOps_INTERFACE_DEFINED__

DEFINE_IIDX(IADsDeleteOps, "b2bd0902-8878-11d1-8c21-00c04fd8d503")

.comdef IADsDeleteOps : public IDispatch

    DeleteObject	proc :LONG
   .ends
endif

ifndef __IADsNamespaces_INTERFACE_DEFINED__
define __IADsNamespaces_INTERFACE_DEFINED__

DEFINE_IIDX(IADsNamespaces, "28b96ba0-b330-11cf-a9ad-00aa006bc149")

.comdef IADsNamespaces : public IADs

    get_DefaultContainer proc :ptr
    put_DefaultContainer proc :BSTR
   .ends
endif

ifndef __IADsClass_INTERFACE_DEFINED__
define __IADsClass_INTERFACE_DEFINED__

DEFINE_IIDX(IADsClass, "c8f93dd0-4ae0-11cf-9e73-00aa004a5691")

.comdef IADsClass : public IADs

    get_PrimaryInterface proc :ptr
    get_CLSID		proc :ptr
    put_CLSID		proc :BSTR
    get_OID		proc :ptr
    put_OID		proc :BSTR
    get_Abstract	proc :ptr
    put_Abstract	proc :VARIANT_BOOL
    get_Auxiliary	proc :ptr
    put_Auxiliary	proc :VARIANT_BOOL
    get_MandatoryProperties proc :ptr
    put_MandatoryProperties proc :VARIANT
    get_OptionalProperties proc :ptr
    put_OptionalProperties proc :VARIANT
    get_NamingProperties proc :ptr
    put_NamingProperties proc :VARIANT
    get_DerivedFrom	proc :ptr
    put_DerivedFrom	proc :VARIANT
    get_AuxDerivedFrom	proc :ptr
    put_AuxDerivedFrom	proc :VARIANT
    get_PossibleSuperiors proc :ptr
    put_PossibleSuperiors proc :VARIANT
    get_Containment	proc :ptr
    put_Containment	proc :VARIANT
    get_Container	proc :ptr
    put_Container	proc :VARIANT_BOOL
    get_HelpFileName	proc :ptr
    put_HelpFileName	proc :BSTR
    get_HelpFileContext proc :ptr
    put_HelpFileContext proc :LONG
    Qualifiers		proc :ptr
   .ends
endif

ifndef __IADsProperty_INTERFACE_DEFINED__
define __IADsProperty_INTERFACE_DEFINED__

DEFINE_IIDX(IADsProperty, "c8f93dd3-4ae0-11cf-9e73-00aa004a5691")

.comdef IADsProperty : public IADs

    get_OID		proc :ptr
    put_OID		proc :BSTR
    get_Syntax		proc :ptr
    put_Syntax		proc :BSTR
    get_MaxRange	proc :ptr
    put_MaxRange	proc :LONG
    get_MinRange	proc :ptr
    put_MinRange	proc :LONG
    get_MultiValued	proc :ptr
    put_MultiValued	proc :VARIANT_BOOL
    Qualifiers		proc :ptr
   .ends
endif

ifndef __IADsSyntax_INTERFACE_DEFINED__
define __IADsSyntax_INTERFACE_DEFINED__

DEFINE_IIDX(IADsSyntax, "c8f93dd2-4ae0-11cf-9e73-00aa004a5691")

.comdef IADsSyntax : public IADs

    get_OleAutoDataType proc :ptr
    put_OleAutoDataType proc :LONG
   .ends
endif

ifndef __IADsLocality_INTERFACE_DEFINED__
define __IADsLocality_INTERFACE_DEFINED__

DEFINE_IIDX(IADsLocality, "a05e03a2-effe-11cf-8abc-00c04fd8d503")

.comdef IADsLocality : public IADs

    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_LocalityName	proc :ptr
    put_LocalityName	proc :BSTR
    get_PostalAddress	proc :ptr
    put_PostalAddress	proc :BSTR
    get_SeeAlso		proc :ptr
    put_SeeAlso		proc :VARIANT
   .ends
endif

ifndef __IADsO_INTERFACE_DEFINED__
define __IADsO_INTERFACE_DEFINED__

DEFINE_IIDX(IADsO, "a1cd2dc6-effe-11cf-8abc-00c04fd8d503")

.comdef IADsO : public IADs

    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_LocalityName	proc :ptr
    put_LocalityName	proc :BSTR
    get_PostalAddress	proc :ptr
    put_PostalAddress	proc :BSTR
    get_TelephoneNumber proc :ptr
    put_TelephoneNumber proc :BSTR
    get_FaxNumber	proc :ptr
    put_FaxNumber	proc :BSTR
    get_SeeAlso		proc :ptr
    put_SeeAlso		proc :VARIANT
   .ends
endif

ifndef __IADsOU_INTERFACE_DEFINED__
define __IADsOU_INTERFACE_DEFINED__

DEFINE_IIDX(IADsOU, "a2f733b8-effe-11cf-8abc-00c04fd8d503")

.comdef IADsOU : public IADs

    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_LocalityName	proc :ptr
    put_LocalityName	proc :BSTR
    get_PostalAddress	proc :ptr
    put_PostalAddress	proc :BSTR
    get_TelephoneNumber proc :ptr
    put_TelephoneNumber proc :BSTR
    get_FaxNumber	proc :ptr
    put_FaxNumber	proc :BSTR
    get_SeeAlso		proc :ptr
    put_SeeAlso		proc :VARIANT
    get_BusinessCategory proc :ptr
    put_BusinessCategory proc :BSTR
   .ends
endif

ifndef __IADsDomain_INTERFACE_DEFINED__
define __IADsDomain_INTERFACE_DEFINED__

DEFINE_IIDX(IADsDomain, "00e4c220-fd16-11ce-abc4-02608c9e7553")

.comdef IADsDomain : public IADs

    get_IsWorkgroup	proc :ptr
    get_MinPasswordLength proc :ptr
    put_MinPasswordLength proc :LONG
    get_MinPasswordAge	proc :ptr
    put_MinPasswordAge	proc :LONG
    get_MaxPasswordAge	proc :ptr
    put_MaxPasswordAge	proc :LONG
    get_MaxBadPasswordsAllowed proc :ptr
    put_MaxBadPasswordsAllowed proc :LONG
    get_PasswordHistoryLength proc :ptr
    put_PasswordHistoryLength proc :LONG
    get_PasswordAttributes proc :ptr
    put_PasswordAttributes proc :LONG
    get_AutoUnlockInterval proc :ptr
    put_AutoUnlockInterval proc :LONG
    get_LockoutObservationInterval proc :ptr
    put_LockoutObservationInterval proc :LONG
   .ends
endif

ifndef __IADsComputer_INTERFACE_DEFINED__
define __IADsComputer_INTERFACE_DEFINED__

DEFINE_IIDX(IADsComputer, "efe3cc70-1d9f-11cf-b1f3-02608c9e7553")

.comdef IADsComputer : public IADs

    get_ComputerID	proc :ptr
    get_Site		proc :ptr
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_Location	proc :ptr
    put_Location	proc :BSTR
    get_PrimaryUser	proc :ptr
    put_PrimaryUser	proc :BSTR
    get_Owner		proc :ptr
    put_Owner		proc :BSTR
    get_Division	proc :ptr
    put_Division	proc :BSTR
    get_Department	proc :ptr
    put_Department	proc :BSTR
    get_Role		proc :ptr
    put_Role		proc :BSTR
    get_OperatingSystem proc :ptr
    put_OperatingSystem proc :BSTR
    get_OperatingSystemVersion proc :ptr
    put_OperatingSystemVersion proc :BSTR
    get_Model		proc :ptr
    put_Model		proc :BSTR
    get_Processor	proc :ptr
    put_Processor	proc :BSTR
    get_ProcessorCount	proc :ptr
    put_ProcessorCount	proc :BSTR
    get_MemorySize	proc :ptr
    put_MemorySize	proc :BSTR
    get_StorageCapacity proc :ptr
    put_StorageCapacity proc :BSTR
    get_NetAddresses	proc :ptr
    put_NetAddresses	proc :VARIANT
   .ends
endif

ifndef __IADsComputerOperations_INTERFACE_DEFINED__
define __IADsComputerOperations_INTERFACE_DEFINED__

DEFINE_IIDX(IADsComputerOperations, "ef497680-1d9f-11cf-b1f3-02608c9e7553")

.comdef IADsComputerOperations : public IADs

    Status		proc :ptr
    Shutdown		proc :VARIANT_BOOL
   .ends
endif

ifndef __IADsGroup_INTERFACE_DEFINED__
define __IADsGroup_INTERFACE_DEFINED__

DEFINE_IIDX(IADsGroup, "27636b00-410f-11cf-b1ff-02608c9e7553")

.comdef IADsGroup : public IADs

    get_Description	proc :ptr
    put_Description	proc :BSTR
    Members		proc :ptr
    IsMember		proc :BSTR, :ptr
    _Add		proc :BSTR
    Remove		proc :BSTR
   .ends
endif

ifndef __IADsUser_INTERFACE_DEFINED__
define __IADsUser_INTERFACE_DEFINED__

DEFINE_IIDX(IADsUser, "3e37e320-17e2-11cf-abc4-02608c9e7553")

.comdef IADsUser : public IADs

    get_BadLoginAddress proc :ptr
    get_BadLoginCount	proc :ptr
    get_LastLogin	proc :ptr
    get_LastLogoff	proc :ptr
    get_LastFailedLogin proc :ptr
    get_PasswordLastChanged proc :ptr
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_Division	proc :ptr
    put_Division	proc :BSTR
    get_Department	proc :ptr
    put_Department	proc :BSTR
    get_EmployeeID	proc :ptr
    put_EmployeeID	proc :BSTR
    get_FullName	proc :ptr
    put_FullName	proc :BSTR
    get_FirstName	proc :ptr
    put_FirstName	proc :BSTR
    get_LastName	proc :ptr
    put_LastName	proc :BSTR
    get_OtherName	proc :ptr
    put_OtherName	proc :BSTR
    get_NamePrefix	proc :ptr
    put_NamePrefix	proc :BSTR
    get_NameSuffix	proc :ptr
    put_NameSuffix	proc :BSTR
    get_Title		proc :ptr
    put_Title		proc :BSTR
    get_Manager		proc :ptr
    put_Manager		proc :BSTR
    get_TelephoneHome	proc :ptr
    put_TelephoneHome	proc :VARIANT
    get_TelephoneMobile proc :ptr
    put_TelephoneMobile proc :VARIANT
    get_TelephoneNumber proc :ptr
    put_TelephoneNumber proc :VARIANT
    get_TelephonePager	proc :ptr
    put_TelephonePager	proc :VARIANT
    get_FaxNumber	proc :ptr
    put_FaxNumber	proc :VARIANT
    get_OfficeLocations proc :ptr
    put_OfficeLocations proc :VARIANT
    get_PostalAddresses proc :ptr
    put_PostalAddresses proc :VARIANT
    get_PostalCodes	proc :ptr
    put_PostalCodes	proc :VARIANT
    get_SeeAlso		proc :ptr
    put_SeeAlso		proc :VARIANT
    get_AccountDisabled proc :ptr
    put_AccountDisabled proc :VARIANT_BOOL
    get_AccountExpirationDate proc :ptr
    put_AccountExpirationDate proc :DATE
    get_GraceLoginsAllowed proc :ptr
    put_GraceLoginsAllowed proc :LONG
    get_GraceLoginsRemaining proc :ptr
    put_GraceLoginsRemaining proc :LONG
    get_IsAccountLocked proc :ptr
    put_IsAccountLocked proc :VARIANT_BOOL
    get_LoginHours	proc :ptr
    put_LoginHours	proc :VARIANT
    get_LoginWorkstations proc :ptr
    put_LoginWorkstations proc :VARIANT
    get_MaxLogins	proc :ptr
    put_MaxLogins	proc :LONG
    get_MaxStorage	proc :ptr
    put_MaxStorage	proc :LONG
    get_PasswordExpirationDate proc :ptr
    put_PasswordExpirationDate proc :DATE
    get_PasswordMinimumLength proc :ptr
    put_PasswordMinimumLength proc :LONG
    get_PasswordRequired proc :ptr
    put_PasswordRequired proc :VARIANT_BOOL
    get_RequireUniquePassword proc :ptr
    put_RequireUniquePassword proc :VARIANT_BOOL
    get_EmailAddress	proc :ptr
    put_EmailAddress	proc :BSTR
    get_HomeDirectory	proc :ptr
    put_HomeDirectory	proc :BSTR
    get_Languages	proc :ptr
    put_Languages	proc :VARIANT
    get_Profile		proc :ptr
    put_Profile		proc :BSTR
    get_LoginScript	proc :ptr
    put_LoginScript	proc :BSTR
    get_Picture		proc :ptr
    put_Picture		proc :VARIANT
    get_HomePage	proc :ptr
    put_HomePage	proc :BSTR
    Groups		proc :ptr
    SetPassword		proc :BSTR
    ChangePassword	proc :BSTR, :BSTR
   .ends
endif

ifndef __IADsPrintQueue_INTERFACE_DEFINED__
define __IADsPrintQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPrintQueue, "b15160d0-1226-11cf-a985-00aa006bc149")

.comdef IADsPrintQueue : public IADs

    get_PrinterPath	proc :ptr
    put_PrinterPath	proc :BSTR
    get_Model		proc :ptr
    put_Model		proc :BSTR
    get_Datatype	proc :ptr
    put_Datatype	proc :BSTR
    get_PrintProcessor	proc :ptr
    put_PrintProcessor	proc :BSTR
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_Location	proc :ptr
    put_Location	proc :BSTR
    get_StartTime	proc :ptr
    put_StartTime	proc :DATE
    get_UntilTime	proc :ptr
    put_UntilTime	proc :DATE
    get_DefaultJobPriority proc :ptr
    put_DefaultJobPriority proc :LONG
    get_Priority	proc :ptr
    put_Priority	proc :LONG
    get_BannerPage	proc :ptr
    put_BannerPage	proc :BSTR
    get_PrintDevices	proc :ptr
    put_PrintDevices	proc :VARIANT
    get_NetAddresses	proc :ptr
    put_NetAddresses	proc :VARIANT
   .ends
endif

ifndef __IADsPrintQueueOperations_INTERFACE_DEFINED__
define __IADsPrintQueueOperations_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPrintQueueOperations, "124be5c0-156e-11cf-a986-00aa006bc149")

.comdef IADsPrintQueueOperations : public IADs

    get_Status		proc :ptr
    PrintJobs		proc :ptr
    _Pause		proc
    Resume		proc
    _Purge		proc
   .ends
endif

ifndef __IADsPrintJob_INTERFACE_DEFINED__
define __IADsPrintJob_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPrintJob, "32fb6780-1ed0-11cf-a988-00aa006bc149")

.comdef IADsPrintJob : public IADs

    get_HostPrintQueue	proc :ptr
    get_User		proc :ptr
    get_UserPath	proc :ptr
    get_TimeSubmitted	proc :ptr
    get_TotalPages	proc :ptr
    get_Size		proc :ptr
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_Priority	proc :ptr
    put_Priority	proc :LONG
    get_StartTime	proc :ptr
    put_StartTime	proc :DATE
    get_UntilTime	proc :ptr
    put_UntilTime	proc :DATE
    get_Notify		proc :ptr
    put_Notify		proc :BSTR
    get_NotifyPath	proc :ptr
    put_NotifyPath	proc :BSTR
   .ends
endif

ifndef __IADsPrintJobOperations_INTERFACE_DEFINED__
define __IADsPrintJobOperations_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPrintJobOperations, "9a52db30-1ecf-11cf-a988-00aa006bc149")

.comdef IADsPrintJobOperations : public IADs

    get_Status		proc :ptr
    get_TimeElapsed	proc :ptr
    get_PagesPrinted	proc :ptr
    get_Position	proc :ptr
    put_Position	proc :LONG
    _Pause		proc
    Resume		proc
   .ends
endif

ifndef __IADsService_INTERFACE_DEFINED__
define __IADsService_INTERFACE_DEFINED__

DEFINE_IIDX(IADsService, "68af66e0-31ca-11cf-a98a-00aa006bc149")

.comdef IADsService : public IADs

    get_HostComputer	proc :ptr
    put_HostComputer	proc :BSTR
    get_DisplayName	proc :ptr
    put_DisplayName	proc :BSTR
    get_Version		proc :ptr
    put_Version		proc :BSTR
    get_ServiceType	proc :ptr
    put_ServiceType	proc :LONG
    get_StartType	proc :ptr
    put_StartType	proc :LONG
    get_Path		proc :ptr
    put_Path		proc :BSTR
    get_StartupParameters proc :ptr
    put_StartupParameters proc :BSTR
    get_ErrorControl	proc :ptr
    put_ErrorControl	proc :LONG
    get_LoadOrderGroup	proc :ptr
    put_LoadOrderGroup	proc :BSTR
    get_ServiceAccountName proc :ptr
    put_ServiceAccountName proc :BSTR
    get_ServiceAccountPath proc :ptr
    put_ServiceAccountPath proc :BSTR
    get_Dependencies	proc :ptr
    put_Dependencies	proc :VARIANT
   .ends
endif

ifndef __IADsServiceOperations_INTERFACE_DEFINED__
define __IADsServiceOperations_INTERFACE_DEFINED__

DEFINE_IIDX(IADsServiceOperations, "5d7b33f0-31ca-11cf-a98a-00aa006bc149")

.comdef IADsServiceOperations : public IADs

    get_Status		proc :ptr
    Start		proc
    Stop		proc
    _Pause		proc
    Continue		proc
    SetPassword		proc :BSTR
   .ends
endif

ifndef __IADsFileService_INTERFACE_DEFINED__
define __IADsFileService_INTERFACE_DEFINED__

DEFINE_IIDX(IADsFileService, "a89d1900-31ca-11cf-a98a-00aa006bc149")

.comdef IADsFileService : public IADsService

    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_MaxUserCount	proc :ptr
    put_MaxUserCount	proc :LONG
   .ends
endif

ifndef __IADsFileServiceOperations_INTERFACE_DEFINED__
define __IADsFileServiceOperations_INTERFACE_DEFINED__

DEFINE_IIDX(IADsFileServiceOperations, "a02ded10-31ca-11cf-a98a-00aa006bc149")

.comdef IADsFileServiceOperations : public IADsServiceOperations

    Sessions		proc :ptr
    Resources		proc :ptr
   .ends
endif

ifndef __IADsFileShare_INTERFACE_DEFINED__
define __IADsFileShare_INTERFACE_DEFINED__

DEFINE_IIDX(IADsFileShare, "eb6dcaf0-4b83-11cf-a995-00aa006bc149")

.comdef IADsFileShare : public IADs

    get_CurrentUserCount proc :ptr
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_HostComputer	proc :ptr
    put_HostComputer	proc :BSTR
    get_Path		proc :ptr
    put_Path		proc :BSTR
    get_MaxUserCount	proc :ptr
    put_MaxUserCount	proc :LONG
   .ends
endif

ifndef __IADsSession_INTERFACE_DEFINED__
define __IADsSession_INTERFACE_DEFINED__

DEFINE_IIDX(IADsSession, "398b7da0-4aab-11cf-ae2c-00aa006ebfb9")

.comdef IADsSession : public IADs

    get_User		proc :ptr
    get_UserPath	proc :ptr
    get_Computer	proc :ptr
    get_ComputerPath	proc :ptr
    get_ConnectTime	proc :ptr
    get_IdleTime	proc :ptr
   .ends
endif

ifndef __IADsResource_INTERFACE_DEFINED__
define __IADsResource_INTERFACE_DEFINED__

DEFINE_IIDX(IADsResource, "34a05b20-4aab-11cf-ae2c-00aa006ebfb9")

.comdef IADsResource : public IADs

    get_User		proc :ptr
    get_UserPath	proc :ptr
    get_Path		proc :ptr
    get_LockCount	proc :ptr
   .ends
endif

ifndef __IADsOpenDSObject_INTERFACE_DEFINED__
define __IADsOpenDSObject_INTERFACE_DEFINED__

DEFINE_IIDX(IADsOpenDSObject, "ddf2891e-0f9c-11d0-8ad4-00c04fd8d503")

.comdef IADsOpenDSObject : public IDispatch

    OpenDSObject	proc :BSTR, :BSTR, :BSTR, :LONG, :ptr
   .ends

endif

ifndef __IDirectoryObject_INTERFACE_DEFINED__
define __IDirectoryObject_INTERFACE_DEFINED__

DEFINE_IIDX(IDirectoryObject, "e798de2c-22e4-11d0-84fe-00c04fd8d503")

.comdef IDirectoryObject : public IUnknown

    GetObjectInformation proc :ptr
    GetObjectAttributes proc :ptr, :DWORD, :ptr, :ptr
    SetObjectAttributes proc :PADS_ATTR_INFO, :DWORD, :ptr
    CreateDSObject	proc :LPWSTR, :PADS_ATTR_INFO, :DWORD, :ptr
    DeleteDSObject	proc :LPWSTR
   .ends
endif

ifndef __IDirectorySearch_INTERFACE_DEFINED__
define __IDirectorySearch_INTERFACE_DEFINED__

DEFINE_IIDX(IDirectorySearch, "109ba8ec-92f0-11d0-a790-00c04fd8d5a8")

.comdef IDirectorySearch : public IUnknown

    SetSearchPreference proc :PADS_SEARCHPREF_INFO, :DWORD
    ExecuteSearch	proc :LPWSTR, :ptr, :DWORD, :PADS_SEARCH_HANDLE
    AbandonSearch	proc :ADS_SEARCH_HANDLE
    GetFirstRow		proc :ADS_SEARCH_HANDLE
    GetNextRow		proc :ADS_SEARCH_HANDLE
    GetPreviousRow	proc :ADS_SEARCH_HANDLE
    GetNextColumnName	proc :ADS_SEARCH_HANDLE, :ptr
    GetColumn		proc :ADS_SEARCH_HANDLE, :LPWSTR, :PADS_SEARCH_COLUMN
    FreeColumn		proc :PADS_SEARCH_COLUMN
    CloseSearchHandle	proc :ADS_SEARCH_HANDLE
   .ends
endif

ifndef __IDirectorySchemaMgmt_INTERFACE_DEFINED__
define __IDirectorySchemaMgmt_INTERFACE_DEFINED__

DEFINE_IIDX(IDirectorySchemaMgmt, "75db3b9c-a4d8-11d0-a79c-00c04fd8d5a8")

.comdef IDirectorySchemaMgmt : public IUnknown

    EnumAttributes	proc :ptr, :DWORD, :ptr, :ptr
    CreateAttributeDefinition proc :LPWSTR, :PADS_ATTR_DEF
    WriteAttributeDefinition proc :LPWSTR, :PADS_ATTR_DEF
    DeleteAttributeDefinition proc :LPWSTR
    EnumClasses		proc :ptr, :DWORD, :ptr, :ptr
    WriteClassDefinition proc :LPWSTR, :PADS_CLASS_DEF
    CreateClassDefinition proc :LPWSTR, :PADS_CLASS_DEF
    DeleteClassDefinition proc :LPWSTR
   .ends
endif

ifndef __IADsAggregatee_INTERFACE_DEFINED__
define __IADsAggregatee_INTERFACE_DEFINED__

DEFINE_IIDX(IADsAggregatee, "1346ce8c-9039-11d0-8528-00c04fd8d503")

.comdef IADsAggregatee : public IUnknown

    ConnectAsAggregatee proc :ptr
    DisconnectAsAggregatee proc
    RelinquishInterface proc :REFIID
    RestoreInterface	proc :REFIID
   .ends
endif

ifndef __IADsAggregator_INTERFACE_DEFINED__
define __IADsAggregator_INTERFACE_DEFINED__

DEFINE_IIDX(IADsAggregator, "52db5fb0-941f-11d0-8529-00c04fd8d503")

.comdef IADsAggregator : public IUnknown

    ConnectAsAggregator proc :ptr
    DisconnectAsAggregator proc
   .ends
endif

ifndef __IADsAccessControlEntry_INTERFACE_DEFINED__
define __IADsAccessControlEntry_INTERFACE_DEFINED__

DEFINE_IIDX(IADsAccessControlEntry, "b4f3a14c-9bdd-11d0-852c-00c04fd8d503")

.comdef IADsAccessControlEntry : public IDispatch

    get_AccessMask	proc :ptr
    put_AccessMask	proc :LONG
    get_AceType		proc :ptr
    put_AceType		proc :LONG
    get_AceFlags	proc :ptr
    put_AceFlags	proc :LONG
    get_Flags		proc :ptr
    put_Flags		proc :LONG
    get_ObjectType	proc :ptr
    put_ObjectType	proc :BSTR
    get_InheritedObjectType proc :ptr
    put_InheritedObjectType proc :BSTR
    get_Trustee		proc :ptr
    put_Trustee		proc :BSTR
   .ends
endif

DEFINE_GUIDS(CLSID_AccessControlEntry, "b75ac000-9bdd-11d0-852c-00c04fd8d503")

ifndef __IADsAccessControlList_INTERFACE_DEFINED__
define __IADsAccessControlList_INTERFACE_DEFINED__

DEFINE_IIDX(IADsAccessControlList, "b7ee91cc-9bdd-11d0-852c-00c04fd8d503")

.comdef IADsAccessControlList : public IDispatch

    get_AclRevision	proc :ptr
    put_AclRevision	proc :LONG
    get_AceCount	proc :ptr
    put_AceCount	proc :LONG
    AddAce		proc :ptr
    RemoveAce		proc :ptr
    CopyAccessList	proc :ptr
    get__NewEnum	proc :ptr
   .ends
endif

DEFINE_GUIDS(CLSID_AccessControlList, "b85ea052-9bdd-11d0-852c-00c04fd8d503")

ifndef __IADsSecurityDescriptor_INTERFACE_DEFINED__
define __IADsSecurityDescriptor_INTERFACE_DEFINED__

DEFINE_IIDX(IADsSecurityDescriptor, "b8c787ca-9bdd-11d0-852c-00c04fd8d503")

.comdef IADsSecurityDescriptor : public IDispatch

    get_Revision	proc :ptr
    put_Revision	proc :LONG
    get_Control		proc :ptr
    put_Control		proc :LONG
    get_Owner		proc :ptr
    put_Owner		proc :BSTR
    get_OwnerDefaulted	proc :ptr
    put_OwnerDefaulted	proc :VARIANT_BOOL
    get_Group		proc :ptr
    put_Group		proc :BSTR
    get_GroupDefaulted	proc :ptr
    put_GroupDefaulted	proc :VARIANT_BOOL
    get_DiscretionaryAcl proc :ptr
    put_DiscretionaryAcl proc :ptr
    get_DaclDefaulted	proc :ptr
    put_DaclDefaulted	proc :VARIANT_BOOL
    get_SystemAcl	proc :ptr
    put_SystemAcl	proc :ptr
    get_SaclDefaulted	proc :ptr
    put_SaclDefaulted	proc :VARIANT_BOOL
    CopySecurityDescriptor proc :ptr
   .ends
endif

DEFINE_GUIDS(CLSID_SecurityDescriptor, "b958f73c-9bdd-11d0-852c-00c04fd8d503")

ifndef __IADsLargeInteger_INTERFACE_DEFINED__
define __IADsLargeInteger_INTERFACE_DEFINED__

DEFINE_IIDX(IADsLargeInteger, "9068270b-0939-11d1-8be1-00c04fd8d503")

.comdef IADsLargeInteger : public IDispatch

    get_HighPart	proc :ptr
    put_HighPart	proc :LONG
    get_LowPart		proc :ptr
    put_LowPart		proc :LONG
   .ends
endif

DEFINE_GUIDS(CLSID_LargeInteger, "927971f5-0939-11d1-8be1-00c04fd8d503")

ifndef __IADsNameTranslate_INTERFACE_DEFINED__
define __IADsNameTranslate_INTERFACE_DEFINED__

DEFINE_IIDX(IADsNameTranslate, "b1b272a3-3625-11d1-a3a4-00c04fb950dc")

.comdef IADsNameTranslate : public IDispatch

    put_ChaseReferral	proc :LONG
    Init		proc :LONG, :BSTR
    InitEx		proc :LONG, :BSTR, :BSTR, :BSTR, :BSTR
    Set			proc :LONG, :BSTR
    Get			proc :LONG, :ptr
    SetEx		proc :LONG, :VARIANT
    GetEx		proc :LONG, :ptr
   .ends
endif

DEFINE_GUIDS(CLSID_NameTranslate, "274fae1f-3626-11d1-a3a4-00c04fb950dc")

ifndef __IADsCaseIgnoreList_INTERFACE_DEFINED__
define __IADsCaseIgnoreList_INTERFACE_DEFINED__

DEFINE_IIDX(IADsCaseIgnoreList, "7b66b533-4680-11d1-a3b4-00c04fb950dc")

.comdef IADsCaseIgnoreList : public IDispatch

    get_CaseIgnoreList	proc :ptr
    put_CaseIgnoreList	proc :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_CaseIgnoreList, "15f88a55-4680-11d1-a3b4-00c04fb950dc")

ifndef __IADsFaxNumber_INTERFACE_DEFINED__
define __IADsFaxNumber_INTERFACE_DEFINED__

DEFINE_IIDX(IADsFaxNumber, "a910dea9-4680-11d1-a3b4-00c04fb950dc")

.comdef IADsFaxNumber : public IDispatch

    get_TelephoneNumber proc :ptr
    put_TelephoneNumber proc :BSTR
    get_Parameters	proc :ptr
    put_Parameters	proc :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_FaxNumber, "a5062215-4681-11d1-a3b4-00c04fb950dc")

ifndef __IADsNetAddress_INTERFACE_DEFINED__
define __IADsNetAddress_INTERFACE_DEFINED__

DEFINE_IIDX(IADsNetAddress, "b21a50a9-4080-11d1-a3ac-00c04fb950dc")

.comdef IADsNetAddress : public IDispatch

    get_AddressType	proc :ptr
    put_AddressType	proc :LONG
    get_Address		proc :ptr
    put_Address		proc :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_NetAddress, "b0b71247-4080-11d1-a3ac-00c04fb950dc")

ifndef __IADsOctetList_INTERFACE_DEFINED__
define __IADsOctetList_INTERFACE_DEFINED__

DEFINE_IIDX(IADsOctetList, "7b28b80f-4680-11d1-a3b4-00c04fb950dc")

.comdef IADsOctetList : public IDispatch

    get_OctetList	proc :ptr
    put_OctetList	proc :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_OctetList, "1241400f-4680-11d1-a3b4-00c04fb950dc")

ifndef __IADsEmail_INTERFACE_DEFINED__
define __IADsEmail_INTERFACE_DEFINED__

DEFINE_IIDX(IADsEmail, "97af011a-478e-11d1-a3b4-00c04fb950dc")

.comdef IADsEmail : public IDispatch

    get_Type		proc :ptr
    put_Type		proc :LONG
    get_Address		proc :ptr
    put_Address		proc :BSTR
   .ends
endif

DEFINE_GUIDS(CLSID_Email, "8f92a857-478e-11d1-a3b4-00c04fb950dc")

ifndef __IADsPath_INTERFACE_DEFINED__
define __IADsPath_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPath, "b287fcd5-4080-11d1-a3ac-00c04fb950dc")

.comdef IADsPath : public IDispatch

    get_Type		proc :ptr
    put_Type		proc :LONG
    get_VolumeName	proc :ptr
    put_VolumeName	proc :BSTR
    get_Path		proc :ptr
    put_Path		proc :BSTR
   .ends
endif

DEFINE_GUIDS(CLSID_Path, "b2538919-4080-11d1-a3ac-00c04fb950dc")

ifndef __IADsReplicaPointer_INTERFACE_DEFINED__
define __IADsReplicaPointer_INTERFACE_DEFINED__

DEFINE_IIDX(IADsReplicaPointer, "f60fb803-4080-11d1-a3ac-00c04fb950dc")

.comdef IADsReplicaPointer : public IDispatch

    get_ServerName	proc :ptr
    put_ServerName	proc :BSTR
    get_ReplicaType	proc :ptr
    put_ReplicaType	proc :LONG
    get_ReplicaNumber	proc :ptr
    put_ReplicaNumber	proc :LONG
    get_Count		proc :ptr
    put_Count		proc :LONG
    get_ReplicaAddressHints proc :ptr
    put_ReplicaAddressHints proc :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_ReplicaPointer, "f5d1badf-4080-11d1-a3ac-00c04fb950dc")

ifndef __IADsAcl_INTERFACE_DEFINED__
define __IADsAcl_INTERFACE_DEFINED__

DEFINE_IIDX(IADsAcl, "8452d3ab-0869-11d1-a377-00c04fb950dc")

.comdef IADsAcl : public IDispatch

    get_ProtectedAttrName proc :ptr
    put_ProtectedAttrName proc :BSTR
    get_SubjectName	proc :ptr
    put_SubjectName	proc :BSTR
    get_Privileges	proc :ptr
    put_Privileges	proc :LONG
    CopyAcl		proc :ptr
   .ends
endif

ifndef __IADsTimestamp_INTERFACE_DEFINED__
define __IADsTimestamp_INTERFACE_DEFINED__

DEFINE_IIDX(IADsTimestamp, "b2f5a901-4080-11d1-a3ac-00c04fb950dc")

.comdef IADsTimestamp : public IDispatch

    get_WholeSeconds	proc :ptr
    put_WholeSeconds	proc :LONG
    get_EventID		proc :ptr
    put_EventID		proc :LONG
   .ends
endif

DEFINE_GUIDS(CLSID_Timestamp, "b2bed2eb-4080-11d1-a3ac-00c04fb950dc")

ifndef __IADsPostalAddress_INTERFACE_DEFINED__
define __IADsPostalAddress_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPostalAddress, "7adecf29-4680-11d1-a3b4-00c04fb950dc")

.comdef IADsPostalAddress : public IDispatch

    get_PostalAddress	proc :ptr
    put_PostalAddress	proc :VARIANT
   .ends
endif

DEFINE_GUIDS(CLSID_PostalAddress, "0a75afcd-4680-11d1-a3b4-00c04fb950dc")

ifndef __IADsBackLink_INTERFACE_DEFINED__
define __IADsBackLink_INTERFACE_DEFINED__

DEFINE_IIDX(IADsBackLink, "fd1302bd-4080-11d1-a3ac-00c04fb950dc")

.comdef IADsBackLink : public IDispatch

    get_RemoteID	proc :ptr
    put_RemoteID	proc :LONG
    get_ObjectName	proc :ptr
    put_ObjectName	proc :BSTR
   .ends
endif

DEFINE_GUIDS(CLSID_BackLink, "fcbf906f-4080-11d1-a3ac-00c04fb950dc")

ifndef __IADsTypedName_INTERFACE_DEFINED__
define __IADsTypedName_INTERFACE_DEFINED__

DEFINE_IIDX(IADsTypedName, "b371a349-4080-11d1-a3ac-00c04fb950dc")

.comdef IADsTypedName : public IDispatch

    get_ObjectName	proc :ptr
    put_ObjectName	proc :BSTR
    get_Level		proc :ptr
    put_Level		proc :LONG
    get_Interval	proc :ptr
    put_Interval	proc :LONG
   .ends
endif

DEFINE_GUIDS(CLSID_TypedName, "b33143cb-4080-11d1-a3ac-00c04fb950dc")

ifndef __IADsHold_INTERFACE_DEFINED__
define __IADsHold_INTERFACE_DEFINED__

DEFINE_IIDX(IADsHold, "b3eb3b37-4080-11d1-a3ac-00c04fb950dc")

.comdef IADsHold : public IDispatch

    get_ObjectName	proc :ptr
    put_ObjectName	proc :BSTR
    get_Amount		proc :ptr
    put_Amount		proc :LONG
   .ends
endif

DEFINE_GUIDS(CLSID_Hold, "b3ad3e13-4080-11d1-a3ac-00c04fb950dc")

ifndef __IADsObjectOptions_INTERFACE_DEFINED__
define __IADsObjectOptions_INTERFACE_DEFINED__

DEFINE_IIDX(IADsObjectOptions, "46f14fda-232b-11d1-a808-00c04fd8d5a8")

.comdef IADsObjectOptions : public IDispatch

    GetOption		proc :LONG, :ptr
    SetOption		proc :LONG, :VARIANT
   .ends
endif

ifndef __IADsPathname_INTERFACE_DEFINED__
define __IADsPathname_INTERFACE_DEFINED__

DEFINE_IIDX(IADsPathname, "d592aed4-f420-11d0-a36e-00c04fb950dc")

.comdef IADsPathname : public IDispatch

    Set			proc :BSTR, :LONG
    SetDisplayType	proc :LONG
    Retrieve		proc :LONG, :ptr
    GetNumElements	proc :ptr
    GetElement		proc :LONG, :ptr
    AddLeafElement	proc :BSTR
    RemoveLeafElement	proc
    CopyPath		proc :ptr
    GetEscapedElement	proc :LONG, :BSTR, :ptr
    get_EscapedMode	proc :ptr
    put_EscapedMode	proc :LONG
   .ends
endif

DEFINE_GUIDS(CLSID_Pathname, "080d0d78-f421-11d0-a36e-00c04fb950dc")

ifndef __IADsADSystemInfo_INTERFACE_DEFINED__
define __IADsADSystemInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IADsADSystemInfo, "5BB11929-AFD1-11d2-9CB9-0000F87A369E")

.comdef IADsADSystemInfo : public IDispatch

    get_UserName	proc :ptr
    get_ComputerName	proc :ptr
    get_SiteName	proc :ptr
    get_DomainShortName proc :ptr
    get_DomainDNSName	proc :ptr
    get_ForestDNSName	proc :ptr
    get_PDCRoleOwner	proc :ptr
    get_SchemaRoleOwner proc :ptr
    get_IsNativeMode	proc :ptr
    GetAnyDCName	proc :ptr
    GetDCSiteName	proc :BSTR, :ptr
    RefreshSchemaCache	proc
    GetTrees		proc :ptr
   .ends
endif

DEFINE_GUIDS(CLSID_ADSystemInfo, "50B6327F-AFD1-11d2-9CB9-0000F87A369E")

ifndef __IADsWinNTSystemInfo_INTERFACE_DEFINED__
define __IADsWinNTSystemInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IADsWinNTSystemInfo, "6C6D65DC-AFD1-11d2-9CB9-0000F87A369E")

.comdef IADsWinNTSystemInfo : public IDispatch

    get_UserName	proc :ptr
    get_ComputerName	proc :ptr
    get_DomainName	proc :ptr
    get_PDC		proc :ptr
   .ends
endif

DEFINE_GUIDS(CLSID_WinNTSystemInfo, "66182EC4-AFD1-11d2-9CB9-0000F87A369E")

ifndef __IADsDNWithBinary_INTERFACE_DEFINED__
define __IADsDNWithBinary_INTERFACE_DEFINED__

DEFINE_IIDX(IADsDNWithBinary, "7e99c0a2-f935-11d2-ba96-00c04fb6d0d1")

.comdef IADsDNWithBinary : public IDispatch

    get_BinaryValue	proc :ptr
    put_BinaryValue	proc :VARIANT
    get_DNString	proc :ptr
    put_DNString	proc :BSTR
   .ends
endif

DEFINE_GUIDS(CLSID_DNWithBinary, "7e99c0a3-f935-11d2-ba96-00c04fb6d0d1")

ifndef __IADsDNWithString_INTERFACE_DEFINED__
define __IADsDNWithString_INTERFACE_DEFINED__

DEFINE_IIDX(IADsDNWithString, "370df02e-f934-11d2-ba96-00c04fb6d0d1")

.comdef IADsDNWithString : public IDispatch

    get_StringValue	proc :ptr
    put_StringValue	proc :BSTR
    get_DNString	proc :ptr
    put_DNString	proc :BSTR
   .ends
endif

DEFINE_GUIDS(CLSID_DNWithString, "334857cc-f934-11d2-ba96-00c04fb6d0d1")

ifndef __IADsSecurityUtility_INTERFACE_DEFINED__
define __IADsSecurityUtility_INTERFACE_DEFINED__

DEFINE_IIDX(IADsSecurityUtility, "a63251b2-5f21-474b-ab52-4a8efad10895")

.comdef IADsSecurityUtility : public IDispatch

    GetSecurityDescriptor proc :VARIANT, :LONG, :LONG, :ptr
    SetSecurityDescriptor proc :VARIANT, :LONG, :VARIANT, :LONG
    ConvertSecurityDescriptor proc :VARIANT, :LONG, :LONG, :ptr
    get_SecurityMask	proc :ptr
    put_SecurityMask	proc :LONG
   .ends
endif

DEFINE_GUIDS(CLSID_ADsSecurityUtility, "f270c64a-ffb8-4ae4-85fe-3a75e5347966")

endif ;; __ActiveDs_LIBRARY_DEFINED__

endif ;; __iads_h__

.pragma list(pop)
