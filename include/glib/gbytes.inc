ifndef __G_BYTES_H__
define __G_BYTES_H__

if not defined(__GLIB_H_INSIDE__) and not defined(GLIB_COMPILATION)
.err<"Only <glib.h> can be included directly.">
endif

include glib/gtypes.inc
include glib/garray.inc

g_bytes_new                     proto __cdecl :gconstpointer, :gsize
g_bytes_new_take                proto __cdecl :gpointer, :gsize
g_bytes_new_static              proto __cdecl :gconstpointer, :gsize
g_bytes_new_with_free_func      proto __cdecl :gconstpointer, :gsize, :GDestroyNotify, :gpointer
g_bytes_new_from_bytes          proto __cdecl :ptr GBytes, :gsize, :gsize
g_bytes_get_data                proto __cdecl :ptr GBytes, :ptr gsize
g_bytes_get_size                proto __cdecl :ptr GBytes
g_bytes_ref                     proto __cdecl :ptr GBytes
g_bytes_unref                   proto __cdecl :ptr GBytes
g_bytes_unref_to_data           proto __cdecl :ptr GBytes, :ptr gsize
g_bytes_unref_to_array          proto __cdecl :ptr GBytes
g_bytes_hash                    proto __cdecl :gconstpointer
g_bytes_equal                   proto __cdecl :gconstpointer, :gconstpointer
g_bytes_compare                 proto __cdecl :gconstpointer, :gconstpointer
g_bytes_get_region              proto __cdecl :ptr GBytes, :gsize, :gsize, :gsize

endif
