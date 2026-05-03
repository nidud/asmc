ifndef __G_IO_MODULE_H__
define __G_IO_MODULE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc
include gmodule.inc

g_io_module_scope_new proto :GIOModuleScopeFlags
g_io_module_scope_free proto :ptr
g_io_module_scope_block proto :ptr, :ptr

define G_IO_TYPE_MODULE         <g_io_module_get_type ()>
G_IO_MODULE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_IO_TYPE_MODULE, GIOModule))>
  endm
G_IO_MODULE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_IO_TYPE_MODULE, GIOModuleClass))>
  endm
G_IO_IS_MODULE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_IO_TYPE_MODULE))>
  endm
G_IO_IS_MODULE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_IO_TYPE_MODULE))>
  endm
G_IO_MODULE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_IO_TYPE_MODULE, GIOModuleClass))>
  endm

g_io_module_get_type proto
g_io_module_new proto :ptr

g_io_modules_scan_all_in_directory proto :ptr
g_io_modules_load_all_in_directory proto :ptr

g_io_modules_scan_all_in_directory_with_scope proto :ptr, :ptr
g_io_modules_load_all_in_directory_with_scope proto :ptr, :ptr

g_io_extension_point_register proto :ptr
g_io_extension_point_lookup proto :ptr
g_io_extension_point_set_required_type proto :ptr, :GType
g_io_extension_point_get_required_type proto :ptr
g_io_extension_point_get_extensions proto :ptr
g_io_extension_point_get_extension_by_name proto :ptr, :ptr
g_io_extension_point_implement proto :ptr, :GType, :ptr, :gint

g_io_extension_get_type proto :ptr
g_io_extension_get_name proto :ptr
g_io_extension_get_priority proto :ptr
g_io_extension_ref_class proto :ptr
g_io_module_load proto :ptr
g_io_module_unload proto :ptr
g_io_module_query proto

endif
