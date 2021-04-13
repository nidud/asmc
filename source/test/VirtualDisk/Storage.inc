define WINVER 0x0602 ; Windows 8.0
define _WIN32_WINNT 0x0602

include windows.inc
include stdio.inc
include stdlib.inc
include virtdisk.inc
include Shlwapi.inc
include rpc.inc
include sddl.inc
include tchar.inc

SampleAddVirtualDiskParent proto \
    VirtualDiskPath: LPCWSTR,
    ParentPath: LPCWSTR

SampleGetVirtualDiskInformation proto \
    VirtualDiskPath: LPCWSTR

SampleCreateVirtualDisk proto \
    VirtualDiskPath: LPCWSTR,
    ParentPath: LPCWSTR,
    Flags: CREATE_VIRTUAL_DISK_FLAG,
    FileSize: ULONGLONG,
    BlockSize: DWORD,
    LogicalSectorSize: DWORD,
    PhysicalSectorSize: DWORD

SampleSetVirtualDiskInformation proto \
    ChildPath: LPCWSTR,
    ParentPath: LPCWSTR,
    PhysicalSectorSize: DWORD

SampleAttachVirtualDisk proto \
    VirtualDiskPath: LPCWSTR,
    ReadOnly: BOOLEAN

SampleDetachVirtualDisk proto \
    VirtualDiskPath: LPCWSTR

SampleMergeVirtualDisk proto \
    VirtualDiskPath: LPCWSTR

SampleCompactVirtualDisk proto \
    VirtualDiskPath: LPCWSTR

SampleResizeVirtualDisk proto \
    VirtualDiskPath: LPCWSTR,
    FileSize: ULONGLONG

SampleMirrorVirtualDisk proto \
    SourcePath: LPCWSTR,
    DestinationPath: LPCWSTR

SampleRawIO proto \
    SourcePath: LPCWSTR,
    DestinationPath: LPCWSTR

SampleSetUserMetaData proto \
    VHDPath: LPCWSTR,
    ID: DWORD

SampleGetUserMetaData proto \
    VHDPath: LPCWSTR

SampleDeleteUserMetaData proto \
    VHDPath: LPCWSTR

SampleEnumerateUserMetaData proto \
    VHDPath: LPCWSTR

SampleGetStorageDependencyInformation proto \
    Disk: LPCWSTR

SampleGetAllAttachedVirtualDiskPhysicalPaths proto
