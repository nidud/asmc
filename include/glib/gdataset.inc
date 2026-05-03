ifndef __G_DATASET_H__
define __G_DATASET_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gquark.inc

CALLBACKC(GDataForeachFunc, :GQuark, :gpointer, :gpointer)

g_datalist_init proto __cdecl :ptr
g_datalist_clear proto __cdecl :ptr
g_datalist_id_get_data proto __cdecl :ptr, :GQuark
g_datalist_id_set_data_full proto __cdecl :ptr, :GQuark, :gpointer, :GDestroyNotify

CALLBACKC(GDuplicateFunc, :gpointer, :gpointer)

g_datalist_id_dup_data proto __cdecl :ptr, :GQuark, :GDuplicateFunc, :gpointer
g_datalist_id_replace_data proto __cdecl :ptr, :GQuark, :gpointer, :gpointer, :GDestroyNotify, :ptr
g_datalist_id_remove_no_notify proto __cdecl :ptr, :GQuark
g_datalist_foreach proto __cdecl :ptr, :GDataForeachFunc, :gpointer

G_DATALIST_FLAGS_MASK	equ 0x3

g_datalist_set_flags proto __cdecl :ptr, :guint
g_datalist_unset_flags proto __cdecl :ptr, :guint
g_datalist_get_flags proto __cdecl :ptr
g_dataset_destroy proto __cdecl :gconstpointer
g_dataset_id_get_data proto __cdecl :gconstpointer, :GQuark
g_datalist_get_data proto __cdecl :ptr, :ptr
g_dataset_id_set_data_full proto __cdecl :gconstpointer, :GQuark, :gpointer, :GDestroyNotify
g_dataset_id_remove_no_notify proto __cdecl :gconstpointer, :GQuark
g_dataset_foreach proto __cdecl :gconstpointer, :GDataForeachFunc, :gpointer

endif
