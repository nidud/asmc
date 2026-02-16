;
; https://github.com/microsoft/Windows-classic-samples/tree/master/Samples/
;   Win7Samples/winbase/io/dledit

define WIN32_LEAN_AND_MEAN 1
define _WIN32_WINNT 0x0500

include windows.inc
include winioctl.inc
include stdio.inc
include stdlib.inc
include tchar.inc

ifndef _TRUNCATE
define _TRUNCATE (-1)
endif

GPT_BASIC_DATA_ATTRIBUTE_HIDDEN equ 0x4000000000000000 ;; from DDK's NTDDDISK.H

IOCTL_VOLUME_GET_GPT_ATTRIBUTES equ CTL_CODE(IOCTL_VOLUME_BASE, 14, METHOD_BUFFERED, FILE_ANY_ACCESS)

VOLUME_GET_GPT_ATTRIBUTES_INFORMATION STRUC
    GptAttributes ULONGLONG ?
VOLUME_GET_GPT_ATTRIBUTES_INFORMATION ENDS
PVOLUME_GET_GPT_ATTRIBUTES_INFORMATION typedef ptr VOLUME_GET_GPT_ATTRIBUTES_INFORMATION


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

_tmain proc uses rsi rdi rbx argc:int_t, argv:ptr ptr TCHAR

    mov rsi,rdx
    .switch ecx
    .case 3

        mov rbx,[rsi+8]
        mov rdi,[rsi+16]

        .ifd !lstrcmpi( rbx, "-r" )

            .endc .ifd !IsDriveLetter( rdi )

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

            MAX_DRIVE_STRING_LENGTH equ (26 * 4 + 1)

            .new szDriveStrings[MAX_DRIVE_STRING_LENGTH]:TCHAR

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
    endp


PrintHelp proc pszAppName:LPCTSTR
    _tprintf(
        "Adds, removes, queries drive letter assignments\n\n"
        "usage: %s <Drive Letter> <NT device name>     add a drive letter\n"
        "       %s -t <Drive Letter> <NT device name>  add a temporary drive letter\n"
        "       %s -r <Drive Letter>                   remove a drive letter\n"
        "       %s <Drive Letter>                      show mapping for drive letter\n"
        "       %s -a                                  show all mappings\n\n"
        "example: %s e:\\ \\Device\\CdRom0\n"
        "         %s -r e:\\\n", rcx, rcx, rcx, rcx, rcx, rcx, rcx )
    xor eax,eax
    ret
    endp


AssignPersistentDriveLetter proc WINAPI pszDriveLetter:LPCTSTR, pszDeviceName:LPCTSTR

    local fResult:BOOL
    local szUniqueVolumeName[MAX_PATH]:TCHAR
    local szDriveLetterAndSlash[4]:TCHAR
    local szDriveLetter[3]:TCHAR

    .ifd lstrlen(pszDriveLetter)
        .ifd lstrlen(pszDeviceName)
            IsDriveLetter(pszDriveLetter)
        .endif
    .endif
    .if eax == 0
        SetLastError(ERROR_INVALID_PARAMETER)
        .return FALSE
    .endif
    mov rcx,pszDriveLetter
    mov szDriveLetterAndSlash[TCHAR*0],[rcx]
    mov szDriveLetterAndSlash[TCHAR*1],':'
    mov szDriveLetterAndSlash[TCHAR*2],'\'
    mov szDriveLetterAndSlash[TCHAR*3],0
    mov szDriveLetter[TCHAR*0],szDriveLetterAndSlash
    mov szDriveLetter[TCHAR*1],':'
    mov szDriveLetter[TCHAR*2],0
    .if QueryDosDevice(&szDriveLetter, &szUniqueVolumeName, MAX_PATH)
        SetLastError(PRIV_ERROR_DRIVE_LETTER_IN_USE)
        .return FALSE
    .endif

    .if DefineDosDevice(DDD_RAW_TARGET_PATH, &szDriveLetter, pszDeviceName)

       .new hDevice:HANDLE
       .new dwBytesReturned:DWORD
       .new szDriveName[7]:TCHAR ;; holds \\.\X: plus NULL.
       .new volinfo:VOLUME_GET_GPT_ATTRIBUTES_INFORMATION
       .new partinfo:PARTITION_INFORMATION
        _tcsncpy_s(&szDriveName, _countof(szDriveName), "\\\\.\\", _TRUNCATE)
        _tcsncat_s(&szDriveName, _countof(szDriveName), &szDriveLetter, _TRUNCATE)
        mov hDevice,CreateFile(&szDriveName, GENERIC_READ, FILE_SHARE_READ or FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL)
        .if hDevice != INVALID_HANDLE_VALUE

            .ifd !DeviceIoControl( hDevice, IOCTL_DISK_GET_PARTITION_INFO, NULL, 0,
                    &partinfo, sizeof(partinfo), &dwBytesReturned, NULL )
                mov partinfo.PartitionType,PARTITION_ENTRY_UNUSED
            .endif
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
            DefineDosDevice(DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
                    &szDriveLetter, pszDeviceName)
            .return FALSE
        .endif

        .if IsPartitionHidden(partinfo.PartitionType, volinfo.GptAttributes)

            ;; remove the drive letter we created, let caller know what happened.

            DefineDosDevice(
                DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
                &szDriveLetter, pszDeviceName )
            SetLastError(PRIV_ERROR_PARTITION_HIDDEN)
            .return FALSE
        .endif

        .if ( IsRecognizedPartition( partinfo.PartitionType ) ||
                partinfo.PartitionType == PARTITION_LDM ||
                partinfo.PartitionType == PARTITION_ENTRY_UNUSED )

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

        DefineDosDevice(
            DDD_RAW_TARGET_PATH or DDD_REMOVE_DEFINITION or DDD_EXACT_MATCH_ON_REMOVE,
            &szDriveLetter, pszDeviceName )
        SetLastError(PRIV_ERROR_PARTITION_NOT_RECOGNIZED)
        mov eax,FALSE
    .endif
    ret
    endp


RemovePersistentDriveLetter proc WINAPI pszDriveLetter:LPCTSTR

   local szDriveLetterAndSlash[4]:TCHAR

    .if lstrlen(pszDriveLetter)
        IsDriveLetter(pszDriveLetter)
    .endif
    .if !eax
        SetLastError(ERROR_INVALID_PARAMETER)
       .return FALSE
    .endif
    mov rcx,pszDriveLetter
    mov szDriveLetterAndSlash[TCHAR*0],[rcx]
    mov szDriveLetterAndSlash[TCHAR*1],':'
    mov szDriveLetterAndSlash[TCHAR*2],'\'
    mov szDriveLetterAndSlash[TCHAR*3],0
    DeleteVolumeMountPoint(&szDriveLetterAndSlash)
    ret
    endp


AssignTemporaryDriveLetter proc WINAPI pszDriveLetter:LPCTSTR, pszDeviceName:LPCTSTR

   local szDevice[MAX_PATH]:TCHAR
   local szDriveLetter[3]:TCHAR
   local fResult:BOOL

    .ifd lstrlen(pszDriveLetter)
        .ifd lstrlen(pszDeviceName)
            IsDriveLetter(pszDriveLetter)
        .endif
    .endif
    .if !eax
        SetLastError(ERROR_INVALID_PARAMETER)
       .return FALSE
    .endif
    mov rcx,pszDriveLetter
    mov szDriveLetter[TCHAR*0],[rcx]
    mov szDriveLetter[TCHAR*1],':'
    mov szDriveLetter[TCHAR*2],0

    .ifd !QueryDosDevice( &szDriveLetter, &szDevice, MAX_PATH )

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
    endp


RemoveTemporaryDriveLetter proc WINAPI pszDriveLetter:LPCTSTR

    local szDriveLetter[3]:TCHAR
    local szDeviceName[MAX_PATH]:TCHAR

    .ifd lstrlen(pszDriveLetter)
        IsDriveLetter(pszDriveLetter)
    .endif
    .if !eax
        SetLastError(ERROR_INVALID_PARAMETER)
        .return FALSE
    .endif
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
    endp


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
    endp


IsDriveLetter proc WINAPI pszDriveLetter:LPCTSTR
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
    endp


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
    VerifyVersionInfo(&osvi, VER_MAJORVERSION or VER_MINORVERSION, comparisonMask)
    ret
    endp

    end _tstart
