ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;;  Cryptographic API Prototypes and Definitions
;;
ifndef __WINCRYPT_H__
__WINCRYPT_H__ equ 1


if(_WIN32_WINNT GE 0x0400)

ifndef _HRESULT_DEFINED
_HRESULT_DEFINED	equ 1
HRESULT			typedef LONG

endif ;; NOT _HRESULT_DEFINED

if NOT defined(_CRYPT32_)
WINCRYPT32API		equ DECSPEC_IMPORT
else
WINCRYPT32API		equ 1
endif

;;
;; Algorithm IDs and Flags
;;

;; ALG_ID crackers
GET_ALG_CLASS macro x
	exitm<(x AND (7 SHL 13))>
	endm
GET_ALG_TYPE macro x
	exitm<(x AND (15 SHL 9))>
	endm
GET_ALG_SID macro x
	exitm<(x AND (511))>
	endm

;; Algorithm classes
ALG_CLASS_ANY		equ (0)
ALG_CLASS_SIGNATURE	equ (1 SHL 13)
ALG_CLASS_MSG_ENCRYPT	equ (2 SHL 13)
ALG_CLASS_DATA_ENCRYPT	equ (3 SHL 13)
ALG_CLASS_HASH		equ (4 SHL 13)
ALG_CLASS_KEY_EXCHANGE	equ (5 SHL 13)

;; Algorithm types
ALG_TYPE_ANY		equ (0)
ALG_TYPE_DSS		equ (1 SHL 9)
ALG_TYPE_RSA		equ (2 SHL 9)
ALG_TYPE_BLOCK		equ (3 SHL 9)
ALG_TYPE_STREAM		equ (4 SHL 9)
ALG_TYPE_DH		equ (5 SHL 9)
ALG_TYPE_SECURECHANNEL	equ (6 SHL 9)

;; Generic sub-ids
ALG_SID_ANY		equ (0)

;; Some RSA sub-ids
ALG_SID_RSA_ANY		equ 0
ALG_SID_RSA_PKCS	equ 1
ALG_SID_RSA_MSATWORK	equ 2
ALG_SID_RSA_ENTRUST	equ 3
ALG_SID_RSA_PGP		equ 4

;; Some DSS sub-ids
;;
ALG_SID_DSS_ANY		equ 0
ALG_SID_DSS_PKCS	equ 1
ALG_SID_DSS_DMS		equ 2

;; Block cipher sub ids
;; DES sub_ids
ALG_SID_DES		equ 1
ALG_SID_3DES		equ 3
ALG_SID_DESX		equ 4
ALG_SID_IDEA		equ 5
ALG_SID_CAST		equ 6
ALG_SID_SAFERSK64	equ 7
ALG_SID_SAFERSK128	equ 8
ALG_SID_3DES_112	equ 9
ALG_SID_CYLINK_MEK	equ 12
ALG_SID_RC5		equ 13

;; Fortezza sub-ids
ALG_SID_SKIPJACK	equ 10
ALG_SID_TEK		equ 11

;; KP_MODE
CRYPT_MODE_CBCI		equ 6	;; ANSI CBC Interleaved
CRYPT_MODE_CFBP		equ 7	;; ANSI CFB Pipelined
CRYPT_MODE_OFBP		equ 8	;; ANSI OFB Pipelined
CRYPT_MODE_CBCOFM	equ 9	;; ANSI CBC + OF Masking
CRYPT_MODE_CBCOFMI	equ 10	;; ANSI CBC + OFM Interleaved

;; RC2 sub-ids
ALG_SID_RC2		equ 2

;; Stream cipher sub-ids
ALG_SID_RC4		equ 1
ALG_SID_SEAL		equ 2

;; Diffie-Hellman sub-ids
ALG_SID_DH_SANDF	equ 1
ALG_SID_DH_EPHEM	equ 2
ALG_SID_AGREED_KEY_ANY	equ 3
ALG_SID_KEA		equ 4

;; Hash sub ids
ALG_SID_MD2		equ 1
ALG_SID_MD4		equ 2
ALG_SID_MD5		equ 3
ALG_SID_SHA		equ 4
ALG_SID_SHA1		equ 4
ALG_SID_MAC		equ 5
ALG_SID_RIPEMD		equ 6
ALG_SID_RIPEMD160	equ 7
ALG_SID_SSL3SHAMD5	equ 8
ALG_SID_HMAC		equ 9

;; secure channel sub ids
ALG_SID_SSL3_MASTER	equ 1
ALG_SID_SCHANNEL_MASTER_HASH equ 2
ALG_SID_SCHANNEL_MAC_KEY equ 3
ALG_SID_PCT1_MASTER	equ 4
ALG_SID_SSL2_MASTER	equ 5
ALG_SID_TLS1_MASTER	equ 6
ALG_SID_SCHANNEL_ENC_KEY equ 7

;; Our silly example sub-id
ALG_SID_EXAMPLE		equ 80

ifndef ALGIDDEF
ALGIDDEF equ 1
ALG_ID			typedef UINT
endif

;; algorithm identifier definitions
CALG_MD2		equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR AG_SID_MD2)
CALG_MD4		equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR AG_SID_MD4)
CALG_MD5		equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR AG_SID_MD5)
CALG_SHA		equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR AG_SID_SHA)
CALG_SHA1		equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR AG_SID_SHA1)
CALG_MAC		equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR AG_SID_MAC)
CALG_RSA_SIGN		equ (ALG_CLASS_SIGNATURE OR ALG_TYPE_RSA OR AG_SID_RSA_ANY)
CALG_DSS_SIGN		equ (ALG_CLASS_SIGNATURE OR ALG_TYPE_DSS OR AG_SID_DSS_ANY)
CALG_RSA_KEYX		equ (ALG_CLASS_KEY_EXCHANGE OR ALG_TYPE_RSA OR AG_SID_RSA_ANY)
CALG_DES		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR AG_SID_DES)
CALG_3DES_112		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR AG_SID_3DES_112)
CALG_3DES		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR AG_SID_3DES)
CALG_RC2		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR AG_SID_RC2)
CALG_RC4		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_STREAM OR AG_SID_RC4)
CALG_SEAL		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_STREAM OR ALG_SID_SEA)
CALG_DH_SF		equ (ALG_CLASS_KEY_EXCHANGE OR ALG_TYPE_DH OR AG_SID_DH_SANDF)
CALG_DH_EPHEM		equ (ALG_CLASS_KEY_EXCHANGE OR ALG_TYPE_DH OR AG_SID_DH_EPHEM)
CALG_AGREEDKEY_ANY	equ (ALG_CLASS_KEY_EXCHANGE OR ALG_TYPE_DH OR AG_SID_AGREED_KEY_ANY)
CALG_KEA_KEYX		equ (ALG_CLASS_KEY_EXCHANGE OR ALG_TYPE_DH OR AG_SID_KEA)
CALG_HUGHES_MD5		equ (ALG_CLASS_KEY_EXCHANGE OR ALG_TYPE_ANY OR AG_SID_MD5)
CALG_SKIPJACK		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR AG_SID_SKIPJACK)
CALG_TEK		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR AG_SID_TEK)
CALG_CYLINK_MEK		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR ALG_SID_CYLINK_MEK)
CALG_SSL3_SHAMD5	equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR ALG_SID_SSL3SHAMD5)
CALG_SSL3_MASTER	equ (ALG_CLASS_MSG_ENCRYPT OR ALG_TYPE_SECURECHANNEL OR ALG_SID_SSL3_MASTER)
CALG_SCHANNEL_MASTER_HASH equ (ALG_CLASS_MSG_ENCRYPT OR ALG_TYPE_SECURECHANNEL OR ALG_SID_SCHANNE_MASTER_HASH)
CALG_SCHANNEL_MAC_KEY	equ (ALG_CLASS_MSG_ENCRYPT OR ALG_TYPE_SECURECHANNEL OR ALG_SID_SCHANNE_MAC_KEY)
CALG_SCHANNEL_ENC_KEY	equ (ALG_CLASS_MSG_ENCRYPT OR ALG_TYPE_SECURECHANNEL OR ALG_SID_SCHANNE_ENC_KEY)
CALG_PCT1_MASTER	equ (ALG_CLASS_MSG_ENCRYPT OR ALG_TYPE_SECURECHANNEL OR AG_SID_PCT1_MASTER)
CALG_SSL2_MASTER	equ (ALG_CLASS_MSG_ENCRYPT OR ALG_TYPE_SECURECHANNEL OR ALG_SID_SSL2_MASTER)
CALG_TLS1_MASTER	equ (ALG_CLASS_MSG_ENCRYPT OR ALG_TYPE_SECURECHANNEL OR ALG_SID_TLS1_MASTER)
CALG_RC5		equ (ALG_CLASS_DATA_ENCRYPT OR ALG_TYPE_BLOCK OR AG_SID_RC5)
CALG_HMAC		equ (ALG_CLASS_HASH OR ALG_TYPE_ANY OR AG_SID_HMAC)

VTableProvStruc		STRUC
Version			dd ?
FuncVerifyImage		FARPROC ?
FuncReturnhWnd		FARPROC ?
dwProvType		dd ?
pbContextInfo		LPSTR ?
cbContextInfo		dd ?
VTableProvStruc		ENDS
PVTableProvStruc	typedef ptr VTableProvStruc

HCRYPTPROV		typedef DWORD
HCRYPTKEY		typedef DWORD
HCRYPTHASH		typedef DWORD

;; dwFlags definitions for CryptAcquireContext
CRYPT_VERIFYCONTEXT	equ 0xF0000000
CRYPT_NEWKEYSET		equ 0x00000008
CRYPT_DELETEKEYSET	equ 0x00000010
CRYPT_MACHINE_KEYSET	equ 0x00000020

;; dwFlag definitions for CryptGenKey
CRYPT_EXPORTABLE	equ 0x00000001
CRYPT_USER_PROTECTED	equ 0x00000002
CRYPT_CREATE_SALT	equ 0x00000004
CRYPT_UPDATE_KEY	equ 0x00000008
CRYPT_NO_SALT		equ 0x00000010
CRYPT_PREGEN		equ 0x00000040
CRYPT_RECIPIENT		equ 0x00000010
CRYPT_INITIATOR		equ 0x00000040
CRYPT_ONLINE		equ 0x00000080
CRYPT_SF		equ 0x00000100
CRYPT_CREATE_IV		equ 0x00000200
CRYPT_KEK		equ 0x00000400
CRYPT_DATA_KEY		equ 0x00000800

;; dwFlags definitions for CryptDeriveKey
CRYPT_SERVER		equ 0x00000400

KEY_LENGTH_MASK		equ 0xFFFF0000

;; dwFlag definitions for CryptExportKey
CRYPT_Y_ONLY		equ 0x00000001
CRYPT_SSL2_SLUMMING	equ 0x00000002

;; dwFlags definitions for CryptHashSessionKey
CRYPT_LITTLE_ENDIAN	equ 0x00000001

;; dwFlag definitions for CryptSetProviderEx and CryptGetDefaultProvider
CRYPT_MACHINE_DEFAULT	equ 0x00000001
CRYPT_USER_DEFAULT	equ 0x00000002
CRYPT_DELETE_DEFAULT	equ 0x00000004

;; exported key blob definitions
SIMPLEBLOB		equ 0x1
PUBLICKEYBLOB		equ 0x6
PRIVATEKEYBLOB		equ 0x7
PLAINTEXTKEYBLOB	equ 0x8

AT_KEYEXCHANGE		equ 1
AT_SIGNATURE		equ 2

CRYPT_USERDATA		equ 1

;; dwParam
KP_IV			equ 1	;; Initialization vector
KP_SALT			equ 2	;; Salt value
KP_PADDING		equ 3	;; Padding values
KP_MODE			equ 4	;; Mode of the cipher
KP_MODE_BITS		equ 5	;; Number of bits to feedback
KP_PERMISSIONS		equ 6	;; Key permissions DWORD
KP_ALGID		equ 7	;; Key algorithm
KP_BLOCKLEN		equ 8	;; Block size of the cipher
KP_KEYLEN		equ 9	;; Length of key in bits
KP_SALT_EX		equ 10	;; Length of salt in bytes
KP_P			equ 11	;; DSS/Diffie-Hellman P value
KP_G			equ 12	;; DSS/Diffie-Hellman G value
KP_Q			equ 13	;; DSS Q value
KP_X			equ 14	;; Diffie-Hellman X value
KP_Y			equ 15	;; Y value
KP_RA			equ 16	;; Fortezza RA value
KP_RB			equ 17	;; Fortezza RB value
KP_INFO			equ 18	;; for putting information into an RSA envelope
KP_EFFECTIVE_KEYLEN	equ 19	;; setting and getting RC2 effective key length
KP_SCHANNEL_ALG		equ 20	;; for setting the Secure Channel algorithms
KP_CLIENT_RANDOM	equ 21	;; for setting the Secure Channel client random data
KP_SERVER_RANDOM	equ 22	;; for setting the Secure Channel server random data
KP_RP			equ 23
KP_PRECOMP_MD5		equ 24
KP_PRECOMP_SHA		equ 25
KP_CERTIFICATE		equ 26	;; for setting Secure Channel certificate data (PCT1)
KP_CLEAR_KEY		equ 27	;; for setting Secure Channel clear key data (PCT1)
KP_PUB_EX_LEN		equ 28
KP_PUB_EX_VAL		equ 29

;; KP_PADDING
PKCS5_PADDING		equ 1	;; PKCS 5 (sec 6.2) padding method
RANDOM_PADDING		equ 2
ZERO_PADDING		equ 3

;; KP_MODE
CRYPT_MODE_CBC		equ 1	;; Cipher block chaining
CRYPT_MODE_ECB		equ 2	;; Electronic code book
CRYPT_MODE_OFB		equ 3	;; Output feedback mode
CRYPT_MODE_CFB		equ 4	;; Cipher feedback mode
CRYPT_MODE_CTS		equ 5	;; Ciphertext stealing mode

;; KP_PERMISSIONS
CRYPT_ENCRYPT		equ 0x0001	;; Allow encryption
CRYPT_DECRYPT		equ 0x0002	;; Allow decryption
CRYPT_EXPORT		equ 0x0004	;; Allow key to be exported
CRYPT_READ		equ 0x0008	;; Allow parameters to be read
CRYPT_WRITE		equ 0x0010	;; Allow parameters to be set
CRYPT_MAC		equ 0x0020	;; Allow MACs to be used with key
CRYPT_EXPORT_KEY	equ 0x0040	;; Allow key to be used for exporting keys
CRYPT_IMPORT_KEY	equ 0x0080	;; Allow key to be used for importing keys

HP_ALGID		equ 0x0001	;; Hash algorithm
HP_HASHVAL		equ 0x0002	;; Hash value
HP_HASHSIZE		equ 0x0004	;; Hash value size
HP_HMAC_INFO		equ 0x0005	;; information for creating an HMAC

CRYPT_FAILED		equ FASE
CRYPT_SUCCEED		equ TRUE

RCRYPT_SUCCEEDED macro rt
	exitm<((rt) EQ CRYPT_SUCCEED)>
	endm
RCRYPT_FAILED macro rt
	exitm<((rt) EQ CRYPT_FAILED)>
	endm

;;
;; CryptGetProvParam
;;
PP_ENUMALGS		equ 1
PP_ENUMCONTAINERS	equ 2
PP_IMPTYPE		equ 3
PP_NAME			equ 4
PP_VERSION		equ 5
PP_CONTAINER		equ 6
PP_CHANGE_PASSWORD	equ 7
PP_KEYSET_SEC_DESCR	equ 8	;; get/set security descriptor of keyset
PP_CERTCHAIN		equ 9	;; for retrieving certificates from tokens
PP_KEY_TYPE_SUBTYPE	equ 10
PP_PROVTYPE		equ 16
PP_KEYSTORAGE		equ 17
PP_APPLI_CERT		equ 18
PP_SYM_KEYSIZE		equ 19
PP_SESSION_KEYSIZE	equ 20
PP_UI_PROMPT		equ 21
PP_ENUMALGS_EX		equ 22

CRYPT_FIRST		equ 1
CRYPT_NEXT		equ 2

CRYPT_IMPL_HARDWARE	equ 1
CRYPT_IMPL_SOFTWARE	equ 2
CRYPT_IMPL_MIXED	equ 3
CRYPT_IMPL_UNKNOWN	equ 4

;; key storage flags
CRYPT_SEC_DESCR		equ 0x00000001
CRYPT_PSTORE		equ 0x00000002
CRYPT_UI_PROMPT		equ 0x00000004

;; protocol flags
CRYPT_FLAG_PCT1		equ 0x0001
CRYPT_FLAG_SSL2		equ 0x0002
CRYPT_FLAG_SSL3		equ 0x0004
CRYPT_FLAG_TLS1		equ 0x0008

;;
;; CryptSetProvParam
;;
PP_CLIENT_HWND		equ 1
PP_CONTEXT_INFO		equ 11
PP_KEYEXCHANGE_KEYSIZE	equ 12
PP_SIGNATURE_KEYSIZE	equ 13
PP_KEYEXCHANGE_ALG	equ 14
PP_SIGNATURE_ALG	equ 15
PP_DELETEKEY		equ 24

PROV_RSA_FULL		equ 1
PROV_RSA_SIG		equ 2
PROV_DSS		equ 3
PROV_FORTEZZA		equ 4
PROV_MS_EXCHANGE	equ 5
PROV_SSL		equ 6
PROV_RSA_SCHANNEL	equ 12
PROV_DSS_DH		equ 13
PROV_EC_ECDSA_SIG	equ 14
PROV_EC_ECNRA_SIG	equ 15
PROV_EC_ECDSA_FULL	equ 16
PROV_EC_ECNRA_FULL	equ 17
PROV_SPYRUS_LYNKS	equ 20

;;
;; STT defined Providers
;;
PROV_STT_MER		equ 7
PROV_STT_ACQ		equ 8
PROV_STT_BRND		equ 9
PROV_STT_ROOT		equ 10
PROV_STT_ISS		equ 11

;;
;; Provider friendly names
;;
MS_DEF_PROV		equ <"Microsoft Base Cryptographic Provider v1.0">
MS_ENHANCED_PROV	equ <"Microsoft Enhanced Cryptographic Provider v1.0">
MS_DEF_RSA_SIG_PROV	equ <"Microsoft RSA Signature Cryptographic Provider">
MS_DEF_RSA_SCHANNEL_PROV equ <"Microsoft Base RSA SChannel Cryptographic Provider">
MS_ENHANCED_RSA_SCHANNEL_PROV equ <"Microsoft Enhanced RSA SChannel Cryptographic Provider">
MS_DEF_DSS_PROV		equ <"Microsoft Base DSS Cryptographic Provider">
MS_DEF_DSS_DH_PROV	equ <"Microsoft Base DSS and Diffie-Hellman Cryptographic Provider">


MAXUIDLEN		equ 64

CUR_BLOB_VERSION	equ 2

;; structure for use with CryptSetHashParam with CALG_HMAC
HMAC_INFO		STRUC
HashAlgid		ALG_ID ?
pbInnerString		LPSTR ?
cbInnerString		dd ?
pbOuterString		LPSTR ?
cbOuterString		dd ?
HMAC_INFO		ENDS
PHMAC_INFO		typedef ptr HMAC_INFO

;; structure for use with CryptSetKeyParam with KP_SCHANNEL_ALG
SCHANNEL_ALG		STRUC
dwUse			dd ?
Algid			ALG_ID ?
cBits			dd ?
SCHANNEL_ALG		ENDS
PSCHANNEL_ALG		typedef ptr SCHANNEL_ALG

;; uses of algortihms for SCHANNEL_ALG structure
SCHANNEL_MAC_KEY	equ 0x00000000
SCHANNEL_ENC_KEY	equ 0x00000001

PROV_ENUMALGS		STRUC
aiAlgid			ALG_ID ?
dwBitLen		dd ?
dwNameLen		dd ?
szName			db 20 dup(?)
PROV_ENUMALGS		ENDS

PROV_ENUMALGS_EX	STRUC
aiAlgid			ALG_ID ?
dwDefaultLen		dd ?
dwMinLen		dd ?
dwMaxLen		dd ?
dwProtocols		dd ?
dwNameLen		dd ?
szName			db 20 dup(?)
dwLongNameLen		dd ?
szLongName		db 40 dup(?)
PROV_ENUMALGS_EX	ENDS

BLOBHEADER		STRUC
bType			db ?
bVersion		db ?
reserved		dw ?
aiKeyAlg		ALG_ID ?
BLOBHEADER		ENDS
PUBLICKEYSTRUC		typedef BLOBHEADER

RSAPUBKEY		STRUC
magic			dd ?	;; Has to be RSA1
bitlen			dd ?	;; # of bits in modulus
pubexp			dd ?	;; public exponent
				;; Modulus data follows
RSAPUBKEY		ENDS

DHPUBKEY		STRUC
magic			dd ?
bitlen			dd ?	;; # of bits in modulus
DHPUBKEY		ENDS
DSSPUBKEY		typedef DHPUBKEY
KEAPUBKEY		typedef DHPUBKEY
TEKPUBKEY		typedef DHPUBKEY

DSSSEED			STRUC
counter			dd ?
seed			db 20 dup(?)
DSSSEED			ENDS

KEY_TYPE_SUBTYPE	STRUC
dwKeySpec		dd ?
_Type			GUID <>
Subtype			GUID <>
KEY_TYPE_SUBTYPE	ENDS
PKEY_TYPE_SUBTYPE	typedef ptr KEY_TYPE_SUBTYPE


;BOOL
CryptAcquireContextA proto _CType \
		phProv: ptr HCRYPTPROV,
	  pszContainer: LPCSTR,
	   pszProvider: LPCSTR,
	    dwProvType: DWORD,
	       dwFlags: DWORD
;BOOL
CryptAcquireContextW proto _CType \
		phProv: ptr HCRYPTPROV,
	  pszContainer: LPCWSTR,
	   pszProvider: LPCWSTR,
	    dwProvType: DWORD,
	       dwFlags: DWORD
ifdef _UNICODE
CryptAcquireContext	equ <CryptAcquireContextW>
else
CryptAcquireContext	equ <CryptAcquireContextA>
endif ;; NOT UNICODE


;BOOL
CryptReleaseContext proto _CType \
		 hProv: HCRYPTPROV,
	       dwFlags: DWORD


;BOOL
CryptGenKey proto _CType \
		 hProv: HCRYPTPROV,
		 Algid: ALG_ID,
	       dwFlags: DWORD,
		 phKey: ptr HCRYPTKEY

;BOOL
CryptDeriveKey proto _CType \
		 hProv: HCRYPTPROV,
		 Algid: ALG_ID,
	     hBaseData: HCRYPTHASH,
	       dwFlags: DWORD,
		 phKey: ptr HCRYPTKEY


;BOOL
CryptDestroyKey proto _CType \
		  hKey: HCRYPTKEY

;BOOL
CryptSetKeyParam proto _CType \
		  hKey: HCRYPTKEY,
	       dwParam: DWORD,
		pbData: LPBYTE,
	       dwFlags: DWORD

;BOOL
CryptGetKeyParam proto _CType \
		  hKey: HCRYPTKEY,
	       dwParam: DWORD,
		pbData: LPBYTE,
	    pdwDataLen: LPDWORD,
	       dwFlags: DWORD

;BOOL
CryptSetHashParam proto _CType \
		 hHash: HCRYPTHASH,
	       dwParam: DWORD,
		pbData: LPBYTE,
	       dwFlags: DWORD

;BOOL
CryptGetHashParam proto _CType \
		 hHash: HCRYPTHASH,
	       dwParam: DWORD,
		pbData: LPBYTE,
	    pdwDataLen: LPDWORD,
	       dwFlags: DWORD

;BOOL
CryptSetProvParam proto _CType \
		 hProv: HCRYPTPROV,
	       dwParam: DWORD,
		pbData: LPBYTE,
	       dwFlags: DWORD

;BOOL
CryptGetProvParam proto _CType \
		 hProv: HCRYPTPROV,
	       dwParam: DWORD,
		pbData: LPBYTE,
	    pdwDataLen: LPDWORD,
	       dwFlags: DWORD

;BOOL
CryptGenRandom proto _CType \
		 hProv: HCRYPTPROV,
		 dwLen: DWORD,
	      pbBuffer: LPBYTE

;BOOL
CryptGetUserKey proto _CType \
		 hProv: HCRYPTPROV,
	     dwKeySpec: DWORD,
	     phUserKey: ptr HCRYPTKEY

;BOOL
CryptExportKey proto _CType \
		  hKey: HCRYPTKEY,
	       hExpKey: HCRYPTKEY,
	    dwBlobType: DWORD,
	       dwFlags: DWORD,
		pbData: LPBYTE,
	    pdwDataLen: LPDWORD

;BOOL
CryptImportKey proto _CType \
		 hProv: HCRYPTPROV,
		pbData: LPBYTE,
	     dwDataLen: DWORD,
	       hPubKey: HCRYPTKEY,
	       dwFlags: DWORD,
		 phKey: ptr HCRYPTKEY

;BOOL
CryptEncrypt proto _CType \
		  hKey: HCRYPTKEY,
		 hHash: HCRYPTHASH,
		 Final: BOOL,
	       dwFlags: DWORD,
		pbData: LPBYTE,
	    pdwDataLen: LPDWORD,
	      dwBufLen: DWORD

;BOOL
CryptDecrypt proto _CType \
		  hKey: HCRYPTKEY,
		 hHash: HCRYPTHASH,
		 Final: BOOL,
	       dwFlags: DWORD,
		pbData: LPBYTE,
	    pdwDataLen: LPDWORD

;BOOL
CryptCreateHash proto _CType \
		 hProv: HCRYPTPROV,
		 Algid: ALG_ID,
		  hKey: HCRYPTKEY,
	       dwFlags: DWORD,
		phHash: ptr HCRYPTHASH

;BOOL
CryptHashData proto _CType \
		 hHash: HCRYPTHASH,
		pbData: LPBYTE,
	     dwDataLen: DWORD,
	       dwFlags: DWORD

;BOOL
CryptHashSessionKey proto _CType \
		 hHash: HCRYPTHASH,
		  hKey: HCRYPTKEY,
	       dwFlags: DWORD

;BOOL
CryptDestroyHash proto _CType \
		 hHash: HCRYPTHASH

;BOOL
CryptSignHashA proto _CType \
		 hHash: HCRYPTHASH,
	     dwKeySpec: DWORD,
	  sDescription: LPCSTR,
	       dwFlags: DWORD,
	   pbSignature: LPBYTE,
	     pdwSigLen: LPDWORD
;BOOL
CryptSignHashW proto _CType \
		 hHash: HCRYPTHASH,
	     dwKeySpec: DWORD,
	  sDescription: LPCWSTR,
	       dwFlags: DWORD,
	   pbSignature: LPBYTE,
	     pdwSigLen: LPDWORD
ifdef _UNICODE
CryptSignHash		equ <CryptSignHashW>
else
CryptSignHash		equ <CryptSignHashA>
endif ;; NOT UNICODE

;BOOL
CryptVerifySignatureA proto _CType \
		 hHash: HCRYPTHASH,
	   pbSignature: LPBYTE,
	      dwSigLen: DWORD,
	       hPubKey: HCRYPTKEY,
	  sDescription: LPCSTR,
	       dwFlags: DWORD
;BOOL
CryptVerifySignatureW proto _CType \
		 hHash: HCRYPTHASH,
	   pbSignature: LPBYTE,
	      dwSigLen: DWORD,
	       hPubKey: HCRYPTKEY,
	  sDescription: LPCWSTR,
	       dwFlags: DWORD
ifdef _UNICODE
CryptVerifySignature	equ <CryptVerifySignatureW>
else
CryptVerifySignature	equ <CryptVerifySignatureA>
endif ;; NOT UNICODE

;BOOL
CryptSetProviderA proto _CType \
	   pszProvName: LPCSTR,
	    dwProvType: DWORD
;BOOL
CryptSetProviderW proto _CType \
	   pszProvName: LPCWSTR,
	    dwProvType: DWORD
ifdef _UNICODE
CryptSetProvider	equ <CryptSetProviderW>
else
CryptSetProvider	equ <CryptSetProviderA>
endif ;; NOT UNICODE

;BOOL
CryptSetProviderExA proto _CType \
	   pszProvName: LPCSTR,
	    dwProvType: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD
;BOOL
CryptSetProviderExW proto _CType \
	   pszProvName: LPCWSTR,
	    dwProvType: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD
ifdef _UNICODE
CryptSetProviderEx	equ <CryptSetProviderExW>
else
CryptSetProviderEx	equ <CryptSetProviderExA>
endif ;; NOT UNICODE

;BOOL
CryptGetDefaultProviderA proto _CType \
	    dwProvType: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
	   pszProvName: LPSTR,
	   pcbProvName: LPDWORD
;BOOL
CryptGetDefaultProviderW proto _CType \
	    dwProvType: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
	   pszProvName: LPWSTR,
	   pcbProvName: LPDWORD
ifdef _UNICODE
CryptGetDefaultProvider equ <CryptGetDefaultProviderW>
else
CryptGetDefaultProvider equ <CryptGetDefaultProviderA>
endif ;; NOT UNICODE

;BOOL
CryptEnumProviderTypesA proto _CType \
	       dwIndex: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
	   pdwProvType: LPDWORD,
	   pszTypeName: LPSTR,
	   pcbTypeName: LPDWORD
;BOOL
CryptEnumProviderTypesW proto _CType \
	       dwIndex: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
	   pdwProvType: LPDWORD,
	   pszTypeName: LPWSTR,
	   pcbTypeName: LPDWORD
ifdef _UNICODE
CryptEnumProviderTypes	equ <CryptEnumProviderTypesW>
else
CryptEnumProviderTypes	equ <CryptEnumProviderTypesA>
endif ;; NOT UNICODE

;BOOL
CryptEnumProvidersA proto _CType \
	       dwIndex: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
	   pdwProvType: LPDWORD,
	   pszProvName: LPSTR,
	   pcbProvName: LPDWORD
;BOOL
CryptEnumProvidersW proto _CType \
	       dwIndex: DWORD,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
	   pdwProvType: LPDWORD,
	   pszProvName: LPWSTR,
	   pcbProvName: LPDWORD
ifdef _UNICODE
CryptEnumProviders	equ <CryptEnumProvidersW>
else
CryptEnumProviders	equ <CryptEnumProvidersA>
endif ;; NOT UNICODE

;BOOL
CryptContextAddRef proto _CType \
		 hProv: HCRYPTPROV,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD

;BOOL
CryptDuplicateKey proto _CType \
		  hKey: HCRYPTKEY,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
		 phKey: ptr HCRYPTKEY

;BOOL
CryptDuplicateHash proto _CType \
		 hHash: HCRYPTHASH,
	   pdwReserved: LPDWORD,
	       dwFlags: DWORD,
		phHash: ptr HCRYPTHASH

;;+-------------------------------------------------------------------------
;;  CRYPTOAPI BLOB definitions
;;--------------------------------------------------------------------------
CRYPT_INTEGER_BLOB	STRUC
cbData			dd ?
pbData			LPSTR ?
CRYPT_INTEGER_BLOB	ENDS

PCRYPT_INTEGER_BLOB	typedef ptr CRYPT_INTEGER_BLOB
CRYPT_UINT_BLOB		typedef CRYPT_INTEGER_BLOB
PCRYPT_UINT_BLOB	typedef ptr CRYPT_INTEGER_BLOB
CRYPT_OBJID_BLOB	typedef CRYPT_INTEGER_BLOB
PCRYPT_OBJID_BLOB	typedef ptr CRYPT_INTEGER_BLOB
CERT_NAME_BLOB		typedef CRYPT_INTEGER_BLOB
PCERT_NAME_BLOB		typedef ptr CRYPT_INTEGER_BLOB
CERT_RDN_VALUE_BLOB	typedef CRYPT_INTEGER_BLOB
PCERT_RDN_VALUE_BLOB	typedef ptr CRYPT_INTEGER_BLOB
CERT_BLOB		typedef CRYPT_INTEGER_BLOB
PCERT_BLOB		typedef ptr CRYPT_INTEGER_BLOB
CRL_BLOB		typedef CRYPT_INTEGER_BLOB
PCRL_BLOB		typedef ptr CRYPT_INTEGER_BLOB
DATA_BLOB		typedef CRYPT_INTEGER_BLOB
PDATA_BLOB		typedef ptr CRYPT_INTEGER_BLOB
CRYPT_DATA_BLOB		typedef CRYPT_INTEGER_BLOB
PCRYPT_DATA_BLOB	typedef ptr CRYPT_INTEGER_BLOB
CRYPT_HASH_BLOB		typedef CRYPT_INTEGER_BLOB
PCRYPT_HASH_BLOB	typedef ptr CRYPT_INTEGER_BLOB
CRYPT_DIGEST_BLOB	typedef CRYPT_INTEGER_BLOB
PCRYPT_DIGEST_BLOB	typedef ptr CRYPT_INTEGER_BLOB
CRYPT_DER_BLOB		typedef CRYPT_INTEGER_BLOB
PCRYPT_DER_BLOB		typedef ptr CRYPT_INTEGER_BLOB
CRYPT_ATTR_BLOB		typedef CRYPT_INTEGER_BLOB
PCRYPT_ATTR_BLOB	typedef ptr CRYPT_INTEGER_BLOB


;;+-------------------------------------------------------------------------
;;  In a CRYPT_BIT_BLOB the last byte may contain 0-7 unused bits. Therefore, the
;;  overall bit length is cbData * 8 - cUnusedBits.
;;--------------------------------------------------------------------------
CRYPT_BIT_BLOB		STRUC
cbData			dd ?
pbData			LPSTR ?
cUnusedBits		dd ?
CRYPT_BIT_BLOB		ENDS
PCRYPT_BIT_BLOB		typedef ptr CRYPT_BIT_BLOB

;;+-------------------------------------------------------------------------
;;  Type used for any algorithm
;;
;;  Where the Parameters CRYPT_OBJID_BLOB is in its encoded representation. For most
;;  algorithm types, the Parameters CRYPT_OBJID_BLOB is NULL (Parameters.cbData = 0).
;;--------------------------------------------------------------------------
CRYPT_ALGORITHM_IDENTIFIER  STRUC
pszObjId		LPSTR ?
Parameters		CRYPT_OBJID_BLOB <>
CRYPT_ALGORITHM_IDENTIFIER ENDS
PCRYPT_ALGORITHM_IDENTIFIER typedef ptr CRYPT_ALGORITHM_IDENTIFIER

;; Following are the definitions of various algorithm object identifiers
;; RSA
szOID_RSA		equ <"1.2.840.113549">
szOID_PKCS		equ <"1.2.840.113549.1">
szOID_RSA_HASH		equ <"1.2.840.113549.2">
szOID_RSA_ENCRYPT	equ <"1.2.840.113549.3">

szOID_PKCS_1		equ <"1.2.840.113549.1.1">
szOID_PKCS_2		equ <"1.2.840.113549.1.2">
szOID_PKCS_3		equ <"1.2.840.113549.1.3">
szOID_PKCS_4		equ <"1.2.840.113549.1.4">
szOID_PKCS_5		equ <"1.2.840.113549.1.5">
szOID_PKCS_6		equ <"1.2.840.113549.1.6">
szOID_PKCS_7		equ <"1.2.840.113549.1.7">
szOID_PKCS_8		equ <"1.2.840.113549.1.8">
szOID_PKCS_9		equ <"1.2.840.113549.1.9">
szOID_PKCS_10		equ <"1.2.840.113549.1.10">

szOID_RSA_RSA		equ <"1.2.840.113549.1.1.1">
szOID_RSA_MD2RSA	equ <"1.2.840.113549.1.1.2">
szOID_RSA_MD4RSA	equ <"1.2.840.113549.1.1.3">
szOID_RSA_MD5RSA	equ <"1.2.840.113549.1.1.4">
szOID_RSA_SHA1RSA	equ <"1.2.840.113549.1.1.5">
szOID_RSA_SETOAEP_RSA	equ <"1.2.840.113549.1.1.6">

szOID_RSA_data		equ <"1.2.840.113549.1.7.1">
szOID_RSA_signedData	equ <"1.2.840.113549.1.7.2">
szOID_RSA_envelopedData equ <"1.2.840.113549.1.7.3">
szOID_RSA_signEnvData	equ <"1.2.840.113549.1.7.4">
szOID_RSA_digestedData	equ <"1.2.840.113549.1.7.5">
szOID_RSA_hashedData	equ <"1.2.840.113549.1.7.5">
szOID_RSA_encryptedData equ <"1.2.840.113549.1.7.6">

szOID_RSA_emailAddr	equ <"1.2.840.113549.1.9.1">
szOID_RSA_unstructName	equ <"1.2.840.113549.1.9.2">
szOID_RSA_contentType	equ <"1.2.840.113549.1.9.3">
szOID_RSA_messageDigest equ <"1.2.840.113549.1.9.4">
szOID_RSA_signingTime	equ <"1.2.840.113549.1.9.5">
szOID_RSA_counterSign	equ <"1.2.840.113549.1.9.6">
szOID_RSA_challengePwd	equ <"1.2.840.113549.1.9.7">
szOID_RSA_unstructAddr	equ <"1.2.840.113549.1.9.8">
szOID_RSA_extCertAttrs	equ <"1.2.840.113549.1.9.9">
szOID_RSA_SMIMECapabilities equ <"1.2.840.113549.1.9.15">
szOID_RSA_preferSignedData equ <"1.2.840.113549.1.9.15.1">

szOID_RSA_MD2		equ <"1.2.840.113549.2.2">
szOID_RSA_MD4		equ <"1.2.840.113549.2.4">
szOID_RSA_MD5		equ <"1.2.840.113549.2.5">

szOID_RSA_RC2CBC	equ <"1.2.840.113549.3.2">
szOID_RSA_RC4		equ <"1.2.840.113549.3.4">
szOID_RSA_DES_EDE3_CBC	equ <"1.2.840.113549.3.7">
szOID_RSA_RC5_CBCPad	equ <"1.2.840.113549.3.9">

;; ITU-T UsefulDefinitions
szOID_DS		equ <"2.5">
szOID_DSALG		equ <"2.5.8">
szOID_DSALG_CRPT	equ <"2.5.8.1">
szOID_DSALG_HASH	equ <"2.5.8.2">
szOID_DSALG_SIGN	equ <"2.5.8.3">
szOID_DSALG_RSA		equ <"2.5.8.1.1">
;; NIST OSE Implementors' Workshop (OIW)
;; http://nemo.ncsl.nist.gov/oiw/agreements/stable/OSI/12s_9506.w51
;; http://nemo.ncsl.nist.gov/oiw/agreements/working/OSI/12w_9503.w51
szOID_OIW		equ <"1.3.14">
;; NIST OSE Implementors' Workshop (OIW) Security SIG algorithm identifiers
szOID_OIWSEC		equ <"1.3.14.3.2">
szOID_OIWSEC_md4RSA	equ <"1.3.14.3.2.2">
szOID_OIWSEC_md5RSA	equ <"1.3.14.3.2.3">
szOID_OIWSEC_md4RSA2	equ <"1.3.14.3.2.4">
szOID_OIWSEC_desECB	equ <"1.3.14.3.2.6">
szOID_OIWSEC_desCBC	equ <"1.3.14.3.2.7">
szOID_OIWSEC_desOFB	equ <"1.3.14.3.2.8">
szOID_OIWSEC_desCFB	equ <"1.3.14.3.2.9">
szOID_OIWSEC_desMAC	equ <"1.3.14.3.2.10">
szOID_OIWSEC_rsaSign	equ <"1.3.14.3.2.11">
szOID_OIWSEC_dsa	equ <"1.3.14.3.2.12">
szOID_OIWSEC_shaDSA	equ <"1.3.14.3.2.13">
szOID_OIWSEC_mdc2RSA	equ <"1.3.14.3.2.14">
szOID_OIWSEC_shaRSA	equ <"1.3.14.3.2.15">
szOID_OIWSEC_dhCommMod	equ <"1.3.14.3.2.16">
szOID_OIWSEC_desEDE	equ <"1.3.14.3.2.17">
szOID_OIWSEC_sha	equ <"1.3.14.3.2.18">
szOID_OIWSEC_mdc2	equ <"1.3.14.3.2.19">
szOID_OIWSEC_dsaComm	equ <"1.3.14.3.2.20">
szOID_OIWSEC_dsaCommSHA equ <"1.3.14.3.2.21">
szOID_OIWSEC_rsaXchg	equ <"1.3.14.3.2.22">
szOID_OIWSEC_keyHashSeal equ <"1.3.14.3.2.23">
szOID_OIWSEC_md2RSASign equ <"1.3.14.3.2.24">
szOID_OIWSEC_md5RSASign equ <"1.3.14.3.2.25">
szOID_OIWSEC_sha1	equ <"1.3.14.3.2.26">
szOID_OIWSEC_dsaSHA1	equ <"1.3.14.3.2.27">
szOID_OIWSEC_dsaCommSHA1 equ <"1.3.14.3.2.28">
szOID_OIWSEC_sha1RSASign equ <"1.3.14.3.2.29">
;; NIST OSE Implementors' Workshop (OIW) Directory SIG algorithm identifiers
szOID_OIWDIR		equ <"1.3.14.7.2">
szOID_OIWDIR_CRPT	equ <"1.3.14.7.2.1">
szOID_OIWDIR_HASH	equ <"1.3.14.7.2.2">
szOID_OIWDIR_SIGN	equ <"1.3.14.7.2.3">
szOID_OIWDIR_md2	equ <"1.3.14.7.2.2.1">
szOID_OIWDIR_md2RSA	equ <"1.3.14.7.2.3.1">


;; INFOSEC Algorithms
;; joint-iso-ccitt(2) country(16) us(840) organization(1) us-government(101) dod(2) id-infosec(1)
szOID_INFOSEC				equ <"2.16.840.1.101.2.1">
szOID_INFOSEC_sdnsSignature		equ <"2.16.840.1.101.2.1.1.1">
szOID_INFOSEC_mosaicSignature		equ <"2.16.840.1.101.2.1.1.2">
szOID_INFOSEC_sdnsConfidentiality	equ <"2.16.840.1.101.2.1.1.3">
szOID_INFOSEC_mosaicConfidentiality	equ <"2.16.840.1.101.2.1.1.4">
szOID_INFOSEC_sdnsIntegrity		equ <"2.16.840.1.101.2.1.1.5">
szOID_INFOSEC_mosaicIntegrity		equ <"2.16.840.1.101.2.1.1.6">
szOID_INFOSEC_sdnsTokenProtection	equ <"2.16.840.1.101.2.1.1.7">
szOID_INFOSEC_mosaicTokenProtection	equ <"2.16.840.1.101.2.1.1.8">
szOID_INFOSEC_sdnsKeyManagement		equ <"2.16.840.1.101.2.1.1.9">
szOID_INFOSEC_mosaicKeyManagement	equ <"2.16.840.1.101.2.1.1.10">
szOID_INFOSEC_sdnsKMandSig		equ <"2.16.840.1.101.2.1.1.11">
szOID_INFOSEC_mosaicKMandSig		equ <"2.16.840.1.101.2.1.1.12">
szOID_INFOSEC_SuiteASignature		equ <"2.16.840.1.101.2.1.1.13">
szOID_INFOSEC_SuiteAConfidentiality	equ <"2.16.840.1.101.2.1.1.14">
szOID_INFOSEC_SuiteAIntegrity		equ <"2.16.840.1.101.2.1.1.15">
szOID_INFOSEC_SuiteATokenProtection	equ <"2.16.840.1.101.2.1.1.16">
szOID_INFOSEC_SuiteAKeyManagement	equ <"2.16.840.1.101.2.1.1.17">
szOID_INFOSEC_SuiteAKMandSig		equ <"2.16.840.1.101.2.1.1.18">
szOID_INFOSEC_mosaicUpdatedSig		equ <"2.16.840.1.101.2.1.1.19">
szOID_INFOSEC_mosaicKMandUpdSig		equ <"2.16.840.1.101.2.1.1.20">
szOID_INFOSEC_mosaicUpdatedInteg	equ <"2.16.840.1.101.2.1.1.21">

CRYPT_OBJID_TABLE	STRUC
dwAlgId			dd ?
pszObjId		LPCSTR ?
CRYPT_OBJID_TABLE	ENDS
PCRYPT_OBJID_TABLE	typedef ptr CRYPT_OBJID_TABLE


;;+-------------------------------------------------------------------------
;;  PKCS #1 HashInfo (DigestInfo)
;;--------------------------------------------------------------------------
CRYPT_HASH_INFO		STRUC
HashAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
Hash			CRYPT_HASH_BLOB <>
CRYPT_HASH_INFO		ENDS
PCRYPT_HASH_INFO	typedef ptr CRYPT_HASH_INFO

;;+-------------------------------------------------------------------------
;;  Type used for an extension to an encoded content
;;
;;  Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
;;--------------------------------------------------------------------------
CERT_EXTENSION		STRUC
pszObjId		LPSTR ?
fCritical		BOOL ?
Value			CRYPT_OBJID_BLOB <>
CERT_EXTENSION		ENDS
PCERT_EXTENSION		typedef ptr CERT_EXTENSION

;;+-------------------------------------------------------------------------
;;  AttributeTypeValue
;;
;;  Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
;;--------------------------------------------------------------------------
CRYPT_ATTRIBUTE_TYPE_VALUE  STRUC
pszObjId		LPSTR ?
Value			CRYPT_OBJID_BLOB <>
CRYPT_ATTRIBUTE_TYPE_VALUE ENDS
PCRYPT_ATTRIBUTE_TYPE_VALUE typedef ptr CRYPT_ATTRIBUTE_TYPE_VALUE

;;+-------------------------------------------------------------------------
;;  Attributes
;;
;;  Where the Value's PATTR_BLOBs are in their encoded representation.
;;--------------------------------------------------------------------------
CRYPT_ATTRIBUTE		STRUC
pszObjId		LPSTR ?
cValue			dd ?
rgValue			PCRYPT_ATTR_BLOB ?
CRYPT_ATTRIBUTE		ENDS
PCRYPT_ATTRIBUTE	typedef ptr CRYPT_ATTRIBUTE

CRYPT_ATTRIBUTES	STRUC
cAttr			dd ?
rgAttr			PCRYPT_ATTRIBUTE ?
CRYPT_ATTRIBUTES	ENDS
PCRYPT_ATTRIBUTES	typedef ptr CRYPT_ATTRIBUTES

;;+-------------------------------------------------------------------------
;;  Attributes making up a Relative Distinguished Name (CERT_RDN)
;;
;;  The interpretation of the Value depends on the dwValueType.
;;  See below for a list of the types.
;;--------------------------------------------------------------------------
CERT_RDN_ATTR		STRUC
pszObjId		LPSTR ?
dwValueType		dd ?
Value			CERT_RDN_VALUE_BLOB <>
CERT_RDN_ATTR		ENDS
PCERT_RDN_ATTR		typedef ptr CERT_RDN_ATTR

;;+-------------------------------------------------------------------------
;;  CERT_RDN attribute Object Identifiers
;;--------------------------------------------------------------------------
;; Labeling attribute types:
szOID_COMMON_NAME	equ <"2.5.4.3"> ;; case-ignore string
szOID_SUR_NAME		equ <"2.5.4.4"> ;; case-ignore string
szOID_DEVICE_SERIAL_NUMBER equ <"2.5.4.5">  ;; printable string

;; Geographic attribute types:
szOID_COUNTRY_NAME	equ <"2.5.4.6"> ;; printable 2char string
szOID_LOCALITY_NAME	equ <"2.5.4.7"> ;; case-ignore string
szOID_STATE_OR_PROVINCE_NAME equ <"2.5.4.8">  ;; case-ignore string
szOID_STREET_ADDRESS	equ <"2.5.4.9"> ;; case-ignore string

;; Organizational attribute types:
szOID_ORGANIZATION_NAME equ <"2.5.4.10"> ;; case-ignore string
szOID_ORGANIZATIONAL_UNIT_NAME equ <"2.5.4.11"> ;; case-ignore string
szOID_TITLE		equ <"2.5.4.12"> ;; case-ignore string

;; Explanatory attribute types:
szOID_DESCRIPTION	equ <"2.5.4.13"> ;; case-ignore string
szOID_SEARCH_GUIDE	equ <"2.5.4.14">
szOID_BUSINESS_CATEGORY equ <"2.5.4.15"> ;; case-ignore string

;; Postal addressing attribute types:
szOID_POSTAL_ADDRESS	equ <"2.5.4.16">
szOID_POSTAL_CODE	equ <"2.5.4.17"> ;; case-ignore string
szOID_POST_OFFICE_BOX	equ <"2.5.4.18"> ;; case-ignore string
szOID_PHYSICAL_DELIVERY_OFFICE_NAME equ <"2.5.4.19"> ;; case-ignore string

;; Telecommunications addressing attribute types:
szOID_TELEPHONE_NUMBER	equ <"2.5.4.20"> ;; telephone number
szOID_TELEX_NUMBER	equ <"2.5.4.21">
szOID_TELETEXT_TERMINAL_IDENTIFIER equ <"2.5.4.22">
szOID_FACSIMILE_TELEPHONE_NUMBER equ <"2.5.4.23">
szOID_X21_ADDRESS	equ <"2.5.4.24"> ;; numeric string
szOID_INTERNATIONAL_ISDN_NUMBER equ <"2.5.4.25"> ;; numeric string
szOID_REGISTERED_ADDRESS equ <"2.5.4.26">
szOID_DESTINATION_INDICATOR equ <"2.5.4.27"> ;; printable string

;; Preference attribute types:
szOID_PREFERRED_DELIVERY_METHOD equ <"2.5.4.28">

;; OSI application attribute types:
szOID_PRESENTATION_ADDRESS equ <"2.5.4.29">
szOID_SUPPORTED_APPLICATION_CONTEXT equ <"2.5.4.30">

;; Relational application attribute types:
szOID_MEMBER		equ <"2.5.4.31">
szOID_OWNER		equ <"2.5.4.32">
szOID_ROLE_OCCUPANT	equ <"2.5.4.33">
szOID_SEE_ALSO		equ <"2.5.4.34">

;; Security attribute types:
szOID_USER_PASSWORD	equ <"2.5.4.35">
szOID_USER_CERTIFICATE	equ <"2.5.4.36">
szOID_CA_CERTIFICATE	equ <"2.5.4.37">
szOID_AUTHORITY_REVOCATION_LIST equ <"2.5.4.38">
szOID_CERTIFICATE_REVOCATION_LIST equ <"2.5.4.39">
szOID_CROSS_CERTIFICATE_PAIR equ <"2.5.4.40">

;; Undocumented attribute types???
;;#define szOID_???			    "2.5.4.41"
szOID_GIVEN_NAME	equ <"2.5.4.42"> ;; case-ignore string
szOID_INITIALS		equ <"2.5.4.43"> ;; case-ignore string

;; Pilot user attribute types:
szOID_DOMAIN_COMPONENT	equ <"0.9.2342.19200300.100.1.25"> ;; IA5 string

;;+-------------------------------------------------------------------------
;;  CERT_RDN Attribute Value Types
;;
;;  For RDN_ENCODED_BLOB, the Value's CERT_RDN_VALUE_BLOB is in its encoded
;;  representation. Otherwise, its an array of bytes.
;;
;;  For all CERT_RDN types, Value.cbData is always the number of bytes, not
;;  necessarily the number of elements in the string. For instance,
;;  RDN_UNIVERSAL_STRING is an array of ints (cbData == intCnt * 4) and
;;  RDN_BMP_STRING is an array of unsigned shorts (cbData == ushortCnt * 2).
;;
;;  For CertDecodeName, two 0 bytes are always appended to the end of the
;;  string (ensures a CHAR or WCHAR string is null terminated).
;;  These added 0 bytes are't included in the BLOB.cbData.
;;--------------------------------------------------------------------------
CERT_RDN_ANY_TYPE	equ 0
CERT_RDN_ENCODED_BLOB	equ 1
CERT_RDN_OCTET_STRING	equ 2
CERT_RDN_NUMERIC_STRING equ 3
CERT_RDN_PRINTABLE_STRING equ 4
CERT_RDN_TELETEX_STRING equ 5
CERT_RDN_T61_STRING	equ 5
CERT_RDN_VIDEOTEX_STRING equ 6
CERT_RDN_IA5_STRING	equ 7
CERT_RDN_GRAPHIC_STRING equ 8
CERT_RDN_VISIBLE_STRING equ 9
CERT_RDN_ISO646_STRING	equ 9
CERT_RDN_GENERAL_STRING equ 10
CERT_RDN_UNIVERSAL_STRING equ 11
CERT_RDN_INT4_STRING	equ 11
CERT_RDN_BMP_STRING	equ 12
CERT_RDN_UNICODE_STRING equ 12


;; Macro to check that the dwValueType is a character string and not an
;; encoded blob or octet string
IS_CERT_RDN_CHAR_STRING macro X
	exitm<(X GE CERT_RDN_NUMERIC_STRING)>
	endm

;;+-------------------------------------------------------------------------
;;  A CERT_RDN consists of an array of the above attributes
;;--------------------------------------------------------------------------
CERT_RDN		STRUC
cRDNAttr		dd ?
rgRDNAttr		PCERT_RDN_ATTR ?
CERT_RDN		ENDS
PCERT_RDN		typedef ptr CERT_RDN

;;+-------------------------------------------------------------------------
;;  Information stored in a subject's or issuer's name. The information
;;  is represented as an array of the above RDNs.
;;--------------------------------------------------------------------------
CERT_NAME_INFO		STRUC
cRDN			dd ?
rgRDN			PCERT_RDN ?
CERT_NAME_INFO		ENDS
PCERT_NAME_INFO		typedef ptr CERT_NAME_INFO

;;+-------------------------------------------------------------------------
;;  Name attribute value without the Object Identifier
;;
;;  The interpretation of the Value depends on the dwValueType.
;;  See above for a list of the types.
;;--------------------------------------------------------------------------
CERT_NAME_VALUE		STRUC
dwValueType		dd ?
Value			CERT_RDN_VALUE_BLOB <>
CERT_NAME_VALUE		ENDS
PCERT_NAME_VALUE	typedef ptr CERT_NAME_VALUE

;;+-------------------------------------------------------------------------
;;  Public Key Info
;;
;;  The PublicKey is the encoded representation of the information as it is
;;  stored in the bit string
;;--------------------------------------------------------------------------
CERT_PUBLIC_KEY_INFO	STRUC
Algorithm		CRYPT_ALGORITHM_IDENTIFIER <>
PublicKey		CRYPT_BIT_BLOB <>
CERT_PUBLIC_KEY_INFO	ENDS
PCERT_PUBLIC_KEY_INFO	typedef ptr CERT_PUBLIC_KEY_INFO

CERT_RSA_PUBLIC_KEY_OBJID equ szOID_RSA_RSA
CERT_DEFAULT_OID_PUBLIC_KEY_SIGN equ szOID_RSA_RSA
CERT_DEFAULT_OID_PUBLIC_KEY_XCHG equ szOID_RSA_RSA

;;+-------------------------------------------------------------------------
;;  Information stored in a certificate
;;
;;  The Issuer, Subject, Algorithm, PublicKey and Extension BLOBs are the
;;  encoded representation of the information.
;;--------------------------------------------------------------------------
CERT_INFO		STRUC
dwVersion		dd ?
SerialNumber		CRYPT_INTEGER_BLOB <>
SignatureAlgorithm	CRYPT_ALGORITHM_IDENTIFIER <>
Issuer			CERT_NAME_BLOB <>
NotBefore		FILETIME <>
NotAfter		FILETIME <>
Subject			CERT_NAME_BLOB <>
SubjectPublicKeyInfo	CERT_PUBLIC_KEY_INFO <>
IssuerUniqueId		CRYPT_BIT_BLOB <>
SubjectUniqueId		CRYPT_BIT_BLOB <>
cExtension		dd ?
rgExtension		PCERT_EXTENSION ?
CERT_INFO		ENDS
PCERT_INFO		typedef ptr CERT_INFO

;;+-------------------------------------------------------------------------
;;  Certificate versions
;;--------------------------------------------------------------------------
CERT_V1			equ 0
CERT_V2			equ 1
CERT_V3			equ 2

;;+-------------------------------------------------------------------------
;;  Certificate Information Flags
;;--------------------------------------------------------------------------
CERT_INFO_VERSION_FLAG	equ 1
CERT_INFO_SERIAL_NUMBER_FLAG equ 2
CERT_INFO_SIGNATURE_ALGORITHM_FLAG equ 3
CERT_INFO_ISSUER_FLAG	equ 4
CERT_INFO_NOT_BEFORE_FLAG equ 5
CERT_INFO_NOT_AFTER_FLAG equ 6
CERT_INFO_SUBJECT_FLAG	equ 7
CERT_INFO_SUBJECT_PUBLIC_KEY_INFO_FLAG equ 8
CERT_INFO_ISSUER_UNIQUE_ID_FLAG equ 9
CERT_INFO_SUBJECT_UNIQUE_ID_FLAG equ 10
CERT_INFO_EXTENSION_FLAG equ 11

;;+-------------------------------------------------------------------------
;;  An entry in a CRL
;;
;;  The Extension BLOBs are the encoded representation of the information.
;;--------------------------------------------------------------------------
CRL_ENTRY		STRUC
SerialNumber		CRYPT_INTEGER_BLOB <>
RevocationDate		FILETIME <>
cExtension		dd ?
rgExtension		PCERT_EXTENSION ?
CRL_ENTRY		ENDS
PCRL_ENTRY		typedef ptr CRL_ENTRY

;;+-------------------------------------------------------------------------
;;  Information stored in a CRL
;;
;;  The Issuer, Algorithm and Extension BLOBs are the encoded
;;  representation of the information.
;;--------------------------------------------------------------------------
CRL_INFO		STRUC
dwVersion		dd ?
SignatureAlgorithm	CRYPT_ALGORITHM_IDENTIFIER <>
Issuer			CERT_NAME_BLOB <>
ThisUpdate		FILETIME <>
NextUpdate		FILETIME <>
cCRLEntry		dd ?
rgCRLEntry		PCRL_ENTRY ?
cExtension		dd ?
rgExtension		PCERT_EXTENSION ?
CRL_INFO		ENDS
PCRL_INFO		typedef ptr CRL_INFO

;;+-------------------------------------------------------------------------
;;  CRL versions
;;--------------------------------------------------------------------------
CRL_V1			equ 0
CRL_V2			equ 1


;;+-------------------------------------------------------------------------
;;  Information stored in a certificate request
;;
;;  The Subject, Algorithm, PublicKey and Attribute BLOBs are the encoded
;;  representation of the information.
;;--------------------------------------------------------------------------
CERT_REQUEST_INFO	STRUC
dwVersion		dd ?
Subject			CERT_NAME_BLOB <>
SubjectPublicKeyInfo	CERT_PUBLIC_KEY_INFO <>
cAttribute		dd ?
rgAttribute		PCRYPT_ATTRIBUTE ?
CERT_REQUEST_INFO	ENDS
PCERT_REQUEST_INFO	typedef ptr CERT_REQUEST_INFO

;;+-------------------------------------------------------------------------
;;  Certificate Request versions
;;--------------------------------------------------------------------------
CERT_REQUEST_V1		equ 0

;;+-------------------------------------------------------------------------
;;  Information stored in Netscape's Keygen request
;;--------------------------------------------------------------------------
CERT_KEYGEN_REQUEST_INFO  STRUC
dwVersion		dd ?
SubjectPublicKeyInfo	CERT_PUBLIC_KEY_INFO <>
pwszChallengeString	LPWSTR ?	;; encoded as IA5
CERT_KEYGEN_REQUEST_INFO ENDS
PCERT_KEYGEN_REQUEST_INFO typedef ptr CERT_KEYGEN_REQUEST_INFO

CERT_KEYGEN_REQUEST_V1	equ 0


;;+-------------------------------------------------------------------------
;;  Certificate, CRL, Certificate Request or Keygen Request Signed Content
;;
;;  The "to be signed" encoded content plus its signature. The ToBeSigned
;;  is the encoded CERT_INFO, CRL_INFO, CERT_REQUEST_INFO or
;;  CERT_KEYGEN_REQUEST_INFO.
;;--------------------------------------------------------------------------
CERT_SIGNED_CONTENT_INFO  STRUC
ToBeSigned		CRYPT_DER_BLOB <>
SignatureAlgorithm	CRYPT_ALGORITHM_IDENTIFIER <>
Signature		CRYPT_BIT_BLOB <>
CERT_SIGNED_CONTENT_INFO ENDS
PCERT_SIGNED_CONTENT_INFO typedef ptr CERT_SIGNED_CONTENT_INFO


;;+-------------------------------------------------------------------------
;;  Certificate Trust List (CTL)
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CTL Usage. Also used for EnhancedKeyUsage extension.
;;--------------------------------------------------------------------------
CTL_USAGE		STRUC
cUsageIdentifier	dd ?
rgpszUsageIdentifier	LPSTR ? ;; array of pszObjId
CTL_USAGE		ENDS
PCTL_USAGE		typedef ptr CTL_USAGE
PCERT_ENHKEY_USAGE	typedef ptr CERT_ENHKEY_USAGE


;;+-------------------------------------------------------------------------
;;  An entry in a CTL
;;--------------------------------------------------------------------------
CTL_ENTRY		STRUC
SubjectIdentifier	CRYPT_DATA_BLOB <>	;; For example, its hash
cAttribute		dd ?
rgAttribute		PCRYPT_ATTRIBUTE ?	;; OPTIONAL
CTL_ENTRY		ENDS
PCTL_ENTRY		typedef ptr CTL_ENTRY

;;+-------------------------------------------------------------------------
;;  Information stored in a CTL
;;--------------------------------------------------------------------------
CTL_INFO		STRUC
dwVersion		dd ?
SubjectUsage		CTL_USAGE <>
ListIdentifier		CRYPT_DATA_BLOB <>	;; OPTIONAL
SequenceNumber		CRYPT_INTEGER_BLOB <>	;; OPTIONAL
ThisUpdate		FILETIME <>
NextUpdate		FILETIME <> ;; OPTIONAL
SubjectAlgorithm	CRYPT_ALGORITHM_IDENTIFIER <>
cCTLEntry		dd ?
rgCTLEntry		PCTL_ENTRY ?	;; OPTIONAL
cExtension		dd ?
rgExtension		PCERT_EXTENSION ?	;; OPTIONAL
CTL_INFO		ENDS
PCTL_INFO		typedef ptr CTL_INFO

;;+-------------------------------------------------------------------------
;;  CTL versions
;;--------------------------------------------------------------------------
CTL_V1			equ 0


;;+-------------------------------------------------------------------------
;;  TimeStamp Request
;;
;;  The pszTimeStamp is the OID for the Time type requested
;;  The pszContentType is the Content Type OID for the content, usually DATA
;;  The Content is a un-decoded blob
;;--------------------------------------------------------------------------
CRYPT_TIME_STAMP_REQUEST_INFO  STRUC
pszTimeStampAlgorithm	LPSTR ? ;; pszObjId
pszContentType		LPSTR ? ;; pszObjId
Content			CRYPT_OBJID_BLOB <>
cAttribute		dd ?
rgAttribute		PCRYPT_ATTRIBUTE ?
CRYPT_TIME_STAMP_REQUEST_INFO ENDS
PCRYPT_TIME_STAMP_REQUEST_INFO typedef ptr CRYPT_TIME_STAMP_REQUEST_INFO

;;+-------------------------------------------------------------------------
;;  Certificate and Message encoding types
;;
;;  The encoding type is a DWORD containing both the certificate and message
;;  encoding types. The certificate encoding type is stored in the LOWORD.
;;  The message encoding type is stored in the HIWORD. Some functions or
;;  structure fields require only one of the encoding types. The following
;;  naming convention is used to indicate which encoding type(s) are
;;  required:
;;	dwEncodingType		    (both encoding types are required)
;;	dwMsgAndCertEncodingType    (both encoding types are required)
;;	dwMsgEncodingType	    (only msg encoding type is required)
;;	dwCertEncodingType	    (only cert encoding type is required)
;;
;;  Its always acceptable to specify both.
;;--------------------------------------------------------------------------
CERT_ENCODING_TYPE_MASK equ 0x0000FFFF
CMSG_ENCODING_TYPE_MASK equ 0xFFFF0000
GET_CERT_ENCODING_TYPE macro X
	exitm<(X AND CERT_ENCODING_TYPE_MASK)>
	endm
GET_CMSG_ENCODING_TYPE macro X
	exitm<(X AND CMSG_ENCODING_TYPE_MASK)>
	endm

CRYPT_ASN_ENCODING	equ 0x00000001
CRYPT_NDR_ENCODING	equ 0x00000002
X509_ASN_ENCODING	equ 0x00000001
X509_NDR_ENCODING	equ 0x00000002
PKCS_7_ASN_ENCODING	equ 0x00010000
PKCS_7_NDR_ENCODING	equ 0x00020000


;;+-------------------------------------------------------------------------
;;  format the specified data structure according to the certificate
;;  encoding type.
;;
;;--------------------------------------------------------------------------
;BOOL
CryptFormatObject proto _CType \
    dwCertEncodingType: DWORD,
	  dwFormatType: DWORD,
       dwFormatStrType: DWORD,
	 pFormatStruct: PVOID,
	lpszStructType: LPCSTR,
	     pbEncoded: LPBYTE,
	     cbEncoded: DWORD,
	      pbFormat: PVOID,
	     pcbFormat: LPDWORD

;;+-------------------------------------------------------------------------
;;  Encode / decode the specified data structure according to the certificate
;;  encoding type.
;;
;;  See below for a list of the predefined data structures.
;;--------------------------------------------------------------------------


;BOOL
CryptEncodeObject proto _CType \
    dwCertEncodingType: DWORD,
	lpszStructType: LPCSTR,
	  pvStructInfo: PVOID,
	     pbEncoded: LPBYTE,
	    pcbEncoded: LPDWORD

;BOOL
CryptDecodeObject proto _CType \
    dwCertEncodingType: DWORD,
	lpszStructType: LPCSTR,
	     pbEncoded: LPBYTE,
	     cbEncoded: DWORD,
	       dwFlags: DWORD,
	  pvStructInfo: PVOID,
	 pcbStructInfo: LPDWORD

;; When the following flag is set the nocopy optimization is enabled.
;; This optimization where appropriate, updates the pvStructInfo fields
;; to point to content residing within pbEncoded instead of making a copy
;; of and appending to pvStructInfo.
;;
;; Note, when set, pbEncoded can't be freed until pvStructInfo is freed.
CRYPT_DECODE_NOCOPY_FLAG equ 0x1

;;+-------------------------------------------------------------------------
;;  Predefined X509 certificate data structures that can be encoded / decoded.
;;--------------------------------------------------------------------------
CRYPT_ENCODE_DECODE_NONE equ 0
X509_CERT		equ (1)
X509_CERT_TO_BE_SIGNED	equ (2)
X509_CERT_CRL_TO_BE_SIGNED equ (3)
X509_CERT_REQUEST_TO_BE_SIGNED equ (4)
X509_EXTENSIONS		equ (5)
X509_NAME_VALUE		equ (6)
X509_NAME		equ (7)
X509_PUBLIC_KEY_INFO	equ (8)

;;+-------------------------------------------------------------------------
;;  Predefined X509 certificate extension data structures that can be
;;  encoded / decoded.
;;--------------------------------------------------------------------------
X509_AUTHORITY_KEY_ID	equ (9)
X509_KEY_ATTRIBUTES	equ (10)
X509_KEY_USAGE_RESTRICTION equ (11)
X509_ALTERNATE_NAME	equ (12)
X509_BASIC_CONSTRAINTS	equ (13)
X509_KEY_USAGE		equ (14)
X509_BASIC_CONSTRAINTS2 equ (15)
X509_CERT_POLICIES	equ (16)

;;+-------------------------------------------------------------------------
;;  Additional predefined data structures that can be encoded / decoded.
;;--------------------------------------------------------------------------
PKCS_UTC_TIME		equ (17)
PKCS_TIME_REQUEST	equ (18)
RSA_CSP_PUBLICKEYBLOB	equ (19)
X509_UNICODE_NAME	equ (20)

X509_KEYGEN_REQUEST_TO_BE_SIGNED equ (21)
PKCS_ATTRIBUTE		equ (22)
PKCS_CONTENT_INFO_SEQUENCE_OF_ANY equ (23)

;;+-------------------------------------------------------------------------
;;  Predefined primitive data structures that can be encoded / decoded.
;;--------------------------------------------------------------------------
X509_UNICODE_NAME_VALUE equ (24)
X509_ANY_STRING		equ X509_NAME_VAUE
X509_UNICODE_ANY_STRING equ X509_UNICODE_NAME_VAUE
X509_OCTET_STRING	equ (25)
X509_BITS		equ (26)
X509_INTEGER		equ (27)
X509_MULTI_BYTE_INTEGER equ (28)
X509_ENUMERATED		equ (29)
X509_CHOICE_OF_TIME	equ (30)

;;+-------------------------------------------------------------------------
;;  More predefined X509 certificate extension data structures that can be
;;  encoded / decoded.
;;--------------------------------------------------------------------------
X509_AUTHORITY_KEY_ID2	equ (31)
;;#define X509_AUTHORITY_INFO_ACCESS	      (32)
X509_CRL_REASON_CODE	equ X509_ENUMERATED
PKCS_CONTENT_INFO	equ (33)
X509_SEQUENCE_OF_ANY	equ (34)
X509_CRL_DIST_POINTS	equ (35)
X509_ENHANCED_KEY_USAGE equ (36)
PKCS_CTL		equ (37)

X509_MULTI_BYTE_UINT	equ (38)
X509_DSS_PUBLICKEY	equ X509_MULTI_BYTE_UINT
X509_DSS_PARAMETERS	equ (39)
X509_DSS_SIGNATURE	equ (40)
PKCS_RC2_CBC_PARAMETERS equ (41)
PKCS_SMIME_CAPABILITIES equ (42)


;;+-------------------------------------------------------------------------
;;  Predefined PKCS #7 data structures that can be encoded / decoded.
;;--------------------------------------------------------------------------
PKCS7_SIGNER_INFO	equ (500)

;;+-------------------------------------------------------------------------
;;  Predefined Software Publishing Credential (SPC)  data structures that
;;  can be encoded / decoded.
;;
;;  Predefined values: 2000 .. 2999
;;
;;  See spc.h for value and data structure definitions.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  Extension Object Identifiers
;;--------------------------------------------------------------------------
szOID_AUTHORITY_KEY_IDENTIFIER equ <"2.5.29.1">
szOID_KEY_ATTRIBUTES	equ <"2.5.29.2">
szOID_KEY_USAGE_RESTRICTION equ <"2.5.29.4">
szOID_SUBJECT_ALT_NAME	equ <"2.5.29.7">
szOID_ISSUER_ALT_NAME	equ <"2.5.29.8">
szOID_BASIC_CONSTRAINTS equ <"2.5.29.10">
szOID_KEY_USAGE		equ <"2.5.29.15">
szOID_BASIC_CONSTRAINTS2 equ <"2.5.29.19">
szOID_CERT_POLICIES	equ <"2.5.29.32">

szOID_AUTHORITY_KEY_IDENTIFIER2 equ <"2.5.29.35">
szOID_SUBJECT_KEY_IDENTIFIER equ <"2.5.29.14">
szOID_SUBJECT_ALT_NAME2 equ <"2.5.29.17">
szOID_ISSUER_ALT_NAME2	equ <"2.5.29.18">
szOID_CRL_REASON_CODE	equ <"2.5.29.21">
szOID_CRL_DIST_POINTS	equ <"2.5.29.31">
szOID_ENHANCED_KEY_USAGE equ <"2.5.29.37">


;; Internet Public Key Infrastructure
szOID_PKIX		equ <"1.3.6.1.5.5.7">
szOID_AUTHORITY_INFO_ACCESS equ <"1.3.6.1.5.5.7.2">

;; Microsoft extensions or attributes
szOID_CERT_EXTENSIONS	equ <"1.3.6.1.4.1.311.2.1.14">
szOID_NEXT_UPDATE_LOCATION equ <"1.3.6.1.4.1.311.10.2">

;;  Microsoft PKCS #7 ContentType Object Identifiers
szOID_CTL		equ <"1.3.6.1.4.1.311.10.1">

;;+-------------------------------------------------------------------------
;;  Extension Object Identifiers (currently not implemented)
;;--------------------------------------------------------------------------
szOID_POLICY_MAPPINGS	equ <"2.5.29.5">
szOID_SUBJECT_DIR_ATTRS equ <"2.5.29.9">

;;+-------------------------------------------------------------------------
;;  Enhanced Key Usage (Purpose) Object Identifiers
;;--------------------------------------------------------------------------
szOID_PKIX_KP		equ <"1.3.6.1.5.5.7.3">

;; Consistent key usage bits: DIGITAL_SIGNATURE, KEY_ENCIPHERMENT
;; or KEY_AGREEMENT
szOID_PKIX_KP_SERVER_AUTH equ <"1.3.6.1.5.5.7.3.1">

;; Consistent key usage bits: DIGITAL_SIGNATURE
szOID_PKIX_KP_CLIENT_AUTH equ <"1.3.6.1.5.5.7.3.2">

;; Consistent key usage bits: DIGITAL_SIGNATURE
szOID_PKIX_KP_CODE_SIGNING equ <"1.3.6.1.5.5.7.3.3">

;; Consistent key usage bits: DIGITAL_SIGNATURE, NON_REPUDIATION and/or
;; (KEY_ENCIPHERMENT or KEY_AGREEMENT)
szOID_PKIX_KP_EMAIL_PROTECTION equ <"1.3.6.1.5.5.7.3.4">

;;+-------------------------------------------------------------------------
;;  Microsoft Enhanced Key Usage (Purpose) Object Identifiers
;;+-------------------------------------------------------------------------

;;  Signer of CTLs
szOID_KP_CTL_USAGE_SIGNING equ <"1.3.6.1.4.1.311.10.3.1">

;;  Signer of TimeStamps
szOID_KP_TIME_STAMP_SIGNING equ <"1.3.6.1.4.1.311.10.3.2">

;;+-------------------------------------------------------------------------
;;  Microsoft Attribute Object Identifiers
;;+-------------------------------------------------------------------------
szOID_YESNO_TRUST_ATTR	equ <"1.3.6.1.4.1.311.10.4.1">

;;+-------------------------------------------------------------------------
;;  X509_CERT
;;
;;  The "to be signed" encoded content plus its signature. The ToBeSigned
;;  content is the CryptEncodeObject() output for one of the following:
;;  X509_CERT_TO_BE_SIGNED, X509_CERT_CRL_TO_BE_SIGNED or
;;  X509_CERT_REQUEST_TO_BE_SIGNED.
;;
;;  pvStructInfo points to CERT_SIGNED_CONTENT_INFO.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_CERT_TO_BE_SIGNED
;;
;;  pvStructInfo points to CERT_INFO.
;;
;;  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
;;  signature (output of a X509_CERT CryptEncodeObject()).
;;
;;  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_CERT_CRL_TO_BE_SIGNED
;;
;;  pvStructInfo points to CRL_INFO.
;;
;;  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
;;  signature (output of a X509_CERT CryptEncodeObject()).
;;
;;  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_CERT_REQUEST_TO_BE_SIGNED
;;
;;  pvStructInfo points to CERT_REQUEST_INFO.
;;
;;  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
;;  signature (output of a X509_CERT CryptEncodeObject()).
;;
;;  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_EXTENSIONS
;;  szOID_CERT_EXTENSIONS
;;
;;  pvStructInfo points to following CERT_EXTENSIONS.
;;--------------------------------------------------------------------------
CERT_EXTENSIONS		STRUC
cExtension		dd ?
rgExtension		PCERT_EXTENSION ?
CERT_EXTENSIONS		ENDS
PCERT_EXTENSIONS	typedef ptr CERT_EXTENSIONS

;;+-------------------------------------------------------------------------
;;  X509_NAME_VALUE
;;  X509_ANY_STRING
;;
;;  pvStructInfo points to CERT_NAME_VALUE.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_UNICODE_NAME_VALUE
;;  X509_UNICODE_ANY_STRING
;;
;;  pvStructInfo points to CERT_NAME_VALUE.
;;
;;  The name values are unicode strings.
;;
;;  For CryptEncodeObject:
;;    Value.pbData points to the unicode string.
;;    If Value.cbData = 0, then, the unicode string is NULL terminated.
;;    Otherwise, Value.cbData is the unicode string byte count. The byte count
;;    is twice the character count.
;;
;;    If the unicode string contains an invalid character for the specified
;;    dwValueType, then, *pcbEncoded is updated with the unicode character
;;    index of the first invalid character. LastError is set to:
;;    CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
;;    CRYPT_E_INVALID_IA5_STRING.
;;
;;    The unicode string is converted before being encoded according to
;;    the specified dwValueType. If dwValueType is set to 0, LastError
;;    is set to E_INVALIDARG.
;;
;;    If the dwValueType isn't one of the character strings (its a
;;    CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING), then, CryptEncodeObject
;;    will return FALSE with LastError set to CRYPT_E_NOT_CHAR_STRING.
;;
;;  For CryptDecodeObject:
;;    Value.pbData points to a NULL terminated unicode string. Value.cbData
;;    contains the byte count of the unicode string excluding the NULL
;;    terminator. dwValueType contains the type used in the encoded object.
;;    Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
;;    converted to the unicode string according to the dwValueType.
;;
;;    If the encoded object isn't one of the character string types, then,
;;    CryptDecodeObject will return FALSE with LastError set to
;;    CRYPT_E_NOT_CHAR_STRING. For a non character string, decode using
;;    X509_NAME_VALUE or X509_ANY_STRING.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_NAME
;;
;;  pvStructInfo points to CERT_NAME_INFO.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_UNICODE_NAME
;;
;;  pvStructInfo points to CERT_NAME_INFO.
;;
;;  The RDN attribute values are unicode strings except for the dwValueTypes of
;;  CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING. These dwValueTypes are
;;  the same as for a X509_NAME. Their values aren't converted to/from unicode.
;;
;;  For CryptEncodeObject:
;;    Value.pbData points to the unicode string.
;;    If Value.cbData = 0, then, the unicode string is NULL terminated.
;;    Otherwise, Value.cbData is the unicode string byte count. The byte count
;;    is twice the character count.
;;
;;    If dwValueType = 0 (CERT_RDN_ANY_TYPE), the pszObjId is used to find
;;    an acceptable dwValueType. If the unicode string contains an
;;    invalid character for the found or specified dwValueType, then,
;;    *pcbEncoded is updated with the error location of the invalid character.
;;    See below for details. LastError is set to:
;;    CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
;;    CRYPT_E_INVALID_IA5_STRING.
;;
;;    The unicode string is converted before being encoded according to
;;    the specified or ObjId matching dwValueType.
;;
;;  For CryptDecodeObject:
;;    Value.pbData points to a NULL terminated unicode string. Value.cbData
;;    contains the byte count of the unicode string excluding the NULL
;;    terminator. dwValueType contains the type used in the encoded object.
;;    Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
;;    converted to the unicode string according to the dwValueType.
;;
;;    If the dwValueType of the encoded value isn't a character string
;;    type, then, it isn't converted to UNICODE. Use the
;;    IS_CERT_RDN_CHAR_STRING() macro on the dwValueType to check
;;    that Value.pbData points to a converted unicode string.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  Unicode Name Value Error Location Definitions
;;
;;  Error location is returned in *pcbEncoded by
;;  CryptEncodeObject(X509_UNICODE_NAME)
;;
;;  Error location consists of:
;;    RDN_INDEX	    - 10 bits << 22
;;    ATTR_INDEX    - 6 bits << 16
;;    VALUE_INDEX   - 16 bits (unicode character index)
;;--------------------------------------------------------------------------
CERT_UNICODE_RDN_ERR_INDEX_MASK equ 0x3FF
CERT_UNICODE_RDN_ERR_INDEX_SHIFT equ 22
CERT_UNICODE_ATTR_ERR_INDEX_MASK equ 0x003F
CERT_UNICODE_ATTR_ERR_INDEX_SHIFT equ 16
CERT_UNICODE_VALUE_ERR_INDEX_MASK equ 0x0000FFFF
CERT_UNICODE_VALUE_ERR_INDEX_SHIFT equ 0

GET_CERT_UNICODE_RDN_ERR_INDEX macro X
	exitm<((X SHR CERT_UNICODE_RDN_ERR_INDEX_SHIFT) AND CERT_UNICODE_RDN_ERR_INDEX_MASK)>
	endm
GET_CERT_UNICODE_ATTR_ERR_INDEX macro X
	exitm<((X SHR CERT_UNICODE_ATTR_ERR_INDEX_SHIFT) AND CERT_UNICODE_ATTR_ERR_INDEX_MASK)>
	endm
GET_CERT_UNICODE_VALUE_ERR_INDEX macro X
	exitm<(X AND CERT_UNICODE_VAUE_ERR_INDEX_MASK)>
	endm

;;+-------------------------------------------------------------------------
;;  X509_PUBLIC_KEY_INFO
;;
;;  pvStructInfo points to CERT_PUBLIC_KEY_INFO.
;;--------------------------------------------------------------------------


;;+-------------------------------------------------------------------------
;;  X509_AUTHORITY_KEY_ID
;;  szOID_AUTHORITY_KEY_IDENTIFIER
;;
;;  pvStructInfo points to following CERT_AUTHORITY_KEY_ID_INFO.
;;--------------------------------------------------------------------------
CERT_AUTHORITY_KEY_ID_INFO  STRUC
KeyId			CRYPT_DATA_BLOB <>
CertIssuer		CERT_NAME_BLOB <>
CertSerialNumber	CRYPT_INTEGER_BLOB <>
CERT_AUTHORITY_KEY_ID_INFO ENDS
PCERT_AUTHORITY_KEY_ID_INFO typedef ptr CERT_AUTHORITY_KEY_ID_INFO

;;+-------------------------------------------------------------------------
;;  X509_KEY_ATTRIBUTES
;;  szOID_KEY_ATTRIBUTES
;;
;;  pvStructInfo points to following CERT_KEY_ATTRIBUTES_INFO.
;;--------------------------------------------------------------------------
CERT_PRIVATE_KEY_VALIDITY  STRUC
NotBefore		FILETIME <>
NotAfter		FILETIME <>
CERT_PRIVATE_KEY_VALIDITY ENDS
PCERT_PRIVATE_KEY_VALIDITY typedef ptr CERT_PRIVATE_KEY_VALIDITY

CERT_KEY_ATTRIBUTES_INFO  STRUC
KeyId			CRYPT_DATA_BLOB <>
IntendedKeyUsage	CRYPT_BIT_BLOB <>
pPrivateKeyUsagePeriod	PCERT_PRIVATE_KEY_VALIDITY ?	;; OPTIONAL
CERT_KEY_ATTRIBUTES_INFO ENDS
PCERT_KEY_ATTRIBUTES_INFO typedef ptr CERT_KEY_ATTRIBUTES_INFO

CERT_DIGITAL_SIGNATURE_KEY_USAGE equ 0x80
CERT_NON_REPUDIATION_KEY_USAGE equ 0x40
CERT_KEY_ENCIPHERMENT_KEY_USAGE equ 0x20
CERT_DATA_ENCIPHERMENT_KEY_USAGE equ 0x10
CERT_KEY_AGREEMENT_KEY_USAGE equ 0x08
CERT_KEY_CERT_SIGN_KEY_USAGE equ 0x04
CERT_OFFLINE_CRL_SIGN_KEY_USAGE equ 0x02

CERT_CRL_SIGN_KEY_USAGE equ 0x02

;;+-------------------------------------------------------------------------
;;  X509_KEY_USAGE_RESTRICTION
;;  szOID_KEY_USAGE_RESTRICTION
;;
;;  pvStructInfo points to following CERT_KEY_USAGE_RESTRICTION_INFO.
;;--------------------------------------------------------------------------
CERT_POLICY_ID		STRUC
cCertPolicyElementId	dd ?
rgpszCertPolicyElementId LPSTR ?	;; pszObjId
CERT_POLICY_ID		ENDS
PCERT_POLICY_ID		typedef ptr CERT_POLICY_ID

CERT_KEY_USAGE_RESTRICTION_INFO	 STRUC
cCertPolicyId		dd ?
rgCertPolicyId		PCERT_POLICY_ID ?
RestrictedKeyUsage	CRYPT_BIT_BLOB <>
CERT_KEY_USAGE_RESTRICTION_INFO ENDS
PCERT_KEY_USAGE_RESTRICTION_INFO typedef ptr CERT_KEY_USAGE_RESTRICTION_INFO

;; See CERT_KEY_ATTRIBUTES_INFO for definition of the RestrictedKeyUsage bits

;;+-------------------------------------------------------------------------
;;  X509_ALTERNATE_NAME
;;  szOID_SUBJECT_ALT_NAME
;;  szOID_ISSUER_ALT_NAME
;;  szOID_SUBJECT_ALT_NAME2
;;  szOID_ISSUER_ALT_NAME2
;;
;;  pvStructInfo points to following CERT_ALT_NAME_INFO.
;;--------------------------------------------------------------------------

CERT_ALT_NAME_ENTRY	STRUC
dwAltNameChoice		dd ?
UNION
  pwszRfc822Name	LPWSTR ?	;; 2  (encoded IA5)
  pwszDNSName		LPWSTR ?	;; 3  (encoded IA5)
  DirectoryName		CERT_NAME_BLOB <> ;; 5
  pwszURL		LPWSTR ?	;; 7  (encoded IA5)
  IPAddress		CRYPT_DATA_BLOB <>	;; 8  (Octet String)
  pszRegisteredID	LPSTR ? ;; 9  (Object Identifer)
ENDS
CERT_ALT_NAME_ENTRY	ENDS
PCERT_ALT_NAME_ENTRY	typedef ptr CERT_ALT_NAME_ENTRY

CERT_ALT_NAME_OTHER_NAME equ 1
CERT_ALT_NAME_RFC822_NAME equ 2
CERT_ALT_NAME_DNS_NAME	equ 3
CERT_ALT_NAME_X400_ADDRESS equ 4
CERT_ALT_NAME_DIRECTORY_NAME equ 5
CERT_ALT_NAME_EDI_PARTY_NAME equ 6
CERT_ALT_NAME_URL	equ 7
CERT_ALT_NAME_IP_ADDRESS equ 8
CERT_ALT_NAME_REGISTERED_ID equ 9


CERT_ALT_NAME_INFO	STRUC
cAltEntry		dd ?
rgAltEntry		PCERT_ALT_NAME_ENTRY ?
CERT_ALT_NAME_INFO	ENDS
PCERT_ALT_NAME_INFO	typedef ptr CERT_ALT_NAME_INFO

;;+-------------------------------------------------------------------------
;;  Alternate name IA5 Error Location Definitions for
;;  CRYPT_E_INVALID_IA5_STRING.
;;
;;  Error location is returned in *pcbEncoded by
;;  CryptEncodeObject(X509_ALTERNATE_NAME)
;;
;;  Error location consists of:
;;    ENTRY_INDEX   - 8 bits << 16
;;    VALUE_INDEX   - 16 bits (unicode character index)
;;--------------------------------------------------------------------------
CERT_ALT_NAME_ENTRY_ERR_INDEX_MASK equ 0xFF
CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT equ 16
CERT_ALT_NAME_VALUE_ERR_INDEX_MASK equ 0x0000FFFF
CERT_ALT_NAME_VALUE_ERR_INDEX_SHIFT equ 0

GET_CERT_ALT_NAME_ENTRY_ERR_INDEX macro X
	exitm<((X SHR CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT) AND CERT_AT_NAME_ENTRY_ERR_INDEX_MASK)>
	endm
GET_CERT_ALT_NAME_VALUE_ERR_INDEX macro X
	exitm<(X AND CERT_ALT_NAME_VAUE_ERR_INDEX_MASK)>
	endm


;;+-------------------------------------------------------------------------
;;  X509_BASIC_CONSTRAINTS
;;  szOID_BASIC_CONSTRAINTS
;;
;;  pvStructInfo points to following CERT_BASIC_CONSTRAINTS_INFO.
;;--------------------------------------------------------------------------
CERT_BASIC_CONSTRAINTS_INFO  STRUC
SubjectType		CRYPT_BIT_BLOB <>
fPathLenConstraint	BOOL ?
dwPathLenConstraint	dd ?
cSubtreesConstraint	dd ?
rgSubtreesConstraint	PVOID ?; CERT_NAME_BLOB ?
CERT_BASIC_CONSTRAINTS_INFO ENDS
PCERT_BASIC_CONSTRAINTS_INFO typedef ptr CERT_BASIC_CONSTRAINTS_INFO

CERT_CA_SUBJECT_FLAG	equ 0x80
CERT_END_ENTITY_SUBJECT_FLAG equ 0x40

;;+-------------------------------------------------------------------------
;;  X509_BASIC_CONSTRAINTS2
;;  szOID_BASIC_CONSTRAINTS2
;;
;;  pvStructInfo points to following CERT_BASIC_CONSTRAINTS2_INFO.
;;--------------------------------------------------------------------------
CERT_BASIC_CONSTRAINTS2_INFO  STRUC
fCA			BOOL ?
fPathLenConstraint	BOOL ?
dwPathLenConstraint	dd ?
CERT_BASIC_CONSTRAINTS2_INFO ENDS
PCERT_BASIC_CONSTRAINTS2_INFO typedef ptr CERT_BASIC_CONSTRAINTS2_INFO

;;+-------------------------------------------------------------------------
;;  X509_KEY_USAGE
;;  szOID_KEY_USAGE
;;
;;  pvStructInfo points to a CRYPT_BIT_BLOB. Has same bit definitions as
;;  CERT_KEY_ATTRIBUTES_INFO's IntendedKeyUsage.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_CERT_POLICIES
;;  szOID_CERT_POLICIES
;;
;;  pvStructInfo points to following CERT_POLICIES_INFO.
;;--------------------------------------------------------------------------
CERT_POLICY_QUALIFIER_INFO  STRUC
pszPolicyQualifierId	LPSTR ? ;; pszObjId
Qualifier		CRYPT_OBJID_BLOB <>	;; optional
CERT_POLICY_QUALIFIER_INFO ENDS
PCERT_POLICY_QUALIFIER_INFO typedef ptr CERT_POLICY_QUALIFIER_INFO

CERT_POLICY_INFO	STRUC
pszPolicyIdentifier	LPSTR ? ;; pszObjId
cPolicyQualifier	dd ?	;; optional
rgPolicyQualifier	PVOID ?; CERT_POLICY_QUALIFIER_INFO ?
CERT_POLICY_INFO	ENDS
PCERT_POLICY_INFO	typedef ptr CERT_POLICY_INFO

CERT_POLICIES_INFO	STRUC
cPolicyInfo		dd ?
rgPolicyInfo		PVOID ?;ptr CERT_POLICY_INFO ?
CERT_POLICIES_INFO	ENDS
PCERT_POLICIES_INFO	typedef ptr CERT_POLICIES_INFO

;;+-------------------------------------------------------------------------
;;  RSA_CSP_PUBLICKEYBLOB
;;
;;  pvStructInfo points to a PUBLICKEYSTRUC immediately followed by a
;;  RSAPUBKEY and the modulus bytes.
;;
;;  CryptExportKey outputs the above StructInfo for a dwBlobType of
;;  PUBLICKEYBLOB. CryptImportKey expects the above StructInfo when
;;  importing a public key.
;;
;;  For dwCertEncodingType = X509_ASN_ENCODING, the RSA_CSP_PUBLICKEYBLOB is
;;  encoded as a PKCS #1 RSAPublicKey consisting of a SEQUENCE of a
;;  modulus INTEGER and a publicExponent INTEGER. The modulus is encoded
;;  as being a unsigned integer. When decoded, if the modulus was encoded
;;  as unsigned integer with a leading 0 byte, the 0 byte is removed before
;;  converting to the CSP modulus bytes.
;;
;;  For decode, the aiKeyAlg field of PUBLICKEYSTRUC is always set to
;;  CALG_RSA_KEYX.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_KEYGEN_REQUEST_TO_BE_SIGNED
;;
;;  pvStructInfo points to CERT_KEYGEN_REQUEST_INFO.
;;
;;  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
;;  signature (output of a X509_CERT CryptEncodeObject()).
;;
;;  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  PKCS_ATTRIBUTE data structure
;;
;;  pvStructInfo points to a CRYPT_ATTRIBUTE.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  PKCS_CONTENT_INFO_SEQUENCE_OF_ANY data structure
;;
;;  pvStructInfo points to following CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY.
;;
;;  For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure wrapping
;;  a sequence of ANY. The value of the contentType field is pszObjId,
;;  while the content field is the following structure:
;;	SequenceOfAny ::= SEQUENCE OF ANY
;;
;;  The CRYPT_DER_BLOBs point to the already encoded ANY content.
;;--------------------------------------------------------------------------
CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY  STRUC
pszObjId		LPSTR ?
cValue			dd ?
rgValue			PCRYPT_DER_BLOB ?
CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY ENDS
PCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY typedef ptr CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY

;;+-------------------------------------------------------------------------
;;  PKCS_CONTENT_INFO data structure
;;
;;  pvStructInfo points to following CRYPT_CONTENT_INFO.
;;
;;  For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure.
;;  The CRYPT_DER_BLOB points to the already encoded ANY content.
;;--------------------------------------------------------------------------
CRYPT_CONTENT_INFO	STRUC
pszObjId		LPSTR ?
Content			CRYPT_DER_BLOB <>
CRYPT_CONTENT_INFO	ENDS
PCRYPT_CONTENT_INFO	typedef ptr CRYPT_CONTENT_INFO


;;+-------------------------------------------------------------------------
;;  X509_OCTET_STRING data structure
;;
;;  pvStructInfo points to a CRYPT_DATA_BLOB.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_BITS data structure
;;
;;  pvStructInfo points to a CRYPT_BIT_BLOB.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_INTEGER data structure
;;
;;  pvStructInfo points to an int.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_MULTI_BYTE_INTEGER data structure
;;
;;  pvStructInfo points to a CRYPT_INTEGER_BLOB.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_ENUMERATED data structure
;;
;;  pvStructInfo points to an int containing the enumerated value
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_CHOICE_OF_TIME data structure
;;
;;  pvStructInfo points to a FILETIME.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_SEQUENCE_OF_ANY data structure
;;
;;  pvStructInfo points to following CRYPT_SEQUENCE_OF_ANY.
;;
;;  The CRYPT_DER_BLOBs point to the already encoded ANY content.
;;--------------------------------------------------------------------------
CRYPT_SEQUENCE_OF_ANY	STRUC
cValue			dd ?
rgValue			PCRYPT_DER_BLOB ?
CRYPT_SEQUENCE_OF_ANY	ENDS
PCRYPT_SEQUENCE_OF_ANY	typedef ptr CRYPT_SEQUENCE_OF_ANY


;;+-------------------------------------------------------------------------
;;  X509_AUTHORITY_KEY_ID2
;;  szOID_AUTHORITY_KEY_IDENTIFIER2
;;
;;  pvStructInfo points to following CERT_AUTHORITY_KEY_ID2_INFO.
;;
;;  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
;;  *pcbEncoded by CryptEncodeObject(X509_AUTHORITY_KEY_ID2)
;;
;;  See X509_ALTERNATE_NAME for error location defines.
;;--------------------------------------------------------------------------
CERT_AUTHORITY_KEY_ID2_INFO  STRUC
KeyId			CRYPT_DATA_BLOB <>
AuthorityCertIssuer	CERT_ALT_NAME_INFO <>	;; Optional, set cAltEntry
						;; to 0 to omit.
AuthorityCertSerialNumber CRYPT_INTEGER_BLOB <>
CERT_AUTHORITY_KEY_ID2_INFO ENDS
PCERT_AUTHORITY_KEY_ID2_INFO typedef ptr CERT_AUTHORITY_KEY_ID2_INFO

;;+-------------------------------------------------------------------------
;;  szOID_SUBJECT_KEY_IDENTIFIER
;;
;;  pvStructInfo points to a CRYPT_DATA_BLOB.
;;--------------------------------------------------------------------------


;;+-------------------------------------------------------------------------
;;  X509_CRL_REASON_CODE
;;  szOID_CRL_REASON_CODE
;;
;;  pvStructInfo points to an int which can be set to one of the following
;;  enumerated values:
;;--------------------------------------------------------------------------
CRL_REASON_UNSPECIFIED	equ 0
CRL_REASON_KEY_COMPROMISE equ 1
CRL_REASON_CA_COMPROMISE equ 2
CRL_REASON_AFFILIATION_CHANGED equ 3
CRL_REASON_SUPERSEDED	equ 4
CRL_REASON_CESSATION_OF_OPERATION equ 5
CRL_REASON_CERTIFICATE_HOLD equ 6
CRL_REASON_REMOVE_FROM_CRL equ 8


;;+-------------------------------------------------------------------------
;;  X509_CRL_DIST_POINTS
;;  szOID_CRL_DIST_POINTS
;;
;;  pvStructInfo points to following CRL_DIST_POINTS_INFO.
;;
;;  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
;;  *pcbEncoded by CryptEncodeObject(X509_CRL_DIST_POINTS)
;;
;;  Error location consists of:
;;    CRL_ISSUER_BIT	- 1 bit	 << 31 (0 for FullName, 1 for CRLIssuer)
;;    POINT_INDEX	- 7 bits << 24
;;    ENTRY_INDEX	- 8 bits << 16
;;    VALUE_INDEX	- 16 bits (unicode character index)
;;
;;  See X509_ALTERNATE_NAME for ENTRY_INDEX and VALUE_INDEX error location
;;  defines.
;;--------------------------------------------------------------------------
CRL_DIST_POINT_NAME	STRUC
dwDistPointNameChoice	dd ?
;UNION
  FullName		CERT_ALT_NAME_INFO <>
;ENDS
CRL_DIST_POINT_NAME	ENDS
PCRL_DIST_POINT_NAME	typedef ptr CRL_DIST_POINT_NAME

CRL_DIST_POINT_NO_NAME	equ 0
CRL_DIST_POINT_FULL_NAME equ 1
CRL_DIST_POINT_ISSUER_RDN_NAME equ 2

CRL_DIST_POINT		STRUC
DistPointName		CRL_DIST_POINT_NAME <>	;; OPTIONAL
ReasonFlags		CRYPT_BIT_BLOB <>	;; OPTIONAL
CRLIssuer		CERT_ALT_NAME_INFO <>	;; OPTIONAL
CRL_DIST_POINT		ENDS
PCRL_DIST_POINT		typedef ptr CRL_DIST_POINT

CRL_REASON_UNUSED_FLAG	equ 0x80
CRL_REASON_KEY_COMPROMISE_FLAG equ 0x40
CRL_REASON_CA_COMPROMISE_FLAG equ 0x20
CRL_REASON_AFFILIATION_CHANGED_FLAG equ 0x10
CRL_REASON_SUPERSEDED_FLAG equ 0x08
CRL_REASON_CESSATION_OF_OPERATION_FLAG equ 0x04
CRL_REASON_CERTIFICATE_HOLD_FLAG equ 0x02

CRL_DIST_POINTS_INFO	STRUC
cDistPoint		dd ?
rgDistPoint		PCRL_DIST_POINT ?
CRL_DIST_POINTS_INFO	ENDS
PCRL_DIST_POINTS_INFO	typedef ptr CRL_DIST_POINTS_INFO

CRL_DIST_POINT_ERR_INDEX_MASK equ 0x7F
CRL_DIST_POINT_ERR_INDEX_SHIFT equ 24
GET_CRL_DIST_POINT_ERR_INDEX macro X
	exitm<((X SHR CRL_DIST_POINT_ERR_INDEX_SHIFT) AND CRL_DIST_POINT_ERR_INDEX_MASK)>
	endm

CRL_DIST_POINT_ERR_CRL_ISSUER_BIT equ 0x80000000
IS_CRL_DIST_POINT_ERR_CRL_ISSUER macro X
	exitm<(0 NOT = (X AND CRL_DIST_POINT_ERR_CRL_ISSUER_BIT))>
	endm


;;+-------------------------------------------------------------------------
;;  X509_ENHANCED_KEY_USAGE
;;  szOID_ENHANCED_KEY_USAGE
;;
;;  pvStructInfo points to a CERT_ENHKEY_USAGE, CTL_USAGE.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NEXT_UPDATE_LOCATION
;;
;;  pvStructInfo points to a CERT_ALT_NAME_INFO.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  PKCS_CTL
;;  szOID_CTL
;;
;;  pvStructInfo points to a CTL_INFO.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_MULTI_BYTE_UINT
;;
;;  pvStructInfo points to a CRYPT_UINT_BLOB. Before encoding, inserts a
;;  leading 0x00. After decoding, removes a leading 0x00.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_DSS_PUBLICKEY
;;
;;  pvStructInfo points to a CRYPT_UINT_BLOB.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  X509_DSS_PARAMETERS
;;
;;  pvStructInfo points to following CERT_DSS_PARAMETERS data structure.
;;--------------------------------------------------------------------------
CERT_DSS_PARAMETERS	STRUC
p			CRYPT_UINT_BLOB <>
q			CRYPT_UINT_BLOB <>
g			CRYPT_UINT_BLOB <>
CERT_DSS_PARAMETERS	ENDS
PCERT_DSS_PARAMETERS	typedef ptr CERT_DSS_PARAMETERS

;;+-------------------------------------------------------------------------
;;  X509_DSS_SIGNATURE
;;
;;  pvStructInfo is a BYTE rgbSignature[CERT_DSS_SIGNATURE_LEN]. The
;;  bytes are ordered as output by the DSS CSP's CryptSignHash().
;;--------------------------------------------------------------------------
CERT_DSS_R_LEN		equ 20
CERT_DSS_S_LEN		equ 20
CERT_DSS_SIGNATURE_LEN	equ (CERT_DSS_R_LEN + CERT_DSS_S_LEN)

;; Sequence of 2 unsigned integers (the extra +1 is for a potential leading
;; 0x00 to make the integer unsigned)
CERT_MAX_ASN_ENCODED_DSS_SIGNATURE_LEN equ (2 + 2*(2 + 20 +1))


;;+-------------------------------------------------------------------------
;;  PKCS_RC2_CBC_PARAMETERS
;;  szOID_RSA_RC2CBC
;;
;;  pvStructInfo points to following CRYPT_RC2_CBC_PARAMETERS data structure.
;;--------------------------------------------------------------------------
CRYPT_RC2_CBC_PARAMETERS  STRUC
dwVersion		dd ?
fIV			BOOL ?	;; set if has following IV
rgbIV			db 8 dup(?)
CRYPT_RC2_CBC_PARAMETERS ENDS
PCRYPT_RC2_CBC_PARAMETERS typedef ptr CRYPT_RC2_CBC_PARAMETERS

CRYPT_RC2_40BIT_VERSION equ 160
CRYPT_RC2_64BIT_VERSION equ 120
CRYPT_RC2_128BIT_VERSION equ 58


;;+-------------------------------------------------------------------------
;;  PKCS_SMIME_CAPABILITIES
;;  szOID_RSA_SMIMECapabilities
;;
;;  pvStructInfo points to following CRYPT_SMIME_CAPABILITIES data structure.
;;
;;  Note, for CryptEncodeObject(X509_ASN_ENCODING), Parameters.cbData == 0
;;  causes the encoded parameters to be omitted and not encoded as a NULL
;;  (05 00) as is done when encoding a CRYPT_ALGORITHM_IDENTIFIER. This
;;  is per the SMIME specification for encoding capabilities.
;;--------------------------------------------------------------------------
CRYPT_SMIME_CAPABILITY	STRUC
pszObjId		LPSTR ?
Parameters		CRYPT_OBJID_BLOB <>
CRYPT_SMIME_CAPABILITY	ENDS
PCRYPT_SMIME_CAPABILITY typedef ptr CRYPT_SMIME_CAPABILITY

CRYPT_SMIME_CAPABILITIES  STRUC
cCapability		dd ?
rgCapability		PCRYPT_SMIME_CAPABILITY ?
CRYPT_SMIME_CAPABILITIES ENDS
PCRYPT_SMIME_CAPABILITIES typedef ptr CRYPT_SMIME_CAPABILITIES


;;+-------------------------------------------------------------------------
;;  PKCS7_SIGNER_INFO
;;
;;  pvStructInfo points to CMSG_SIGNER_INFO.
;;--------------------------------------------------------------------------


;;+-------------------------------------------------------------------------
;;  Netscape Certificate Extension Object Identifiers
;;--------------------------------------------------------------------------
szOID_NETSCAPE			equ <"2.16.840.1.113730">
szOID_NETSCAPE_CERT_EXTENSION	equ <"2.16.840.1.113730.1">
szOID_NETSCAPE_CERT_TYPE	equ <"2.16.840.1.113730.1.1">
szOID_NETSCAPE_BASE_URL		equ <"2.16.840.1.113730.1.2">
szOID_NETSCAPE_REVOCATION_URL	equ <"2.16.840.1.113730.1.3">
szOID_NETSCAPE_CA_REVOCATION_URL equ <"2.16.840.1.113730.1.4">
szOID_NETSCAPE_CERT_RENEWAL_URL equ <"2.16.840.1.113730.1.7">
szOID_NETSCAPE_CA_POLICY_URL	equ <"2.16.840.1.113730.1.8">
szOID_NETSCAPE_SSL_SERVER_NAME	equ <"2.16.840.1.113730.1.12">
szOID_NETSCAPE_COMMENT		equ <"2.16.840.1.113730.1.13">

;;+-------------------------------------------------------------------------
;;  Netscape Certificate Data Type Object Identifiers
;;--------------------------------------------------------------------------
szOID_NETSCAPE_DATA_TYPE	equ <"2.16.840.1.113730.2">
szOID_NETSCAPE_CERT_SEQUENCE	equ <"2.16.840.1.113730.2.5">


;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_CERT_TYPE extension
;;
;;  Its value is a bit string. CryptDecodeObject/CryptEncodeObject using
;;  X509_BITS.
;;
;;  The following bits are defined:
;;--------------------------------------------------------------------------
NETSCAPE_SSL_CLIENT_AUTH_CERT_TYPE equ 0x80
NETSCAPE_SSL_SERVER_AUTH_CERT_TYPE equ 0x40
NETSCAPE_SSL_CA_CERT_TYPE equ 0x04

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_BASE_URL extension
;;
;;  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
;;  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
;;  dwValueType = CERT_RDN_IA5_STRING.
;;
;;  When present this string is added to the beginning of all relative URLs
;;  in the certificate.	 This extension can be considered an optimization
;;  to reduce the size of the URL extensions.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_REVOCATION_URL extension
;;
;;  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
;;  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
;;  dwValueType = CERT_RDN_IA5_STRING.
;;
;;  It is a relative or absolute URL that can be used to check the
;;  revocation status of a certificate. The revocation check will be
;;  performed as an HTTP GET method using a url that is the concatenation of
;;  revocation-url and certificate-serial-number.
;;  Where the certificate-serial-number is encoded as a string of
;;  ascii hexadecimal digits. For example, if the netscape-base-url is
;;  https://www.certs-r-us.com/, the netscape-revocation-url is
;;  cgi-bin/check-rev.cgi?, and the certificate serial number is 173420,
;;  the resulting URL would be:
;;  https://www.certs-r-us.com/cgi-bin/check-rev.cgi?02a56c
;;
;;  The server should return a document with a Content-Type of
;;  application/x-netscape-revocation.	The document should contain
;;  a single ascii digit, '1' if the certificate is not curently valid,
;;  and '0' if it is curently valid.
;;
;;  Note: for all of the URLs that include the certificate serial number,
;;  the serial number will be encoded as a string which consists of an even
;;  number of hexadecimal digits.  If the number of significant digits is odd,
;;  the string will have a single leading zero to ensure an even number of
;;  digits is generated.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_CA_REVOCATION_URL extension
;;
;;  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
;;  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
;;  dwValueType = CERT_RDN_IA5_STRING.
;;
;;  It is a relative or absolute URL that can be used to check the
;;  revocation status of any certificates that are signed by the CA that
;;  this certificate belongs to. This extension is only valid in CA
;;  certificates.  The use of this extension is the same as the above
;;  szOID_NETSCAPE_REVOCATION_URL extension.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_CERT_RENEWAL_URL extension
;;
;;  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
;;  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
;;  dwValueType = CERT_RDN_IA5_STRING.
;;
;;  It is a relative or absolute URL that points to a certificate renewal
;;  form. The renewal form will be accessed with an HTTP GET method using a
;;  url that is the concatenation of renewal-url and
;;  certificate-serial-number. Where the certificate-serial-number is
;;  encoded as a string of ascii hexadecimal digits. For example, if the
;;  netscape-base-url is https://www.certs-r-us.com/, the
;;  netscape-cert-renewal-url is cgi-bin/check-renew.cgi?, and the
;;  certificate serial number is 173420, the resulting URL would be:
;;  https://www.certs-r-us.com/cgi-bin/check-renew.cgi?02a56c
;;  The document returned should be an HTML form that will allow the user
;;  to request a renewal of their certificate.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_CA_POLICY_URL extension
;;
;;  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
;;  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
;;  dwValueType = CERT_RDN_IA5_STRING.
;;
;;  It is a relative or absolute URL that points to a web page that
;;  describes the policies under which the certificate was issued.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_SSL_SERVER_NAME extension
;;
;;  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
;;  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
;;  dwValueType = CERT_RDN_IA5_STRING.
;;
;;  It is a "shell expression" that can be used to match the hostname of the
;;  SSL server that is using this certificate.	It is recommended that if
;;  the server's hostname does not match this pattern the user be notified
;;  and given the option to terminate the SSL connection.  If this extension
;;  is not present then the CommonName in the certificate subject's
;;  distinguished name is used for the same purpose.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_COMMENT extension
;;
;;  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
;;  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
;;  dwValueType = CERT_RDN_IA5_STRING.
;;
;;  It is a comment that may be displayed to the user when the certificate
;;  is viewed.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  szOID_NETSCAPE_CERT_SEQUENCE
;;
;;  Its value is a PKCS#7 ContentInfo structure wrapping a sequence of
;;  certificates. The value of the contentType field is
;;  szOID_NETSCAPE_CERT_SEQUENCE, while the content field is the following
;;  structure:
;;	CertificateSequence ::= SEQUENCE OF Certificate.
;;
;;  CryptDecodeObject/CryptEncodeObject using
;;  PKCS_CONTENT_INFO_SEQUENCE_OF_ANY, where,
;;  pszObjId = szOID_NETSCAPE_CERT_SEQUENCE and the CRYPT_DER_BLOBs point
;;  to encoded X509 certificates.
;;--------------------------------------------------------------------------


;;+=========================================================================
;;  Object IDentifier (OID) Installable Functions:  Data Structures and APIs
;;==========================================================================

HCRYPTOIDFUNCSET	typedef PVOID
HCRYPTOIDFUNCADDR	typedef PVOID

;; Predefined OID Function Names
CRYPT_OID_ENCODE_OBJECT_FUNC equ <"CryptDllEncodeObject">
CRYPT_OID_DECODE_OBJECT_FUNC equ <"CryptDllDecodeObject">
CRYPT_OID_CREATE_COM_OBJECT_FUNC equ <"CryptDllCreateCOMObject">
CRYPT_OID_VERIFY_REVOCATION_FUNC equ <"CertDllVerifyRevocation">
CRYPT_OID_VERIFY_CTL_USAGE_FUNC equ <"CertDllVerifyCTLUsage">
CRYPT_OID_FORMAT_OBJECT_FUNC equ <"CryptDllFormatObject">
CRYPT_OID_FIND_OID_INFO_FUNC equ <"CryptDllFindOIDInfo">

;; CryptDllEncodeObject has same function signature as CryptEncodeObject.

;; CryptDllDecodeObject has same function signature as CryptDecodeObject.

;; CryptDllCreateCOMObject has the following signature:
;;	BOOL WINAPI CryptDllCreateCOMObject(
;;	   DWORD dwEncodingType,
;;	   LPCSTR pszOID,
;;	   PCRYPT_DATA_BLOB pEncodedContent,
;;	   DWORD dwFlags,
;;	   REFIID riid,
;;	   void **ppvObj);

;; CertDllVerifyRevocation has the same signature as CertVerifyRevocation
;;  (See CertVerifyRevocation for details on when called)

;; CertDllVerifyCTLUsage has the same signature as CertVerifyCTLUsage

;; CryptDllFindOIDInfo currently is only used to store values used by
;; CryptFindOIDInfo. See CryptFindOIDInfo() for more details.

;;  Example of a complete OID Function Registry Name:
;;    HKEY_LOCAL_MACHINE\Software\Microsoft\Cryptography\OID
;;	Encoding Type 1\CryptDllEncodeObject\1.2.3
;;
;;  The key's L"Dll" value contains the name of the Dll.
;;  The key's L"FuncName" value overrides the default function name
CRYPT_OID_REGPATH	equ <"Software\\Microsoft\\Cryptography\\OID">
CRYPT_OID_REG_ENCODING_TYPE_PREFIX equ <"EncodingType ">
CRYPT_OID_REG_DLL_VALUE_NAME equ L"Dll"
CRYPT_OID_REG_FUNC_NAME_VALUE_NAME equ L"FuncName">
CRYPT_OID_REG_FUNC_NAME_VALUE_NAME_A equ <"FuncName">

;; OID used for Default OID functions
CRYPT_DEFAULT_OID	equ <"DEFAULT">

CRYPT_OID_FUNC_ENTRY	STRUC
pszOID			LPCSTR ?
pvFuncAddr		PVOID ?
CRYPT_OID_FUNC_ENTRY	ENDS
PCRYPT_OID_FUNC_ENTRY	typedef ptr CRYPT_OID_FUNC_ENTRY


CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG equ 1

;;+-------------------------------------------------------------------------
;;  Install a set of callable OID function addresses.
;;
;;  By default the functions are installed at end of the list.
;;  Set CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG to install at beginning of list.
;;
;;  hModule should be updated with the hModule passed to DllMain to prevent
;;  the Dll containing the function addresses from being unloaded by
;;  CryptGetOIDFuncAddress/CryptFreeOIDFunctionAddress. This would be the
;;  case when the Dll has also regsvr32'ed OID functions via
;;  CryptRegisterOIDFunction.
;;
;;  DEFAULT functions are installed by setting rgFuncEntry[].pszOID =
;;  CRYPT_DEFAULT_OID.
;;--------------------------------------------------------------------------
;BOOL
CryptInstallOIDFunctionAddress proto _CType \
	       hModule: HMODULE, ; hModule passed to DllMain
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
	    cFuncEntry: DWORD,
	   rgFuncEntry: CRYPT_OID_FUNC_ENTRY,
	       dwFlags: DWORD

;;+-------------------------------------------------------------------------
;;  Initialize and return handle to the OID function set identified by its
;;  function name.
;;
;;  If the set already exists, a handle to the existing set is returned.
;;--------------------------------------------------------------------------
;HCRYPTOIDFUNCSET
CryptInitOIDFunctionSet proto _CType \
	   pszFuncName: LPCSTR,
	       dwFlags: DWORD

;;+-------------------------------------------------------------------------
;;  Search the list of installed functions for an encoding type and OID match.
;;  If not found, search the registry.
;;
;;  For success, returns TRUE with *ppvFuncAddr updated with the function's
;;  address and *phFuncAddr updated with the function address's handle.
;;  The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
;;  be called to release it.
;;
;;  For a registry match, the Dll containing the function is loaded.
;;--------------------------------------------------------------------------
;BOOL
CryptGetOIDFunctionAddress proto _CType \
	      hFuncSet: HCRYPTOIDFUNCSET,
	dwEncodingType: DWORD,
		pszOID: LPCSTR,
	       dwFlags: DWORD,
	   ppvFuncAddr: PVOID,
	    phFuncAddr: ptr HCRYPTOIDFUNCADDR


;;+-------------------------------------------------------------------------
;;  Get the list of registered default Dll entries for the specified
;;  function set and encoding type.
;;
;;  The returned list consists of none, one or more null terminated Dll file
;;  names. The list is terminated with an empty (L"\0") Dll file name.
;;  For example: L"first.dll" L"\0" L"second.dll" L"\0" L"\0"
;;--------------------------------------------------------------------------
;BOOL
CryptGetDefaultOIDDllList proto _CType \
	      hFuncSet: HCRYPTOIDFUNCSET,
	dwEncodingType: DWORD,
	   pwszDllList: LPWSTR,
	   pcchDllList: LPDWORD

;;+-------------------------------------------------------------------------
;;  Either: get the first or next installed DEFAULT function OR
;;  load the Dll containing the DEFAULT function.
;;
;;  If pwszDll is NULL, search the list of installed DEFAULT functions.
;;  *phFuncAddr must be set to NULL to get the first installed function.
;;  Successive installed functions are returned by setting *phFuncAddr
;;  to the hFuncAddr returned by the previous call.
;;
;;  If pwszDll is NULL, the input *phFuncAddr
;;  is always CryptFreeOIDFunctionAddress'ed by this function, even for
;;  an error.
;;
;;  If pwszDll isn't NULL, then, attempts to load the Dll and the DEFAULT
;;  function. *phFuncAddr is ignored upon entry and isn't
;;  CryptFreeOIDFunctionAddress'ed.
;;
;;  For success, returns TRUE with *ppvFuncAddr updated with the function's
;;  address and *phFuncAddr updated with the function address's handle.
;;  The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
;;  be called to release it or CryptGetDefaultOIDFunctionAddress can also
;;  be called for a NULL pwszDll.
;;--------------------------------------------------------------------------
;BOOL
CryptGetDefaultOIDFunctionAddress proto _CType \
	      hFuncSet: HCRYPTOIDFUNCSET,
	dwEncodingType: DWORD,
	       pwszDll: LPCWSTR,
	       dwFlags: DWORD,
	   ppvFuncAddr: PVOID,
	    phFuncAddr: ptr HCRYPTOIDFUNCADDR

;;+-------------------------------------------------------------------------
;;  Releases the handle AddRef'ed and returned by CryptGetOIDFunctionAddress
;;  or CryptGetDefaultOIDFunctionAddress.
;;
;;  If a Dll was loaded for the function its unloaded. However, before doing
;;  the unload, the DllCanUnloadNow function exported by the loaded Dll is
;;  called. It should return S_FALSE to inhibit the unload or S_TRUE to enable
;;  the unload. If the Dll doesn't export DllCanUnloadNow, the Dll is unloaded.
;;
;;  DllCanUnloadNow has the following signature:
;;	STDAPI	DllCanUnloadNow(void);
;;--------------------------------------------------------------------------
;BOOL
CryptFreeOIDFunctionAddress proto _CType \
	     hFuncAddr: HCRYPTOIDFUNCADDR,
	       dwFlags: DWORD

;;+-------------------------------------------------------------------------
;;  Register the Dll containing the function to be called for the specified
;;  encoding type, function name and OID.
;;
;;  pwszDll may contain environment-variable strings
;;  which are ExpandEnvironmentStrings()'ed before loading the Dll.
;;
;;  In addition to registering the DLL, you may override the
;;  name of the function to be called. For example,
;;	pszFuncName = "CryptDllEncodeObject",
;;	pszOverrideFuncName = "MyEncodeXyz".
;;  This allows a Dll to export multiple OID functions for the same
;;  function name without needing to interpose its own OID dispatcher function.
;;--------------------------------------------------------------------------
;BOOL
CryptRegisterOIDFunction proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
		pszOID: LPCSTR,
	       pwszDll: LPCWSTR,
   pszOverrideFuncName: LPCSTR

;;+-------------------------------------------------------------------------
;;  Unregister the Dll containing the function to be called for the specified
;;  encoding type, function name and OID.
;;--------------------------------------------------------------------------
;BOOL
CryptUnregisterOIDFunction proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
		pszOID: LPCSTR


;;+-------------------------------------------------------------------------
;;  Register the Dll containing the default function to be called for the
;;  specified encoding type and function name.
;;
;;  Unlike CryptRegisterOIDFunction, you can't override the function name
;;  needing to be exported by the Dll.
;;
;;  The Dll is inserted before the entry specified by dwIndex.
;;    dwIndex == 0, inserts at the beginning.
;;    dwIndex == CRYPT_REGISTER_LAST_INDEX, appends at the end.
;;
;;  pwszDll may contain environment-variable strings
;;  which are ExpandEnvironmentStrings()'ed before loading the Dll.
;;--------------------------------------------------------------------------
;BOOL
CryptRegisterDefaultOIDFunction proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
	       dwIndex: DWORD,
	       pwszDll: LPCWSTR

CRYPT_REGISTER_FIRST_INDEX equ 0
CRYPT_REGISTER_LAST_INDEX equ 0xFFFFFFFF

;;+-------------------------------------------------------------------------
;;  Unregister the Dll containing the default function to be called for
;;  the specified encoding type and function name.
;;--------------------------------------------------------------------------
;BOOL
CryptUnregisterDefaultOIDFunction proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
	       pwszDll: LPCWSTR

;;+-------------------------------------------------------------------------
;;  Set the value for the specified encoding type, function name, OID and
;;  value name.
;;
;;  See RegSetValueEx for the possible value types.
;;
;;  String types are UNICODE.
;;--------------------------------------------------------------------------
;BOOL
CryptSetOIDFunctionValue proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
		pszOID: LPCSTR,
	 pwszValueName: LPCWSTR,
	   dwValueType: DWORD,
	   pbValueData: LPBYTE,
	   cbValueData: DWORD

;;+-------------------------------------------------------------------------
;;  Get the value for the specified encoding type, function name, OID and
;;  value name.
;;
;;  See RegEnumValue for the possible value types.
;;
;;  String types are UNICODE.
;;--------------------------------------------------------------------------
;BOOL
CryptGetOIDFunctionValue proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
		pszOID: LPCSTR,
	 pwszValueName: LPCWSTR,
	  pdwValueType: LPDWORD,
	   pbValueData: LPBYTE,
	  pcbValueData: LPDWORD

;BOOL
PFN_CRYPT_ENUM_OID_FUNC_T typedef proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
		pszOID: LPCSTR,
		cValue: DWORD,
	 rgdwValueType: DWORD,
       rgpwszValueName: LPCWSTR,
	 rgpbValueData: LPBYTE,
	 rgcbValueData: DWORD,
		 pvArg: PVOID
PFN_CRYPT_ENUM_OID_FUNC typedef ptr PFN_CRYPT_ENUM_OID_FUNC_T

;;+-------------------------------------------------------------------------
;;  Enumerate the OID functions identified by their encoding type,
;;  function name and OID.
;;
;;  pfnEnumOIDFunc is called for each registry key matching the input
;;  parameters. Setting dwEncodingType to CRYPT_MATCH_ANY_ENCODING_TYPE matches
;;  any. Setting pszFuncName or pszOID to NULL matches any.
;;
;;  Set pszOID == CRYPT_DEFAULT_OID to restrict the enumeration to only the
;;  DEFAULT functions
;;
;;  String types are UNICODE.
;;--------------------------------------------------------------------------
;BOOL
CryptEnumOIDFunction proto _CType \
	dwEncodingType: DWORD,
	   pszFuncName: LPCSTR,
		pszOID: LPCSTR,
	       dwFlags: DWORD,
		 pvArg: PVOID,
	pfnEnumOIDFunc: PFN_CRYPT_ENUM_OID_FUNC

CRYPT_MATCH_ANY_ENCODING_TYPE equ 0xFFFFFFFF


;;+=========================================================================
;;  Object IDentifier (OID) Information:  Data Structures and APIs
;;==========================================================================

;;+-------------------------------------------------------------------------
;;  OID Information
;;--------------------------------------------------------------------------
CRYPT_OID_INFO		STRUC
cbSize			dd ?
pszOID			LPCSTR ?
pwszName		LPCWSTR ?
dwGroupId		dd ?
UNION
 dwValue		dd ?
 Algid			ALG_ID ?
 dwLength		dd ?
ENDS
ExtraInfo		CRYPT_DATA_BLOB <>
CRYPT_OID_INFO		ENDS
PCRYPT_OID_INFO		typedef ptr CRYPT_OID_INFO
PCCRYPT_OID_INFO	typedef ptr CRYPT_OID_INFO
;CCRYPT_OID_INFO

;;+-------------------------------------------------------------------------
;;  OID Group IDs
;;--------------------------------------------------------------------------
CRYPT_HASH_ALG_OID_GROUP_ID equ 1
CRYPT_ENCRYPT_ALG_OID_GROUP_ID equ 2
CRYPT_PUBKEY_ALG_OID_GROUP_ID equ 3
CRYPT_SIGN_ALG_OID_GROUP_ID equ 4
CRYPT_RDN_ATTR_OID_GROUP_ID equ 5
CRYPT_EXT_OR_ATTR_OID_GROUP_ID equ 6
CRYPT_ENHKEY_USAGE_OID_GROUP_ID equ 7
CRYPT_POLICY_OID_GROUP_ID equ 8
CRYPT_LAST_OID_GROUP_ID equ 8

CRYPT_FIRST_ALG_OID_GROUP_ID equ CRYPT_HASH_AG_OID_GROUP_ID
CRYPT_LAST_ALG_OID_GROUP_ID equ CRYPT_SIGN_AG_OID_GROUP_ID


;; The CRYPT_*_ALG_OID_GROUP_ID's have an Algid. The CRYPT_RDN_ATTR_OID_GROUP_ID
;; has a dwLength. The CRYPT_EXT_OR_ATTR_OID_GROUP_ID,
;; CRYPT_ENHKEY_USAGE_OID_GROUP_ID or CRYPT_POLICY_OID_GROUP_ID don't have a
;; dwValue.
;;

;; CRYPT_PUBKEY_ALG_OID_GROUP_ID has the following optional ExtraInfo:
;;  DWORD[0] - Flags. CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG can be set to
;;	       inhibit the reformatting of the signature before
;;	       CryptVerifySignature is called or after CryptSignHash
;;	       is called. CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG can
;;	       be set to include the public key algorithm's parameters
;;	       in the PKCS7's digestEncryptionAlgorithm's parameters.

CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG equ 0x1
CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG equ 0x2

;; CRYPT_SIGN_ALG_OID_GROUP_ID has the following optional ExtraInfo:
;;  DWORD[0] - Public Key Algid.
;;  DWORD[1] - Flags. Same as above for CRYPT_PUBKEY_ALG_OID_GROUP_ID.

;; CRYPT_RDN_ATTR_OID_GROUP_ID has the following optional ExtraInfo:
;;  Array of DWORDs:
;;   [0 ..] - Null terminated list of acceptable RDN attribute
;;	      value types. An empty list implies CERT_RDN_PRINTABLE_STRING,
;;	      CERT_RDN_T61_STRING, 0.

;;+-------------------------------------------------------------------------
;;  Find OID information. Returns NULL if unable to find any information
;;  for the specified key and group. Note, returns a pointer to a constant
;;  data structure. The returned pointer MUST NOT be freed.
;;
;;  dwKeyType's:
;;    CRYPT_OID_INFO_OID_KEY, pvKey points to a szOID
;;    CRYPT_OID_INFO_NAME_KEY, pvKey points to a wszName
;;    CRYPT_OID_INFO_ALGID_KEY, pvKey points to an ALG_ID
;;    CRYPT_OID_INFO_SIGN_KEY, pvKey points to an array of two ALG_ID's:
;;	ALG_ID[0] - Hash Algid
;;	ALG_ID[1] - PubKey Algid
;;
;;  Setting dwGroupId to 0, searches all groups according to the dwKeyType.
;;  Otherwise, only the dwGroupId is searched.
;;--------------------------------------------------------------------------
;PCCRYPT_OID_INFO
CryptFindOIDInfo proto _CType \
	     dwKeyType: DWORD,
		 pvKey: PVOID,
	     dwGroupId: DWORD

CRYPT_OID_INFO_OID_KEY	equ 1
CRYPT_OID_INFO_NAME_KEY equ 2
CRYPT_OID_INFO_ALGID_KEY equ 3
CRYPT_OID_INFO_SIGN_KEY equ 4

;;+-------------------------------------------------------------------------
;;  Register OID information. The OID information specified in the
;;  CCRYPT_OID_INFO structure is persisted to the registry.
;;
;;  crypt32.dll contains information for the commonly known OIDs. This function
;;  allows applications to augment crypt32.dll's OID information. During
;;  CryptFindOIDInfo's first call, the registered OID information is installed.
;;
;;  By default the registered OID information is installed after crypt32.dll's
;;  OID entries. Set CRYPT_INSTALL_OID_INFO_BEFORE_FLAG to install before.
;;--------------------------------------------------------------------------
;BOOL
CryptRegisterOIDInfo proto _CType \
		 pInfo: PCCRYPT_OID_INFO,
	       dwFlags: DWORD

CRYPT_INSTALL_OID_INFO_BEFORE_FLAG equ 1

;;+-------------------------------------------------------------------------
;;  Unregister OID information. Only the pszOID and dwGroupId fields are
;;  used to identify the OID information to be unregistered.
;;--------------------------------------------------------------------------
;BOOL
CryptUnregisterOIDInfo proto _CType \
		 pInfo: PCCRYPT_OID_INFO


;;+=========================================================================
;;  Low Level Cryptographic Message Data Structures and APIs
;;==========================================================================

HCRYPTMSG		typedef PVOID

szOID_PKCS_7_DATA	equ <"1.2.840.113549.1.7.1">
szOID_PKCS_7_SIGNED	equ <"1.2.840.113549.1.7.2">
szOID_PKCS_7_ENVELOPED	equ <"1.2.840.113549.1.7.3">
szOID_PKCS_7_SIGNEDANDENVELOPED equ <"1.2.840.113549.1.7.4">
szOID_PKCS_7_DIGESTED	equ <"1.2.840.113549.1.7.5">
szOID_PKCS_7_ENCRYPTED	equ <"1.2.840.113549.1.7.6">

szOID_PKCS_9_CONTENT_TYPE equ <"1.2.840.113549.1.9.3">
szOID_PKCS_9_MESSAGE_DIGEST equ <"1.2.840.113549.1.9.4">

;;+-------------------------------------------------------------------------
;;  Message types
;;--------------------------------------------------------------------------
CMSG_DATA		equ 1
CMSG_SIGNED		equ 2
CMSG_ENVELOPED		equ 3
CMSG_SIGNED_AND_ENVELOPED equ 4
CMSG_HASHED		equ 5
CMSG_ENCRYPTED		equ 6

;;+-------------------------------------------------------------------------
;;  Message Type Bit Flags
;;--------------------------------------------------------------------------
CMSG_ALL_FLAGS		equ ( NOT 0UL)
CMSG_DATA_FLAG		equ (1 SHL CMSG_DATA)
CMSG_SIGNED_FLAG	equ (1 SHL CMSG_SIGNED)
CMSG_ENVELOPED_FLAG	equ (1 SHL CMSG_ENVEOPED)
CMSG_SIGNED_AND_ENVELOPED_FLAG equ (1 SHL CMSG_SIGNED_AND_ENVEOPED)
CMSG_HASHED_FLAG	equ (1 SHL CMSG_HASHED)
CMSG_ENCRYPTED_FLAG	equ (1 SHL CMSG_ENCRYPTED)

;;+-------------------------------------------------------------------------
;;  The message encode information (pvMsgEncodeInfo) is message type dependent
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_DATA: pvMsgEncodeInfo = NULL
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNED
;;
;;  The pCertInfo in the CMSG_SIGNER_ENCODE_INFO provides the Issuer, SerialNumber
;;  and PublicKeyInfo.Algorithm. The PublicKeyInfo.Algorithm implicitly
;;  specifies the HashEncryptionAlgorithm to be used.
;;
;;  The hCryptProv and dwKeySpec specify the private key to use. If dwKeySpec
;;  == 0, then, defaults to AT_SIGNATURE.
;;
;;  pvHashAuxInfo currently isn't used and must be set to NULL.
;;--------------------------------------------------------------------------
CMSG_SIGNER_ENCODE_INFO	 STRUC
cbSize			dd ?
pCertInfo		PCERT_INFO ?
hCryptProv		HCRYPTPROV ?
dwKeySpec		dd ?
HashAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
pvHashAuxInfo		PVOID ?
cAuthAttr		dd ?
rgAuthAttr		PCRYPT_ATTRIBUTE ?
cUnauthAttr		dd ?
rgUnauthAttr		PCRYPT_ATTRIBUTE ?
CMSG_SIGNER_ENCODE_INFO ENDS
PCMSG_SIGNER_ENCODE_INFO typedef ptr CMSG_SIGNER_ENCODE_INFO

CMSG_SIGNED_ENCODE_INFO	 STRUC
cbSize			dd ?
cSigners		dd ?
rgSigners		PCMSG_SIGNER_ENCODE_INFO ?
cCertEncoded		dd ?
rgCertEncoded		PCERT_BLOB ?
cCrlEncoded		dd ?
rgCrlEncoded		PCRL_BLOB ?
CMSG_SIGNED_ENCODE_INFO ENDS
PCMSG_SIGNED_ENCODE_INFO typedef ptr CMSG_SIGNED_ENCODE_INFO

;;+-------------------------------------------------------------------------
;;  CMSG_ENVELOPED
;;
;;  The PCERT_INFO for the rgRecipients provides the Issuer, SerialNumber
;;  and PublicKeyInfo. The PublicKeyInfo.Algorithm implicitly
;;  specifies the KeyEncryptionAlgorithm to be used.
;;
;;  The PublicKeyInfo.PublicKey in PCERT_INFO is used to encrypt the content
;;  encryption key for the recipient.
;;
;;  hCryptProv is used to do the content encryption, recipient key encryption
;;  and export. The hCryptProv's private keys aren't used.
;;
;;  Note: CAPI currently doesn't support more than one KeyEncryptionAlgorithm
;;  per provider. This will need to be fixed.
;;
;;  pvEncryptionAuxInfo currently isn't used and must be set to NULL.
;;--------------------------------------------------------------------------
CMSG_ENVELOPED_ENCODE_INFO  STRUC
cbSize			dd ?
hCryptProv		HCRYPTPROV ?
ContentEncryptionAlgorithm CRYPT_ALGORITHM_IDENTIFIER <>
pvEncryptionAuxInfo	PVOID ?
cRecipients		dd ?
rgpRecipients		PCERT_INFO ?
CMSG_ENVELOPED_ENCODE_INFO ENDS
PCMSG_ENVELOPED_ENCODE_INFO typedef ptr CMSG_ENVELOPED_ENCODE_INFO

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNED_AND_ENVELOPED
;;
;;  For PKCS #7, a signed and enveloped message doesn't have the
;;  signer's authenticated or unauthenticated attributes. Otherwise, a
;;  combination of the CMSG_SIGNED_ENCODE_INFO and CMSG_ENVELOPED_ENCODE_INFO.
;;--------------------------------------------------------------------------
CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO  STRUC
cbSize			dd ?
SignedInfo		CMSG_SIGNED_ENCODE_INFO <>
EnvelopedInfo		CMSG_ENVELOPED_ENCODE_INFO <>
CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO ENDS
PCMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO typedef ptr CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO

;;+-------------------------------------------------------------------------
;;  CMSG_HASHED
;;
;;  hCryptProv is used to do the hash. Doesn't need to use a private key.
;;
;;  If fDetachedHash is set, then, the encoded message doesn't contain
;;  any content (its treated as NULL Data)
;;
;;  pvHashAuxInfo currently isn't used and must be set to NULL.
;;--------------------------------------------------------------------------
CMSG_HASHED_ENCODE_INFO	 STRUC
cbSize			dd ?
hCryptProv		HCRYPTPROV ?
HashAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
pvHashAuxInfo		PVOID ?
CMSG_HASHED_ENCODE_INFO ENDS
PCMSG_HASHED_ENCODE_INFO typedef ptr CMSG_HASHED_ENCODE_INFO

;;+-------------------------------------------------------------------------
;;  CMSG_ENCRYPTED
;;
;;  The key used to encrypt the message is identified outside of the message
;;  content (for example, password).
;;
;;  The content input to CryptMsgUpdate has already been encrypted.
;;
;;  pvEncryptionAuxInfo currently isn't used and must be set to NULL.
;;--------------------------------------------------------------------------
CMSG_ENCRYPTED_ENCODE_INFO  STRUC
cbSize			dd ?
ContentEncryptionAlgorithm CRYPT_ALGORITHM_IDENTIFIER <>
pvEncryptionAuxInfo	PVOID ?
CMSG_ENCRYPTED_ENCODE_INFO ENDS
PCMSG_ENCRYPTED_ENCODE_INFO typedef ptr CMSG_ENCRYPTED_ENCODE_INFO

;;+-------------------------------------------------------------------------
;;  This parameter allows messages to be of variable length with streamed
;;  output.
;;
;;  By default, messages are of a definite length and
;;  CryptMsgGetParam(CMSG_CONTENT_PARAM) is
;;  called to get the cryptographically processed content. Until closed,
;;  the handle keeps a copy of the processed content.
;;
;;  With streamed output, the processed content can be freed as its streamed.
;;
;;  If the length of the content to be updated is known at the time of the
;;  open, then, ContentLength should be set to that length. Otherwise, it
;;  should be set to CMSG_INDEFINITE_LENGTH.
;;--------------------------------------------------------------------------
;BOOL
PFN_CMSG_STREAM_OUTPUT_T typedef proto _CType \
		 pvArg: PVOID,
		pbData: LPBYTE,
		cbData: DWORD,
		fFinal: BOOL
PFN_CMSG_STREAM_OUTPUT typedef ptr PFN_CMSG_STREAM_OUTPUT_T

CMSG_INDEFINITE_LENGTH	equ (0xFFFFFFFF)

CMSG_STREAM_INFO	STRUC
cbContent		dd ?
pfnStreamOutput		PFN_CMSG_STREAM_OUTPUT ?
pvArg			PVOID ?
CMSG_STREAM_INFO	ENDS
PCMSG_STREAM_INFO	typedef ptr CMSG_STREAM_INFO

;;+-------------------------------------------------------------------------
;;  Open dwFlags
;;--------------------------------------------------------------------------
CMSG_BARE_CONTENT_FLAG	equ 0x00000001
CMSG_LENGTH_ONLY_FLAG	equ 0x00000002
CMSG_DETACHED_FLAG	equ 0x00000004
CMSG_AUTHENTICATED_ATTRIBUTES_FLAG equ 0x00000008
CMSG_CONTENTS_OCTETS_FLAG equ 0x00000010
CMSG_MAX_LENGTH_FLAG	equ 0x00000020

;;+-------------------------------------------------------------------------
;;  Open a cryptographic message for encoding
;;
;;  For PKCS #7:
;;  If the content to be passed to CryptMsgUpdate has already
;;  been message encoded (the input to CryptMsgUpdate is the streamed output
;;  from another message encode), then, the CMSG_ENCODED_CONTENT_INFO_FLAG should
;;  be set in dwFlags. If not set, then, the inner ContentType is Data and
;;  the input to CryptMsgUpdate is treated as the inner Data type's Content,
;;  a string of bytes.
;;  If CMSG_BARE_CONTENT_FLAG is specified for a streamed message,
;;  the streamed output will not have an outer ContentInfo wrapper. This
;;  makes it suitable to be streamed into an enclosing message.
;;
;;  The pStreamInfo parameter needs to be set to stream the encoded message
;;  output.
;;--------------------------------------------------------------------------
;HCRYPTMSG
CryptMsgOpenToEncode proto _CType \
     dwMsgEncodingType: DWORD,
	       dwFlags: DWORD,
	     dwMsgType: DWORD,
       pvMsgEncodeInfo: PVOID,
  pszInnerContentObjID: LPSTR,
	   pStreamInfo: PCMSG_STREAM_INFO

;;+-------------------------------------------------------------------------
;;  Calculate the length of an encoded cryptographic message.
;;
;;  Calculates the length of the encoded message given the
;;  message type, encoding parameters and total length of
;;  the data to be updated. Note, this might not be the exact length. However,
;;  it will always be greater than or equal to the actual length.
;;--------------------------------------------------------------------------
;DWORD
CryptMsgCalculateEncodedLength proto _CType \
     dwMsgEncodingType: DWORD,
	       dwFlags: DWORD,
	     dwMsgType: DWORD,
       pvMsgEncodeInfo: PVOID,
  pszInnerContentObjID: LPSTR,
		cbData: DWORD

;;+-------------------------------------------------------------------------
;;  Open a cryptographic message for decoding
;;
;; These comments need to be changed
;;  For PKCS #7: if the inner ContentType isn't Data, then, the inner
;;  ContentInfo consisting of both ContentType and Content is output.
;;  To also enable ContentInfo output for the Data ContentType, then,
;;  the CMSG_ENCODED_CONTENT_INFO_FLAG should be set
;;  in dwFlags. If not set, then, only the content portion of the inner
;;  ContentInfo is output for the Data ContentType.
;;
;;  To only calculate the length of the decoded message, set the
;;  CMSG_LENGTH_ONLY_FLAG in dwFlags. After the final CryptMsgUpdate get the
;;  MSG_CONTENT_PARAM. Note, this might not be the exact length. However,
;;  it will always be greater than or equal to the actual length.
;;
;;  hCryptProv specifies the crypto provider to use for hashing and/or
;;  decrypting the message. For enveloped messages, hCryptProv also specifies
;;  the private exchange key to use. For signed messages, hCryptProv is used
;;  when CryptMsgVerifySigner is called.
;;
;;  For enveloped messages, the pRecipientInfo contains the Issuer and
;;  SerialNumber identifying the RecipientInfo in the message.
;;
;;  Note, the pRecipientInfo should correspond to the provider's private
;;  exchange key.
;;
;;  If pRecipientInfo is NULL, then, the message isn't decrypted. To decrypt
;;  the message, CryptMsgControl(CMSG_CTRL_DECRYPT) is called after the final
;;  CryptMsgUpdate.
;;
;;  The pStreamInfo parameter needs to be set to stream the decoded content
;;  output. Note, if pRecipientInfo is NULL, then, the streamed output isn't
;;  decrypted.
;;--------------------------------------------------------------------------
;HCRYPTMSG
CryptMsgOpenToDecode proto _CType \
     dwMsgEncodingType: DWORD,
	       dwFlags: DWORD,
	     dwMsgType: DWORD,
	    hCryptProv: HCRYPTPROV,
	pRecipientInfo: PCERT_INFO,
	   pStreamInfo: PCMSG_STREAM_INFO

;;+-------------------------------------------------------------------------
;;  Close a cryptographic message handle
;;
;;  LastError is preserved unless FALSE is returned.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgClose proto _CType \
	     hCryptMsg: HCRYPTMSG

;;+-------------------------------------------------------------------------
;;  Update the content of a cryptographic message. Depending on how the
;;  message was opened, the content is either encoded or decoded.
;;
;;  This function is repetitively called to append to the message content.
;;  fFinal is set to identify the last update. On fFinal, the encode/decode
;;  is completed. The encoded/decoded content and the decoded parameters
;;  are valid until the open and all duplicated handles are closed.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgUpdate proto _CType \
	     hCryptMsg: HCRYPTMSG,
		pbData: LPBYTE,
		cbData: DWORD,
		fFinal: BOOL

;;+-------------------------------------------------------------------------
;;  Perform a special "control" function after the final CryptMsgUpdate of a
;;  encoded/decoded cryptographic message.
;;
;;  The dwCtrlType parameter specifies the type of operation to be performed.
;;
;;  The pvCtrlPara definition depends on the dwCtrlType value.
;;
;;  See below for a list of the control operations and their pvCtrlPara
;;  type definition.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgControl proto _CType \
	     hCryptMsg: HCRYPTMSG,
	       dwFlags: DWORD,
	    dwCtrlType: DWORD,
	    pvCtrlPara: PVOID

;;+-------------------------------------------------------------------------
;;  Message control types
;;--------------------------------------------------------------------------
CMSG_CTRL_VERIFY_SIGNATURE equ 1
CMSG_CTRL_DECRYPT	equ 2
CMSG_CTRL_VERIFY_HASH	equ 5
CMSG_CTRL_ADD_SIGNER	equ 6
CMSG_CTRL_DEL_SIGNER	equ 7
CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR equ 8
CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR equ 9
CMSG_CTRL_ADD_CERT	equ 10
CMSG_CTRL_DEL_CERT	equ 11
CMSG_CTRL_ADD_CRL	equ 12
CMSG_CTRL_DEL_CRL	equ 13

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_VERIFY_SIGNATURE
;;
;;  Verify the signature of a SIGNED or SIGNED_AND_ENVELOPED
;;  message after it has been decoded.
;;
;;  For a SIGNED_AND_ENVELOPED message, called after
;;  CryptMsgControl(CMSG_CTRL_DECRYPT), if CryptMsgOpenToDecode was called
;;  with a NULL pRecipientInfo.
;;
;;  pvCtrlPara points to a CERT_INFO struct.
;;
;;  The CERT_INFO contains the Issuer and SerialNumber identifying
;;  the Signer of the message. The CERT_INFO also contains the
;;  PublicKeyInfo
;;  used to verify the signature. The cryptographic provider specified
;;  in CryptMsgOpenToDecode is used.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_DECRYPT
;;
;;  Decrypt an ENVELOPED or SIGNED_AND_ENVELOPED message after it has been
;;  decoded.
;;
;;  hCryptProv and dwKeySpec specify the private key to use. For dwKeySpec ==
;;  0, defaults to AT_KEYEXCHANGE.
;;
;;  dwRecipientIndex is the index of the recipient in the message associated
;;  with the hCryptProv's private key.
;;
;;  This control function needs to be called, if you don't know the appropriate
;;  recipient before calling CryptMsgOpenToDecode. After the final
;;  CryptMsgUpdate, the list of recipients is obtained by iterating through
;;  CMSG_RECIPIENT_INFO_PARAM. The recipient corresponding to a private
;;  key owned by the caller is selected and passed to this function to decrypt
;;  the message.
;;
;;  Note, the message can only be decrypted once.
;;--------------------------------------------------------------------------
CMSG_CTRL_DECRYPT_PARA	STRUC
cbSize			dd ?
hCryptProv		HCRYPTPROV ?
dwKeySpec		dd ?
dwRecipientIndex	dd ?
CMSG_CTRL_DECRYPT_PARA	ENDS
PCMSG_CTRL_DECRYPT_PARA typedef ptr CMSG_CTRL_DECRYPT_PARA


;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_VERIFY_HASH
;;
;;  Verify the hash of a HASHED message after it has been decoded.
;;
;;  Only the hCryptMsg parameter is used, to specify the message whose
;;  hash is being verified.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_ADD_SIGNER
;;
;;  Add a signer to a signed-data or signed-and-enveloped-data message.
;;
;;  pvCtrlPara points to a CMSG_SIGNER_ENCODE_INFO.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_DEL_SIGNER
;;
;;  Remove a signer from a signed-data or signed-and-enveloped-data message.
;;
;;  pvCtrlPara points to a DWORD containing the 0-based index of the
;;  signer to be removed.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR
;;
;;  Add an unauthenticated attribute to the SignerInfo of a signed-data or
;;  signed-and-enveloped-data message.
;;
;;  The unauthenticated attribute is input in the form of an encoded blob.
;;--------------------------------------------------------------------------

CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA  STRUC
cbSize			dd ?
dwSignerIndex		dd ?
blob			CRYPT_DATA_BLOB <>
CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA ENDS
PCMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA typedef ptr CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR
;;
;;  Delete an unauthenticated attribute from the SignerInfo of a signed-data
;;  or signed-and-enveloped-data message.
;;
;;  The unauthenticated attribute to be removed is specified by
;;  a 0-based index.
;;--------------------------------------------------------------------------

CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA  STRUC
cbSize			dd ?
dwSignerIndex		dd ?
dwUnauthAttrIndex	dd ?
CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA ENDS
PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA typedef ptr CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_ADD_CERT
;;
;;  Add a certificate to a signed-data or signed-and-enveloped-data message.
;;
;;  pvCtrlPara points to a CRYPT_DATA_BLOB containing the certificate's
;;  encoded bytes.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_DEL_CERT
;;
;;  Delete a certificate from a signed-data or signed-and-enveloped-data
;;  message.
;;
;;  pvCtrlPara points to a DWORD containing the 0-based index of the
;;  certificate to be removed.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_ADD_CRL
;;
;;  Add a CRL to a signed-data or signed-and-enveloped-data message.
;;
;;  pvCtrlPara points to a CRYPT_DATA_BLOB containing the CRL's
;;  encoded bytes.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CTRL_DEL_CRL
;;
;;  Delete a CRL from a signed-data or signed-and-enveloped-data message.
;;
;;  pvCtrlPara points to a DWORD containing the 0-based index of the CRL
;;  to be removed.
;;--------------------------------------------------------------------------


;;+-------------------------------------------------------------------------
;;  Verify a countersignature, at the SignerInfo level.
;;  ie. verify that pbSignerInfoCountersignature contains the encrypted
;;  hash of the encryptedDigest field of pbSignerInfo.
;;
;;  hCryptProv is used to hash the encryptedDigest field of pbSignerInfo.
;;  The only fields referenced from pciCountersigner are SerialNumber, Issuer,
;;  and SubjectPublicKeyInfo.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgVerifyCountersignatureEncoded proto _CType \
	    hCryptProv: HCRYPTPROV,
	dwEncodingType: DWORD,
	  pbSignerInfo: PBYTE,
	  cbSignerInfo: DWORD,
pbSignerInfoCountersignature: PBYTE,
cbSignerInfoCountersignature: DWORD,
      pciCountersigner: PCERT_INFO

;;+-------------------------------------------------------------------------
;;  Countersign an already-existing signature in a message
;;
;;  dwIndex is a zero-based index of the SignerInfo to be countersigned.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgCountersign proto _CType \
	     hCryptMsg: HCRYPTMSG,
	       dwIndex: DWORD,
       cCountersigners: DWORD,
      rgCountersigners: PCMSG_SIGNER_ENCODE_INFO

;;+-------------------------------------------------------------------------
;;  Countersign an already-existing signature (encoded SignerInfo).
;;  Output an encoded SignerInfo blob, suitable for use as a countersignature
;;  attribute in the unauthenticated attributes of a signed-data or
;;  signed-and-enveloped-data message.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgCountersignEncoded proto _CType \
	dwEncodingType: DWORD,
	  pbSignerInfo: PBYTE,
	  cbSignerInfo: DWORD,
       cCountersigners: DWORD,
      rgCountersigners: PCMSG_SIGNER_ENCODE_INFO,
    pbCountersignature: PBYTE,
   pcbCountersignature: PDWORD


;;+-------------------------------------------------------------------------
;;  Get a parameter after encoding/decoding a cryptographic message. Called
;;  after the final CryptMsgUpdate. Only the CMSG_CONTENT_PARAM and
;;  CMSG_COMPUTED_HASH_PARAM are valid for an encoded message.
;;
;;  For an encoded HASHED message, the CMSG_COMPUTED_HASH_PARAM can be got
;;  before any CryptMsgUpdates to get its length.
;;
;;  The pvData type definition depends on the dwParamType value.
;;
;;  Elements pointed to by fields in the pvData structure follow the
;;  structure. Therefore, *pcbData may exceed the size of the structure.
;;
;;  Upon input, if *pcbData == 0, then, *pcbData is updated with the length
;;  of the data and the pvData parameter is ignored.
;;
;;  Upon return, *pcbData is updated with the length of the data.
;;
;;  The OBJID BLOBs returned in the pvData structures point to
;;  their still encoded representation. The appropriate functions
;;  must be called to decode the information.
;;
;;  See below for a list of the parameters to get.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgGetParam proto _CType \
	     hCryptMsg: HCRYPTMSG,
	   dwParamType: DWORD,
	       dwIndex: DWORD,
		pvData: PVOID,
	       pcbData: LPDWORD

;;+-------------------------------------------------------------------------
;;  Get parameter types and their corresponding data structure definitions.
;;--------------------------------------------------------------------------
CMSG_TYPE_PARAM		equ 1
CMSG_CONTENT_PARAM	equ 2
CMSG_BARE_CONTENT_PARAM equ 3
CMSG_INNER_CONTENT_TYPE_PARAM equ 4
CMSG_SIGNER_COUNT_PARAM equ 5
CMSG_SIGNER_INFO_PARAM	equ 6
CMSG_SIGNER_CERT_INFO_PARAM equ 7
CMSG_SIGNER_HASH_ALGORITHM_PARAM equ 8
CMSG_SIGNER_AUTH_ATTR_PARAM equ 9
CMSG_SIGNER_UNAUTH_ATTR_PARAM equ 10
CMSG_CERT_COUNT_PARAM	equ 11
CMSG_CERT_PARAM		equ 12
CMSG_CRL_COUNT_PARAM	equ 13
CMSG_CRL_PARAM		equ 14
CMSG_ENVELOPE_ALGORITHM_PARAM equ 15
CMSG_RECIPIENT_COUNT_PARAM equ 17
CMSG_RECIPIENT_INDEX_PARAM equ 18
CMSG_RECIPIENT_INFO_PARAM equ 19
CMSG_HASH_ALGORITHM_PARAM equ 20
CMSG_HASH_DATA_PARAM	equ 21
CMSG_COMPUTED_HASH_PARAM equ 22
CMSG_ENCRYPT_PARAM	equ 26
CMSG_ENCRYPTED_DIGEST	equ 27
CMSG_ENCODED_SIGNER	equ 28
CMSG_ENCODED_MESSAGE	equ 29

;;+-------------------------------------------------------------------------
;;  CMSG_TYPE_PARAM
;;
;;  The type of the decoded message.
;;
;;  pvData points to a DWORD
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CONTENT_PARAM
;;
;;  The encoded content of a cryptographic message. Depending on how the
;;  message was opened, the content is either the whole PKCS#7
;;  message (opened to encode) or the inner content (opened to decode).
;;  In the decode case, the decrypted content is returned, if enveloped.
;;  If not enveloped, and if the inner content is of type DATA, the returned
;;  data is the contents octets of the inner content.
;;
;;  pvData points to the buffer receiving the content bytes
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_BARE_CONTENT_PARAM
;;
;;  The encoded content of an encoded cryptographic message, without the
;;  outer layer of ContentInfo. That is, only the encoding of the
;;  ContentInfo.content field is returned.
;;
;;  pvData points to the buffer receiving the content bytes
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_INNER_CONTENT_TYPE_PARAM
;;
;;  The type of the inner content of a decoded cryptographic message,
;;  in the form of a NULL-terminated object identifier string
;;  (eg. "1.2.840.113549.1.7.1").
;;
;;  pvData points to the buffer receiving the object identifier string
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNER_COUNT_PARAM
;;
;;  Count of signers in a SIGNED or SIGNED_AND_ENVELOPED message
;;
;;  pvData points to a DWORD
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNER_CERT_INFO_PARAM
;;
;;  To get all the signers, repetitively call CryptMsgGetParam, with
;;  dwIndex set to 0 .. SignerCount - 1.
;;
;;  pvData points to a CERT_INFO struct.
;;
;;  Only the following fields have been updated in the CERT_INFO struct:
;;  Issuer and SerialNumber.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNER_INFO_PARAM
;;
;;  To get all the signers, repetitively call CryptMsgGetParam, with
;;  dwIndex set to 0 .. SignerCount - 1.
;;
;;  pvData points to a CMSG_SIGNER_INFO struct.
;;--------------------------------------------------------------------------
CMSG_SIGNER_INFO	STRUC
dwVersion		dd ?
Issuer			CERT_NAME_BLOB <>
SerialNumber		CRYPT_INTEGER_BLOB <>
HashAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
HashEncryptionAlgorithm CRYPT_ALGORITHM_IDENTIFIER <>
EncryptedHash		CRYPT_DATA_BLOB <>
AuthAttrs		CRYPT_ATTRIBUTES <>
UnauthAttrs		CRYPT_ATTRIBUTES <>
CMSG_SIGNER_INFO	ENDS
PCMSG_SIGNER_INFO	typedef ptr CMSG_SIGNER_INFO

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNER_HASH_ALGORITHM_PARAM
;;
;;  This parameter specifies the HashAlgorithm that was used for the signer.
;;
;;  Set dwIndex to iterate through all the signers.
;;
;;  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNER_AUTH_ATTR_PARAM
;;
;;  The authenticated attributes for the signer.
;;
;;  Set dwIndex to iterate through all the signers.
;;
;;  pvData points to a CMSG_ATTR struct.
;;--------------------------------------------------------------------------
CMSG_ATTR		typedef CRYPT_ATTRIBUTES
PCMSG_ATTR		typedef ptr CRYPT_ATTRIBUTES

;;+-------------------------------------------------------------------------
;;  CMSG_SIGNER_UNAUTH_ATTR_PARAM
;;
;;  The unauthenticated attributes for the signer.
;;
;;  Set dwIndex to iterate through all the signers.
;;
;;  pvData points to a CMSG_ATTR struct.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CERT_COUNT_PARAM
;;
;;  Count of certificates in a SIGNED or SIGNED_AND_ENVELOPED message.
;;
;;  pvData points to a DWORD
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CERT_PARAM
;;
;;  To get all the certificates, repetitively call CryptMsgGetParam, with
;;  dwIndex set to 0 .. CertCount - 1.
;;
;;  pvData points to an array of the certificate's encoded bytes.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CRL_COUNT_PARAM
;;
;;  Count of CRLs in a SIGNED or SIGNED_AND_ENVELOPED message.
;;
;;  pvData points to a DWORD
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_CRL_PARAM
;;
;;  To get all the CRLs, repetitively call CryptMsgGetParam, with
;;  dwIndex set to 0 .. CrlCount - 1.
;;
;;  pvData points to an array of the CRL's encoded bytes.
;;--------------------------------------------------------------------------


;;+-------------------------------------------------------------------------
;;  CMSG_ENVELOPE_ALGORITHM_PARAM
;;
;;  The ContentEncryptionAlgorithm that was used in
;;  an ENVELOPED or SIGNED_AND_ENVELOPED message.
;;
;;  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_RECIPIENT_COUNT_PARAM
;;
;;  Count of recipients in an ENVELOPED or SIGNED_AND_ENVELOPED message.
;;
;;  pvData points to a DWORD
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_RECIPIENT_INDEX_PARAM
;;
;;  Index of the recipient used to decrypt an ENVELOPED or SIGNED_AND_ENVELOPED
;;  message.
;;
;;  pvData points to a DWORD
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_RECIPIENT_INFO_PARAM
;;
;;  To get all the recipients, repetitively call CryptMsgGetParam, with
;;  dwIndex set to 0 .. RecipientCount - 1.
;;
;;  pvData points to a CERT_INFO struct.
;;
;;  Only the following fields have been updated in the CERT_INFO struct:
;;  Issuer, SerialNumber and PublicKeyAlgorithm. The PublicKeyAlgorithm
;;  specifies the KeyEncryptionAlgorithm that was used.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_HASH_ALGORITHM_PARAM
;;
;;  The HashAlgorithm in a HASHED message.
;;
;;  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_HASH_DATA_PARAM
;;
;;  The hash in a HASHED message.
;;
;;  pvData points to an array of bytes.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_COMPUTED_HASH_PARAM
;;
;;  The computed hash for a HASHED message.
;;
;;  This may be called for either an encoded or decoded message.
;;  It also may be called before any encoded CryptMsgUpdates to get its length.
;;
;;  pvData points to an array of bytes.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_ENCRYPT_PARAM
;;
;;  The ContentEncryptionAlgorithm that was used in an ENCRYPTED message.
;;
;;  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CMSG_ENCODED_MESSAGE
;;
;;  The full encoded message. This is useful in the case of a decoded
;;  message which has been modified (eg. a signed-data or
;;  signed-and-enveloped-data message which has been countersigned).
;;
;;  pvData points to an array of the message's encoded bytes.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CryptMsg OID installable functions
;;--------------------------------------------------------------------------

;; If *phCryptProv is NULL upon entry, then, if supported, the installable
;; function should acquire a default provider and return. Note, its up
;; to the installable function to release at process detach.
CMSG_OID_GEN_ENCRYPT_KEY_FUNC equ <"CryptMsgDllGenEncryptKey">
;typedef BOOL (WINAPI *PFN_CMSG_GEN_ENCRYPT_KEY) ( HCRYPTPROV		   *phCryptProv, PCRYPT_ALGORITHM_IDENTIFIER	paiEncrypt, PVOID			pvEncryptAuxInfo, PCERT_PUBLIC_KEY_INFO pPublicKeyInfo, HCRYPTKEY		       *phEncryptKey

CMSG_OID_EXPORT_ENCRYPT_KEY_FUNC equ <"CryptMsgDllExportEncryptKey">
;typedef BOOL (WINAPI *PFN_CMSG_EXPORT_ENCRYPT_KEY) ( HCRYPTPROV			hCryptProv, HCRYPTKEY			hEncryptKey, PCERT_PUBLIC_KEY_INFO	pPublicKeyInfo, PBYTE		       pbData, PDWORD		   pcbData

CMSG_OID_IMPORT_ENCRYPT_KEY_FUNC equ <"CryptMsgDllImportEncryptKey">
;typedef BOOL (WINAPI *PFN_CMSG_IMPORT_ENCRYPT_KEY) ( HCRYPTPROV			hCryptProv, DWORD			dwKeySpec, PCRYPT_ALGORITHM_IDENTIFIER	paiEncrypt, PCRYPT_ALGORITHM_IDENTIFIER paiPubKey, PBYTE			pbEncodedKey, DWORD			cbEncodedKey, HCRYPTKEY		       *phEncryptKey


;;+=========================================================================
;;  Certificate Store Data Structures and APIs
;;==========================================================================

;;+-------------------------------------------------------------------------
;;		In its most basic implementation, a cert store is simply a
;;		collection of certificates and/or CRLs. This is the case when
;;		a cert store is opened with all of its certificates and CRLs
;;		coming from a PKCS #7 encoded cryptographic message.
;;
;;		Nonetheless, all cert stores have the following properties:
;;		 - A public key may have more than one certificate in the store.
;;		   For example, a private/public key used for signing may have a
;;		   certificate issued for VISA and another issued for
;;		   Mastercard. Also, when a certificate is renewed there might
;;		   be more than one certificate with the same subject and
;;		   issuer.
;;		 - However, each certificate in the store is uniquely
;;		   identified by its Issuer and SerialNumber.
;;		 - There's an issuer of subject certificate relationship. A
;;		   certificate's issuer is found by doing a match of
;;		   pSubjectCert->Issuer with pIssuerCert->Subject.
;;		   The relationship is verified by using
;;		   the issuer's public key to verify the subject certificate's
;;		   signature. Note, there might be X.509 v3 extensions
;;		   to assist in finding the issuer certificate.
;;		 - Since issuer certificates might be renewed, a subject
;;		   certificate might have more than one issuer certificate.
;;		 - There's an issuer of CRL relationship. An
;;		   issuer's CRL is found by doing a match of
;;		   pIssuerCert->Subject with pCrl->Issuer.
;;		   The relationship is verified by using
;;		   the issuer's public key to verify the CRL's
;;		   signature. Note, there might be X.509 v3 extensions
;;		   to assist in finding the CRL.
;;		 - Since some issuers might support the X.509 v3 delta CRL
;;		   extensions, an issuer might have more than one CRL.
;;		 - The store shouldn't have any redundant certificates or
;;		   CRLs. There shouldn't be two certificates with the same
;;		   Issuer and SerialNumber. There shouldn't be two CRLs with
;;		   the same Issuer, ThisUpdate and NextUpdate.
;;		 - The store has NO policy or trust information. No
;;		   certificates are tagged as being "root". Its up to
;;		   the application to maintain a list of CertIds (Issuer +
;;		   SerialNumber) for certificates it trusts.
;;		 - The store might contain bad certificates and/or CRLs.
;;		   The issuer's signature of a subject certificate or CRL may
;;		   not verify. Certificates or CRLs may not satisfy their
;;		   time validity requirements. Certificates may be
;;		   revoked.
;;
;;		In addition to the certificates and CRLs, properties can be
;;		stored. There are two predefined property IDs for a user
;;		certificate: CERT_KEY_PROV_HANDLE_PROP_ID and
;;		CERT_KEY_PROV_INFO_PROP_ID. The CERT_KEY_PROV_HANDLE_PROP_ID
;;		is a HCRYPTPROV handle to the private key assoicated
;;		with the certificate. The CERT_KEY_PROV_INFO_PROP_ID contains
;;		information to be used to call
;;		CryptAcquireContext and CryptProvSetParam to get a handle
;;		to the private key associated with the certificate.
;;
;;		There exists two more predefined property IDs for certificates
;;		and CRLs, CERT_SHA1_HASH_PROP_ID and CERT_MD5_HASH_PROP_ID.
;;		If these properties don't already exist, then, a hash of the
;;		content is computed. (CERT_HASH_PROP_ID maps to the default
;;		hash algorithm, currently, CERT_SHA1_HASH_PROP_ID).
;;
;;		There are additional APIs for creating certificate and CRL
;;	contexts not in a store (CertCreateCertificateContext and
;;	CertCreateCRLContext).
;;
;;--------------------------------------------------------------------------


HCERTSTORE		typedef PVOID

;;+-------------------------------------------------------------------------
;;  Certificate context.
;;
;;  A certificate context contains both the encoded and decoded representation
;;  of a certificate. A certificate context returned by a cert store function
;;  must be freed by calling the CertFreeCertificateContext function. The
;;  CertDuplicateCertificateContext function can be called to make a duplicate
;;  copy (which also must be freed by calling CertFreeCertificateContext).
;;--------------------------------------------------------------------------
CERT_CONTEXT		STRUC
dwCertEncodingType	dd ?
pbCertEncoded		LPSTR ?
cbCertEncoded		dd ?
pCertInfo		PCERT_INFO ?
hCertStore		HCERTSTORE ?
CERT_CONTEXT		ENDS
PCERT_CONTEXT		typedef ptr CERT_CONTEXT
PCCERT_CONTEXT		typedef ptr CERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  CRL context.
;;
;;  A CRL context contains both the encoded and decoded representation
;;  of a CRL. A CRL context returned by a cert store function
;;  must be freed by calling the CertFreeCRLContext function. The
;;  CertDuplicateCRLContext function can be called to make a duplicate
;;  copy (which also must be freed by calling CertFreeCRLContext).
;;--------------------------------------------------------------------------
CRL_CONTEXT		STRUC
dwCertEncodingType	dd ?
pbCrlEncoded		LPSTR ?
cbCrlEncoded		dd ?
pCrlInfo		PCRL_INFO ?
hCertStore		HCERTSTORE ?
CRL_CONTEXT		ENDS
PCRL_CONTEXT		typedef ptr CRL_CONTEXT
PCCRL_CONTEXT		typedef ptr CRL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Certificate Trust List (CTL) context.
;;
;;  A CTL context contains both the encoded and decoded representation
;;  of a CTL. Also contains an opened HCRYPTMSG handle to the decoded
;;  cryptographic signed message containing the CTL_INFO as its inner content.
;;  pbCtlContent is the encoded inner content of the signed message.
;;
;;  The CryptMsg APIs can be used to extract additional signer information.
;;--------------------------------------------------------------------------
CTL_CONTEXT		STRUC
dwMsgAndCertEncodingType dd ?
pbCtlEncoded		LPSTR ?
cbCtlEncoded		dd ?
pCtlInfo		PCTL_INFO ?
hCertStore		HCERTSTORE ?
hCryptMsg		HCRYPTMSG ?
pbCtlContent		LPSTR ?
cbCtlContent		dd ?
CTL_CONTEXT		ENDS
PCTL_CONTEXT		typedef ptr CTL_CONTEXT
PCCTL_CONTEXT		typedef ptr CTL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Certificate, CRL and CTL property IDs
;;
;;  See CertSetCertificateContextProperty or CertGetCertificateContextProperty
;;  for usage information.
;;--------------------------------------------------------------------------
CERT_KEY_PROV_HANDLE_PROP_ID	equ 1
CERT_KEY_PROV_INFO_PROP_ID	equ 2
CERT_SHA1_HASH_PROP_ID		equ 3
CERT_MD5_HASH_PROP_ID		equ 4
CERT_HASH_PROP_ID		equ CERT_SHA1_HASH_PROP_ID
CERT_KEY_CONTEXT_PROP_ID	equ 5
CERT_KEY_SPEC_PROP_ID		equ 6
CERT_IE30_RESERVED_PROP_ID	equ 7
CERT_PUBKEY_HASH_RESERVED_PROP_ID equ 8
CERT_ENHKEY_USAGE_PROP_ID	equ 9
CERT_CTL_USAGE_PROP_ID		equ CERT_ENHKEY_USAGE_PROP_ID
CERT_NEXT_UPDATE_LOCATION_PROP_ID equ 10
CERT_FRIENDLY_NAME_PROP_ID	equ 11
CERT_PVK_FILE_PROP_ID		equ 12
;; Note, 32 - 34 are reserved for the CERT, CRL and CTL file element IDs.
CERT_FIRST_RESERVED_PROP_ID	equ 13

CERT_LAST_RESERVED_PROP_ID	equ 0x00007FFF
CERT_FIRST_USER_PROP_ID		equ 0x00008000
CERT_LAST_USER_PROP_ID		equ 0x0000FFFF


IS_CERT_HASH_PROP_ID macro X
	exitm<(CERT_SHA1_HASH_PROP_ID EQ (X) OR CERT_MD5_HASH_PROP_ID EQ (X))>
	endm


;;+-------------------------------------------------------------------------
;;  Cryptographic Key Provider Information
;;
;;  CRYPT_KEY_PROV_INFO defines the CERT_KEY_PROV_INFO_PROP_ID's pvData.
;;
;;  The CRYPT_KEY_PROV_INFO fields are passed to CryptAcquireContext
;;  to get a HCRYPTPROV handle. The optional CRYPT_KEY_PROV_PARAM fields are
;;  passed to CryptProvSetParam to further initialize the provider.
;;
;;  The dwKeySpec field identifies the private key to use from the container
;;  For example, AT_KEYEXCHANGE or AT_SIGNATURE.
;;--------------------------------------------------------------------------
CRYPT_KEY_PROV_PARAM	STRUC
dwParam			dd ?
pbData			LPSTR ?
cbData			dd ?
dwFlags			dd ?
CRYPT_KEY_PROV_PARAM	ENDS
PCRYPT_KEY_PROV_PARAM	typedef ptr CRYPT_KEY_PROV_PARAM

CRYPT_KEY_PROV_INFO	STRUC
pwszContainerName	LPWSTR ?
pwszProvName		LPWSTR ?
dwProvType		dd ?
dwFlags			dd ?
cProvParam		dd ?
rgProvParam		PCRYPT_KEY_PROV_PARAM ?
dwKeySpec		dd ?
CRYPT_KEY_PROV_INFO	ENDS
PCRYPT_KEY_PROV_INFO	typedef ptr CRYPT_KEY_PROV_INFO

;;+-------------------------------------------------------------------------
;;  The following flag should be set in the above dwFlags to enable
;;  a CertSetCertificateContextProperty(CERT_KEY_CONTEXT_PROP_ID) after a
;;  CryptAcquireContext is done in the Sign or Decrypt Message functions.
;;
;;  The following define must not collide with any of the
;;  CryptAcquireContext dwFlag defines.
;;--------------------------------------------------------------------------
CERT_SET_KEY_PROV_HANDLE_PROP_ID equ 0x00000001
CERT_SET_KEY_CONTEXT_PROP_ID equ 0x00000001

;;+-------------------------------------------------------------------------
;;  Certificate Key Context
;;
;;  CERT_KEY_CONTEXT defines the CERT_KEY_CONTEXT_PROP_ID's pvData.
;;--------------------------------------------------------------------------
CERT_KEY_CONTEXT	STRUC
cbSize			dd ?	;; sizeof(CERT_KEY_CONTEXT)
hCryptProv		HCRYPTPROV ?
dwKeySpec		dd ?
CERT_KEY_CONTEXT	ENDS
PCERT_KEY_CONTEXT	typedef ptr CERT_KEY_CONTEXT

;;+-------------------------------------------------------------------------
;;  Certificate Store Provider Types
;;--------------------------------------------------------------------------
CERT_STORE_PROV_MSG	equ 1
CERT_STORE_PROV_MEMORY	equ 2
CERT_STORE_PROV_FILE	equ 3
CERT_STORE_PROV_REG	equ 4

CERT_STORE_PROV_PKCS7		equ 5
CERT_STORE_PROV_SERIALIZED	equ 6
CERT_STORE_PROV_FILENAME_A	equ 7
CERT_STORE_PROV_FILENAME_W	equ 8
CERT_STORE_PROV_FILENAME	equ CERT_STORE_PROV_FILENAME_W
CERT_STORE_PROV_SYSTEM_A	equ 9
CERT_STORE_PROV_SYSTEM_W	equ 10
CERT_STORE_PROV_SYSTEM		equ CERT_STORE_PROV_SYSTEM_W

sz_CERT_STORE_PROV_MEMORY	equ <"Memory">
sz_CERT_STORE_PROV_FILENAME_W	equ <"File">
sz_CERT_STORE_PROV_FILENAME	equ sz_CERT_STORE_PROV_FILENAME_W
sz_CERT_STORE_PROV_SYSTEM_W	equ <"System">
sz_CERT_STORE_PROV_SYSTEM	equ sz_CERT_STORE_PROV_SYSTEM_W
sz_CERT_STORE_PROV_PKCS7	equ <"PKCS7">
sz_CERT_STORE_PROV_SERIALIZED	equ <"Serialized">

;;+-------------------------------------------------------------------------
;;  Certificate Store verify/results flags
;;--------------------------------------------------------------------------
CERT_STORE_SIGNATURE_FLAG equ 0x00000001
CERT_STORE_TIME_VALIDITY_FLAG equ 0x00000002
CERT_STORE_REVOCATION_FLAG equ 0x00000004
CERT_STORE_NO_CRL_FLAG	equ 0x00010000
CERT_STORE_NO_ISSUER_FLAG equ 0x00020000


;;+-------------------------------------------------------------------------
;;  Certificate Store open/property flags
;;--------------------------------------------------------------------------
CERT_STORE_NO_CRYPT_RELEASE_FLAG equ 0x00000001
CERT_STORE_READONLY_FLAG equ 0x00008000

;;+-------------------------------------------------------------------------
;;  Certificate Store Provider flags are in the HiWord (0xFFFF0000)
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  Certificate System Store Flag Values
;;--------------------------------------------------------------------------
;; Location of the system store in the registry:
;;  HKEY_CURRENT_USER or HKEY_LOCAL_MACHINE
CERT_SYSTEM_STORE_LOCATION_MASK equ 0x00030000
CERT_SYSTEM_STORE_CURRENT_USER equ 0x00010000
CERT_SYSTEM_STORE_LOCAL_MACHINE equ 0x00020000


;;+-------------------------------------------------------------------------
;;  Open the cert store using the specified store provider.
;;
;;  hCryptProv specifies the crypto provider to use to create the hash
;;  properties or verify the signature of a subject certificate or CRL.
;;  The store doesn't need to use a private
;;  key. If the CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, hCryptProv is
;;  CryptReleaseContext'ed on the final CertCloseStore.
;;
;;  Note, if the open fails, hCryptProv is released if it would have been
;;  released when the store was closed.
;;
;;  If hCryptProv is zero, then, the default provider and container for the
;;  PROV_RSA_FULL provider type is CryptAcquireContext'ed with
;;  CRYPT_VERIFYCONTEXT access. The CryptAcquireContext is deferred until
;;  the first create hash or verify signature. In addition, once acquired,
;;  the default provider isn't released until process exit when crypt32.dll
;;  is unloaded. The acquired default provider is shared across all stores
;;  and threads.
;;
;;  After initializing the store's data structures and optionally acquiring a
;;  default crypt provider, CertOpenStore calls CryptGetOIDFunctionAddress to
;;  get the address of the CRYPT_OID_OPEN_STORE_PROV_FUNC specified by
;;  lpszStoreProvider. Since a store can contain certificates with different
;;  encoding types, CryptGetOIDFunctionAddress is called with dwEncodingType
;;  set to 0 and not the dwEncodingType passed to CertOpenStore.
;;  PFN_CERT_DLL_OPEN_STORE_FUNC specifies the signature of the provider's
;;  open function. This provider open function is called to load the
;;  store's certificates and CRLs. Optionally, the provider may return an
;;  array of functions called before a certificate or CRL is added or deleted
;;  or has a property that is set.
;;
;;  Use of the dwEncodingType parameter is provider dependent. The type
;;  definition for pvPara also depends on the provider.
;;
;;  Store providers are installed or registered via
;;  CryptInstallOIDFunctionAddress or CryptRegisterOIDFunction, where,
;;  dwEncodingType is 0 and pszFuncName is CRYPT_OID_OPEN_STORE_PROV_FUNC.
;;
;;  Here's a list of the predefined provider types (implemented in crypt32.dll):
;;
;;  CERT_STORE_PROV_MSG:
;;	Gets the certificates and CRLs from the specified cryptographic message.
;;	dwEncodingType contains the message and certificate encoding types.
;;	The message's handle is passed in pvPara. Given,
;;	    HCRYPTMSG hCryptMsg; pvPara = (const void *) hCryptMsg;
;;
;;  CERT_STORE_PROV_MEMORY
;;  sz_CERT_STORE_PROV_MEMORY:
;;	Opens a store without any initial certificates or CRLs. pvPara
;;	isn't used.
;;
;;  CERT_STORE_PROV_FILE:
;;	Reads the certificates and CRLs from the specified file. The file's
;;	handle is passed in pvPara. Given,
;;	    HANDLE hFile; pvPara = (const void *) hFile;
;;
;;	For a successful open, the file pointer is advanced past
;;	the certificates and CRLs and their properties read from the file.
;;	Note, only expects a serialized store and not a file containing
;;	either a PKCS #7 signed message or a single encoded certificate.
;;
;;	The hFile isn't closed.
;;
;;  CERT_STORE_PROV_REG:
;;	Reads the certificates and CRLs from the registry. The registry's
;;	key handle is passed in pvPara. Given,
;;	    HKEY hKey; pvPara = (const void *) hKey;
;;
;;	The input hKey isn't closed by the provider. Before returning, the
;;	provider opens/creates "Certificates" and "CRLs" subkeys. These
;;	subkeys remain open until the store is closed.
;;
;;	If CERT_STORE_READONLY_FLAG is set, then, the registry subkeys are
;;	RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry subkeys
;;	are RegCreateKey'ed with KEY_ALL_ACCESS.
;;
;;	This provider returns the array of functions for reading, writing,
;;	deleting and property setting certificates and CRLs.
;;	Any changes to the opened store are immediately pushed through to
;;	the registry. However, if CERT_STORE_READONLY_FLAG is set, then,
;;	writing, deleting or property setting results in a
;;	SetLastError(E_ACCESSDENIED).
;;
;;	Note, all the certificates and CRLs are read from the registry
;;	when the store is opened. The opened store serves as a write through
;;	cache. However, the opened store isn't notified of other changes
;;	made to the registry. Note, RegNotifyChangeKeyValue is supported
;;	on NT but not supported on Windows95.
;;
;;  CERT_STORE_PROV_PKCS7:
;;  sz_CERT_STORE_PROV_PKCS7:
;;	Gets the certificates and CRLs from the encoded PKCS #7 signed message.
;;	dwEncodingType specifies the message and certificate encoding types.
;;	The pointer to the encoded message's blob is passed in pvPara. Given,
;;	    CRYPT_DATA_BLOB EncodedMsg; pvPara = (const void *) &EncodedMsg;
;;
;;	Note, also supports the IE3.0 special version of a
;;	PKCS #7 signed message referred to as a "SPC" formatted message.
;;
;;  CERT_STORE_PROV_SERIALIZED:
;;  sz_CERT_STORE_PROV_SERIALIZED:
;;	Gets the certificates and CRLs from memory containing a serialized
;;	store.	The pointer to the serialized memory blob is passed in pvPara.
;;	Given,
;;	    CRYPT_DATA_BLOB Serialized; pvPara = (const void *) &Serialized;
;;
;;  CERT_STORE_PROV_FILENAME_A:
;;  CERT_STORE_PROV_FILENAME_W:
;;  CERT_STORE_PROV_FILENAME:
;;  sz_CERT_STORE_PROV_FILENAME_W:
;;  sz_CERT_STORE_PROV_FILENAME:
;;	Opens the file and first attempts to read as a serialized store. Then,
;;	as a PKCS #7 signed message. Finally, as a single encoded certificate.
;;	The filename is passed in pvPara. The filename is UNICODE for the
;;	"_W" provider and ASCII for the "_A" provider. For "_W": given,
;;	    LPCWSTR pwszFilename; pvPara = (const void *) pwszFilename;
;;	For "_A": given,
;;	    LPCSTR pszFilename; pvPara = (const void *) pszFilename;
;;
;;	Note, the default (without "_A" or "_W") is unicode.
;;
;;	Note, also supports the reading of the IE3.0 special version of a
;;	PKCS #7 signed message file referred to as a "SPC" formatted file.
;;
;;  CERT_STORE_PROV_SYSTEM_A:
;;  CERT_STORE_PROV_SYSTEM_W:
;;  CERT_STORE_PROV_SYSTEM:
;;  sz_CERT_STORE_PROV_SYSTEM_W:
;;  sz_CERT_STORE_PROV_SYSTEM:
;;	Opens the specified "system" store. Currently, all the system
;;	stores are stored in the registry. The upper word of the dwFlags
;;	parameter is used to specify the location of the system store. It
;;	should be set to either CERT_SYSTEM_STORE_CURRENT_USER for
;;	HKEY_CURRENT_USER or CERT_SYSTEM_STORE_LOCAL_MACHINE for
;;	HKEY_LOCAL_MACHINE.
;;
;;	After opening the registry key associated with the system name,
;;	the CERT_STORE_PROV_REG provider is called to complete the open.
;;
;;	The system store name is passed in pvPara. The name is UNICODE for the
;;	"_W" provider and ASCII for the "_A" provider. For "_W": given,
;;	    LPCWSTR pwszSystemName; pvPara = (const void *) pwszSystemName;
;;	For "_A": given,
;;	    LPCSTR pszSystemName; pvPara = (const void *) pszSystemName;
;;
;;	Note, the default (without "_A" or "_W") is UNICODE.
;;
;;	If CERT_STORE_READONLY_FLAG is set, then, the registry is
;;	RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry is
;;	RegCreateKey'ed with KEY_ALL_ACCESS.
;;
;;	The "root" store is treated differently from the other system
;;	stores. Before a certificate is added to or deleted from the "root"
;;	store, a pop up message box is displayed. The certificate's subject,
;;	issuer, serial number, time validity, sha1 and md5 thumbprints are
;;	displayed. The user is given the option to do the add or delete.
;;	If they don't allow the operation, LastError is set to E_ACCESSDENIED.
;;--------------------------------------------------------------------------
;HCERTSTORE
CertOpenStore proto _CType \
     lpszStoreProvider: LPCSTR,
	dwEncodingType: DWORD,
	    hCryptProv: HCRYPTPROV,
	       dwFlags: DWORD,
		pvPara: PVOID


;;+-------------------------------------------------------------------------
;;  OID Installable Certificate Store Provider Data Structures
;;--------------------------------------------------------------------------

;; Handle returned by the store provider when opened.
HCERTSTOREPROV		typedef PVOID

;; Store Provider OID function's pszFuncName.
CRYPT_OID_OPEN_STORE_PROV_FUNC equ <"CertDllOpenStoreProv">

;; Note, the Store Provider OID function's dwEncodingType is always 0.

;; The following information is returned by the provider when opened. Its
;; zeroed with cbSize set before the provider is called. If the provider
;; doesn't need to be called again after the open it doesn't need to
;; make any updates to the CERT_STORE_PROV_INFO.
CERT_STORE_PROV_INFO	STRUC
cbSize			dd ?
cStoreProvFunc		dd ?
rgpvStoreProvFunc	PVOID ?
hStoreProv		HCERTSTOREPROV ?
dwStoreProvFlags	dd ?
CERT_STORE_PROV_INFO	ENDS
PCERT_STORE_PROV_INFO	typedef ptr CERT_STORE_PROV_INFO

;; Definition of the store provider's open function.
;;
;; *pStoreProvInfo has been zeroed before the call.
;;
;; Note, pStoreProvInfo->cStoreProvFunc should be set last.  Once set,
;; all subsequent store calls, such as CertAddSerializedElementToStore will
;; call the appropriate provider callback function.
;typedef BOOL (WINAPI *PFN_CERT_DLL_OPEN_STORE_PROV_FUNC)( LPCSTR lpszStoreProvider, DWORD dwEncodingType, HCRYPTPROV hCryptProv, DWORD dwFlags, PVOID pvPara, HCERTSTORE hCertStore, PCERT_STORE_PROV_INFO pStoreProvInfo

;; Indices into the store provider's array of callback functions.
;;
;; The provider can implement any subset of the following functions. It
;; sets pStoreProvInfo->cStoreProvFunc to the last index + 1 and any
;; preceding not implemented functions to NULL.
CERT_STORE_PROV_CLOSE_FUNC equ 0
CERT_STORE_PROV_READ_CERT_FUNC equ 1
CERT_STORE_PROV_WRITE_CERT_FUNC equ 2
CERT_STORE_PROV_DELETE_CERT_FUNC equ 3
CERT_STORE_PROV_SET_CERT_PROPERTY_FUNC equ 4
CERT_STORE_PROV_READ_CRL_FUNC equ 5
CERT_STORE_PROV_WRITE_CRL_FUNC equ 6
CERT_STORE_PROV_DELETE_CRL_FUNC equ 7
CERT_STORE_PROV_SET_CRL_PROPERTY_FUNC equ 8
CERT_STORE_PROV_READ_CTL_FUNC equ 9
CERT_STORE_PROV_WRITE_CTL_FUNC equ 10
CERT_STORE_PROV_DELETE_CTL_FUNC equ 11
CERT_STORE_PROV_SET_CTL_PROPERTY_FUNC equ 12

;; Called by CertCloseStore when the store's reference count is
;; decremented to 0.
;typedef void (WINAPI *PFN_CERT_STORE_PROV_CLOSE)( HCERTSTOREPROV hStoreProv, DWORD dwFlags

;; Currently not called directly by the store APIs. However, may be exported
;; to support other providers based on it.
;;
;; Reads the provider's copy of the certificate context. If it exists,
;; creates a new certificate context.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_READ_CERT)( HCERTSTOREPROV hStoreProv, PCCERT_CONTEXT pStoreCertContext, DWORD dwFlags, PCCERT_CONTEXT *ppProvCertContext

CERT_STORE_PROV_WRITE_ADD_FLAG equ 0x1

;; Called by CertAddEncodedCertificateToStore,
;; CertAddCertificateContextToStore or CertAddSerializedElementToStore before
;; adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
;; addition to the encoded certificate, the added pCertContext might also
;; have properties.
;;
;; Returns TRUE if its OK to update the the store.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_WRITE_CERT)( HCERTSTOREPROV hStoreProv, PCCERT_CONTEXT pCertContext, DWORD dwFlags

;; Called by CertDeleteCertificateFromStore before deleting from the
;; store.
;;
;; Returns TRUE if its OK to delete from the store.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_DELETE_CERT)( HCERTSTOREPROV hStoreProv, PCCERT_CONTEXT pCertContext, DWORD dwFlags

;; Called by CertSetCertificateContextProperty before setting the
;; certificate's property. Also called by CertGetCertificateContextProperty,
;; when getting a hash property that needs to be created and then persisted
;; via the set.
;;
;; Upon input, the property hasn't been set for the pCertContext parameter.
;;
;; Returns TRUE if its OK to set the property.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_SET_CERT_PROPERTY)( HCERTSTOREPROV hStoreProv, PCCERT_CONTEXT pCertContext, DWORD dwPropId, DWORD dwFlags, PVOID pvData

;; Currently not called directly by the store APIs. However, may be exported
;; to support other providers based on it.
;;
;; Reads the provider's copy of the CRL context. If it exists,
;; creates a new CRL context.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_READ_CRL)( HCERTSTOREPROV hStoreProv, PCCRL_CONTEXT pStoreCrlContext, DWORD dwFlags, PCCRL_CONTEXT *ppProvCrlContext

;; Called by CertAddEncodedCRLToStore,
;; CertAddCRLContextToStore or CertAddSerializedElementToStore before
;; adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
;; addition to the encoded CRL, the added pCertContext might also
;; have properties.
;;
;; Returns TRUE if its OK to update the the store.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_WRITE_CRL)( HCERTSTOREPROV hStoreProv, PCCRL_CONTEXT pCrlContext, DWORD dwFlags

;; Called by CertDeleteCRLFromStore before deleting from the store.
;;
;; Returns TRUE if its OK to delete from the store.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_DELETE_CRL)( HCERTSTOREPROV hStoreProv, PCCRL_CONTEXT pCrlContext, DWORD dwFlags

;; Called by CertSetCRLContextProperty before setting the
;; CRL's property. Also called by CertGetCRLContextProperty,
;; when getting a hash property that needs to be created and then persisted
;; via the set.
;;
;; Upon input, the property hasn't been set for the pCrlContext parameter.
;;
;; Returns TRUE if its OK to set the property.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_SET_CRL_PROPERTY)( HCERTSTOREPROV hStoreProv, PCCRL_CONTEXT pCrlContext, DWORD dwPropId, DWORD dwFlags, PVOID pvData

;; Currently not called directly by the store APIs. However, may be exported
;; to support other providers based on it.
;;
;; Reads the provider's copy of the CTL context. If it exists,
;; creates a new CTL context.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_READ_CTL)( HCERTSTOREPROV hStoreProv, PCCTL_CONTEXT pStoreCtlContext, DWORD dwFlags, PCCTL_CONTEXT *ppProvCtlContext

;; Called by CertAddEncodedCTLToStore,
;; CertAddCTLContextToStore or CertAddSerializedElementToStore before
;; adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
;; addition to the encoded CTL, the added pCertContext might also
;; have properties.
;;
;; Returns TRUE if its OK to update the the store.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_WRITE_CTL)( HCERTSTOREPROV hStoreProv, PCCTL_CONTEXT pCtlContext, DWORD dwFlags

;; Called by CertDeleteCTLFromStore before deleting from the store.
;;
;; Returns TRUE if its OK to delete from the store.
;typedef BOOL (WINAPI *PFN_CERT_STORE_PROV_DELETE_CTL)( HCERTSTOREPROV hStoreProv, PCCTL_CONTEXT pCtlContext, DWORD dwFlags

;; Called by CertSetCTLContextProperty before setting the
;; CTL's property. Also called by CertGetCTLContextProperty,
;; when getting a hash property that needs to be created and then persisted
;; via the set.
;;
;; Upon input, the property hasn't been set for the pCtlContext parameter.
;;
;; Returns TRUE if its OK to set the property.
;BOOL
PFN_CERT_STORE_PROV_SET_CTL_PROPERTY_T typedef proto _CType \
	  hStoreProv: HCERTSTOREPROV,
	 pCtlContext: PCCTL_CONTEXT,
	    dwPropId: DWORD,
	     dwFlags: DWORD,
	      pvData: PVOID
PFN_CERT_STORE_PROV_SET_CTL_PROPERTY typedef ptr PFN_CERT_STORE_PROV_SET_CTL_PROPERTY_T

;;+-------------------------------------------------------------------------
;;  Duplicate a cert store handle
;;--------------------------------------------------------------------------
;HCERTSTORE
CertDuplicateStore proto _CType \
	    hCertStore: HCERTSTORE

CERT_STORE_SAVE_AS_STORE	equ 1
CERT_STORE_SAVE_AS_PKCS7	equ 2

CERT_STORE_SAVE_TO_FILE		equ 1
CERT_STORE_SAVE_TO_MEMORY	equ 2
CERT_STORE_SAVE_TO_FILENAME_A	equ 3
CERT_STORE_SAVE_TO_FILENAME_W	equ 4
CERT_STORE_SAVE_TO_FILENAME	equ CERT_STORE_SAVE_TO_FILENAME_W

;;+-------------------------------------------------------------------------
;;  Save the cert store. Extended version with lots of options.
;;
;;  According to the dwSaveAs parameter, the store can be saved as a
;;  serialized store (CERT_STORE_SAVE_AS_STORE) containing properties in
;;  addition to encoded certificates, CRLs and CTLs or the store can be saved
;;  as a PKCS #7 signed message (CERT_STORE_SAVE_AS_PKCS7) which doesn't
;;  include the properties or CTLs.
;;
;;  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
;;  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't saved into
;;  a serialized store.
;;
;;  For CERT_STORE_SAVE_AS_PKCS7, the dwEncodingType specifies the message
;;  encoding type. The dwEncodingType parameter isn't used for
;;  CERT_STORE_SAVE_AS_STORE.
;;
;;  The dwFlags parameter currently isn't used and should be set to 0.
;;
;;  The dwSaveTo and pvSaveToPara parameters specify where to save the
;;  store as follows:
;;    CERT_STORE_SAVE_TO_FILE:
;;	Saves to the specified file. The file's handle is passed in
;;	pvSaveToPara. Given,
;;	    HANDLE hFile; pvSaveToPara = (void *) hFile;
;;
;;	For a successful save, the file pointer is positioned after the
;;	last write.
;;
;;    CERT_STORE_SAVE_TO_MEMORY:
;;	Saves to the specified memory blob. The pointer to
;;	the memory blob is passed in pvSaveToPara. Given,
;;	    CRYPT_DATA_BLOB SaveBlob; pvSaveToPara = (void *) &SaveBlob;
;;	Upon entry, the SaveBlob's pbData and cbData need to be initialized.
;;	Upon return, cbData is updated with the actual length.
;;	For a length only calculation, pbData should be set to NULL. If
;;	pbData is non-NULL and cbData isn't large enough, FALSE is returned
;;	with a last error of ERRROR_MORE_DATA.
;;
;;    CERT_STORE_SAVE_TO_FILENAME_A:
;;    CERT_STORE_SAVE_TO_FILENAME_W:
;;    CERT_STORE_SAVE_TO_FILENAME:
;;	Opens the file and saves to it. The filename is passed in pvSaveToPara.
;;	The filename is UNICODE for the "_W" option and ASCII for the "_A"
;;	option. For "_W": given,
;;	    LPCWSTR pwszFilename; pvSaveToPara = (void *) pwszFilename;
;;	For "_A": given,
;;	    LPCSTR pszFilename; pvSaveToPara = (void *) pszFilename;
;;
;;	Note, the default (without "_A" or "_W") is UNICODE.
;;
;;--------------------------------------------------------------------------
;BOOL
CertSaveStore proto _CType \
	    hCertStore: HCERTSTORE,
	dwEncodingType: DWORD,
	      dwSaveAs: DWORD,
	      dwSaveTo: DWORD,
	  pvSaveToPara: PVOID,
	       dwFlags: DWORD

;;+-------------------------------------------------------------------------
;;  Certificate Store close flags
;;--------------------------------------------------------------------------
CERT_CLOSE_STORE_FORCE_FLAG equ 0x00000001
CERT_CLOSE_STORE_CHECK_FLAG equ 0x00000002

;;+-------------------------------------------------------------------------
;;  Close a cert store handle.
;;
;;  There needs to be a corresponding close for each open and duplicate.
;;
;;  Even on the final close, the cert store isn't freed until all of its
;;  certificate and CRL contexts have also been freed.
;;
;;  On the final close, the hCryptProv passed to CertStoreOpen is
;;  CryptReleaseContext'ed.
;;
;;  To force the closure of the store with all of its memory freed, set the
;;  CERT_STORE_CLOSE_FORCE_FLAG. This flag should be set when the caller does
;;  its own reference counting and wants everything to vanish.
;;
;;  To check if all the store's certificates and CRLs have been freed and that
;;  this is the last CertCloseStore, set the CERT_CLOSE_STORE_CHECK_FLAG. If
;;  set and certs, CRLs or stores still need to be freed/closed, FALSE is
;;  returned with LastError set to CRYPT_E_PENDING_CLOSE. Note, for FALSE,
;;  the store is still closed. This is a diagnostic flag.
;;
;;  LastError is preserved unless CERT_CLOSE_STORE_CHECK_FLAG is set and FALSE
;;  is returned.
;;--------------------------------------------------------------------------
;BOOL
CertCloseStore proto _CType \
	    hCertStore: HCERTSTORE,
	       dwFlags: DWORD

;;+-------------------------------------------------------------------------
;;  Get the subject certificate context uniquely identified by its Issuer and
;;  SerialNumber from the store.
;;
;;  If the certificate isn't found, NULL is returned. Otherwise, a pointer to
;;  a read only CERT_CONTEXT is returned. CERT_CONTEXT must be freed by calling
;;  CertFreeCertificateContext. CertDuplicateCertificateContext can be called to make a
;;  duplicate.
;;
;;  The returned certificate might not be valid. Normally, it would be
;;  verified when getting its issuer certificate (CertGetIssuerCertificateFromStore).
;;--------------------------------------------------------------------------
;PCCERT_CONTEXT
CertGetSubjectCertificateFromStore proto _CType \
	    hCertStore: HCERTSTORE,
    dwCertEncodingType: DWORD,
	       pCertId: PCERT_INFO

;;+-------------------------------------------------------------------------
;;  Enumerate the certificate contexts in the store.
;;
;;  If a certificate isn't found, NULL is returned.
;;  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
;;  must be freed by calling CertFreeCertificateContext or is freed when passed as the
;;  pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
;;  can be called to make a duplicate.
;;
;;  pPrevCertContext MUST BE NULL to enumerate the first
;;  certificate in the store. Successive certificates are enumerated by setting
;;  pPrevCertContext to the CERT_CONTEXT returned by a previous call.
;;
;;  NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
;;  this function, even for an error.
;;--------------------------------------------------------------------------
;PCCERT_CONTEXT
CertEnumCertificatesInStore proto _CType \
	    hCertStore: HCERTSTORE,
      pPrevCertContext: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Find the first or next certificate context in the store.
;;
;;  The certificate is found according to the dwFindType and its pvFindPara.
;;  See below for a list of the find types and its parameters.
;;
;;  Currently dwFindFlags is only used for CERT_FIND_SUBJECT_ATTR,
;;  CERT_FIND_ISSUER_ATTR or CERT_FIND_CTL_USAGE. Otherwise, must be set to 0.
;;
;;  Usage of dwCertEncodingType depends on the dwFindType.
;;
;;  If the first or next certificate isn't found, NULL is returned.
;;  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
;;  must be freed by calling CertFreeCertificateContext or is freed when passed as the
;;  pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
;;  can be called to make a duplicate.
;;
;;  pPrevCertContext MUST BE NULL on the first
;;  call to find the certificate. To find the next certificate, the
;;  pPrevCertContext is set to the CERT_CONTEXT returned by a previous call.
;;
;;  NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
;;  this function, even for an error.
;;--------------------------------------------------------------------------
;PCCERT_CONTEXT
CertFindCertificateInStore proto _CType \
	    hCertStore: HCERTSTORE,
    dwCertEncodingType: DWORD,
	   dwFindFlags: DWORD,
	    dwFindType: DWORD,
	    pvFindPara: PVOID,
      pPrevCertContext: PCCERT_CONTEXT


;;+-------------------------------------------------------------------------
;; Certificate comparison functions
;;--------------------------------------------------------------------------
CERT_COMPARE_MASK	equ 0xFFFF
CERT_COMPARE_SHIFT	equ 16
CERT_COMPARE_ANY	equ 0
CERT_COMPARE_SHA1_HASH	equ 1
CERT_COMPARE_NAME	equ 2
CERT_COMPARE_ATTR	equ 3
CERT_COMPARE_MD5_HASH	equ 4
CERT_COMPARE_PROPERTY	equ 5
CERT_COMPARE_PUBLIC_KEY equ 6
CERT_COMPARE_HASH	equ CERT_COMPARE_SHA1_HASH
CERT_COMPARE_NAME_STR_A equ 7
CERT_COMPARE_NAME_STR_W equ 8
CERT_COMPARE_KEY_SPEC	equ 9
CERT_COMPARE_ENHKEY_USAGE equ 10
CERT_COMPARE_CTL_USAGE	equ CERT_COMPARE_ENHKEY_USAGE

;;+-------------------------------------------------------------------------
;;  dwFindType
;;
;;  The dwFindType definition consists of two components:
;;   - comparison function
;;   - certificate information flag
;;--------------------------------------------------------------------------
CERT_FIND_ANY		equ (CERT_COMPARE_ANY SHL CERT_COMPARE_SHIFT)
CERT_FIND_SHA1_HASH	equ (CERT_COMPARE_SHA1_HASH SHL CERT_COMPARE_SHIFT)
CERT_FIND_MD5_HASH	equ (CERT_COMPARE_MD5_HASH SHL CERT_COMPARE_SHIFT)
CERT_FIND_HASH		equ CERT_FIND_SHA1_HASH
CERT_FIND_PROPERTY	equ (CERT_COMPARE_PROPERTY SHL CERT_COMPARE_SHIFT)
CERT_FIND_PUBLIC_KEY	equ (CERT_COMPARE_PUBLIC_KEY SHL CERT_COMPARE_SHIFT)
CERT_FIND_SUBJECT_NAME	equ (CERT_COMPARE_NAME SHL CERT_COMPARE_SHIFT OR CERT_INFO_SUBJECT_FAG)
CERT_FIND_SUBJECT_ATTR	equ (CERT_COMPARE_ATTR SHL CERT_COMPARE_SHIFT OR CERT_INFO_SUBJECT_FAG)
CERT_FIND_ISSUER_NAME	equ (CERT_COMPARE_NAME SHL CERT_COMPARE_SHIFT OR CERT_INFO_ISSUER_FAG)
CERT_FIND_ISSUER_ATTR	equ (CERT_COMPARE_ATTR SHL CERT_COMPARE_SHIFT OR CERT_INFO_ISSUER_FAG)
CERT_FIND_SUBJECT_STR_A equ (CERT_COMPARE_NAME_STR_A SHL CERT_COMPARE_SHIFT OR CERT_INFO_SUBJECT_FAG)
CERT_FIND_SUBJECT_STR_W equ (CERT_COMPARE_NAME_STR_W SHL CERT_COMPARE_SHIFT OR CERT_INFO_SUBJECT_FAG)
CERT_FIND_SUBJECT_STR	equ CERT_FIND_SUBJECT_STR_W
CERT_FIND_ISSUER_STR_A	equ (CERT_COMPARE_NAME_STR_A SHL CERT_COMPARE_SHIFT OR CERT_INFO_ISSUER_FAG)
CERT_FIND_ISSUER_STR_W	equ (CERT_COMPARE_NAME_STR_W SHL CERT_COMPARE_SHIFT OR CERT_INFO_ISSUER_FAG)
CERT_FIND_ISSUER_STR	equ CERT_FIND_ISSUER_STR_W
CERT_FIND_KEY_SPEC	equ (CERT_COMPARE_KEY_SPEC SHL CERT_COMPARE_SHIFT)
CERT_FIND_ENHKEY_USAGE	equ (CERT_COMPARE_ENHKEY_USAGE SHL CERT_COMPARE_SHIFT)
CERT_FIND_CTL_USAGE	equ CERT_FIND_ENHKEY_USAGE



;;+-------------------------------------------------------------------------
;;  CERT_FIND_ANY
;;
;;  Find any certificate.
;;
;;  pvFindPara isn't used.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_HASH
;;
;;  Find a certificate with the specified hash.
;;
;;  pvFindPara points to a CRYPT_HASH_BLOB.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_PROPERTY
;;
;;  Find a certificate having the specified property.
;;
;;  pvFindPara points to a DWORD containing the PROP_ID
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_PUBLIC_KEY
;;
;;  Find a certificate matching the specified public key.
;;
;;  pvFindPara points to a CERT_PUBLIC_KEY_INFO containing the public key
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_SUBJECT_NAME
;;  CERT_FIND_ISSUER_NAME
;;
;;  Find a certificate with the specified subject/issuer name. Does an exact
;;  match of the entire name.
;;
;;  Restricts search to certificates matching the dwCertEncodingType.
;;
;;  pvFindPara points to a CERT_NAME_BLOB.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_SUBJECT_ATTR
;;  CERT_FIND_ISSUER_ATTR
;;
;;  Find a certificate with the specified subject/issuer attributes.
;;
;;  Compares the attributes in the subject/issuer name with the
;;  Relative Distinguished Name's (CERT_RDN) array of attributes specified in
;;  pvFindPara. The comparison iterates through the CERT_RDN attributes and looks
;;  for an attribute match in any of the subject/issuer's RDNs.
;;
;;  The CERT_RDN_ATTR fields can have the following special values:
;;    pszObjId == NULL		    - ignore the attribute object identifier
;;    dwValueType == RDN_ANY_TYPE   - ignore the value type
;;    Value.pbData == NULL	    - match any value
;;
;;  Currently only an exact, case sensitive match is supported.
;;
;;  CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set in dwFindFlags if the RDN was
;;  initialized with unicode strings as for
;;  CryptEncodeObject(X509_UNICODE_NAME).
;;
;;  Restricts search to certificates matching the dwCertEncodingType.
;;
;;  pvFindPara points to a CERT_RDN (defined in wincert.h).
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_SUBJECT_STR_A
;;  CERT_FIND_SUBJECT_STR_W | CERT_FIND_SUBJECT_STR
;;  CERT_FIND_ISSUER_STR_A
;;  CERT_FIND_ISSUER_STR_W  | CERT_FIND_ISSUER_STR
;;
;;  Find a certificate containing the specified subject/issuer name string.
;;
;;  First, the certificate's subject/issuer is converted to a name string
;;  via CertNameToStrA/CertNameToStrW(CERT_SIMPLE_NAME_STR). Then, a
;;  case insensitive substring within string match is performed.
;;
;;  Restricts search to certificates matching the dwCertEncodingType.
;;
;;  For *_STR_A, pvFindPara points to a null terminated character string.
;;  For *_STR_W, pvFindPara points to a null terminated wide character string.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_KEY_SPEC
;;
;;  Find a certificate having a CERT_KEY_SPEC_PROP_ID property matching
;;  the specified KeySpec.
;;
;;  pvFindPara points to a DWORD containing the KeySpec.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CERT_FIND_ENHKEY_USAGE
;;
;;  Find a certificate having the szOID_ENHANCED_KEY_USAGE extension or
;;  the CERT_ENHKEY_USAGE_PROP_ID and matching the specified pszUsageIdentifers.
;;
;;  pvFindPara points to a CERT_ENHKEY_USAGE data structure. If pvFindPara
;;  is NULL or CERT_ENHKEY_USAGE's cUsageIdentifier is 0, then, matches any
;;  certificate having enhanced key usage.
;;
;;  The CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG can be set in dwFindFlags to
;;  also match a certificate without either the extension or property.
;;
;;  If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set in dwFindFlags, finds
;;  certificates without the key usage extension or property. Setting this
;;  flag takes precedence over pvFindPara being NULL.
;;
;;  If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only does a match
;;  using the extension. If pvFindPara is NULL or cUsageIdentifier is set to
;;  0, finds certificates having the extension. If
;;  CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
;;  without the extension. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
;;  certificates without the extension.
;;
;;  If the CERT_FIND_EXT_PROP_ENHKEY_USAGE_FLAG is set, then, only does a match
;;  using the property. If pvFindPara is NULL or cUsageIdentifier is set to
;;  0, finds certificates having the property. If
;;  CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
;;  without the property. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
;;  certificates without the property.
;;--------------------------------------------------------------------------

CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG	equ 0x1
CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG	equ 0x2
CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG	equ 0x4
CERT_FIND_NO_ENHKEY_USAGE_FLAG		equ 0x8

CERT_FIND_OPTIONAL_CTL_USAGE_FLAG	equ CERT_FIND_OPTIONAL_ENHKEY_USAGE_FAG
CERT_FIND_EXT_ONLY_CTL_USAGE_FLAG	equ CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FAG
CERT_FIND_PROP_ONLY_CTL_USAGE_FLAG	equ CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FAG
CERT_FIND_NO_CTL_USAGE_FLAG		equ CERT_FIND_NO_ENHKEY_USAGE_FAG

;;+-------------------------------------------------------------------------
;;  Get the certificate context from the store for the first or next issuer
;;  of the specified subject certificate. Perform the enabled
;;  verification checks on the subject. (Note, the checks are on the subject
;;  using the returned issuer certificate.)
;;
;;  If the first or next issuer certificate isn't found, NULL is returned.
;;  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
;;  must be freed by calling CertFreeCertificateContext or is freed when passed as the
;;  pPrevIssuerContext on a subsequent call. CertDuplicateCertificateContext
;;  can be called to make a duplicate.
;;
;;  For a self signed subject certificate, NULL is returned with LastError set
;;  to CERT_STORE_SELF_SIGNED. The enabled verification checks are still done.
;;
;;  The pSubjectContext may have been obtained from this store, another store
;;  or created by the caller application. When created by the caller, the
;;  CertCreateCertificateContext function must have been called.
;;
;;  An issuer may have multiple certificates. This may occur when the validity
;;  period is about to change. pPrevIssuerContext MUST BE NULL on the first
;;  call to get the issuer. To get the next certificate for the issuer, the
;;  pPrevIssuerContext is set to the CERT_CONTEXT returned by a previous call.
;;
;;  NOTE: a NON-NULL pPrevIssuerContext is always CertFreeCertificateContext'ed by
;;  this function, even for an error.
;;
;;  The following flags can be set in *pdwFlags to enable verification checks
;;  on the subject certificate context:
;;	CERT_STORE_SIGNATURE_FLAG     - use the public key in the returned
;;					issuer certificate to verify the
;;					signature on the subject certificate.
;;					Note, if pSubjectContext->hCertStore ==
;;					hCertStore, the store provider might
;;					be able to eliminate a redo of
;;					the signature verify.
;;	CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
;;					its within the subject certificate's
;;					validity period
;;	CERT_STORE_REVOCATION_FLAG    - check if the subject certificate is on
;;					the issuer's revocation list
;;
;;  If an enabled verification check fails, then, its flag is set upon return.
;;  If CERT_STORE_REVOCATION_FLAG was enabled and the issuer doesn't have a
;;  CRL in the store, then, CERT_STORE_NO_CRL_FLAG is set in addition to
;;  the CERT_STORE_REVOCATION_FLAG.
;;
;;  If CERT_STORE_SIGNATURE_FLAG or CERT_STORE_REVOCATION_FLAG is set, then,
;;  CERT_STORE_NO_ISSUER_FLAG is set if it doesn't have an issuer certificate
;;  in the store.
;;
;;  For a verification check failure, a pointer to the issuer's CERT_CONTEXT
;;  is still returned and SetLastError isn't updated.
;;--------------------------------------------------------------------------
;PCCERT_CONTEXT
CertGetIssuerCertificateFromStore proto _CType \
	    hCertStore: HCERTSTORE,
       pSubjectContext: PCCERT_CONTEXT,
    pPrevIssuerContext: PCCERT_CONTEXT,
	      pdwFlags: LPDWORD

;;+-------------------------------------------------------------------------
;;  Perform the enabled verification checks on the subject certificate
;;  using the issuer. Same checks and flags definitions as for the above
;;  CertGetIssuerCertificateFromStore.
;;
;;  If you are only checking CERT_STORE_TIME_VALIDITY_FLAG, then, the
;;  issuer can be NULL.
;;
;;  For a verification check failure, SUCCESS is still returned.
;;--------------------------------------------------------------------------
;BOOL
CertVerifySubjectCertificateContext proto _CType \
	      pSubject: PCCERT_CONTEXT,
	       pIssuer: PCCERT_CONTEXT,
	      pdwFlags: LPDWORD

;;+-------------------------------------------------------------------------
;;  Duplicate a certificate context
;;--------------------------------------------------------------------------
;PCCERT_CONTEXT
CertDuplicateCertificateContext proto _CType \
	  pCertContext: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Create a certificate context from the encoded certificate. The created
;;  context isn't put in a store.
;;
;;  Makes a copy of the encoded certificate in the created context.
;;
;;  If unable to decode and create the certificate context, NULL is returned.
;;  Otherwise, a pointer to a read only CERT_CONTEXT is returned.
;;  CERT_CONTEXT must be freed by calling CertFreeCertificateContext.
;;  CertDuplicateCertificateContext can be called to make a duplicate.
;;
;;  CertSetCertificateContextProperty and CertGetCertificateContextProperty can be called
;;  to store properties for the certificate.
;;--------------------------------------------------------------------------
;PCCERT_CONTEXT
CertCreateCertificateContext proto _CType \
    dwCertEncodingType: DWORD,
	 pbCertEncoded: LPBYTE,
	 cbCertEncoded: DWORD

;;+-------------------------------------------------------------------------
;;  Free a certificate context
;;
;;  There needs to be a corresponding free for each context obtained by a
;;  get, find, duplicate or create.
;;--------------------------------------------------------------------------
;BOOL
CertFreeCertificateContext proto _CType \
	  pCertContext: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Set the property for the specified certificate context.
;;
;;  The type definition for pvData depends on the dwPropId value. There are
;;  five predefined types:
;;	CERT_KEY_PROV_HANDLE_PROP_ID - a HCRYPTPROV for the certificate's
;;	private key is passed in pvData. Updates the hCryptProv field
;;	of the CERT_KEY_CONTEXT_PROP_ID. If the CERT_KEY_CONTEXT_PROP_ID
;;	doesn't exist, its created with all the other fields zeroed out. If
;;	CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, HCRYPTPROV is implicitly
;;	released when either the property is set to NULL or on the final
;;	free of the CertContext.
;;
;;	CERT_KEY_PROV_INFO_PROP_ID - a PCRYPT_KEY_PROV_INFO for the certificate's
;;	private key is passed in pvData.
;;
;;	CERT_SHA1_HASH_PROP_ID -
;;	CERT_MD5_HASH_PROP_ID  - normally, either property is implicitly
;;	set by doing a CertGetCertificateContextProperty. pvData points to a
;;	CRYPT_HASH_BLOB.
;;
;;	CERT_KEY_CONTEXT_PROP_ID - a PCERT_KEY_CONTEXT for the certificate's
;;	private key is passed in pvData. The CERT_KEY_CONTEXT contains both the
;;	hCryptProv and dwKeySpec for the private key.
;;	See the CERT_KEY_PROV_HANDLE_PROP_ID for more information about
;;	the hCryptProv field and dwFlags settings. Note, more fields may
;;	be added for this property. The cbSize field value will be adjusted
;;	accordingly.
;;
;;	CERT_KEY_SPEC_PROP_ID - the dwKeySpec for the private key. pvData
;;	points to a DWORD containing the KeySpec
;;
;;	CERT_ENHKEY_USAGE_PROP_ID - enhanced key usage definition for the
;;	certificate. pvData points to a CRYPT_DATA_BLOB containing an
;;	ASN.1 encoded CERT_ENHKEY_USAGE (encoded via
;;	CryptEncodeObject(X509_ENHANCED_KEY_USAGE).
;;
;;	CERT_NEXT_UPDATE_LOCATION_PROP_ID - location of the next update.
;;	Currently only applicable to CTLs. pvData points to a CRYPT_DATA_BLOB
;;	containing an ASN.1 encoded CERT_ALT_NAME_INFO (encoded via
;;	CryptEncodeObject(X509_ALTERNATE_NAME)).
;;
;;	CERT_FRIENDLY_NAME_PROP_ID - friendly name for the cert, CRL or CTL.
;;	pvData points to a CRYPT_DATA_BLOB. pbData is a pointer to a NULL
;;	terminated unicode, wide character string.
;;	cbData = (wcslen((LPWSTR) pbData) + 1) * sizeof(WCHAR).
;;
;;  For all the other PROP_IDs: an encoded PCRYPT_DATA_BLOB is passed in pvData.
;;
;;  If the property already exists, then, the old value is deleted and silently
;;  replaced. Setting, pvData to NULL, deletes the property.
;;--------------------------------------------------------------------------
;BOOL
CertSetCertificateContextProperty proto _CType \
	  pCertContext: PCCERT_CONTEXT,
	      dwPropId: DWORD,
	       dwFlags: DWORD,
		pvData: PVOID

;;+-------------------------------------------------------------------------
;;  Get the property for the specified certificate context.
;;
;;  For CERT_KEY_PROV_HANDLE_PROP_ID, pvData points to a HCRYPTPROV.
;;
;;  For CERT_KEY_PROV_INFO_PROP_ID, pvData points to a CRYPT_KEY_PROV_INFO structure.
;;  Elements pointed to by fields in the pvData structure follow the
;;  structure. Therefore, *pcbData may exceed the size of the structure.
;;
;;  For CERT_KEY_CONTEXT_PROP_ID, pvData points to a CERT_KEY_CONTEXT structure.
;;
;;  For CERT_KEY_SPEC_PROP_ID, pvData points to a DWORD containing the KeySpec.
;;  If the CERT_KEY_CONTEXT_PROP_ID exists, the KeySpec is obtained from there.
;;  Otherwise, if the CERT_KEY_PROV_INFO_PROP_ID exists, its the source
;;  of the KeySpec.
;;
;;  For CERT_SHA1_HASH_PROP_ID or CERT_MD5_HASH_PROP_ID, if the hash
;;  doesn't already exist, then, its computed via CryptHashCertificate()
;;  and then set. pvData points to the computed hash. Normally, the length
;;  is 20 bytes for SHA and 16 for MD5.
;;
;;  For all other PROP_IDs, pvData points to an encoded array of bytes.
;;--------------------------------------------------------------------------
;BOOL
CertGetCertificateContextProperty proto _CType \
	  pCertContext: PCCERT_CONTEXT,
	      dwPropId: DWORD,
		pvData: PVOID,
	       pcbData: LPDWORD

;;+-------------------------------------------------------------------------
;;  Enumerate the properties for the specified certificate context.
;;
;;  To get the first property, set dwPropId to 0. The ID of the first
;;  property is returned. To get the next property, set dwPropId to the
;;  ID returned by the last call. To enumerate all the properties continue
;;  until 0 is returned.
;;
;;  CertGetCertificateContextProperty is called to get the property's data.
;;
;;  Note, since, the CERT_KEY_PROV_HANDLE_PROP_ID and CERT_KEY_SPEC_PROP_ID
;;  properties are stored as fields in the CERT_KEY_CONTEXT_PROP_ID
;;  property, they aren't enumerated individually.
;;--------------------------------------------------------------------------
;DWORD
CertEnumCertificateContextProperties proto _CType \
	  pCertContext: PCCERT_CONTEXT,
	      dwPropId: DWORD

;;+-------------------------------------------------------------------------
;;  Get the first or next CRL context from the store for the specified
;;  issuer certificate. Perform the enabled verification checks on the CRL.
;;
;;  If the first or next CRL isn't found, NULL is returned.
;;  Otherwise, a pointer to a read only CRL_CONTEXT is returned. CRL_CONTEXT
;;  must be freed by calling CertFreeCRLContext. However, the free must be
;;  pPrevCrlContext on a subsequent call. CertDuplicateCRLContext
;;  can be called to make a duplicate.
;;
;;  The pIssuerContext may have been obtained from this store, another store
;;  or created by the caller application. When created by the caller, the
;;  CertCreateCertificateContext function must have been called.
;;
;;  If pIssuerContext == NULL, finds all the CRLs in the store.
;;
;;  An issuer may have multiple CRLs. For example, it generates delta CRLs
;;  using a X.509 v3 extension. pPrevCrlContext MUST BE NULL on the first
;;  call to get the CRL. To get the next CRL for the issuer, the
;;  pPrevCrlContext is set to the CRL_CONTEXT returned by a previous call.
;;
;;  NOTE: a NON-NULL pPrevCrlContext is always CertFreeCRLContext'ed by
;;  this function, even for an error.
;;
;;  The following flags can be set in *pdwFlags to enable verification checks
;;  on the returned CRL:
;;	CERT_STORE_SIGNATURE_FLAG     - use the public key in the
;;					issuer's certificate to verify the
;;					signature on the returned CRL.
;;					Note, if pIssuerContext->hCertStore ==
;;					hCertStore, the store provider might
;;					be able to eliminate a redo of
;;					the signature verify.
;;	CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
;;					its within the CRL's ThisUpdate and
;;					NextUpdate validity period.
;;
;;  If an enabled verification check fails, then, its flag is set upon return.
;;
;;  If pIssuerContext == NULL, then, an enabled CERT_STORE_SIGNATURE_FLAG
;;  always fails and the CERT_STORE_NO_ISSUER_FLAG is also set.
;;
;;  For a verification check failure, a pointer to the first or next
;;  CRL_CONTEXT is still returned and SetLastError isn't updated.
;;--------------------------------------------------------------------------
;PCCRL_CONTEXT
CertGetCRLFromStore proto _CType \
	    hCertStore: HCERTSTORE,
	pIssuerContext: PCCERT_CONTEXT,
       pPrevCrlContext: PCCRL_CONTEXT,
	      pdwFlags: LPDWORD


;;+-------------------------------------------------------------------------
;;  Duplicate a CRL context
;;--------------------------------------------------------------------------
;PCCRL_CONTEXT
CertDuplicateCRLContext proto _CType \
	   pCrlContext: PCCRL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Create a CRL context from the encoded CRL. The created
;;  context isn't put in a store.
;;
;;  Makes a copy of the encoded CRL in the created context.
;;
;;  If unable to decode and create the CRL context, NULL is returned.
;;  Otherwise, a pointer to a read only CRL_CONTEXT is returned.
;;  CRL_CONTEXT must be freed by calling CertFreeCRLContext.
;;  CertDuplicateCRLContext can be called to make a duplicate.
;;
;;  CertSetCRLContextProperty and CertGetCRLContextProperty can be called
;;  to store properties for the CRL.
;;--------------------------------------------------------------------------
;PCCRL_CONTEXT
CertCreateCRLContext proto _CType \
    dwCertEncodingType: DWORD,
	  pbCrlEncoded: LPBYTE,
	  cbCrlEncoded: DWORD

;;+-------------------------------------------------------------------------
;;  Free a CRL context
;;
;;  There needs to be a corresponding free for each context obtained by a
;;  get, duplicate or create.
;;--------------------------------------------------------------------------
;BOOL
CertFreeCRLContext proto _CType \
	   pCrlContext: PCCRL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Set the property for the specified CRL context.
;;
;;  Same Property Ids and semantics as CertSetCertificateContextProperty.
;;--------------------------------------------------------------------------
;BOOL
CertSetCRLContextProperty proto _CType \
	   pCrlContext: PCCRL_CONTEXT,
	      dwPropId: DWORD,
	       dwFlags: DWORD,
		pvData: PVOID

;;+-------------------------------------------------------------------------
;;  Get the property for the specified CRL context.
;;
;;  Same Property Ids and semantics as CertGetCertificateContextProperty.
;;
;;  CERT_SHA1_HASH_PROP_ID or CERT_MD5_HASH_PROP_ID is the predefined
;;  property of most interest.
;;--------------------------------------------------------------------------
;BOOL
CertGetCRLContextProperty proto _CType \
	   pCrlContext: PCCRL_CONTEXT,
	      dwPropId: DWORD,
		pvData: PVOID,
	       pcbData: LPDWORD

;;+-------------------------------------------------------------------------
;;  Enumerate the properties for the specified CRL context.
;;
;;  To get the first property, set dwPropId to 0. The ID of the first
;;  property is returned. To get the next property, set dwPropId to the
;;  ID returned by the last call. To enumerate all the properties continue
;;  until 0 is returned.
;;
;;  CertGetCRLContextProperty is called to get the property's data.
;;--------------------------------------------------------------------------
;DWORD
CertEnumCRLContextProperties proto _CType \
	   pCrlContext: PCCRL_CONTEXT,
	      dwPropId: DWORD

;;+-------------------------------------------------------------------------
;; Add certificate/CRL, encoded, context or element disposition values.
;;--------------------------------------------------------------------------
CERT_STORE_ADD_NEW		equ 1
CERT_STORE_ADD_USE_EXISTING	equ 2
CERT_STORE_ADD_REPLACE_EXISTING equ 3
CERT_STORE_ADD_ALWAYS		equ 4

;;+-------------------------------------------------------------------------
;;  Add the encoded certificate to the store according to the specified
;;  disposition action.
;;
;;  Makes a copy of the encoded certificate before adding to the store.
;;
;;  dwAddDispostion specifies the action to take if the certificate
;;  already exists in the store. This parameter must be one of the following
;;  values:
;;    CERT_STORE_ADD_NEW
;;	Fails if the certificate already exists in the store. LastError
;;	is set to CRYPT_E_EXISTS.
;;    CERT_STORE_ADD_USE_EXISTING
;;	If the certifcate already exists, then, its used and if ppCertContext
;;	is non-NULL, the existing context is duplicated.
;;    CERT_STORE_ADD_REPLACE_EXISTING
;;	If the certificate already exists, then, the existing certificate
;;	context is deleted before creating and adding the new context.
;;    CERT_STORE_ADD_ALWAYS
;;	No check is made to see if the certificate already exists. A
;;	new certificate context is always created. This may lead to
;;	duplicates in the store.
;;
;;  CertGetSubjectCertificateFromStore is called to determine if the
;;  certificate already exists in the store.
;;
;;  ppCertContext can be NULL, indicating the caller isn't interested
;;  in getting the CERT_CONTEXT of the added or existing certificate.
;;--------------------------------------------------------------------------
;BOOL
CertAddEncodedCertificateToStore proto _CType \
	    hCertStore: HCERTSTORE,
    dwCertEncodingType: DWORD,
	 pbCertEncoded: LPBYTE,
	 cbCertEncoded: DWORD,
      dwAddDisposition: DWORD,
	 ppCertContext: ptr PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Add the certificate context to the store according to the specified
;;  disposition action.
;;
;;  In addition to the encoded certificate, the context's properties are
;;  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
;;  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
;;
;;  Makes a copy of the certificate context before adding to the store.
;;
;;  dwAddDispostion specifies the action to take if the certificate
;;  already exists in the store. This parameter must be one of the following
;;  values:
;;    CERT_STORE_ADD_NEW
;;	Fails if the certificate already exists in the store. LastError
;;	is set to CRYPT_E_EXISTS.
;;    CERT_STORE_ADD_USE_EXISTING
;;	If the certifcate already exists, then, its used and if ppStoreContext
;;	is non-NULL, the existing context is duplicated. Iterates
;;	through pCertContext's properties and only copies the properties
;;	that don't already exist. The SHA1 and MD5 hash properties aren't
;;	copied.
;;    CERT_STORE_ADD_REPLACE_EXISTING
;;	If the certificate already exists, then, the existing certificate
;;	context is deleted before creating and adding a new context.
;;	Properties are copied before doing the add.
;;    CERT_STORE_ADD_ALWAYS
;;	No check is made to see if the certificate already exists. A
;;	new certificate context is always created and added. This may lead to
;;	duplicates in the store. Properties are
;;	copied before doing the add.
;;
;;  CertGetSubjectCertificateFromStore is called to determine if the
;;  certificate already exists in the store.
;;
;;  ppStoreContext can be NULL, indicating the caller isn't interested
;;  in getting the CERT_CONTEXT of the added or existing certificate.
;;--------------------------------------------------------------------------
;BOOL
CertAddCertificateContextToStore proto _CType \
	    hCertStore: HCERTSTORE,
	  pCertContext: PCCERT_CONTEXT,
      dwAddDisposition: DWORD,
	ppStoreContext: ptr PCCERT_CONTEXT


;;+-------------------------------------------------------------------------
;;  Certificate Store Context Types
;;--------------------------------------------------------------------------
CERT_STORE_CERTIFICATE_CONTEXT equ 1
CERT_STORE_CRL_CONTEXT	equ 2
CERT_STORE_CTL_CONTEXT	equ 3

;;+-------------------------------------------------------------------------
;;  Certificate Store Context Bit Flags
;;--------------------------------------------------------------------------
CERT_STORE_ALL_CONTEXT_FLAG equ ( NOT 0UL)
CERT_STORE_CERTIFICATE_CONTEXT_FLAG equ (1 SHL CERT_STORE_CERTIFICATE_CONTEXT)
CERT_STORE_CRL_CONTEXT_FLAG equ (1 SHL CERT_STORE_CRL_CONTEXT)
CERT_STORE_CTL_CONTEXT_FLAG equ (1 SHL CERT_STORE_CTL_CONTEXT)

;;+-------------------------------------------------------------------------
;;  Add the serialized certificate or CRL element to the store.
;;
;;  The serialized element contains the encoded certificate, CRL or CTL and
;;  its properties, such as, CERT_KEY_PROV_INFO_PROP_ID.
;;
;;  If hCertStore is NULL, creates a certificate, CRL or CTL context not
;;  residing in any store.
;;
;;  dwAddDispostion specifies the action to take if the certificate or CRL
;;  already exists in the store. See CertAddCertificateContextToStore for a
;;  list of and actions taken.
;;
;;  dwFlags currently isn't used and should be set to 0.
;;
;;  dwContextTypeFlags specifies the set of allowable contexts. For example, to
;;  add either a certificate or CRL, set dwContextTypeFlags to:
;;	CERT_STORE_CERTIFICATE_CONTEXT_FLAG | CERT_STORE_CRL_CONTEXT_FLAG
;;
;;  *pdwContextType is updated with the type of the context returned in
;;  *ppvContxt. pdwContextType or ppvContext can be NULL, indicating the
;;  caller isn't interested in getting the output. If *ppvContext is
;;  returned it must be freed by calling CertFreeCertificateContext or
;;  CertFreeCRLContext.
;;--------------------------------------------------------------------------
;BOOL
CertAddSerializedElementToStore proto _CType \
	    hCertStore: HCERTSTORE,
	     pbElement: LPBYTE,
	     cbElement: DWORD,
      dwAddDisposition: DWORD,
	       dwFlags: DWORD,
    dwContextTypeFlags: DWORD,
	pdwContextType: LPDWORD,
	    ppvContext: PVOID

;;+-------------------------------------------------------------------------
;;  Delete the specified certificate from the store.
;;
;;  All subsequent gets or finds for the certificate will fail. However,
;;  memory allocated for the certificate isn't freed until all of its contexts
;;  have also been freed.
;;
;;  The pCertContext is obtained from a get, enum, find or duplicate.
;;
;;  Some store provider implementations might also delete the issuer's CRLs
;;  if this is the last certificate for the issuer in the store.
;;
;;  NOTE: the pCertContext is always CertFreeCertificateContext'ed by
;;  this function, even for an error.
;;--------------------------------------------------------------------------
;BOOL
CertDeleteCertificateFromStore proto _CType \
	  pCertContext: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Add the encoded CRL to the store according to the specified
;;  disposition option.
;;
;;  Makes a copy of the encoded CRL before adding to the store.
;;
;;  dwAddDispostion specifies the action to take if the CRL
;;  already exists in the store. See CertAddEncodedCertificateToStore for a
;;  list of and actions taken.
;;
;;  Compares the CRL's Issuer to determine if the CRL already exists in the
;;  store.
;;
;;  ppCrlContext can be NULL, indicating the caller isn't interested
;;  in getting the CRL_CONTEXT of the added or existing CRL.
;;--------------------------------------------------------------------------
;BOOL
CertAddEncodedCRLToStore proto _CType \
	    hCertStore: HCERTSTORE,
    dwCertEncodingType: DWORD,
	  pbCrlEncoded: LPBYTE,
	  cbCrlEncoded: DWORD,
      dwAddDisposition: DWORD,
	  ppCrlContext: PCCRL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Add the CRL context to the store according to the specified
;;  disposition option.
;;
;;  In addition to the encoded CRL, the context's properties are
;;  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
;;  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
;;
;;  Makes a copy of the encoded CRL before adding to the store.
;;
;;  dwAddDispostion specifies the action to take if the CRL
;;  already exists in the store. See CertAddCertificateContextToStore for a
;;  list of and actions taken.
;;
;;  Compares the CRL's Issuer, ThisUpdate and NextUpdate to determine
;;  if the CRL already exists in the store.
;;
;;  ppStoreContext can be NULL, indicating the caller isn't interested
;;  in getting the CRL_CONTEXT of the added or existing CRL.
;;--------------------------------------------------------------------------
;BOOL
CertAddCRLContextToStore proto _CType \
	    hCertStore: HCERTSTORE,
	   pCrlContext: PCCRL_CONTEXT,
      dwAddDisposition: DWORD,
	ppStoreContext: PCCRL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Delete the specified CRL from the store.
;;
;;  All subsequent gets for the CRL will fail. However,
;;  memory allocated for the CRL isn't freed until all of its contexts
;;  have also been freed.
;;
;;  The pCrlContext is obtained from a get or duplicate.
;;
;;  NOTE: the pCrlContext is always CertFreeCRLContext'ed by
;;  this function, even for an error.
;;--------------------------------------------------------------------------
;BOOL
CertDeleteCRLFromStore proto _CType \
	   pCrlContext: PCCRL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Serialize the certificate context's encoded certificate and its
;;  properties.
;;--------------------------------------------------------------------------
;BOOL
CertSerializeCertificateStoreElement proto _CType \
	  pCertContext: PCCERT_CONTEXT,
	       dwFlags: DWORD,
	     pbElement: LPBYTE,
	    pcbElement: LPDWORD


;;+-------------------------------------------------------------------------
;;  Serialize the CRL context's encoded CRL and its properties.
;;--------------------------------------------------------------------------
;BOOL
CertSerializeCRLStoreElement proto _CType \
	   pCrlContext: PCCRL_CONTEXT,
	       dwFlags: DWORD,
	     pbElement: LPBYTE,
	    pcbElement: LPDWORD


;;+=========================================================================
;;  Certificate Trust List (CTL) Store Data Structures and APIs
;;==========================================================================

;;+-------------------------------------------------------------------------
;;  Duplicate a CTL context
;;--------------------------------------------------------------------------
;PCCTL_CONTEXT
CertDuplicateCTLContext proto _CType \
	   pCtlContext: PCCTL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Create a CTL context from the encoded CTL. The created
;;  context isn't put in a store.
;;
;;  Makes a copy of the encoded CTL in the created context.
;;
;;  If unable to decode and create the CTL context, NULL is returned.
;;  Otherwise, a pointer to a read only CTL_CONTEXT is returned.
;;  CTL_CONTEXT must be freed by calling CertFreeCTLContext.
;;  CertDuplicateCTLContext can be called to make a duplicate.
;;
;;  CertSetCTLContextProperty and CertGetCTLContextProperty can be called
;;  to store properties for the CTL.
;;--------------------------------------------------------------------------
;PCCTL_CONTEXT
CertCreateCTLContext proto _CType \
dwMsgAndCertEncodingType: DWORD,
	  pbCtlEncoded: LPBYTE,
	  cbCtlEncoded: DWORD

;;+-------------------------------------------------------------------------
;;  Free a CTL context
;;
;;  There needs to be a corresponding free for each context obtained by a
;;  get, duplicate or create.
;;--------------------------------------------------------------------------
;BOOL
CertFreeCTLContext proto _CType \
	   pCtlContext: PCCTL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Set the property for the specified CTL context.
;;
;;  Same Property Ids and semantics as CertSetCertificateContextProperty.
;;--------------------------------------------------------------------------
;BOOL
CertSetCTLContextProperty proto _CType \
	   pCtlContext: PCCTL_CONTEXT,
	      dwPropId: DWORD,
	       dwFlags: DWORD,
		pvData: PVOID

;;+-------------------------------------------------------------------------
;;  Get the property for the specified CTL context.
;;
;;  Same Property Ids and semantics as CertGetCertificateContextProperty.
;;
;;  CERT_SHA1_HASH_PROP_ID or CERT_NEXT_UPDATE_LOCATION_PROP_ID are the
;;  predefined properties of most interest.
;;--------------------------------------------------------------------------
;BOOL
CertGetCTLContextProperty proto _CType \
	   pCtlContext: PCCTL_CONTEXT,
	      dwPropId: DWORD,
		pvData: PVOID,
	       pcbData: LPDWORD

;;+-------------------------------------------------------------------------
;;  Enumerate the properties for the specified CTL context.
;;--------------------------------------------------------------------------
;DWORD
CertEnumCTLContextProperties proto _CType \
	   pCtlContext: PCCTL_CONTEXT,
	      dwPropId: DWORD

;;+-------------------------------------------------------------------------
;;  Enumerate the CTL contexts in the store.
;;
;;  If a CTL isn't found, NULL is returned.
;;  Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
;;  must be freed by calling CertFreeCTLContext or is freed when passed as the
;;  pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
;;  can be called to make a duplicate.
;;
;;  pPrevCtlContext MUST BE NULL to enumerate the first
;;  CTL in the store. Successive CTLs are enumerated by setting
;;  pPrevCtlContext to the CTL_CONTEXT returned by a previous call.
;;
;;  NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
;;  this function, even for an error.
;;--------------------------------------------------------------------------
;PCCTL_CONTEXT
CertEnumCTLsInStore proto _CType \
	    hCertStore: HCERTSTORE,
       pPrevCtlContext: PCCTL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Attempt to find the specified subject in the CTL.
;;
;;  For CTL_CERT_SUBJECT_TYPE, pvSubject points to a CERT_CONTEXT. The CTL's
;;  SubjectAlgorithm is examined to determine the representation of the
;;  subject's identity. Initially, only SHA1 or MD5 hash will be supported.
;;  The appropriate hash property is obtained from the CERT_CONTEXT.
;;
;;  For CTL_ANY_SUBJECT_TYPE, pvSubject points to the CTL_ANY_SUBJECT_INFO
;;  structure which contains the SubjectAlgorithm to be matched in the CTL
;;  and the SubjectIdentifer to be matched in one of the CTL entries.
;;
;;  The certificate's hash or the CTL_ANY_SUBJECT_INFO's SubjectIdentifier
;;  is used as the key in searching the subject entries. A binary
;;  memory comparison is done between the key and the entry's SubjectIdentifer.
;;
;;  dwEncodingType isn't used for either of the above SubjectTypes.
;;--------------------------------------------------------------------------
;PCTL_ENTRY
CertFindSubjectInCTL proto _CType \
	dwEncodingType: DWORD,
	 dwSubjectType: DWORD,
	     pvSubject: PVOID,
	   pCtlContext: PCCTL_CONTEXT,
	       dwFlags: DWORD

;; Subject Types:
;;  CTL_ANY_SUBJECT_TYPE, pvSubject points to following CTL_ANY_SUBJECT_INFO.
;;  CTL_CERT_SUBJECT_TYPE, pvSubject points to CERT_CONTEXT.
CTL_ANY_SUBJECT_TYPE	equ 1
CTL_CERT_SUBJECT_TYPE	equ 2

CTL_ANY_SUBJECT_INFO	STRUC
SubjectAlgorithm	CRYPT_ALGORITHM_IDENTIFIER <>
SubjectIdentifier	CRYPT_DATA_BLOB <>
CTL_ANY_SUBJECT_INFO	ENDS
PCTL_ANY_SUBJECT_INFO	typedef ptr CTL_ANY_SUBJECT_INFO

;;+-------------------------------------------------------------------------
;;  Find the first or next CTL context in the store.
;;
;;  The CTL is found according to the dwFindType and its pvFindPara.
;;  See below for a list of the find types and its parameters.
;;
;;  Currently dwFindFlags isn't used and must be set to 0.
;;
;;  Usage of dwMsgAndCertEncodingType depends on the dwFindType.
;;
;;  If the first or next CTL isn't found, NULL is returned.
;;  Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
;;  must be freed by calling CertFreeCTLContext or is freed when passed as the
;;  pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
;;  can be called to make a duplicate.
;;
;;  pPrevCtlContext MUST BE NULL on the first
;;  call to find the CTL. To find the next CTL, the
;;  pPrevCtlContext is set to the CTL_CONTEXT returned by a previous call.
;;
;;  NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
;;  this function, even for an error.
;;--------------------------------------------------------------------------
;PCCTL_CONTEXT
CertFindCTLInStore proto _CType \
	    hCertStore: HCERTSTORE,
dwMsgAndCertEncodingType: DWORD,
	   dwFindFlags: DWORD,
	    dwFindType: DWORD,
	    pvFindPara: PVOID,
       pPrevCtlContext: PCCTL_CONTEXT

CTL_FIND_ANY		equ 0
CTL_FIND_SHA1_HASH	equ 1
CTL_FIND_MD5_HASH	equ 2
CTL_FIND_USAGE		equ 3
CTL_FIND_SUBJECT	equ 4

CTL_FIND_USAGE_PARA	STRUC
cbSize			dd ?
SubjectUsage		CTL_USAGE <>	;; optional
ListIdentifier		CRYPT_DATA_BLOB <>	;; optional
pSigner			PCERT_INFO ?	;; optional
CTL_FIND_USAGE_PARA	ENDS
PCTL_FIND_USAGE_PARA	typedef ptr CTL_FIND_USAGE_PARA

CTL_FIND_NO_LIST_ID_CBDATA	equ 0xFFFFFFFF
CTL_FIND_NO_SIGNER_PTR		equ 0xFFFFFFFF

CTL_FIND_SAME_USAGE_FLAG equ 0x1


CTL_FIND_SUBJECT_PARA	STRUC
cbSize			dd ?
pUsagePara		PCTL_FIND_USAGE_PARA ?	;; optional
dwSubjectType		dd ?
pvSubject		PVOID ?
CTL_FIND_SUBJECT_PARA	ENDS
PCTL_FIND_SUBJECT_PARA	typedef ptr CTL_FIND_SUBJECT_PARA


;;+-------------------------------------------------------------------------
;;  CTL_FIND_ANY
;;
;;  Find any CTL.
;;
;;  pvFindPara isn't used.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CTL_FIND_SHA1_HASH
;;  CTL_FIND_MD5_HASH
;;
;;  Find a CTL with the specified hash.
;;
;;  pvFindPara points to a CRYPT_HASH_BLOB.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CTL_FIND_USAGE
;;
;;  Find a CTL having the specified usage identifiers, list identifier or
;;  signer. The CertEncodingType of the signer is obtained from the
;;  dwMsgAndCertEncodingType parameter.
;;
;;  pvFindPara points to a CTL_FIND_USAGE_PARA data structure. The
;;  SubjectUsage.cUsageIdentifer can be 0 to match any usage. The
;;  ListIdentifier.cbData can be 0 to match any list identifier. To only match
;;  CTLs without a ListIdentifier, cbData must be set to
;;  CTL_FIND_NO_LIST_ID_CBDATA. pSigner can be NULL to match any signer. Only
;;  the Issuer and SerialNumber fields of the pSigner's PCERT_INFO are used.
;;  To only match CTLs without a signer, pSigner must be set to
;;  CTL_FIND_NO_SIGNER_PTR.
;;
;;  The CTL_FIND_SAME_USAGE_FLAG can be set in dwFindFlags to
;;  only match CTLs with the same usage identifiers. CTLs having additional
;;  usage identifiers aren't matched. For example, if only "1.2.3" is specified
;;  in CTL_FIND_USAGE_PARA, then, for a match, the CTL must only contain
;;  "1.2.3" and not any additional usage identifers.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  CTL_FIND_SUBJECT
;;
;;  Find a CTL having the specified subject. CertFindSubjectInCTL can be
;;  called to get a pointer to the subject's entry in the CTL.  pUsagePara can
;;  optionally be set to enable the above CTL_FIND_USAGE matching.
;;
;;  pvFindPara points to a CTL_FIND_SUBJECT_PARA data structure.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  Add the encoded CTL to the store according to the specified
;;  disposition option.
;;
;;  Makes a copy of the encoded CTL before adding to the store.
;;
;;  dwAddDispostion specifies the action to take if the CTL
;;  already exists in the store. See CertAddEncodedCertificateToStore for a
;;  list of and actions taken.
;;
;;  Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
;;  to determine if the CTL already exists in the store.
;;
;;  ppCtlContext can be NULL, indicating the caller isn't interested
;;  in getting the CTL_CONTEXT of the added or existing CTL.
;;--------------------------------------------------------------------------
;BOOL
CertAddEncodedCTLToStore proto _CType \
	    hCertStore: HCERTSTORE,
dwMsgAndCertEncodingType: DWORD,
	  pbCtlEncoded: LPBYTE,
	  cbCtlEncoded: DWORD,
      dwAddDisposition: DWORD,
	  ppCtlContext: PCCTL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Add the CTL context to the store according to the specified
;;  disposition option.
;;
;;  In addition to the encoded CTL, the context's properties are
;;  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
;;  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
;;
;;  Makes a copy of the encoded CTL before adding to the store.
;;
;;  dwAddDispostion specifies the action to take if the CTL
;;  already exists in the store. See CertAddCertificateContextToStore for a
;;  list of and actions taken.
;;
;;  Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
;;  to determine if the CTL already exists in the store.
;;
;;  ppStoreContext can be NULL, indicating the caller isn't interested
;;  in getting the CTL_CONTEXT of the added or existing CTL.
;;--------------------------------------------------------------------------
;BOOL
CertAddCTLContextToStore proto _CType \
	    hCertStore: HCERTSTORE,
	   pCtlContext: PCCTL_CONTEXT,
      dwAddDisposition: DWORD,
	ppStoreContext: PCCTL_CONTEXT

;;+-------------------------------------------------------------------------
;;  Serialize the CTL context's encoded CTL and its properties.
;;--------------------------------------------------------------------------
;BOOL
CertSerializeCTLStoreElement proto _CType \
	   pCtlContext: PCCTL_CONTEXT,
	       dwFlags: DWORD,
	     pbElement: LPBYTE,
	    pcbElement: LPDWORD

;;+-------------------------------------------------------------------------
;;  Delete the specified CTL from the store.
;;
;;  All subsequent gets for the CTL will fail. However,
;;  memory allocated for the CTL isn't freed until all of its contexts
;;  have also been freed.
;;
;;  The pCtlContext is obtained from a get or duplicate.
;;
;;  NOTE: the pCtlContext is always CertFreeCTLContext'ed by
;;  this function, even for an error.
;;--------------------------------------------------------------------------
;BOOL
CertDeleteCTLFromStore proto _CType \
	   pCtlContext: PCCTL_CONTEXT


;;+=========================================================================
;;  Enhanced Key Usage Helper Functions
;;==========================================================================

;;+-------------------------------------------------------------------------
;;  Get the enhanced key usage extension or property from the certificate
;;  and decode.
;;
;;  If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
;;  extension.
;;
;;  If the CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
;;  property.
;;--------------------------------------------------------------------------
;BOOL
CertGetEnhancedKeyUsage proto _CType \
	  pCertContext: PCCERT_CONTEXT,
	       dwFlags: DWORD,
		pUsage: PCERT_ENHKEY_USAGE,
	      pcbUsage: LPDWORD

;;+-------------------------------------------------------------------------
;;  Set the enhanced key usage property for the certificate.
;;--------------------------------------------------------------------------
;BOOL
CertSetEnhancedKeyUsage proto _CType \
	  pCertContext: PCCERT_CONTEXT,
		pUsage: PCERT_ENHKEY_USAGE

;;+-------------------------------------------------------------------------
;;  Add the usage identifier to the certificate's enhanced key usage property.
;;--------------------------------------------------------------------------
;BOOL
CertAddEnhancedKeyUsageIdentifier proto _CType \
	  pCertContext: PCCERT_CONTEXT,
    pszUsageIdentifier: LPCSTR


;;+-------------------------------------------------------------------------
;;  Remove the usage identifier from the certificate's enhanced key usage
;;  property.
;;--------------------------------------------------------------------------
;BOOL
CertRemoveEnhancedKeyUsageIdentifier proto _CType \
	  pCertContext: PCCERT_CONTEXT,
    pszUsageIdentifier: LPCSTR


;;+=========================================================================
;;  Cryptographic Message helper functions for verifying and signing a
;;  CTL.
;;==========================================================================

;;+-------------------------------------------------------------------------
;;  Get and verify the signer of a cryptographic message.
;;
;;  To verify a CTL, the hCryptMsg is obtained from the CTL_CONTEXT's
;;  hCryptMsg field.
;;
;;  If CMSG_TRUSTED_SIGNER_FLAG is set, then, treat the Signer stores as being
;;  trusted and only search them to find the certificate corresponding to the
;;  signer's issuer and serial number.  Otherwise, the SignerStores are
;;  optionally provided to supplement the message's store of certificates.
;;  If a signer certificate is found, its public key is used to verify
;;  the message signature. The CMSG_SIGNER_ONLY_FLAG can be set to
;;  return the signer without doing the signature verify.
;;
;;  If CMSG_USE_SIGNER_INDEX_FLAG is set, then, only get the signer specified
;;  by *pdwSignerIndex. Otherwise, iterate through all the signers
;;  until a signer verifies or no more signers.
;;
;;  For a verified signature, *ppSigner is updated with certificate context
;;  of the signer and *pdwSignerIndex is updated with the index of the signer.
;;  ppSigner and/or pdwSignerIndex can be NULL, indicating the caller isn't
;;  interested in getting the CertContext and/or index of the signer.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgGetAndVerifySigner proto _CType \
	     hCryptMsg: HCRYPTMSG,
	  cSignerStore: DWORD,
	rghSignerStore: ptr HCERTSTORE,
	       dwFlags: DWORD,
	      ppSigner: PCCERT_CONTEXT,
	pdwSignerIndex: LPDWORD

CMSG_TRUSTED_SIGNER_FLAG	equ 0x1
CMSG_SIGNER_ONLY_FLAG		equ 0x2
CMSG_USE_SIGNER_INDEX_FLAG	equ 0x4

;;+-------------------------------------------------------------------------
;;  Sign an encoded CTL.
;;
;;  The pbCtlContent can be obtained via a CTL_CONTEXT's pbCtlContent
;;  field or via a CryptEncodeObject(PKCS_CTL).
;;--------------------------------------------------------------------------
;BOOL
CryptMsgSignCTL proto _CType \
     dwMsgEncodingType: DWORD,
	  pbCtlContent: LPBYTE,
	  cbCtlContent: DWORD,
	     pSignInfo: PCMSG_SIGNED_ENCODE_INFO,
	       dwFlags: DWORD,
	     pbEncoded: LPBYTE,
	    pcbEncoded: LPDWORD

;;+-------------------------------------------------------------------------
;;  Encode the CTL and create a signed message containing the encoded CTL.
;;--------------------------------------------------------------------------
;BOOL
CryptMsgEncodeAndSignCTL proto _CType \
     dwMsgEncodingType: DWORD,
	      pCtlInfo: PCTL_INFO,
	     pSignInfo: PCMSG_SIGNED_ENCODE_INFO,
	       dwFlags: DWORD,
	     pbEncoded: LPBYTE,
	    pcbEncoded: LPDWORD


;;+=========================================================================
;;  Certificate Verify CTL Usage Data Structures and APIs
;;==========================================================================

CTL_VERIFY_USAGE_PARA	STRUC
cbSize			dd ?
ListIdentifier		CRYPT_DATA_BLOB <>	;; OPTIONAL
cCtlStore		dd ?
rghCtlStore		PVOID ?;HCERTSTORE ? ;; OPTIONAL
cSignerStore		dd ?
rghSignerStore		PVOID ?;HCERTSTORE ?	;; OPTIONAL
CTL_VERIFY_USAGE_PARA	ENDS
PCTL_VERIFY_USAGE_PARA	typedef ptr CTL_VERIFY_USAGE_PARA

CTL_VERIFY_USAGE_STATUS	 STRUC
cbSize			dd ?
dwError			dd ?
dwFlags			dd ?
ppCtl			PCCTL_CONTEXT ? ;;OUT OPTIONAL
dwCtlEntryIndex		dd ?
ppSigner		PCCERT_CONTEXT ?	;;OUT OPTIONAL
dwSignerIndex		dd ?
CTL_VERIFY_USAGE_STATUS ENDS
PCTL_VERIFY_USAGE_STATUS typedef ptr CTL_VERIFY_USAGE_STATUS

CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG	equ 0x1
CERT_VERIFY_TRUSTED_SIGNERS_FLAG	equ 0x2
CERT_VERIFY_NO_TIME_CHECK_FLAG		equ 0x4
CERT_VERIFY_ALLOW_MORE_USAGE_FLAG	equ 0x8

CERT_VERIFY_UPDATED_CTL_FLAG		equ 0x1

;;+-------------------------------------------------------------------------
;;  Verify that a subject is trusted for the specified usage by finding a
;;  signed and time valid CTL with the usage identifiers and containing the
;;  the subject. A subject can be identified by either its certificate context
;;  or any identifier such as its SHA1 hash.
;;
;;  See CertFindSubjectInCTL for definition of dwSubjectType and pvSubject
;;  parameters.
;;
;;  Via pVerifyUsagePara, the caller can specify the stores to be searched
;;  to find the CTL. The caller can also specify the stores containing
;;  acceptable CTL signers. By setting the ListIdentifier, the caller
;;  can also restrict to a particular signer CTL list.
;;
;;  Via pVerifyUsageStatus, the CTL containing the subject, the subject's
;;  index into the CTL's array of entries, and the signer of the CTL
;;  are returned. If the caller is not interested, ppCtl and ppSigner can be set
;;  to NULL. Returned contexts must be freed via the store's free context APIs.
;;
;;  If the CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG isn't set, then, a time
;;  invalid CTL in one of the CtlStores may be replaced. When replaced, the
;;  CERT_VERIFY_UPDATED_CTL_FLAG is set in pVerifyUsageStatus->dwFlags.
;;
;;  If the CERT_VERIFY_TRUSTED_SIGNERS_FLAG is set, then, only the
;;  SignerStores specified in pVerifyUsageStatus are searched to find
;;  the signer. Otherwise, the SignerStores provide additional sources
;;  to find the signer's certificate.
;;
;;  If CERT_VERIFY_NO_TIME_CHECK_FLAG is set, then, the CTLs aren't checked
;;  for time validity.
;;
;;  If CERT_VERIFY_ALLOW_MORE_USAGE_FLAG is set, then, the CTL may contain
;;  additional usage identifiers than specified by pSubjectUsage. Otherwise,
;;  the found CTL will contain the same usage identifers and no more.
;;
;;  CertVerifyCTLUsage will be implemented as a dispatcher to OID installable
;;  functions. First, it will try to find an OID function matching the first
;;  usage object identifier in the pUsage sequence. Next, it will dispatch
;;  to the default CertDllVerifyCTLUsage functions.
;;
;;  If the subject is trusted for the specified usage, then, TRUE is
;;  returned. Otherwise, FALSE is returned with dwError set to one of the
;;  following:
;;	CRYPT_E_NO_VERIFY_USAGE_DLL
;;	CRYPT_E_NO_VERIFY_USAGE_CHECK
;;	CRYPT_E_VERIFY_USAGE_OFFLINE
;;	CRYPT_E_NOT_IN_CTL
;;	CRYPT_E_NO_TRUSTED_SIGNER
;;--------------------------------------------------------------------------
;BOOL
CertVerifyCTLUsage proto _CType \
	dwEncodingType: DWORD,
	 dwSubjectType: DWORD,
	     pvSubject: PVOID,
	 pSubjectUsage: PCTL_USAGE,
	       dwFlags: DWORD,
      pVerifyUsagePara: PCTL_VERIFY_USAGE_PARA,
    pVerifyUsageStatus: PCTL_VERIFY_USAGE_STATUS


;;+=========================================================================
;;  Certificate Revocation Data Structures and APIs
;;==========================================================================

;;+-------------------------------------------------------------------------
;;  The following data structure may be passed to CertVerifyRevocation to
;;  assist in finding the issuer of the context to be verified.
;;
;;  When pIssuerCert is specified, pIssuerCert is the issuer of
;;  rgpvContext[cContext - 1].
;;
;;  When cCertStore and rgCertStore are specified, these stores may contain
;;  an issuer certificate.
;;--------------------------------------------------------------------------
CERT_REVOCATION_PARA	STRUC
cbSize			dd ?
pIssuerCert		PCCERT_CONTEXT ?
cCertStore		dd ?
rgCertStore		PVOID ?;HCERTSTORE ?
CERT_REVOCATION_PARA	ENDS
PCERT_REVOCATION_PARA	typedef ptr CERT_REVOCATION_PARA


;;+-------------------------------------------------------------------------
;;  The following data structure is returned by CertVerifyRevocation to
;;  specify the status of the revoked or unchecked context. Review the
;;  following CertVerifyRevocation comments for details.
;;
;;  Upon input to CertVerifyRevocation, cbSize must be set to a size
;;  >= sizeof(CERT_REVOCATION_STATUS). Otherwise, CertVerifyRevocation
;;  returns FALSE and sets LastError to E_INVALIDARG.
;;
;;  Upon input to the installed or registered CRYPT_OID_VERIFY_REVOCATION_FUNC
;;  functions, the dwIndex, dwError and dwReason have been zero'ed.
;;--------------------------------------------------------------------------
CERT_REVOCATION_STATUS	STRUC
cbSize			dd ?
dwIndex			dd ?
dwError			dd ?
dwReason		dd ?
CERT_REVOCATION_STATUS	ENDS
PCERT_REVOCATION_STATUS typedef ptr CERT_REVOCATION_STATUS


;;+-------------------------------------------------------------------------
;;  Verifies the array of contexts for revocation. The dwRevType parameter
;;  indicates the type of the context data structure passed in rgpvContext.
;;  Currently only the revocation of certificates is defined.
;;
;;  If the CERT_VERIFY_REV_CHAIN_FLAG flag is set, then, CertVerifyRevocation
;;  is verifying a chain of certs where, rgpvContext[i + 1] is the issuer
;;  of rgpvContext[i]. Otherwise, CertVerifyRevocation makes no assumptions
;;  about the order of the contexts.
;;
;;  To assist in finding the issuer, the pRevPara may optionally be set. See
;;  the CERT_REVOCATION_PARA data structure for details.
;;
;;  The contexts must contain enough information to allow the
;;  installable or registered revocation DLLs to find the revocation server. For
;;  certificates, this information would normally be conveyed in an
;;  extension such as the IETF's AuthorityInfoAccess extension.
;;
;;  CertVerifyRevocation returns TRUE if all of the contexts were successfully
;;  checked and none were revoked. Otherwise, returns FALSE and updates the
;;  returned pRevStatus data structure as follows:
;;    dwIndex
;;	Index of the first context that was revoked or unable to
;;	be checked for revocation
;;    dwError
;;	Error status. LastError is also set to this error status.
;;	dwError can be set to one of the following error codes defined
;;	in winerror.h:
;;	  ERROR_SUCCESS - good context
;;	  CRYPT_E_REVOKED - context was revoked. dwReason contains the
;;	     reason for revocation
;;	  CRYPT_E_REVOCATION_OFFLINE - unable to connect to the
;;	     revocation server
;;	  CRYPT_E_NOT_IN_REVOCATION_DATABASE - the context to be checked
;;	     was not found in the revocation server's database.
;;	  CRYPT_E_NO_REVOCATION_CHECK - the called revocation function
;;	     wasn't able to do a revocation check on the context
;;	  CRYPT_E_NO_REVOCATION_DLL - no installed or registered Dll was
;;	     found to verify revocation
;;    dwReason
;;	The dwReason is currently only set for CRYPT_E_REVOKED and contains
;;	the reason why the context was revoked. May be one of the following
;;	CRL reasons defined by the CRL Reason Code extension ("2.5.29.21")
;;	    CRL_REASON_UNSPECIFIED		0
;;	    CRL_REASON_KEY_COMPROMISE		1
;;	    CRL_REASON_CA_COMPROMISE		2
;;	    CRL_REASON_AFFILIATION_CHANGED	3
;;	    CRL_REASON_SUPERSEDED		4
;;	    CRL_REASON_CESSATION_OF_OPERATION	5
;;	    CRL_REASON_CERTIFICATE_HOLD		6
;;
;;  For each entry in rgpvContext, CertVerifyRevocation iterates
;;  through the CRYPT_OID_VERIFY_REVOCATION_FUNC
;;  function set's list of installed DEFAULT functions.
;;  CryptGetDefaultOIDFunctionAddress is called with pwszDll = NULL. If no
;;  installed functions are found capable of doing the revocation verification,
;;  CryptVerifyRevocation iterates through CRYPT_OID_VERIFY_REVOCATION_FUNC's
;;  list of registered DEFAULT Dlls. CryptGetDefaultOIDDllList is called to
;;  get the list. CryptGetDefaultOIDFunctionAddress is called to load the Dll.
;;
;;  The called functions have the same signature as CertVerifyRevocation. A
;;  called function returns TRUE if it was able to successfully check all of
;;  the contexts and none were revoked. Otherwise, the called function returns
;;  FALSE and updates pRevStatus. dwIndex is set to the index of
;;  the first context that was found to be revoked or unable to be checked.
;;  dwError and LastError are updated. For CRYPT_E_REVOKED, dwReason
;;  is updated. Upon input to the called function, dwIndex, dwError and
;;  dwReason have been zero'ed. cbSize has been checked to be >=
;;  sizeof(CERT_REVOCATION_STATUS).
;;
;;  If the called function returns FALSE, and dwError isn't set to
;;  CRYPT_E_REVOKED, then, CertVerifyRevocation either continues on to the
;;  next DLL in the list for a returned dwIndex of 0 or for a returned
;;  dwIndex > 0, restarts the process of finding a verify function by
;;  advancing the start of the context array to the returned dwIndex and
;;  decrementing the count of remaining contexts.
;;--------------------------------------------------------------------------
;BOOL
CertVerifyRevocation proto _CType \
	dwEncodingType: DWORD,
	     dwRevType: DWORD,
	      cContext: DWORD,
	   rgpvContext: PVOID,
	       dwFlags: DWORD,
	      pRevPara: PCERT_REVOCATION_PARA,
	    pRevStatus: PCERT_REVOCATION_STATUS

;;+-------------------------------------------------------------------------
;;  Revocation types
;;--------------------------------------------------------------------------
CERT_CONTEXT_REVOCATION_TYPE equ 1

;;+-------------------------------------------------------------------------
;;  When the following flag is set, rgpvContext[] consists of a chain
;;  of certificates, where rgpvContext[i + 1] is the issuer of rgpvContext[i].
;;--------------------------------------------------------------------------
CERT_VERIFY_REV_CHAIN_FLAG equ 0x1

;;+-------------------------------------------------------------------------
;;  CERT_CONTEXT_REVOCATION_TYPE
;;
;;  pvContext points to a const CERT_CONTEXT.
;;--------------------------------------------------------------------------

;;+=========================================================================
;;  Certificate Helper APIs
;;==========================================================================


;;+-------------------------------------------------------------------------
;;  Compare two multiple byte integer blobs to see if they are identical.
;;
;;  Before doing the comparison, leading zero bytes are removed from a
;;  positive number and leading 0xFF bytes are removed from a negative
;;  number.
;;
;;  The multiple byte integers are treated as Little Endian. pbData[0] is the
;;  least significant byte and pbData[cbData - 1] is the most significant
;;  byte.
;;
;;  Returns TRUE if the integer blobs are identical after removing leading
;;  0 or 0xFF bytes.
;;--------------------------------------------------------------------------
;BOOL
CertCompareIntegerBlob proto _CType \
		 pInt1: PCRYPT_INTEGER_BLOB,
		 pInt2: PCRYPT_INTEGER_BLOB

;;+-------------------------------------------------------------------------
;;  Compare two certificates to see if they are identical.
;;
;;  Since a certificate is uniquely identified by its Issuer and SerialNumber,
;;  these are the only fields needing to be compared.
;;
;;  Returns TRUE if the certificates are identical.
;;--------------------------------------------------------------------------
;BOOL
CertCompareCertificate proto _CType \
    dwCertEncodingType: DWORD,
	      pCertId1: PCERT_INFO,
	      pCertId2: PCERT_INFO

;;+-------------------------------------------------------------------------
;;  Compare two certificate names to see if they are identical.
;;
;;  Returns TRUE if the names are identical.
;;--------------------------------------------------------------------------
;BOOL
CertCompareCertificateName proto _CType \
    dwCertEncodingType: DWORD,
	    pCertName1: PCERT_NAME_BLOB,
	    pCertName2: PCERT_NAME_BLOB

;;+-------------------------------------------------------------------------
;;  Compare the attributes in the certificate name with the specified
;;  Relative Distinguished Name's (CERT_RDN) array of attributes.
;;  The comparison iterates through the CERT_RDN attributes and looks for an
;;  attribute match in any of the certificate name's RDNs.
;;  Returns TRUE if all the attributes are found and match.
;;
;;  The CERT_RDN_ATTR fields can have the following special values:
;;    pszObjId == NULL		    - ignore the attribute object identifier
;;    dwValueType == RDN_ANY_TYPE   - ignore the value type
;;
;;  Currently only an exact, case sensitive match is supported.
;;
;;  CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set if the pRDN was initialized
;;  with unicode strings as for CryptEncodeObject(X509_UNICODE_NAME).
;;--------------------------------------------------------------------------
;BOOL
CertIsRDNAttrsInCertificateName proto _CType \
    dwCertEncodingType: DWORD,
	       dwFlags: DWORD,
	     pCertName: PCERT_NAME_BLOB,
		  pRDN: PCERT_RDN

CERT_UNICODE_IS_RDN_ATTRS_FLAG equ 0x1

;;+-------------------------------------------------------------------------
;;  Compare two public keys to see if they are identical.
;;
;;  Returns TRUE if the keys are identical.
;;--------------------------------------------------------------------------
;BOOL
CertComparePublicKeyInfo proto _CType \
    dwCertEncodingType: DWORD,
	   pPublicKey1: PCERT_PUBLIC_KEY_INFO,
	   pPublicKey2: PCERT_PUBLIC_KEY_INFO

;;+-------------------------------------------------------------------------
;;  Get the public/private key's bit length.
;;
;;  Returns 0 if unable to determine the key's length.
;;--------------------------------------------------------------------------
;DWORD
CertGetPublicKeyLength proto _CType \
    dwCertEncodingType: DWORD,
	    pPublicKey: PCERT_PUBLIC_KEY_INFO

;;+-------------------------------------------------------------------------
;;  Verify the signature of a subject certificate or a CRL using the
;;  public key info
;;
;;  Returns TRUE for a valid signature.
;;
;;  hCryptProv specifies the crypto provider to use to verify the signature.
;;  It doesn't need to use a private key.
;;--------------------------------------------------------------------------
;BOOL
CryptVerifyCertificateSignature proto _CType \
	    hCryptProv: HCRYPTPROV,
    dwCertEncodingType: DWORD,
	     pbEncoded: LPBYTE,
	     cbEncoded: DWORD,
	    pPublicKey: PCERT_PUBLIC_KEY_INFO

;;+-------------------------------------------------------------------------
;;  Compute the hash of the "to be signed" information in the encoded
;;  signed content (CERT_SIGNED_CONTENT_INFO).
;;
;;  hCryptProv specifies the crypto provider to use to compute the hash.
;;  It doesn't need to use a private key.
;;--------------------------------------------------------------------------
;BOOL
CryptHashToBeSigned proto _CType \
	    hCryptProv: HCRYPTPROV,
    dwCertEncodingType: DWORD,
	     pbEncoded: LPBYTE,
	     cbEncoded: DWORD,
	pbComputedHash: LPBYTE,
       pcbComputedHash: LPDWORD

;;+-------------------------------------------------------------------------
;;  Hash the encoded content.
;;
;;  hCryptProv specifies the crypto provider to use to compute the hash.
;;  It doesn't need to use a private key.
;;
;;  Algid specifies the CAPI hash algorithm to use. If Algid is 0, then, the
;;  default hash algorithm (currently SHA1) is used.
;;--------------------------------------------------------------------------
;BOOL
CryptHashCertificate proto _CType \
	    hCryptProv: HCRYPTPROV,
		 Algid: ALG_ID,
	       dwFlags: DWORD,
	     pbEncoded: LPBYTE,
	     cbEncoded: DWORD,
	pbComputedHash: LPBYTE,
       pcbComputedHash: LPDWORD

;;+-------------------------------------------------------------------------
;;  Sign the "to be signed" information in the encoded signed content.
;;
;;  hCryptProv specifies the crypto provider to use to do the signature.
;;  It uses the specified private key.
;;--------------------------------------------------------------------------
;BOOL
CryptSignCertificate proto _CType \
	    hCryptProv: HCRYPTPROV,
	     dwKeySpec: DWORD,
    dwCertEncodingType: DWORD,
   pbEncodedToBeSigned: LPBYTE,
   cbEncodedToBeSigned: DWORD,
   pSignatureAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER,
	 pvHashAuxInfo: PVOID,
	   pbSignature: LPBYTE,
	  pcbSignature: LPDWORD

;;+-------------------------------------------------------------------------
;;  Encode the "to be signed" information. Sign the encoded "to be signed".
;;  Encode the "to be signed" and the signature.
;;
;;  hCryptProv specifies the crypto provider to use to do the signature.
;;  It uses the specified private key.
;;--------------------------------------------------------------------------
;BOOL
CryptSignAndEncodeCertificate proto _CType \
	    hCryptProv: HCRYPTPROV,
	     dwKeySpec: DWORD,
    dwCertEncodingType: DWORD,
	lpszStructType: LPCSTR,
	  pvStructInfo: PVOID,	 ;;"to be signed"
   pSignatureAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER,
	 pvHashAuxInfo: PVOID,
	     pbEncoded: PBYTE,
	    pcbEncoded: LPDWORD


;;+-------------------------------------------------------------------------
;;  Verify the time validity of a certificate.
;;
;;  Returns -1 if before NotBefore, +1 if after NotAfter and otherwise 0 for
;;  a valid certificate
;;
;;  If pTimeToVerify is NULL, uses the current time.
;;--------------------------------------------------------------------------
;LONG
CertVerifyTimeValidity proto _CType \
	 pTimeToVerify: LPFILETIME,
	     pCertInfo: PCERT_INFO


;;+-------------------------------------------------------------------------
;;  Verify the time validity of a CRL.
;;
;;  Returns -1 if before ThisUpdate, +1 if after NextUpdate and otherwise 0 for
;;  a valid CRL
;;
;;  If pTimeToVerify is NULL, uses the current time.
;;--------------------------------------------------------------------------
;LONG
CertVerifyCRLTimeValidity proto _CType \
	 pTimeToVerify: LPFILETIME,
	      pCrlInfo: PCRL_INFO

;;+-------------------------------------------------------------------------
;;  Verify that the subject's time validity nests within the issuer's time
;;  validity.
;;
;;  Returns TRUE if it nests. Otherwise, returns FALSE.
;;--------------------------------------------------------------------------
;BOOL
CertVerifyValidityNesting proto _CType \
	  pSubjectInfo: PCERT_INFO,
	   pIssuerInfo: PCERT_INFO

;;+-------------------------------------------------------------------------
;;  Verify that the subject certificate isn't on its issuer CRL.
;;
;;  Returns true if the certificate isn't on the CRL.
;;--------------------------------------------------------------------------
;BOOL
CertVerifyCRLRevocation proto _CType \
    dwCertEncodingType: DWORD,
	       pCertId: PCERT_INFO,
	      cCrlInfo: DWORD,
	    rgpCrlInfo: PCRL_INFO

;;+-------------------------------------------------------------------------
;;  Convert the CAPI AlgId to the ASN.1 Object Identifier string
;;
;;  Returns NULL if there isn't an ObjId corresponding to the AlgId.
;;--------------------------------------------------------------------------
;LPCSTR
CertAlgIdToOID proto _CType \
	       dwAlgId: DWORD

;;+-------------------------------------------------------------------------
;;  Convert the ASN.1 Object Identifier string to the CAPI AlgId.
;;
;;  Returns 0 if there isn't an AlgId corresponding to the ObjId.
;;--------------------------------------------------------------------------
;DWORD
CertOIDToAlgId proto _CType \
	      pszObjId: LPCSTR

;;+-------------------------------------------------------------------------
;;  Find an extension identified by its Object Identifier.
;;
;;  If found, returns pointer to the extension. Otherwise, returns NULL.
;;--------------------------------------------------------------------------
;PCERT_EXTENSION
CertFindExtension proto _CType \
	      pszObjId: LPCSTR,
	   cExtensions: DWORD,
	  rgExtensions: CERT_EXTENSION

;;+-------------------------------------------------------------------------
;;  Find the first attribute identified by its Object Identifier.
;;
;;  If found, returns pointer to the attribute. Otherwise, returns NULL.
;;--------------------------------------------------------------------------
;PCRYPT_ATTRIBUTE
CertFindAttribute proto _CType \
	      pszObjId: LPCSTR,
		 cAttr: DWORD,
		rgAttr: CRYPT_ATTRIBUTE

;;+-------------------------------------------------------------------------
;;  Find the first CERT_RDN attribute identified by its Object Identifier in
;;  the name's list of Relative Distinguished Names.
;;
;;  If found, returns pointer to the attribute. Otherwise, returns NULL.
;;--------------------------------------------------------------------------
;PCERT_RDN_ATTR
CertFindRDNAttr proto _CType \
	      pszObjId: LPCSTR,
		 pName: PCERT_NAME_INFO

;;+-------------------------------------------------------------------------
;;  Get the intended key usage bytes from the certificate.
;;
;;  If the certificate doesn't have any intended key usage bytes, returns FALSE
;;  and *pbKeyUsage is zeroed. Otherwise, returns TRUE and up through
;;  cbKeyUsage bytes are copied into *pbKeyUsage. Any remaining uncopied
;;  bytes are zeroed.
;;--------------------------------------------------------------------------
;BOOL
CertGetIntendedKeyUsage proto _CType \
    dwCertEncodingType: DWORD,
	     pCertInfo: PCERT_INFO,
	    pbKeyUsage: LPBYTE,
	    cbKeyUsage: DWORD


;;+-------------------------------------------------------------------------
;;  Export the public key info associated with the provider's corresponding
;;  private key.
;;
;;  Calls CryptExportPublicKeyInfo with pszPublicKeyObjId = szOID_RSA_RSA,
;;  dwFlags = 0 and pvAuxInfo = NULL.
;;--------------------------------------------------------------------------
;BOOL
CryptExportPublicKeyInfo proto _CType \
	    hCryptProv: HCRYPTPROV,
	     dwKeySpec: DWORD,
    dwCertEncodingType: DWORD,
		 pInfo: PCERT_PUBLIC_KEY_INFO,
	       pcbInfo: LPDWORD


;;+-------------------------------------------------------------------------
;;  Export the public key info associated with the provider's corresponding
;;  private key.
;;
;;  Uses the dwCertEncodingType and pszPublicKeyObjId to call the
;;  installable CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC. The called function
;;  has the same signature as CryptExportPublicKeyInfoEx.
;;
;;  If unable to find an installable OID function for the pszPublicKeyObjId,
;;  attempts to export as a RSA Public Key (szOID_RSA_RSA).
;;
;;  The dwFlags and pvAuxInfo aren't used for szOID_RSA_RSA.
;;--------------------------------------------------------------------------
CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC equ <"CryptDllExportPublicKeyInfoEx">

;BOOL
CryptExportPublicKeyInfoEx proto _CType \
	    hCryptProv: HCRYPTPROV,
	     dwKeySpec: DWORD,
    dwCertEncodingType: DWORD,
     pszPublicKeyObjId: LPSTR,
	       dwFlags: DWORD,
	     pvAuxInfo: PVOID,
		 pInfo: PCERT_PUBLIC_KEY_INFO,
	       pcbInfo: LPDWORD


;;+-------------------------------------------------------------------------
;;  Convert and import the public key info into the provider and return a
;;  handle to the public key.
;;
;;  Calls CryptImportPublicKeyInfoEx with aiKeyAlg = 0, dwFlags = 0 and
;;  pvAuxInfo = NULL.
;;--------------------------------------------------------------------------
;BOOL
CryptImportPublicKeyInfo proto _CType \
	    hCryptProv: HCRYPTPROV,
    dwCertEncodingType: DWORD,
		 pInfo: PCERT_PUBLIC_KEY_INFO,
		 phKey: ptr HCRYPTKEY

;;+-------------------------------------------------------------------------
;;  Convert and import the public key info into the provider and return a
;;  handle to the public key.
;;
;;  Uses the dwCertEncodingType and pInfo->Algorithm.pszObjId to call the
;;  installable CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC. The called function
;;  has the same signature as CryptImportPublicKeyInfoEx.
;;
;;  If unable to find an installable OID function for the pszObjId,
;;  attempts to import as a RSA Public Key (szOID_RSA_RSA).
;;
;;  For szOID_RSA_RSA: aiKeyAlg may be set to CALG_RSA_SIGN or CALG_RSA_KEYX.
;;  Defaults to CALG_RSA_KEYX. The dwFlags and pvAuxInfo aren't used.
;;--------------------------------------------------------------------------
CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC equ <"CryptDllImportPublicKeyInfoEx">

;BOOL
CryptImportPublicKeyInfoEx proto _CType \
	    hCryptProv: HCRYPTPROV,
    dwCertEncodingType: DWORD,
		 pInfo: PCERT_PUBLIC_KEY_INFO,
	      aiKeyAlg: ALG_ID,
	       dwFlags: DWORD,
	     pvAuxInfo: PVOID,
		 phKey: ptr HCRYPTKEY

;;+-------------------------------------------------------------------------
;;  Compute the hash of the encoded public key info.
;;
;;  The public key info is encoded and then hashed.
;;--------------------------------------------------------------------------
;BOOL
CryptHashPublicKeyInfo proto _CType \
	    hCryptProv: HCRYPTPROV,
		 Algid: ALG_ID,
	       dwFlags: DWORD,
    dwCertEncodingType: DWORD,
		 pInfo: PCERT_PUBLIC_KEY_INFO,
	pbComputedHash: LPBYTE,
       pcbComputedHash: LPDWORD

;;+-------------------------------------------------------------------------
;;  Convert a Name Value to a null terminated char string
;;
;;  Returns the number of characters converted including the terminating null
;;  character. If psz is NULL or csz is 0, returns the required size of the
;;  destination string (including the terminating null char).
;;
;;  If psz != NULL && csz != 0, returned psz is always NULL terminated.
;;
;;  Note: csz includes the NULL char.
;;--------------------------------------------------------------------------
;DWORD
CertRDNValueToStrA proto _CType \
	   dwValueType: DWORD,
		pValue: PCERT_RDN_VALUE_BLOB,
		   psz: LPSTR,
		   csz: DWORD
;;+-------------------------------------------------------------------------
;;  Convert a Name Value to a null terminated char string
;;
;;  Returns the number of characters converted including the terminating null
;;  character. If psz is NULL or csz is 0, returns the required size of the
;;  destination string (including the terminating null char).
;;
;;  If psz != NULL && csz != 0, returned psz is always NULL terminated.
;;
;;  Note: csz includes the NULL char.
;;--------------------------------------------------------------------------
;DWORD
CertRDNValueToStrW proto _CType \
	   dwValueType: DWORD,
		pValue: PCERT_RDN_VALUE_BLOB,
		   psz: LPWSTR,
		   csz: DWORD
ifdef _UNICODE
CertRDNValueToStr	equ <CertRDNValueToStrW>
else
CertRDNValueToStr	equ <CertRDNValueToStrA>
endif ;; NOT UNICODE

;;+-------------------------------------------------------------------------
;;  Convert the certificate name blob to a null terminated char string.
;;
;;  Follows the string representation of distinguished names specified in
;;  RFC 1779. (Note, added double quoting "" for embedded quotes, quote
;;  empty strings and don't quote strings containing consecutive spaces).
;;  RDN values of type CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING are
;;  formatted in hexadecimal (e.g. #0A56CF).
;;
;;  The name string is formatted according to the dwStrType:
;;    CERT_SIMPLE_NAME_STR
;;	The object identifiers are discarded. CERT_RDN entries are separated
;;	by ", ". Multiple attributes per CERT_RDN are separated by " + ".
;;	For example:
;;	    Microsoft, Joe Cool + Programmer
;;    CERT_OID_NAME_STR
;;	The object identifiers are included with a "=" separator from their
;;	attribute value. CERT_RDN entries are separated by ", ".
;;	Multiple attributes per CERT_RDN are separated by " + ". For example:
;;	    2.5.4.11=Microsoft, 2.5.4.3=Joe Cool + 2.5.4.12=Programmer
;;    CERT_X500_NAME_STR
;;	The object identifiers are converted to their X500 key name. Otherwise,
;;	same as CERT_OID_NAME_STR. If the object identifier doesn't have
;;	a corresponding X500 key name, then, the object identifier is used with
;;	a "OID." prefix. For example:
;;	    OU=Microsoft, CN=Joe Cool + T=Programmer, OID.1.2.3.4.5.6=Unknown
;;
;;  We quote the RDN value if it contains leading or trailing whitespace
;;  or one of the following characters: ",", "+", "=", """, "\n",  "<", ">",
;;  "#" or ";". The quoting character is ". If the the RDN Value contains
;;  a " it is double quoted (""). For example:
;;	OU="  Microsoft", CN="Joe ""Cool""" + T="Programmer, Manager"
;;
;;  CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to replace
;;  the ", " separator with a "; " separator.
;;
;;  CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to replace
;;  the ", " separator with a "\r\n" separator.
;;
;;  CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to replace the
;;  " + " separator with a single space, " ".
;;
;;  CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
;;  the above quoting.
;;
;;  Returns the number of characters converted including the terminating null
;;  character. If psz is NULL or csz is 0, returns the required size of the
;;  destination string (including the terminating null char).
;;
;;  If psz != NULL && csz != 0, returned psz is always NULL terminated.
;;
;;  Note: csz includes the NULL char.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;--------------------------------------------------------------------------
;DWORD
CertNameToStrA proto _CType \
    dwCertEncodingType: DWORD,
		 pName: PCERT_NAME_BLOB,
	     dwStrType: DWORD,
		   psz: LPSTR,
		   csz: DWORD
;;+-------------------------------------------------------------------------
;;--------------------------------------------------------------------------
;DWORD
CertNameToStrW proto _CType \
    dwCertEncodingType: DWORD,
		 pName: PCERT_NAME_BLOB,
	     dwStrType: DWORD,
		   psz: LPWSTR,
		   csz: DWORD
ifdef _UNICODE
CertNameToStr		equ <CertNameToStrW>
else
CertNameToStr		equ <CertNameToStrA>
endif ;; NOT UNICODE

;;+-------------------------------------------------------------------------
;;  Certificate name string types
;;--------------------------------------------------------------------------
CERT_SIMPLE_NAME_STR	equ 1
CERT_OID_NAME_STR	equ 2
CERT_X500_NAME_STR	equ 3

;;+-------------------------------------------------------------------------
;;  Certificate name string type flags OR'ed with the above types
;;--------------------------------------------------------------------------
CERT_NAME_STR_SEMICOLON_FLAG	equ 0x40000000
CERT_NAME_STR_NO_PLUS_FLAG	equ 0x20000000
CERT_NAME_STR_NO_QUOTING_FLAG	equ 0x10000000
CERT_NAME_STR_CRLF_FLAG		equ 0x08000000
CERT_NAME_STR_COMMA_FLAG	equ 0x04000000


;;+-------------------------------------------------------------------------
;;  Convert the null terminated X500 string to an encoded certificate name.
;;
;;  The input string is expected to be formatted the same as the output
;;  from the above CertNameToStr API.
;;
;;  The CERT_SIMPLE_NAME_STR type isn't supported. Otherwise, when dwStrType
;;  is set to 0, CERT_OID_NAME_STR or CERT_X500_NAME_STR, allow either a
;;  case insensitive X500 key (CN=), case insensitive "OID." prefixed
;;  object identifier (OID.1.2.3.4.5.6=) or an object identifier (1.2.3.4=).
;;
;;  If no flags are OR'ed into dwStrType, then, allow "," or ";" as RDN
;;  separators and "+" as the multiple RDN value separator. Quoting is
;;  supported. A quote may be included in a quoted value by double quoting,
;;  for example (CN="Joe ""Cool"""). A value starting with a "#" is treated
;;  as ascii hex and converted to a CERT_RDN_OCTET_STRING. Embedded whitespace
;;  is skipped (1.2.3 = # AB CD 01  is the same as 1.2.3=#ABCD01).
;;
;;  Whitespace surrounding the keys, object identifers and values is removed.
;;
;;  CERT_NAME_STR_COMMA_FLAG can be or'ed into dwStrType to only allow the
;;  "," as the RDN separator.
;;
;;  CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to only allow the
;;  ";" as the RDN separator.
;;
;;  CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to only allow
;;  "\r" or "\n" as the RDN separator.
;;
;;  CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to ignore "+"
;;  as a separator and not allow multiple values per RDN.
;;
;;  CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
;;  quoting.
;;
;;  Support the following X500 Keys:
;;
;;  Key		Object Identifier		RDN Value Type(s)
;;  ---		-----------------		-----------------
;;  CN		szOID_COMMON_NAME		Printable, T61
;;  L		szOID_LOCALITY_NAME		Printable, T61
;;  O		szOID_ORGANIZATION_NAME		Printable, T61
;;  OU		szOID_ORGANIZATIONAL_UNIT_NAME	Printable, T61
;;  Email	szOID_RSA_emailAddr		Only IA5
;;  C		szOID_COUNTRY_NAME		Only Printable
;;  S		szOID_STATE_OR_PROVINCE_NAME	Printable, T61
;;  ST		szOID_STATE_OR_PROVINCE_NAME	Printable, T61
;;  STREET	szOID_STREET_ADDRESS		Printable, T61
;;  T		szOID_TITLE			Printable, T61
;;  Title	szOID_TITLE			Printable, T61
;;  G		szOID_GIVEN_NAME		Printable, T61
;;  GivenName	szOID_GIVEN_NAME		Printable, T61
;;  I		szOID_INITIALS			Printable, T61
;;  Initials	szOID_INITIALS			Printable, T61
;;  SN		szOID_SUR_NAME			Printable, T61
;;  DC		szOID_DOMAIN_COMPONENT		Only IA5
;;
;;  The T61 types are UTF-8 encoded.
;;
;;  Returns TRUE if successfully parsed the input string and encoded
;;  the name.
;;
;;  If the input string is detected to be invalid, *ppszError is updated
;;  to point to the beginning of the invalid character sequence. Otherwise,
;;  *ppszError is set to NULL. *ppszError is updated with a non-NULL pointer
;;  for the following errors:
;;	CRYPT_E_INVALID_X500_STRING
;;	CRYPT_E_INVALID_NUMERIC_STRING
;;	CRYPT_E_INVALID_PRINTABLE_STRING
;;	CRYPT_E_INVALID_IA5_STRING
;;
;;  ppszError can be set to NULL if not interested in getting a pointer
;;  to the invalid character sequence.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;--------------------------------------------------------------------------
;BOOL
CertStrToNameA proto _CType \
    dwCertEncodingType: DWORD,
	       pszX500: LPCSTR,
	     dwStrType: DWORD,
	    pvReserved: PVOID,
	     pbEncoded: LPBYTE,
	    pcbEncoded: LPDWORD,
	     ppszError: LPCSTR
;;+-------------------------------------------------------------------------
;;--------------------------------------------------------------------------
;BOOL
CertStrToNameW proto _CType \
    dwCertEncodingType: DWORD,
	       pszX500: LPCWSTR,
	     dwStrType: DWORD,
	    pvReserved: PVOID,
	     pbEncoded: LPBYTE,
	    pcbEncoded: LPDWORD,
	     ppszError: LPCWSTR
ifdef _UNICODE
CertStrToName		equ <CertStrToNameW>
else
CertStrToName		equ <CertStrToNameA>
endif ;; NOT UNICODE


;;+=========================================================================
;;  Simplified Cryptographic Message Data Structures and APIs
;;==========================================================================


;;+-------------------------------------------------------------------------
;;		Conventions for the *pb and *pcb output parameters:
;;
;;		Upon entry to the function:
;;		    if pcb is && pcb == NULL, then,
;;			No output is returned
;;		    else if pb == NULL && pcb != NULL, then,
;;			Length only determination. No length error is
;;			returned.
;;		    otherwise where (pb != NULL && pcb != NULL && *pcb != 0)
;;			Output is returned. If *pcb isn't big enough a
;;			length error is returned. In all cases *pcb is updated
;;			with the actual length needed/returned.
;;--------------------------------------------------------------------------


;;+-------------------------------------------------------------------------
;;  Type definitions of the parameters used for doing the cryptographic
;;  operations.
;;--------------------------------------------------------------------------

;;+-------------------------------------------------------------------------
;;  Callback to get and verify the signer's certificate.
;;
;;  Passed the CertId of the signer (its Issuer and SerialNumber) and a
;;  handle to its cryptographic signed message's cert store.
;;
;;  For CRYPT_E_NO_SIGNER, called with pSignerId == NULL.
;;
;;  For a valid signer certificate, returns a pointer to a read only
;;  CERT_CONTEXT. The returned CERT_CONTEXT is either obtained from a
;;  cert store or was created via CertCreateCertificateContext. For either case,
;;  its freed via CertFreeCertificateContext.
;;
;;  If a valid certificate isn't found, this callback returns NULL with
;;  LastError set via SetLastError().
;;
;;  The NULL implementation tries to get the Signer certificate from the
;;  message cert store. It doesn't verify the certificate.
;;--------------------------------------------------------------------------
;PCCERT_CONTEXT
PFN_CRYPT_GET_SIGNER_CERTIFICATE_T typedef proto _CType \
	      pvGetArg: PVOID,
    dwCertEncodingType: DWORD,
	     pSignerId: PCERT_INFO,	;; Only the Issuer and SerialNumber
					;; fields have been updated
	 hMsgCertStore: HCERTSTORE
PFN_CRYPT_GET_SIGNER_CERTIFICATE typedef ptr PFN_CRYPT_GET_SIGNER_CERTIFICATE_T
;;+-------------------------------------------------------------------------
;;  The CRYPT_SIGN_MESSAGE_PARA are used for signing messages using the
;;  specified signing certificate contexts. (Note, allows multiple signers.)
;;
;;  Either the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID must
;;  be set for each rgpSigningCert[]. Either one specifies the private
;;  signature key to use.
;;
;;  If any certificates and/or CRLs are to be included in the signed message,
;;  then, the MsgCert and MsgCrl parameters need to be updated. If the
;;  rgpSigningCerts are to be included, then, they must also be in the
;;  rgpMsgCert array.
;;
;;  cbSize must be set to the sizeof(CRYPT_SIGN_MESSAGE_PARA) or else
;;  LastError will be updated with E_INVALIDARG.
;;
;;  pvHashAuxInfo currently isn't used and must be set to NULL.
;;
;;  dwFlags normally is set to 0. However, if the encoded output
;;  is to be a CMSG_SIGNED inner content of an outer cryptographic message,
;;  such as a CMSG_ENVELOPED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
;;  should be set. If not set, then it would be encoded as an inner content
;;  type of CMSG_DATA.
;;
;;  dwInnerContentType is normally set to 0. It needs to be set if the
;;  ToBeSigned input is the encoded output of another cryptographic
;;  message, such as, an CMSG_ENVELOPED. When set, it's one of the cryptographic
;;  message types, for example, CMSG_ENVELOPED.
;;
;;  If the inner content of a nested cryptographic message is data (CMSG_DATA
;;  the default), then, neither dwFlags or dwInnerContentType need to be set.
;;--------------------------------------------------------------------------
CRYPT_SIGN_MESSAGE_PARA	 STRUC
cbSize			dd ?
dwMsgEncodingType	dd ?
pSigningCert		PCCERT_CONTEXT ?
HashAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
pvHashAuxInfo		PVOID ?
cMsgCert		dd ?
rgpMsgCert		PCCERT_CONTEXT ?
cMsgCrl			dd ?
rgpMsgCrl		PCCRL_CONTEXT ?
cAuthAttr		dd ?
rgAuthAttr		PCRYPT_ATTRIBUTE ?
cUnauthAttr		dd ?
rgUnauthAttr		PCRYPT_ATTRIBUTE ?
dwFlags			dd ?
dwInnerContentType	dd ?
CRYPT_SIGN_MESSAGE_PARA ENDS
PCRYPT_SIGN_MESSAGE_PARA typedef ptr CRYPT_SIGN_MESSAGE_PARA

CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG equ 0x1

;;+-------------------------------------------------------------------------
;;  The CRYPT_VERIFY_MESSAGE_PARA are used to verify signed messages.
;;
;;  hCryptProv is used to do hashing and signature verification.
;;
;;  The dwCertEncodingType specifies the encoding type of the certificates
;;  and/or CRLs in the message.
;;
;;  pfnGetSignerCertificate is called to get and verify the message signer's
;;  certificate.
;;
;;  cbSize must be set to the sizeof(CRYPT_VERIFY_MESSAGE_PARA) or else
;;  LastError will be updated with E_INVALIDARG.
;;--------------------------------------------------------------------------
CRYPT_VERIFY_MESSAGE_PARA  STRUC
cbSize			dd ?
dwMsgAndCertEncodingType dd ?
hCryptProv		HCRYPTPROV ?
pfnGetSignerCertificate PFN_CRYPT_GET_SIGNER_CERTIFICATE ?
pvGetArg		PVOID ?
CRYPT_VERIFY_MESSAGE_PARA ENDS
PCRYPT_VERIFY_MESSAGE_PARA typedef ptr CRYPT_VERIFY_MESSAGE_PARA

;;+-------------------------------------------------------------------------
;;  The CRYPT_ENCRYPT_MESSAGE_PARA are used for encrypting messages.
;;
;;  hCryptProv is used to do content encryption, recipient key
;;  encryption, and recipient key export. Its private key
;;  isn't used.
;;
;;  pvEncryptionAuxInfo currently isn't used and must be set to NULL.
;;
;;  cbSize must be set to the sizeof(CRYPT_ENCRYPT_MESSAGE_PARA) or else
;;  LastError will be updated with E_INVALIDARG.
;;
;;  dwFlags normally is set to 0. However, if the encoded output
;;  is to be a CMSG_ENVELOPED inner content of an outer cryptographic message,
;;  such as a CMSG_SIGNED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
;;  should be set. If not set, then it would be encoded as an inner content
;;  type of CMSG_DATA.
;;
;;  dwInnerContentType is normally set to 0. It needs to be set if the
;;  ToBeEncrypted input is the encoded output of another cryptographic
;;  message, such as, an CMSG_SIGNED. When set, it's one of the cryptographic
;;  message types, for example, CMSG_SIGNED.
;;
;;  If the inner content of a nested cryptographic message is data (CMSG_DATA
;;  the default), then, neither dwFlags or dwInnerContentType need to be set.
;;--------------------------------------------------------------------------
CRYPT_ENCRYPT_MESSAGE_PARA  STRUC
cbSize			dd ?
dwMsgEncodingType	dd ?
hCryptProv		HCRYPTPROV ?
ContentEncryptionAlgorithm CRYPT_ALGORITHM_IDENTIFIER <>
pvEncryptionAuxInfo	PVOID ?
dwFlags			dd ?
dwInnerContentType	dd ?
CRYPT_ENCRYPT_MESSAGE_PARA ENDS
PCRYPT_ENCRYPT_MESSAGE_PARA typedef ptr CRYPT_ENCRYPT_MESSAGE_PARA

;;+-------------------------------------------------------------------------
;;  The CRYPT_DECRYPT_MESSAGE_PARA are used for decrypting messages.
;;
;;  The CertContext to use for decrypting a message is obtained from one
;;  of the specified cert stores. An encrypted message can have one or
;;  more recipients. The recipients are identified by their CertId (Issuer
;;  and SerialNumber). The cert stores are searched to find the CertContext
;;  corresponding to the CertId.
;;
;;  Only CertContexts in the store with either
;;  the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID set
;;  can be used. Either property specifies the private exchange key to use.
;;
;;  cbSize must be set to the sizeof(CRYPT_DECRYPT_MESSAGE_PARA) or else
;;  LastError will be updated with E_INVALIDARG.
;;--------------------------------------------------------------------------
CRYPT_DECRYPT_MESSAGE_PARA  STRUC
cbSize			dd ?
dwMsgAndCertEncodingType dd ?
cCertStore		dd ?
rghCertStore		PVOID ?;HCERTSTORE ?
CRYPT_DECRYPT_MESSAGE_PARA ENDS
PCRYPT_DECRYPT_MESSAGE_PARA typedef ptr CRYPT_DECRYPT_MESSAGE_PARA

;;+-------------------------------------------------------------------------
;;  The CRYPT_HASH_MESSAGE_PARA are used for hashing or unhashing
;;  messages.
;;
;;  hCryptProv is used to compute the hash.
;;
;;  pvHashAuxInfo currently isn't used and must be set to NULL.
;;
;;  cbSize must be set to the sizeof(CRYPT_HASH_MESSAGE_PARA) or else
;;  LastError will be updated with E_INVALIDARG.
;;--------------------------------------------------------------------------
CRYPT_HASH_MESSAGE_PARA	 STRUC
cbSize			dd ?
dwMsgEncodingType	dd ?
hCryptProv		HCRYPTPROV ?
HashAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
pvHashAuxInfo		PVOID ?
CRYPT_HASH_MESSAGE_PARA ENDS
PCRYPT_HASH_MESSAGE_PARA typedef ptr CRYPT_HASH_MESSAGE_PARA



;;+-------------------------------------------------------------------------
;;  The CRYPT_KEY_SIGN_MESSAGE_PARA are used for signing messages until a
;;  certificate has been created for the signature key.
;;
;;  pvHashAuxInfo currently isn't used and must be set to NULL.
;;
;;  If PubKeyAlgorithm isn't set, defaults to szOID_RSA_RSA.
;;
;;  cbSize must be set to the sizeof(CRYPT_KEY_SIGN_MESSAGE_PARA) or else
;;  LastError will be updated with E_INVALIDARG.
;;--------------------------------------------------------------------------
CRYPT_KEY_SIGN_MESSAGE_PARA  STRUC
cbSize			dd ?
dwMsgAndCertEncodingType dd ?
hCryptProv		HCRYPTPROV ?
dwKeySpec		dd ?
HashAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
pvHashAuxInfo		PVOID ?
PubKeyAlgorithm		CRYPT_ALGORITHM_IDENTIFIER <>
CRYPT_KEY_SIGN_MESSAGE_PARA ENDS
PCRYPT_KEY_SIGN_MESSAGE_PARA typedef ptr CRYPT_KEY_SIGN_MESSAGE_PARA

;;+-------------------------------------------------------------------------
;;  The CRYPT_KEY_VERIFY_MESSAGE_PARA are used to verify signed messages without
;;  a certificate for the signer.
;;
;;  Normally used until a certificate has been created for the key.
;;
;;  hCryptProv is used to do hashing and signature verification.
;;
;;  cbSize must be set to the sizeof(CRYPT_KEY_VERIFY_MESSAGE_PARA) or else
;;  LastError will be updated with E_INVALIDARG.
;;--------------------------------------------------------------------------
CRYPT_KEY_VERIFY_MESSAGE_PARA  STRUC
cbSize			dd ?
dwMsgEncodingType	dd ?
hCryptProv		HCRYPTPROV ?
CRYPT_KEY_VERIFY_MESSAGE_PARA ENDS
PCRYPT_KEY_VERIFY_MESSAGE_PARA typedef ptr CRYPT_KEY_VERIFY_MESSAGE_PARA


;;+-------------------------------------------------------------------------
;;  Sign the message.
;;
;;  If fDetachedSignature is TRUE, the "to be signed" content isn't included
;;  in the encoded signed blob.
;;--------------------------------------------------------------------------
;BOOL
CryptSignMessage proto _CType \
	     pSignPara: PCRYPT_SIGN_MESSAGE_PARA,
    fDetachedSignature: BOOL,
	   cToBeSigned: DWORD,
	rgpbToBeSigned: LPBYTE,
	rgcbToBeSigned: DWORD,
	  pbSignedBlob: LPBYTE,
	 pcbSignedBlob: LPDWORD

;;+-------------------------------------------------------------------------
;;  Verify a signed message.
;;
;;  If pbDecoded == NULL, then, *pcbDecoded is implicitly set to 0 on input.
;;  For *pcbDecoded == 0 && ppSignerCert == NULL on input, the signer isn't
;;  verified.
;;
;;  A message might have more than one signer. Set dwSignerIndex to iterate
;;  through all the signers. dwSignerIndex == 0 selects the first signer.
;;
;;  pVerifyPara's pfnGetSignerCertificate is called to get the signer's
;;  certificate.
;;
;;  For a verified signer and message, *ppSignerCert is updated
;;  with the CertContext of the signer. It must be freed by calling
;;  CertFreeCertificateContext. Otherwise, *ppSignerCert is set to NULL.
;;
;;  ppSignerCert can be NULL, indicating the caller isn't interested
;;  in getting the CertContext of the signer.
;;
;;  pcbDecoded can be NULL, indicating the caller isn't interested in getting
;;  the decoded content. Furthermore, if the message doesn't contain any
;;  content or signers, then, pcbDecoded must be set to NULL, to allow the
;;  pVerifyPara->pfnGetCertificate to be called. Normally, this would be
;;  the case when the signed message contains only certficates and CRLs.
;;  If pcbDecoded is NULL and the message doesn't have the indicated signer,
;;  pfnGetCertificate is called with pSignerId set to NULL.
;;
;;  If the message doesn't contain any signers || dwSignerIndex > message's
;;  SignerCount, then, an error is returned with LastError set to
;;  CRYPT_E_NO_SIGNER. Also, for CRYPT_E_NO_SIGNER, pfnGetSignerCertificate
;;  is still called with pSignerId set to NULL.
;;
;;  Note, an alternative way to get the certificates and CRLs from a
;;  signed message is to call CryptGetMessageCertificates.
;;--------------------------------------------------------------------------
;BOOL
CryptVerifyMessageSignature proto _CType \
	   pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA,
	 dwSignerIndex: DWORD,
	  pbSignedBlob: LPBYTE,
	  cbSignedBlob: DWORD,
	     pbDecoded: LPBYTE,
	    pcbDecoded: LPDWORD,
	  ppSignerCert: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Returns the count of signers in the signed message. For no signers, returns
;;  0. For an error returns -1 with LastError updated accordingly.
;;--------------------------------------------------------------------------
;LONG
CryptGetMessageSignerCount proto _CType \
     dwMsgEncodingType: DWORD,
	  pbSignedBlob: LPBYTE,
	  cbSignedBlob: DWORD

;;+-------------------------------------------------------------------------
;;  Returns the cert store containing the message's certs and CRLs.
;;  For an error, returns NULL with LastError updated.
;;--------------------------------------------------------------------------
;HCERTSTORE
CryptGetMessageCertificates proto _CType \
dwMsgAndCertEncodingType: DWORD,
	    hCryptProv: HCRYPTPROV,
	       dwFlags: DWORD,
	  pbSignedBlob: LPBYTE,
	  cbSignedBlob: DWORD

;;+-------------------------------------------------------------------------
;;  Verify a signed message containing detached signature(s).
;;  The "to be signed" content is passed in separately. No
;;  decoded output. Otherwise, identical to CryptVerifyMessageSignature.
;;--------------------------------------------------------------------------
;BOOL
CryptVerifyDetachedMessageSignature proto _CType \
	   pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA,
	 dwSignerIndex: DWORD,
    pbDetachedSignBlob: LPBYTE,
    cbDetachedSignBlob: DWORD,
	   cToBeSigned: DWORD,
	rgpbToBeSigned: LPBYTE,
	rgcbToBeSigned: DWORD,
	  ppSignerCert: ptr PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Encrypts the message for the recipient(s).
;;--------------------------------------------------------------------------
;BOOL
CryptEncryptMessage proto _CType \
	  pEncryptPara: PCRYPT_ENCRYPT_MESSAGE_PARA,
	cRecipientCert: DWORD,
      rgpRecipientCert: PCCERT_CONTEXT,
       pbToBeEncrypted: LPBYTE,
       cbToBeEncrypted: DWORD,
       pbEncryptedBlob: LPBYTE,
      pcbEncryptedBlob: LPDWORD

;;+-------------------------------------------------------------------------
;;  Decrypts the message.
;;
;;  If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
;;  For *pcbDecrypted == 0 && ppXchgCert == NULL on input, the message isn't
;;  decrypted.
;;
;;  For a successfully decrypted message, *ppXchgCert is updated
;;  with the CertContext used to decrypt. It must be freed by calling
;;  CertStoreFreeCert. Otherwise, *ppXchgCert is set to NULL.
;;
;;  ppXchgCert can be NULL, indicating the caller isn't interested
;;  in getting the CertContext used to decrypt.
;;--------------------------------------------------------------------------
;BOOL
CryptDecryptMessage proto _CType \
	  pDecryptPara: PCRYPT_DECRYPT_MESSAGE_PARA,
       pbEncryptedBlob: LPBYTE,
       cbEncryptedBlob: DWORD,
	   pbDecrypted: LPBYTE,
	  pcbDecrypted: LPDWORD,
	    ppXchgCert: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Sign the message and encrypt for the recipient(s). Does a CryptSignMessage
;;  followed with a CryptEncryptMessage.
;;
;;  Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
;;  inside of an CMSG_ENVELOPED.
;;--------------------------------------------------------------------------
;BOOL
CryptSignAndEncryptMessage proto _CType \
	     pSignPara: PCRYPT_SIGN_MESSAGE_PARA,
	  pEncryptPara: PCRYPT_ENCRYPT_MESSAGE_PARA,
	cRecipientCert: DWORD,
      rgpRecipientCert: PCCERT_CONTEXT,
pbToBeSignedAndEncrypted: LPBYTE,
cbToBeSignedAndEncrypted: DWORD,
pbSignedAndEncryptedBlob: LPBYTE,
pcbSignedAndEncryptedBlob: LPDWORD

;;+-------------------------------------------------------------------------
;;  Decrypts the message and verifies the signer. Does a CryptDecryptMessage
;;  followed with a CryptVerifyMessageSignature.
;;
;;  If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
;;  For *pcbDecrypted == 0 && ppSignerCert == NULL on input, the signer isn't
;;  verified.
;;
;;  A message might have more than one signer. Set dwSignerIndex to iterate
;;  through all the signers. dwSignerIndex == 0 selects the first signer.
;;
;;  The pVerifyPara's VerifySignerPolicy is called to verify the signer's
;;  certificate.
;;
;;  For a successfully decrypted and verified message, *ppXchgCert and
;;  *ppSignerCert are updated. They must be freed by calling
;;  CertStoreFreeCert. Otherwise, they are set to NULL.
;;
;;  ppXchgCert and/or ppSignerCert can be NULL, indicating the
;;  caller isn't interested in getting the CertContext.
;;
;;  Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
;;  inside of an CMSG_ENVELOPED.
;;
;;  The message always needs to be decrypted to allow access to the
;;  signed message. Therefore, if ppXchgCert != NULL, its always updated.
;;--------------------------------------------------------------------------
;BOOL
CryptDecryptAndVerifyMessageSignature proto _CType \
	  pDecryptPara: PCRYPT_DECRYPT_MESSAGE_PARA,
	   pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA,
	 dwSignerIndex: DWORD,
       pbEncryptedBlob: LPBYTE,
       cbEncryptedBlob: DWORD,
	   pbDecrypted: LPBYTE,
	  pcbDecrypted: LPDWORD,
	    ppXchgCert: PCCERT_CONTEXT,
	  ppSignerCert: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Decodes a cryptographic message which may be one of the following types:
;;    CMSG_DATA
;;    CMSG_SIGNED
;;    CMSG_ENVELOPED
;;    CMSG_SIGNED_AND_ENVELOPED
;;    CMSG_HASHED
;;
;;  dwMsgTypeFlags specifies the set of allowable messages. For example, to
;;  decode either SIGNED or ENVELOPED messages, set dwMsgTypeFlags to:
;;	CMSG_SIGNED_FLAG | CMSG_ENVELOPED_FLAG.
;;
;;  dwProvInnerContentType is only applicable when processing nested
;;  crytographic messages. When processing an outer crytographic message
;;  it must be set to 0. When decoding a nested cryptographic message
;;  its the dwInnerContentType returned by a previous CryptDecodeMessage
;;  of the outer message. The InnerContentType can be any of the CMSG types,
;;  for example, CMSG_DATA, CMSG_SIGNED, ...
;;
;;  The optional *pdwMsgType is updated with the type of message.
;;
;;  The optional *pdwInnerContentType is updated with the type of the inner
;;  message. Unless there is cryptographic message nesting, CMSG_DATA
;;  is returned.
;;
;;  For CMSG_DATA: returns decoded content.
;;  For CMSG_SIGNED: same as CryptVerifyMessageSignature.
;;  For CMSG_ENVELOPED: same as CryptDecryptMessage.
;;  For CMSG_SIGNED_AND_ENVELOPED: same as CryptDecryptMessage plus
;;	CryptVerifyMessageSignature.
;;  For CMSG_HASHED: verifies the hash and returns decoded content.
;;--------------------------------------------------------------------------
;BOOL
CryptDecodeMessage proto _CType \
	dwMsgTypeFlags: DWORD,
	  pDecryptPara: PCRYPT_DECRYPT_MESSAGE_PARA,
	   pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA,
	 dwSignerIndex: DWORD,
	 pbEncodedBlob: LPBYTE,
	 cbEncodedBlob: DWORD,
dwPrevInnerContentType: DWORD,
	    pdwMsgType: LPDWORD,
   pdwInnerContentType: LPDWORD,
	     pbDecoded: LPBYTE,
	    pcbDecoded: LPDWORD,
	    ppXchgCert: PCCERT_CONTEXT,
	  ppSignerCert: PCCERT_CONTEXT

;;+-------------------------------------------------------------------------
;;  Hash the message.
;;
;;  If fDetachedHash is TRUE, only the ComputedHash is encoded in the
;;  pbHashedBlob. Otherwise, both the ToBeHashed and ComputedHash
;;  are encoded.
;;
;;  pcbHashedBlob or pcbComputedHash can be NULL, indicating the caller
;;  isn't interested in getting the output.
;;--------------------------------------------------------------------------
;BOOL
CryptHashMessage proto _CType \
	     pHashPara: PCRYPT_HASH_MESSAGE_PARA,
	 fDetachedHash: BOOL,
	   cToBeHashed: DWORD,
	rgpbToBeHashed: LPBYTE,
	rgcbToBeHashed: DWORD,
	  pbHashedBlob: LPBYTE,
	 pcbHashedBlob: LPDWORD,
	pbComputedHash: LPBYTE,
       pcbComputedHash: LPDWORD

;;+-------------------------------------------------------------------------
;;  Verify a hashed message.
;;
;;  pcbToBeHashed or pcbComputedHash can be NULL,
;;  indicating the caller isn't interested in getting the output.
;;--------------------------------------------------------------------------
;BOOL
CryptVerifyMessageHash proto _CType \
	     pHashPara: PCRYPT_HASH_MESSAGE_PARA,
	  pbHashedBlob: LPBYTE,
	  cbHashedBlob: DWORD,
	  pbToBeHashed: LPBYTE,
	 pcbToBeHashed: LPDWORD,
	pbComputedHash: LPBYTE,
       pcbComputedHash: LPDWORD

;;+-------------------------------------------------------------------------
;;  Verify a hashed message containing a detached hash.
;;  The "to be hashed" content is passed in separately. No
;;  decoded output. Otherwise, identical to CryptVerifyMessageHash.
;;
;;  pcbComputedHash can be NULL, indicating the caller isn't interested
;;  in getting the output.
;;--------------------------------------------------------------------------
;BOOL
CryptVerifyDetachedMessageHash proto _CType \
	     pHashPara: PCRYPT_HASH_MESSAGE_PARA,
    pbDetachedHashBlob: LPBYTE,
    cbDetachedHashBlob: DWORD,
	   cToBeHashed: DWORD,
	rgpbToBeHashed: LPBYTE,
	rgcbToBeHashed: DWORD,
	pbComputedHash: LPBYTE,
       pcbComputedHash: LPDWORD

;;+-------------------------------------------------------------------------
;;  Sign the message using the provider's private key specified in the
;;  parameters. A dummy SignerId is created and stored in the message.
;;
;;  Normally used until a certificate has been created for the key.
;;--------------------------------------------------------------------------
;BOOL
CryptSignMessageWithKey proto _CType \
	     pSignPara: PCRYPT_KEY_SIGN_MESSAGE_PARA,
	  pbToBeSigned: LPBYTE,
	  cbToBeSigned: DWORD,
	  pbSignedBlob: LPBYTE,
	 pcbSignedBlob: LPDWORD

;;+-------------------------------------------------------------------------
;;  Verify a signed message using the specified public key info.
;;
;;  Normally called by a CA until it has created a certificate for the
;;  key.
;;
;;  pPublicKeyInfo contains the public key to use to verify the signed
;;  message. If NULL, the signature isn't verified (for instance, the decoded
;;  content may contain the PublicKeyInfo).
;;
;;  pcbDecoded can be NULL, indicating the caller isn't interested
;;  in getting the decoded content.
;;--------------------------------------------------------------------------
;BOOL
CryptVerifyMessageSignatureWithKey proto _CType \
	   pVerifyPara: PCRYPT_KEY_VERIFY_MESSAGE_PARA,
	pPublicKeyInfo: PCERT_PUBLIC_KEY_INFO,
	  pbSignedBlob: LPBYTE,
	  cbSignedBlob: DWORD,
	     pbDecoded: LPBYTE,
	    pcbDecoded: LPDWORD


;;+=========================================================================
;;  System Certificate Store Data Structures and APIs
;;==========================================================================


;;+-------------------------------------------------------------------------
;;  Get a system certificate store based on a subsystem protocol.
;;
;;  Current examples of subsystems protocols are:
;;	"MY"	Cert Store hold certs with associated Private Keys
;;	"CA"	Certifying Authority certs
;;	"ROOT"	Root Certs
;;	"SPC"	Software publisher certs
;;
;;
;;  If hProv is NULL the default provider "1" is opened for you.
;;  When the store is closed the provider is release. Otherwise
;;  if hProv is not NULL, no provider is created or released.
;;
;;  The returned Cert Store can be searched for an appropriate Cert
;;  using the Cert Store API's (see certstor.h)
;;
;;  When done, the cert store should be closed using CertStoreClose
;;--------------------------------------------------------------------------


;HCERTSTORE
CertOpenSystemStoreA proto _CType \
		 hProv: HCRYPTPROV,
   szSubsystemProtocol: LPCSTR
;HCERTSTORE
CertOpenSystemStoreW proto _CType \
		 hProv: HCRYPTPROV,
   szSubsystemProtocol: LPCWSTR
ifdef _UNICODE
CertOpenSystemStore	equ <CertOpenSystemStoreW>
else
CertOpenSystemStore	equ <CertOpenSystemStoreA>
endif ;; NOT UNICODE

;BOOL
CertAddEncodedCertificateToSystemStoreA proto _CType \
       szCertStoreName: LPCSTR,
	 pbCertEncoded: LPBYTE,
	 cbCertEncoded: DWORD
;BOOL
CertAddEncodedCertificateToSystemStoreW proto _CType \
       szCertStoreName: LPCWSTR,
	 pbCertEncoded: LPBYTE,
	 cbCertEncoded: DWORD
ifdef _UNICODE
CertAddEncodedCertificateToSystemStore equ <CertAddEncodedCertificateToSystemStoreW>
else
CertAddEncodedCertificateToSystemStore equ <CertAddEncodedCertificateToSystemStoreA>
endif ;; NOT UNICODE


;;+-------------------------------------------------------------------------
;;  Find all certificate chains tying the given issuer name to any certificate
;;  that the current user has a private key for.
;;
;;  If no certificate chain is found, FALSE is returned with LastError set
;;  to CRYPT_E_NOT_FOUND and the counts zeroed.
;;
;;  IE 3.0 ASSUMPTION:
;;   The client certificates are in the "My" system store. The issuer
;;   cerificates may be in the "Root", "CA" or "My" system stores.
;;--------------------------------------------------------------------------
CERT_CHAIN		STRUC
cCerts			dd ?	;; number of certs in chain
certs			PCERT_BLOB ?	;; pointer to array of cert chain blobs
					;; representing the certs
keyLocatorInfo		CRYPT_KEY_PROV_INFO <>	;; key locator for cert
CERT_CHAIN		ENDS
PCERT_CHAIN		typedef ptr CERT_CHAIN


;; WINCRYPT32API    This is not exported by crypt32, it is exported by softpub
;HRESULT

FindCertsByIssuer proto _CType \
	   pCertChains: PCERT_CHAIN,
	 pcbCertChains: LPDWORD,
	  pcCertChains: LPDWORD,	; count of certificates chains returned
   pbEncodedIssuerName: LPBYTE,		; DER encoded issuer name
   cbEncodedIssuerName: DWORD,		; count in bytes of encoded issuer name
	   pwszPurpose: LPCWSTR,	; "ClientAuth" or "CodeSigning"
	     dwKeySpec: DWORD		; only return signers supporting this keyspec

endif ;; _WIN32_WINNT GE 0x0400

endif ;; __WINCRYPT_H__

.list
