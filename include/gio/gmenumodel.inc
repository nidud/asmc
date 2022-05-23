ifndef __G_MENU_MODEL_H__
define __G_MENU_MODEL_H__

include glib-object.inc

include gio/giotypes.inc

define G_MENU_ATTRIBUTE_ACTION <"action">
define G_MENU_ATTRIBUTE_ACTION_NAMESPACE <"action-namespace">
define G_MENU_ATTRIBUTE_TARGET <"target">
define G_MENU_ATTRIBUTE_LABEL <"label">
define G_MENU_ATTRIBUTE_ICON <"icon">
define G_MENU_LINK_SUBMENU <"submenu">
define G_MENU_LINK_SECTION <"section">

G_TYPE_MENU_MODEL equ <g_menu_model_get_type>
G_MENU_MODEL macro inst
	exitm<G_TYPE_CHECK_INSTANCE_CAST (inst, G_TYPE_MENU_MODEL, GMenuModel)>
	endm
G_MENU_MODEL_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_MENU_MODEL, GMenuModelClass))>
	endm
G_IS_MENU_MODEL macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_MENU_MODEL))>
	endm
G_IS_MENU_MODEL_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_MENU_MODEL))>
	endm
G_MENU_MODEL_GET_CLASS macro inst
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_MENU_MODEL, GMenuModelClass))>
	endm

GMenuModel		STRUC
parent_instance		GObject <>
priv			ptr GMenuModelPrivate ?
GMenuModel		ENDS

GMenuModelClass		STRUC
parent_class		GObjectClass <>
is_mutable		proc :ptr GMenuModel
get_n_items		proc :ptr GMenuModel
get_item_attributes	proc :ptr GMenuModel, :gint, :ptr GHashTable
iterate_item_attributes proc :ptr GMenuModel, :gint
get_item_attribute_value proc :ptr GMenuModel, :gint, :ptr gchar, :ptr GVariantType
get_item_links		proc :ptr GMenuModel, :gint, :ptr GHashTable
iterate_item_links	proc :ptr GMenuModel, :gint
get_item_link		proc :ptr GMenuModel, :gint, :ptr gchar
GMenuModelClass		ENDS

;GType
g_menu_model_get_type proto __cdecl

;gboolean
g_menu_model_is_mutable proto __cdecl \
		 model: ptr GMenuModel

;gint
g_menu_model_get_n_items proto __cdecl \
		 model: ptr GMenuModel


;GMenuAttributeIter
g_menu_model_iterate_item_attributes proto __cdecl \
		 model: ptr GMenuModel,
	    item_index: gint

;GVariant
g_menu_model_get_item_attribute_value proto __cdecl \
		 model: ptr GMenuModel,
	    item_index: gint,
	     attribute: ptr gchar,
	 expected_type: ptr GVariantType

;gboolean
g_menu_model_get_item_attribute proto _CDecl \
		 model: ptr GMenuModel,
	    item_index: gint,
	     attribute: ptr gchar,
	 format_string: ptr gchar,
		      : vararg

;GMenuLinkIter
g_menu_model_iterate_item_links proto __cdecl \
		 model: ptr GMenuModel,
	    item_index: gint

;GMenuModel
g_menu_model_get_item_link proto __cdecl \
		 model: ptr GMenuModel,
	    item_index: gint,
		  link: ptr gchar


;void
g_menu_model_items_changed proto __cdecl \
		 model: ptr GMenuModel,
	      position: gint,
	       removed: gint,
		 added: gint



G_TYPE_MENU_ATTRIBUTE_ITER equ <g_menu_attribute_iter_get_type>
G_MENU_ATTRIBUTE_ITER macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_MENU_ATTRIBUTE_ITER, GMenuAttributeIter))>
	endm

G_MENU_ATTRIBUTE_ITER_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_MENU_ATTRIBUTE_ITER, GMenuAttributeIterClass))>
	endm
G_IS_MENU_ATTRIBUTE_ITER macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_MENU_ATTRIBUTE_ITER))>
	endm
G_IS_MENU_ATTRIBUTE_ITER_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_MENU_ATTRIBUTE_ITER))>
	endm
G_MENU_ATTRIBUTE_ITER_GET_CLASS macro inst
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_MENU_ATTRIBUTE_ITER, GMenuAttributeIterClass))>
	endm


GMenuAttributeIter	STRUC
parent_instance		GObject <>
priv			ptr GMenuAttributeIterPrivate ?
GMenuAttributeIter	ENDS

GMenuAttributeIterClass STRUC
parent_class		GObjectClass <>
get_next		proc :ptr GMenuAttributeIter, :ptr gchar, :ptr GVariant
GMenuAttributeIterClass ENDS

;GType
g_menu_attribute_iter_get_type proto __cdecl

;gboolean
g_menu_attribute_iter_get_next proto __cdecl \
		  iter: ptr GMenuAttributeIter,
	      out_name: ptr gchar,
		 value: ptr GVariant

;gboolean
g_menu_attribute_iter_next proto __cdecl \
		  iter: ptr GMenuAttributeIter

;const
g_menu_attribute_iter_get_name proto __cdecl \
		  iter: ptr GMenuAttributeIter

;GVariant
g_menu_attribute_iter_get_value proto __cdecl \
		  iter: ptr GMenuAttributeIter



G_TYPE_MENU_LINK_ITER equ <g_menu_link_iter_get_type>
G_MENU_LINK_ITER macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_MENU_LINK_ITER, GMenuLinkIter))>
	endm
G_MENU_LINK_ITER_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_MENU_LINK_ITER, GMenuLinkIterClass))>
	endm
G_IS_MENU_LINK_ITER macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_MENU_LINK_ITER))>
	endm
G_IS_MENU_LINK_ITER_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_MENU_LINK_ITER))>
	endm
G_MENU_LINK_ITER_GET_CLASS macro inst
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_MENU_LINK_ITER, GMenuLinkIterClass))>
	endm


GMenuLinkIter		STRUC
parent_instance		GObject <>
priv			ptr GMenuLinkIterPrivate ?
GMenuLinkIter		ENDS

GMenuLinkIterClass	STRUC
parent_class		GObjectClass <>
get_next		proc :ptr GMenuLinkIter, :ptr gchar, :ptr GMenuModel
GMenuLinkIterClass	ENDS

;GType
g_menu_link_iter_get_type proto __cdecl

;gboolean
g_menu_link_iter_get_next proto __cdecl \
		  iter: ptr GMenuLinkIter,
	      out_link: ptr gchar,
		 value: ptr GMenuModel

;gboolean
g_menu_link_iter_next proto __cdecl \
		  iter: ptr GMenuLinkIter

;const
g_menu_link_iter_get_name proto __cdecl \
		  iter: ptr GMenuLinkIter

;GMenuModel
g_menu_link_iter_get_value proto __cdecl \
		  iter: ptr GMenuLinkIter

endif
