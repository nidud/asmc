ifndef __G_QSORT_H__
define __G_QSORT_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;void
g_qsort_with_data proto __cdecl \
		 pbase: gconstpointer,
	   total_elems: gint,
		  size: gsize,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer


endif ;; __G_QSORT_H__
