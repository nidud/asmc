ifndef __G_DATE_TIME_H__
define __G_DATE_TIME_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtimezone.inc

G_TIME_SPAN_DAY         equ 86400000000
G_TIME_SPAN_HOUR        equ 3600000000
G_TIME_SPAN_MINUTE      equ 60000000
G_TIME_SPAN_SECOND      equ 1000000
G_TIME_SPAN_MILLISECOND equ 1000

GTimeSpan typedef gint64

g_date_time_unref proto __cdecl :ptr
g_date_time_ref proto __cdecl :ptr
g_date_time_new_now proto __cdecl :ptr
g_date_time_new_now_local proto __cdecl
g_date_time_new_now_utc proto __cdecl
g_date_time_new_from_unix_local proto __cdecl :gint64
g_date_time_new_from_unix_utc proto __cdecl :gint64
g_date_time_new_from_iso8601 proto __cdecl :ptr, :ptr
g_date_time_new proto __cdecl :ptr, :gint, :gint, :gint, :gint, :gint, :gdouble
g_date_time_new_local proto __cdecl :gint, :gint, :gint, :gint, :gint, :gdouble
g_date_time_new_utc proto __cdecl :gint, :gint, :gint, :gint, :gint, :gdouble
g_date_time_add proto __cdecl :ptr, :GTimeSpan
g_date_time_add_years proto __cdecl :ptr, :gint
g_date_time_add_months proto __cdecl :ptr, :gint
g_date_time_add_weeks proto __cdecl :ptr, :gint
g_date_time_add_days proto __cdecl :ptr, :gint
g_date_time_add_hours proto __cdecl :ptr, :gint
g_date_time_add_minutes proto __cdecl :ptr, :gint
g_date_time_add_seconds proto __cdecl :ptr, :gdouble
g_date_time_add_full proto __cdecl :ptr, :gint, :gint, :gint, :gint, :gint, :gdouble
g_date_time_compare proto __cdecl :gconstpointer, :gconstpointer
g_date_time_difference proto __cdecl :ptr, :ptr
g_date_time_hash proto __cdecl :gconstpointer
g_date_time_equal proto __cdecl :gconstpointer, :gconstpointer
g_date_time_get_ymd proto __cdecl :ptr, :ptr, :ptr, :ptr
g_date_time_get_year proto __cdecl :ptr
g_date_time_get_month proto __cdecl :ptr
g_date_time_get_day_of_month proto __cdecl :ptr
g_date_time_get_week_numbering_year proto __cdecl :ptr
g_date_time_get_week_of_year proto __cdecl :ptr
g_date_time_get_day_of_week proto __cdecl :ptr
g_date_time_get_day_of_year proto __cdecl :ptr
g_date_time_get_hour proto __cdecl :ptr
g_date_time_get_minute proto __cdecl :ptr
g_date_time_get_second proto __cdecl :ptr
g_date_time_get_microsecond proto __cdecl :ptr
g_date_time_get_seconds proto __cdecl :ptr
g_date_time_to_unix proto __cdecl :ptr
g_date_time_to_timeval proto __cdecl :ptr, :ptr
g_date_time_get_utc_offset proto __cdecl :ptr
g_date_time_get_timezone proto __cdecl :ptr
g_date_time_get_timezone_abbreviation proto __cdecl :ptr
g_date_time_is_daylight_savings proto __cdecl :ptr
g_date_time_to_timezone proto __cdecl :ptr, :ptr
g_date_time_to_local proto __cdecl :ptr
g_date_time_to_utc proto __cdecl :ptr
g_date_time_format proto __cdecl :ptr, :ptr
g_date_time_format_iso8601 proto __cdecl :ptr

endif
