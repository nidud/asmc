ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eglobalization2Enumberformatting_h__
define __windows2Eglobalization2Enumberformatting_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace Globalization
.namespace NumberFormatting

.enum RoundingAlgorithm {
    RoundingAlgorithm_None  = 0,
    RoundingAlgorithm_RoundDown = 1,
    RoundingAlgorithm_RoundUp   = 2,
    RoundingAlgorithm_RoundTowardsZero  = 3,
    RoundingAlgorithm_RoundAwayFromZero = 4,
    RoundingAlgorithm_RoundHalfDown = 5,
    RoundingAlgorithm_RoundHalfUp   = 6,
    RoundingAlgorithm_RoundHalfTowardsZero  = 7,
    RoundingAlgorithm_RoundHalfAwayFromZero = 8,
    RoundingAlgorithm_RoundHalfToEven   = 9,
    RoundingAlgorithm_RoundHalfToOdd    = 10
    }

.enum CurrencyFormatterMode {
    CurrencyFormatterMode_UseSymbol = 0,
    CurrencyFormatterMode_UseCurrencyCode   = 1
    }

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberRounder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberRounder_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumberRounder <L"Windows.Globalization.NumberFormatting.INumberRounder">
DEFINE_IIDX(INumberRounder, "5473C375-38ED-4631-B80C-EF34FC48B7F5")

.comdef INumberRounder : public IInspectable

    RoundInt32          proc :INT32, :ptr
    RoundUInt32         proc :UINT32, :ptr
    RoundInt64          proc :INT64, :ptr
    RoundUInt64         proc :UINT64, :ptr
    RoundSingle         proc :FLOAT, :ptr
    RoundDouble         proc :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CISignificantDigitsNumberRounder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CISignificantDigitsNumberRounder_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_ISignificantDigitsNumberRounder <L"Windows.Globalization.NumberFormatting.ISignificantDigitsNumberRounder">
DEFINE_IIDX(ISignificantDigitsNumberRounder, "F5941BCA-6646-4913-8C76-1B191FF94DFD")

.comdef ISignificantDigitsNumberRounder : public IInspectable

    get_RoundingAlgorithm proc :ptr
    put_RoundingAlgorithm proc :Windows::Globalization::NumberFormatting::RoundingAlgorithm
    get_SignificantDigits proc :ptr
    put_SignificantDigits proc :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIIncrementNumberRounder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIIncrementNumberRounder_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_IIncrementNumberRounder <L"Windows.Globalization.NumberFormatting.IIncrementNumberRounder">
DEFINE_IIDX(IIncrementNumberRounder, "70A64FF8-66AB-4155-9DA1-739E46764543")

.comdef IIncrementNumberRounder : public IInspectable

    get_RoundingAlgorithm proc :ptr
    put_RoundingAlgorithm proc :Windows::Globalization::NumberFormatting::RoundingAlgorithm
    get_Increment       proc :ptr
    put_Increment       proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberFormatter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberFormatter_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumberFormatter <L"Windows.Globalization.NumberFormatting.INumberFormatter">
DEFINE_IIDX(INumberFormatter, "A5007C49-7676-4DB7-8631-1B6FF265CAA9")

.comdef INumberFormatter : public IInspectable

    FormatInt           proc :INT64, :ptr
    FormatUInt          proc :UINT64, :ptr
    FormatDouble        proc :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberFormatter2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberFormatter2_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumberFormatter2 <L"Windows.Globalization.NumberFormatting.INumberFormatter2">
DEFINE_IIDX(INumberFormatter2, "D4A8C1F0-80D0-4B0D-A89E-882C1E8F8310")

.comdef INumberFormatter2 : public IInspectable

    FormatInt           proc :INT64, :ptr
    FormatUInt          proc :UINT64, :ptr
    FormatDouble        proc :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberParser_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberParser_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumberParser <L"Windows.Globalization.NumberFormatting.INumberParser">
DEFINE_IIDX(INumberParser, "E6659412-4A13-4A53-83A1-392FBE4CFF9F")

.comdef INumberParser : public IInspectable

    ParseInt            proc :HSTRING, :ptr
    ParseUInt           proc :HSTRING, :ptr
    ParseDouble         proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberFormatterOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberFormatterOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumberFormatterOptions <L"Windows.Globalization.NumberFormatting.INumberFormatterOptions">
DEFINE_IIDX(INumberFormatterOptions, "80332D21-AEE1-4A39-BAA2-07ED8C96DAF6")

.comdef INumberFormatterOptions : public IInspectable

    get_Languages       proc :ptr
    get_GeographicRegion proc :ptr
    get_IntegerDigits   proc :ptr
    put_IntegerDigits   proc :INT32
    get_FractionDigits  proc :ptr
    put_FractionDigits  proc :INT32
    get_IsGrouped       proc :ptr
    put_IsGrouped       proc :boolean
    get_IsDecimalPointAlwaysDisplayed proc :ptr
    put_IsDecimalPointAlwaysDisplayed proc :boolean
    get_NumeralSystem   proc :ptr
    put_NumeralSystem   proc :HSTRING
    get_ResolvedLanguage proc :ptr
    get_ResolvedGeographicRegion proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CISignificantDigitsOption_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CISignificantDigitsOption_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_ISignificantDigitsOption <L"Windows.Globalization.NumberFormatting.ISignificantDigitsOption">
DEFINE_IIDX(ISignificantDigitsOption, "1D4DFCDD-2D43-4EE8-BBF1-C1B26A711A58")

.comdef ISignificantDigitsOption : public IInspectable

    get_SignificantDigits proc :ptr
    put_SignificantDigits proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberRounderOption_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumberRounderOption_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumberRounderOption <L"Windows.Globalization.NumberFormatting.INumberRounderOption">
DEFINE_IIDX(INumberRounderOption, "3B088433-646F-4EFE-8D48-66EB2E49E736")

.comdef INumberRounderOption : public IInspectable

    get_NumberRounder   proc :ptr
    put_NumberRounder   proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CISignedZeroOption_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CISignedZeroOption_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_ISignedZeroOption <L"Windows.Globalization.NumberFormatting.ISignedZeroOption">
DEFINE_IIDX(ISignedZeroOption, "FD1CDD31-0A3C-49C4-A642-96A1564F4F30")

.comdef ISignedZeroOption : public IInspectable

    get_IsZeroSigned    proc :ptr
    put_IsZeroSigned    proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIDecimalFormatterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIDecimalFormatterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_IDecimalFormatterFactory <L"Windows.Globalization.NumberFormatting.IDecimalFormatterFactory">
DEFINE_IIDX(IDecimalFormatterFactory, "0D018C9A-E393-46B8-B830-7A69C8F89FBB")

.comdef IDecimalFormatterFactory : public IInspectable

    CreateDecimalFormatter proc :ptr, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIPercentFormatterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIPercentFormatterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_IPercentFormatterFactory <L"Windows.Globalization.NumberFormatting.IPercentFormatterFactory">
DEFINE_IIDX(IPercentFormatterFactory, "B7828AEF-FED4-4018-A6E2-E09961E03765")

.comdef IPercentFormatterFactory : public IInspectable

    CreatePercentFormatter proc :ptr, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIPermilleFormatterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CIPermilleFormatterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_IPermilleFormatterFactory <L"Windows.Globalization.NumberFormatting.IPermilleFormatterFactory">
DEFINE_IIDX(IPermilleFormatterFactory, "2B37B4AC-E638-4ED5-A998-62F6B06A49AE")

.comdef IPermilleFormatterFactory : public IInspectable

    CreatePermilleFormatter proc :ptr, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CICurrencyFormatterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CICurrencyFormatterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_ICurrencyFormatterFactory <L"Windows.Globalization.NumberFormatting.ICurrencyFormatterFactory">
DEFINE_IIDX(ICurrencyFormatterFactory, "86C7537E-B938-4AA2-84B0-2C33DC5B1450")

.comdef ICurrencyFormatterFactory : public IInspectable

    CreateCurrencyFormatterCode proc :HSTRING, :ptr
    CreateCurrencyFormatterCodeContext proc :HSTRING, :ptr, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CICurrencyFormatter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CICurrencyFormatter_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_ICurrencyFormatter <L"Windows.Globalization.NumberFormatting.ICurrencyFormatter">
DEFINE_IIDX(ICurrencyFormatter, "11730CA5-4B00-41B2-B332-73B12A497D54")

.comdef ICurrencyFormatter : public IInspectable

    get_Currency        proc :ptr
    put_Currency        proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CICurrencyFormatter2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CICurrencyFormatter2_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_ICurrencyFormatter2 <L"Windows.Globalization.NumberFormatting.ICurrencyFormatter2">
DEFINE_IIDX(ICurrencyFormatter2, "072C2F1D-E7BA-4197-920E-247C92F7DEA6")

.comdef ICurrencyFormatter2 : public IInspectable

    get_Mode            proc :ptr
    put_Mode            proc :Windows::Globalization::NumberFormatting::CurrencyFormatterMode
    ApplyRoundingForCurrency proc :Windows::Globalization::NumberFormatting::RoundingAlgorithm
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumeralSystemTranslatorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumeralSystemTranslatorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumeralSystemTranslatorFactory <L"Windows.Globalization.NumberFormatting.INumeralSystemTranslatorFactory">
DEFINE_IIDX(INumeralSystemTranslatorFactory, "9630C8DA-36EF-4D88-A85C-6F0D98D620A6")

.comdef INumeralSystemTranslatorFactory : public IInspectable

    Create              proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumeralSystemTranslator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CNumberFormatting_CINumeralSystemTranslator_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_NumberFormatting_INumeralSystemTranslator <L"Windows.Globalization.NumberFormatting.INumeralSystemTranslator">
DEFINE_IIDX(INumeralSystemTranslator, "28F5BC2C-8C23-4234-AD2E-FA5A3A426E9B")

.comdef INumeralSystemTranslator : public IInspectable

    get_Languages       proc :ptr
    get_ResolvedLanguage proc :ptr
    get_NumeralSystem   proc :ptr
    put_NumeralSystem   proc :HSTRING
    TranslateNumerals   proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Globalization_NumberFormatting_SignificantDigitsNumberRounder_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumberFormatting_SignificantDigitsNumberRounder_DEFINED
define RuntimeClass_Windows_Globalization_NumberFormatting_SignificantDigitsNumberRounder <L"Windows.Globalization.NumberFormatting.SignificantDigitsNumberRounder">
endif
ifndef RUNTIMECLASS_Windows_Globalization_NumberFormatting_IncrementNumberRounder_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumberFormatting_IncrementNumberRounder_DEFINED
define RuntimeClass_Windows_Globalization_NumberFormatting_IncrementNumberRounder <L"Windows.Globalization.NumberFormatting.IncrementNumberRounder">
endif
ifndef RUNTIMECLASS_Windows_Globalization_NumberFormatting_DecimalFormatter_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumberFormatting_DecimalFormatter_DEFINED
define RuntimeClass_Windows_Globalization_NumberFormatting_DecimalFormatter <L"Windows.Globalization.NumberFormatting.DecimalFormatter">
endif
ifndef RUNTIMECLASS_Windows_Globalization_NumberFormatting_PercentFormatter_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumberFormatting_PercentFormatter_DEFINED
define RuntimeClass_Windows_Globalization_NumberFormatting_PercentFormatter <L"Windows.Globalization.NumberFormatting.PercentFormatter">
endif
ifndef RUNTIMECLASS_Windows_Globalization_NumberFormatting_PermilleFormatter_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumberFormatting_PermilleFormatter_DEFINED
define RuntimeClass_Windows_Globalization_NumberFormatting_PermilleFormatter <L"Windows.Globalization.NumberFormatting.PermilleFormatter">
endif
ifndef RUNTIMECLASS_Windows_Globalization_NumberFormatting_CurrencyFormatter_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumberFormatting_CurrencyFormatter_DEFINED
define RuntimeClass_Windows_Globalization_NumberFormatting_CurrencyFormatter <L"Windows.Globalization.NumberFormatting.CurrencyFormatter">
endif
ifndef RUNTIMECLASS_Windows_Globalization_NumberFormatting_NumeralSystemTranslator_DEFINED
define RUNTIMECLASS_Windows_Globalization_NumberFormatting_NumeralSystemTranslator_DEFINED
define RuntimeClass_Windows_Globalization_NumberFormatting_NumeralSystemTranslator <L"Windows.Globalization.NumberFormatting.NumeralSystemTranslator">
endif

endif
