ifndef __GTK_SCROLLABLE_H__
__GTK_SCROLLABLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc
include gtk/gtktypes.inc
include gtk/gtkborder.inc

G_BEGIN_DECLS

GTK_TYPE_SCROLLABLE equ <gtk_scrollable_get_type>
GTK_SCROLLABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj),     GTK_TYPE_SCROLLABLE, GtkScrollable))>
	endm
GTK_IS_SCROLLABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj),     GTK_TYPE_SCROLLABLE))>
	endm
GTK_SCROLLABLE_GET_IFACE macro inst
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_SCROLLABLE, GtkScrollableInterface))>
	endm

GtkScrollableInterface	STRUC
base_iface		GTypeInterface <>
get_border		proc :ptr GtkScrollable, :ptr GtkBorder
GtkScrollableInterface	ENDS

;GType
gtk_scrollable_get_type proto __cdecl
;GtkAdjustment
gtk_scrollable_get_hadjustment proto __cdecl \
	    scrollable: ptr GtkScrollable

;void
gtk_scrollable_set_hadjustment proto __cdecl \
	    scrollable: ptr GtkScrollable,
	   hadjustment: ptr GtkAdjustment

;GtkAdjustment
gtk_scrollable_get_vadjustment proto __cdecl \
	    scrollable: ptr GtkScrollable

;void
gtk_scrollable_set_vadjustment proto __cdecl \
	    scrollable: ptr GtkScrollable,
	   vadjustment: ptr GtkAdjustment

;GtkScrollablePolicy
gtk_scrollable_get_hscroll_policy proto __cdecl \
	    scrollable: ptr GtkScrollable

;void
gtk_scrollable_set_hscroll_policy proto __cdecl \
	    scrollable: ptr GtkScrollable,
		policy: GtkScrollablePolicy

;GtkScrollablePolicy
gtk_scrollable_get_vscroll_policy proto __cdecl \
	    scrollable: ptr GtkScrollable

;void
gtk_scrollable_set_vscroll_policy proto __cdecl \
	    scrollable: ptr GtkScrollable,
		policy: GtkScrollablePolicy


;gboolean
gtk_scrollable_get_border proto __cdecl \
	    scrollable: ptr GtkScrollable,
		border: ptr GtkBorder

G_END_DECLS

endif
