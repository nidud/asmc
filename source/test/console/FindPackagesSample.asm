
include windows.inc
include winrt/windows.management.deployment.inc
include sddl.inc
include winrt/roapi.inc
include iostream
include tchar.inc

ifdef _LIBCMT
.pragma comment(linker,"/defaultlib:libcmtd")
.pragma comment(linker,"/defaultlib:\asmc\lib\x64\combase")
endif

.data
 DECLARE_IID(IStorageItem)
 DECLARE_IID(IActivationFactory)
 DECLARE_IID(IPackageManager)

.code

DisplayHString proc name:ptr wchar_t, hstring:HSTRING, hr:HRESULT
    .if (SUCCEEDED(hr))
       .new length:UINT32
       .new string:ptr wchar_t = WindowsGetStringRawBuffer(hstring, &length)
        wcout << name << string << endl
    .endif
    ret
    endp

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
            .if (SUCCEEDED(StorageFolder.QueryInterface(&IID_IStorageItem, &pItem)))
                DisplayHString("Location: ", hstring, pItem.get_Path(&hstring))
            .endif
        .endif
        .if (SUCCEEDED(Package.get_IsFramework(&isFramework)))
            wcout << "IsFramework: " << isFramework << endl
        .endif
    .endif
    ret
    endp

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
    endp

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
    endp

_tmain proc
    wcout << "Copyright (C) The Asmc Contributors. All Rights Reserved." << endl
    wcout << "FindPackages sample" << endl << endl
   .new hr:HRESULT = CoInitializeEx(nullptr, COINIT_MULTITHREADED)
    .if (SUCCEEDED(hr))
       .new activationFactory:ptr IActivationFactory = nullptr
       .new activationUri:HSTRING = nullptr
       .new uriString:LPTSTR = RuntimeClass_Windows_Management_Deployment_PackageManager
       .new uriStrLen:size_t = _tcslen(uriString)
        mov hr,WindowsCreateString(uriString, uriStrLen, &activationUri)
        .if (SUCCEEDED(hr))
            mov hr,RoGetActivationFactory(activationUri, &IID_IActivationFactory, &activationFactory)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,activationFactory.ActivateInstance(&activationFactory)
        .endif
        .if (SUCCEEDED(hr))
            .new packageManager:ptr Windows::Management::Deployment::IPackageManager = nullptr
            mov hr,activationFactory.QueryInterface(&IID_IPackageManager, &packageManager)
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
    endp

    end _tstart
