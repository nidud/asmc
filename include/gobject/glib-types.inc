ifndef __GLIB_TYPES_H__
__GLIB_TYPES_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION) AND NOT defined(GLIB_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif
include glib.inc
ifdef __GI_SCANNER__
GType                   typedef gsize
endif

G_TYPE_DATE             equ <g_date_get_type>
G_TYPE_STRV             equ <g_strv_get_type>
G_TYPE_GSTRING          equ <g_gstring_get_type>
G_TYPE_HASH_TABLE       equ <g_hash_table_get_type>
G_TYPE_REGEX            equ <g_regex_get_type>
G_TYPE_MATCH_INFO       equ <g_match_info_get_type>
G_TYPE_ARRAY            equ <g_array_get_type>
G_TYPE_BYTE_ARRAY       equ <g_byte_array_get_type>
G_TYPE_PTR_ARRAY        equ <g_ptr_array_get_type>
G_TYPE_BYTES            equ <g_bytes_get_type>
G_TYPE_VARIANT_TYPE     equ <g_variant_type_get_gtype>
G_TYPE_ERROR            equ <g_error_get_type>
G_TYPE_DATE_TIME        equ <g_date_time_get_type>
G_TYPE_TIME_ZONE        equ <g_time_zone_get_type>
G_TYPE_IO_CHANNEL       equ <g_io_channel_get_type>
G_TYPE_IO_CONDITION     equ <g_io_condition_get_type>
G_TYPE_VARIANT_BUILDER  equ <g_variant_builder_get_type>
G_TYPE_VARIANT_DICT     equ <g_variant_dict_get_type>
G_TYPE_MAIN_LOOP        equ <g_main_loop_get_type>
G_TYPE_MAIN_CONTEXT     equ <g_main_context_get_type>
G_TYPE_SOURCE           equ <g_source_get_type>
G_TYPE_POLLFD           equ <g_pollfd_get_type>
G_TYPE_MARKUP_PARSE_CONTEXT equ <g_markup_parse_context_get_type>
G_TYPE_KEY_FILE         equ <g_key_file_get_type>
G_TYPE_MAPPED_FILE      equ <g_mapped_file_get_type>
G_TYPE_THREAD           equ <g_thread_get_type>
G_TYPE_CHECKSUM         equ <g_checksum_get_type>
G_TYPE_OPTION_GROUP     equ <g_option_group_get_type>

g_date_get_type proto __cdecl
g_strv_get_type proto __cdecl
g_gstring_get_type proto __cdecl
g_hash_table_get_type proto __cdecl
g_array_get_type proto __cdecl
g_byte_array_get_type proto __cdecl
g_ptr_array_get_type proto __cdecl
g_bytes_get_type proto __cdecl
g_variant_type_get_gtype proto __cdecl
g_regex_get_type proto __cdecl
g_match_info_get_type proto __cdecl
g_error_get_type proto __cdecl
g_date_time_get_type proto __cdecl
g_time_zone_get_type proto __cdecl
g_io_channel_get_type proto __cdecl
g_io_condition_get_type proto __cdecl
g_variant_builder_get_type proto __cdecl
g_variant_dict_get_type proto __cdecl
g_key_file_get_type proto __cdecl
g_main_loop_get_type proto __cdecl
g_main_context_get_type proto __cdecl
g_source_get_type proto __cdecl
g_pollfd_get_type proto __cdecl
g_thread_get_type proto __cdecl
g_checksum_get_type proto __cdecl
g_markup_parse_context_get_type proto __cdecl
g_mapped_file_get_type proto __cdecl
g_option_group_get_type proto __cdecl
;GLIB_DEPRECATED_FOR('G_TYPE_VARIANT')
g_variant_get_gtype proto __cdecl

endif
