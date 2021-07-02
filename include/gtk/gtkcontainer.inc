ifndef __GTK_CONTAINER_H__
__GTK_CONTAINER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif
include gtk/gtkwidget.inc

GTK_TYPE_CONTAINER equ <gtk_container_get_type>
GTK_CONTAINER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CONTAINER, GtkContainer))>
	endm
GTK_CONTAINER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CONTAINER, GtkContainerClass))>
	endm
GTK_IS_CONTAINER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CONTAINER))>
	endm
GTK_IS_CONTAINER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CONTAINER))>
	endm
GTK_CONTAINER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CONTAINER, GtkContainerClass))>
	endm

GtkContainer		STRUC
widget			GtkWidget <>
priv			ptr_t ?
GtkContainer		ENDS

GtkContainerClass	STRUC
parent_class		GtkWidgetClass <>
_add			proc :ptr GtkContainer, :ptr GtkWidget
remove			proc :ptr GtkContainer, :ptr GtkWidget
check_resize		proc :ptr GtkContainer
forall			proc :ptr GtkContainer, :gboolean, :GtkCallback, :gpointer
set_focus_child		proc :ptr GtkContainer, :ptr GtkWidget
child_type		proc :ptr GtkContainer
composite_name		proc :ptr GtkContainer, :ptr, :ptr
set_child_property	proc :ptr GtkContainer, :ptr GtkWidget, :guint, :ptr GValue, :ptr GParamSpec
get_child_property	proc :ptr GtkContainer, :ptr GtkWidget, :guint, :ptr GValue, :ptr GParamSpec
get_path_for_child	proc :ptr GtkContainer, :ptr GtkWidget
_handle_border_width	int_t ? ;: 1 unsigned ?
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkContainerClass	ENDS

.enum GtkResizeMode {
  GTK_RESIZE_PARENT,
  GTK_RESIZE_QUEUE,
  GTK_RESIZE_IMMEDIATE
}

gtk_container_get_type proto __cdecl
gtk_container_set_border_width proto __cdecl \
	     container: ptr GtkContainer,
	  border_width: guint
gtk_container_get_border_width proto __cdecl \
	     container: ptr GtkContainer

;void
gtk_container_add proto __cdecl \
	     container: ptr GtkContainer,
		widget: ptr GtkWidget

;void
gtk_container_remove proto __cdecl \
	     container: ptr GtkContainer,
		widget: ptr GtkWidget


;void
gtk_container_set_resize_mode proto __cdecl \
	     container: ptr GtkContainer,
	   resize_mode: GtkResizeMode

;GtkResizeMode
gtk_container_get_resize_mode proto __cdecl \
	     container: ptr GtkContainer


;void
gtk_container_check_resize proto __cdecl \
	     container: ptr GtkContainer


;void
gtk_container_foreach proto __cdecl \
	     container: ptr GtkContainer,
	      callback: GtkCallback,
	 callback_data: gpointer

;GList*
gtk_container_get_children proto __cdecl \
	     container: ptr GtkContainer


;void
gtk_container_propagate_draw proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
		    cr: ptr cairo_t


;void
gtk_container_set_focus_chain proto __cdecl \
	     container: ptr GtkContainer,
     focusable_widgets: ptr GList

;gboolean
gtk_container_get_focus_chain proto __cdecl \
	     container: ptr GtkContainer,
     focusable_widgets: ptr GList

gtk_container_unset_focus_chain proto __cdecl \
	     container: ptr GtkContainer


GTK_IS_RESIZE_CONTAINER macro widget
	exitm<.err>
	endm


gtk_container_set_reallocate_redraws proto __cdecl \
	     container: ptr GtkContainer,
	 needs_redraws: gboolean

gtk_container_set_focus_child proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget

;GtkWidget
gtk_container_get_focus_child proto __cdecl \
	     container: ptr GtkContainer

;void
gtk_container_set_focus_vadjustment proto __cdecl \
	     container: ptr GtkContainer,
	    adjustment: ptr GtkAdjustment

;GtkAdjustment
gtk_container_get_focus_vadjustment proto __cdecl \
	     container: ptr GtkContainer

;void
gtk_container_set_focus_hadjustment proto __cdecl \
	     container: ptr GtkContainer,
	    adjustment: ptr GtkAdjustment

;GtkAdjustment
gtk_container_get_focus_hadjustment proto __cdecl \
	     container: ptr GtkContainer


;void
gtk_container_resize_children proto __cdecl \
	     container: ptr GtkContainer


;GType
gtk_container_child_type proto __cdecl \
	     container: ptr GtkContainer



;void
gtk_container_class_install_child_property proto __cdecl \
		cclass: ptr GtkContainerClass,
	   property_id: guint,
		 pspec: ptr GParamSpec

;void
gtk_container_class_install_child_properties proto __cdecl \
		cclass: ptr GtkContainerClass,
	      n_pspecs: guint,
		pspecs: ptr GParamSpec

;GParamSpec*
gtk_container_class_find_child_property proto __cdecl \
		cclass: ptr GObjectClass,
	 property_name: ptr gchar

;GParamSpec**
gtk_container_class_list_child_properties proto __cdecl \
		cclass: ptr GObjectClass,
	  n_properties: ptr guint

;void
gtk_container_add_with_properties proto _CDecl \
	     container: ptr GtkContainer,
		widget: ptr GtkWidget,
       first_prop_name: ptr gchar,
		      : vararg

;void
gtk_container_child_set proto _CDecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
       first_prop_name: ptr gchar,
		      : vararg

;void
gtk_container_child_get proto _CDecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
       first_prop_name: ptr gchar,
		      : vararg

;void
gtk_container_child_set_valist proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
   first_property_name: ptr gchar,
	      var_args: va_list

;void
gtk_container_child_get_valist proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
   first_property_name: ptr gchar,
	      var_args: va_list

;void
gtk_container_child_set_property proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
	 property_name: ptr gchar,
		 value: ptr GValue

;void
gtk_container_child_get_property proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
	 property_name: ptr gchar,
		 value: ptr GValue


;void
gtk_container_child_notify proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
	child_property: ptr gchar


;void
gtk_container_child_notify_by_pspec proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget,
		 pspec: ptr GParamSpec


GTK_CONTAINER_WARN_INVALID_CHILD_PROPERTY_ID macro object, property_id, pspec
	exitm<.err>
	endm

gtk_container_forall proto __cdecl \
	     container: ptr GtkContainer,
	      callback: GtkCallback,
	 callback_data: gpointer

gtk_container_class_handle_border_width proto __cdecl \
		 klass: ptr GtkContainerClass

;GtkWidgetPath
gtk_container_get_path_for_child proto __cdecl \
	     container: ptr GtkContainer,
		 child: ptr GtkWidget

endif
