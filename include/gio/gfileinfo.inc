ifndef __G_FILE_INFO_H__
define __G_FILE_INFO_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_FILE_INFO         <g_file_info_get_type ()>
G_FILE_INFO macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILE_INFO, GFileInfo))>
  endm
G_FILE_INFO_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILE_INFO, GFileInfoClass))>
  endm
G_IS_FILE_INFO macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILE_INFO))>
  endm
G_IS_FILE_INFO_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILE_INFO))>
  endm
G_FILE_INFO_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILE_INFO, GFileInfoClass))>
  endm


;GFileInfoClass          typedef _GFileInfoClass

define G_FILE_ATTRIBUTE_STANDARD_TYPE <"standard::type">
define G_FILE_ATTRIBUTE_STANDARD_IS_HIDDEN <"standard::is-hidden">
define G_FILE_ATTRIBUTE_STANDARD_IS_BACKUP <"standard::is-backup">
define G_FILE_ATTRIBUTE_STANDARD_IS_SYMLINK <"standard::is-symlink">
define G_FILE_ATTRIBUTE_STANDARD_IS_VIRTUAL <"standard::is-virtual">
define G_FILE_ATTRIBUTE_STANDARD_IS_VOLATILE <"standard::is-volatile">
define G_FILE_ATTRIBUTE_STANDARD_NAME <"standard::name">
define G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME <"standard::display-name">
define G_FILE_ATTRIBUTE_STANDARD_EDIT_NAME <"standard::edit-name">
define G_FILE_ATTRIBUTE_STANDARD_COPY_NAME <"standard::copy-name">
define G_FILE_ATTRIBUTE_STANDARD_DESCRIPTION <"standard::description">
define G_FILE_ATTRIBUTE_STANDARD_ICON <"standard::icon">
define G_FILE_ATTRIBUTE_STANDARD_SYMBOLIC_ICON <"standard::symbolic-icon">
define G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE <"standard::content-type">
define G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE <"standard::fast-content-type">
define G_FILE_ATTRIBUTE_STANDARD_SIZE <"standard::size">
define G_FILE_ATTRIBUTE_STANDARD_ALLOCATED_SIZE <"standard::allocated-size">
define G_FILE_ATTRIBUTE_STANDARD_SYMLINK_TARGET <"standard::symlink-target">
define G_FILE_ATTRIBUTE_STANDARD_TARGET_URI <"standard::target-uri">
define G_FILE_ATTRIBUTE_STANDARD_SORT_ORDER <"standard::sort-order">
define G_FILE_ATTRIBUTE_ETAG_VALUE <"etag::value">
define G_FILE_ATTRIBUTE_ID_FILE <"id::file">
define G_FILE_ATTRIBUTE_ID_FILESYSTEM <"id::filesystem">
define G_FILE_ATTRIBUTE_ACCESS_CAN_READ <"access::can-read">
define G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE <"access::can-write">
define G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE <"access::can-execute">
define G_FILE_ATTRIBUTE_ACCESS_CAN_DELETE <"access::can-delete">
define G_FILE_ATTRIBUTE_ACCESS_CAN_TRASH <"access::can-trash">
define G_FILE_ATTRIBUTE_ACCESS_CAN_RENAME <"access::can-rename">

define G_FILE_ATTRIBUTE_MOUNTABLE_CAN_MOUNT <"mountable::can-mount">
define G_FILE_ATTRIBUTE_MOUNTABLE_CAN_UNMOUNT <"mountable::can-unmount">
define G_FILE_ATTRIBUTE_MOUNTABLE_CAN_EJECT <"mountable::can-eject">
define G_FILE_ATTRIBUTE_MOUNTABLE_UNIX_DEVICE <"mountable::unix-device">
define G_FILE_ATTRIBUTE_MOUNTABLE_UNIX_DEVICE_FILE <"mountable::unix-device-file">
define G_FILE_ATTRIBUTE_MOUNTABLE_HAL_UDI <"mountable::hal-udi">
define G_FILE_ATTRIBUTE_MOUNTABLE_CAN_START <"mountable::can-start">
define G_FILE_ATTRIBUTE_MOUNTABLE_CAN_START_DEGRADED <"mountable::can-start-degraded">

define G_FILE_ATTRIBUTE_MOUNTABLE_CAN_STOP <"mountable::can-stop">
define G_FILE_ATTRIBUTE_MOUNTABLE_START_STOP_TYPE <"mountable::start-stop-type">
define G_FILE_ATTRIBUTE_MOUNTABLE_CAN_POLL <"mountable::can-poll">
define G_FILE_ATTRIBUTE_MOUNTABLE_IS_MEDIA_CHECK_AUTOMATIC <"mountable::is-media-check-automatic">
define G_FILE_ATTRIBUTE_TIME_MODIFIED <"time::modified">
define G_FILE_ATTRIBUTE_TIME_MODIFIED_USEC <"time::modified-usec">
define G_FILE_ATTRIBUTE_TIME_ACCESS <"time::access">
define G_FILE_ATTRIBUTE_TIME_ACCESS_USEC <"time::access-usec">
define G_FILE_ATTRIBUTE_TIME_CHANGED <"time::changed">
define G_FILE_ATTRIBUTE_TIME_CHANGED_USEC <"time::changed-usec">
define G_FILE_ATTRIBUTE_TIME_CREATED <"time::created">
define G_FILE_ATTRIBUTE_TIME_CREATED_USEC <"time::created-usec">

define G_FILE_ATTRIBUTE_UNIX_DEVICE <"unix::device">
define G_FILE_ATTRIBUTE_UNIX_INODE <"unix::inode">
define G_FILE_ATTRIBUTE_UNIX_MODE <"unix::mode">
define G_FILE_ATTRIBUTE_UNIX_NLINK <"unix::nlink">
define G_FILE_ATTRIBUTE_UNIX_UID <"unix::uid">
define G_FILE_ATTRIBUTE_UNIX_GID <"unix::gid">
define G_FILE_ATTRIBUTE_UNIX_RDEV <"unix::rdev">
define G_FILE_ATTRIBUTE_UNIX_BLOCK_SIZE <"unix::block-size">
define G_FILE_ATTRIBUTE_UNIX_BLOCKS <"unix::blocks">
define G_FILE_ATTRIBUTE_UNIX_IS_MOUNTPOINT <"unix::is-mountpoint">

define G_FILE_ATTRIBUTE_DOS_IS_ARCHIVE <"dos::is-archive">
define G_FILE_ATTRIBUTE_DOS_IS_SYSTEM <"dos::is-system">
define G_FILE_ATTRIBUTE_DOS_IS_MOUNTPOINT <"dos::is-mountpoint">
define G_FILE_ATTRIBUTE_DOS_REPARSE_POINT_TAG <"dos::reparse-point-tag">

define G_FILE_ATTRIBUTE_OWNER_USER <"owner::user">
define G_FILE_ATTRIBUTE_OWNER_USER_REAL <"owner::user-real">
define G_FILE_ATTRIBUTE_OWNER_GROUP <"owner::group">

define G_FILE_ATTRIBUTE_THUMBNAIL_PATH <"thumbnail::path">
define G_FILE_ATTRIBUTE_THUMBNAILING_FAILED <"thumbnail::failed">
define G_FILE_ATTRIBUTE_THUMBNAIL_IS_VALID <"thumbnail::is-valid">

define G_FILE_ATTRIBUTE_PREVIEW_ICON <"preview::icon">

define G_FILE_ATTRIBUTE_FILESYSTEM_SIZE <"filesystem::size">
define G_FILE_ATTRIBUTE_FILESYSTEM_FREE <"filesystem::free">
define G_FILE_ATTRIBUTE_FILESYSTEM_USED <"filesystem::used">
define G_FILE_ATTRIBUTE_FILESYSTEM_TYPE <"filesystem::type">
define G_FILE_ATTRIBUTE_FILESYSTEM_READONLY <"filesystem::readonly">
define G_FILE_ATTRIBUTE_FILESYSTEM_USE_PREVIEW <"filesystem::use-preview">
define G_FILE_ATTRIBUTE_FILESYSTEM_REMOTE <"filesystem::remote">
define G_FILE_ATTRIBUTE_GVFS_BACKEND <"gvfs::backend">
define G_FILE_ATTRIBUTE_SELINUX_CONTEXT <"selinux::context">
define G_FILE_ATTRIBUTE_TRASH_ITEM_COUNT <"trash::item-count">
define G_FILE_ATTRIBUTE_TRASH_ORIG_PATH <"trash::orig-path">
define G_FILE_ATTRIBUTE_TRASH_DELETION_DATE <"trash::deletion-date">
define G_FILE_ATTRIBUTE_RECENT_MODIFIED <"recent::modified">

g_file_info_get_type proto

g_file_info_new proto
g_file_info_dup proto :ptr
g_file_info_copy_into proto :ptr, :ptr
g_file_info_has_attribute proto :ptr, :ptr
g_file_info_has_namespace proto :ptr, :ptr
g_file_info_list_attributes proto :ptr, :ptr
g_file_info_get_attribute_data proto :ptr, :ptr, :ptr, :ptr, :ptr
g_file_info_get_attribute_type proto :ptr, :ptr
g_file_info_remove_attribute proto :ptr, :ptr
g_file_info_get_attribute_status proto :ptr, :ptr
g_file_info_set_attribute_status proto :ptr, :ptr, :GFileAttributeStatus
g_file_info_get_attribute_as_string proto :ptr, :ptr
g_file_info_get_attribute_string proto :ptr, :ptr
g_file_info_get_attribute_byte_string proto :ptr, :ptr
g_file_info_get_attribute_boolean proto :ptr, :ptr
g_file_info_get_attribute_uint32 proto :ptr, :ptr
g_file_info_get_attribute_int32 proto :ptr, :ptr
g_file_info_get_attribute_uint64 proto :ptr, :ptr
g_file_info_get_attribute_int64 proto :ptr, :ptr
g_file_info_get_attribute_object proto :ptr, :ptr
g_file_info_get_attribute_stringv proto :ptr, :ptr

g_file_info_set_attribute proto :ptr, :ptr, :GFileAttributeType, :gpointer
g_file_info_set_attribute_string proto :ptr, :ptr, :ptr
g_file_info_set_attribute_byte_string proto :ptr, :ptr, :ptr
g_file_info_set_attribute_boolean proto :ptr, :ptr, :gboolean
g_file_info_set_attribute_uint32 proto :ptr, :ptr, :guint32
g_file_info_set_attribute_int32 proto :ptr, :ptr, :gint32
g_file_info_set_attribute_uint64 proto :ptr, :ptr, :guint64
g_file_info_set_attribute_int64 proto :ptr, :ptr, :gint64
g_file_info_set_attribute_object proto :ptr, :ptr, :ptr
g_file_info_set_attribute_stringv proto :ptr, :ptr, :ptr

g_file_info_clear_status proto :ptr

g_file_info_get_deletion_date proto :ptr
g_file_info_get_file_type proto :ptr
g_file_info_get_is_hidden proto :ptr
g_file_info_get_is_backup proto :ptr
g_file_info_get_is_symlink proto :ptr
g_file_info_get_name proto :ptr
g_file_info_get_display_name proto :ptr
g_file_info_get_edit_name proto :ptr
g_file_info_get_icon proto :ptr
g_file_info_get_symbolic_icon proto :ptr
g_file_info_get_content_type proto :ptr
g_file_info_get_size proto :ptr
g_file_info_get_modification_time proto :ptr, :ptr
g_file_info_get_modification_date_time proto :ptr
g_file_info_get_access_date_time proto :ptr
g_file_info_get_creation_date_time proto :ptr
g_file_info_get_symlink_target proto :ptr
g_file_info_get_etag proto :ptr
g_file_info_get_sort_order proto :ptr

g_file_info_set_attribute_mask proto :ptr, :ptr
g_file_info_unset_attribute_mask proto :ptr

g_file_info_set_file_type proto :ptr, :GFileType
g_file_info_set_is_hidden proto :ptr, :gboolean
g_file_info_set_is_symlink proto :ptr, :gboolean
g_file_info_set_name proto :ptr, :ptr
g_file_info_set_display_name proto :ptr, :ptr
g_file_info_set_edit_name proto :ptr, :ptr
g_file_info_set_icon proto :ptr, :ptr
g_file_info_set_symbolic_icon proto :ptr, :ptr
g_file_info_set_content_type proto :ptr, :ptr
g_file_info_set_size proto :ptr, :goffset
g_file_info_set_modification_time proto :ptr, :ptr
g_file_info_set_modification_date_time proto :ptr, :ptr
g_file_info_set_access_date_time proto :ptr, :ptr
g_file_info_set_creation_date_time proto :ptr, :ptr
g_file_info_set_symlink_target proto :ptr, :ptr
g_file_info_set_sort_order proto :ptr, :gint32

define G_TYPE_FILE_ATTRIBUTE_MATCHER <g_file_attribute_matcher_get_type ()>
g_file_attribute_matcher_get_type proto

g_file_attribute_matcher_new proto :ptr
g_file_attribute_matcher_ref proto :ptr
g_file_attribute_matcher_unref proto :ptr
g_file_attribute_matcher_subtract proto :ptr, :ptr
g_file_attribute_matcher_matches proto :ptr, :ptr
g_file_attribute_matcher_matches_only proto :ptr, :ptr
g_file_attribute_matcher_enumerate_namespace proto :ptr, :ptr
g_file_attribute_matcher_enumerate_next proto :ptr
g_file_attribute_matcher_to_string proto :ptr

endif
