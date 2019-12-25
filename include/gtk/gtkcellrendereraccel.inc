ifndef __GTK_CELL_RENDERER_ACCEL_H__
__GTK_CELL_RENDERER_ACCEL_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderertext.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_RENDERER_ACCEL equ <gtk_cell_renderer_accel_get_type>
GTK_CELL_RENDERER_ACCEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_ACCEL, GtkCellRendererAccel))>
	endm
GTK_CELL_RENDERER_ACCEL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_RENDERER_ACCEL, GtkCellRendererAccelClass))>
	endm
GTK_IS_CELL_RENDERER_ACCEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_ACCEL))>
	endm
GTK_IS_CELL_RENDERER_ACCEL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_RENDERER_ACCEL))>
	endm
GTK_CELL_RENDERER_ACCEL_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_RENDERER_ACCEL, GtkCellRendererAccelClass))>
	endm

GTK_CELL_RENDERER_ACCEL_MODE_GTK equ 0
GTK_CELL_RENDERER_ACCEL_MODE_OTHER equ 1
GTK_CELL_RENDERER_ACCEL_MODE_MODIFIER_TAP equ 2

GtkCellRendererAccel	STRUC
parent			GtkCellRendererText <>
priv			ptr_t ?
GtkCellRendererAccel	ENDS

GtkCellRendererAccelClass STRUC
parent_class		GtkCellRendererTextClass <>
accel_edited		proc :ptr GtkCellRendererAccel, :ptr gchar, :guint, :GdkModifierType, :guint
accel_cleared		proc :ptr GtkCellRendererAccel, :ptr gchar
_gtk_reserved0		proc
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellRendererAccelClass ENDS

;GType
gtk_cell_renderer_accel_get_type proto __cdecl
;GtkCellRenderer
gtk_cell_renderer_accel_new proto __cdecl

G_END_DECLS

endif
