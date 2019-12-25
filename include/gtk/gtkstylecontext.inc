ifndef __GTK_STYLE_CONTEXT_H__
__GTK_STYLE_CONTEXT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkborder.inc
include gtk/gtkcsssection.inc
include gtk/gtkstyleprovider.inc
include gtk/gtktypes.inc
;include atk/atk.inc

G_BEGIN_DECLS

GTK_TYPE_STYLE_CONTEXT equ <gtk_style_context_get_type>
GTK_STYLE_CONTEXT macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_STYLE_CONTEXT, GtkStyleContext))>
	endm
GTK_STYLE_CONTEXT_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_CAST	  ((c), GTK_TYPE_STYLE_CONTEXT, GtkStyleContextClass))>
	endm
GTK_IS_STYLE_CONTEXT macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_STYLE_CONTEXT))>
	endm
GTK_IS_STYLE_CONTEXT_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_TYPE	  ((c), GTK_TYPE_STYLE_CONTEXT))>
	endm
GTK_STYLE_CONTEXT_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS  ((o), GTK_TYPE_STYLE_CONTEXT, GtkStyleContextClass))>
	endm

GtkStyleContext		STRUC
parent_object		GObject <>
priv			ptr_t ?
GtkStyleContext		ENDS

GtkStyleContextClass	STRUC
parent_class		GObjectClass <>
changed			proc :ptr GtkStyleContext
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkStyleContextClass	ENDS


GTK_STYLE_PROPERTY_BACKGROUND_COLOR equ <"background-color">
GTK_STYLE_PROPERTY_COLOR equ <"color">
GTK_STYLE_PROPERTY_FONT equ <"font">
GTK_STYLE_PROPERTY_PADDING equ <"padding">
GTK_STYLE_PROPERTY_BORDER_WIDTH equ <"border-width">
GTK_STYLE_PROPERTY_MARGIN equ <"margin">
GTK_STYLE_PROPERTY_BORDER_RADIUS equ <"border-radius">
GTK_STYLE_PROPERTY_BORDER_STYLE equ <"border-style">
GTK_STYLE_PROPERTY_BORDER_COLOR equ <"border-color">
GTK_STYLE_PROPERTY_BACKGROUND_IMAGE equ <"background-image">

GTK_STYLE_CLASS_CELL	equ <"cell">
GTK_STYLE_CLASS_DIM_LABEL equ <"dim-label">
GTK_STYLE_CLASS_ENTRY	equ <"entry">
GTK_STYLE_CLASS_LABEL	equ <"label">
GTK_STYLE_CLASS_COMBOBOX_ENTRY equ <"combobox-entry">
GTK_STYLE_CLASS_BUTTON	equ <"button">
GTK_STYLE_CLASS_LIST	equ <"list">
GTK_STYLE_CLASS_LIST_ROW equ <"list-row">
GTK_STYLE_CLASS_CALENDAR equ <"calendar">
GTK_STYLE_CLASS_SLIDER	equ <"slider">
GTK_STYLE_CLASS_BACKGROUND equ <"background">
GTK_STYLE_CLASS_RUBBERBAND equ <"rubberband">
GTK_STYLE_CLASS_CSD	equ <"csd">
GTK_STYLE_CLASS_TOOLTIP equ <"tooltip">
GTK_STYLE_CLASS_MENU	equ <"menu">
GTK_STYLE_CLASS_CONTEXT_MENU equ <"context-menu">
GTK_STYLE_CLASS_TOUCH_SELECTION equ <"touch-selection">
GTK_STYLE_CLASS_MENUBAR equ <"menubar">
GTK_STYLE_CLASS_MENUITEM equ <"menuitem">
GTK_STYLE_CLASS_TOOLBAR equ <"toolbar">
GTK_STYLE_CLASS_PRIMARY_TOOLBAR equ <"primary-toolbar">
GTK_STYLE_CLASS_INLINE_TOOLBAR equ <"inline-toolbar">
GTK_STYLE_CLASS_STATUSBAR equ <"statusbar">
GTK_STYLE_CLASS_RADIO	equ <"radio">
GTK_STYLE_CLASS_CHECK	equ <"check">
GTK_STYLE_CLASS_DEFAULT equ <"default">
GTK_STYLE_CLASS_TROUGH	equ <"trough">
GTK_STYLE_CLASS_SCROLLBAR equ <"scrollbar">
GTK_STYLE_CLASS_SCROLLBARS_JUNCTION equ <"scrollbars-junction">
GTK_STYLE_CLASS_SCALE	equ <"scale">
GTK_STYLE_CLASS_SCALE_HAS_MARKS_ABOVE equ <"scale-has-marks-above">
GTK_STYLE_CLASS_SCALE_HAS_MARKS_BELOW equ <"scale-has-marks-below">
GTK_STYLE_CLASS_HEADER	equ <"header">
GTK_STYLE_CLASS_ACCELERATOR equ <"accelerator">
GTK_STYLE_CLASS_RAISED	equ <"raised">
GTK_STYLE_CLASS_LINKED	equ <"linked">
GTK_STYLE_CLASS_GRIP	equ <"grip">
GTK_STYLE_CLASS_DOCK	equ <"dock">
GTK_STYLE_CLASS_PROGRESSBAR equ <"progressbar">
GTK_STYLE_CLASS_SPINNER equ <"spinner">
GTK_STYLE_CLASS_MARK	equ <"mark">
GTK_STYLE_CLASS_EXPANDER equ <"expander">
GTK_STYLE_CLASS_SPINBUTTON equ <"spinbutton">
GTK_STYLE_CLASS_NOTEBOOK equ <"notebook">
GTK_STYLE_CLASS_VIEW	equ <"view">
GTK_STYLE_CLASS_SIDEBAR equ <"sidebar">
GTK_STYLE_CLASS_IMAGE	equ <"image">
GTK_STYLE_CLASS_HIGHLIGHT equ <"highlight">
GTK_STYLE_CLASS_FRAME	equ <"frame">
GTK_STYLE_CLASS_DND	equ <"dnd">
GTK_STYLE_CLASS_PANE_SEPARATOR equ <"pane-separator">
GTK_STYLE_CLASS_SEPARATOR equ <"separator">
GTK_STYLE_CLASS_INFO	equ <"info">
GTK_STYLE_CLASS_WARNING equ <"warning">
GTK_STYLE_CLASS_QUESTION equ <"question">
GTK_STYLE_CLASS_ERROR	equ <"error">
GTK_STYLE_CLASS_HORIZONTAL equ <"horizontal">
GTK_STYLE_CLASS_VERTICAL equ <"vertical">
GTK_STYLE_CLASS_TOP	equ <"top">
GTK_STYLE_CLASS_BOTTOM	equ <"bottom">
GTK_STYLE_CLASS_LEFT	equ <"left">
GTK_STYLE_CLASS_RIGHT	equ <"right">
GTK_STYLE_CLASS_PULSE	equ <"pulse">
GTK_STYLE_CLASS_ARROW	equ <"arrow">
GTK_STYLE_CLASS_OSD	equ <"osd">
GTK_STYLE_CLASS_LEVEL_BAR equ <"level-bar">
GTK_STYLE_CLASS_CURSOR_HANDLE equ <"cursor-handle">
GTK_STYLE_CLASS_INSERTION_CURSOR equ <"insertion-cursor">
GTK_STYLE_CLASS_TITLEBAR equ <"titlebar">
GTK_STYLE_CLASS_TITLE	equ <"title">
GTK_STYLE_CLASS_SUBTITLE equ <"subtitle">
GTK_STYLE_CLASS_NEEDS_ATTENTION equ <"needs-attention">
GTK_STYLE_CLASS_SUGGESTED_ACTION equ <"suggested-action">
GTK_STYLE_CLASS_DESTRUCTIVE_ACTION equ <"destructive-action">
GTK_STYLE_CLASS_POPOVER equ <"popover">

GTK_STYLE_CLASS_POPUP	equ <"popup">
GTK_STYLE_CLASS_MESSAGE_DIALOG equ <"message-dialog">
GTK_STYLE_CLASS_FLAT	equ <"flat">
GTK_STYLE_CLASS_READ_ONLY equ <"read-only">
GTK_STYLE_CLASS_OVERSHOOT equ <"overshoot">
GTK_STYLE_CLASS_UNDERSHOOT equ <"undershoot">
GTK_STYLE_CLASS_PAPER	equ <"paper">
GTK_STYLE_CLASS_MONOSPACE equ <"monospace">
GTK_STYLE_CLASS_WIDE	equ <"wide">
GTK_STYLE_REGION_ROW	equ <"row">
GTK_STYLE_REGION_COLUMN equ <"column">
GTK_STYLE_REGION_COLUMN_HEADER equ <"column-header">
GTK_STYLE_REGION_TAB	equ <"tab">

;GType
gtk_style_context_get_type proto __cdecl

;GtkStyleContext
gtk_style_context_new proto __cdecl

;void
gtk_style_context_add_provider_for_screen proto __cdecl \
		screen: ptr GdkScreen,
	      provider: ptr GtkStyleProvider,
	      priority: guint

;void
gtk_style_context_remove_provider_for_screen proto __cdecl \
		screen: ptr GdkScreen,
	      provider: ptr GtkStyleProvider


;void
gtk_style_context_add_provider proto __cdecl \
	       context: ptr GtkStyleContext,
	      provider: ptr GtkStyleProvider,
	      priority: guint


;void
gtk_style_context_remove_provider proto __cdecl \
	       context: ptr GtkStyleContext,
	      provider: ptr GtkStyleProvider


;void
gtk_style_context_save proto __cdecl \
	       context: ptr GtkStyleContext

;void
gtk_style_context_restore proto __cdecl \
	       context: ptr GtkStyleContext


;GtkCssSection
gtk_style_context_get_section proto __cdecl \
	       context: ptr GtkStyleContext,
	      property: ptr gchar

;void
gtk_style_context_get_property proto __cdecl \
	       context: ptr GtkStyleContext,
	      property: ptr gchar,
		 state: GtkStateFlags,
		 value: ptr GValue

;void
gtk_style_context_get_valist proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
		  args: va_list

;void
gtk_style_context_get proto _CDecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
		      : vararg

;void
gtk_style_context_set_state proto __cdecl \
	       context: ptr GtkStyleContext,
		 flags: GtkStateFlags

;GtkStateFlags
gtk_style_context_get_state proto __cdecl \
	       context: ptr GtkStyleContext


;void
gtk_style_context_set_scale proto __cdecl \
	       context: ptr GtkStyleContext,
		 scale: gint

;gint
gtk_style_context_get_scale proto __cdecl \
	       context: ptr GtkStyleContext


;gboolean
gtk_style_context_state_is_running proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateType,
	      progress: ptr gdouble


;void
gtk_style_context_set_path proto __cdecl \
	       context: ptr GtkStyleContext,
		  path: ptr GtkWidgetPath

;const
gtk_style_context_get_path proto __cdecl \
	       context: ptr GtkStyleContext

;void
gtk_style_context_set_parent proto __cdecl \
	       context: ptr GtkStyleContext,
		parent: ptr GtkStyleContext

;GtkStyleContext
gtk_style_context_get_parent proto __cdecl \
	       context: ptr GtkStyleContext


;GList
gtk_style_context_list_classes proto __cdecl \
	       context: ptr GtkStyleContext


;void
gtk_style_context_add_class proto __cdecl \
	       context: ptr GtkStyleContext,
	    class_name: ptr gchar

;void
gtk_style_context_remove_class proto __cdecl \
	       context: ptr GtkStyleContext,
	    class_name: ptr gchar

;gboolean
gtk_style_context_has_class proto __cdecl \
	       context: ptr GtkStyleContext,
	    class_name: ptr gchar


;GList
gtk_style_context_list_regions proto __cdecl \
	       context: ptr GtkStyleContext


;void
gtk_style_context_add_region proto __cdecl \
	       context: ptr GtkStyleContext,
	   region_name: ptr gchar,
		 flags: GtkRegionFlags

;void
gtk_style_context_remove_region proto __cdecl \
	       context: ptr GtkStyleContext,
	   region_name: ptr gchar

;gboolean
gtk_style_context_has_region proto __cdecl \
	       context: ptr GtkStyleContext,
	   region_name: ptr gchar,
	  flags_return: ptr GtkRegionFlags


;void
gtk_style_context_get_style_property proto __cdecl \
	       context: ptr GtkStyleContext,
	 property_name: ptr gchar,
		 value: ptr GValue

;void
gtk_style_context_get_style_valist proto __cdecl \
	       context: ptr GtkStyleContext,
		  args: va_list

;void
gtk_style_context_get_style proto _CDecl \
	       context: ptr GtkStyleContext,
		      : vararg


;GtkIconSet
gtk_style_context_lookup_icon_set proto __cdecl \
	       context: ptr GtkStyleContext,
	      stock_id: ptr gchar

;GdkPixbuf
gtk_icon_set_render_icon_pixbuf proto __cdecl \
	      icon_set: ptr GtkIconSet,
	       context: ptr GtkStyleContext,
		  size: GtkIconSize

;cairo_surface_t
gtk_icon_set_render_icon_surface proto __cdecl \
	      icon_set: ptr GtkIconSet,
	       context: ptr GtkStyleContext,
		  size: GtkIconSize,
		 scale: int_t,
	    for_window: ptr GdkWindow


;void
gtk_style_context_set_screen proto __cdecl \
	       context: ptr GtkStyleContext,
		screen: ptr GdkScreen

;GdkScreen
gtk_style_context_get_screen proto __cdecl \
	       context: ptr GtkStyleContext


;void
gtk_style_context_set_frame_clock proto __cdecl \
	       context: ptr GtkStyleContext,
	   frame_clock: ptr GdkFrameClock

;GdkFrameClock
gtk_style_context_get_frame_clock proto __cdecl \
	       context: ptr GtkStyleContext


;void
gtk_style_context_set_direction proto __cdecl \
	       context: ptr GtkStyleContext,
	     direction: GtkTextDirection

;GtkTextDirection
gtk_style_context_get_direction proto __cdecl \
	       context: ptr GtkStyleContext


;void
gtk_style_context_set_junction_sides proto __cdecl \
	       context: ptr GtkStyleContext,
		 sides: GtkJunctionSides

;GtkJunctionSides
gtk_style_context_get_junction_sides proto __cdecl \
	       context: ptr GtkStyleContext


;gboolean
gtk_style_context_lookup_color proto __cdecl \
	       context: ptr GtkStyleContext,
	    color_name: ptr gchar,
		 color: ptr GdkRGBA


;void
gtk_style_context_notify_state_change proto __cdecl \
	       context: ptr GtkStyleContext,
		window: ptr GdkWindow,
	     region_id: gpointer,
		 state: GtkStateType,
	   state_value: gboolean

;void
gtk_style_context_cancel_animations proto __cdecl \
	       context: ptr GtkStyleContext,
	     region_id: gpointer

;void
gtk_style_context_scroll_animations proto __cdecl \
	       context: ptr GtkStyleContext,
		window: ptr GdkWindow,
		   _dx: gint,
		    dy: gint


;void
gtk_style_context_push_animatable_region proto __cdecl \
	       context: ptr GtkStyleContext,
	     region_id: gpointer

;void
gtk_style_context_pop_animatable_region proto __cdecl \
	       context: ptr GtkStyleContext


;void
gtk_style_context_get_color proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
		 color: ptr GdkRGBA

;void
gtk_style_context_get_background_color proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
		 color: ptr GdkRGBA

;void
gtk_style_context_get_border_color proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
		 color: ptr GdkRGBA


;const
gtk_style_context_get_font proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags

;void
gtk_style_context_get_border proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
		border: ptr GtkBorder

;void
gtk_style_context_get_padding proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
	       padding: ptr GtkBorder

;void
gtk_style_context_get_margin proto __cdecl \
	       context: ptr GtkStyleContext,
		 state: GtkStateFlags,
		margin: ptr GtkBorder


;void
gtk_style_context_invalidate proto __cdecl \
	       context: ptr GtkStyleContext

;void
gtk_style_context_reset_widgets proto __cdecl \
		screen: ptr GdkScreen


;void
gtk_style_context_set_background proto __cdecl \
	       context: ptr GtkStyleContext,
		window: ptr GdkWindow


;void
gtk_render_insertion_cursor proto __cdecl \
	       context: ptr GtkStyleContext,
		    cr: ptr cairo_t,
		     x: gdouble,
		     y: gdouble,
		layout: ptr PangoLayout,
		 index: int_t,
	     direction: int_t;PangoDirection

;void
gtk_draw_insertion_cursor proto __cdecl \
		widget: ptr GtkWidget,
		    cr: ptr cairo_t,
	      location: ptr GdkRectangle,
	    is_primary: gboolean,
	     direction: GtkTextDirection,
	    draw_arrow: gboolean

G_END_DECLS

endif
