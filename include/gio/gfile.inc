ifndef __G_FILE_H__
define __G_FILE_H__

if NOT defined (__GIO_GIO_H_INSIDE__) AND NOT defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

G_TYPE_FILE equ <g_file_get_type>
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
_dup			proc :ptr GFile
hash			proc :ptr GFile
equal			proc :ptr GFile, :ptr GFile
is_native		proc :ptr GFile
has_uri_scheme		proc :ptr GFile, :ptr char_t
get_uri_scheme		proc :ptr GFile
get_basename		proc :ptr GFile
get_path		proc :ptr GFile
get_uri			proc :ptr GFile
get_parse_name		proc :ptr GFile
get_parent		proc :ptr GFile
prefix_matches		proc :ptr GFile, :ptr GFile
get_relative_path	proc :ptr GFile, :ptr GFile
resolve_relative_path	proc :ptr GFile, :ptr char_t
get_child_for_display_name proc :ptr GFile, :ptr char_t, :ptr GError
enumerate_children	proc :ptr GFile, :ptr char_t, :GFileQueryInfoFlags, :ptr GCancellable, :ptr GError
enumerate_children_async proc :ptr GFile, :ptr char_t, :GFileQueryInfoFlags, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
enumerate_children_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
query_info		proc :ptr GFile, :ptr char_t, :GFileQueryInfoFlags, :ptr GCancellable, :ptr GError
query_info_async	proc :ptr GFile, :ptr char_t, :GFileQueryInfoFlags, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
query_info_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
query_filesystem_info	proc :ptr GFile, :ptr char_t, :ptr GCancellable, :ptr GError
query_filesystem_info_async proc :ptr GFile, :ptr char_t, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
query_filesystem_info_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
find_enclosing_mount	proc :ptr GFile, :ptr GCancellable, :ptr GError
find_enclosing_mount_async proc :ptr GFile, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
find_enclosing_mount_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
set_display_name	proc :ptr GFile, :ptr char_t, :ptr GCancellable, :ptr GError
set_display_name_async	proc :ptr GFile, :ptr char_t, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
set_display_name_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
query_settable_attributes proc :ptr GFile, :ptr GCancellable, :ptr GError
_query_settable_attributes_async proc
_query_settable_attributes_finish proc
query_writable_namespaces proc :ptr GFile, :ptr GCancellable, :ptr GError
_query_writable_namespaces_async proc
_query_writable_namespaces_finish proc
set_attribute		proc :ptr GFile, :ptr char_t, :GFileAttributeType, :gpointer, :GFileQueryInfoFlags, :ptr GCancellable, :ptr GError
set_attributes_from_info proc :ptr GFile, :ptr GFileInfo, :GFileQueryInfoFlags, :ptr GCancellable, :ptr GError
set_attributes_async	proc :ptr GFile, :ptr GFileInfo, :GFileQueryInfoFlags, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
set_attributes_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GFileInfo, :ptr GError
read_fn			proc :ptr GFile, :ptr GCancellable, :ptr GError
read_async		proc :ptr GFile, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
read_finish		proc :ptr GFile, :ptr GFileInputStream, :ptr GAsyncResult, :ptr GError
append_to		proc :ptr GFile, :GFileCreateFlags, :ptr GCancellable, :ptr GError
append_to_async		proc :ptr GFile, :GFileCreateFlags, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
append_to_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
create			proc :ptr GFile, :GFileCreateFlags, :ptr GCancellable, :ptr GError
create_async		proc :ptr GFile, :GFileCreateFlags, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
create_finish		proc :ptr GFile, :ptr GAsyncResult, :ptr GError
replace			proc :ptr GFile, :ptr char_t, :gboolean, :GFileCreateFlags, :ptr GCancellable, :ptr GError
replace_async		proc :ptr GFile, :ptr char_t, :gboolean, :GFileCreateFlags, :SINT, :ptr GCancel, :GAsyncReadyCallback, :gpointer
replace_finish		proc :ptr GFile, :ptr GAsyncResult, :ptr GError
delete_file		proc :ptr GFile, :ptr GCancellable, :ptr GError
delete_file_async	proc :ptr GFile, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
delete_file_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
trash			proc :ptr GFile, :ptr GCancellable, :ptr GError
trash_async		proc :ptr GFile, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
trash_finish		proc :ptr GFile, :ptr GAsyncResult, :ptr GError
make_directory		proc :ptr GFile, :ptr GCancellable, :ptr GError
make_directory_async	proc :ptr GFile, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
make_directory_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
make_symbolic_link	proc :ptr GFile, :ptr char_t, :ptr GCancellable, :ptr GError
_make_symbolic_link_async proc
_make_symbolic_link_finish proc
copy			proc :ptr GFile, :ptr GFile, :GFileCopyFlags, :ptr GCancellable, :GFileProgressCallback, :gpointer, :ptr GError
copy_async		proc :ptr GFile, :ptr GFile, :GFileCopyFlags, :SINT, :ptr GCancellable, :GFileProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
copy_finish		proc :ptr GFile, :ptr GAsyncResult, :ptr GError
move			proc :ptr GFile, :ptr GFile, :GFileCopyFlags, :ptr GCancellable, :GFileProgressCallback, :gpointer, :ptr GError
move_async		proc :ptr GFile, :ptr GFile, :GFileCopyFlags, :SINT, :ptr GCancellable, :GFileProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
move_finish		proc :ptr GFile, :ptr GAsyncResult, :ptr GError
mount_mountable		proc :ptr GFile, :GMountMountFlags, :ptr GMountOperation, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
mount_mountable_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
unmount_mountable	proc :ptr GFile, :GMountUnmountFlags, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
unmount_mountable_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
eject_mountable		proc :ptr GFile, :GMountUnmountFlags, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
eject_mountable_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
mount_enclosing_volume	proc :ptr GFile, :GMountMountFlags, :ptr GMountOperation, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
mount_enclosing_volume_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
monitor_dir		proc :ptr GFile,:ptr GFileMonitor, :GFileMonitorFlags, :ptr GCancellable, :ptr GError
monitor_file		proc :ptr GFile, :ptr GFileMonitor, :GFileMonitorFlags, :ptr GCancellable, :ptr GError
open_readwrite		proc :ptr GFile, :ptr GFileIOStream, :ptr GCancellable, :ptr GError
open_readwrite_async	proc :ptr GFile, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
open_readwrite_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
create_readwrite	proc :ptr GFile, :ptr GFileIOStream, :GFileCreateFlags, :ptr GCancellable, :ptr GError
create_readwrite_async	proc :ptr GFile, :GFileCreateFlags, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
create_readwrite_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
replace_readwrite	proc :ptr GFile, :ptr char_t, :gboolean, :GFileCreateFlags, :ptr GCancellable, :ptr GError
replace_readwrite_async proc :ptr GFile, :ptr char_t, :gboolean, :GFileCreateFlags, :SINT, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
replace_readwrite_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
start_mountable		proc :ptr GFile, :GDriveStartFlags, :ptr GMountOperation, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
start_mountable_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
stop_mountable		proc :ptr GFile, :GMountUnmountFlags, :ptr GMountOperation, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
stop_mountable_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError

supports_thread_contexts gboolean ?

unmount_mountable_with_operation proc :ptr GFile, :GMountUnmountFlags, :ptr GMountOperation, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
unmount_mountable_with_operation_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
eject_mountable_with_operation proc :ptr GFile, :GMountUnmountFlags, :ptr GMountOperation, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
eject_mountable_with_operation_finish proc :ptr GFile, :ptr GAsyncResult, :ptr GError
poll_mountable		proc :ptr GFile, :ptr GCancellable, :GAsyncReadyCallback, :gpointer
poll_mountable_finish	proc :ptr GFile, :ptr GAsyncResult, :ptr GError
measure_disk_usage	proc :ptr GFile, :GFileMeasureFlags, :ptr GCancellable, :GFileMeasureProgressCallback, :gpointer, :ptr guint64, :ptr guint64, :ptr, :ptr GError
measure_disk_usage_async proc :ptr GFile, :GFileMeasureFlags, :gint, :ptr GCancellable, :GFileMeasureProgressCallback, :gpointer, :GAsyncReadyCallback, :gpointer
measure_disk_usage_finish proc :ptr GFile, :ptr GAsyncResult, :ptr guint64, :ptr guint64, :ptr guint64, :ptr GError
GFileIface		ENDS

;GType
g_file_get_type proto __cdecl

;GFile
g_file_new_for_path proto __cdecl \
		  path: ptr char_t

;GFile
g_file_new_for_uri proto __cdecl \
		   uri: ptr char_t

;GFile
g_file_new_for_commandline_arg proto __cdecl \
		   arg: ptr char_t

;GFile
g_file_new_for_commandline_arg_and_cwd proto __cdecl \
		   arg: ptr gchar,
		  _cwd: ptr gchar

;GFile
g_file_new_tmp proto __cdecl \
		  tmpl: ptr char_t,
	      iostream: ptr GFileIOStream,
		 error: ptr GError

;GFile
g_file_parse_name proto __cdecl \
	    parse_name: ptr char_t

;GFile
g_file_new_build_filename proto _CDecl \
	 first_element: ptr gchar,
		      : vararg

;GFile
g_file_dup proto __cdecl \
		  file: ptr GFile

;guint
g_file_hash proto __cdecl \
		  file: gconstpointer

;gboolean
g_file_equal proto __cdecl \
		 file1: ptr GFile,
		 file2: ptr GFile

;char
g_file_get_basename proto __cdecl \
		  file: ptr GFile

;char
g_file_get_path proto __cdecl \
		  file: ptr GFile

;const
g_file_peek_path proto __cdecl \
		  file: ptr GFile

;char
g_file_get_uri proto __cdecl \
		  file: ptr GFile

;char
g_file_get_parse_name proto __cdecl \
		  file: ptr GFile

;GFile
g_file_get_parent proto __cdecl \
		  file: ptr GFile

;gboolean
g_file_has_parent proto __cdecl \
		  file: ptr GFile,
		parent: ptr GFile

;GFile
g_file_get_child proto __cdecl \
		  file: ptr GFile,
		  name: ptr char_t

;GFile
g_file_get_child_for_display_name proto __cdecl \
		  file: ptr GFile,
	  display_name: ptr char_t,
		 error: ptr GError

;gboolean
g_file_has_prefix proto __cdecl \
		  file: ptr GFile,
		prefix: ptr GFile

;char
g_file_get_relative_path proto __cdecl \
		parent: ptr GFile,
	    descendant: ptr GFile

;GFile
g_file_resolve_relative_path proto __cdecl \
		  file: ptr GFile,
	 relative_path: ptr char_t

;gboolean
g_file_is_native proto __cdecl \
		  file: ptr GFile

;gboolean
g_file_has_uri_scheme proto __cdecl \
		  file: ptr GFile,
	    uri_scheme: ptr char_t

;char
g_file_get_uri_scheme proto __cdecl \
		  file: ptr GFile

;GFileInputStream
g_file_read proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_read_async proto __cdecl \
		  file: ptr GFile,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileInputStream
g_file_read_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GFileOutputStream
g_file_append_to proto __cdecl \
		  file: ptr GFile,
		 flags: GFileCreateFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;GFileOutputStream
g_file_create proto __cdecl \
		  file: ptr GFile,
		 flags: GFileCreateFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;GFileOutputStream
g_file_replace proto __cdecl \
		  file: ptr GFile,
		  etag: ptr char_t,
	   make_backup: gboolean,
		 flags: GFileCreateFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_append_to_async proto __cdecl \
		  file: ptr GFile,
		 flags: GFileCreateFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileOutputStream
g_file_append_to_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_create_async proto __cdecl \
		  file: ptr GFile,
		 flags: GFileCreateFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileOutputStream
g_file_create_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_replace_async proto __cdecl \
		  file: ptr GFile,
		  etag: ptr char_t,
	   make_backup: gboolean,
		 flags: GFileCreateFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileOutputStream
g_file_replace_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GFileIOStream
g_file_open_readwrite proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_open_readwrite_async proto __cdecl \
		  file: ptr GFile,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileIOStream
g_file_open_readwrite_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GFileIOStream
g_file_create_readwrite proto __cdecl \
		  file: ptr GFile,
		 flags: GFileCreateFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_create_readwrite_async proto __cdecl \
		  file: ptr GFile,
		 flags: GFileCreateFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileIOStream
g_file_create_readwrite_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GFileIOStream
g_file_replace_readwrite proto __cdecl \
		  file: ptr GFile,
		  etag: ptr char_t,
	   make_backup: gboolean,
		 flags: GFileCreateFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_replace_readwrite_async proto __cdecl \
		  file: ptr GFile,
		  etag: ptr char_t,
	   make_backup: gboolean,
		 flags: GFileCreateFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileIOStream
g_file_replace_readwrite_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;gboolean
g_file_query_exists proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable

;GFileType
g_file_query_file_type proto __cdecl \
		  file: ptr GFile,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable

;GFileInfo
g_file_query_info proto __cdecl \
		  file: ptr GFile,
	    attributes: ptr char_t,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_query_info_async proto __cdecl \
		  file: ptr GFile,
	    attributes: ptr char_t,
		 flags: GFileQueryInfoFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileInfo
g_file_query_info_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GFileInfo
g_file_query_filesystem_info proto __cdecl \
		  file: ptr GFile,
	    attributes: ptr char_t,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_query_filesystem_info_async proto __cdecl \
		  file: ptr GFile,
	    attributes: ptr char_t,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileInfo
g_file_query_filesystem_info_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GMount
g_file_find_enclosing_mount proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_find_enclosing_mount_async proto __cdecl \
		  file: ptr GFile,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GMount
g_file_find_enclosing_mount_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GFileEnumerator
g_file_enumerate_children proto __cdecl \
		  file: ptr GFile,
	    attributes: ptr char_t,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_enumerate_children_async proto __cdecl \
		  file: ptr GFile,
	    attributes: ptr char_t,
		 flags: GFileQueryInfoFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFileEnumerator
g_file_enumerate_children_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GFile
g_file_set_display_name proto __cdecl \
		  file: ptr GFile,
	  display_name: ptr char_t,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_set_display_name_async proto __cdecl \
		  file: ptr GFile,
	  display_name: ptr char_t,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFile
g_file_set_display_name_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;gboolean
g_file_delete proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;void
g_file_delete_async proto __cdecl \
		  file: ptr GFile,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer


;gboolean
g_file_delete_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError


;gboolean
g_file_trash proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;void
g_file_trash_async proto __cdecl \
		  file: ptr GFile,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer


;gboolean
g_file_trash_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError


;gboolean
g_file_copy proto __cdecl \
		source: ptr GFile,
	   destination: ptr GFile,
		 flags: GFileCopyFlags,
	   cancellable: ptr GCancellable,
     progress_callback: GFileProgressCallback,
progress_callback_data: gpointer,
		 error: ptr GError

;void
g_file_copy_async proto __cdecl \
		source: ptr GFile,
	   destination: ptr GFile,
		 flags: GFileCopyFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
     progress_callback: GFileProgressCallback,
progress_callback_data: gpointer,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_copy_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
		 error: ptr GError

;gboolean
g_file_move proto __cdecl \
		source: ptr GFile,
	   destination: ptr GFile,
		 flags: GFileCopyFlags,
	   cancellable: ptr GCancellable,
     progress_callback: GFileProgressCallback,
progress_callback_data: gpointer,
		 error: ptr GError

;void
g_file_move_async proto __cdecl \
		source: ptr GFile,
	   destination: ptr GFile,
		 flags: GFileCopyFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
     progress_callback: GFileProgressCallback,
progress_callback_data: gpointer,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_move_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;gboolean
g_file_make_directory proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_make_directory_async proto __cdecl \
		  file: ptr GFile,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_make_directory_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError


;gboolean
g_file_make_directory_with_parents proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_make_symbolic_link proto __cdecl \
		  file: ptr GFile,
	 symlink_value: ptr char_t,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;GFileAttributeInfoList
g_file_query_settable_attributes proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;GFileAttributeInfoList
g_file_query_writable_namespaces proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_set_attribute proto __cdecl \
		  file: ptr GFile,
	     attribute: ptr char_t,
		  type: GFileAttributeType,
	       value_p: gpointer,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_set_attributes_from_info proto __cdecl \
		  file: ptr GFile,
		  info: ptr GFileInfo,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_set_attributes_async proto __cdecl \
		  file: ptr GFile,
		  info: ptr GFileInfo,
		 flags: GFileQueryInfoFlags,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_set_attributes_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		  info: ptr GFileInfo,
		 error: ptr GError

;gboolean
g_file_set_attribute_string proto __cdecl \
		  file: ptr GFile,
	     attribute: ptr char_t,
		 value: ptr char_t,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_set_attribute_byte_string proto __cdecl \
		  file: ptr GFile,
	     attribute: ptr char_t,
		 value: ptr char_t,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_set_attribute_uint32 proto __cdecl \
		  file: ptr GFile,
	     attribute: ptr char_t,
		 value: guint32,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_set_attribute_int32 proto __cdecl \
		  file: ptr GFile,
	     attribute: ptr char_t,
		 value: gint32,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_set_attribute_uint64 proto __cdecl \
		  file: ptr GFile,
	     attribute: ptr char_t,
		 value: guint64,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_set_attribute_int64 proto __cdecl \
		  file: ptr GFile,
	     attribute: ptr char_t,
		 value: gint64,
		 flags: GFileQueryInfoFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_mount_enclosing_volume proto __cdecl \
	      location: ptr GFile,
		 flags: GMountMountFlags,
       mount_operation: ptr GMountOperation,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_mount_enclosing_volume_finish proto __cdecl \
	      location: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_mount_mountable proto __cdecl \
		  file: ptr GFile,
		 flags: GMountMountFlags,
       mount_operation: ptr GMountOperation,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GFile
g_file_mount_mountable_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_unmount_mountable proto __cdecl \
		  file: ptr GFile,
		 flags: GMountUnmountFlags,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer


g_file_unmount_mountable_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_unmount_mountable_with_operation proto __cdecl \
		  file: ptr GFile,
		 flags: GMountUnmountFlags,
       mount_operation: ptr GMountOperation,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_unmount_mountable_with_operation_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_eject_mountable proto __cdecl \
		  file: ptr GFile,
		 flags: GMountUnmountFlags,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

g_file_eject_mountable_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_eject_mountable_with_operation proto __cdecl \
		  file: ptr GFile,
		 flags: GMountUnmountFlags,
       mount_operation: ptr GMountOperation,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_eject_mountable_with_operation_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;char
g_file_build_attribute_list_for_copy proto __cdecl \
		  file: ptr GFile,
		 flags: GFileCopyFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_file_copy_attributes proto __cdecl \
		source: ptr GFile,
	   destination: ptr GFile,
		 flags: GFileCopyFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;GFileMonitor*
g_file_monitor_directory proto __cdecl \
		  file: ptr GFile,
		 flags: GFileMonitorFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;GFileMonitor*
g_file_monitor_file proto __cdecl \
		  file: ptr GFile,
		 flags: GFileMonitorFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;GFileMonitor*
g_file_monitor proto __cdecl \
		  file: ptr GFile,
		 flags: GFileMonitorFlags,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;gboolean
g_file_measure_disk_usage proto __cdecl \
		  file: ptr GFile,
		 flags: GFileMeasureFlags,
	   cancellable: ptr GCancellable,
     progress_callback: GFileMeasureProgressCallback,
	 progress_data: gpointer,
	    disk_usage: ptr guint64,
	      num_dirs: ptr guint64,
	     num_files: ptr guint64,
		 error: ptr GError

;void
g_file_measure_disk_usage_async proto __cdecl \
		  file: ptr GFile,
		 flags: GFileMeasureFlags,
	   io_priority: gint,
	   cancellable: ptr GCancellable,
     progress_callback: GFileMeasureProgressCallback,
	 progress_data: gpointer,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer


;gboolean
g_file_measure_disk_usage_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
	    disk_usage: ptr guint64,
	      num_dirs: ptr guint64,
	     num_files: ptr guint64,
		 error: ptr GError


;void
g_file_start_mountable proto __cdecl \
		  file: ptr GFile,
		 flags: GDriveStartFlags,
       start_operation: ptr GMountOperation,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_start_mountable_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;void
g_file_stop_mountable proto __cdecl \
		  file: ptr GFile,
		 flags: GMountUnmountFlags,
       mount_operation: ptr GMountOperation,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_stop_mountable_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError


;void
g_file_poll_mountable proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_poll_mountable_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError

;GAppInfo
g_file_query_default_handler proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_query_default_handler_async proto __cdecl \
		  file: ptr GFile,
	   io_priority: SINT,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GAppInfo
g_file_query_default_handler_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
		 error: ptr GError


;gboolean
g_file_load_contents proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
	      contents: ptr char_t,
		length: ptr gsize,
	      etag_out: ptr char_t,
		 error: ptr GError

;void
g_file_load_contents_async proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_load_contents_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
	      contents: ptr char_t,
		length: ptr gsize,
	      etag_out: ptr char_t,
		 error: ptr GError

;void
g_file_load_partial_contents_async proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
    read_more_callback: GFileReadMoreCallback,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_load_partial_contents_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
	      contents: ptr char_t,
		length: ptr gsize,
	      etag_out: ptr char_t,
		 error: ptr GError

;gboolean
g_file_replace_contents proto __cdecl \
		  file: ptr GFile,
	      contents: ptr char_t,
		length: gsize,
		  etag: ptr char_t,
	   make_backup: gboolean,
		 flags: GFileCreateFlags,
	      new_etag: ptr char_t,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_file_replace_contents_async proto __cdecl \
		  file: ptr GFile,
	      contents: ptr char_t,
		length: gsize,
		  etag: ptr char_t,
	   make_backup: gboolean,
		 flags: GFileCreateFlags,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;void
g_file_replace_contents_bytes_async proto __cdecl \
		  file: ptr GFile,
	      contents: ptr GBytes,
		  etag: ptr char_t,
	   make_backup: gboolean,
		 flags: GFileCreateFlags,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_file_replace_contents_finish proto __cdecl \
		  file: ptr GFile,
		   res: ptr GAsyncResult,
	      new_etag: ptr char_t,
		 error: ptr GError


;gboolean
g_file_supports_thread_contexts proto __cdecl \
		  file: ptr GFile


;GBytes
g_file_load_bytes proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
	      etag_out: ptr gchar,
		 error: ptr GError

;void
g_file_load_bytes_async proto __cdecl \
		  file: ptr GFile,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GBytes
g_file_load_bytes_finish proto __cdecl \
		  file: ptr GFile,
		result: ptr GAsyncResult,
	      etag_out: ptr gchar,
		 error: ptr GError


endif
