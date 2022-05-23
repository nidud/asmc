ifndef __G_EMBLEMED_ICON_H__
define __G_EMBLEMED_ICON_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gicon.inc
include gio/gemblem.inc

define G_TYPE_EMBLEMED_ICON         <g_emblemed_icon_get_type>
G_EMBLEMED_ICON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_EMBLEMED_ICON, GEmblemedIcon))>
  endm
G_EMBLEMED_ICON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_EMBLEMED_ICON, GEmblemedIconClass))>
  endm
G_IS_EMBLEMED_ICON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_EMBLEMED_ICON))>
  endm
G_IS_EMBLEMED_ICON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_EMBLEMED_ICON))>
  endm
G_EMBLEMED_ICON_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_EMBLEMED_ICON, GEmblemedIconClass))>
  endm

;GEmblemedIconPrivate    typedef _GEmblemedIconPrivate

_GEmblemedIcon          struct
parent_instance         GObject <>
priv                    ptr GEmblemedIconPrivate ?
_GEmblemedIcon          ends
GEmblemedIcon           typedef _GEmblemedIcon

_GEmblemedIconClass     struct
parent_class            GObjectClass <>
_GEmblemedIconClass     ends
GEmblemedIconClass      typedef _GEmblemedIconClass

g_emblemed_icon_get_type proto

g_emblemed_icon_new proto :ptr, :ptr
g_emblemed_icon_get_icon proto :ptr
g_emblemed_icon_get_emblems proto :ptr
g_emblemed_icon_add_emblem proto :ptr, :ptr
g_emblemed_icon_clear_emblems proto :ptr

endif
