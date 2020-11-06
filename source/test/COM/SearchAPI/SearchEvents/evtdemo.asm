;
; https://docs.microsoft.com/en-us/windows/win32/search/-search-sample-searchevents
;
include crtdbg.inc
include msdasc.inc
include atlbase.inc
include atlcom.inc
include searchapi.inc
include propkey.inc
include ntquery.inc
include strsafe.inc
include wininet.inc
include shlwapi.inc

.code

;;*****************************************************************************
;; Open a database session...

OpenSession proc ppCreateCommand:ptr ptr IDBCreateCommand

  local hr:HRESULT
  local spDataInit:ptr IDataInitialize
  local spUnknownDBInitialize:ptr IUnknown
  local spDBInitialize:ptr IDBInitialize
  local spDBCreateSession:ptr IDBCreateSession

    xor eax,eax
    mov [rcx],rax
    mov spDataInit,rax
    mov spUnknownDBInitialize,rax
    mov spDBInitialize,rax
    mov spDBCreateSession,rax

    mov hr,CoCreateInstance(&CLSID_MSDAINITIALIZE, NULL, CLSCTX_INPROC_SERVER,
            &IID_IDataInitialize, &spDataInit)

    .if (SUCCEEDED(hr))
        mov hr,spDataInit.GetDataSource(NULL, CLSCTX_INPROC_SERVER,
                L"provider=Search.CollatorDSO.1", &IID_IDBInitialize, &spUnknownDBInitialize)
    .endif
    .if (SUCCEEDED(hr))

        mov hr,spUnknownDBInitialize.QueryInterface(&IID_IDBInitialize, &spDBInitialize)
    .endif
    .if (SUCCEEDED(hr))

        mov hr,spDBInitialize.Initialize()
    .endif
    .if (SUCCEEDED(hr))

        mov hr,spDBInitialize.QueryInterface(&IID_IDBCreateSession, &spDBCreateSession)
    .endif
    .if (SUCCEEDED(hr))

        .new spUnknownCreateCommand:ptr IUnknown
        mov hr,spDBCreateSession.CreateSession(0, &IID_IDBCreateCommand, &spUnknownCreateCommand)
        .if (SUCCEEDED(hr))

            mov hr,spUnknownCreateCommand.QueryInterface(&IID_IDBCreateCommand, ppCreateCommand)
        .endif
    .endif

    .return hr

OpenSession endp

;;*****************************************************************************
;; Run a query against the database, optionally enabling eventing...

ExecuteQuery proc pDBCreateCommand:ptr IDBCreateCommand, pwszQuerySQL:PCWSTR,
        fEnableEventing:BOOL, riid:REFIID, ppv:ptr ptr

  local hr:HRESULT
  local spUnknownCommand:ptr IUnknown
  local spCommandProperties:ptr ICommandProperties
  local spCommandText:ptr ICommandText

    xor eax,eax
    mov spUnknownCommand,rax
    mov spCommandProperties,rax
    mov spCommandText,rax

    mov hr,pDBCreateCommand.CreateCommand(0, &IID_ICommand, &spUnknownCommand)
    .if (SUCCEEDED(hr))

        mov hr,spUnknownCommand.QueryInterface(&IID_ICommandProperties, &spCommandProperties)
    .endif

    .if (SUCCEEDED(hr))

       .data
        guidQueryExt GUID DBPROPSET_QUERYEXT
       .code

       .new rgProps[2]:DBPROP
       .new propSet:DBPROPSET

        mov rgProps.dwPropertyID,   DBPROP_USEEXTENDEDDBTYPES
        mov rgProps.dwOptions,      DBPROPOPTIONS_OPTIONAL
        mov rgProps.vValue.vt,      VT_BOOL
        mov rgProps.vValue.boolVal, VARIANT_TRUE
        mov propSet.cProperties,1

        .if (fEnableEventing)

            mov rgProps[DBPROP].dwPropertyID,   DBPROP_ENABLEROWSETEVENTS
            mov rgProps[DBPROP].dwOptions,      DBPROPOPTIONS_OPTIONAL
            mov rgProps[DBPROP].vValue.vt,      VT_BOOL
            mov rgProps[DBPROP].vValue.boolVal, VARIANT_TRUE
            inc propSet.cProperties
        .endif

        mov propSet.rgProperties,&rgProps
        mov propSet.guidPropertySet,guidQueryExt
        mov hr,spCommandProperties.SetProperties(1, &propSet)
    .endif
    .if (SUCCEEDED(hr))

        mov hr,spUnknownCommand.QueryInterface(&IID_ICommandText, &spCommandText)
    .endif
    .if (SUCCEEDED(hr))

        mov hr,spCommandText.SetCommandText(&DBGUID_DEFAULT, pwszQuerySQL)
    .endif
    .if (SUCCEEDED(hr))

       .new cRows:DBROWCOUNT
        mov hr,spCommandText.Execute(NULL, riid, NULL, &cRows, ppv)
    .endif

    .return hr

ExecuteQuery endp


;;*****************************************************************************
;; Retrieves the URL from a given workid

RetrieveURL proc pDBCreateCommand:ptr IDBCreateCommand, itemID:REFPROPVARIANT,
        pwszURL:PWSTR, cchURL:int_t

  local hr:HRESULT
  local wszQuery[512]:WCHAR
  local spRowset:ptr IRowset

    mov spRowset,NULL
    mov wszQuery,0
    mov hr,E_INVALIDARG

    .if ([rdx].PROPVARIANT.vt == VT_UI4)
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))
        mov hr,StringCchPrintf(
                &wszQuery,
                lengthof wszQuery,
                L"SELECT TOP 1 System.ItemUrl FROM SystemIndex WHERE workid=%u",
                [rdx].PROPVARIANT.ulVal)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,ExecuteQuery(pDBCreateCommand, &wszQuery, FALSE,
                &IID_IRowset, &spRowset)
    .endif
    .if (SUCCEEDED(hr))

       .new spGetRow:ptr IGetRow
       .new ciRowsRetrieved:DBCOUNTITEM
       .new hRow:HROW
       .new phRow:HROW
       .new spPropertyStore:ptr IPropertyStore

        mov ciRowsRetrieved,0
        mov hRow,NULL
        mov phRow,&hRow

        mov hr,spRowset.GetNextRows( DB_NULL_HCHAPTER, 0, 1, &ciRowsRetrieved, &phRow )
        .if (SUCCEEDED(hr))

            mov hr,spRowset.QueryInterface(&IID_IGetRow, &spGetRow)
            .if (SUCCEEDED(hr))

               .new spUnknownPropertyStore:ptr IUnknown
                mov hr,spGetRow.GetRowFromHROW( NULL, hRow, &IID_IPropertyStore, &spUnknownPropertyStore )
                .if (SUCCEEDED(hr))

                    mov hr,spUnknownPropertyStore.QueryInterface(&IID_IPropertyStore, &spPropertyStore)
                .endif
            .endif
            .if (SUCCEEDED(hr))

               .new var:PROPVARIANT
                mov hr,spPropertyStore.GetValue( &PKEY_ItemUrl, &var )
                .if (SUCCEEDED(hr))

                    .if (var.vt == VT_LPWSTR)

                        mov hr,StringCchCopy( pwszURL, cchURL, var.pwszVal )

                    .else

                        mov hr,E_INVALIDARG
                    .endif
                    PropVariantClear( &var )
                .endif
            .endif
            spRowset.ReleaseRows( ciRowsRetrieved, phRow, NULL, NULL, NULL )
        .endif
    .endif

    .return hr

RetrieveURL endp

;;*****************************************************************************

ItemStateToString proc itemState:ROWSETEVENT_ITEMSTATE

    .switch (itemState)
    .case ROWSETEVENT_ITEMSTATE_NOTINROWSET
        .return &@CStr(L"NotInRowset")
    .case ROWSETEVENT_ITEMSTATE_INROWSET
        .return &@CStr(L"InRowset")
    .case ROWSETEVENT_ITEMSTATE_UNKNOWN
        .return &@CStr(L"Unknown")
    .endsw
    .return &@CStr(L"")

ItemStateToString endp

;;*****************************************************************************

PriorityLevelToString proc priority:PRIORITY_LEVEL

    .switch priority
    .case PRIORITY_LEVEL_FOREGROUND
        .return &@CStr(L"Foreground")
    .case PRIORITY_LEVEL_HIGH
        .return &@CStr(L"High")
    .case PRIORITY_LEVEL_LOW
        .return &@CStr(L"Low")
    .case PRIORITY_LEVEL_DEFAULT
        .return &@CStr(L"Default")
    .endsw
    .return &@CStr(L"")

PriorityLevelToString endp



;;*****************************************************************************
;; An event listener class that listens to indexer events and logs them
;; as they arrive...

.class CRowsetEventListener : public IRowsetEvents

    spDBCreateCommand LPIDBCreateCommand ?

    PrintURL proc itemID:REFPROPVARIANT
    .ENDS


CRowsetEventListener::Release proc

    HeapAlloc(GetProcessHeap(), 0, this)
    ret

CRowsetEventListener::Release endp

CreateComObject proc pp:ptr ptr CRowsetEventListener

    xor eax,eax
    mov [rcx],rax

    .if HeapAlloc(GetProcessHeap(), 0, CRowsetEventListener + CRowsetEventListenerVtbl)

        lea rcx,[rax+CRowsetEventListener]
        mov [rax],rcx
        mov [rax].CRowsetEventListener.spDBCreateCommand,NULL
        for q,<Release,AddRef,QueryInterface,OnNewItem,OnChangedItem,OnDeletedItem,OnRowsetEvent,PrintURL>
            lea rdx,CRowsetEventListener_&q
            mov [rcx].CRowsetEventListenerVtbl.&q,rdx
            endm
        mov rcx,pp
        mov [rcx],rax
    .endif
    .if rax
        mov rax,S_OK
    .else
        mov eax,E_OUTOFMEMORY
    .endif
    ret

CreateComObject endp

CRowsetEventListener::AddRef proc
    ret
CRowsetEventListener::AddRef endp

CRowsetEventListener::QueryInterface proc riid:REFIID, ppv:ptr ptr
    mov [r8],rcx
    mov eax,NOERROR
    ret
CRowsetEventListener::QueryInterface endp

CRowsetEventListener::PrintURL proc itemID:REFPROPVARIANT

  local hr:HRESULT
  local wszURL[INTERNET_MAX_URL_LENGTH]:WCHAR

    mov hr,E_INVALIDARG
    .if ([rdx].PROPVARIANT.vt == VT_UI4)
        mov hr,S_OK
    .endif
    .if (SUCCEEDED(hr))

        mov rcx,[rcx].CRowsetEventListener.spDBCreateCommand
        mov hr,RetrieveURL( rcx, itemID, &wszURL, ARRAYSIZE(wszURL) )
        .if (FAILED(hr))

            ;; It's possible that for some items we won't be able to retrieve the URL.
            ;; This can happen when our application doesn't have sufficient priveledges to read the URL
            ;; or if the URL has been deleted from the system.

            mov hr,StringCchCopy( &wszURL, ARRAYSIZE(wszURL), L"URL-Lookup-NotFound" )
        .endif
    .endif
    .if (SUCCEEDED(hr))

        mov rcx,itemID
        mov edx,[rcx].PROPVARIANT.ulVal
        _tprintf( "workid: %u;  URL: %S\n", edx, &wszURL )
    .endif
    .return hr

CRowsetEventListener::PrintURL endp

CRowsetEventListener::OnNewItem proc itemID:REFPROPVARIANT, newItemState:ROWSETEVENT_ITEMSTATE

    ;; This event is received when the indexer has completed indexing of a NEW item that falls within the
    ;; scope of your query.  If your query is for C:\users, then only newly indexed items within C:\users
    ;; will be given.

    _tprintf( "OnNewItem( newItemState: %S )\n\t\t", ItemStateToString(newItemState) )
    .return this.PrintURL( itemID )

CRowsetEventListener::OnNewItem endp

CRowsetEventListener::OnChangedItem proc itemID:REFPROPVARIANT,
        rowsetItemState:ROWSETEVENT_ITEMSTATE, changedItemState:ROWSETEVENT_ITEMSTATE

    ;; This event is received when the indexer has completed re-indexing of an item that was already in
    ;; the index that falls within the scope of your query.  The rowsetItemState parameter indicates the
    ;; state of the item regarding your query when it was initially executed.  The changedItemState
    ;; represents the state of the item following reindexing.

    _tprintf( "OnChangedItem( rowsetItemState: %S changedItemState: %S )\n\t\t", ItemStateToString(rowsetItemState), ItemStateToString(changedItemState) )
    .return this.PrintURL( itemID )

CRowsetEventListener::OnChangedItem endp


CRowsetEventListener::OnDeletedItem proc itemID:REFPROPVARIANT, deletedItemState:ROWSETEVENT_ITEMSTATE

    ;; This event is received when the indexer has completed deletion of an item that was already in
    ;; the index that falls within the scope of your query.  Note that the item may not have been in your
    ;; original query even if the original query was solely scope-based if the item was added following
    ;; your query.

    _tprintf( "OnDeletedItem( deletedItemState: %S )\n\t\t", ItemStateToString(deletedItemState) )
    .return this.PrintURL( itemID )

CRowsetEventListener::OnDeletedItem endp


CRowsetEventListener::OnRowsetEvent proc eventType:ROWSETEVENT_TYPE, eventData:REFPROPVARIANT

    .switch (eventType)

    .case ROWSETEVENT_TYPE_DATAEXPIRED

        ;; This event signals that your rowset is no longer valid, so further calls made to the rowset
        ;; will fail.  This can happen if the client (your application) loses its connection to the
        ;; indexer.  Indexer restarts or network problems with remote queries could cause this.

        _tprintf( "OnRowsetEvent( ROWSETEVENT_TYPE_DATAEXPIRED )\n\t\tData backing the rowset has expired.  Requerying is needed.\n" )
        .endc

    .case ROWSETEVENT_TYPE_FOREGROUNDLOST

        ;; This event signals that a previous request for PRIORITY_LEVEL_FOREGROUND made on this rowset
        ;; has been downgraded to PRIORITY_LEVEL_HIGH.  The most likely cause of this is another query
        ;; having requested foreground prioritization.  The indexer treats prioritization requests as a
        ;; stack where only the top request on the stack may have foreground priority.

        _tprintf( "OnRowsetEvent( ROWSETEVENT_TYPE_FOREGROUNDLOST )\n\t\tForeground priority has been downgraded to high priority.\n" )
        .endc

    .case ROWSETEVENT_TYPE_SCOPESTATISTICS
        ;; This informational event is sent periodically when there has been a prioritization request for
        ;; any value other than PRIORITY_LEVEL_DEFAULT.  This event allows tracking indexing progress in
        ;; response to a prioritization reqeust.

        mov rcx,eventData
        _tprintf(
            "OnRowsetEvent( ROWSETEVENT_TYPE_SCOPESTATISTICS )\n\t\tStatistics( indexedDocs:%u docsToAddCount:%u docsToReindexCount: %u )\n",
            [rcx].PROPVARIANT.caul.pElems[0],
            [rcx].PROPVARIANT.caul.pElems[8],
            [rcx].PROPVARIANT.caul.pElems[16] )
        .endc
    .endsw
    .return S_OK

CRowsetEventListener::OnRowsetEvent endp


;;*****************************************************************************
;; Watches events on the given query with the given priority for a period of
;; time.  If dwTimeout == 0, then it will monitor until all items are indexed
;; within the query.  Otherwise, it monitors for dwTimeout MS.

WatchEvents proc pwszQuerySQL:PCWSTR, priority:PRIORITY_LEVEL, dwTimeout:DWORD

  local hr:HRESULT
  local spDBCreateCommand:ptr IDBCreateCommand
  local spRowset:ptr IRowset
  local spRowsetPrioritization:ptr IRowsetPrioritization
  local spListener:ptr CRowsetEventListener

    xor eax,eax
    mov spRowset,rax
    mov spRowsetPrioritization,rax
    mov spListener,rax

    mov hr,OpenSession( &spDBCreateCommand )
    .if (SUCCEEDED(hr))

        mov hr,ExecuteQuery( spDBCreateCommand, pwszQuerySQL,
                TRUE, &IID_IRowset, &spRowset)
    .endif
    .if (SUCCEEDED(hr))

        mov hr,spRowset.QueryInterface(&IID_IRowsetPrioritization, &spRowsetPrioritization)
    .endif
    .if (SUCCEEDED(hr))

        mov hr,CreateComObject( &spListener )
    .endif
    .if (SUCCEEDED(hr))

        mov rcx,spListener
        mov [rcx].CRowsetEventListener.spDBCreateCommand,spDBCreateCommand

       .new dwAdviseID:DWORD
        mov hr,ConnectToConnectionPoint( spListener, ; .GetUnknown()
                &IID_IRowsetEvents, TRUE, spRowset, &dwAdviseID, NULL )
        .if (SUCCEEDED(hr))

           .new indexedDocumentCount:DWORD
           .new oustandingAddCount:DWORD
           .new oustandingModifyCount:DWORD
            mov indexedDocumentCount,  0
            mov oustandingAddCount,    0
            mov oustandingModifyCount, 0

            spRowsetPrioritization.GetScopeStatistics( &indexedDocumentCount, &oustandingAddCount, &oustandingModifyCount )

            _tprintf( "Prioritization and Eventing Demo\n\n" )
            _tprintf( "Query:               %S\n\n", pwszQuerySQL )
            _tprintf( "Indexed Docs:        %u\n", indexedDocumentCount )
            _tprintf( "Oustanding Adds:     %u\n", oustandingAddCount )
            _tprintf( "Oustanding Modifies: %u\n\n", oustandingModifyCount )
            _tprintf( "Setting Priority:    %S\n\n", PriorityLevelToString(priority) )
            _tprintf( "Now monitoring events for this query...\n\n" )

            spRowsetPrioritization.SetScopePriority( priority, 1000 )

            .if (dwTimeout == 0)

                .while (SUCCEEDED(hr) && ((oustandingAddCount > 0) || (oustandingModifyCount > 0)))

                    Sleep( 1000 )
                    mov hr,spRowsetPrioritization.GetScopeStatistics( &indexedDocumentCount, &oustandingAddCount, &oustandingModifyCount )
                .endw

            .else

                Sleep( dwTimeout )
            .endif

            ConnectToConnectionPoint( spListener,;.GetUnknown(),
                &IID_IRowsetEvents, FALSE, spRowset, &dwAdviseID, NULL )
        .endif
    .endif

    .if (FAILED(hr))

        _tprintf( "Failure: %08X\n", hr )
    .endif
    ret

WatchEvents endp


wmain proc uses rsi rdi rbx argc:int_t, argv:ptr wchar_t

  local hr:HRESULT
  local wszURL[INTERNET_MAX_URL_LENGTH]:WCHAR
  local fHandled:BOOL
  local dwTimeout:DWORD
  local priority:PRIORITY_LEVEL

    xor ebx,ebx
    mov rsi,rdx

    .if (argc <= 1)

        inc ebx

    .elseif (argc == 2)

        mov rdx,[rsi+8]
        mov eax,[rdx]
        .if ( ax == '-' || ax == '/' )

            shr eax,16

            .if ( ax == '?' )

                inc ebx
            .endif
        .endif
    .endif

    .if ebx

        _tprintf( "Allows monitoring and prioritization of indexer URLs.\n\n"
                  "Eventing [drive:][path] [/p[:]priority] [/t[:]duration]\n\n"
                  "  [drive:][path]\n"
                  "             Specifies drive and directory of location to watch\n"
                  "  /p         Prioritizes indexing at the given speed\n"
                  "  priority     F  Foreground      H High\n"
                  "               L  Low             D Default\n"
                  "  /t         Specifies how long in MS to monitor query\n"
                  "  duration     0     Until all content is indexed\n"
                  "               NNNN  Monitor for NNNN milliseconds\n\n" )
        .return 0
    .endif

    mov hr,CoInitializeEx(0, COINIT_MULTITHREADED or COINIT_DISABLE_OLE1DDE)
    .if (SUCCEEDED(hr))

        mov hr,S_OK
        mov fHandled,TRUE
        mov dwTimeout,(300 * 1000) ;; default 5 mins
        mov priority,PRIORITY_LEVEL_DEFAULT
        mov wszURL,0

        .for (ebx = 1: ((ebx < argc) && SUCCEEDED(hr)): ebx++)

            mov rcx,[rsi+rbx*8]
            .if (word ptr [rcx] == '/')

                movzx eax,word ptr [rcx+2]
                or eax,0x20
                .if (eax == 'p')

                    add rcx,4
                    mov ax,[rcx]
                    .if (ax == ':')
                        add rcx,2
                    .endif
                    mov ax,[rcx]
                    or eax,0x20

                    .switch eax

                    .case 'f'
                        mov priority,PRIORITY_LEVEL_FOREGROUND
                        .endc
                    .case 'h'
                        mov priority,PRIORITY_LEVEL_HIGH
                        .endc
                    .case 'l'
                        mov priority,PRIORITY_LEVEL_LOW
                        .endc
                    .case 'd'
                        mov priority,PRIORITY_LEVEL_DEFAULT
                        .endc
                    .default
                        mov hr,E_INVALIDARG
                    .endsw

                .elseif (eax == 't')

                    add rcx,4
                    mov ax,[rcx]
                    .if (ax == ':')
                        add rcx,2
                    .endif
                    mov dwTimeout,_wtol(rcx)
                    mov fHandled,TRUE

                .else

                    mov hr,E_INVALIDARG
                .endif

            .else

                mov hr,StringCchCopy( &wszURL, ARRAYSIZE(wszURL), rcx )
            .endif
        .endf

        .if (SUCCEEDED(hr))

            .new wszQuerySQL[INTERNET_MAX_URL_LENGTH]:WCHAR
            .if (wszURL)

                mov hr,StringCchPrintf( &wszQuerySQL,
                    ARRAYSIZE(wszQuerySQL), L"SELECT workid FROM SystemIndex WHERE SCOPE='%s'", &wszURL )

            .else

                mov hr,StringCchCopy( &wszQuerySQL,
                    ARRAYSIZE(wszQuerySQL), L"SELECT workid FROM SystemIndex" )
            .endif
            .if (SUCCEEDED(hr))

                WatchEvents( &wszQuerySQL, priority, dwTimeout )
            .endif
        .endif

        CoUninitialize()
    .endif
    .return 0

wmain endp

    end
