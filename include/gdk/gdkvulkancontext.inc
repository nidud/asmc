ifndef __GDK_VULKAN_CONTEXT__
define __GDK_VULKAN_CONTEXT__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

ifdef GDK_RENDERING_VULKAN
include vulkan/vulkan.inc
endif

define GDK_TYPE_VULKAN_CONTEXT <gdk_vulkan_context_get_type ()>
GDK_VULKAN_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_VULKAN_CONTEXT, GdkVulkanContext))>
  endm
GDK_IS_VULKAN_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_VULKAN_CONTEXT))>
  endm

define GDK_VULKAN_ERROR <gdk_vulkan_error_quark ()>

gdk_vulkan_error_quark proto

gdk_vulkan_context_get_type proto

ifndef __GI_SCANNER__
ifdef GDK_RENDERING_VULKAN

gdk_vulkan_strerror proto :VkResult

gdk_vulkan_context_get_instance proto :ptr
gdk_vulkan_context_get_physical_device proto :ptr
gdk_vulkan_context_get_device proto :ptr
gdk_vulkan_context_get_queue proto :ptr
gdk_vulkan_context_get_queue_family_index proto :ptr
gdk_vulkan_context_get_image_format proto :ptr
gdk_vulkan_context_get_n_images proto :ptr
gdk_vulkan_context_get_image proto :ptr, :guint
gdk_vulkan_context_get_draw_index proto :ptr
gdk_vulkan_context_get_draw_semaphore proto :ptr

endif
endif

endif
