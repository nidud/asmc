ifndef __G_TYPE_MODULE_H__
define __G_TYPE_MODULE_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gobject.inc
include gobject/genums.inc

define G_TYPE_TYPE_MODULE              <g_type_module_get_type ()>
G_TYPE_MODULE macro module
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((module), G_TYPE_TYPE_MODULE, GTypeModule))>
  endm
G_TYPE_MODULE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TYPE_MODULE, GTypeModuleClass))>
  endm
G_IS_TYPE_MODULE macro module
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((module), G_TYPE_TYPE_MODULE))>
  endm
G_IS_TYPE_MODULE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TYPE_MODULE))>
  endm
G_TYPE_MODULE_GET_CLASS macro module
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((module), G_TYPE_TYPE_MODULE, GTypeModuleClass))>
  endm

_GTypeModule            struct
parent_instance         GObject <>
use_count               guint ?
type_infos              ptr GSList ?
interface_infos         ptr GSList ?
name                    ptr gchar ?
_GTypeModule            ends
GTypeModule             typedef _GTypeModule

_GTypeModuleClass       struct
parent_class            GObjectClass <>
load                    proc :ptr
unload                  proc :ptr
reserved1               proc
reserved2               proc
reserved3               proc
reserved4               proc
_GTypeModuleClass       ends
GTypeModuleClass        typedef _GTypeModuleClass


G_DEFINE_DYNAMIC_TYPE macro TN, t_n, T_P
  exitm<G_DEFINE_DYNAMIC_TYPE_EXTENDED (TN, t_n, T_P, 0, {})>
  endm

G_DEFINE_DYNAMIC_TYPE_EXTENDED macro TypeName, type_name, TYPE_PARENT, flags, CODE
    &type_name&_init proto :ptr TypeName
    &type_name&_class_init proto :ptr &TypeName&Class
    &type_name&_class_finalize proto :ptr &TypeName&Class
   .data
    &type_name&_parent_class gpointer NULL
    &type_name&_type_id GType 0
    &TypeName&_private_offset gint 0
   .code
    &type_name&_get_instance_private proc self:ptr TypeName
        G_STRUCT_MEMBER_P(self, &TypeName&_private_offset)
        ret
    &type_name&_get_instance_private endp
    &type_name&_class_intern_init proc klass:gpointer
        mov &type_name&_parent_class,g_type_class_peek_parent(klass)
        &type_name&_class_init(klass)
        ret
    &type_name&_class_intern_init endp
    &type_name&_get_type proc
        mov eax,gtk_gadget_type_id
        ret
    &type_name&_get_type endp
    &type_name&_register_type proc type_module:ptr GTypeModule
    .data
     g_define_type_info GTypeInfo {
        sizeof(&TypeName&Class),
        NULL,
        NULL,
        &type_name&_class_intern_init,
        &type_name&_class_finalize,
        NULL,
        sizeof(TypeName),
        0,
        &type_name&_init,
        NULL
        }
   .code
        mov &type_name&_type_id,g_type_module_register_type(type_module,
            GTK_TYPE_THING, "&TypeName&", &g_define_type_info, flags)
   .data
    g_implement_interface_info GInterfaceInfo { &type_name&_gizmo_init }
   .code
        g_type_module_add_interface(type_module, g_define_type_id, TYPE_GIZMO, &g_implement_interface_info)
        ret
    &type_name&_register_type endp
  exitm<>
  endm


G_IMPLEMENT_INTERFACE_DYNAMIC macro TYPE_IFACE, iface_init
   .data
    g_implement_interface_info GInterfaceInfo { iface_init, NULL, NULL }
   .code
    g_type_module_add_interface (type_module, g_define_type_id, TYPE_IFACE, addr g_implement_interface_info)
  exitm<>
  endm


G_ADD_PRIVATE_DYNAMIC macro TypeName
    mov &TypeName&_private_offset,sizeof (&TypeName&Private)
  exitm<>
  endm

g_type_module_get_type proto
g_type_module_use proto :ptr
g_type_module_unuse proto :ptr
g_type_module_set_name proto :ptr, :ptr
g_type_module_register_type proto :ptr, :GType, :ptr, :ptr, :GTypeFlags
g_type_module_add_interface proto :ptr, :GType, :GType, :ptr
g_type_module_register_enum proto :ptr, :ptr, :ptr
g_type_module_register_flags proto :ptr, :ptr, :ptr

endif
