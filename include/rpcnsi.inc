ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;;    This file contains the types and function definitions to use the
;;    Name Service Independent APIs.
;;
ifndef __RPCNSI_H__
__RPCNSI_H__ equ 1

RPC_NS_HANDLE	typedef ptr

RPC_C_NS_SYNTAX_DEFAULT		equ 0
RPC_C_NS_SYNTAX_DCE		equ 3

RPC_C_PROFILE_DEFAULT_ELT	equ 0
RPC_C_PROFILE_ALL_ELT		equ 1
RPC_C_PROFILE_ALL_ELTS		equ RPC_C_PROFILE_ALL_ET
RPC_C_PROFILE_MATCH_BY_IF	equ 2
RPC_C_PROFILE_MATCH_BY_MBR	equ 3
RPC_C_PROFILE_MATCH_BY_BOTH	equ 4

RPC_C_NS_DEFAULT_EXP_AGE	equ -1

;; Server APIs

;RPC_STATUS
RpcNsBindingExportA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
		IfSpec: RPC_IF_HANDLE,
	    BindingVec: ptr RPC_BINDING_VECTOR,
	 ObjectUuidVec: ptr UUID_VECTOR


;RPC_STATUS
RpcNsBindingUnexportA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
		IfSpec: RPC_IF_HANDLE,
	 ObjectUuidVec: ptr UUID_VECTOR

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsBindingExportW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
		IfSpec: RPC_IF_HANDLE,
	    BindingVec: ptr RPC_BINDING_VECTOR,
	 ObjectUuidVec: ptr UUID_VECTOR

;RPC_STATUS
RpcNsBindingUnexportW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
		IfSpec: RPC_IF_HANDLE,
	 ObjectUuidVec: ptr UUID_VECTOR

endif

;; Client APIs

;RPC_STATUS
RpcNsBindingLookupBeginA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
		IfSpec: RPC_IF_HANDLE,
	       ObjUuid: ptr UUID,
       BindingMaxCount: DWORD,
	 LookupContext: ptr RPC_NS_HANDLE

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsBindingLookupBeginW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
		IfSpec: RPC_IF_HANDLE,
	       ObjUuid: ptr UUID,
       BindingMaxCount: DWORD,
	 LookupContext: ptr RPC_NS_HANDLE
endif

;RPC_STATUS
RpcNsBindingLookupNext proto _CType \
	 LookupContext: RPC_NS_HANDLE,
	    BindingVec: ptr RPC_BINDING_VECTOR

;RPC_STATUS
RpcNsBindingLookupDone proto _CType \
	 LookupContext: ptr RPC_NS_HANDLE

;; Group APIs

;RPC_STATUS
RpcNsGroupDeleteA proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPBYTE

;RPC_STATUS
RpcNsGroupMbrAddA proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPBYTE,
      MemberNameSyntax: DWORD,
	    MemberName: LPBYTE

;RPC_STATUS
RpcNsGroupMbrRemoveA proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPBYTE,
      MemberNameSyntax: DWORD,
	    MemberName: LPBYTE

;RPC_STATUS
RpcNsGroupMbrInqBeginA proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPBYTE,
      MemberNameSyntax: DWORD,
	InquiryContext: ptr RPC_NS_HANDLE

;RPC_STATUS
RpcNsGroupMbrInqNextA proto _CType \
	InquiryContext: RPC_NS_HANDLE,
	    MemberName: LPBYTE

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsGroupDeleteW proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPWORD

;RPC_STATUS
RpcNsGroupMbrAddW proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPWORD,
      MemberNameSyntax: DWORD,
	    MemberName: LPWORD

;RPC_STATUS
RpcNsGroupMbrRemoveW proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPWORD,
      MemberNameSyntax: DWORD,
	    MemberName: LPWORD

;RPC_STATUS
RpcNsGroupMbrInqBeginW proto _CType \
       GroupNameSyntax: DWORD,
	     GroupName: LPWORD,
      MemberNameSyntax: DWORD,
	InquiryContext: ptr RPC_NS_HANDLE

;RPC_STATUS
RpcNsGroupMbrInqNextW proto _CType \
	InquiryContext: RPC_NS_HANDLE,
	    MemberName: LPWORD

endif

;RPC_STATUS
RpcNsGroupMbrInqDone proto _CType \
	InquiryContext: ptr RPC_NS_HANDLE

;; Profile APIs

;RPC_STATUS
RpcNsProfileDeleteA proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPBYTE

;RPC_STATUS
RpcNsProfileEltAddA proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPBYTE,
		  IfId: ptr RPC_IF_ID,
      MemberNameSyntax: DWORD,
	    MemberName: LPBYTE,
	      Priority: DWORD,
	    Annotation: LPBYTE

;RPC_STATUS
RpcNsProfileEltRemoveA proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPBYTE,
		  IfId: ptr RPC_IF_ID,
      MemberNameSyntax: DWORD,
	    MemberName: LPBYTE

;RPC_STATUS
RpcNsProfileEltInqBeginA proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPBYTE,
	   InquiryType: DWORD,
		  IfId: ptr RPC_IF_ID,
	    VersOption: DWORD,
      MemberNameSyntax: DWORD,
	    MemberName: LPBYTE,
	InquiryContext: ptr RPC_NS_HANDLE

;RPC_STATUS
RpcNsProfileEltInqNextA proto _CType \
	InquiryContext: RPC_NS_HANDLE,
		  IfId: ptr RPC_IF_ID,
	    MemberName: LPBYTE,
	      Priority: LPDWORD,
	    Annotation: LPBYTE

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsProfileDeleteW proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPWORD

;RPC_STATUS
RpcNsProfileEltAddW proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPWORD,
		  IfId: ptr RPC_IF_ID,
      MemberNameSyntax: DWORD,
	    MemberName: LPWORD,
	      Priority: DWORD,
	    Annotation: LPWORD

;RPC_STATUS
RpcNsProfileEltRemoveW proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPWORD,
		  IfId: ptr RPC_IF_ID,
      MemberNameSyntax: DWORD,
	    MemberName: LPWORD

;RPC_STATUS
RpcNsProfileEltInqBeginW proto _CType \
     ProfileNameSyntax: DWORD,
	   ProfileName: LPWORD,
	   InquiryType: DWORD,
		  IfId: ptr RPC_IF_ID,
	    VersOption: DWORD,
      MemberNameSyntax: DWORD,
	    MemberName: LPWORD,
	InquiryContext: ptr RPC_NS_HANDLE

;RPC_STATUS
RpcNsProfileEltInqNextW proto _CType \
	InquiryContext: RPC_NS_HANDLE,
		  IfId: ptr RPC_IF_ID,
	    MemberName: LPWORD,
	      Priority: LPDWORD,
	    Annotation: LPWORD

endif

;RPC_STATUS
RpcNsProfileEltInqDone proto _CType \
	InquiryContext: ptr RPC_NS_HANDLE

;; Entry object APIs

;RPC_STATUS
RpcNsEntryObjectInqBeginA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
	InquiryContext: ptr RPC_NS_HANDLE

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsEntryObjectInqBeginW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
	InquiryContext: ptr RPC_NS_HANDLE

endif

;RPC_STATUS
RpcNsEntryObjectInqNext proto _CType \
	InquiryContext: RPC_NS_HANDLE,
	       ObjUuid: ptr UUID

;RPC_STATUS
RpcNsEntryObjectInqDone proto _CType \
	InquiryContext: ptr RPC_NS_HANDLE

;; Management and MISC APIs

;RPC_STATUS
RpcNsEntryExpandNameA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
	  ExpandedName: LPBYTE

;RPC_STATUS
RpcNsMgmtBindingUnexportA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
		  IfId: ptr RPC_IF_ID,
	    VersOption: DWORD,
	 ObjectUuidVec: ptr UUID_VECTOR

;RPC_STATUS
RpcNsMgmtEntryCreateA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE

;RPC_STATUS
RpcNsMgmtEntryDeleteA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE

;RPC_STATUS
RpcNsMgmtEntryInqIfIdsA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
	       IfIdVec: ptr RPC_IF_ID_VECTOR

;RPC_STATUS
RpcNsMgmtHandleSetExpAge proto _CType \
	      NsHandle: RPC_NS_HANDLE,
	 ExpirationAge: DWORD

;RPC_STATUS
RpcNsMgmtInqExpAge proto _CType \
	 ExpirationAge: LPDWORD

;RPC_STATUS
RpcNsMgmtSetExpAge proto _CType \
	 ExpirationAge: DWORD

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsEntryExpandNameW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
	  ExpandedName: LPWORD

;RPC_STATUS
RpcNsMgmtBindingUnexportW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
		  IfId: ptr RPC_IF_ID,
	    VersOption: DWORD,
	 ObjectUuidVec: ptr UUID_VECTOR

;RPC_STATUS
RpcNsMgmtEntryCreateW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD

;RPC_STATUS
RpcNsMgmtEntryDeleteW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD

;RPC_STATUS
RpcNsMgmtEntryInqIfIdsW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
	       IfIdVec: ptr RPC_IF_ID_VECTOR

endif

;; Client API's implemented in wrappers.

;RPC_STATUS
RpcNsBindingImportBeginA proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPBYTE,
		IfSpec: RPC_IF_HANDLE,
	       ObjUuid: ptr UUID,
	 ImportContext: ptr RPC_NS_HANDLE

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsBindingImportBeginW proto _CType \
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD,
		IfSpec: RPC_IF_HANDLE,
	       ObjUuid: ptr UUID,
	 ImportContext: ptr RPC_NS_HANDLE

endif

;RPC_STATUS
RpcNsBindingImportNext proto _CType \
	 ImportContext: RPC_NS_HANDLE,
	       Binding: ptr RPC_BINDING_HANDLE

;RPC_STATUS
RpcNsBindingImportDone proto _CType \
	 ImportContext: ptr RPC_NS_HANDLE

;RPC_STATUS
RpcNsBindingSelect proto _CType \
	    BindingVec: ptr RPC_BINDING_VECTOR,
	       Binding: ptr RPC_BINDING_HANDLE

ifdef _UNICODE

RpcNsBindingLookupBegin equ <RpcNsBindingLookupBeginW>
RpcNsBindingImportBegin equ <RpcNsBindingImportBeginW>
RpcNsBindingExport	equ <RpcNsBindingExportW>
RpcNsBindingUnexport	equ <RpcNsBindingUnexportW>
RpcNsGroupDelete	equ <RpcNsGroupDeleteW>
RpcNsGroupMbrAdd	equ <RpcNsGroupMbrAddW>
RpcNsGroupMbrRemove	equ <RpcNsGroupMbrRemoveW>
RpcNsGroupMbrInqBegin	equ <RpcNsGroupMbrInqBeginW>
RpcNsGroupMbrInqNext	equ <RpcNsGroupMbrInqNextW>
RpcNsEntryExpandName	equ <RpcNsEntryExpandNameW>
RpcNsEntryObjectInqBegin equ <RpcNsEntryObjectInqBeginW>
RpcNsMgmtBindingUnexport equ <RpcNsMgmtBindingUnexportW>
RpcNsMgmtEntryCreate	equ <RpcNsMgmtEntryCreateW>
RpcNsMgmtEntryDelete	equ <RpcNsMgmtEntryDeleteW>
RpcNsMgmtEntryInqIfIds	equ <RpcNsMgmtEntryInqIfIdsW>
RpcNsProfileDelete	equ <RpcNsProfileDeleteW>
RpcNsProfileEltAdd	equ <RpcNsProfileEltAddW>
RpcNsProfileEltRemove	equ <RpcNsProfileEltRemoveW>
RpcNsProfileEltInqBegin equ <RpcNsProfileEltInqBeginW>
RpcNsProfileEltInqNext	equ <RpcNsProfileEltInqNextW>

else

RpcNsBindingLookupBegin equ <RpcNsBindingLookupBeginA>
RpcNsBindingImportBegin equ <RpcNsBindingImportBeginA>
RpcNsBindingExport	equ <RpcNsBindingExportA>
RpcNsBindingUnexport	equ <RpcNsBindingUnexportA>
RpcNsGroupDelete	equ <RpcNsGroupDeleteA>
RpcNsGroupMbrAdd	equ <RpcNsGroupMbrAddA>
RpcNsGroupMbrRemove	equ <RpcNsGroupMbrRemoveA>
RpcNsGroupMbrInqBegin	equ <RpcNsGroupMbrInqBeginA>
RpcNsGroupMbrInqNext	equ <RpcNsGroupMbrInqNextA>
RpcNsEntryExpandName	equ <RpcNsEntryExpandNameA>
RpcNsEntryObjectInqBegin equ <RpcNsEntryObjectInqBeginA>
RpcNsMgmtBindingUnexport equ <RpcNsMgmtBindingUnexportA>
RpcNsMgmtEntryCreate	equ <RpcNsMgmtEntryCreateA>
RpcNsMgmtEntryDelete	equ <RpcNsMgmtEntryDeleteA>
RpcNsMgmtEntryInqIfIds	equ <RpcNsMgmtEntryInqIfIdsA>
RpcNsProfileDelete	equ <RpcNsProfileDeleteA>
RpcNsProfileEltAdd	equ <RpcNsProfileEltAddA>
RpcNsProfileEltRemove	equ <RpcNsProfileEltRemoveA>
RpcNsProfileEltInqBegin equ <RpcNsProfileEltInqBeginA>
RpcNsProfileEltInqNext	equ <RpcNsProfileEltInqNextA>

endif ;; UNICODE

endif ;; __RPCNSI_H__

.list
