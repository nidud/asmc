ifndef __G_DATASET_H__
define __G_DATASET_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gquark.inc

CALLBACKC(GDataForeachFunc, :GQuark, :gpointer, :gpointer)

g_datalist_init proto __cdecl \
	      datalist: ptr GData

g_datalist_clear proto __cdecl \
	      datalist: ptr GData

;gpointer
g_datalist_id_get_data proto __cdecl \
	      datalist: ptr GData,
		key_id: GQuark

g_datalist_id_set_data_full proto __cdecl \
	      datalist: ptr GData,
		key_id: GQuark,
		  data: gpointer,
	  destroy_func: GDestroyNotify


CALLBACKC(GDuplicateFunc, :gpointer, :gpointer)

;gpointer
g_datalist_id_dup_data proto __cdecl \
	      datalist: ptr GData,
		key_id: GQuark,
	      dup_func: GDuplicateFunc,
	     user_data: gpointer

;gboolean
g_datalist_id_replace_data proto __cdecl \
	      datalist: ptr GData,
		key_id: GQuark,
		oldval: gpointer,
		newval: gpointer,
	       destroy: GDestroyNotify,
	   old_destroy: ptr GDestroyNotify


;gpointer
g_datalist_id_remove_no_notify proto __cdecl \
	      datalist: ptr GData,
		key_id: GQuark

g_datalist_foreach proto __cdecl \
	      datalist: ptr GData,
		  func: GDataForeachFunc,
	     user_data: gpointer


G_DATALIST_FLAGS_MASK	equ 0x3

g_datalist_set_flags proto __cdecl \
	      datalist: ptr GData,
		 flags: guint

g_datalist_unset_flags proto __cdecl \
	      datalist: ptr GData,
		 flags: guint

g_datalist_get_flags proto __cdecl \
	      datalist: ptr GData


g_dataset_destroy proto __cdecl \
      dataset_location: gconstpointer

;gpointer
g_dataset_id_get_data proto __cdecl \
      dataset_location: gconstpointer,
		key_id: GQuark

;gpointer
g_datalist_get_data proto __cdecl \
	      datalist: ptr GData,
		   key: ptr gchar

;void
g_dataset_id_set_data_full proto __cdecl \
      dataset_location: gconstpointer,
		key_id: GQuark,
		  data: gpointer,
	  destroy_func: GDestroyNotify

;gpointer
g_dataset_id_remove_no_notify proto __cdecl \
      dataset_location: gconstpointer,
		key_id: GQuark

;void
g_dataset_foreach proto __cdecl \
      dataset_location: gconstpointer,
		  func: GDataForeachFunc,
	     user_data: gpointer

endif
