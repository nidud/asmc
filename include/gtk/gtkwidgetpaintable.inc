ifndef __GTK_WIDGET_PAINTABLE_H__
define __GTK_WIDGET_PAINTABLE_H__

include gtk/gtktypes.inc

define GTK_TYPE_WIDGET_PAINTABLE <gtk_widget_paintable_get_type>

gtk_widget_paintable_new proto :ptr
gtk_widget_paintable_get_widget proto :ptr
gtk_widget_paintable_set_widget proto :ptr, :ptr

endif
