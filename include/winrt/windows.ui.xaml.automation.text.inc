ifndef _RPC500_
include rpc500.inc
endif
ifndef __windows2Eui2Examl2Eautomation2Etext_h__
define __windows2Eui2Examl2Eautomation2Etext_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Automation
.namespace Text

.enum TextPatternRangeEndpoint {
    TextPatternRangeEndpoint_Start,
    TextPatternRangeEndpoint_End
    }

.enum TextUnit {
    TextUnit_Character,
    TextUnit_Format,
    TextUnit_Word,
    TextUnit_Line,
    TextUnit_Paragraph,
    TextUnit_Page,
    TextUnit_Document
    }

.endn
.endn
.endn
.endn
.endn

endif
