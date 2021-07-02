ifndef __GTK_RANGE_H__
__GTK_RANGE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_RANGE equ <gtk_range_get_type>
GTK_RANGE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RANGE, GtkRange))>
	endm
GTK_RANGE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RANGE, GtkRangeClass))>
	endm
GTK_IS_RANGE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RANGE))>
	endm
GTK_IS_RANGE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RANGE))>
	endm
GTK_RANGE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RANGE, GtkRangeClass))>
	endm

GtkRange		STRUC
widget			GtkWidget <>
priv			ptr_t ?
GtkRange		ENDS

GtkRangeClass		STRUC
parent_class		GtkWidgetClass <>
slider_detail		string_t ?
stepper_detail		string_t ?
value_changed		proc :ptr GtkRange
adjust_bounds		proc :ptr GtkRange, :gdouble
move_slider		proc :ptr GtkRange, :GtkScrollType
get_range_border	proc :ptr GtkRange, :ptr GtkBorder
change_value		proc :ptr GtkRange, :GtkScrollType, :gdouble
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkRangeClass		ENDS


;GType
gtk_range_get_type proto __cdecl

;void
gtk_range_set_adjustment proto __cdecl \
		 range: ptr GtkRange,
	    adjustment: ptr GtkAdjustment

;GtkAdjustment*
gtk_range_get_adjustment proto __cdecl \
		 range: ptr GtkRange


;void
gtk_range_set_inverted proto __cdecl \
		 range: ptr GtkRange,
	       setting: gboolean

;gboolean
gtk_range_get_inverted proto __cdecl \
		 range: ptr GtkRange


;void
gtk_range_set_flippable proto __cdecl \
		 range: ptr GtkRange,
	     flippable: gboolean

;gboolean
gtk_range_get_flippable proto __cdecl \
		 range: ptr GtkRange


;void
gtk_range_set_slider_size_fixed proto __cdecl \
		 range: ptr GtkRange,
	    size_fixed: gboolean

;gboolean
gtk_range_get_slider_size_fixed proto __cdecl \
		 range: ptr GtkRange


;void
gtk_range_set_min_slider_size proto __cdecl \
		 range: ptr GtkRange,
	      min_size: gint

;gint
gtk_range_get_min_slider_size proto __cdecl \
		 range: ptr GtkRange


;void
gtk_range_get_range_rect proto __cdecl \
		 range: ptr GtkRange,
	    range_rect: ptr GdkRectangle

;void
gtk_range_get_slider_range proto __cdecl \
		 range: ptr GtkRange,
	  slider_start: ptr gint,
	    slider_end: ptr gint


;void
gtk_range_set_lower_stepper_sensitivity proto __cdecl \
		 range: ptr GtkRange,
	   sensitivity: GtkSensitivityType

;GtkSensitivityType
gtk_range_get_lower_stepper_sensitivity proto __cdecl \
		 range: ptr GtkRange

;void
gtk_range_set_upper_stepper_sensitivity proto __cdecl \
		 range: ptr GtkRange,
	   sensitivity: GtkSensitivityType

;GtkSensitivityType
gtk_range_get_upper_stepper_sensitivity proto __cdecl \
		 range: ptr GtkRange


;void
gtk_range_set_increments proto __cdecl \
		 range: ptr GtkRange,
		  step: gdouble,
		  page: gdouble

;void
gtk_range_set_range proto __cdecl \
		 range: ptr GtkRange,
		   min: gdouble,
		   max: gdouble

;void
gtk_range_set_value proto __cdecl \
		 range: ptr GtkRange,
		 value: gdouble

;gdouble
gtk_range_get_value proto __cdecl \
		 range: ptr GtkRange


;void
gtk_range_set_show_fill_level proto __cdecl \
		 range: ptr GtkRange,
       show_fill_level: gboolean

;gboolean
gtk_range_get_show_fill_level proto __cdecl \
		 range: ptr GtkRange

;void
gtk_range_set_restrict_to_fill_level proto __cdecl \
		 range: ptr GtkRange,
restrict_to_fill_level: gboolean

;gboolean
gtk_range_get_restrict_to_fill_level proto __cdecl \
		 range: ptr GtkRange

;void
gtk_range_set_fill_level proto __cdecl \
		 range: ptr GtkRange,
	    fill_level: gdouble

;gdouble
gtk_range_get_fill_level proto __cdecl \
		 range: ptr GtkRange

;void
gtk_range_set_round_digits proto __cdecl \
		 range: ptr GtkRange,
	  round_digits: gint

;gint
gtk_range_get_round_digits proto __cdecl \
		 range: ptr GtkRange


G_END_DECLS

endif
