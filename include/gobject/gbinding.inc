ifndef __G_BINDING_H__
define __G_BINDING_H__
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include glib.inc
include gobject/gobject.inc

G_TYPE_BINDING_FLAGS	equ <g_binding_flags_get_type>

G_TYPE_BINDING		equ <g_binding_get_type>
G_BINDING macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_BINDING, GBinding))>
	endm
G_IS_BINDING macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_BINDING))>
	endm

CALLBACKC(GBindingTransformFunc, :ptr GBinding, \
				 :ptr GValue, \
				 :ptr GValue, \
				 :gpointer)

.enum GBindingFlags {
  G_BINDING_DEFAULT	   = 0,
  G_BINDING_BIDIRECTIONAL  = 1 shl 0,
  G_BINDING_SYNC_CREATE	   = 1 shl 1,
  G_BINDING_INVERT_BOOLEAN = 1 shl 2
  }

;GType
g_binding_flags_get_type proto __cdecl
;GType
g_binding_get_type proto __cdecl

;GBindingFlags
g_binding_get_flags proto __cdecl \
	       binding: ptr GBinding

;GObject
g_binding_get_source proto __cdecl \
	       binding: ptr GBinding

;GObject
g_binding_get_target proto __cdecl \
	       binding: ptr GBinding

;const
g_binding_get_source_property proto __cdecl \
	       binding: ptr GBinding

;const
g_binding_get_target_property proto __cdecl \
	       binding: ptr GBinding

;void
g_binding_unbind proto __cdecl \
	       binding: ptr GBinding


;GBinding
g_object_bind_property proto __cdecl \
		source: gpointer,
       source_property: ptr gchar,
		target: gpointer,
       target_property: ptr gchar,
		 flags: GBindingFlags

;GBinding
g_object_bind_property_full proto __cdecl \
		source: gpointer,
       source_property: ptr gchar,
		target: gpointer,
       target_property: ptr gchar,
		 flags: GBindingFlags,
	  transform_to: GBindingTransformFunc,
	transform_from: GBindingTransformFunc,
	     user_data: gpointer,
		notify: GDestroyNotify

;GBinding
g_object_bind_property_with_closures proto __cdecl \
		source: gpointer,
       source_property: ptr gchar,
		target: gpointer,
       target_property: ptr gchar,
		 flags: GBindingFlags,
	  transform_to: ptr GClosure,
	transform_from: ptr GClosure

endif
