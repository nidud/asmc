ifndef __G_MEM_H__
__G_MEM_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gutils.inc

if GLIB_SIZEOF_VOID_P GT GLIB_SIZEOF_LONG
  G_MEM_ALIGN	equ GLIB_SIZEOF_VOID_P
else
  G_MEM_ALIGN	equ GLIB_SIZEOF_LONG
endif

g_free proto __cdecl \
		   mem: gpointer

g_clear_pointer proto __cdecl \
		    pp: ptr gpointer,
	       destroy: GDestroyNotify

;gpointer
g_malloc proto __cdecl \
	       n_bytes: gsize

g_malloc0 proto __cdecl \
	       n_bytes: gsize

g_realloc proto __cdecl \
		   mem: gpointer,
	       n_bytes: gsize

g_try_malloc proto __cdecl \
	       n_bytes: gsize

g_try_malloc0 proto __cdecl \
	       n_bytes: gsize

g_try_realloc proto __cdecl \
		   mem: gpointer,
	       n_bytes: gsize

g_malloc_n proto __cdecl \
	      n_blocks: gsize,
	 n_block_bytes: gsize

g_malloc0_n proto __cdecl \
	      n_blocks: gsize,
	 n_block_bytes: gsize

g_realloc_n proto __cdecl \
		   mem: gpointer,
	      n_blocks: gsize,
	 n_block_bytes: gsize

g_try_malloc_n proto __cdecl \
	      n_blocks: gsize,
	 n_block_bytes: gsize

;gpointer
g_try_malloc0_n proto __cdecl \
	      n_blocks: gsize,
	 n_block_bytes: gsize

;gpointer
g_try_realloc_n proto __cdecl \
		   mem: gpointer,
	      n_blocks: gsize,
	 n_block_bytes: gsize
if 0
g_clear_pointer macro pp, destroy
	exitm<.err>
	endm

g_steal_pointer macro pp
	exitm<.err>
	endm
endif

_G_NEW macro struct_type, n_structs, func
	exitm<.err>
	endm
_G_RENEW macro struct_type, mem, n_structs, func
	exitm<.err>
	endm

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


g_mem_set_vtable proto __cdecl \
		vtable: ptr GMemVTable

;GLIB_VAR gboolean g_mem_gc_friendly;
;GLIB_VAR GMemVTable *glib_mem_profiler_table;

g_mem_profile proto __cdecl

endif
