ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eglobalization_h__
define __windows2Eglobalization_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CGlobalization__CJapanesePhoneme_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CGlobalization__CJapanesePhoneme_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CGlobalization__CJapanesePhoneme, "f15ca7e7-69a8-564d-9c20-4da75a773432")

.comdef __FIIterator_1_Windows__CGlobalization__CJapanesePhoneme : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CGlobalization__CJapanesePhoneme_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CGlobalization__CJapanesePhoneme_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CGlobalization__CJapanesePhoneme, "1aad17cb-1829-5236-8aef-0b75f8dfd7a6")

.comdef __FIIterable_1_Windows__CGlobalization__CJapanesePhoneme : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CGlobalization__CLanguage, "30e99ae6-f414-5243-8db2-aab38ea3f1f1")

.comdef __FIIterator_1_Windows__CGlobalization__CLanguage : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CGlobalization__CLanguage, "48409a10-61b6-5db1-a69d-8abc46ac608a")

.comdef __FIIterable_1_Windows__CGlobalization__CLanguage : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CGlobalization__CJapanesePhoneme_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CGlobalization__CJapanesePhoneme_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CGlobalization__CJapanesePhoneme, "4cdc5bd0-d4aa-5b60-bf25-7144905050f9")

.comdef __FIVectorView_1_Windows__CGlobalization__CJapanesePhoneme : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CGlobalization__CLanguage, "144b0f3d-2d59-5dd2-b012-908ec3e06435")

.comdef __FIVectorView_1_Windows__CGlobalization__CLanguage : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CGlobalization__CLanguage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CGlobalization__CLanguage, "dcf2525a-42c0-501d-9fcb-471fae060396")

.comdef __FIVector_1_Windows__CGlobalization__CLanguage : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace Globalization

.enum DayOfWeek {
    DayOfWeek_Sunday	= 0,
    DayOfWeek_Monday	= 1,
    DayOfWeek_Tuesday	= 2,
    DayOfWeek_Wednesday = 3,
    DayOfWeek_Thursday	= 4,
    DayOfWeek_Friday	= 5,
    DayOfWeek_Saturday	= 6
    }

ifndef ____x_ABI_CWindows_CGlobalization_CIJapanesePhoneticAnalyzerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CIJapanesePhoneticAnalyzerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_IJapanesePhoneticAnalyzerStatics <L"Windows.Globalization.IJapanesePhoneticAnalyzerStatics">
DEFINE_IIDX(IJapanesePhoneticAnalyzerStatics, "88AB9E90-93DE-41B2-B4D5-8EDB227FD1C2")

.comdef IJapanesePhoneticAnalyzerStatics : public IInspectable

    GetWords		proc :HSTRING, :ptr
    GetWordsWithMonoRubyOption proc :HSTRING, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CIJapanesePhoneme_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CIJapanesePhoneme_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_IJapanesePhoneme <L"Windows.Globalization.IJapanesePhoneme">
DEFINE_IIDX(IJapanesePhoneme, "2F6A9300-E85B-43E6-897D-5D82F862DF21")

.comdef IJapanesePhoneme : public IInspectable

    get_DisplayText	proc :ptr
    get_YomiText	proc :ptr
    get_IsPhraseStart	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CICalendarIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CICalendarIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ICalendarIdentifiersStatics <L"Windows.Globalization.ICalendarIdentifiersStatics">
DEFINE_IIDX(ICalendarIdentifiersStatics, "80653F68-2CB2-4C1F-B590-F0F52BF4FD1A")

.comdef ICalendarIdentifiersStatics : public IInspectable

    get_Gregorian	proc :ptr
    get_Hebrew		proc :ptr
    get_Hijri		proc :ptr
    get_Japanese	proc :ptr
    get_Julian		proc :ptr
    get_Korean		proc :ptr
    get_Taiwan		proc :ptr
    get_Thai		proc :ptr
    get_UmAlQura	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CIClockIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CIClockIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_IClockIdentifiersStatics <L"Windows.Globalization.IClockIdentifiersStatics">
DEFINE_IIDX(IClockIdentifiersStatics, "523805BB-12EC-4F83-BC31-B1B4376B0808")

.comdef IClockIdentifiersStatics : public IInspectable

    get_TwelveHour	proc :ptr
    get_TwentyFourHour	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CINumeralSystemIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CINumeralSystemIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_INumeralSystemIdentifiersStatics <L"Windows.Globalization.INumeralSystemIdentifiersStatics">
DEFINE_IIDX(INumeralSystemIdentifiersStatics, "A5C662C3-68C9-4D3D-B765-972029E21DEC")

.comdef INumeralSystemIdentifiersStatics : public IInspectable

    get_Arab		proc :ptr
    get_ArabExt		proc :ptr
    get_Bali		proc :ptr
    get_Beng		proc :ptr
    get_Cham		proc :ptr
    get_Deva		proc :ptr
    get_FullWide	proc :ptr
    get_Gujr		proc :ptr
    get_Guru		proc :ptr
    get_HaniDec		proc :ptr
    get_Java		proc :ptr
    get_Kali		proc :ptr
    get_Khmr		proc :ptr
    get_Knda		proc :ptr
    get_Lana		proc :ptr
    get_LanaTham	proc :ptr
    get_Laoo		proc :ptr
    get_Latn		proc :ptr
    get_Lepc		proc :ptr
    get_Limb		proc :ptr
    get_Mlym		proc :ptr
    get_Mong		proc :ptr
    get_Mtei		proc :ptr
    get_Mymr		proc :ptr
    get_MymrShan	proc :ptr
    get_Nkoo		proc :ptr
    get_Olck		proc :ptr
    get_Orya		proc :ptr
    get_Saur		proc :ptr
    get_Sund		proc :ptr
    get_Talu		proc :ptr
    get_TamlDec		proc :ptr
    get_Telu		proc :ptr
    get_Thai		proc :ptr
    get_Tibt		proc :ptr
    get_Vaii		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CICurrencyIdentifiersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CICurrencyIdentifiersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ICurrencyIdentifiersStatics <L"Windows.Globalization.ICurrencyIdentifiersStatics">
DEFINE_IIDX(ICurrencyIdentifiersStatics, "9F1D091B-D586-4913-9B6A-A9BD2DC12874")

.comdef ICurrencyIdentifiersStatics : public IInspectable

    get_AED		proc :ptr
    get_AFN		proc :ptr
    get_ALL		proc :ptr
    get_AMD		proc :ptr
    get_ANG		proc :ptr
    get_AOA		proc :ptr
    get_ARS		proc :ptr
    get_AUD		proc :ptr
    get_AWG		proc :ptr
    get_AZN		proc :ptr
    get_BAM		proc :ptr
    get_BBD		proc :ptr
    get_BDT		proc :ptr
    get_BGN		proc :ptr
    get_BHD		proc :ptr
    get_BIF		proc :ptr
    get_BMD		proc :ptr
    get_BND		proc :ptr
    get_BOB		proc :ptr
    get_BRL		proc :ptr
    get_BSD		proc :ptr
    get_BTN		proc :ptr
    get_BWP		proc :ptr
    get_BYR		proc :ptr
    get_BZD		proc :ptr
    get_CAD		proc :ptr
    get_CDF		proc :ptr
    get_CHF		proc :ptr
    get_CLP		proc :ptr
    get_CNY		proc :ptr
    get_COP		proc :ptr
    get_CRC		proc :ptr
    get_CUP		proc :ptr
    get_CVE		proc :ptr
    get_CZK		proc :ptr
    get_DJF		proc :ptr
    get_DKK		proc :ptr
    get_DOP		proc :ptr
    get_DZD		proc :ptr
    get_EGP		proc :ptr
    get_ERN		proc :ptr
    get_ETB		proc :ptr
    get_EUR		proc :ptr
    get_FJD		proc :ptr
    get_FKP		proc :ptr
    get_GBP		proc :ptr
    get_GEL		proc :ptr
    get_GHS		proc :ptr
    get_GIP		proc :ptr
    get_GMD		proc :ptr
    get_GNF		proc :ptr
    get_GTQ		proc :ptr
    get_GYD		proc :ptr
    get_HKD		proc :ptr
    get_HNL		proc :ptr
    get_HRK		proc :ptr
    get_HTG		proc :ptr
    get_HUF		proc :ptr
    get_IDR		proc :ptr
    get_ILS		proc :ptr
    get_INR		proc :ptr
    get_IQD		proc :ptr
    get_IRR		proc :ptr
    get_ISK		proc :ptr
    get_JMD		proc :ptr
    get_JOD		proc :ptr
    get_JPY		proc :ptr
    get_KES		proc :ptr
    get_KGS		proc :ptr
    get_KHR		proc :ptr
    get_KMF		proc :ptr
    get_KPW		proc :ptr
    get_KRW		proc :ptr
    get_KWD		proc :ptr
    get_KYD		proc :ptr
    get_KZT		proc :ptr
    get_LAK		proc :ptr
    get_LBP		proc :ptr
    get_LKR		proc :ptr
    get_LRD		proc :ptr
    get_LSL		proc :ptr
    get_LTL		proc :ptr
    get_LVL		proc :ptr
    get_LYD		proc :ptr
    get_MAD		proc :ptr
    get_MDL		proc :ptr
    get_MGA		proc :ptr
    get_MKD		proc :ptr
    get_MMK		proc :ptr
    get_MNT		proc :ptr
    get_MOP		proc :ptr
    get_MRO		proc :ptr
    get_MUR		proc :ptr
    get_MVR		proc :ptr
    get_MWK		proc :ptr
    get_MXN		proc :ptr
    get_MYR		proc :ptr
    get_MZN		proc :ptr
    get_NAD		proc :ptr
    get_NGN		proc :ptr
    get_NIO		proc :ptr
    get_NOK		proc :ptr
    get_NPR		proc :ptr
    get_NZD		proc :ptr
    get_OMR		proc :ptr
    get_PAB		proc :ptr
    get_PEN		proc :ptr
    get_PGK		proc :ptr
    get_PHP		proc :ptr
    get_PKR		proc :ptr
    get_PLN		proc :ptr
    get_PYG		proc :ptr
    get_QAR		proc :ptr
    get_RON		proc :ptr
    get_RSD		proc :ptr
    get_RUB		proc :ptr
    get_RWF		proc :ptr
    get_SAR		proc :ptr
    get_SBD		proc :ptr
    get_SCR		proc :ptr
    get_SDG		proc :ptr
    get_SEK		proc :ptr
    get_SGD		proc :ptr
    get_SHP		proc :ptr
    get_SLL		proc :ptr
    get_SOS		proc :ptr
    get_SRD		proc :ptr
    get_STD		proc :ptr
    get_SYP		proc :ptr
    get_SZL		proc :ptr
    get_THB		proc :ptr
    get_TJS		proc :ptr
    get_TMT		proc :ptr
    get_TND		proc :ptr
    get_TOP		proc :ptr
    get_TRY		proc :ptr
    get_TTD		proc :ptr
    get_TWD		proc :ptr
    get_TZS		proc :ptr
    get_UAH		proc :ptr
    get_UGX		proc :ptr
    get_USD		proc :ptr
    get_UYU		proc :ptr
    get_UZS		proc :ptr
    get_VEF		proc :ptr
    get_VND		proc :ptr
    get_VUV		proc :ptr
    get_WST		proc :ptr
    get_XAF		proc :ptr
    get_XCD		proc :ptr
    get_XOF		proc :ptr
    get_XPF		proc :ptr
    get_XXX		proc :ptr
    get_YER		proc :ptr
    get_ZAR		proc :ptr
    get_ZMW		proc :ptr
    get_ZWL		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CIGeographicRegion_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CIGeographicRegion_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_IGeographicRegion <L"Windows.Globalization.IGeographicRegion">
DEFINE_IIDX(IGeographicRegion, "01E9A621-4A64-4ED9-954F-9EDEB07BD903")

.comdef IGeographicRegion : public IInspectable

    get_Code		proc :ptr
    get_CodeTwoLetter	proc :ptr
    get_CodeThreeLetter proc :ptr
    get_CodeThreeDigit	proc :ptr
    get_DisplayName	proc :ptr
    get_NativeName	proc :ptr
    get_CurrenciesInUse proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CIGeographicRegionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CIGeographicRegionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_IGeographicRegionFactory <L"Windows.Globalization.IGeographicRegionFactory">
DEFINE_IIDX(IGeographicRegionFactory, "53425270-77B4-426B-859F-81E19D512546")

.comdef IGeographicRegionFactory : public IInspectable

    CreateGeographicRegion proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CIGeographicRegionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CIGeographicRegionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_IGeographicRegionStatics <L"Windows.Globalization.IGeographicRegionStatics">
DEFINE_IIDX(IGeographicRegionStatics, "29E28974-7AD9-4EF4-8799-B3B44FADEC08")

.comdef IGeographicRegionStatics : public IInspectable

    IsSupported		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CILanguage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CILanguage_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ILanguage <L"Windows.Globalization.ILanguage">
DEFINE_IIDX(ILanguage, "EA79A752-F7C2-4265-B1BD-C4DEC4E4F080")

.comdef ILanguage : public IInspectable

    get_LanguageTag	proc :ptr
    get_DisplayName	proc :ptr
    get_NativeName	proc :ptr
    get_Script		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CILanguageExtensionSubtags_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CILanguageExtensionSubtags_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ILanguageExtensionSubtags <L"Windows.Globalization.ILanguageExtensionSubtags">
DEFINE_IIDX(ILanguageExtensionSubtags, "7D7DAF45-368D-4364-852B-DEC927037B85")

.comdef ILanguageExtensionSubtags : public IInspectable

    GetExtensionSubtags proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CILanguageFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CILanguageFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ILanguageFactory <L"Windows.Globalization.ILanguageFactory">
DEFINE_IIDX(ILanguageFactory, "9B0252AC-0C27-44F8-B792-9793FB66C63E")

.comdef ILanguageFactory : public IInspectable

    CreateLanguage	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CILanguageStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CILanguageStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ILanguageStatics <L"Windows.Globalization.ILanguageStatics">
DEFINE_IIDX(ILanguageStatics,  "B23CD557-0865-46D4-89B8-D59BE8990F0D")

.comdef ILanguageStatics : public IInspectable

    IsWellFormed	proc :HSTRING, :ptr
    get_CurrentInputMethodLanguageTag proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CICalendar_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CICalendar_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ICalendar <L"Windows.Globalization.ICalendar">
DEFINE_IIDX(ICalendar, "CA30221D-86D9-40FB-A26B-D44EB7CF08EA")

.comdef ICalendar : public IInspectable

    Clone		proc :ptr
    SetToMin		proc
    SetToMax		proc
    get_Languages	proc :ptr
    get_NumeralSystem	proc :ptr
    put_NumeralSystem	proc :HSTRING
    GetCalendarSystem	proc :ptr
    ChangeCalendarSystem proc :HSTRING
    GetClock		proc :ptr
    ChangeClock		proc :HSTRING
    GetDateTime		proc :ptr
    SetDateTime		proc :Windows::Foundation::DateTime
    SetToNow		proc
    get_FirstEra	proc :ptr
    get_LastEra		proc :ptr
    get_NumberOfEras	proc :ptr
    get_Era		proc :ptr
    put_Era		proc :INT32
    AddEras		proc :INT32
    EraAsFullString	proc :ptr
    EraAsString		proc :INT32, :ptr
    get_FirstYearInThisEra proc :ptr
    get_LastYearInThisEra proc :ptr
    get_NumberOfYearsInThisEra proc :ptr
    get_Year		proc :ptr
    put_Year		proc :INT32
    AddYears		proc :INT32
    YearAsString	proc :ptr
    YearAsTruncatedString proc :INT32, :ptr
    YearAsPaddedString	proc :INT32, :ptr
    get_FirstMonthInThisYear proc :ptr
    get_LastMonthInThisYear proc :ptr
    get_NumberOfMonthsInThisYear proc :ptr
    get_Month		proc :ptr
    put_Month		proc :INT32
    AddMonths		proc :INT32
    MonthAsFullString	proc :ptr
    MonthAsString	proc :INT32, :ptr
    MonthAsFullSoloString proc :ptr
    MonthAsSoloString	proc :INT32, :ptr
    MonthAsNumericString proc :ptr
    MonthAsPaddedNumericString proc :INT32, :ptr
    AddWeeks		proc :INT32
    get_FirstDayInThisMonth proc :ptr
    get_LastDayInThisMonth proc :ptr
    get_NumberOfDaysInThisMonth proc :ptr
    get_Day		proc :ptr
    put_Day		proc :INT32
    AddDays		proc :INT32
    DayAsString		proc :ptr
    DayAsPaddedString	proc :INT32, :ptr
    get_DayOfWeek	proc :ptr
    DayOfWeekAsFullString proc :ptr
    DayOfWeekAsString	proc :INT32, :ptr
    DayOfWeekAsFullSoloString proc :ptr
    DayOfWeekAsSoloString proc :INT32, :ptr
    get_FirstPeriodInThisDay proc :ptr
    get_LastPeriodInThisDay proc :ptr
    get_NumberOfPeriodsInThisDay proc :ptr
    get_Period		proc :ptr
    put_Period		proc :INT32
    AddPeriods		proc :INT32
    PeriodAsFullString	proc :ptr
    PeriodAsString	proc :INT32, :ptr
    get_FirstHourInThisPeriod proc :ptr
    get_LastHourInThisPeriod proc :ptr
    get_NumberOfHoursInThisPeriod proc :ptr
    get_Hour		proc :ptr
    put_Hour		proc :INT32
    AddHours		proc :INT32
    HourAsString	proc :ptr
    HourAsPaddedString	proc :INT32, :ptr
    get_Minute		proc :ptr
    put_Minute		proc :INT32
    AddMinutes		proc :INT32
    MinuteAsString	proc :ptr
    MinuteAsPaddedString proc :INT32, :ptr
    get_Second		proc :ptr
    put_Second		proc :INT32
    AddSeconds		proc :INT32
    SecondAsString	proc :ptr
    SecondAsPaddedString proc :INT32, :ptr
    get_Nanosecond	proc :ptr
    put_Nanosecond	proc :INT32
    AddNanoseconds	proc :INT32
    NanosecondAsString	proc :ptr
    NanosecondAsPaddedString proc :INT32, :ptr
    Compare		proc :ptr, :ptr
    CompareDateTime	proc :Windows::Foundation::DateTime, :ptr
    CopyTo		proc :ptr
    get_FirstMinuteInThisHour proc :ptr
    get_LastMinuteInThisHour proc :ptr
    get_NumberOfMinutesInThisHour proc :ptr
    get_FirstSecondInThisMinute proc :ptr
    get_LastSecondInThisMinute proc :ptr
    get_NumberOfSecondsInThisMinute proc :ptr
    get_ResolvedLanguage proc :ptr
    get_IsDaylightSavingTime proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CICalendarFactory2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CICalendarFactory2_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ICalendarFactory2 <L"Windows.Globalization.ICalendarFactory2">
DEFINE_IIDX(ICalendarFactory2, "B44B378C-CA7E-4590-9E72-EA2BEC1A5115")

.comdef ICalendarFactory2 : public IInspectable

    CreateCalendarWithTimeZone proc :ptr, :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CITimeZoneOnCalendar_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CITimeZoneOnCalendar_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ITimeZoneOnCalendar <L"Windows.Globalization.ITimeZoneOnCalendar">
DEFINE_IIDX(ITimeZoneOnCalendar, "BB3C25E5-46CF-4317-A3F5-02621AD54478")

.comdef ITimeZoneOnCalendar : public IInspectable

    GetTimeZone		proc :ptr
    ChangeTimeZone	proc :HSTRING
    TimeZoneAsFullString proc :ptr
    TimeZoneAsString	proc :INT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CICalendarFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CICalendarFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_ICalendarFactory <L"Windows.Globalization.ICalendarFactory">
DEFINE_IIDX(ICalendarFactory, "83F58412-E56B-4C75-A66E-0F63D57758A6")

.comdef ICalendarFactory : public IInspectable

    CreateCalendarDefaultCalendarAndClock proc :ptr, :ptr
    CreateCalendar	proc :ptr, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CIApplicationLanguagesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CIApplicationLanguagesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_IApplicationLanguagesStatics <L"Windows.Globalization.IApplicationLanguagesStatics">
DEFINE_IIDX(IApplicationLanguagesStatics, "75B40847-0A4C-4A92-9565-FD63C95F7AED")

.comdef IApplicationLanguagesStatics : public IInspectable

    get_PrimaryLanguageOverride proc :ptr
    put_PrimaryLanguageOverride proc :HSTRING
    get_Languages	proc :ptr
    get_ManifestLanguages proc :ptr
   .ends

endif

.endn
.endn

ifndef RUNTIMECLASS_Windows_Globalization_JapanesePhoneme_DEFINED
define RUNTIMECLASS_Windows_Globalization_JapanesePhoneme_DEFINED
define RuntimeClass_Windows_Globalization_JapanesePhoneme <L"Windows.Globalization.JapanesePhoneme">
endif
ifndef RUNTIMECLASS_Windows_Globalization_JapanesePhoneticAnalyzer_DEFINED
define RUNTIMECLASS_Windows_Globalization_JapanesePhoneticAnalyzer_DEFINED
define RuntimeClass_Windows_Globalization_JapanesePhoneticAnalyzer <L"Windows.Globalization.JapanesePhoneticAnalyzer">
endif
ifndef RUNTIMECLASS_Windows_Globalization_CalendarIdentifiers_DEFINED
define RUNTIMECLASS_Windows_Globalization_CalendarIdentifiers_DEFINED
define RuntimeClass_Windows_Globalization_CalendarIdentifiers <L"Windows.Globalization.CalendarIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_Globalization_ClockIdentifiers_DEFINED
define RUNTIMECLASS_Windows_Globalization_ClockIdentifiers_DEFINED
define RuntimeClass_Windows_Globalization_ClockIdentifiers <L"Windows.Globalization.ClockIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_Globalization_NumeralSystemIdentifiers_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumeralSystemIdentifiers_DEFINED
define RuntimeClass_Windows_Globalization_NumeralSystemIdentifiers <L"Windows.Globalization.NumeralSystemIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_Globalization_CurrencyIdentifiers_DEFINED
define RUNTIMECLASS_Windows_Globalization_CurrencyIdentifiers_DEFINED
define RuntimeClass_Windows_Globalization_CurrencyIdentifiers <L"Windows.Globalization.CurrencyIdentifiers">
endif
ifndef RUNTIMECLASS_Windows_Globalization_GeographicRegion_DEFINED
define RUNTIMECLASS_Windows_Globalization_GeographicRegion_DEFINED
define RuntimeClass_Windows_Globalization_GeographicRegion <L"Windows.Globalization.GeographicRegion">
endif
ifndef RUNTIMECLASS_Windows_Globalization_Language_DEFINED
define RUNTIMECLASS_Windows_Globalization_Language_DEFINED
define RuntimeClass_Windows_Globalization_Language <L"Windows.Globalization.Language">
endif
ifndef RUNTIMECLASS_Windows_Globalization_Calendar_DEFINED
define RUNTIMECLASS_Windows_Globalization_Calendar_DEFINED
define RuntimeClass_Windows_Globalization_Calendar <L"Windows.Globalization.Calendar">
endif
ifndef RUNTIMECLASS_Windows_Globalization_ApplicationLanguages_DEFINED
define RUNTIMECLASS_Windows_Globalization_ApplicationLanguages_DEFINED
define RuntimeClass_Windows_Globalization_ApplicationLanguages <L"Windows.Globalization.ApplicationLanguages">
endif

endif
