ifndef _DIACREATE_H_
define _DIACREATE_H_

;HRESULT
NoRegCoCreate proto WINAPI \
               dllName: ptr wchar_t,
                rclsid: REFCLSID,
                  riid: REFIID,
                   ppv: ptr ptr

endif
