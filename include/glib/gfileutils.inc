ifndef __G_FILEUTILS_H__
define __G_FILEUTILS_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glibconfig.inc
include glib/gerror.inc

G_FILE_ERROR equ <g_file_error_quark>

.enum GFileError {
    G_FILE_ERROR_EXIST,
    G_FILE_ERROR_ISDIR,
    G_FILE_ERROR_ACCES,
    G_FILE_ERROR_NAMETOOLONG,
    G_FILE_ERROR_NOENT,
    G_FILE_ERROR_NOTDIR,
    G_FILE_ERROR_NXIO,
    G_FILE_ERROR_NODEV,
    G_FILE_ERROR_ROFS,
    G_FILE_ERROR_TXTBSY,
    G_FILE_ERROR_FAULT,
    G_FILE_ERROR_LOOP,
    G_FILE_ERROR_NOSPC,
    G_FILE_ERROR_NOMEM,
    G_FILE_ERROR_MFILE,
    G_FILE_ERROR_NFILE,
    G_FILE_ERROR_BADF,
    G_FILE_ERROR_INVAL,
    G_FILE_ERROR_PIPE,
    G_FILE_ERROR_AGAIN,
    G_FILE_ERROR_INTR,
    G_FILE_ERROR_IO,
    G_FILE_ERROR_PERM,
    G_FILE_ERROR_NOSYS,
    G_FILE_ERROR_FAILED
    }

.enum GFileTest {
    G_FILE_TEST_IS_REGULAR    = 1 shl 0,
    G_FILE_TEST_IS_SYMLINK    = 1 shl 1,
    G_FILE_TEST_IS_DIR	      = 1 shl 2,
    G_FILE_TEST_IS_EXECUTABLE = 1 shl 3,
    G_FILE_TEST_EXISTS	      = 1 shl 4
    }

.enum GFileSetContentsFlags {
    G_FILE_SET_CONTENTS_NONE = 0,
    G_FILE_SET_CONTENTS_CONSISTENT = 1 shl 0,
    G_FILE_SET_CONTENTS_DURABLE = 1 shl 1,
    G_FILE_SET_CONTENTS_ONLY_EXISTING = 1 shl 2
    }

;GQuark
g_file_error_quark proto __cdecl

;GFileError
g_file_error_from_errno proto __cdecl \
		err_no: gint


;gboolean
g_file_test proto __cdecl \
	      filename: ptr gchar,
		 _test: GFileTest

;gboolean
g_file_get_contents proto __cdecl \
	      filename: ptr gchar,
	      contents: ptr gchar,
		length: ptr gsize,
		 error: ptr GError

;gboolean
g_file_set_contents proto __cdecl \
	      filename: ptr gchar,
	      contents: ptr gchar,
		length: gssize,
		 error: ptr GError


;gboolean
g_file_set_contents_full proto __cdecl \
	      filename: ptr gchar,
	      contents: ptr gchar,
		length: gssize,
		 flags: GFileSetContentsFlags,
		  mode: SINT,
		 error: ptr GError


;gchar
g_file_read_link proto __cdecl \
	      filename: ptr gchar,
		 error: ptr GError

;gchar
g_mkdtemp proto __cdecl \
		  tmpl: ptr gchar

;gchar
g_mkdtemp_full proto __cdecl \
		  tmpl: ptr gchar,
		  mode: gint

;gint
g_mkstemp proto __cdecl \
		  tmpl: ptr gchar

;gint
g_mkstemp_full proto __cdecl \
		  tmpl: ptr gchar,
		 flags: gint,
		  mode: gint



;gint
g_file_open_tmp proto __cdecl \
		  tmpl: ptr gchar,
	     name_used: ptr gchar,
		 error: ptr GError

;gchar
g_dir_make_tmp proto __cdecl \
		  tmpl: ptr gchar,
		 error: ptr GError


;gchar
g_build_path proto _CDecl \
	     separator: ptr gchar,
	 first_element: ptr gchar,
		      : vararg

;gchar
g_build_pathv proto __cdecl \
	     separator: ptr gchar,
		  args: ptr gchar


;gchar
g_build_filename proto _CDecl \
	 first_element: ptr gchar,
		      : vararg

;gchar
g_build_filenamev proto __cdecl \
		  args: ptr gchar

;gchar
g_build_filename_valist proto __cdecl \
	 first_element: ptr gchar,
		  args: ptr va_list


;gint
g_mkdir_with_parents proto __cdecl \
	      pathname: ptr gchar,
		  mode: gint


ifdef G_OS_WIN32

G_IS_DIR_SEPARATOR macro c
	exitm<((c) EQ G_DIR_SEPARATOR OR (c) EQ '/')>
	endm

else

G_IS_DIR_SEPARATOR macro c
	exitm<((c) EQ G_DIR_SEPARATOR)>
	endm

endif

;gboolean
g_path_is_absolute proto __cdecl \
	     file_name: ptr gchar

;const
g_path_skip_root proto __cdecl \
	     file_name: ptr gchar


g_basename proto __cdecl \
	     file_name: ptr gchar

g_dirname equ <g_path_get_dirname>

;gchar
g_get_current_dir proto __cdecl
;gchar
g_path_get_basename proto __cdecl \
	     file_name: ptr gchar

;gchar
g_path_get_dirname proto __cdecl \
	     file_name: ptr gchar


;gchar
g_canonicalize_filename proto __cdecl \
	      filename: ptr gchar,
	   relative_to: ptr gchar

endif
