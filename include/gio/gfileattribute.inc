ifndef __G_FILE_ATTRIBUTE_H__
define __G_FILE_ATTRIBUTE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

_GFileAttributeInfo     struct
name                    ptr sbyte ?
type                    GFileAttributeType ?
flags                   GFileAttributeInfoFlags ?
_GFileAttributeInfo     ends
GFileAttributeInfo      typedef _GFileAttributeInfo

_GFileAttributeInfoList struct
infos                   ptr GFileAttributeInfo ?
n_infos                 sdword ?
_GFileAttributeInfoList ends
GFileAttributeInfoList  typedef _GFileAttributeInfoList

define G_TYPE_FILE_ATTRIBUTE_INFO_LIST <g_file_attribute_info_list_get_type>
g_file_attribute_info_list_get_type proto

g_file_attribute_info_list_new proto
g_file_attribute_info_list_ref proto :ptr
g_file_attribute_info_list_unref proto :ptr
g_file_attribute_info_list_dup proto :ptr
g_file_attribute_info_list_lookup proto :ptr, :ptr
g_file_attribute_info_list_add proto :ptr, :ptr, :GFileAttributeType, :GFileAttributeInfoFlags

endif
