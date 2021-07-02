ifndef __GTK_LEVEL_BAR_H__
__GTK_LEVEL_BAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_LEVEL_BAR equ <gtk_level_bar_get_type>
GTK_LEVEL_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LEVEL_BAR, GtkLevelBar))>
	endm
GTK_LEVEL_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_LEVEL_BAR, GtkLevelBarClass))>
	endm
GTK_IS_LEVEL_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LEVEL_BAR))>
	endm
GTK_IS_LEVEL_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_LEVEL_BAR))>
	endm
GTK_LEVEL_BAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_LEVEL_BAR, GtkLevelBarClass))>
	endm

GTK_LEVEL_BAR_OFFSET_LOW equ <"low">
GTK_LEVEL_BAR_OFFSET_HIGH equ <"high">

GtkLevelBar		STRUC
parent			GtkWidget <>
priv			ptr_t ?
GtkLevelBar		ENDS

GtkLevelBarClass	STRUC
parent_class		GtkWidgetClass <>
offset_changed		proc :ptr GtkLevelBar, :ptr gchar
padding			gpointer 16 dup(?)
GtkLevelBarClass	ENDS

;GType
gtk_level_bar_get_type proto __cdecl

;GtkWidget
gtk_level_bar_new proto __cdecl

;GtkWidget
gtk_level_bar_new_for_interval proto __cdecl \
	     min_value: gdouble,
	     max_value: gdouble


;void
gtk_level_bar_set_mode proto __cdecl \
		  self: ptr GtkLevelBar,
		  mode: GtkLevelBarMode

;GtkLevelBarMode
gtk_level_bar_get_mode proto __cdecl \
		  self: ptr GtkLevelBar


;void
gtk_level_bar_set_value proto __cdecl \
		  self: ptr GtkLevelBar,
		 value: gdouble

;gdouble
gtk_level_bar_get_value proto __cdecl \
		  self: ptr GtkLevelBar


;void
gtk_level_bar_set_min_value proto __cdecl \
		  self: ptr GtkLevelBar,
		 value: gdouble

;gdouble
gtk_level_bar_get_min_value proto __cdecl \
		  self: ptr GtkLevelBar


;void
gtk_level_bar_set_max_value proto __cdecl \
		  self: ptr GtkLevelBar,
		 value: gdouble

;gdouble
gtk_level_bar_get_max_value proto __cdecl \
		  self: ptr GtkLevelBar


;void
gtk_level_bar_set_inverted proto __cdecl \
		  self: ptr GtkLevelBar,
	      inverted: gboolean


;gboolean
gtk_level_bar_get_inverted proto __cdecl \
		  self: ptr GtkLevelBar


;void
gtk_level_bar_add_offset_value proto __cdecl \
		  self: ptr GtkLevelBar,
		  name: ptr gchar,
		 value: gdouble

;void
gtk_level_bar_remove_offset_value proto __cdecl \
		  self: ptr GtkLevelBar,
		  name: ptr gchar

;gboolean
gtk_level_bar_get_offset_value proto __cdecl \
		  self: ptr GtkLevelBar,
		  name: ptr gchar,
		 value: ptr gdouble

G_END_DECLS

endif
