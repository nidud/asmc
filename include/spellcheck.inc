ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __spellcheck_h__
define __spellcheck_h__

include oaidl.inc
include ocidl.inc

ifndef MIN_SPELLING_NTDDI
define MIN_SPELLING_NTDDI NTDDI_WIN8
endif

if NTDDI_VERSION GE MIN_SPELLING_NTDDI
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum WORDLIST_TYPE {
    WORDLIST_TYPE_IGNORE	= 0,
    WORDLIST_TYPE_ADD		= 1,
    WORDLIST_TYPE_EXCLUDE	= 2,
    WORDLIST_TYPE_AUTOCORRECT	= 3
    }

ifndef __ISpellingError_INTERFACE_DEFINED__
define __ISpellingError_INTERFACE_DEFINED__

.enum CORRECTIVE_ACTION {
    CORRECTIVE_ACTION_NONE	= 0,
    CORRECTIVE_ACTION_GET_SUGGESTIONS	= 1,
    CORRECTIVE_ACTION_REPLACE	= 2,
    CORRECTIVE_ACTION_DELETE	= 3
    }


DEFINE_IIDX(ISpellingError, "B7C82D61-FBE8-4B47-9B27-6C0D2E0DE0A3")

.comdef ISpellingError : public IUnknown

    get_StartIndex	proc :ptr
    get_Length		proc :ptr
    get_CorrectiveAction proc :ptr
    get_Replacement	proc :ptr
   .ends

endif

ifndef __IEnumSpellingError_INTERFACE_DEFINED__
define __IEnumSpellingError_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumSpellingError, "803E3BD4-2828-4410-8290-418D1D73C762")

.comdef IEnumSpellingError : public IUnknown

    Next		proc :ptr
   .ends

endif

ifndef __IOptionDescription_INTERFACE_DEFINED__
define __IOptionDescription_INTERFACE_DEFINED__

DEFINE_IIDX(IOptionDescription, "432E5F85-35CF-4606-A801-6F70277E1D7A")

.comdef IOptionDescription : public IUnknown

    get_Id		proc :ptr
    get_Heading		proc :ptr
    get_Description	proc :ptr
    get_Labels		proc :ptr
   .ends

endif

ifndef __ISpellCheckerChangedEventHandler_INTERFACE_DEFINED__
define __ISpellCheckerChangedEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellCheckerChangedEventHandler, "0B83A5B0-792F-4EAB-9799-ACF52C5ED08A")

.comdef ISpellCheckerChangedEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef __ISpellChecker_INTERFACE_DEFINED__
define __ISpellChecker_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellChecker, "B6FD0B71-E2BC-4653-8D05-F197E412770B")

.comdef ISpellChecker : public IUnknown

    get_LanguageTag	proc :ptr
    Check		proc :LPCWSTR, :ptr
    Suggest		proc :LPCWSTR, :ptr
    _Add		proc :LPCWSTR
    Ignore		proc :LPCWSTR
    AutoCorrect		proc :LPCWSTR, :LPCWSTR
    GetOptionValue	proc :LPCWSTR, :ptr
    get_OptionIds	proc :ptr
    get_Id		proc :ptr
    get_LocalizedName	proc :ptr
    add_SpellCheckerChanged proc :ptr, :ptr
    remove_SpellCheckerChanged proc :DWORD
    GetOptionDescription proc :LPCWSTR, :ptr
    ComprehensiveCheck	proc :LPCWSTR, :ptr
   .ends

endif

ifndef __ISpellCheckerFactory_INTERFACE_DEFINED__
define __ISpellCheckerFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellCheckerFactory, "8E018A9D-2415-4677-BF08-794EA61F94BB")

.comdef ISpellCheckerFactory : public IUnknown

    get_SupportedLanguages proc :ptr
    IsSupported		proc :LPCWSTR, :ptr
    CreateSpellChecker	proc :LPCWSTR, :ptr
   .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IUserDictionariesRegistrar_INTERFACE_DEFINED__
define __IUserDictionariesRegistrar_INTERFACE_DEFINED__

DEFINE_IIDX(IUserDictionariesRegistrar, "AA176B85-0E12-4844-8E1A-EEF1DA77F586")

.comdef IUserDictionariesRegistrar : public IUnknown

    RegisterUserDictionary proc :LPCWSTR, :LPCWSTR
    UnregisterUserDictionary proc :LPCWSTR, :LPCWSTR
   .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __MsSpellCheckLib_LIBRARY_DEFINED__
define __MsSpellCheckLib_LIBRARY_DEFINED__

externdef		LIBID_MsSpellCheckLib:IID

DEFINE_GUIDS(CLSID_SpellCheckerFactory, "7AB36653-1796-484B-BDFA-E74F1DB7C1DC")

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

endif ;; (NTDDI GE MIN_SPELLING_NTDDI)

endif
