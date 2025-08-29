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

ifndef __spellcheckprovider_h__
define __spellcheckprovider_h__

include SpellCheck.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef MIN_SPELLING_NTDDI
define MIN_SPELLING_NTDDI NTDDI_WIN8
endif

if NTDDI_VERSION ge MIN_SPELLING_NTDDI

ifndef __ISpellCheckProvider_INTERFACE_DEFINED__
define __ISpellCheckProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellCheckProvider, "73E976E0-8ED4-4EB1-80D7-1BE0A16B0C38")

.comdef ISpellCheckProvider : public IUnknown
    get_LanguageTag     proc :ptr
    Check               proc :LPCWSTR, :ptr ptr
    Suggest             proc :LPCWSTR, :ptr ptr
    GetOptionValue      proc :LPCWSTR, :ptr
    SetOptionValue      proc :LPCWSTR, :BYTE
    get_OptionIds       proc :ptr ptr
    get_Id              proc :ptr
    get_LocalizedName   proc :ptr
    GetOptionDescription proc :LPCWSTR, :ptr ptr
    InitializeWordlist  proc :WORDLIST_TYPE, :ptr
   .ends

endif

ifndef __IComprehensiveSpellCheckProvider_INTERFACE_DEFINED__
define __IComprehensiveSpellCheckProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IComprehensiveSpellCheckProvider, "0C58F8DE-8E94-479E-9717-70C42C4AD2C3")

.comdef IComprehensiveSpellCheckProvider : public IUnknown
    ComprehensiveCheck  proc :LPCWSTR, :ptr ptr
   .ends

endif

ifndef __ISpellCheckProviderFactory_INTERFACE_DEFINED__
define __ISpellCheckProviderFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellCheckProviderFactory, "9F671E11-77D6-4C92-AEFB-615215E3A4BE")

.comdef ISpellCheckProviderFactory : public IUnknown
    get_SupportedLanguages proc :ptr ptr
    IsSupported         proc :LPCWSTR, :ptr
    CreateSpellCheckProvider proc :LPCWSTR, :ptr ptr
   .ends

endif

endif
endif

endif
