
include Storage.inc

.data

VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN GUID {
    0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }

.code

ShowUsage proto \
    ModuleName: PWCHAR

wmain proc uses rsi argc:int_t, argv:ptr ptr WCHAR

    .new rc:DWORD=1

    mov rsi,argv

    .if (argc == 2)

        .if (_wcsicmp([rsi+size_t], L"GetAllAttachedVirtualDiskPhysicalPaths") == 0)

            mov rc,SampleGetAllAttachedVirtualDiskPhysicalPaths()

        .else

            ShowUsage([rsi])
        .endif

    .elseif (argc == 3)

        .if (_wcsicmp([rsi+size_t], L"GetVirtualDiskInformation") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2]

            mov rc,SampleGetVirtualDiskInformation(virtualDiskPath)

        .elseif (_wcsicmp([rsi+size_t], L"DetachVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];

            mov rc,SampleDetachVirtualDisk(
                    virtualDiskPath)

        .elseif (_wcsicmp([rsi+size_t], L"MergeVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];

            mov rc,SampleMergeVirtualDisk(
                    virtualDiskPath)

        .elseif (_wcsicmp([rsi+size_t], L"CompactVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];

            mov rc,SampleCompactVirtualDisk(
                    virtualDiskPath)

        .elseif (_wcsicmp([rsi+size_t], L"EnumerateUserMetaData") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];

            mov rc,SampleEnumerateUserMetaData(
                    virtualDiskPath)

        .elseif (_wcsicmp([rsi+size_t], L"GetUserMetaData") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];

            mov rc,SampleGetUserMetaData(
                    virtualDiskPath)

        .elseif (_wcsicmp([rsi+size_t], L"DeleteUserMetaData") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];

            mov rc,SampleDeleteUserMetaData(
                    virtualDiskPath)

        .elseif (_wcsicmp([rsi+size_t], L"GetStorageDependencyInformation") == 0)

            .new Disk:LPCWSTR = [rsi+size_t*2]

            mov rc,SampleGetStorageDependencyInformation(
                    Disk)

        .else

            ShowUsage([rsi])
        .endif

    .elseif (argc == 4)

        .if (_wcsicmp([rsi+size_t], L"AttachVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];
            .new readOnly:LPCWSTR = [rsi+size_t*3];

            xor edx,edx
            .if byte ptr [rax] == 't' || byte ptr [rax] == 'T'
                inc edx
            .endif

            mov rc,SampleAttachVirtualDisk(
                    virtualDiskPath,
                    dl)

        .elseif (_wcsicmp([rsi+size_t*1], L"MirrorVirtualDisk") == 0)

            .new sourcePath:LPCWSTR = [rsi+size_t*2];
            .new destinationPath:LPCWSTR = [rsi+size_t*3];

            mov rc,SampleMirrorVirtualDisk(
                    sourcePath,
                    destinationPath)

        .elseif (_wcsicmp([rsi+size_t], L"CreateDifferencingVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];
            .new parentPath:LPCWSTR = [rsi+size_t*3];

            mov rc,SampleCreateVirtualDisk(
                    virtualDiskPath,
                    parentPath,
                    CREATE_VIRTUAL_DISK_FLAG_NONE,
                    0,
                    0,
                    0,
                    0)

        .elseif (_wcsicmp([rsi+size_t], L"RawIO") == 0)

            .new sourcePath:LPCWSTR = [rsi+size_t*2];
            .new destinationPath:LPCWSTR = [rsi+size_t*3];

            mov rc,SampleRawIO(
                    sourcePath,
                    destinationPath)

        .elseif (_wcsicmp([rsi+size_t*1], L"ResizeVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];
            .new fileSize:ULONGLONG = _wtoi64([rsi+size_t*3])


            mov rc,SampleResizeVirtualDisk(
                    virtualDiskPath,
                    fileSize)

        .elseif (_wcsicmp([rsi+size_t], L"SetUserMetaData") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];
            .new ID:DWORD = _wtoi([rsi+size_t*3])

            mov rc,SampleSetUserMetaData(
                    virtualDiskPath,
                    ID)

        .elseif (_wcsicmp([rsi+size_t], L"AddVirtualDiskParent") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];
            .new parentPath:LPCWSTR = [rsi+size_t*3];

            mov rc,SampleAddVirtualDiskParent(
                    virtualDiskPath,
                    parentPath)

        .else

            ShowUsage([rsi])
        .endif

    .elseif (argc == 5)

        .if (_wcsicmp([rsi+size_t], L"SetVirtualDiskInformation") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];
            .new parentPath:LPCWSTR = [rsi+size_t*3];
            .new physicalSectorSize:DWORD = _wtoi([rsi+size_t*4])

            mov rc,SampleSetVirtualDiskInformation(
                    virtualDiskPath,
                    parentPath,
                    physicalSectorSize)

        .else

            ShowUsage([rsi])
        .endif

    .elseif (argc == 7)

        .if (_wcsicmp([rsi+size_t], L"CreateFixedVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2]
            .new parentPath:LPCWSTR = NULL

            .new fileSize:ULONGLONG = _wtoi64([rsi+size_t*3])
            .new blockSize:DWORD = _wtoi([rsi+size_t*4])
            .new logicalSectorSize:DWORD = _wtoi([rsi+size_t*5])
            .new physicalSectorSize:DWORD = _wtoi([rsi+size_t*6])

            mov rc,SampleCreateVirtualDisk(
                    virtualDiskPath,
                    parentPath,
                    CREATE_VIRTUAL_DISK_FLAG_FULL_PHYSICAL_ALLOCATION,
                    fileSize,
                    blockSize,
                    logicalSectorSize,
                    physicalSectorSize)

        .elseif (_wcsicmp([rsi+size_t], L"CreateDynamicVirtualDisk") == 0)

            .new virtualDiskPath:LPCWSTR = [rsi+size_t*2];
            .new parentPath:LPCWSTR = NULL;

            .new fileSize:ULONGLONG = _wtoi64([rsi+size_t*3])
            .new blockSize:DWORD = _wtoi([rsi+size_t*4])
            .new logicalSectorSize:DWORD = _wtoi([rsi+size_t*5])
            .new physicalSectorSize:DWORD = _wtoi([rsi+size_t*6])

            mov rc,SampleCreateVirtualDisk(
                    virtualDiskPath,
                    parentPath,
                    CREATE_VIRTUAL_DISK_FLAG_NONE,
                    fileSize,
                    blockSize,
                    logicalSectorSize,
                    physicalSectorSize)

        .else

            ShowUsage([rsi])
        .endif

    .else

        ShowUsage(L"")
    .endif

    .return rc

wmain endp


ShowUsage proc \
    ModuleName: PWCHAR

    wprintf(L"\nUsage:\t%s <SampleName> <Arguments>\n", ModuleName)

    wprintf(L"Supported SampleNames and Arguments:\n")
    wprintf(L"   GetVirtualDiskInformation <path>\n")
    wprintf(L"   CreateFixedVirtualDisk <path> <file size> <block size> <logical sector size> <physical sector size>\n")
    wprintf(L"   CreateDynamicVirtualDisk <path> <file size> <block size> <logical sector size> <physical sector size>\n")
    wprintf(L"   CreateDifferencingVirtualDisk <path> <parent path>\n")
    wprintf(L"   AttachVirtualDisk <path> <readonly>\n")
    wprintf(L"   DetachVirtualDisk <path>\n")
    wprintf(L"   SetVirtualDiskInformation <child> <parent> <physical sector size>\n")
    wprintf(L"   MergeVirtualDisk <path>\n")
    wprintf(L"   CompactVirtualDisk <path>\n")
    wprintf(L"   ResizeVirtualDisk <path> 2147483648\n")
    wprintf(L"   MirrorVirtualDisk <source> <destination>\n")
    wprintf(L"   RawIO <source> <destination>\n")
    wprintf(L"   EnumerateUserMetaData <path>\n")
    wprintf(L"   SetUserMetaData <path> <metadata int>\n")
    wprintf(L"   GetUserMetaData <path>\n")
    wprintf(L"   DeleteUserMetaData <path>\n")
    wprintf(L"   AddVirtualDiskParent <path> <parent path>\n")
    wprintf(L"   GetStorageDependencyInformation [<volume> | <disk>]\n")
    wprintf(L"   GetAllAttachedVirtualDiskPhysicalPaths\n")


    wprintf(L"\nExamples:\n")
    wprintf(L"   %s GetVirtualDiskInformation c:\\fixed.vhd\n", ModuleName)
    wprintf(L"   %s CreateFixedVirtualDisk c:\\fixed.vhd 1073741824 0 0 0\n", ModuleName)
    wprintf(L"   %s CreateDynamicVirtualDisk c:\\dynamic.vhdx 1073741824 0 0 0\n", ModuleName)
    wprintf(L"   %s CreateDifferencingVirtualDisk c:\\diff.vhdx c:\\dynamic.vhdx\n", ModuleName)
    wprintf(L"   %s AttachVirtualDisk c:\\fixed.vhd true\n", ModuleName)
    wprintf(L"   %s DetachVirtualDisk c:\\fixed.vhd\n", ModuleName)
    wprintf(L"   %s SetVirtualDiskInformation c:\\diff.vhd c:\\fixed.vhd 4096\n", ModuleName)
    wprintf(L"   %s MergeVirtualDisk c:\\diff.vhd\n", ModuleName)
    wprintf(L"   %s CompactVirtualDisk c:\\dynamic.vhd\n", ModuleName)
    wprintf(L"   %s ResizeVirtualDisk c:\\dynamic.vhd 2147483648\n", ModuleName)
    wprintf(L"   %s MirrorVirtualDisk c:\\fixed.vhd c:\\fixed2.vhd\n", ModuleName)
    wprintf(L"   %s RawIO c:\\source.vhdx c:\\destination.vhdx\n", ModuleName)
    wprintf(L"   %s EnumerateUserMetaData c:\\fixed.vhdx\n", ModuleName)
    wprintf(L"   %s SetUserMetaData c:\\fixed.vhdx 1234\n", ModuleName)
    wprintf(L"   %s GetUserMetaData c:\\fixed.vhdx\n", ModuleName)
    wprintf(L"   %s DeleteUserMetaData c:\\fixed.vhdx\n", ModuleName)
    wprintf(L"   %s AddVirtualDiskParent c:\\diff.vhdx c:\\dynamic.vhdx\n", ModuleName)
    wprintf(L"   %s GetStorageDependencyInformation C:\n", ModuleName)
    wprintf(L"   %s GetAllAttachedVirtualDiskPhysicalPaths\n", ModuleName)

    wprintf(L"\n\n")
    ret

ShowUsage endp

    end

