ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 475
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

ifndef __dcompanimation_h__
define __dcompanimation_h__

include wtypes.inc
include unknwn.inc

ifndef __IDCompositionAnimation_INTERFACE_DEFINED__
define __IDCompositionAnimation_INTERFACE_DEFINED__

DEFINE_IIDX(IDCompositionAnimation, "CBFD91D9-51B2-45e4-B3DE-D19CCFB863C5")

.comdef IDCompositionAnimation : public IUnknown

    Reset               proc
    SetAbsoluteBeginTime proc :LARGE_INTEGER
    AddCubic            proc :real8, :real4, :real4, :real4, :real4
    AddSinusoidal       proc :real8, :real4, :real4, :real4, :real4
    AddRepeat           proc :real8, :real8
    _End                proc :real8, :real4
    .ends

endif
endif
