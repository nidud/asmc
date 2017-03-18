ifndef WINTRUST_H
WINTRUST_H equ 1

include wincrypt.inc

ifndef WIN_CERT_REVISION_1_0   ;; there were duplicate definitions in winbase.h
WT_DEFINE_ALL_APIS equ 1
;else
;WT_DEFINE_ALL_APIS equ <>
endif

;include pshpack8.inc

WINTRUST_CONFIG_REGPATH			    equ <L"Software\\Microsoft\\Cryptography\\Wintrust\\Config">
WINTRUST_MAX_HEADER_BYTES_TO_MAP_VALUE_NAME equ <L"MaxHeaderBytesToMap">
WINTRUST_MAX_HEADER_BYTES_TO_MAP_DEFAULT    equ 0x00A00000
WINTRUST_MAX_HASH_BYTES_TO_MAP_VALUE_NAME   equ <L"MaxHashBytesToMap">
WINTRUST_MAX_HASH_BYTES_TO_MAP_DEFAULT	    equ 0x00100000

WTD_UI_ALL		equ 1
WTD_UI_NONE		equ 2
WTD_UI_NOBAD		equ 3
WTD_UI_NOGOOD		equ 4

WTD_REVOKE_NONE		equ 0x00000000
WTD_REVOKE_WHOLECHAIN	equ 0x00000001

WTD_CHOICE_FILE		equ 1
WTD_CHOICE_CATALOG	equ 2
WTD_CHOICE_BLOB		equ 3
WTD_CHOICE_SIGNER	equ 4
WTD_CHOICE_CERT		equ 5

WTD_STATEACTION_IGNORE		equ 0x00000000
WTD_STATEACTION_VERIFY		equ 0x00000001
WTD_STATEACTION_CLOSE		equ 0x00000002
WTD_STATEACTION_AUTO_CACHE	equ 0x00000003
WTD_STATEACTION_AUTO_CACHE_FLUSH equ 0x00000004

WTD_PROV_FLAGS_MASK		equ 0x0000FFFF
WTD_USE_IE4_TRUST_FLAG		equ 0x00000001
WTD_NO_IE4_CHAIN_FLAG		equ 0x00000002
WTD_NO_POLICY_USAGE_FLAG	equ 0x00000004
WTD_REVOCATION_CHECK_NONE	equ 0x00000010
WTD_REVOCATION_CHECK_END_CERT	equ 0x00000020
WTD_REVOCATION_CHECK_CHAIN	equ 0x00000040
WTD_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT equ 0x00000080
WTD_SAFER_FLAG			equ 0x00000100
WTD_HASH_ONLY_FLAG		equ 0x00000200
WTD_USE_DEFAULT_OSVER_CHECK	equ 0x00000400
WTD_LIFETIME_SIGNING_FLAG	equ 0x00000800
WTD_CACHE_ONLY_URL_RETRIEVAL	equ 0x00001000	; affects CRL retrieval and AIA retrieval

WTD_UICONTEXT_EXECUTE	equ 0
WTD_UICONTEXT_INSTALL	equ 1

WINTRUST_DATA		STRUC
cbStruct		dd ?	;; = sizeof(WINTRUST_DATA)
pPolicyCallbackData	PVOID ? ;; optional: used to pass data between the app and policy
pSIPClientData		PVOID ? ;; optional: used to pass data between the app and SIP.
dwUIChoice		dd ?	;; required: UI choice.	 One of the following.
fdwRevocationChecks	dd ?	;; required: certificate revocation check options
dwUnionChoice		dd ?	;; required: which structure is being passed in?
UNION
 pFile			PWINTRUST_FILE_INFO ?
 pCatalog		PWINTRUST_CATALOG_INFO ?
 pBlob			PWINTRUST_BLOB_INFO ?
 pSgnr			PWINTRUST_SGNR_INFO ?
 pCert			PWINTRUST_CERT_INFO ?
ENDS
dwStateAction		dd ?	;; optional (Catalog File Processing)
hWVTStateData		HANDLE ?	;; optional (Catalog File Processing)
pwszURLReference	LPWCHAR ?	;; optional: (future) used to determine zone.
dwProvFlags		dd ?
dwUIContext		dd ?
WINTRUST_DATA		ENDS
PWINTRUST_DATA		typedef ptr WINTRUST_DATA

WINTRUST_FILE_INFO	STRUC
cbStruct		dd ?		;; = sizeof(WINTRUST_FILE_INFO)
pcwszFilePath		LPCWSTR ?	;; required, file name to be verified
hFile			HANDLE ?	;; optional, open handle to pcwszFilePath
pgKnownSubject		LPGUID ?	;; optional: fill if the subject type is known.
WINTRUST_FILE_INFO	ENDS
PWINTRUST_FILE_INFO	typedef ptr WINTRUST_FILE_INFO

WINTRUST_CATALOG_INFO	STRUC
cbStruct		dd ?	;; = sizeof(WINTRUST_CATALOG_INFO)
dwCatalogVersion	dd ?	;; optional: Catalog version number
pcwszCatalogFilePath	LPCWSTR ?	;; required: path/name to Catalog file
pcwszMemberTag		LPCWSTR ?	;; optional: tag to member in Catalog
pcwszMemberFilePath	LPCWSTR ?	;; required: path/name to member file
hMemberFile		HANDLE ?	;; optional: open handle to pcwszMemberFilePath
pbCalculatedFileHash	LPBYTE ?	;; optional: pass in the calculated hash
cbCalculatedFileHash	dd ?	;; optional: pass in the count bytes of the calc hash
pcCatalogContext	PCCTL_CONTEXT ? ;; optional: pass in to use instead of CatalogFilePath.
WINTRUST_CATALOG_INFO	ENDS
PWINTRUST_CATALOG_INFO	typedef ptr WINTRUST_CATALOG_INFO

WINTRUST_BLOB_INFO	STRUC
cbStruct		dd ?	;; = sizeof(WINTRUST_BLOB_INFO)
gSubject		GUID <> ;; SIP to load
pcwszDisplayName	LPCWSTR ?	;; display name of object
cbMemObject		dd ?
pbMemObject		LPBYTE ?
cbMemSignedMsg		dd ?
pbMemSignedMsg		LPBYTE ?
WINTRUST_BLOB_INFO	ENDS
PWINTRUST_BLOB_INFO	typedef ptr WINTRUST_BLOB_INFO

WINTRUST_SGNR_INFO	STRUC
cbStruct		dd ?		;; = sizeof(WINTRUST_SGNR_INFO)
pcwszDisplayName	LPCWSTR ?	;; name of the "thing" the pbMem is pointing to.
psSignerInfo		LPCMSG_SIGNER_INFO ?
chStores		dd ?		;; number of stores in pahStores
pahStores		LPHCERTSTORE ?	;; array of stores to add to internal list
WINTRUST_SGNR_INFO	ENDS
PWINTRUST_SGNR_INFO	typedef ptr WINTRUST_SGNR_INFO

WTCI_DONT_OPEN_STORES	equ 0x00000001	; only open dummy "root" all other are in pahStores.
WTCI_OPEN_ONLY_ROOT	equ 0x00000002
WTCI_USE_LOCAL_MACHINE	equ 0x00000004	; Local machine context

WINTRUST_CERT_INFO	STRUC
cbStruct		dd ?		;; = sizeof(WINTRUST_CERT_INFO)
pcwszDisplayName	LPCWSTR ?	;; display name
psCertContext		LPCERT_CONTEXT ?
chStores		dd ?		;; number of stores in pahStores
pahStores		LPHCERTSTORE ?	;; array of stores to add to internal list
dwFlags			dd ?
psftVerifyAsOf		LPFILETIME ?	;; if not null, each cert will be validated as of this time.
WINTRUST_CERT_INFO	ENDS
PWINTRUST_CERT_INFO	typedef ptr WINTRUST_CERT_INFO

;include <poppack.h>

WinVerifyTrust proto _CType \
		  hwnd: HWND,
	    pgActionID: ptr GUID,
	      pWVTData: LPVOID

WinVerifyTrustEx proto _CType \
		  hwnd: HWND,
	    pgActionID: ptr GUID,
	 pWinTrustData: LPWINTRUST_DATA

WTPF_TRUSTTEST		equ 0x00000020	;; trust any "TEST" certificate
WTPF_TESTCANBEVALID	equ 0x00000080
WTPF_IGNOREEXPIRATION	equ 0x00000100	;; Use expiration date
WTPF_IGNOREREVOKATION	equ 0x00000200	;; Do revocation check
WTPF_OFFLINEOK_IND	equ 0x00000400	;; off-line is ok individual certs
WTPF_OFFLINEOK_COM	equ 0x00000800	;; off-line is ok commercial certs
WTPF_OFFLINEOKNBU_IND	equ 0x00001000	;; off-line is ok individual certs, no bad ui
WTPF_OFFLINEOKNBU_COM	equ 0x00002000	;; off-line is ok commercial certs, no bad ui
WTPF_VERIFY_V1_OFF	equ 0x00010000	;; turn verify of v1 certs off
WTPF_IGNOREREVOCATIONONTS equ 0x00020000  ;; ignore TimeStamp revocation checks
WTPF_ALLOWONLYPERTRUST	equ 0x00040000	;; allow only items in personal trust db.

;void
WintrustGetRegPolicyFlags proto _CType \
	 pdwPolicyFlags: LPDWORD

;BOOL
WintrustSetRegPolicyFlags proto _CType \
	  dwPolicyFlags: DWORD



TRUSTERROR_STEP_WVTPARAMS	equ 0
TRUSTERROR_STEP_FILEIO		equ 2
TRUSTERROR_STEP_SIP		equ 3
TRUSTERROR_STEP_SIPSUBJINFO	equ 5
TRUSTERROR_STEP_CATALOGFILE	equ 6
TRUSTERROR_STEP_CERTSTORE	equ 7
TRUSTERROR_STEP_MESSAGE		equ 8
TRUSTERROR_STEP_MSG_SIGNERCOUNT equ 9
TRUSTERROR_STEP_MSG_INNERCNTTYPE equ 10
TRUSTERROR_STEP_MSG_INNERCNT	equ 11
TRUSTERROR_STEP_MSG_STORE	equ 12
TRUSTERROR_STEP_MSG_SIGNERINFO	equ 13
TRUSTERROR_STEP_MSG_SIGNERCERT	equ 14
TRUSTERROR_STEP_MSG_CERTCHAIN	equ 15
TRUSTERROR_STEP_MSG_COUNTERSIGINFO equ 16
TRUSTERROR_STEP_MSG_COUNTERSIGCERT equ 17
TRUSTERROR_STEP_VERIFY_MSGHASH	equ 18
TRUSTERROR_STEP_VERIFY_MSGINDIRECTDATA equ 19

TRUSTERROR_STEP_FINAL_WVTINIT	equ 30
TRUSTERROR_STEP_FINAL_INITPROV	equ 31
TRUSTERROR_STEP_FINAL_OBJPROV	equ 32
TRUSTERROR_STEP_FINAL_SIGPROV	equ 33
TRUSTERROR_STEP_FINAL_CERTPROV	equ 34
TRUSTERROR_STEP_FINAL_CERTCHKPROV equ 35
TRUSTERROR_STEP_FINAL_POLICYPROV equ 36
TRUSTERROR_STEP_FINAL_UIPROV	equ 37

TRUSTERROR_MAX_STEPS		equ 38

;PVOID
PFN_CPD_MEM_ALLOC_T typedef proto _CType \
		cbSize: DWORD
PFN_CPD_MEM_ALLOC typedef ptr PFN_CPD_MEM_ALLOC_T

;void
PFN_CPD_MEM_FREE_T typedef proto _CType \
	    pvMem2Free: PVOID
PFN_CPD_MEM_FREE typedef ptr PFN_CPD_MEM_FREE_T

;typedef CRYPT_PROVIDER_DATA
;typedef CRYPT_PROVIDER_SGNR
;typedef CRYPT_PROVIDER_PRIVDATA

;BOOL
PFN_CPD_ADD_STORE_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA,
	    hStore2Add: HCERTSTORE
PFN_CPD_ADD_STORE typedef PFN_CPD_ADD_STORE_T

;BOOL
PFN_CPD_ADD_SGNR_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA,
	fCounterSigner: BOOL,
	     idxSigner: DWORD,
	     pSgnr2Add: ptr CRYPT_PROVIDER_SGNR
PFN_CPD_ADD_SGNR typedef ptr PFN_CPD_ADD_SGNR_T

;BOOL
PFN_CPD_ADD_CERT_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA,
	     idxSigner: DWORD,
	fCounterSigner: BOOL,
      idxCounterSigner: DWORD,
	     pCert2Add: PCCERT_CONTEXT
PFN_CPD_ADD_CERT typedef ptr PFN_CPD_ADD_CERT_T

;BOOL
PFN_CPD_ADD_PRIVDATA_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA,
	 pPrivData2Add: ptr CRYPT_PROVIDER_PRIVDATA
PFN_CPD_ADD_PRIVDATA typedef ptr PFN_CPD_ADD_PRIVDATA_T

;HRESULT
PFN_PROVIDER_INIT_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVIDER_INIT_CALL typedef ptr PFN_PROVIDER_INIT_CALL_T

;HRESULT
PFN_PROVIDER_OBJTRUST_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVIDER_OBJTRUST_CALL typedef ptr PFN_PROVIDER_OBJTRUST_CALL_T

;HRESULT
PFN_PROVIDER_SIGTRUST_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVIDER_SIGTRUST_CALL typedef ptr PFN_PROVIDER_SIGTRUST_CALL_T

;HRESULT
PFN_PROVIDER_CERTTRUST_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVIDER_CERTTRUST_CALL typedef ptr PFN_PROVIDER_CERTTRUST_CALL_T

;HRESULT
PFN_PROVIDER_FINALPOLICY_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVIDER_FINALPOLICY_CALL typedef PFN_PROVIDER_FINALPOLICY_CALL_T

;HRESULT
PFN_PROVIDER_TESTFINALPOLICY_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVIDER_TESTFINALPOLICY_CALL typedef ptr PFN_PROVIDER_TESTFINALPOLICY_CALL_T

;HRESULT
PFN_PROVIDER_CLEANUP_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVIDER_CLEANUP_CALL typedef PFN_PROVIDER_CLEANUP_CALL_T

;BOOL
PFN_PROVIDER_CERTCHKPOLICY_CALL_T typedef proto _CType \
	     pProvData: ptr CRYPT_PROVIDER_DATA,
	     idxSigner: DWORD,
   fCounterSignerChain: BOOL,
      idxCounterSigner: DWORD


WVT_OFFSETOF macro t,f
	exitm<t.f>
	endm

;; WOB #1251526 -- macro must check whether _all_ bytes of the member
;; lie within the struct size specified

WVT_ISINSTRUCT macro structtypedef, structpassedsize, member
	if (structtypedef.member + sizeof(structtypedef.member)) LE structpassedsize
	   exitm<1>
	endif
	exitm<0>
	endm

WVT_IS_CBSTRUCT_GT_MEMBEROFFSET macro structtypedef, structpassedsize, member
	exitm<WVT_ISINSTRUCT(structtypedef, structpassedsize, member)>
	endm

;include <pshpack8.h>

CPD_CHOICE_SIP				equ 1
CPD_USE_NT5_CHAIN_FLAG			equ 0x80000000
CPD_REVOCATION_CHECK_NONE		equ 0x00010000
CPD_REVOCATION_CHECK_END_CERT		equ 0x00020000
CPD_REVOCATION_CHECK_CHAIN		equ 0x00040000
CPD_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT equ 0x00080000
CPD_UISTATE_MODE_PROMPT			equ 0x00000000
CPD_UISTATE_MODE_BLOCK			equ 0x00000001
CPD_UISTATE_MODE_ALLOW			equ 0x00000002
CPD_UISTATE_MODE_MASK			equ 0x00000003

CRYPT_PROVIDER_DATA	STRUC
cbStruct		dd ?		;; = sizeof(TRUST_PROVIDER_DATA) (set in WVT)
pWintrustData		LPWINTRUST_DATA ? ;; NOT verified (set in WVT)
fOpenedFile		BOOL ?		;; the provider opened the file handle (if applicable)
hWndParent		HWND ?		;; if passed in, else, Desktop hWnd (set in WVT).
pgActionID		LPGUID ?	;; represents the Provider combination (set in WVT).
hProv			HCRYPTPROV ?	;; set to NULL to let CryptoAPI to assign.
dwError			dd ?		;; error if a low-level, system error was encountered
dwRegSecuritySettings	dd ?		;; ie security settings (set in WVT)
dwRegPolicySettings	dd ?		;; setreg settings (set in WVT)
psPfns			PCRYPT_PROVIDER_FUNCTIONS ?
cdwTrustStepErrors	dd ?		;; set in WVT.
padwTrustStepErrors	LPDWORD ?	;; allocated in WVT.  filled in WVT & Trust Provider
chStores		dd ?		;; number of stores in pahStores (root set in WVT)
pahStores		LPHCERTSTORE ?	;; array of known stores (root set in WVT) root is ALWAYS #0!!!
dwEncoding		dd ?		;; message encoding type (set in WVT and Signature Prov)
hMsg			HCRYPTMSG ?	;; set in Signature Prov.
csSigners		dd ?		;; use Add2 and Get functions!
pasSigners		PCRYPT_PROVIDER_SGNR ?
csProvPrivData		dd ?		;; use Add2 and Get functions!
pasProvPrivData		PCRYPT_PROVIDER_PRIVDATA ?
dwSubjectChoice		dd ?
UNION
 pPDSip			PPROVDATA_SIP ?
ENDS
pszUsageOID		LPSTR ?		;; set in Init Provider
fRecallWithState	BOOL ?		;; state was maintained for Catalog Files.
sftSystemTime		FILETIME <>
pszCTLSignerUsageOID	LPSTR ?
dwProvFlags		dd ?		;; LOWORD intialized from WINTRUST_DATA's dwProvFlags.
dwFinalError		dd ?
pRequestUsage		PCERT_USAGE_MATCH ?
dwTrustPubSettings	dd ?
dwUIStateFlags		dd ?
CRYPT_PROVIDER_DATA	ENDS
PCRYPT_PROVIDER_DATA	typedef ptr CRYPT_PROVIDER_DATA

CRYPT_PROVIDER_FUNCTIONS STRUC
cbStruct		dd ?
pfnAlloc		PFN_CPD_MEM_ALLOC ?	;; set in WVT
pfnFree			PFN_CPD_MEM_FREE ?	;; set in WVT
pfnAddStore2Chain	PFN_CPD_ADD_STORE ?	;; call to add a store to the chain.
pfnAddSgnr2Chain	PFN_CPD_ADD_SGNR ?	;; call to add a sgnr struct to a msg struct sgnr chain
pfnAddCert2Chain	PFN_CPD_ADD_CERT ?	;; call to add a cert struct to a sgnr struct cert chain
pfnAddPrivData2Chain	PFN_CPD_ADD_PRIVDATA ?	;; call to add provider private data to struct.
pfnInitialize		PFN_PROVIDER_INIT_CALL ?	;; initialize Policy data.
pfnObjectTrust		PFN_PROVIDER_OBJTRUST_CALL ?	;; build info up to the signer info(s).
pfnSignatureTrust	PFN_PROVIDER_SIGTRUST_CALL ?	;; build info to the signing cert
pfnCertificateTrust	PFN_PROVIDER_CERTTRUST_CALL ?	;; build the chain
pfnFinalPolicy		PFN_PROVIDER_FINALPOLICY_CALL ? ;; final call to policy
pfnCertCheckPolicy	PFN_PROVIDER_CERTCHKPOLICY_CALL ?	;; check each cert will building chain
pfnTestFinalPolicy	PFN_PROVIDER_TESTFINALPOLICY_CALL ?	;; dump structures to a file (or whatever the policy chooses)
psUIpfns		PCRYPT_PROVUI_FUNCS ?
pfnCleanupPolicy	PFN_PROVIDER_CLEANUP_CALL ?	;; PRIVDATA cleanup routine.
CRYPT_PROVIDER_FUNCTIONS ENDS
PCRYPT_PROVIDER_FUNCTIONS typedef ptr CRYPT_PROVIDER_FUNCTIONS


;BOOL
PFN_PROVUI_CALL_T typedef proto _CType \
    hWndSecurityDialog: HWND,
	     pProvData: ptr CRYPT_PROVIDER_DATA
PFN_PROVUI_CALL typedef ptr PFN_PROVUI_CALL_T

CRYPT_PROVUI_FUNCS	STRUC
cbStruct		dd ?
psUIData		PCRYPT_PROVUI_DATA ?
pfnOnMoreInfoClick	PFN_PROVUI_CALL ?
pfnOnMoreInfoClickDefault PFN_PROVUI_CALL ?
pfnOnAdvancedClick	PFN_PROVUI_CALL ?
pfnOnAdvancedClickDefault PFN_PROVUI_CALL ?
CRYPT_PROVUI_FUNCS	ENDS
PCRYPT_PROVUI_FUNCS	typedef ptr CRYPT_PROVUI_FUNCS

CRYPT_PROVUI_DATA	STRUC
cbStruct		dd ?
dwFinalError		dd ?
pYesButtonText		LPWCHAR ?	;; default: "&Yes"
pNoButtonText		LPWCHAR ?	;; default: "&No"
pMoreInfoButtonText	LPWCHAR ?	;; default: "&More Info"
pAdvancedLinkText	LPWCHAR ?	;; default: <none>
pCopyActionText		LPWCHAR ?
pCopyActionTextNoTS	LPWCHAR ?
pCopyActionTextNotSigned LPWCHAR ?
CRYPT_PROVUI_DATA	ENDS
PCRYPT_PROVUI_DATA	typedef ptr CRYPT_PROVUI_DATA

SGNR_TYPE_TIMESTAMP	equ 0x00000010

CRYPT_PROVIDER_SGNR	STRUC
cbStruct		dd ?
sftVerifyAsOf		FILETIME <>	;; either today's filetime or the timestamps
csCertChain		dd ?	;; use Add2 and Get functions!
pasCertChain		PCRYPT_PROVIDER_CERT ?
dwSignerType		dd ?	;; set if known by policy
psSigner		LPCMSG_SIGNER_INFO ?	;; must use the pfnAlloc allocator!
dwError			dd ?	;; error encounted while building/verifying the signer.
csCounterSigners	dd ?	;; use Add2 and Get functions!
pasCounterSigners	PCRYPT_PROVIDER_SGNR ?
pChainContext		PCCERT_CHAIN_CONTEXT ?
CRYPT_PROVIDER_SGNR	ENDS
PCRYPT_PROVIDER_SGNR	typedef ptr CRYPT_PROVIDER_SGNR

CERT_CONFIDENCE_SIG	equ 0x10000000	; this cert
CERT_CONFIDENCE_TIME	equ 0x01000000	; issuer cert
CERT_CONFIDENCE_TIMENEST equ 0x00100000	 ; this cert
CERT_CONFIDENCE_AUTHIDEXT equ 0x00010000  ; this cert
CERT_CONFIDENCE_HYGIENE equ 0x00001000	; this cert
CERT_CONFIDENCE_HIGHEST equ 0x11111000

CRYPT_PROVIDER_CERT	STRUC
cbStruct		dd ?
pCert			PCCERT_CONTEXT ?	;; must have its own ref-count!
fCommercial		BOOL ?
fTrustedRoot		BOOL ?	;; certchk policy should set this.
fSelfSigned		BOOL ?	;; set in cert provider
fTestCert		BOOL ?	;; certchk policy will set
dwRevokedReason		dd ?
dwConfidence		dd ?	;; set in the Certificate Provider
dwError			dd ?
pTrustListContext	LPCTL_CONTEXT ?
fTrustListSignerCert	BOOL ?
pCtlContext		PCCTL_CONTEXT ?
dwCtlError		dd ?
fIsCyclic		BOOL ?
pChainElement		PCERT_CHAIN_ELEMENT ?
CRYPT_PROVIDER_CERT	ENDS
PCRYPT_PROVIDER_CERT	typedef ptr CRYPT_PROVIDER_CERT

CRYPT_PROVIDER_PRIVDATA STRUC
cbStruct		dd ?
gProviderID		GUID <>
cbProvData		dd ?
pvProvData		PVOID ?
CRYPT_PROVIDER_PRIVDATA ENDS
PCRYPT_PROVIDER_PRIVDATA typedef ptr CRYPT_PROVIDER_PRIVDATA

PROVDATA_SIP		STRUC
cbStruct		dd ?	;; = sizeof(PROVDATA_SIP)
gSubject		GUID <> ;; subject guid of file/member file. (set in Sig Prov)
pSip			PSIP_DISPATCH_INFO ?
pCATSip			PSIP_DISPATCH_INFO ?
psSipSubjectInfo	PSIP_SUBJECTINFO ?
psSipCATSubjectInfo	PSIP_SUBJECTINFO ?
psIndirectData		PSIP_INDIRECT_DATA ?
PROVDATA_SIP		ENDS
PPROVDATA_SIP		typedef ptr PROVDATA_SIP

;;////////////////////////////////////////////////////////////////////////////
;;
;; structures used to register action IDs
;;----------------------------------------------------------------------------
;;
WT_CURRENT_VERSION	equ 0x00000200

CRYPT_TRUST_REG_ENTRY	STRUC
cbStruct		dd ?
pwszDLLName		LPWCHAR ?
pwszFunctionName	LPWCHAR ?	;; no more than WT_MAX_FUNC_NAME!
CRYPT_TRUST_REG_ENTRY	ENDS
PCRYPT_TRUST_REG_ENTRY	typedef ptr CRYPT_TRUST_REG_ENTRY

CRYPT_REGISTER_ACTIONID STRUC
cbStruct		dd ?
sInitProvider		CRYPT_TRUST_REG_ENTRY ?
sObjectProvider		CRYPT_TRUST_REG_ENTRY ?
sSignatureProvider	CRYPT_TRUST_REG_ENTRY ?
sCertificateProvider	CRYPT_TRUST_REG_ENTRY ?
sCertificatePolicyProvider CRYPT_TRUST_REG_ENTRY ?
sFinalPolicyProvider	CRYPT_TRUST_REG_ENTRY ?
sTestPolicyProvider	CRYPT_TRUST_REG_ENTRY ?
sCleanupProvider	CRYPT_TRUST_REG_ENTRY ?
CRYPT_REGISTER_ACTIONID ENDS
PCRYPT_REGISTER_ACTIONID typedef ptr CRYPT_REGISTER_ACTIONID

;typedef CRYPT_PROVIDER_DEFUSAGE

;BOOL
PFN_ALLOCANDFILLDEFUSAGE_T typedef proto _CType \
	   pszUsageOID: LPSTR,
	    psDefUsage: ptr CRYPT_PROVIDER_DEFUSAGE
PFN_ALLOCANDFILLDEFUSAGE typedef ptr PFN_ALLOCANDFILLDEFUSAGE_T

;BOOL
PFN_FREEDEFUSAGE_T typedef proto _CType \
	   pszUsageOID: LPSTR,
	    psDefUsage: ptr CRYPT_PROVIDER_DEFUSAGE
PFN_FREEDEFUSAGE typedef ptr PFN_FREEDEFUSAGE_T


CRYPT_PROVIDER_REGDEFUSAGE STRUC
cbStruct		dd ?	;; = sizeof CRYPT_PROVIDER_REGDEFUSAGE
pgActionID		LPGUID ?
pwszDllName		LPWCHAR ?
pwszLoadCallbackDataFunctionName LPSTR ?
pwszFreeCallbackDataFunctionName LPSTR ?
CRYPT_PROVIDER_REGDEFUSAGE ENDS
PCRYPT_PROVIDER_REGDEFUSAGE typedef ptr CRYPT_PROVIDER_REGDEFUSAGE

CRYPT_PROVIDER_DEFUSAGE STRUC
cbStruct		dd ?	;; = sizeof CRYPT_PROVIDER_DEFUSAGE
gActionID		GUID <> ;; ActionID of provider
pDefPolicyCallbackData	LPVOID ?;; normally filled in WINTRUST_DATA
pDefSIPClientData	LPVOID ?;; normally filled in WINTRUST_DATA
CRYPT_PROVIDER_DEFUSAGE ENDS
PCRYPT_PROVIDER_DEFUSAGE typedef ptr CRYPT_PROVIDER_DEFUSAGE

;include <poppack.h>

WT_PROVIDER_DLL_NAME	equ <L"WINTRUST.DLL">
WT_PROVIDER_CERTTRUST_FUNCTION equ <L"WintrustCertificateTrust">

;BOOL
WintrustAddActionID proto _CType \
	    pgActionID: LPGUID,
	      fdwFlags: DWORD,
	    psProvInfo: ptr CRYPT_REGISTER_ACTIONID

WT_ADD_ACTION_ID_RET_RESULT_FLAG equ 0x1


;BOOL
WintrustRemoveActionID proto _CType \
	    pgActionID: LPGUID

;BOOL
WintrustLoadFunctionPointers proto _CType \
	    pgActionID: LPGUID,
		 pPfns: ptr CRYPT_PROVIDER_FUNCTIONS

;BOOL
WintrustAddDefaultForUsage proto _CType \
	   pszUsageOID: LPSTR,
	    psDefUsage: ptr CRYPT_PROVIDER_REGDEFUSAGE

DWACTION_ALLOCANDFILL	equ 1
DWACTION_FREE		equ 2

;BOOL
WintrustGetDefaultForUsage
	    dwActionID: DWORD,
	   pszUsageOID: LPSTR,
	       psUsage: ptr CRYPT_PROVIDER_DEFUSAGE

;CRYPT_PROVIDER_SGNR *
WTHelperGetProvSignerFromChain
	     pProvData: ptr CRYPT_PROVIDER_DATA,
	     idxSigner: DWORD,
	fCounterSigner: BOOL,
      idxCounterSigner: DWORD

;CRYPT_PROVIDER_CERT *
WTHelperGetProvCertFromChain
		 pSgnr: ptr CRYPT_PROVIDER_SGNR,
	       idxCert: DWORD

;CRYPT_PROVIDER_DATA *
WTHelperProvDataFromStateData
	    hStateData: HANDLE

;CRYPT_PROVIDER_PRIVDATA *
WTHelperGetProvPrivateDataFromChain
	     pProvData: ptr CRYPT_PROVIDER_DATA,
	  pgProviderID: ptr GUID

;BOOL
WTHelperCertIsSelfSigned
	    dwEncoding: DWORD,
		 pCert: ptr CERT_INFO

;HRESULT
WTHelperCertCheckValidSignature
	     pProvData: ptr CRYPT_PROVIDER_DATA

;include <pshpack8.h>

;;
;;  CTL Trusted CA Lists
;;
szOID_TRUSTED_CODESIGNING_CA_LIST equ <"1.3.6.1.4.1.311.2.2.1">
szOID_TRUSTED_CLIENT_AUTH_CA_LIST equ <"1.3.6.1.4.1.311.2.2.2">
szOID_TRUSTED_SERVER_AUTH_CA_LIST equ <"1.3.6.1.4.1.311.2.2.3">

;;
;;  encode/decode OID defines
;;
SPC_COMMON_NAME_OBJID		equ szOID_COMMON_NAME
SPC_TIME_STAMP_REQUEST_OBJID	equ <"1.3.6.1.4.1.311.3.2.1">
SPC_INDIRECT_DATA_OBJID		equ <"1.3.6.1.4.1.311.2.1.4">
SPC_SP_AGENCY_INFO_OBJID	equ <"1.3.6.1.4.1.311.2.1.10">
SPC_STATEMENT_TYPE_OBJID	equ <"1.3.6.1.4.1.311.2.1.11">
SPC_SP_OPUS_INFO_OBJID		equ <"1.3.6.1.4.1.311.2.1.12">
SPC_CERT_EXTENSIONS_OBJID	equ <"1.3.6.1.4.1.311.2.1.14">
SPC_PE_IMAGE_DATA_OBJID		equ <"1.3.6.1.4.1.311.2.1.15">
SPC_RAW_FILE_DATA_OBJID		equ <"1.3.6.1.4.1.311.2.1.18">
SPC_STRUCTURED_STORAGE_DATA_OBJID equ <"1.3.6.1.4.1.311.2.1.19">
SPC_JAVA_CLASS_DATA_OBJID	equ <"1.3.6.1.4.1.311.2.1.20">
SPC_INDIVIDUAL_SP_KEY_PURPOSE_OBJID equ <"1.3.6.1.4.1.311.2.1.21">
SPC_COMMERCIAL_SP_KEY_PURPOSE_OBJID equ <"1.3.6.1.4.1.311.2.1.22">
SPC_CAB_DATA_OBJID		equ <"1.3.6.1.4.1.311.2.1.25">
SPC_GLUE_RDN_OBJID		equ <"1.3.6.1.4.1.311.2.1.25">	;; obsolete NOT
SPC_MINIMAL_CRITERIA_OBJID	equ <"1.3.6.1.4.1.311.2.1.26">
SPC_FINANCIAL_CRITERIA_OBJID	equ <"1.3.6.1.4.1.311.2.1.27">
SPC_LINK_OBJID			equ <"1.3.6.1.4.1.311.2.1.28">
SPC_SIGINFO_OBJID		equ <"1.3.6.1.4.1.311.2.1.30">

;;
;;  Page hash versions
;;
SPC_PE_IMAGE_PAGE_HASHES_V1_OBJID equ <"1.3.6.1.4.1.311.2.3.1">	   ;; V1
SPC_PE_IMAGE_PAGE_HASHES_V2_OBJID equ <"1.3.6.1.4.1.311.2.3.2">	   ;; V2

;;
;;  Catalog entries
;;
CAT_NAMEVALUE_OBJID	equ <"1.3.6.1.4.1.311.12.2.1">
CAT_MEMBERINFO_OBJID	equ <"1.3.6.1.4.1.311.12.2.2">

;;
;;  encode/decode internal defines
;;
SPC_SP_AGENCY_INFO_STRUCT	equ 2000
SPC_MINIMAL_CRITERIA_STRUCT	equ 2001
SPC_FINANCIAL_CRITERIA_STRUCT	equ 2002
SPC_INDIRECT_DATA_CONTENT_STRUCT equ 2003
SPC_PE_IMAGE_DATA_STRUCT	equ 2004
SPC_LINK_STRUCT			equ 2005
SPC_STATEMENT_TYPE_STRUCT	equ 2006
SPC_SP_OPUS_INFO_STRUCT		equ 2007
SPC_CAB_DATA_STRUCT		equ 2008
SPC_JAVA_CLASS_DATA_STRUCT	equ 2009
SPC_SIGINFO_STRUCT		equ 2130
CAT_NAMEVALUE_STRUCT		equ 2221
CAT_MEMBERINFO_STRUCT		equ 2222

SPC_UUID_LENGTH			equ 16

;SPC_UUID[SPC_UUID_LENGTH] typedef BYTE

SpcSerializedObjectAttributesClassId equ <{0xA6,0xB5,0x86,0xD5,0xB4,0xA1,0x24,0x66,0xAE,0x05,0xA2,0x17,0xDA,0x8E,0x60,0xD6}>

SPC_SERIALIZED_OBJECT	STRUC
ClassId			db SPC_UUID_LENGTH dup(?) ;SPC_UUID ?
SerializedData		CRYPT_DATA_BLOB <>
SPC_SERIALIZED_OBJECT	ENDS
PSPC_SERIALIZED_OBJECT	typedef ptr SPC_SERIALIZED_OBJECT

SPC_SIGINFO_		STRUC
dwSipVersion		dd ?
gSIPGuid		GUID <>
dwReserved1		dd ?
dwReserved2		dd ?
dwReserved3		dd ?
dwReserved4		dd ?
dwReserved5		dd ?
SPC_SIGINFO		ENDS
PSPC_SIGINFO		typedef ptr SPC_SIGINFO

SPC_LINK		STRUC
dwLinkChoice		dd ?
SPC_URL_LINK_CHOICE	equ 1
SPC_MONIKER_LINK_CHOICE equ 2
SPC_FILE_LINK_CHOICE	equ 3
UNION
 pwszUrl		LPWSTR ?
 Moniker		SPC_SERIALIZED_OBJECT <>
 pwszFile		LPWSTR ?
ENDS
SPC_LINK		ENDS
PSPC_LINK		typedef ptr SPC_LINK

SPC_PE_IMAGE_DATA	STRUC
Flags			CRYPT_BIT_BLOB ?
pFile			PSPC_LINK ?
SPC_PE_IMAGE_DATA	ENDS
PSPC_PE_IMAGE_DATA	typedef ptr SPC_PE_IMAGE_DATA

SPC_INDIRECT_DATA_CONTENT STRUC
_Data			CRYPT_ATTRIBUTE_TYPE_VALUE ?
DigestAlgorithm		CRYPT_ALGORITHM_IDENTIFIER ?
Digest			CRYPT_HASH_BLOB ?
SPC_INDIRECT_DATA_CONTENT ENDS
PSPC_INDIRECT_DATA_CONTENT typedef ptr SPC_INDIRECT_DATA_CONTENT

SPC_FINANCIAL_CRITERIA	STRUC
fFinancialInfoAvailable BOOL ?
fMeetsCriteria		BOOL ?
SPC_FINANCIAL_CRITERIA	ENDS
PSPC_FINANCIAL_CRITERIA typedef ptr SPC_FINANCIAL_CRITERIA

SPC_IMAGE		STRUC
pImageLink		PSPC_LINK ?
Bitmap			CRYPT_DATA_BLOB ?
Metafile		CRYPT_DATA_BLOB ?
EnhancedMetafile	CRYPT_DATA_BLOB ?
GifFile			CRYPT_DATA_BLOB ?
SPC_IMAGE		ENDS
PSPC_IMAGE		typedef ptr SPC_IMAGE

SPC_SP_AGENCY_INFO	STRUC
pPolicyInformation	PSPC_LINK ?
pwszPolicyDisplayText	LPWSTR ?
pLogoImage		PSPC_IMAGE ?
pLogoLink		PSPC_LINK ?
SPC_SP_AGENCY_INFO	ENDS
PSPC_SP_AGENCY_INFO	typedef ptr SPC_SP_AGENCY_INFO

SPC_STATEMENT_TYPE	STRUC
cKeyPurposeId		dd ?
rgpszKeyPurposeId	LPLPSTR ?	;; pszObjId

SPC_STATEMENT_TYPE	ENDS
PSPC_STATEMENT_TYPE	typedef ptr SPC_STATEMENT_TYPE

SPC_SP_OPUS_INFO	STRUC
pwszProgramName		LPCWSTR ?
pMoreInfo		typedef ptr SPC_LINK_
pPublisherInfo		typedef ptr SPC_LINK_
SPC_SP_OPUS_INFO	ENDS
PSPC_SP_OPUS_INFO	typedef ptr SPC_SP_OPUS_INFO

CAT_NAMEVALUE		STRUC
pwszTag			LPWSTR ?
fdwFlags		dd ?
Value			CRYPT_DATA_BLOB ?
CAT_NAMEVALUE		ENDS
PCAT_NAMEVALUE		typedef ptr CAT_NAMEVALUE

CAT_MEMBERINFO		STRUC
pwszSubjGuid		LPWSTR ?
dwCertVersion		dd ?
CAT_MEMBERINFO		ENDS
PCAT_MEMBERINFO		typedef ptr CAT_MEMBERINFO

;include <poppack.h>

;;
;;  support for old calling convention: *** DO NOT USE ***
;;
ifdef WT_DEFINE_ALL_APIS

WIN_CERTIFICATE		STRUC
dwLength		dd ?
wRevision		dw ?
wCertificateType	dw ?	;; WIN_CERT_TYPE_xxx
bCertificate		db ANYSIZE_ARRAY dup(?)
WIN_CERTIFICATE		ENDS
LPWIN_CERTIFICATE	typedef ptr WIN_CERTIFICATE

WIN_CERT_REVISION_1_0		equ 0x0100
WIN_CERT_REVISION_2_0		equ 0x0200
WIN_CERT_TYPE_X509		equ 0x0001 ;; bCertificate contains an X.509 Certificate
WIN_CERT_TYPE_PKCS_SIGNED_DATA	equ 0x0002 ;; bCertificate contains a PKCS SignedData structure
WIN_CERT_TYPE_RESERVED_1	equ 0x0003 ;; Reserved
WIN_CERT_TYPE_TS_STACK_SIGNED	equ 0x0004 ;; Terminal Server Protocol Stack Certificate signing


WIN_TRUST_SUBJECT	typedef LPVOID

WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT STRUC
hClientToken		HANDLE ?
SubjectType		LPGUID ?
Subject			WIN_TRUST_SUBJECT ?
WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT ENDS
LPWIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT  typedef ptr WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT


WIN_TRUST_ACTDATA_SUBJECT_ONLY STRUC
SubjectType		LPGUID ?
Subject			WIN_TRUST_SUBJECT ?
WIN_TRUST_ACTDATA_SUBJECT_ONLY ENDS
LPWIN_TRUST_ACTDATA_SUBJECT_ONLY typedef ptr WIN_TRUST_ACTDATA_SUBJECT_ONLY

;; RawFile == 959dc450-8d9e-11cf-8736-00aa00a485eb
WIN_TRUST_SUBJTYPE_RAW_FILE equ \
<{0x959dc450,0x8d9e,0x11cf,{0x87,0x36,0x00,0xaa,0x00,0xa4,0x85,0xeb}}>
;; PeImage == 43c9a1e0-8da0-11cf-8736-00aa00a485eb
WIN_TRUST_SUBJTYPE_PE_IMAGE equ \
<{0x43c9a1e0,0x8da0,0x11cf,{0x87,0x36,0x00,0xaa,0x00,0xa4,0x85,0xeb}}>
;; JavaClass = 08ad3990-8da1-11cf-8736-00aa00a485eb
WIN_TRUST_SUBJTYPE_JAVA_CLASS equ \
<{0x08ad3990,0x8da1,0x11cf,{0x87,0x36,0x00,0xaa,0x00,0xa4,0x85,0xeb}}>
;; Cabinet = d17c5374-a392-11cf-9df5-00aa00c184e0
WIN_TRUST_SUBJTYPE_CABINET equ \
<{0xd17c5374,0xa392,0x11cf,{0x9d,0xf5,0x00,0xaa,0x00,0xc1,0x84,0xe0}}>

WIN_TRUST_SUBJECT_FILE	STRUC
hFile			HANDLE ?
lpPath			LPCWSTR ?
WIN_TRUST_SUBJECT_FILE	ENDS
LPWIN_TRUST_SUBJECT_FILE typedef ptr WIN_TRUST_SUBJECT_FILE

WIN_TRUST_SUBJTYPE_RAW_FILEEX equ \
<{0x6f458110,0xc2f1,0x11cf,{0x8a,0x69,0x0,0xaa,0x0,0x6c,0x37,0x6}}>
WIN_TRUST_SUBJTYPE_PE_IMAGEEX equ \
<{0x6f458111,0xc2f1,0x11cf,{0x8a,0x69,0x0,0xaa,0x0,0x6c,0x37,0x6}}>
WIN_TRUST_SUBJTYPE_JAVA_CLASSEX equ \
<{0x6f458113,0xc2f1,0x11cf,{0x8a,0x69,0x0,0xaa,0x0,0x6c,0x37,0x6}}>
WIN_TRUST_SUBJTYPE_CABINETEX equ \
<{0x6f458114,0xc2f1,0x11cf,{0x8a,0x69,0x0,0xaa,0x0,0x6c,0x37,0x6}}>

WIN_TRUST_SUBJECT_FILE_AND_DISPLAY STRUC
hFile			HANDLE ?	;; handle to the open file if you got it
lpPath			LPCWSTR ?	;; the path to open if you don't
lpDisplayName		LPCWSTR ?	;; (optional) display name to show to user
WIN_TRUST_SUBJECT_FILE_AND_DISPLAY ENDS
LPWIN_TRUST_SUBJECT_FILE_AND_DISPLAY typedef ptr WIN_TRUST_SUBJECT_FILE_AND_DISPLAY

;; OleStorage == c257e740-8da0-11cf-8736-00aa00a485eb
WIN_TRUST_SUBJTYPE_OLE_STORAGE equ \
<{0xc257e740,0x8da0,0x11cf,{0x87,0x36,0x00,0xaa,0x00,0xa4,0x85,0xeb}}>
;; TrustedPublisher == 66426730-8da1-11cf-8736-00aa00a485eb
WIN_SPUB_ACTION_TRUSTED_PUBLISHER equ \
<{0x66426730,0x8da1,0x11cf,{0x87,0x36,0x00,0xaa,0x00,0xa4,0x85,0xeb}}>
;; NtActivateImage == 8bc96b00-8da1-11cf-8736-00aa00a485eb
WIN_SPUB_ACTION_NT_ACTIVATE_IMAGE equ \
<{0x8bc96b00,0x8da1,0x11cf,{0x87,0x36,0x00,0xaa,0x00,0xa4,0x85,0xeb}}>
;; PublishedSoftware == 64b9d180-8da2-11cf-8736-00aa00a485eb
WIN_SPUB_ACTION_PUBLISHED_SOFTWARE equ \
<{0x64b9d180,0x8da2,0x11cf,{0x87,0x36,0x00,0xaa,0x00,0xa4,0x85,0xeb}}>

WIN_SPUB_TRUSTED_PUBLISHER_DATA STRUC
hClientToken		HANDLE ?
lpCertificate		LPWIN_CERTIFICATE ?
WIN_SPUB_TRUSTED_PUBLISHER_DATA ENDS
LPWIN_SPUB_TRUSTED_PUBLISHER_DATA typedef ptr WIN_SPUB_TRUSTED_PUBLISHER_DATA

endif

;BOOL
OpenPersonalTrustDBDialogEx proto _CType \
	    hwndParent: HWND,
	       dwFlags: DWORD,
	    pvReserved: PVOID

WT_TRUSTDBDIALOG_NO_UI_FLAG		equ 0x00000001
WT_TRUSTDBDIALOG_ONLY_PUB_TAB_FLAG	equ 0x00000002
WT_TRUSTDBDIALOG_WRITE_LEGACY_REG_FLAG	equ 0x00000100
WT_TRUSTDBDIALOG_WRITE_IEAK_STORE_FLAG	equ 0x00000200

endif ;; WINTRUST_H
