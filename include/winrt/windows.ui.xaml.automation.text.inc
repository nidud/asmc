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

ifndef __windows2Eui2Examl2Eautomation2Etext_h__
define __windows2Eui2Examl2Eautomation2Etext_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Automation
.namespace Text

.enum TextPatternRangeEndpoint {
    TextPatternRangeEndpoint_Start  = 0,
    TextPatternRangeEndpoint_End    = 1
    }

.enum TextUnit {
    TextUnit_Character  = 0,
    TextUnit_Format     = 1,
    TextUnit_Word       = 2,
    TextUnit_Line       = 3,
    TextUnit_Paragraph  = 4,
    TextUnit_Page       = 5,
    TextUnit_Document   = 6
    }

.endn
.endn
.endn
.endn
.endn

endif
