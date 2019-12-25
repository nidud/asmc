ifndef __GTK_PROGRESS_BAR_H__
__GTK_PROGRESS_BAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_PROGRESS_BAR equ <gtk_progress_bar_get_type>
GTK_PROGRESS_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PROGRESS_BAR, GtkProgressBar))>
	endm
GTK_PROGRESS_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_PROGRESS_BAR, GtkProgressBarClass))>
	endm
GTK_IS_PROGRESS_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PROGRESS_BAR))>
	endm
GTK_IS_PROGRESS_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_PROGRESS_BAR))>
	endm
GTK_PROGRESS_BAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_PROGRESS_BAR, GtkProgressBarClass))>
	endm

GtkProgressBar		STRUC
parent			GtkWidget <>
priv			ptr_t ?
GtkProgressBar		ENDS

GtkProgressBarClass	STRUC
parent_class		GtkWidgetClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkProgressBarClass	ENDS


;GType
gtk_progress_bar_get_type proto __cdecl
;GtkWidget*
gtk_progress_bar_new proto __cdecl

;void
gtk_progress_bar_pulse proto __cdecl \
		  pbar: ptr GtkProgressBar

;void
gtk_progress_bar_set_text proto __cdecl \
		  pbar: ptr GtkProgressBar,
		  text: ptr gchar

;void
gtk_progress_bar_set_fraction proto __cdecl \
		  pbar: ptr GtkProgressBar,
	      fraction: gdouble


;void
gtk_progress_bar_set_pulse_step proto __cdecl \
		  pbar: ptr GtkProgressBar,
	      fraction: gdouble

;void
gtk_progress_bar_set_inverted proto __cdecl \
		  pbar: ptr GtkProgressBar,
	      inverted: gboolean


;const
gtk_progress_bar_get_text proto __cdecl \
		  pbar: ptr GtkProgressBar

;gdouble
gtk_progress_bar_get_fraction proto __cdecl \
		  pbar: ptr GtkProgressBar

;gdouble
gtk_progress_bar_get_pulse_step proto __cdecl \
		  pbar: ptr GtkProgressBar


;gboolean
gtk_progress_bar_get_inverted proto __cdecl \
		  pbar: ptr GtkProgressBar

;void
gtk_progress_bar_set_ellipsize proto __cdecl \
		  pbar: ptr GtkProgressBar,
		  mode: int_t;PangoEllipsizeMode

;PangoEllipsizeMode
gtk_progress_bar_get_ellipsize proto __cdecl \
		  pbar: ptr GtkProgressBar


;void
gtk_progress_bar_set_show_text proto __cdecl \
		  pbar: ptr GtkProgressBar,
	     show_text: gboolean

;gboolean
gtk_progress_bar_get_show_text proto __cdecl \
		  pbar: ptr GtkProgressBar


G_END_DECLS

endif
