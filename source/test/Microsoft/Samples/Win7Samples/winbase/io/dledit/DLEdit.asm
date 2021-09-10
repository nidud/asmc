;
; https://github.com/microsoft/Windows-classic-samples/tree/master/Samples/
;   Win7Samples/winbase/io/dledit

;;
;; DLEDIT  -- Drive Letter Assignment Editor
;;
;; This program demonstrates how to add or remove persistent drive letter
;; assignments in Windows 2000, Windows XP, and Windows Server 2003.  These
;; drive letter assignments persist through machine reboots.
;;
;; Platforms:
;;    This program requires Windows 2000 or later.
;;
;; Command-line syntax:
;;    DLEDIT <drive letter> <NT device name>      -- Adds persistent drive letter
;;    DLEDIT -t <drive letter> <NT device name>   -- Adds temporary drive letter
;;    DLEDIT -r <drive letter>                    -- Removes a drive letter
;;    DLEDIT <drive letter>                       -- Shows drive letter mapping
;;    DLEDIT -a                                   -- Shows all drive letter mappings
;;
;; Command-line examples:
;;
;;    Say that E: refers to CD-ROM drive, and you want to make F: point to that
;;    CD-ROM drive instead.  Use the following two commands:
;;
;;       DLEDIT -r E:\
;;       DLEDIT F:\ \Device\CdRom0
;;
;;    To display what device a drive letter is mapped to, use the following
;;    command:
;;
;;       DLEDIT f:
;;
;;
;; *******************************************************************************
;; WARNING: WARNING: WARNING: WARNING: WARNING: WARNING: WARNING: WARNING:
;;
;;    This program really will change drive letter assignments, and the changes
;;    persist through reboots.  Do not remove drive letters of your hard disks if
;;    you don't have this program on a floppy disk or you might not be able to
;;    access your hard disks again!
;; *******************************************************************************
;;
;; -----------------------------------------------------------------------------

;;
;; reduce number of headers pulled in by windows.h to improve build time
;;
WIN32_LEAN_AND_MEAN equ 1
_WIN32_WINNT equ 0x0500

include windows.inc
include winioctl.inc
include stdio.inc
include stdlib.inc
include tchar.inc

;; -----------------------------------------------------------------------------

GPT_BASIC_DATA_ATTRIBUTE_HIDDEN equ 0x4000000000000000 ;; from DDK's NTDDDISK.H

IOCTL_VOLUME_GET_GPT_ATTRIBUTES equ CTL_CODE(IOCTL_VOLUME_BASE, 14, METHOD_BUFFERED, FILE_ANY_ACCESS)

VOLUME_GET_GPT_ATTRIBUTES_INFORMATION STRUC
    GptAttributes ULONGLONG ?
VOLUME_GET_GPT_ATTRIBUTES_INFORMATION ENDS
PVOLUME_GET_GPT_ATTRIBUTES_INFORMATION typedef ptr VOLUME_GET_GPT_ATTRIBUTES_INFORMATION

;; -----------------------------------------------------------------------------


HIDDEN_PARTITION_FLAG equ 0x10


;; Private error codes.  Follows guidelines in winerror.h

PRIV_ERROR_DRIVE_LETTER_IN_USE      equ 0xE0000001
PRIV_ERROR_DRIVE_LETTER_NOT_USED    equ 0xE0000002
PRIV_ERROR_PARTITION_HIDDEN         equ 0x60000001
PRIV_ERROR_PARTITION_NOT_RECOGNIZED equ 0x60000002
PRIV_ERROR_NOT_PARTITIONABLE_DEVICE equ 0x60000003

option dllimport:none

AssignPersistentDriveLetter proto WINAPI :LPCTSTR, :LPCTSTR
RemovePersistentDriveLetter proto WINAPI :LPCTSTR
AssignTemporaryDriveLetter  proto WINAPI :LPCTSTR, :LPCTSTR
RemoveTemporaryDriveLetter  proto WINAPI :LPCTSTR
IsPartitionHidden           proto WINAPI :BYTE, :ULONGLONG
IsDriveLetter               proto WINAPI :LPCTSTR
IsWindowsXP_orLater         proto WINAPI
PrintHelp                   proto WINAPI :LPCTSTR

    .code

;;
;; main( IN argc, IN argv )
;;
;; Parameters
;;    argc
;;       Count of the command-line arguments
;;    argv
;;       Array of pointers to the individual command-line arguments
;;
;; This function is the main program.  It parses the command-line arguments and
;; performs the work of either removing a drive letter or adding a new one.
;;


_tmain proc uses rsi rdi rbx argc:int_t, argv:ptr ptr TCHAR

    ;;
    ;; Command-line parsing.
    ;;     1) Validate arguments
    ;;     2) Determine what user wants to do
    ;;

    mov rsi,rdx
    .switch ecx

    .case 3

        mov rbx,[rsi+8]
        mov rdi,[rsi+16]

        .ifd !lstrcmpi( rbx, "-r" )

            .endc .ifd !IsDriveLetter( rdi )

            ;;
            ;; User wants to remove the drive letter.  Command line should be:
            ;;   dledit -r <drive letter>
            ;;

            .if !RemovePersistentDriveLetter( rdi )

                .if !RemoveTemporaryDriveLetter( rdi )

                    GetLastError()

                    .switch eax

                    .case ERROR_FILE_NOT_FOUND
                        _tprintf( "%s is not in use\n", rdi )
                        .endc

                    .default
                        _tprintf( "error %lu: couldn't remove %s\n", eax, rdi )
                    .endsw
                .endif
            .endif
            .endc ;; End if remove drive letter mapping
        .endif

        .endc .if !IsDriveLetter( rbx )

        ;;
        ;; User wants to add a persistent drive letter.  Command line should be:
        ;;    dledit <drive letter> <NT device name>
        ;;
        ;;   Try a persistent drive letter; if partition is hidden, the persistent
        ;;   mapping will fail--try a temporary mapping and tell user about it.
        ;;
        ;;   Note: Hidden partitions can be assigned temporary drive letters.
        ;;   These are nothing more than symbolic links created with
        ;;   DefineDosDevice.  Temporary drive letters will be removed when the
        ;;   system is rebooted.
        ;;

        .if !AssignPersistentDriveLetter( rbx, rdi )

            GetLastError()
            .switch eax
            .case PRIV_ERROR_PARTITION_HIDDEN
                .if AssignTemporaryDriveLetter( rbx, rdi )
                    _tprintf( "%s is hidden; mapped %s temporarily\n", rdi, rbx )
                .else
                    _tprintf( "%s is hidden; couldn't map %s to it\n", rdi, rbx )
                .endif
                .endc
            .case PRIV_ERROR_DRIVE_LETTER_IN_USE
                _tprintf( "%s is in use, can't map it to %s\n", rbx, rdi )
                .endc
            .case ERROR_FILE_NOT_FOUND
                _tprintf( "%s doesn't exist or can't be opened\n", rdi )
                .endc
            .case ERROR_INVALID_PARAMETER
                _tprintf( "%s already has a drive letter; can't map %s to it\n", rdi, rbx )
                .endc
            .default
                _tprintf( "error %lu: couldn't map %s to %s\n", eax, rbx, rdi )
            .endsw
        .endif
        .endc ;; End if add persistent drive letter mapping

    .case 4

        mov rbx,[rsi+1*8]
        mov rdi,[rsi+2*8]
        mov rsi,[rsi+3*8]

        .endc .if lstrcmpi( rbx, "-t" )
        .endc .if !IsDriveLetter( rdi )

        ;;
        ;;   User wants to add a temporary drive letter.  Command line should be:
        ;;      dledit -t <drive letter> <NT device name>
        ;;

        .if !AssignTemporaryDriveLetter( rdi, rsi )

            GetLastError()
            .switch eax
            .case ERROR_FILE_NOT_FOUND
                _tprintf( "%s doesn't exist or can't be opened\n", rsi )
                .endc
            .case PRIV_ERROR_DRIVE_LETTER_IN_USE
                _tprintf( "%s is in use, can't map it to %s\n", rdi, rsi )
                .endc
            .default
                _tprintf( "error %lu: couldn't map %s to %s\n", eax, rdi, rsi )
            .endsw
        .endif
        .endc ;; End if add temporary drive letter mapping

    .case 2

        .new szNtDeviceName[MAX_PATH]:TCHAR
        .new szDriveLetter[3]:TCHAR

        mov rbx,[rsi+8]

        .if !lstrcmpi( rbx, "-a" )

            ;;
            ;;   User wants to show all mappings of drive letters to their respective
            ;;   devices.  Command line should be:
            ;;      dledit -a
            ;;
            ;;   Largest possible array of drive strings is 26 drive letters
            ;;   times 4 chars per drive letter plus 1 for the terminating NULL
            ;;
            MAX_DRIVE_STRING_LENGTH equ (26 * 4 + 1)

            .new szDriveStrings[MAX_DRIVE_STRING_LENGTH]:TCHAR

            ;;
            ;;   Get a list of all current drive letters, then for each, print the
            ;;   mapping.  Drive letters are returned in the form
            ;;   A:\<NULL>B:\<NULL>C:\<NULL>...<NULL>.
            ;;
            GetLogicalDriveStrings( MAX_DRIVE_STRING_LENGTH, &szDriveStrings )

            .if ( eax && eax <= MAX_DRIVE_STRING_LENGTH )

                _tprintf( "Drive     Device\n"
                          "-----     ------\n" )

                lea rbx,szDriveStrings

                .while TCHAR ptr [rbx] != 0

                    ;; QueryDosDevice requires drive letters in the format X:

                    mov szDriveLetter[TCHAR*0],[rbx]
                    mov szDriveLetter[TCHAR*1],':'
                    mov szDriveLetter[TCHAR*2],0

                    .if QueryDosDevice( &szDriveLetter, &szNtDeviceName, MAX_PATH )

                        _tprintf( "%-10s%s\n", &szDriveLetter, &szNtDeviceName )
                    .endif

                    add rbx,TCHAR*4 ;; size of X:\<NULL>
                .endw

            .else

                _tprintf( "couldn't list drive letters and their devices\n" )
            .endif

            .endc ;; End if show all drive letter mappings
        .endif

        .endc .if !IsDriveLetter( rbx )

        ;;
        ;;   User wants to show what device is connected to the drive letter.
        ;;   Command line should be:
        ;;      dledit <drive letter>
        ;;
        ;;   Command-line argument for the drive letter could be in one of two
        ;;   formats:  C:\ or C:.  We normalize this to C: for QueryDosDevice.
        ;;

        mov szDriveLetter[TCHAR*0],[rbx]
        mov szDriveLetter[TCHAR*1],':'
        mov szDriveLetter[TCHAR*2],0

        .if QueryDosDevice(rbx, &szNtDeviceName, MAX_PATH)

            _tprintf("%s is mapped to %s\n", &szDriveLetter, &szNtDeviceName )

        .else

            GetLastError()
            .switch eax
            .case ERROR_FILE_NOT_FOUND
                _tprintf("%s is not in use\n", rbx )
                .endc
            .default
                _tprintf("error %lu: couldn't get mapping for %s\n", eax, rbx )
            .endsw
        .endif
        .endc ;; End if show drive letter mapping

    .default

        ;; User has selected an invalid operation--display help.

        PrintHelp( "DLEdit" )
    .endsw
    ret

_tmain endp

;;
;; PrintHelp( IN pszAppName )
;;
;; Parameters
;;    pszAppName
;;       The name of the executable.  Used in displaying the help for this app.
;;
;; Prints the command-line usage help.
;;

PrintHelp proc pszAppName:LPCTSTR

    _tprintf(
        "Adds, removes, queries drive letter assignments\n\n"
        "usage: %s <Drive Letter> <NT device name>     add a drive letter\n"
        "       %s -t <Drive Letter> <NT device name>  add a temporary drive letter\n"
        "       %s -r <Drive Letter>                   remove a drive letter\n"
        "       %s <Drive Letter>                      show mapping for drive letter\n"
        "       %s -a                                  show all mappings\n\n"
        "example: %s e:\\ \\Device\\CdRom0\n"
        "         %s -r e:\\\n",
        rcx, rcx, rcx, rcx, rcx, rcx, rcx
        )
   xor eax,eax
   ret

PrintHelp endp


;;
;; AssignPersistentDriveLetter(IN pszDriveLetter, IN pszDeviceName)
;;
;; Description:
;;    Creates a persistent drive letter that refers to a specified device. This
;;    drive letter will remain even when the system is restarted.
;;
;; Parameters:
;;    pszDriveLetter
;;       The new drive letter to create.  Must be in the form X: or X:\
;;
;;    pszDeviceName
;;       The NT device name to which the drive letter will be assigned.
;;
;; Return Value:
;;    Returns TRUE if the drive letter was added, or FALSE if it wasn't.
;;

AssignPersistentDriveLetter proc WINAPI pszDriveLetter:LPCTSTR, pszDeviceName:LPCTSTR

    local fResult:BOOL
    local szUniqueVolumeName[MAX_PATH]:TCHAR
    local szDriveLetterAndSlash[4]:TCHAR
    local szDriveLetter[3]:TCHAR

    ;;
    ;; Make sure we are passed a drive letter and a device name.  lstrlen
    ;; is useful because it will return zero if the pointer points to memory
    ;; that can't be read or a string that causes an invalid page fault before
    ;; the terminating NULL.
    ;;

    .ifd lstrlen(pszDriveLetter)
        .ifd lstrlen(pszDeviceName)
            IsDriveLetter(pszDriveLetter)
        .endif
    .endif
    .if eax == 0
        SetLastError(ERROR_INVALID_PARAMETER)
        .return FALSE
    .endif

    ;;
    ;; GetVolumeNameForVolumeMountPoint, SetVolumeMountPoint, and
    ;; DeleteVolumeMountPoint require drive letters to have a trailing backslash.
    ;; However, DefineDosDevice and QueryDosDevice require that the trailing
    ;; backslash be absent.  So, we'll set up the following variables:
    ;;
    ;; szDriveLetterAndSlash     for the mount point APIs
    ;; szDriveLetter             for DefineDosDevice
    ;;

    mov rcx,pszDriveLetter
    mov szDriveLetterAndSlash[TCHAR*0],[rcx]
    mov szDriveLetterAndSlash[TCHAR*1],':'
    mov szDriveLetterAndSlash[TCHAR*2],'\'
    mov szDriveLetterAndSlash[TCHAR*3],0

    mov szDriveLetter[TCHAR*0],szDriveLetterAndSlash
    mov szDriveLetter[TCHAR*1],':'
    mov szDriveLetter[TCHAR*2],0

    ;;
    ;; Determine if the drive letter is currently in use.  If so, return the
    ;; error to the caller.  NOTE:  we temporarily reuse szUniqueVolumeName
    ;; instead of allocating a large array for this one call.
    ;;

    .if QueryDosDevice(&szDriveLetter, &szUniqueVolumeName, MAX_PATH)

        SetLastError(PRIV_ERROR_DRIVE_LETTER_IN_USE)
        .return FALSE
    .endif


    ;;
    ;; To map a persistent drive letter, we must make sure that the target
    ;; device is one of the following:
    ;;
    ;;    A recognized partition and is not hidden
    ;;    A dynamic volume
    ;;    A non-partitionable device such as CD-ROM
    ;;
    ;; Start by using the drive letter as a symbolic link to the device.  Then,
    ;; open the device to gather the information necessary to determine if the
    ;; drive can have a persistent drive letter.
    ;;

    .if DefineDosDevice(DDD_RAW_TARGET_PATH, &szDriveLetter, pszDeviceName)

        .new hDevice:HANDLE
        .new dwBytesReturned:DWORD
        .new szDriveName[7]:TCHAR ;; holds \\.\X: plus NULL.

        .new volinfo:VOLUME_GET_GPT_ATTRIBUTES_INFORMATION
        .new partinfo:PARTITION_INFORMATION


        _tcsncpy_s(&szDriveName, _countof(szDriveName), "\\\\.\\", _TRUNCATE)
        _tcsncat_s(&szDriveName, _countof(szDriveName), &szDriveLetter, _TRUNCATE)

        mov hDevice,CreateFile(&szDriveName, GENERIC_READ,
                            FILE_SHARE_READ or FILE_SHARE_WRITE,
                            NULL, OPEN_EXISTING, 0, NULL)

        .if hDevice != INVALID_HANDLE_VALUE

            ;;
            ;; See if drive is partitionable and retrieve the partition type.
            ;; If the device doesn't have a partition, note it by setting the
            ;; partition type to unused.
            ;;

            .ifd !DeviceIoControl( hDevice, IOCTL_DISK_GET_PARTITION_INFO, NULL, 0,
                    &partinfo, sizeof(partinfo), &dwBytesReturned, NULL )

                mov partinfo.PartitionType,PARTITION_ENTRY_UNUSED
            .endif

            ;;
            ;; On Windows XP, partition entries on GUID Partition Table drives
            ;; have an attribute that determines whether partitions are hidden.
            ;; Therefore, we must check this bit on the target partition.
            ;;
            ;; If we're running on Windows 2000, there are no GPT drives, so
            ;; set flags to none.  This is important for the check for hidden
            ;; partitions later.
            ;;
            .if IsWindowsXP_orLater()

                .ifd !DeviceIoControl( hDevice, IOCTL_VOLUME_GET_GPT_ATTRIBUTES, NULL, 0,
                        &volinfo, sizeof(volinfo), &dwBytesReturned, NULL )

                    mov volinfo.GptAttributes,0
                .endif

            .else

                mov volinfo.GptAttributes,0
            .endif
            CloseHandle(hDevice)

        .else

            ;;
            ;; Remove the drive letter symbolic link we created, let caller know
            ;; we couldn't open the drive.
            ;;
            DefineDosDevice(DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
                    &szDriveLetter, pszDeviceName)
            .return FALSE
        .endif

        ;;
        ;; Now, make sure drive meets requirements for receiving a persistent
        ;; drive letter.
        ;;
        ;; Note: on Windows XP, partitions that were hidden when the system
        ;; booted are not assigned a unique volume name.  They will not be given
        ;; one until they are marked as not hidden and the system rebooted.
        ;; Therefore, we cannot create a mount point hidden partitions.
        ;;
        ;; On Windows 2000, hidden partitions are assigned unique volume names
        ;; and so can have persistent drive letters.  However, we will not allow
        ;; that behavior in this tool as hidden partitions should not be assigned
        ;; drive letters.
        ;;

        .if IsPartitionHidden(partinfo.PartitionType, volinfo.GptAttributes)

            ;; remove the drive letter we created, let caller know what happened.

            DefineDosDevice(
                DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
                &szDriveLetter, pszDeviceName )

            SetLastError(PRIV_ERROR_PARTITION_HIDDEN)
            .return FALSE
        .endif

        ;;
        ;; Verify that the drive letter must refer to a recognized partition,
        ;; a dynamic volume, or a non-partitionable device such as CD-ROM.
        ;;

        .if ( IsRecognizedPartition( partinfo.PartitionType ) || \
                partinfo.PartitionType == PARTITION_LDM || \
                partinfo.PartitionType == PARTITION_ENTRY_UNUSED )

            ;;
            ;; Now add the drive letter by calling on the volume mount manager.
            ;; Once we have the unique volume name that the new drive letter
            ;; will point to, delete the symbolic link because the Mount Manager
            ;; allows only one reference to a device at a time (the new one to
            ;; be added).
            ;;

            mov fResult,GetVolumeNameForVolumeMountPoint(&szDriveLetterAndSlash,
                                                     &szUniqueVolumeName,
                                                     MAX_PATH)

            DefineDosDevice(
                DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
                &szDriveLetter, pszDeviceName )

            mov eax,fResult
            .if eax
                SetVolumeMountPoint(&szDriveLetterAndSlash, &szUniqueVolumeName)
            .endif
            .return
        .endif

        ;;
        ;; Device doesn't meet the criteria for persistent drive letter.
        ;; Remove the drive letter symbolic link we created.
        ;;

        DefineDosDevice(
            DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
            &szDriveLetter, pszDeviceName )
        SetLastError(PRIV_ERROR_PARTITION_NOT_RECOGNIZED)
        mov eax,FALSE

        ;; end if DeviceIoControl to map symbolic link
    .endif
    ret

AssignPersistentDriveLetter endp


;;
;; RemovePersistentDriveLetter( IN pszDriveLetter)
;;
;; Description:
;;    Removes a drive letter that was created by AssignPersistentDriveLetter().
;;
;; Parameters:
;;    pszDriveLetter
;;       The drive letter to remove.  Must be in the format X: or X:\
;;
;; Return Value:
;;    Returns TRUE if the drive letter was removed, or FALSE if it wasn't.
;;

RemovePersistentDriveLetter proc WINAPI pszDriveLetter:LPCTSTR

   local szDriveLetterAndSlash[4]:TCHAR

   ;; Make sure we have a drive letter.

   .if lstrlen(pszDriveLetter)
       IsDriveLetter(pszDriveLetter)
   .endif
   .if !eax
      SetLastError(ERROR_INVALID_PARAMETER)
      .return FALSE
   .endif

   ;;
   ;; pszDriveLetter could be in the format X: or X:\.  DeleteVolumeMountPoint
   ;; requires X:\, so add a trailing backslash.
   ;;
   mov rcx,pszDriveLetter
   mov szDriveLetterAndSlash[TCHAR*0],[rcx]
   mov szDriveLetterAndSlash[TCHAR*1],':'
   mov szDriveLetterAndSlash[TCHAR*2],'\'
   mov szDriveLetterAndSlash[TCHAR*3],0

   DeleteVolumeMountPoint(&szDriveLetterAndSlash)
   ret

RemovePersistentDriveLetter endp


;;
;; AssignTemporaryDriveLetter( IN pszDriveLetter, IN pszDeviceName)
;;
;; Description:
;;    Creates a temporary drive letter that refers to a specified device.  This
;;    drive letter will exist only until the system is shut down or restarted.
;;
;; Parameters:
;;    pszDriveLetter
;;       The new drive letter to create.  Must be in the form X: or X:\
;;
;;    pszDeviceName
;;       The NT device name to which the drive letter will be assigned.
;;
;; Return Value:
;;    Returns TRUE if the temporary drive letter was assigned, or FALSE if it
;;    could not be.
;;
;; Notes:
;;    A temporary drive letter is just a symbolic link.  It can be removed at any
;;    time by deleting the symbolic link. If it exists when the system is shut
;;    down or restarted, it will be removed automatically.
;;
;;    AssignTemporaryDriveLetter requires device to be present.
;;

AssignTemporaryDriveLetter proc WINAPI pszDriveLetter:LPCTSTR, pszDeviceName:LPCTSTR

   local szDevice[MAX_PATH]:TCHAR
   local szDriveLetter[3]:TCHAR
   local fResult:BOOL

   ;; Verify that caller passed a drive letter and device name.

   .ifd lstrlen(pszDriveLetter)
       .ifd lstrlen(pszDeviceName)
            IsDriveLetter(pszDriveLetter)
       .endif
   .endif
   .if !eax
      SetLastError(ERROR_INVALID_PARAMETER)
      .return FALSE
   .endif

   ;;
   ;; Make sure the drive letter isn't already in use.  If not in use,
   ;; create the symbolic link to establish the temporary drive letter.
   ;;
   ;; pszDriveLetter could be in the format X: or X:\; QueryDosDevice and
   ;; DefineDosDevice need X:
   ;;
   mov rcx,pszDriveLetter
   mov szDriveLetter[TCHAR*0],[rcx]
   mov szDriveLetter[TCHAR*1],':'
   mov szDriveLetter[TCHAR*2],0

   .ifd !QueryDosDevice( &szDriveLetter, &szDevice, MAX_PATH )

      ;;
      ;; If we can create the symbolic link, verify that it points to a real
      ;; device.  If not, remove the link and return an error.  CreateFile sets
      ;; the last error code to ERROR_FILE_NOT_FOUND.
      ;;

      .ifd DefineDosDevice( DDD_RAW_TARGET_PATH, &szDriveLetter, pszDeviceName )

         .new hDevice:HANDLE
         .new szDriveName[7]:TCHAR ;; holds \\.\X: plus NULL.

         _tcsncpy_s(&szDriveName, _countof(szDriveName), "\\\\.\\", _TRUNCATE)
         _tcsncat_s(&szDriveName, _countof(szDriveName), &szDriveLetter, _TRUNCATE)

         CreateFile( &szDriveName, GENERIC_READ, FILE_SHARE_READ or FILE_SHARE_WRITE,
                NULL, OPEN_EXISTING, 0, NULL )

         .if eax != INVALID_HANDLE_VALUE

            CloseHandle(rax)
            mov eax,TRUE

         .else

            DefineDosDevice(
                    DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
                    &szDriveLetter, pszDeviceName )
            xor eax,eax
         .endif
      .endif

   .else

      SetLastError(PRIV_ERROR_DRIVE_LETTER_IN_USE)
      xor eax,eax
   .endif
   ret

AssignTemporaryDriveLetter endp


;;
;; RemoveTemporaryDriveLetter( IN pszDriveLetter)
;;
;; Description:
;;    Removes a drive letter that was created by AssignTemporaryDriveLetter().
;;
;; Parameters:
;;    pszDriveLetter
;;       The drive letter to remove.  Must be in the format X: or X:\
;;
;; Return Value:
;;    Returns TRUE if the drive letter was removed, or FALSE if it wasn't.
;;

RemoveTemporaryDriveLetter proc WINAPI pszDriveLetter:LPCTSTR

    local szDriveLetter[3]:TCHAR
    local szDeviceName[MAX_PATH]:TCHAR

    ;; Verify that caller passed a drive letter and device name.

    .ifd lstrlen(pszDriveLetter)
        IsDriveLetter(pszDriveLetter)
    .endif
    .if !eax

        SetLastError(ERROR_INVALID_PARAMETER)
        .return FALSE
    .endif

    ;;
    ;; pszDriveLetter could be in the format X: or X:\; DefineDosDevice
    ;; needs X:
    ;;
    mov rcx,pszDriveLetter
    mov szDriveLetter[TCHAR*0],[rcx]
    mov szDriveLetter[TCHAR*1],':'
    mov szDriveLetter[TCHAR*2],0

    .ifd QueryDosDevice(&szDriveLetter, &szDeviceName, MAX_PATH)

        DefineDosDevice(
            DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
            &szDriveLetter, &szDeviceName )
    .endif
    ret

RemoveTemporaryDriveLetter endp


;;
;; IsPartitionHidden( IN partitionType, IN partitionAttribs)
;;
;; Description:
;;    Determines if the partition hosting a volume is hidden or not.
;;
;; Parameters:
;;    partitionType
;;       Specifies the partitition type; this value is obtained from
;;       IOCTL_DISK_GET_PARTITION_INFO or IOCTL_DISK_GET_DRIVE_GEOMETRY.
;;       A partition type that has bit 0x10 set is hidden.
;;
;;    partitionAttribs
;;       Specifies the attributes of a GUID Partition Type (GPT)-style partition
;;       entry.  This value is obtained from IOCTL_VOLUME_GET_GPT_ATTRIBUTES
;;       or IOCTL_DISK_GET_DRIVE_GEOMETRY_EX.  A GPT partition that has
;;       GPT_BASIC_DATA_ATTRIBUTE_HIDDEN set is hidden.
;;
;; Return Value:
;;    Returns TRUE if the partition is hidden or FALSE if it is not.
;;
;; Notes:
;;    On Windows XP and Windows Server 2003, partitions that were hidden when
;;    the system booted are not assigned a unique volume name.  They will not
;;    be given one until they are marked as not hidden and the system rebooted.
;;    Therefore, we cannot create a mount point hidden partitions.
;;
;;    On Windows 2000, hidden partitions are assigned unique volume names
;;    and so can have persistent drive letters.  However, we will not allow
;;    that behavior in this tool as hidden partitions should not be assigned
;;    drive letters.
;;

IsPartitionHidden proc WINAPI partitionType:BYTE, partitionAttribs:ULONGLONG

    and ecx,not HIDDEN_PARTITION_FLAG
    IsRecognizedPartition(cl)
    mov rcx,GPT_BASIC_DATA_ATTRIBUTE_HIDDEN
    .if (partitionAttribs & rcx) || ((partitionType & HIDDEN_PARTITION_FLAG) && eax )
        mov eax,TRUE
    .else
        mov eax,FALSE
    .endif
    ret

IsPartitionHidden endp


;;
;; IsDriveLetter( IN pszDriveLetter)
;;
;; Description:
;;    Verifies string passed in is of the form X: or X:\ where X is a letter.
;;
;; Parameters:
;;    pszDriveLetter
;;       A null terminated string.
;;
;; Return Value:
;;    TRUE if the string is of the form X: or X:\ where X is a letter.  X
;;    may be upper-case or lower-case.  If the string isn't of this from,
;;    returns FALSE.
;;

IsDriveLetter proc WINAPI pszDriveLetter:LPCTSTR

    ;;
    ;; format must be: X:<null> or X:\<NULL> where X is a letter.  lstrlen will
    ;; return 0 if inaccessible pointer is supplied, or if reading bytes of
    ;; string causes an access violation before reaching a terminating NULL.
    ;;

    IsCharAlpha([rcx])
    mov rcx,pszDriveLetter
    movzx edx,TCHAR ptr [rcx+TCHAR*0]
    movzx r8d,TCHAR ptr [rcx+TCHAR*1]
    movzx r9d,TCHAR ptr [rcx+TCHAR*2]
    movzx ecx,TCHAR ptr [rcx+TCHAR*3]

    .if ( edx && eax && r8d == ':' && ( r9d == 0 || r9d == '\' && ecx == 0 ) )
        mov eax,TRUE
    .else
        mov eax,FALSE
    .endif
    ret

IsDriveLetter endp


;;
;; IsWindowsXP_orLater()
;;
;; Description:
;;    Determines if the currently-running version of Windows is Windows XP or
;;    Windows Server 2003 or later.
;;
;; Return Value:
;;    Returns TRUE if the currently-running system is Windows XP or Windows 2003
;;    Server or later systems. Returns FALSE otherwise.
;;

IsWindowsXP_orLater proc WINAPI

    local osvi:OSVERSIONINFOEX
    local comparisonMask:ULONGLONG

    ZeroMemory(&osvi, sizeof(osvi))

    mov osvi.dwOSVersionInfoSize,sizeof(osvi)
    mov osvi.dwMajorVersion,5
    mov osvi.dwMinorVersion,1

    mov comparisonMask,0

    mov comparisonMask,VerSetConditionMask(comparisonMask, VER_MAJORVERSION, VER_GREATER_EQUAL)
    mov comparisonMask,VerSetConditionMask(comparisonMask, VER_MINORVERSION, VER_GREATER_EQUAL)

    .return VerifyVersionInfo(&osvi, VER_MAJORVERSION or VER_MINORVERSION, comparisonMask)

IsWindowsXP_orLater endp

    end _tstart
