ifndef __GLIB_TYPES_H__
define __GLIB_TYPES_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION) and not defined(GLIB_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include glib.inc

ifdef __GI_SCANNER__
GType typedef gsize
endif

define G_TYPE_DATE <g_date_get_type ()>
define G_TYPE_STRV <g_strv_get_type ()>
define G_TYPE_GSTRING <g_gstring_get_type ()>
define G_TYPE_HASH_TABLE <g_hash_table_get_type ()>
define G_TYPE_REGEX <g_regex_get_type ()>
define G_TYPE_MATCH_INFO <g_match_info_get_type ()>
define G_TYPE_ARRAY <g_array_get_type ()>
define G_TYPE_BYTE_ARRAY <g_byte_array_get_type ()>
define G_TYPE_PTR_ARRAY <g_ptr_array_get_type ()>
define G_TYPE_BYTES <g_bytes_get_type ()>
define G_TYPE_VARIANT_TYPE <g_variant_type_get_gtype ()>
define G_TYPE_ERROR <g_error_get_type ()>
define G_TYPE_DATE_TIME <g_date_time_get_type ()>
define G_TYPE_TIME_ZONE <g_time_zone_get_type ()>
define G_TYPE_IO_CHANNEL <g_io_channel_get_type ()>
define G_TYPE_IO_CONDITION <g_io_condition_get_type ()>
define G_TYPE_VARIANT_BUILDER <g_variant_builder_get_type ()>
define G_TYPE_VARIANT_DICT <g_variant_dict_get_type ()>
define G_TYPE_MAIN_LOOP <g_main_loop_get_type ()>
define G_TYPE_MAIN_CONTEXT <g_main_context_get_type ()>
define G_TYPE_SOURCE <g_source_get_type ()>
define G_TYPE_POLLFD <g_pollfd_get_type ()>
define G_TYPE_MARKUP_PARSE_CONTEXT <g_markup_parse_context_get_type ()>
define G_TYPE_KEY_FILE <g_key_file_get_type ()>
define G_TYPE_MAPPED_FILE <g_mapped_file_get_type ()>
define G_TYPE_THREAD <g_thread_get_type ()>
define G_TYPE_CHECKSUM <g_checksum_get_type ()>
define G_TYPE_OPTION_GROUP <g_option_group_get_type ()>
define G_TYPE_URI <g_uri_get_type ()>
define G_TYPE_TREE <g_tree_get_type ()>
define G_TYPE_PATTERN_SPEC <g_pattern_spec_get_type ()>

g_date_get_type proto
g_strv_get_type proto
g_gstring_get_type proto
g_hash_table_get_type proto
g_array_get_type proto
g_byte_array_get_type proto
g_ptr_array_get_type proto
g_bytes_get_type proto
g_variant_type_get_gtype proto
g_regex_get_type proto
g_match_info_get_type proto
g_error_get_type proto
g_date_time_get_type proto
g_time_zone_get_type proto
g_io_channel_get_type proto
g_io_condition_get_type proto
g_variant_builder_get_type proto
g_variant_dict_get_type proto
g_key_file_get_type proto
g_main_loop_get_type proto
g_main_context_get_type proto
g_source_get_type proto
g_pollfd_get_type proto
g_thread_get_type proto
g_checksum_get_type proto
g_markup_parse_context_get_type proto
g_mapped_file_get_type proto
g_option_group_get_type proto
g_uri_get_type proto
g_tree_get_type proto
g_pattern_spec_get_type proto

g_variant_get_gtype proto

endif
