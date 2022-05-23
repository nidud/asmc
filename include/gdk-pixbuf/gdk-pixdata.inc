ifndef __GDK_PIXDATA_H__
define __GDK_PIXDATA_H__

ifndef GDK_PIXBUF_DISABLE_DEPRECATED
include gdk-pixbuf/gdk-pixbuf.inc

GDK_PIXBUF_MAGIC_NUMBER equ (0x47646b50)

.enum {
    GDK_PIXDATA_COLOR_TYPE_RGB	  = 0x01,
    GDK_PIXDATA_COLOR_TYPE_RGBA	  = 0x02,
    GDK_PIXDATA_COLOR_TYPE_MASK	  = 0xff,
    GDK_PIXDATA_SAMPLE_WIDTH_8	  = 0x01 shl 16,
    GDK_PIXDATA_SAMPLE_WIDTH_MASK = 0x0f shl 16,
    GDK_PIXDATA_ENCODING_RAW	  = 0x01 shl 24,
    GDK_PIXDATA_ENCODING_RLE	  = 0x02 shl 24,
    GDK_PIXDATA_ENCODING_MASK	  = 0x0f shl 24
    }

GdkPixdata		STRUC
magic			guint32 ?
length			gint32 ?
pixdata_type		guint32 ?
rowstride		guint32 ?
width			guint32 ?
height			guint32 ?
pixel_data		ptr guint8 ?
GdkPixdata		ENDS

GDK_PIXDATA_HEADER_LENGTH equ (4 + 4 + 4 + 4 + 4 + 4)


gdk_pixdata_serialize proto __cdecl \
	       pixdata: ptr GdkPixdata,
       stream_length_p: ptr guint

gdk_pixdata_deserialize proto __cdecl \
	       pixdata: ptr GdkPixdata,
	 stream_length: guint,
		stream: ptr guint8,
		 error: ptr GError

gdk_pixdata_from_pixbuf proto __cdecl \
	       pixdata: ptr GdkPixdata,
		pixbuf: ptr GdkPixbuf,
	       use_rle: gboolean

gdk_pixbuf_from_pixdata proto __cdecl \
	       pixdata: ptr GdkPixdata,
	   copy_pixels: gboolean,
		 error: ptr GError

.enum GdkPixdataDumpType {
    GDK_PIXDATA_DUMP_PIXDATA_STREAM	= 0,
    GDK_PIXDATA_DUMP_PIXDATA_STRUCT	= 1,
    GDK_PIXDATA_DUMP_MACROS		= 2,
    GDK_PIXDATA_DUMP_GTYPES		= 0,
    GDK_PIXDATA_DUMP_CTYPES		= 1 shl 8,
    GDK_PIXDATA_DUMP_STATIC		= 1 shl 9,
    GDK_PIXDATA_DUMP_CONST		= 1 shl 10,
    GDK_PIXDATA_DUMP_RLE_DECODER	= 1 shl 16
    }


gdk_pixdata_to_csource proto __cdecl \
	       pixdata: ptr GdkPixdata,
		  name: ptr gchar,
	     dump_type: GdkPixdataDumpType


endif

endif
