ifndef __GTK_LABEL_H__
__GTK_LABEL_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/deprecated/gtkmisc.inc
include gtk/gtkwindow.inc
include gtk/gtkmenu.inc

ifndef PangoEllipsizeMode
PangoEllipsizeMode	typedef int_t
PangoWrapMode		typedef int_t
endif

G_BEGIN_DECLS

GTK_TYPE_LABEL equ <gtk_label_get_type>
GTK_LABEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LABEL, GtkLabel))>
	endm
GTK_LABEL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_LABEL, GtkLabelClass))>
	endm
GTK_IS_LABEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LABEL))>
	endm
GTK_IS_LABEL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_LABEL))>
	endm
GTK_LABEL_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_LABEL, GtkLabelClass))>
	endm


GtkLabel		STRUC
misc			GtkMisc <>
priv			ptr_t ?
GtkLabel		ENDS

GtkLabelClass		STRUC
parent_class		GtkMiscClass <>
move_cursor		proc :ptr GtkLabel, :GtkMovementStep, :gint, :gboolean
copy_clipboard		proc :ptr GtkLabel
populate_popup		proc :ptr GtkLabel, :ptr GtkMenu
activate_link		proc :ptr GtkLabel, :string_t
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkLabelClass		ENDS

;GType
gtk_label_get_type proto __cdecl
;GtkWidget*
gtk_label_new proto __cdecl \
		  _str: ptr gchar

;GtkWidget*
gtk_label_new_with_mnemonic proto __cdecl \
		  _str: ptr gchar

;void
gtk_label_set_text proto __cdecl \
		_label: ptr GtkLabel,
		  _str: ptr gchar

;const
gtk_label_get_text proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_attributes proto __cdecl \
		_label: ptr GtkLabel,
		 attrs: ptr PangoAttrList

;PangoAttrList
gtk_label_get_attributes proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_label proto __cdecl \
		_label: ptr GtkLabel,
		  _str: ptr gchar

;const
gtk_label_get_label proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_markup proto __cdecl \
		_label: ptr GtkLabel,
		  _str: ptr gchar

;void
gtk_label_set_use_markup proto __cdecl \
		_label: ptr GtkLabel,
	       setting: gboolean

;gboolean
gtk_label_get_use_markup proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_use_underline proto __cdecl \
		_label: ptr GtkLabel,
	       setting: gboolean

;gboolean
gtk_label_get_use_underline proto __cdecl \
		_label: ptr GtkLabel


;void
gtk_label_set_markup_with_mnemonic proto __cdecl \
		_label: ptr GtkLabel,
		  _str: ptr gchar

;guint
gtk_label_get_mnemonic_keyval proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_mnemonic_widget proto __cdecl \
		_label: ptr GtkLabel,
		widget: ptr GtkWidget

;GtkWidget
gtk_label_get_mnemonic_widget proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_text_with_mnemonic proto __cdecl \
		_label: ptr GtkLabel,
		  _str: ptr gchar

;void
gtk_label_set_justify proto __cdecl \
		_label: ptr GtkLabel,
		 jtype: GtkJustification

;GtkJustification
gtk_label_get_justify proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_ellipsize proto __cdecl \
		_label: ptr GtkLabel,
		  mode: PangoEllipsizeMode

;PangoEllipsizeMode
gtk_label_get_ellipsize proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_width_chars proto __cdecl \
		_label: ptr GtkLabel,
	       n_chars: gint

;gint
gtk_label_get_width_chars proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_max_width_chars proto __cdecl \
		_label: ptr GtkLabel,
	       n_chars: gint

;gint
gtk_label_get_max_width_chars proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_lines proto __cdecl \
		_label: ptr GtkLabel,
		 lines: gint

;gint
gtk_label_get_lines proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_pattern proto __cdecl \
		_label: ptr GtkLabel,
	       pattern: ptr gchar

;void
gtk_label_set_line_wrap proto __cdecl \
		_label: ptr GtkLabel,
		  wrap: gboolean

;gboolean
gtk_label_get_line_wrap proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_line_wrap_mode proto __cdecl \
		_label: ptr GtkLabel,
	     wrap_mode: PangoWrapMode

;PangoWrapMode
gtk_label_get_line_wrap_mode proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_selectable proto __cdecl \
		_label: ptr GtkLabel,
	       setting: gboolean

;gboolean
gtk_label_get_selectable proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_angle proto __cdecl \
		_label: ptr GtkLabel,
		 angle: gdouble

;gdouble
gtk_label_get_angle proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_select_region proto __cdecl \
		_label: ptr GtkLabel,
	  start_offset: gint,
	    end_offset: gint

;gboolean
gtk_label_get_selection_bounds proto __cdecl \
		_label: ptr GtkLabel,
		 start: ptr gint,
		  _end: ptr gint


;PangoLayout
gtk_label_get_layout proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_get_layout_offsets proto __cdecl \
		_label: ptr GtkLabel,
		     x: ptr gint,
		     y: ptr gint


;void
gtk_label_set_single_line_mode proto __cdecl \
		_label: ptr GtkLabel,
      single_line_mode: gboolean

;gboolean
gtk_label_get_single_line_mode proto __cdecl \
		_label: ptr GtkLabel


;const
gtk_label_get_current_uri proto __cdecl \
		_label: ptr GtkLabel

;void
gtk_label_set_track_visited_links proto __cdecl \
		_label: ptr GtkLabel,
	   track_links: gboolean

;gboolean
gtk_label_get_track_visited_links proto __cdecl \
		_label: ptr GtkLabel


;void
gtk_label_set_xalign proto __cdecl \
		_label: ptr GtkLabel,
		xalign: gfloat


;gfloat
gtk_label_get_xalign proto __cdecl \
		_label: ptr GtkLabel


;void
gtk_label_set_yalign proto __cdecl \
		_label: ptr GtkLabel,
		yalign: gfloat


;gfloat
gtk_label_get_yalign proto __cdecl \
		_label: ptr GtkLabel


G_END_DECLS

endif
