ifndef __GDK_SELECTION_H__
__GDK_SELECTION_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

GDK_SELECTION_PRIMARY   equ _GDK_MAKE_ATOM (1)
GDK_SELECTION_SECONDARY equ _GDK_MAKE_ATOM (2)
GDK_SELECTION_CLIPBOARD equ _GDK_MAKE_ATOM (69)
GDK_TARGET_BITMAP       equ _GDK_MAKE_ATOM (5)
GDK_TARGET_COLORMAP     equ _GDK_MAKE_ATOM (7)
GDK_TARGET_DRAWABLE     equ _GDK_MAKE_ATOM (17)
GDK_TARGET_PIXMAP       equ _GDK_MAKE_ATOM (20)
GDK_TARGET_STRING       equ _GDK_MAKE_ATOM (31)
GDK_SELECTION_TYPE_ATOM equ _GDK_MAKE_ATOM (4)
GDK_SELECTION_TYPE_BITMAP equ _GDK_MAKE_ATOM (5)
GDK_SELECTION_TYPE_COLORMAP equ _GDK_MAKE_ATOM (7)
GDK_SELECTION_TYPE_DRAWABLE equ _GDK_MAKE_ATOM (17)
GDK_SELECTION_TYPE_INTEGER equ _GDK_MAKE_ATOM (19)
GDK_SELECTION_TYPE_PIXMAP equ _GDK_MAKE_ATOM (20)
GDK_SELECTION_TYPE_WINDOW equ _GDK_MAKE_ATOM (33)
GDK_SELECTION_TYPE_STRING equ _GDK_MAKE_ATOM (31)

;gboolean
gdk_selection_owner_set proto __cdecl \
                 owner: ptr GdkWindow,
             selection: GdkAtom,
                 time_: guint32,
            send_event: gboolean

;GdkWindow*
gdk_selection_owner_get proto __cdecl \
             selection: GdkAtom

;gboolean
gdk_selection_owner_set_for_display proto __cdecl \
               display: ptr GdkDisplay,
                 owner: ptr GdkWindow,
             selection: GdkAtom,
                 time_: guint32,
            send_event: gboolean

;GdkWindow
gdk_selection_owner_get_for_display proto __cdecl \
               display: ptr GdkDisplay,
             selection: GdkAtom


;void
gdk_selection_convert proto __cdecl \
             requestor: ptr GdkWindow,
             selection: GdkAtom,
                target: GdkAtom,
                 time_: guint32

;gint
gdk_selection_property_get proto __cdecl \
             requestor: ptr GdkWindow,
                  data: ptr guchar,
             prop_type: ptr GdkAtom,
           prop_format: ptr gint


;void
gdk_selection_send_notify proto __cdecl \
             requestor: ptr GdkWindow,
             selection: GdkAtom,
                target: GdkAtom,
              property: GdkAtom,
                 time_: guint32


;void
gdk_selection_send_notify_for_display proto __cdecl \
               display: ptr GdkDisplay,
             requestor: ptr GdkWindow,
             selection: GdkAtom,
                target: GdkAtom,
              property: GdkAtom,
                 time_: guint32


endif
