
define STRICT_TYPED_ITEMIDS     1

include windows.inc             ; Standard include
include Shellapi.inc            ; Included for shell constants such as FO_* values
include shlobj.inc              ; Required for necessary shell dependencies
include strsafe.inc             ; Including StringCch* helpers

define c_szSampleFileName       <"SampleFile">
define c_szSampleFileNewname    <"NewName">
define c_szSampleFileExt        <"txt">
define c_szSampleSrcDir         <"FileOpSampleSource">
define c_szSampleDstDir         <"FileOpSampleDestination">
define c_cMaxFilesToCreate      10

.code

CreateAndInitializeFileOperation proc riid:REFIID, ppv:ptr ptr

  local hr:HRESULT
  local pfo:ptr IFileOperation

    xor eax,eax
    mov [rdx],rax

    ; Create the IFileOperation object

    mov hr,CoCreateInstance(&CLSID_FileOperation, NULL, CLSCTX_ALL, &IID_IFileOperation, &pfo)
    .if (SUCCEEDED(hr))

        ; Set the operation flags.  Turn off  all UI
        ; from being shown to the user during the
        ; operation.  This includes error, confirmation
        ; and progress dialogs.

        mov hr,pfo.SetOperationFlags(FOF_NO_UI)
        .if (SUCCEEDED(hr))

            mov hr,pfo.QueryInterface(riid, ppv)
        .endif
        pfo.Release();
    .endif
    mov eax,hr
    ret

CreateAndInitializeFileOperation endp

;
;  Synopsis:  Create the source and destination folders for the sample
;
;  Arguments: psiSampleRoot  - Item of the parent folder where the sample folders will be created
;             ppsiSampleSrc  - On success contains the source folder item to be used for sample operations
;             ppsiSampleDst  - On success contains the destination folder item to be used for sample operations
;
;  Returns:   S_OK if successful
;
CreateSampleFolders proc psiSampleRoot:ptr IShellItem,
     ppsiSampleSrc:ptr ptr IShellItem, ppsiSampleDst:ptr ptr IShellItem

  local hr:HRESULT
  local pfo:ptr IFileOperation
  local psiSrc:ptr IShellItem
  local psiDst:ptr IShellItem

    xor eax,eax
    mov [rdx],rax
    mov [r8],rax
    mov psiSrc,rax
    mov psiDst,rax

    mov hr,CreateAndInitializeFileOperation(&IID_IFileOperation, &pfo)
    .if (SUCCEEDED(hr))

        ; Use the file operation to create a source and destination folder

        mov hr,pfo.NewItem(psiSampleRoot, FILE_ATTRIBUTE_DIRECTORY, c_szSampleSrcDir, NULL, NULL)
        .if (SUCCEEDED(hr))

            mov hr,pfo.NewItem(psiSampleRoot, FILE_ATTRIBUTE_DIRECTORY, c_szSampleDstDir, NULL, NULL)
            .if (SUCCEEDED(hr))

                mov hr,pfo.PerformOperations()
                .if (SUCCEEDED(hr))

                    ; Now that the folders have been created, create items for them.  This is just an optimization so
                    ; that the sample does not have to rebind to these items for each sample type.

                    mov hr,SHCreateItemFromRelativeName(psiSampleRoot, c_szSampleSrcDir, NULL, &IID_IShellItem, &psiSrc)
                    .if (SUCCEEDED(hr))

                        mov hr,SHCreateItemFromRelativeName(psiSampleRoot, c_szSampleDstDir, NULL, &IID_IShellItem, &psiDst)
                        .if (SUCCEEDED(hr))

                            mov rcx,ppsiSampleSrc
                            mov rax,psiSrc
                            mov [rcx],rax
                            mov rcx,ppsiSampleDst
                            mov rax,psiDst
                            mov [rcx],rax

                            ; Caller takes ownership

                            xor eax,eax
                            mov psiSrc,rax
                            mov psiDst,rax
                        .endif
                    .endif
                    .if (psiSrc)

                        psiSrc.Release()
                    .endif
                    .if (psiDst)

                        psiDst.Release()
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return( hr )

CreateSampleFolders endp

;
;  Synopsis:  Creates all of the files needed by this sample the requested known folder
;
;  Arguments: psiFolder  - Folder that will contain the sample files
;
;  Returns:   S_OK if successful
;
CreateSampleFiles proc uses rsi psiFolder:ptr IShellItem

  local hr:HRESULT
  local pfo:ptr IFileOperation
  local szSampleFileName[MAX_PATH]:WCHAR

    mov hr,CreateAndInitializeFileOperation(&IID_IFileOperation, &pfo)
    .if (SUCCEEDED(hr))

        mov hr,StringCchPrintfW(&szSampleFileName, ARRAYSIZE(szSampleFileName), "%s.%s", c_szSampleFileName, c_szSampleFileExt)
        .if (SUCCEEDED(hr))

            ; the file to be used for the single copy sample

            mov hr,pfo.NewItem(psiFolder, FILE_ATTRIBUTE_NORMAL, &szSampleFileName, NULL, NULL)

            ; the files to be used for the multiple copy sample

            .for ( esi = 0: SUCCEEDED(hr) && esi < c_cMaxFilesToCreate: esi++ )

                mov hr,StringCchPrintfW(&szSampleFileName, ARRAYSIZE(szSampleFileName), "%s%u.%s", c_szSampleFileName, rsi, c_szSampleFileExt)
                .if (SUCCEEDED(hr))
                    mov hr,pfo.NewItem(psiFolder, FILE_ATTRIBUTE_NORMAL, &szSampleFileName, NULL, NULL)
                .endif
            .endf
            .if (SUCCEEDED(hr))

                mov hr,pfo.PerformOperations()
            .endif
        .endif
        pfo.Release()
    .endif
    .return( hr )

CreateSampleFiles endp

;
;  Synopsis:  Deletes the files/folders created by this sample
;
;  Arguments: psiSrc  - Source folder item
;             psiDst  - Destination folder item
;
;  Returns:   S_OK if successful
;
DeleteSampleFiles proc psiSrc:ptr IShellItem, psiDst:ptr IShellItem

  local hr:HRESULT
  local pfo:ptr IFileOperation

    mov hr,CreateAndInitializeFileOperation(&IID_IFileOperation, &pfo)
    .if (SUCCEEDED(hr))
        mov hr,pfo.DeleteItem(psiSrc, NULL)
        .if (SUCCEEDED(hr))
            mov hr,pfo.DeleteItem(psiDst, NULL)
            .if (SUCCEEDED(hr))
                mov hr,pfo.PerformOperations()
            .endif
        .endif
        pfo.Release()
    .endif
    .return( hr )

DeleteSampleFiles endp

;
;  Synopsis:  This example copies a single item from the sample source folder
;             to the sample dest folder using a new item name.
;
;  Arguments: psiSrc  - Source folder item
;             psiDst  - Destination folder item
;
;  Returns:   S_OK if successful
;
CopySingleFile proc psiSrc:ptr IShellItem, psiDst:ptr IShellItem

  local hr:HRESULT
  local pfo:ptr IFileOperation
  local szNewName[MAX_PATH]:WCHAR
  local szSampleFileName[MAX_PATH]:WCHAR
  local psiSrcFile:ptr IShellItem

    ; Create the IFileOperation object

    mov hr,CreateAndInitializeFileOperation(&IID_IFileOperation, &pfo)
    .if (SUCCEEDED(hr))
        mov hr,StringCchPrintfW(&szSampleFileName, ARRAYSIZE(szSampleFileName), "%s.%s", c_szSampleFileName, c_szSampleFileExt)
        .if (SUCCEEDED(hr))
            mov hr,SHCreateItemFromRelativeName(psiSrc, &szSampleFileName, NULL, &IID_IShellItem, &psiSrcFile)
            .if (SUCCEEDED(hr))
                mov hr,StringCchPrintfW(&szNewName, ARRAYSIZE(szNewName), "%s.%s", c_szSampleFileNewname, c_szSampleFileExt)
                .if (SUCCEEDED(hr))
                    mov hr,pfo.CopyItem(psiSrcFile, psiDst, &szNewName, NULL)
                    .if (SUCCEEDED(hr))
                        mov hr,pfo.PerformOperations()
                    .endif
                .endif
                psiSrcFile.Release()
            .endif
        .endif
        pfo.Release()
    .endif
    .return( hr )

CopySingleFile endp

;
;  Synopsis:  Creates an IShellItemArray containing the sample files to be used
;             in the CopyMultipleFiles sample
;
;  Arguments: psiSrc  - Source folder item
;
;  Returns:   S_OK if successful
;
CreateShellItemArrayOfSampleFiles proc uses rsi rdi psiSrc:ptr IShellItem, riid:REFIID, ppv:ptr ptr

  local hr:HRESULT
  local psfSampleSrc:ptr IShellFolder
  local rgpidlChildren[c_cMaxFilesToCreate]:PITEMID_CHILD ;= {0};
  local szSampleFileName[MAX_PATH]:WCHAR
  local psia:ptr IShellItemArray

    xor eax,eax
    mov [r8],rax
    lea rdi,rgpidlChildren
    mov [rdi],rax

    mov hr,psiSrc.BindToHandler(NULL, &BHID_SFObject, &IID_IShellFolder, &psfSampleSrc)
    .if (SUCCEEDED(hr))
        .for (esi = 0: SUCCEEDED(hr) && esi < ARRAYSIZE(rgpidlChildren): esi++)
            mov hr,StringCchPrintfW(&szSampleFileName, ARRAYSIZE(szSampleFileName), "%s%u.%s", c_szSampleFileName, esi, c_szSampleFileExt)
            .if (SUCCEEDED(hr))
                mov hr,psfSampleSrc.ParseDisplayName(NULL, NULL, &szSampleFileName, NULL, &[rdi+rsi*8], NULL)
            .endif
        .endf
        .if (SUCCEEDED(hr))
            mov hr,SHCreateShellItemArray(NULL, psfSampleSrc, c_cMaxFilesToCreate, &rgpidlChildren, &psia)
            .if (SUCCEEDED(hr))
                mov hr,psia.QueryInterface(riid, ppv)
                psia.Release()
            .endif
        .endif
        .for (esi = 0: esi < ARRAYSIZE(rgpidlChildren): esi++)
            CoTaskMemFree([rdi+rsi*8])
        .endf
        psfSampleSrc.Release()
    .endif
    .return( hr )

CreateShellItemArrayOfSampleFiles endp

;
;  Synopsis:  This example creates multiple files under the specified folder
;             path and copies them to the same directory with a new name.
;
;  Arguments: psiSrc  - Source folder item
;             psiDst  - Destination folder item
;
;  Returns:   S_OK if successful
;
CopyMultipleFiles proc psiSrc:ptr IShellItem, psiDst:ptr IShellItem

  local hr:HRESULT
  local pfo:ptr IFileOperation
  local psiaSampleFiles:ptr IShellItemArray

    ; Create the IFileOperation object

    mov hr,CreateAndInitializeFileOperation(&IID_IFileOperation, &pfo)
    .if (SUCCEEDED(hr))
        mov hr,CreateShellItemArrayOfSampleFiles(psiSrc, &IID_IShellItemArray, &psiaSampleFiles)
        .if (SUCCEEDED(hr))
            mov hr,pfo.CopyItems(psiaSampleFiles, psiDst)
            .if (SUCCEEDED(hr))
                mov hr,pfo.PerformOperations()
            .endif
            psiaSampleFiles.Release()
        .endif
        pfo.Release()
    .endif
    .return( hr )

CopyMultipleFiles endp

wmain proc

  local hr:HRESULT
  local psiDocuments:ptr IShellItem
  local psiSampleSrc:ptr IShellItem
  local psiSampleDst:ptr IShellItem

    mov hr,CoInitializeEx(NULL, COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE)
    .if (SUCCEEDED(hr))

        ; Get the documents known folder.  This folder will be used to create subfolders
        ; for the sample source and destination

        mov hr,SHCreateItemInKnownFolder(&FOLDERID_Documents, KF_FLAG_DEFAULT_PATH, NULL, &IID_IShellItem, &psiDocuments)
        .if (SUCCEEDED(hr))
            mov hr,CreateSampleFolders(psiDocuments, &psiSampleSrc, &psiSampleDst)
            .if (SUCCEEDED(hr))
                mov hr,CreateSampleFiles(psiSampleSrc)
                .if (SUCCEEDED(hr))
                    mov hr,CopySingleFile(psiSampleSrc, psiSampleDst)
                    .if (SUCCEEDED(hr))
                        mov hr,CopyMultipleFiles(psiSampleSrc, psiSampleDst)
                    .endif
                .endif
                DeleteSampleFiles(psiSampleSrc, psiSampleDst)
                psiSampleSrc.Release()
                psiSampleDst.Release()
            .endif
            psiDocuments.Release()
        .endif
        CoUninitialize()
    .endif
    .return( 0 )

wmain endp

    end
