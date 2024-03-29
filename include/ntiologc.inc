ifndef _NTIOLOGC_
define _NTIOLOGC_

define FACILITY_RPC_STUBS               0x3
define FACILITY_RPC_RUNTIME             0x2
define FACILITY_MCA_ERROR_CODE          0x5
define FACILITY_IO_ERROR_CODE           0x4

define STATUS_SEVERITY_WARNING          0x2
define STATUS_SEVERITY_SUCCESS          0x0
define STATUS_SEVERITY_INFORMATIONAL    0x1
define STATUS_SEVERITY_ERROR            0x3

IO_ERR_INSUFFICIENT_RESOURCES equ (0xC0040002)
IO_ERR_DRIVER_ERROR     equ (0xC0040004)
IO_ERR_SEEK_ERROR       equ (0xC0040006)
IO_ERR_BAD_BLOCK        equ (0xC0040007)
IO_ERR_TIMEOUT          equ (0xC0040009)
IO_ERR_CONTROLLER_ERROR equ (0xC004000B)
IO_ERR_NOT_READY        equ (0xC004000F)
IO_ERR_INVALID_REQUEST  equ (0xC0040010)
IO_ERR_RESET            equ (0xC0040013)
IO_ERR_BAD_FIRMWARE     equ (0xC0040019)
IO_WRN_BAD_FIRMWARE     equ (0x8004001A)
IO_WRITE_CACHE_ENABLED  equ (0x80040020)
IO_RECOVERED_VIA_ECC    equ (0x80040021)
IO_WRITE_CACHE_DISABLED equ (0x80040022)
IO_WARNING_PAGING_FAILURE equ (0x80040033)
IO_WRN_FAILURE_PREDICTED equ (0x80040034)
IO_WARNING_ALLOCATION_FAILED equ (0x80040038)
IO_WARNING_DUPLICATE_SIGNATURE equ (0x8004003A)
IO_WARNING_DUPLICATE_PATH equ (0x8004003B)
IO_WARNING_WRITE_FUA_PROBLEM equ (0x80040084)
IO_WARNING_VOLUME_LOST_DISK_EXTENT equ (0x8004008E)
IO_WARNING_DEVICE_HAS_INTERNAL_DUMP equ (0x8004008F)
IO_WARNING_SOFT_THRESHOLD_REACHED equ (0x80040090)
IO_WARNING_SOFT_THRESHOLD_REACHED_EX equ (0x80040091)
IO_WARNING_SOFT_THRESHOLD_REACHED_EX_LUN_LUN equ (0x80040092)
IO_WARNING_SOFT_THRESHOLD_REACHED_EX_LUN_POOL equ (0x80040093)
IO_WARNING_SOFT_THRESHOLD_REACHED_EX_POOL_LUN equ (0x80040094)
IO_WARNING_SOFT_THRESHOLD_REACHED_EX_POOL_POOL equ (0x80040095)
IO_ERROR_DISK_RESOURCES_EXHAUSTED equ (0xC0040096)
IO_WARNING_DISK_CAPACITY_CHANGED equ (0x80040097)
IO_WARNING_DISK_PROVISIONING_TYPE_CHANGED equ (0x80040098)
IO_WARNING_IO_OPERATION_RETRIED equ (0x80040099)
IO_ERROR_IO_HARDWARE_ERROR equ (0xC004009A)
IO_WARNING_COMPLETION_TIME equ (0x8004009B)
IO_WARNING_DISK_SURPRISE_REMOVED equ (0x8004009D)
IO_ERR_RETRY_SUCCEEDED  equ (0x00040001)
IO_ERR_CONFIGURATION_ERROR equ (0xC0040003)
IO_ERR_PARITY           equ (0xC0040005)
IO_ERR_OVERRUN_ERROR    equ (0xC0040008)
IO_ERR_SEQUENCE         equ (0xC004000A)
IO_ERR_INTERNAL_ERROR   equ (0xC004000C)
IO_ERR_INCORRECT_IRQL   equ (0xC004000D)
IO_ERR_INVALID_IOBASE   equ (0xC004000E)
IO_ERR_VERSION          equ (0xC0040011)
IO_ERR_LAYERED_FAILURE  equ (0xC0040012)
IO_ERR_PROTOCOL         equ (0xC0040014)
IO_ERR_MEMORY_CONFLICT_DETECTED equ (0xC0040015)
IO_ERR_PORT_CONFLICT_DETECTED equ (0xC0040016)
IO_ERR_DMA_CONFLICT_DETECTED equ (0xC0040017)
IO_ERR_IRQ_CONFLICT_DETECTED equ (0xC0040018)
IO_ERR_DMA_RESOURCE_CONFLICT equ (0xC004001B)
IO_ERR_INTERRUPT_RESOURCE_CONFLICT equ (0xC004001C)
IO_ERR_MEMORY_RESOURCE_CONFLICT equ (0xC004001D)
IO_ERR_PORT_RESOURCE_CONFLICT equ (0xC004001E)
IO_BAD_BLOCK_WITH_NAME  equ (0xC004001F)
IO_FILE_QUOTA_THRESHOLD equ (0x40040024)
IO_FILE_QUOTA_LIMIT     equ (0x40040025)
IO_FILE_QUOTA_STARTED   equ (0x40040026)
IO_FILE_QUOTA_SUCCEEDED equ (0x40040027)
IO_FILE_QUOTA_FAILED    equ (0x80040028)
IO_FILE_SYSTEM_CORRUPT  equ (0xC0040029)
IO_FILE_QUOTA_CORRUPT   equ (0xC004002A)
IO_SYSTEM_SLEEP_FAILED  equ (0xC004002B)
IO_DUMP_POINTER_FAILURE equ (0xC004002C)
IO_DUMP_DRIVER_LOAD_FAILURE equ (0xC004002D)
IO_DUMP_INITIALIZATION_FAILURE equ (0xC004002E)
IO_DUMP_DUMPFILE_CONFLICT equ (0xC004002F)
IO_DUMP_DIRECT_CONFIG_FAILED equ (0xC0040030)
IO_DUMP_PAGE_CONFIG_FAILED equ (0xC0040031)
IO_LOST_DELAYED_WRITE   equ (0x80040032)
IO_WARNING_INTERRUPT_STILL_PENDING equ (0x80040035)
IO_DRIVER_CANCEL_TIMEOUT equ (0x80040036)
IO_FILE_SYSTEM_CORRUPT_WITH_NAME equ (0xC0040037)
IO_WARNING_LOG_FLUSH_FAILED equ (0x80040039)

MCA_WARNING_CACHE       equ (0x8005003C)
MCA_ERROR_CACHE         equ (0xC005003D)
MCA_WARNING_TLB         equ (0x8005003E)
MCA_ERROR_TLB           equ (0xC005003F)
MCA_WARNING_CPU_BUS     equ (0x80050040)
MCA_ERROR_CPU_BUS       equ (0xC0050041)
MCA_WARNING_REGISTER_FILE equ (0x80050042)
MCA_ERROR_REGISTER_FILE equ (0xC0050043)
MCA_WARNING_MAS         equ (0x80050044)
MCA_ERROR_MAS           equ (0xC0050045)
MCA_WARNING_MEM_UNKNOWN equ (0x80050046)
MCA_ERROR_MEM_UNKNOWN   equ (0xC0050047)
MCA_WARNING_MEM_1_2     equ (0x80050048)
MCA_ERROR_MEM_1_2       equ (0xC0050049)
MCA_WARNING_MEM_1_2_5   equ (0x8005004A)
MCA_ERROR_MEM_1_2_5     equ (0xC005004B)
MCA_WARNING_MEM_1_2_5_4 equ (0x8005004C)
MCA_ERROR_MEM_1_2_5_4   equ (0xC005004D)
MCA_WARNING_SYSTEM_EVENT equ (0x8005004E)
MCA_ERROR_SYSTEM_EVENT  equ (0xC005004F)
MCA_WARNING_PCI_BUS_PARITY equ (0x80050050)
MCA_ERROR_PCI_BUS_PARITY equ (0xC0050051)
MCA_WARNING_PCI_BUS_PARITY_NO_INFO equ (0x80050052)
MCA_ERROR_PCI_BUS_PARITY_NO_INFO equ (0xC0050053)
MCA_WARNING_PCI_BUS_SERR equ (0x80050054)
MCA_ERROR_PCI_BUS_SERR  equ (0xC0050055)
MCA_WARNING_PCI_BUS_SERR_NO_INFO equ (0x80050056)
MCA_ERROR_PCI_BUS_SERR_NO_INFO equ (0xC0050057)
MCA_WARNING_PCI_BUS_MASTER_ABORT equ (0x80050058)
MCA_ERROR_PCI_BUS_MASTER_ABORT equ (0xC0050059)
MCA_WARNING_PCI_BUS_MASTER_ABORT_NO_INFO equ (0x8005005A)
MCA_ERROR_PCI_BUS_MASTER_ABORT_NO_INFO equ (0xC005005B)
MCA_WARNING_PCI_BUS_TIMEOUT equ (0x8005005C)
MCA_ERROR_PCI_BUS_TIMEOUT equ (0xC005005D)
MCA_WARNING_PCI_BUS_TIMEOUT_NO_INFO equ (0x8005005E)
MCA_ERROR_PCI_BUS_TIMEOUT_NO_INFO equ (0xC005005F)
MCA_WARNING_PCI_BUS_UNKNOWN equ (0x80050060)
MCA_ERROR_PCI_BUS_UNKNOWN equ (0xC0050061)
MCA_WARNING_PCI_DEVICE  equ (0x80050062)
MCA_ERROR_PCI_DEVICE    equ (0xC0050063)
MCA_WARNING_SMBIOS      equ (0x80050064)
MCA_ERROR_SMBIOS        equ (0xC0050065)
MCA_WARNING_PLATFORM_SPECIFIC equ (0x80050066)
MCA_ERROR_PLATFORM_SPECIFIC equ (0xC0050067)
MCA_WARNING_UNKNOWN     equ (0x80050068)
MCA_ERROR_UNKNOWN       equ (0xC0050069)
MCA_WARNING_UNKNOWN_NO_CPU equ (0x8005006A)
MCA_ERROR_UNKNOWN_NO_CPU equ (0xC005006B)

IO_ERR_THREAD_STUCK_IN_DEVICE_DRIVER equ (0xC004006C)

MCA_WARNING_CMC_THRESHOLD_EXCEEDED equ (0x8005006D)
MCA_WARNING_CPE_THRESHOLD_EXCEEDED equ (0x8005006E)
MCA_WARNING_CPU_THERMAL_THROTTLED equ (0x8005006F)
MCA_INFO_CPU_THERMAL_THROTTLING_REMOVED equ (0x40050070)
MCA_WARNING_CPU         equ (0x80050071)
MCA_ERROR_CPU           equ (0xC0050072)
MCA_INFO_NO_MORE_CORRECTED_ERROR_LOGS equ (0x40050073)
MCA_INFO_MEMORY_PAGE_MARKED_BAD equ (0x40050074)

IO_ERR_PORT_TIMEOUT     equ (0xC0040075)
IO_WARNING_BUS_RESET    equ (0x80040076)
IO_INFO_THROTTLE_COMPLETE equ (0x40040077)

MCA_MEMORYHIERARCHY_ERROR equ (0xC0050078)
MCA_TLB_ERROR           equ (0xC0050079)
MCA_BUS_ERROR           equ (0xC005007A)
MCA_BUS_TIMEOUT_ERROR   equ (0xC005007B)
MCA_INTERNALTIMER_ERROR equ (0xC005007C)
MCA_MICROCODE_ROM_PARITY_ERROR equ (0xC005007E)
MCA_EXTERNAL_ERROR      equ (0xC005007F)
MCA_FRC_ERROR           equ (0xC0050080)

IO_WARNING_RESET        equ (0x80040081)
IO_CDROM_EXCLUSIVE_LOCK equ (0x40040085)
IO_LOST_DELAYED_WRITE_NETWORK_DISCONNECTED equ (0x8004008B)
IO_LOST_DELAYED_WRITE_NETWORK_SERVER_ERROR equ (0x8004008C)
IO_LOST_DELAYED_WRITE_NETWORK_LOCAL_DISK_ERROR equ (0x8004008D)
IO_WARNING_DUMP_DISABLED_DEVICE_GONE equ (0x8004009C)

endif
