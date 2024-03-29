ifndef __GTK_IM_CONTEXT_INFO_H__
define __GTK_IM_CONTEXT_INFO_H__

if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib.inc

GtkIMContextInfo	STRUC
context_id		ptr_t ?
context_name		ptr_t ?
domain			ptr_t ?
domain_dirname		ptr_t ?
default_locales		ptr_t ?
GtkIMContextInfo	ENDS

endif
