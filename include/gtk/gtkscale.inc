ifndef __GTK_SCALE_H__
__GTK_SCALE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkrange.inc

G_BEGIN_DECLS

GTK_TYPE_SCALE equ <gtk_scale_get_type>
GTK_SCALE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCALE, GtkScale))>
	endm
GTK_SCALE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SCALE, GtkScaleClass))>
	endm
GTK_IS_SCALE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCALE))>
	endm
GTK_IS_SCALE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SCALE))>
	endm
GTK_SCALE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SCALE, GtkScaleClass))>
	endm

GtkScale		STRUC
range			GtkRange <>
priv			ptr_t ?
GtkScale		ENDS

GtkScaleClass		STRUC
parent_class		GtkRangeClass <>
format_value		proc :ptr GtkScale, :gdouble
draw_value		proc :ptr GtkScale
get_layout_offsets	proc :ptr GtkScale, :ptr gint, :ptr gint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkScaleClass		ENDS

;GType
gtk_scale_get_type proto __cdecl
;GtkWidget
gtk_scale_new proto __cdecl \
	   orientation: GtkOrientation,
	    adjustment: ptr GtkAdjustment

;GtkWidget
gtk_scale_new_with_range proto __cdecl \
	   orientation: GtkOrientation,
		   min: gdouble,
		   max: gdouble,
		  step: gdouble

;void
gtk_scale_set_digits proto __cdecl \
		 scale: ptr GtkScale,
		digits: gint

;gint
gtk_scale_get_digits proto __cdecl \
		 scale: ptr GtkScale

;void
gtk_scale_set_draw_value proto __cdecl \
		 scale: ptr GtkScale,
	    draw_value: gboolean

;gboolean
gtk_scale_get_draw_value proto __cdecl \
		 scale: ptr GtkScale

;void
gtk_scale_set_has_origin proto __cdecl \
		 scale: ptr GtkScale,
	    has_origin: gboolean

;gboolean
gtk_scale_get_has_origin proto __cdecl \
		 scale: ptr GtkScale

;void
gtk_scale_set_value_pos proto __cdecl \
		 scale: ptr GtkScale,
		   pos: GtkPositionType

;GtkPositionType
gtk_scale_get_value_pos proto __cdecl \
		 scale: ptr GtkScale

;PangoLayout
gtk_scale_get_layout proto __cdecl \
		 scale: ptr GtkScale

;void
gtk_scale_get_layout_offsets proto __cdecl \
		 scale: ptr GtkScale,
		     x: ptr gint,
		     y: ptr gint

;void
gtk_scale_add_mark proto __cdecl \
		 scale: ptr GtkScale,
		 value: gdouble,
	      position: GtkPositionType,
		markup: ptr gchar

;void
gtk_scale_clear_marks proto __cdecl \
		 scale: ptr GtkScale

G_END_DECLS

endif
