include winapifamily.inc
ifndef __NCRYPT_H__
define __NCRYPT_H__

ifndef __SECSTATUS_DEFINED__
SECURITY_STATUS		typedef LONG
define __SECSTATUS_DEFINED__
endif

include bcrypt.inc

ifndef HCRYPTPROV_DEFINED
define HCRYPTPROV_DEFINED
HCRYPTPROV		typedef ULONG_PTR
HCRYPTKEY		typedef ULONG_PTR
HCRYPTHASH		typedef ULONG_PTR
endif

NCRYPT_MAX_KEY_NAME_LENGTH equ 512
NCRYPT_MAX_ALG_ID_LENGTH equ 512

CALLBACK(PFN_NCRYPT_ALLOC, :size_t)
CALLBACK(PFN_NCRYPT_FREE, :ptr)

NCRYPT_ALLOC_PARA	STRUC
cbSize			dd ?
pfnAlloc		PFN_NCRYPT_ALLOC ?
pfnFree			PFN_NCRYPT_FREE ?
NCRYPT_ALLOC_PARA	ENDS


MS_KEY_STORAGE_PROVIDER equ <L"Microsoft Software Key Storage Provider">
MS_SMART_CARD_KEY_STORAGE_PROVIDER equ <L"Microsoft Smart Card Key Storage Provider">
MS_PLATFORM_KEY_STORAGE_PROVIDER equ <L"Microsoft Platform Crypto Provider">

NCRYPT_RSA_ALGORITHM	equ BCRYPT_RSA_ALGORITHM
NCRYPT_RSA_SIGN_ALGORITHM equ BCRYPT_RSA_SIGN_ALGORITHM
NCRYPT_DH_ALGORITHM	equ BCRYPT_DH_ALGORITHM
NCRYPT_DSA_ALGORITHM	equ BCRYPT_DSA_ALGORITHM
NCRYPT_MD2_ALGORITHM	equ BCRYPT_MD2_ALGORITHM
NCRYPT_MD4_ALGORITHM	equ BCRYPT_MD4_ALGORITHM
NCRYPT_MD5_ALGORITHM	equ BCRYPT_MD5_ALGORITHM
NCRYPT_SHA1_ALGORITHM	equ BCRYPT_SHA1_ALGORITHM
NCRYPT_SHA256_ALGORITHM equ BCRYPT_SHA256_ALGORITHM
NCRYPT_SHA384_ALGORITHM equ BCRYPT_SHA384_ALGORITHM
NCRYPT_SHA512_ALGORITHM equ BCRYPT_SHA512_ALGORITHM
NCRYPT_ECDSA_P256_ALGORITHM equ BCRYPT_ECDSA_P256_ALGORITHM
NCRYPT_ECDSA_P384_ALGORITHM equ BCRYPT_ECDSA_P384_ALGORITHM
NCRYPT_ECDSA_P521_ALGORITHM equ BCRYPT_ECDSA_P521_ALGORITHM
NCRYPT_ECDH_P256_ALGORITHM equ BCRYPT_ECDH_P256_ALGORITHM
NCRYPT_ECDH_P384_ALGORITHM equ BCRYPT_ECDH_P384_ALGORITHM
NCRYPT_ECDH_P521_ALGORITHM equ BCRYPT_ECDH_P521_ALGORITHM

if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_AES_ALGORITHM	equ BCRYPT_AES_ALGORITHM
NCRYPT_RC2_ALGORITHM	equ BCRYPT_RC2_ALGORITHM
NCRYPT_3DES_ALGORITHM	equ BCRYPT_3DES_ALGORITHM
NCRYPT_DES_ALGORITHM	equ BCRYPT_DES_ALGORITHM
NCRYPT_DESX_ALGORITHM	equ BCRYPT_DESX_ALGORITHM
NCRYPT_3DES_112_ALGORITHM equ BCRYPT_3DES_112_ALGORITHM

NCRYPT_SP800108_CTR_HMAC_ALGORITHM equ BCRYPT_SP800108_CTR_HMAC_ALGORITHM
NCRYPT_SP80056A_CONCAT_ALGORITHM equ BCRYPT_SP80056A_CONCAT_ALGORITHM
NCRYPT_PBKDF2_ALGORITHM equ BCRYPT_PBKDF2_ALGORITHM
NCRYPT_CAPI_KDF_ALGORITHM equ BCRYPT_CAPI_KDF_ALGORITHM
endif

NCRYPT_KEY_STORAGE_ALGORITHM equ <L"KEY_STORAGE">

NCRYPT_CIPHER_INTERFACE equ BCRYPT_CIPHER_INTERFACE
NCRYPT_HASH_INTERFACE	equ BCRYPT_HASH_INTERFACE
NCRYPT_ASYMMETRIC_ENCRYPTION_INTERFACE equ BCRYPT_ASYMMETRIC_ENCRYPTION_INTERFACE
NCRYPT_SECRET_AGREEMENT_INTERFACE equ BCRYPT_SECRET_AGREEMENT_INTERFACE
NCRYPT_SIGNATURE_INTERFACE equ BCRYPT_SIGNATURE_INTERFACE
if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_KEY_DERIVATION_INTERFACE equ BCRYPT_KEY_DERIVATION_INTERFACE
endif

NCRYPT_KEY_STORAGE_INTERFACE equ 0x00010001
NCRYPT_SCHANNEL_INTERFACE equ 0x00010002
NCRYPT_SCHANNEL_SIGNATURE_INTERFACE equ 0x00010003
if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_KEY_PROTECTION_INTERFACE equ 0x00010004
endif

NCRYPT_RSA_ALGORITHM_GROUP equ NCRYPT_RSA_ALGORITHM
NCRYPT_DH_ALGORITHM_GROUP equ NCRYPT_DH_ALGORITHM
NCRYPT_DSA_ALGORITHM_GROUP equ NCRYPT_DSA_ALGORITHM
NCRYPT_ECDSA_ALGORITHM_GROUP equ <L"ECDSA">
NCRYPT_ECDH_ALGORITHM_GROUP equ <L"ECDH">

if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_AES_ALGORITHM_GROUP equ NCRYPT_AES_ALGORITHM
NCRYPT_RC2_ALGORITHM_GROUP equ NCRYPT_RC2_ALGORITHM
NCRYPT_DES_ALGORITHM_GROUP equ <L"DES">
NCRYPT_KEY_DERIVATION_GROUP equ <L"KEY_DERIVATION">
endif

NCRYPTBUFFER_VERSION	equ 0

NCRYPTBUFFER_EMPTY	equ 0
NCRYPTBUFFER_DATA	equ 1
NCRYPTBUFFER_PROTECTION_DESCRIPTOR_STRING equ 3
NCRYPTBUFFER_PROTECTION_FLAGS equ 4

NCRYPTBUFFER_SSL_CLIENT_RANDOM equ 20
NCRYPTBUFFER_SSL_SERVER_RANDOM equ 21
NCRYPTBUFFER_SSL_HIGHEST_VERSION equ 22
NCRYPTBUFFER_SSL_CLEAR_KEY equ 23
NCRYPTBUFFER_SSL_KEY_ARG_DATA equ 24

NCRYPTBUFFER_PKCS_OID	equ 40
NCRYPTBUFFER_PKCS_ALG_OID equ 41
NCRYPTBUFFER_PKCS_ALG_PARAM equ 42
NCRYPTBUFFER_PKCS_ALG_ID equ 43
NCRYPTBUFFER_PKCS_ATTRS equ 44
NCRYPTBUFFER_PKCS_KEY_NAME equ 45
NCRYPTBUFFER_PKCS_SECRET equ 46

NCRYPTBUFFER_CERT_BLOB	equ 47


NCryptBuffer		typedef BCryptBuffer
PNCryptBuffer		typedef ptr BCryptBuffer
NCryptBufferDesc	typedef BCryptBufferDesc
PNCryptBufferDesc	typedef ptr BCryptBufferDesc

NCRYPT_HANDLE		typedef ULONG_PTR
NCRYPT_PROV_HANDLE	typedef ULONG_PTR
NCRYPT_KEY_HANDLE	typedef ULONG_PTR
NCRYPT_HASH_HANDLE	typedef ULONG_PTR
NCRYPT_SECRET_HANDLE	typedef ULONG_PTR

if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_CIPHER_PADDING_INFO STRUC
cbSize			ULONG ?
dwFlags			dd ?
pbIV			PUCHAR ?
cbIV			ULONG ?
pbOtherInfo		PUCHAR ?
cbOtherInfo		ULONG ?
NCRYPT_CIPHER_PADDING_INFO ENDS
PNCRYPT_CIPHER_PADDING_INFO typedef ptr NCRYPT_CIPHER_PADDING_INFO

NCRYPT_CIPHER_NO_PADDING_FLAG equ 0x00000000
NCRYPT_CIPHER_BLOCK_PADDING_FLAG equ 0x00000001
NCRYPT_CIPHER_OTHER_PADDING_FLAG equ 0x00000002

endif

if (NTDDI_VERSION GE NTDDI_WINBLUE)

NCRYPT_PLATFORM_ATTEST_MAGIC equ 0x44504150  ;; 'PAPD'

NCRYPT_PLATFORM_ATTEST_PADDING_INFO  STRUC
magic			ULONG ? ;; 'PAPD'
pcrMask			ULONG ?
NCRYPT_PLATFORM_ATTEST_PADDING_INFO ENDS

NCRYPT_KEY_ATTEST_MAGIC equ 0x4450414b	;; 'KAPD'

NCRYPT_KEY_ATTEST_PADDING_INFO	STRUC
magic			ULONG ? ;; 'KAPD'
pbKeyBlob		PUCHAR ?
cbKeyBlob		ULONG ?
pbKeyAuth		PUCHAR ?
cbKeyAuth		ULONG ?
NCRYPT_KEY_ATTEST_PADDING_INFO ENDS

endif

NCRYPT_NO_PADDING_FLAG	equ 0x00000001
NCRYPT_PAD_PKCS1_FLAG	equ 0x00000002
NCRYPT_PAD_OAEP_FLAG	equ 0x00000004
NCRYPT_PAD_PSS_FLAG	equ 0x00000008
if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_PAD_CIPHER_FLAG	equ 0x00000010
endif

NCRYPT_REGISTER_NOTIFY_FLAG equ 0x00000001
NCRYPT_UNREGISTER_NOTIFY_FLAG equ 0x00000002
NCRYPT_NO_KEY_VALIDATION equ BCRYPT_NO_KEY_VALIDATION
NCRYPT_MACHINE_KEY_FLAG equ 0x00000020
NCRYPT_SILENT_FLAG	equ 0x00000040
NCRYPT_OVERWRITE_KEY_FLAG equ 0x00000080
NCRYPT_WRITE_KEY_TO_LEGACY_STORE_FLAG equ 0x00000200
NCRYPT_DO_NOT_FINALIZE_FLAG equ 0x00000400
NCRYPT_EXPORT_LEGACY_FLAG equ 0x00000800
if (NTDDI_VERSION GE NTDDI_WINBLUE)
NCRYPT_IGNORE_DEVICE_STATE_FLAG equ 0x00001000
endif
NCRYPT_PERSIST_ONLY_FLAG equ 0x40000000
NCRYPT_PERSIST_FLAG	equ 0x80000000


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

NCRYPT_SILENT_FLAG	equ 0x00000040
if (NTDDI_VERSION GE NTDDI_WINBLUE)
NCRYPT_IGNORE_DEVICE_STATE_FLAG equ 0x00001000
endif

NCryptOpenStorageProvider proto WINAPI :ptr, :LPCWSTR, :DWORD

NCRYPT_CIPHER_OPERATION equ BCRYPT_CIPHER_OPERATION
NCRYPT_HASH_OPERATION	equ BCRYPT_HASH_OPERATION
NCRYPT_ASYMMETRIC_ENCRYPTION_OPERATION equ BCRYPT_ASYMMETRIC_ENCRYPTION_OPERATION
NCRYPT_SECRET_AGREEMENT_OPERATION equ BCRYPT_SECRET_AGREEMENT_OPERATION
NCRYPT_SIGNATURE_OPERATION equ BCRYPT_SIGNATURE_OPERATION
NCRYPT_RNG_OPERATION	equ BCRYPT_RNG_OPERATION
if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_KEY_DERIVATION_OPERATION equ BCRYPT_KEY_DERIVATION_OPERATION
endif
NCryptAlgorithmName	STRUC
pszName			LPWSTR ?
dwClass			dd ?
dwAlgOperations		dd ?
dwFlags			dd ?
NCryptAlgorithmName	ENDS

NCryptEnumAlgorithms proto WINAPI :NCRYPT_PROV_HANDLE, :DWORD, :ptr DWORD, :ptr, :DWORD
NCryptIsAlgSupported proto WINAPI :NCRYPT_PROV_HANDLE, :LPCWSTR, :DWORD

NCRYPT_MACHINE_KEY_FLAG equ 0x00000020

NCryptKeyName		STRUC
pszName			LPWSTR ?
pszAlgid		LPWSTR ?
dwLegacyKeySpec		dd ?
dwFlags			dd ?
NCryptKeyName		ENDS

NCryptEnumKeys proto WINAPI :NCRYPT_PROV_HANDLE, :LPCWSTR, :ptr, :ptr, :DWORD

NCryptProviderName	STRUC
pszName			LPWSTR ?
pszComment		LPWSTR ?
NCryptProviderName	ENDS

NCryptEnumStorageProviders proto WINAPI :ptr, :ptr, :DWORD
NCryptFreeBuffer proto WINAPI :ptr

NCRYPT_MACHINE_KEY_FLAG equ 0x00000020
NCRYPT_SILENT_FLAG	equ 0x00000040

NCryptOpenKey proto WINAPI :NCRYPT_PROV_HANDLE, :ptr, :LPCWSTR, :DWORD, :DWORD

NCRYPT_MACHINE_KEY_FLAG equ 0x00000020
NCRYPT_OVERWRITE_KEY_FLAG equ 0x00000080

NCryptCreatePersistedKey proto WINAPI :NCRYPT_PROV_HANDLE, :ptr, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD

NCRYPT_NAME_PROPERTY	equ <L"Name">
NCRYPT_UNIQUE_NAME_PROPERTY equ <L"Unique Name">
NCRYPT_ALGORITHM_PROPERTY equ <L"Algorithm Name">
NCRYPT_LENGTH_PROPERTY	equ <L"Length">
NCRYPT_LENGTHS_PROPERTY equ <L"Lengths">
NCRYPT_BLOCK_LENGTH_PROPERTY equ <L"Block Length">
if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_CHAINING_MODE_PROPERTY equ <L"Chaining Mode">
NCRYPT_AUTH_TAG_LENGTH	equ <L"AuthTagLength">
endif
NCRYPT_UI_POLICY_PROPERTY equ <L"UI Policy">
NCRYPT_EXPORT_POLICY_PROPERTY equ <L"Export Policy">
NCRYPT_WINDOW_HANDLE_PROPERTY equ <L"HWND Handle">
NCRYPT_USE_CONTEXT_PROPERTY equ <L"Use Context">
NCRYPT_IMPL_TYPE_PROPERTY equ <L"Impl Type">
NCRYPT_KEY_USAGE_PROPERTY equ <L"Key Usage">
NCRYPT_KEY_TYPE_PROPERTY equ <L"Key Type">
NCRYPT_VERSION_PROPERTY equ <L"Version">
NCRYPT_SECURITY_DESCR_SUPPORT_PROPERTY equ <L"Security Descr Support">
NCRYPT_SECURITY_DESCR_PROPERTY equ <L"Security Descr">
NCRYPT_USE_COUNT_ENABLED_PROPERTY equ <L"Enabled Use Count">
NCRYPT_USE_COUNT_PROPERTY equ <L"Use Count">
NCRYPT_LAST_MODIFIED_PROPERTY equ <L"Modified">
NCRYPT_MAX_NAME_LENGTH_PROPERTY equ <L"Max Name Length">
NCRYPT_ALGORITHM_GROUP_PROPERTY equ <L"Algorithm Group">
NCRYPT_DH_PARAMETERS_PROPERTY equ BCRYPT_DH_PARAMETERS
NCRYPT_PROVIDER_HANDLE_PROPERTY equ <L"Provider Handle">
NCRYPT_PIN_PROPERTY	equ <L"SmartCardPin">
NCRYPT_READER_PROPERTY	equ <L"SmartCardReader">
NCRYPT_SMARTCARD_GUID_PROPERTY equ <L"SmartCardGuid">
NCRYPT_CERTIFICATE_PROPERTY equ <L"SmartCardKeyCertificate">
NCRYPT_PIN_PROMPT_PROPERTY equ <L"SmartCardPinPrompt">
NCRYPT_USER_CERTSTORE_PROPERTY equ <L"SmartCardUserCertStore">
NCRYPT_ROOT_CERTSTORE_PROPERTY equ <L"SmartcardRootCertStore">
NCRYPT_SECURE_PIN_PROPERTY equ <L"SmartCardSecurePin">
NCRYPT_ASSOCIATED_ECDH_KEY equ <L"SmartCardAssociatedECDHKey">
NCRYPT_SCARD_PIN_ID	equ <L"SmartCardPinId">
NCRYPT_SCARD_PIN_INFO	equ <L"SmartCardPinInfo">
if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_READER_ICON_PROPERTY equ <L"SmartCardReaderIcon">
NCRYPT_KDF_SECRET_VALUE equ <L"KDFKeySecret">

NCRYPT_PCP_PLATFORM_TYPE_PROPERTY equ <L"PCP_PLATFORM_TYPE">
NCRYPT_PCP_PROVIDER_VERSION_PROPERTY equ <L"PCP_PROVIDER_VERSION">
NCRYPT_PCP_EKPUB_PROPERTY equ <L"PCP_EKPUB">
NCRYPT_PCP_EKCERT_PROPERTY equ <L"PCP_EKCERT">
NCRYPT_PCP_EKNVCERT_PROPERTY equ <L"PCP_EKNVCERT">
NCRYPT_PCP_SRKPUB_PROPERTY equ <L"PCP_SRKPUB">
NCRYPT_PCP_PCRTABLE_PROPERTY equ <L"PCP_PCRTABLE">
NCRYPT_PCP_CHANGEPASSWORD_PROPERTY equ <L"PCP_CHANGEPASSWORD">
NCRYPT_PCP_PASSWORD_REQUIRED_PROPERTY equ <L"PCP_PASSWORD_REQUIRED">
NCRYPT_PCP_USAGEAUTH_PROPERTY equ <L"PCP_USAGEAUTH">
NCRYPT_PCP_MIGRATIONPASSWORD_PROPERTY equ <L"PCP_MIGRATIONPASSWORD">
NCRYPT_PCP_EXPORT_ALLOWED_PROPERTY equ <L"PCP_EXPORT_ALLOWED">
NCRYPT_PCP_STORAGEPARENT_PROPERTY equ <L"PCP_STORAGEPARENT">
NCRYPT_PCP_PROVIDERHANDLE_PROPERTY equ <L"PCP_PROVIDERMHANDLE">
NCRYPT_PCP_PLATFORMHANDLE_PROPERTY equ <L"PCP_PLATFORMHANDLE">
NCRYPT_PCP_PLATFORM_BINDING_PCRMASK_PROPERTY equ <L"PCP_PLATFORM_BINDING_PCRMASK">
NCRYPT_PCP_PLATFORM_BINDING_PCRDIGESTLIST_PROPERTY equ <L"PCP_PLATFORM_BINDING_PCRDIGESTLIST">
NCRYPT_PCP_PLATFORM_BINDING_PCRDIGEST_PROPERTY equ <L"PCP_PLATFORM_BINDING_PCRDIGEST">
NCRYPT_PCP_KEY_USAGE_POLICY_PROPERTY equ <L"PCP_KEY_USAGE_POLICY">
NCRYPT_PCP_TPM12_IDBINDING_PROPERTY equ <L"PCP_TPM12_IDBINDING">
NCRYPT_PCP_TPM12_IDBINDING_DYNAMIC_PROPERTY equ <L"PCP_TPM12_IDBINDING_DYNAMIC">
NCRYPT_PCP_TPM12_IDACTIVATION_PROPERTY equ <L"PCP_TPM12_IDACTIVATION">
NCRYPT_PCP_KEYATTESTATION_PROPERTY equ <L"PCP_TPM12_KEYATTESTATION">
NCRYPT_PCP_ALTERNATE_KEY_STORAGE_LOCATION_PROPERTY equ <L"PCP_ALTERNATE_KEY_STORAGE_LOCATION">

NCRYPT_TPM12_PROVIDER	equ (0x00010000)
NCRYPT_PCP_SIGNATURE_KEY equ (0x00000001)
NCRYPT_PCP_ENCRYPTION_KEY equ (0x00000002)
NCRYPT_PCP_GENERIC_KEY	equ (NCRYPT_PCP_SIGNATURE_KEY OR NCRYPT_PCP_ENCRYPTION_KEY)
NCRYPT_PCP_STORAGE_KEY	equ (0x00000004)
NCRYPT_PCP_IDENTITY_KEY equ (0x00000008)
endif

if (NTDDI_VERSION GE NTDDI_WIN8)
NCRYPT_INITIALIZATION_VECTOR equ BCRYPT_INITIALIZATION_VECTOR
endif

NCRYPT_MAX_PROPERTY_NAME equ 64

NCRYPT_MAX_PROPERTY_DATA equ 0x100000

NCRYPT_ALLOW_EXPORT_FLAG equ 0x00000001
NCRYPT_ALLOW_PLAINTEXT_EXPORT_FLAG equ 0x00000002
NCRYPT_ALLOW_ARCHIVING_FLAG equ 0x00000004
NCRYPT_ALLOW_PLAINTEXT_ARCHIVING_FLAG equ 0x00000008

NCRYPT_IMPL_HARDWARE_FLAG equ 0x00000001
NCRYPT_IMPL_SOFTWARE_FLAG equ 0x00000002
NCRYPT_IMPL_REMOVABLE_FLAG equ 0x00000008
NCRYPT_IMPL_HARDWARE_RNG_FLAG equ 0x00000010

NCRYPT_ALLOW_DECRYPT_FLAG equ 0x00000001
NCRYPT_ALLOW_SIGNING_FLAG equ 0x00000002
NCRYPT_ALLOW_KEY_AGREEMENT_FLAG equ 0x00000004
NCRYPT_ALLOW_ALL_USAGES equ 0x00ffffff

NCRYPT_UI_PROTECT_KEY_FLAG equ 0x00000001
NCRYPT_UI_FORCE_HIGH_PROTECTION_FLAG equ 0x00000002
if (NTDDI_VERSION GE NTDDI_WINBLUE)
NCRYPT_UI_FINGERPRINT_PROTECTION_FLAG equ 0x00000004
NCRYPT_UI_APPCONTAINER_ACCESS_MEDIUM_FLAG equ 0x00000008
endif


NCRYPT_UI_POLICY	STRUC
dwVersion		dd ?
dwFlags			dd ?
pszCreationTitle	LPCWSTR ?
pszFriendlyName		LPCWSTR ?
pszDescription		LPCWSTR ?
NCRYPT_UI_POLICY	ENDS

NCRYPT_SUPPORTED_LENGTHS STRUC
dwMinLength		dd ?
dwMaxLength		dd ?
dwIncrement		dd ?
dwDefaultLength		dd ?
NCRYPT_SUPPORTED_LENGTHS ENDS

NCRYPT_PERSIST_ONLY_FLAG equ 0x40000000

NCryptGetProperty proto WINAPI :NCRYPT_HANDLE, :LPCWSTR, :PBYTE, :DWORD, :ptr, :DWORD

NCRYPT_PERSIST_FLAG	equ 0x80000000
NCRYPT_PERSIST_ONLY_FLAG equ 0x40000000

NCryptSetProperty proto WINAPI :NCRYPT_HANDLE, :LPCWSTR, :PBYTE, :DWORD, :DWORD

NCRYPT_WRITE_KEY_TO_LEGACY_STORE_FLAG equ 0x00000200

NCryptFinalizeKey proto WINAPI :NCRYPT_KEY_HANDLE, :DWORD
NCryptEncrypt proto WINAPI :NCRYPT_KEY_HANDLE, :PBYTE, :DWORD, :ptr, :PBYTE, :DWORD, :ptr, :DWORD
NCryptDecrypt proto WINAPI :NCRYPT_KEY_HANDLE, :PBYTE, :DWORD, :ptr, :PBYTE, :DWORD, :ptr, :DWORD

if (NTDDI_VERSION GE NTDDI_WIN8)

NCRYPT_KEY_BLOB_HEADER	STRUC
cbSize			ULONG ?
dwMagic			ULONG ?
cbAlgName		ULONG ?
cbKeyData		ULONG ?
NCRYPT_KEY_BLOB_HEADER	ENDS
PNCRYPT_KEY_BLOB_HEADER typedef ptr NCRYPT_KEY_BLOB_HEADER

NCRYPT_CIPHER_KEY_BLOB_MAGIC equ 0x52485043	 ;; CPHR
NCRYPT_PROTECTED_KEY_BLOB_MAGIC equ 0x4B545250	    ;; PRTK

NCRYPT_CIPHER_KEY_BLOB	equ <L"CipherKeyBlob">
NCRYPT_PROTECTED_KEY_BLOB equ <L"ProtectedKeyBlob">

endif

NCRYPT_PKCS7_ENVELOPE_BLOB equ <L"PKCS7_ENVELOPE">
NCRYPT_PKCS8_PRIVATE_KEY_BLOB equ <L"PKCS8_PRIVATEKEY">
NCRYPT_OPAQUETRANSPORT_BLOB equ <L"OpaqueTransport">


NCRYPT_MACHINE_KEY_FLAG equ 0x00000020
NCRYPT_DO_NOT_FINALIZE_FLAG equ 0x00000400
NCRYPT_EXPORT_LEGACY_FLAG equ 0x00000800

NCryptImportKey proto WINAPI :NCRYPT_PROV_HANDLE, :NCRYPT_KEY_HANDLE, :LPCWSTR, :ptr, :ptr, :PBYTE, :DWORD, :DWORD
NCryptExportKey proto WINAPI :NCRYPT_KEY_HANDLE, :NCRYPT_KEY_HANDLE, :LPCWSTR, :ptr, :PBYTE, :DWORD, :ptr, :DWORD
NCryptSignHash proto WINAPI :NCRYPT_KEY_HANDLE, :ptr, :PBYTE, :DWORD, :PBYTE, :DWORD, :ptr, :DWORD
NCryptVerifySignature proto WINAPI :NCRYPT_KEY_HANDLE, :ptr, :PBYTE, :DWORD, :PBYTE, :DWORD, :DWORD
NCryptDeleteKey proto WINAPI :NCRYPT_KEY_HANDLE, :DWORD
NCryptFreeObject proto WINAPI :NCRYPT_HANDLE
NCryptIsKeyHandle proto WINAPI :NCRYPT_KEY_HANDLE
NCryptTranslateHandle proto WINAPI :ptr, :ptr, :HCRYPTPROV, :HCRYPTKEY, :DWORD, :DWORD

NCRYPT_REGISTER_NOTIFY_FLAG equ 0x00000001
NCRYPT_UNREGISTER_NOTIFY_FLAG equ 0x00000002
NCRYPT_MACHINE_KEY_FLAG equ 0x00000020

NCryptNotifyChangeKey proto WINAPI :NCRYPT_PROV_HANDLE, :ptr, :DWORD
NCryptSecretAgreement proto WINAPI :NCRYPT_KEY_HANDLE, :NCRYPT_KEY_HANDLE, :ptr, :DWORD
NCryptDeriveKey proto WINAPI :NCRYPT_SECRET_HANDLE, :LPCWSTR, :ptr, :PBYTE, :DWORD, :ptr, :ULONG

if (NTDDI_VERSION GE NTDDI_WIN8)
NCryptKeyDerivation proto WINAPI :NCRYPT_KEY_HANDLE, :ptr, :PUCHAR, :DWORD, :ptr, :ULONG
endif
NCRYPT_KEY_STORAGE_INTERFACE_VERSION equ BCRYPT_MAKE_INTERFACE_VERSION(1,0)
NCRYPT_KEY_STORAGE_INTERFACE_VERSION_2 equ BCRYPT_MAKE_INTERFACE_VERSION(2,0)

endif

endif
