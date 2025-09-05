ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __spellcheck_h__
define __spellcheck_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef MIN_SPELLING_NTDDI
define MIN_SPELLING_NTDDI NTDDI_WIN8
endif

if NTDDI_VERSION ge MIN_SPELLING_NTDDI

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum WORDLIST_TYPE {
	WORDLIST_TYPE_IGNORE,
	WORDLIST_TYPE_ADD,
	WORDLIST_TYPE_EXCLUDE,
	WORDLIST_TYPE_AUTOCORRECT
	}

ifndef __ISpellingError_INTERFACE_DEFINED__
define __ISpellingError_INTERFACE_DEFINED__

.enum CORRECTIVE_ACTION {
	CORRECTIVE_ACTION_NONE,
	CORRECTIVE_ACTION_GET_SUGGESTIONS,
	CORRECTIVE_ACTION_REPLACE,
	CORRECTIVE_ACTION_DELETE
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
    Next		proc :ptr ptr
   .ends

endif

ifndef __IOptionDescription_INTERFACE_DEFINED__
define __IOptionDescription_INTERFACE_DEFINED__

DEFINE_IIDX(IOptionDescription, "432E5F85-35CF-4606-A801-6F70277E1D7A")

.comdef IOptionDescription : public IUnknown
    get_Id		proc :ptr
    get_Heading		proc :ptr
    get_Description	proc :ptr
    get_Labels		proc :ptr ptr
   .ends

endif

ifndef __ISpellCheckerChangedEventHandler_INTERFACE_DEFINED__
define __ISpellCheckerChangedEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellCheckerChangedEventHandler, "0B83A5B0-792F-4EAB-9799-ACF52C5ED08A")

.comdef ISpellCheckerChangedEventHandler : public IUnknown
    IInvoke		proc :ptr
   .ends

endif

ifndef __ISpellChecker_INTERFACE_DEFINED__
define __ISpellChecker_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellChecker, "B6FD0B71-E2BC-4653-8D05-F197E412770B")

.comdef ISpellChecker : public IUnknown
    get_LanguageTag	proc :ptr
    Check		proc :LPCWSTR, :ptr ptr
    Suggest		proc :LPCWSTR, :ptr ptr
    _Add		proc :LPCWSTR
    Ignore		proc :LPCWSTR
    AutoCorrect		proc :LPCWSTR, :LPCWSTR
    GetOptionValue	proc :LPCWSTR, :ptr
    get_OptionIds	proc :ptr ptr
    get_Id		proc :ptr
    get_LocalizedName	proc :ptr
    add_SpellCheckerChanged proc :ptr, :ptr
    remove_SpellCheckerChanged proc :DWORD
    GetOptionDescription proc :LPCWSTR, :ptr ptr
    ComprehensiveCheck	proc :LPCWSTR, :ptr ptr
   .ends

endif

ifndef __ISpellChecker2_INTERFACE_DEFINED__
define __ISpellChecker2_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellChecker2, "E7ED1C71-87F7-4378-A840-C9200DACEE47")

.comdef ISpellChecker2 : public ISpellChecker
    Remove		proc :LPCWSTR
   .ends

endif

ifndef __ISpellCheckerFactory_INTERFACE_DEFINED__
define __ISpellCheckerFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ISpellCheckerFactory, "8E018A9D-2415-4677-BF08-794EA61F94BB")

.comdef ISpellCheckerFactory : public IUnknown
    get_SupportedLanguages proc :ptr ptr
    IsSupported		proc :LPCWSTR, :ptr
    CreateSpellChecker	proc :LPCWSTR, :ptr ptr
   .ends

endif

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
ifndef __IUserDictionariesRegistrar_INTERFACE_DEFINED__
define __IUserDictionariesRegistrar_INTERFACE_DEFINED__

DEFINE_IIDX(IUserDictionariesRegistrar, "AA176B85-0E12-4844-8E1A-EEF1DA77F586")

.comdef IUserDictionariesRegistrar : public IUnknown
    RegisterUserDictionary proc :LPCWSTR, :LPCWSTR
    UnregisterUserDictionary proc :LPCWSTR, :LPCWSTR
   .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __MsSpellCheckLib_LIBRARY_DEFINED__
define __MsSpellCheckLib_LIBRARY_DEFINED__
DEFINE_GUID(LIBID_MsSpellCheckLib, 0x4A250E01,0x61EA,0x400B,0xA2,0x7D,0xBF,0x37,0x44,0xBC,0xC9,0xF5)
DEFINE_GUIDS(CLSID_SpellCheckerFactory, "7AB36653-1796-484B-BDFA-E74F1DB7C1DC")
endif
endif

endif

endif
