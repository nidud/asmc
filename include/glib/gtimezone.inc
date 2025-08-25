ifndef __G_TIME_ZONE_H__
define __G_TIME_ZONE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc
include glib/gtypes.inc

.enum GTimeType {
    G_TIME_TYPE_STANDARD,
    G_TIME_TYPE_DAYLIGHT,
    G_TIME_TYPE_UNIVERSAL
    }

g_time_zone_new proto __cdecl :ptr
g_time_zone_new_identifier proto __cdecl :ptr
g_time_zone_new_utc proto __cdecl
g_time_zone_new_local proto __cdecl
g_time_zone_new_offset proto __cdecl :gint32
g_time_zone_ref proto __cdecl :ptr
g_time_zone_unref proto __cdecl :ptr
g_time_zone_find_interval proto __cdecl :ptr, :GTimeType, :gint64
g_time_zone_adjust_time proto __cdecl :ptr, :GTimeType, :ptr
g_time_zone_get_abbreviation proto __cdecl :ptr, :gint
g_time_zone_get_offset proto __cdecl :ptr, :gint
g_time_zone_is_dst proto __cdecl :ptr, :gint
g_time_zone_get_identifier proto __cdecl :ptr

endif
