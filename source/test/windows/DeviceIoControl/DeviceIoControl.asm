; DEVICEIOCONTROL.ASM--
;
; https://docs.microsoft.com/en-us/windows/win32/devio/calling-deviceiocontrol
;
; The code of interest is in the subroutine GetDriveGeometry. The
; code in main shows how to interpret the results of the call.
;
include windows.inc
include winioctl.inc
include stdio.inc
include tchar.inc

define wszDrive <L"\\\\.\\PhysicalDrive0">

.code

GetDriveGeometry proc wszPath:LPWSTR, pdg:ptr DISK_GEOMETRY

   .new hDevice:HANDLE = INVALID_HANDLE_VALUE    ; handle to the drive to be examined
   .new bResult:BOOL   = FALSE                   ; results flag
   .new junk:DWORD     = 0                       ; discard results

    mov hDevice,CreateFileW(wszPath,              ; drive to open
                            0,                    ; no access to the drive
                            FILE_SHARE_READ or FILE_SHARE_WRITE,
                            NULL,                 ; default security attributes
                            OPEN_EXISTING,        ; disposition
                            0,                    ; file attributes
                            NULL)                 ; do not copy file attributes

    .if ( hDevice == INVALID_HANDLE_VALUE )       ; cannot open the drive
        .return(FALSE)
    .endif
    mov bResult,DeviceIoControl(hDevice,                       ; device to be queried
                                IOCTL_DISK_GET_DRIVE_GEOMETRY, ; operation to perform
                                NULL, 0,                       ; no input buffer
                                pdg, sizeof(DISK_GEOMETRY),    ; output buffer
                                &junk,                         ; # bytes returned
                                NULL)                          ; synchronous I/O
    CloseHandle(hDevice)
    .return(bResult)
    endp


wmain proc

   .new pdg:DISK_GEOMETRY = {0}  ; disk drive geometry structure
   .new bResult:BOOL = FALSE     ; generic results flag
   .new DiskSize:ULONGLONG = 0   ; size of the drive, in bytes

    mov bResult,GetDriveGeometry(wszDrive, &pdg)

    .if (bResult)

        wprintf(L"Drive path      = %ws\n",   wszDrive)
        wprintf(L"Cylinders       = %I64d\n", pdg.Cylinders)
        wprintf(L"Tracks/cylinder = %ld\n",   pdg.TracksPerCylinder)
        wprintf(L"Sectors/track   = %ld\n",   pdg.SectorsPerTrack)
        wprintf(L"Bytes/sector    = %ld\n",   pdg.BytesPerSector)
        mov eax,pdg.TracksPerCylinder
        mul pdg.SectorsPerTrack
        mul pdg.BytesPerSector
        mul pdg.Cylinders.QuadPart
        mov DiskSize,rax
        mov rcx,1024 * 1024 * 1024
        div rcx
        cvtsi2sd xmm2,rax
        movq rax,xmm2
        wprintf(L"Disk size       = %I64d (Bytes)\n"
                 "                = %.2f (Gb)\n",
                DiskSize, rax)
    .else
        wprintf(L"GetDriveGeometry failed. Error %ld.\n", GetLastError())
    .endif
    .return(bResult)
    endp

    end _tstart
