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

ifndef __windows2Eglobalization2Edatetimeformatting_h__
define __windows2Eglobalization2Edatetimeformatting_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace Globalization
.namespace DateTimeFormatting

.enum YearFormat {
    YearFormat_None = 0,
    YearFormat_Default  = 1,
    YearFormat_Abbreviated  = 2,
    YearFormat_Full = 3
    }

.enum MonthFormat {
    MonthFormat_None    = 0,
    MonthFormat_Default = 1,
    MonthFormat_Abbreviated = 2,
    MonthFormat_Full    = 3,
    MonthFormat_Numeric = 4
    }

.enum DayOfWeekFormat {
    DayOfWeekFormat_None    = 0,
    DayOfWeekFormat_Default = 1,
    DayOfWeekFormat_Abbreviated = 2,
    DayOfWeekFormat_Full    = 3
    }

.enum DayFormat {
    DayFormat_None  = 0,
    DayFormat_Default   = 1
    }

.enum HourFormat {
    HourFormat_None = 0,
    HourFormat_Default  = 1
    }

.enum MinuteFormat {
    MinuteFormat_None   = 0,
    MinuteFormat_Default    = 1
    }

.enum SecondFormat {
    SecondFormat_None   = 0,
    SecondFormat_Default    = 1
    }

ifndef ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatter_INTERFACE_DEFINED__
DEFINE_IIDX(IDateTimeFormatter, "95EECA10-73E0-4E4B-A183-3D6AD0BA35EC")

.comdef IDateTimeFormatter : public IInspectable

    get_Languages       proc :ptr
    get_GeographicRegion proc :ptr
    get_Calendar        proc :ptr
    get_Clock           proc :ptr
    get_NumeralSystem   proc :ptr
    put_NumeralSystem   proc :HSTRING
    get_Patterns        proc :ptr
    get_Template        proc :ptr
    Format              proc :Windows::Foundation::DateTime, :ptr
    get_IncludeYear     proc :ptr
    get_IncludeMonth    proc :ptr
    get_IncludeDayOfWeek proc :ptr
    get_IncludeDay      proc :ptr
    get_IncludeHour     proc :ptr
    get_IncludeMinute   proc :ptr
    get_IncludeSecond   proc :ptr
    get_ResolvedLanguage proc :ptr
    get_ResolvedGeographicRegion proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_DateTimeFormatting_IDateTimeFormatterFactory <L"Windows.Globalization.DateTimeFormatting.IDateTimeFormatterFactory">
DEFINE_IIDX(IDateTimeFormatterFactory, "EC8D8A53-1A2E-412D-8815-3B745FB1A2A0")

.comdef IDateTimeFormatterFactory : public IInspectable

    CreateDateTimeFormatter proc :HSTRING, :ptr
    CreateDateTimeFormatterLanguages proc :HSTRING, :ptr, :ptr
    CreateDateTimeFormatterContext proc :HSTRING, :ptr, :HSTRING, :HSTRING, :HSTRING, :ptr
    CreateDateTimeFormatterDate proc \
            :Windows::Globalization::DateTimeFormatting::YearFormat,
            :Windows::Globalization::DateTimeFormatting::MonthFormat,
            :Windows::Globalization::DateTimeFormatting::DayFormat,
            :Windows::Globalization::DateTimeFormatting::DayOfWeekFormat,
            :ptr
    CreateDateTimeFormatterTime proc \
            :Windows::Globalization::DateTimeFormatting::HourFormat,
            :Windows::Globalization::DateTimeFormatting::MinuteFormat,
            :Windows::Globalization::DateTimeFormatting::SecondFormat,
            :ptr
    CreateDateTimeFormatterDateTimeLanguages proc \
            :Windows::Globalization::DateTimeFormatting::YearFormat,
            :Windows::Globalization::DateTimeFormatting::MonthFormat,
            :Windows::Globalization::DateTimeFormatting::DayFormat,
            :Windows::Globalization::DateTimeFormatting::DayOfWeekFormat,
            :Windows::Globalization::DateTimeFormatting::HourFormat,
            :Windows::Globalization::DateTimeFormatting::MinuteFormat,
            :Windows::Globalization::DateTimeFormatting::SecondFormat,
            :ptr,
            :ptr
    CreateDateTimeFormatterDateTimeContext proc \
            :Windows::Globalization::DateTimeFormatting::YearFormat,
            :Windows::Globalization::DateTimeFormatting::MonthFormat,
            :Windows::Globalization::DateTimeFormatting::DayFormat,
            :Windows::Globalization::DateTimeFormatting::DayOfWeekFormat,
            :Windows::Globalization::DateTimeFormatting::HourFormat,
            :Windows::Globalization::DateTimeFormatting::MinuteFormat,
            :Windows::Globalization::DateTimeFormatting::SecondFormat,
            :ptr, :HSTRING, :HSTRING, :HSTRING,
            :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatterStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatterStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_DateTimeFormatting_IDateTimeFormatterStatics <L"Windows.Globalization.DateTimeFormatting.IDateTimeFormatterStatics">
DEFINE_IIDX(IDateTimeFormatterStatics, "BFCDE7C0-DF4C-4A2E-9012-F47DAF3F1212")

.comdef IDateTimeFormatterStatics : public IInspectable

    get_LongDate        proc :ptr
    get_LongTime        proc :ptr
    get_ShortDate       proc :ptr
    get_ShortTime       proc :ptr
   .ends
endif


ifndef ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatter2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CDateTimeFormatting_CIDateTimeFormatter2_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_DateTimeFormatting_IDateTimeFormatter2 <L"Windows.Globalization.DateTimeFormatting.IDateTimeFormatter2">
DEFINE_IIDX(IDateTimeFormatter2, "27C91A86-BDAA-4FD0-9E36-671D5AA5EE03")

.comdef IDateTimeFormatter2 : public IInspectable

    FormatUsingTimeZone proc :Windows::Foundation::DateTime, :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

endif
