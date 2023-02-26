ifndef __IGraphicsCaptureItemInterop_INTERFACE_DEFINED__
define __IGraphicsCaptureItemInterop_INTERFACE_DEFINED__

include windows.ui.composition.inc
include windows.graphics.capture.inc

DEFINE_IIDX(IGraphicsCaptureItemInterop, "3628E81B-3CAC-4C60-B7F4-23CE0E0C3356")

.comdef IGraphicsCaptureItemInterop : public IUnknown

    CreateForWindow     proc :HWND, :REFIID, :ptr ptr
    CreateForMonitor    proc :HMONITOR, :REFIID, :ptr ptr
   .ends

endif
