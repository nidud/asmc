;
; DOS and OS/2 Compatible Error Code definitions returned by the Win32 Base
; API functions.
;
.xlist

ifndef _WINERROR_
_WINERROR_ equ 1


;;
;;  Values are 32 bit values layed out as follows:
;;
;;   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;  +---+-+-+-----------------------+-------------------------------+
;;  |Sev|C|R|	  Facility	    |		    Code	    |
;;  +---+-+-+-----------------------+-------------------------------+
;;
;;  where
;;
;;	Sev - is the severity code
;;
;;	    00 - Success
;;	    01 - Informational
;;	    10 - Warning
;;	    11 - Error
;;
;;	C - is the Customer code flag
;;
;;	R - is a reserved bit
;;
;;	Facility - is the facility code
;;
;;	Code - is the facility's status code
;;
;;
;; Define the facility codes
;;
FACILITY_WINDOWS	equ 8
FACILITY_STORAGE	equ 3
FACILITY_SSPI		equ 9
FACILITY_SETUPAPI	equ 15
FACILITY_RPC		equ 1
FACILITY_WIN32		equ 7
FACILITY_CONTROL	equ 10
FACILITY_NULL		equ 0
FACILITY_MSMQ		equ 14
FACILITY_MEDIASERVER	equ 13
FACILITY_INTERNET	equ 12
FACILITY_ITF		equ 4
FACILITY_DISPATCH	equ 2
FACILITY_CERT		equ 11


;;
;; Define the severity codes
;;


;;
;; MessageId: ERROR_SUCCESS
;;
;; MessageText:
;;
;;  The operation completed successfully.
;;
ERROR_SUCCESS	equ 0

NO_ERROR	equ 0 ; dderror

;;
;; MessageId: ERROR_INVALID_FUNCTION
;;
;; MessageText:
;;
;;  Incorrect function.
;;
ERROR_INVALID_FUNCTION	equ 1 ; dderror

;;
;; MessageId: ERROR_FILE_NOT_FOUND
;;
;; MessageText:
;;
;;  The system cannot find the file specified.
;;
ERROR_FILE_NOT_FOUND	equ 2

;;
;; MessageId: ERROR_PATH_NOT_FOUND
;;
;; MessageText:
;;
;;  The system cannot find the path specified.
;;
ERROR_PATH_NOT_FOUND equ 3

;;
;; MessageId: ERROR_TOO_MANY_OPEN_FILES
;;
;; MessageText:
;;
;;  The system cannot open the file.
;;
ERROR_TOO_MANY_OPEN_FILES equ 4

;;
;; MessageId: ERROR_ACCESS_DENIED
;;
;; MessageText:
;;
;;  Access is denied.
;;
ERROR_ACCESS_DENIED equ 5

;;
;; MessageId: ERROR_INVALID_HANDLE
;;
;; MessageText:
;;
;;  The handle is invalid.
;;
ERROR_INVALID_HANDLE	equ 6

;;
;; MessageId: ERROR_ARENA_TRASHED
;;
;; MessageText:
;;
;;  The storage control blocks were destroyed.
;;
ERROR_ARENA_TRASHED	equ 7

;;
;; MessageId: ERROR_NOT_ENOUGH_MEMORY
;;
;; MessageText:
;;
;;  Not enough storage is available to process this command.
;;
ERROR_NOT_ENOUGH_MEMORY equ 8	 ;; dderror

;;
;; MessageId: ERROR_INVALID_BLOCK
;;
;; MessageText:
;;
;;  The storage control block address is invalid.
;;
ERROR_INVALID_BLOCK	equ 9

;;
;; MessageId: ERROR_BAD_ENVIRONMENT
;;
;; MessageText:
;;
;;  The environment is incorrect.
;;
ERROR_BAD_ENVIRONMENT	equ 10

;;
;; MessageId: ERROR_BAD_FORMAT
;;
;; MessageText:
;;
;;  An attempt was made to load a program with an
;;  incorrect format.
;;
ERROR_BAD_FORMAT	equ 11

;;
;; MessageId: ERROR_INVALID_ACCESS
;;
;; MessageText:
;;
;;  The access code is invalid.
;;
ERROR_INVALID_ACCESS	equ 12

;;
;; MessageId: ERROR_INVALID_DATA
;;
;; MessageText:
;;
;;  The data is invalid.
;;
ERROR_INVALID_DATA	equ 13

;;
;; MessageId: ERROR_OUTOFMEMORY
;;
;; MessageText:
;;
;;  Not enough storage is available to complete this operation.
;;
ERROR_OUTOFMEMORY	equ 14

;;
;; MessageId: ERROR_INVALID_DRIVE
;;
;; MessageText:
;;
;;  The system cannot find the drive specified.
;;
ERROR_INVALID_DRIVE	equ 15

;;
;; MessageId: ERROR_CURRENT_DIRECTORY
;;
;; MessageText:
;;
;;  The directory cannot be removed.
;;
ERROR_CURRENT_DIRECTORY equ 16

;;
;; MessageId: ERROR_NOT_SAME_DEVICE
;;
;; MessageText:
;;
;;  The system cannot move the file
;;  to a different disk drive.
;;
ERROR_NOT_SAME_DEVICE	equ 17

;;
;; MessageId: ERROR_NO_MORE_FILES
;;
;; MessageText:
;;
;;  There are no more files.
;;
ERROR_NO_MORE_FILES	equ 18

;;
;; MessageId: ERROR_WRITE_PROTECT
;;
;; MessageText:
;;
;;  The media is write protected.
;;
ERROR_WRITE_PROTECT	equ 19

;;
;; MessageId: ERROR_BAD_UNIT
;;
;; MessageText:
;;
;;  The system cannot find the device specified.
;;
ERROR_BAD_UNIT	equ 20

;;
;; MessageId: ERROR_NOT_READY
;;
;; MessageText:
;;
;;  The device is not ready.
;;
ERROR_NOT_READY equ 21

;;
;; MessageId: ERROR_BAD_COMMAND
;;
;; MessageText:
;;
;;  The device does not recognize the command.
;;
ERROR_BAD_COMMAND	equ 22

;;
;; MessageId: ERROR_CRC
;;
;; MessageText:
;;
;;  Data error (cyclic redundancy check).
;;
ERROR_CRC	equ 23

;;
;; MessageId: ERROR_BAD_LENGTH
;;
;; MessageText:
;;
;;  The program issued a command but the
;;  command length is incorrect.
;;
ERROR_BAD_LENGTH	equ 24

;;
;; MessageId: ERROR_SEEK
;;
;; MessageText:
;;
;;  The drive cannot locate a specific
;;  area or track on the disk.
;;
ERROR_SEEK	equ 25

;;
;; MessageId: ERROR_NOT_DOS_DISK
;;
;; MessageText:
;;
;;  The specified disk or diskette cannot be accessed.
;;
ERROR_NOT_DOS_DISK	equ 26

;;
;; MessageId: ERROR_SECTOR_NOT_FOUND
;;
;; MessageText:
;;
;;  The drive cannot find the sector requested.
;;
ERROR_SECTOR_NOT_FOUND	equ 27

;;
;; MessageId: ERROR_OUT_OF_PAPER
;;
;; MessageText:
;;
;;  The printer is out of paper.
;;
ERROR_OUT_OF_PAPER	equ 28

;;
;; MessageId: ERROR_WRITE_FAULT
;;
;; MessageText:
;;
;;  The system cannot write to the specified device.
;;
ERROR_WRITE_FAULT	equ 29

;;
;; MessageId: ERROR_READ_FAULT
;;
;; MessageText:
;;
;;  The system cannot read from the specified device.
;;
ERROR_READ_FAULT	equ 30

;;
;; MessageId: ERROR_GEN_FAILURE
;;
;; MessageText:
;;
;;  A device attached to the system is not functioning.
;;
ERROR_GEN_FAILURE	equ 31

;;
;; MessageId: ERROR_SHARING_VIOLATION
;;
;; MessageText:
;;
;;  The process cannot access the file because
;;  it is being used by another process.
;;
ERROR_SHARING_VIOLATION equ 32

;;
;; MessageId: ERROR_LOCK_VIOLATION
;;
;; MessageText:
;;
;;  The process cannot access the file because
;;  another process has locked a portion of the file.
;;
ERROR_LOCK_VIOLATION	equ 33

;;
;; MessageId: ERROR_WRONG_DISK
;;
;; MessageText:
;;
;;  The wrong diskette is in the drive.
;;  Insert %2 (Volume Serial Number: %3)
;;  into drive %1.
;;
ERROR_WRONG_DISK	equ 34

;;
;; MessageId: ERROR_SHARING_BUFFER_EXCEEDED
;;
;; MessageText:
;;
;;  Too many files opened for sharing.
;;
ERROR_SHARING_BUFFER_EXCEEDED	equ 36

;;
;; MessageId: ERROR_HANDLE_EOF
;;
;; MessageText:
;;
;;  Reached the end of the file.
;;
ERROR_HANDLE_EOF	equ 38

;;
;; MessageId: ERROR_HANDLE_DISK_FULL
;;
;; MessageText:
;;
;;  The disk is full.
;;
ERROR_HANDLE_DISK_FULL	equ 39

;;
;; MessageId: ERROR_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The network request is not supported.
;;
ERROR_NOT_SUPPORTED	equ 50

;;
;; MessageId: ERROR_REM_NOT_LIST
;;
;; MessageText:
;;
;;  The remote computer is not available.
;;
ERROR_REM_NOT_LIST	equ 51

;;
;; MessageId: ERROR_DUP_NAME
;;
;; MessageText:
;;
;;  A duplicate name exists on the network.
;;
ERROR_DUP_NAME	equ 52

;;
;; MessageId: ERROR_BAD_NETPATH
;;
;; MessageText:
;;
;;  The network path was not found.
;;
ERROR_BAD_NETPATH	equ 53

;;
;; MessageId: ERROR_NETWORK_BUSY
;;
;; MessageText:
;;
;;  The network is busy.
;;
ERROR_NETWORK_BUSY	equ 54

;;
;; MessageId: ERROR_DEV_NOT_EXIST
;;
;; MessageText:
;;
;;  The specified network resource or device is no longer
;;  available.
;;
ERROR_DEV_NOT_EXIST	equ 55	  ;; dderror

;;
;; MessageId: ERROR_TOO_MANY_CMDS
;;
;; MessageText:
;;
;;  The network BIOS command limit has been reached.
;;
ERROR_TOO_MANY_CMDS	equ 56

;;
;; MessageId: ERROR_ADAP_HDW_ERR
;;
;; MessageText:
;;
;;  A network adapter hardware error occurred.
;;
ERROR_ADAP_HDW_ERR	equ 57

;;
;; MessageId: ERROR_BAD_NET_RESP
;;
;; MessageText:
;;
;;  The specified server cannot perform the requested
;;  operation.
;;
ERROR_BAD_NET_RESP	equ 58

;;
;; MessageId: ERROR_UNEXP_NET_ERR
;;
;; MessageText:
;;
;;  An unexpected network error occurred.
;;
ERROR_UNEXP_NET_ERR	equ 59

;;
;; MessageId: ERROR_BAD_REM_ADAP
;;
;; MessageText:
;;
;;  The remote adapter is not compatible.
;;
ERROR_BAD_REM_ADAP	equ 60

;;
;; MessageId: ERROR_PRINTQ_FULL
;;
;; MessageText:
;;
;;  The printer queue is full.
;;
ERROR_PRINTQ_FULL	equ 61

;;
;; MessageId: ERROR_NO_SPOOL_SPACE
;;
;; MessageText:
;;
;;  Space to store the file waiting to be printed is
;;  not available on the server.
;;
ERROR_NO_SPOOL_SPACE	equ 62

;;
;; MessageId: ERROR_PRINT_CANCELLED
;;
;; MessageText:
;;
;;  Your file waiting to be printed was deleted.
;;
ERROR_PRINT_CANCELLED	equ 63

;;
;; MessageId: ERROR_NETNAME_DELETED
;;
;; MessageText:
;;
;;  The specified network name is no longer available.
;;
ERROR_NETNAME_DELETED	equ 64

;;
;; MessageId: ERROR_NETWORK_ACCESS_DENIED
;;
;; MessageText:
;;
;;  Network access is denied.
;;
ERROR_NETWORK_ACCESS_DENIED	equ 65

;;
;; MessageId: ERROR_BAD_DEV_TYPE
;;
;; MessageText:
;;
;;  The network resource type is not correct.
;;
ERROR_BAD_DEV_TYPE	equ 66

;;
;; MessageId: ERROR_BAD_NET_NAME
;;
;; MessageText:
;;
;;  The network name cannot be found.
;;
ERROR_BAD_NET_NAME	equ 67

;;
;; MessageId: ERROR_TOO_MANY_NAMES
;;
;; MessageText:
;;
;;  The name limit for the local computer network
;;  adapter card was exceeded.
;;
ERROR_TOO_MANY_NAMES	equ 68

;;
;; MessageId: ERROR_TOO_MANY_SESS
;;
;; MessageText:
;;
;;  The network BIOS session limit was exceeded.
;;
ERROR_TOO_MANY_SESS	equ 69

;;
;; MessageId: ERROR_SHARING_PAUSED
;;
;; MessageText:
;;
;;  The remote server has been paused or is in the
;;  process of being started.
;;
ERROR_SHARING_PAUSED	equ 70

;;
;; MessageId: ERROR_REQ_NOT_ACCEP
;;
;; MessageText:
;;
;;  No more connections can be made to this remote computer at this time
;;  because there are already as many connections as the computer can accept.
;;
ERROR_REQ_NOT_ACCEP	equ 71

;;
;; MessageId: ERROR_REDIR_PAUSED
;;
;; MessageText:
;;
;;  The specified printer or disk device has been paused.
;;
ERROR_REDIR_PAUSED	equ 72

;;
;; MessageId: ERROR_FILE_EXISTS
;;
;; MessageText:
;;
;;  The file exists.
;;
ERROR_FILE_EXISTS	equ 80

;;
;; MessageId: ERROR_CANNOT_MAKE
;;
;; MessageText:
;;
;;  The directory or file cannot be created.
;;
ERROR_CANNOT_MAKE	equ 82

;;
;; MessageId: ERROR_FAIL_I24
;;
;; MessageText:
;;
;;  Fail on INT 24.
;;
ERROR_FAIL_I24	equ 83

;;
;; MessageId: ERROR_OUT_OF_STRUCTURES
;;
;; MessageText:
;;
;;  Storage to process this request is not available.
;;
ERROR_OUT_OF_STRUCTURES equ 84

;;
;; MessageId: ERROR_ALREADY_ASSIGNED
;;
;; MessageText:
;;
;;  The local device name is already in use.
;;
ERROR_ALREADY_ASSIGNED	equ 85

;;
;; MessageId: ERROR_INVALID_PASSWORD
;;
;; MessageText:
;;
;;  The specified network password is not correct.
;;
ERROR_INVALID_PASSWORD	equ 86

;;
;; MessageId: ERROR_INVALID_PARAMETER
;;
;; MessageText:
;;
;;  The parameter is incorrect.
;;
ERROR_INVALID_PARAMETER equ 87	  ;; dderror

;;
;; MessageId: ERROR_NET_WRITE_FAULT
;;
;; MessageText:
;;
;;  A write fault occurred on the network.
;;
ERROR_NET_WRITE_FAULT	equ 88

;;
;; MessageId: ERROR_NO_PROC_SLOTS
;;
;; MessageText:
;;
;;  The system cannot start another process at
;;  this time.
;;
ERROR_NO_PROC_SLOTS	equ 89

;;
;; MessageId: ERROR_TOO_MANY_SEMAPHORES
;;
;; MessageText:
;;
;;  Cannot create another system semaphore.
;;
ERROR_TOO_MANY_SEMAPHORES	equ 100

;;
;; MessageId: ERROR_EXCL_SEM_ALREADY_OWNED
;;
;; MessageText:
;;
;;  The exclusive semaphore is owned by another process.
;;
ERROR_EXCL_SEM_ALREADY_OWNED	equ 101

;;
;; MessageId: ERROR_SEM_IS_SET
;;
;; MessageText:
;;
;;  The semaphore is set and cannot be closed.
;;
ERROR_SEM_IS_SET	equ 102

;;
;; MessageId: ERROR_TOO_MANY_SEM_REQUESTS
;;
;; MessageText:
;;
;;  The semaphore cannot be set again.
;;
ERROR_TOO_MANY_SEM_REQUESTS	equ 103

;;
;; MessageId: ERROR_INVALID_AT_INTERRUPT_TIME
;;
;; MessageText:
;;
;;  Cannot request exclusive semaphores at interrupt time.
;;
ERROR_INVALID_AT_INTERRUPT_TIME equ 104

;;
;; MessageId: ERROR_SEM_OWNER_DIED
;;
;; MessageText:
;;
;;  The previous ownership of this semaphore has ended.
;;
ERROR_SEM_OWNER_DIED	equ 105

;;
;; MessageId: ERROR_SEM_USER_LIMIT
;;
;; MessageText:
;;
;;  Insert the diskette for drive %1.
;;
ERROR_SEM_USER_LIMIT	equ 106

;;
;; MessageId: ERROR_DISK_CHANGE
;;
;; MessageText:
;;
;;  The program stopped because an alternate diskette was not inserted.
;;
ERROR_DISK_CHANGE	equ 107

;;
;; MessageId: ERROR_DRIVE_LOCKED
;;
;; MessageText:
;;
;;  The disk is in use or locked by
;;  another process.
;;
ERROR_DRIVE_LOCKED	equ 108

;;
;; MessageId: ERROR_BROKEN_PIPE
;;
;; MessageText:
;;
;;  The pipe has been ended.
;;
ERROR_BROKEN_PIPE	equ 109

;;
;; MessageId: ERROR_OPEN_FAILED
;;
;; MessageText:
;;
;;  The system cannot open the
;;  device or file specified.
;;
ERROR_OPEN_FAILED	equ 110

;;
;; MessageId: ERROR_BUFFER_OVERFLOW
;;
;; MessageText:
;;
;;  The file name is too long.
;;
ERROR_BUFFER_OVERFLOW	equ 111

;;
;; MessageId: ERROR_DISK_FULL
;;
;; MessageText:
;;
;;  There is not enough space on the disk.
;;
ERROR_DISK_FULL equ 112

;;
;; MessageId: ERROR_NO_MORE_SEARCH_HANDLES
;;
;; MessageText:
;;
;;  No more internal file identifiers available.
;;
ERROR_NO_MORE_SEARCH_HANDLES	equ 113

;;
;; MessageId: ERROR_INVALID_TARGET_HANDLE
;;
;; MessageText:
;;
;;  The target internal file identifier is incorrect.
;;
ERROR_INVALID_TARGET_HANDLE	equ 114

;;
;; MessageId: ERROR_INVALID_CATEGORY
;;
;; MessageText:
;;
;;  The IOCTL call made by the application program is
;;  not correct.
;;
ERROR_INVALID_CATEGORY	equ 117

;;
;; MessageId: ERROR_INVALID_VERIFY_SWITCH
;;
;; MessageText:
;;
;;  The verify-on-write switch parameter value is not
;;  correct.
;;
ERROR_INVALID_VERIFY_SWITCH	equ 118

;;
;; MessageId: ERROR_BAD_DRIVER_LEVEL
;;
;; MessageText:
;;
;;  The system does not support the command requested.
;;
ERROR_BAD_DRIVER_LEVEL	equ 119

;;
;; MessageId: ERROR_CALL_NOT_IMPLEMENTED
;;
;; MessageText:
;;
;;  This function is not supported on this system.
;;
ERROR_CALL_NOT_IMPLEMENTED	equ 120

;;
;; MessageId: ERROR_SEM_TIMEOUT
;;
;; MessageText:
;;
;;  The semaphore timeout period has expired.
;;
ERROR_SEM_TIMEOUT	equ 121

;;
;; MessageId: ERROR_INSUFFICIENT_BUFFER
;;
;; MessageText:
;;
;;  The data area passed to a system call is too
;;  small.
;;
ERROR_INSUFFICIENT_BUFFER	equ 122	   ;; dderror

;;
;; MessageId: ERROR_INVALID_NAME
;;
;; MessageText:
;;
;;  The filename, directory name, or volume label syntax is incorrect.
;;
ERROR_INVALID_NAME	equ 123

;;
;; MessageId: ERROR_INVALID_LEVEL
;;
;; MessageText:
;;
;;  The system call level is not correct.
;;
ERROR_INVALID_LEVEL	equ 124

;;
;; MessageId: ERROR_NO_VOLUME_LABEL
;;
;; MessageText:
;;
;;  The disk has no volume label.
;;
ERROR_NO_VOLUME_LABEL	equ 125

;;
;; MessageId: ERROR_MOD_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified module could not be found.
;;
ERROR_MOD_NOT_FOUND	equ 126

;;
;; MessageId: ERROR_PROC_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified procedure could not be found.
;;
ERROR_PROC_NOT_FOUND	equ 127

;;
;; MessageId: ERROR_WAIT_NO_CHILDREN
;;
;; MessageText:
;;
;;  There are no child processes to wait for.
;;
ERROR_WAIT_NO_CHILDREN	equ 128

;;
;; MessageId: ERROR_CHILD_NOT_COMPLETE
;;
;; MessageText:
;;
;;  The %1 application cannot be run in Win32 mode.
;;
ERROR_CHILD_NOT_COMPLETE	equ 129

;;
;; MessageId: ERROR_DIRECT_ACCESS_HANDLE
;;
;; MessageText:
;;
;;  Attempt to use a file handle to an open disk partition for an
;;  operation other than raw disk I/O.
;;
ERROR_DIRECT_ACCESS_HANDLE	equ 130

;;
;; MessageId: ERROR_NEGATIVE_SEEK
;;
;; MessageText:
;;
;;  An attempt was made to move the file pointer before the beginning of the file.
;;
ERROR_NEGATIVE_SEEK	equ 131

;;
;; MessageId: ERROR_SEEK_ON_DEVICE
;;
;; MessageText:
;;
;;  The file pointer cannot be set on the specified device or file.
;;
ERROR_SEEK_ON_DEVICE	equ 132

;;
;; MessageId: ERROR_IS_JOIN_TARGET
;;
;; MessageText:
;;
;;  A JOIN or SUBST command
;;  cannot be used for a drive that
;;  contains previously joined drives.
;;
ERROR_IS_JOIN_TARGET	equ 133

;;
;; MessageId: ERROR_IS_JOINED
;;
;; MessageText:
;;
;;  An attempt was made to use a
;;  JOIN or SUBST command on a drive that has
;;  already been joined.
;;
ERROR_IS_JOINED equ 134

;;
;; MessageId: ERROR_IS_SUBSTED
;;
;; MessageText:
;;
;;  An attempt was made to use a
;;  JOIN or SUBST command on a drive that has
;;  already been substituted.
;;
ERROR_IS_SUBSTED	equ 135

;;
;; MessageId: ERROR_NOT_JOINED
;;
;; MessageText:
;;
;;  The system tried to delete
;;  the JOIN of a drive that is not joined.
;;
ERROR_NOT_JOINED	equ 136

;;
;; MessageId: ERROR_NOT_SUBSTED
;;
;; MessageText:
;;
;;  The system tried to delete the
;;  substitution of a drive that is not substituted.
;;
ERROR_NOT_SUBSTED	equ 137

;;
;; MessageId: ERROR_JOIN_TO_JOIN
;;
;; MessageText:
;;
;;  The system tried to join a drive
;;  to a directory on a joined drive.
;;
ERROR_JOIN_TO_JOIN	equ 138

;;
;; MessageId: ERROR_SUBST_TO_SUBST
;;
;; MessageText:
;;
;;  The system tried to substitute a
;;  drive to a directory on a substituted drive.
;;
ERROR_SUBST_TO_SUBST	equ 139

;;
;; MessageId: ERROR_JOIN_TO_SUBST
;;
;; MessageText:
;;
;;  The system tried to join a drive to
;;  a directory on a substituted drive.
;;
ERROR_JOIN_TO_SUBST	equ 140

;;
;; MessageId: ERROR_SUBST_TO_JOIN
;;
;; MessageText:
;;
;;  The system tried to SUBST a drive
;;  to a directory on a joined drive.
;;
ERROR_SUBST_TO_JOIN	equ 141

;;
;; MessageId: ERROR_BUSY_DRIVE
;;
;; MessageText:
;;
;;  The system cannot perform a JOIN or SUBST at this time.
;;
ERROR_BUSY_DRIVE	equ 142

;;
;; MessageId: ERROR_SAME_DRIVE
;;
;; MessageText:
;;
;;  The system cannot join or substitute a
;;  drive to or for a directory on the same drive.
;;
ERROR_SAME_DRIVE	equ 143

;;
;; MessageId: ERROR_DIR_NOT_ROOT
;;
;; MessageText:
;;
;;  The directory is not a subdirectory of the root directory.
;;
ERROR_DIR_NOT_ROOT	equ 144

;;
;; MessageId: ERROR_DIR_NOT_EMPTY
;;
;; MessageText:
;;
;;  The directory is not empty.
;;
ERROR_DIR_NOT_EMPTY	equ 145

;;
;; MessageId: ERROR_IS_SUBST_PATH
;;
;; MessageText:
;;
;;  The path specified is being used in
;;  a substitute.
;;
ERROR_IS_SUBST_PATH	equ 146

;;
;; MessageId: ERROR_IS_JOIN_PATH
;;
;; MessageText:
;;
;;  Not enough resources are available to
;;  process this command.
;;
ERROR_IS_JOIN_PATH	equ 147

;;
;; MessageId: ERROR_PATH_BUSY
;;
;; MessageText:
;;
;;  The path specified cannot be used at this time.
;;
ERROR_PATH_BUSY equ 148

;;
;; MessageId: ERROR_IS_SUBST_TARGET
;;
;; MessageText:
;;
;;  An attempt was made to join
;;  or substitute a drive for which a directory
;;  on the drive is the target of a previous
;;  substitute.
;;
ERROR_IS_SUBST_TARGET	equ 149

;;
;; MessageId: ERROR_SYSTEM_TRACE
;;
;; MessageText:
;;
;;  System trace information was not specified in your
;;  CONFIG.SYS file, or tracing is disallowed.
;;
ERROR_SYSTEM_TRACE	equ 150

;;
;; MessageId: ERROR_INVALID_EVENT_COUNT
;;
;; MessageText:
;;
;;  The number of specified semaphore events for
;;  DosMuxSemWait is not correct.
;;
ERROR_INVALID_EVENT_COUNT	equ 151

;;
;; MessageId: ERROR_TOO_MANY_MUXWAITERS
;;
;; MessageText:
;;
;;  DosMuxSemWait did not execute; too many semaphores
;;  are already set.
;;
ERROR_TOO_MANY_MUXWAITERS	equ 152

;;
;; MessageId: ERROR_INVALID_LIST_FORMAT
;;
;; MessageText:
;;
;;  The DosMuxSemWait list is not correct.
;;
ERROR_INVALID_LIST_FORMAT	equ 153

;;
;; MessageId: ERROR_LABEL_TOO_LONG
;;
;; MessageText:
;;
;;  The volume label you entered exceeds the label character
;;  limit of the target file system.
;;
ERROR_LABEL_TOO_LONG	equ 154

;;
;; MessageId: ERROR_TOO_MANY_TCBS
;;
;; MessageText:
;;
;;  Cannot create another thread.
;;
ERROR_TOO_MANY_TCBS	equ 155

;;
;; MessageId: ERROR_SIGNAL_REFUSED
;;
;; MessageText:
;;
;;  The recipient process has refused the signal.
;;
ERROR_SIGNAL_REFUSED	equ 156

;;
;; MessageId: ERROR_DISCARDED
;;
;; MessageText:
;;
;;  The segment is already discarded and cannot be locked.
;;
ERROR_DISCARDED equ 157

;;
;; MessageId: ERROR_NOT_LOCKED
;;
;; MessageText:
;;
;;  The segment is already unlocked.
;;
ERROR_NOT_LOCKED	equ 158

;;
;; MessageId: ERROR_BAD_THREADID_ADDR
;;
;; MessageText:
;;
;;  The address for the thread ID is not correct.
;;
ERROR_BAD_THREADID_ADDR equ 159

;;
;; MessageId: ERROR_BAD_ARGUMENTS
;;
;; MessageText:
;;
;;  The argument string passed to DosExecPgm is not correct.
;;
ERROR_BAD_ARGUMENTS	equ 160

;;
;; MessageId: ERROR_BAD_PATHNAME
;;
;; MessageText:
;;
;;  The specified path is invalid.
;;
ERROR_BAD_PATHNAME	equ 161

;;
;; MessageId: ERROR_SIGNAL_PENDING
;;
;; MessageText:
;;
;;  A signal is already pending.
;;
ERROR_SIGNAL_PENDING	equ 162

;;
;; MessageId: ERROR_MAX_THRDS_REACHED
;;
;; MessageText:
;;
;;  No more threads can be created in the system.
;;
ERROR_MAX_THRDS_REACHED equ 164

;;
;; MessageId: ERROR_LOCK_FAILED
;;
;; MessageText:
;;
;;  Unable to lock a region of a file.
;;
ERROR_LOCK_FAILED	equ 167

;;
;; MessageId: ERROR_BUSY
;;
;; MessageText:
;;
;;  The requested resource is in use.
;;
ERROR_BUSY	equ 170

;;
;; MessageId: ERROR_CANCEL_VIOLATION
;;
;; MessageText:
;;
;;  A lock request was not outstanding for the supplied cancel region.
;;
ERROR_CANCEL_VIOLATION	equ 173

;;
;; MessageId: ERROR_ATOMIC_LOCKS_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The file system does not support atomic changes to the lock type.
;;
ERROR_ATOMIC_LOCKS_NOT_SUPPORTED	equ 174

;;
;; MessageId: ERROR_INVALID_SEGMENT_NUMBER
;;
;; MessageText:
;;
;;  The system detected a segment number that was not correct.
;;
ERROR_INVALID_SEGMENT_NUMBER	equ 180

;;
;; MessageId: ERROR_INVALID_ORDINAL
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_INVALID_ORDINAL	equ 182

;;
;; MessageId: ERROR_ALREADY_EXISTS
;;
;; MessageText:
;;
;;  Cannot create a file when that file already exists.
;;
ERROR_ALREADY_EXISTS	equ 183

;;
;; MessageId: ERROR_INVALID_FLAG_NUMBER
;;
;; MessageText:
;;
;;  The flag passed is not correct.
;;
ERROR_INVALID_FLAG_NUMBER	equ 186

;;
;; MessageId: ERROR_SEM_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified system semaphore name was not found.
;;
ERROR_SEM_NOT_FOUND	equ 187

;;
;; MessageId: ERROR_INVALID_STARTING_CODESEG
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_INVALID_STARTING_CODESEG	equ 188

;;
;; MessageId: ERROR_INVALID_STACKSEG
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_INVALID_STACKSEG	equ 189

;;
;; MessageId: ERROR_INVALID_MODULETYPE
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_INVALID_MODULETYPE	equ 190

;;
;; MessageId: ERROR_INVALID_EXE_SIGNATURE
;;
;; MessageText:
;;
;;  Cannot run %1 in Win32 mode.
;;
ERROR_INVALID_EXE_SIGNATURE	equ 191

;;
;; MessageId: ERROR_EXE_MARKED_INVALID
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_EXE_MARKED_INVALID	equ 192

;;
;; MessageId: ERROR_BAD_EXE_FORMAT
;;
;; MessageText:
;;
;;  %1 is not a valid Win32 application.
;;
ERROR_BAD_EXE_FORMAT	equ 193

;;
;; MessageId: ERROR_ITERATED_DATA_EXCEEDS_64k
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_ITERATED_DATA_EXCEEDS_64k equ 194

;;
;; MessageId: ERROR_INVALID_MINALLOCSIZE
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_INVALID_MINALLOCSIZE	equ 195

;;
;; MessageId: ERROR_DYNLINK_FROM_INVALID_RING
;;
;; MessageText:
;;
;;  The operating system cannot run this
;;  application program.
;;
ERROR_DYNLINK_FROM_INVALID_RING equ 196

;;
;; MessageId: ERROR_IOPL_NOT_ENABLED
;;
;; MessageText:
;;
;;  The operating system is not presently
;;  configured to run this application.
;;
ERROR_IOPL_NOT_ENABLED	equ 197

;;
;; MessageId: ERROR_INVALID_SEGDPL
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_INVALID_SEGDPL	equ 198

;;
;; MessageId: ERROR_AUTODATASEG_EXCEEDS_64k
;;
;; MessageText:
;;
;;  The operating system cannot run this
;;  application program.
;;
ERROR_AUTODATASEG_EXCEEDS_64k	equ 199

;;
;; MessageId: ERROR_RING2SEG_MUST_BE_MOVABLE
;;
;; MessageText:
;;
;;  The code segment cannot be greater than or equal to 64K.
;;
ERROR_RING2SEG_MUST_BE_MOVABLE	equ 200

;;
;; MessageId: ERROR_RELOC_CHAIN_XEEDS_SEGLIM
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_RELOC_CHAIN_XEEDS_SEGLIM	equ 201

;;
;; MessageId: ERROR_INFLOOP_IN_RELOC_CHAIN
;;
;; MessageText:
;;
;;  The operating system cannot run %1.
;;
ERROR_INFLOOP_IN_RELOC_CHAIN	equ 202

;;
;; MessageId: ERROR_ENVVAR_NOT_FOUND
;;
;; MessageText:
;;
;;  The system could not find the environment
;;  option that was entered.
;;
ERROR_ENVVAR_NOT_FOUND	equ 203

;;
;; MessageId: ERROR_NO_SIGNAL_SENT
;;
;; MessageText:
;;
;;  No process in the command subtree has a
;;  signal handler.
;;
ERROR_NO_SIGNAL_SENT	equ 205

;;
;; MessageId: ERROR_FILENAME_EXCED_RANGE
;;
;; MessageText:
;;
;;  The filename or extension is too long.
;;
ERROR_FILENAME_EXCED_RANGE	equ 206

;;
;; MessageId: ERROR_RING2_STACK_IN_USE
;;
;; MessageText:
;;
;;  The ring 2 stack is in use.
;;
ERROR_RING2_STACK_IN_USE	equ 207

;;
;; MessageId: ERROR_META_EXPANSION_TOO_LONG
;;
;; MessageText:
;;
;;  The global filename characters, * or ?, are entered
;;  incorrectly or too many global filename characters are specified.
;;
ERROR_META_EXPANSION_TOO_LONG	equ 208

;;
;; MessageId: ERROR_INVALID_SIGNAL_NUMBER
;;
;; MessageText:
;;
;;  The signal being posted is not correct.
;;
ERROR_INVALID_SIGNAL_NUMBER	equ 209

;;
;; MessageId: ERROR_THREAD_1_INACTIVE
;;
;; MessageText:
;;
;;  The signal handler cannot be set.
;;
ERROR_THREAD_1_INACTIVE equ 210

;;
;; MessageId: ERROR_LOCKED
;;
;; MessageText:
;;
;;  The segment is locked and cannot be reallocated.
;;
ERROR_LOCKED	equ 212

;;
;; MessageId: ERROR_TOO_MANY_MODULES
;;
;; MessageText:
;;
;;  Too many dynamic-link modules are attached to this
;;  program or dynamic-link module.
;;
ERROR_TOO_MANY_MODULES	equ 214

;;
;; MessageId: ERROR_NESTING_NOT_ALLOWED
;;
;; MessageText:
;;
;;  Can't nest calls to LoadModule.
;;
ERROR_NESTING_NOT_ALLOWED	equ 215

;;
;; MessageId: ERROR_EXE_MACHINE_TYPE_MISMATCH
;;
;; MessageText:
;;
;;  The image file %1 is valid, but is for a machine type other
;;  than the current machine.
;;
ERROR_EXE_MACHINE_TYPE_MISMATCH equ 216

;;
;; MessageId: ERROR_BAD_PIPE
;;
;; MessageText:
;;
;;  The pipe state is invalid.
;;
ERROR_BAD_PIPE	equ 230

;;
;; MessageId: ERROR_PIPE_BUSY
;;
;; MessageText:
;;
;;  All pipe instances are busy.
;;
ERROR_PIPE_BUSY equ 231

;;
;; MessageId: ERROR_NO_DATA
;;
;; MessageText:
;;
;;  The pipe is being closed.
;;
ERROR_NO_DATA	equ 232

;;
;; MessageId: ERROR_PIPE_NOT_CONNECTED
;;
;; MessageText:
;;
;;  No process is on the other end of the pipe.
;;
ERROR_PIPE_NOT_CONNECTED	equ 233

;;
;; MessageId: ERROR_MORE_DATA
;;
;; MessageText:
;;
;;  More data is available.
;;
ERROR_MORE_DATA equ 234	   ;; dderror

;;
;; MessageId: ERROR_VC_DISCONNECTED
;;
;; MessageText:
;;
;;  The session was canceled.
;;
ERROR_VC_DISCONNECTED	equ 240

;;
;; MessageId: ERROR_INVALID_EA_NAME
;;
;; MessageText:
;;
;;  The specified extended attribute name was invalid.
;;
ERROR_INVALID_EA_NAME	equ 254

;;
;; MessageId: ERROR_EA_LIST_INCONSISTENT
;;
;; MessageText:
;;
;;  The extended attributes are inconsistent.
;;
ERROR_EA_LIST_INCONSISTENT	equ 255

;;
;; MessageId: ERROR_NO_MORE_ITEMS
;;
;; MessageText:
;;
;;  No more data is available.
;;
ERROR_NO_MORE_ITEMS	equ 259

;;
;; MessageId: ERROR_CANNOT_COPY
;;
;; MessageText:
;;
;;  The copy functions cannot be used.
;;
ERROR_CANNOT_COPY	equ 266

;;
;; MessageId: ERROR_DIRECTORY
;;
;; MessageText:
;;
;;  The directory name is invalid.
;;
ERROR_DIRECTORY equ 267

;;
;; MessageId: ERROR_EAS_DIDNT_FIT
;;
;; MessageText:
;;
;;  The extended attributes did not fit in the buffer.
;;
ERROR_EAS_DIDNT_FIT	equ 275

;;
;; MessageId: ERROR_EA_FILE_CORRUPT
;;
;; MessageText:
;;
;;  The extended attribute file on the mounted file system is corrupt.
;;
ERROR_EA_FILE_CORRUPT	equ 276

;;
;; MessageId: ERROR_EA_TABLE_FULL
;;
;; MessageText:
;;
;;  The extended attribute table file is full.
;;
ERROR_EA_TABLE_FULL	equ 277

;;
;; MessageId: ERROR_INVALID_EA_HANDLE
;;
;; MessageText:
;;
;;  The specified extended attribute handle is invalid.
;;
ERROR_INVALID_EA_HANDLE equ 278

;;
;; MessageId: ERROR_EAS_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The mounted file system does not support extended attributes.
;;
ERROR_EAS_NOT_SUPPORTED equ 282

;;
;; MessageId: ERROR_NOT_OWNER
;;
;; MessageText:
;;
;;  Attempt to release mutex not owned by caller.
;;
ERROR_NOT_OWNER equ 288

;;
;; MessageId: ERROR_TOO_MANY_POSTS
;;
;; MessageText:
;;
;;  Too many posts were made to a semaphore.
;;
ERROR_TOO_MANY_POSTS	equ 298

;;
;; MessageId: ERROR_PARTIAL_COPY
;;
;; MessageText:
;;
;;  Only part of a ReadProcessMemoty or WriteProcessMemory request was completed.
;;
ERROR_PARTIAL_COPY	equ 299

;;
;; MessageId: ERROR_OPLOCK_NOT_GRANTED
;;
;; MessageText:
;;
;;  The oplock request is denied.
;;
ERROR_OPLOCK_NOT_GRANTED	equ 300

;;
;; MessageId: ERROR_INVALID_OPLOCK_PROTOCOL
;;
;; MessageText:
;;
;;  An invalid oplock acknowledgment was received by the system.
;;
ERROR_INVALID_OPLOCK_PROTOCOL	equ 301

;;
;; MessageId: ERROR_MR_MID_NOT_FOUND
;;
;; MessageText:
;;
;;  The system cannot find message text for message number 0x%1
;;  in the message file for %2.
;;
ERROR_MR_MID_NOT_FOUND	equ 317

;;
;; MessageId: ERROR_INVALID_ADDRESS
;;
;; MessageText:
;;
;;  Attempt to access invalid address.
;;
ERROR_INVALID_ADDRESS	equ 487

;;
;; MessageId: ERROR_ARITHMETIC_OVERFLOW
;;
;; MessageText:
;;
;;  Arithmetic result exceeded 32 bits.
;;
ERROR_ARITHMETIC_OVERFLOW	equ 534

;;
;; MessageId: ERROR_PIPE_CONNECTED
;;
;; MessageText:
;;
;;  There is a process on other end of the pipe.
;;
ERROR_PIPE_CONNECTED	equ 535

;;
;; MessageId: ERROR_PIPE_LISTENING
;;
;; MessageText:
;;
;;  Waiting for a process to open the other end of the pipe.
;;
ERROR_PIPE_LISTENING	equ 536

;;
;; MessageId: ERROR_EA_ACCESS_DENIED
;;
;; MessageText:
;;
;;  Access to the extended attribute was denied.
;;
ERROR_EA_ACCESS_DENIED	equ 994

;;
;; MessageId: ERROR_OPERATION_ABORTED
;;
;; MessageText:
;;
;;  The I/O operation has been aborted because of either a thread exit
;;  or an application request.
;;
ERROR_OPERATION_ABORTED equ 995

;;
;; MessageId: ERROR_IO_INCOMPLETE
;;
;; MessageText:
;;
;;  Overlapped I/O event is not in a signaled state.
;;
ERROR_IO_INCOMPLETE	equ 996

;;
;; MessageId: ERROR_IO_PENDING
;;
;; MessageText:
;;
;;  Overlapped I/O operation is in progress.
;;
ERROR_IO_PENDING	equ 997	   ;; dderror

;;
;; MessageId: ERROR_NOACCESS
;;
;; MessageText:
;;
;;  Invalid access to memory location.
;;
ERROR_NOACCESS	equ 998

;;
;; MessageId: ERROR_SWAPERROR
;;
;; MessageText:
;;
;;  Error performing inpage operation.
;;
ERROR_SWAPERROR equ 999

;;
;; MessageId: ERROR_STACK_OVERFLOW
;;
;; MessageText:
;;
;;  Recursion too deep; the stack overflowed.
;;
ERROR_STACK_OVERFLOW	equ 1001

;;
;; MessageId: ERROR_INVALID_MESSAGE
;;
;; MessageText:
;;
;;  The window cannot act on the sent message.
;;
ERROR_INVALID_MESSAGE	equ 1002

;;
;; MessageId: ERROR_CAN_NOT_COMPLETE
;;
;; MessageText:
;;
;;  Cannot complete this function.
;;
ERROR_CAN_NOT_COMPLETE	equ 1003

;;
;; MessageId: ERROR_INVALID_FLAGS
;;
;; MessageText:
;;
;;  Invalid flags.
;;
ERROR_INVALID_FLAGS	equ 1004

;;
;; MessageId: ERROR_UNRECOGNIZED_VOLUME
;;
;; MessageText:
;;
;;  The volume does not contain a recognized file system.
;;  Please make sure that all required file system drivers are loaded and that the
;;  volume is not corrupted.
;;
ERROR_UNRECOGNIZED_VOLUME	equ 1005

;;
;; MessageId: ERROR_FILE_INVALID
;;
;; MessageText:
;;
;;  The volume for a file has been externally altered so that the
;;  opened file is no longer valid.
;;
ERROR_FILE_INVALID	equ 1006

;;
;; MessageId: ERROR_FULLSCREEN_MODE
;;
;; MessageText:
;;
;;  The requested operation cannot be performed in full-screen mode.
;;
ERROR_FULLSCREEN_MODE	equ 1007

;;
;; MessageId: ERROR_NO_TOKEN
;;
;; MessageText:
;;
;;  An attempt was made to reference a token that does not exist.
;;
ERROR_NO_TOKEN	equ 1008

;;
;; MessageId: ERROR_BADDB
;;
;; MessageText:
;;
;;  The configuration registry database is corrupt.
;;
ERROR_BADDB	equ 1009

;;
;; MessageId: ERROR_BADKEY
;;
;; MessageText:
;;
;;  The configuration registry key is invalid.
;;
ERROR_BADKEY	equ 1010

;;
;; MessageId: ERROR_CANTOPEN
;;
;; MessageText:
;;
;;  The configuration registry key could not be opened.
;;
ERROR_CANTOPEN	equ 1011

;;
;; MessageId: ERROR_CANTREAD
;;
;; MessageText:
;;
;;  The configuration registry key could not be read.
;;
ERROR_CANTREAD	equ 1012

;;
;; MessageId: ERROR_CANTWRITE
;;
;; MessageText:
;;
;;  The configuration registry key could not be written.
;;
ERROR_CANTWRITE equ 1013

;;
;; MessageId: ERROR_REGISTRY_RECOVERED
;;
;; MessageText:
;;
;;  One of the files in the registry database had to be recovered
;;  by use of a log or alternate copy.	The recovery was successful.
;;
ERROR_REGISTRY_RECOVERED	equ 1014

;;
;; MessageId: ERROR_REGISTRY_CORRUPT
;;
;; MessageText:
;;
;;  The registry is corrupted. The structure of one of the files that contains
;;  registry data is corrupted, or the system's image of the file in memory
;;  is corrupted, or the file could not be recovered because the alternate
;;  copy or log was absent or corrupted.
;;
ERROR_REGISTRY_CORRUPT	equ 1015

;;
;; MessageId: ERROR_REGISTRY_IO_FAILED
;;
;; MessageText:
;;
;;  An I/O operation initiated by the registry failed unrecoverably.
;;  The registry could not read in, or write out, or flush, one of the files
;;  that contain the system's image of the registry.
;;
ERROR_REGISTRY_IO_FAILED	equ 1016

;;
;; MessageId: ERROR_NOT_REGISTRY_FILE
;;
;; MessageText:
;;
;;  The system has attempted to load or restore a file into the registry, but the
;;  specified file is not in a registry file format.
;;
ERROR_NOT_REGISTRY_FILE equ 1017

;;
;; MessageId: ERROR_KEY_DELETED
;;
;; MessageText:
;;
;;  Illegal operation attempted on a registry key that has been marked for deletion.
;;
ERROR_KEY_DELETED	equ 1018

;;
;; MessageId: ERROR_NO_LOG_SPACE
;;
;; MessageText:
;;
;;  System could not allocate the required space in a registry log.
;;
ERROR_NO_LOG_SPACE	equ 1019

;;
;; MessageId: ERROR_KEY_HAS_CHILDREN
;;
;; MessageText:
;;
;;  Cannot create a symbolic link in a registry key that already
;;  has subkeys or values.
;;
ERROR_KEY_HAS_CHILDREN	equ 1020

;;
;; MessageId: ERROR_CHILD_MUST_BE_VOLATILE
;;
;; MessageText:
;;
;;  Cannot create a stable subkey under a volatile parent key.
;;
ERROR_CHILD_MUST_BE_VOLATILE	equ 1021

;;
;; MessageId: ERROR_NOTIFY_ENUM_DIR
;;
;; MessageText:
;;
;;  A notify change request is being completed and the information
;;  is not being returned in the caller's buffer. The caller now
;;  needs to enumerate the files to find the changes.
;;
ERROR_NOTIFY_ENUM_DIR	equ 1022

;;
;; MessageId: ERROR_DEPENDENT_SERVICES_RUNNING
;;
;; MessageText:
;;
;;  A stop control has been sent to a service that other running services
;;  are dependent on.
;;
ERROR_DEPENDENT_SERVICES_RUNNING	equ 1051

;;
;; MessageId: ERROR_INVALID_SERVICE_CONTROL
;;
;; MessageText:
;;
;;  The requested control is not valid for this service.
;;
ERROR_INVALID_SERVICE_CONTROL	equ 1052

;;
;; MessageId: ERROR_SERVICE_REQUEST_TIMEOUT
;;
;; MessageText:
;;
;;  The service did not respond to the start or control request in a timely
;;  fashion.
;;
ERROR_SERVICE_REQUEST_TIMEOUT	equ 1053

;;
;; MessageId: ERROR_SERVICE_NO_THREAD
;;
;; MessageText:
;;
;;  A thread could not be created for the service.
;;
ERROR_SERVICE_NO_THREAD equ 1054

;;
;; MessageId: ERROR_SERVICE_DATABASE_LOCKED
;;
;; MessageText:
;;
;;  The service database is locked.
;;
ERROR_SERVICE_DATABASE_LOCKED	equ 1055

;;
;; MessageId: ERROR_SERVICE_ALREADY_RUNNING
;;
;; MessageText:
;;
;;  An instance of the service is already running.
;;
ERROR_SERVICE_ALREADY_RUNNING	equ 1056

;;
;; MessageId: ERROR_INVALID_SERVICE_ACCOUNT
;;
;; MessageText:
;;
;;  The account name is invalid or does not exist.
;;
ERROR_INVALID_SERVICE_ACCOUNT	equ 1057

;;
;; MessageId: ERROR_SERVICE_DISABLED
;;
;; MessageText:
;;
;;  The service cannot be started, either because it is disabled or because
;;  it has no enabled devices associated with it.
;;
ERROR_SERVICE_DISABLED	equ 1058

;;
;; MessageId: ERROR_CIRCULAR_DEPENDENCY
;;
;; MessageText:
;;
;;  Circular service dependency was specified.
;;
ERROR_CIRCULAR_DEPENDENCY	equ 1059

;;
;; MessageId: ERROR_SERVICE_DOES_NOT_EXIST
;;
;; MessageText:
;;
;;  The specified service does not exist as an installed service.
;;
ERROR_SERVICE_DOES_NOT_EXIST	equ 1060

;;
;; MessageId: ERROR_SERVICE_CANNOT_ACCEPT_CTRL
;;
;; MessageText:
;;
;;  The service cannot accept control messages at this time.
;;
ERROR_SERVICE_CANNOT_ACCEPT_CTRL	equ 1061

;;
;; MessageId: ERROR_SERVICE_NOT_ACTIVE
;;
;; MessageText:
;;
;;  The service has not been started.
;;
ERROR_SERVICE_NOT_ACTIVE	equ 1062

;;
;; MessageId: ERROR_FAILED_SERVICE_CONTROLLER_CONNECT
;;
;; MessageText:
;;
;;  The service process could not connect to the service controller.
;;
ERROR_FAILED_SERVICE_CONTROLLER_CONNECT equ 1063

;;
;; MessageId: ERROR_EXCEPTION_IN_SERVICE
;;
;; MessageText:
;;
;;  An exception occurred in the service when handling the control request.
;;
ERROR_EXCEPTION_IN_SERVICE	equ 1064

;;
;; MessageId: ERROR_DATABASE_DOES_NOT_EXIST
;;
;; MessageText:
;;
;;  The database specified does not exist.
;;
ERROR_DATABASE_DOES_NOT_EXIST	equ 1065

;;
;; MessageId: ERROR_SERVICE_SPECIFIC_ERROR
;;
;; MessageText:
;;
;;  The service has returned a service-specific error code.
;;
ERROR_SERVICE_SPECIFIC_ERROR	equ 1066

;;
;; MessageId: ERROR_PROCESS_ABORTED
;;
;; MessageText:
;;
;;  The process terminated unexpectedly.
;;
ERROR_PROCESS_ABORTED	equ 1067

;;
;; MessageId: ERROR_SERVICE_DEPENDENCY_FAIL
;;
;; MessageText:
;;
;;  The dependency service or group failed to start.
;;
ERROR_SERVICE_DEPENDENCY_FAIL	equ 1068

;;
;; MessageId: ERROR_SERVICE_LOGON_FAILED
;;
;; MessageText:
;;
;;  The service did not start due to a logon failure.
;;
ERROR_SERVICE_LOGON_FAILED	equ 1069

;;
;; MessageId: ERROR_SERVICE_START_HANG
;;
;; MessageText:
;;
;;  After starting, the service hung in a start-pending state.
;;
ERROR_SERVICE_START_HANG	equ 1070

;;
;; MessageId: ERROR_INVALID_SERVICE_LOCK
;;
;; MessageText:
;;
;;  The specified service database lock is invalid.
;;
ERROR_INVALID_SERVICE_LOCK	equ 1071

;;
;; MessageId: ERROR_SERVICE_MARKED_FOR_DELETE
;;
;; MessageText:
;;
;;  The specified service has been marked for deletion.
;;
ERROR_SERVICE_MARKED_FOR_DELETE equ 1072

;;
;; MessageId: ERROR_SERVICE_EXISTS
;;
;; MessageText:
;;
;;  The specified service already exists.
;;
ERROR_SERVICE_EXISTS	equ 1073

;;
;; MessageId: ERROR_ALREADY_RUNNING_LKG
;;
;; MessageText:
;;
;;  The system is currently running with the last-known-good configuration.
;;
ERROR_ALREADY_RUNNING_LKG	equ 1074

;;
;; MessageId: ERROR_SERVICE_DEPENDENCY_DELETED
;;
;; MessageText:
;;
;;  The dependency service does not exist or has been marked for
;;  deletion.
;;
ERROR_SERVICE_DEPENDENCY_DELETED	equ 1075

;;
;; MessageId: ERROR_BOOT_ALREADY_ACCEPTED
;;
;; MessageText:
;;
;;  The current boot has already been accepted for use as the
;;  last-known-good control set.
;;
ERROR_BOOT_ALREADY_ACCEPTED	equ 1076

;;
;; MessageId: ERROR_SERVICE_NEVER_STARTED
;;
;; MessageText:
;;
;;  No attempts to start the service have been made since the last boot.
;;
ERROR_SERVICE_NEVER_STARTED	equ 1077

;;
;; MessageId: ERROR_DUPLICATE_SERVICE_NAME
;;
;; MessageText:
;;
;;  The name is already in use as either a service name or a service display
;;  name.
;;
ERROR_DUPLICATE_SERVICE_NAME	equ 1078

;;
;; MessageId: ERROR_DIFFERENT_SERVICE_ACCOUNT
;;
;; MessageText:
;;
;;  The account specified for this service is different from the account
;;  specified for other services running in the same process.
;;
ERROR_DIFFERENT_SERVICE_ACCOUNT equ 1079

;;
;; MessageId: ERROR_CANNOT_DETECT_DRIVER_FAILURE
;;
;; MessageText:
;;
;;  Failure actions can only be set for Win32 services, not for drivers.
;;
ERROR_CANNOT_DETECT_DRIVER_FAILURE	equ 1080

;;
;; MessageId: ERROR_CANNOT_DETECT_PROCESS_ABORT
;;
;; MessageText:
;;
;;  This service runs in the same process as the service control manager.
;;  Therefore, the service control manager cannot take action if this
;;  service's process terminates unexpectedly.
;;
ERROR_CANNOT_DETECT_PROCESS_ABORT	equ 1081

;;
;; MessageId: ERROR_NO_RECOVERY_PROGRAM
;;
;; MessageText:
;;
;;  No recovery program has been configured for this service.
;;
ERROR_NO_RECOVERY_PROGRAM	equ 1082

;;
;; MessageId: ERROR_END_OF_MEDIA
;;
;; MessageText:
;;
;;  The physical end of the tape has been reached.
;;
ERROR_END_OF_MEDIA	equ 1100

;;
;; MessageId: ERROR_FILEMARK_DETECTED
;;
;; MessageText:
;;
;;  A tape access reached a filemark.
;;
ERROR_FILEMARK_DETECTED equ 1101

;;
;; MessageId: ERROR_BEGINNING_OF_MEDIA
;;
;; MessageText:
;;
;;  The beginning of the tape or a partition was encountered.
;;
ERROR_BEGINNING_OF_MEDIA	equ 1102

;;
;; MessageId: ERROR_SETMARK_DETECTED
;;
;; MessageText:
;;
;;  A tape access reached the end of a set of files.
;;
ERROR_SETMARK_DETECTED	equ 1103

;;
;; MessageId: ERROR_NO_DATA_DETECTED
;;
;; MessageText:
;;
;;  No more data is on the tape.
;;
ERROR_NO_DATA_DETECTED	equ 1104

;;
;; MessageId: ERROR_PARTITION_FAILURE
;;
;; MessageText:
;;
;;  Tape could not be partitioned.
;;
ERROR_PARTITION_FAILURE equ 1105

;;
;; MessageId: ERROR_INVALID_BLOCK_LENGTH
;;
;; MessageText:
;;
;;  When accessing a new tape of a multivolume partition, the current
;;  blocksize is incorrect.
;;
ERROR_INVALID_BLOCK_LENGTH	equ 1106

;;
;; MessageId: ERROR_DEVICE_NOT_PARTITIONED
;;
;; MessageText:
;;
;;  Tape partition information could not be found when loading a tape.
;;
ERROR_DEVICE_NOT_PARTITIONED	equ 1107

;;
;; MessageId: ERROR_UNABLE_TO_LOCK_MEDIA
;;
;; MessageText:
;;
;;  Unable to lock the media eject mechanism.
;;
ERROR_UNABLE_TO_LOCK_MEDIA	equ 1108

;;
;; MessageId: ERROR_UNABLE_TO_UNLOAD_MEDIA
;;
;; MessageText:
;;
;;  Unable to unload the media.
;;
ERROR_UNABLE_TO_UNLOAD_MEDIA	equ 1109

;;
;; MessageId: ERROR_MEDIA_CHANGED
;;
;; MessageText:
;;
;;  The media in the drive may have changed.
;;
ERROR_MEDIA_CHANGED	equ 1110

;;
;; MessageId: ERROR_BUS_RESET
;;
;; MessageText:
;;
;;  The I/O bus was reset.
;;
ERROR_BUS_RESET equ 1111

;;
;; MessageId: ERROR_NO_MEDIA_IN_DRIVE
;;
;; MessageText:
;;
;;  No media in drive.
;;
ERROR_NO_MEDIA_IN_DRIVE equ 1112

;;
;; MessageId: ERROR_NO_UNICODE_TRANSLATION
;;
;; MessageText:
;;
;;  No mapping for the Unicode character exists in the target multi-byte code page.
;;
ERROR_NO_UNICODE_TRANSLATION	equ 1113

;;
;; MessageId: ERROR_DLL_INIT_FAILED
;;
;; MessageText:
;;
;;  A dynamic link library (DLL) initialization routine failed.
;;
ERROR_DLL_INIT_FAILED	equ 1114

;;
;; MessageId: ERROR_SHUTDOWN_IN_PROGRESS
;;
;; MessageText:
;;
;;  A system shutdown is in progress.
;;
ERROR_SHUTDOWN_IN_PROGRESS	equ 1115

;;
;; MessageId: ERROR_NO_SHUTDOWN_IN_PROGRESS
;;
;; MessageText:
;;
;;  Unable to abort the system shutdown because no shutdown was in progress.
;;
ERROR_NO_SHUTDOWN_IN_PROGRESS	equ 1116

;;
;; MessageId: ERROR_IO_DEVICE
;;
;; MessageText:
;;
;;  The request could not be performed because of an I/O device error.
;;
ERROR_IO_DEVICE equ 1117

;;
;; MessageId: ERROR_SERIAL_NO_DEVICE
;;
;; MessageText:
;;
;;  No serial device was successfully initialized.  The serial driver will unload.
;;
ERROR_SERIAL_NO_DEVICE	equ 1118

;;
;; MessageId: ERROR_IRQ_BUSY
;;
;; MessageText:
;;
;;  Unable to open a device that was sharing an interrupt request (IRQ)
;;  with other devices. At least one other device that uses that IRQ
;;  was already opened.
;;
ERROR_IRQ_BUSY	equ 1119

;;
;; MessageId: ERROR_MORE_WRITES
;;
;; MessageText:
;;
;;  A serial I/O operation was completed by another write to the serial port.
;;  (The IOCTL_SERIAL_XOFF_COUNTER reached zero.)
;;
ERROR_MORE_WRITES	equ 1120

;;
;; MessageId: ERROR_COUNTER_TIMEOUT
;;
;; MessageText:
;;
;;  A serial I/O operation completed because the timeout period expired.
;;  (The IOCTL_SERIAL_XOFF_COUNTER did not reach zero.)
;;
ERROR_COUNTER_TIMEOUT	equ 1121

;;
;; MessageId: ERROR_FLOPPY_ID_MARK_NOT_FOUND
;;
;; MessageText:
;;
;;  No ID address mark was found on the floppy disk.
;;
ERROR_FLOPPY_ID_MARK_NOT_FOUND	equ 1122

;;
;; MessageId: ERROR_FLOPPY_WRONG_CYLINDER
;;
;; MessageText:
;;
;;  Mismatch between the floppy disk sector ID field and the floppy disk
;;  controller track address.
;;
ERROR_FLOPPY_WRONG_CYLINDER	equ 1123

;;
;; MessageId: ERROR_FLOPPY_UNKNOWN_ERROR
;;
;; MessageText:
;;
;;  The floppy disk controller reported an error that is not recognized
;;  by the floppy disk driver.
;;
ERROR_FLOPPY_UNKNOWN_ERROR	equ 1124

;;
;; MessageId: ERROR_FLOPPY_BAD_REGISTERS
;;
;; MessageText:
;;
;;  The floppy disk controller returned inconsistent results in its registers.
;;
ERROR_FLOPPY_BAD_REGISTERS	equ 1125

;;
;; MessageId: ERROR_DISK_RECALIBRATE_FAILED
;;
;; MessageText:
;;
;;  While accessing the hard disk, a recalibrate operation failed, even after retries.
;;
ERROR_DISK_RECALIBRATE_FAILED	equ 1126

;;
;; MessageId: ERROR_DISK_OPERATION_FAILED
;;
;; MessageText:
;;
;;  While accessing the hard disk, a disk operation failed even after retries.
;;
ERROR_DISK_OPERATION_FAILED	equ 1127

;;
;; MessageId: ERROR_DISK_RESET_FAILED
;;
;; MessageText:
;;
;;  While accessing the hard disk, a disk controller reset was needed, but
;;  even that failed.
;;
ERROR_DISK_RESET_FAILED equ 1128

;;
;; MessageId: ERROR_EOM_OVERFLOW
;;
;; MessageText:
;;
;;  Physical end of tape encountered.
;;
ERROR_EOM_OVERFLOW	equ 1129

;;
;; MessageId: ERROR_NOT_ENOUGH_SERVER_MEMORY
;;
;; MessageText:
;;
;;  Not enough server storage is available to process this command.
;;
ERROR_NOT_ENOUGH_SERVER_MEMORY	equ 1130

;;
;; MessageId: ERROR_POSSIBLE_DEADLOCK
;;
;; MessageText:
;;
;;  A potential deadlock condition has been detected.
;;
ERROR_POSSIBLE_DEADLOCK equ 1131

;;
;; MessageId: ERROR_MAPPED_ALIGNMENT
;;
;; MessageText:
;;
;;  The base address or the file offset specified does not have the proper
;;  alignment.
;;
ERROR_MAPPED_ALIGNMENT	equ 1132

;;
;; MessageId: ERROR_SET_POWER_STATE_VETOED
;;
;; MessageText:
;;
;;  An attempt to change the system power state was vetoed by another
;;  application or driver.
;;
ERROR_SET_POWER_STATE_VETOED	equ 1140

;;
;; MessageId: ERROR_SET_POWER_STATE_FAILED
;;
;; MessageText:
;;
;;  The system BIOS failed an attempt to change the system power state.
;;
ERROR_SET_POWER_STATE_FAILED	equ 1141

;;
;; MessageId: ERROR_TOO_MANY_LINKS
;;
;; MessageText:
;;
;;  An attempt was made to create more links on a file than
;;  the file system supports.
;;
ERROR_TOO_MANY_LINKS	equ 1142

;;
;; MessageId: ERROR_OLD_WIN_VERSION
;;
;; MessageText:
;;
;;  The specified program requires a newer version of Windows.
;;
ERROR_OLD_WIN_VERSION	equ 1150

;;
;; MessageId: ERROR_APP_WRONG_OS
;;
;; MessageText:
;;
;;  The specified program is not a Windows or MS-DOS program.
;;
ERROR_APP_WRONG_OS	equ 1151

;;
;; MessageId: ERROR_SINGLE_INSTANCE_APP
;;
;; MessageText:
;;
;;  Cannot start more than one instance of the specified program.
;;
ERROR_SINGLE_INSTANCE_APP	equ 1152

;;
;; MessageId: ERROR_RMODE_APP
;;
;; MessageText:
;;
;;  The specified program was written for an earlier version of Windows.
;;
ERROR_RMODE_APP equ 1153

;;
;; MessageId: ERROR_INVALID_DLL
;;
;; MessageText:
;;
;;  One of the library files needed to run this application is damaged.
;;
ERROR_INVALID_DLL	equ 1154

;;
;; MessageId: ERROR_NO_ASSOCIATION
;;
;; MessageText:
;;
;;  No application is associated with the specified file for this operation.
;;
ERROR_NO_ASSOCIATION	equ 1155

;;
;; MessageId: ERROR_DDE_FAIL
;;
;; MessageText:
;;
;;  An error occurred in sending the command to the application.
;;
ERROR_DDE_FAIL	equ 1156

;;
;; MessageId: ERROR_DLL_NOT_FOUND
;;
;; MessageText:
;;
;;  One of the library files needed to run this application cannot be found.
;;
ERROR_DLL_NOT_FOUND	equ 1157

;;
;; MessageId: ERROR_NO_MORE_USER_HANDLES
;;
;; MessageText:
;;
;;  The current process has used all of its system allowance of handles for Window Manager objects.
;;
ERROR_NO_MORE_USER_HANDLES	equ 1158

;;
;; MessageId: ERROR_MESSAGE_SYNC_ONLY
;;
;; MessageText:
;;
;;  The message can be used only with synchronous operations.
;;
ERROR_MESSAGE_SYNC_ONLY equ 1159

;;
;; MessageId: ERROR_SOURCE_ELEMENT_EMPTY
;;
;; MessageText:
;;
;;  The indicated source element has no media.
;;
ERROR_SOURCE_ELEMENT_EMPTY	equ 1160

;;
;; MessageId: ERROR_DESTINATION_ELEMENT_FULL
;;
;; MessageText:
;;
;;  The indicated destination element already contains media.
;;
ERROR_DESTINATION_ELEMENT_FULL	equ 1161

;;
;; MessageId: ERROR_ILLEGAL_ELEMENT_ADDRESS
;;
;; MessageText:
;;
;;  The indicated element does not exist.
;;
ERROR_ILLEGAL_ELEMENT_ADDRESS	equ 1162

;;
;; MessageId: ERROR_MAGAZINE_NOT_PRESENT
;;
;; MessageText:
;;
;;  The indicated element is part of a magazine that is not present.
;;
ERROR_MAGAZINE_NOT_PRESENT	equ 1163

;;
;; MessageId: ERROR_DEVICE_REINITIALIZATION_NEEDED
;;
;; MessageText:
;;
;;  The indicated device requires reinitialization due to hardware errors.
;;
ERROR_DEVICE_REINITIALIZATION_NEEDED	equ 1164    ;; dderror

;;
;; MessageId: ERROR_DEVICE_REQUIRES_CLEANING
;;
;; MessageText:
;;
;;  The device has indicated that cleaning is required before further operations are attempted.
;;
ERROR_DEVICE_REQUIRES_CLEANING	equ 1165

;;
;; MessageId: ERROR_DEVICE_DOOR_OPEN
;;
;; MessageText:
;;
;;  The device has indicated that its door is open.
;;
ERROR_DEVICE_DOOR_OPEN	equ 1166

;;
;; MessageId: ERROR_DEVICE_NOT_CONNECTED
;;
;; MessageText:
;;
;;  The device is not connected.
;;
ERROR_DEVICE_NOT_CONNECTED	equ 1167

;;
;; MessageId: ERROR_NOT_FOUND
;;
;; MessageText:
;;
;;  Element not found.
;;
ERROR_NOT_FOUND equ 1168

;;
;; MessageId: ERROR_NO_MATCH
;;
;; MessageText:
;;
;;  There was no match for the specified key in the index.
;;
ERROR_NO_MATCH	equ 1169

;;
;; MessageId: ERROR_SET_NOT_FOUND
;;
;; MessageText:
;;
;;  The property set specified does not exist on the object.
;;
ERROR_SET_NOT_FOUND	equ 1170

;;
;; MessageId: ERROR_POINT_NOT_FOUND
;;
;; MessageText:
;;
;;  The point passed to GetMouseMovePoints is not in the buffer.
;;
ERROR_POINT_NOT_FOUND	equ 1171

;;
;; MessageId: ERROR_NO_TRACKING_SERVICE
;;
;; MessageText:
;;
;;  The tracking (workstation) service is not running.
;;
ERROR_NO_TRACKING_SERVICE	equ 1172

;;
;; MessageId: ERROR_NO_VOLUME_ID
;;
;; MessageText:
;;
;;  The Volume ID could not be found.
;;
ERROR_NO_VOLUME_ID	equ 1173




;;;;/;;/;;/;;/;;/;;/;;/;;//
;;			 ;;
;; Winnet32 Status Codes ;;
;;			 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;//


;;
;; MessageId: ERROR_CONNECTED_OTHER_PASSWORD
;;
;; MessageText:
;;
;;  The network connection was made successfully, but the user had to be prompted
;;  for a password other than the one originally specified.
;;
ERROR_CONNECTED_OTHER_PASSWORD	equ 2108

;;
;; MessageId: ERROR_BAD_USERNAME
;;
;; MessageText:
;;
;;  The specified username is invalid.
;;
ERROR_BAD_USERNAME	equ 2202

;;
;; MessageId: ERROR_NOT_CONNECTED
;;
;; MessageText:
;;
;;  This network connection does not exist.
;;
ERROR_NOT_CONNECTED	equ 2250

;;
;; MessageId: ERROR_OPEN_FILES
;;
;; MessageText:
;;
;;  This network connection has files open or requests pending.
;;
ERROR_OPEN_FILES	equ 2401

;;
;; MessageId: ERROR_ACTIVE_CONNECTIONS
;;
;; MessageText:
;;
;;  Active connections still exist.
;;
ERROR_ACTIVE_CONNECTIONS	equ 2402

;;
;; MessageId: ERROR_DEVICE_IN_USE
;;
;; MessageText:
;;
;;  The device is in use by an active process and cannot be disconnected.
;;
ERROR_DEVICE_IN_USE	equ 2404

;;
;; MessageId: ERROR_BAD_DEVICE
;;
;; MessageText:
;;
;;  The specified device name is invalid.
;;
ERROR_BAD_DEVICE	equ 1200

;;
;; MessageId: ERROR_CONNECTION_UNAVAIL
;;
;; MessageText:
;;
;;  The device is not currently connected but it is a remembered connection.
;;
ERROR_CONNECTION_UNAVAIL	equ 1201

;;
;; MessageId: ERROR_DEVICE_ALREADY_REMEMBERED
;;
;; MessageText:
;;
;;  An attempt was made to remember a device that had previously been remembered.
;;
ERROR_DEVICE_ALREADY_REMEMBERED equ 1202

;;
;; MessageId: ERROR_NO_NET_OR_BAD_PATH
;;
;; MessageText:
;;
;;  No network provider accepted the given network path.
;;
ERROR_NO_NET_OR_BAD_PATH	equ 1203

;;
;; MessageId: ERROR_BAD_PROVIDER
;;
;; MessageText:
;;
;;  The specified network provider name is invalid.
;;
ERROR_BAD_PROVIDER	equ 1204

;;
;; MessageId: ERROR_CANNOT_OPEN_PROFILE
;;
;; MessageText:
;;
;;  Unable to open the network connection profile.
;;
ERROR_CANNOT_OPEN_PROFILE	equ 1205

;;
;; MessageId: ERROR_BAD_PROFILE
;;
;; MessageText:
;;
;;  The network connection profile is corrupted.
;;
ERROR_BAD_PROFILE	equ 1206

;;
;; MessageId: ERROR_NOT_CONTAINER
;;
;; MessageText:
;;
;;  Cannot enumerate a noncontainer.
;;
ERROR_NOT_CONTAINER	equ 1207

;;
;; MessageId: ERROR_EXTENDED_ERROR
;;
;; MessageText:
;;
;;  An extended error has occurred.
;;
ERROR_EXTENDED_ERROR	equ 1208

;;
;; MessageId: ERROR_INVALID_GROUPNAME
;;
;; MessageText:
;;
;;  The format of the specified group name is invalid.
;;
ERROR_INVALID_GROUPNAME equ 1209

;;
;; MessageId: ERROR_INVALID_COMPUTERNAME
;;
;; MessageText:
;;
;;  The format of the specified computer name is invalid.
;;
ERROR_INVALID_COMPUTERNAME	equ 1210

;;
;; MessageId: ERROR_INVALID_EVENTNAME
;;
;; MessageText:
;;
;;  The format of the specified event name is invalid.
;;
ERROR_INVALID_EVENTNAME equ 1211

;;
;; MessageId: ERROR_INVALID_DOMAINNAME
;;
;; MessageText:
;;
;;  The format of the specified domain name is invalid.
;;
ERROR_INVALID_DOMAINNAME	equ 1212

;;
;; MessageId: ERROR_INVALID_SERVICENAME
;;
;; MessageText:
;;
;;  The format of the specified service name is invalid.
;;
ERROR_INVALID_SERVICENAME	equ 1213

;;
;; MessageId: ERROR_INVALID_NETNAME
;;
;; MessageText:
;;
;;  The format of the specified network name is invalid.
;;
ERROR_INVALID_NETNAME	equ 1214

;;
;; MessageId: ERROR_INVALID_SHARENAME
;;
;; MessageText:
;;
;;  The format of the specified share name is invalid.
;;
ERROR_INVALID_SHARENAME equ 1215

;;
;; MessageId: ERROR_INVALID_PASSWORDNAME
;;
;; MessageText:
;;
;;  The format of the specified password is invalid.
;;
ERROR_INVALID_PASSWORDNAME	equ 1216

;;
;; MessageId: ERROR_INVALID_MESSAGENAME
;;
;; MessageText:
;;
;;  The format of the specified message name is invalid.
;;
ERROR_INVALID_MESSAGENAME	equ 1217

;;
;; MessageId: ERROR_INVALID_MESSAGEDEST
;;
;; MessageText:
;;
;;  The format of the specified message destination is invalid.
;;
ERROR_INVALID_MESSAGEDEST	equ 1218

;;
;; MessageId: ERROR_SESSION_CREDENTIAL_CONFLICT
;;
;; MessageText:
;;
;;  The credentials supplied conflict with an existing set of credentials.
;;
ERROR_SESSION_CREDENTIAL_CONFLICT	equ 1219

;;
;; MessageId: ERROR_REMOTE_SESSION_LIMIT_EXCEEDED
;;
;; MessageText:
;;
;;  An attempt was made to establish a session to a network server, but there
;;  are already too many sessions established to that server.
;;
ERROR_REMOTE_SESSION_LIMIT_EXCEEDED	equ 1220

;;
;; MessageId: ERROR_DUP_DOMAINNAME
;;
;; MessageText:
;;
;;  The workgroup or domain name is already in use by another computer on the
;;  network.
;;
ERROR_DUP_DOMAINNAME	equ 1221

;;
;; MessageId: ERROR_NO_NETWORK
;;
;; MessageText:
;;
;;  The network is not present or not started.
;;
ERROR_NO_NETWORK	equ 1222

;;
;; MessageId: ERROR_CANCELLED
;;
;; MessageText:
;;
;;  The operation was canceled by the user.
;;
ERROR_CANCELLED equ 1223

;;
;; MessageId: ERROR_USER_MAPPED_FILE
;;
;; MessageText:
;;
;;  The requested operation cannot be performed on a file with a user-mapped section open.
;;
ERROR_USER_MAPPED_FILE	equ 1224

;;
;; MessageId: ERROR_CONNECTION_REFUSED
;;
;; MessageText:
;;
;;  The remote system refused the network connection.
;;
ERROR_CONNECTION_REFUSED	equ 1225

;;
;; MessageId: ERROR_GRACEFUL_DISCONNECT
;;
;; MessageText:
;;
;;  The network connection was gracefully closed.
;;
ERROR_GRACEFUL_DISCONNECT	equ 1226

;;
;; MessageId: ERROR_ADDRESS_ALREADY_ASSOCIATED
;;
;; MessageText:
;;
;;  The network transport endpoint already has an address associated with it.
;;
ERROR_ADDRESS_ALREADY_ASSOCIATED	equ 1227

;;
;; MessageId: ERROR_ADDRESS_NOT_ASSOCIATED
;;
;; MessageText:
;;
;;  An address has not yet been associated with the network endpoint.
;;
ERROR_ADDRESS_NOT_ASSOCIATED	equ 1228

;;
;; MessageId: ERROR_CONNECTION_INVALID
;;
;; MessageText:
;;
;;  An operation was attempted on a nonexistent network connection.
;;
ERROR_CONNECTION_INVALID	equ 1229

;;
;; MessageId: ERROR_CONNECTION_ACTIVE
;;
;; MessageText:
;;
;;  An invalid operation was attempted on an active network connection.
;;
ERROR_CONNECTION_ACTIVE equ 1230

;;
;; MessageId: ERROR_NETWORK_UNREACHABLE
;;
;; MessageText:
;;
;;  The remote network is not reachable by the transport.
;;
ERROR_NETWORK_UNREACHABLE	equ 1231

;;
;; MessageId: ERROR_HOST_UNREACHABLE
;;
;; MessageText:
;;
;;  The remote system is not reachable by the transport.
;;
ERROR_HOST_UNREACHABLE	equ 1232

;;
;; MessageId: ERROR_PROTOCOL_UNREACHABLE
;;
;; MessageText:
;;
;;  The remote system does not support the transport protocol.
;;
ERROR_PROTOCOL_UNREACHABLE	equ 1233

;;
;; MessageId: ERROR_PORT_UNREACHABLE
;;
;; MessageText:
;;
;;  No service is operating at the destination network endpoint
;;  on the remote system.
;;
ERROR_PORT_UNREACHABLE	equ 1234

;;
;; MessageId: ERROR_REQUEST_ABORTED
;;
;; MessageText:
;;
;;  The request was aborted.
;;
ERROR_REQUEST_ABORTED	equ 1235

;;
;; MessageId: ERROR_CONNECTION_ABORTED
;;
;; MessageText:
;;
;;  The network connection was aborted by the local system.
;;
ERROR_CONNECTION_ABORTED	equ 1236

;;
;; MessageId: ERROR_RETRY
;;
;; MessageText:
;;
;;  The operation could not be completed.  A retry should be performed.
;;
ERROR_RETRY	equ 1237

;;
;; MessageId: ERROR_CONNECTION_COUNT_LIMIT
;;
;; MessageText:
;;
;;  A connection to the server could not be made because the limit on the number of
;;  concurrent connections for this account has been reached.
;;
ERROR_CONNECTION_COUNT_LIMIT	equ 1238

;;
;; MessageId: ERROR_LOGIN_TIME_RESTRICTION
;;
;; MessageText:
;;
;;  Attempting to log in during an unauthorized time of day for this account.
;;
ERROR_LOGIN_TIME_RESTRICTION	equ 1239

;;
;; MessageId: ERROR_LOGIN_WKSTA_RESTRICTION
;;
;; MessageText:
;;
;;  The account is not authorized to log in from this station.
;;
ERROR_LOGIN_WKSTA_RESTRICTION	equ 1240

;;
;; MessageId: ERROR_INCORRECT_ADDRESS
;;
;; MessageText:
;;
;;  The network address could not be used for the operation requested.
;;
ERROR_INCORRECT_ADDRESS equ 1241

;;
;; MessageId: ERROR_ALREADY_REGISTERED
;;
;; MessageText:
;;
;;  The service is already registered.
;;
ERROR_ALREADY_REGISTERED	equ 1242

;;
;; MessageId: ERROR_SERVICE_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified service does not exist.
;;
ERROR_SERVICE_NOT_FOUND equ 1243

;;
;; MessageId: ERROR_NOT_AUTHENTICATED
;;
;; MessageText:
;;
;;  The operation being requested was not performed because the user
;;  has not been authenticated.
;;
ERROR_NOT_AUTHENTICATED equ 1244

;;
;; MessageId: ERROR_NOT_LOGGED_ON
;;
;; MessageText:
;;
;;  The operation being requested was not performed because the user
;;  has not logged on to the network.
;;  The specified service does not exist.
;;
ERROR_NOT_LOGGED_ON	equ 1245

;;
;; MessageId: ERROR_CONTINUE
;;
;; MessageText:
;;
;;  Continue with work in progress.
;;
ERROR_CONTINUE	equ 1246

;;
;; MessageId: ERROR_ALREADY_INITIALIZED
;;
;; MessageText:
;;
;;  An attempt was made to perform an initialization operation when
;;  initialization has already been completed.
;;
ERROR_ALREADY_INITIALIZED	equ 1247

;;
;; MessageId: ERROR_NO_MORE_DEVICES
;;
;; MessageText:
;;
;;  No more local devices.
;;
ERROR_NO_MORE_DEVICES	equ 1248

;;
;; MessageId: ERROR_NO_SUCH_SITE
;;
;; MessageText:
;;
;;  The specified site does not exist.
;;
ERROR_NO_SUCH_SITE	equ 1249

;;
;; MessageId: ERROR_DOMAIN_CONTROLLER_EXISTS
;;
;; MessageText:
;;
;;  A domain controller with the specified name already exists.
;;
ERROR_DOMAIN_CONTROLLER_EXISTS	equ 1250

;;
;; MessageId: ERROR_DS_NOT_INSTALLED
;;
;; MessageText:
;;
;;  An error occurred while installing the Windows NT directory service. Please view the event log for more information.
;;
ERROR_DS_NOT_INSTALLED	equ 1251




;;;;/;;/;;/;;/;;/;;/;;/;;//
;;			 ;;
;; Security Status Codes ;;
;;			 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;//


;;
;; MessageId: ERROR_NOT_ALL_ASSIGNED
;;
;; MessageText:
;;
;;  Not all privileges referenced are assigned to the caller.
;;
ERROR_NOT_ALL_ASSIGNED	equ 1300

;;
;; MessageId: ERROR_SOME_NOT_MAPPED
;;
;; MessageText:
;;
;;  Some mapping between account names and security IDs was not done.
;;
ERROR_SOME_NOT_MAPPED	equ 1301

;;
;; MessageId: ERROR_NO_QUOTAS_FOR_ACCOUNT
;;
;; MessageText:
;;
;;  No system quota limits are specifically set for this account.
;;
ERROR_NO_QUOTAS_FOR_ACCOUNT	equ 1302

;;
;; MessageId: ERROR_LOCAL_USER_SESSION_KEY
;;
;; MessageText:
;;
;;  No encryption key is available.  A well-known encryption key was returned.
;;
ERROR_LOCAL_USER_SESSION_KEY	equ 1303

;;
;; MessageId: ERROR_NULL_LM_PASSWORD
;;
;; MessageText:
;;
;;  The Windows NT password is too complex to be converted to a LAN Manager
;;  password.  The LAN Manager password returned is a NULL string.
;;
ERROR_NULL_LM_PASSWORD	equ 1304

;;
;; MessageId: ERROR_UNKNOWN_REVISION
;;
;; MessageText:
;;
;;  The revision level is unknown.
;;
ERROR_UNKNOWN_REVISION	equ 1305

;;
;; MessageId: ERROR_REVISION_MISMATCH
;;
;; MessageText:
;;
;;  Indicates two revision levels are incompatible.
;;
ERROR_REVISION_MISMATCH equ 1306

;;
;; MessageId: ERROR_INVALID_OWNER
;;
;; MessageText:
;;
;;  This security ID may not be assigned as the owner of this object.
;;
ERROR_INVALID_OWNER	equ 1307

;;
;; MessageId: ERROR_INVALID_PRIMARY_GROUP
;;
;; MessageText:
;;
;;  This security ID may not be assigned as the primary group of an object.
;;
ERROR_INVALID_PRIMARY_GROUP	equ 1308

;;
;; MessageId: ERROR_NO_IMPERSONATION_TOKEN
;;
;; MessageText:
;;
;;  An attempt has been made to operate on an impersonation token
;;  by a thread that is not currently impersonating a client.
;;
ERROR_NO_IMPERSONATION_TOKEN	equ 1309

;;
;; MessageId: ERROR_CANT_DISABLE_MANDATORY
;;
;; MessageText:
;;
;;  The group may not be disabled.
;;
ERROR_CANT_DISABLE_MANDATORY	equ 1310

;;
;; MessageId: ERROR_NO_LOGON_SERVERS
;;
;; MessageText:
;;
;;  There are currently no logon servers available to service the logon
;;  request.
;;
ERROR_NO_LOGON_SERVERS	equ 1311

;;
;; MessageId: ERROR_NO_SUCH_LOGON_SESSION
;;
;; MessageText:
;;
;;   A specified logon session does not exist.	It may already have
;;   been terminated.
;;
ERROR_NO_SUCH_LOGON_SESSION	equ 1312

;;
;; MessageId: ERROR_NO_SUCH_PRIVILEGE
;;
;; MessageText:
;;
;;   A specified privilege does not exist.
;;
ERROR_NO_SUCH_PRIVILEGE equ 1313

;;
;; MessageId: ERROR_PRIVILEGE_NOT_HELD
;;
;; MessageText:
;;
;;   A required privilege is not held by the client.
;;
ERROR_PRIVILEGE_NOT_HELD	equ 1314

;;
;; MessageId: ERROR_INVALID_ACCOUNT_NAME
;;
;; MessageText:
;;
;;  The name provided is not a properly formed account name.
;;
ERROR_INVALID_ACCOUNT_NAME	equ 1315

;;
;; MessageId: ERROR_USER_EXISTS
;;
;; MessageText:
;;
;;  The specified user already exists.
;;
ERROR_USER_EXISTS	equ 1316

;;
;; MessageId: ERROR_NO_SUCH_USER
;;
;; MessageText:
;;
;;  The specified user does not exist.
;;
ERROR_NO_SUCH_USER	equ 1317

;;
;; MessageId: ERROR_GROUP_EXISTS
;;
;; MessageText:
;;
;;  The specified group already exists.
;;
ERROR_GROUP_EXISTS	equ 1318

;;
;; MessageId: ERROR_NO_SUCH_GROUP
;;
;; MessageText:
;;
;;  The specified group does not exist.
;;
ERROR_NO_SUCH_GROUP	equ 1319

;;
;; MessageId: ERROR_MEMBER_IN_GROUP
;;
;; MessageText:
;;
;;  Either the specified user account is already a member of the specified
;;  group, or the specified group cannot be deleted because it contains
;;  a member.
;;
ERROR_MEMBER_IN_GROUP	equ 1320

;;
;; MessageId: ERROR_MEMBER_NOT_IN_GROUP
;;
;; MessageText:
;;
;;  The specified user account is not a member of the specified group account.
;;
ERROR_MEMBER_NOT_IN_GROUP	equ 1321

;;
;; MessageId: ERROR_LAST_ADMIN
;;
;; MessageText:
;;
;;  The last remaining administration account cannot be disabled
;;  or deleted.
;;
ERROR_LAST_ADMIN	equ 1322

;;
;; MessageId: ERROR_WRONG_PASSWORD
;;
;; MessageText:
;;
;;  Unable to update the password.  The value provided as the current
;;  password is incorrect.
;;
ERROR_WRONG_PASSWORD	equ 1323

;;
;; MessageId: ERROR_ILL_FORMED_PASSWORD
;;
;; MessageText:
;;
;;  Unable to update the password.  The value provided for the new password
;;  contains values that are not allowed in passwords.
;;
ERROR_ILL_FORMED_PASSWORD	equ 1324

;;
;; MessageId: ERROR_PASSWORD_RESTRICTION
;;
;; MessageText:
;;
;;  Unable to update the password because a password update rule has been
;;  violated.
;;
ERROR_PASSWORD_RESTRICTION	equ 1325

;;
;; MessageId: ERROR_LOGON_FAILURE
;;
;; MessageText:
;;
;;  Logon failure: unknown user name or bad password.
;;
ERROR_LOGON_FAILURE	equ 1326

;;
;; MessageId: ERROR_ACCOUNT_RESTRICTION
;;
;; MessageText:
;;
;;  Logon failure: user account restriction.
;;
ERROR_ACCOUNT_RESTRICTION	equ 1327

;;
;; MessageId: ERROR_INVALID_LOGON_HOURS
;;
;; MessageText:
;;
;;  Logon failure: account logon time restriction violation.
;;
ERROR_INVALID_LOGON_HOURS	equ 1328

;;
;; MessageId: ERROR_INVALID_WORKSTATION
;;
;; MessageText:
;;
;;  Logon failure: user not allowed to log on to this computer.
;;
ERROR_INVALID_WORKSTATION	equ 1329

;;
;; MessageId: ERROR_PASSWORD_EXPIRED
;;
;; MessageText:
;;
;;  Logon failure: the specified account password has expired.
;;
ERROR_PASSWORD_EXPIRED	equ 1330

;;
;; MessageId: ERROR_ACCOUNT_DISABLED
;;
;; MessageText:
;;
;;  Logon failure: account currently disabled.
;;
ERROR_ACCOUNT_DISABLED	equ 1331

;;
;; MessageId: ERROR_NONE_MAPPED
;;
;; MessageText:
;;
;;  No mapping between account names and security IDs was done.
;;
ERROR_NONE_MAPPED	equ 1332

;;
;; MessageId: ERROR_TOO_MANY_LUIDS_REQUESTED
;;
;; MessageText:
;;
;;  Too many local user identifiers (LUIDs) were requested at one time.
;;
ERROR_TOO_MANY_LUIDS_REQUESTED	equ 1333

;;
;; MessageId: ERROR_LUIDS_EXHAUSTED
;;
;; MessageText:
;;
;;  No more local user identifiers (LUIDs) are available.
;;
ERROR_LUIDS_EXHAUSTED	equ 1334

;;
;; MessageId: ERROR_INVALID_SUB_AUTHORITY
;;
;; MessageText:
;;
;;  The subauthority part of a security ID is invalid for this particular use.
;;
ERROR_INVALID_SUB_AUTHORITY	equ 1335

;;
;; MessageId: ERROR_INVALID_ACL
;;
;; MessageText:
;;
;;  The access control list (ACL) structure is invalid.
;;
ERROR_INVALID_ACL	equ 1336

;;
;; MessageId: ERROR_INVALID_SID
;;
;; MessageText:
;;
;;  The security ID structure is invalid.
;;
ERROR_INVALID_SID	equ 1337

;;
;; MessageId: ERROR_INVALID_SECURITY_DESCR
;;
;; MessageText:
;;
;;  The security descriptor structure is invalid.
;;
ERROR_INVALID_SECURITY_DESCR	equ 1338

;;
;; MessageId: ERROR_BAD_INHERITANCE_ACL
;;
;; MessageText:
;;
;;  The inherited access control list (ACL) or access control entry (ACE)
;;  could not be built.
;;
ERROR_BAD_INHERITANCE_ACL	equ 1340

;;
;; MessageId: ERROR_SERVER_DISABLED
;;
;; MessageText:
;;
;;  The server is currently disabled.
;;
ERROR_SERVER_DISABLED	equ 1341

;;
;; MessageId: ERROR_SERVER_NOT_DISABLED
;;
;; MessageText:
;;
;;  The server is currently enabled.
;;
ERROR_SERVER_NOT_DISABLED	equ 1342

;;
;; MessageId: ERROR_INVALID_ID_AUTHORITY
;;
;; MessageText:
;;
;;  The value provided was an invalid value for an identifier authority.
;;
ERROR_INVALID_ID_AUTHORITY	equ 1343

;;
;; MessageId: ERROR_ALLOTTED_SPACE_EXCEEDED
;;
;; MessageText:
;;
;;  No more memory is available for security information updates.
;;
ERROR_ALLOTTED_SPACE_EXCEEDED	equ 1344

;;
;; MessageId: ERROR_INVALID_GROUP_ATTRIBUTES
;;
;; MessageText:
;;
;;  The specified attributes are invalid, or incompatible with the
;;  attributes for the group as a whole.
;;
ERROR_INVALID_GROUP_ATTRIBUTES	equ 1345

;;
;; MessageId: ERROR_BAD_IMPERSONATION_LEVEL
;;
;; MessageText:
;;
;;  Either a required impersonation level was not provided, or the
;;  provided impersonation level is invalid.
;;
ERROR_BAD_IMPERSONATION_LEVEL	equ 1346

;;
;; MessageId: ERROR_CANT_OPEN_ANONYMOUS
;;
;; MessageText:
;;
;;  Cannot open an anonymous level security token.
;;
ERROR_CANT_OPEN_ANONYMOUS	equ 1347

;;
;; MessageId: ERROR_BAD_VALIDATION_CLASS
;;
;; MessageText:
;;
;;  The validation information class requested was invalid.
;;
ERROR_BAD_VALIDATION_CLASS	equ 1348

;;
;; MessageId: ERROR_BAD_TOKEN_TYPE
;;
;; MessageText:
;;
;;  The type of the token is inappropriate for its attempted use.
;;
ERROR_BAD_TOKEN_TYPE	equ 1349

;;
;; MessageId: ERROR_NO_SECURITY_ON_OBJECT
;;
;; MessageText:
;;
;;  Unable to perform a security operation on an object
;;  that has no associated security.
;;
ERROR_NO_SECURITY_ON_OBJECT	equ 1350

;;
;; MessageId: ERROR_CANT_ACCESS_DOMAIN_INFO
;;
;; MessageText:
;;
;;  Indicates a Windows NT Server could not be contacted or that
;;  objects within the domain are protected such that necessary
;;  information could not be retrieved.
;;
ERROR_CANT_ACCESS_DOMAIN_INFO	equ 1351

;;
;; MessageId: ERROR_INVALID_SERVER_STATE
;;
;; MessageText:
;;
;;  The security account manager (SAM) or local security
;;  authority (LSA) server was in the wrong state to perform
;;  the security operation.
;;
ERROR_INVALID_SERVER_STATE	equ 1352

;;
;; MessageId: ERROR_INVALID_DOMAIN_STATE
;;
;; MessageText:
;;
;;  The domain was in the wrong state to perform the security operation.
;;
ERROR_INVALID_DOMAIN_STATE	equ 1353

;;
;; MessageId: ERROR_INVALID_DOMAIN_ROLE
;;
;; MessageText:
;;
;;  This operation is only allowed for the Primary Domain Controller of the domain.
;;
ERROR_INVALID_DOMAIN_ROLE	equ 1354

;;
;; MessageId: ERROR_NO_SUCH_DOMAIN
;;
;; MessageText:
;;
;;  The specified domain did not exist.
;;
ERROR_NO_SUCH_DOMAIN	equ 1355

;;
;; MessageId: ERROR_DOMAIN_EXISTS
;;
;; MessageText:
;;
;;  The specified domain already exists.
;;
ERROR_DOMAIN_EXISTS	equ 1356

;;
;; MessageId: ERROR_DOMAIN_LIMIT_EXCEEDED
;;
;; MessageText:
;;
;;  An attempt was made to exceed the limit on the number of domains per server.
;;
ERROR_DOMAIN_LIMIT_EXCEEDED	equ 1357

;;
;; MessageId: ERROR_INTERNAL_DB_CORRUPTION
;;
;; MessageText:
;;
;;  Unable to complete the requested operation because of either a
;;  catastrophic media failure or a data structure corruption on the disk.
;;
ERROR_INTERNAL_DB_CORRUPTION	equ 1358

;;
;; MessageId: ERROR_INTERNAL_ERROR
;;
;; MessageText:
;;
;;  The security account database contains an internal inconsistency.
;;
ERROR_INTERNAL_ERROR	equ 1359

;;
;; MessageId: ERROR_GENERIC_NOT_MAPPED
;;
;; MessageText:
;;
;;  Generic access types were contained in an access mask which should
;;  already be mapped to nongeneric types.
;;
ERROR_GENERIC_NOT_MAPPED	equ 1360

;;
;; MessageId: ERROR_BAD_DESCRIPTOR_FORMAT
;;
;; MessageText:
;;
;;  A security descriptor is not in the right format (absolute or self-relative).
;;
ERROR_BAD_DESCRIPTOR_FORMAT	equ 1361

;;
;; MessageId: ERROR_NOT_LOGON_PROCESS
;;
;; MessageText:
;;
;;  The requested action is restricted for use by logon processes
;;  only.  The calling process has not registered as a logon process.
;;
ERROR_NOT_LOGON_PROCESS equ 1362

;;
;; MessageId: ERROR_LOGON_SESSION_EXISTS
;;
;; MessageText:
;;
;;  Cannot start a new logon session with an ID that is already in use.
;;
ERROR_LOGON_SESSION_EXISTS	equ 1363

;;
;; MessageId: ERROR_NO_SUCH_PACKAGE
;;
;; MessageText:
;;
;;  A specified authentication package is unknown.
;;
ERROR_NO_SUCH_PACKAGE	equ 1364

;;
;; MessageId: ERROR_BAD_LOGON_SESSION_STATE
;;
;; MessageText:
;;
;;  The logon session is not in a state that is consistent with the
;;  requested operation.
;;
ERROR_BAD_LOGON_SESSION_STATE	equ 1365

;;
;; MessageId: ERROR_LOGON_SESSION_COLLISION
;;
;; MessageText:
;;
;;  The logon session ID is already in use.
;;
ERROR_LOGON_SESSION_COLLISION	equ 1366

;;
;; MessageId: ERROR_INVALID_LOGON_TYPE
;;
;; MessageText:
;;
;;  A logon request contained an invalid logon type value.
;;
ERROR_INVALID_LOGON_TYPE	equ 1367

;;
;; MessageId: ERROR_CANNOT_IMPERSONATE
;;
;; MessageText:
;;
;;  Unable to impersonate using a named pipe until data has been read
;;  from that pipe.
;;
ERROR_CANNOT_IMPERSONATE	equ 1368

;;
;; MessageId: ERROR_RXACT_INVALID_STATE
;;
;; MessageText:
;;
;;  The transaction state of a registry subtree is incompatible with the
;;  requested operation.
;;
ERROR_RXACT_INVALID_STATE	equ 1369

;;
;; MessageId: ERROR_RXACT_COMMIT_FAILURE
;;
;; MessageText:
;;
;;  An internal security database corruption has been encountered.
;;
ERROR_RXACT_COMMIT_FAILURE	equ 1370

;;
;; MessageId: ERROR_SPECIAL_ACCOUNT
;;
;; MessageText:
;;
;;  Cannot perform this operation on built-in accounts.
;;
ERROR_SPECIAL_ACCOUNT	equ 1371

;;
;; MessageId: ERROR_SPECIAL_GROUP
;;
;; MessageText:
;;
;;  Cannot perform this operation on this built-in special group.
;;
ERROR_SPECIAL_GROUP	equ 1372

;;
;; MessageId: ERROR_SPECIAL_USER
;;
;; MessageText:
;;
;;  Cannot perform this operation on this built-in special user.
;;
ERROR_SPECIAL_USER	equ 1373

;;
;; MessageId: ERROR_MEMBERS_PRIMARY_GROUP
;;
;; MessageText:
;;
;;  The user cannot be removed from a group because the group
;;  is currently the user's primary group.
;;
ERROR_MEMBERS_PRIMARY_GROUP	equ 1374

;;
;; MessageId: ERROR_TOKEN_ALREADY_IN_USE
;;
;; MessageText:
;;
;;  The token is already in use as a primary token.
;;
ERROR_TOKEN_ALREADY_IN_USE	equ 1375

;;
;; MessageId: ERROR_NO_SUCH_ALIAS
;;
;; MessageText:
;;
;;  The specified local group does not exist.
;;
ERROR_NO_SUCH_ALIAS	equ 1376

;;
;; MessageId: ERROR_MEMBER_NOT_IN_ALIAS
;;
;; MessageText:
;;
;;  The specified account name is not a member of the local group.
;;
ERROR_MEMBER_NOT_IN_ALIAS	equ 1377

;;
;; MessageId: ERROR_MEMBER_IN_ALIAS
;;
;; MessageText:
;;
;;  The specified account name is already a member of the local group.
;;
ERROR_MEMBER_IN_ALIAS	equ 1378

;;
;; MessageId: ERROR_ALIAS_EXISTS
;;
;; MessageText:
;;
;;  The specified local group already exists.
;;
ERROR_ALIAS_EXISTS	equ 1379

;;
;; MessageId: ERROR_LOGON_NOT_GRANTED
;;
;; MessageText:
;;
;;  Logon failure: the user has not been granted the requested
;;  logon type at this computer.
;;
ERROR_LOGON_NOT_GRANTED equ 1380

;;
;; MessageId: ERROR_TOO_MANY_SECRETS
;;
;; MessageText:
;;
;;  The maximum number of secrets that may be stored in a single system has been
;;  exceeded.
;;
ERROR_TOO_MANY_SECRETS	equ 1381

;;
;; MessageId: ERROR_SECRET_TOO_LONG
;;
;; MessageText:
;;
;;  The length of a secret exceeds the maximum length allowed.
;;
ERROR_SECRET_TOO_LONG	equ 1382

;;
;; MessageId: ERROR_INTERNAL_DB_ERROR
;;
;; MessageText:
;;
;;  The local security authority database contains an internal inconsistency.
;;
ERROR_INTERNAL_DB_ERROR equ 1383

;;
;; MessageId: ERROR_TOO_MANY_CONTEXT_IDS
;;
;; MessageText:
;;
;;  During a logon attempt, the user's security context accumulated too many
;;  security IDs.
;;
ERROR_TOO_MANY_CONTEXT_IDS	equ 1384

;;
;; MessageId: ERROR_LOGON_TYPE_NOT_GRANTED
;;
;; MessageText:
;;
;;  Logon failure: the user has not been granted the requested logon type
;;  at this computer.
;;
ERROR_LOGON_TYPE_NOT_GRANTED	equ 1385

;;
;; MessageId: ERROR_NT_CROSS_ENCRYPTION_REQUIRED
;;
;; MessageText:
;;
;;  A cross-encrypted password is necessary to change a user password.
;;
ERROR_NT_CROSS_ENCRYPTION_REQUIRED	equ 1386

;;
;; MessageId: ERROR_NO_SUCH_MEMBER
;;
;; MessageText:
;;
;;  A new member could not be added to a local group because the member does
;;  not exist.
;;
ERROR_NO_SUCH_MEMBER	equ 1387

;;
;; MessageId: ERROR_INVALID_MEMBER
;;
;; MessageText:
;;
;;  A new member could not be added to a local group because the member has the
;;  wrong account type.
;;
ERROR_INVALID_MEMBER	equ 1388

;;
;; MessageId: ERROR_TOO_MANY_SIDS
;;
;; MessageText:
;;
;;  Too many security IDs have been specified.
;;
ERROR_TOO_MANY_SIDS	equ 1389

;;
;; MessageId: ERROR_LM_CROSS_ENCRYPTION_REQUIRED
;;
;; MessageText:
;;
;;  A cross-encrypted password is necessary to change this user password.
;;
ERROR_LM_CROSS_ENCRYPTION_REQUIRED	equ 1390

;;
;; MessageId: ERROR_NO_INHERITANCE
;;
;; MessageText:
;;
;;  Indicates an ACL contains no inheritable components.
;;
ERROR_NO_INHERITANCE	equ 1391

;;
;; MessageId: ERROR_FILE_CORRUPT
;;
;; MessageText:
;;
;;  The file or directory is corrupted and unreadable.
;;
ERROR_FILE_CORRUPT	equ 1392

;;
;; MessageId: ERROR_DISK_CORRUPT
;;
;; MessageText:
;;
;;  The disk structure is corrupted and unreadable.
;;
ERROR_DISK_CORRUPT	equ 1393

;;
;; MessageId: ERROR_NO_USER_SESSION_KEY
;;
;; MessageText:
;;
;;  There is no user session key for the specified logon session.
;;
ERROR_NO_USER_SESSION_KEY	equ 1394

;;
;; MessageId: ERROR_LICENSE_QUOTA_EXCEEDED
;;
;; MessageText:
;;
;;  The service being accessed is licensed for a particular number of connections.
;;  No more connections can be made to the service at this time
;;  because there are already as many connections as the service can accept.
;;
ERROR_LICENSE_QUOTA_EXCEEDED	equ 1395

;; End of security error codes



;;;;/;;/;;/;;/;;/;;/;;/;;//
;;			 ;;
;; WinUser Error Codes	 ;;
;;			 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;//


;;
;; MessageId: ERROR_INVALID_WINDOW_HANDLE
;;
;; MessageText:
;;
;;  Invalid window handle.
;;
ERROR_INVALID_WINDOW_HANDLE	equ 1400

;;
;; MessageId: ERROR_INVALID_MENU_HANDLE
;;
;; MessageText:
;;
;;  Invalid menu handle.
;;
ERROR_INVALID_MENU_HANDLE	equ 1401

;;
;; MessageId: ERROR_INVALID_CURSOR_HANDLE
;;
;; MessageText:
;;
;;  Invalid cursor handle.
;;
ERROR_INVALID_CURSOR_HANDLE	equ 1402

;;
;; MessageId: ERROR_INVALID_ACCEL_HANDLE
;;
;; MessageText:
;;
;;  Invalid accelerator table handle.
;;
ERROR_INVALID_ACCEL_HANDLE	equ 1403

;;
;; MessageId: ERROR_INVALID_HOOK_HANDLE
;;
;; MessageText:
;;
;;  Invalid hook handle.
;;
ERROR_INVALID_HOOK_HANDLE	equ 1404

;;
;; MessageId: ERROR_INVALID_DWP_HANDLE
;;
;; MessageText:
;;
;;  Invalid handle to a multiple-window position structure.
;;
ERROR_INVALID_DWP_HANDLE	equ 1405

;;
;; MessageId: ERROR_TLW_WITH_WSCHILD
;;
;; MessageText:
;;
;;  Cannot create a top-level child window.
;;
ERROR_TLW_WITH_WSCHILD	equ 1406

;;
;; MessageId: ERROR_CANNOT_FIND_WND_CLASS
;;
;; MessageText:
;;
;;  Cannot find window class.
;;
ERROR_CANNOT_FIND_WND_CLASS	equ 1407

;;
;; MessageId: ERROR_WINDOW_OF_OTHER_THREAD
;;
;; MessageText:
;;
;;  Invalid window; it belongs to other thread.
;;
ERROR_WINDOW_OF_OTHER_THREAD	equ 1408

;;
;; MessageId: ERROR_HOTKEY_ALREADY_REGISTERED
;;
;; MessageText:
;;
;;  Hot key is already registered.
;;
ERROR_HOTKEY_ALREADY_REGISTERED equ 1409

;;
;; MessageId: ERROR_CLASS_ALREADY_EXISTS
;;
;; MessageText:
;;
;;  Class already exists.
;;
ERROR_CLASS_ALREADY_EXISTS	equ 1410

;;
;; MessageId: ERROR_CLASS_DOES_NOT_EXIST
;;
;; MessageText:
;;
;;  Class does not exist.
;;
ERROR_CLASS_DOES_NOT_EXIST	equ 1411

;;
;; MessageId: ERROR_CLASS_HAS_WINDOWS
;;
;; MessageText:
;;
;;  Class still has open windows.
;;
ERROR_CLASS_HAS_WINDOWS equ 1412

;;
;; MessageId: ERROR_INVALID_INDEX
;;
;; MessageText:
;;
;;  Invalid index.
;;
ERROR_INVALID_INDEX	equ 1413

;;
;; MessageId: ERROR_INVALID_ICON_HANDLE
;;
;; MessageText:
;;
;;  Invalid icon handle.
;;
ERROR_INVALID_ICON_HANDLE	equ 1414

;;
;; MessageId: ERROR_PRIVATE_DIALOG_INDEX
;;
;; MessageText:
;;
;;  Using private DIALOG window words.
;;
ERROR_PRIVATE_DIALOG_INDEX	equ 1415

;;
;; MessageId: ERROR_LISTBOX_ID_NOT_FOUND
;;
;; MessageText:
;;
;;  The list box identifier was not found.
;;
ERROR_LISTBOX_ID_NOT_FOUND	equ 1416

;;
;; MessageId: ERROR_NO_WILDCARD_CHARACTERS
;;
;; MessageText:
;;
;;  No wildcards were found.
;;
ERROR_NO_WILDCARD_CHARACTERS	equ 1417

;;
;; MessageId: ERROR_CLIPBOARD_NOT_OPEN
;;
;; MessageText:
;;
;;  Thread does not have a clipboard open.
;;
ERROR_CLIPBOARD_NOT_OPEN	equ 1418

;;
;; MessageId: ERROR_HOTKEY_NOT_REGISTERED
;;
;; MessageText:
;;
;;  Hot key is not registered.
;;
ERROR_HOTKEY_NOT_REGISTERED	equ 1419

;;
;; MessageId: ERROR_WINDOW_NOT_DIALOG
;;
;; MessageText:
;;
;;  The window is not a valid dialog window.
;;
ERROR_WINDOW_NOT_DIALOG equ 1420

;;
;; MessageId: ERROR_CONTROL_ID_NOT_FOUND
;;
;; MessageText:
;;
;;  Control ID not found.
;;
ERROR_CONTROL_ID_NOT_FOUND	equ 1421

;;
;; MessageId: ERROR_INVALID_COMBOBOX_MESSAGE
;;
;; MessageText:
;;
;;  Invalid message for a combo box because it does not have an edit control.
;;
ERROR_INVALID_COMBOBOX_MESSAGE	equ 1422

;;
;; MessageId: ERROR_WINDOW_NOT_COMBOBOX
;;
;; MessageText:
;;
;;  The window is not a combo box.
;;
ERROR_WINDOW_NOT_COMBOBOX	equ 1423

;;
;; MessageId: ERROR_INVALID_EDIT_HEIGHT
;;
;; MessageText:
;;
;;  Height must be less than 256.
;;
ERROR_INVALID_EDIT_HEIGHT	equ 1424

;;
;; MessageId: ERROR_DC_NOT_FOUND
;;
;; MessageText:
;;
;;  Invalid device context (DC) handle.
;;
ERROR_DC_NOT_FOUND	equ 1425

;;
;; MessageId: ERROR_INVALID_HOOK_FILTER
;;
;; MessageText:
;;
;;  Invalid hook procedure type.
;;
ERROR_INVALID_HOOK_FILTER	equ 1426

;;
;; MessageId: ERROR_INVALID_FILTER_PROC
;;
;; MessageText:
;;
;;  Invalid hook procedure.
;;
ERROR_INVALID_FILTER_PROC	equ 1427

;;
;; MessageId: ERROR_HOOK_NEEDS_HMOD
;;
;; MessageText:
;;
;;  Cannot set nonlocal hook without a module handle.
;;
ERROR_HOOK_NEEDS_HMOD	equ 1428

;;
;; MessageId: ERROR_GLOBAL_ONLY_HOOK
;;
;; MessageText:
;;
;;  This hook procedure can only be set globally.
;;
ERROR_GLOBAL_ONLY_HOOK	equ 1429

;;
;; MessageId: ERROR_JOURNAL_HOOK_SET
;;
;; MessageText:
;;
;;  The journal hook procedure is already installed.
;;
ERROR_JOURNAL_HOOK_SET	equ 1430

;;
;; MessageId: ERROR_HOOK_NOT_INSTALLED
;;
;; MessageText:
;;
;;  The hook procedure is not installed.
;;
ERROR_HOOK_NOT_INSTALLED	equ 1431

;;
;; MessageId: ERROR_INVALID_LB_MESSAGE
;;
;; MessageText:
;;
;;  Invalid message for single-selection list box.
;;
ERROR_INVALID_LB_MESSAGE	equ 1432

;;
;; MessageId: ERROR_SETCOUNT_ON_BAD_LB
;;
;; MessageText:
;;
;;  LB_SETCOUNT sent to non-lazy list box.
;;
ERROR_SETCOUNT_ON_BAD_LB	equ 1433

;;
;; MessageId: ERROR_LB_WITHOUT_TABSTOPS
;;
;; MessageText:
;;
;;  This list box does not support tab stops.
;;
ERROR_LB_WITHOUT_TABSTOPS	equ 1434

;;
;; MessageId: ERROR_DESTROY_OBJECT_OF_OTHER_THREAD
;;
;; MessageText:
;;
;;  Cannot destroy object created by another thread.
;;
ERROR_DESTROY_OBJECT_OF_OTHER_THREAD	equ 1435

;;
;; MessageId: ERROR_CHILD_WINDOW_MENU
;;
;; MessageText:
;;
;;  Child windows cannot have menus.
;;
ERROR_CHILD_WINDOW_MENU equ 1436

;;
;; MessageId: ERROR_NO_SYSTEM_MENU
;;
;; MessageText:
;;
;;  The window does not have a system menu.
;;
ERROR_NO_SYSTEM_MENU	equ 1437

;;
;; MessageId: ERROR_INVALID_MSGBOX_STYLE
;;
;; MessageText:
;;
;;  Invalid message box style.
;;
ERROR_INVALID_MSGBOX_STYLE	equ 1438

;;
;; MessageId: ERROR_INVALID_SPI_VALUE
;;
;; MessageText:
;;
;;  Invalid system-wide (SPI_*) parameter.
;;
ERROR_INVALID_SPI_VALUE equ 1439

;;
;; MessageId: ERROR_SCREEN_ALREADY_LOCKED
;;
;; MessageText:
;;
;;  Screen already locked.
;;
ERROR_SCREEN_ALREADY_LOCKED	equ 1440

;;
;; MessageId: ERROR_HWNDS_HAVE_DIFF_PARENT
;;
;; MessageText:
;;
;;  All handles to windows in a multiple-window position structure must
;;  have the same parent.
;;
ERROR_HWNDS_HAVE_DIFF_PARENT	equ 1441

;;
;; MessageId: ERROR_NOT_CHILD_WINDOW
;;
;; MessageText:
;;
;;  The window is not a child window.
;;
ERROR_NOT_CHILD_WINDOW	equ 1442

;;
;; MessageId: ERROR_INVALID_GW_COMMAND
;;
;; MessageText:
;;
;;  Invalid GW_* command.
;;
ERROR_INVALID_GW_COMMAND	equ 1443

;;
;; MessageId: ERROR_INVALID_THREAD_ID
;;
;; MessageText:
;;
;;  Invalid thread identifier.
;;
ERROR_INVALID_THREAD_ID equ 1444

;;
;; MessageId: ERROR_NON_MDICHILD_WINDOW
;;
;; MessageText:
;;
;;  Cannot process a message from a window that is not a multiple document
;;  interface (MDI) window.
;;
ERROR_NON_MDICHILD_WINDOW	equ 1445

;;
;; MessageId: ERROR_POPUP_ALREADY_ACTIVE
;;
;; MessageText:
;;
;;  Popup menu already active.
;;
ERROR_POPUP_ALREADY_ACTIVE	equ 1446

;;
;; MessageId: ERROR_NO_SCROLLBARS
;;
;; MessageText:
;;
;;  The window does not have scroll bars.
;;
ERROR_NO_SCROLLBARS	equ 1447

;;
;; MessageId: ERROR_INVALID_SCROLLBAR_RANGE
;;
;; MessageText:
;;
;;  Scroll bar range cannot be greater than 0x7FFF.
;;
ERROR_INVALID_SCROLLBAR_RANGE	equ 1448

;;
;; MessageId: ERROR_INVALID_SHOWWIN_COMMAND
;;
;; MessageText:
;;
;;  Cannot show or remove the window in the way specified.
;;
ERROR_INVALID_SHOWWIN_COMMAND	equ 1449

;;
;; MessageId: ERROR_NO_SYSTEM_RESOURCES
;;
;; MessageText:
;;
;;  Insufficient system resources exist to complete the requested service.
;;
ERROR_NO_SYSTEM_RESOURCES	equ 1450

;;
;; MessageId: ERROR_NONPAGED_SYSTEM_RESOURCES
;;
;; MessageText:
;;
;;  Insufficient system resources exist to complete the requested service.
;;
ERROR_NONPAGED_SYSTEM_RESOURCES equ 1451

;;
;; MessageId: ERROR_PAGED_SYSTEM_RESOURCES
;;
;; MessageText:
;;
;;  Insufficient system resources exist to complete the requested service.
;;
ERROR_PAGED_SYSTEM_RESOURCES	equ 1452

;;
;; MessageId: ERROR_WORKING_SET_QUOTA
;;
;; MessageText:
;;
;;  Insufficient quota to complete the requested service.
;;
ERROR_WORKING_SET_QUOTA equ 1453

;;
;; MessageId: ERROR_PAGEFILE_QUOTA
;;
;; MessageText:
;;
;;  Insufficient quota to complete the requested service.
;;
ERROR_PAGEFILE_QUOTA	equ 1454

;;
;; MessageId: ERROR_COMMITMENT_LIMIT
;;
;; MessageText:
;;
;;  The paging file is too small for this operation to complete.
;;
ERROR_COMMITMENT_LIMIT	equ 1455

;;
;; MessageId: ERROR_MENU_ITEM_NOT_FOUND
;;
;; MessageText:
;;
;;  A menu item was not found.
;;
ERROR_MENU_ITEM_NOT_FOUND	equ 1456

;;
;; MessageId: ERROR_INVALID_KEYBOARD_HANDLE
;;
;; MessageText:
;;
;;  Invalid keyboard layout handle.
;;
ERROR_INVALID_KEYBOARD_HANDLE	equ 1457

;;
;; MessageId: ERROR_HOOK_TYPE_NOT_ALLOWED
;;
;; MessageText:
;;
;;  Hook type not allowed.
;;
ERROR_HOOK_TYPE_NOT_ALLOWED	equ 1458

;;
;; MessageId: ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION
;;
;; MessageText:
;;
;;  This operation requires an interactive window station.
;;
ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION	equ 1459

;;
;; MessageId: ERROR_TIMEOUT
;;
;; MessageText:
;;
;;  This operation returned because the timeout period expired.
;;
ERROR_TIMEOUT	equ 1460

;;
;; MessageId: ERROR_INVALID_MONITOR_HANDLE
;;
;; MessageText:
;;
;;  Invalid monitor handle.
;;
ERROR_INVALID_MONITOR_HANDLE	equ 1461

;; End of WinUser error codes



;;;;/;;/;;/;;/;;/;;/;;/;;//
;;			 ;;
;; Eventlog Status Codes ;;
;;			 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;//


;;
;; MessageId: ERROR_EVENTLOG_FILE_CORRUPT
;;
;; MessageText:
;;
;;  The event log file is corrupted.
;;
ERROR_EVENTLOG_FILE_CORRUPT	equ 1500

;;
;; MessageId: ERROR_EVENTLOG_CANT_START
;;
;; MessageText:
;;
;;  No event log file could be opened, so the event logging service did not start.
;;
ERROR_EVENTLOG_CANT_START	equ 1501

;;
;; MessageId: ERROR_LOG_FILE_FULL
;;
;; MessageText:
;;
;;  The event log file is full.
;;
ERROR_LOG_FILE_FULL	equ 1502

;;
;; MessageId: ERROR_EVENTLOG_FILE_CHANGED
;;
;; MessageText:
;;
;;  The event log file has changed between read operations.
;;
ERROR_EVENTLOG_FILE_CHANGED	equ 1503

;; End of eventlog error codes



;;;;/;;/;;/;;/;;/;;/;;/;;//
;;			 ;;
;; MSI Error Codes	 ;;
;;			 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;//


;;
;; MessageId: ERROR_INSTALL_SERVICE
;;
;; MessageText:
;;
;;  Failure accessing install service.
;;
ERROR_INSTALL_SERVICE	equ 1601

;;
;; MessageId: ERROR_INSTALL_USEREXIT
;;
;; MessageText:
;;
;;  The user canceled the installation.
;;
ERROR_INSTALL_USEREXIT	equ 1602

;;
;; MessageId: ERROR_INSTALL_FAILURE
;;
;; MessageText:
;;
;;  Fatal error during installation.
;;
ERROR_INSTALL_FAILURE	equ 1603

;;
;; MessageId: ERROR_INSTALL_SUSPEND
;;
;; MessageText:
;;
;;  Installation suspended, incomplete.
;;
ERROR_INSTALL_SUSPEND	equ 1604

;;
;; MessageId: ERROR_UNKNOWN_PRODUCT
;;
;; MessageText:
;;
;;  Product code not registered.
;;
ERROR_UNKNOWN_PRODUCT	equ 1605

;;
;; MessageId: ERROR_UNKNOWN_FEATURE
;;
;; MessageText:
;;
;;  Feature ID not registered.
;;
ERROR_UNKNOWN_FEATURE	equ 1606

;;
;; MessageId: ERROR_UNKNOWN_COMPONENT
;;
;; MessageText:
;;
;;  Component ID not registered.
;;
ERROR_UNKNOWN_COMPONENT equ 1607

;;
;; MessageId: ERROR_UNKNOWN_PROPERTY
;;
;; MessageText:
;;
;;  Unknown property.
;;
ERROR_UNKNOWN_PROPERTY	equ 1608

;;
;; MessageId: ERROR_INVALID_HANDLE_STATE
;;
;; MessageText:
;;
;;  Handle is in an invalid state.
;;
ERROR_INVALID_HANDLE_STATE	equ 1609

;;
;; MessageId: ERROR_BAD_CONFIGURATION
;;
;; MessageText:
;;
;;  Configuration data corrupt.
;;
ERROR_BAD_CONFIGURATION equ 1610

;;
;; MessageId: ERROR_INDEX_ABSENT
;;
;; MessageText:
;;
;;  Language not available.
;;
ERROR_INDEX_ABSENT	equ 1611

;;
;; MessageId: ERROR_INSTALL_SOURCE_ABSENT
;;
;; MessageText:
;;
;;  Install source unavailable.
;;
ERROR_INSTALL_SOURCE_ABSENT	equ 1612

;;
;; MessageId: ERROR_BAD_DATABASE_VERSION
;;
;; MessageText:
;;
;;  Database version unsupported.
;;
ERROR_BAD_DATABASE_VERSION	equ 1613

;;
;; MessageId: ERROR_PRODUCT_UNINSTALLED
;;
;; MessageText:
;;
;;  Product is uninstalled.
;;
ERROR_PRODUCT_UNINSTALLED	equ 1614

;;
;; MessageId: ERROR_BAD_QUERY_SYNTAX
;;
;; MessageText:
;;
;;  SQL query syntax invalid or unsupported.
;;
ERROR_BAD_QUERY_SYNTAX	equ 1615

;;
;; MessageId: ERROR_INVALID_FIELD
;;
;; MessageText:
;;
;;  Record field does not exist.
;;
ERROR_INVALID_FIELD	equ 1616

;; End of MSI error codes



;;;;/;;/;;/;;/;;/;;/;;/;;//
;;			 ;;
;;   RPC Status Codes	 ;;
;;			 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;//


;;
;; MessageId: RPC_S_INVALID_STRING_BINDING
;;
;; MessageText:
;;
;;  The string binding is invalid.
;;
RPC_S_INVALID_STRING_BINDING	equ 1700

;;
;; MessageId: RPC_S_WRONG_KIND_OF_BINDING
;;
;; MessageText:
;;
;;  The binding handle is not the correct type.
;;
RPC_S_WRONG_KIND_OF_BINDING	equ 1701

;;
;; MessageId: RPC_S_INVALID_BINDING
;;
;; MessageText:
;;
;;  The binding handle is invalid.
;;
RPC_S_INVALID_BINDING	equ 1702

;;
;; MessageId: RPC_S_PROTSEQ_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The RPC protocol sequence is not supported.
;;
RPC_S_PROTSEQ_NOT_SUPPORTED	equ 1703

;;
;; MessageId: RPC_S_INVALID_RPC_PROTSEQ
;;
;; MessageText:
;;
;;  The RPC protocol sequence is invalid.
;;
RPC_S_INVALID_RPC_PROTSEQ	equ 1704

;;
;; MessageId: RPC_S_INVALID_STRING_UUID
;;
;; MessageText:
;;
;;  The string universal unique identifier (UUID) is invalid.
;;
RPC_S_INVALID_STRING_UUID	equ 1705

;;
;; MessageId: RPC_S_INVALID_ENDPOINT_FORMAT
;;
;; MessageText:
;;
;;  The endpoint format is invalid.
;;
RPC_S_INVALID_ENDPOINT_FORMAT	equ 1706

;;
;; MessageId: RPC_S_INVALID_NET_ADDR
;;
;; MessageText:
;;
;;  The network address is invalid.
;;
RPC_S_INVALID_NET_ADDR	equ 1707

;;
;; MessageId: RPC_S_NO_ENDPOINT_FOUND
;;
;; MessageText:
;;
;;  No endpoint was found.
;;
RPC_S_NO_ENDPOINT_FOUND equ 1708

;;
;; MessageId: RPC_S_INVALID_TIMEOUT
;;
;; MessageText:
;;
;;  The timeout value is invalid.
;;
RPC_S_INVALID_TIMEOUT	equ 1709

;;
;; MessageId: RPC_S_OBJECT_NOT_FOUND
;;
;; MessageText:
;;
;;  The object universal unique identifier (UUID) was not found.
;;
RPC_S_OBJECT_NOT_FOUND	equ 1710

;;
;; MessageId: RPC_S_ALREADY_REGISTERED
;;
;; MessageText:
;;
;;  The object universal unique identifier (UUID) has already been registered.
;;
RPC_S_ALREADY_REGISTERED	equ 1711

;;
;; MessageId: RPC_S_TYPE_ALREADY_REGISTERED
;;
;; MessageText:
;;
;;  The type universal unique identifier (UUID) has already been registered.
;;
RPC_S_TYPE_ALREADY_REGISTERED	equ 1712

;;
;; MessageId: RPC_S_ALREADY_LISTENING
;;
;; MessageText:
;;
;;  The RPC server is already listening.
;;
RPC_S_ALREADY_LISTENING equ 1713

;;
;; MessageId: RPC_S_NO_PROTSEQS_REGISTERED
;;
;; MessageText:
;;
;;  No protocol sequences have been registered.
;;
RPC_S_NO_PROTSEQS_REGISTERED	equ 1714

;;
;; MessageId: RPC_S_NOT_LISTENING
;;
;; MessageText:
;;
;;  The RPC server is not listening.
;;
RPC_S_NOT_LISTENING	equ 1715

;;
;; MessageId: RPC_S_UNKNOWN_MGR_TYPE
;;
;; MessageText:
;;
;;  The manager type is unknown.
;;
RPC_S_UNKNOWN_MGR_TYPE	equ 1716

;;
;; MessageId: RPC_S_UNKNOWN_IF
;;
;; MessageText:
;;
;;  The interface is unknown.
;;
RPC_S_UNKNOWN_IF	equ 1717

;;
;; MessageId: RPC_S_NO_BINDINGS
;;
;; MessageText:
;;
;;  There are no bindings.
;;
RPC_S_NO_BINDINGS	equ 1718

;;
;; MessageId: RPC_S_NO_PROTSEQS
;;
;; MessageText:
;;
;;  There are no protocol sequences.
;;
RPC_S_NO_PROTSEQS	equ 1719

;;
;; MessageId: RPC_S_CANT_CREATE_ENDPOINT
;;
;; MessageText:
;;
;;  The endpoint cannot be created.
;;
RPC_S_CANT_CREATE_ENDPOINT	equ 1720

;;
;; MessageId: RPC_S_OUT_OF_RESOURCES
;;
;; MessageText:
;;
;;  Not enough resources are available to complete this operation.
;;
RPC_S_OUT_OF_RESOURCES	equ 1721

;;
;; MessageId: RPC_S_SERVER_UNAVAILABLE
;;
;; MessageText:
;;
;;  The RPC server is unavailable.
;;
RPC_S_SERVER_UNAVAILABLE	equ 1722

;;
;; MessageId: RPC_S_SERVER_TOO_BUSY
;;
;; MessageText:
;;
;;  The RPC server is too busy to complete this operation.
;;
RPC_S_SERVER_TOO_BUSY	equ 1723

;;
;; MessageId: RPC_S_INVALID_NETWORK_OPTIONS
;;
;; MessageText:
;;
;;  The network options are invalid.
;;
RPC_S_INVALID_NETWORK_OPTIONS	equ 1724

;;
;; MessageId: RPC_S_NO_CALL_ACTIVE
;;
;; MessageText:
;;
;;  There are no remote procedure calls active on this thread.
;;
RPC_S_NO_CALL_ACTIVE	equ 1725

;;
;; MessageId: RPC_S_CALL_FAILED
;;
;; MessageText:
;;
;;  The remote procedure call failed.
;;
RPC_S_CALL_FAILED	equ 1726

;;
;; MessageId: RPC_S_CALL_FAILED_DNE
;;
;; MessageText:
;;
;;  The remote procedure call failed and did not execute.
;;
RPC_S_CALL_FAILED_DNE	equ 1727

;;
;; MessageId: RPC_S_PROTOCOL_ERROR
;;
;; MessageText:
;;
;;  A remote procedure call (RPC) protocol error occurred.
;;
RPC_S_PROTOCOL_ERROR	equ 1728

;;
;; MessageId: RPC_S_UNSUPPORTED_TRANS_SYN
;;
;; MessageText:
;;
;;  The transfer syntax is not supported by the RPC server.
;;
RPC_S_UNSUPPORTED_TRANS_SYN	equ 1730

;;
;; MessageId: RPC_S_UNSUPPORTED_TYPE
;;
;; MessageText:
;;
;;  The universal unique identifier (UUID) type is not supported.
;;
RPC_S_UNSUPPORTED_TYPE	equ 1732

;;
;; MessageId: RPC_S_INVALID_TAG
;;
;; MessageText:
;;
;;  The tag is invalid.
;;
RPC_S_INVALID_TAG	equ 1733

;;
;; MessageId: RPC_S_INVALID_BOUND
;;
;; MessageText:
;;
;;  The array bounds are invalid.
;;
RPC_S_INVALID_BOUND	equ 1734

;;
;; MessageId: RPC_S_NO_ENTRY_NAME
;;
;; MessageText:
;;
;;  The binding does not contain an entry name.
;;
RPC_S_NO_ENTRY_NAME	equ 1735

;;
;; MessageId: RPC_S_INVALID_NAME_SYNTAX
;;
;; MessageText:
;;
;;  The name syntax is invalid.
;;
RPC_S_INVALID_NAME_SYNTAX	equ 1736

;;
;; MessageId: RPC_S_UNSUPPORTED_NAME_SYNTAX
;;
;; MessageText:
;;
;;  The name syntax is not supported.
;;
RPC_S_UNSUPPORTED_NAME_SYNTAX	equ 1737

;;
;; MessageId: RPC_S_UUID_NO_ADDRESS
;;
;; MessageText:
;;
;;  No network address is available to use to construct a universal
;;  unique identifier (UUID).
;;
RPC_S_UUID_NO_ADDRESS	equ 1739

;;
;; MessageId: RPC_S_DUPLICATE_ENDPOINT
;;
;; MessageText:
;;
;;  The endpoint is a duplicate.
;;
RPC_S_DUPLICATE_ENDPOINT	equ 1740

;;
;; MessageId: RPC_S_UNKNOWN_AUTHN_TYPE
;;
;; MessageText:
;;
;;  The authentication type is unknown.
;;
RPC_S_UNKNOWN_AUTHN_TYPE	equ 1741

;;
;; MessageId: RPC_S_MAX_CALLS_TOO_SMALL
;;
;; MessageText:
;;
;;  The maximum number of calls is too small.
;;
RPC_S_MAX_CALLS_TOO_SMALL	equ 1742

;;
;; MessageId: RPC_S_STRING_TOO_LONG
;;
;; MessageText:
;;
;;  The string is too long.
;;
RPC_S_STRING_TOO_LONG	equ 1743

;;
;; MessageId: RPC_S_PROTSEQ_NOT_FOUND
;;
;; MessageText:
;;
;;  The RPC protocol sequence was not found.
;;
RPC_S_PROTSEQ_NOT_FOUND equ 1744

;;
;; MessageId: RPC_S_PROCNUM_OUT_OF_RANGE
;;
;; MessageText:
;;
;;  The procedure number is out of range.
;;
RPC_S_PROCNUM_OUT_OF_RANGE	equ 1745

;;
;; MessageId: RPC_S_BINDING_HAS_NO_AUTH
;;
;; MessageText:
;;
;;  The binding does not contain any authentication information.
;;
RPC_S_BINDING_HAS_NO_AUTH	equ 1746

;;
;; MessageId: RPC_S_UNKNOWN_AUTHN_SERVICE
;;
;; MessageText:
;;
;;  The authentication service is unknown.
;;
RPC_S_UNKNOWN_AUTHN_SERVICE	equ 1747

;;
;; MessageId: RPC_S_UNKNOWN_AUTHN_LEVEL
;;
;; MessageText:
;;
;;  The authentication level is unknown.
;;
RPC_S_UNKNOWN_AUTHN_LEVEL	equ 1748

;;
;; MessageId: RPC_S_INVALID_AUTH_IDENTITY
;;
;; MessageText:
;;
;;  The security context is invalid.
;;
RPC_S_INVALID_AUTH_IDENTITY	equ 1749

;;
;; MessageId: RPC_S_UNKNOWN_AUTHZ_SERVICE
;;
;; MessageText:
;;
;;  The authorization service is unknown.
;;
RPC_S_UNKNOWN_AUTHZ_SERVICE	equ 1750

;;
;; MessageId: EPT_S_INVALID_ENTRY
;;
;; MessageText:
;;
;;  The entry is invalid.
;;
EPT_S_INVALID_ENTRY	equ 1751

;;
;; MessageId: EPT_S_CANT_PERFORM_OP
;;
;; MessageText:
;;
;;  The server endpoint cannot perform the operation.
;;
EPT_S_CANT_PERFORM_OP	equ 1752

;;
;; MessageId: EPT_S_NOT_REGISTERED
;;
;; MessageText:
;;
;;  There are no more endpoints available from the endpoint mapper.
;;
EPT_S_NOT_REGISTERED	equ 1753

;;
;; MessageId: RPC_S_NOTHING_TO_EXPORT
;;
;; MessageText:
;;
;;  No interfaces have been exported.
;;
RPC_S_NOTHING_TO_EXPORT equ 1754

;;
;; MessageId: RPC_S_INCOMPLETE_NAME
;;
;; MessageText:
;;
;;  The entry name is incomplete.
;;
RPC_S_INCOMPLETE_NAME	equ 1755

;;
;; MessageId: RPC_S_INVALID_VERS_OPTION
;;
;; MessageText:
;;
;;  The version option is invalid.
;;
RPC_S_INVALID_VERS_OPTION	equ 1756

;;
;; MessageId: RPC_S_NO_MORE_MEMBERS
;;
;; MessageText:
;;
;;  There are no more members.
;;
RPC_S_NO_MORE_MEMBERS	equ 1757

;;
;; MessageId: RPC_S_NOT_ALL_OBJS_UNEXPORTED
;;
;; MessageText:
;;
;;  There is nothing to unexport.
;;
RPC_S_NOT_ALL_OBJS_UNEXPORTED	equ 1758

;;
;; MessageId: RPC_S_INTERFACE_NOT_FOUND
;;
;; MessageText:
;;
;;  The interface was not found.
;;
RPC_S_INTERFACE_NOT_FOUND	equ 1759

;;
;; MessageId: RPC_S_ENTRY_ALREADY_EXISTS
;;
;; MessageText:
;;
;;  The entry already exists.
;;
RPC_S_ENTRY_ALREADY_EXISTS	equ 1760

;;
;; MessageId: RPC_S_ENTRY_NOT_FOUND
;;
;; MessageText:
;;
;;  The entry is not found.
;;
RPC_S_ENTRY_NOT_FOUND	equ 1761

;;
;; MessageId: RPC_S_NAME_SERVICE_UNAVAILABLE
;;
;; MessageText:
;;
;;  The name service is unavailable.
;;
RPC_S_NAME_SERVICE_UNAVAILABLE	equ 1762

;;
;; MessageId: RPC_S_INVALID_NAF_ID
;;
;; MessageText:
;;
;;  The network address family is invalid.
;;
RPC_S_INVALID_NAF_ID	equ 1763

;;
;; MessageId: RPC_S_CANNOT_SUPPORT
;;
;; MessageText:
;;
;;  The requested operation is not supported.
;;
RPC_S_CANNOT_SUPPORT	equ 1764

;;
;; MessageId: RPC_S_NO_CONTEXT_AVAILABLE
;;
;; MessageText:
;;
;;  No security context is available to allow impersonation.
;;
RPC_S_NO_CONTEXT_AVAILABLE	equ 1765

;;
;; MessageId: RPC_S_INTERNAL_ERROR
;;
;; MessageText:
;;
;;  An internal error occurred in a remote procedure call (RPC).
;;
RPC_S_INTERNAL_ERROR	equ 1766

;;
;; MessageId: RPC_S_ZERO_DIVIDE
;;
;; MessageText:
;;
;;  The RPC server attempted an integer division by zero.
;;
RPC_S_ZERO_DIVIDE	equ 1767

;;
;; MessageId: RPC_S_ADDRESS_ERROR
;;
;; MessageText:
;;
;;  An addressing error occurred in the RPC server.
;;
RPC_S_ADDRESS_ERROR	equ 1768

;;
;; MessageId: RPC_S_FP_DIV_ZERO
;;
;; MessageText:
;;
;;  A floating-point operation at the RPC server caused a division by zero.
;;
RPC_S_FP_DIV_ZERO	equ 1769

;;
;; MessageId: RPC_S_FP_UNDERFLOW
;;
;; MessageText:
;;
;;  A floating-point underflow occurred at the RPC server.
;;
RPC_S_FP_UNDERFLOW	equ 1770

;;
;; MessageId: RPC_S_FP_OVERFLOW
;;
;; MessageText:
;;
;;  A floating-point overflow occurred at the RPC server.
;;
RPC_S_FP_OVERFLOW	equ 1771

;;
;; MessageId: RPC_X_NO_MORE_ENTRIES
;;
;; MessageText:
;;
;;  The list of RPC servers available for the binding of auto handles
;;  has been exhausted.
;;
RPC_X_NO_MORE_ENTRIES	equ 1772

;;
;; MessageId: RPC_X_SS_CHAR_TRANS_OPEN_FAIL
;;
;; MessageText:
;;
;;  Unable to open the character translation table file.
;;
RPC_X_SS_CHAR_TRANS_OPEN_FAIL	equ 1773

;;
;; MessageId: RPC_X_SS_CHAR_TRANS_SHORT_FILE
;;
;; MessageText:
;;
;;  The file containing the character translation table has fewer than
;;  512 bytes.
;;
RPC_X_SS_CHAR_TRANS_SHORT_FILE	equ 1774

;;
;; MessageId: RPC_X_SS_IN_NULL_CONTEXT
;;
;; MessageText:
;;
;;  A null context handle was passed from the client to the host during
;;  a remote procedure call.
;;
RPC_X_SS_IN_NULL_CONTEXT	equ 1775

;;
;; MessageId: RPC_X_SS_CONTEXT_DAMAGED
;;
;; MessageText:
;;
;;  The context handle changed during a remote procedure call.
;;
RPC_X_SS_CONTEXT_DAMAGED	equ 1777

;;
;; MessageId: RPC_X_SS_HANDLES_MISMATCH
;;
;; MessageText:
;;
;;  The binding handles passed to a remote procedure call do not match.
;;
RPC_X_SS_HANDLES_MISMATCH	equ 1778

;;
;; MessageId: RPC_X_SS_CANNOT_GET_CALL_HANDLE
;;
;; MessageText:
;;
;;  The stub is unable to get the remote procedure call handle.
;;
RPC_X_SS_CANNOT_GET_CALL_HANDLE equ 1779

;;
;; MessageId: RPC_X_NULL_REF_POINTER
;;
;; MessageText:
;;
;;  A null reference pointer was passed to the stub.
;;
RPC_X_NULL_REF_POINTER	equ 1780

;;
;; MessageId: RPC_X_ENUM_VALUE_OUT_OF_RANGE
;;
;; MessageText:
;;
;;  The enumeration value is out of range.
;;
RPC_X_ENUM_VALUE_OUT_OF_RANGE	equ 1781

;;
;; MessageId: RPC_X_BYTE_COUNT_TOO_SMALL
;;
;; MessageText:
;;
;;  The byte count is too small.
;;
RPC_X_BYTE_COUNT_TOO_SMALL	equ 1782

;;
;; MessageId: RPC_X_BAD_STUB_DATA
;;
;; MessageText:
;;
;;  The stub received bad data.
;;
RPC_X_BAD_STUB_DATA	equ 1783

;;
;; MessageId: ERROR_INVALID_USER_BUFFER
;;
;; MessageText:
;;
;;  The supplied user buffer is not valid for the requested operation.
;;
ERROR_INVALID_USER_BUFFER	equ 1784

;;
;; MessageId: ERROR_UNRECOGNIZED_MEDIA
;;
;; MessageText:
;;
;;  The disk media is not recognized.  It may not be formatted.
;;
ERROR_UNRECOGNIZED_MEDIA	equ 1785

;;
;; MessageId: ERROR_NO_TRUST_LSA_SECRET
;;
;; MessageText:
;;
;;  The workstation does not have a trust secret.
;;
ERROR_NO_TRUST_LSA_SECRET	equ 1786

;;
;; MessageId: ERROR_NO_TRUST_SAM_ACCOUNT
;;
;; MessageText:
;;
;;  The SAM database on the Windows NT Server does not have a computer
;;  account for this workstation trust relationship.
;;
ERROR_NO_TRUST_SAM_ACCOUNT	equ 1787

;;
;; MessageId: ERROR_TRUSTED_DOMAIN_FAILURE
;;
;; MessageText:
;;
;;  The trust relationship between the primary domain and the trusted
;;  domain failed.
;;
ERROR_TRUSTED_DOMAIN_FAILURE	equ 1788

;;
;; MessageId: ERROR_TRUSTED_RELATIONSHIP_FAILURE
;;
;; MessageText:
;;
;;  The trust relationship between this workstation and the primary
;;  domain failed.
;;
ERROR_TRUSTED_RELATIONSHIP_FAILURE	equ 1789

;;
;; MessageId: ERROR_TRUST_FAILURE
;;
;; MessageText:
;;
;;  The network logon failed.
;;
ERROR_TRUST_FAILURE	equ 1790

;;
;; MessageId: RPC_S_CALL_IN_PROGRESS
;;
;; MessageText:
;;
;;  A remote procedure call is already in progress for this thread.
;;
RPC_S_CALL_IN_PROGRESS	equ 1791

;;
;; MessageId: ERROR_NETLOGON_NOT_STARTED
;;
;; MessageText:
;;
;;  An attempt was made to logon, but the network logon service was not started.
;;
ERROR_NETLOGON_NOT_STARTED	equ 1792

;;
;; MessageId: ERROR_ACCOUNT_EXPIRED
;;
;; MessageText:
;;
;;  The user's account has expired.
;;
ERROR_ACCOUNT_EXPIRED	equ 1793

;;
;; MessageId: ERROR_REDIRECTOR_HAS_OPEN_HANDLES
;;
;; MessageText:
;;
;;  The redirector is in use and cannot be unloaded.
;;
ERROR_REDIRECTOR_HAS_OPEN_HANDLES	equ 1794

;;
;; MessageId: ERROR_PRINTER_DRIVER_ALREADY_INSTALLED
;;
;; MessageText:
;;
;;  The specified printer driver is already installed.
;;
ERROR_PRINTER_DRIVER_ALREADY_INSTALLED	equ 1795

;;
;; MessageId: ERROR_UNKNOWN_PORT
;;
;; MessageText:
;;
;;  The specified port is unknown.
;;
ERROR_UNKNOWN_PORT	equ 1796

;;
;; MessageId: ERROR_UNKNOWN_PRINTER_DRIVER
;;
;; MessageText:
;;
;;  The printer driver is unknown.
;;
ERROR_UNKNOWN_PRINTER_DRIVER	equ 1797

;;
;; MessageId: ERROR_UNKNOWN_PRINTPROCESSOR
;;
;; MessageText:
;;
;;  The print processor is unknown.
;;
ERROR_UNKNOWN_PRINTPROCESSOR	equ 1798

;;
;; MessageId: ERROR_INVALID_SEPARATOR_FILE
;;
;; MessageText:
;;
;;  The specified separator file is invalid.
;;
ERROR_INVALID_SEPARATOR_FILE	equ 1799

;;
;; MessageId: ERROR_INVALID_PRIORITY
;;
;; MessageText:
;;
;;  The specified priority is invalid.
;;
ERROR_INVALID_PRIORITY	equ 1800

;;
;; MessageId: ERROR_INVALID_PRINTER_NAME
;;
;; MessageText:
;;
;;  The printer name is invalid.
;;
ERROR_INVALID_PRINTER_NAME	equ 1801

;;
;; MessageId: ERROR_PRINTER_ALREADY_EXISTS
;;
;; MessageText:
;;
;;  The printer already exists.
;;
ERROR_PRINTER_ALREADY_EXISTS	equ 1802

;;
;; MessageId: ERROR_INVALID_PRINTER_COMMAND
;;
;; MessageText:
;;
;;  The printer command is invalid.
;;
ERROR_INVALID_PRINTER_COMMAND	equ 1803

;;
;; MessageId: ERROR_INVALID_DATATYPE
;;
;; MessageText:
;;
;;  The specified datatype is invalid.
;;
ERROR_INVALID_DATATYPE	equ 1804

;;
;; MessageId: ERROR_INVALID_ENVIRONMENT
;;
;; MessageText:
;;
;;  The environment specified is invalid.
;;
ERROR_INVALID_ENVIRONMENT	equ 1805

;;
;; MessageId: RPC_S_NO_MORE_BINDINGS
;;
;; MessageText:
;;
;;  There are no more bindings.
;;
RPC_S_NO_MORE_BINDINGS	equ 1806

;;
;; MessageId: ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT
;;
;; MessageText:
;;
;;  The account used is an interdomain trust account.  Use your global user account or local user account to access this server.
;;
ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT equ 1807

;;
;; MessageId: ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT
;;
;; MessageText:
;;
;;  The account used is a computer account.  Use your global user account or local user account to access this server.
;;
ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT equ 1808

;;
;; MessageId: ERROR_NOLOGON_SERVER_TRUST_ACCOUNT
;;
;; MessageText:
;;
;;  The account used is a server trust account. Use your global user account or local user account to access this server.
;;
ERROR_NOLOGON_SERVER_TRUST_ACCOUNT	equ 1809

;;
;; MessageId: ERROR_DOMAIN_TRUST_INCONSISTENT
;;
;; MessageText:
;;
;;  The name or security ID (SID) of the domain specified is inconsistent
;;  with the trust information for that domain.
;;
ERROR_DOMAIN_TRUST_INCONSISTENT equ 1810

;;
;; MessageId: ERROR_SERVER_HAS_OPEN_HANDLES
;;
;; MessageText:
;;
;;  The server is in use and cannot be unloaded.
;;
ERROR_SERVER_HAS_OPEN_HANDLES	equ 1811

;;
;; MessageId: ERROR_RESOURCE_DATA_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified image file did not contain a resource section.
;;
ERROR_RESOURCE_DATA_NOT_FOUND	equ 1812

;;
;; MessageId: ERROR_RESOURCE_TYPE_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified resource type cannot be found in the image file.
;;
ERROR_RESOURCE_TYPE_NOT_FOUND	equ 1813

;;
;; MessageId: ERROR_RESOURCE_NAME_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified resource name cannot be found in the image file.
;;
ERROR_RESOURCE_NAME_NOT_FOUND	equ 1814

;;
;; MessageId: ERROR_RESOURCE_LANG_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified resource language ID cannot be found in the image file.
;;
ERROR_RESOURCE_LANG_NOT_FOUND	equ 1815

;;
;; MessageId: ERROR_NOT_ENOUGH_QUOTA
;;
;; MessageText:
;;
;;  Not enough quota is available to process this command.
;;
ERROR_NOT_ENOUGH_QUOTA	equ 1816

;;
;; MessageId: RPC_S_NO_INTERFACES
;;
;; MessageText:
;;
;;  No interfaces have been registered.
;;
RPC_S_NO_INTERFACES	equ 1817

;;
;; MessageId: RPC_S_CALL_CANCELLED
;;
;; MessageText:
;;
;;  The remote procedure call was cancelled.
;;
RPC_S_CALL_CANCELLED	equ 1818

;;
;; MessageId: RPC_S_BINDING_INCOMPLETE
;;
;; MessageText:
;;
;;  The binding handle does not contain all required information.
;;
RPC_S_BINDING_INCOMPLETE	equ 1819

;;
;; MessageId: RPC_S_COMM_FAILURE
;;
;; MessageText:
;;
;;  A communications failure occurred during a remote procedure call.
;;
RPC_S_COMM_FAILURE	equ 1820

;;
;; MessageId: RPC_S_UNSUPPORTED_AUTHN_LEVEL
;;
;; MessageText:
;;
;;  The requested authentication level is not supported.
;;
RPC_S_UNSUPPORTED_AUTHN_LEVEL	equ 1821

;;
;; MessageId: RPC_S_NO_PRINC_NAME
;;
;; MessageText:
;;
;;  No principal name registered.
;;
RPC_S_NO_PRINC_NAME	equ 1822

;;
;; MessageId: RPC_S_NOT_RPC_ERROR
;;
;; MessageText:
;;
;;  The error specified is not a valid Windows RPC error code.
;;
RPC_S_NOT_RPC_ERROR	equ 1823

;;
;; MessageId: RPC_S_UUID_LOCAL_ONLY
;;
;; MessageText:
;;
;;  A UUID that is valid only on this computer has been allocated.
;;
RPC_S_UUID_LOCAL_ONLY	equ 1824

;;
;; MessageId: RPC_S_SEC_PKG_ERROR
;;
;; MessageText:
;;
;;  A security package specific error occurred.
;;
RPC_S_SEC_PKG_ERROR	equ 1825

;;
;; MessageId: RPC_S_NOT_CANCELLED
;;
;; MessageText:
;;
;;  Thread is not canceled.
;;
RPC_S_NOT_CANCELLED	equ 1826

;;
;; MessageId: RPC_X_INVALID_ES_ACTION
;;
;; MessageText:
;;
;;  Invalid operation on the encoding/decoding handle.
;;
RPC_X_INVALID_ES_ACTION equ 1827

;;
;; MessageId: RPC_X_WRONG_ES_VERSION
;;
;; MessageText:
;;
;;  Incompatible version of the serializing package.
;;
RPC_X_WRONG_ES_VERSION	equ 1828

;;
;; MessageId: RPC_X_WRONG_STUB_VERSION
;;
;; MessageText:
;;
;;  Incompatible version of the RPC stub.
;;
RPC_X_WRONG_STUB_VERSION	equ 1829

;;
;; MessageId: RPC_X_INVALID_PIPE_OBJECT
;;
;; MessageText:
;;
;;  The RPC pipe object is invalid or corrupted.
;;
RPC_X_INVALID_PIPE_OBJECT	equ 1830

;;
;; MessageId: RPC_X_WRONG_PIPE_ORDER
;;
;; MessageText:
;;
;;  An invalid operation was attempted on an RPC pipe object.
;;
RPC_X_WRONG_PIPE_ORDER	equ 1831

;;
;; MessageId: RPC_X_WRONG_PIPE_VERSION
;;
;; MessageText:
;;
;;  Unsupported RPC pipe version.
;;
RPC_X_WRONG_PIPE_VERSION	equ 1832

;;
;; MessageId: RPC_S_GROUP_MEMBER_NOT_FOUND
;;
;; MessageText:
;;
;;  The group member was not found.
;;
RPC_S_GROUP_MEMBER_NOT_FOUND	equ 1898

;;
;; MessageId: EPT_S_CANT_CREATE
;;
;; MessageText:
;;
;;  The endpoint mapper database entry could not be created.
;;
EPT_S_CANT_CREATE	equ 1899

;;
;; MessageId: RPC_S_INVALID_OBJECT
;;
;; MessageText:
;;
;;  The object universal unique identifier (UUID) is the nil UUID.
;;
RPC_S_INVALID_OBJECT	equ 1900

;;
;; MessageId: ERROR_INVALID_TIME
;;
;; MessageText:
;;
;;  The specified time is invalid.
;;
ERROR_INVALID_TIME	equ 1901

;;
;; MessageId: ERROR_INVALID_FORM_NAME
;;
;; MessageText:
;;
;;  The specified form name is invalid.
;;
ERROR_INVALID_FORM_NAME equ 1902

;;
;; MessageId: ERROR_INVALID_FORM_SIZE
;;
;; MessageText:
;;
;;  The specified form size is invalid.
;;
ERROR_INVALID_FORM_SIZE equ 1903

;;
;; MessageId: ERROR_ALREADY_WAITING
;;
;; MessageText:
;;
;;  The specified printer handle is already being waited on
;;
ERROR_ALREADY_WAITING	equ 1904

;;
;; MessageId: ERROR_PRINTER_DELETED
;;
;; MessageText:
;;
;;  The specified printer has been deleted.
;;
ERROR_PRINTER_DELETED	equ 1905

;;
;; MessageId: ERROR_INVALID_PRINTER_STATE
;;
;; MessageText:
;;
;;  The state of the printer is invalid.
;;
ERROR_INVALID_PRINTER_STATE	equ 1906

;;
;; MessageId: ERROR_PASSWORD_MUST_CHANGE
;;
;; MessageText:
;;
;;  The user must change his password before he logs on the first time.
;;
ERROR_PASSWORD_MUST_CHANGE	equ 1907

;;
;; MessageId: ERROR_DOMAIN_CONTROLLER_NOT_FOUND
;;
;; MessageText:
;;
;;  Could not find the domain controller for this domain.
;;
ERROR_DOMAIN_CONTROLLER_NOT_FOUND	equ 1908

;;
;; MessageId: ERROR_ACCOUNT_LOCKED_OUT
;;
;; MessageText:
;;
;;  The referenced account is currently locked out and may not be logged on to.
;;
ERROR_ACCOUNT_LOCKED_OUT	equ 1909

;;
;; MessageId: OR_INVALID_OXID
;;
;; MessageText:
;;
;;  The object exporter specified was not found.
;;
OR_INVALID_OXID equ 1910

;;
;; MessageId: OR_INVALID_OID
;;
;; MessageText:
;;
;;  The object specified was not found.
;;
OR_INVALID_OID	equ 1911

;;
;; MessageId: OR_INVALID_SET
;;
;; MessageText:
;;
;;  The object resolver set specified was not found.
;;
OR_INVALID_SET	equ 1912

;;
;; MessageId: RPC_S_SEND_INCOMPLETE
;;
;; MessageText:
;;
;;  Some data remains to be sent in the request buffer.
;;
RPC_S_SEND_INCOMPLETE	equ 1913

;;
;; MessageId: RPC_S_INVALID_ASYNC_HANDLE
;;
;; MessageText:
;;
;;  Invalid asynchronous remote procedure call handle.
;;
RPC_S_INVALID_ASYNC_HANDLE	equ 1914

;;
;; MessageId: RPC_S_INVALID_ASYNC_CALL
;;
;; MessageText:
;;
;;  Invalid asynchronous RPC call handle for this operation.
;;
RPC_S_INVALID_ASYNC_CALL	equ 1915

;;
;; MessageId: RPC_X_PIPE_CLOSED
;;
;; MessageText:
;;
;;  The RPC pipe object has already been closed.
;;
RPC_X_PIPE_CLOSED	equ 1916

;;
;; MessageId: RPC_X_PIPE_DISCIPLINE_ERROR
;;
;; MessageText:
;;
;;  The RPC call completed before all pipes were processed.
;;
RPC_X_PIPE_DISCIPLINE_ERROR	equ 1917

;;
;; MessageId: RPC_X_PIPE_EMPTY
;;
;; MessageText:
;;
;;  No more data is available from the RPC pipe.
;;
RPC_X_PIPE_EMPTY	equ 1918

;;
;; MessageId: ERROR_NO_SITENAME
;;
;; MessageText:
;;
;;  No site name is available for this machine.
;;
ERROR_NO_SITENAME	equ 1919

;;
;; MessageId: ERROR_CANT_ACCESS_FILE
;;
;; MessageText:
;;
;;  The file can not be accessed by the system.
;;
ERROR_CANT_ACCESS_FILE	equ 1920

;;
;; MessageId: ERROR_CANT_RESOLVE_FILENAME
;;
;; MessageText:
;;
;;  The name of the file cannot be resolved by the system.
;;
ERROR_CANT_RESOLVE_FILENAME	equ 1921

;;
;; MessageId: ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY
;;
;; MessageText:
;;
;;  The directory service evaluated group memberships locally.
;;
ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY	equ 1922

;;
;; MessageId: ERROR_DS_NO_ATTRIBUTE_OR_VALUE
;;
;; MessageText:
;;
;;  The specified directory service attribute or value does not exist.
;;
ERROR_DS_NO_ATTRIBUTE_OR_VALUE	equ 1923

;;
;; MessageId: ERROR_DS_INVALID_ATTRIBUTE_SYNTAX
;;
;; MessageText:
;;
;;  The attribute syntax specified to the directory service is invalid.
;;
ERROR_DS_INVALID_ATTRIBUTE_SYNTAX	equ 1924

;;
;; MessageId: ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED
;;
;; MessageText:
;;
;;  The attribute type specified to the directory service is not defined.
;;
ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED	equ 1925

;;
;; MessageId: ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS
;;
;; MessageText:
;;
;;  The specified directory service attribute or value already exists.
;;
ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS	equ 1926

;;
;; MessageId: ERROR_DS_BUSY
;;
;; MessageText:
;;
;;  The directory service is busy.
;;
ERROR_DS_BUSY	equ 1927

;;
;; MessageId: ERROR_DS_UNAVAILABLE
;;
;; MessageText:
;;
;;  The directory service is unavailable.
;;
ERROR_DS_UNAVAILABLE	equ 1928

;;
;; MessageId: ERROR_DS_NO_RIDS_ALLOCATED
;;
;; MessageText:
;;
;;  The directory service was unable to allocate a relative identifier.
;;
ERROR_DS_NO_RIDS_ALLOCATED	equ 1929

;;
;; MessageId: ERROR_DS_NO_MORE_RIDS
;;
;; MessageText:
;;
;;  The directory service has exhausted the pool of relative identifiers.
;;
ERROR_DS_NO_MORE_RIDS	equ 1930

;;
;; MessageId: ERROR_DS_INCORRECT_ROLE_OWNER
;;
;; MessageText:
;;
;;  The requested operation could not be performed because the directory service is not the
;;  master for that type of operation.
;;
ERROR_DS_INCORRECT_ROLE_OWNER	equ 1931

;;
;; MessageId: ERROR_DS_RIDMGR_INIT_ERROR
;;
;; MessageText:
;;
;;  The directory service was unable to initialize the subsystem that allocates relative identifiers.
;;
ERROR_DS_RIDMGR_INIT_ERROR	equ 1932

;;
;; MessageId: ERROR_DS_OBJ_CLASS_VIOLATION
;;
;; MessageText:
;;
;;  The requested operation did not satisfy one or more constraints associated with the class of the object.
;;
ERROR_DS_OBJ_CLASS_VIOLATION	equ 1933

;;
;; MessageId: ERROR_DS_CANT_ON_NON_LEAF
;;
;; MessageText:
;;
;;  The directory service can perform the requested operation only on a leaf object.
;;
ERROR_DS_CANT_ON_NON_LEAF	equ 1934

;;
;; MessageId: ERROR_DS_CANT_ON_RDN
;;
;; MessageText:
;;
;;  The directory service cannot perform the requested operation on the RDN attribute of an object.
;;
ERROR_DS_CANT_ON_RDN	equ 1935

;;
;; MessageId: ERROR_DS_CANT_MOD_OBJ_CLASS
;;
;; MessageText:
;;
;;  The directory service detected an attempt to modify the object class of an object.
;;
ERROR_DS_CANT_MOD_OBJ_CLASS	equ 1936

;;
;; MessageId: ERROR_DS_CROSS_DOM_MOVE_ERROR
;;
;; MessageText:
;;
;;  The requested cross domain move operation could not be performed.
;;
ERROR_DS_CROSS_DOM_MOVE_ERROR	equ 1937

;;
;; MessageId: ERROR_DS_GC_NOT_AVAILABLE
;;
;; MessageText:
;;
;;  Unable to contact the global catalog server.
;;
ERROR_DS_GC_NOT_AVAILABLE	equ 1938

;;
;; MessageId: ERROR_NO_BROWSER_SERVERS_FOUND
;;
;; MessageText:
;;
;;  The list of servers for this workgroup is not currently available
;;
ERROR_NO_BROWSER_SERVERS_FOUND	equ 6118




;;;;/;;/;;/;;/;;/;;/;;/;;//
;;			 ;;
;;   OpenGL Error Code	 ;;
;;			 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;//


;;
;; MessageId: ERROR_INVALID_PIXEL_FORMAT
;;
;; MessageText:
;;
;;  The pixel format is invalid.
;;
ERROR_INVALID_PIXEL_FORMAT	equ 2000

;;
;; MessageId: ERROR_BAD_DRIVER
;;
;; MessageText:
;;
;;  The specified driver is invalid.
;;
ERROR_BAD_DRIVER	equ 2001

;;
;; MessageId: ERROR_INVALID_WINDOW_STYLE
;;
;; MessageText:
;;
;;  The window style or class attribute is invalid for this operation.
;;
ERROR_INVALID_WINDOW_STYLE	equ 2002

;;
;; MessageId: ERROR_METAFILE_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The requested metafile operation is not supported.
;;
ERROR_METAFILE_NOT_SUPPORTED	equ 2003

;;
;; MessageId: ERROR_TRANSFORM_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The requested transformation operation is not supported.
;;
ERROR_TRANSFORM_NOT_SUPPORTED	equ 2004

;;
;; MessageId: ERROR_CLIPPING_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The requested clipping operation is not supported.
;;
ERROR_CLIPPING_NOT_SUPPORTED	equ 2005

;; End of OpenGL error codes



;;;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;
;;					 ;;
;;   Image Color Management Error Code	 ;;
;;					 ;;
;;;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;


;;
;; MessageId: ERROR_INVALID_CMM
;;
;; MessageText:
;;
;;  The specified color management module is invalid.
;;
ERROR_INVALID_CMM	equ 2300

;;
;; MessageId: ERROR_INVALID_PROFILE
;;
;; MessageText:
;;
;;  The specified color profile is invalid.
;;
ERROR_INVALID_PROFILE	equ 2301

;;
;; MessageId: ERROR_TAG_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified tag was not found.
;;
ERROR_TAG_NOT_FOUND	equ 2302

;;
;; MessageId: ERROR_TAG_NOT_PRESENT
;;
;; MessageText:
;;
;;  A required tag is not present.
;;
ERROR_TAG_NOT_PRESENT	equ 2303

;;
;; MessageId: ERROR_DUPLICATE_TAG
;;
;; MessageText:
;;
;;  The specified tag is already present.
;;
ERROR_DUPLICATE_TAG	equ 2304

;;
;; MessageId: ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE
;;
;; MessageText:
;;
;;  The specified color profile is not associated with any device.
;;
ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE	equ 2305

;;
;; MessageId: ERROR_PROFILE_NOT_FOUND
;;
;; MessageText:
;;
;;  The specified color profile was not found.
;;
ERROR_PROFILE_NOT_FOUND equ 2306

;;
;; MessageId: ERROR_INVALID_COLORSPACE
;;
;; MessageText:
;;
;;  The specified color space is invalid.
;;
ERROR_INVALID_COLORSPACE	equ 2307

;;
;; MessageId: ERROR_ICM_NOT_ENABLED
;;
;; MessageText:
;;
;;  Image Color Management is not enabled.
;;
ERROR_ICM_NOT_ENABLED	equ 2308

;;
;; MessageId: ERROR_DELETING_ICM_XFORM
;;
;; MessageText:
;;
;;  There was an error while deleting the color transform.
;;
ERROR_DELETING_ICM_XFORM	equ 2309

;;
;; MessageId: ERROR_INVALID_TRANSFORM
;;
;; MessageText:
;;
;;  The specified color transform is invalid.
;;
ERROR_INVALID_TRANSFORM equ 2310


;;;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;//
;;				  ;;
;;     Win32 Spooler Error Codes  ;;
;;				  ;;
;;;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;//
;;
;; MessageId: ERROR_UNKNOWN_PRINT_MONITOR
;;
;; MessageText:
;;
;;  The specified print monitor is unknown.
;;
ERROR_UNKNOWN_PRINT_MONITOR	equ 3000

;;
;; MessageId: ERROR_PRINTER_DRIVER_IN_USE
;;
;; MessageText:
;;
;;  The specified printer driver is currently in use.
;;
ERROR_PRINTER_DRIVER_IN_USE	equ 3001

;;
;; MessageId: ERROR_SPOOL_FILE_NOT_FOUND
;;
;; MessageText:
;;
;;  The spool file was not found.
;;
ERROR_SPOOL_FILE_NOT_FOUND	equ 3002

;;
;; MessageId: ERROR_SPL_NO_STARTDOC
;;
;; MessageText:
;;
;;  A StartDocPrinter call was not issued.
;;
ERROR_SPL_NO_STARTDOC	equ 3003

;;
;; MessageId: ERROR_SPL_NO_ADDJOB
;;
;; MessageText:
;;
;;  An AddJob call was not issued.
;;
ERROR_SPL_NO_ADDJOB	equ 3004

;;
;; MessageId: ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED
;;
;; MessageText:
;;
;;  The specified print processor has already been installed.
;;
ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED equ 3005

;;
;; MessageId: ERROR_PRINT_MONITOR_ALREADY_INSTALLED
;;
;; MessageText:
;;
;;  The specified print monitor has already been installed.
;;
ERROR_PRINT_MONITOR_ALREADY_INSTALLED	equ 3006

;;
;; MessageId: ERROR_INVALID_PRINT_MONITOR
;;
;; MessageText:
;;
;;  The specified print monitor does not have the required functions.
;;
ERROR_INVALID_PRINT_MONITOR	equ 3007

;;
;; MessageId: ERROR_PRINT_MONITOR_IN_USE
;;
;; MessageText:
;;
;;  The specified print monitor is currently in use.
;;
ERROR_PRINT_MONITOR_IN_USE	equ 3008

;;
;; MessageId: ERROR_PRINTER_HAS_JOBS_QUEUED
;;
;; MessageText:
;;
;;  The requested operation is not allowed when there are jobs queued to the printer.
;;
ERROR_PRINTER_HAS_JOBS_QUEUED	equ 3009

;;
;; MessageId: ERROR_SUCCESS_REBOOT_REQUIRED
;;
;; MessageText:
;;
;;  The requested operation is successful.  Changes will not be effective until the system is rebooted.
;;
ERROR_SUCCESS_REBOOT_REQUIRED	equ 3010

;;
;; MessageId: ERROR_SUCCESS_RESTART_REQUIRED
;;
;; MessageText:
;;
;;  The requested operation is successful.  Changes will not be effective until the service is restarted.
;;
ERROR_SUCCESS_RESTART_REQUIRED	equ 3011

;;;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;//
;;				  ;;
;;     Wins Error Codes		  ;;
;;				  ;;
;;;;/;;/;;/;;/;;/;;/;;/;;/;;/;;/;;//
;;
;; MessageId: ERROR_WINS_INTERNAL
;;
;; MessageText:
;;
;;  WINS encountered an error while processing the command.
;;
ERROR_WINS_INTERNAL	equ 4000

;;
;; MessageId: ERROR_CAN_NOT_DEL_LOCAL_WINS
;;
;; MessageText:
;;
;;  The local WINS can not be deleted.
;;
ERROR_CAN_NOT_DEL_LOCAL_WINS	equ 4001

;;
;; MessageId: ERROR_STATIC_INIT
;;
;; MessageText:
;;
;;  The importation from the file failed.
;;
ERROR_STATIC_INIT	equ 4002

;;
;; MessageId: ERROR_INC_BACKUP
;;
;; MessageText:
;;
;;  The backup failed. Was a full backup done before?
;;
ERROR_INC_BACKUP	equ 4003

;;
;; MessageId: ERROR_FULL_BACKUP
;;
;; MessageText:
;;
;;  The backup failed. Check the directory to which you are backing the database.
;;
ERROR_FULL_BACKUP	equ 4004

;;
;; MessageId: ERROR_REC_NON_EXISTENT
;;
;; MessageText:
;;
;;  The name does not exist in the WINS database.
;;
ERROR_REC_NON_EXISTENT	equ 4005

;;
;; MessageId: ERROR_RPL_NOT_ALLOWED
;;
;; MessageText:
;;
;;  Replication with a nonconfigured partner is not allowed.
;;
ERROR_RPL_NOT_ALLOWED	equ 4006

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;				  ;;
;;     DHCP Error Codes		  ;;
;;				  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;
;; MessageId: ERROR_DHCP_ADDRESS_CONFLICT
;;
;; MessageText:
;;
;;  The DHCP client has obtained an IP address that is already in use on the network.  The local interface will be disabled until the DHCP client can obtain a new address.
;;
ERROR_DHCP_ADDRESS_CONFLICT	equ 4100

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;				  ;;
;;     WMI Error Codes		  ;;
;;				  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;
;; MessageId: ERROR_WMI_GUID_NOT_FOUND
;;
;; MessageText:
;;
;;  The GUID passed was not recognized as valid by a WMI data provider.
;;
ERROR_WMI_GUID_NOT_FOUND	equ 4200

;;
;; MessageId: ERROR_WMI_INSTANCE_NOT_FOUND
;;
;; MessageText:
;;
;;  The instance name passed was not recognized as valid by a WMI data provider.
;;
ERROR_WMI_INSTANCE_NOT_FOUND	equ 4201

;;
;; MessageId: ERROR_WMI_ITEMID_NOT_FOUND
;;
;; MessageText:
;;
;;  The data item ID passed was not recognized as valid by a WMI data provider.
;;
ERROR_WMI_ITEMID_NOT_FOUND	equ 4202

;;
;; MessageId: ERROR_WMI_TRY_AGAIN
;;
;; MessageText:
;;
;;  The WMI request could not be completed and should be retried.
;;
ERROR_WMI_TRY_AGAIN	equ 4203

;;
;; MessageId: ERROR_WMI_DP_NOT_FOUND
;;
;; MessageText:
;;
;;  The WMI data provider could not be located.
;;
ERROR_WMI_DP_NOT_FOUND	equ 4204

;;
;; MessageId: ERROR_WMI_UNRESOLVED_INSTANCE_REF
;;
;; MessageText:
;;
;;  The WMI data provider references an instance set that has not been registered.
;;
ERROR_WMI_UNRESOLVED_INSTANCE_REF	equ 4205

;;
;; MessageId: ERROR_WMI_ALREADY_ENABLED
;;
;; MessageText:
;;
;;  The WMI data block or event notification has already been enabled.
;;
ERROR_WMI_ALREADY_ENABLED	equ 4206

;;
;; MessageId: ERROR_WMI_GUID_DISCONNECTED
;;
;; MessageText:
;;
;;  The WMI data block is no longer available.
;;
ERROR_WMI_GUID_DISCONNECTED	equ 4207

;;
;; MessageId: ERROR_WMI_SERVER_UNAVAILABLE
;;
;; MessageText:
;;
;;  The WMI data service is not available.
;;
ERROR_WMI_SERVER_UNAVAILABLE	equ 4208

;;
;; MessageId: ERROR_WMI_DP_FAILED
;;
;; MessageText:
;;
;;  The WMI data provider failed to carry out the request.
;;
ERROR_WMI_DP_FAILED	equ 4209

;;
;; MessageId: ERROR_WMI_INVALID_MOF
;;
;; MessageText:
;;
;;  The WMI MOF information is not valid.
;;
ERROR_WMI_INVALID_MOF	equ 4210

;;
;; MessageId: ERROR_WMI_INVALID_REGINFO
;;
;; MessageText:
;;
;;  The WMI registration information is not valid.
;;
ERROR_WMI_INVALID_REGINFO	equ 4211

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;				  ;;
;; NT Media Services Error Codes  ;;
;;				  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;
;; MessageId: ERROR_INVALID_MEDIA
;;
;; MessageText:
;;
;;  The media identifier does not represent a valid medium.
;;
ERROR_INVALID_MEDIA	equ 4300

;;
;; MessageId: ERROR_INVALID_LIBRARY
;;
;; MessageText:
;;
;;  The library identifier does not represent a valid library.
;;
ERROR_INVALID_LIBRARY	equ 4301

;;
;; MessageId: ERROR_INVALID_MEDIA_POOL
;;
;; MessageText:
;;
;;  The media pool identifier does not represent a valid media pool.
;;
ERROR_INVALID_MEDIA_POOL	equ 4302

;;
;; MessageId: ERROR_DRIVE_MEDIA_MISMATCH
;;
;; MessageText:
;;
;;  The drive and medium are not compatible or exist in different libraries.
;;
ERROR_DRIVE_MEDIA_MISMATCH	equ 4303

;;
;; MessageId: ERROR_MEDIA_OFFLINE
;;
;; MessageText:
;;
;;  The medium currently exists in an offline library and must be online to perform this operation.
;;
ERROR_MEDIA_OFFLINE	equ 4304

;;
;; MessageId: ERROR_LIBRARY_OFFLINE
;;
;; MessageText:
;;
;;  The operation cannot be performed on an offline library.
;;
ERROR_LIBRARY_OFFLINE	equ 4305

;;
;; MessageId: ERROR_EMPTY
;;
;; MessageText:
;;
;;  The library, drive, or media pool is empty.
;;
ERROR_EMPTY	equ 4306

;;
;; MessageId: ERROR_NOT_EMPTY
;;
;; MessageText:
;;
;;  The library, drive, or media pool must be empty to perform this operation.
;;
ERROR_NOT_EMPTY equ 4307

;;
;; MessageId: ERROR_MEDIA_UNAVAILABLE
;;
;; MessageText:
;;
;;  No media is currently available in this media pool or library.
;;
ERROR_MEDIA_UNAVAILABLE equ 4308

;;
;; MessageId: ERROR_RESOURCE_DISABLED
;;
;; MessageText:
;;
;;  A resource required for this operation is disabled.
;;
ERROR_RESOURCE_DISABLED equ 4309

;;
;; MessageId: ERROR_INVALID_CLEANER
;;
;; MessageText:
;;
;;  The media identifier does not represent a valid cleaner.
;;
ERROR_INVALID_CLEANER	equ 4310

;;
;; MessageId: ERROR_UNABLE_TO_CLEAN
;;
;; MessageText:
;;
;;  The drive cannot be cleaned or does not support cleaning.
;;
ERROR_UNABLE_TO_CLEAN	equ 4311

;;
;; MessageId: ERROR_OBJECT_NOT_FOUND
;;
;; MessageText:
;;
;;  The object identifier does not represent a valid object.
;;
ERROR_OBJECT_NOT_FOUND	equ 4312

;;
;; MessageId: ERROR_DATABASE_FAILURE
;;
;; MessageText:
;;
;;  Unable to read from or write to the database.
;;
ERROR_DATABASE_FAILURE	equ 4313

;;
;; MessageId: ERROR_DATABASE_FULL
;;
;; MessageText:
;;
;;  The database is full.
;;
ERROR_DATABASE_FULL	equ 4314

;;
;; MessageId: ERROR_MEDIA_INCOMPATIBLE
;;
;; MessageText:
;;
;;  The medium is not compatible with the device or media pool.
;;
ERROR_MEDIA_INCOMPATIBLE	equ 4315

;;
;; MessageId: ERROR_RESOURCE_NOT_PRESENT
;;
;; MessageText:
;;
;;  The resource required for this operation does not exist.
;;
ERROR_RESOURCE_NOT_PRESENT	equ 4316

;;
;; MessageId: ERROR_INVALID_OPERATION
;;
;; MessageText:
;;
;;  The operation identifier is not valid.
;;
ERROR_INVALID_OPERATION equ 4317

;;
;; MessageId: ERROR_MEDIA_NOT_AVAILABLE
;;
;; MessageText:
;;
;;  The media is not mounted or ready for use.
;;
ERROR_MEDIA_NOT_AVAILABLE	equ 4318

;;
;; MessageId: ERROR_DEVICE_NOT_AVAILABLE
;;
;; MessageText:
;;
;;  The device is not ready for use.
;;
ERROR_DEVICE_NOT_AVAILABLE	equ 4319

;;
;; MessageId: ERROR_REQUEST_REFUSED
;;
;; MessageText:
;;
;;  The operator or administrator has refused the request.
;;
ERROR_REQUEST_REFUSED	equ 4320

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;					  ;;
;; NT Remote Storage Service Error Codes  ;;
;;					  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MessageId: ERROR_FILE_OFFLINE
;;
;; MessageText:
;;
;;  The remote storage service was not able to recall the file.
;;
ERROR_FILE_OFFLINE	equ 4350

;;
;; MessageId: ERROR_REMOTE_STORAGE_NOT_ACTIVE
;;
;; MessageText:
;;
;;  The remote storage service is not operational at this time.
;;
ERROR_REMOTE_STORAGE_NOT_ACTIVE equ 4351

;;
;; MessageId: ERROR_REMOTE_STORAGE_MEDIA_ERROR
;;
;; MessageText:
;;
;;  The remote storage service encountered a media error.
;;
ERROR_REMOTE_STORAGE_MEDIA_ERROR	equ 4352

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;					  ;;
;; NT Reparse Points Error Codes	  ;;
;;					  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MessageId: ERROR_NOT_A_REPARSE_POINT
;;
;; MessageText:
;;
;;  The file or directory is not a reparse point.
;;
ERROR_NOT_A_REPARSE_POINT	equ 4390

;;
;; MessageId: ERROR_REPARSE_ATTRIBUTE_CONFLICT
;;
;; MessageText:
;;
;;  The reparse point attribute cannot be set because it conflicts with an existing attribute.
;;
ERROR_REPARSE_ATTRIBUTE_CONFLICT	equ 4391

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;				  ;;
;;     Cluster Error Codes	  ;;
;;				  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;
;; MessageId: ERROR_DEPENDENT_RESOURCE_EXISTS
;;
;; MessageText:
;;
;;  The cluster resource cannot be moved to another group because other resources are dependent on it.
;;
ERROR_DEPENDENT_RESOURCE_EXISTS equ 5001

;;
;; MessageId: ERROR_DEPENDENCY_NOT_FOUND
;;
;; MessageText:
;;
;;  The cluster resource dependency cannot be found.
;;
ERROR_DEPENDENCY_NOT_FOUND	equ 5002

;;
;; MessageId: ERROR_DEPENDENCY_ALREADY_EXISTS
;;
;; MessageText:
;;
;;  The cluster resource cannot be made dependent on the specified resource because it is already dependent.
;;
ERROR_DEPENDENCY_ALREADY_EXISTS equ 5003

;;
;; MessageId: ERROR_RESOURCE_NOT_ONLINE
;;
;; MessageText:
;;
;;  The cluster resource is not online.
;;
ERROR_RESOURCE_NOT_ONLINE	equ 5004

;;
;; MessageId: ERROR_HOST_NODE_NOT_AVAILABLE
;;
;; MessageText:
;;
;;  A cluster node is not available for this operation.
;;
ERROR_HOST_NODE_NOT_AVAILABLE	equ 5005

;;
;; MessageId: ERROR_RESOURCE_NOT_AVAILABLE
;;
;; MessageText:
;;
;;  The cluster resource is not available.
;;
ERROR_RESOURCE_NOT_AVAILABLE	equ 5006

;;
;; MessageId: ERROR_RESOURCE_NOT_FOUND
;;
;; MessageText:
;;
;;  The cluster resource could not be found.
;;
ERROR_RESOURCE_NOT_FOUND	equ 5007

;;
;; MessageId: ERROR_SHUTDOWN_CLUSTER
;;
;; MessageText:
;;
;;  The cluster is being shut down.
;;
ERROR_SHUTDOWN_CLUSTER	equ 5008

;;
;; MessageId: ERROR_CANT_EVICT_ACTIVE_NODE
;;
;; MessageText:
;;
;;  A cluster node cannot be evicted from the cluster while it is online.
;;
ERROR_CANT_EVICT_ACTIVE_NODE	equ 5009

;;
;; MessageId: ERROR_OBJECT_ALREADY_EXISTS
;;
;; MessageText:
;;
;;  The object already exists.
;;
ERROR_OBJECT_ALREADY_EXISTS	equ 5010

;;
;; MessageId: ERROR_OBJECT_IN_LIST
;;
;; MessageText:
;;
;;  The object is already in the list.
;;
ERROR_OBJECT_IN_LIST	equ 5011

;;
;; MessageId: ERROR_GROUP_NOT_AVAILABLE
;;
;; MessageText:
;;
;;  The cluster group is not available for any new requests.
;;
ERROR_GROUP_NOT_AVAILABLE	equ 5012

;;
;; MessageId: ERROR_GROUP_NOT_FOUND
;;
;; MessageText:
;;
;;  The cluster group could not be found.
;;
ERROR_GROUP_NOT_FOUND	equ 5013

;;
;; MessageId: ERROR_GROUP_NOT_ONLINE
;;
;; MessageText:
;;
;;  The operation could not be completed because the cluster group is not online.
;;
ERROR_GROUP_NOT_ONLINE	equ 5014

;;
;; MessageId: ERROR_HOST_NODE_NOT_RESOURCE_OWNER
;;
;; MessageText:
;;
;;  The cluster node is not the owner of the resource.
;;
ERROR_HOST_NODE_NOT_RESOURCE_OWNER	equ 5015

;;
;; MessageId: ERROR_HOST_NODE_NOT_GROUP_OWNER
;;
;; MessageText:
;;
;;  The cluster node is not the owner of the group.
;;
ERROR_HOST_NODE_NOT_GROUP_OWNER equ 5016

;;
;; MessageId: ERROR_RESMON_CREATE_FAILED
;;
;; MessageText:
;;
;;  The cluster resource could not be created in the specified resource monitor.
;;
ERROR_RESMON_CREATE_FAILED	equ 5017

;;
;; MessageId: ERROR_RESMON_ONLINE_FAILED
;;
;; MessageText:
;;
;;  The cluster resource could not be brought online by the resource monitor.
;;
ERROR_RESMON_ONLINE_FAILED	equ 5018

;;
;; MessageId: ERROR_RESOURCE_ONLINE
;;
;; MessageText:
;;
;;  The operation could not be completed because the cluster resource is online.
;;
ERROR_RESOURCE_ONLINE	equ 5019

;;
;; MessageId: ERROR_QUORUM_RESOURCE
;;
;; MessageText:
;;
;;  The cluster resource could not be deleted or brought offline because it is the quorum resource.
;;
ERROR_QUORUM_RESOURCE	equ 5020

;;
;; MessageId: ERROR_NOT_QUORUM_CAPABLE
;;
;; MessageText:
;;
;;  The cluster could not make the specified resource a quorum resource because it is not capable of being a quorum resource.
;;
ERROR_NOT_QUORUM_CAPABLE	equ 5021

;;
;; MessageId: ERROR_CLUSTER_SHUTTING_DOWN
;;
;; MessageText:
;;
;;  The cluster software is shutting down.
;;
ERROR_CLUSTER_SHUTTING_DOWN	equ 5022

;;
;; MessageId: ERROR_INVALID_STATE
;;
;; MessageText:
;;
;;  The group or resource is not in the correct state to perform the requested operation.
;;
ERROR_INVALID_STATE	equ 5023

;;
;; MessageId: ERROR_RESOURCE_PROPERTIES_STORED
;;
;; MessageText:
;;
;;  The properties were stored but not all changes will take effect until the next
;;  time the resource is brought online.
;;
ERROR_RESOURCE_PROPERTIES_STORED	equ 5024

;;
;; MessageId: ERROR_NOT_QUORUM_CLASS
;;
;; MessageText:
;;
;;  The cluster could not make the specified resource a quorum resource because it does not belong to a shared storage class.
;;
ERROR_NOT_QUORUM_CLASS	equ 5025

;;
;; MessageId: ERROR_CORE_RESOURCE
;;
;; MessageText:
;;
;;  The cluster resource could not be deleted since it is a core resource.
;;
ERROR_CORE_RESOURCE	equ 5026

;;
;; MessageId: ERROR_QUORUM_RESOURCE_ONLINE_FAILED
;;
;; MessageText:
;;
;;  The quorum resource failed to come online.
;;
ERROR_QUORUM_RESOURCE_ONLINE_FAILED	equ 5027

;;
;; MessageId: ERROR_QUORUMLOG_OPEN_FAILED
;;
;; MessageText:
;;
;;  The quorum log could not be created or mounted successfully.
;;
ERROR_QUORUMLOG_OPEN_FAILED	equ 5028

;;
;; MessageId: ERROR_CLUSTERLOG_CORRUPT
;;
;; MessageText:
;;
;;  The cluster log is corrupt.
;;
ERROR_CLUSTERLOG_CORRUPT	equ 5029

;;
;; MessageId: ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE
;;
;; MessageText:
;;
;;  The record could not be written to the cluster log since it exceeds the maximum size.
;;
ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE equ 5030

;;
;; MessageId: ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE
;;
;; MessageText:
;;
;;  The cluster log exceeds its maximum size.
;;
ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE	equ 5031

;;
;; MessageId: ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND
;;
;; MessageText:
;;
;;  No checkpoint record was found in the cluster log.
;;
ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND	equ 5032

;;
;; MessageId: ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE
;;
;; MessageText:
;;
;;  The minimum required disk space needed for logging is not available.
;;
ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE	equ 5033

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;				  ;;
;;     EFS Error Codes		  ;;
;;				  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;
;; MessageId: ERROR_ENCRYPTION_FAILED
;;
;; MessageText:
;;
;;  The specified file could not be encrypted.
;;
ERROR_ENCRYPTION_FAILED equ 6000

;;
;; MessageId: ERROR_DECRYPTION_FAILED
;;
;; MessageText:
;;
;;  The specified file could not be decrypted.
;;
ERROR_DECRYPTION_FAILED equ 6001

;;
;; MessageId: ERROR_FILE_ENCRYPTED
;;
;; MessageText:
;;
;;  The specified file is encrypted and the user does not have the ability to decrypt it.
;;
ERROR_FILE_ENCRYPTED	equ 6002

;;
;; MessageId: ERROR_NO_RECOVERY_POLICY
;;
;; MessageText:
;;
;;  There is no encryption recovery policy configured for this system.
;;
ERROR_NO_RECOVERY_POLICY	equ 6003

;;
;; MessageId: ERROR_NO_EFS
;;
;; MessageText:
;;
;;  The required encryption driver is not loaded for this system.
;;
ERROR_NO_EFS	equ 6004

;;
;; MessageId: ERROR_WRONG_EFS
;;
;; MessageText:
;;
;;  The file was encrypted with a different encryption driver than is currently loaded.
;;
ERROR_WRONG_EFS equ 6005

;;
;; MessageId: ERROR_NO_USER_KEYS
;;
;; MessageText:
;;
;;  There are no EFS keys defined for the user.
;;
ERROR_NO_USER_KEYS	equ 6006

;;
;; MessageId: ERROR_FILE_NOT_ENCRYPTED
;;
;; MessageText:
;;
;;  The specified file is not encrypted.
;;
ERROR_FILE_NOT_ENCRYPTED	equ 6007

;;
;; MessageId: ERROR_NOT_EXPORT_FORMAT
;;
;; MessageText:
;;
;;  The specified file is not in the defined EFS export format.
;;
ERROR_NOT_EXPORT_FORMAT equ 6008

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;				  ;;
;;     OLE Error Codes		  ;;
;;				  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/

;;
;; OLE error definitions and values
;;
;; The return value of OLE APIs and methods is an HRESULT.
;; This is not a handle to anything, but is merely a 32-bit value
;; with several fields encoded in the value.  The parts of an
;; HRESULT are shown below.
;;
;; Many of the macros and functions below were orginally defined to
;; operate on SCODEs.  SCODEs are no longer used.  The macros are
;; still present for compatibility and easy porting of Win16 code.
;; Newly written code should use the HRESULT macros and functions.
;;

;;
;;  HRESULTs are 32 bit values layed out as follows:
;;
;;   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;  +-+-+-+-+-+---------------------+-------------------------------+
;;  |S|R|C|N|r|	   Facility	    |		    Code	    |
;;  +-+-+-+-+-+---------------------+-------------------------------+
;;
;;  where
;;
;;	S - Severity - indicates success/fail
;;
;;	    0 - Success
;;	    1 - Fail (COERROR)
;;
;;	R - reserved portion of the facility code, corresponds to NT's
;;		second severity bit.
;;
;;	C - reserved portion of the facility code, corresponds to NT's
;;		C field.
;;
;;	N - reserved portion of the facility code. Used to indicate a
;;		mapped NT status value.
;;
;;	r - reserved portion of the facility code. Reserved for internal
;;		use. Used to indicate HRESULT values that are not status
;;		values, but are instead message ids for display strings.
;;
;;	Facility - is the facility code
;;
;;	Code - is the facility's status code
;;

;;
;; Severity values
;;

SEVERITY_SUCCESS	equ 0
SEVERITY_ERROR	equ 1


;;
;; Generic test for success on any status value (non-negative numbers
;; indicate success).
;;
if 0
SUCCEEDED macro Status
	exitm<Status GE 0>
	endm
;;
;; and the inverse
;;
FAILED macro Status
	exitm <( ( Status ) LT 0 ) >
	endm
endif


;;
;; Generic test for error on any status value.
;;

;;
;; Return the code
;;
IS_ERROR macro Status
	exitm <( ( Status )  shr  31 == SEVERITY_ERROR ) >
	endm

HRESULT_CODE macro hr
	exitm <( ( hr )	 and  0FFFFh ) >
	endm

SCODE_CODE macro sc
	exitm <( ( sc )	 and  0FFFFh ) >
	endm
;;
;;  Return the facility
;;

HRESULT_FACILITY macro hr
	exitm <( ( ( hr )  shr	16 )  and  1fffh ) >
	endm
SCODE_FACILITY macro sc
	exitm <( ( ( sc )  shr	16 )  and  1fffh ) >
	endm
;;
;;  Return the severity
;;

HRESULT_SEVERITY macro hr
	exitm <( ( ( hr )  shr	31 )  and  1h ) >
	endm
SCODE_SEVERITY macro sc
	exitm <( ( ( sc )  shr	31 )  and  1h ) >
	endm
;;
;; Create an HRESULT value from component pieces
;;

MAKE_HRESULT macro sev,fac,code
	exitm <((sev shl 31) or (fac shl 16) or (code))>
	endm
MAKE_SCODE macro sev,fac,code
	exitm <((sev shl 31) or (fac shl 16) or (code))>
	endm


;;
;; Map a WIN32 error value into a HRESULT
;; Note: This assumes that WIN32 errors fall in the range -32k to 32k.
;;
;; Define bits here so macros are guaranteed to work

FACILITY_NT_BIT equ 0x10000000
HRESULT_FROM_WIN32 macro x
	exitm <( x ? ( ( ( x and 0000FFFFh) or ( FACILITY_WIN32 shl 16) or 80000000h)) : 0 )>
	endm
;;
;; Map an NT status value into a HRESULT
;;
HRESULT_FROM_NT macro x
	exitm <( ( ( x )  or  FACILITY_NT_BIT ) ) >
	endm


;; ****** OBSOLETE functions

;; HRESULT functions
;; As noted above, these functions are obsolete and should not be used.


;; Extract the SCODE from a HRESULT

GetScode macro hr
	exitm <(hr)>
	endm

;; Convert an SCODE into an HRESULT.

ResultFromScode macro sc
	exitm <(sc)>
	endm


;; PropagateResult is a noop
PropagateResult macro hrPrevious,scBase
	exitm <(scBase)>
	endm


;; ****** End of OBSOLETE functions.


;; ---------------------- HRESULT value definitions -----------------
;;
;; HRESULT definitions
;;
_HRESULT_TYPEDEF_ macro _sc
	exitm <_sc>
	endm

NOERROR equ 0

;;
;; Error definitions follow
;;

;;
;; Codes 0x4000-0x40ff are reserved for OLE
;;
;;
;; Error codes
;;
;;
;; MessageId: E_UNEXPECTED
;;
;; MessageText:
;;
;;  Catastrophic failure
;;
E_UNEXPECTED equ _HRESULT_TYPEDEF_(0x8000FFFF)

ifdef _WIN32
;;
;; MessageId: E_NOTIMPL
;;
;; MessageText:
;;
;;  Not implemented
;;
E_NOTIMPL equ _HRESULT_TYPEDEF_(0x80004001)

;;
;; MessageId: E_OUTOFMEMORY
;;
;; MessageText:
;;
;;  Ran out of memory
;;
E_OUTOFMEMORY equ _HRESULT_TYPEDEF_(0x8007000E)

;;
;; MessageId: E_INVALIDARG
;;
;; MessageText:
;;
;;  One or more arguments are invalid
;;
E_INVALIDARG equ _HRESULT_TYPEDEF_(0x80070057)

;;
;; MessageId: E_NOINTERFACE
;;
;; MessageText:
;;
;;  No such interface supported
;;
E_NOINTERFACE equ _HRESULT_TYPEDEF_(0x80004002)

;;
;; MessageId: E_POINTER
;;
;; MessageText:
;;
;;  Invalid pointer
;;
E_POINTER equ _HRESULT_TYPEDEF_(0x80004003)

;;
;; MessageId: E_HANDLE
;;
;; MessageText:
;;
;;  Invalid handle
;;
E_HANDLE equ _HRESULT_TYPEDEF_(0x80070006)

;;
;; MessageId: E_ABORT
;;
;; MessageText:
;;
;;  Operation aborted
;;
E_ABORT equ _HRESULT_TYPEDEF_(0x80004004)

;;
;; MessageId: E_FAIL
;;
;; MessageText:
;;
;;  Unspecified error
;;
E_FAIL equ _HRESULT_TYPEDEF_(0x80004005)

;;
;; MessageId: E_ACCESSDENIED
;;
;; MessageText:
;;
;;  General access denied error
;;
E_ACCESSDENIED equ _HRESULT_TYPEDEF_(0x80070005)

else
;;
;; MessageId: E_NOTIMPL
;;
;; MessageText:
;;
;;  Not implemented
;;
E_NOTIMPL equ _HRESULT_TYPEDEF_(0x80000001)

;;
;; MessageId: E_OUTOFMEMORY
;;
;; MessageText:
;;
;;  Ran out of memory
;;
E_OUTOFMEMORY equ _HRESULT_TYPEDEF_(0x80000002)

;;
;; MessageId: E_INVALIDARG
;;
;; MessageText:
;;
;;  One or more arguments are invalid
;;
E_INVALIDARG equ _HRESULT_TYPEDEF_(0x80000003)

;;
;; MessageId: E_NOINTERFACE
;;
;; MessageText:
;;
;;  No such interface supported
;;
E_NOINTERFACE equ _HRESULT_TYPEDEF_(0x80000004)

;;
;; MessageId: E_POINTER
;;
;; MessageText:
;;
;;  Invalid pointer
;;
E_POINTER equ _HRESULT_TYPEDEF_(0x80000005)

;;
;; MessageId: E_HANDLE
;;
;; MessageText:
;;
;;  Invalid handle
;;
E_HANDLE equ _HRESULT_TYPEDEF_(0x80000006)

;;
;; MessageId: E_ABORT
;;
;; MessageText:
;;
;;  Operation aborted
;;
E_ABORT equ _HRESULT_TYPEDEF_(0x80000007)

;;
;; MessageId: E_FAIL
;;
;; MessageText:
;;
;;  Unspecified error
;;
E_FAIL equ _HRESULT_TYPEDEF_(0x80000008)

;;
;; MessageId: E_ACCESSDENIED
;;
;; MessageText:
;;
;;  General access denied error
;;
E_ACCESSDENIED equ _HRESULT_TYPEDEF_(0x80000009)

endif ; _WIN32
;;
;; MessageId: E_PENDING
;;
;; MessageText:
;;
;;  The data necessary to complete this operation is not yet available.
;;
E_PENDING equ _HRESULT_TYPEDEF_(0x8000000A)

;;
;; MessageId: CO_E_INIT_TLS
;;
;; MessageText:
;;
;;  Thread local storage failure
;;
CO_E_INIT_TLS equ _HRESULT_TYPEDEF_(0x80004006)

;;
;; MessageId: CO_E_INIT_SHARED_ALLOCATOR
;;
;; MessageText:
;;
;;  Get shared memory allocator failure
;;
CO_E_INIT_SHARED_ALLOCATOR equ _HRESULT_TYPEDEF_(0x80004007)

;;
;; MessageId: CO_E_INIT_MEMORY_ALLOCATOR
;;
;; MessageText:
;;
;;  Get memory allocator failure
;;
CO_E_INIT_MEMORY_ALLOCATOR equ _HRESULT_TYPEDEF_(0x80004008)

;;
;; MessageId: CO_E_INIT_CLASS_CACHE
;;
;; MessageText:
;;
;;  Unable to initialize class cache
;;
CO_E_INIT_CLASS_CACHE equ _HRESULT_TYPEDEF_(0x80004009)

;;
;; MessageId: CO_E_INIT_RPC_CHANNEL
;;
;; MessageText:
;;
;;  Unable to initialize RPC services
;;
CO_E_INIT_RPC_CHANNEL equ _HRESULT_TYPEDEF_(0x8000400A)

;;
;; MessageId: CO_E_INIT_TLS_SET_CHANNEL_CONTROL
;;
;; MessageText:
;;
;;  Cannot set thread local storage channel control
;;
CO_E_INIT_TLS_SET_CHANNEL_CONTROL equ _HRESULT_TYPEDEF_(0x8000400B)

;;
;; MessageId: CO_E_INIT_TLS_CHANNEL_CONTROL
;;
;; MessageText:
;;
;;  Could not allocate thread local storage channel control
;;
CO_E_INIT_TLS_CHANNEL_CONTROL equ _HRESULT_TYPEDEF_(0x8000400C)

;;
;; MessageId: CO_E_INIT_UNACCEPTED_USER_ALLOCATOR
;;
;; MessageText:
;;
;;  The user supplied memory allocator is unacceptable
;;
CO_E_INIT_UNACCEPTED_USER_ALLOCATOR equ _HRESULT_TYPEDEF_(0x8000400D)

;;
;; MessageId: CO_E_INIT_SCM_MUTEX_EXISTS
;;
;; MessageText:
;;
;;  The OLE service mutex already exists
;;
CO_E_INIT_SCM_MUTEX_EXISTS equ _HRESULT_TYPEDEF_(0x8000400E)

;;
;; MessageId: CO_E_INIT_SCM_FILE_MAPPING_EXISTS
;;
;; MessageText:
;;
;;  The OLE service file mapping already exists
;;
CO_E_INIT_SCM_FILE_MAPPING_EXISTS equ _HRESULT_TYPEDEF_(0x8000400F)

;;
;; MessageId: CO_E_INIT_SCM_MAP_VIEW_OF_FILE
;;
;; MessageText:
;;
;;  Unable to map view of file for OLE service
;;
CO_E_INIT_SCM_MAP_VIEW_OF_FILE equ _HRESULT_TYPEDEF_(0x80004010)

;;
;; MessageId: CO_E_INIT_SCM_EXEC_FAILURE
;;
;; MessageText:
;;
;;  Failure attempting to launch OLE service
;;
CO_E_INIT_SCM_EXEC_FAILURE equ _HRESULT_TYPEDEF_(0x80004011)

;;
;; MessageId: CO_E_INIT_ONLY_SINGLE_THREADED
;;
;; MessageText:
;;
;;  There was an attempt to call CoInitialize a second time while single threaded
;;
CO_E_INIT_ONLY_SINGLE_THREADED equ _HRESULT_TYPEDEF_(0x80004012)

;;
;; MessageId: CO_E_CANT_REMOTE
;;
;; MessageText:
;;
;;  A Remote activation was necessary but was not allowed
;;
CO_E_CANT_REMOTE equ _HRESULT_TYPEDEF_(0x80004013)

;;
;; MessageId: CO_E_BAD_SERVER_NAME
;;
;; MessageText:
;;
;;  A Remote activation was necessary but the server name provided was invalid
;;
CO_E_BAD_SERVER_NAME equ _HRESULT_TYPEDEF_(0x80004014)

;;
;; MessageId: CO_E_WRONG_SERVER_IDENTITY
;;
;; MessageText:
;;
;;  The class is configured to run as a security id different from the caller
;;
CO_E_WRONG_SERVER_IDENTITY equ _HRESULT_TYPEDEF_(0x80004015)

;;
;; MessageId: CO_E_OLE1DDE_DISABLED
;;
;; MessageText:
;;
;;  Use of Ole1 services requiring DDE windows is disabled
;;
CO_E_OLE1DDE_DISABLED equ _HRESULT_TYPEDEF_(0x80004016)

;;
;; MessageId: CO_E_RUNAS_SYNTAX
;;
;; MessageText:
;;
;;  A RunAs specification must be <domain name>\<user name> or simply <user name>
;;
CO_E_RUNAS_SYNTAX equ _HRESULT_TYPEDEF_(0x80004017)

;;
;; MessageId: CO_E_CREATEPROCESS_FAILURE
;;
;; MessageText:
;;
;;  The server process could not be started.  The pathname may be incorrect.
;;
CO_E_CREATEPROCESS_FAILURE equ _HRESULT_TYPEDEF_(0x80004018)

;;
;; MessageId: CO_E_RUNAS_CREATEPROCESS_FAILURE
;;
;; MessageText:
;;
;;  The server process could not be started as the configured identity.	 The pathname may be incorrect or unavailable.
;;
CO_E_RUNAS_CREATEPROCESS_FAILURE equ _HRESULT_TYPEDEF_(0x80004019)

;;
;; MessageId: CO_E_RUNAS_LOGON_FAILURE
;;
;; MessageText:
;;
;;  The server process could not be started because the configured identity is incorrect.  Check the username and password.
;;
CO_E_RUNAS_LOGON_FAILURE equ _HRESULT_TYPEDEF_(0x8000401A)

;;
;; MessageId: CO_E_LAUNCH_PERMSSION_DENIED
;;
;; MessageText:
;;
;;  The client is not allowed to launch this server.
;;
CO_E_LAUNCH_PERMSSION_DENIED equ _HRESULT_TYPEDEF_(0x8000401B)

;;
;; MessageId: CO_E_START_SERVICE_FAILURE
;;
;; MessageText:
;;
;;  The service providing this server could not be started.
;;
CO_E_START_SERVICE_FAILURE equ _HRESULT_TYPEDEF_(0x8000401C)

;;
;; MessageId: CO_E_REMOTE_COMMUNICATION_FAILURE
;;
;; MessageText:
;;
;;  This computer was unable to communicate with the computer providing the server.
;;
CO_E_REMOTE_COMMUNICATION_FAILURE equ _HRESULT_TYPEDEF_(0x8000401D)

;;
;; MessageId: CO_E_SERVER_START_TIMEOUT
;;
;; MessageText:
;;
;;  The server did not respond after being launched.
;;
CO_E_SERVER_START_TIMEOUT equ _HRESULT_TYPEDEF_(0x8000401E)

;;
;; MessageId: CO_E_CLSREG_INCONSISTENT
;;
;; MessageText:
;;
;;  The registration information for this server is inconsistent or incomplete.
;;
CO_E_CLSREG_INCONSISTENT equ _HRESULT_TYPEDEF_(0x8000401F)

;;
;; MessageId: CO_E_IIDREG_INCONSISTENT
;;
;; MessageText:
;;
;;  The registration information for this interface is inconsistent or incomplete.
;;
CO_E_IIDREG_INCONSISTENT equ _HRESULT_TYPEDEF_(0x80004020)

;;
;; MessageId: CO_E_NOT_SUPPORTED
;;
;; MessageText:
;;
;;  The operation attempted is not supported.
;;
CO_E_NOT_SUPPORTED equ _HRESULT_TYPEDEF_(0x80004021)

;;
;; MessageId: CO_E_RELOAD_DLL
;;
;; MessageText:
;;
;;  A dll must be loaded.
;;
CO_E_RELOAD_DLL equ _HRESULT_TYPEDEF_(0x80004022)

;;
;; MessageId: CO_E_MSI_ERROR
;;
;; MessageText:
;;
;;  A Microsoft Software Installer error was encountered.
;;
CO_E_MSI_ERROR equ _HRESULT_TYPEDEF_(0x80004023)


;;
;; Success codes
;;
S_OK	equ 0x00000000
S_FALSE equ 0x00000001

;; ******************
;; FACILITY_ITF
;; ******************

;;
;; Codes 0x0-0x01ff are reserved for the OLE group of
;; interfaces.
;;


;;
;; Generic OLE errors that may be returned by many inerfaces
;;

OLE_E_FIRST	equ 0x80040000
OLE_E_LAST	equ 0x800400FF
OLE_S_FIRST	equ 0x00040000
OLE_S_LAST	equ 0x000400FF

;;
;; Old OLE errors
;;
;;
;; MessageId: OLE_E_OLEVERB
;;
;; MessageText:
;;
;;  Invalid OLEVERB structure
;;
OLE_E_OLEVERB equ _HRESULT_TYPEDEF_(0x80040000)

;;
;; MessageId: OLE_E_ADVF
;;
;; MessageText:
;;
;;  Invalid advise flags
;;
OLE_E_ADVF equ _HRESULT_TYPEDEF_(0x80040001)

;;
;; MessageId: OLE_E_ENUM_NOMORE
;;
;; MessageText:
;;
;;  Can't enumerate any more, because the associated data is missing
;;
OLE_E_ENUM_NOMORE equ _HRESULT_TYPEDEF_(0x80040002)

;;
;; MessageId: OLE_E_ADVISENOTSUPPORTED
;;
;; MessageText:
;;
;;  This implementation doesn't take advises
;;
OLE_E_ADVISENOTSUPPORTED equ _HRESULT_TYPEDEF_(0x80040003)

;;
;; MessageId: OLE_E_NOCONNECTION
;;
;; MessageText:
;;
;;  There is no connection for this connection ID
;;
OLE_E_NOCONNECTION equ _HRESULT_TYPEDEF_(0x80040004)

;;
;; MessageId: OLE_E_NOTRUNNING
;;
;; MessageText:
;;
;;  Need to run the object to perform this operation
;;
OLE_E_NOTRUNNING equ _HRESULT_TYPEDEF_(0x80040005)

;;
;; MessageId: OLE_E_NOCACHE
;;
;; MessageText:
;;
;;  There is no cache to operate on
;;
OLE_E_NOCACHE equ _HRESULT_TYPEDEF_(0x80040006)

;;
;; MessageId: OLE_E_BLANK
;;
;; MessageText:
;;
;;  Uninitialized object
;;
OLE_E_BLANK equ _HRESULT_TYPEDEF_(0x80040007)

;;
;; MessageId: OLE_E_CLASSDIFF
;;
;; MessageText:
;;
;;  Linked object's source class has changed
;;
OLE_E_CLASSDIFF equ _HRESULT_TYPEDEF_(0x80040008)

;;
;; MessageId: OLE_E_CANT_GETMONIKER
;;
;; MessageText:
;;
;;  Not able to get the moniker of the object
;;
OLE_E_CANT_GETMONIKER equ _HRESULT_TYPEDEF_(0x80040009)

;;
;; MessageId: OLE_E_CANT_BINDTOSOURCE
;;
;; MessageText:
;;
;;  Not able to bind to the source
;;
OLE_E_CANT_BINDTOSOURCE equ _HRESULT_TYPEDEF_(0x8004000A)

;;
;; MessageId: OLE_E_STATIC
;;
;; MessageText:
;;
;;  Object is static; operation not allowed
;;
OLE_E_STATIC equ _HRESULT_TYPEDEF_(0x8004000B)

;;
;; MessageId: OLE_E_PROMPTSAVECANCELLED
;;
;; MessageText:
;;
;;  User canceled out of save dialog
;;
OLE_E_PROMPTSAVECANCELLED equ _HRESULT_TYPEDEF_(0x8004000C)

;;
;; MessageId: OLE_E_INVALIDRECT
;;
;; MessageText:
;;
;;  Invalid rectangle
;;
OLE_E_INVALIDRECT equ _HRESULT_TYPEDEF_(0x8004000D)

;;
;; MessageId: OLE_E_WRONGCOMPOBJ
;;
;; MessageText:
;;
;;  compobj.dll is too old for the ole2.dll initialized
;;
OLE_E_WRONGCOMPOBJ equ _HRESULT_TYPEDEF_(0x8004000E)

;;
;; MessageId: OLE_E_INVALIDHWND
;;
;; MessageText:
;;
;;  Invalid window handle
;;
OLE_E_INVALIDHWND equ _HRESULT_TYPEDEF_(0x8004000F)

;;
;; MessageId: OLE_E_NOT_INPLACEACTIVE
;;
;; MessageText:
;;
;;  Object is not in any of the inplace active states
;;
OLE_E_NOT_INPLACEACTIVE equ _HRESULT_TYPEDEF_(0x80040010)

;;
;; MessageId: OLE_E_CANTCONVERT
;;
;; MessageText:
;;
;;  Not able to convert object
;;
OLE_E_CANTCONVERT equ _HRESULT_TYPEDEF_(0x80040011)

;;
;; MessageId: OLE_E_NOSTORAGE
;;
;; MessageText:
;;
;;  Not able to perform the operation because object is not given storage yet
;;
;;
OLE_E_NOSTORAGE equ _HRESULT_TYPEDEF_(0x80040012)

;;
;; MessageId: DV_E_FORMATETC
;;
;; MessageText:
;;
;;  Invalid FORMATETC structure
;;
DV_E_FORMATETC equ _HRESULT_TYPEDEF_(0x80040064)

;;
;; MessageId: DV_E_DVTARGETDEVICE
;;
;; MessageText:
;;
;;  Invalid DVTARGETDEVICE structure
;;
DV_E_DVTARGETDEVICE equ _HRESULT_TYPEDEF_(0x80040065)

;;
;; MessageId: DV_E_STGMEDIUM
;;
;; MessageText:
;;
;;  Invalid STDGMEDIUM structure
;;
DV_E_STGMEDIUM equ _HRESULT_TYPEDEF_(0x80040066)

;;
;; MessageId: DV_E_STATDATA
;;
;; MessageText:
;;
;;  Invalid STATDATA structure
;;
DV_E_STATDATA equ _HRESULT_TYPEDEF_(0x80040067)

;;
;; MessageId: DV_E_LINDEX
;;
;; MessageText:
;;
;;  Invalid lindex
;;
DV_E_LINDEX equ _HRESULT_TYPEDEF_(0x80040068)

;;
;; MessageId: DV_E_TYMED
;;
;; MessageText:
;;
;;  Invalid tymed
;;
DV_E_TYMED equ _HRESULT_TYPEDEF_(0x80040069)

;;
;; MessageId: DV_E_CLIPFORMAT
;;
;; MessageText:
;;
;;  Invalid clipboard format
;;
DV_E_CLIPFORMAT equ _HRESULT_TYPEDEF_(0x8004006A)

;;
;; MessageId: DV_E_DVASPECT
;;
;; MessageText:
;;
;;  Invalid aspect(s)
;;
DV_E_DVASPECT equ _HRESULT_TYPEDEF_(0x8004006B)

;;
;; MessageId: DV_E_DVTARGETDEVICE_SIZE
;;
;; MessageText:
;;
;;  tdSize parameter of the DVTARGETDEVICE structure is invalid
;;
DV_E_DVTARGETDEVICE_SIZE equ _HRESULT_TYPEDEF_(0x8004006C)

;;
;; MessageId: DV_E_NOIVIEWOBJECT
;;
;; MessageText:
;;
;;  Object doesn't support IViewObject interface
;;
DV_E_NOIVIEWOBJECT equ _HRESULT_TYPEDEF_(0x8004006D)

DRAGDROP_E_FIRST	equ 0x80040100
DRAGDROP_E_LAST		equ 0x8004010F
DRAGDROP_S_FIRST	equ 0x00040100
DRAGDROP_S_LAST		equ 0x0004010F
;;
;; MessageId: DRAGDROP_E_NOTREGISTERED
;;
;; MessageText:
;;
;;  Trying to revoke a drop target that has not been registered
;;
DRAGDROP_E_NOTREGISTERED equ _HRESULT_TYPEDEF_(0x80040100)

;;
;; MessageId: DRAGDROP_E_ALREADYREGISTERED
;;
;; MessageText:
;;
;;  This window has already been registered as a drop target
;;
DRAGDROP_E_ALREADYREGISTERED equ _HRESULT_TYPEDEF_(0x80040101)

;;
;; MessageId: DRAGDROP_E_INVALIDHWND
;;
;; MessageText:
;;
;;  Invalid window handle
;;
DRAGDROP_E_INVALIDHWND equ _HRESULT_TYPEDEF_(0x80040102)

CLASSFACTORY_E_FIRST	equ 0x80040110
CLASSFACTORY_E_LAST	equ 0x8004011F
CLASSFACTORY_S_FIRST	equ 0x00040110
CLASSFACTORY_S_LAST	equ 0x0004011F
;;
;; MessageId: CLASS_E_NOAGGREGATION
;;
;; MessageText:
;;
;;  Class does not support aggregation (or class object is remote)
;;
CLASS_E_NOAGGREGATION equ _HRESULT_TYPEDEF_(0x80040110)

;;
;; MessageId: CLASS_E_CLASSNOTAVAILABLE
;;
;; MessageText:
;;
;;  ClassFactory cannot supply requested class
;;
CLASS_E_CLASSNOTAVAILABLE equ _HRESULT_TYPEDEF_(0x80040111)

;;
;; MessageId: CLASS_E_NOTLICENSED
;;
;; MessageText:
;;
;;  Class is not licensed for use
;;
CLASS_E_NOTLICENSED equ _HRESULT_TYPEDEF_(0x80040112)

MARSHAL_E_FIRST equ 0x80040120
MARSHAL_E_LAST	equ 0x8004012F
MARSHAL_S_FIRST equ 0x00040120
MARSHAL_S_LAST	equ 0x0004012F
DATA_E_FIRST	equ 0x80040130
DATA_E_LAST	equ 0x8004013F
DATA_S_FIRST	equ 0x00040130
DATA_S_LAST	equ 0x0004013F
VIEW_E_FIRST	equ 0x80040140
VIEW_E_LAST	equ 0x8004014F
VIEW_S_FIRST	equ 0x00040140
VIEW_S_LAST	equ 0x0004014F
;;
;; MessageId: VIEW_E_DRAW
;;
;; MessageText:
;;
;;  Error drawing view
;;
VIEW_E_DRAW equ _HRESULT_TYPEDEF_(0x80040140)

REGDB_E_FIRST	equ 0x80040150
REGDB_E_LAST	equ 0x8004015F
REGDB_S_FIRST	equ 0x00040150
REGDB_S_LAST	equ 0x0004015F
;;
;; MessageId: REGDB_E_READREGDB
;;
;; MessageText:
;;
;;  Could not read key from registry
;;
REGDB_E_READREGDB equ _HRESULT_TYPEDEF_(0x80040150)

;;
;; MessageId: REGDB_E_WRITEREGDB
;;
;; MessageText:
;;
;;  Could not write key to registry
;;
REGDB_E_WRITEREGDB equ _HRESULT_TYPEDEF_(0x80040151)

;;
;; MessageId: REGDB_E_KEYMISSING
;;
;; MessageText:
;;
;;  Could not find the key in the registry
;;
REGDB_E_KEYMISSING equ _HRESULT_TYPEDEF_(0x80040152)

;;
;; MessageId: REGDB_E_INVALIDVALUE
;;
;; MessageText:
;;
;;  Invalid value for registry
;;
REGDB_E_INVALIDVALUE equ _HRESULT_TYPEDEF_(0x80040153)

;;
;; MessageId: REGDB_E_CLASSNOTREG
;;
;; MessageText:
;;
;;  Class not registered
;;
REGDB_E_CLASSNOTREG equ _HRESULT_TYPEDEF_(0x80040154)

;;
;; MessageId: REGDB_E_IIDNOTREG
;;
;; MessageText:
;;
;;  Interface not registered
;;
REGDB_E_IIDNOTREG equ _HRESULT_TYPEDEF_(0x80040155)

CAT_E_FIRST	equ 0x80040160
CAT_E_LAST	equ 0x80040161
;;
;; MessageId: CAT_E_CATIDNOEXIST
;;
;; MessageText:
;;
;;  CATID does not exist
;;
CAT_E_CATIDNOEXIST equ _HRESULT_TYPEDEF_(0x80040160)

;;
;; MessageId: CAT_E_NODESCRIPTION
;;
;; MessageText:
;;
;;  Description not found
;;
CAT_E_NODESCRIPTION equ _HRESULT_TYPEDEF_(0x80040161)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
;;				  ;;
;;     Class Store Error Codes	  ;;
;;				  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
CS_E_FIRST	equ 0x80040164
CS_E_LAST	equ 0x80040168
;;
;; MessageId: CS_E_PACKAGE_NOTFOUND
;;
;; MessageText:
;;
;;  No package in Class Store meets this criteria
;;
CS_E_PACKAGE_NOTFOUND equ _HRESULT_TYPEDEF_(0x80040164)

;;
;; MessageId: CS_E_NOT_DELETABLE
;;
;; MessageText:
;;
;;  Deleting this will break referential integrity
;;
CS_E_NOT_DELETABLE equ _HRESULT_TYPEDEF_(0x80040165)

;;
;; MessageId: CS_E_CLASS_NOTFOUND
;;
;; MessageText:
;;
;;  No such CLSID in Class Store
;;
CS_E_CLASS_NOTFOUND equ _HRESULT_TYPEDEF_(0x80040166)

;;
;; MessageId: CS_E_INVALID_VERSION
;;
;; MessageText:
;;
;;  The Class Store is corrupted or has a version that is no more supported
;;
CS_E_INVALID_VERSION equ _HRESULT_TYPEDEF_(0x80040167)

;;
;; MessageId: CS_E_NO_CLASSSTORE
;;
;; MessageText:
;;
;;  No such Class Store
;;
CS_E_NO_CLASSSTORE equ _HRESULT_TYPEDEF_(0x80040168)

CACHE_E_FIRST	equ 0x80040170
CACHE_E_LAST	equ 0x8004017F
CACHE_S_FIRST	equ 0x00040170
CACHE_S_LAST	equ 0x0004017F
;;
;; MessageId: CACHE_E_NOCACHE_UPDATED
;;
;; MessageText:
;;
;;  Cache not updated
;;
CACHE_E_NOCACHE_UPDATED equ _HRESULT_TYPEDEF_(0x80040170)

OLEOBJ_E_FIRST	equ 0x80040180
OLEOBJ_E_LAST	equ 0x8004018F
OLEOBJ_S_FIRST	equ 0x00040180
OLEOBJ_S_LAST	equ 0x0004018F
;;
;; MessageId: OLEOBJ_E_NOVERBS
;;
;; MessageText:
;;
;;  No verbs for OLE object
;;
OLEOBJ_E_NOVERBS equ _HRESULT_TYPEDEF_(0x80040180)

;;
;; MessageId: OLEOBJ_E_INVALIDVERB
;;
;; MessageText:
;;
;;  Invalid verb for OLE object
;;
OLEOBJ_E_INVALIDVERB equ _HRESULT_TYPEDEF_(0x80040181)

CLIENTSITE_E_FIRST	equ 0x80040190
CLIENTSITE_E_LAST	equ 0x8004019F
CLIENTSITE_S_FIRST	equ 0x00040190
CLIENTSITE_S_LAST	equ 0x0004019F
;;
;; MessageId: INPLACE_E_NOTUNDOABLE
;;
;; MessageText:
;;
;;  Undo is not available
;;
INPLACE_E_NOTUNDOABLE equ _HRESULT_TYPEDEF_(0x800401A0)

;;
;; MessageId: INPLACE_E_NOTOOLSPACE
;;
;; MessageText:
;;
;;  Space for tools is not available
;;
INPLACE_E_NOTOOLSPACE equ _HRESULT_TYPEDEF_(0x800401A1)

INPLACE_E_FIRST equ 0x800401A0
INPLACE_E_LAST	equ 0x800401AF
INPLACE_S_FIRST equ 0x000401A0
INPLACE_S_LAST	equ 0x000401AF
ENUM_E_FIRST	equ 0x800401B0
ENUM_E_LAST	equ 0x800401BF
ENUM_S_FIRST	equ 0x000401B0
ENUM_S_LAST	equ 0x000401BF
CONVERT10_E_FIRST	equ 0x800401C0
CONVERT10_E_LAST	equ 0x800401CF
CONVERT10_S_FIRST	equ 0x000401C0
CONVERT10_S_LAST	equ 0x000401CF
;;
;; MessageId: CONVERT10_E_OLESTREAM_GET
;;
;; MessageText:
;;
;;  OLESTREAM Get method failed
;;
CONVERT10_E_OLESTREAM_GET equ _HRESULT_TYPEDEF_(0x800401C0)

;;
;; MessageId: CONVERT10_E_OLESTREAM_PUT
;;
;; MessageText:
;;
;;  OLESTREAM Put method failed
;;
CONVERT10_E_OLESTREAM_PUT equ _HRESULT_TYPEDEF_(0x800401C1)

;;
;; MessageId: CONVERT10_E_OLESTREAM_FMT
;;
;; MessageText:
;;
;;  Contents of the OLESTREAM not in correct format
;;
CONVERT10_E_OLESTREAM_FMT equ _HRESULT_TYPEDEF_(0x800401C2)

;;
;; MessageId: CONVERT10_E_OLESTREAM_BITMAP_TO_DIB
;;
;; MessageText:
;;
;;  There was an error in a Windows GDI call while converting the bitmap to a DIB
;;
CONVERT10_E_OLESTREAM_BITMAP_TO_DIB equ _HRESULT_TYPEDEF_(0x800401C3)

;;
;; MessageId: CONVERT10_E_STG_FMT
;;
;; MessageText:
;;
;;  Contents of the IStorage not in correct format
;;
CONVERT10_E_STG_FMT equ _HRESULT_TYPEDEF_(0x800401C4)

;;
;; MessageId: CONVERT10_E_STG_NO_STD_STREAM
;;
;; MessageText:
;;
;;  Contents of IStorage is missing one of the standard streams
;;
CONVERT10_E_STG_NO_STD_STREAM equ _HRESULT_TYPEDEF_(0x800401C5)

;;
;; MessageId: CONVERT10_E_STG_DIB_TO_BITMAP
;;
;; MessageText:
;;
;;  There was an error in a Windows GDI call while converting the DIB to a bitmap.
;;
;;
CONVERT10_E_STG_DIB_TO_BITMAP equ _HRESULT_TYPEDEF_(0x800401C6)

CLIPBRD_E_FIRST equ 0x800401D0
CLIPBRD_E_LAST	equ 0x800401DF
CLIPBRD_S_FIRST equ 0x000401D0
CLIPBRD_S_LAST	equ 0x000401DF
;;
;; MessageId: CLIPBRD_E_CANT_OPEN
;;
;; MessageText:
;;
;;  OpenClipboard Failed
;;
CLIPBRD_E_CANT_OPEN equ _HRESULT_TYPEDEF_(0x800401D0)

;;
;; MessageId: CLIPBRD_E_CANT_EMPTY
;;
;; MessageText:
;;
;;  EmptyClipboard Failed
;;
CLIPBRD_E_CANT_EMPTY equ _HRESULT_TYPEDEF_(0x800401D1)

;;
;; MessageId: CLIPBRD_E_CANT_SET
;;
;; MessageText:
;;
;;  SetClipboard Failed
;;
CLIPBRD_E_CANT_SET equ _HRESULT_TYPEDEF_(0x800401D2)

;;
;; MessageId: CLIPBRD_E_BAD_DATA
;;
;; MessageText:
;;
;;  Data on clipboard is invalid
;;
CLIPBRD_E_BAD_DATA equ _HRESULT_TYPEDEF_(0x800401D3)

;;
;; MessageId: CLIPBRD_E_CANT_CLOSE
;;
;; MessageText:
;;
;;  CloseClipboard Failed
;;
CLIPBRD_E_CANT_CLOSE equ _HRESULT_TYPEDEF_(0x800401D4)

MK_E_FIRST	equ 0x800401E0
MK_E_LAST	equ 0x800401EF
MK_S_FIRST	equ 0x000401E0
MK_S_LAST	equ 0x000401EF
;;
;; MessageId: MK_E_CONNECTMANUALLY
;;
;; MessageText:
;;
;;  Moniker needs to be connected manually
;;
MK_E_CONNECTMANUALLY equ _HRESULT_TYPEDEF_(0x800401E0)

;;
;; MessageId: MK_E_EXCEEDEDDEADLINE
;;
;; MessageText:
;;
;;  Operation exceeded deadline
;;
MK_E_EXCEEDEDDEADLINE equ _HRESULT_TYPEDEF_(0x800401E1)

;;
;; MessageId: MK_E_NEEDGENERIC
;;
;; MessageText:
;;
;;  Moniker needs to be generic
;;
MK_E_NEEDGENERIC equ _HRESULT_TYPEDEF_(0x800401E2)

;;
;; MessageId: MK_E_UNAVAILABLE
;;
;; MessageText:
;;
;;  Operation unavailable
;;
MK_E_UNAVAILABLE equ _HRESULT_TYPEDEF_(0x800401E3)

;;
;; MessageId: MK_E_SYNTAX
;;
;; MessageText:
;;
;;  Invalid syntax
;;
MK_E_SYNTAX equ _HRESULT_TYPEDEF_(0x800401E4)

;;
;; MessageId: MK_E_NOOBJECT
;;
;; MessageText:
;;
;;  No object for moniker
;;
MK_E_NOOBJECT equ _HRESULT_TYPEDEF_(0x800401E5)

;;
;; MessageId: MK_E_INVALIDEXTENSION
;;
;; MessageText:
;;
;;  Bad extension for file
;;
MK_E_INVALIDEXTENSION equ _HRESULT_TYPEDEF_(0x800401E6)

;;
;; MessageId: MK_E_INTERMEDIATEINTERFACENOTSUPPORTED
;;
;; MessageText:
;;
;;  Intermediate operation failed
;;
MK_E_INTERMEDIATEINTERFACENOTSUPPORTED equ _HRESULT_TYPEDEF_(0x800401E7)

;;
;; MessageId: MK_E_NOTBINDABLE
;;
;; MessageText:
;;
;;  Moniker is not bindable
;;
MK_E_NOTBINDABLE equ _HRESULT_TYPEDEF_(0x800401E8)

;;
;; MessageId: MK_E_NOTBOUND
;;
;; MessageText:
;;
;;  Moniker is not bound
;;
MK_E_NOTBOUND equ _HRESULT_TYPEDEF_(0x800401E9)

;;
;; MessageId: MK_E_CANTOPENFILE
;;
;; MessageText:
;;
;;  Moniker cannot open file
;;
MK_E_CANTOPENFILE equ _HRESULT_TYPEDEF_(0x800401EA)

;;
;; MessageId: MK_E_MUSTBOTHERUSER
;;
;; MessageText:
;;
;;  User input required for operation to succeed
;;
MK_E_MUSTBOTHERUSER equ _HRESULT_TYPEDEF_(0x800401EB)

;;
;; MessageId: MK_E_NOINVERSE
;;
;; MessageText:
;;
;;  Moniker class has no inverse
;;
MK_E_NOINVERSE equ _HRESULT_TYPEDEF_(0x800401EC)

;;
;; MessageId: MK_E_NOSTORAGE
;;
;; MessageText:
;;
;;  Moniker does not refer to storage
;;
MK_E_NOSTORAGE equ _HRESULT_TYPEDEF_(0x800401ED)

;;
;; MessageId: MK_E_NOPREFIX
;;
;; MessageText:
;;
;;  No common prefix
;;
MK_E_NOPREFIX equ _HRESULT_TYPEDEF_(0x800401EE)

;;
;; MessageId: MK_E_ENUMERATION_FAILED
;;
;; MessageText:
;;
;;  Moniker could not be enumerated
;;
MK_E_ENUMERATION_FAILED equ _HRESULT_TYPEDEF_(0x800401EF)

CO_E_FIRST	equ 0x800401F0
CO_E_LAST	equ 0x800401FF
CO_S_FIRST	equ 0x000401F0
CO_S_LAST	equ 0x000401FF
;;
;; MessageId: CO_E_NOTINITIALIZED
;;
;; MessageText:
;;
;;  CoInitialize has not been called.
;;
CO_E_NOTINITIALIZED equ _HRESULT_TYPEDEF_(0x800401F0)

;;
;; MessageId: CO_E_ALREADYINITIALIZED
;;
;; MessageText:
;;
;;  CoInitialize has already been called.
;;
CO_E_ALREADYINITIALIZED equ _HRESULT_TYPEDEF_(0x800401F1)

;;
;; MessageId: CO_E_CANTDETERMINECLASS
;;
;; MessageText:
;;
;;  Class of object cannot be determined
;;
CO_E_CANTDETERMINECLASS equ _HRESULT_TYPEDEF_(0x800401F2)

;;
;; MessageId: CO_E_CLASSSTRING
;;
;; MessageText:
;;
;;  Invalid class string
;;
CO_E_CLASSSTRING equ _HRESULT_TYPEDEF_(0x800401F3)

;;
;; MessageId: CO_E_IIDSTRING
;;
;; MessageText:
;;
;;  Invalid interface string
;;
CO_E_IIDSTRING equ _HRESULT_TYPEDEF_(0x800401F4)

;;
;; MessageId: CO_E_APPNOTFOUND
;;
;; MessageText:
;;
;;  Application not found
;;
CO_E_APPNOTFOUND equ _HRESULT_TYPEDEF_(0x800401F5)

;;
;; MessageId: CO_E_APPSINGLEUSE
;;
;; MessageText:
;;
;;  Application cannot be run more than once
;;
CO_E_APPSINGLEUSE equ _HRESULT_TYPEDEF_(0x800401F6)

;;
;; MessageId: CO_E_ERRORINAPP
;;
;; MessageText:
;;
;;  Some error in application program
;;
CO_E_ERRORINAPP equ _HRESULT_TYPEDEF_(0x800401F7)

;;
;; MessageId: CO_E_DLLNOTFOUND
;;
;; MessageText:
;;
;;  DLL for class not found
;;
CO_E_DLLNOTFOUND equ _HRESULT_TYPEDEF_(0x800401F8)

;;
;; MessageId: CO_E_ERRORINDLL
;;
;; MessageText:
;;
;;  Error in the DLL
;;
CO_E_ERRORINDLL equ _HRESULT_TYPEDEF_(0x800401F9)

;;
;; MessageId: CO_E_WRONGOSFORAPP
;;
;; MessageText:
;;
;;  Wrong OS or OS version for application
;;
CO_E_WRONGOSFORAPP equ _HRESULT_TYPEDEF_(0x800401FA)

;;
;; MessageId: CO_E_OBJNOTREG
;;
;; MessageText:
;;
;;  Object is not registered
;;
CO_E_OBJNOTREG equ _HRESULT_TYPEDEF_(0x800401FB)

;;
;; MessageId: CO_E_OBJISREG
;;
;; MessageText:
;;
;;  Object is already registered
;;
CO_E_OBJISREG equ _HRESULT_TYPEDEF_(0x800401FC)

;;
;; MessageId: CO_E_OBJNOTCONNECTED
;;
;; MessageText:
;;
;;  Object is not connected to server
;;
CO_E_OBJNOTCONNECTED equ _HRESULT_TYPEDEF_(0x800401FD)

;;
;; MessageId: CO_E_APPDIDNTREG
;;
;; MessageText:
;;
;;  Application was launched but it didn't register a class factory
;;
CO_E_APPDIDNTREG equ _HRESULT_TYPEDEF_(0x800401FE)

;;
;; MessageId: CO_E_RELEASED
;;
;; MessageText:
;;
;;  Object has been released
;;
CO_E_RELEASED equ _HRESULT_TYPEDEF_(0x800401FF)

;;
;; MessageId: CO_E_FAILEDTOIMPERSONATE
;;
;; MessageText:
;;
;;  Unable to impersonate DCOM client
;;
CO_E_FAILEDTOIMPERSONATE equ _HRESULT_TYPEDEF_(0x80040200)

;;
;; MessageId: CO_E_FAILEDTOGETSECCTX
;;
;; MessageText:
;;
;;  Unable to obtain server's security context
;;
CO_E_FAILEDTOGETSECCTX equ _HRESULT_TYPEDEF_(0x80040201)

;;
;; MessageId: CO_E_FAILEDTOOPENTHREADTOKEN
;;
;; MessageText:
;;
;;  Unable to open the access token of the current thread
;;
CO_E_FAILEDTOOPENTHREADTOKEN equ _HRESULT_TYPEDEF_(0x80040202)

;;
;; MessageId: CO_E_FAILEDTOGETTOKENINFO
;;
;; MessageText:
;;
;;  Unable to obtain user info from an access token
;;
CO_E_FAILEDTOGETTOKENINFO equ _HRESULT_TYPEDEF_(0x80040203)

;;
;; MessageId: CO_E_TRUSTEEDOESNTMATCHCLIENT
;;
;; MessageText:
;;
;;  The client who called IAccessControl::IsAccessPermitted was the trustee provided tot he method
;;
CO_E_TRUSTEEDOESNTMATCHCLIENT equ _HRESULT_TYPEDEF_(0x80040204)

;;
;; MessageId: CO_E_FAILEDTOQUERYCLIENTBLANKET
;;
;; MessageText:
;;
;;  Unable to obtain the client's security blanket
;;
CO_E_FAILEDTOQUERYCLIENTBLANKET equ _HRESULT_TYPEDEF_(0x80040205)

;;
;; MessageId: CO_E_FAILEDTOSETDACL
;;
;; MessageText:
;;
;;  Unable to set a discretionary ACL into a security descriptor
;;
CO_E_FAILEDTOSETDACL equ _HRESULT_TYPEDEF_(0x80040206)

;;
;; MessageId: CO_E_ACCESSCHECKFAILED
;;
;; MessageText:
;;
;;  The system function, AccessCheck, returned false
;;
CO_E_ACCESSCHECKFAILED equ _HRESULT_TYPEDEF_(0x80040207)

;;
;; MessageId: CO_E_NETACCESSAPIFAILED
;;
;; MessageText:
;;
;;  Either NetAccessDel or NetAccessAdd returned an error code.
;;
CO_E_NETACCESSAPIFAILED equ _HRESULT_TYPEDEF_(0x80040208)

;;
;; MessageId: CO_E_WRONGTRUSTEENAMESYNTAX
;;
;; MessageText:
;;
;;  One of the trustee strings provided by the user did not conform to the <Domain>\<Name> syntax and it was not the "*" string
;;
CO_E_WRONGTRUSTEENAMESYNTAX equ _HRESULT_TYPEDEF_(0x80040209)

;;
;; MessageId: CO_E_INVALIDSID
;;
;; MessageText:
;;
;;  One of the security identifiers provided by the user was invalid
;;
CO_E_INVALIDSID equ _HRESULT_TYPEDEF_(0x8004020A)

;;
;; MessageId: CO_E_CONVERSIONFAILED
;;
;; MessageText:
;;
;;  Unable to convert a wide character trustee string to a multibyte trustee string
;;
CO_E_CONVERSIONFAILED equ _HRESULT_TYPEDEF_(0x8004020B)

;;
;; MessageId: CO_E_NOMATCHINGSIDFOUND
;;
;; MessageText:
;;
;;  Unable to find a security identifier that corresponds to a trustee string provided by the user
;;
CO_E_NOMATCHINGSIDFOUND equ _HRESULT_TYPEDEF_(0x8004020C)

;;
;; MessageId: CO_E_LOOKUPACCSIDFAILED
;;
;; MessageText:
;;
;;  The system function, LookupAccountSID, failed
;;
CO_E_LOOKUPACCSIDFAILED equ _HRESULT_TYPEDEF_(0x8004020D)

;;
;; MessageId: CO_E_NOMATCHINGNAMEFOUND
;;
;; MessageText:
;;
;;  Unable to find a trustee name that corresponds to a security identifier provided by the user
;;
CO_E_NOMATCHINGNAMEFOUND equ _HRESULT_TYPEDEF_(0x8004020E)

;;
;; MessageId: CO_E_LOOKUPACCNAMEFAILED
;;
;; MessageText:
;;
;;  The system function, LookupAccountName, failed
;;
CO_E_LOOKUPACCNAMEFAILED equ _HRESULT_TYPEDEF_(0x8004020F)

;;
;; MessageId: CO_E_SETSERLHNDLFAILED
;;
;; MessageText:
;;
;;  Unable to set or reset a serialization handle
;;
CO_E_SETSERLHNDLFAILED equ _HRESULT_TYPEDEF_(0x80040210)

;;
;; MessageId: CO_E_FAILEDTOGETWINDIR
;;
;; MessageText:
;;
;;  Unable to obtain the Windows directory
;;
CO_E_FAILEDTOGETWINDIR equ _HRESULT_TYPEDEF_(0x80040211)

;;
;; MessageId: CO_E_PATHTOOLONG
;;
;; MessageText:
;;
;;  Path too long
;;
CO_E_PATHTOOLONG equ _HRESULT_TYPEDEF_(0x80040212)

;;
;; MessageId: CO_E_FAILEDTOGENUUID
;;
;; MessageText:
;;
;;  Unable to generate a uuid.
;;
CO_E_FAILEDTOGENUUID equ _HRESULT_TYPEDEF_(0x80040213)

;;
;; MessageId: CO_E_FAILEDTOCREATEFILE
;;
;; MessageText:
;;
;;  Unable to create file
;;
CO_E_FAILEDTOCREATEFILE equ _HRESULT_TYPEDEF_(0x80040214)

;;
;; MessageId: CO_E_FAILEDTOCLOSEHANDLE
;;
;; MessageText:
;;
;;  Unable to close a serialization handle or a file handle.
;;
CO_E_FAILEDTOCLOSEHANDLE equ _HRESULT_TYPEDEF_(0x80040215)

;;
;; MessageId: CO_E_EXCEEDSYSACLLIMIT
;;
;; MessageText:
;;
;;  The number of ACEs in an ACL exceeds the system limit
;;
CO_E_EXCEEDSYSACLLIMIT equ _HRESULT_TYPEDEF_(0x80040216)

;;
;; MessageId: CO_E_ACESINWRONGORDER
;;
;; MessageText:
;;
;;  Not all the DENY_ACCESS ACEs are arranged in front of the GRANT_ACCESS ACEs in the stream
;;
CO_E_ACESINWRONGORDER equ _HRESULT_TYPEDEF_(0x80040217)

;;
;; MessageId: CO_E_INCOMPATIBLESTREAMVERSION
;;
;; MessageText:
;;
;;  The version of ACL format in the stream is not supported by this implementation of IAccessControl
;;
CO_E_INCOMPATIBLESTREAMVERSION equ _HRESULT_TYPEDEF_(0x80040218)

;;
;; MessageId: CO_E_FAILEDTOOPENPROCESSTOKEN
;;
;; MessageText:
;;
;;  Unable to open the access token of the server process
;;
CO_E_FAILEDTOOPENPROCESSTOKEN equ _HRESULT_TYPEDEF_(0x80040219)

;;
;; MessageId: CO_E_DECODEFAILED
;;
;; MessageText:
;;
;;  Unable to decode the ACL in the stream provided by the user
;;
CO_E_DECODEFAILED equ _HRESULT_TYPEDEF_(0x8004021A)

;;
;; MessageId: CO_E_ACNOTINITIALIZED
;;
;; MessageText:
;;
;;  The COM IAccessControl object is not initialized
;;
CO_E_ACNOTINITIALIZED equ _HRESULT_TYPEDEF_(0x8004021B)

;;
;; Old OLE Success Codes
;;
;;
;; MessageId: OLE_S_USEREG
;;
;; MessageText:
;;
;;  Use the registry database to provide the requested information
;;
OLE_S_USEREG equ _HRESULT_TYPEDEF_(0x00040000)

;;
;; MessageId: OLE_S_STATIC
;;
;; MessageText:
;;
;;  Success, but static
;;
OLE_S_STATIC equ _HRESULT_TYPEDEF_(0x00040001)

;;
;; MessageId: OLE_S_MAC_CLIPFORMAT
;;
;; MessageText:
;;
;;  Macintosh clipboard format
;;
OLE_S_MAC_CLIPFORMAT equ _HRESULT_TYPEDEF_(0x00040002)

;;
;; MessageId: DRAGDROP_S_DROP
;;
;; MessageText:
;;
;;  Successful drop took place
;;
DRAGDROP_S_DROP equ _HRESULT_TYPEDEF_(0x00040100)

;;
;; MessageId: DRAGDROP_S_CANCEL
;;
;; MessageText:
;;
;;  Drag-drop operation canceled
;;
DRAGDROP_S_CANCEL equ _HRESULT_TYPEDEF_(0x00040101)

;;
;; MessageId: DRAGDROP_S_USEDEFAULTCURSORS
;;
;; MessageText:
;;
;;  Use the default cursor
;;
DRAGDROP_S_USEDEFAULTCURSORS equ _HRESULT_TYPEDEF_(0x00040102)

;;
;; MessageId: DATA_S_SAMEFORMATETC
;;
;; MessageText:
;;
;;  Data has same FORMATETC
;;
DATA_S_SAMEFORMATETC equ _HRESULT_TYPEDEF_(0x00040130)

;;
;; MessageId: VIEW_S_ALREADY_FROZEN
;;
;; MessageText:
;;
;;  View is already frozen
;;
VIEW_S_ALREADY_FROZEN equ _HRESULT_TYPEDEF_(0x00040140)

;;
;; MessageId: CACHE_S_FORMATETC_NOTSUPPORTED
;;
;; MessageText:
;;
;;  FORMATETC not supported
;;
CACHE_S_FORMATETC_NOTSUPPORTED equ _HRESULT_TYPEDEF_(0x00040170)

;;
;; MessageId: CACHE_S_SAMECACHE
;;
;; MessageText:
;;
;;  Same cache
;;
CACHE_S_SAMECACHE equ _HRESULT_TYPEDEF_(0x00040171)

;;
;; MessageId: CACHE_S_SOMECACHES_NOTUPDATED
;;
;; MessageText:
;;
;;  Some cache(s) not updated
;;
CACHE_S_SOMECACHES_NOTUPDATED equ _HRESULT_TYPEDEF_(0x00040172)

;;
;; MessageId: OLEOBJ_S_INVALIDVERB
;;
;; MessageText:
;;
;;  Invalid verb for OLE object
;;
OLEOBJ_S_INVALIDVERB equ _HRESULT_TYPEDEF_(0x00040180)

;;
;; MessageId: OLEOBJ_S_CANNOT_DOVERB_NOW
;;
;; MessageText:
;;
;;  Verb number is valid but verb cannot be done now
;;
OLEOBJ_S_CANNOT_DOVERB_NOW equ _HRESULT_TYPEDEF_(0x00040181)

;;
;; MessageId: OLEOBJ_S_INVALIDHWND
;;
;; MessageText:
;;
;;  Invalid window handle passed
;;
OLEOBJ_S_INVALIDHWND equ _HRESULT_TYPEDEF_(0x00040182)

;;
;; MessageId: INPLACE_S_TRUNCATED
;;
;; MessageText:
;;
;;  Message is too long; some of it had to be truncated before displaying
;;
INPLACE_S_TRUNCATED equ _HRESULT_TYPEDEF_(0x000401A0)

;;
;; MessageId: CONVERT10_S_NO_PRESENTATION
;;
;; MessageText:
;;
;;  Unable to convert OLESTREAM to IStorage
;;
CONVERT10_S_NO_PRESENTATION equ _HRESULT_TYPEDEF_(0x000401C0)

;;
;; MessageId: MK_S_REDUCED_TO_SELF
;;
;; MessageText:
;;
;;  Moniker reduced to itself
;;
MK_S_REDUCED_TO_SELF equ _HRESULT_TYPEDEF_(0x000401E2)

;;
;; MessageId: MK_S_ME
;;
;; MessageText:
;;
;;  Common prefix is this moniker
;;
MK_S_ME equ _HRESULT_TYPEDEF_(0x000401E4)

;;
;; MessageId: MK_S_HIM
;;
;; MessageText:
;;
;;  Common prefix is input moniker
;;
MK_S_HIM equ _HRESULT_TYPEDEF_(0x000401E5)

;;
;; MessageId: MK_S_US
;;
;; MessageText:
;;
;;  Common prefix is both monikers
;;
MK_S_US equ _HRESULT_TYPEDEF_(0x000401E6)

;;
;; MessageId: MK_S_MONIKERALREADYREGISTERED
;;
;; MessageText:
;;
;;  Moniker is already registered in running object table
;;
MK_S_MONIKERALREADYREGISTERED equ _HRESULT_TYPEDEF_(0x000401E7)

;; ******************
;; FACILITY_WINDOWS
;; ******************
;;
;; Codes 0x0-0x01ff are reserved for the OLE group of
;; interfaces.
;;
;;
;; MessageId: CO_E_CLASS_CREATE_FAILED
;;
;; MessageText:
;;
;;  Attempt to create a class object failed
;;
CO_E_CLASS_CREATE_FAILED equ _HRESULT_TYPEDEF_(0x80080001)

;;
;; MessageId: CO_E_SCM_ERROR
;;
;; MessageText:
;;
;;  OLE service could not bind object
;;
CO_E_SCM_ERROR equ _HRESULT_TYPEDEF_(0x80080002)

;;
;; MessageId: CO_E_SCM_RPC_FAILURE
;;
;; MessageText:
;;
;;  RPC communication failed with OLE service
;;
CO_E_SCM_RPC_FAILURE equ _HRESULT_TYPEDEF_(0x80080003)

;;
;; MessageId: CO_E_BAD_PATH
;;
;; MessageText:
;;
;;  Bad path to object
;;
CO_E_BAD_PATH equ _HRESULT_TYPEDEF_(0x80080004)

;;
;; MessageId: CO_E_SERVER_EXEC_FAILURE
;;
;; MessageText:
;;
;;  Server execution failed
;;
CO_E_SERVER_EXEC_FAILURE equ _HRESULT_TYPEDEF_(0x80080005)

;;
;; MessageId: CO_E_OBJSRV_RPC_FAILURE
;;
;; MessageText:
;;
;;  OLE service could not communicate with the object server
;;
CO_E_OBJSRV_RPC_FAILURE equ _HRESULT_TYPEDEF_(0x80080006)

;;
;; MessageId: MK_E_NO_NORMALIZED
;;
;; MessageText:
;;
;;  Moniker path could not be normalized
;;
MK_E_NO_NORMALIZED equ _HRESULT_TYPEDEF_(0x80080007)

;;
;; MessageId: CO_E_SERVER_STOPPING
;;
;; MessageText:
;;
;;  Object server is stopping when OLE service contacts it
;;
CO_E_SERVER_STOPPING equ _HRESULT_TYPEDEF_(0x80080008)

;;
;; MessageId: MEM_E_INVALID_ROOT
;;
;; MessageText:
;;
;;  An invalid root block pointer was specified
;;
MEM_E_INVALID_ROOT equ _HRESULT_TYPEDEF_(0x80080009)

;;
;; MessageId: MEM_E_INVALID_LINK
;;
;; MessageText:
;;
;;  An allocation chain contained an invalid link pointer
;;
MEM_E_INVALID_LINK equ _HRESULT_TYPEDEF_(0x80080010)

;;
;; MessageId: MEM_E_INVALID_SIZE
;;
;; MessageText:
;;
;;  The requested allocation size was too large
;;
MEM_E_INVALID_SIZE equ _HRESULT_TYPEDEF_(0x80080011)

;;
;; MessageId: CO_S_NOTALLINTERFACES
;;
;; MessageText:
;;
;;  Not all the requested interfaces were available
;;
CO_S_NOTALLINTERFACES equ _HRESULT_TYPEDEF_(0x00080012)

;; ******************
;; FACILITY_DISPATCH
;; ******************
;;
;; MessageId: DISP_E_UNKNOWNINTERFACE
;;
;; MessageText:
;;
;;  Unknown interface.
;;
DISP_E_UNKNOWNINTERFACE equ _HRESULT_TYPEDEF_(0x80020001)

;;
;; MessageId: DISP_E_MEMBERNOTFOUND
;;
;; MessageText:
;;
;;  Member not found.
;;
DISP_E_MEMBERNOTFOUND equ _HRESULT_TYPEDEF_(0x80020003)

;;
;; MessageId: DISP_E_PARAMNOTFOUND
;;
;; MessageText:
;;
;;  Parameter not found.
;;
DISP_E_PARAMNOTFOUND equ _HRESULT_TYPEDEF_(0x80020004)

;;
;; MessageId: DISP_E_TYPEMISMATCH
;;
;; MessageText:
;;
;;  Type mismatch.
;;
DISP_E_TYPEMISMATCH equ _HRESULT_TYPEDEF_(0x80020005)

;;
;; MessageId: DISP_E_UNKNOWNNAME
;;
;; MessageText:
;;
;;  Unknown name.
;;
DISP_E_UNKNOWNNAME equ _HRESULT_TYPEDEF_(0x80020006)

;;
;; MessageId: DISP_E_NONAMEDARGS
;;
;; MessageText:
;;
;;  No named arguments.
;;
DISP_E_NONAMEDARGS equ _HRESULT_TYPEDEF_(0x80020007)

;;
;; MessageId: DISP_E_BADVARTYPE
;;
;; MessageText:
;;
;;  Bad variable type.
;;
DISP_E_BADVARTYPE equ _HRESULT_TYPEDEF_(0x80020008)

;;
;; MessageId: DISP_E_EXCEPTION
;;
;; MessageText:
;;
;;  Exception occurred.
;;
DISP_E_EXCEPTION equ _HRESULT_TYPEDEF_(0x80020009)

;;
;; MessageId: DISP_E_OVERFLOW
;;
;; MessageText:
;;
;;  Out of present range.
;;
DISP_E_OVERFLOW equ _HRESULT_TYPEDEF_(0x8002000A)

;;
;; MessageId: DISP_E_BADINDEX
;;
;; MessageText:
;;
;;  Invalid index.
;;
DISP_E_BADINDEX equ _HRESULT_TYPEDEF_(0x8002000B)

;;
;; MessageId: DISP_E_UNKNOWNLCID
;;
;; MessageText:
;;
;;  Unknown language.
;;
DISP_E_UNKNOWNLCID equ _HRESULT_TYPEDEF_(0x8002000C)

;;
;; MessageId: DISP_E_ARRAYISLOCKED
;;
;; MessageText:
;;
;;  Memory is locked.
;;
DISP_E_ARRAYISLOCKED equ _HRESULT_TYPEDEF_(0x8002000D)

;;
;; MessageId: DISP_E_BADPARAMCOUNT
;;
;; MessageText:
;;
;;  Invalid number of parameters.
;;
DISP_E_BADPARAMCOUNT equ _HRESULT_TYPEDEF_(0x8002000E)

;;
;; MessageId: DISP_E_PARAMNOTOPTIONAL
;;
;; MessageText:
;;
;;  Parameter not optional.
;;
DISP_E_PARAMNOTOPTIONAL equ _HRESULT_TYPEDEF_(0x8002000F)

;;
;; MessageId: DISP_E_BADCALLEE
;;
;; MessageText:
;;
;;  Invalid callee.
;;
DISP_E_BADCALLEE equ _HRESULT_TYPEDEF_(0x80020010)

;;
;; MessageId: DISP_E_NOTACOLLECTION
;;
;; MessageText:
;;
;;  Does not support a collection.
;;
DISP_E_NOTACOLLECTION equ _HRESULT_TYPEDEF_(0x80020011)

;;
;; MessageId: DISP_E_DIVBYZERO
;;
;; MessageText:
;;
;;  Division by zero.
;;
DISP_E_DIVBYZERO equ _HRESULT_TYPEDEF_(0x80020012)

;;
;; MessageId: TYPE_E_BUFFERTOOSMALL
;;
;; MessageText:
;;
;;  Buffer too small.
;;
TYPE_E_BUFFERTOOSMALL equ _HRESULT_TYPEDEF_(0x80028016)

;;
;; MessageId: TYPE_E_FIELDNOTFOUND
;;
;; MessageText:
;;
;;  Field name not defined in the record.
;;
TYPE_E_FIELDNOTFOUND equ _HRESULT_TYPEDEF_(0x80028017)

;;
;; MessageId: TYPE_E_INVDATAREAD
;;
;; MessageText:
;;
;;  Old format or invalid type library.
;;
TYPE_E_INVDATAREAD equ _HRESULT_TYPEDEF_(0x80028018)

;;
;; MessageId: TYPE_E_UNSUPFORMAT
;;
;; MessageText:
;;
;;  Old format or invalid type library.
;;
TYPE_E_UNSUPFORMAT equ _HRESULT_TYPEDEF_(0x80028019)

;;
;; MessageId: TYPE_E_REGISTRYACCESS
;;
;; MessageText:
;;
;;  Error accessing the OLE registry.
;;
TYPE_E_REGISTRYACCESS equ _HRESULT_TYPEDEF_(0x8002801C)

;;
;; MessageId: TYPE_E_LIBNOTREGISTERED
;;
;; MessageText:
;;
;;  Library not registered.
;;
TYPE_E_LIBNOTREGISTERED equ _HRESULT_TYPEDEF_(0x8002801D)

;;
;; MessageId: TYPE_E_UNDEFINEDTYPE
;;
;; MessageText:
;;
;;  Bound to unknown type.
;;
TYPE_E_UNDEFINEDTYPE equ _HRESULT_TYPEDEF_(0x80028027)

;;
;; MessageId: TYPE_E_QUALIFIEDNAMEDISALLOWED
;;
;; MessageText:
;;
;;  Qualified name disallowed.
;;
TYPE_E_QUALIFIEDNAMEDISALLOWED equ _HRESULT_TYPEDEF_(0x80028028)

;;
;; MessageId: TYPE_E_INVALIDSTATE
;;
;; MessageText:
;;
;;  Invalid forward reference, or reference to uncompiled type.
;;
TYPE_E_INVALIDSTATE equ _HRESULT_TYPEDEF_(0x80028029)

;;
;; MessageId: TYPE_E_WRONGTYPEKIND
;;
;; MessageText:
;;
;;  Type mismatch.
;;
TYPE_E_WRONGTYPEKIND equ _HRESULT_TYPEDEF_(0x8002802A)

;;
;; MessageId: TYPE_E_ELEMENTNOTFOUND
;;
;; MessageText:
;;
;;  Element not found.
;;
TYPE_E_ELEMENTNOTFOUND equ _HRESULT_TYPEDEF_(0x8002802B)

;;
;; MessageId: TYPE_E_AMBIGUOUSNAME
;;
;; MessageText:
;;
;;  Ambiguous name.
;;
TYPE_E_AMBIGUOUSNAME equ _HRESULT_TYPEDEF_(0x8002802C)

;;
;; MessageId: TYPE_E_NAMECONFLICT
;;
;; MessageText:
;;
;;  Name already exists in the library.
;;
TYPE_E_NAMECONFLICT equ _HRESULT_TYPEDEF_(0x8002802D)

;;
;; MessageId: TYPE_E_UNKNOWNLCID
;;
;; MessageText:
;;
;;  Unknown LCID.
;;
TYPE_E_UNKNOWNLCID equ _HRESULT_TYPEDEF_(0x8002802E)

;;
;; MessageId: TYPE_E_DLLFUNCTIONNOTFOUND
;;
;; MessageText:
;;
;;  Function not defined in specified DLL.
;;
TYPE_E_DLLFUNCTIONNOTFOUND equ _HRESULT_TYPEDEF_(0x8002802F)

;;
;; MessageId: TYPE_E_BADMODULEKIND
;;
;; MessageText:
;;
;;  Wrong module kind for the operation.
;;
TYPE_E_BADMODULEKIND equ _HRESULT_TYPEDEF_(0x800288BD)

;;
;; MessageId: TYPE_E_SIZETOOBIG
;;
;; MessageText:
;;
;;  Size may not exceed 64K.
;;
TYPE_E_SIZETOOBIG equ _HRESULT_TYPEDEF_(0x800288C5)

;;
;; MessageId: TYPE_E_DUPLICATEID
;;
;; MessageText:
;;
;;  Duplicate ID in inheritance hierarchy.
;;
TYPE_E_DUPLICATEID equ _HRESULT_TYPEDEF_(0x800288C6)

;;
;; MessageId: TYPE_E_INVALIDID
;;
;; MessageText:
;;
;;  Incorrect inheritance depth in standard OLE hmember.
;;
TYPE_E_INVALIDID equ _HRESULT_TYPEDEF_(0x800288CF)

;;
;; MessageId: TYPE_E_TYPEMISMATCH
;;
;; MessageText:
;;
;;  Type mismatch.
;;
TYPE_E_TYPEMISMATCH equ _HRESULT_TYPEDEF_(0x80028CA0)

;;
;; MessageId: TYPE_E_OUTOFBOUNDS
;;
;; MessageText:
;;
;;  Invalid number of arguments.
;;
TYPE_E_OUTOFBOUNDS equ _HRESULT_TYPEDEF_(0x80028CA1)

;;
;; MessageId: TYPE_E_IOERROR
;;
;; MessageText:
;;
;;  I/O Error.
;;
TYPE_E_IOERROR equ _HRESULT_TYPEDEF_(0x80028CA2)

;;
;; MessageId: TYPE_E_CANTCREATETMPFILE
;;
;; MessageText:
;;
;;  Error creating unique tmp file.
;;
TYPE_E_CANTCREATETMPFILE equ _HRESULT_TYPEDEF_(0x80028CA3)

;;
;; MessageId: TYPE_E_CANTLOADLIBRARY
;;
;; MessageText:
;;
;;  Error loading type library/DLL.
;;
TYPE_E_CANTLOADLIBRARY equ _HRESULT_TYPEDEF_(0x80029C4A)

;;
;; MessageId: TYPE_E_INCONSISTENTPROPFUNCS
;;
;; MessageText:
;;
;;  Inconsistent property functions.
;;
TYPE_E_INCONSISTENTPROPFUNCS equ _HRESULT_TYPEDEF_(0x80029C83)

;;
;; MessageId: TYPE_E_CIRCULARTYPE
;;
;; MessageText:
;;
;;  Circular dependency between types/modules.
;;
TYPE_E_CIRCULARTYPE equ _HRESULT_TYPEDEF_(0x80029C84)

;; ******************
;; FACILITY_STORAGE
;; ******************
;;
;; MessageId: STG_E_INVALIDFUNCTION
;;
;; MessageText:
;;
;;  Unable to perform requested operation.
;;
STG_E_INVALIDFUNCTION equ _HRESULT_TYPEDEF_(0x80030001)

;;
;; MessageId: STG_E_FILENOTFOUND
;;
;; MessageText:
;;
;;  %1 could not be found.
;;
STG_E_FILENOTFOUND equ _HRESULT_TYPEDEF_(0x80030002)

;;
;; MessageId: STG_E_PATHNOTFOUND
;;
;; MessageText:
;;
;;  The path %1 could not be found.
;;
STG_E_PATHNOTFOUND equ _HRESULT_TYPEDEF_(0x80030003)

;;
;; MessageId: STG_E_TOOMANYOPENFILES
;;
;; MessageText:
;;
;;  There are insufficient resources to open another file.
;;
STG_E_TOOMANYOPENFILES equ _HRESULT_TYPEDEF_(0x80030004)

;;
;; MessageId: STG_E_ACCESSDENIED
;;
;; MessageText:
;;
;;  Access Denied.
;;
STG_E_ACCESSDENIED equ _HRESULT_TYPEDEF_(0x80030005)

;;
;; MessageId: STG_E_INVALIDHANDLE
;;
;; MessageText:
;;
;;  Attempted an operation on an invalid object.
;;
STG_E_INVALIDHANDLE equ _HRESULT_TYPEDEF_(0x80030006)

;;
;; MessageId: STG_E_INSUFFICIENTMEMORY
;;
;; MessageText:
;;
;;  There is insufficient memory available to complete operation.
;;
STG_E_INSUFFICIENTMEMORY equ _HRESULT_TYPEDEF_(0x80030008)

;;
;; MessageId: STG_E_INVALIDPOINTER
;;
;; MessageText:
;;
;;  Invalid pointer error.
;;
STG_E_INVALIDPOINTER equ _HRESULT_TYPEDEF_(0x80030009)

;;
;; MessageId: STG_E_NOMOREFILES
;;
;; MessageText:
;;
;;  There are no more entries to return.
;;
STG_E_NOMOREFILES equ _HRESULT_TYPEDEF_(0x80030012)

;;
;; MessageId: STG_E_DISKISWRITEPROTECTED
;;
;; MessageText:
;;
;;  Disk is write-protected.
;;
STG_E_DISKISWRITEPROTECTED equ _HRESULT_TYPEDEF_(0x80030013)

;;
;; MessageId: STG_E_SEEKERROR
;;
;; MessageText:
;;
;;  An error occurred during a seek operation.
;;
STG_E_SEEKERROR equ _HRESULT_TYPEDEF_(0x80030019)

;;
;; MessageId: STG_E_WRITEFAULT
;;
;; MessageText:
;;
;;  A disk error occurred during a write operation.
;;
STG_E_WRITEFAULT equ _HRESULT_TYPEDEF_(0x8003001D)

;;
;; MessageId: STG_E_READFAULT
;;
;; MessageText:
;;
;;  A disk error occurred during a read operation.
;;
STG_E_READFAULT equ _HRESULT_TYPEDEF_(0x8003001E)

;;
;; MessageId: STG_E_SHAREVIOLATION
;;
;; MessageText:
;;
;;  A share violation has occurred.
;;
STG_E_SHAREVIOLATION equ _HRESULT_TYPEDEF_(0x80030020)

;;
;; MessageId: STG_E_LOCKVIOLATION
;;
;; MessageText:
;;
;;  A lock violation has occurred.
;;
STG_E_LOCKVIOLATION equ _HRESULT_TYPEDEF_(0x80030021)

;;
;; MessageId: STG_E_FILEALREADYEXISTS
;;
;; MessageText:
;;
;;  %1 already exists.
;;
STG_E_FILEALREADYEXISTS equ _HRESULT_TYPEDEF_(0x80030050)

;;
;; MessageId: STG_E_INVALIDPARAMETER
;;
;; MessageText:
;;
;;  Invalid parameter error.
;;
STG_E_INVALIDPARAMETER equ _HRESULT_TYPEDEF_(0x80030057)

;;
;; MessageId: STG_E_MEDIUMFULL
;;
;; MessageText:
;;
;;  There is insufficient disk space to complete operation.
;;
STG_E_MEDIUMFULL equ _HRESULT_TYPEDEF_(0x80030070)

;;
;; MessageId: STG_E_PROPSETMISMATCHED
;;
;; MessageText:
;;
;;  Illegal write of non-simple property to simple property set.
;;
STG_E_PROPSETMISMATCHED equ _HRESULT_TYPEDEF_(0x800300F0)

;;
;; MessageId: STG_E_ABNORMALAPIEXIT
;;
;; MessageText:
;;
;;  An API call exited abnormally.
;;
STG_E_ABNORMALAPIEXIT equ _HRESULT_TYPEDEF_(0x800300FA)

;;
;; MessageId: STG_E_INVALIDHEADER
;;
;; MessageText:
;;
;;  The file %1 is not a valid compound file.
;;
STG_E_INVALIDHEADER equ _HRESULT_TYPEDEF_(0x800300FB)

;;
;; MessageId: STG_E_INVALIDNAME
;;
;; MessageText:
;;
;;  The name %1 is not valid.
;;
STG_E_INVALIDNAME equ _HRESULT_TYPEDEF_(0x800300FC)

;;
;; MessageId: STG_E_UNKNOWN
;;
;; MessageText:
;;
;;  An unexpected error occurred.
;;
STG_E_UNKNOWN equ _HRESULT_TYPEDEF_(0x800300FD)

;;
;; MessageId: STG_E_UNIMPLEMENTEDFUNCTION
;;
;; MessageText:
;;
;;  That function is not implemented.
;;
STG_E_UNIMPLEMENTEDFUNCTION equ _HRESULT_TYPEDEF_(0x800300FE)

;;
;; MessageId: STG_E_INVALIDFLAG
;;
;; MessageText:
;;
;;  Invalid flag error.
;;
STG_E_INVALIDFLAG equ _HRESULT_TYPEDEF_(0x800300FF)

;;
;; MessageId: STG_E_INUSE
;;
;; MessageText:
;;
;;  Attempted to use an object that is busy.
;;
STG_E_INUSE equ _HRESULT_TYPEDEF_(0x80030100)

;;
;; MessageId: STG_E_NOTCURRENT
;;
;; MessageText:
;;
;;  The storage has been changed since the last commit.
;;
STG_E_NOTCURRENT equ _HRESULT_TYPEDEF_(0x80030101)

;;
;; MessageId: STG_E_REVERTED
;;
;; MessageText:
;;
;;  Attempted to use an object that has ceased to exist.
;;
STG_E_REVERTED equ _HRESULT_TYPEDEF_(0x80030102)

;;
;; MessageId: STG_E_CANTSAVE
;;
;; MessageText:
;;
;;  Can't save.
;;
STG_E_CANTSAVE equ _HRESULT_TYPEDEF_(0x80030103)

;;
;; MessageId: STG_E_OLDFORMAT
;;
;; MessageText:
;;
;;  The compound file %1 was produced with an incompatible version of storage.
;;
STG_E_OLDFORMAT equ _HRESULT_TYPEDEF_(0x80030104)

;;
;; MessageId: STG_E_OLDDLL
;;
;; MessageText:
;;
;;  The compound file %1 was produced with a newer version of storage.
;;
STG_E_OLDDLL equ _HRESULT_TYPEDEF_(0x80030105)

;;
;; MessageId: STG_E_SHAREREQUIRED
;;
;; MessageText:
;;
;;  Share.exe or equivalent is required for operation.
;;
STG_E_SHAREREQUIRED equ _HRESULT_TYPEDEF_(0x80030106)

;;
;; MessageId: STG_E_NOTFILEBASEDSTORAGE
;;
;; MessageText:
;;
;;  Illegal operation called on non-file based storage.
;;
STG_E_NOTFILEBASEDSTORAGE equ _HRESULT_TYPEDEF_(0x80030107)

;;
;; MessageId: STG_E_EXTANTMARSHALLINGS
;;
;; MessageText:
;;
;;  Illegal operation called on object with extant marshallings.
;;
STG_E_EXTANTMARSHALLINGS equ _HRESULT_TYPEDEF_(0x80030108)

;;
;; MessageId: STG_E_DOCFILECORRUPT
;;
;; MessageText:
;;
;;  The docfile has been corrupted.
;;
STG_E_DOCFILECORRUPT equ _HRESULT_TYPEDEF_(0x80030109)

;;
;; MessageId: STG_E_BADBASEADDRESS
;;
;; MessageText:
;;
;;  OLE32.DLL has been loaded at the wrong address.
;;
STG_E_BADBASEADDRESS equ _HRESULT_TYPEDEF_(0x80030110)

;;
;; MessageId: STG_E_INCOMPLETE
;;
;; MessageText:
;;
;;  The file download was aborted abnormally.  The file is incomplete.
;;
STG_E_INCOMPLETE equ _HRESULT_TYPEDEF_(0x80030201)

;;
;; MessageId: STG_E_TERMINATED
;;
;; MessageText:
;;
;;  The file download has been terminated.
;;
STG_E_TERMINATED equ _HRESULT_TYPEDEF_(0x80030202)

;;
;; MessageId: STG_S_CONVERTED
;;
;; MessageText:
;;
;;  The underlying file was converted to compound file format.
;;
STG_S_CONVERTED equ _HRESULT_TYPEDEF_(0x00030200)

;;
;; MessageId: STG_S_BLOCK
;;
;; MessageText:
;;
;;  The storage operation should block until more data is available.
;;
STG_S_BLOCK equ _HRESULT_TYPEDEF_(0x00030201)

;;
;; MessageId: STG_S_RETRYNOW
;;
;; MessageText:
;;
;;  The storage operation should retry immediately.
;;
STG_S_RETRYNOW equ _HRESULT_TYPEDEF_(0x00030202)

;;
;; MessageId: STG_S_MONITORING
;;
;; MessageText:
;;
;;  The notified event sink will not influence the storage operation.
;;
STG_S_MONITORING equ _HRESULT_TYPEDEF_(0x00030203)

;;
;; MessageId: STG_S_MULTIPLEOPENS
;;
;; MessageText:
;;
;;  Multiple opens prevent consolidated. (commit succeeded).
;;
STG_S_MULTIPLEOPENS equ _HRESULT_TYPEDEF_(0x00030204)

;;
;; MessageId: STG_S_CONSOLIDATIONFAILED
;;
;; MessageText:
;;
;;  Consolidation of the storage file failed. (commit succeeded).
;;
STG_S_CONSOLIDATIONFAILED equ _HRESULT_TYPEDEF_(0x00030205)

;;
;; MessageId: STG_S_CANNOTCONSOLIDATE
;;
;; MessageText:
;;
;;  Consolidation of the storage file is inappropriate. (commit succeeded).
;;
STG_S_CANNOTCONSOLIDATE equ _HRESULT_TYPEDEF_(0x00030206)

;; ******************
;; FACILITY_RPC
;; ******************
;;
;; Codes 0x0-0x11 are propagated from 16 bit OLE.
;;
;;
;; MessageId: RPC_E_CALL_REJECTED
;;
;; MessageText:
;;
;;  Call was rejected by callee.
;;
RPC_E_CALL_REJECTED equ _HRESULT_TYPEDEF_(0x80010001)

;;
;; MessageId: RPC_E_CALL_CANCELED
;;
;; MessageText:
;;
;;  Call was canceled by the message filter.
;;
RPC_E_CALL_CANCELED equ _HRESULT_TYPEDEF_(0x80010002)

;;
;; MessageId: RPC_E_CANTPOST_INSENDCALL
;;
;; MessageText:
;;
;;  The caller is dispatching an intertask SendMessage call and
;;  cannot call out via PostMessage.
;;
RPC_E_CANTPOST_INSENDCALL equ _HRESULT_TYPEDEF_(0x80010003)

;;
;; MessageId: RPC_E_CANTCALLOUT_INASYNCCALL
;;
;; MessageText:
;;
;;  The caller is dispatching an asynchronous call and cannot
;;  make an outgoing call on behalf of this call.
;;
RPC_E_CANTCALLOUT_INASYNCCALL equ _HRESULT_TYPEDEF_(0x80010004)

;;
;; MessageId: RPC_E_CANTCALLOUT_INEXTERNALCALL
;;
;; MessageText:
;;
;;  It is illegal to call out while inside message filter.
;;
RPC_E_CANTCALLOUT_INEXTERNALCALL equ _HRESULT_TYPEDEF_(0x80010005)

;;
;; MessageId: RPC_E_CONNECTION_TERMINATED
;;
;; MessageText:
;;
;;  The connection terminated or is in a bogus state
;;  and cannot be used any more. Other connections
;;  are still valid.
;;
RPC_E_CONNECTION_TERMINATED equ _HRESULT_TYPEDEF_(0x80010006)

;;
;; MessageId: RPC_E_SERVER_DIED
;;
;; MessageText:
;;
;;  The callee (server [not server application]) is not available
;;  and disappeared; all connections are invalid.  The call may
;;  have executed.
;;
RPC_E_SERVER_DIED equ _HRESULT_TYPEDEF_(0x80010007)

;;
;; MessageId: RPC_E_CLIENT_DIED
;;
;; MessageText:
;;
;;  The caller (client) disappeared while the callee (server) was
;;  processing a call.
;;
RPC_E_CLIENT_DIED equ _HRESULT_TYPEDEF_(0x80010008)

;;
;; MessageId: RPC_E_INVALID_DATAPACKET
;;
;; MessageText:
;;
;;  The data packet with the marshalled parameter data is incorrect.
;;
RPC_E_INVALID_DATAPACKET equ _HRESULT_TYPEDEF_(0x80010009)

;;
;; MessageId: RPC_E_CANTTRANSMIT_CALL
;;
;; MessageText:
;;
;;  The call was not transmitted properly; the message queue
;;  was full and was not emptied after yielding.
;;
RPC_E_CANTTRANSMIT_CALL equ _HRESULT_TYPEDEF_(0x8001000A)

;;
;; MessageId: RPC_E_CLIENT_CANTMARSHAL_DATA
;;
;; MessageText:
;;
;;  The client (caller) cannot marshall the parameter data - low memory, etc.
;;
RPC_E_CLIENT_CANTMARSHAL_DATA equ _HRESULT_TYPEDEF_(0x8001000B)

;;
;; MessageId: RPC_E_CLIENT_CANTUNMARSHAL_DATA
;;
;; MessageText:
;;
;;  The client (caller) cannot unmarshall the return data - low memory, etc.
;;
RPC_E_CLIENT_CANTUNMARSHAL_DATA equ _HRESULT_TYPEDEF_(0x8001000C)

;;
;; MessageId: RPC_E_SERVER_CANTMARSHAL_DATA
;;
;; MessageText:
;;
;;  The server (callee) cannot marshall the return data - low memory, etc.
;;
RPC_E_SERVER_CANTMARSHAL_DATA equ _HRESULT_TYPEDEF_(0x8001000D)

;;
;; MessageId: RPC_E_SERVER_CANTUNMARSHAL_DATA
;;
;; MessageText:
;;
;;  The server (callee) cannot unmarshall the parameter data - low memory, etc.
;;
RPC_E_SERVER_CANTUNMARSHAL_DATA equ _HRESULT_TYPEDEF_(0x8001000E)

;;
;; MessageId: RPC_E_INVALID_DATA
;;
;; MessageText:
;;
;;  Received data is invalid; could be server or client data.
;;
RPC_E_INVALID_DATA equ _HRESULT_TYPEDEF_(0x8001000F)

;;
;; MessageId: RPC_E_INVALID_PARAMETER
;;
;; MessageText:
;;
;;  A particular parameter is invalid and cannot be (un)marshalled.
;;
RPC_E_INVALID_PARAMETER equ _HRESULT_TYPEDEF_(0x80010010)

;;
;; MessageId: RPC_E_CANTCALLOUT_AGAIN
;;
;; MessageText:
;;
;;  There is no second outgoing call on same channel in DDE conversation.
;;
RPC_E_CANTCALLOUT_AGAIN equ _HRESULT_TYPEDEF_(0x80010011)

;;
;; MessageId: RPC_E_SERVER_DIED_DNE
;;
;; MessageText:
;;
;;  The callee (server [not server application]) is not available
;;  and disappeared; all connections are invalid.  The call did not execute.
;;
RPC_E_SERVER_DIED_DNE equ _HRESULT_TYPEDEF_(0x80010012)

;;
;; MessageId: RPC_E_SYS_CALL_FAILED
;;
;; MessageText:
;;
;;  System call failed.
;;
RPC_E_SYS_CALL_FAILED equ _HRESULT_TYPEDEF_(0x80010100)

;;
;; MessageId: RPC_E_OUT_OF_RESOURCES
;;
;; MessageText:
;;
;;  Could not allocate some required resource (memory, events, ...)
;;
RPC_E_OUT_OF_RESOURCES equ _HRESULT_TYPEDEF_(0x80010101)

;;
;; MessageId: RPC_E_ATTEMPTED_MULTITHREAD
;;
;; MessageText:
;;
;;  Attempted to make calls on more than one thread in single threaded mode.
;;
RPC_E_ATTEMPTED_MULTITHREAD equ _HRESULT_TYPEDEF_(0x80010102)

;;
;; MessageId: RPC_E_NOT_REGISTERED
;;
;; MessageText:
;;
;;  The requested interface is not registered on the server object.
;;
RPC_E_NOT_REGISTERED equ _HRESULT_TYPEDEF_(0x80010103)

;;
;; MessageId: RPC_E_FAULT
;;
;; MessageText:
;;
;;  RPC could not call the server or could not return the results of calling the server.
;;
RPC_E_FAULT equ _HRESULT_TYPEDEF_(0x80010104)

;;
;; MessageId: RPC_E_SERVERFAULT
;;
;; MessageText:
;;
;;  The server threw an exception.
;;
RPC_E_SERVERFAULT equ _HRESULT_TYPEDEF_(0x80010105)

;;
;; MessageId: RPC_E_CHANGED_MODE
;;
;; MessageText:
;;
;;  Cannot change thread mode after it is set.
;;
RPC_E_CHANGED_MODE equ _HRESULT_TYPEDEF_(0x80010106)

;;
;; MessageId: RPC_E_INVALIDMETHOD
;;
;; MessageText:
;;
;;  The method called does not exist on the server.
;;
RPC_E_INVALIDMETHOD equ _HRESULT_TYPEDEF_(0x80010107)

;;
;; MessageId: RPC_E_DISCONNECTED
;;
;; MessageText:
;;
;;  The object invoked has disconnected from its clients.
;;
RPC_E_DISCONNECTED equ _HRESULT_TYPEDEF_(0x80010108)

;;
;; MessageId: RPC_E_RETRY
;;
;; MessageText:
;;
;;  The object invoked chose not to process the call now.  Try again later.
;;
RPC_E_RETRY equ _HRESULT_TYPEDEF_(0x80010109)

;;
;; MessageId: RPC_E_SERVERCALL_RETRYLATER
;;
;; MessageText:
;;
;;  The message filter indicated that the application is busy.
;;
RPC_E_SERVERCALL_RETRYLATER equ _HRESULT_TYPEDEF_(0x8001010A)

;;
;; MessageId: RPC_E_SERVERCALL_REJECTED
;;
;; MessageText:
;;
;;  The message filter rejected the call.
;;
RPC_E_SERVERCALL_REJECTED equ _HRESULT_TYPEDEF_(0x8001010B)

;;
;; MessageId: RPC_E_INVALID_CALLDATA
;;
;; MessageText:
;;
;;  A call control interfaces was called with invalid data.
;;
RPC_E_INVALID_CALLDATA equ _HRESULT_TYPEDEF_(0x8001010C)

;;
;; MessageId: RPC_E_CANTCALLOUT_ININPUTSYNCCALL
;;
;; MessageText:
;;
;;  An outgoing call cannot be made since the application is dispatching an input-synchronous call.
;;
RPC_E_CANTCALLOUT_ININPUTSYNCCALL equ _HRESULT_TYPEDEF_(0x8001010D)

;;
;; MessageId: RPC_E_WRONG_THREAD
;;
;; MessageText:
;;
;;  The application called an interface that was marshalled for a different thread.
;;
RPC_E_WRONG_THREAD equ _HRESULT_TYPEDEF_(0x8001010E)

;;
;; MessageId: RPC_E_THREAD_NOT_INIT
;;
;; MessageText:
;;
;;  CoInitialize has not been called on the current thread.
;;
RPC_E_THREAD_NOT_INIT equ _HRESULT_TYPEDEF_(0x8001010F)

;;
;; MessageId: RPC_E_VERSION_MISMATCH
;;
;; MessageText:
;;
;;  The version of OLE on the client and server machines does not match.
;;
RPC_E_VERSION_MISMATCH equ _HRESULT_TYPEDEF_(0x80010110)

;;
;; MessageId: RPC_E_INVALID_HEADER
;;
;; MessageText:
;;
;;  OLE received a packet with an invalid header.
;;
RPC_E_INVALID_HEADER equ _HRESULT_TYPEDEF_(0x80010111)

;;
;; MessageId: RPC_E_INVALID_EXTENSION
;;
;; MessageText:
;;
;;  OLE received a packet with an invalid extension.
;;
RPC_E_INVALID_EXTENSION equ _HRESULT_TYPEDEF_(0x80010112)

;;
;; MessageId: RPC_E_INVALID_IPID
;;
;; MessageText:
;;
;;  The requested object or interface does not exist.
;;
RPC_E_INVALID_IPID equ _HRESULT_TYPEDEF_(0x80010113)

;;
;; MessageId: RPC_E_INVALID_OBJECT
;;
;; MessageText:
;;
;;  The requested object does not exist.
;;
RPC_E_INVALID_OBJECT equ _HRESULT_TYPEDEF_(0x80010114)

;;
;; MessageId: RPC_S_CALLPENDING
;;
;; MessageText:
;;
;;  OLE has sent a request and is waiting for a reply.
;;
RPC_S_CALLPENDING equ _HRESULT_TYPEDEF_(0x80010115)

;;
;; MessageId: RPC_S_WAITONTIMER
;;
;; MessageText:
;;
;;  OLE is waiting before retrying a request.
;;
RPC_S_WAITONTIMER equ _HRESULT_TYPEDEF_(0x80010116)

;;
;; MessageId: RPC_E_CALL_COMPLETE
;;
;; MessageText:
;;
;;  Call context cannot be accessed after call completed.
;;
RPC_E_CALL_COMPLETE equ _HRESULT_TYPEDEF_(0x80010117)

;;
;; MessageId: RPC_E_UNSECURE_CALL
;;
;; MessageText:
;;
;;  Impersonate on unsecure calls is not supported.
;;
RPC_E_UNSECURE_CALL equ _HRESULT_TYPEDEF_(0x80010118)

;;
;; MessageId: RPC_E_TOO_LATE
;;
;; MessageText:
;;
;;  Security must be initialized before any interfaces are marshalled or
;;  unmarshalled.  It cannot be changed once initialized.
;;
RPC_E_TOO_LATE equ _HRESULT_TYPEDEF_(0x80010119)

;;
;; MessageId: RPC_E_NO_GOOD_SECURITY_PACKAGES
;;
;; MessageText:
;;
;;  No security packages are installed on this machine or the user is not logged
;;  on or there are no compatible security packages between the client and server.
;;
RPC_E_NO_GOOD_SECURITY_PACKAGES equ _HRESULT_TYPEDEF_(0x8001011A)

;;
;; MessageId: RPC_E_ACCESS_DENIED
;;
;; MessageText:
;;
;;  Access is denied.
;;
RPC_E_ACCESS_DENIED equ _HRESULT_TYPEDEF_(0x8001011B)

;;
;; MessageId: RPC_E_REMOTE_DISABLED
;;
;; MessageText:
;;
;;  Remote calls are not allowed for this process.
;;
RPC_E_REMOTE_DISABLED equ _HRESULT_TYPEDEF_(0x8001011C)

;;
;; MessageId: RPC_E_INVALID_OBJREF
;;
;; MessageText:
;;
;;  The marshaled interface data packet (OBJREF) has an invalid or unknown format.
;;
RPC_E_INVALID_OBJREF equ _HRESULT_TYPEDEF_(0x8001011D)

;;
;; MessageId: RPC_E_NO_CONTEXT
;;
;; MessageText:
;;
;;  No context is associated with this call.  This happens for some custom
;;  marshalled calls and on the client side of the call.
;;
RPC_E_NO_CONTEXT equ _HRESULT_TYPEDEF_(0x8001011E)

;;
;; MessageId: RPC_E_TIMEOUT
;;
;; MessageText:
;;
;;  This operation returned because the timeout period expired.
;;
RPC_E_TIMEOUT equ _HRESULT_TYPEDEF_(0x8001011F)

;;
;; MessageId: RPC_E_NO_SYNC
;;
;; MessageText:
;;
;;  There are no synchronize objects to wait on.
;;
RPC_E_NO_SYNC equ _HRESULT_TYPEDEF_(0x80010120)

;;
;; MessageId: RPC_E_UNEXPECTED
;;
;; MessageText:
;;
;;  An internal error occurred.
;;
RPC_E_UNEXPECTED equ _HRESULT_TYPEDEF_(0x8001FFFF)


 ;;;;;;;;;;;;;;;;;
 ;;
 ;;  FACILITY_SSPI
 ;;
 ;;;;;;;;;;;;;;;;;

;;
;; MessageId: NTE_BAD_UID
;;
;; MessageText:
;;
;;  Bad UID.
;;
NTE_BAD_UID equ _HRESULT_TYPEDEF_(0x80090001)

;;
;; MessageId: NTE_BAD_HASH
;;
;; MessageText:
;;
;;  Bad Hash.
;;
NTE_BAD_HASH equ _HRESULT_TYPEDEF_(0x80090002)

;;
;; MessageId: NTE_BAD_KEY
;;
;; MessageText:
;;
;;  Bad Key.
;;
NTE_BAD_KEY equ _HRESULT_TYPEDEF_(0x80090003)

;;
;; MessageId: NTE_BAD_LEN
;;
;; MessageText:
;;
;;  Bad Length.
;;
NTE_BAD_LEN equ _HRESULT_TYPEDEF_(0x80090004)

;;
;; MessageId: NTE_BAD_DATA
;;
;; MessageText:
;;
;;  Bad Data.
;;
NTE_BAD_DATA equ _HRESULT_TYPEDEF_(0x80090005)

;;
;; MessageId: NTE_BAD_SIGNATURE
;;
;; MessageText:
;;
;;  Invalid Signature.
;;
NTE_BAD_SIGNATURE equ _HRESULT_TYPEDEF_(0x80090006)

;;
;; MessageId: NTE_BAD_VER
;;
;; MessageText:
;;
;;  Bad Version of provider.
;;
NTE_BAD_VER equ _HRESULT_TYPEDEF_(0x80090007)

;;
;; MessageId: NTE_BAD_ALGID
;;
;; MessageText:
;;
;;  Invalid algorithm specified.
;;
NTE_BAD_ALGID equ _HRESULT_TYPEDEF_(0x80090008)

;;
;; MessageId: NTE_BAD_FLAGS
;;
;; MessageText:
;;
;;  Invalid flags specified.
;;
NTE_BAD_FLAGS equ _HRESULT_TYPEDEF_(0x80090009)

;;
;; MessageId: NTE_BAD_TYPE
;;
;; MessageText:
;;
;;  Invalid type specified.
;;
NTE_BAD_TYPE equ _HRESULT_TYPEDEF_(0x8009000A)

;;
;; MessageId: NTE_BAD_KEY_STATE
;;
;; MessageText:
;;
;;  Key not valid for use in specified state.
;;
NTE_BAD_KEY_STATE equ _HRESULT_TYPEDEF_(0x8009000B)

;;
;; MessageId: NTE_BAD_HASH_STATE
;;
;; MessageText:
;;
;;  Hash not valid for use in specified state.
;;
NTE_BAD_HASH_STATE equ _HRESULT_TYPEDEF_(0x8009000C)

;;
;; MessageId: NTE_NO_KEY
;;
;; MessageText:
;;
;;  Key does not exist.
;;
NTE_NO_KEY equ _HRESULT_TYPEDEF_(0x8009000D)

;;
;; MessageId: NTE_NO_MEMORY
;;
;; MessageText:
;;
;;  Insufficient memory available for the operation.
;;
NTE_NO_MEMORY equ _HRESULT_TYPEDEF_(0x8009000E)

;;
;; MessageId: NTE_EXISTS
;;
;; MessageText:
;;
;;  Object already exists.
;;
NTE_EXISTS equ _HRESULT_TYPEDEF_(0x8009000F)

;;
;; MessageId: NTE_PERM
;;
;; MessageText:
;;
;;  Access denied.
;;
NTE_PERM equ _HRESULT_TYPEDEF_(0x80090010)

;;
;; MessageId: NTE_NOT_FOUND
;;
;; MessageText:
;;
;;  Object was not found.
;;
NTE_NOT_FOUND equ _HRESULT_TYPEDEF_(0x80090011)

;;
;; MessageId: NTE_DOUBLE_ENCRYPT
;;
;; MessageText:
;;
;;  Data already encrypted.
;;
NTE_DOUBLE_ENCRYPT equ _HRESULT_TYPEDEF_(0x80090012)

;;
;; MessageId: NTE_BAD_PROVIDER
;;
;; MessageText:
;;
;;  Invalid provider specified.
;;
NTE_BAD_PROVIDER equ _HRESULT_TYPEDEF_(0x80090013)

;;
;; MessageId: NTE_BAD_PROV_TYPE
;;
;; MessageText:
;;
;;  Invalid provider type specified.
;;
NTE_BAD_PROV_TYPE equ _HRESULT_TYPEDEF_(0x80090014)

;;
;; MessageId: NTE_BAD_PUBLIC_KEY
;;
;; MessageText:
;;
;;  Provider's public key is invalid.
;;
NTE_BAD_PUBLIC_KEY equ _HRESULT_TYPEDEF_(0x80090015)

;;
;; MessageId: NTE_BAD_KEYSET
;;
;; MessageText:
;;
;;  Keyset does not exist
;;
NTE_BAD_KEYSET equ _HRESULT_TYPEDEF_(0x80090016)

;;
;; MessageId: NTE_PROV_TYPE_NOT_DEF
;;
;; MessageText:
;;
;;  Provider type not defined.
;;
NTE_PROV_TYPE_NOT_DEF equ _HRESULT_TYPEDEF_(0x80090017)

;;
;; MessageId: NTE_PROV_TYPE_ENTRY_BAD
;;
;; MessageText:
;;
;;  Provider type as registered is invalid.
;;
NTE_PROV_TYPE_ENTRY_BAD equ _HRESULT_TYPEDEF_(0x80090018)

;;
;; MessageId: NTE_KEYSET_NOT_DEF
;;
;; MessageText:
;;
;;  The keyset is not defined.
;;
NTE_KEYSET_NOT_DEF equ _HRESULT_TYPEDEF_(0x80090019)

;;
;; MessageId: NTE_KEYSET_ENTRY_BAD
;;
;; MessageText:
;;
;;  Keyset as registered is invalid.
;;
NTE_KEYSET_ENTRY_BAD equ _HRESULT_TYPEDEF_(0x8009001A)

;;
;; MessageId: NTE_PROV_TYPE_NO_MATCH
;;
;; MessageText:
;;
;;  Provider type does not match registered value.
;;
NTE_PROV_TYPE_NO_MATCH equ _HRESULT_TYPEDEF_(0x8009001B)

;;
;; MessageId: NTE_SIGNATURE_FILE_BAD
;;
;; MessageText:
;;
;;  The digital signature file is corrupt.
;;
NTE_SIGNATURE_FILE_BAD equ _HRESULT_TYPEDEF_(0x8009001C)

;;
;; MessageId: NTE_PROVIDER_DLL_FAIL
;;
;; MessageText:
;;
;;  Provider DLL failed to initialize correctly.
;;
NTE_PROVIDER_DLL_FAIL equ _HRESULT_TYPEDEF_(0x8009001D)

;;
;; MessageId: NTE_PROV_DLL_NOT_FOUND
;;
;; MessageText:
;;
;;  Provider DLL could not be found.
;;
NTE_PROV_DLL_NOT_FOUND equ _HRESULT_TYPEDEF_(0x8009001E)

;;
;; MessageId: NTE_BAD_KEYSET_PARAM
;;
;; MessageText:
;;
;;  The Keyset parameter is invalid.
;;
NTE_BAD_KEYSET_PARAM equ _HRESULT_TYPEDEF_(0x8009001F)

;;
;; MessageId: NTE_FAIL
;;
;; MessageText:
;;
;;  An internal error occurred.
;;
NTE_FAIL equ _HRESULT_TYPEDEF_(0x80090020)

;;
;; MessageId: NTE_SYS_ERR
;;
;; MessageText:
;;
;;  A base error occurred.
;;
NTE_SYS_ERR equ _HRESULT_TYPEDEF_(0x80090021)

;;
;; MessageId: CRYPT_E_MSG_ERROR
;;
;; MessageText:
;;
;;  An error was encountered doing a cryptographic message operation.
;;
CRYPT_E_MSG_ERROR equ _HRESULT_TYPEDEF_(0x80091001)

;;
;; MessageId: CRYPT_E_UNKNOWN_ALGO
;;
;; MessageText:
;;
;;  The cryptographic algorithm is unknown.
;;
CRYPT_E_UNKNOWN_ALGO equ _HRESULT_TYPEDEF_(0x80091002)

;;
;; MessageId: CRYPT_E_OID_FORMAT
;;
;; MessageText:
;;
;;  The object identifier is badly formatted.
;;
CRYPT_E_OID_FORMAT equ _HRESULT_TYPEDEF_(0x80091003)

;;
;; MessageId: CRYPT_E_INVALID_MSG_TYPE
;;
;; MessageText:
;;
;;  The message type is invalid.
;;
CRYPT_E_INVALID_MSG_TYPE equ _HRESULT_TYPEDEF_(0x80091004)

;;
;; MessageId: CRYPT_E_UNEXPECTED_ENCODING
;;
;; MessageText:
;;
;;  The message is not encoded as expected.
;;
CRYPT_E_UNEXPECTED_ENCODING equ _HRESULT_TYPEDEF_(0x80091005)

;;
;; MessageId: CRYPT_E_AUTH_ATTR_MISSING
;;
;; MessageText:
;;
;;  The message does not contain an expected authenticated attribute.
;;
CRYPT_E_AUTH_ATTR_MISSING equ _HRESULT_TYPEDEF_(0x80091006)

;;
;; MessageId: CRYPT_E_HASH_VALUE
;;
;; MessageText:
;;
;;  The hash value is not correct.
;;
CRYPT_E_HASH_VALUE equ _HRESULT_TYPEDEF_(0x80091007)

;;
;; MessageId: CRYPT_E_INVALID_INDEX
;;
;; MessageText:
;;
;;  The index value is not valid.
;;
CRYPT_E_INVALID_INDEX equ _HRESULT_TYPEDEF_(0x80091008)

;;
;; MessageId: CRYPT_E_ALREADY_DECRYPTED
;;
;; MessageText:
;;
;;  The message content has already been decrypted.
;;
CRYPT_E_ALREADY_DECRYPTED equ _HRESULT_TYPEDEF_(0x80091009)

;;
;; MessageId: CRYPT_E_NOT_DECRYPTED
;;
;; MessageText:
;;
;;  The message content has not been decrypted yet.
;;
CRYPT_E_NOT_DECRYPTED equ _HRESULT_TYPEDEF_(0x8009100A)

;;
;; MessageId: CRYPT_E_RECIPIENT_NOT_FOUND
;;
;; MessageText:
;;
;;  The enveloped-data message does not contain the specified recipient.
;;
CRYPT_E_RECIPIENT_NOT_FOUND equ _HRESULT_TYPEDEF_(0x8009100B)

;;
;; MessageId: CRYPT_E_CONTROL_TYPE
;;
;; MessageText:
;;
;;  The control type is not valid.
;;
CRYPT_E_CONTROL_TYPE equ _HRESULT_TYPEDEF_(0x8009100C)

;;
;; MessageId: CRYPT_E_ISSUER_SERIALNUMBER
;;
;; MessageText:
;;
;;  The issuer and/or serial number are/is not valid.
;;
CRYPT_E_ISSUER_SERIALNUMBER equ _HRESULT_TYPEDEF_(0x8009100D)

;;
;; MessageId: CRYPT_E_SIGNER_NOT_FOUND
;;
;; MessageText:
;;
;;  The original signer is not found.
;;
CRYPT_E_SIGNER_NOT_FOUND equ _HRESULT_TYPEDEF_(0x8009100E)

;;
;; MessageId: CRYPT_E_ATTRIBUTES_MISSING
;;
;; MessageText:
;;
;;  The message does not contain the requested attributes.
;;
CRYPT_E_ATTRIBUTES_MISSING equ _HRESULT_TYPEDEF_(0x8009100F)

;;
;; MessageId: CRYPT_E_STREAM_MSG_NOT_READY
;;
;; MessageText:
;;
;;  The steamed message is note yet able to return the requested data.
;;
CRYPT_E_STREAM_MSG_NOT_READY equ _HRESULT_TYPEDEF_(0x80091010)

;;
;; MessageId: CRYPT_E_STREAM_INSUFFICIENT_DATA
;;
;; MessageText:
;;
;;  The streamed message needs more data before the decode can complete.
;;
CRYPT_E_STREAM_INSUFFICIENT_DATA equ _HRESULT_TYPEDEF_(0x80091011)

;;
;; MessageId: CRYPT_E_BAD_LEN
;;
;; MessageText:
;;
;;  The length specified for the output data was insufficient.
;;
CRYPT_E_BAD_LEN equ _HRESULT_TYPEDEF_(0x80092001)

;;
;; MessageId: CRYPT_E_BAD_ENCODE
;;
;; MessageText:
;;
;;  An error was encountered while encoding or decoding.
;;
CRYPT_E_BAD_ENCODE equ _HRESULT_TYPEDEF_(0x80092002)

;;
;; MessageId: CRYPT_E_FILE_ERROR
;;
;; MessageText:
;;
;;  An error occurred while reading or writing to the file
;;
CRYPT_E_FILE_ERROR equ _HRESULT_TYPEDEF_(0x80092003)

;;
;; MessageId: CRYPT_E_NOT_FOUND
;;
;; MessageText:
;;
;;  The object or property wasn't found
;;
CRYPT_E_NOT_FOUND equ _HRESULT_TYPEDEF_(0x80092004)

;;
;; MessageId: CRYPT_E_EXISTS
;;
;; MessageText:
;;
;;  The object or property already exists
;;
CRYPT_E_EXISTS equ _HRESULT_TYPEDEF_(0x80092005)

;;
;; MessageId: CRYPT_E_NO_PROVIDER
;;
;; MessageText:
;;
;;  No provider was specified for the store or object
;;
CRYPT_E_NO_PROVIDER equ _HRESULT_TYPEDEF_(0x80092006)

;;
;; MessageId: CRYPT_E_SELF_SIGNED
;;
;; MessageText:
;;
;;  The specified certificate is self signed.
;;
CRYPT_E_SELF_SIGNED equ _HRESULT_TYPEDEF_(0x80092007)

;;
;; MessageId: CRYPT_E_DELETED_PREV
;;
;; MessageText:
;;
;;  The previous certificate or CRL context was deleted.
;;
CRYPT_E_DELETED_PREV equ _HRESULT_TYPEDEF_(0x80092008)

;;
;; MessageId: CRYPT_E_NO_MATCH
;;
;; MessageText:
;;
;;  No match when trying to find the object.
;;
CRYPT_E_NO_MATCH equ _HRESULT_TYPEDEF_(0x80092009)

;;
;; MessageId: CRYPT_E_UNEXPECTED_MSG_TYPE
;;
;; MessageText:
;;
;;  The type of the cryptographic message being decoded is different than what was expected.
;;
CRYPT_E_UNEXPECTED_MSG_TYPE equ _HRESULT_TYPEDEF_(0x8009200A)

;;
;; MessageId: CRYPT_E_NO_KEY_PROPERTY
;;
;; MessageText:
;;
;;  The certificate doesn't have a private key property
;;
CRYPT_E_NO_KEY_PROPERTY equ _HRESULT_TYPEDEF_(0x8009200B)

;;
;; MessageId: CRYPT_E_NO_DECRYPT_CERT
;;
;; MessageText:
;;
;;  No certificate was found having a private key property to use for decrypting.
;;
CRYPT_E_NO_DECRYPT_CERT equ _HRESULT_TYPEDEF_(0x8009200C)

;;
;; MessageId: CRYPT_E_BAD_MSG
;;
;; MessageText:
;;
;;  Either, not a cryptographic message or incorrectly formatted.
;;
CRYPT_E_BAD_MSG equ _HRESULT_TYPEDEF_(0x8009200D)

;;
;; MessageId: CRYPT_E_NO_SIGNER
;;
;; MessageText:
;;
;;  The signed message doesn't have a signer for the specified signer index
;;
CRYPT_E_NO_SIGNER equ _HRESULT_TYPEDEF_(0x8009200E)

;;
;; MessageId: CRYPT_E_PENDING_CLOSE
;;
;; MessageText:
;;
;;  Final closure is pending until additional frees or closes.
;;
CRYPT_E_PENDING_CLOSE equ _HRESULT_TYPEDEF_(0x8009200F)

;;
;; MessageId: CRYPT_E_REVOKED
;;
;; MessageText:
;;
;;  The certificate or signature has been revoked
;;
CRYPT_E_REVOKED equ _HRESULT_TYPEDEF_(0x80092010)

;;
;; MessageId: CRYPT_E_NO_REVOCATION_DLL
;;
;; MessageText:
;;
;;  No Dll or exported function was found to verify revocation.
;;
CRYPT_E_NO_REVOCATION_DLL equ _HRESULT_TYPEDEF_(0x80092011)

;;
;; MessageId: CRYPT_E_NO_REVOCATION_CHECK
;;
;; MessageText:
;;
;;  The called function wasn't able to do a revocation check on the certificate or signature.
;;
CRYPT_E_NO_REVOCATION_CHECK equ _HRESULT_TYPEDEF_(0x80092012)

;;
;; MessageId: CRYPT_E_REVOCATION_OFFLINE
;;
;; MessageText:
;;
;;  Since the revocation server was offline, the called function wasn't able to complete the revocation check.
;;
CRYPT_E_REVOCATION_OFFLINE equ _HRESULT_TYPEDEF_(0x80092013)

;;
;; MessageId: CRYPT_E_NOT_IN_REVOCATION_DATABASE
;;
;; MessageText:
;;
;;  The certificate or signature to be checked was not found in the revocation servers database.
;;
CRYPT_E_NOT_IN_REVOCATION_DATABASE equ _HRESULT_TYPEDEF_(0x80092014)

;;
;; MessageId: CRYPT_E_INVALID_NUMERIC_STRING
;;
;; MessageText:
;;
;;  The string contains a non-numeric character.
;;
CRYPT_E_INVALID_NUMERIC_STRING equ _HRESULT_TYPEDEF_(0x80092020)

;;
;; MessageId: CRYPT_E_INVALID_PRINTABLE_STRING
;;
;; MessageText:
;;
;;  The string contains a non-printable character.
;;
CRYPT_E_INVALID_PRINTABLE_STRING equ _HRESULT_TYPEDEF_(0x80092021)

;;
;; MessageId: CRYPT_E_INVALID_IA5_STRING
;;
;; MessageText:
;;
;;  The string contains a character not in the 7 bit ASCII character set.
;;
CRYPT_E_INVALID_IA5_STRING equ _HRESULT_TYPEDEF_(0x80092022)

;;
;; MessageId: CRYPT_E_INVALID_X500_STRING
;;
;; MessageText:
;;
;;  The string contains an invalid X500 name attribute key, oid, value or delimiter.
;;
CRYPT_E_INVALID_X500_STRING equ _HRESULT_TYPEDEF_(0x80092023)

;;
;; MessageId: CRYPT_E_NOT_CHAR_STRING
;;
;; MessageText:
;;
;;  The dwValueType for the CERT_NAME_VALUE is not one of the character strings.  Most likely it is either a CERT_RDN_ENCODED_BLOB or CERT_TDN_OCTED_STRING.
;;
CRYPT_E_NOT_CHAR_STRING equ _HRESULT_TYPEDEF_(0x80092024)

;;
;; MessageId: CRYPT_E_FILERESIZED
;;
;; MessageText:
;;
;;  The Put operation can not continue.	 The file needs to be resized.	However, there is already a signature present.	A complete signing operation must be done.
;;
CRYPT_E_FILERESIZED equ _HRESULT_TYPEDEF_(0x80092025)

;;
;; MessageId: CRYPT_E_SECURITY_SETTINGS
;;
;; MessageText:
;;
;;  The cryptography operation has failed due to a local security option setting.
;;
CRYPT_E_SECURITY_SETTINGS equ _HRESULT_TYPEDEF_(0x80092026)

;;
;; MessageId: CRYPT_E_NO_VERIFY_USAGE_DLL
;;
;; MessageText:
;;
;;  No DLL or exported function was found to verify subject usage.
;;
CRYPT_E_NO_VERIFY_USAGE_DLL equ _HRESULT_TYPEDEF_(0x80092027)

;;
;; MessageId: CRYPT_E_NO_VERIFY_USAGE_CHECK
;;
;; MessageText:
;;
;;  The called function wasn't able to do a usage check on the subject.
;;
CRYPT_E_NO_VERIFY_USAGE_CHECK equ _HRESULT_TYPEDEF_(0x80092028)

;;
;; MessageId: CRYPT_E_VERIFY_USAGE_OFFLINE
;;
;; MessageText:
;;
;;  Since the server was offline, the called function wasn't able to complete the usage check.
;;
CRYPT_E_VERIFY_USAGE_OFFLINE equ _HRESULT_TYPEDEF_(0x80092029)

;;
;; MessageId: CRYPT_E_NOT_IN_CTL
;;
;; MessageText:
;;
;;  The subject was not found in a Certificate Trust List (CTL).
;;
CRYPT_E_NOT_IN_CTL equ _HRESULT_TYPEDEF_(0x8009202A)

;;
;; MessageId: CRYPT_E_NO_TRUSTED_SIGNER
;;
;; MessageText:
;;
;;  No trusted signer was found to verify the signature of the message or trust list.
;;
CRYPT_E_NO_TRUSTED_SIGNER equ _HRESULT_TYPEDEF_(0x8009202B)

;;
;; MessageId: CRYPT_E_OSS_ERROR
;;
;; MessageText:
;;
;;  OSS Certificate encode/decode error code base
;;
;;  See asn1code.h for a definition of the OSS runtime errors. The OSS
;;  error values are offset by CRYPT_E_OSS_ERROR.
;;
CRYPT_E_OSS_ERROR equ _HRESULT_TYPEDEF_(0x80093000)

;;
;; MessageId: CERTSRV_E_BAD_REQUESTSUBJECT
;;
;; MessageText:
;;
;;  The request subject name is invalid or too long.
;;
CERTSRV_E_BAD_REQUESTSUBJECT equ _HRESULT_TYPEDEF_(0x80094001)

;;
;; MessageId: CERTSRV_E_NO_REQUEST
;;
;; MessageText:
;;
;;  The request does not exist.
;;
CERTSRV_E_NO_REQUEST equ _HRESULT_TYPEDEF_(0x80094002)

;;
;; MessageId: CERTSRV_E_BAD_REQUESTSTATUS
;;
;; MessageText:
;;
;;  The request's current status does not allow this operation.
;;
CERTSRV_E_BAD_REQUESTSTATUS equ _HRESULT_TYPEDEF_(0x80094003)

;;
;; MessageId: CERTSRV_E_PROPERTY_EMPTY
;;
;; MessageText:
;;
;;  The requested property value is empty.
;;
CERTSRV_E_PROPERTY_EMPTY equ _HRESULT_TYPEDEF_(0x80094004)

;;
;; MessageId: CERTDB_E_JET_ERROR
;;
;; MessageText:
;;
;;  Jet error code base
;;
;;  See jet.h for a definition of the Jet runtime errors.
;;  Negative Jet error values are masked to three digits and offset by CERTDB_E_JET_ERROR.
;;
CERTDB_E_JET_ERROR equ _HRESULT_TYPEDEF_(0x80095000)

;;
;; MessageId: TRUST_E_SYSTEM_ERROR
;;
;; MessageText:
;;
;;  A system-level error occured while verifying trust.
;;
TRUST_E_SYSTEM_ERROR equ _HRESULT_TYPEDEF_(0x80096001)

;;
;; MessageId: TRUST_E_NO_SIGNER_CERT
;;
;; MessageText:
;;
;;  The certificate for the signer of the message is invalid or not found.
;;
TRUST_E_NO_SIGNER_CERT equ _HRESULT_TYPEDEF_(0x80096002)

;;
;; MessageId: TRUST_E_COUNTER_SIGNER
;;
;; MessageText:
;;
;;  One of the counter signers was invalid.
;;
TRUST_E_COUNTER_SIGNER equ _HRESULT_TYPEDEF_(0x80096003)

;;
;; MessageId: TRUST_E_CERT_SIGNATURE
;;
;; MessageText:
;;
;;  The signature of the certificate can not be verified.
;;
TRUST_E_CERT_SIGNATURE equ _HRESULT_TYPEDEF_(0x80096004)

;;
;; MessageId: TRUST_E_TIME_STAMP
;;
;; MessageText:
;;
;;  The time stamp signer and or certificate could not be verified or is malformed.
;;
TRUST_E_TIME_STAMP equ _HRESULT_TYPEDEF_(0x80096005)

;;
;; MessageId: TRUST_E_BAD_DIGEST
;;
;; MessageText:
;;
;;  The objects digest did not verify.
;;
TRUST_E_BAD_DIGEST equ _HRESULT_TYPEDEF_(0x80096010)

;;
;; MessageId: TRUST_E_BASIC_CONSTRAINTS
;;
;; MessageText:
;;
;;  The cerficates basic constraints are invalid or missing.
;;
TRUST_E_BASIC_CONSTRAINTS equ _HRESULT_TYPEDEF_(0x80096019)

;;
;; MessageId: TRUST_E_FINANCIAL_CRITERIA
;;
;; MessageText:
;;
;;  The certificate does not meet or contain the Authenticode financial extensions.
;;
TRUST_E_FINANCIAL_CRITERIA equ _HRESULT_TYPEDEF_(0x8009601E)

NTE_OP_OK	equ 0

;;
;; Note that additional FACILITY_SSPI errors are in issperr.h
;;
;; ******************
;; FACILITY_CERT
;; ******************
;;
;; MessageId: TRUST_E_PROVIDER_UNKNOWN
;;
;; MessageText:
;;
;;  The specified trust provider is not known on this system.
;;
TRUST_E_PROVIDER_UNKNOWN equ _HRESULT_TYPEDEF_(0x800B0001)

;;
;; MessageId: TRUST_E_ACTION_UNKNOWN
;;
;; MessageText:
;;
;;  The trust verification action specified is not supported by the specified trust provider.
;;
TRUST_E_ACTION_UNKNOWN equ _HRESULT_TYPEDEF_(0x800B0002)

;;
;; MessageId: TRUST_E_SUBJECT_FORM_UNKNOWN
;;
;; MessageText:
;;
;;  The form specified for the subject is not one supported or known by the specified trust provider.
;;
TRUST_E_SUBJECT_FORM_UNKNOWN equ _HRESULT_TYPEDEF_(0x800B0003)

;;
;; MessageId: TRUST_E_SUBJECT_NOT_TRUSTED
;;
;; MessageText:
;;
;;  The subject is not trusted for the specified action.
;;
TRUST_E_SUBJECT_NOT_TRUSTED equ _HRESULT_TYPEDEF_(0x800B0004)

;;
;; MessageId: DIGSIG_E_ENCODE
;;
;; MessageText:
;;
;;  Error due to problem in ASN.1 encoding process.
;;
DIGSIG_E_ENCODE equ _HRESULT_TYPEDEF_(0x800B0005)

;;
;; MessageId: DIGSIG_E_DECODE
;;
;; MessageText:
;;
;;  Error due to problem in ASN.1 decoding process.
;;
DIGSIG_E_DECODE equ _HRESULT_TYPEDEF_(0x800B0006)

;;
;; MessageId: DIGSIG_E_EXTENSIBILITY
;;
;; MessageText:
;;
;;  Reading / writing Extensions where Attributes are appropriate, and visa versa.
;;
DIGSIG_E_EXTENSIBILITY equ _HRESULT_TYPEDEF_(0x800B0007)

;;
;; MessageId: DIGSIG_E_CRYPTO
;;
;; MessageText:
;;
;;  Unspecified cryptographic failure.
;;
DIGSIG_E_CRYPTO equ _HRESULT_TYPEDEF_(0x800B0008)

;;
;; MessageId: PERSIST_E_SIZEDEFINITE
;;
;; MessageText:
;;
;;  The size of the data could not be determined.
;;
PERSIST_E_SIZEDEFINITE equ _HRESULT_TYPEDEF_(0x800B0009)

;;
;; MessageId: PERSIST_E_SIZEINDEFINITE
;;
;; MessageText:
;;
;;  The size of the indefinite-sized data could not be determined.
;;
PERSIST_E_SIZEINDEFINITE equ _HRESULT_TYPEDEF_(0x800B000A)

;;
;; MessageId: PERSIST_E_NOTSELFSIZING
;;
;; MessageText:
;;
;;  This object does not read and write self-sizing data.
;;
PERSIST_E_NOTSELFSIZING equ _HRESULT_TYPEDEF_(0x800B000B)

;;
;; MessageId: TRUST_E_NOSIGNATURE
;;
;; MessageText:
;;
;;  No signature was present in the subject.
;;
TRUST_E_NOSIGNATURE equ _HRESULT_TYPEDEF_(0x800B0100)

;;
;; MessageId: CERT_E_EXPIRED
;;
;; MessageText:
;;
;;  A required certificate is not within its validity period.
;;
CERT_E_EXPIRED equ _HRESULT_TYPEDEF_(0x800B0101)

;;
;; MessageId: CERT_E_VALIDITYPERIODNESTING
;;
;; MessageText:
;;
;;  The validity periods of the certification chain do not nest correctly.
;;
CERT_E_VALIDITYPERIODNESTING equ _HRESULT_TYPEDEF_(0x800B0102)

;;
;; MessageId: CERT_E_ROLE
;;
;; MessageText:
;;
;;  A certificate that can only be used as an end-entity is being used as a CA or visa versa.
;;
CERT_E_ROLE equ _HRESULT_TYPEDEF_(0x800B0103)

;;
;; MessageId: CERT_E_PATHLENCONST
;;
;; MessageText:
;;
;;  A path length constraint in the certification chain has been violated.
;;
CERT_E_PATHLENCONST equ _HRESULT_TYPEDEF_(0x800B0104)

;;
;; MessageId: CERT_E_CRITICAL
;;
;; MessageText:
;;
;;  An extension of unknown type that is labeled 'critical' is present in a certificate.
;;
CERT_E_CRITICAL equ _HRESULT_TYPEDEF_(0x800B0105)

;;
;; MessageId: CERT_E_PURPOSE
;;
;; MessageText:
;;
;;  A certificate is being used for a purpose other than that for which it is permitted.
;;
CERT_E_PURPOSE equ _HRESULT_TYPEDEF_(0x800B0106)

;;
;; MessageId: CERT_E_ISSUERCHAINING
;;
;; MessageText:
;;
;;  A parent of a given certificate in fact did not issue that child certificate.
;;
CERT_E_ISSUERCHAINING equ _HRESULT_TYPEDEF_(0x800B0107)

;;
;; MessageId: CERT_E_MALFORMED
;;
;; MessageText:
;;
;;  A certificate is missing or has an empty value for an important field, such as a subject or issuer name.
;;
CERT_E_MALFORMED equ _HRESULT_TYPEDEF_(0x800B0108)

;;
;; MessageId: CERT_E_UNTRUSTEDROOT
;;
;; MessageText:
;;
;;  A certification chain processed correctly, but terminated in a root certificate which isn't trusted by the trust provider.
;;
CERT_E_UNTRUSTEDROOT equ _HRESULT_TYPEDEF_(0x800B0109)

;;
;; MessageId: CERT_E_CHAINING
;;
;; MessageText:
;;
;;  A chain of certs didn't chain as they should in a certain application of chaining.
;;
CERT_E_CHAINING equ _HRESULT_TYPEDEF_(0x800B010A)

;;
;; MessageId: TRUST_E_FAIL
;;
;; MessageText:
;;
;;  Generic Trust Failure.
;;
TRUST_E_FAIL equ _HRESULT_TYPEDEF_(0x800B010B)

;;
;; MessageId: CERT_E_REVOKED
;;
;; MessageText:
;;
;;  A certificate was explicitly revoked by its issuer.
;;
CERT_E_REVOKED equ _HRESULT_TYPEDEF_(0x800B010C)

;;
;; MessageId: CERT_E_UNTRUSTEDTESTROOT
;;
;; MessageText:
;;
;;  The root certificate is a testing certificate and the policy settings disallow test certificates.
;;
CERT_E_UNTRUSTEDTESTROOT equ _HRESULT_TYPEDEF_(0x800B010D)

;;
;; MessageId: CERT_E_REVOCATION_FAILURE
;;
;; MessageText:
;;
;;  The revocation process could not continue - the certificate(s) could not be checked.
;;
CERT_E_REVOCATION_FAILURE equ _HRESULT_TYPEDEF_(0x800B010E)

;;
;; MessageId: CERT_E_CN_NO_MATCH
;;
;; MessageText:
;;
;;  The certificate's CN name does not match the passed value.
;;
CERT_E_CN_NO_MATCH equ _HRESULT_TYPEDEF_(0x800B010F)

;;
;; MessageId: CERT_E_WRONG_USAGE
;;
;; MessageText:
;;
;;  The certificate is not valid for the requested usage.
;;
CERT_E_WRONG_USAGE equ _HRESULT_TYPEDEF_(0x800B0110)

;; *****************
;; FACILITY_SETUPAPI
;; *****************
;;
;; Since these error codes aren't in the standard Win32 range (i.e., 0-64K), define a
;; macro to map either Win32 or SetupAPI error codes into an HRESULT.
;;
HRESULT_FROM_SETUPAPI macro x
	exitm <( ( ( ( x )  and	 ( APPLICATION_ERROR_MASK  or  ERROR_SEVERITY_ERROR ) ) == ( APPLICATION_ERROR_MASK  or	 ERROR_SEVERITY_ERROR ) ) ? ( ( ( ( x )	 and  0000FFFFh )  or  ( FACILITY_SETUPAPI  shl	 16 )  or  80000000h ) ) : HRESULT_FROM_WIN32 ( x ) ) >
	endm
;;
;; MessageId: SPAPI_E_EXPECTED_SECTION_NAME
;;
;; MessageText:
;;
;;  A non-empty line was encountered in the INF before the start of a section.
;;
SPAPI_E_EXPECTED_SECTION_NAME equ _HRESULT_TYPEDEF_(0x800F0000)

;;
;; MessageId: SPAPI_E_BAD_SECTION_NAME_LINE
;;
;; MessageText:
;;
;;  A section name marker in the INF is not complete, or does not exist on a line by itself.
;;
SPAPI_E_BAD_SECTION_NAME_LINE equ _HRESULT_TYPEDEF_(0x800F0001)

;;
;; MessageId: SPAPI_E_SECTION_NAME_TOO_LONG
;;
;; MessageText:
;;
;;  An INF section was encountered whose name exceeds the maximum section name length.
;;
SPAPI_E_SECTION_NAME_TOO_LONG equ _HRESULT_TYPEDEF_(0x800F0002)

;;
;; MessageId: SPAPI_E_GENERAL_SYNTAX
;;
;; MessageText:
;;
;;  The syntax of the INF is invalid.
;;
SPAPI_E_GENERAL_SYNTAX equ _HRESULT_TYPEDEF_(0x800F0003)

;;
;; MessageId: SPAPI_E_WRONG_INF_STYLE
;;
;; MessageText:
;;
;;  The style of the INF is different than what was requested.
;;
SPAPI_E_WRONG_INF_STYLE equ _HRESULT_TYPEDEF_(0x800F0100)

;;
;; MessageId: SPAPI_E_SECTION_NOT_FOUND
;;
;; MessageText:
;;
;;  The required section was not found in the INF.
;;
SPAPI_E_SECTION_NOT_FOUND equ _HRESULT_TYPEDEF_(0x800F0101)

;;
;; MessageId: SPAPI_E_LINE_NOT_FOUND
;;
;; MessageText:
;;
;;  The required line was not found in the INF.
;;
SPAPI_E_LINE_NOT_FOUND equ _HRESULT_TYPEDEF_(0x800F0102)

;;
;; MessageId: SPAPI_E_NO_ASSOCIATED_CLASS
;;
;; MessageText:
;;
;;  The INF or the device information set or element does not have an associated install class.
;;
SPAPI_E_NO_ASSOCIATED_CLASS equ _HRESULT_TYPEDEF_(0x800F0200)

;;
;; MessageId: SPAPI_E_CLASS_MISMATCH
;;
;; MessageText:
;;
;;  The INF or the device information set or element does not match the specified install class.
;;
SPAPI_E_CLASS_MISMATCH equ _HRESULT_TYPEDEF_(0x800F0201)

;;
;; MessageId: SPAPI_E_DUPLICATE_FOUND
;;
;; MessageText:
;;
;;  An existing device was found that is a duplicate of the device being manually installed.
;;
SPAPI_E_DUPLICATE_FOUND equ _HRESULT_TYPEDEF_(0x800F0202)

;;
;; MessageId: SPAPI_E_NO_DRIVER_SELECTED
;;
;; MessageText:
;;
;;  There is no driver selected for the device information set or element.
;;
SPAPI_E_NO_DRIVER_SELECTED equ _HRESULT_TYPEDEF_(0x800F0203)

;;
;; MessageId: SPAPI_E_KEY_DOES_NOT_EXIST
;;
;; MessageText:
;;
;;  The requested device registry key does not exist.
;;
SPAPI_E_KEY_DOES_NOT_EXIST equ _HRESULT_TYPEDEF_(0x800F0204)

;;
;; MessageId: SPAPI_E_INVALID_DEVINST_NAME
;;
;; MessageText:
;;
;;  The device instance name is invalid.
;;
SPAPI_E_INVALID_DEVINST_NAME equ _HRESULT_TYPEDEF_(0x800F0205)

;;
;; MessageId: SPAPI_E_INVALID_CLASS
;;
;; MessageText:
;;
;;  The install class is not present or is invalid.
;;
SPAPI_E_INVALID_CLASS equ _HRESULT_TYPEDEF_(0x800F0206)

;;
;; MessageId: SPAPI_E_DEVINST_ALREADY_EXISTS
;;
;; MessageText:
;;
;;  The device instance cannot be created because it already exists.
;;
SPAPI_E_DEVINST_ALREADY_EXISTS equ _HRESULT_TYPEDEF_(0x800F0207)

;;
;; MessageId: SPAPI_E_DEVINFO_NOT_REGISTERED
;;
;; MessageText:
;;
;;  The operation cannot be performed on a device information element that has not been registered.
;;
SPAPI_E_DEVINFO_NOT_REGISTERED equ _HRESULT_TYPEDEF_(0x800F0208)

;;
;; MessageId: SPAPI_E_INVALID_REG_PROPERTY
;;
;; MessageText:
;;
;;  The device property code is invalid.
;;
SPAPI_E_INVALID_REG_PROPERTY equ _HRESULT_TYPEDEF_(0x800F0209)

;;
;; MessageId: SPAPI_E_NO_INF
;;
;; MessageText:
;;
;;  The INF from which a driver list is to be built does not exist.
;;
SPAPI_E_NO_INF equ _HRESULT_TYPEDEF_(0x800F020A)

;;
;; MessageId: SPAPI_E_NO_SUCH_DEVINST
;;
;; MessageText:
;;
;;  The device instance does not exist in the hardware tree.
;;
SPAPI_E_NO_SUCH_DEVINST equ _HRESULT_TYPEDEF_(0x800F020B)

;;
;; MessageId: SPAPI_E_CANT_LOAD_CLASS_ICON
;;
;; MessageText:
;;
;;  The icon representing this install class cannot be loaded.
;;
SPAPI_E_CANT_LOAD_CLASS_ICON equ _HRESULT_TYPEDEF_(0x800F020C)

;;
;; MessageId: SPAPI_E_INVALID_CLASS_INSTALLER
;;
;; MessageText:
;;
;;  The class installer registry entry is invalid.
;;
SPAPI_E_INVALID_CLASS_INSTALLER equ _HRESULT_TYPEDEF_(0x800F020D)

;;
;; MessageId: SPAPI_E_DI_DO_DEFAULT
;;
;; MessageText:
;;
;;  The class installer has indicated that the default action should be performed for this installation request.
;;
SPAPI_E_DI_DO_DEFAULT equ _HRESULT_TYPEDEF_(0x800F020E)

;;
;; MessageId: SPAPI_E_DI_NOFILECOPY
;;
;; MessageText:
;;
;;  The operation does not require any files to be copied.
;;
SPAPI_E_DI_NOFILECOPY equ _HRESULT_TYPEDEF_(0x800F020F)

;;
;; MessageId: SPAPI_E_INVALID_HWPROFILE
;;
;; MessageText:
;;
;;  The specified hardware profile does not exist.
;;
SPAPI_E_INVALID_HWPROFILE equ _HRESULT_TYPEDEF_(0x800F0210)

;;
;; MessageId: SPAPI_E_NO_DEVICE_SELECTED
;;
;; MessageText:
;;
;;  There is no device information element currently selected for this device information set.
;;
SPAPI_E_NO_DEVICE_SELECTED equ _HRESULT_TYPEDEF_(0x800F0211)

;;
;; MessageId: SPAPI_E_DEVINFO_LIST_LOCKED
;;
;; MessageText:
;;
;;  The operation cannot be performed because the device information set is locked.
;;
SPAPI_E_DEVINFO_LIST_LOCKED equ _HRESULT_TYPEDEF_(0x800F0212)

;;
;; MessageId: SPAPI_E_DEVINFO_DATA_LOCKED
;;
;; MessageText:
;;
;;  The operation cannot be performed because the device information element is locked.
;;
SPAPI_E_DEVINFO_DATA_LOCKED equ _HRESULT_TYPEDEF_(0x800F0213)

;;
;; MessageId: SPAPI_E_DI_BAD_PATH
;;
;; MessageText:
;;
;;  The specified path does not contain any applicable device INFs.
;;
SPAPI_E_DI_BAD_PATH equ _HRESULT_TYPEDEF_(0x800F0214)

;;
;; MessageId: SPAPI_E_NO_CLASSINSTALL_PARAMS
;;
;; MessageText:
;;
;;  No class installer parameters have been set for the device information set or element.
;;
SPAPI_E_NO_CLASSINSTALL_PARAMS equ _HRESULT_TYPEDEF_(0x800F0215)

;;
;; MessageId: SPAPI_E_FILEQUEUE_LOCKED
;;
;; MessageText:
;;
;;  The operation cannot be performed because the file queue is locked.
;;
SPAPI_E_FILEQUEUE_LOCKED equ _HRESULT_TYPEDEF_(0x800F0216)

;;
;; MessageId: SPAPI_E_BAD_SERVICE_INSTALLSECT
;;
;; MessageText:
;;
;;  A service installation section in this INF is invalid.
;;
SPAPI_E_BAD_SERVICE_INSTALLSECT equ _HRESULT_TYPEDEF_(0x800F0217)

;;
;; MessageId: SPAPI_E_NO_CLASS_DRIVER_LIST
;;
;; MessageText:
;;
;;  There is no class driver list for the device information element.
;;
SPAPI_E_NO_CLASS_DRIVER_LIST equ _HRESULT_TYPEDEF_(0x800F0218)

;;
;; MessageId: SPAPI_E_NO_ASSOCIATED_SERVICE
;;
;; MessageText:
;;
;;  The installation failed because a function driver was not specified for this device instance.
;;
SPAPI_E_NO_ASSOCIATED_SERVICE equ _HRESULT_TYPEDEF_(0x800F0219)

;;
;; MessageId: SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE
;;
;; MessageText:
;;
;;  There is presently no default device interface designated for this interface class.
;;
SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE equ _HRESULT_TYPEDEF_(0x800F021A)

;;
;; MessageId: SPAPI_E_DEVICE_INTERFACE_ACTIVE
;;
;; MessageText:
;;
;;  The operation cannot be performed because the device interface is currently active.
;;
SPAPI_E_DEVICE_INTERFACE_ACTIVE equ _HRESULT_TYPEDEF_(0x800F021B)

;;
;; MessageId: SPAPI_E_DEVICE_INTERFACE_REMOVED
;;
;; MessageText:
;;
;;  The operation cannot be performed because the device interface has been removed from the system.
;;
SPAPI_E_DEVICE_INTERFACE_REMOVED equ _HRESULT_TYPEDEF_(0x800F021C)

;;
;; MessageId: SPAPI_E_BAD_INTERFACE_INSTALLSECT
;;
;; MessageText:
;;
;;  An interface installation section in this INF is invalid.
;;
SPAPI_E_BAD_INTERFACE_INSTALLSECT equ _HRESULT_TYPEDEF_(0x800F021D)

;;
;; MessageId: SPAPI_E_NO_SUCH_INTERFACE_CLASS
;;
;; MessageText:
;;
;;  This interface class does not exist in the system.
;;
SPAPI_E_NO_SUCH_INTERFACE_CLASS equ _HRESULT_TYPEDEF_(0x800F021E)

;;
;; MessageId: SPAPI_E_INVALID_REFERENCE_STRING
;;
;; MessageText:
;;
;;  The reference string supplied for this interface device is invalid.
;;
SPAPI_E_INVALID_REFERENCE_STRING equ _HRESULT_TYPEDEF_(0x800F021F)

;;
;; MessageId: SPAPI_E_INVALID_MACHINENAME
;;
;; MessageText:
;;
;;  The specified machine name does not conform to UNC naming conventions.
;;
SPAPI_E_INVALID_MACHINENAME equ _HRESULT_TYPEDEF_(0x800F0220)

;;
;; MessageId: SPAPI_E_REMOTE_COMM_FAILURE
;;
;; MessageText:
;;
;;  A general remote communication error occurred.
;;
SPAPI_E_REMOTE_COMM_FAILURE equ _HRESULT_TYPEDEF_(0x800F0221)

;;
;; MessageId: SPAPI_E_MACHINE_UNAVAILABLE
;;
;; MessageText:
;;
;;  The machine selected for remote communication is not available at this time.
;;
SPAPI_E_MACHINE_UNAVAILABLE equ _HRESULT_TYPEDEF_(0x800F0222)

;;
;; MessageId: SPAPI_E_NO_CONFIGMGR_SERVICES
;;
;; MessageText:
;;
;;  The Plug and Play service is not available on the remote machine.
;;
SPAPI_E_NO_CONFIGMGR_SERVICES equ _HRESULT_TYPEDEF_(0x800F0223)

;;
;; MessageId: SPAPI_E_INVALID_PROPPAGE_PROVIDER
;;
;; MessageText:
;;
;;  The property page provider registry entry is invalid.
;;
SPAPI_E_INVALID_PROPPAGE_PROVIDER equ _HRESULT_TYPEDEF_(0x800F0224)

;;
;; MessageId: SPAPI_E_NO_SUCH_DEVICE_INTERFACE
;;
;; MessageText:
;;
;;  The requested device interface is not present in the system.
;;
SPAPI_E_NO_SUCH_DEVICE_INTERFACE equ _HRESULT_TYPEDEF_(0x800F0225)

;;
;; MessageId: SPAPI_E_DI_POSTPROCESSING_REQUIRED
;;
;; MessageText:
;;
;;  The device's co-installer has additional work to perform after installation is complete.
;;
SPAPI_E_DI_POSTPROCESSING_REQUIRED equ _HRESULT_TYPEDEF_(0x800F0226)

;;
;; MessageId: SPAPI_E_INVALID_COINSTALLER
;;
;; MessageText:
;;
;;  The device's co-installer is invalid.
;;
SPAPI_E_INVALID_COINSTALLER equ _HRESULT_TYPEDEF_(0x800F0227)

;;
;; MessageId: SPAPI_E_NO_COMPAT_DRIVERS
;;
;; MessageText:
;;
;;  There are no compatible drivers for this device.
;;
SPAPI_E_NO_COMPAT_DRIVERS equ _HRESULT_TYPEDEF_(0x800F0228)

;;
;; MessageId: SPAPI_E_NO_DEVICE_ICON
;;
;; MessageText:
;;
;;  There is no icon that represents this device or device type.
;;
SPAPI_E_NO_DEVICE_ICON equ _HRESULT_TYPEDEF_(0x800F0229)

;;
;; MessageId: SPAPI_E_INVALID_INF_LOGCONFIG
;;
;; MessageText:
;;
;;  A logical configuration specified in this INF is invalid.
;;
SPAPI_E_INVALID_INF_LOGCONFIG equ _HRESULT_TYPEDEF_(0x800F022A)

;;
;; MessageId: SPAPI_E_DI_DONT_INSTALL
;;
;; MessageText:
;;
;;  The class installer has denied the request to install or upgrade this device.
;;
SPAPI_E_DI_DONT_INSTALL equ _HRESULT_TYPEDEF_(0x800F022B)

;;
;; MessageId: SPAPI_E_INVALID_FILTER_DRIVER
;;
;; MessageText:
;;
;;  One of the filter drivers installed for this device is invalid.
;;
SPAPI_E_INVALID_FILTER_DRIVER equ _HRESULT_TYPEDEF_(0x800F022C)

;;
;; MessageId: SPAPI_E_ERROR_NOT_INSTALLED
;;
;; MessageText:
;;
;;  No installed components were detected.
;;
SPAPI_E_ERROR_NOT_INSTALLED equ _HRESULT_TYPEDEF_(0x800F1000)

endif ;; _WINERROR_

.list
