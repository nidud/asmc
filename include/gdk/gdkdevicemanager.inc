ifndef __GDK_DEVICE_MANAGER_H__
__GDK_DEVICE_MANAGER_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkdevice.inc

GDK_TYPE_DEVICE_MANAGER equ <gdk_device_manager_get_type>
GDK_DEVICE_MANAGER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_DEVICE_MANAGER, GdkDeviceManager))>
	endm
GDK_IS_DEVICE_MANAGER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_DEVICE_MANAGER))>
	endm

;GType
gdk_device_manager_get_type proto __cdecl

;GdkDisplay
gdk_device_manager_get_display proto __cdecl \
	device_manager: ptr GdkDeviceManager

;GList
gdk_device_manager_list_devices proto __cdecl \
	device_manager: ptr GdkDeviceManager,
		  type: GdkDeviceType

;GdkDevice
gdk_device_manager_get_client_pointer proto __cdecl \
	device_manager: ptr GdkDeviceManager

endif
