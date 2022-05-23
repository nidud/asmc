ifndef __GMODULE_H__
define __GMODULE_H__

include glib.inc

.enum GModuleFlags {
  G_MODULE_BIND_LAZY	= 1 shl 0,
  G_MODULE_BIND_LOCAL	= 1 shl 1,
  G_MODULE_BIND_MASK	= 0x03
}

;GModule		 typedef _GModule
CALLBACK(GModuleCheckInit, :ptr)
CALLBACK(GModuleUnload, :ptr)

define G_MODULE_ERROR <g_module_error_quark>
g_module_error_quark proto

.enum GModuleError {
  G_MODULE_ERROR_FAILED,
  G_MODULE_ERROR_CHECK_FAILED,
}

g_module_supported proto
g_module_open proto :ptr, :GModuleFlags
g_module_open_full proto :ptr, :GModuleFlags, :ptr
g_module_close proto :ptr
g_module_make_resident proto :ptr
g_module_error proto
g_module_symbol proto :ptr, :ptr, :ptr
g_module_name proto :ptr
g_module_build_path proto :ptr, :ptr

endif
