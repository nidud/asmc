ifndef __G_TEST_UTILS_H__
define __G_TEST_UTILS_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gmessages.inc
include glib/gstring.inc
include glib/gerror.inc
include glib/gslist.inc
include errno.inc
include string.inc

CALLBACK(GTestFunc)
CALLBACK(GTestDataFunc, :gconstpointer)
CALLBACK(GTestFixtureFunc, :gpointer, :gconstpointer)

g_strcmp0 proto :ptr, :ptr
g_test_init proto :ptr, :ptr, :vararg

define G_TEST_OPTION_ISOLATE_DIRS <"isolate_dirs">

g_test_subprocess proto

g_test_run proto
g_test_add_func proto :ptr, :GTestFunc
g_test_add_data_func proto :ptr, :gconstpointer, :GTestDataFunc
g_test_add_data_func_full proto :ptr, :gpointer, :GTestDataFunc, :GDestroyNotify
g_test_get_path proto
g_test_fail proto
g_test_incomplete proto :ptr
g_test_skip proto :ptr
g_test_failed proto
g_test_set_nonfatal_assertions proto

g_test_bug_base proto :ptr
g_test_bug proto :ptr
g_test_summary proto :ptr

g_test_timer_start proto
g_test_timer_elapsed proto

g_test_queue_free proto :gpointer
g_test_queue_destroy proto :GDestroyNotify, :gpointer
g_test_queue_unref macro gobject
  exitm<g_test_queue_destroy (g_object_unref, gobject)>
  endm

.enum GTestTrapFlags {
  G_TEST_TRAP_SILENCE_STDOUT    = 1 shl 7,
  G_TEST_TRAP_SILENCE_STDERR    = 1 shl 8,
  G_TEST_TRAP_INHERIT_STDIN     = 1 shl 9
}

g_test_trap_fork proto :guint64, :GTestTrapFlags

.enum GTestSubprocessFlags {
  G_TEST_SUBPROCESS_INHERIT_STDIN  = 1 shl 0,
  G_TEST_SUBPROCESS_INHERIT_STDOUT = 1 shl 1,
  G_TEST_SUBPROCESS_INHERIT_STDERR = 1 shl 2
}

g_test_trap_subprocess proto :ptr, :guint64, :GTestSubprocessFlags

g_test_trap_has_passed proto
g_test_trap_reached_timeout proto
g_test_trap_assert_passed macro
  exitm<g_test_trap_assertions (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, 0, 0)>
  endm
g_test_trap_assert_failed macro
  exitm<g_test_trap_assertions (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, 1, 0)>
  endm
g_test_trap_assert_stdout macro soutpattern
  exitm<g_test_trap_assertions (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, 2, soutpattern)>
  endm
g_test_trap_assert_stdout_unmatched macro soutpattern
  exitm<g_test_trap_assertions (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, 3, soutpattern)>
  endm
g_test_trap_assert_stderr macro serrpattern
  exitm<g_test_trap_assertions (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, 4, serrpattern)>
  endm
g_test_trap_assert_stderr_unmatched macro serrpattern
  exitm<g_test_trap_assertions (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, 5, serrpattern)>
  endm


g_test_rand_bit macro
  exitm<(g_test_rand_int() & (1 shl 15))>
  endm
g_test_rand_int proto
g_test_rand_int_range proto :gint32, :gint32
g_test_rand_double proto
g_test_rand_double_range proto :real8, :real8


g_test_create_case proto :ptr, :gsize, :gconstpointer, :GTestFixtureFunc, :GTestFixtureFunc, :GTestFixtureFunc
g_test_create_suite proto :ptr
g_test_get_root proto
g_test_suite_add proto :ptr, :ptr
g_test_suite_add_suite proto :ptr, :ptr
g_test_run_suite proto :ptr

g_test_case_free proto :ptr

g_test_suite_free proto :ptr

g_test_trap_assertions proto :ptr, :ptr, :sdword, :ptr, :guint64, :ptr
g_assertion_message proto :ptr, :ptr, :sdword, :ptr, :ptr
g_assertion_message_expr proto :ptr, :ptr, :sdword, :ptr, :ptr
g_assertion_message_cmpstr proto :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :ptr, :ptr

g_assertion_message_cmpstrv proto :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :ptr, :gsize
g_assertion_message_cmpnum proto :ptr, :ptr, :sdword, :ptr, :ptr, :real8, :ptr, :real8, :sbyte
g_assertion_message_error proto :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :GQuark, :sdword
g_test_add_vtable proto :ptr, :gsize, :gconstpointer, :GTestFixtureFunc, :GTestFixtureFunc, :GTestFixtureFunc

GTestConfig             struct
test_initialized        gboolean ?
test_quick              gboolean ?
test_perf               gboolean ?
test_verbose            gboolean ?
test_quiet              gboolean ?
test_undefined          gboolean ?
GTestConfig             ends

.enum GTestResult {
  G_TEST_RUN_SUCCESS,
  G_TEST_RUN_SKIPPED,
  G_TEST_RUN_FAILURE,
  G_TEST_RUN_INCOMPLETE
}

.enum GTestLogType {
  G_TEST_LOG_NONE,
  G_TEST_LOG_ERROR,
  G_TEST_LOG_START_BINARY,
  G_TEST_LOG_LIST_CASE,
  G_TEST_LOG_SKIP_CASE,
  G_TEST_LOG_START_CASE,
  G_TEST_LOG_STOP_CASE,
  G_TEST_LOG_MIN_RESULT,
  G_TEST_LOG_MAX_RESULT,
  G_TEST_LOG_MESSAGE,
  G_TEST_LOG_START_SUITE,
  G_TEST_LOG_STOP_SUITE
}

GTestLogMsg             struct
log_type                GTestLogType ?
n_strings               guint ?
strings                 ptr gchar ?
n_nums                  guint ?
nums                    ptr real8 ?
GTestLogMsg             ends

GTestLogBuffer          struct
data                    ptr GString ?
msgs                    ptr GSList ?
GTestLogBuffer          ends

g_test_log_type_name proto :GTestLogType
g_test_log_buffer_new proto
g_test_log_buffer_free proto :ptr
g_test_log_buffer_push proto :ptr, :guint, :ptr
g_test_log_buffer_pop proto :ptr
g_test_log_msg_free proto :ptr

CALLBACK(GTestLogFatalFunc, :ptr, :GLogLevelFlags, :ptr, :gpointer)

g_test_expect_message proto :ptr, :GLogLevelFlags, :ptr
g_test_assert_expected_messages_internal proto :ptr, :ptr, :sdword, :ptr

.enum GTestFileType {
  G_TEST_DIST,
  G_TEST_BUILT
}

g_test_build_filename proto :GTestFileType, :ptr, :vararg
g_test_get_dir proto :GTestFileType
g_test_get_filename proto :GTestFileType, :ptr, :vararg

g_test_assert_expected_messages macro
  exitm<g_test_assert_expected_messages_internal (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC)>
  endm

endif
