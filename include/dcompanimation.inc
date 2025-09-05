ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __dcompanimation_h__
define __dcompanimation_h__

include wtypes.inc
ifndef __unknwn_h__
include unknwn.inc
endif

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
