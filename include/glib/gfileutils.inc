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

g_file_error_quark proto __cdecl
g_file_error_from_errno proto __cdecl :gint
g_file_test proto __cdecl :ptr, :GFileTest
g_file_get_contents proto __cdecl :ptr, :ptr, :ptr, :ptr
g_file_set_contents proto __cdecl :ptr, :ptr, :gssize, :ptr
g_file_set_contents_full proto __cdecl :ptr, :ptr, :gssize, :GFileSetContentsFlags, :SINT, :ptr
g_file_read_link proto __cdecl :ptr, :ptr
g_mkdtemp proto __cdecl :ptr
g_mkdtemp_full proto __cdecl :ptr, :gint
g_mkstemp proto __cdecl :ptr
g_mkstemp_full proto __cdecl :ptr, :gint, :gint
g_file_open_tmp proto __cdecl :ptr, :ptr, :ptr
g_dir_make_tmp proto __cdecl :ptr, :ptr
g_build_path proto __Cdecl :ptr, :ptr, :vararg
g_build_pathv proto __cdecl :ptr, :ptr
g_build_filename proto __Cdecl :ptr, :vararg
g_build_filenamev proto __cdecl :ptr
g_build_filename_valist proto __cdecl :ptr, :ptr
g_mkdir_with_parents proto __cdecl :ptr, :gint

ifdef G_OS_WIN32

G_IS_DIR_SEPARATOR macro c
	exitm<((c) EQ G_DIR_SEPARATOR OR (c) EQ '/')>
	endm

else

G_IS_DIR_SEPARATOR macro c
	exitm<((c) EQ G_DIR_SEPARATOR)>
	endm

endif

g_path_is_absolute proto __cdecl :ptr
g_path_skip_root proto __cdecl :ptr
g_basename proto __cdecl :ptr

g_dirname equ <g_path_get_dirname>

g_get_current_dir proto __cdecl
g_path_get_basename proto __cdecl :ptr
g_path_get_dirname proto __cdecl :ptr
g_canonicalize_filename proto __cdecl :ptr, :ptr

endif
