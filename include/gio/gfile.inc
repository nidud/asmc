ifndef __G_FILE_H__
define __G_FILE_H__

if NOT defined (__GIO_GIO_H_INSIDE__) AND NOT defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_FILE <g_file_get_type ()>
G_FILE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_FILE, GFile))>
	endm
G_IS_FILE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_FILE))>
	endm
G_FILE_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_FILE, GFileIface))>
	endm

GFileIface		STRUC
g_iface			GTypeInterface <>
_dup			proc :ptr
hash			proc :ptr
equal			proc :ptr, :ptr
is_native		proc :ptr
has_uri_scheme		proc :ptr, :ptr
get_uri_scheme		proc :ptr
get_basename		proc :ptr
get_path		proc :ptr
get_uri			proc :ptr
get_parse_name		proc :ptr
get_parent		proc :ptr
prefix_matches		proc :ptr, :ptr
get_relative_path	proc :ptr, :ptr
resolve_relative_path	proc :ptr, :ptr
get_child_for_display_name proc :ptr, :ptr, :ptr
enumerate_children	proc :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
enumerate_children_async proc :ptr, :ptr, :GFileQueryInfoFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
enumerate_children_finish proc :ptr, :ptr, :ptr
query_info		proc :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
query_info_async	proc :ptr, :ptr, :GFileQueryInfoFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
query_info_finish	proc :ptr, :ptr, :ptr
query_filesystem_info	proc :ptr, :ptr, :ptr, :ptr
query_filesystem_info_async proc :ptr, :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
query_filesystem_info_finish proc :ptr, :ptr, :ptr
find_enclosing_mount	proc :ptr, :ptr, :ptr
find_enclosing_mount_async proc :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
find_enclosing_mount_finish proc :ptr, :ptr, :ptr
set_display_name	proc :ptr, :ptr, :ptr, :ptr
set_display_name_async	proc :ptr, :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
set_display_name_finish proc :ptr, :ptr, :ptr
query_settable_attributes proc :ptr, :ptr, :ptr
_query_settable_attributes_async proc
_query_settable_attributes_finish proc
query_writable_namespaces proc :ptr, :ptr, :ptr
_query_writable_namespaces_async proc
_query_writable_namespaces_finish proc
set_attribute		proc :ptr, :ptr, :GFileAttributeType, :gpointer, :GFileQueryInfoFlags, :ptr, :ptr
set_attributes_from_info proc :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
set_attributes_async	proc :ptr, :ptr, :GFileQueryInfoFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
set_attributes_finish	proc :ptr, :ptr, :ptr, :ptr
read_fn			proc :ptr, :ptr, :ptr
read_async		proc :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
read_finish		proc :ptr, :ptr, :ptr, :ptr
append_to		proc :ptr, :GFileCreateFlags, :ptr, :ptr
append_to_async		proc :ptr, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
append_to_finish	proc :ptr, :ptr, :ptr
create			proc :ptr, :GFileCreateFlags, :ptr, :ptr
create_async		proc :ptr, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
create_finish		proc :ptr, :ptr, :ptr
replace			proc :ptr, :ptr, :gboolean, :GFileCreateFlags, :ptr, :ptr
replace_async		proc :ptr, :ptr, :gboolean, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
replace_finish		proc :ptr, :ptr, :ptr
delete_file		proc :ptr, :ptr, :ptr
delete_file_async	proc :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
delete_file_finish	proc :ptr, :ptr, :ptr
trash			proc :ptr, :ptr, :ptr
trash_async		proc :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
trash_finish		proc :ptr, :ptr, :ptr
make_directory		proc :ptr, :ptr, :ptr
make_directory_async	proc :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
make_directory_finish	proc :ptr, :ptr, :ptr
make_symbolic_link	proc :ptr, :ptr, :ptr, :ptr
_make_symbolic_link_async proc
_make_symbolic_link_finish proc
copy			proc :ptr, :ptr, :GFileCopyFlags, :ptr, :GFileProgressCallback, :gpointer, :ptr
copy_async		proc :ptr, :ptr, :GFileCopyFlags, :SINT, :ptr, :GFileProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
copy_finish		proc :ptr, :ptr, :ptr
move			proc :ptr, :ptr, :GFileCopyFlags, :ptr, :GFileProgressCallback, :gpointer, :ptr
move_async		proc :ptr, :ptr, :GFileCopyFlags, :SINT, :ptr, :GFileProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
move_finish		proc :ptr, :ptr, :ptr
mount_mountable		proc :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
mount_mountable_finish	proc :ptr, :ptr, :ptr
unmount_mountable	proc :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
unmount_mountable_finish proc :ptr, :ptr, :ptr
eject_mountable		proc :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
eject_mountable_finish	proc :ptr, :ptr, :ptr
mount_enclosing_volume	proc :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
mount_enclosing_volume_finish proc :ptr, :ptr, :ptr
monitor_dir		proc :ptr,:ptr, :GFileMonitorFlags, :ptr, :ptr
monitor_file		proc :ptr, :ptr, :GFileMonitorFlags, :ptr, :ptr
open_readwrite		proc :ptr, :ptr, :ptr, :ptr
open_readwrite_async	proc :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
open_readwrite_finish	proc :ptr, :ptr, :ptr
create_readwrite	proc :ptr, :ptr, :GFileCreateFlags, :ptr, :ptr
create_readwrite_async	proc :ptr, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
create_readwrite_finish proc :ptr, :ptr, :ptr
replace_readwrite	proc :ptr, :ptr, :gboolean, :GFileCreateFlags, :ptr, :ptr
replace_readwrite_async proc :ptr, :ptr, :gboolean, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
replace_readwrite_finish proc :ptr, :ptr, :ptr
start_mountable		proc :ptr, :GDriveStartFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
start_mountable_finish	proc :ptr, :ptr, :ptr
stop_mountable		proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
stop_mountable_finish	proc :ptr, :ptr, :ptr

supports_thread_contexts gboolean ?

unmount_mountable_with_operation proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
unmount_mountable_with_operation_finish proc :ptr, :ptr, :ptr
eject_mountable_with_operation proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
eject_mountable_with_operation_finish proc :ptr, :ptr, :ptr
poll_mountable		proc :ptr, :ptr, :GAsyncReadyCallback, :gpointer
poll_mountable_finish	proc :ptr, :ptr, :ptr
measure_disk_usage	proc :ptr, :GFileMeasureFlags, :ptr, :GFileMeasureProgressCallback, :gpointer, :ptr, :ptr, :ptr, :ptr
measure_disk_usage_async proc :ptr, :GFileMeasureFlags, :gint, :ptr, :GFileMeasureProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
measure_disk_usage_finish proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
GFileIface		ENDS

g_file_get_type proto __cdecl
g_file_new_for_path proto __cdecl :ptr
g_file_new_for_uri proto __cdecl :ptr
g_file_new_for_commandline_arg proto __cdecl :ptr
g_file_new_for_commandline_arg_and_cwd proto __cdecl :ptr, :ptr
g_file_new_tmp proto __cdecl :ptr, :ptr, :ptr
g_file_parse_name proto __cdecl :ptr
g_file_new_build_filename proto __Cdecl :ptr, :vararg
g_file_dup proto __cdecl :ptr
g_file_hash proto __cdecl :gconstpointer
g_file_equal proto __cdecl :ptr, :ptr
g_file_get_basename proto __cdecl :ptr
g_file_get_path proto __cdecl :ptr
g_file_peek_path proto __cdecl :ptr
g_file_get_uri proto __cdecl :ptr
g_file_get_parse_name proto __cdecl :ptr
g_file_get_parent proto __cdecl :ptr
g_file_has_parent proto __cdecl :ptr, :ptr
g_file_get_child proto __cdecl :ptr, :ptr
g_file_get_child_for_display_name proto __cdecl :ptr, :ptr, :ptr
g_file_has_prefix proto __cdecl :ptr, :ptr
g_file_get_relative_path proto __cdecl :ptr, :ptr
g_file_resolve_relative_path proto __cdecl :ptr, :ptr
g_file_is_native proto __cdecl :ptr
g_file_has_uri_scheme proto __cdecl :ptr, :ptr
g_file_get_uri_scheme proto __cdecl :ptr
g_file_read proto __cdecl :ptr, :ptr, :ptr
g_file_read_async proto __cdecl :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_read_finish proto __cdecl :ptr, :ptr, :ptr
g_file_append_to proto __cdecl :ptr, :GFileCreateFlags, :ptr, :ptr
g_file_create proto __cdecl :ptr, :GFileCreateFlags, :ptr, :ptr
g_file_replace proto __cdecl :ptr, :ptr, :gboolean, :GFileCreateFlags, :ptr, :ptr
g_file_append_to_async proto __cdecl :ptr, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_append_to_finish proto __cdecl :ptr, :ptr, :ptr
g_file_create_async proto __cdecl :ptr, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_create_finish proto __cdecl :ptr, :ptr, :ptr
g_file_replace_async proto __cdecl :ptr, :ptr,:gboolean, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_replace_finish proto __cdecl :ptr, :ptr, :ptr
g_file_open_readwrite proto __cdecl :ptr, :ptr, :ptr
g_file_open_readwrite_async proto __cdecl :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_open_readwrite_finish proto __cdecl :ptr, :ptr, :ptr
g_file_create_readwrite proto __cdecl :ptr, :GFileCreateFlags, :ptr, :ptr
g_file_create_readwrite_async proto __cdecl :ptr, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_create_readwrite_finish proto __cdecl :ptr, :ptr, :ptr
g_file_replace_readwrite proto __cdecl :ptr, :ptr, :gboolean, :GFileCreateFlags, :ptr, :ptr
g_file_replace_readwrite_async proto __cdecl :ptr, :ptr, :gboolean, :GFileCreateFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_replace_readwrite_finish proto __cdecl :ptr, :ptr, :ptr
g_file_query_exists proto __cdecl :ptr, :ptr
g_file_query_file_type proto __cdecl :ptr, :GFileQueryInfoFlags, :ptr
g_file_query_info proto __cdecl :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
g_file_query_info_async proto __cdecl :ptr, :ptr, :GFileQueryInfoFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_query_info_finish proto __cdecl :ptr, :ptr, :ptr
g_file_query_filesystem_info proto __cdecl :ptr, :ptr, :ptr, :ptr
g_file_query_filesystem_info_async proto __cdecl :ptr, :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_query_filesystem_info_finish proto __cdecl :ptr, :ptr, :ptr
g_file_find_enclosing_mount proto __cdecl :ptr, :ptr, :ptr
g_file_find_enclosing_mount_async proto __cdecl :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_find_enclosing_mount_finish proto __cdecl :ptr, :ptr, :ptr
g_file_enumerate_children proto __cdecl :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
g_file_enumerate_children_async proto __cdecl :ptr, :ptr, :GFileQueryInfoFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_enumerate_children_finish proto __cdecl :ptr, :ptr, :ptr
g_file_set_display_name proto __cdecl :ptr, :ptr, :ptr, :ptr
g_file_set_display_name_async proto __cdecl :ptr, :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_set_display_name_finish proto __cdecl :ptr, :ptr, :ptr
g_file_delete proto __cdecl :ptr, :ptr, :ptr
g_file_delete_async proto __cdecl :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_delete_finish proto __cdecl :ptr, :ptr, :ptr
g_file_trash proto __cdecl :ptr, :ptr, :ptr
g_file_trash_async proto __cdecl :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_trash_finish proto __cdecl :ptr, :ptr, :ptr
g_file_copy proto __cdecl :ptr, :ptr, :GFileCopyFlags, :ptr, :GFileProgressCallback, :gpointer, :ptr
g_file_copy_async proto __cdecl :ptr, :ptr, :GFileCopyFlags, :SINT, :ptr, :GFileProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
g_file_copy_finish proto __cdecl :ptr, :ptr, :ptr
g_file_move proto __cdecl :ptr, :ptr, :GFileCopyFlags, :ptr, :GFileProgressCallback, :gpointer, :ptr
g_file_move_async proto __cdecl :ptr, :ptr, :GFileCopyFlags, :SINT, :ptr, :GFileProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
g_file_move_finish proto __cdecl :ptr, :ptr, :ptr
g_file_make_directory proto __cdecl :ptr, :ptr, :ptr
g_file_make_directory_async proto __cdecl :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_make_directory_finish proto __cdecl :ptr, :ptr, :ptr
g_file_make_directory_with_parents proto __cdecl :ptr, :ptr, :ptr
g_file_make_symbolic_link proto __cdecl :ptr, :ptr, :ptr, :ptr
g_file_query_settable_attributes proto __cdecl :ptr, :ptr, :ptr
g_file_query_writable_namespaces proto __cdecl :ptr, :ptr, :ptr
g_file_set_attribute proto __cdecl :ptr, :ptr, :GFileAttributeType, :gpointer, :GFileQueryInfoFlags, :ptr, :ptr
g_file_set_attributes_from_info proto __cdecl :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
g_file_set_attributes_async proto __cdecl :ptr, :ptr, :GFileQueryInfoFlags, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_set_attributes_finish proto __cdecl :ptr, :ptr, :ptr, :ptr
g_file_set_attribute_string proto __cdecl :ptr, :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
g_file_set_attribute_byte_string proto __cdecl :ptr, :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
g_file_set_attribute_uint32 proto __cdecl :ptr, :ptr, :guint32, :GFileQueryInfoFlags, :ptr, :ptr
g_file_set_attribute_int32 proto __cdecl :ptr, :ptr, :gint32, :GFileQueryInfoFlags, :ptr, :ptr
g_file_set_attribute_uint64 proto __cdecl :ptr, :ptr, :guint64, :GFileQueryInfoFlags, :ptr, :ptr
g_file_set_attribute_int64 proto __cdecl :ptr, :ptr, :gint64, :GFileQueryInfoFlags, :ptr, :ptr
g_file_mount_enclosing_volume proto __cdecl :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_mount_enclosing_volume_finish proto __cdecl :ptr, :ptr, :ptr
g_file_mount_mountable proto __cdecl :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_mount_mountable_finish proto __cdecl :ptr, :ptr, :ptr
g_file_unmount_mountable proto __cdecl :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_file_unmount_mountable_finish proto __cdecl :ptr, :ptr, :ptr
g_file_unmount_mountable_with_operation proto __cdecl :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_unmount_mountable_with_operation_finish proto __cdecl :ptr, :ptr, :ptr
g_file_eject_mountable proto __cdecl :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_file_eject_mountable_finish proto __cdecl :ptr, :ptr, :ptr
g_file_eject_mountable_with_operation proto __cdecl :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_eject_mountable_with_operation_finish proto __cdecl :ptr, :ptr, :ptr
g_file_build_attribute_list_for_copy proto __cdecl :ptr, :GFileCopyFlags, :ptr, :ptr
g_file_copy_attributes proto __cdecl :ptr, :ptr, :GFileCopyFlags, :ptr, :ptr
g_file_monitor_directory proto __cdecl :ptr, :GFileMonitorFlags, :ptr, :ptr
g_file_monitor_file proto __cdecl :ptr, :GFileMonitorFlags, :ptr, :ptr
g_file_monitor proto __cdecl :ptr, :GFileMonitorFlags, :ptr, :ptr
g_file_measure_disk_usage proto __cdecl :ptr, :GFileMeasureFlags, :ptr, :GFileMeasureProgressCallback, :gpointer, :ptr, :ptr, :ptr, :ptr
g_file_measure_disk_usage_async proto __cdecl :ptr, :GFileMeasureFlags, :gint, :ptr, :GFileMeasureProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
g_file_measure_disk_usage_finish proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_file_start_mountable proto __cdecl :ptr, :GDriveStartFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_start_mountable_finish proto __cdecl :ptr, :ptr, :ptr
g_file_stop_mountable proto __cdecl :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_stop_mountable_finish proto __cdecl :ptr, :ptr, :ptr
g_file_poll_mountable proto __cdecl :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_poll_mountable_finish proto __cdecl :ptr, :ptr, :ptr
g_file_query_default_handler proto __cdecl :ptr, :ptr, :ptr
g_file_query_default_handler_async proto __cdecl :ptr, :SINT, :ptr, :GAsyncReadyCallback, :gpointer
g_file_query_default_handler_finish proto __cdecl :ptr, :ptr, :ptr
g_file_load_contents proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_file_load_contents_async proto __cdecl :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_load_contents_finish proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_file_load_partial_contents_async proto __cdecl :ptr, :ptr, :GFileReadMoreCallback, :GAsyncReadyCallback, :gpointer
g_file_load_partial_contents_finish proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_file_replace_contents proto __cdecl :ptr, :ptr, :gsize, :ptr, :gboolean, :GFileCreateFlags, :ptr, :ptr, :ptr
g_file_replace_contents_async proto __cdecl :ptr, :ptr, :gsize, :ptr, :gboolean, :GFileCreateFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_file_replace_contents_bytes_async proto __cdecl :ptr, :ptr, :ptr, :gboolean, :GFileCreateFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_file_replace_contents_finish proto __cdecl :ptr, :ptr, :ptr, :ptr
g_file_supports_thread_contexts proto __cdecl :ptr
g_file_load_bytes proto __cdecl :ptr, :ptr, :ptr, :ptr
g_file_load_bytes_async proto __cdecl :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_file_load_bytes_finish proto __cdecl :ptr, :ptr, :ptr, :ptr

endif
