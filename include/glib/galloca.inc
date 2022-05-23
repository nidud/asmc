ifndef __G_ALLOCA_H__
define __G_ALLOCA_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
include string.inc
include malloc.inc

define g_alloca <alloca>

g_alloca0 proto watcall size:sword {
    .if ( size )
        memset(alloca(size), 0, size)
    .endif
    }

g_newa macro struct_type, n_structs
    exitm<alloca(sizeof(struct_type) * n_structs)>
    endm

g_newa0 macro struct_type, n_structs
    exitm<g_alloca0(sizeof(struct_type) * n_structs)>
    endm

endif
