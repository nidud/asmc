ifndef _LSALOOKUP_
define _LSALOOKUP_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

;ifdef _NTDEF_
;PLSA_UNICODE_STRING     typedef ptr LSA_UNICODE_STRING
;PLSA_STRING             typedef ptr LSA_STRING
;PLSA_OBJECT_ATTRIBUTES  typedef ptr LSA_OBJECT_ATTRIBUTES
;else

LSA_UNICODE_STRING      struct
Length                  USHORT ?
MaximumLength           USHORT ?
Buffer                  PWSTR ?
LSA_UNICODE_STRING      ends
PLSA_UNICODE_STRING     typedef ptr LSA_UNICODE_STRING

LSA_STRING              struct
Length                  USHORT ?
MaximumLength           USHORT ?
Buffer                  PCHAR ?
LSA_STRING              ends
PLSA_STRING             typedef ptr LSA_STRING

LSA_OBJECT_ATTRIBUTES   struct
Length                  ULONG ?
RootDirectory           HANDLE ?
ObjectName              PLSA_UNICODE_STRING ?
Attributes              ULONG ?
SecurityDescriptor      PVOID ?
SecurityQualityOfService PVOID ?
LSA_OBJECT_ATTRIBUTES   ends
PLSA_OBJECT_ATTRIBUTES  typedef ptr LSA_OBJECT_ATTRIBUTES

;endif

LSA_TRUST_INFORMATION   struct
Name                    LSA_UNICODE_STRING <>
Sid                     PSID ?
LSA_TRUST_INFORMATION   ends
PLSA_TRUST_INFORMATION  typedef ptr LSA_TRUST_INFORMATION

LSA_REFERENCED_DOMAIN_LIST struct
Entries                 ULONG ?
Domains                 PLSA_TRUST_INFORMATION ?
LSA_REFERENCED_DOMAIN_LIST ends
PLSA_REFERENCED_DOMAIN_LIST typedef ptr LSA_REFERENCED_DOMAIN_LIST

if (_WIN32_WINNT ge 0x0501)
LSA_TRANSLATED_SID2     struct
Use                     SID_NAME_USE ?
Sid                     PSID ?
DomainIndex             LONG ?
Flags                   ULONG ?
LSA_TRANSLATED_SID2     ends
PLSA_TRANSLATED_SID2    typedef ptr LSA_TRANSLATED_SID2
endif

LSA_TRANSLATED_NAME     struct
Use                     SID_NAME_USE ?
Name                    LSA_UNICODE_STRING <>
DomainIndex             LONG ?
LSA_TRANSLATED_NAME     ends
PLSA_TRANSLATED_NAME    typedef ptr LSA_TRANSLATED_NAME

POLICY_ACCOUNT_DOMAIN_INFO struct
DomainName              LSA_UNICODE_STRING <>
DomainSid               PSID ?
POLICY_ACCOUNT_DOMAIN_INFO ends
PPOLICY_ACCOUNT_DOMAIN_INFO typedef ptr POLICY_ACCOUNT_DOMAIN_INFO

POLICY_DNS_DOMAIN_INFO  struct
Name                    LSA_UNICODE_STRING <>
DnsDomainName           LSA_UNICODE_STRING <>
DnsForestName           LSA_UNICODE_STRING <>
DomainGuid              GUID <>
Sid                     PSID ?
POLICY_DNS_DOMAIN_INFO  ends
PPOLICY_DNS_DOMAIN_INFO typedef ptr POLICY_DNS_DOMAIN_INFO

define LOOKUP_VIEW_LOCAL_INFORMATION       0x00000001
define LOOKUP_TRANSLATE_NAMES              0x00000800

.enum LSA_LOOKUP_DOMAIN_INFO_CLASS {
    AccountDomainInformation = 5,
    DnsDomainInformation     = 12
    }

PLSA_LOOKUP_HANDLE      typedef ptr LSA_LOOKUP_HANDLE

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

LsaLookupOpenLocalPolicy proto WINAPI :PLSA_OBJECT_ATTRIBUTES, :ACCESS_MASK, :PLSA_LOOKUP_HANDLE
LsaLookupClose proto WINAPI :LSA_LOOKUP_HANDLE
LsaLookupTranslateSids proto WINAPI :LSA_LOOKUP_HANDLE, :ULONG, :ptr, :ptr, :ptr

if (_WIN32_WINNT ge 0x0501)
LsaLookupTranslateNames proto WINAPI :LSA_LOOKUP_HANDLE, :ULONG, :ULONG, :PLSA_UNICODE_STRING, :ptr, :ptr
endif

LsaLookupGetDomainInfo proto WINAPI :LSA_LOOKUP_HANDLE, :LSA_LOOKUP_DOMAIN_INFO_CLASS, :ptr
LsaLookupFreeMemory proto WINAPI :PVOID

endif

endif

