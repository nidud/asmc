ifndef __ATLDBCLI_H__
__ATLDBCLI_H__ equ <>

include atldef.inc

ifndef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
.err <This file is not compatible with the current WINAPI_FAMILY>
endif

ifndef __ATLBASE_H__
include atlbase.inc
endif

include atlsimpstr.inc

ifndef __oledb_h__
include oledb.inc
endif

include oledberr.inc
include msdaguid.inc
include msdasc.inc

.pragma pack(push, _ATL_PACKING)

LPIDBInitialize typedef ptr IDBInitialize

.template CDataSource

    m_spInit LPIDBInitialize ?

    .static OpenFromInitializationString :LPCOLESTR, :BOOL {

       .new hr:HRESULT
       .new spDataInit:ptr IDataInitialize
       .new szInitializationString:LPCOLESTR
       .new fPromptForInfo:BOOL

        mov szInitializationString,rdx
        mov fPromptForInfo,r8d
        mov hr,CoCreateInstance(&CLSID_MSDAINITIALIZE, NULL, CLSCTX_INPROC_SERVER, &IID_IDataInitialize, &spDataInit)

        .if (SUCCESS(hr))

            mov hr,spDataInit.GetDataSource(NULL, CLSCTX_INPROC_SERVER, szInitializationString, &IID_IDBInitialize, &this.m_spInit)

            .if (SUCCESS(hr))

                .if ( fPromptForInfo )

                   .new spIDBProperties:ptr IDBProperties
                   .new rgProperties:DBPROP
                   .new rgPropertySets:DBPROPSET

                    mov hr,this.m_spInit.QueryInterface( &IID_IDBProperties, &spIDBProperties )

                    VariantInit(&rgProperties.vValue)
                    mov rgProperties.dwOptions,DBPROPOPTIONS_REQUIRED
                    mov rgProperties.colid,DB_NULLID
                    mov rgProperties.dwPropertyID,DBPROP_INIT_PROMPT
                    mov rgProperties.vValue.vt,VT_I2
                    mov rgProperties.vValue.lVal,DBPROMPT_COMPLETEREQUIRED
                    mov rgPropertySets.rgProperties,&rgProperties
                    mov rgPropertySets.cProperties,1
                    mov rgPropertySets.guidPropertySet,DBPROPSET_DBINIT
                    mov hr,spIDBProperties.SetProperties( 1, &rgPropertySets )
                    .if (SUCCESS(hr))
                        this.m_spInit.Initialize()
                    .endif
                .endif
            .endif
        .endif
        }
    .ENDS


LPIOpenRowset typedef ptr IOpenRowset

.template CSession

    m_spOpenRowset LPIOpenRowset ?

    ;; Create a session on the passed datasource

    .static Open :abs, :abs=<NULL>, :abs=<0> {

       .new ulPropSets:BOOL
       .new pPropSet:ptr DBPROPSET
       .new spSession:ptr IDBCreateSession

        mov pPropSet,_2
        mov ulPropSets,_3

        .ifsd _1.m_spInit.QueryInterface(&IID_IDBCreateSession, &spSession) >= 0

            spSession.CreateSession(NULL, &IID_IOpenRowset, &this.m_spOpenRowset)

            .if ( pPropSet != NULL && SUCCEEDED(eax) && this.m_spOpenRowset != NULL )

                ;; If the user didn't specify the default parameter, use one

                .if (pPropSet != NULL && ulPropSets == 0)

                    mov ulPropSets,1
                .endif

                .new spSessionProperties:ptr ISessionProperties
                .ifsd this.m_spOpenRowset.QueryInterface(&IID_ISessionProperties, &spSessionProperties) >= 0
                    spSessionProperties.SetProperties( ulPropSets, pPropSet )
                .endif
            .endif
        .endif
        }

    .static Close {
        this.m_spOpenRowset.Release()
        }

    .ENDS


.template CCommandBase

    LPICommand typedef ptr ICommand

    m_spCommand LPICommand ?
    m_hParameterAccessor HACCESSOR ?

    .static CCommandBase {
        mov this.m_hParameterAccessor,0
        }

    ;; Release the command
    .static ReleaseCommand {
        .new hr:HRESULT
        ;; Release the parameter accessor if necessary, before releasing the command
        .if (this.m_hParameterAccessor != 0 && this.m_spCommand != NULL )

            .new spAccessor:ptr IAccessor
            mov hr,this.m_spCommand.QueryInterface(&IID_IAccessor, &spAccessor)
            .if (SUCCEEDED(hr))

                spAccessor.ReleaseAccessor(this.m_hParameterAccessor, NULL)
                mov this.m_hParameterAccessor,0
            .endif
        .endif
        this.m_spCommand.Release()
        }

    ;; Create the command
    .static CreateCommand :abs {
        ;; Before creating the command, release the old one if necessary.
        this.ReleaseCommand()

        .new spCreateCommand:ptr IDBCreateCommand

        mov hr,_1.m_spOpenRowset.QueryInterface(&IID_IDBCreateCommand, &spCreateCommand)
        .if (SUCCESS(hr))
            spCreateCommand.CreateCommand(NULL, &IID_ICommand, &m_spCommand)
        .endif
        mov eax,hr
        }

    ;; Create the command and set the command text
    .static Create :abs, :abs, :abs=<DBGUID_DEFAULT> {

       .new hr:HRESULT

        mov hr,this.CreateCommand(_1)
        .if (SUCCEEDED(hr))

            .new spCommandText:ptr ICommandText
            mov hr,this.m_spCommand.QueryInterface(&IID_ICommandText, &spCommandText)
            .if (SUCCEEDED(hr))
                mov hr,spCommandText.SetCommandText(addr _3, _2)
            .endif
        .endif
        mov eax,hr
        }

    .ENDS


.template CCommand : public CCommandBase

    ;; Create a command on the session and execute it

    .static Open :abs, :abs, :abs=<NULL>, :abs=<NULL>, :abs=<DBGUID_DEFAULT>, :abs=<TRUE>, :abs=<0> {

       .new hr:HRESULT
        mov hr,S_OK
        .if (_2 == NULL)
            mov hr,_CommandClass::GetDefaultCommand(&_2)
        .endif
        .if hr == S_OK
            mov hr,this.Create(_1, _2, _5)
        .endif
        .if hr == S_OK
            mov hr,this.Open2(_3, _4, _6, _7)
        .endif
        mov eax,hr
        }

    ;; Used if you have previously created the command

    .static Open2 :abs=<NULL>, :abs=<NULL>, :abs=<TRUE>, :abs=<0> {

       .new hr:HRESULT
       .new params:DBPARAMS
       .new pParams:ptr DBPARAMS

        mov hr,S_OK
        ;; Bind the parameters if we have some

        .if (_ParamClass::HasParameters())

            ;; Bind the parameters in the accessor if they haven't already been bound
            mov hr,BindParameters(&this.m_hParameterAccessor, this.m_spCommand, &params.pData)
            .if (SUCCESS(hr))

                ;; Setup the DBPARAMS structure

                mov params.cParamSets,1
                mov params.hAccessor,m_hParameterAccessor
                mov pParams,&params
            .endif

        .else
            mov pParams,NULL
        .endif
        .if (SUCCESS(hr))
            mov hr,ExecuteAndBind(pParams, _1, _2, _3, _4)
        .endif
        mov eax,hr
        }
    .ENDS

.pragma pack(pop)

endif
