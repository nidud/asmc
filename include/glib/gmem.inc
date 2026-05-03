ifndef __G_MEM_H__
define __G_MEM_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gutils.inc

if GLIB_SIZEOF_VOID_P GT GLIB_SIZEOF_LONG
  G_MEM_ALIGN	equ GLIB_SIZEOF_VOID_P
else
  G_MEM_ALIGN	equ GLIB_SIZEOF_LONG
endif

g_free proto __cdecl :ptr
g_clear_pointer proto __cdecl :ptr, :GDestroyNotify
g_malloc proto __cdecl :gsize
g_malloc0 proto __cdecl :gsize
g_realloc proto __cdecl :ptr, :gsize
g_try_malloc proto __cdecl :gsize
g_try_malloc0 proto __cdecl :gsize
g_try_realloc proto __cdecl :ptr, :gsize
g_malloc_n proto __cdecl :gsize, :gsize
g_malloc0_n proto __cdecl :gsize, :gsize
g_realloc_n proto __cdecl :ptr, :gsize, :gsize
g_try_malloc_n proto __cdecl :gsize, :gsize
g_try_malloc0_n proto __cdecl :gsize, :gsize
g_try_realloc_n proto __cdecl :ptr, :gsize, :gsize

g_new macro struct_type, n_structs
	exitm<_G_NEW (struct_type, n_structs, malloc)>
	endm

g_new0 macro struct_type, n_structs
	exitm<_G_NEW (struct_type, n_structs, malloc0)>
	endm

g_renew macro struct_type, mem, n_structs
	exitm<_G_RENEW (struct_type, mem, n_structs, realloc)>
	endm

g_try_new macro struct_type, n_structs
	exitm<_G_NEW (struct_type, n_structs, try_malloc)>
	endm

g_try_new0 macro struct_type, n_structs
	exitm<_G_NEW (struct_type, n_structs, try_malloc0)>
	endm

g_try_renew macro struct_type, mem, n_structs
	exitm<_G_RENEW (struct_type, mem, n_structs, try_realloc)>
	endm

GMemVTable		STRUC
malloc			proc :gsize
realloc			proc :gpointer, :gsize
free			proc :gpointer
calloc			proc :gsize, :gsize
try_malloc		proc :gsize
try_realloc		proc :gpointer, :gsize
GMemVTable		ENDS

g_mem_set_vtable proto __cdecl :ptr
g_mem_profile proto __cdecl

endif
