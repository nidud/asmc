ifndef _ADOCTINT_H_
define _ADOCTINT_H_

.pragma list(push, 0)

ifndef _INC_TCHAR
include tchar.inc
endif

ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef __adocat_h__
define __adocat_h__

include oaidl.inc
include ocidl.inc

.enum RuleEnum {
	adRINone	= 0,
	adRICascade	= 1,
	adRISetNull	= 2,
	adRISetDefault	= 3
    }
.enum KeyTypeEnum {
	adKeyPrimary	= 1,
	adKeyForeign	= 2,
	adKeyUnique	= 3
    }
.enum ActionEnum {
	adAccessGrant	= 1,
	adAccessSet	= 2,
	adAccessDeny	= 3,
	adAccessRevoke	= 4
    }
.enum ColumnAttributesEnum {
	adColFixed	= 1,
	adColNullable	= 2
    }
.enum SortOrderEnum {
	adSortAscending = 1,
	adSortDescending = 2
    }
.enum RightsEnum {
	adRightNone	= 0,
	adRightDrop	= 0x100,
	adRightExclusive = 0x200,
	adRightReadDesign = 0x400,
	adRightWriteDesign = 0x800,
	adRightWithGrant = 0x1000,
	adRightReference = 0x2000,
	adRightCreate	= 0x4000,
	adRightInsert	= 0x8000,
	adRightDelete	= 0x10000,
	adRightReadPermissions = 0x20000,
	adRightWritePermissions = 0x40000,
	adRightWriteOwner = 0x80000,
	adRightMaximumAllowed = 0x2000000,
	adRightFull	= 0x10000000,
	adRightExecute	= 0x20000000,
	adRightUpdate	= 0x40000000,
	adRightRead	= 0x80000000
    }
.enum DataTypeEnum {
	adEmpty		= 0,
	adTinyInt	= 16,
	adSmallInt	= 2,
	adInteger	= 3,
	adBigInt	= 20,
	adUnsignedTinyInt = 17,
	adUnsignedSmallInt = 18,
	adUnsignedInt	= 19,
	adUnsignedBigInt = 21,
	adSingle	= 4,
	adDouble	= 5,
	adCurrency	= 6,
	adDecimal	= 14,
	adNumeric	= 131,
	adBoolean	= 11,
	adError		= 10,
	adUserDefined	= 132,
	adVariant	= 12,
	adIDispatch	= 9,
	adIUnknown	= 13,
	adGUID		= 72,
	adDate		= 7,
	adDBDate	= 133,
	adDBTime	= 134,
	adDBTimeStamp	= 135,
	adBSTR		= 8,
	adChar		= 129,
	adVarChar	= 200,
	adLongVarChar	= 201,
	adWChar		= 130,
	adVarWChar	= 202,
	adLongVarWChar	= 203,
	adBinary	= 128,
	adVarBinary	= 204,
	adLongVarBinary = 205,
	adChapter	= 136,
	adFileTime	= 64,
	adPropVariant	= 138,
	adVarNumeric	= 139
    }
.enum AllowNullsEnum {
	adIndexNullsAllow	= 0,
	adIndexNullsDisallow	= 1,
	adIndexNullsIgnore	= 2,
	adIndexNullsIgnoreAny	= 4
    }
.enum ObjectTypeEnum {
	adPermObjProviderSpecific = -1,
	adPermObjTable	= 1,
	adPermObjColumn = 2,
	adPermObjDatabase = 3,
	adPermObjProcedure = 4,
	adPermObjView	= 5
    }
.enum InheritTypeEnum {
	adInheritNone	= 0,
	adInheritObjects = 1,
	adInheritContainers = 2,
	adInheritBoth	= 3,
	adInheritNoPropogate = 4
    }

ifndef __ADOX_LIBRARY_DEFINED__
define __ADOX_LIBRARY_DEFINED__

externdef LIBID_ADOX:IID

ifndef ___ADOCollection_INTERFACE_DEFINED__
define ___ADOCollection_INTERFACE_DEFINED__

DEFINE_IIDX(_ADOCollection, "00000512-0000-0010-8000-00AA006D2EA4")

.comdef ADOCollection : public IDispatch

    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
   .ends

endif

ifndef ___ADODynaCollection_INTERFACE_DEFINED__
define ___ADODynaCollection_INTERFACE_DEFINED__

DEFINE_IIDX(_ADODynaCollection, "00000513-0000-0010-8000-00AA006D2EA4")

.comdef ADODynaCollection : public ADOCollection

    Append		proc :ptr
    Delete		proc :VARIANT
   .ends

endif

ifndef ___Catalog_INTERFACE_DEFINED__
define ___Catalog_INTERFACE_DEFINED__

DEFINE_IIDX(_Catalog, "00000603-0000-0010-8000-00AA006D2EA4")

.comdef Catalog : public IDispatch

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
define ___Table_INTERFACE_DEFINED__

DEFINE_IIDX(_Table, "00000610-0000-0010-8000-00AA006D2EA4")

.comdef Table : public IDispatch

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
define ___Group25_INTERFACE_DEFINED__

DEFINE_IIDX(_Group25, "00000616-0000-0010-8000-00AA006D2EA4")

.comdef Group25 : public IDispatch

    get_Name		proc :ptr
    put_Name		proc :BSTR
    GetPermissions	proc :VARIANT, :ObjectTypeEnum, :VARIANT, :ptr
    SetPermissions	proc :VARIANT, :ObjectTypeEnum, :ActionEnum, :RightsEnum, :InheritTypeEnum, :VARIANT
    get_Users		proc :ptr
   .ends

endif

ifndef ___Group_INTERFACE_DEFINED__
define ___Group_INTERFACE_DEFINED__

DEFINE_IIDX(_Group, "00000628-0000-0010-8000-00AA006D2EA4")

.comdef _Group : public Group25

    get_Properties	proc :ptr
    get_ParentCatalog	proc :ptr
    put_ParentCatalog	proc :ptr
    putref_ParentADOCatalog proc :ptr
   .ends

endif

ifndef ___User25_INTERFACE_DEFINED__
define ___User25_INTERFACE_DEFINED__

DEFINE_IIDX(_User25, "00000619-0000-0010-8000-00AA006D2EA4")

.comdef User25 : public IDispatch

    get_Name		proc :ptr
    put_Name		proc :BSTR
    GetPermissions	proc :VARIANT, :ObjectTypeEnum, :VARIANT, :ptr
    SetPermissions	proc :VARIANT, :ObjectTypeEnum, :ActionEnum, :RightsEnum, :InheritTypeEnum, :VARIANT
    ChangePassword	proc :BSTR, :BSTR
    get_Groups		proc :ptr
   .ends

endif

ifndef ___User_INTERFACE_DEFINED__
define ___User_INTERFACE_DEFINED__

DEFINE_IIDX(_User, "00000627-0000-0010-8000-00AA006D2EA4")

.comdef User : public User25

    get_Properties	proc :ptr
    get_ParentCatalog	proc :ptr
    put_ParentCatalog	proc :ptr
    putref_ParentADOCatalog proc :ptr
   .ends

endif

ifndef ___Column_INTERFACE_DEFINED__
define ___Column_INTERFACE_DEFINED__

DEFINE_IIDX(_Column, "0000061C-0000-0010-8000-00AA006D2EA4")

.comdef Column : public IDispatch

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
define ___Index_INTERFACE_DEFINED__

DEFINE_IIDX(_Index, "0000061F-0000-0010-8000-00AA006D2EA4")

.comdef Index : public IDispatch

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
define ___Key_INTERFACE_DEFINED__

DEFINE_IIDX(_Key, "00000622-0000-0010-8000-00AA006D2EA4")

.comdef Key : public IDispatch

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
define __View_INTERFACE_DEFINED__

DEFINE_IIDX(View, "00000613-0000-0010-8000-00AA006D2EA4")

.comdef View : public IDispatch

    get_Command		proc :ptr
    put_Command		proc :VARIANT
    putref_Command	proc :ptr
    get_Name		proc :ptr
    get_DateCreated	proc :ptr
    get_DateModified	proc :ptr
   .ends

endif

ifndef __Procedure_INTERFACE_DEFINED__
define __Procedure_INTERFACE_DEFINED__

DEFINE_IIDX(Procedure, "00000625-0000-0010-8000-00AA006D2EA4")

.comdef Procedure : public IDispatch

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
define __Property_INTERFACE_DEFINED__

DEFINE_IIDX(Property, "00000503-0000-0010-8000-00AA006D2EA4")

.comdef Property : public IDispatch

    get_Value		proc :ptr
    put_Value		proc :VARIANT
    get_Name		proc :ptr
    get_Type		proc :ptr
    get_Attributes	proc :ptr
    put_Attributes	proc :LONG
   .ends

endif

ifndef __Properties_INTERFACE_DEFINED__
define __Properties_INTERFACE_DEFINED__

DEFINE_IIDX(Properties, "00000504-0000-0010-8000-00AA006D2EA4")

.comdef Properties : public IDispatch

    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
   .ends

endif

externdef		CLSID_Group:CLSID
externdef		CLSID_User:CLSID
externdef		CLSID_Column:CLSID
externdef		CLSID_Index:CLSID
externdef		CLSID_Key:CLSID

ifndef __Tables_INTERFACE_DEFINED__
define __Tables_INTERFACE_DEFINED__

DEFINE_IIDX(Tables, "00000611-0000-0010-8000-00AA006D2EA4")

.comdef Tables : public Properties

    Append		proc :VARIANT
    Delete		proc :VARIANT
   .ends

endif

ifndef __Columns_INTERFACE_DEFINED__
define __Columns_INTERFACE_DEFINED__

DEFINE_IIDX(Columns, "0000061D-0000-0010-8000-00AA006D2EA4")

.comdef Columns : public Properties

    Append		proc :VARIANT, :DataTypeEnum, :LONG
    Delete		proc :VARIANT
   .ends

endif

ifndef __Procedures_INTERFACE_DEFINED__
define __Procedures_INTERFACE_DEFINED__

DEFINE_IIDX(Procedures, "00000626-0000-0010-8000-00AA006D2EA4")

.comdef Procedures : public Properties

    Append		proc :BSTR, :ptr
    Delete		proc :VARIANT
   .ends

endif

ifndef __Views_INTERFACE_DEFINED__
define __Views_INTERFACE_DEFINED__

DEFINE_IIDX(Views, "00000614-0000-0010-8000-00AA006D2EA4")

.comdef Views : public Properties

    Append		proc :BSTR, :ptr
    Delete		proc :VARIANT
   .ends

endif

ifndef __Indexes_INTERFACE_DEFINED__
define __Indexes_INTERFACE_DEFINED__

DEFINE_IIDX(Indexes, "00000620-0000-0010-8000-00AA006D2EA4")

.comdef Indexes : public Properties

    Append		proc :VARIANT, :VARIANT
    Delete		proc :VARIANT
   .ends

endif

ifndef __Keys_INTERFACE_DEFINED__
define __Keys_INTERFACE_DEFINED__

DEFINE_IIDX(Keys, "00000623-0000-0010-8000-00AA006D2EA4")

.comdef Keys : public Properties

    Append		proc :VARIANT, :KeyTypeEnum, :VARIANT, :BSTR, :BSTR
    Delete		proc :VARIANT
   .ends

endif

ifndef __Users_INTERFACE_DEFINED__
define __Users_INTERFACE_DEFINED__

DEFINE_IIDX(Users, "0000061A-0000-0010-8000-00AA006D2EA4")

.comdef Users : public Properties

    Append		proc :VARIANT, :BSTR
    Delete		proc :VARIANT
   .ends

endif

ifndef __Groups_INTERFACE_DEFINED__
define __Groups_INTERFACE_DEFINED__

DEFINE_IIDX(Groups, "00000617-0000-0010-8000-00AA006D2EA4")

.comdef Groups : public Properties

    Append		proc :VARIANT
    Delete		proc :VARIANT
   .ends

endif

endif
endif

.pragma list(pop)
endif
