ifndef __GTK_IMAGE_H__
__GTK_IMAGE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/deprecated/gtkmisc.inc


G_BEGIN_DECLS

GTK_TYPE_IMAGE equ <gtk_image_get_type>
GTK_IMAGE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_IMAGE, GtkImage))>
	endm
GTK_IMAGE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_IMAGE, GtkImageClass))>
	endm
GTK_IS_IMAGE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_IMAGE))>
	endm
GTK_IS_IMAGE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_IMAGE))>
	endm
GTK_IMAGE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_IMAGE, GtkImageClass))>
	endm

.enum GtkImageType {
  GTK_IMAGE_EMPTY,
  GTK_IMAGE_PIXBUF,
  GTK_IMAGE_STOCK,
  GTK_IMAGE_ICON_SET,
  GTK_IMAGE_ANIMATION,
  GTK_IMAGE_ICON_NAME,
  GTK_IMAGE_GICON,
  GTK_IMAGE_SURFACE
}

GtkImage		STRUC
misc			GtkMisc <>
priv			ptr_t ?
GtkImage		ENDS

GtkImageClass		STRUC
parent_class		GtkMiscClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkImageClass		ENDS

;GType
gtk_image_get_type proto __cdecl

;GtkWidget*
gtk_image_new proto __cdecl
;GtkWidget*
gtk_image_new_from_file proto __cdecl \
	      filename: ptr gchar

;GtkWidget*
gtk_image_new_from_resource proto __cdecl \
	 resource_path: ptr gchar

;GtkWidget*
gtk_image_new_from_pixbuf proto __cdecl \
		pixbuf: ptr GdkPixbuf

;GtkWidget*
gtk_image_new_from_stock proto __cdecl \
	      stock_id: ptr gchar,
		  size: GtkIconSize

;GtkWidget*
gtk_image_new_from_icon_set proto __cdecl \
	      icon_set: ptr GtkIconSet,
		  size: GtkIconSize

;GtkWidget*
gtk_image_new_from_animation proto __cdecl \
	     animation: ptr GdkPixbufAnimation

;GtkWidget*
gtk_image_new_from_icon_name proto __cdecl \
	     icon_name: ptr gchar,
		  size: GtkIconSize

;GtkWidget*
gtk_image_new_from_gicon proto __cdecl \
		  icon: ptr GIcon,
		  size: GtkIconSize

;GtkWidget*
gtk_image_new_from_surface proto __cdecl \
	       surface: ptr cairo_surface_t


;void
gtk_image_clear proto __cdecl \
		 image: ptr GtkImage

;void
gtk_image_set_from_file proto __cdecl \
		 image: ptr GtkImage,
	      filename: ptr gchar

;void
gtk_image_set_from_resource proto __cdecl \
		 image: ptr GtkImage,
	 resource_path: ptr gchar

;void
gtk_image_set_from_pixbuf proto __cdecl \
		 image: ptr GtkImage,
		pixbuf: ptr GdkPixbuf

;void
gtk_image_set_from_stock proto __cdecl \
		 image: ptr GtkImage,
	      stock_id: ptr gchar,
		  size: GtkIconSize

;void
gtk_image_set_from_icon_set proto __cdecl \
		 image: ptr GtkImage,
	      icon_set: ptr GtkIconSet,
		  size: GtkIconSize

;void
gtk_image_set_from_animation proto __cdecl \
		 image: ptr GtkImage,
	     animation: ptr GdkPixbufAnimation

;void
gtk_image_set_from_icon_name proto __cdecl \
		 image: ptr GtkImage,
	     icon_name: ptr gchar,
		  size: GtkIconSize

;void
gtk_image_set_from_gicon proto __cdecl \
		 image: ptr GtkImage,
		  icon: ptr GIcon,
		  size: GtkIconSize

;void
gtk_image_set_from_surface proto __cdecl \
		 image: ptr GtkImage,
	       surface: ptr cairo_surface_t

;void
gtk_image_set_pixel_size proto __cdecl \
		 image: ptr GtkImage,
	    pixel_size: gint


;GtkImageType
gtk_image_get_storage_type proto __cdecl \
		 image: ptr GtkImage


;GdkPixbuf*
gtk_image_get_pixbuf proto __cdecl \
		 image: ptr GtkImage

;void
gtk_image_get_stock proto __cdecl \
		 image: ptr GtkImage,
	      stock_id: ptr gchar,
		  size: ptr GtkIconSize

;void
gtk_image_get_icon_set proto __cdecl \
		 image: ptr GtkImage,
	      icon_set: ptr GtkIconSet,
		  size: ptr GtkIconSize

;GdkPixbufAnimation*
gtk_image_get_animation proto __cdecl \
		 image: ptr GtkImage

;void
gtk_image_get_icon_name proto __cdecl \
		 image: ptr GtkImage,
	     icon_name: ptr gchar,
		  size: ptr GtkIconSize

;void
gtk_image_get_gicon proto __cdecl \
		 image: ptr GtkImage,
		 gicon: ptr GIcon,
		  size: ptr GtkIconSize

;gint
gtk_image_get_pixel_size proto __cdecl \
		 image: ptr GtkImage

G_END_DECLS

endif
