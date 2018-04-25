ifndef ADC_INCLUDED
ADC_INCLUDED equ <>
.pragma list(push, 0)

_CLSID_FoxRowset	  equ <{0x3ff292b6,0xb204,0x11cf,{0x8d,0x23,0x0,0xaa,0x00,0x5f,0xfe,0x58}}>
_DBPROPSET_ADC		  equ <{0xb68e3cc1,0x6deb,0x11d0,{0x8d,0xf6,0x0,0xaa,0x00,0x5f,0xfe,0x58}}>
_IID_IAsyncAllowed	  equ <{0xf5f2893a,0xba9e,0x11d0,{0xab,0xb9,0x0,0xc0,0x4f,0xc2,0x9f,0x8f}}>
_IID_IRowsetADCExtensions equ <{0xF17324c4,0x68E0,0x11D0,{0xAD,0x45,0x0,0xC0,0x4F,0xC2,0x98,0x63}}>
_IID_IUpdateInfo	  equ <{0xa0385420,0x62b8,0x11d1,{0x9a,0x06,0x0,0xa0,0xc9,0x03,0xaa,0x45}}>
_IID_IRowsetSynchronize	  equ <{0x1be41e60,0x807a,0x11d1,{0x9a,0x14,0x0,0xa0,0xc9,0x03,0xaa,0x45}}>
_IID_IRowsetProperties	  equ <{0x1e837070,0xbcfc,0x11d1,{0x9a,0x2c,0x0,0xa0,0xc9,0x03,0xaa,0x45}}>

ADCPROPENUM		typedef SDWORD
DBPROP_ADC_ASYNCHFETCHSIZE equ 3
DBPROP_ADC_BATCHSIZE	equ 4
DBPROP_ADC_UPDATECRITERIA equ 5
DBPROP_ADC_ASYNCHPREFETCHSIZE equ 7
DBPROP_ADC_ASYNCHTHREADPRIORITY equ 8
DBPROP_ADC_CACHECHILDROWS equ 9
DBPROP_ADC_MAINTAINCHANGESTATUS equ 10
DBPROP_ADC_AUTORECALC	equ 11
DBPROP_ADC_UNIQUETABLE	equ 13
DBPROP_ADC_UNIQUESCHEMA equ 14
DBPROP_ADC_UNIQUECATALOG equ 15
DBPROP_ADC_CUSTOMRESYNCH equ 16
DBPROP_ADC_CEVER	equ 17
DBPROP_ADC_RESHAPENAME	equ 18
DBPROP_ADC_UPDATERESYNC equ 19
DBPROP_ADC_BACKINGSTORE equ 21
DBPROP_ADC_RELEASESHAPEONDISCONNECT equ 22


ifndef _COMMON_ADC_AND_ADO_PROPS_
_COMMON_ADC_AND_ADO_PROPS_ equ 1

ADCPROP_UPDATECRITERIA_ENUM typedef SDWORD
adCriteriaKey		equ 0
adCriteriaAllCols	equ 1
adCriteriaUpdCols	equ 2
adCriteriaTimeStamp	equ 3

ADCPROP_ASYNCTHREADPRIORITY_ENUM typedef SDWORD
adPriorityLowest	equ 1
adPriorityBelowNormal	equ 2
adPriorityNormal	equ 3
adPriorityAboveNormal	equ 4
adPriorityHighest	equ 5

ADCPROP_UPDATERESYNC_ENUM typedef SDWORD
adResyncNone		equ 0
adResyncAutoIncrement	equ 1
adResyncConflicts	equ 2
adResyncUpdates		equ 4
adResyncInserts		equ 8
adResyncAll		equ 0xF

ADCPROP_AUTORECALC_ENUM typedef SDWORD
adRecalcUpFront		equ 0
adRecalcAlways		equ 1
endif

FOXROWSETPROPENUM	typedef SDWORD
DBPROP_FOXTABLENAME	equ 0xeeff

.pragma list(pop)
endif
