
ifdef _LIBCMT
.pragma comment(linker,"/defaultlib:libcmtd")
.pragma comment(linker,"/defaultlib:\asmc\lib\x64\combase")
.pragma comment(linker,"/defaultlib:legacy_stdio_definitions")
endif

include windows.inc
include objbase.inc
include roapi.inc
include iostream
include windows.management.deployment.inc
include tchar.inc

define nullptr 0

option dllimport:none

.comdef ProgressHandler : public IUnknown

    m_refCount      int_t ?
    m_pEvent        ptr HANDLE ?
    m_pStatus       ptr AsyncStatus ?

    ProgressHandler proc :ptr HANDLE, :ptr AsyncStatus
    IInvoke         proc :ptr IAsyncActionWithProgress, :AsyncStatus
   .ends

   .code

wmain proc argc:int_t, argv:ptr wstring_t

    wcout << "Copyright (C) The Asmc Contributors. All Rights Reserved." << endl
    wcout << "AddPackage sample" << endl << endl

    .if ( argc < 2 )

        wcout << "Usage: AddPackageSample.exe packageUri" << endl
        .return 1
    .endif

    mov rdx,argv
    mov rax,[rdx+size_t]

   .new inputUri:ptr wchar_t = rax
   .new returnValue:int_t = 0
   .new hr:HRESULT = CoInitializeEx(nullptr, COINIT_MULTITHREADED)

    .if (SUCCEEDED(hr))

        .new completedEvent:HANDLE = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS)
        .if ( completedEvent == nullptr )
            wcout << "CreateEvent Failed, error code=" << GetLastError() << endl
            mov returnValue,1
        .else
            .new factoryGUI:GUID = {0x44A9796F,0x723E,0x4FDF,{0xA2,0x18,0x03,0x3E,0x75,0xB0,0xC0,0x84}}
            .new inputPackageUri:HSTRING = nullptr
            .new foundationUri:HSTRING = nullptr
            mov hr,WindowsCreateString(RuntimeClass_Windows_Foundation_Uri, lengthof(@CStr(-1))-1, &foundationUri)
            .if (SUCCEEDED(hr))
                mov hr,WindowsCreateString(inputUri, wcslen(inputUri), &inputPackageUri)
            .endif
            .if (SUCCEEDED(hr))
               .new classFactory:ptr Windows::Foundation::IUriRuntimeClassFactory = nullptr
                mov hr,RoGetActivationFactory(foundationUri, &factoryGUI, &classFactory)
            .endif
            .if (SUCCEEDED(hr))
               .new packageUri:ptr Windows::Foundation::IUriRuntimeClass = nullptr
                mov hr,classFactory.CreateUri(inputPackageUri, &packageUri)
            .endif
            .if (SUCCEEDED(hr))

               .new activationFactory:ptr IActivationFactory
               .new activationGUI:GUID = {0x00000035,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
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
                  .new managerGUI:GUID = {0x9A7D4B65,0x5E8F,0x4FC7,{0xA2,0xE5,0x7F,0x69,0x25,0xCB,0x8B,0x53}}
                   mov hr,activationFactory.QueryInterface(&managerGUI, &packageManager)
                .endif
            .endif

            .if (SUCCEEDED(hr))

               .new deploymentOperation:ptr __FIAsyncOperationWithProgress_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress = nullptr
                mov hr,packageManager.AddPackageAsync(packageUri, nullptr,
                        Windows::Management::Deployment::DeploymentOptions::None, &deploymentOperation)
            .endif

            .if (SUCCEEDED(hr))
               .new Status:AsyncStatus = 0
               .new progressHandler:ptr ProgressHandler(&completedEvent, &Status)
                mov hr,deploymentOperation.put_Completed(progressHandler)
            .endif

            .if (SUCCEEDED(hr))

                wcout << "Installing package " << inputUri << endl
                wcout << "Waiting for installation to complete..." << endl
                WaitForSingleObject(completedEvent, INFINITE)
                .if (Status == AsyncStatus_Error)

                   .new errorMsg:wstring_t = "Unknown"
                   .new errorCode:int_t = 0
                   .new deploymentResult:ptr Windows::Management::Deployment::IDeploymentResult = nullptr
                    mov hr,deploymentOperation.GetResults(&deploymentResult)
                    .if (SUCCEEDED(hr))

                        .new errorText:HSTRING = nullptr
                        .new length:UINT32
                        .if (SUCCEEDED(deploymentResult.get_ErrorText(&errorText)))
                            mov errorMsg,WindowsGetStringRawBuffer(errorText, &length)
                        .endif
                        deploymentResult.get_ExtendedErrorCode(&errorCode)
                    .endif
                    wcout << "Installation Error: " << errorCode << endl
                    wcout << "Detailed Error Text: " << errorMsg << endl
                .elseif (Status == AsyncStatus_Canceled)
                    wcout << "Installation Canceled" << endl
                .elseif (Status == AsyncStatus_Completed)
                    wcout << "Installation succeeded!" << endl
                .endif
            .endif
        .endif
    .endif
    .if (FAILED(hr))
        wcout << "AddPackageSample failed, error: " << GetLastError() << endl
        mov returnValue,1
    .endif
    .if (completedEvent != nullptr)
        CloseHandle(completedEvent)
    .endif
    CoUninitialize()
    .return returnValue
    endp


ProgressHandler::QueryInterface proc
    .return E_NOINTERFACE
    endp

   assume class:rbx

ProgressHandler::AddRef proc
    .return InterlockedIncrement(&m_refCount)
    endp

ProgressHandler::Release proc
    .if ( InterlockedDecrement(&m_refCount) == 0 )
        free(rbx)
        xor eax,eax
    .endif
    ret
    endp

ProgressHandler::IInvoke proc asyncInfo:ptr IAsyncActionWithProgress, status:AsyncStatus
    mov rax,m_pStatus
    mov [rax],r8d
    .if ( r8d >= AsyncStatus_Completed )
        mov rcx,m_pEvent
        SetEvent([rcx])
    .endif
    mov eax,S_OK
    ret
    endp

ProgressHandler::ProgressHandler proc pEvent:ptr HANDLE, pStatus:ptr AsyncStatus
    mov rbx,@ComAlloc(ProgressHandler)
    mov rdx,pStatus
    mov m_pStatus,rdx
    mov rdx,pEvent
    mov m_pEvent,rdx
    ret
    endp

    end _tstart
