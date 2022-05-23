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

;void
g_date_time_unref proto __cdecl \
              datetime: ptr GDateTime

;GDateTime
g_date_time_ref proto __cdecl \
              datetime: ptr GDateTime


;GDateTime
g_date_time_new_now proto __cdecl \
                    tz: ptr GTimeZone

;GDateTime
g_date_time_new_now_local proto __cdecl

;GDateTime
g_date_time_new_now_utc proto __cdecl

;GDateTime
g_date_time_new_from_unix_local proto __cdecl \
                     t: gint64

;GDateTime
g_date_time_new_from_unix_utc proto __cdecl \
                     t: gint64


;GDateTime
g_date_time_new_from_iso8601 proto __cdecl \
                  text: ptr gchar,
            default_tz: ptr GTimeZone


;GDateTime
g_date_time_new proto __cdecl \
                    tz: ptr GTimeZone,
                  year: gint,
                 month: gint,
                   day: gint,
                  hour: gint,
                minute: gint,
               seconds: gdouble

;GDateTime
g_date_time_new_local proto __cdecl \
                  year: gint,
                 month: gint,
                   day: gint,
                  hour: gint,
                minute: gint,
               seconds: gdouble

;GDateTime
g_date_time_new_utc proto __cdecl \
                  year: gint,
                 month: gint,
                   day: gint,
                  hour: gint,
                minute: gint,
               seconds: gdouble


;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add proto __cdecl \
              datetime: ptr GDateTime,
              timespan: GTimeSpan


;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_years proto __cdecl \
              datetime: ptr GDateTime,
                 years: gint

;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_months proto __cdecl \
              datetime: ptr GDateTime,
                months: gint

;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_weeks proto __cdecl \
              datetime: ptr GDateTime,
                 weeks: gint

;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_days proto __cdecl \
              datetime: ptr GDateTime,
                  days: gint


;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_hours proto __cdecl \
              datetime: ptr GDateTime,
                 hours: gint

;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_minutes proto __cdecl \
              datetime: ptr GDateTime,
               minutes: gint

;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_seconds proto __cdecl \
              datetime: ptr GDateTime,
               seconds: gdouble


;G_GNUC_WARN_UNUSED_RESULT
g_date_time_add_full proto __cdecl \
              datetime: ptr GDateTime,
                 years: gint,
                months: gint,
                  days: gint,
                 hours: gint,
               minutes: gint,
               seconds: gdouble


;gint
g_date_time_compare proto __cdecl \
                   dt1: gconstpointer,
                   dt2: gconstpointer

;GTimeSpan
g_date_time_difference proto __cdecl \
                  _end: ptr GDateTime,
                 begin: ptr GDateTime

;guint
g_date_time_hash proto __cdecl \
              datetime: gconstpointer

;gboolean
g_date_time_equal proto __cdecl \
                   dt1: gconstpointer,
                   dt2: gconstpointer


;void
g_date_time_get_ymd proto __cdecl \
              datetime: ptr GDateTime,
                  year: ptr gint,
                 month: ptr gint,
                   day: ptr gint


;gint
g_date_time_get_year proto __cdecl \
              datetime: ptr GDateTime

;gint
g_date_time_get_month proto __cdecl \
              datetime: ptr GDateTime

;gint
g_date_time_get_day_of_month proto __cdecl \
              datetime: ptr GDateTime


;gint
g_date_time_get_week_numbering_year proto __cdecl \
              datetime: ptr GDateTime

;gint
g_date_time_get_week_of_year proto __cdecl \
              datetime: ptr GDateTime

;gint
g_date_time_get_day_of_week proto __cdecl \
              datetime: ptr GDateTime


;gint
g_date_time_get_day_of_year proto __cdecl \
              datetime: ptr GDateTime


;gint
g_date_time_get_hour proto __cdecl \
              datetime: ptr GDateTime

;gint
g_date_time_get_minute proto __cdecl \
              datetime: ptr GDateTime

;gint
g_date_time_get_second proto __cdecl \
              datetime: ptr GDateTime

;gint
g_date_time_get_microsecond proto __cdecl \
              datetime: ptr GDateTime

;gdouble
g_date_time_get_seconds proto __cdecl \
              datetime: ptr GDateTime


;gint64
g_date_time_to_unix proto __cdecl \
              datetime: ptr GDateTime

g_date_time_to_timeval proto __cdecl \
              datetime: ptr GDateTime,
                    tv: ptr GTimeVal

;GTimeSpan
g_date_time_get_utc_offset proto __cdecl \
              datetime: ptr GDateTime

;GTimeZone
g_date_time_get_timezone proto __cdecl \
              datetime: ptr GDateTime

;const
g_date_time_get_timezone_abbreviation proto __cdecl \
              datetime: ptr GDateTime

;gboolean
g_date_time_is_daylight_savings proto __cdecl \
              datetime: ptr GDateTime


;GDateTime
g_date_time_to_timezone proto __cdecl \
              datetime: ptr GDateTime,
                    tz: ptr GTimeZone

;GDateTime
g_date_time_to_local proto __cdecl \
              datetime: ptr GDateTime

;GDateTime
g_date_time_to_utc proto __cdecl \
              datetime: ptr GDateTime


;gchar
g_date_time_format proto __cdecl \
              datetime: ptr GDateTime,
                format: ptr gchar

;gchar
g_date_time_format_iso8601 proto __cdecl \
              datetime: ptr GDateTime

endif
