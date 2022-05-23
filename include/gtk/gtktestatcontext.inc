ifndef __GTK_TEST_STATUS_CONTEXT_H__
define __GTK_TEST_STATUS_CONTEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkatcontext.inc

gtk_test_accessible_assert_role macro accessible,role
  exitm<.err>
  endm
gtk_test_accessible_assert_property macro accessible,property
  exitm<.err>
  endm
gtk_test_accessible_assert_relation macro accessible,relation
  exitm<.err>
  endm
gtk_test_accessible_assert_state macro accessible,state
  exitm<.err>
  endm

gtk_test_accessible_has_role proto :ptr, :GtkAccessibleRole
gtk_test_accessible_has_property proto :ptr, :GtkAccessibleProperty
gtk_test_accessible_has_relation proto :ptr, :GtkAccessibleRelation
gtk_test_accessible_has_state proto :ptr, :GtkAccessibleState

gtk_test_accessible_check_property proto :ptr, :GtkAccessibleProperty, :vararg
gtk_test_accessible_check_relation proto :ptr, :GtkAccessibleRelation, :vararg
gtk_test_accessible_check_state proto :ptr, :GtkAccessibleState, :vararg

gtk_test_accessible_assertion_message_role proto :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :GtkAccessibleRole, :GtkAccessibleRole

endif
