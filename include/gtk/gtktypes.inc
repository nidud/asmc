ifndef __GTK_TYPES_H__
define __GTK_TYPES_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
if 0
GtkAdjustment           typedef _GtkAdjustment
GtkBitset               typedef _GtkBitset
GtkBuilder              typedef _GtkBuilder
GtkBuilderScope         typedef _GtkBuilderScope
GtkCssStyleChange       typedef _GtkCssStyleChange
GtkEventController      typedef _GtkEventController
GtkGesture              typedef _GtkGesture
GtkLayoutManager        typedef _GtkLayoutManager
GtkListItem             typedef _GtkListItem
GtkListItemFactory      typedef _GtkListItemFactory
GtkNative               typedef _GtkNative
GtkRequisition          typedef _GtkRequisition
GtkRoot                 typedef _GtkRoot
GtkSettings             typedef _GtkSettings
GtkShortcut             typedef _GtkShortcut
GtkShortcutAction       typedef _GtkShortcutAction
GtkShortcutTrigger      typedef _GtkShortcutTrigger
GtkSnapshot             typedef GdkSnapshot
GtkStyleContext         typedef _GtkStyleContext
GtkTooltip              typedef _GtkTooltip
GtkWidget               typedef _GtkWidget
GtkWindow               typedef _GtkWindow
endif
define GTK_INVALID_LIST_POSITION ( 0xffffffff)

endif
