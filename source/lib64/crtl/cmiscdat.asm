
ifndef CRTDLL

include cruntime.inc
include internal.inc
include stdlib.inc
include fltintrn.inc

;;-
;;  ... table of (model-dependent) code pointers ...
;;
;;  Entries all point to _fptrap by default,
;;  but are changed to point to the appropriate
;;  routine if the _fltused initializer (_cfltcvt_init)
;;  is linked in.
;;
;;  if the _fltused modules are linked in, then the
;;  _cfltcvt_init initializer sets the entries of
;;  _cfltcvt_tab.
;;
CALLBACK(PFV)

    .data
    _cfltcvt_tab PFV 10 dup(_fptrap)

    .code

_initp_misc_cfltcvt_tab proc frame uses rsi rbx

    .for (rsi = &_cfltcvt_tab,
          ebx = 0 : ebx < _countof(_cfltcvt_tab) : ++ebx, rsi += sizeof(PFV))

        mov [rsi],EncodePointer([rsi])
    .endf
    ret

_initp_misc_cfltcvt_tab endp

endif

    end
