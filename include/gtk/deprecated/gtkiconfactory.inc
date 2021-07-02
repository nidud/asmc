ifndef __GTK_ICON_FACTORY_H__
__GTK_ICON_FACTORY_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc
include gtk/gtktypes.inc

G_BEGIN_DECLS

GTK_TYPE_ICON_FACTORY equ <gtk_icon_factory_get_type>
GTK_ICON_FACTORY macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_ICON_FACTORY, GtkIconFactory))>
	endm
GTK_ICON_FACTORY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ICON_FACTORY, GtkIconFactoryClass))>
	endm
GTK_IS_ICON_FACTORY macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_ICON_FACTORY))>
	endm
GTK_IS_ICON_FACTORY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ICON_FACTORY))>
	endm
GTK_ICON_FACTORY_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ICON_FACTORY, GtkIconFactoryClass))>
	endm
GTK_TYPE_ICON_SET	equ <gtk_icon_set_get_type>
GTK_TYPE_ICON_SOURCE	equ <gtk_icon_source_get_type>

GtkIconFactory		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkIconFactory		ENDS

GtkIconFactoryClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkIconFactoryClass	ENDS

;GType
gtk_icon_factory_get_type proto __cdecl
;GtkIconFactory*
gtk_icon_factory_new proto __cdecl
;void
gtk_icon_factory_add proto __cdecl \
	       factory: ptr GtkIconFactory,
	      stock_id: ptr gchar,
	      icon_set: ptr GtkIconSet

;GtkIconSet*
gtk_icon_factory_lookup proto __cdecl \
	       factory: ptr GtkIconFactory,
	      stock_id: ptr gchar


;; Manage the default icon factory stack

;void
gtk_icon_factory_add_default proto __cdecl \
	       factory: ptr GtkIconFactory

;void
gtk_icon_factory_remove_default proto __cdecl \
	       factory: ptr GtkIconFactory

;GtkIconSet*
gtk_icon_factory_lookup_default proto __cdecl \
	      stock_id: ptr gchar


ifndef GDK_MULTIHEAD_SAFE
;gboolean
gtk_icon_size_lookup proto __cdecl \
		  size: GtkIconSize,
		 width: ptr gint,
		height: ptr gint

endif ;; GDK_MULTIHEAD_SAFE
;gboolean
gtk_icon_size_lookup_for_settings proto __cdecl \
	      settings: ptr GtkSettings,
		  size: GtkIconSize,
		 width: ptr gint,
		height: ptr gint


;GtkIconSize
gtk_icon_size_register proto __cdecl \
		  name: ptr gchar,
		 width: gint,
		height: gint

;void
gtk_icon_size_register_alias proto __cdecl \
		_alias: ptr gchar,
		target: GtkIconSize

;GtkIconSize
gtk_icon_size_from_name proto __cdecl \
		  name: ptr gchar

;const
gtk_icon_size_get_name proto __cdecl \
		  size: GtkIconSize


;; Icon sets

;GType
gtk_icon_set_get_type proto __cdecl
;GtkIconSet*
gtk_icon_set_new proto __cdecl
;GtkIconSet*
gtk_icon_set_new_from_pixbuf proto __cdecl \
		pixbuf: ptr GdkPixbuf


;GtkIconSet*
gtk_icon_set_ref proto __cdecl \
	      icon_set: ptr GtkIconSet

;void
gtk_icon_set_unref proto __cdecl \
	      icon_set: ptr GtkIconSet

;GtkIconSet*
gtk_icon_set_copy proto __cdecl \
	      icon_set: ptr GtkIconSet


;GdkPixbuf*
gtk_icon_set_render_icon proto __cdecl \
	      icon_set: ptr GtkIconSet,
		 style: ptr GtkStyle,
	     direction: GtkTextDirection,
		 state: GtkStateType,
		  size: GtkIconSize,
		widget: ptr GtkWidget,
		detail: ptr gchar


;void
gtk_icon_set_add_source proto __cdecl \
	      icon_set: ptr GtkIconSet,
		source: ptr GtkIconSource


;void
gtk_icon_set_get_sizes proto __cdecl \
	      icon_set: ptr GtkIconSet,
		 sizes: ptr GtkIconSize,
	       n_sizes: ptr gint


;GType
gtk_icon_source_get_type proto __cdecl
;GtkIconSource*
gtk_icon_source_new proto __cdecl
;GtkIconSource*
gtk_icon_source_copy proto __cdecl \
		source: ptr GtkIconSource

;void
gtk_icon_source_free proto __cdecl \
		source: ptr GtkIconSource


;void
gtk_icon_source_set_filename proto __cdecl \
		source: ptr GtkIconSource,
	      filename: ptr gchar

;void
gtk_icon_source_set_icon_name proto __cdecl \
		source: ptr GtkIconSource,
	     icon_name: ptr gchar

;void
gtk_icon_source_set_pixbuf proto __cdecl \
		source: ptr GtkIconSource,
		pixbuf: ptr GdkPixbuf


;const
gtk_icon_source_get_filename proto __cdecl \
		source: ptr GtkIconSource

;const
gtk_icon_source_get_icon_name proto __cdecl \
		source: ptr GtkIconSource

;GdkPixbuf*
gtk_icon_source_get_pixbuf proto __cdecl \
		source: ptr GtkIconSource


;void
gtk_icon_source_set_direction_wildcarded proto __cdecl \
		source: ptr GtkIconSource,
	       setting: gboolean

;void
gtk_icon_source_set_state_wildcarded proto __cdecl \
		source: ptr GtkIconSource,
	       setting: gboolean

;void
gtk_icon_source_set_size_wildcarded proto __cdecl \
		source: ptr GtkIconSource,
	       setting: gboolean

;gboolean
gtk_icon_source_get_size_wildcarded proto __cdecl \
		source: ptr GtkIconSource

;gboolean
gtk_icon_source_get_state_wildcarded proto __cdecl \
		source: ptr GtkIconSource

;gboolean
gtk_icon_source_get_direction_wildcarded proto __cdecl \
		source: ptr GtkIconSource

;void
gtk_icon_source_set_direction proto __cdecl \
		source: ptr GtkIconSource,
	     direction: GtkTextDirection

;void
gtk_icon_source_set_state proto __cdecl \
		source: ptr GtkIconSource,
		 state: GtkStateType

;void
gtk_icon_source_set_size proto __cdecl \
		source: ptr GtkIconSource,
		  size: GtkIconSize

;GtkTextDirection
gtk_icon_source_get_direction proto __cdecl \
		source: ptr GtkIconSource

;GtkStateType
gtk_icon_source_get_state proto __cdecl \
		source: ptr GtkIconSource

;GtkIconSize
gtk_icon_source_get_size proto __cdecl \
		source: ptr GtkIconSource



;; ignore this
;void
_gtk_icon_set_invalidate_caches proto __cdecl
;GList*
_gtk_icon_factory_list_ids proto __cdecl
;void
_gtk_icon_factory_ensure_default_icons proto __cdecl

G_END_DECLS

endif
