ifndef _DIACREATE_H_
_DIACREATE_H_ equ <>

;HRESULT
NoRegCoCreate proto WINAPI \
               dllName: ptr wchar_t,
                rclsid: REFCLSID,
                  riid: REFIID,
                   ppv: ptr ptr

endif
