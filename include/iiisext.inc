include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 475
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef __iiisext_h__
define __iiisext_h__

ifndef __IISExt_LIBRARY_DEFINED__
define __IISExt_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_IISExt, 0x2a56ea30,0xafeb,0x11d1,0x98,0x68,0x00,0xa0,0xc9,0x22,0xe7,0x03)

ifndef __IISApplicationPool_INTERFACE_DEFINED__
define __IISApplicationPool_INTERFACE_DEFINED__

DEFINE_IIDX(IISApplicationPool, "0B3CB1E1-829A-4c06-8B09-F56DA1894C88")

.comdef IISApplicationPool : public IADs
    Recycle             proc
    EnumAppsInPool      proc :ptr
    Start               proc
    Stop                proc
   .ends

endif

ifndef __IISApplicationPools_INTERFACE_DEFINED__
define __IISApplicationPools_INTERFACE_DEFINED__

DEFINE_IIDX(IISApplicationPools, "587F123F-49B4-49dd-939E-F4547AA3FA75")

.comdef IISApplicationPools : public IADs
   .ends

endif

ifndef __IISWebService_INTERFACE_DEFINED__
define __IISWebService_INTERFACE_DEFINED__

DEFINE_IIDX(IISWebService, "EE46D40C-1B38-4a02-898D-358E74DFC9D2")

.comdef IISWebService : public IADs
    GetCurrentMode      proc :ptr
    CreateNewSite       proc :BSTR, :ptr, :BSTR, :VARIANT, :ptr
    EnableApplication   proc :BSTR
    RemoveApplication   proc :BSTR
    ListApplications    proc :ptr
    AddDependency       proc :BSTR, :BSTR
    RemoveDependency    proc :BSTR, :BSTR
    EnableWebServiceExtension proc :BSTR
    DisableWebServiceExtension proc :BSTR
    ListWebServiceExtensions proc :ptr
    EnableExtensionFile proc :BSTR
    DisableExtensionFile proc :BSTR
    AddExtensionFile    proc :BSTR, :VARIANT, :BSTR, :VARIANT, :BSTR
    DeleteExtensionFileRecord proc :BSTR
    ListExtensionFiles  proc :ptr
    QueryGroupIDStatus  proc :BSTR, :ptr
   .ends

endif

ifndef __IISDsCrMap_INTERFACE_DEFINED__
define __IISDsCrMap_INTERFACE_DEFINED__

DEFINE_IIDX(IISDsCrMap, "edcd6a60-b053-11d0-a62f-00a0c922e752")

.comdef IISDsCrMap : public IADs
    CreateMapping       proc :VARIANT, :BSTR, :BSTR, :BSTR, :LONG
    GetMapping          proc :LONG, :VARIANT, :ptr, :ptr, :ptr, :ptr, :ptr
    DeleteMapping       proc :LONG, :VARIANT
    SetEnabled          proc :LONG, :VARIANT, :LONG
    SetName             proc :LONG, :VARIANT, :BSTR
    SetPwd              proc :LONG, :VARIANT, :BSTR
    SetAcct             proc :LONG, :VARIANT, :BSTR
   .ends

endif

ifndef __IISApp_INTERFACE_DEFINED__
define __IISApp_INTERFACE_DEFINED__

DEFINE_IIDX(IISApp, "46FBBB80-0192-11d1-9C39-00A0C922E703")

.comdef IISApp : public IADs
    AppCreate           proc :VARIANT_BOOL
    AppDelete           proc
    AppDeleteRecursive  proc
    AppUnLoad           proc
    AppUnLoadRecursive  proc
    AppDisable          proc
    AppDisableRecursive proc
    AppEnable           proc
    AppEnableRecursive  proc
    AppGetStatus        proc :ptr
    AspAppRestart       proc
   .ends

endif

ifndef __IISApp2_INTERFACE_DEFINED__
define __IISApp2_INTERFACE_DEFINED__

DEFINE_IIDX(IISApp2, "603DCBEA-7350-11d2-A7BE-0000F8085B95")

.comdef IISApp2 : public IISApp
    AppCreate2          proc :LONG
    AppGetStatus2       proc :ptr
   .ends

endif

ifndef __IISApp3_INTERFACE_DEFINED__
define __IISApp3_INTERFACE_DEFINED__

DEFINE_IIDX(IISApp3, "2812B639-8FAC-4510-96C5-71DDBD1F54FC")

.comdef IISApp3 : public IISApp2
    AppCreate3          proc :LONG, :VARIANT, :VARIANT
   .ends

endif

ifndef __IISComputer_INTERFACE_DEFINED__
define __IISComputer_INTERFACE_DEFINED__

DEFINE_IIDX(IISComputer, "CF87A2E0-078B-11d1-9C3D-00A0C922E703")

.comdef IISComputer : public IADs
    Backup              proc :BSTR, :LONG, :LONG
    Restore             proc :BSTR, :LONG, :LONG
    EnumBackups         proc :BSTR, :LONG, :ptr, :ptr, :ptr
    DeleteBackup        proc :BSTR, :LONG
   .ends

endif

ifndef __IISComputer2_INTERFACE_DEFINED__
define __IISComputer2_INTERFACE_DEFINED__

DEFINE_IIDX(IISComputer2, "63d89839-5762-4a68-b1b9-3507ea76cbbf")

.comdef IISComputer2 : public IISComputer
    BackupWithPassword  proc :BSTR, :LONG, :LONG, :BSTR
    RestoreWithPassword proc :BSTR, :LONG, :LONG, :BSTR
    Export              proc :BSTR, :BSTR, :BSTR, :LONG
    Import              proc :BSTR, :BSTR, :BSTR, :BSTR, :LONG
    SaveData            proc
   .ends

endif

DEFINE_GUIDS(CLSID_IISExtComputer, "91ef9258-afec-11d1-9868-00a0c922e703")
DEFINE_GUIDS(CLSID_IISExtApp, "b4f34438-afec-11d1-9868-00a0c922e703")
DEFINE_GUIDS(CLSID_IISExtServer, "c3b32488-afec-11d1-9868-00a0c922e703")
DEFINE_GUIDS(CLSID_IISExtDsCrMap, "bc36cde8-afeb-11d1-9868-00a0c922e703")
DEFINE_GUIDS(CLSID_IISExtApplicationPool, "E99F9D0C-FB39-402b-9EEB-AA185237BD34")
DEFINE_GUIDS(CLSID_IISExtApplicationPools, "95863074-A389-406a-A2D7-D98BFC95B905")
DEFINE_GUIDS(CLSID_IISExtWebService, "40B8F873-B30E-475d-BEC5-4D0EBB0DBAF3")

endif

endif

endif
