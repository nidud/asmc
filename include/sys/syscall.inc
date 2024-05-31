; SYSCALL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __SYSCALL_INC
define __SYSCALL_INC

.enum {

ifdef _WIN64

    SYS_READ                    = 0,
    SYS_WRITE                   = 1,
    SYS_OPEN                    = 2,
    SYS_CLOSE                   = 3,
    SYS_STAT                    = 4,
    SYS_FSTAT                   = 5,
    SYS_LSTAT                   = 6,
    SYS_POLL                    = 7,
    SYS_LSEEK                   = 8,
    SYS_MMAP                    = 9,
    SYS_MPROTECT                = 10,
    SYS_MUNMAP                  = 11,
    SYS_BRK                     = 12,
    SYS_RT_SIGACTION            = 13,
    SYS_RT_SIGPROCMASK          = 14,
    SYS_RT_SIGRETURN            = 15,
    SYS_IOCTL                   = 16,
    SYS_PREAD64                 = 17,
    SYS_PWRITE64                = 18,
    SYS_READV                   = 19,
    SYS_WRITEV                  = 20,
    SYS_ACCESS                  = 21,
    SYS_PIPE                    = 22,
    SYS_SELECT                  = 23,   ; sys_select()
    SYS_MREMAP                  = 25,   ; sys_mremap()
    SYS_MSYNC                   = 26,   ; sys_msync()
    SYS_SHMGET                  = 29,   ; sys_shmget()
    SYS_SHMAT                   = 30,   ; sys_shmat()
    SYS_SHMCTL                  = 31,   ; sys_shmctl()
    SYS_DUP                     = 32,
    SYS_DUP2                    = 33,
    SYS_PAUSE                   = 34,   ; sys_pause()
    SYS_NANOSLEEP               = 35,
    SYS_GETITIMER               = 36,   ; sys_getitimer()
    SYS_ALARM                   = 37,
    SYS_SETITIMER               = 38,   ; sys_setitimer()
    SYS_GETPID                  = 39,
    SYS_SENDFILE                = 40,   ; sys_sendfile64()
    SYS_SOCKET                  = 41,   ; sys_socket()
    SYS_ACCEPT                  = 43,   ; sys_accept()
    SYS_SENDTO                  = 44,   ; sys_sendto()
    SYS_RECVFROM                = 45,   ; sys_recvfrom()
    SYS_SHUTDOWN                = 48,   ; sys_shutdown()
    SYS_BIND                    = 49,   ; sys_bind()
    SYS_LISTEN                  = 50,   ; sys_listen()
    SYS_SOCKETPAIR              = 53,   ; sys_socketpair()
    SYS_SETSOCKOPT              = 54,   ; sys_setsockopt()
    SYS_GETSOCKOPT              = 55,   ; sys_getsockopt()
    SYS_CLONE                   = 56,   ; sys_clone(64)
    SYS_FORK                    = 57,
    SYS_VFORK                   = 58,
    SYS_EXECVE                  = 59,
    SYS_EXIT                    = 60,
    SYS_WAIT4                   = 61,
    SYS_KILL                    = 62,
    SYS_UNAME                   = 63,   ; sys_newuname()
    SYS_SEMGET                  = 64,   ; sys_semget()
    SYS_SEMOP                   = 65,   ; sys_semop()
    SYS_SEMCTL                  = 66,   ; sys_semctl()
    SYS_SHMDT                   = 67,   ; sys_shmdt()
    SYS_MSGGET                  = 68,   ; sys_msgget()
    SYS_MSGSND                  = 69,   ; sys_msgsnd()
    SYS_MSGRCV                  = 70,   ; sys_msgrcv()
    SYS_MSGCTL                  = 71,   ; sys_msgctl()
    SYS_FCNTL                   = 72,
    SYS_FLOCK                   = 73,   ; sys_flock()
    SYS_FSYNC                   = 74,
    SYS_FDATASYNC               = 75,
    SYS_TRUNCATE                = 76,   ; sys_truncate()
    SYS_FTRUNCATE               = 77,   ; sys_ftruncate()
    SYS_GETDENTS                = 78,
    SYS_GETCWD                  = 79,
    SYS_CHDIR                   = 80,
    SYS_FCHDIR                  = 81,
    SYS_RENAME                  = 82,
    SYS_MKDIR                   = 83,
    SYS_RMDIR                   = 84,
    SYS_CREAT                   = 85,
    SYS_LINK                    = 86,   ; sys_link()
    SYS_UNLINK                  = 87,
    SYS_READLINK                = 89,   ; sys_readlink()
    SYS_CHMOD                   = 90,
    SYS_FCHMOD                  = 91,
    SYS_CHOWN                   = 92,
    SYS_FCHOWN                  = 93,
    SYS_LCHOWN                  = 94,   ; sys_lchown()
    SYS_UMASK                   = 95,   ; sys_umask()
    SYS_GETTIMEOFDAY            = 96,
    SYS_GETRLIMIT               = 97,   ; sys_getrlimit()
    SYS_GETRUSAGE               = 98,   ; sys_getrusage()
    SYS_TIMES                   = 100,
    SYS_PTRACE                  = 101,  ; sys_ptrace()
    SYS_GETUID                  = 102,  ; sys_getuid()
    SYS_SYSLOG                  = 103,  ; sys_syslog()
    SYS_GETGID                  = 104,  ; sys_getgid()
    SYS_SETUID                  = 105,  ; sys_setuid()
    SYS_SETGID                  = 106,  ; sys_setgid()
    SYS_SETSID                  = 112,  ; sys_setsid()
    SYS_SETREUID                = 113,  ; sys_setreuid()
    SYS_SETREGID                = 114,  ; sys_setregid()
    SYS_GETGROUPS               = 115,  ; sys_getgroups()
    SYS_SETGROUPS               = 116,  ; sys_setgroups()
    SYS_SETRESUID               = 117,  ; sys_setresuid()
    SYS_GETRESUID               = 118,  ; sys_getresuid()
    SYS_SETRESGID               = 119,  ; sys_setresgid()
    SYS_GETRESGID               = 120,  ; sys_getresgid()
    SYS_SETFSUID                = 122,  ; sys_setfsuid()
    SYS_SETFSGID                = 123,  ; sys_setfsgid()
    SYS_GETSID                  = 124,  ; sys_getsid()
    SYS_CAPGET                  = 125,  ; sys_capget()
    SYS_CAPSET                  = 126,  ; sys_capset()
    SYS_RT_SIGPENDING           = 127,  ; sys_rt_sigpending()
    SYS_RT_SIGSUSPEND           = 130,  ; sys_rt_sigsuspend()
    SYS_UTIME                   = 132,  ; sys_utime()
    SYS_MKNOD                   = 133,  ; sys_mknod()
    SYS_USELIB                  = 134,  ; sys_uselib()
    SYS_USTAT                   = 136,  ; sys_ustat()
    SYS_STATFS                  = 137,  ; sys_statfs()
    SYS_SYSFS                   = 139,  ; sys_sysfs()
    SYS_SCHED_SETPARAM          = 142,  ; sys_sched_setparam()
    SYS_SCHED_GETPARAM          = 143,  ; sys_sched_getparam()
    SYS_SCHED_SETSCHEDULER      = 144,  ; sys_sched_setscheduler()
    SYS_SCHED_GETSCHEDULER      = 145,  ; sys_sched_getscheduler()
    SYS_SCHED_GET_PRIORITY_MAX  = 146,  ; sys_sched_get_priority_max()
    SYS_SCHED_GET_PRIORITY_MIN  = 147,  ; sys_sched_get_priority_min()
    SYS_SCHED_RR_GET_INTERVAL   = 148,  ; sys_sched_rr_get_interval()
    SYS_MLOCK                   = 149,  ; sys_mlock()
    SYS_MLOCKALL                = 151,  ; sys_mlockall()
    SYS_MUNLOCKALL              = 152,  ; sys_munlockall()
    SYS_MODIFY_LDT              = 154,  ; sys_modify_ldt()
    SYS_PIVOT_ROOT              = 155,  ; sys_pivot_root()
    SYS_PRCTL                   = 157,  ; sys_prctl()
    SYS_ARCH_PRCTL              = 158,  ; sys_arch_prctl()
    SYS_ADJTIMEX                = 159,  ; sys_adjtimex()
    SYS_SETRLIMIT               = 160,  ; sys_setrlimit()
    SYS_CHROOT                  = 161,
    SYS_SYNC                    = 162,  ; sys_sync()
    SYS_ACCT                    = 163,  ; sys_acct()
    SYS_SETTIMEOFDAY            = 164,
    SYS_MOUNT                   = 165,  ; sys_mount()
    SYS_SWAPON                  = 167,  ; sys_swapon()
    SYS_REBOOT                  = 169,  ; sys_reboot()
    SYS_SETDOMAINNAME           = 171,  ; sys_setdomainname()
    SYS_IOPL                    = 172,  ; stub_iopl()
    SYS_IOPERM                  = 173,  ; sys_ioperm()
    SYS_CREATE_MODULE           = 174,  ;
    SYS_DELETE_MODULE           = 176,  ; sys_delete_module()
    SYS_GET_KERNEL_SYMS         = 177,  ;
    SYS_QUERY_MODULE            = 178,  ;
    SYS_QUOTACTL                = 179,  ; sys_quotactl()
    SYS_NFSSERVCTL              = 180,  ;
    SYS_GETPMSG                 = 181,  ;
    SYS_PUTPMSG                 = 182,  ;
    SYS_AFS_SYSCALL             = 183,  ;
    SYS_TUXCALL                 = 184,  ;
    SYS_SECURITY                = 185,  ;
    SYS_GETTID                  = 186,  ; sys_gettid()
    SYS_READAHEAD               = 187,  ; sys_readahead()
    SYS_SETXATTR                = 188,  ; sys_setxattr()
    SYS_LSETXATTR               = 189,  ; sys_lsetxattr()
    SYS_FSETXATTR               = 190,  ; sys_fsetxattr()
    SYS_GETXATTR                = 191,  ; sys_getxattr()
    SYS_LGETXATTR               = 192,  ; sys_lgetxattr()
    SYS_FGETXATTR               = 193,  ; sys_fgetxattr()
    SYS_LISTXATTR               = 194,  ; sys_listxattr()
    SYS_LLISTXATTR              = 195,  ; sys_llistxattr()
    SYS_FLISTXATTR              = 196,  ; sys_flistxattr()
    SYS_LREMOVEXATTR            = 198,  ; sys_lremovexattr()
    SYS_FREMOVEXATTR            = 199,  ; sys_fremovexattr()
    SYS_TKILL                   = 200,  ; sys_tkill()
    SYS_TIME                    = 201,
    SYS_FUTEX                   = 202,  ; sys_futex()
    SYS_SCHED_SETAFFINITY       = 203,  ; sys_sched_setaffinity()
    SYS_SCHED_GETAFFINITY       = 204,  ; sys_sched_getaffinity()
    SYS_SET_THREAD_AREA         = 205,
    SYS_IO_SETUP                = 206,  ; sys_io_setup()
    SYS_IO_DESTROY              = 207,  ; sys_io_destroy()
    SYS_IO_GETEVENTS            = 208,  ; sys_io_getevents()
    SYS_IO_SUBMIT               = 209,  ; sys_io_submit()
    SYS_IO_CANCEL               = 210,  ; sys_io_cancel()
    SYS_GET_THREAD_AREA         = 211,
    SYS_LOOKUP_DCOOKIE          = 212,  ; sys_lookup_dcookie()
    SYS_EPOLL_CREATE            = 213,  ; sys_epoll_create()
    SYS_EPOLL_CTL_OLD           = 214,
    SYS_EPOLL_WAIT_OLD          = 215,
    SYS_REMAP_FILE_PAGES        = 216,  ; sys_remap_file_pages()
    SYS_GETDENTS64              = 217,
    SYS_SEMTIMEDOP              = 220,  ; sys_semtimedop()
    SYS_FADVISE64               = 221,  ; sys_fadvise64()
    SYS_TIMER_CREATE            = 222,  ; sys_timer_create()
    SYS_TIMER_SETTIME           = 223,  ; sys_timer_settime()
    SYS_TIMER_GETTIME           = 224,  ; sys_timer_gettime()
    SYS_TIMER_GETOVERRUN        = 225,  ; sys_timer_getoverrun()
    SYS_TIMER_DELETE            = 226,  ; sys_timer_delete()
    SYS_CLOCK_SETTIME           = 227,
    SYS_CLOCK_GETTIME           = 228,
    SYS_CLOCK_GETRES            = 229,
    SYS_CLOCK_NANOSLEEP         = 230,
    SYS_EXIT_GROUP              = 231,  ; sys_exit_group()
    SYS_EPOLL_WAIT              = 232,  ; sys_epoll_wait()
    SYS_EPOLL_CTL               = 233,  ; sys_epoll_ctl()
    SYS_TGKILL                  = 234,  ; sys_tgkill()
    SYS_UTIMES                  = 235,  ; sys_utimes()
    SYS_VSERVER                 = 236,
    SYS_MBIND                   = 237,  ; sys_mbind()
    SYS_SET_MEMPOLICY           = 238,  ; sys_set_mempolicy()
    SYS_GET_MEMPOLICY           = 239,  ; sys_get_mempolicy()
    SYS_MQ_UNLINK               = 241,  ; sys_mq_unlink()
    SYS_MQ_TIMEDSEND            = 242,  ; sys_mq_timedsend()
    SYS_MQ_NOTIFY               = 244,  ; sys_mq_notify()
    SYS_MQ_GETSETATTR           = 245,  ; sys_mq_getsetattr()
    SYS_KEXEC_LOAD              = 246,  ; sys_kexec_load()
    SYS_WAITID                  = 247,  ; sys_waitid(64)
    SYS_KEYCTL                  = 250,  ; sys_keyctl()
    SYS_IOPRIO_SET              = 251,  ; sys_ioprio_set()
    SYS_IOPRIO_GET              = 252,  ; sys_ioprio_get()
    SYS_INOTIFY_INIT            = 253,  ; sys_inotify_init()
    SYS_INOTIFY_ADD_WATCH       = 254,  ; sys_inotify_add_watch()
    SYS_INOTIFY_RM_WATCH        = 255,  ; sys_inotify_rm_watch()
    SYS_MIGRATE_PAGES           = 256,  ; sys_migrate_pages()
    SYS_OPENAT                  = 257,  ; sys_openat()
    SYS_FCHOWNAT                = 260,  ; sys_fchownat()
    SYS_FUTIMESAT               = 261,  ; sys_futimesat()
    SYS_NEWFSTATAT              = 262,  ; sys_newfstatat()
    SYS_UNLINKAT                = 263,  ; sys_unlinkat()
    SYS_RENAMEAT                = 264,  ; sys_renameat()
    SYS_LINKAT                  = 265,  ; sys_linkat()
    SYS_SYMLINKAT               = 266,  ; sys_symlinkat()
    SYS_READLINKAT              = 267,  ; sys_readlinkat()
    SYS_FCHMODAT                = 268,  ; sys_fchmodat()
    SYS_FACCESSAT               = 269,  ; sys_faccessat()
    SYS_PSELECT6                = 270,  ; sys_pselect6()
    SYS_PPOLL                   = 271,  ; sys_ppoll()
    SYS_SPLICE                  = 275,  ; sys_splice()
    SYS_VMSPLICE                = 278,  ; sys_vmsplice()
    SYS_MOVE_PAGES              = 279,  ; sys_move_pages()
    SYS_UTIMENSAT               = 280,  ; sys_utimensat()
    SYS_SIGNALFD                = 282,  ; sys_signalfd()
    SYS_TIMERFD_CREATE          = 283,  ; sys_timerfd_create()
    SYS_FALLOCATE               = 285,  ; sys_fallocate()
    SYS_SIGNALFD4               = 289,  ; sys_signalfd4()
    SYS_EVENTFD2                = 290,  ; sys_eventfd2()
    SYS_EPOLL_CREATE1           = 291,  ; sys_epoll_create1()
    SYS_DUP3                    = 292,  ; sys_dup3()
    SYS_PIPE2                   = 293,  ; sys_pipe2()
    SYS_INOTIFY_INIT1           = 294,  ; sys_inotify_init1()
    SYS_PREADV                  = 295,  ; sys_preadv()
    SYS_RT_TGSIGQUEUEINFO       = 297,  ; sys_rt_tgsigqueueinfo()
    SYS_RECVMMSG                = 299,  ; sys_recvmmsg()
    SYS_FANOTIFY_INIT           = 300,  ; sys_fanotify_init()
    SYS_FANOTIFY_MARK           = 301,  ; sys_fanotify_mark()
    SYS_PRLIMIT64               = 302,  ; sys_prlimit64()
    SYS_NAME_TO_HANDLE_AT       = 303,  ; sys_name_to_handle_at()
    SYS_OPEN_BY_HANDLE_AT       = 304,  ; sys_open_by_handle_at()
    SYS_CLOCK_ADJTIME           = 305,  ; sys_clock_adjtime()
    SYS_SYNCFS                  = 306,  ; sys_syncfs()
    SYS_SENDMMSG                = 307,  ; sys_sendmmsg()
    SYS_SETNS                   = 308,  ; sys_setns()
    SYS_GETCPU                  = 309,  ; sys_getcpu()
    SYS_PROCESS_VM_READV        = 310,  ; sys_process_vm_readv()
    SYS_PROCESS_VM_WRITEV       = 311,  ; sys_process_vm_writev()
    SYS_KCMP                    = 312,  ; sys_kcmp()
    SYS_FINIT_MODULE            = 313,  ; sys_finit_module()

else

    SYS_EXIT                    = 1,
    SYS_FORK                    = 2,
    SYS_READ                    = 3,
    SYS_WRITE                   = 4,
    SYS_OPEN                    = 5,
    SYS_CREAT                   = 8,
    SYS_CLOSE                   = 6,
    SYS_WAITPID                 = 7,
    SYS_UNLINK                  = 10,
    SYS_EXECVE                  = 11,
    SYS_CHDIR                   = 12,
    SYS_TIME                    = 13,
    SYS_CHMOD                   = 15,
    SYS_LSEEK                   = 19,
    SYS_GETPID                  = 20,
    SYS_ALARM                   = 27,
    SYS_ACCESS                  = 33,
    SYS_KILL                    = 37,
    SYS_RENAME                  = 38,
    SYS_MKDIR                   = 39,
    SYS_RMDIR                   = 40,
    SYS_DUP                     = 41,
    SYS_PIPE                    = 42,
    SYS_TIMES                   = 43,
    SYS_BRK                     = 45,
    SYS_IOCTL                   = 54,
    SYS_FCNTL                   = 55,
    SYS_CHROOT                  = 61,
    SYS_DUP2                    = 63,
    SYS_GETTIMEOFDAY            = 78,
    SYS_SETTIMEOFDAY            = 79,
    SYS_MMAP                    = 90,
    SYS_MUNMAP                  = 91,
    SYS_FCHMOD                  = 94,
    SYS_FCHOWN                  = 95,
    SYS_STAT                    = 106,
    SYS_LSTAT                   = 107,
    SYS_FSTAT                   = 108,
    SYS_WAIT4                   = 114,
    SYS_FSYNC                   = 118,
    SYS_MPROTECT                = 125,
    SYS_FCHDIR                  = 133,
    SYS_LLSEEK                  = 140,
    SYS_GETDENTS                = 141,
    SYS_READV                   = 145,
    SYS_WRITEV                  = 146,
    SYS_FDATASYNC               = 148,
    SYS_NANOSLEEP               = 162,
    SYS_POLL                    = 168,
    SYS_RT_SIGRETURN            = 173,
    SYS_RT_SIGACTION            = 174,
    SYS_RT_SIGPROCMASK          = 175,
    SYS_PREAD64                 = 180,
    SYS_PWRITE64                = 181,
    SYS_CHOWN                   = 182,
    SYS_GETCWD                  = 183,
    SYS_VFORK                   = 190,
    SYS_STAT64                  = 195,
    SYS_LSTAT64                 = 196,
    SYS_FSTAT64                 = 197,
    SYS_GETDENTS64              = 220,
    SYS_CLOCK_SETTIME           = 264,
    SYS_CLOCK_GETTIME           = 265,
    SYS_CLOCK_GETRES            = 266,
    SYS_CLOCK_NANOSLEEP         = 267,
    SYS_WAITID                  = 284,
endif
    }

ifdef _WIN64

sys_read proto :int_t, :ptr, :size_t {
    mov eax,SYS_READ
    syscall
    }
sys_write proto :int_t, :ptr, :size_t {
    mov eax,SYS_WRITE
    syscall
    }
sys_open proto :string_t, :int_t, :int_t {
    mov eax,SYS_OPEN
    syscall
    }
sys_creat proto :string_t, :uint_t {
    mov eax,SYS_CREAT
    syscall
    }
sys_close proto :int_t {
    mov eax,SYS_CLOSE
    syscall
    }
sys_chmod proto :string_t, :int_t {
    mov eax,SYS_CHMOD
    syscall
    }
sys_fchmod proto :int_t, :int_t {
    mov eax,SYS_FCHMOD
    syscall
    }
sys_newstat proto :string_t, :ptr {
    mov eax,SYS_STAT
    syscall
    }
sys_newfstat proto :int_t, :ptr {
    mov eax,SYS_FSTAT
    syscall
    }
sys_newlstat proto :string_t, :ptr {
    mov eax,SYS_LSTAT
    syscall
    }
sys_lseek proto :int_t, :size_t, :uint_t {
    mov eax,SYS_LSEEK
    syscall
    }
sys_nanosleep proto :ptr, :ptr {
    mov eax,SYS_NANOSLEEP
    syscall
    }
sys_mmap proto :ptr, :size_t, :size_t, :size_t, :size_t, :size_t {
    add rsi,_GRANULARITY-1
    and sil,-(_GRANULARITY)
    mov r10,rcx
    mov rcx,rsi
    mov eax,SYS_MMAP
    syscall
    }
sys_munmap proto :ptr, :size_t {
    mov eax,SYS_MUNMAP
    syscall
    }
sys_mprotect proto :ptr, :size_t, :int_t {
    mov eax,SYS_MPROTECT
    syscall
    }
sys_rt_sigaction proto :int_t, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_RT_SIGACTION
    syscall
    }
sys_rt_sigprocmask proto :int_t, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_RT_SIGPROCMASK
    syscall
    }
sys_rt_sigreturn proto {
    mov eax,SYS_RT_SIGRETURN
    syscall
    }
sys_fcntl proto :int_t, :int_t, :int_t {
    mov eax,SYS_FCNTL
    syscall
    }
sys_access proto :string_t, :int_t {
    mov eax,SYS_ACCESS
    syscall
    }
sys_ioctl proto :int_t, :int_t, :ptr {
    mov eax,SYS_IOCTL
    syscall
    }
sys_getcwd proto :string_t, :int_t {
    mov eax,SYS_GETCWD
    syscall
    }
sys_chdir proto :string_t {
    mov eax,SYS_CHDIR
    syscall
    }
sys_chroot proto :string_t {
    mov eax,SYS_CHROOT
    syscall
    }
sys_fchdir proto :int_t {
    mov eax,SYS_FCHDIR
    syscall
    }
sys_mkdir proto :string_t {
    mov eax,SYS_MKDIR
    syscall
    }
sys_rmdir proto :string_t {
    mov eax,SYS_RMDIR
    syscall
    }
sys_exit proto :int_t {
    mov eax,SYS_EXIT
    syscall
    }
sys_unlink proto :string_t {
    mov eax,SYS_UNLINK
    syscall
    }
sys_rename proto :string_t, :string_t {
    mov eax,SYS_RENAME
    syscall
    }
sys_time proto :ptr {
    mov eax,SYS_TIME
    syscall
    }
sys_times proto :ptr {
    mov eax,SYS_TIMES
    syscall
    }
sys_gettimeofday proto :ptr, :ptr {
    mov eax,SYS_GETTIMEOFDAY
    syscall
    }
sys_settimeofday proto :ptr, :ptr {
    mov eax,SYS_SETTIMEOFDAY
    syscall
    }
sys_getdents proto :int_t, :ptr, :uint_t {
    mov eax,SYS_GETDENTS
    syscall
    }
sys_getdents64 proto :int_t, :ptr, :uint_t {
    mov eax,SYS_GETDENTS64
    syscall
    }
sys_fork proto {
    mov eax,SYS_FORK
    syscall
    }
sys_vfork proto {
    mov eax,SYS_VFORK
    syscall
    }
sys_execve proto :string_t, :array_t, :array_t {
    mov eax,SYS_EXECVE
    syscall
    }
sys_wait4 proto :int_t, :ptr int_t, :int_t, :ptr rusage {
    mov r10,rcx
    mov eax,SYS_WAIT4
    syscall
    }
sys_clone proto :size_t, :size_t, :ptr int_t, :size_t, :ptr int_t {
    mov r10,rcx
    mov eax,SYS_CLONE
    syscall
    }
sys_getpid proto {
    mov eax,SYS_GETPID
    syscall
    }
sys_chown proto :string_t, :uint_t, :uint_t {
    mov eax,SYS_CHOWN
    syscall
    }
sys_fchown proto :int_t, :uint_t, :uint_t {
    mov eax,SYS_FCHOWN
    syscall
    }
sys_alarm proto :uint_t {
    mov eax,SYS_ALARM
    syscall
    }
sys_pipe proto :ptr int_t {
    mov eax,SYS_PIPE
    syscall
    }
sys_fdatasync proto :int_t {
    mov eax,SYS_FDATASYNC
    syscall
    }
sys_clock_settime proto :int_t, :ptr {
    mov eax,SYS_CLOCK_SETTIME
    syscall
    }
sys_clock_gettime proto :int_t, :ptr {
    mov eax,SYS_CLOCK_GETTIME
    syscall
    }
sys_clock_getres proto :int_t, :ptr {
    mov eax,SYS_CLOCK_GETRES
    syscall
    }
sys_clock_nanosleep proto :int_t, :int_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_CLOCK_NANOSLEEP
    syscall
    }
sys_dup proto :int_t {
    mov eax,SYS_DUP
    syscall
    }
sys_dup2 proto :int_t, :int_t {
    mov eax,SYS_DUP2
    syscall
    }
sys_fsync proto :int_t {
    mov eax,SYS_FSYNC
    syscall
    }
sys_brk proto :ptr {
    mov eax,SYS_BRK
    syscall
    }
sys_poll proto :ptr, :uint_t, :int_t {
    mov eax,SYS_POLL
    syscall
    }
sys_kill proto :int_t, :int_t {
    mov eax,SYS_KILL
    syscall
    }
sys_pread64 proto :int_t, :ptr, :size_t, :uint64_t {
    mov eax,SYS_PREAD64
    syscall
    }
sys_pwrite64 proto :int_t, :ptr, :size_t, :uint64_t {
    mov eax,SYS_PWRITE64
    syscall
    }
sys_readv proto :int_t, :ptr, :int_t {
    mov eax,SYS_READV
    syscall
    }
sys_writev proto :int_t, :ptr, :int_t {
    mov eax,SYS_WRITEV
    syscall
    }

else

sys_call macro id, _1, _2, _3, _4, _5
ifnb <_1>
    push    ebx
    mov     ebx,_1
 ifnb <_2>
    mov     ecx,_2
  ifnb <_3>
    mov     edx,_3
   ifnb <_4>
    push    esi
    mov     esi,_4
    ifnb <_5>
    push    edi
    mov     edi,_5
    endif
   endif
  endif
 endif
endif
    mov     eax,id
    int     0x80
ifnb <_1>
 ifnb <_4>
  ifnb <_5>
    pop     edi
  endif
    pop     esi
 endif
    pop     ebx
endif
    retm   <eax>
    endm

sys_fork proto fastcall {
    sys_call(SYS_FORK)
    }
sys_vfork proto fastcall {
    sys_call(SYS_VFORK)
    }
sys_getpid proto fastcall {
    sys_call(SYS_GETPID)
    }
sys_execve proto fastcall :string_t, :array_t, :abs {
    sys_call(SYS_EXECVE, _1, _2, _3)
    }
sys_wait4 proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_WAIT4, _1, _2, _3, _4)
    }
sys_waitid proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_WAITID, _1, _2, _3, _4, _5)
    }
sys_waitpid proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_WAITPID, _1, _2, _3)
    }
sys_read proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_READ, _1, _2, _3)
    }
sys_write proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_WRITE, _1, _2, _3)
    }
sys_open proto fastcall :string_t, :int_t, :abs {
    sys_call(SYS_OPEN, _1, _2, _3)
    }
sys_creat proto fastcall :string_t, :uint_t {
    sys_call(SYS_CREAT, _1, _2)
    }
sys_close proto fastcall :int_t {
    sys_call(SYS_CLOSE, _1)
    }
sys_chmod proto fastcall :string_t, :int_t {
    sys_call(SYS_CHMOD, _1, _2)
    }
sys_fchmod proto fastcall :int_t, :int_t {
    sys_call(SYS_FCHMOD, _1, _2)
    }
sys_newstat proto fastcall :string_t, :ptr {
    sys_call(SYS_STAT, _1, _2)
    }
sys_newstat64 proto fastcall :string_t, :ptr {
    sys_call(SYS_STAT64, _1, _2)
    }
sys_newfstat proto fastcall :int_t, :ptr {
    sys_call(SYS_FSTAT, _1, _2)
    }
sys_newfstat64 proto fastcall :int_t, :ptr {
    sys_call(SYS_FSTAT64, _1, _2)
    }
sys_newlstat proto fastcall :string_t, :ptr {
    sys_call(SYS_LSTAT, _1, _2)
    }
sys_newlstat64 proto fastcall :string_t, :ptr {
    sys_call(SYS_LSTAT64, _1, _2)
    }
sys_lseek proto fastcall :int_t, :size_t, :abs {
    sys_call(SYS_LSEEK, _1, _2, _3)
    }
sys_llseek proto fastcall :int_t, :uint_t, :abs, :abs, :abs {
    sys_call(SYS_LLSEEK, _1, _2, _3, _4, _5)
    }

.template mmap_arg_struct
    m_addr   dd ? ; Address where pages will be mapped (0)
    m_len    dd ?
    m_prot   dd ? ; PROT_EXEC, PROT_READ, PROT_WRITE
    m_flags  dd ?
    m_fd     dd ?
    m_offset dd ? ; ignored if MAP_ANON
   .ends

sys_mmap proto fastcall :ptr, :size_t, :abs, :abs, :abs, :abs {

   .new mmap:mmap_arg_struct

    add edx,_GRANULARITY-1
    and dl,-(_GRANULARITY)
    mov mmap.m_addr,ecx
    mov mmap.m_len,edx
    mov mmap.m_prot,_3
    mov mmap.m_flags,_4
    mov mmap.m_fd,_5
    mov mmap.m_offset,_6
    lea ecx,mmap
    sys_call(SYS_MMAP, ecx)
    }


sys_munmap proto fastcall :ptr, :size_t {
    sys_call(SYS_MUNMAP, _1, _2)
    }
sys_mprotect proto fastcall :ptr, :size_t, :abs {
    sys_call(SYS_MPROTECT, _1, _2, _3)
    }
sys_rt_sigaction proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_RT_SIGACTION, _1, _2, _3, _4)
    }
sys_rt_sigprocmask proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_RT_SIGPROCMASK, _1, _2, _3, _4)
    }
sys_rt_sigreturn proto fastcall {
    sys_call(SYS_RT_SIGRETURN)
    }
sys_fcntl proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_FCNTL, _1, _2, _3)
    }
sys_access proto fastcall :string_t, :int_t {
    sys_call(SYS_ACCESS, _1, _2)
    }
sys_ioctl proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_IOCTL, _1, _2, _3)
    }
sys_getcwd proto fastcall :string_t, :int_t {
    sys_call(SYS_GETCWD, _1, _2)
    }
sys_chdir proto fastcall :string_t {
    sys_call(SYS_CHDIR, _1)
    }
sys_chroot proto fastcall :string_t {
    sys_call(SYS_CHROOT, _1)
    }
sys_fchdir proto fastcall :int_t {
    sys_call(SYS_FCHDIR, _1)
    }
sys_mkdir proto fastcall :string_t {
    sys_call(SYS_MKDIR, _1)
    }
sys_rmdir proto fastcall :string_t {
    sys_call(SYS_RMDIR, _1)
    }
sys_exit proto fastcall :int_t {
    sys_call(SYS_EXIT, _1)
    }
sys_unlink proto fastcall :string_t {
    sys_call(SYS_UNLINK, _1)
    }
sys_rename proto fastcall :string_t, :string_t {
    sys_call(SYS_RENAME, _1, _2)
    }
sys_time proto fastcall :ptr {
    sys_call(SYS_TIME, _1)
    }
sys_times proto fastcall :ptr {
    sys_call(SYS_TIMES, _1)
    }
sys_nanosleep proto fastcall :ptr, :ptr {
    sys_call(SYS_NANOSLEEP, _1, _2)
    }
sys_gettimeofday proto fastcall :ptr, :ptr {
    sys_call(SYS_GETTIMEOFDAY, _1, _2)
    }
sys_settimeofday proto fastcall :ptr, :ptr {
    sys_call(SYS_SETTIMEOFDAY, _1, _2)
    }
sys_getdents proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_GETDENTS, _1, _2)
    }
sys_getdents64 proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_GETDENTS64, _1, _2)
    }
sys_chown proto fastcall :string_t, :uint_t, :abs {
    sys_call(SYS_CHOWN, _1, _2, _3)
    }
sys_fchown proto fastcall :int_t, :uint_t, :abs {
    sys_call(SYS_FCHOWN, _1, _2, _3)
    }
sys_alarm proto fastcall :uint_t {
    sys_call(SYS_ALARM, _1)
    }
sys_pipe proto fastcall :ptr int_t {
    sys_call(SYS_PIPE, _1)
    }
sys_fdatasync proto fastcall :int_t {
    sys_call(SYS_FDATASYNC, _1)
    }
sys_clock_settime proto fastcall :int_t, :ptr {
    sys_call(SYS_CLOCK_SETTIME, _1, _2)
    }
sys_clock_gettime proto fastcall :int_t, :ptr {
    sys_call(SYS_CLOCK_GETTIME, _1, _2)
    }
sys_clock_getres proto fastcall :int_t, :ptr {
    sys_call(SYS_CLOCK_GETRES, _1, _2)
    }
sys_clock_nanosleep proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_CLOCK_NANOSLEEP, _1, _2, _3, _4)
    }
sys_dup proto fastcall :int_t {
    sys_call(SYS_DUP, _1)
    }
sys_dup2 proto fastcall :int_t, :int_t {
    sys_call(SYS_DUP2, _1, _2)
    }
sys_fsync proto fastcall :int_t {
    sys_call(SYS_FSYNC, _1)
    }
sys_brk proto fastcall :ptr {
    sys_call(SYS_BRK, _1)
    }
sys_poll proto fastcall :ptr, :uint_t, :abs {
    sys_call(SYS_POLL, _1, _2, _3)
    }
sys_kill proto fastcall :int_t, :int_t {
    sys_call(SYS_KILL, _1, _2)
    }
sys_pread64 proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_PREAD64, _1, _2, _3, _4, _5)
    }
sys_pwrite64 proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_PWRITE64, _1, _2, _3, _4, _5)
    }
sys_readv proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_READV, _1, _2, _3)
    }
sys_writev proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_WRITEV, _1, _2, _3)
    }

endif
endif
