ifndef __G_MENU_H__
define __G_MENU_H__

include gio/gmenumodel.inc

define G_TYPE_MENU          <g_menu_get_type ()>
G_MENU macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_MENU, GMenu))>
  endm
G_IS_MENU macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_MENU))>
  endm

define G_TYPE_MENU_ITEM     <g_menu_item_get_type ()>
G_MENU_ITEM macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_MENU_ITEM, GMenuItem))>
  endm
G_IS_MENU_ITEM macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_MENU_ITEM))>
  endm

;GMenuItem               typedef _GMenuItem
;GMenu                   typedef _GMenu

g_menu_get_type proto
g_menu_new proto
g_menu_freeze proto :ptr
g_menu_insert_item proto :ptr, :gint, :ptr
g_menu_prepend_item proto :ptr, :ptr
g_menu_append_item proto :ptr, :ptr
g_menu_remove proto :ptr, :gint

g_menu_remove_all proto :ptr

g_menu_insert proto :ptr, :gint, :ptr, :ptr
g_menu_prepend proto :ptr, :ptr, :ptr
g_menu_append proto :ptr, :ptr, :ptr

g_menu_insert_section proto :ptr, :gint, :ptr, :ptr
g_menu_prepend_section proto :ptr, :ptr, :ptr
g_menu_append_section proto :ptr, :ptr, :ptr

g_menu_insert_submenu proto :ptr, :gint, :ptr, :ptr
g_menu_prepend_submenu proto :ptr, :ptr, :ptr
g_menu_append_submenu proto :ptr, :ptr, :ptr


g_menu_item_get_type proto
g_menu_item_new proto :ptr, :ptr

g_menu_item_new_from_model proto :ptr, :gint

g_menu_item_new_submenu proto :ptr, :ptr

g_menu_item_new_section proto :ptr, :ptr

g_menu_item_get_attribute_value proto :ptr, :ptr, :ptr
g_menu_item_get_attribute proto :ptr, :ptr, :ptr, :vararg
g_menu_item_get_link proto :ptr, :ptr

g_menu_item_set_attribute_value proto :ptr, :ptr, :ptr
g_menu_item_set_attribute proto :ptr, :ptr, :ptr, :vararg
g_menu_item_set_link proto :ptr, :ptr, :ptr
g_menu_item_set_label proto :ptr, :ptr
g_menu_item_set_submenu proto :ptr, :ptr
g_menu_item_set_section proto :ptr, :ptr
g_menu_item_set_action_and_target_value proto :ptr, :ptr, :ptr
g_menu_item_set_action_and_target proto :ptr, :ptr, :ptr, :vararg
g_menu_item_set_detailed_action proto :ptr, :ptr

g_menu_item_set_icon proto :ptr, :ptr

endif
