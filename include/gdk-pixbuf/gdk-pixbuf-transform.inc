ifndef GDK_PIXBUF_TRANSFORM_H
define GDK_PIXBUF_TRANSFORM_H

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include glib.inc
include gdk-pixbuf/gdk-pixbuf-core.inc


.enum GdkInterpType {
    GDK_INTERP_NEAREST,
    GDK_INTERP_TILES,
    GDK_INTERP_BILINEAR,
    GDK_INTERP_HYPER
    }

.enum GdkPixbufRotation {
    GDK_PIXBUF_ROTATE_NONE		=   0,
    GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE	=  90,
    GDK_PIXBUF_ROTATE_UPSIDEDOWN	= 180,
    GDK_PIXBUF_ROTATE_CLOCKWISE		= 270
    }


gdk_pixbuf_scale proto __cdecl \
		   src: ptr GdkPixbuf,
		  dest: ptr GdkPixbuf,
		dest_x: SINT,
		dest_y: SINT,
	    dest_width: SINT,
	   dest_height: SINT,
	      offset_x: double,
	      offset_y: double,
	       scale_x: double,
	       scale_y: double,
	   interp_type: GdkInterpType

gdk_pixbuf_composite proto __cdecl \
		   src: ptr GdkPixbuf,
		  dest: ptr GdkPixbuf,
		dest_x: SINT,
		dest_y: SINT,
	    dest_width: SINT,
	   dest_height: SINT,
	      offset_x: double,
	      offset_y: double,
	       scale_x: double,
	       scale_y: double,
	   interp_type: GdkInterpType,
	 overall_alpha: SINT

gdk_pixbuf_composite_color proto __cdecl \
		   src: ptr GdkPixbuf,
		  dest: ptr GdkPixbuf,
		dest_x: SINT,
		dest_y: SINT,
	    dest_width: SINT,
	   dest_height: SINT,
	      offset_x: double,
	      offset_y: double,
	       scale_x: double,
	       scale_y: double,
	   interp_type: GdkInterpType,
	 overall_alpha: SINT,
	       check_x: SINT,
	       check_y: SINT,
	    check_size: SINT,
		color1: guint32,
		color2: guint32


gdk_pixbuf_scale_simple proto __cdecl \
		   src: ptr GdkPixbuf,
	    dest_width: SINT,
	   dest_height: SINT,
	   interp_type: GdkInterpType


gdk_pixbuf_composite_color_simple proto __cdecl \
		   src: ptr GdkPixbuf,
	    dest_width: SINT,
	   dest_height: SINT,
	   interp_type: GdkInterpType,
	 overall_alpha: SINT,
	    check_size: SINT,
		color1: guint32,
		color2: guint32


gdk_pixbuf_rotate_simple proto __cdecl \
		   src: ptr GdkPixbuf,
		 angle: GdkPixbufRotation

gdk_pixbuf_flip proto __cdecl \
		   src: ptr GdkPixbuf,
	    horizontal: gboolean

endif
