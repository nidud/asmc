include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef _WININET_
include SpecStrings.inc
define _WININET_

.pragma pack(push, size_t)

.pragma comment(lib, wininet)

HINTERNET               typedef ptr
LPHINTERNET             typedef ptr HINTERNET

INTERNET_PORT           typedef WORD
LPINTERNET_PORT         typedef ptr INTERNET_PORT

define INTERNET_INVALID_PORT_NUMBER    0

define INTERNET_DEFAULT_FTP_PORT       21
define INTERNET_DEFAULT_GOPHER_PORT    70
define INTERNET_DEFAULT_HTTP_PORT      80
define INTERNET_DEFAULT_HTTPS_PORT     443
define INTERNET_DEFAULT_SOCKS_PORT     1080

define INTERNET_MAX_HOST_NAME_LENGTH   256
define INTERNET_MAX_USER_NAME_LENGTH   128
define INTERNET_MAX_PASSWORD_LENGTH    128
define INTERNET_MAX_PORT_NUMBER_LENGTH 5
define INTERNET_MAX_PORT_NUMBER_VALUE  65535
define INTERNET_MAX_PATH_LENGTH        2048
define INTERNET_MAX_SCHEME_LENGTH      32
define INTERNET_MAX_URL_LENGTH         (INTERNET_MAX_SCHEME_LENGTH + tchar_t*3 + INTERNET_MAX_PATH_LENGTH)

define INTERNET_KEEP_ALIVE_UNKNOWN     (-1)
define INTERNET_KEEP_ALIVE_ENABLED     1
define INTERNET_KEEP_ALIVE_DISABLED    0

define INTERNET_REQFLAG_FROM_CACHE     0x00000001
define INTERNET_REQFLAG_ASYNC          0x00000002
define INTERNET_REQFLAG_VIA_PROXY      0x00000004
define INTERNET_REQFLAG_NO_HEADERS     0x00000008
define INTERNET_REQFLAG_PASSIVE        0x00000010
define INTERNET_REQFLAG_CACHE_WRITE_DISABLED 0x00000040
define INTERNET_REQFLAG_NET_TIMEOUT    0x00000080

define INTERNET_FLAG_IDN_DIRECT        0x00000001
define INTERNET_FLAG_IDN_PROXY         0x00000002

define INTERNET_FLAG_RELOAD            0x80000000

define INTERNET_FLAG_RAW_DATA          0x40000000
define INTERNET_FLAG_EXISTING_CONNECT  0x20000000

define INTERNET_FLAG_ASYNC             0x10000000

define INTERNET_FLAG_PASSIVE           0x08000000

define INTERNET_FLAG_NO_CACHE_WRITE    0x04000000
define INTERNET_FLAG_DONT_CACHE        INTERNET_FLAG_NO_CACHE_WRITE
define INTERNET_FLAG_MAKE_PERSISTENT   0x02000000
define INTERNET_FLAG_FROM_CACHE        0x01000000
define INTERNET_FLAG_OFFLINE           INTERNET_FLAG_FROM_CACHE

define INTERNET_FLAG_SECURE            0x00800000
define INTERNET_FLAG_KEEP_CONNECTION   0x00400000
define INTERNET_FLAG_NO_AUTO_REDIRECT  0x00200000
define INTERNET_FLAG_READ_PREFETCH     0x00100000
define INTERNET_FLAG_NO_COOKIES        0x00080000
define INTERNET_FLAG_NO_AUTH           0x00040000
define INTERNET_FLAG_RESTRICTED_ZONE   0x00020000
define INTERNET_FLAG_CACHE_IF_NET_FAIL 0x00010000

define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP   0x00008000
define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS  0x00004000
define INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  0x00002000
define INTERNET_FLAG_IGNORE_CERT_CN_INVALID    0x00001000

define INTERNET_FLAG_RESYNCHRONIZE     0x00000800
define INTERNET_FLAG_HYPERLINK         0x00000400
define INTERNET_FLAG_NO_UI             0x00000200
define INTERNET_FLAG_PRAGMA_NOCACHE    0x00000100
define INTERNET_FLAG_CACHE_ASYNC       0x00000080
define INTERNET_FLAG_FORMS_SUBMIT      0x00000040
define INTERNET_FLAG_FWD_BACK          0x00000020
define INTERNET_FLAG_NEED_FILE         0x00000010
define INTERNET_FLAG_MUST_CACHE_REQUEST INTERNET_FLAG_NEED_FILE

define INTERNET_FLAG_TRANSFER_ASCII    FTP_TRANSFER_TYPE_ASCII
define INTERNET_FLAG_TRANSFER_BINARY   FTP_TRANSFER_TYPE_BINARY

define SECURITY_INTERNET_MASK  (INTERNET_FLAG_IGNORE_CERT_CN_INVALID    or \
                                INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  or \
                                INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS  or \
                                INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP   )

define SECURITY_IGNORE_ERROR_MASK  (INTERNET_FLAG_IGNORE_CERT_CN_INVALID    or \
                                     INTERNET_FLAG_IGNORE_CERT_DATE_INVALID or \
                                     SECURITY_FLAG_IGNORE_UNKNOWN_CA        or \
                                     SECURITY_FLAG_IGNORE_REVOCATION        or \
                                     SECURITY_FLAG_IGNORE_WEAK_SIGNATURE)

define INTERNET_FLAGS_MASK     (INTERNET_FLAG_RELOAD              or \
                                INTERNET_FLAG_RAW_DATA            or \
                                INTERNET_FLAG_EXISTING_CONNECT    or \
                                INTERNET_FLAG_ASYNC               or \
                                INTERNET_FLAG_PASSIVE             or \
                                INTERNET_FLAG_NO_CACHE_WRITE      or \
                                INTERNET_FLAG_MAKE_PERSISTENT     or \
                                INTERNET_FLAG_FROM_CACHE          or \
                                INTERNET_FLAG_SECURE              or \
                                INTERNET_FLAG_KEEP_CONNECTION     or \
                                INTERNET_FLAG_NO_AUTO_REDIRECT    or \
                                INTERNET_FLAG_READ_PREFETCH       or \
                                INTERNET_FLAG_NO_COOKIES          or \
                                INTERNET_FLAG_NO_AUTH             or \
                                INTERNET_FLAG_CACHE_IF_NET_FAIL   or \
                                SECURITY_INTERNET_MASK            or \
                                INTERNET_FLAG_RESYNCHRONIZE       or \
                                INTERNET_FLAG_HYPERLINK           or \
                                INTERNET_FLAG_NO_UI               or \
                                INTERNET_FLAG_PRAGMA_NOCACHE      or \
                                INTERNET_FLAG_CACHE_ASYNC         or \
                                INTERNET_FLAG_FORMS_SUBMIT        or \
                                INTERNET_FLAG_NEED_FILE           or \
                                INTERNET_FLAG_RESTRICTED_ZONE     or \
                                INTERNET_FLAG_TRANSFER_BINARY     or \
                                INTERNET_FLAG_TRANSFER_ASCII      or \
                                INTERNET_FLAG_FWD_BACK            or \
                                INTERNET_FLAG_BGUPDATE            or \
                                )



define INTERNET_ERROR_MASK_INSERT_CDROM                    0x1
define INTERNET_ERROR_MASK_COMBINED_SEC_CERT               0x2
define INTERNET_ERROR_MASK_NEED_MSN_SSPI_PKG               0X4
define INTERNET_ERROR_MASK_LOGIN_FAILURE_DISPLAY_ENTITY_BODY 0x8

define INTERNET_OPTIONS_MASK   (not INTERNET_FLAGS_MASK)

define WININET_API_FLAG_ASYNC          0x00000001
define WININET_API_FLAG_SYNC           0x00000004
define WININET_API_FLAG_USE_CONTEXT    0x00000008

define INTERNET_NO_CALLBACK            0

.enum INTERNET_SCHEME {
    INTERNET_SCHEME_PARTIAL = -2,
    INTERNET_SCHEME_UNKNOWN = -1,
    INTERNET_SCHEME_DEFAULT = 0,
    INTERNET_SCHEME_FTP,
    INTERNET_SCHEME_GOPHER,
    INTERNET_SCHEME_HTTP,
    INTERNET_SCHEME_HTTPS,
    INTERNET_SCHEME_FILE,
    INTERNET_SCHEME_NEWS,
    INTERNET_SCHEME_MAILTO,
    INTERNET_SCHEME_SOCKS,
    INTERNET_SCHEME_JAVASCRIPT,
    INTERNET_SCHEME_VBSCRIPT,
    INTERNET_SCHEME_RES,
    INTERNET_SCHEME_FIRST = INTERNET_SCHEME_FTP,
    INTERNET_SCHEME_LAST = INTERNET_SCHEME_RES
    }
LPINTERNET_SCHEME typedef ptr INTERNET_SCHEME

INTERNET_ASYNC_RESULT   struct
dwResult                DWORD_PTR ?
dwError                 DWORD ?
INTERNET_ASYNC_RESULT   ends
LPINTERNET_ASYNC_RESULT typedef ptr INTERNET_ASYNC_RESULT

INTERNET_DIAGNOSTIC_SOCKET_INFO struct
Socket                  DWORD_PTR ?
SourcePort              DWORD ?
DestPort                DWORD ?
Flags                   DWORD ?
INTERNET_DIAGNOSTIC_SOCKET_INFO ends
LPINTERNET_DIAGNOSTIC_SOCKET_INFO typedef ptr INTERNET_DIAGNOSTIC_SOCKET_INFO

define IDSI_FLAG_KEEP_ALIVE    0x00000001
define IDSI_FLAG_SECURE        0x00000002
define IDSI_FLAG_PROXY         0x00000004
define IDSI_FLAG_TUNNEL        0x00000008

INTERNET_PROXY_INFO     struct
dwAccessType            DWORD ?
lpszProxy               LPCTSTR ?
lpszProxyBypass         LPCTSTR ?
INTERNET_PROXY_INFO     ends
LPINTERNET_PROXY_INFO   typedef ptr INTERNET_PROXY_INFO

INTERNET_PER_CONN_OPTIONA struct
dwOption                DWORD ?
union Value
 dwValue                DWORD ?
 pszValue               LPSTR ?
 ftValue                FILETIME <>
ends
INTERNET_PER_CONN_OPTIONA ends
LPINTERNET_PER_CONN_OPTIONA typedef ptr INTERNET_PER_CONN_OPTIONA
INTERNET_PER_CONN_OPTIONW struct
dwOption                DWORD ?
union Value
 dwValue                DWORD ?
 pszValue               LPWSTR ?
 ftValue                FILETIME <>
ends
INTERNET_PER_CONN_OPTIONW ends
LPINTERNET_PER_CONN_OPTIONW typedef ptr INTERNET_PER_CONN_OPTIONW
ifdef _UNICODE
INTERNET_PER_CONN_OPTION typedef INTERNET_PER_CONN_OPTIONW
LPINTERNET_PER_CONN_OPTION typedef LPINTERNET_PER_CONN_OPTIONW
else
INTERNET_PER_CONN_OPTION typedef INTERNET_PER_CONN_OPTIONA
LPINTERNET_PER_CONN_OPTION typedef LPINTERNET_PER_CONN_OPTIONA
endif

INTERNET_PER_CONN_OPTION_LISTA struct
dwSize                  DWORD ?
pszConnection           LPSTR ?
dwOptionCount           DWORD ?
dwOptionError           DWORD ?
pOptions                LPINTERNET_PER_CONN_OPTIONA ?
INTERNET_PER_CONN_OPTION_LISTA ends
LPINTERNET_PER_CONN_OPTION_LISTA typedef ptr INTERNET_PER_CONN_OPTION_LISTA
INTERNET_PER_CONN_OPTION_LISTW struct
dwSize                  DWORD ?
pszConnection           LPWSTR ?
dwOptionCount           DWORD ?
dwOptionError           DWORD ?
pOptions                LPINTERNET_PER_CONN_OPTIONW ?
INTERNET_PER_CONN_OPTION_LISTW ends
LPINTERNET_PER_CONN_OPTION_LISTW typedef ptr INTERNET_PER_CONN_OPTION_LISTW
ifdef _UNICODE
INTERNET_PER_CONN_OPTION_LIST typedef INTERNET_PER_CONN_OPTION_LISTW
LPINTERNET_PER_CONN_OPTION_LIST typedef LPINTERNET_PER_CONN_OPTION_LISTW
else
INTERNET_PER_CONN_OPTION_LIST typedef INTERNET_PER_CONN_OPTION_LISTA
LPINTERNET_PER_CONN_OPTION_LIST typedef LPINTERNET_PER_CONN_OPTION_LISTA
endif

define INTERNET_PER_CONN_FLAGS                         1
define INTERNET_PER_CONN_PROXY_SERVER                  2
define INTERNET_PER_CONN_PROXY_BYPASS                  3
define INTERNET_PER_CONN_AUTOCONFIG_URL                4
define INTERNET_PER_CONN_AUTODISCOVERY_FLAGS           5
define INTERNET_PER_CONN_AUTOCONFIG_SECONDARY_URL      6
define INTERNET_PER_CONN_AUTOCONFIG_RELOAD_DELAY_MINS  7
define INTERNET_PER_CONN_AUTOCONFIG_LAST_DETECT_TIME   8
define INTERNET_PER_CONN_AUTOCONFIG_LAST_DETECT_URL    9
define INTERNET_PER_CONN_FLAGS_UI                      10

define PROXY_TYPE_DIRECT                               0x00000001
define PROXY_TYPE_PROXY                                0x00000002
define PROXY_TYPE_AUTO_PROXY_URL                       0x00000004
define PROXY_TYPE_AUTO_DETECT                          0x00000008

define AUTO_PROXY_FLAG_USER_SET                        0x00000001
define AUTO_PROXY_FLAG_ALWAYS_DETECT                   0x00000002
define AUTO_PROXY_FLAG_DETECTION_RUN                   0x00000004
define AUTO_PROXY_FLAG_MIGRATED                        0x00000008
define AUTO_PROXY_FLAG_DONT_CACHE_PROXY_RESULT         0x00000010
define AUTO_PROXY_FLAG_CACHE_INIT_RUN                  0x00000020
define AUTO_PROXY_FLAG_DETECTION_SUSPECT               0x00000040

INTERNET_VERSION_INFO   struct
dwMajorVersion          DWORD ?
dwMinorVersion          DWORD ?
INTERNET_VERSION_INFO   ends
LPINTERNET_VERSION_INFO typedef ptr INTERNET_VERSION_INFO

HTTP_VERSION_INFO       struct
dwMajorVersion          DWORD ?
dwMinorVersion          DWORD ?
HTTP_VERSION_INFO       ends
LPHTTP_VERSION_INFO     typedef ptr HTTP_VERSION_INFO

INTERNET_CONNECTED_INFO struct
dwConnectedState        DWORD ?
dwFlags                 DWORD ?
INTERNET_CONNECTED_INFO ends
LPINTERNET_CONNECTED_INFO typedef ptr INTERNET_CONNECTED_INFO

define ISO_FORCE_DISCONNECTED  0x00000001

URL_COMPONENTSA         struct
dwStructSize            DWORD ?
lpszScheme              LPSTR ?
dwSchemeLength          DWORD ?
nScheme                 INTERNET_SCHEME ?
lpszHostName            LPSTR ?
dwHostNameLength        DWORD ?
nPort                   INTERNET_PORT ?
lpszUserName            LPSTR ?
dwUserNameLength        DWORD ?
lpszPassword            LPSTR ?
dwPasswordLength        DWORD ?
lpszUrlPath             LPSTR ?
dwUrlPathLength         DWORD ?
lpszExtraInfo           LPSTR ?
dwExtraInfoLength       DWORD ?
URL_COMPONENTSA         ends
LPURL_COMPONENTSA       typedef ptr URL_COMPONENTSA
URL_COMPONENTSW         struct
dwStructSize            DWORD ?
lpszScheme              LPWSTR ?
dwSchemeLength          DWORD ?
nScheme                 INTERNET_SCHEME ?
lpszHostName            LPWSTR ?
dwHostNameLength        DWORD ?
nPort                   INTERNET_PORT ?
lpszUserName            LPWSTR ?
dwUserNameLength        DWORD ?
lpszPassword            LPWSTR ?
dwPasswordLength        DWORD ?
lpszUrlPath             LPWSTR ?
dwUrlPathLength         DWORD ?
lpszExtraInfo           LPWSTR ?
dwExtraInfoLength       DWORD ?
URL_COMPONENTSW         ends
LPURL_COMPONENTSW       typedef ptr URL_COMPONENTSW
ifdef _UNICODE
URL_COMPONENTS          typedef URL_COMPONENTSW
LPURL_COMPONENTS        typedef LPURL_COMPONENTSW
else
URL_COMPONENTS          typedef URL_COMPONENTSA
LPURL_COMPONENTS        typedef LPURL_COMPONENTSA
endif

INTERNET_CERTIFICATE_INFO struct
ftExpiry                FILETIME <>
ftStart                 FILETIME <>
lpszSubjectInfo         LPTSTR ?
lpszIssuerInfo          LPTSTR ?
lpszProtocolName        LPTSTR ?
lpszSignatureAlgName    LPTSTR ?
lpszEncryptionAlgName   LPTSTR ?
dwKeySize               DWORD ?
INTERNET_CERTIFICATE_INFO ends
LPINTERNET_CERTIFICATE_INFO typedef ptr INTERNET_CERTIFICATE_INFO

INTERNET_BUFFERSA       struct
dwStructSize            DWORD ?
Next                    ptr INTERNET_BUFFERSA ?
lpcszHeader             LPCSTR ?
dwHeadersLength         DWORD ?
dwHeadersTotal          DWORD ?
lpvBuffer               LPVOID ?
dwBufferLength          DWORD ?
dwBufferTotal           DWORD ?
dwOffsetLow             DWORD ?
dwOffsetHigh            DWORD ?
INTERNET_BUFFERSA       ends
LPINTERNET_BUFFERSA     typedef ptr INTERNET_BUFFERSA
INTERNET_BUFFERSW       struct
dwStructSize            DWORD ?
Next                    ptr INTERNET_BUFFERSW ?
lpcszHeader             LPCWSTR ?
dwHeadersLength         DWORD ?
dwHeadersTotal          DWORD ?
lpvBuffer               LPVOID ?
dwBufferLength          DWORD ?
dwBufferTotal           DWORD ?
dwOffsetLow             DWORD ?
dwOffsetHigh            DWORD ?
INTERNET_BUFFERSW       ends
LPINTERNET_BUFFERSW     typedef ptr INTERNET_BUFFERSW
ifdef _UNICODE
INTERNET_BUFFERS        typedef INTERNET_BUFFERSW
LPINTERNET_BUFFERS      typedef LPINTERNET_BUFFERSW
else
INTERNET_BUFFERS        typedef INTERNET_BUFFERSA
LPINTERNET_BUFFERS      typedef LPINTERNET_BUFFERSA
endif

InternetTimeFromSystemTimeA proto WINAPI :ptr, :DWORD, :LPSTR, :DWORD
InternetTimeFromSystemTimeW proto WINAPI :ptr, :DWORD, :LPWSTR, :DWORD
ifdef _UNICODE
define InternetTimeFromSystemTime  <InternetTimeFromSystemTimeW>
else
ifdef _WINX32_
define InternetTimeFromSystemTime  <InternetTimeFromSystemTimeA>
else
InternetTimeFromSystemTime proto WINAPI :ptr, :DWORD, :LPSTR, :DWORD
endif
endif

define INTERNET_RFC1123_FORMAT     0
define INTERNET_RFC1123_BUFSIZE   30

InternetTimeToSystemTimeA proto WINAPI :LPCSTR, :ptr, :DWORD
InternetTimeToSystemTimeW proto WINAPI :LPCWSTR, :ptr, :DWORD
ifdef _UNICODE
define InternetTimeToSystemTime  <InternetTimeToSystemTimeW>
else
ifdef _WINX32_
define InternetTimeToSystemTime  <InternetTimeToSystemTimeA>
else
InternetTimeToSystemTime proto WINAPI :LPCSTR, :ptr, :DWORD
endif
endif

InternetCrackUrlA proto WINAPI :LPCSTR, :DWORD, :DWORD, :LPURL_COMPONENTSA
InternetCrackUrlW proto WINAPI :LPCWSTR, :DWORD, :DWORD, :LPURL_COMPONENTSW
ifdef _UNICODE
define InternetCrackUrl  <InternetCrackUrlW>
else
define InternetCrackUrl  <InternetCrackUrlA>
endif

InternetCreateUrlA proto WINAPI :LPURL_COMPONENTSA, :DWORD, :LPSTR, :LPDWORD
InternetCreateUrlW proto WINAPI :LPURL_COMPONENTSW, :DWORD, :LPWSTR, :LPDWORD
ifdef _UNICODE
define InternetCreateUrl  <InternetCreateUrlW>
else
define InternetCreateUrl  <InternetCreateUrlA>
endif

InternetCanonicalizeUrlA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :DWORD
InternetCanonicalizeUrlW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD
ifdef _UNICODE
define InternetCanonicalizeUrl  <InternetCanonicalizeUrlW>
else
define InternetCanonicalizeUrl  <InternetCanonicalizeUrlA>
endif

InternetCombineUrlA proto WINAPI :LPCSTR, :LPCSTR, :LPSTR, :LPDWORD, :DWORD
InternetCombineUrlW proto WINAPI :LPCWSTR, :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD
ifdef _UNICODE
define InternetCombineUrl  <InternetCombineUrlW>
else
define InternetCombineUrl  <InternetCombineUrlA>
endif

define ICU_ESCAPE      0x80000000
define ICU_USERNAME    0x40000000

define ICU_NO_ENCODE   0x20000000
define ICU_DECODE      0x10000000
define ICU_NO_META     0x08000000
define ICU_ENCODE_SPACES_ONLY 0x04000000
define ICU_BROWSER_MODE 0x02000000
define ICU_ENCODE_PERCENT      0x00001000

InternetOpenA proto WINAPI :LPCSTR, :DWORD, :LPCSTR, :LPCSTR, :DWORD
InternetOpenW proto WINAPI :LPCWSTR, :DWORD, :LPCWSTR, :LPCWSTR, :DWORD
ifdef _UNICODE
define InternetOpen  <InternetOpenW>
else
define InternetOpen  <InternetOpenA>
endif

define INTERNET_OPEN_TYPE_PRECONFIG                    0
define INTERNET_OPEN_TYPE_DIRECT                       1
define INTERNET_OPEN_TYPE_PROXY                        3
define INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY  4

define PRE_CONFIG_INTERNET_ACCESS  INTERNET_OPEN_TYPE_PRECONFIG
define LOCAL_INTERNET_ACCESS       INTERNET_OPEN_TYPE_DIRECT
define CERN_PROXY_INTERNET_ACCESS  INTERNET_OPEN_TYPE_PROXY

InternetCloseHandle proto WINAPI :HINTERNET

InternetConnectA proto WINAPI :HINTERNET, :LPCSTR, :INTERNET_PORT, :LPCSTR, :LPCSTR, :DWORD, :DWORD, :DWORD_PTR
InternetConnectW proto WINAPI :HINTERNET, :LPCWSTR, :INTERNET_PORT, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD, :DWORD_PTR
ifdef _UNICODE
define InternetConnect  <InternetConnectW>
else
define InternetConnect  <InternetConnectA>
endif

define INTERNET_SERVICE_FTP    1
define INTERNET_SERVICE_GOPHER 2
define INTERNET_SERVICE_HTTP   3

InternetOpenUrlA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR, :DWORD, :DWORD, :DWORD_PTR
InternetOpenUrlW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD, :DWORD_PTR
ifdef _UNICODE
define InternetOpenUrl  <InternetOpenUrlW>
else
define InternetOpenUrl  <InternetOpenUrlA>
endif

InternetReadFile proto WINAPI :HINTERNET, :LPVOID, :DWORD, :LPDWORD

InternetReadFileExA proto WINAPI :HINTERNET, :LPINTERNET_BUFFERSA, :DWORD, :DWORD_PTR
InternetReadFileExW proto WINAPI :HINTERNET, :LPINTERNET_BUFFERSW, :DWORD, :DWORD_PTR
ifdef _UNICODE
define InternetReadFileEx  <InternetReadFileExW>
else
define InternetReadFileEx  <InternetReadFileExA>
endif

define IRF_ASYNC       WININET_API_FLAG_ASYNC
define IRF_SYNC        WININET_API_FLAG_SYNC
define IRF_USE_CONTEXT WININET_API_FLAG_USE_CONTEXT
define IRF_NO_WAIT     0x00000008

InternetSetFilePointer proto WINAPI :HINTERNET, :LONG, :PLONG, :DWORD, :DWORD_PTR

InternetWriteFile proto WINAPI :HINTERNET, :LPCVOID, :DWORD, :LPDWORD

InternetQueryDataAvailable proto WINAPI :HINTERNET, :LPDWORD, :DWORD, :DWORD_PTR

InternetFindNextFileA proto WINAPI :HINTERNET, :LPVOID
InternetFindNextFileW proto WINAPI :HINTERNET, :LPVOID
ifdef _UNICODE
define InternetFindNextFile  <InternetFindNextFileW>
else
define InternetFindNextFile  <InternetFindNextFileA>
endif

InternetQueryOptionA proto WINAPI :HINTERNET, :DWORD, :LPVOID, :LPDWORD
InternetQueryOptionW proto WINAPI :HINTERNET, :DWORD, :LPVOID, :LPDWORD
ifdef _UNICODE
define InternetQueryOption  <InternetQueryOptionW>
else
define InternetQueryOption  <InternetQueryOptionA>
endif

InternetSetOptionA proto WINAPI :HINTERNET, :DWORD, :LPVOID, :DWORD
InternetSetOptionW proto WINAPI :HINTERNET, :DWORD, :LPVOID, :DWORD
ifdef _UNICODE
define InternetSetOption  <InternetSetOptionW>
else
define InternetSetOption  <InternetSetOptionA>
endif

InternetSetOptionExA proto WINAPI :HINTERNET, :DWORD, :LPVOID, :DWORD, :DWORD
InternetSetOptionExW proto WINAPI :HINTERNET, :DWORD, :LPVOID, :DWORD, :DWORD
ifdef _UNICODE
define InternetSetOptionEx  <InternetSetOptionExW>
else
define InternetSetOptionEx  <InternetSetOptionExA>
endif

InternetLockRequestFile proto WINAPI :HINTERNET, :ptr

InternetUnlockRequestFile proto WINAPI :HANDLE

define ISO_GLOBAL      0x00000001
define ISO_REGISTRY    0x00000002

define ISO_VALID_FLAGS (ISO_GLOBAL or ISO_REGISTRY)

define INTERNET_OPTION_CALLBACK                1
define INTERNET_OPTION_CONNECT_TIMEOUT         2
define INTERNET_OPTION_CONNECT_RETRIES         3
define INTERNET_OPTION_CONNECT_BACKOFF         4
define INTERNET_OPTION_SEND_TIMEOUT            5
define INTERNET_OPTION_CONTROL_SEND_TIMEOUT    INTERNET_OPTION_SEND_TIMEOUT
define INTERNET_OPTION_RECEIVE_TIMEOUT         6
define INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT INTERNET_OPTION_RECEIVE_TIMEOUT
define INTERNET_OPTION_DATA_SEND_TIMEOUT       7
define INTERNET_OPTION_DATA_RECEIVE_TIMEOUT    8
define INTERNET_OPTION_HANDLE_TYPE             9
define INTERNET_OPTION_LISTEN_TIMEOUT          11
define INTERNET_OPTION_READ_BUFFER_SIZE        12
define INTERNET_OPTION_WRITE_BUFFER_SIZE       13

define INTERNET_OPTION_ASYNC_ID                15
define INTERNET_OPTION_ASYNC_PRIORITY          16

define INTERNET_OPTION_PARENT_HANDLE           21
define INTERNET_OPTION_KEEP_CONNECTION         22
define INTERNET_OPTION_REQUEST_FLAGS           23
define INTERNET_OPTION_EXTENDED_ERROR          24

define INTERNET_OPTION_OFFLINE_MODE            26
define INTERNET_OPTION_CACHE_STREAM_HANDLE     27
define INTERNET_OPTION_USERNAME                28
define INTERNET_OPTION_PASSWORD                29
define INTERNET_OPTION_ASYNC                   30
define INTERNET_OPTION_SECURITY_FLAGS          31
define INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT 32
define INTERNET_OPTION_DATAFILE_NAME           33
define INTERNET_OPTION_URL                     34
define INTERNET_OPTION_SECURITY_CERTIFICATE    35
define INTERNET_OPTION_SECURITY_KEY_BITNESS    36
define INTERNET_OPTION_REFRESH                 37
define INTERNET_OPTION_PROXY                   38
define INTERNET_OPTION_SETTINGS_CHANGED        39
define INTERNET_OPTION_VERSION                 40
define INTERNET_OPTION_USER_AGENT              41
define INTERNET_OPTION_END_BROWSER_SESSION     42
define INTERNET_OPTION_PROXY_USERNAME          43
define INTERNET_OPTION_PROXY_PASSWORD          44
define INTERNET_OPTION_CONTEXT_VALUE           45
define INTERNET_OPTION_CONNECT_LIMIT           46
define INTERNET_OPTION_SECURITY_SELECT_CLIENT_CERT 47
define INTERNET_OPTION_POLICY                  48
define INTERNET_OPTION_DISCONNECTED_TIMEOUT    49
define INTERNET_OPTION_CONNECTED_STATE         50
define INTERNET_OPTION_IDLE_STATE              51
define INTERNET_OPTION_OFFLINE_SEMANTICS       52
define INTERNET_OPTION_SECONDARY_CACHE_KEY     53
define INTERNET_OPTION_CALLBACK_FILTER         54
define INTERNET_OPTION_CONNECT_TIME            55
define INTERNET_OPTION_SEND_THROUGHPUT         56
define INTERNET_OPTION_RECEIVE_THROUGHPUT      57
define INTERNET_OPTION_REQUEST_PRIORITY        58
define INTERNET_OPTION_HTTP_VERSION            59
define INTERNET_OPTION_RESET_URLCACHE_SESSION  60
define INTERNET_OPTION_ERROR_MASK              62
define INTERNET_OPTION_FROM_CACHE_TIMEOUT      63
define INTERNET_OPTION_BYPASS_EDITED_ENTRY     64

define INTERNET_OPTION_HTTP_DECODING           65

define INTERNET_OPTION_DIAGNOSTIC_SOCKET_INFO  67
define INTERNET_OPTION_CODEPAGE                68
define INTERNET_OPTION_CACHE_TIMESTAMPS        69
define INTERNET_OPTION_DISABLE_AUTODIAL        70
define INTERNET_OPTION_MAX_CONNS_PER_SERVER     73
define INTERNET_OPTION_MAX_CONNS_PER_1_0_SERVER 74
define INTERNET_OPTION_PER_CONNECTION_OPTION   75
define INTERNET_OPTION_DIGEST_AUTH_UNLOAD             76
define INTERNET_OPTION_IGNORE_OFFLINE           77
define INTERNET_OPTION_IDENTITY                 78
define INTERNET_OPTION_REMOVE_IDENTITY          79
define INTERNET_OPTION_ALTER_IDENTITY           80
define INTERNET_OPTION_SUPPRESS_BEHAVIOR        81
define INTERNET_OPTION_AUTODIAL_MODE            82
define INTERNET_OPTION_AUTODIAL_CONNECTION      83
define INTERNET_OPTION_CLIENT_CERT_CONTEXT      84
define INTERNET_OPTION_AUTH_FLAGS               85
define INTERNET_OPTION_COOKIES_3RD_PARTY        86
define INTERNET_OPTION_DISABLE_PASSPORT_AUTH    87
define INTERNET_OPTION_SEND_UTF8_SERVERNAME_TO_PROXY         88
define INTERNET_OPTION_EXEMPT_CONNECTION_LIMIT  89
define INTERNET_OPTION_ENABLE_PASSPORT_AUTH     90

define INTERNET_OPTION_HIBERNATE_INACTIVE_WORKER_THREADS       91
define INTERNET_OPTION_ACTIVATE_WORKER_THREADS                 92
define INTERNET_OPTION_RESTORE_WORKER_THREAD_DEFAULTS          93
define INTERNET_OPTION_SOCKET_SEND_BUFFER_LENGTH               94
define INTERNET_OPTION_PROXY_SETTINGS_CHANGED                  95
define INTERNET_OPTION_DATAFILE_EXT                            96

define INTERNET_OPTION_CODEPAGE_PATH                100
define INTERNET_OPTION_CODEPAGE_EXTRA               101
define INTERNET_OPTION_IDN                          102
define INTERNET_OPTION_MAX_CONNS_PER_PROXY          103
define INTERNET_OPTION_SUPPRESS_SERVER_AUTH         104
define INTERNET_OPTION_SERVER_CERT_CHAIN_CONTEXT    105
define INTERNET_OPTION_ENABLE_REDIRECT_CACHE_READ   122
define INTERNET_OPTION_COMPRESSED_CONTENT_LENGTH    147
define INTERNET_OPTION_ENABLE_HTTP_PROTOCOL         148
define INTERNET_OPTION_HTTP_PROTOCOL_USED           149
define INTERNET_OPTION_ENCODE_EXTRA                 155
define INTERNET_OPTION_HSTS                         157
define INTERNET_OPTION_ENTERPRISE_CONTEXT           159
define INTERNET_OPTION_CONNECTION_FILTER            162
define INTERNET_OPTION_REFERER_TOKEN_BINDING_HOSTNAME          163
define INTERNET_OPTION_TOKEN_BINDING_PUBLIC_KEY     181
define INTERNET_OPTION_COOKIES_SAME_SITE_LEVEL      187

define INTERNET_FIRST_OPTION                   INTERNET_OPTION_CALLBACK
define INTERNET_LAST_OPTION                    INTERNET_OPTION_COOKIES_SAME_SITE_LEVEL
define INTERNET_PRIORITY_FOREGROUND            1000

define HTTP_COOKIES_SAME_SITE_LEVEL_UNKNOWN        0x0
define HTTP_COOKIES_SAME_SITE_LEVEL_SAME_SITE      0x1
define HTTP_COOKIES_SAME_SITE_LEVEL_CROSS_SITE_LAX 0x2
define HTTP_COOKIES_SAME_SITE_LEVEL_CROSS_SITE     0x3

define HTTP_COOKIES_SAME_SITE_LEVEL_MAX HTTP_COOKIES_SAME_SITE_LEVEL_CROSS_SITE

define HTTP_PROTOCOL_FLAG_HTTP2 0x2
define HTTP_PROTOCOL_MASK (HTTP_PROTOCOL_FLAG_HTTP2)

define INTERNET_HANDLE_TYPE_INTERNET           1
define INTERNET_HANDLE_TYPE_CONNECT_FTP        2
define INTERNET_HANDLE_TYPE_CONNECT_GOPHER     3
define INTERNET_HANDLE_TYPE_CONNECT_HTTP       4
define INTERNET_HANDLE_TYPE_FTP_FIND           5
define INTERNET_HANDLE_TYPE_FTP_FIND_HTML      6
define INTERNET_HANDLE_TYPE_FTP_FILE           7
define INTERNET_HANDLE_TYPE_FTP_FILE_HTML      8
define INTERNET_HANDLE_TYPE_GOPHER_FIND        9
define INTERNET_HANDLE_TYPE_GOPHER_FIND_HTML   10
define INTERNET_HANDLE_TYPE_GOPHER_FILE        11
define INTERNET_HANDLE_TYPE_GOPHER_FILE_HTML   12
define INTERNET_HANDLE_TYPE_HTTP_REQUEST       13
define INTERNET_HANDLE_TYPE_FILE_REQUEST       14

define AUTH_FLAG_DISABLE_NEGOTIATE             0x00000001
define AUTH_FLAG_ENABLE_NEGOTIATE              0x00000002
define AUTH_FLAG_DISABLE_BASIC_CLEARCHANNEL    0x00000004
define AUTH_FLAG_DISABLE_SERVER_AUTH           0x00000008

define SECURITY_FLAG_SECURE                    0x00000001
define SECURITY_FLAG_STRENGTH_WEAK             0x10000000
define SECURITY_FLAG_STRENGTH_MEDIUM           0x40000000
define SECURITY_FLAG_STRENGTH_STRONG           0x20000000
define SECURITY_FLAG_UNKNOWNBIT                0x80000000
define SECURITY_FLAG_FORTEZZA                  0x08000000
define SECURITY_FLAG_NORMALBITNESS             SECURITY_FLAG_STRENGTH_WEAK

define SECURITY_FLAG_SSL                       0x00000002
define SECURITY_FLAG_SSL3                      0x00000004
define SECURITY_FLAG_PCT                       0x00000008
define SECURITY_FLAG_PCT4                      0x00000010
define SECURITY_FLAG_IETFSSL4                  0x00000020

define SECURITY_FLAG_40BIT                     SECURITY_FLAG_STRENGTH_WEAK
define SECURITY_FLAG_128BIT                    SECURITY_FLAG_STRENGTH_STRONG
define SECURITY_FLAG_56BIT                     SECURITY_FLAG_STRENGTH_MEDIUM

define SECURITY_FLAG_IGNORE_REVOCATION         0x00000080
define SECURITY_FLAG_IGNORE_UNKNOWN_CA         0x00000100
define SECURITY_FLAG_IGNORE_WRONG_USAGE        0x00000200
define SECURITY_FLAG_IGNORE_WEAK_SIGNATURE     0x00010000

define SECURITY_FLAG_IGNORE_CERT_CN_INVALID    INTERNET_FLAG_IGNORE_CERT_CN_INVALID
define SECURITY_FLAG_IGNORE_CERT_DATE_INVALID  INTERNET_FLAG_IGNORE_CERT_DATE_INVALID

define SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS  INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS
define SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP

define SECURITY_SET_MASK       (SECURITY_FLAG_IGNORE_REVOCATION or SECURITY_FLAG_IGNORE_UNKNOWN_CA or SECURITY_FLAG_IGNORE_CERT_CN_INVALID or SECURITY_FLAG_IGNORE_CERT_DATE_INVALID or SECURITY_FLAG_IGNORE_WRONG_USAGE or SECURITY_FLAG_IGNORE_WEAK_SIGNATURE)

define SECURITY_FLAG_OPT_IN_WEAK_SIGNATURE     0x00020000

define AUTODIAL_MODE_NEVER                     1
define AUTODIAL_MODE_ALWAYS                    2
define AUTODIAL_MODE_NO_NETWORK_PRESENT        4

InternetGetLastResponseInfoA proto WINAPI :LPDWORD, :LPSTR, :LPDWORD
InternetGetLastResponseInfoW proto WINAPI :LPDWORD, :LPWSTR, :LPDWORD
ifdef _UNICODE
define InternetGetLastResponseInfo  <InternetGetLastResponseInfoW>
else
define InternetGetLastResponseInfo  <InternetGetLastResponseInfoA>
endif

CALLBACK(INTERNET_STATUS_CALLBACK, :HINTERNET, :DWORD_PTR, :DWORD, :LPVOID, :DWORD)
LPINTERNET_STATUS_CALLBACK typedef ptr INTERNET_STATUS_CALLBACK

InternetSetStatusCallbackA proto WINAPI :HINTERNET, :INTERNET_STATUS_CALLBACK
InternetSetStatusCallbackW proto WINAPI :HINTERNET, :INTERNET_STATUS_CALLBACK

ifdef _UNICODE
define InternetSetStatusCallback  <InternetSetStatusCallbackW>
else
ifdef _WINX32_
define InternetSetStatusCallback  <InternetSetStatusCallbackA>
else
InternetSetStatusCallback proto WINAPI :HINTERNET, :INTERNET_STATUS_CALLBACK
endif
endif

define INTERNET_STATUS_RESOLVING_NAME          10
define INTERNET_STATUS_NAME_RESOLVED           11
define INTERNET_STATUS_CONNECTING_TO_SERVER    20
define INTERNET_STATUS_CONNECTED_TO_SERVER     21
define INTERNET_STATUS_SENDING_REQUEST         30
define INTERNET_STATUS_REQUEST_SENT            31
define INTERNET_STATUS_RECEIVING_RESPONSE      40
define INTERNET_STATUS_RESPONSE_RECEIVED       41
define INTERNET_STATUS_CTL_RESPONSE_RECEIVED   42
define INTERNET_STATUS_PREFETCH                43
define INTERNET_STATUS_CLOSING_CONNECTION      50
define INTERNET_STATUS_CONNECTION_CLOSED       51
define INTERNET_STATUS_HANDLE_CREATED          60
define INTERNET_STATUS_HANDLE_CLOSING          70
define INTERNET_STATUS_DETECTING_PROXY         80
define INTERNET_STATUS_REQUEST_COMPLETE        100
define INTERNET_STATUS_REDIRECT                110
define INTERNET_STATUS_INTERMEDIATE_RESPONSE   120
define INTERNET_STATUS_USER_INPUT_REQUIRED     140
define INTERNET_STATUS_STATE_CHANGE            200
define INTERNET_STATUS_COOKIE_SENT             320
define INTERNET_STATUS_COOKIE_RECEIVED         321
define INTERNET_STATUS_PRIVACY_IMPACTED        324
define INTERNET_STATUS_P3P_HEADER              325
define INTERNET_STATUS_P3P_POLICYREF           326
define INTERNET_STATUS_COOKIE_HISTORY          327

define INTERNET_STATE_CONNECTED                0x00000001
define INTERNET_STATE_DISCONNECTED             0x00000002
define INTERNET_STATE_DISCONNECTED_BY_USER     0x00000010
define INTERNET_STATE_IDLE                     0x00000100
define INTERNET_STATE_BUSY                     0x00000200

.enum InternetCookieState {
    COOKIE_STATE_UNKNOWN        = 0x0,
    COOKIE_STATE_ACCEPT         = 0x1,
    COOKIE_STATE_PROMPT         = 0x2,
    COOKIE_STATE_LEASH          = 0x3,
    COOKIE_STATE_DOWNGRADE      = 0x4,
    COOKIE_STATE_REJECT         = 0x5,
    COOKIE_STATE_MAX            = COOKIE_STATE_REJECT,
    }

IncomingCookieState     struct
cSession                sdword ?
cPersistent             sdword ?
cAccepted               sdword ?
cLeashed                sdword ?
cDowngraded             sdword ?
cBlocked                sdword ?
pszLocation             string_t ?
IncomingCookieState     ends

OutgoingCookieState     struct
cSent                   sdword ?
cSuppressed             sdword ?
pszLocation             string_t ?
OutgoingCookieState     ends

InternetCookieHistory   struct
fAccepted               BOOL ?
fLeashed                BOOL ?
fDowngraded             BOOL ?
fRejected               BOOL ?
InternetCookieHistory   ends

CookieDecision          struct
dwCookieState           DWORD ?
fAllowSession           BOOL ?
CookieDecision          ends

define INTERNET_INVALID_STATUS_CALLBACK        (-1)

define FTP_TRANSFER_TYPE_UNKNOWN   0x00000000
define FTP_TRANSFER_TYPE_ASCII     0x00000001
define FTP_TRANSFER_TYPE_BINARY    0x00000002

define FTP_TRANSFER_TYPE_MASK      (FTP_TRANSFER_TYPE_ASCII or FTP_TRANSFER_TYPE_BINARY)

FtpFindFirstFileA proto WINAPI :HINTERNET, :LPCSTR, :LPWIN32_FIND_DATAA, :DWORD, :DWORD_PTR
FtpFindFirstFileW proto WINAPI :HINTERNET, :LPCWSTR, :LPWIN32_FIND_DATAW, :DWORD, :DWORD_PTR
ifdef _UNICODE
define FtpFindFirstFile  <FtpFindFirstFileW>
else
define FtpFindFirstFile  <FtpFindFirstFileA>
endif

FtpGetFileA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR, :BOOL, :DWORD, :DWORD, :DWORD_PTR
FtpGetFileW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR, :BOOL, :DWORD, :DWORD, :DWORD_PTR
ifdef _UNICODE
define FtpGetFile  <FtpGetFileW>
else
define FtpGetFile  <FtpGetFileA>
endif

FtpPutFileA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR, :DWORD, :DWORD_PTR
FtpPutFileW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD_PTR
ifdef _UNICODE
define FtpPutFile  <FtpPutFileW>
else
define FtpPutFile  <FtpPutFileA>
endif

FtpGetFileEx proto WINAPI :HINTERNET, :LPCSTR, :LPCWSTR, :BOOL, :DWORD, :DWORD, :DWORD_PTR

FtpPutFileEx proto WINAPI :HINTERNET, :LPCWSTR, :LPCSTR, :DWORD, :DWORD_PTR

FtpDeleteFileA proto WINAPI :HINTERNET, :LPCSTR
FtpDeleteFileW proto WINAPI :HINTERNET, :LPCWSTR
ifdef _UNICODE
define FtpDeleteFile  <FtpDeleteFileW>
else
define FtpDeleteFile  <FtpDeleteFileA>
endif

FtpRenameFileA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR
FtpRenameFileW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define FtpRenameFile  <FtpRenameFileW>
else
define FtpRenameFile  <FtpRenameFileA>
endif

FtpOpenFileA proto WINAPI :HINTERNET, :LPCSTR, :DWORD, :DWORD, :DWORD_PTR
FtpOpenFileW proto WINAPI :HINTERNET, :LPCWSTR, :DWORD, :DWORD, :DWORD_PTR
ifdef _UNICODE
define FtpOpenFile  <FtpOpenFileW>
else
define FtpOpenFile  <FtpOpenFileA>
endif

FtpCreateDirectoryA proto WINAPI :HINTERNET, :LPCSTR
FtpCreateDirectoryW proto WINAPI :HINTERNET, :LPCWSTR
ifdef _UNICODE
define FtpCreateDirectory  <FtpCreateDirectoryW>
else
define FtpCreateDirectory  <FtpCreateDirectoryA>
endif

FtpRemoveDirectoryA proto WINAPI :HINTERNET, :LPCSTR
FtpRemoveDirectoryW proto WINAPI :HINTERNET, :LPCWSTR
ifdef _UNICODE
define FtpRemoveDirectory  <FtpRemoveDirectoryW>
else
define FtpRemoveDirectory  <FtpRemoveDirectoryA>
endif

FtpSetCurrentDirectoryA proto WINAPI :HINTERNET, :LPCSTR
FtpSetCurrentDirectoryW proto WINAPI :HINTERNET, :LPCWSTR
ifdef _UNICODE
define FtpSetCurrentDirectory  <FtpSetCurrentDirectoryW>
else
define FtpSetCurrentDirectory  <FtpSetCurrentDirectoryA>
endif

FtpGetCurrentDirectoryA proto WINAPI :HINTERNET, :LPSTR, :LPDWORD
FtpGetCurrentDirectoryW proto WINAPI :HINTERNET, :LPWSTR, :LPDWORD
ifdef _UNICODE
define FtpGetCurrentDirectory  <FtpGetCurrentDirectoryW>
else
define FtpGetCurrentDirectory  <FtpGetCurrentDirectoryA>
endif

FtpCommandA proto WINAPI :HINTERNET, :BOOL, :DWORD, :LPCSTR, :DWORD_PTR, :ptr
FtpCommandW proto WINAPI :HINTERNET, :BOOL, :DWORD, :LPCWSTR, :DWORD_PTR, :ptr
ifdef _UNICODE
define FtpCommand  <FtpCommandW>
else
define FtpCommand  <FtpCommandA>
endif

FtpGetFileSize proto WINAPI :HINTERNET, :LPDWORD

define MAX_GOPHER_DISPLAY_TEXT     128
define MAX_GOPHER_SELECTOR_TEXT    256
define MAX_GOPHER_HOST_NAME        INTERNET_MAX_HOST_NAME_LENGTH
define MAX_GOPHER_LOCATOR_LENGTH   (1 + MAX_GOPHER_DISPLAY_TEXT + 1 + MAX_GOPHER_SELECTOR_TEXT + 1 + MAX_GOPHER_HOST_NAME + 1 + INTERNET_MAX_PORT_NUMBER_LENGTH + 1 + 1 + 2 )

GOPHER_FIND_DATAA       struct
DisplayString           CHAR MAX_GOPHER_DISPLAY_TEXT + 1 dup(?)
GopherType              DWORD ?
SizeLow                 DWORD ?
SizeHigh                DWORD ?
LastModificationTime    FILETIME <>
Locator                 CHAR MAX_GOPHER_LOCATOR_LENGTH + 1 dup(?)
GOPHER_FIND_DATAA       ends
LPGOPHER_FIND_DATAA     typedef ptr GOPHER_FIND_DATAA
GOPHER_FIND_DATAW       struct
DisplayString           WCHAR MAX_GOPHER_DISPLAY_TEXT + 1 dup(?)
GopherType              DWORD ?
SizeLow                 DWORD ?
SizeHigh                DWORD ?
LastModificationTime    FILETIME <>
Locator                 WCHAR MAX_GOPHER_LOCATOR_LENGTH + 1 dup(?)
GOPHER_FIND_DATAW       ends
LPGOPHER_FIND_DATAW     typedef ptr GOPHER_FIND_DATAW
ifdef _UNICODE
GOPHER_FIND_DATA        typedef GOPHER_FIND_DATAW
LPGOPHER_FIND_DATA      typedef LPGOPHER_FIND_DATAW
else
GOPHER_FIND_DATA        typedef GOPHER_FIND_DATAA
LPGOPHER_FIND_DATA      typedef LPGOPHER_FIND_DATAA
endif

define GOPHER_TYPE_TEXT_FILE       0x00000001
define GOPHER_TYPE_DIRECTORY       0x00000002
define GOPHER_TYPE_CSO             0x00000004
define GOPHER_TYPE_ERROR           0x00000008
define GOPHER_TYPE_MAC_BINHEX      0x00000010
define GOPHER_TYPE_DOS_ARCHIVE     0x00000020
define GOPHER_TYPE_UNIX_UUENCODED  0x00000040
define GOPHER_TYPE_INDEX_SERVER    0x00000080
define GOPHER_TYPE_TELNET          0x00000100
define GOPHER_TYPE_BINARY          0x00000200
define GOPHER_TYPE_REDUNDANT       0x00000400
define GOPHER_TYPE_TN3270          0x00000800
define GOPHER_TYPE_GIF             0x00001000
define GOPHER_TYPE_IMAGE           0x00002000
define GOPHER_TYPE_BITMAP          0x00004000
define GOPHER_TYPE_MOVIE           0x00008000
define GOPHER_TYPE_SOUND           0x00010000
define GOPHER_TYPE_HTML            0x00020000
define GOPHER_TYPE_PDF             0x00040000
define GOPHER_TYPE_CALENDAR        0x00080000
define GOPHER_TYPE_INLINE          0x00100000
define GOPHER_TYPE_UNKNOWN         0x20000000
define GOPHER_TYPE_ASK             0x40000000
define GOPHER_TYPE_GOPHER_PLUS     0x80000000

IS_GOPHER_FILE macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_FILE_MASK) ? TRUE : FALSE)>
  endm
IS_GOPHER_DIRECTORY macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_DIRECTORY) ? TRUE : FALSE)>
  endm
IS_GOPHER_PHONE_SERVER macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_CSO) ? TRUE : FALSE)>
  endm
IS_GOPHER_ERROR macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_ERROR) ? TRUE : FALSE)>
  endm
IS_GOPHER_INDEX_SERVER macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_INDEX_SERVER) ? TRUE : FALSE)>
  endm
IS_GOPHER_TELNET_SESSION macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_TELNET) ? TRUE : FALSE)>
  endm
IS_GOPHER_BACKUP_SERVER macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_REDUNDANT) ? TRUE : FALSE)>
  endm
IS_GOPHER_TN3270_SESSION macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_TN3270) ? TRUE : FALSE)>
  endm
IS_GOPHER_ASK macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_ASK) ? TRUE : FALSE)>
  endm
IS_GOPHER_PLUS macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_GOPHER_PLUS) ? TRUE : FALSE)>
  endm

IS_GOPHER_TYPE_KNOWN macro type
  exitm<(BOOL)(((type) and GOPHER_TYPE_UNKNOWN) ? FALSE : TRUE)>
  endm

define GOPHER_TYPE_FILE_MASK (GOPHER_TYPE_TEXT_FILE or \
                              GOPHER_TYPE_MAC_BINHEX or \
                              GOPHER_TYPE_DOS_ARCHIVE or \
                              GOPHER_TYPE_UNIX_UUENCODED or \
                              GOPHER_TYPE_BINARY or \
                              GOPHER_TYPE_GIF or \
                              GOPHER_TYPE_IMAGE or \
                              GOPHER_TYPE_BITMAP or \
                              GOPHER_TYPE_MOVIE or \
                              GOPHER_TYPE_SOUND or \
                              GOPHER_TYPE_HTML or \
                              GOPHER_TYPE_PDF or \
                              GOPHER_TYPE_CALENDAR or \
                              GOPHER_TYPE_INLINE)

GOPHER_ADMIN_ATTRIBUTE_TYPE struct
_Comment                LPCTSTR ?
EmailAddress            LPCTSTR ?
GOPHER_ADMIN_ATTRIBUTE_TYPE ends
LPGOPHER_ADMIN_ATTRIBUTE_TYPE typedef ptr GOPHER_ADMIN_ATTRIBUTE_TYPE

GOPHER_MOD_DATE_ATTRIBUTE_TYPE struct
DateAndTime             FILETIME <>
GOPHER_MOD_DATE_ATTRIBUTE_TYPE ends
LPGOPHER_MOD_DATE_ATTRIBUTE_TYPE typedef ptr GOPHER_MOD_DATE_ATTRIBUTE_TYPE

GOPHER_TTL_ATTRIBUTE_TYPE struct
Ttl                     DWORD ?
GOPHER_TTL_ATTRIBUTE_TYPE ends
LPGOPHER_TTL_ATTRIBUTE_TYPE typedef ptr GOPHER_TTL_ATTRIBUTE_TYPE

GOPHER_SCORE_ATTRIBUTE_TYPE struct
Score                   sdword ?
GOPHER_SCORE_ATTRIBUTE_TYPE ends
LPGOPHER_SCORE_ATTRIBUTE_TYPE typedef ptr GOPHER_SCORE_ATTRIBUTE_TYPE

GOPHER_SCORE_RANGE_ATTRIBUTE_TYPE struct
LowerBound              sdword ?
UpperBound              sdword ?
GOPHER_SCORE_RANGE_ATTRIBUTE_TYPE ends
LPGOPHER_SCORE_RANGE_ATTRIBUTE_TYPE typedef ptr GOPHER_SCORE_RANGE_ATTRIBUTE_TYPE

GOPHER_SITE_ATTRIBUTE_TYPE struct
Site                    LPCTSTR ?
GOPHER_SITE_ATTRIBUTE_TYPE ends
LPGOPHER_SITE_ATTRIBUTE_TYPE typedef ptr GOPHER_SITE_ATTRIBUTE_TYPE

GOPHER_ORGANIZATION_ATTRIBUTE_TYPE struct
Organization            LPCTSTR ?
GOPHER_ORGANIZATION_ATTRIBUTE_TYPE ends
LPGOPHER_ORGANIZATION_ATTRIBUTE_TYPE typedef ptr GOPHER_ORGANIZATION_ATTRIBUTE_TYPE

GOPHER_LOCATION_ATTRIBUTE_TYPE struct
Location                LPCTSTR ?
GOPHER_LOCATION_ATTRIBUTE_TYPE ends
LPGOPHER_LOCATION_ATTRIBUTE_TYPE typedef ptr GOPHER_LOCATION_ATTRIBUTE_TYPE

GOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE struct
DegreesNorth            sdword ?
MinutesNorth            sdword ?
SecondsNorth            sdword ?
DegreesEast             sdword ?
MinutesEast             sdword ?
SecondsEast             sdword ?
GOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE ends
LPGOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE typedef ptr GOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE

GOPHER_TIMEZONE_ATTRIBUTE_TYPE struct
Zone                    sdword ?
GOPHER_TIMEZONE_ATTRIBUTE_TYPE ends
LPGOPHER_TIMEZONE_ATTRIBUTE_TYPE typedef ptr GOPHER_TIMEZONE_ATTRIBUTE_TYPE

GOPHER_PROVIDER_ATTRIBUTE_TYPE struct
Provider                LPCTSTR ?
GOPHER_PROVIDER_ATTRIBUTE_TYPE ends
LPGOPHER_PROVIDER_ATTRIBUTE_TYPE typedef ptr GOPHER_PROVIDER_ATTRIBUTE_TYPE

GOPHER_VERSION_ATTRIBUTE_TYPE struct
Version                 LPCTSTR ?
GOPHER_VERSION_ATTRIBUTE_TYPE ends
LPGOPHER_VERSION_ATTRIBUTE_TYPE typedef ptr GOPHER_VERSION_ATTRIBUTE_TYPE

GOPHER_ABSTRACT_ATTRIBUTE_TYPE struct
ShortAbstract           LPCTSTR ?
AbstractFile            LPCTSTR ?
GOPHER_ABSTRACT_ATTRIBUTE_TYPE ends
LPGOPHER_ABSTRACT_ATTRIBUTE_TYPE typedef ptr GOPHER_ABSTRACT_ATTRIBUTE_TYPE

GOPHER_VIEW_ATTRIBUTE_TYPE struct
ContentType             LPCTSTR ?
Language                LPCTSTR ?
Size                    DWORD ?
GOPHER_VIEW_ATTRIBUTE_TYPE ends
LPGOPHER_VIEW_ATTRIBUTE_TYPE typedef ptr GOPHER_VIEW_ATTRIBUTE_TYPE

GOPHER_VERONICA_ATTRIBUTE_TYPE struct
TreeWalk                BOOL ?
GOPHER_VERONICA_ATTRIBUTE_TYPE ends
LPGOPHER_VERONICA_ATTRIBUTE_TYPE typedef ptr GOPHER_VERONICA_ATTRIBUTE_TYPE

GOPHER_ASK_ATTRIBUTE_TYPE struct
QuestionType            LPCTSTR ?
QuestionText            LPCTSTR ?
GOPHER_ASK_ATTRIBUTE_TYPE ends
LPGOPHER_ASK_ATTRIBUTE_TYPE typedef ptr GOPHER_ASK_ATTRIBUTE_TYPE

GOPHER_UNKNOWN_ATTRIBUTE_TYPE struct
Text                    LPCTSTR ?
GOPHER_UNKNOWN_ATTRIBUTE_TYPE ends
LPGOPHER_UNKNOWN_ATTRIBUTE_TYPE typedef ptr GOPHER_UNKNOWN_ATTRIBUTE_TYPE

GOPHER_ATTRIBUTE_TYPE   struct
CategoryId              DWORD ?
AttributeId             DWORD ?
union AttributeType
 Admin                  GOPHER_ADMIN_ATTRIBUTE_TYPE <>
 ModDate                GOPHER_MOD_DATE_ATTRIBUTE_TYPE <>
 Ttl                    GOPHER_TTL_ATTRIBUTE_TYPE <>
 Score                  GOPHER_SCORE_ATTRIBUTE_TYPE <>
 ScoreRange             GOPHER_SCORE_RANGE_ATTRIBUTE_TYPE <>
 Site                   GOPHER_SITE_ATTRIBUTE_TYPE <>
 Organization           GOPHER_ORGANIZATION_ATTRIBUTE_TYPE <>
 Location               GOPHER_LOCATION_ATTRIBUTE_TYPE <>
 GeographicalLocation   GOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE <>
 TimeZone               GOPHER_TIMEZONE_ATTRIBUTE_TYPE <>
 Provider               GOPHER_PROVIDER_ATTRIBUTE_TYPE <>
 Version                GOPHER_VERSION_ATTRIBUTE_TYPE <>
 Abstract               GOPHER_ABSTRACT_ATTRIBUTE_TYPE <>
 View                   GOPHER_VIEW_ATTRIBUTE_TYPE <>
 Veronica               GOPHER_VERONICA_ATTRIBUTE_TYPE <>
 Ask                    GOPHER_ASK_ATTRIBUTE_TYPE <>
 Unknown                GOPHER_UNKNOWN_ATTRIBUTE_TYPE <>
ends
GOPHER_ATTRIBUTE_TYPE   ends
LPGOPHER_ATTRIBUTE_TYPE typedef ptr GOPHER_ATTRIBUTE_TYPE

define MAX_GOPHER_CATEGORY_NAME    128
define MAX_GOPHER_ATTRIBUTE_NAME   128
define MIN_GOPHER_ATTRIBUTE_LENGTH 256

define GOPHER_INFO_CATEGORY        <"+INFO">
define GOPHER_ADMIN_CATEGORY       <"+ADMIN">
define GOPHER_VIEWS_CATEGORY       <"+VIEWS">
define GOPHER_ABSTRACT_CATEGORY    <"+ABSTRACT">
define GOPHER_VERONICA_CATEGORY    <"+VERONICA">

define GOPHER_ADMIN_ATTRIBUTE      <"Admin">
define GOPHER_MOD_DATE_ATTRIBUTE   <"Mod-Date">
define GOPHER_TTL_ATTRIBUTE        <"TTL">
define GOPHER_SCORE_ATTRIBUTE      <"Score">
define GOPHER_RANGE_ATTRIBUTE      <"Score-range">
define GOPHER_SITE_ATTRIBUTE       <"Site">
define GOPHER_ORG_ATTRIBUTE        <"Org">
define GOPHER_LOCATION_ATTRIBUTE   <"Loc">
define GOPHER_GEOG_ATTRIBUTE       <"Geog">
define GOPHER_TIMEZONE_ATTRIBUTE   <"TZ">
define GOPHER_PROVIDER_ATTRIBUTE   <"Provider">
define GOPHER_VERSION_ATTRIBUTE    <"Version">
define GOPHER_ABSTRACT_ATTRIBUTE   <"Abstract">
define GOPHER_VIEW_ATTRIBUTE       <"View">
define GOPHER_TREEWALK_ATTRIBUTE   <"treewalk">

define GOPHER_ATTRIBUTE_ID_BASE        0xabcccc00

define GOPHER_CATEGORY_ID_ALL          (GOPHER_ATTRIBUTE_ID_BASE + 1)

define GOPHER_CATEGORY_ID_INFO         (GOPHER_ATTRIBUTE_ID_BASE + 2)
define GOPHER_CATEGORY_ID_ADMIN        (GOPHER_ATTRIBUTE_ID_BASE + 3)
define GOPHER_CATEGORY_ID_VIEWS        (GOPHER_ATTRIBUTE_ID_BASE + 4)
define GOPHER_CATEGORY_ID_ABSTRACT     (GOPHER_ATTRIBUTE_ID_BASE + 5)
define GOPHER_CATEGORY_ID_VERONICA     (GOPHER_ATTRIBUTE_ID_BASE + 6)
define GOPHER_CATEGORY_ID_ASK          (GOPHER_ATTRIBUTE_ID_BASE + 7)

define GOPHER_CATEGORY_ID_UNKNOWN      (GOPHER_ATTRIBUTE_ID_BASE + 8)
define GOPHER_ATTRIBUTE_ID_ALL         (GOPHER_ATTRIBUTE_ID_BASE + 9)

define GOPHER_ATTRIBUTE_ID_ADMIN       (GOPHER_ATTRIBUTE_ID_BASE + 10)
define GOPHER_ATTRIBUTE_ID_MOD_DATE    (GOPHER_ATTRIBUTE_ID_BASE + 11)
define GOPHER_ATTRIBUTE_ID_TTL         (GOPHER_ATTRIBUTE_ID_BASE + 12)
define GOPHER_ATTRIBUTE_ID_SCORE       (GOPHER_ATTRIBUTE_ID_BASE + 13)
define GOPHER_ATTRIBUTE_ID_RANGE       (GOPHER_ATTRIBUTE_ID_BASE + 14)
define GOPHER_ATTRIBUTE_ID_SITE        (GOPHER_ATTRIBUTE_ID_BASE + 15)
define GOPHER_ATTRIBUTE_ID_ORG         (GOPHER_ATTRIBUTE_ID_BASE + 16)
define GOPHER_ATTRIBUTE_ID_LOCATION    (GOPHER_ATTRIBUTE_ID_BASE + 17)
define GOPHER_ATTRIBUTE_ID_GEOG        (GOPHER_ATTRIBUTE_ID_BASE + 18)
define GOPHER_ATTRIBUTE_ID_TIMEZONE    (GOPHER_ATTRIBUTE_ID_BASE + 19)
define GOPHER_ATTRIBUTE_ID_PROVIDER    (GOPHER_ATTRIBUTE_ID_BASE + 20)
define GOPHER_ATTRIBUTE_ID_VERSION     (GOPHER_ATTRIBUTE_ID_BASE + 21)
define GOPHER_ATTRIBUTE_ID_ABSTRACT    (GOPHER_ATTRIBUTE_ID_BASE + 22)
define GOPHER_ATTRIBUTE_ID_VIEW        (GOPHER_ATTRIBUTE_ID_BASE + 23)
define GOPHER_ATTRIBUTE_ID_TREEWALK    (GOPHER_ATTRIBUTE_ID_BASE + 24)

define GOPHER_ATTRIBUTE_ID_UNKNOWN     (GOPHER_ATTRIBUTE_ID_BASE + 25)

GopherCreateLocatorA proto WINAPI :LPCSTR, :INTERNET_PORT, :LPCSTR, :LPCSTR, :DWORD, :LPSTR, :LPDWORD
GopherCreateLocatorW proto WINAPI :LPCWSTR, :INTERNET_PORT, :LPCWSTR, :LPCWSTR, :DWORD, :LPWSTR, :LPDWORD
ifdef _UNICODE
define GopherCreateLocator  <GopherCreateLocatorW>
else
define GopherCreateLocator  <GopherCreateLocatorA>
endif

GopherGetLocatorTypeA proto WINAPI :LPCSTR, :LPDWORD
GopherGetLocatorTypeW proto WINAPI :LPCWSTR, :LPDWORD
ifdef _UNICODE
define GopherGetLocatorType  <GopherGetLocatorTypeW>
else
define GopherGetLocatorType  <GopherGetLocatorTypeA>
endif

GopherFindFirstFileA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR, :LPGOPHER_FIND_DATAA, :DWORD, :DWORD_PTR
GopherFindFirstFileW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR, :LPGOPHER_FIND_DATAW, :DWORD, :DWORD_PTR
ifdef _UNICODE
define GopherFindFirstFile  <GopherFindFirstFileW>
else
define GopherFindFirstFile  <GopherFindFirstFileA>
endif

GopherOpenFileA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR, :DWORD, :DWORD_PTR
GopherOpenFileW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD_PTR
ifdef _UNICODE
define GopherOpenFile  <GopherOpenFileW>
else
define GopherOpenFile  <GopherOpenFileA>
endif

CALLBACK(GOPHER_ATTRIBUTE_ENUMERATOR, :LPGOPHER_ATTRIBUTE_TYPE, :DWORD)

GopherGetAttributeA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR, :LPBYTE, :DWORD, :LPDWORD, :GOPHER_ATTRIBUTE_ENUMERATOR, :DWORD_PTR
GopherGetAttributeW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR, :LPBYTE, :DWORD, :LPDWORD, :GOPHER_ATTRIBUTE_ENUMERATOR, :DWORD_PTR
ifdef _UNICODE
define GopherGetAttribute  <GopherGetAttributeW>
else
define GopherGetAttribute  <GopherGetAttributeA>
endif

define HTTP_MAJOR_VERSION      1
define HTTP_MINOR_VERSION      0

define HTTP_VERSIONA           <"HTTP/1.0">
define HTTP_VERSIONW           <L"HTTP/1.0">

ifdef _UNICODE
define HTTP_VERSION            HTTP_VERSIONW
else
define HTTP_VERSION            HTTP_VERSIONA
endif

define HTTP_QUERY_MIME_VERSION                 0
define HTTP_QUERY_CONTENT_TYPE                 1
define HTTP_QUERY_CONTENT_TRANSFER_ENCODING    2
define HTTP_QUERY_CONTENT_ID                   3
define HTTP_QUERY_CONTENT_DESCRIPTION          4
define HTTP_QUERY_CONTENT_LENGTH               5
define HTTP_QUERY_CONTENT_LANGUAGE             6
define HTTP_QUERY_ALLOW                        7
define HTTP_QUERY_PUBLIC                       8
define HTTP_QUERY_DATE                         9
define HTTP_QUERY_EXPIRES                      10
define HTTP_QUERY_LAST_MODIFIED                11
define HTTP_QUERY_MESSAGE_ID                   12
define HTTP_QUERY_URI                          13
define HTTP_QUERY_DERIVED_FROM                 14
define HTTP_QUERY_COST                         15
define HTTP_QUERY_LINK                         16
define HTTP_QUERY_PRAGMA                       17
define HTTP_QUERY_VERSION                      18
define HTTP_QUERY_STATUS_CODE                  19
define HTTP_QUERY_STATUS_TEXT                  20
define HTTP_QUERY_RAW_HEADERS                  21
define HTTP_QUERY_RAW_HEADERS_CRLF             22
define HTTP_QUERY_CONNECTION                   23
define HTTP_QUERY_ACCEPT                       24
define HTTP_QUERY_ACCEPT_CHARSET               25
define HTTP_QUERY_ACCEPT_ENCODING              26
define HTTP_QUERY_ACCEPT_LANGUAGE              27
define HTTP_QUERY_AUTHORIZATION                28
define HTTP_QUERY_CONTENT_ENCODING             29
define HTTP_QUERY_FORWARDED                    30
define HTTP_QUERY_FROM                         31
define HTTP_QUERY_IF_MODIFIED_SINCE            32
define HTTP_QUERY_LOCATION                     33
define HTTP_QUERY_ORIG_URI                     34
define HTTP_QUERY_REFERER                      35
define HTTP_QUERY_RETRY_AFTER                  36
define HTTP_QUERY_SERVER                       37
define HTTP_QUERY_TITLE                        38
define HTTP_QUERY_USER_AGENT                   39
define HTTP_QUERY_WWW_AUTHENTICATE             40
define HTTP_QUERY_PROXY_AUTHENTICATE           41
define HTTP_QUERY_ACCEPT_RANGES                42
define HTTP_QUERY_SET_COOKIE                   43
define HTTP_QUERY_COOKIE                       44
define HTTP_QUERY_REQUEST_METHOD               45
define HTTP_QUERY_REFRESH                      46
define HTTP_QUERY_CONTENT_DISPOSITION          47

define HTTP_QUERY_AGE                          48
define HTTP_QUERY_CACHE_CONTROL                49
define HTTP_QUERY_CONTENT_BASE                 50
define HTTP_QUERY_CONTENT_LOCATION             51
define HTTP_QUERY_CONTENT_MD5                  52
define HTTP_QUERY_CONTENT_RANGE                53
define HTTP_QUERY_ETAG                         54
define HTTP_QUERY_HOST                         55
define HTTP_QUERY_IF_MATCH                     56
define HTTP_QUERY_IF_NONE_MATCH                57
define HTTP_QUERY_IF_RANGE                     58
define HTTP_QUERY_IF_UNMODIFIED_SINCE          59
define HTTP_QUERY_MAX_FORWARDS                 60
define HTTP_QUERY_PROXY_AUTHORIZATION          61
define HTTP_QUERY_RANGE                        62
define HTTP_QUERY_TRANSFER_ENCODING            63
define HTTP_QUERY_UPGRADE                      64
define HTTP_QUERY_VARY                         65
define HTTP_QUERY_VIA                          66
define HTTP_QUERY_WARNING                      67
define HTTP_QUERY_EXPECT                       68
define HTTP_QUERY_PROXY_CONNECTION             69
define HTTP_QUERY_UNLESS_MODIFIED_SINCE        70

define HTTP_QUERY_ECHO_REQUEST                 71
define HTTP_QUERY_ECHO_REPLY                   72

define HTTP_QUERY_ECHO_HEADERS                 73
define HTTP_QUERY_ECHO_HEADERS_CRLF            74

define HTTP_QUERY_PROXY_SUPPORT                75
define HTTP_QUERY_AUTHENTICATION_INFO          76
define HTTP_QUERY_PASSPORT_URLS                77
define HTTP_QUERY_PASSPORT_CONFIG              78

define HTTP_QUERY_X_CONTENT_TYPE_OPTIONS       79
define HTTP_QUERY_P3P                          80
define HTTP_QUERY_X_P2P_PEERDIST               81
define HTTP_QUERY_TRANSLATE                    82
define HTTP_QUERY_X_UA_COMPATIBLE              83
define HTTP_QUERY_DEFAULT_STYLE                84
define HTTP_QUERY_X_FRAME_OPTIONS              85
define HTTP_QUERY_X_XSS_PROTECTION             86

define HTTP_QUERY_SET_COOKIE2                  87
define HTTP_QUERY_DO_NOT_TRACK                 88
define HTTP_QUERY_KEEP_ALIVE                   89
define HTTP_QUERY_HTTP2_SETTINGS               90
define HTTP_QUERY_STRICT_TRANSPORT_SECURITY    91
define HTTP_QUERY_TOKEN_BINDING                92
define HTTP_QUERY_INCLUDE_REFERRED_TOKEN_BINDING_ID  93
define HTTP_QUERY_INCLUDE_REFERER_TOKEN_BINDING_ID   HTTP_QUERY_INCLUDE_REFERRED_TOKEN_BINDING_ID

define HTTP_QUERY_PUBLIC_KEY_PINS              94
define HTTP_QUERY_PUBLIC_KEY_PINS_REPORT_ONLY  95
define HTTP_QUERY_MAX                          95
define HTTP_QUERY_CUSTOM                       65535
define HTTP_QUERY_FLAG_REQUEST_HEADERS         0x80000000
define HTTP_QUERY_FLAG_SYSTEMTIME              0x40000000
define HTTP_QUERY_FLAG_NUMBER                  0x20000000
define HTTP_QUERY_FLAG_COALESCE                0x10000000
define HTTP_QUERY_FLAG_NUMBER64                0x08000000
define HTTP_QUERY_FLAG_COALESCE_WITH_COMMA     0x04000000
define HTTP_QUERY_MODIFIER_FLAGS_MASK          (HTTP_QUERY_FLAG_REQUEST_HEADERS or HTTP_QUERY_FLAG_SYSTEMTIME or HTTP_QUERY_FLAG_NUMBER or HTTP_QUERY_FLAG_COALESCE or HTTP_QUERY_FLAG_NUMBER64 or HTTP_QUERY_FLAG_COALESCE_WITH_COMMA )
define HTTP_QUERY_HEADER_MASK                  ( not HTTP_QUERY_MODIFIER_FLAGS_MASK)

define HTTP_STATUS_CONTINUE            100
define HTTP_STATUS_SWITCH_PROTOCOLS    101

define HTTP_STATUS_OK                  200
define HTTP_STATUS_CREATED             201
define HTTP_STATUS_ACCEPTED            202
define HTTP_STATUS_PARTIAL             203
define HTTP_STATUS_NO_CONTENT          204
define HTTP_STATUS_RESET_CONTENT       205
define HTTP_STATUS_PARTIAL_CONTENT     206

define HTTP_STATUS_AMBIGUOUS           300
define HTTP_STATUS_MOVED               301
define HTTP_STATUS_REDIRECT            302
define HTTP_STATUS_REDIRECT_METHOD     303
define HTTP_STATUS_NOT_MODIFIED        304
define HTTP_STATUS_USE_PROXY           305
define HTTP_STATUS_REDIRECT_KEEP_VERB  307
define HTTP_STATUS_PERMANENT_REDIRECT  308

define HTTP_STATUS_BAD_REQUEST         400
define HTTP_STATUS_DENIED              401
define HTTP_STATUS_PAYMENT_REQ         402
define HTTP_STATUS_FORBIDDEN           403
define HTTP_STATUS_NOT_FOUND           404
define HTTP_STATUS_BAD_METHOD          405
define HTTP_STATUS_NONE_ACCEPTABLE     406
define HTTP_STATUS_PROXY_AUTH_REQ      407
define HTTP_STATUS_REQUEST_TIMEOUT     408
define HTTP_STATUS_CONFLICT            409
define HTTP_STATUS_GONE                410
define HTTP_STATUS_LENGTH_REQUIRED     411
define HTTP_STATUS_PRECOND_FAILED      412
define HTTP_STATUS_REQUEST_TOO_LARGE   413
define HTTP_STATUS_URI_TOO_LONG        414
define HTTP_STATUS_UNSUPPORTED_MEDIA   415
define HTTP_STATUS_MISDIRECTED_REQUEST 421
define HTTP_STATUS_RETRY_WITH          449

define HTTP_STATUS_SERVER_ERROR        500
define HTTP_STATUS_NOT_SUPPORTED       501
define HTTP_STATUS_BAD_GATEWAY         502
define HTTP_STATUS_SERVICE_UNAVAIL     503
define HTTP_STATUS_GATEWAY_TIMEOUT     504
define HTTP_STATUS_VERSION_NOT_SUP     505

define HTTP_STATUS_FIRST               HTTP_STATUS_CONTINUE
define HTTP_STATUS_LAST                HTTP_STATUS_VERSION_NOT_SUP

HttpOpenRequestA proto WINAPI :HINTERNET, :LPCSTR, :LPCSTR, :LPCSTR, :LPCSTR, :ptr, :DWORD, :DWORD_PTR
HttpOpenRequestW proto WINAPI :HINTERNET, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr, :DWORD, :DWORD_PTR
ifdef _UNICODE
define HttpOpenRequest  <HttpOpenRequestW>
else
define HttpOpenRequest  <HttpOpenRequestA>
endif

HttpAddRequestHeadersA proto WINAPI :HINTERNET, :LPCSTR, :DWORD, :DWORD
HttpAddRequestHeadersW proto WINAPI :HINTERNET, :LPCWSTR, :DWORD, :DWORD
ifdef _UNICODE
define HttpAddRequestHeaders  <HttpAddRequestHeadersW>
else
define HttpAddRequestHeaders  <HttpAddRequestHeadersA>
endif

define HTTP_ADDREQ_INDEX_MASK      0x0000FFFF
define HTTP_ADDREQ_FLAGS_MASK      0xFFFF0000
define HTTP_ADDREQ_FLAG_ADD_IF_NEW 0x10000000
define HTTP_ADDREQ_FLAG_ADD        0x20000000

define INTERNET_RAS_INSTALLED              0x10
define INTERNET_CONNECTION_OFFLINE         0x20
define INTERNET_CONNECTION_CONFIGURED      0x40

CALLBACK(PFN_DIAL_HANDLER, :HWND, :LPCSTR, :DWORD, :LPDWORD)

define INTERNET_CUSTOMDIAL_CONNECT         0
define INTERNET_CUSTOMDIAL_UNATTENDED      1
define INTERNET_CUSTOMDIAL_DISCONNECT      2
define INTERNET_CUSTOMDIAL_SHOWOFFLINE     4

define INTERNET_CUSTOMDIAL_SAFE_FOR_UNATTENDED 1
define INTERNET_CUSTOMDIAL_WILL_SUPPLY_STATE   2
define INTERNET_CUSTOMDIAL_CAN_HANGUP          4

InternetSetDialStateA proto WINAPI :LPCSTR, :DWORD, :DWORD

InternetSetDialStateW proto WINAPI :LPCWSTR, :DWORD, :DWORD

ifdef _UNICODE
define InternetSetDialState  <InternetSetDialStateW>
else
ifdef _WINX32_
define InternetSetDialState  <InternetSetDialStateA>
else
InternetSetDialState proto WINAPI :LPCSTR, :DWORD, :DWORD
endif
endif

define INTERNET_DIALSTATE_DISCONNECTED     1

InternetSetPerSiteCookieDecisionA proto WINAPI :LPCSTR, :DWORD
InternetSetPerSiteCookieDecisionW proto WINAPI :LPCWSTR, :DWORD
ifdef _UNICODE
define InternetSetPerSiteCookieDecision  <InternetSetPerSiteCookieDecisionW>
else
define InternetSetPerSiteCookieDecision  <InternetSetPerSiteCookieDecisionA>
endif

InternetGetPerSiteCookieDecisionA proto WINAPI :LPCSTR, :ptr
InternetGetPerSiteCookieDecisionW proto WINAPI :LPCWSTR, :ptr
ifdef _UNICODE
define InternetGetPerSiteCookieDecision  <InternetGetPerSiteCookieDecisionW>
else
define InternetGetPerSiteCookieDecision  <InternetGetPerSiteCookieDecisionA>
endif

InternetClearAllPerSiteCookieDecisions proto WINAPI
InternetEnumPerSiteCookieDecisionA proto WINAPI :LPSTR, :ptr, :ptr, :sdword
InternetEnumPerSiteCookieDecisionW proto WINAPI :LPWSTR, :ptr, :ptr, :sdword
ifdef _UNICODE
define InternetEnumPerSiteCookieDecision  <InternetEnumPerSiteCookieDecisionW>
else
define InternetEnumPerSiteCookieDecision  <InternetEnumPerSiteCookieDecisionA>
endif

define INTERNET_IDENTITY_FLAG_PRIVATE_CACHE        0x01
define INTERNET_IDENTITY_FLAG_SHARED_CACHE         0x02
define INTERNET_IDENTITY_FLAG_CLEAR_DATA           0x04
define INTERNET_IDENTITY_FLAG_CLEAR_COOKIES        0x08
define INTERNET_IDENTITY_FLAG_CLEAR_HISTORY        0x10
define INTERNET_IDENTITY_FLAG_CLEAR_CONTENT        0x20

define INTERNET_SUPPRESS_RESET_ALL                 0x00
define INTERNET_SUPPRESS_COOKIE_POLICY             0x01
define INTERNET_SUPPRESS_COOKIE_POLICY_RESET       0x02

define PRIVACY_TEMPLATE_NO_COOKIES     0
define PRIVACY_TEMPLATE_HIGH           1
define PRIVACY_TEMPLATE_MEDIUM_HIGH    2
define PRIVACY_TEMPLATE_MEDIUM         3
define PRIVACY_TEMPLATE_MEDIUM_LOW     4
define PRIVACY_TEMPLATE_LOW            5
define PRIVACY_TEMPLATE_CUSTOM         100
define PRIVACY_TEMPLATE_ADVANCED       101

define PRIVACY_TEMPLATE_MAX            PRIVACY_TEMPLATE_LOW

define PRIVACY_TYPE_FIRST_PARTY        0
define PRIVACY_TYPE_THIRD_PARTY        1

PrivacySetZonePreferenceW proto WINAPI :DWORD, :DWORD, :DWORD, :LPCWSTR
PrivacyGetZonePreferenceW proto WINAPI :DWORD, :DWORD, :LPDWORD, :LPWSTR, :LPDWORD
HttpIsHostHstsEnabled proto WINAPI :PCWSTR, :PBOOL

.pragma pack(pop)

endif

endif
