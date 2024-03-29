ifndef _MSADERR_H_
define _MSADERR_H_

ifndef FACILITY_WINDOWS
FACILITY_WINDOWS	equ 0x8
FACILITY_STORAGE	equ 0x3
FACILITY_ITF		equ 0x4
STATUS_SEVERITY_SUCCESS equ 0x0
STATUS_SEVERITY_COERROR equ 0x2
DB_E_BOGUS		equ 0x80040EFF
endif

ifndef OLEDBVER
OLEDBVER		equ 0x0270
endif

DB_E_BADACCESSORHANDLE	equ 0x80040E00
DB_E_ROWLIMITEXCEEDED	equ 0x80040E01
DB_E_READONLYACCESSOR	equ 0x80040E02
DB_E_SCHEMAVIOLATION	equ 0x80040E03
DB_E_BADROWHANDLE	equ 0x80040E04
DB_E_OBJECTOPEN		equ 0x80040E05

if OLEDBVER GE 0x0150
DB_E_BADCHAPTER		equ 0x80040E06
endif

DB_E_CANTCONVERTVALUE	equ 0x80040E07
DB_E_BADBINDINFO	equ 0x80040E08
DB_SEC_E_PERMISSIONDENIED equ 0x80040E09
DB_E_NOTAREFERENCECOLUMN equ 0x80040E0A

if OLEDBVER GE 0x0250
DB_E_LIMITREJECTED	equ 0x80040E0B
endif

DB_E_NOCOMMAND		equ 0x80040E0C
if OLEDBVER GE 0x0250
DB_E_COSTLIMIT		equ 0x80040E0D
endif

DB_E_BADBOOKMARK	equ 0x80040E0E
DB_E_BADLOCKMODE	equ 0x80040E0F
DB_E_PARAMNOT0x80040E10 equ 1
DB_E_BADCOLUMNID	equ 0x80040E11
DB_E_BADRATIO		equ 0x80040E12

if OLEDBVER GE 0x0200
DB_E_BADVALUES		equ 0x80040E13
endif

DB_E_ERRORSINCOMMAND	equ 0x80040E14
DB_E_CANTCANCEL		equ 0x80040E15
DB_E_DIALECTNOTSUPPORTED equ 0x80040E16
DB_E_DUPLICATEDATASOURCE equ 0x80040E17
DB_E_CANNOTRESTART	equ 0x80040E18
DB_E_NOTFOUND		equ 0x80040E19
DB_E_NEWLYINSERTED	equ 0x80040E1B

if OLEDBVER GE 0x0250
DB_E_CANNOTFREE		equ 0x80040E1A
DB_E_GOALREJECTED	equ 0x80040E1C
endif

DB_E_UNSUPPORTEDCONVERSION equ 0x80040E1D
DB_E_BADSTARTPOSITION	equ 0x80040E1E

if OLEDBVER GE 0x0200
DB_E_NOQUERY		equ 0x80040E1F
endif

DB_E_NOTREENTRANT	equ 0x80040E20
DB_E_ERRORSOCCURRED	equ 0x80040E21
DB_E_NOAGGREGATION	equ 0x80040E22
DB_E_DELETEDROW		equ 0x80040E23
DB_E_CANTFETCHBACKWARDS equ 0x80040E24
DB_E_ROWSNOTRELEASED	equ 0x80040E25
DB_E_BADSTORAGEFLAG	equ 0x80040E26

if OLEDBVER GE 0x0150
DB_E_BADCOMPAREOP	equ 0x80040E27
endif

DB_E_BADSTATUSVALUE	equ 0x80040E28
DB_E_CANTSCROLLBACKWARDS equ 0x80040E29

if OLEDBVER GE 0x0250
DB_E_BADREGIONHANDLE	equ 0x80040E2A
DB_E_NONCONTIGUOUSRANGE equ 0x80040E2B
DB_E_INVALIDTRANSITION	equ 0x80040E2C
DB_E_NOTASUBREGION	equ 0x80040E2D
endif

DB_E_MULTIPLESTATEMENTS equ 0x80040E2E
DB_E_INTEGRITYVIOLATION equ 0x80040E2F
DB_E_BADTYPENAME	equ 0x80040E30
DB_E_ABORTLIMITREACHED	equ 0x80040E31

if OLEDBVER GE 0x0200
DB_E_ROWSETINCOMMAND	equ 0x80040E32
DB_E_CANTTRANSLATE	equ 0x80040E33
endif

DB_E_DUPLICATEINDEXID	equ 0x80040E34
DB_E_NOINDEX		equ 0x80040E35
DB_E_INDEXINUSE		equ 0x80040E36
DB_E_NOTABLE		equ 0x80040E37
DB_E_CONCURRENCYVIOLATION equ 0x80040E38
DB_E_BADCOPY		equ 0x80040E39
DB_E_BADPRECISION	equ 0x80040E3A
DB_E_BADSCALE		equ 0x80040E3B
DB_E_BADTABLEID		equ 0x80040E3C
DB_E_BADID		equ DB_E_BADTABLEID
DB_E_BADTYPE		equ 0x80040E3D
DB_E_DUPLICATECOLUMNID	equ 0x80040E3E
DB_E_DUPLICATETABLEID	equ 0x80040E3F
DB_E_TABLEINUSE		equ 0x80040E40
DB_E_NOLOCALE		equ 0x80040E41
DB_E_BADRECORDNUM	equ 0x80040E42
DB_E_BOOKMARKSKIPPED	equ 0x80040E43
DB_E_BADPROPERTYVALUE	equ 0x80040E44
DB_E_INVALID		equ 0x80040E45
DB_E_BADACCESSORFLAGS	equ 0x80040E46
DB_E_BADSTORAGEFLAGS	equ 0x80040E47
DB_E_BYREFACCESSORNOTSUPPORTED equ 0x80040E48
DB_E_NULLACCESSORNOTSUPPORTED equ 0x80040E49
DB_E_NOTPREPARED	equ 0x80040E4A
DB_E_BADACCESSORTYPE	equ 0x80040E4B
DB_E_WRITEONLYACCESSOR	equ 0x80040E4C
DB_SEC_E_AUTH_FAILED	equ 0x80040E4D
DB_E_CANCELED		equ 0x80040E4E

if OLEDBVER GE 0x0200
DB_E_CHAPTERNOTRELEASED equ 0x80040E4F
endif

DB_E_BADSOURCEHANDLE	equ 0x80040E50
DB_E_PARAMUNAVAILABLE	equ 0x80040E51
DB_E_ALREADYINITIALIZED equ 0x80040E52
DB_E_NOTSUPPORTED	equ 0x80040E53
DB_E_MAXPENDCHANGESEXCEEDED equ 0x80040E54
DB_E_BADORDINAL		equ 0x80040E55
DB_E_PENDINGCHANGES	equ 0x80040E56
DB_E_DATAOVERFLOW	equ 0x80040E57
DB_E_BADHRESULT		equ 0x80040E58
DB_E_BADLOOKUPID	equ 0x80040E59
DB_E_BADDYNAMICERRORID	equ 0x80040E5A
DB_E_PENDINGINSERT	equ 0x80040E5B
DB_E_BADCONVERTFLAG	equ 0x80040E5C
DB_E_BADPARAMETERNAME	equ 0x80040E5D
DB_E_MULTIPLESTORAGE	equ 0x80040E5E
DB_E_CANTFILTER		equ 0x80040E5F
DB_E_CANTORDER		equ 0x80040E60

if OLEDBVER GE 0x0200
MD_E_BADTUPLE		equ 0x80040E61
MD_E_BADCOORDINATE	equ 0x80040E62
MD_E_INVALIDAXIS	equ 0x80040E63
MD_E_INVALIDCELLRANGE	equ 0x80040E64
DB_E_NOCOLUMN		equ 0x80040E65
DB_E_COMMANDNOTPERSISTED equ 0x80040E67
DB_E_DUPLICATEID	equ 0x80040E68
DB_E_OBJECTCREATIONLIMITREACHED equ 0x80040E69
DB_E_BADINDEXID		equ 0x80040E72
DB_E_BADINITSTRING	equ 0x80040E73
DB_E_NOPROVIDERSREGISTERED equ 0x80040E74
DB_E_MISMATCHEDPROVIDER equ 0x80040E75
DB_E_BADCOMMANDID	equ 0x80040E76
endif

if OLEDBVER GE 0x0210
SEC_E_PERMISSIONDENIED	equ DB_SEC_E_PERMISSIONDENIED
SEC_E_BADTRUSTEEID	equ 0x80040E6A
SEC_E_NOTRUSTEEID	equ 0x80040E6B
SEC_E_NOMEMBERSHIPSUPPORT equ 0x80040E6C
SEC_E_INVALIDOBJECT	equ 0x80040E6D
SEC_E_NOOWNER		equ 0x80040E6E
SEC_E_INVALIDACCESSENTRYLIST equ 0x80040E6F
SEC_E_INVALIDOWNER	equ 0x80040E70
SEC_E_INVALIDACCESSENTRY equ 0x80040E71

DB_E_BADCONSTRAINTTYPE	equ 0x80040E77
DB_E_BADCONSTRAINTFORM	equ 0x80040E78
DB_E_BADDEFERRABILITY	equ 0x80040E79
DB_E_BADMATCHTYPE	equ 0x80040E80
DB_E_BADUPDATEDELETERULE equ 0x80040E8A
DB_E_BADCONSTRAINTID	equ 0x80040E8B
DB_E_BADCOMMANDFLAGS	equ 0x80040E8C
DB_E_OBJECTMISMATCH	equ 0x80040E8D
DB_E_NOSOURCEOBJECT	equ 0x80040E91
DB_E_RESOURCELOCKED	equ 0x80040E92
DB_E_NOTCOLLECTION	equ 0x80040E93
DB_E_READONLY		equ 0x80040E94
DB_E_ASYNCNOTSUPPORTED	equ 0x80040E95
DB_E_CANNOTCONNECT	equ 0x80040E96
DB_E_TIMEOUT		equ 0x80040E97
DB_E_RESOURCEEXISTS	equ 0x80040E98
DB_E_RESOURCEOUTOFSCOPE equ 0x80040E8E
DB_E_DROPRESTRICTED	equ 0x80040E90
DB_E_DUPLICATECONSTRAINTID equ 0x80040E99
DB_E_OUTOFSPACE		equ 0x80040E9A
SEC_E_PERMISSIONDENIED	equ DB_SEC_E_PERMISSIONDENIED
endif
if OLEDBVER GE 0x0250
DB_SEC_E_SAFEMODE_DENIED equ 0x80040E9B
endif

if OLEDBVER GE 0x0260
DB_E_NOSTATISTIC	equ 0x80040E9C
DB_E_ALTERRESTRICTED	equ 0x80040E9D
DB_E_RESOURCENOTSUPPORTED equ 0x80040E9E
DB_E_NOCONSTRAINT	equ 0x80040E9F
DB_E_COLUMNUNAVAILABLE	equ 0x80040EA0

endif
DB_S_ROWLIMITEXCEEDED	equ 0x00040EC0
DB_S_COLUMNTYPEMISMATCH equ 0x00040EC1
DB_S_TYPEINFOOVERRIDDEN equ 0x00040EC2
DB_S_BOOKMARKSKIPPED	equ 0x00040EC3

if OLEDBVER GE 0x0200
DB_S_NONEXTROWSET	equ 0x00040EC5
endif

DB_S_ENDOFROWSET	equ 0x00040EC6
DB_S_COMMANDREEXECUTED	equ 0x00040EC7
DB_S_BUFFERFULL		equ 0x00040EC8
DB_S_NORESULT		equ 0x00040EC9
DB_S_CANTRELEASE	equ 0x00040ECA

if OLEDBVER GE 0x0250
DB_S_GOALCHANGED	equ 0x00040ECB
endif

if OLEDBVER GE 0x0150
DB_S_UNWANTEDOPERATION	equ 0x00040ECC
endif

DB_S_DIALECTIGNORED	equ 0x00040ECD
DB_S_UNWANTEDPHASE	equ 0x00040ECE
DB_S_UNWANTEDREASON	equ 0x00040ECF

if OLEDBVER GE 0x0150
DB_S_ASYNCHRONOUS	equ 0x00040ED0
endif

DB_S_COLUMNSCHANGED	equ 0x00040ED1
DB_S_ERRORSRETURNED	equ 0x00040ED2
DB_S_BADROWHANDLE	equ 0x00040ED3
DB_S_DELETEDROW		equ 0x00040ED4

if OLEDBVER GE 0x0250
DB_S_TOOMANYCHANGES	equ 0x00040ED5
endif

DB_S_STOPLIMITREACHED	equ 0x00040ED6
DB_S_LOCKUPGRADED	equ 0x00040ED8
DB_S_PROPERTIESCHANGED	equ 0x00040ED9
DB_S_ERRORSOCCURRED	equ 0x00040EDA
DB_S_PARAMUNAVAILABLE	equ 0x00040EDB
DB_S_MULTIPLECHANGES	equ 0x00040EDC

if OLEDBVER GE 0x0210
DB_S_NOTSINGLETON	equ 0x00040ED7
DB_S_NOROWSPECIFICCOLUMNS equ 0x00040EDD
endif

ifdef MESSAGESANDHEADERS
STG_E_FILENOTFOUND	equ 0x80030002
STG_E_PATHNOTFOUND	equ 0x80030003
STG_E_FILEALREADYEXISTS equ 0x80030050
STG_E_INVALIDHEADER	equ 0x800300FB
STG_E_INVALIDNAME	equ 0x800300FC
STG_E_OLDFORMAT		equ 0x80030104
STG_E_OLDDLL		equ 0x80030105
endif
endif
