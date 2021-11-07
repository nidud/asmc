ifndef __RO_METADATA_H__
define __RO_METADATA_H__

if NTDDI_VERSION GE NTDDI_WIN8
MetaDataGetDispenser proto WINAPI \
                rclsid: REFCLSID,
                  riid: REFIID,
                   ppv: ptr ptr
endif

endif
