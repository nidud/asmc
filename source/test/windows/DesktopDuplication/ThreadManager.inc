
ifndef _THREADMANAGER_H_
define _THREADMANAGER_H_

include CommonTypes.inc

.class THREADMANAGER

    m_PtrInfo           PTR_INFO <>
    m_ThreadCount       UINT ?
    m_ThreadHandles     ptr HANDLE ?
    m_ThreadData        ptr THREAD_DATA ?

    THREADMANAGER       proc
    Release             proc

    Clean               proc
    Initialize          proc :SINT, :UINT, :HANDLE, :HANDLE, :HANDLE, :HANDLE, :ptr RECT
    GetPointerInfo      proc
    WaitForThreadTermination proc

    InitializeDx        proc :ptr DX_RESOURCES
    CleanDx             proc :ptr DX_RESOURCES
   .ends

endif
