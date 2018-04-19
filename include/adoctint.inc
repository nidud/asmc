ifndef _ADOCTINT_H_
_ADOCTINT_H_ equ <>
ifndef _INC_TCHAR
include tchar.inc
endif

ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef __adocat_h__
__adocat_h__ equ 1

ifndef ___ADOCollection_FWD_DEFINED__
___ADOCollection_FWD_DEFINED__ equ 1
endif
ifndef ___ADODynaCollection_FWD_DEFINED__
___ADODynaCollection_FWD_DEFINED__ equ 1
endif
ifndef ___Catalog_FWD_DEFINED__
___Catalog_FWD_DEFINED__ equ 1
endif
ifndef ___Table_FWD_DEFINED__
___Table_FWD_DEFINED__ equ 1
endif
ifndef ___Group25_FWD_DEFINED__
___Group25_FWD_DEFINED__ equ 1
endif
ifndef ___Group_FWD_DEFINED__
___Group_FWD_DEFINED__ equ 1
endif
ifndef ___User25_FWD_DEFINED__
___User25_FWD_DEFINED__ equ 1
endif
ifndef ___User_FWD_DEFINED__
___User_FWD_DEFINED__ equ 1
endif
ifndef ___Column_FWD_DEFINED__
___Column_FWD_DEFINED__ equ 1
endif
ifndef ___Index_FWD_DEFINED__
___Index_FWD_DEFINED__ equ 1
endif
ifndef ___Key_FWD_DEFINED__
___Key_FWD_DEFINED__ equ 1
endif
ifndef __View_FWD_DEFINED__
__View_FWD_DEFINED__ equ 1
endif
ifndef __Procedure_FWD_DEFINED__
__Procedure_FWD_DEFINED__ equ 1
endif
ifndef __Catalog_FWD_DEFINED__
__Catalog_FWD_DEFINED__ equ 1
;Catalog typedef ADOCatalog
endif
ifndef __Table_FWD_DEFINED__
__Table_FWD_DEFINED__ equ 1
;Table typedef ADOTable
endif
ifndef __Property_FWD_DEFINED__
__Property_FWD_DEFINED__ equ 1
endif
ifndef __Group_FWD_DEFINED__
__Group_FWD_DEFINED__ equ 1
;Group typedef ADOGroup
endif
ifndef __User_FWD_DEFINED__
__User_FWD_DEFINED__ equ 1
;User typedef ADOUser
endif
ifndef __Column_FWD_DEFINED__
__Column_FWD_DEFINED__ equ 1
;Column typedef ADOColumn
endif
ifndef __Index_FWD_DEFINED__
__Index_FWD_DEFINED__ equ 1
;Index typedef ADOIndex
endif
ifndef __Key_FWD_DEFINED__
__Key_FWD_DEFINED__ equ 1
;Key typedef ADOKey
endif
ifndef __Tables_FWD_DEFINED__
__Tables_FWD_DEFINED__ equ 1
endif
ifndef __Columns_FWD_DEFINED__
__Columns_FWD_DEFINED__ equ 1
endif
ifndef __Procedures_FWD_DEFINED__
__Procedures_FWD_DEFINED__ equ 1
endif
ifndef __Views_FWD_DEFINED__
__Views_FWD_DEFINED__ equ 1
endif
ifndef __Indexes_FWD_DEFINED__
__Indexes_FWD_DEFINED__ equ 1
endif
ifndef __Keys_FWD_DEFINED__
__Keys_FWD_DEFINED__ equ 1
endif
ifndef __Users_FWD_DEFINED__
__Users_FWD_DEFINED__ equ 1
endif
ifndef __Groups_FWD_DEFINED__
__Groups_FWD_DEFINED__ equ 1
endif
ifndef __Properties_FWD_DEFINED__
__Properties_FWD_DEFINED__ equ 1
endif
include oaidl.inc
include ocidl.inc

RuleEnum		typedef SDWORD
adRINone		equ 0
adRICascade		equ 1
adRISetNull		equ 2
adRISetDefault		equ 3
KeyTypeEnum		typedef SDWORD
adKeyPrimary		equ 1
adKeyForeign		equ 2
adKeyUnique		equ 3
ActionEnum		typedef SDWORD
adAccessGrant		equ 1
adAccessSet		equ 2
adAccessDeny		equ 3
adAccessRevoke		equ 4
ColumnAttributesEnum	typedef SDWORD
adColFixed		equ 1
adColNullable		equ 2
SortOrderEnum		typedef SDWORD
adSortAscending		equ 1
adSortDescending	equ 2
RightsEnum		typedef SDWORD
adRightNone		equ 0
adRightDrop		equ 0x100
adRightExclusive	equ 0x200
adRightReadDesign	equ 0x400
adRightWriteDesign	equ 0x800
adRightWithGrant	equ 0x1000
adRightReference	equ 0x2000
adRightCreate		equ 0x4000
adRightInsert		equ 0x8000
adRightDelete		equ 0x10000
adRightReadPermissions	equ 0x20000
adRightWritePermissions equ 0x40000
adRightWriteOwner	equ 0x80000
adRightMaximumAllowed	equ 0x2000000
adRightFull		equ 0x10000000
adRightExecute		equ 0x20000000
adRightUpdate		equ 0x40000000
adRightRead		equ 0x80000000

DataTypeEnum		typedef SDWORD
adEmpty			equ 0
adTinyInt		equ 16
adSmallInt		equ 2
adInteger		equ 3
adBigInt		equ 20
adUnsignedTinyInt	equ 17
adUnsignedSmallInt	equ 18
adUnsignedInt		equ 19
adUnsignedBigInt	equ 21
adSingle		equ 4
adDouble		equ 5
adCurrency		equ 6
adDecimal		equ 14
adNumeric		equ 131
adBoolean		equ 11
adError			equ 10
adUserDefined		equ 132
adVariant		equ 12
adIDispatch		equ 9
adIUnknown		equ 13
adGUID			equ 72
adDate			equ 7
adDBDate		equ 133
adDBTime		equ 134
adDBTimeStamp		equ 135
adBSTR			equ 8
adChar			equ 129
adVarChar		equ 200
adLongVarChar		equ 201
adWChar			equ 130
adVarWChar		equ 202
adLongVarWChar		equ 203
adBinary		equ 128
adVarBinary		equ 204
adLongVarBinary		equ 205
adChapter		equ 136
adFileTime		equ 64
adPropVariant		equ 138
adVarNumeric		equ 139

AllowNullsEnum		typedef SDWORD
adIndexNullsAllow	equ 0
adIndexNullsDisallow	equ 1
adIndexNullsIgnore	equ 2
adIndexNullsIgnoreAny	equ 4
ObjectTypeEnum		typedef SDWORD
adPermObjProviderSpecific equ -1
adPermObjTable		equ 1
adPermObjColumn		equ 2
adPermObjDatabase	equ 3
adPermObjProcedure	equ 4
adPermObjView		equ 5
InheritTypeEnum		typedef SDWORD
adInheritNone		equ 0
adInheritObjects	equ 1
adInheritContainers	equ 2
adInheritBoth		equ 3
adInheritNoPropogate	equ 4
externdef		__MIDL_itf_adocat_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_adocat_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE
ifndef __ADOX_LIBRARY_DEFINED__
__ADOX_LIBRARY_DEFINED__ equ 1
externdef		LIBID_ADOX:IID
ifndef ___ADOCollection_INTERFACE_DEFINED__
___ADOCollection_INTERFACE_DEFINED__ equ 1

externdef		IID__ADOCollection:IID

.comdef ADOCollection

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    .ends

endif
ifndef ___ADODynaCollection_INTERFACE_DEFINED__
___ADODynaCollection_INTERFACE_DEFINED__ equ 1

externdef		IID__ADODynaCollection:IID

.comdef ADODynaCollection

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    Append		proc :ptr
    Delete		proc :VARIANT
    .ends

endif
ifndef ___Catalog_INTERFACE_DEFINED__
___Catalog_INTERFACE_DEFINED__ equ 1

externdef		IID__Catalog:IID

.comdef Catalog

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Tables		proc :ptr
    get_ActiveConnection proc :ptr
    put_ActiveConnection proc :VARIANT
    putref_ActiveConnection proc :ptr
    get_Procedures	proc :ptr
    get_Views		proc :ptr
    get_Groups		proc :ptr
    get_Users		proc :ptr
    Create		proc :BSTR, :ptr
    GetObjectOwner	proc :BSTR, :ObjectTypeEnum, :VARIANT, :ptr
    SetObjectOwner	proc :BSTR, :ObjectTypeEnum, :BSTR, :VARIANT
    .ends

endif
ifndef ___Table_INTERFACE_DEFINED__
___Table_INTERFACE_DEFINED__ equ 1

externdef		IID__Table:IID

.comdef Table

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Columns		proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Type		proc :ptr
    get_Indexes		proc :ptr
    get_Keys		proc :ptr
    get_Properties	proc :ptr
    get_DateCreated	proc :ptr
    get_DateModified	proc :ptr
    get_ParentCatalog	proc :ptr
    put_ParentCatalog	proc :ptr
    putref_ParentADOCatalog proc :ptr
    .ends

endif
ifndef ___Group25_INTERFACE_DEFINED__
___Group25_INTERFACE_DEFINED__ equ 1

externdef		IID__Group25:IID

.comdef Group25

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    GetPermissions	proc :VARIANT, :ObjectTypeEnum, :VARIANT, :ptr
    SetPermissions	proc :VARIANT, :ObjectTypeEnum, :ActionEnum, :RightsEnum, :InheritTypeEnum, :VARIANT
    get_Users		proc :ptr
    .ends

endif
ifndef ___Group_INTERFACE_DEFINED__
___Group_INTERFACE_DEFINED__ equ 1

externdef		IID__Group:IID

.comdef _Group

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    GetPermissions	proc :VARIANT, :ObjectTypeEnum, :VARIANT, :ptr
    SetPermissions	proc :VARIANT, :ObjectTypeEnum, :ActionEnum, :RightsEnum, :InheritTypeEnum, :VARIANT
    get_Users		proc :ptr
    get_Properties	proc :ptr
    get_ParentCatalog	proc :ptr
    put_ParentCatalog	proc :ptr
    putref_ParentADOCatalog proc :ptr
    .ends

endif
ifndef ___User25_INTERFACE_DEFINED__
___User25_INTERFACE_DEFINED__ equ 1

externdef		IID__User25:IID

.comdef User25

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    GetPermissions	proc :VARIANT, :ObjectTypeEnum, :VARIANT, :ptr
    SetPermissions	proc :VARIANT, :ObjectTypeEnum, :ActionEnum, :RightsEnum, :InheritTypeEnum, :VARIANT
    ChangePassword	proc :BSTR, :BSTR
    get_Groups		proc :ptr
    .ends

endif
ifndef ___User_INTERFACE_DEFINED__
___User_INTERFACE_DEFINED__ equ 1

externdef		IID__User:IID

.comdef User

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    GetPermissions	proc :VARIANT, :ObjectTypeEnum, :VARIANT, :ptr
    SetPermissions	proc :VARIANT, :ObjectTypeEnum, :ActionEnum, :RightsEnum, :InheritTypeEnum, :VARIANT
    ChangePassword	proc :BSTR, :BSTR
    get_Groups		proc :ptr
    get_Properties	proc :ptr
    get_ParentCatalog	proc :ptr
    put_ParentCatalog	proc :ptr
    putref_ParentADOCatalog proc :ptr
    .ends

endif
ifndef ___Column_INTERFACE_DEFINED__
___Column_INTERFACE_DEFINED__ equ 1

externdef		IID__Column:IID

.comdef Column

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Attributes	proc :ptr
    put_Attributes	proc :ColumnAttributesEnum
    get_DefinedSize	proc :ptr
    put_DefinedSize	proc :LONG
    get_NumericScale	proc :ptr
    put_NumericScale	proc :BYTE
    get_Precision	proc :ptr
    put_Precision	proc :LONG
    get_RelatedColumn	proc :ptr
    put_RelatedColumn	proc :BSTR
    get_SortOrder	proc :ptr
    put_SortOrder	proc :SortOrderEnum
    get_Type		proc :ptr
    put_Type		proc :DataTypeEnum
    get_Properties	proc :ptr
    get_ParentCatalog	proc :ptr
    put_ParentCatalog	proc :ptr
    putref_ParentADOCatalog proc :ptr
    .ends

endif
ifndef ___Index_INTERFACE_DEFINED__
___Index_INTERFACE_DEFINED__ equ 1

externdef		IID__Index:IID

.comdef Index

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Clustered	proc :ptr
    put_Clustered	proc :VARIANT_BOOL
    get_IndexNulls	proc :ptr
    put_IndexNulls	proc :AllowNullsEnum
    get_PrimaryKey	proc :ptr
    put_PrimaryKey	proc :VARIANT_BOOL
    get_Unique		proc :ptr
    put_Unique		proc :VARIANT_BOOL
    get_Columns		proc :ptr
    get_Properties	proc :ptr
    .ends

endif
ifndef ___Key_INTERFACE_DEFINED__
___Key_INTERFACE_DEFINED__ equ 1

externdef		IID__Key:IID

.comdef Key

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_DeleteRule	proc :ptr
    put_DeleteRule	proc :RuleEnum
    get_Type		proc :ptr
    put_Type		proc :KeyTypeEnum
    get_RelatedTable	proc :ptr
    put_RelatedTable	proc :BSTR
    get_UpdateRule	proc :ptr
    put_UpdateRule	proc :RuleEnum
    get_Columns		proc :ptr
    .ends

endif
ifndef __View_INTERFACE_DEFINED__
__View_INTERFACE_DEFINED__ equ 1

externdef		IID_View:IID

.comdef View

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Command		proc :ptr
    put_Command		proc :VARIANT
    putref_Command	proc :ptr
    get_Name		proc :ptr
    get_DateCreated	proc :ptr
    get_DateModified	proc :ptr
    .ends

endif
ifndef __Procedure_INTERFACE_DEFINED__
__Procedure_INTERFACE_DEFINED__ equ 1

externdef		IID_Procedure:IID

.comdef Procedure

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Command		proc :ptr
    put_Command		proc :VARIANT
    putref_Command	proc :ptr
    get_Name		proc :ptr
    get_DateCreated	proc :ptr
    get_DateModified	proc :ptr
    .ends

endif
externdef		CLSID_Catalog:CLSID
externdef		CLSID_Table:CLSID
ifndef __Property_INTERFACE_DEFINED__
__Property_INTERFACE_DEFINED__ equ 1

externdef		IID_Property:IID

.comdef Property

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Value		proc :ptr
    put_Value		proc :VARIANT
    get_Name		proc :ptr
    get_Type		proc :ptr
    get_Attributes	proc :ptr
    put_Attributes	proc :LONG
    .ends

endif
externdef		CLSID_Group:CLSID
externdef		CLSID_User:CLSID
externdef		CLSID_Column:CLSID
externdef		CLSID_Index:CLSID
externdef		CLSID_Key:CLSID
ifndef __Tables_INTERFACE_DEFINED__
__Tables_INTERFACE_DEFINED__ equ 1

externdef		IID_Tables:IID

.comdef Tables

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :VARIANT
    Delete		proc :VARIANT
    .ends

endif
ifndef __Columns_INTERFACE_DEFINED__
__Columns_INTERFACE_DEFINED__ equ 1

externdef		IID_Columns:IID

.comdef Columns

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :VARIANT, :DataTypeEnum, :LONG
    Delete		proc :VARIANT
    .ends

endif
ifndef __Procedures_INTERFACE_DEFINED__
__Procedures_INTERFACE_DEFINED__ equ 1

externdef		IID_Procedures:IID

.comdef Procedures

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :BSTR, :ptr
    Delete		proc :VARIANT
    .ends

endif
ifndef __Views_INTERFACE_DEFINED__
__Views_INTERFACE_DEFINED__ equ 1

externdef		IID_Views:IID

.comdef Views

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :BSTR, :ptr
    Delete		proc :VARIANT
    .ends

endif
ifndef __Indexes_INTERFACE_DEFINED__
__Indexes_INTERFACE_DEFINED__ equ 1

externdef		IID_Indexes:IID

.comdef Indexes

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :VARIANT, :VARIANT
    Delete		proc :VARIANT
    .ends

endif
ifndef __Keys_INTERFACE_DEFINED__
__Keys_INTERFACE_DEFINED__ equ 1

externdef		IID_Keys:IID

.comdef Keys

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :VARIANT, :KeyTypeEnum, :VARIANT, :BSTR, :BSTR
    Delete		proc :VARIANT
    .ends

endif
ifndef __Users_INTERFACE_DEFINED__
__Users_INTERFACE_DEFINED__ equ 1

externdef		IID_Users:IID

.comdef Users

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :VARIANT, :BSTR
    Delete		proc :VARIANT
    .ends

endif
ifndef __Groups_INTERFACE_DEFINED__
__Groups_INTERFACE_DEFINED__ equ 1

externdef		IID_Groups:IID

.comdef Groups

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    Append		proc :VARIANT
    Delete		proc :VARIANT
    .ends

endif
ifndef __Properties_INTERFACE_DEFINED__
__Properties_INTERFACE_DEFINED__ equ 1

externdef		IID_Properties:IID

.comdef Properties

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    .ends

endif
endif
endif
endif
