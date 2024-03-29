ifndef __WLANTYPES_H__
define __WLANTYPES_H__
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum _DOT11_BSS_TYPE {
    dot11_BSS_type_infrastructure = 1,
    dot11_BSS_type_independent = 2,
    dot11_BSS_type_any = 3
    }
DOT11_BSS_TYPE          typedef _DOT11_BSS_TYPE
PDOT11_BSS_TYPE         typedef ptr _DOT11_BSS_TYPE

define DOT11_SSID_MAX_LENGTH   32

_DOT11_SSID             struct
uSSIDLength             ULONG ?
ucSSID                  UCHAR DOT11_SSID_MAX_LENGTH dup(?)
_DOT11_SSID             ends
DOT11_SSID              typedef _DOT11_SSID
PDOT11_SSID             typedef ptr _DOT11_SSID

.enum _DOT11_AUTH_ALGORITHM {
    DOT11_AUTH_ALGO_80211_OPEN          = 1,
    DOT11_AUTH_ALGO_80211_SHARED_KEY    = 2,
    DOT11_AUTH_ALGO_WPA                 = 3,
    DOT11_AUTH_ALGO_WPA_PSK             = 4,
    DOT11_AUTH_ALGO_WPA_NONE            = 5,
    DOT11_AUTH_ALGO_RSNA                = 6,
    DOT11_AUTH_ALGO_RSNA_PSK            = 7,
    DOT11_AUTH_ALGO_WPA3                = 8,
    DOT11_AUTH_ALGO_WPA3_SAE            = 9,
if (NTDDI_VERSION ge NTDDI_WIN10_VB)
    DOT11_AUTH_ALGO_OWE                 = 10,
endif
    DOT11_AUTH_ALGO_IHV_START           = 0x80000000,
    DOT11_AUTH_ALGO_IHV_END             = 0xffffffff
    }
DOT11_AUTH_ALGORITHM    typedef _DOT11_AUTH_ALGORITHM
PDOT11_AUTH_ALGORITHM   typedef ptr _DOT11_AUTH_ALGORITHM

define DOT11_AUTH_ALGORITHM_OPEN_SYSTEM        DOT11_AUTH_ALGO_80211_OPEN
define DOT11_AUTH_ALGORITHM_SHARED_KEY         DOT11_AUTH_ALGO_80211_SHARED_KEY
define DOT11_AUTH_ALGORITHM_WPA                DOT11_AUTH_ALGO_WPA
define DOT11_AUTH_ALGORITHM_WPA_PSK            DOT11_AUTH_ALGO_WPA_PSK
define DOT11_AUTH_ALGORITHM_WPA_NONE           DOT11_AUTH_ALGO_WPA_NONE
define DOT11_AUTH_ALGORITHM_RSNA               DOT11_AUTH_ALGO_RSNA
define DOT11_AUTH_ALGORITHM_RSNA_PSK           DOT11_AUTH_ALGO_RSNA_PSK
define DOT11_AUTH_ALGORITHM_WPA3               DOT11_AUTH_ALGO_WPA3
define DOT11_AUTH_ALGORITHM_WPA3_SAE           DOT11_AUTH_ALGO_WPA3_SAE
if (NTDDI_VERSION ge NTDDI_WIN10_VB)
define DOT11_AUTH_ALGORITHM_OWE                DOT11_AUTH_ALGO_OWE
endif


.enum _DOT11_CIPHER_ALGORITHM {
    DOT11_CIPHER_ALGO_NONE = 0x00,
    DOT11_CIPHER_ALGO_WEP40 = 0x01,
    DOT11_CIPHER_ALGO_TKIP = 0x02,
    DOT11_CIPHER_ALGO_CCMP = 0x04,
    DOT11_CIPHER_ALGO_WEP104 = 0x05,
    DOT11_CIPHER_ALGO_BIP = 0x06,
    DOT11_CIPHER_ALGO_GCMP = 0x08,
    DOT11_CIPHER_ALGO_GCMP_256 = 0x09,
    DOT11_CIPHER_ALGO_CCMP_256 = 0x0a,
    DOT11_CIPHER_ALGO_BIP_GMAC_128 = 0x0b,
    DOT11_CIPHER_ALGO_BIP_GMAC_256 = 0x0c,
    DOT11_CIPHER_ALGO_BIP_CMAC_256 = 0x0d,
    DOT11_CIPHER_ALGO_WPA_USE_GROUP = 0x100,
    DOT11_CIPHER_ALGO_RSN_USE_GROUP = 0x100,
    DOT11_CIPHER_ALGO_WEP = 0x101,
    DOT11_CIPHER_ALGO_IHV_START = 0x80000000,
    DOT11_CIPHER_ALGO_IHV_END = 0xffffffff
    }
DOT11_CIPHER_ALGORITHM  typedef _DOT11_CIPHER_ALGORITHM
PDOT11_CIPHER_ALGORITHM typedef ptr _DOT11_CIPHER_ALGORITHM

DOT11_AUTH_CIPHER_PAIR  struct
AuthAlgoId              DOT11_AUTH_ALGORITHM ?
CipherAlgoId            DOT11_CIPHER_ALGORITHM ?
DOT11_AUTH_CIPHER_PAIR  ends
PDOT11_AUTH_CIPHER_PAIR typedef ptr DOT11_AUTH_CIPHER_PAIR

define DOT11_OI_MAX_LENGTH   5
define DOT11_OI_MIN_LENGTH   3
_DOT11_OI               struct
OILength                USHORT ?
OI                      UCHAR DOT11_OI_MAX_LENGTH dup(?)
_DOT11_OI               ends
DOT11_OI                typedef _DOT11_OI
PDOT11_OI               typedef ptr _DOT11_OI

DOT11_ACCESSNETWORKOPTIONS struct
AccessNetworkType       UINT8 ?
Internet                UINT8 ?
ASRA                    UINT8 ?
ESR                     UINT8 ?
UESA                    UINT8 ?
DOT11_ACCESSNETWORKOPTIONS ends
PDOT11_ACCESSNETWORKOPTIONS typedef ptr DOT11_ACCESSNETWORKOPTIONS

DOT11_VENUEINFO         struct
VenueGroup              UINT8 ?
VenueType               UINT8 ?
DOT11_VENUEINFO         ends
PDOT11_VENUEINFO        typedef ptr DOT11_VENUEINFO

endif

endif
