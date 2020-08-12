ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __tvratings_h__
__tvratings_h__ equ <>

ifndef __IXDSToRat_FWD_DEFINED__
__IXDSToRat_FWD_DEFINED__ equ 1
endif
ifndef __IEvalRat_FWD_DEFINED__
__IEvalRat_FWD_DEFINED__ equ 1
endif
ifndef __XDSToRat_FWD_DEFINED__
__XDSToRat_FWD_DEFINED__ equ 1
endif
ifndef __EvalRat_FWD_DEFINED__
__EvalRat_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc

include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum EnTvRat_System {
    MPAA	= 0,
    US_TV	= 1,
    Canadian_English	= 2,
    Canadian_French	= 3,
    Reserved4	= 4,
    System5	= 5,
    System6	= 6,
    Reserved7	= 7,
    PBDA	= 8,
    AgeBased	= 9,
    TvRat_kSystems	= 10,
    TvRat_SystemDontKnow	= 255
    }

.enum EnTvRat_GenericLevel {
    TvRat_0	= 0,
    TvRat_1	= 1,
    TvRat_2	= 2,
    TvRat_3	= 3,
    TvRat_4	= 4,
    TvRat_5	= 5,
    TvRat_6	= 6,
    TvRat_7	= 7,
    TvRat_8	= 8,
    TvRat_9	= 9,
    TvRat_10	= 10,
    TvRat_11	= 11,
    TvRat_12	= 12,
    TvRat_13	= 13,
    TvRat_14	= 14,
    TvRat_15	= 15,
    TvRat_16	= 16,
    TvRat_17	= 17,
    TvRat_18	= 18,
    TvRat_19	= 19,
    TvRat_20	= 20,
    TvRat_21	= 21,
    TvRat_kLevels	= 22,
    TvRat_Unblock	= -1,
    TvRat_LevelDontKnow = 255
    }

.enum EnTvRat_MPAA {
    MPAA_NotApplicable	= TvRat_0,
    MPAA_G	= TvRat_1,
    MPAA_PG	= TvRat_2,
    MPAA_PG13	= TvRat_3,
    MPAA_R	= TvRat_4,
    MPAA_NC17	= TvRat_5,
    MPAA_X	= TvRat_6,
    MPAA_NotRated	= TvRat_7
    }

.enum EnTvRat_US_TV {
    US_TV_None	= TvRat_0,
    US_TV_Y	= TvRat_1,
    US_TV_Y7	= TvRat_2,
    US_TV_G	= TvRat_3,
    US_TV_PG	= TvRat_4,
    US_TV_14	= TvRat_5,
    US_TV_MA	= TvRat_6,
    US_TV_None7 = TvRat_7
    }

.enum EnTvRat_CAE_TV {
    CAE_TV_Exempt	= TvRat_0,
    CAE_TV_C	= TvRat_1,
    CAE_TV_C8	= TvRat_2,
    CAE_TV_G	= TvRat_3,
    CAE_TV_PG	= TvRat_4,
    CAE_TV_14	= TvRat_5,
    CAE_TV_18	= TvRat_6,
    CAE_TV_Reserved	= TvRat_7
    }

.enum EnTvRat_CAF_TV {
    CAF_TV_Exempt	= TvRat_0,
    CAF_TV_G	= TvRat_1,
    CAF_TV_8	= TvRat_2,
    CAF_TV_13	= TvRat_3,
    CAF_TV_16	= TvRat_4,
    CAF_TV_18	= TvRat_5,
    CAF_TV_Reserved6	= TvRat_6,
    CAF_TV_Reserved	= TvRat_7
    }

.enum BfEnTvRat_GenericAttributes {
    BfAttrNone	= 0,
    BfIsBlocked = 1,
    BfIsAttr_1	= 2,
    BfIsAttr_2	= 4,
    BfIsAttr_3	= 8,
    BfIsAttr_4	= 16,
    BfIsAttr_5	= 32,
    BfIsAttr_6	= 64,
    BfIsAttr_7	= 128,
    BfValidAttrSubmask	= 255
    }

.enum BfEnTvRat_Attributes_US_TV {
    US_TV_IsBlocked	= BfIsBlocked,
    US_TV_IsViolent	= BfIsAttr_1,
    US_TV_IsSexualSituation	= BfIsAttr_2,
    US_TV_IsAdultLanguage	= BfIsAttr_3,
    US_TV_IsSexuallySuggestiveDialog	= BfIsAttr_4,
    US_TV_ValidAttrSubmask	= 31
    }

.enum BfEnTvRat_Attributes_MPAA {
    MPAA_IsBlocked	= BfIsBlocked,
    MPAA_ValidAttrSubmask	= 1
    }

.enum BfEnTvRat_Attributes_CAE_TV {
    CAE_IsBlocked	= BfIsBlocked,
    CAE_ValidAttrSubmask	= 1
    }

.enum BfEnTvRat_Attributes_CAF_TV {
    CAF_IsBlocked	= BfIsBlocked,
    CAF_ValidAttrSubmask	= 1
    }

ifndef __IXDSToRat_INTERFACE_DEFINED__
__IXDSToRat_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXDSToRat, "C5C5C5B0-3ABC-11D6-B25B-00C04FA0C026")

.comdef IXDSToRat : public IDispatch

    Init		proc
    ParseXDSBytePair	proc :BYTE, :BYTE, :ptr, :ptr, :ptr
    .ends

endif

ifndef __IEvalRat_INTERFACE_DEFINED__
__IEvalRat_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEvalRat, "C5C5C5B1-3ABC-11D6-B25B-00C04FA0C026")

.comdef IEvalRat : public IDispatch

    get_BlockedRatingAttributes proc :EnTvRat_System, :EnTvRat_GenericLevel, :ptr LONG
    put_BlockedRatingAttributes proc :EnTvRat_System, :EnTvRat_GenericLevel, :LONG
    get_BlockUnRated	proc :ptr BOOL
    put_BlockUnRated	proc :BOOL
    MostRestrictiveRating proc :EnTvRat_System, :EnTvRat_GenericLevel, :LONG, :EnTvRat_System,
	:EnTvRat_GenericLevel, :LONG, :ptr EnTvRat_System, :ptr EnTvRat_GenericLevel, :ptr LONG
    TestRating proc :EnTvRat_System, :EnTvRat_GenericLevel, :LONG
    .ends

endif

ifndef __TVRATINGSLib_LIBRARY_DEFINED__
__TVRATINGSLib_LIBRARY_DEFINED__ equ 1

externdef LIBID_TVRATINGSLib:IID

DEFINE_GUIDS(CLSID_XDSToRat, "C5C5C5F0-3ABC-11D6-B25B-00C04FA0C026")
DEFINE_GUIDS(CLSID_EvalRat, "C5C5C5F1-3ABC-11D6-B25B-00C04FA0C026")

endif
endif
endif


