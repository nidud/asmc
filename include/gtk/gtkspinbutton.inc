ifndef __GTK_SPIN_BUTTON_H__
__GTK_SPIN_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkentry.inc

G_BEGIN_DECLS

GTK_TYPE_SPIN_BUTTON equ <gtk_spin_button_get_type>
GTK_SPIN_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SPIN_BUTTON, GtkSpinButton))>
	endm
GTK_SPIN_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SPIN_BUTTON, GtkSpinButtonClass))>
	endm
GTK_IS_SPIN_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SPIN_BUTTON))>
	endm
GTK_IS_SPIN_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SPIN_BUTTON))>
	endm
GTK_SPIN_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SPIN_BUTTON, GtkSpinButtonClass))>
	endm

GTK_INPUT_ERROR		equ -1

.enum GtkSpinButtonUpdatePolicy {
  GTK_UPDATE_ALWAYS,
  GTK_UPDATE_IF_VALID
}

.enum GtkSpinType {
  GTK_SPIN_STEP_FORWARD,
  GTK_SPIN_STEP_BACKWARD,
  GTK_SPIN_PAGE_FORWARD,
  GTK_SPIN_PAGE_BACKWARD,
  GTK_SPIN_HOME,
  GTK_SPIN_END,
  GTK_SPIN_USER_DEFINED
}


GtkSpinButton		STRUC
entry			GtkEntry <>
priv			ptr_t ?
GtkSpinButton		ENDS

GtkSpinButtonClass	STRUC
parent_class		GtkEntryClass <>
input			proc :ptr GtkSpinButton, :ptr gdouble
output			proc :ptr GtkSpinButton
value_changed		proc :ptr GtkSpinButton
change_value		proc :ptr GtkSpinButton, :GtkScrollType
wrapped			proc :ptr GtkSpinButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSpinButtonClass	ENDS


;GType
gtk_spin_button_get_type proto __cdecl

;void
gtk_spin_button_configure proto __cdecl \
	   spin_button: ptr GtkSpinButton,
	    adjustment: ptr GtkAdjustment,
	    climb_rate: gdouble,
		digits: guint


;GtkWidget*
gtk_spin_button_new proto __cdecl \
	    adjustment: ptr GtkAdjustment,
	    climb_rate: gdouble,
		digits: guint


;GtkWidget*
gtk_spin_button_new_with_range proto __cdecl \
		   min: gdouble,
		   max: gdouble,
		  step: gdouble


;void
gtk_spin_button_set_adjustment proto __cdecl \
	   spin_button: ptr GtkSpinButton,
	    adjustment: ptr GtkAdjustment


;GtkAdjustment*
gtk_spin_button_get_adjustment proto __cdecl \
	   spin_button: ptr GtkSpinButton


;void
gtk_spin_button_set_digits proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		digits: guint

;guint
gtk_spin_button_get_digits proto __cdecl \
	   spin_button: ptr GtkSpinButton


;void
gtk_spin_button_set_increments proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		  step: gdouble,
		  page: gdouble

;void
gtk_spin_button_get_increments proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		  step: ptr gdouble,
		  page: ptr gdouble


;void
gtk_spin_button_set_range proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		   min: gdouble,
		   max: gdouble

;void
gtk_spin_button_get_range proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		   min: ptr gdouble,
		   max: ptr gdouble


;gdouble
gtk_spin_button_get_value proto __cdecl \
	   spin_button: ptr GtkSpinButton


;gint
gtk_spin_button_get_value_as_int proto __cdecl \
	   spin_button: ptr GtkSpinButton


;void
gtk_spin_button_set_value proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		 value: gdouble


;void
gtk_spin_button_set_update_policy proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		policy: GtkSpinButtonUpdatePolicy

;GtkSpinButtonUpdatePolicy
gtk_spin_button_get_update_policy proto __cdecl \
	   spin_button: ptr GtkSpinButton


;void
gtk_spin_button_set_numeric proto __cdecl \
	   spin_button: ptr GtkSpinButton,
	       numeric: gboolean

;gboolean
gtk_spin_button_get_numeric proto __cdecl \
	   spin_button: ptr GtkSpinButton


;void
gtk_spin_button_spin proto __cdecl \
	   spin_button: ptr GtkSpinButton,
	     direction: GtkSpinType,
	     increment: gdouble


;void
gtk_spin_button_set_wrap proto __cdecl \
	   spin_button: ptr GtkSpinButton,
		  wrap: gboolean

;gboolean
gtk_spin_button_get_wrap proto __cdecl \
	   spin_button: ptr GtkSpinButton


;void
gtk_spin_button_set_snap_to_ticks proto __cdecl \
	   spin_button: ptr GtkSpinButton,
	 snap_to_ticks: gboolean

;gboolean
gtk_spin_button_get_snap_to_ticks proto __cdecl \
	   spin_button: ptr GtkSpinButton

;void
gtk_spin_button_update proto __cdecl \
	   spin_button: ptr GtkSpinButton


;void
_gtk_spin_button_get_panels proto __cdecl \
	   spin_button: ptr GtkSpinButton,
	    down_panel: ptr GdkWindow,
	      up_panel: ptr GdkWindow


G_END_DECLS

endif
