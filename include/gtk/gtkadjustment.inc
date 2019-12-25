ifndef __GTK_ADJUSTMENT_H__
__GTK_ADJUSTMENT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktypes.inc

G_BEGIN_DECLS

GTK_TYPE_ADJUSTMENT equ <gtk_adjustment_get_type>
GTK_ADJUSTMENT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ADJUSTMENT, GtkAdjustment))>
	endm
GTK_ADJUSTMENT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ADJUSTMENT, GtkAdjustmentClass))>
	endm
GTK_IS_ADJUSTMENT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ADJUSTMENT))>
	endm
GTK_IS_ADJUSTMENT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ADJUSTMENT))>
	endm
GTK_ADJUSTMENT_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ADJUSTMENT, GtkAdjustmentClass))>
	endm


GtkAdjustment		STRUC
parent_instance		GInitiallyUnowned <>
priv			ptr_t ?
GtkAdjustment		ENDS

GtkAdjustmentClass	STRUC
parent_class		GInitiallyUnownedClass <>
changed			proc :ptr GtkAdjustment
value_changed		proc :ptr GtkAdjustment
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkAdjustmentClass	ENDS


;GType
gtk_adjustment_get_type proto __cdecl
;GtkAdjustment*
gtk_adjustment_new proto __cdecl \
		 value: gdouble,
		 lower: gdouble,
		 upper: gdouble,
	step_increment: gdouble,
	page_increment: gdouble,
	     page_size: gdouble


;void
gtk_adjustment_changed proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_value_changed proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_clamp_page proto __cdecl \
	    adjustment: ptr GtkAdjustment,
		 lower: gdouble,
		 upper: gdouble


;gdouble
gtk_adjustment_get_value proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_set_value proto __cdecl \
	    adjustment: ptr GtkAdjustment,
		 value: gdouble

;gdouble
gtk_adjustment_get_lower proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_set_lower proto __cdecl \
	    adjustment: ptr GtkAdjustment,
		 lower: gdouble

;gdouble
gtk_adjustment_get_upper proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_set_upper proto __cdecl \
	    adjustment: ptr GtkAdjustment,
		 upper: gdouble

;gdouble
gtk_adjustment_get_step_increment proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_set_step_increment proto __cdecl \
	    adjustment: ptr GtkAdjustment,
	step_increment: gdouble

;gdouble
gtk_adjustment_get_page_increment proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_set_page_increment proto __cdecl \
	    adjustment: ptr GtkAdjustment,
	page_increment: gdouble

;gdouble
gtk_adjustment_get_page_size proto __cdecl \
	    adjustment: ptr GtkAdjustment

;void
gtk_adjustment_set_page_size proto __cdecl \
	    adjustment: ptr GtkAdjustment,
	     page_size: gdouble


;void
gtk_adjustment_configure proto __cdecl \
	    adjustment: ptr GtkAdjustment,
		 value: gdouble,
		 lower: gdouble,
		 upper: gdouble,
	step_increment: gdouble,
	page_increment: gdouble,
	     page_size: gdouble

;gdouble
gtk_adjustment_get_minimum_increment proto __cdecl \
	    adjustment: ptr GtkAdjustment

G_END_DECLS

endif
