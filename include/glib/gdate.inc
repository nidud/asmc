ifndef __G_DATE_H__
define __G_DATE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include time.inc

include glib/gtypes.inc
include glib/gquark.inc


GDateTime	typedef gint32
GTime		typedef gint32
GDateYear	typedef guint16
GDateDay	typedef guint8

.enum GDateDMY {
    G_DATE_DAY	 = 0,
    G_DATE_MONTH = 1,
    G_DATE_YEAR	 = 2
    }

.enum GDateWeekday {
    G_DATE_BAD_WEEKDAY	= 0,
    G_DATE_MONDAY	= 1,
    G_DATE_TUESDAY	= 2,
    G_DATE_WEDNESDAY	= 3,
    G_DATE_THURSDAY	= 4,
    G_DATE_FRIDAY	= 5,
    G_DATE_SATURDAY	= 6,
    G_DATE_SUNDAY	= 7
    }
.enum GDateMonth {
    G_DATE_BAD_MONTH = 0,
    G_DATE_JANUARY   = 1,
    G_DATE_FEBRUARY  = 2,
    G_DATE_MARCH     = 3,
    G_DATE_APRIL     = 4,
    G_DATE_MAY	     = 5,
    G_DATE_JUNE	     = 6,
    G_DATE_JULY	     = 7,
    G_DATE_AUGUST    = 8,
    G_DATE_SEPTEMBER = 9,
    G_DATE_OCTOBER   = 10,
    G_DATE_NOVEMBER  = 11,
    G_DATE_DECEMBER  = 12
    }

define G_DATE_BAD_JULIAN 0
define G_DATE_BAD_DAY	 0
define G_DATE_BAD_YEAR	 0

GDate			STRUC
julian_days		dd ?
RECORD
 julian			dd : 1 ?
 dmy			dd : 1 ?
 day			dd : 6 ?
 month			dd : 4 ?
 year			dd : 16 ?
ENDS
GDate			ENDS

g_date_new proto __cdecl
g_date_new_dmy proto __cdecl :GDateDay, :GDateMonth, :GDateYear
g_date_new_julian proto __cdecl :guint32
g_date_free proto __cdecl :ptr
g_date_copy proto __cdecl :ptr
g_date_valid proto __cdecl :ptr
g_date_valid_day proto __cdecl :GDateDay
g_date_valid_month proto __cdecl :GDateMonth
g_date_valid_year proto __cdecl :GDateYear
g_date_valid_weekday proto __cdecl :GDateWeekday
g_date_valid_julian proto __cdecl :guint32
g_date_valid_dmy proto __cdecl :GDateDay, :GDateMonth, :GDateYear
g_date_get_weekday proto __cdecl :ptr
g_date_get_month proto __cdecl :ptr
g_date_get_year proto __cdecl :ptr
g_date_get_day proto __cdecl :ptr
g_date_get_julian proto __cdecl :ptr
g_date_get_day_of_year proto __cdecl :ptr
g_date_get_monday_week_of_year proto __cdecl :ptr
g_date_get_sunday_week_of_year proto __cdecl :ptr
g_date_get_iso8601_week_of_year proto __cdecl :ptr
g_date_clear proto __cdecl :ptr, :guint
g_date_set_parse proto __cdecl :ptr, :ptr
g_date_set_time_t proto __cdecl :ptr, :time_t
g_date_set_time_val proto __cdecl :ptr, :ptr
g_date_set_time proto __cdecl :ptr, :GTime
g_date_set_month proto __cdecl :ptr, :GDateMonth
g_date_set_day proto __cdecl :ptr, :GDateDay
g_date_set_year proto __cdecl :ptr, :GDateYear
g_date_set_dmy proto __cdecl :ptr, :GDateDay, :GDateMonth, :GDateYear
g_date_set_julian proto __cdecl :ptr, :guint32
g_date_is_first_of_month proto __cdecl :ptr
g_date_is_last_of_month proto __cdecl :ptr
g_date_add_days proto __cdecl :ptr, :guint
g_date_subtract_days proto __cdecl :ptr, :guint
g_date_add_months proto __cdecl :ptr, :guint
g_date_subtract_months proto __cdecl :ptr, :guint
g_date_add_years proto __cdecl :ptr, :guint
g_date_subtract_years proto __cdecl :ptr, :guint
g_date_is_leap_year proto __cdecl :GDateYear
g_date_get_days_in_month proto __cdecl :GDateMonth, :GDateYear
g_date_get_monday_weeks_in_year proto __cdecl :GDateYear
g_date_get_sunday_weeks_in_year proto __cdecl :GDateYear
g_date_days_between proto __cdecl :ptr, :ptr
g_date_compare proto __cdecl :ptr, :ptr
g_date_to_struct_tm proto __cdecl :ptr, :ptr
g_date_clamp proto __cdecl :ptr, :ptr, :ptr
g_date_order proto __cdecl :ptr, :ptr
g_date_strftime proto __cdecl :ptr, :gsize, :ptr, :ptr

g_date_weekday			equ <g_date_get_weekday>
g_date_month			equ <g_date_get_month>
g_date_year			equ <g_date_get_year>
g_date_day			equ <g_date_get_day>
g_date_julian			equ <g_date_get_julian>
g_date_day_of_year		equ <g_date_get_day_of_year>
g_date_monday_week_of_year	equ <g_date_get_monday_week_of_year>
g_date_sunday_week_of_year	equ <g_date_get_sunday_week_of_year>
g_date_days_in_month		equ <g_date_get_days_in_month>
g_date_monday_weeks_in_year	equ <g_date_get_monday_weeks_in_year>
g_date_sunday_weeks_in_year	equ <g_date_get_sunday_weeks_in_year>

endif
