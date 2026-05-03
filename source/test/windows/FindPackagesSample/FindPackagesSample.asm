
include windows.inc
include windows.management.deployment.inc
include sddl.inc
include roapi.inc
include iostream
include tchar.inc

ifdef _LIBCMT
.pragma comment(linker,"/defaultlib:libcmtd")
.pragma comment(linker,"/defaultlib:\asmc\lib\x64\combase")
endif

.code

DisplayHString proc name:ptr wchar_t, hstring:HSTRING, hr:HRESULT

    .if (SUCCEEDED(hr))

       .new length:UINT32
       .new string:ptr wchar_t = WindowsGetStringRawBuffer(hstring, &length)
        wcout << name << string << endl
    .endif
    ret

DisplayHString endp

DisplayPackageInfo proc Package:ptr Windows::ApplicationModel::IPackage

   .new hstring:HSTRING
   .new version:Windows::ApplicationModel::PackageVersion
   .new PackageId:ptr Windows::ApplicationModel::IPackageId = nullptr
   .new isFramework:bool
   .new StorageFolder:ptr Windows::Storage::IStorageFolder

    .if (SUCCEEDED(Package.get_Id(&PackageId)))

        DisplayHString("Name: ", hstring, PackageId.get_Name(&hstring))
        DisplayHString("FullName: ", hstring, PackageId.get_FullName(&hstring))

        .if (SUCCEEDED(PackageId.get_Version(&version)))

            wcout << "Version: " << version.Major << "." << version.Minor
            wcout << "." << version.Build << "." << version.Revision << endl
        .endif

        DisplayHString("Publisher: ", hstring, PackageId.get_Publisher(&hstring))
        DisplayHString("PublisherId: ", hstring, PackageId.get_PublisherId(&hstring))

        .if (SUCCEEDED(Package.get_InstalledLocation(&StorageFolder)))

            .new pItem:ptr Windows::Storage::IStorageItem
            .new ItemGUI:GUID = {
                0x4207A996,0xCA2F,0x42F7,{0xBD,0xE8,0x8B,0x10,0x45,0x7A,0x7F,0x30}
                }

            .if (SUCCEEDED(StorageFolder.QueryInterface(&ItemGUI, &pItem)))

                DisplayHString("Location: ", hstring, pItem.get_Path(&hstring))
            .endif
        .endif

        .if (SUCCEEDED(Package.get_IsFramework(&isFramework)))

            wcout << "IsFramework: " << isFramework << endl
        .endif
    .endif
    ret

DisplayPackageInfo endp

SidToAccountName proc sidString:LPWSTR, stringSid:LPWSTR

    .new sid:PSID = nullptr
    .new name[256]:wchar_t
    .new domainName[256]:wchar_t

    .if ( ConvertStringSidToSid(sidString, &sid) )

       .new nameCharCount:DWORD = 0
       .new domainNameCharCount:DWORD = 0
       .new sidType:SID_NAME_USE

        ; determine how much space is required to store the name and domainName

        LookupAccountSid(nullptr, sid, nullptr, &nameCharCount,
                nullptr, &domainNameCharCount, &sidType)

        mov edx,nameCharCount
        inc edx
        shl edx,1
        ZeroMemory(&name, edx)

        mov edx,domainNameCharCount
        inc edx
        shl edx,1
        ZeroMemory(&domainName, edx)

        .if ( LookupAccountSid(nullptr, sid, &name, &nameCharCount,
                &domainName, &domainNameCharCount, &sidType) )

            wcscpy(stringSid, &domainName)
            wcscat(stringSid, "\\")
            wcscat(stringSid, &name)
        .endif
        LocalFree(sid)
    .endif

    .if (wcslen(stringSid) == 0)
        .return sidString
    .endif
    .return stringSid

SidToAccountName endp

DisplayPackageUsers proc \
        packageManager: ptr Windows::Management::Deployment::IPackageManager,
        package:        ptr Windows::ApplicationModel::IPackage

   .new hstring:HSTRING
   .new Iterator:ptr __FIIterator_1_Windows__CManagement__CDeployment__CPackageUserInformation = nullptr
   .new Iterable:ptr __FIIterable_1_Windows__CManagement__CDeployment__CPackageUserInformation = nullptr
   .new PackageId:ptr Windows::ApplicationModel::IPackageId = nullptr
   .new hr:HRESULT = package.get_Id(&PackageId)
   .new UserName[256]:wchar_t

    .if (SUCCEEDED(hr))
        mov hr,PackageId.get_FullName(&hstring)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,packageManager.FindUsers(hstring, &Iterable)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,Iterable.First(&Iterator)
    .endif
    .if (SUCCEEDED(hr))

       .new hasCurrent:bool = false
       .new hasNext:bool = false
       .new userInformation:ptr Windows::Management::Deployment::IPackageUserInformation

        wcout << "Users: "

        .while 1

            .if (SUCCEEDED(Iterator.get_HasCurrent(&hasCurrent)))

                .if ( hasCurrent )

                    .if (SUCCEEDED(Iterator.get_Current(&userInformation)))

                        .if (SUCCEEDED(userInformation.get_UserSecurityId(&hstring)))

                           .new string:ptr wchar_t
                           .new length:UINT32
                            mov string,SidToAccountName(
                                    WindowsGetStringRawBuffer(hstring, &length),
                                    &UserName)

                            wcout << string << " "
                        .endif
                    .endif
                .endif
            .endif
            .break .if (FAILED(Iterator.MoveNext(&hasNext)))
            .break .if (hasNext == false)
        .endw

        wcout << endl
    .endif
    ret

DisplayPackageUsers endp

wmain proc

    wcout << "Copyright (C) The Asmc Contributors. All Rights Reserved." << endl
    wcout << "FindPackages sample" << endl << endl

   .new hr:HRESULT = CoInitializeEx(nullptr, COINIT_MULTITHREADED)

    .if (SUCCEEDED(hr))

       .new activationFactory:ptr IActivationFactory = nullptr
       .new activationGUI:GUID = {
                0x00000035,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
       .new activationUri:HSTRING = nullptr
        mov hr,WindowsCreateString(RuntimeClass_Windows_Management_Deployment_PackageManager,
                lengthof(@CStr(-1))-1, &activationUri)
        .if (SUCCEEDED(hr))
            mov hr,RoGetActivationFactory(activationUri, &activationGUI, &activationFactory)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,activationFactory.ActivateInstance(&activationFactory)
        .endif
        .if (SUCCEEDED(hr))

            .new packageManager:ptr Windows::Management::Deployment::IPackageManager = nullptr
            .new managerGUI:GUID = {
                    0x9A7D4B65,0x5E8F,0x4FC7,{0xA2,0xE5,0x7F,0x69,0x25,0xCB,0x8B,0x53}}
            mov hr,activationFactory.QueryInterface(&managerGUI, &packageManager)
        .endif
        .if (SUCCEEDED(hr))

           .new Packages:ptr __FIIterable_1_Windows__CApplicationModel__CPackage = nullptr
            mov hr,packageManager.FindPackages(&Packages)
        .endif
        .if (SUCCEEDED(hr))

           .new Iterator:ptr __FIIterator_1_Windows__CApplicationModel__CPackage
            mov hr,Packages.First(&Iterator)
        .endif
        .if (SUCCEEDED(hr))

           .new hasCurrent:bool = false
           .new hasNext:bool = false
           .new packageCount:int_t = 0
           .new Package:ptr Windows::ApplicationModel::IPackage

            .while 1

                .if (SUCCEEDED(Iterator.get_HasCurrent(&hasCurrent)))

                    .if ( hasCurrent )

                        .if (SUCCEEDED(Iterator.get_Current(&Package)))

                            inc packageCount

                            DisplayPackageInfo(Package)
                            DisplayPackageUsers(packageManager, Package)

                            wcout << endl
                        .endif
                    .endif
                .endif
                .break .if (FAILED(Iterator.MoveNext(&hasNext)))
                .break .if (hasNext == false)
            .endw

            Iterator.Release()
            Packages.Release()

            wcout << "Package Count: " << packageCount << endl
        .endif

        packageManager.Release()
        activationFactory.Release()
    .endif
    .if (FAILED(hr))

       .new szMessage:ptr wchar_t
        mov edx,hr
        .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)

            mov hr,HRESULT_CODE(edx)
        .endif

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER or \
            FORMAT_MESSAGE_FROM_SYSTEM or \
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &szMessage,
            0,
            NULL)

        wcout << "FindPackagesSample failed, error: " << szMessage << endl
        LocalFree(szMessage)
    .endif
    CoUninitialize()
   .return 0

wmain endp

    end _tstart
