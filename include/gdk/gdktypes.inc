ifndef __GDK_TYPES_H__
define __GDK_TYPES_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib.inc
include glib-object.inc
include gio/gio.inc
include cairo.inc
include pango/pango.inc

include gdk/gdkconfig.inc

define GDK_CURRENT_TIME     0

ifdef __GI_SCANNER__
GdkRectangle            struct
x                       sdword ?
y                       sdword ?
width                   sdword ?
height                  sdword ?
GdkRectangle            ends
else
GdkRectangle            typedef cairo_rectangle_int_t
endif

GDK_DECLARE_INTERNAL_TYPE macro ModuleObjName, module_obj_name, MODULE, OBJ_NAME, ParentName
    &module_obj_name&_get_type proto
    ModuleObjName typedef _&ModuleObjName&
    &ModuleObjName&Class typedef _&ModuleObjName&Class
    _GLIB_DEFINE_AUTOPTR_CHAINUP (ModuleObjName, ParentName)
    G_DEFINE_AUTOPTR_CLEANUP_FUNC (ModuleObjName##Class, g_type_class_unref)
    &MODULE&_&OBJ_NAME& proto :ptr {
        G_TYPE_CHECK_INSTANCE_CAST (_1, &module_obj_name&_get_type (), ModuleObjName)
        }
    &MODULE&_&OBJ_NAME&_CLASS proto :ptr {
        G_TYPE_CHECK_CLASS_CAST (_1, &module_obj_name&_get_type (), &ModuleObjName&Class)
        }
    &MODULE&_IS_&OBJ_NAME proto :ptr {
        G_TYPE_CHECK_INSTANCE_TYPE (_1, &module_obj_name&_get_type ())
        }
    &MODULE&_IS_&OBJ_NAME&_CLASS :ptr {
        G_TYPE_CHECK_CLASS_TYPE (_1, &module_obj_name&_get_type ())
        }
    &MODULE&_&OBJ_NAME&_GET_CLASS :ptr {
        G_TYPE_INSTANCE_GET_CLASS (_1, &module_obj_name&_get_type(), &ModuleObjName&Class)
        }
  exitm<>
  endm

GdkKeymapKey            struct
keycode                 guint ?
_group                  sdword ?
level                   sdword ?
GdkKeymapKey            ends

endif
