ifndef __LMJOIN_H__
__LMJOIN_H__ equ <>

NETSETUP_NAME_TYPE      typedef SDWORD
NetSetupUnknown         equ 0
NetSetupMachine         equ 1
NetSetupWorkgroup       equ 2
NetSetupDomain          equ 3
NetSetupNonExistentDomain equ 4
if(_WIN32_WINNT GE 0x0500)
NetSetupDnsMachine      equ 5
endif


NETSETUP_JOIN_STATUS    typedef SDWORD
PNETSETUP_JOIN_STATUS   typedef ptr SDWORD
NetSetupUnknownStatus   equ 0
NetSetupUnjoined        equ 1
NetSetupWorkgroupName   equ 2
NetSetupDomainName      equ 3

NETSETUP_JOIN_DOMAIN    equ 0x00000001
NETSETUP_ACCT_CREATE    equ 0x00000002
NETSETUP_ACCT_DELETE    equ 0x00000004
NETSETUP_WIN9X_UPGRADE  equ 0x00000010
NETSETUP_DOMAIN_JOIN_IF_JOINED equ 0x00000020
NETSETUP_JOIN_UNSECURE  equ 0x00000040
NETSETUP_MACHINE_PWD_PASSED equ 0x00000080
NETSETUP_DEFER_SPN_SET  equ 0x00000100

NETSETUP_JOIN_DC_ACCOUNT equ 0x00000200
NETSETUP_JOIN_WITH_NEW_NAME equ 0x00000400
NETSETUP_JOIN_READONLY  equ 0x00000800
NETSETUP_DNS_NAME_CHANGES_ONLY equ 0x00001000

NETSETUP_INSTALL_INVOCATION equ 0x00040000

NETSETUP_AMBIGUOUS_DC   equ 0x00001000
NETSETUP_NO_NETLOGON_CACHE equ 0x00002000
NETSETUP_DONT_CONTROL_SERVICES equ 0x00004000
NETSETUP_SET_MACHINE_NAME equ 0x00008000
NETSETUP_FORCE_SPN_SET  equ 0x00010000
NETSETUP_NO_ACCT_REUSE  equ 0x00020000

NETSETUP_IGNORE_UNSUPPORTED_FLAGS equ 0x10000000

NETSETUP_VALID_UNJOIN_FLAGS equ (NETSETUP_ACCT_DELETE OR NETSETUP_IGNORE_UNSUPPORTED_FLAGS OR NETSETUP_JOIN_DC_ACCOUNT)
NETSETUP_PROCESS_OFFLINE_FLAGS equ ( NETSETUP_JOIN_DOMAIN OR NETSETUP_DOMAIN_JOIN_IF_JOINED OR NETSETUP_JOIN_WITH_NEW_NAME OR NETSETUP_DONT_CONTROL_SERVICES )

;NET_API_STATUS
NetJoinDomain proto WINAPI \
              lpServer: LPCWSTR,
              lpDomain: LPCWSTR,
           lpAccountOU: LPCWSTR,
             lpAccount: LPCWSTR,
            lpPassword: LPCWSTR,
          fJoinOptions: DWORD

if(_WIN32_WINNT GE 0x0601)

NETSETUP_PROVISION_DOWNLEVEL_PRIV_SUPPORT equ 0x00000001
NETSETUP_PROVISION_REUSE_ACCOUNT equ 0x00000002
NETSETUP_PROVISION_USE_DEFAULT_PASSWORD equ 0x00000004
NETSETUP_PROVISION_SKIP_ACCOUNT_SEARCH equ 0x00000008
NETSETUP_PROVISION_ONLINE_CALLER equ 0x40000000
NETSETUP_PROVISION_CHECK_PWD_ONLY equ 0x80000000

;NET_API_STATUS
NetProvisionComputerAccount proto WINAPI \
              lpDomain: LPCWSTR,
         lpMachineName: LPCWSTR,
    lpMachineAccountOU: LPCWSTR,
              lpDcName: LPCWSTR,
             dwOptions: DWORD,
     pProvisionBinData: ptr PBYTE,
pdwProvisionBinDataSize: ptr DWORD,
    pProvisionTextData: ptr LPWSTR


;NET_API_STATUS
NetRequestOfflineDomainJoin proto WINAPI \
     pProvisionBinData: ptr BYTE,
cbProvisionBinDataSize: DWORD,
             dwOptions: DWORD,
         lpWindowsPath: LPCWSTR


endif

;NET_API_STATUS
NetUnjoinDomain proto WINAPI \
              lpServer: LPCWSTR,
             lpAccount: LPCWSTR,
            lpPassword: LPCWSTR,
        fUnjoinOptions: DWORD


;NET_API_STATUS
NetRenameMachineInDomain proto WINAPI \
                 lpServer: LPCWSTR,
         lpNewMachineName: LPCWSTR,
                lpAccount: LPCWSTR,
               lpPassword: LPCWSTR,
           fRenameOptions: DWORD

;NET_API_STATUS
NetValidateName proto WINAPI \
              lpServer: LPCWSTR,
                lpName: LPCWSTR,
             lpAccount: LPCWSTR,
            lpPassword: LPCWSTR,
              NameType: NETSETUP_NAME_TYPE

;NET_API_STATUS
NetGetJoinInformation proto WINAPI \
              lpServer: LPCWSTR,
          lpNameBuffer: ptr LPWSTR,
            BufferType: PNETSETUP_JOIN_STATUS

;NET_API_STATUS
NetGetJoinableOUs proto WINAPI \
              lpServer: LPCWSTR,
              lpDomain: LPCWSTR,
             lpAccount: LPCWSTR,
            lpPassword: LPCWSTR,
               OUCount: ptr DWORD,
                   OUs: ptr ptr LPWSTR

if(_WIN32_WINNT GE 0x0501)

NET_IGNORE_UNSUPPORTED_FLAGS equ 0x01

;NET_API_STATUS
NetAddAlternateComputerName proto WINAPI \
                Server: LPCWSTR,
         AlternateName: LPCWSTR,
         DomainAccount: LPCWSTR,
 DomainAccountPassword: LPCWSTR,
              Reserved: ULONG


;NET_API_STATUS
NetRemoveAlternateComputerName proto WINAPI \
                Server: LPCWSTR,
         AlternateName: LPCWSTR,
         DomainAccount: LPCWSTR,
 DomainAccountPassword: LPCWSTR,
              Reserved: ULONG

;NET_API_STATUS
NetSetPrimaryComputerName proto WINAPI \
                Server: LPCWSTR,
           PrimaryName: LPCWSTR,
         DomainAccount: LPCWSTR,
 DomainAccountPassword: LPCWSTR,
              Reserved: ULONG


NET_COMPUTER_NAME_TYPE  typedef SDWORD
NetPrimaryComputerName  equ 0
NetAlternateComputerNames equ 1
NetAllComputerNames     equ 2
NetComputerNameTypeMax  equ 3

;NET_API_STATUS
NetEnumerateComputerNames proto WINAPI \
                Server: LPCWSTR,
              NameType: NET_COMPUTER_NAME_TYPE,
              Reserved: ULONG,
            EntryCount: PDWORD,
         ComputerNames: ptr ptr LPWSTR

endif

endif
