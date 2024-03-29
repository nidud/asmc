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

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __filter_h__
define __filter_h__

include unknwn.inc
include objidl.inc
include propidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef _TAGFULLPROPSPEC_DEFINED_
define _TAGFULLPROPSPEC_DEFINED_
FULLPROPSPEC		STRUC
guidPropSet		GUID <>
psProperty		PROPSPEC <>
FULLPROPSPEC		ENDS
endif

ifndef __IFilter_INTERFACE_DEFINED__
define __IFilter_INTERFACE_DEFINED__

ifndef _IFILTER_INIT_DEFINED
define _IFILTER_INIT_DEFINED

.enum IFILTER_INIT {
    IFILTER_INIT_CANON_PARAGRAPHS	= 1,
    IFILTER_INIT_HARD_LINE_BREAKS	= 2,
    IFILTER_INIT_CANON_HYPHENS	= 4,
    IFILTER_INIT_CANON_SPACES	= 8,
    IFILTER_INIT_APPLY_INDEX_ATTRIBUTES = 16,
    IFILTER_INIT_APPLY_OTHER_ATTRIBUTES = 32,
    IFILTER_INIT_APPLY_CRAWL_ATTRIBUTES = 256,
    IFILTER_INIT_INDEXING_ONLY	= 64,
    IFILTER_INIT_SEARCH_LINKS	= 128,
    IFILTER_INIT_FILTER_OWNED_VALUE_OK	= 512,
    IFILTER_INIT_FILTER_AGGRESSIVE_BREAK	= 1024,
    IFILTER_INIT_DISABLE_EMBEDDED	= 2048,
    IFILTER_INIT_EMIT_FORMATTING	= 4096
    }

endif

ifndef _IFILTER_FLAGS_DEFINED
define _IFILTER_FLAGS_DEFINED
.enum IFILTER_FLAGS {
    IFILTER_FLAGS_OLE_PROPERTIES = 1
    }
endif

ifndef _CHUNKSTATE_DEFINED
define _CHUNKSTATE_DEFINED
.enum CHUNKSTATE {
    CHUNK_TEXT	= 0x1,
    CHUNK_VALUE = 0x2,
    CHUNK_FILTER_OWNED_VALUE = 0x4
    }
endif

ifndef _CHUNK_BREAKTYPE_DEFINED
define _CHUNK_BREAKTYPE_DEFINED
.enum CHUNK_BREAKTYPE {
    CHUNK_NO_BREAK = 0,
    CHUNK_EOW	= 1,
    CHUNK_EOS	= 2,
    CHUNK_EOP	= 3,
    CHUNK_EOC	= 4
    }
endif

ifndef _FILTERREGION_DEFINED
define _FILTERREGION_DEFINED
FILTERREGION		STRUC
idChunk			ULONG ?
cwcStart		ULONG ?
cwcExtent		ULONG ?
FILTERREGION		ENDS
endif

ifndef _STAT_CHUNK_DEFINED
define _STAT_CHUNK_DEFINED
STAT_CHUNK		STRUC
idChunk			ULONG ?
breakType		CHUNK_BREAKTYPE ?
flags			CHUNKSTATE ?
locale			LCID ?
attribute		FULLPROPSPEC <>
idChunkSource		ULONG ?
cwcStartSource		ULONG ?
cwcLenSource		ULONG ?
STAT_CHUNK		ENDS
endif

DEFINE_IIDX(IFilter, "89BCB740-6119-101A-BCB7-00DD010655AF")

.comdef IFilter : public IUnknown

    Init		proc :ULONG, :ULONG, :ptr, :ptr
    GetChunk		proc :ptr
    GetText		proc :ptr, :ptr
    GetValue		proc :ptr
    BindRegion		proc :FILTERREGION, :REFIID, :ptr
   .ends

endif

endif
endif
