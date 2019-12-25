ifndef __GTK_SCROLLED_WINDOW_H__
__GTK_SCROLLED_WINDOW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_SCROLLED_WINDOW equ <gtk_scrolled_window_get_type>
GTK_SCROLLED_WINDOW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCROLLED_WINDOW, GtkScrolledWindow))>
	endm
GTK_SCROLLED_WINDOW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SCROLLED_WINDOW, GtkScrolledWindowClass))>
	endm
GTK_IS_SCROLLED_WINDOW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCROLLED_WINDOW))>
	endm
GTK_IS_SCROLLED_WINDOW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SCROLLED_WINDOW))>
	endm
GTK_SCROLLED_WINDOW_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SCROLLED_WINDOW, GtkScrolledWindowClass))>
	endm


GtkScrolledWindow	STRUC
container		GtkBin <>
priv			ptr_t ?
GtkScrolledWindow	ENDS

GtkScrolledWindowClass	STRUC
parent_class		GtkBinClass <>
scrollbar_spacing	gint ?
scroll_child		proc :ptr GtkScrolledWindow, :GtkScrollType, :gboolean
move_focus_out		proc :ptr GtkScrolledWindow, :GtkDirectionType
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkScrolledWindowClass	ENDS


.enum GtkCornerType {
  GTK_CORNER_TOP_LEFT,
  GTK_CORNER_BOTTOM_LEFT,
  GTK_CORNER_TOP_RIGHT,
  GTK_CORNER_BOTTOM_RIGHT
}

.enum GtkPolicyType {
  GTK_POLICY_ALWAYS,
  GTK_POLICY_AUTOMATIC,
  GTK_POLICY_NEVER,
  GTK_POLICY_EXTERNAL
}

;GType
gtk_scrolled_window_get_type proto __cdecl
;GtkWidget*
gtk_scrolled_window_new proto __cdecl \
	   hadjustment: ptr GtkAdjustment,
	   vadjustment: ptr GtkAdjustment

;void
gtk_scrolled_window_set_hadjustment proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
	   hadjustment: ptr GtkAdjustment

;void
gtk_scrolled_window_set_vadjustment proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
	   vadjustment: ptr GtkAdjustment

;GtkAdjustment*
gtk_scrolled_window_get_hadjustment proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;GtkAdjustment*
gtk_scrolled_window_get_vadjustment proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;GtkWidget*
gtk_scrolled_window_get_hscrollbar proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;GtkWidget*
gtk_scrolled_window_get_vscrollbar proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;void
gtk_scrolled_window_set_policy proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
     hscrollbar_policy: GtkPolicyType,
     vscrollbar_policy: GtkPolicyType

;void
gtk_scrolled_window_get_policy proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
     hscrollbar_policy: ptr GtkPolicyType,
     vscrollbar_policy: ptr GtkPolicyType

;void
gtk_scrolled_window_set_placement proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
      window_placement: GtkCornerType

;void
gtk_scrolled_window_unset_placement proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow


;GtkCornerType
gtk_scrolled_window_get_placement proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;void
gtk_scrolled_window_set_shadow_type proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
		  type: GtkShadowType

;GtkShadowType
gtk_scrolled_window_get_shadow_type proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;void
gtk_scrolled_window_add_with_viewport proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
		 child: ptr GtkWidget


;gint
gtk_scrolled_window_get_min_content_width proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;void
gtk_scrolled_window_set_min_content_width proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
		 width: gint

;gint
gtk_scrolled_window_get_min_content_height proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

;void
gtk_scrolled_window_set_min_content_height proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
		height: gint

;void
gtk_scrolled_window_set_kinetic_scrolling proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
     kinetic_scrolling: gboolean

;gboolean
gtk_scrolled_window_get_kinetic_scrolling proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow


;void
gtk_scrolled_window_set_capture_button_press proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
  capture_button_press: gboolean

;gboolean
gtk_scrolled_window_get_capture_button_press proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow


;void
gtk_scrolled_window_set_overlay_scrolling proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow,
     overlay_scrolling: gboolean

;gboolean
gtk_scrolled_window_get_overlay_scrolling proto __cdecl \
       scrolled_window: ptr GtkScrolledWindow

G_END_DECLS

endif
