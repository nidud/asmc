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
    SYS_SELECT                  = 23,
    SYS_SCHED_YIELD             = 24,
    SYS_MREMAP                  = 25,
    SYS_MSYNC                   = 26,
    SYS_MINCORE                 = 27,
    SYS_MADVISE                 = 28,
    SYS_SHMGET                  = 29,
    SYS_SHMAT                   = 30,
    SYS_SHMCTL                  = 31,
    SYS_DUP                     = 32,
    SYS_DUP2                    = 33,
    SYS_PAUSE                   = 34,
    SYS_NANOSLEEP               = 35,
    SYS_GETITIMER               = 36,
    SYS_ALARM                   = 37,
    SYS_SETITIMER               = 38,
    SYS_GETPID                  = 39,
    SYS_SENDFILE                = 40,
    SYS_SOCKET                  = 41,
    SYS_CONNECT                 = 42,
    SYS_ACCEPT                  = 43,
    SYS_SENDTO                  = 44,
    SYS_RECVFROM                = 45,
    SYS_SENDMSG                 = 46,
    SYS_RECVMSG                 = 47,
    SYS_SHUTDOWN                = 48,
    SYS_BIND                    = 49,
    SYS_LISTEN                  = 50,
    SYS_GETSOCKNAME             = 51,
    SYS_GETPEERNAME             = 52,
    SYS_SOCKETPAIR              = 53,
    SYS_SETSOCKOPT              = 54,
    SYS_GETSOCKOPT              = 55,
    SYS_CLONE                   = 56,
    SYS_FORK                    = 57,
    SYS_VFORK                   = 58,
    SYS_EXECVE                  = 59,
    SYS_EXIT                    = 60,
    SYS_WAIT4                   = 61,
    SYS_KILL                    = 62,
    SYS_UNAME                   = 63,
    SYS_SEMGET                  = 64,
    SYS_SEMOP                   = 65,
    SYS_SEMCTL                  = 66,
    SYS_SHMDT                   = 67,
    SYS_MSGGET                  = 68,
    SYS_MSGSND                  = 69,
    SYS_MSGRCV                  = 70,
    SYS_MSGCTL                  = 71,
    SYS_FCNTL                   = 72,
    SYS_FLOCK                   = 73,
    SYS_FSYNC                   = 74,
    SYS_FDATASYNC               = 75,
    SYS_TRUNCATE                = 76,
    SYS_FTRUNCATE               = 77,
    SYS_GETDENTS                = 78,
    SYS_GETCWD                  = 79,
    SYS_CHDIR                   = 80,
    SYS_FCHDIR                  = 81,
    SYS_RENAME                  = 82,
    SYS_MKDIR                   = 83,
    SYS_RMDIR                   = 84,
    SYS_CREAT                   = 85,
    SYS_LINK                    = 86,
    SYS_UNLINK                  = 87,
    SYS_SYMLINK                 = 88,
    SYS_READLINK                = 89,
    SYS_CHMOD                   = 90,
    SYS_FCHMOD                  = 91,
    SYS_CHOWN                   = 92,
    SYS_FCHOWN                  = 93,
    SYS_LCHOWN                  = 94,
    SYS_UMASK                   = 95,
    SYS_GETTIMEOFDAY            = 96,
    SYS_GETRLIMIT               = 97,
    SYS_GETRUSAGE               = 98,
    SYS_SYSINFO                 = 99,
    SYS_TIMES                   = 100,
    SYS_PTRACE                  = 101,
    SYS_GETUID                  = 102,
    SYS_SYSLOG                  = 103,
    SYS_GETGID                  = 104,
    SYS_SETUID                  = 105,
    SYS_SETGID                  = 106,
    SYS_GETEUID                 = 107,
    SYS_GETEGID                 = 108,
    SYS_SETPGID                 = 109,
    SYS_GETPPID                 = 110,
    SYS_GETPGRP                 = 111,
    SYS_SETSID                  = 112,
    SYS_SETREUID                = 113,
    SYS_SETREGID                = 114,
    SYS_GETGROUPS               = 115,
    SYS_SETGROUPS               = 116,
    SYS_SETRESUID               = 117,
    SYS_GETRESUID               = 118,
    SYS_SETRESGID               = 119,
    SYS_GETRESGID               = 120,
    SYS_GETPGID                 = 121,
    SYS_SETFSUID                = 122,
    SYS_SETFSGID                = 123,
    SYS_GETSID                  = 124,
    SYS_CAPGET                  = 125,
    SYS_CAPSET                  = 126,
    SYS_RT_SIGPENDING           = 127,
    SYS_RT_SIGTIMEDWAIT         = 128,
    SYS_RT_SIGQUEUEINFO         = 129,
    SYS_RT_SIGSUSPEND           = 130,
    SYS_SIGALTSTACK             = 131,
    SYS_UTIME                   = 132,
    SYS_MKNOD                   = 133,
    SYS_USELIB                  = 134,
    SYS_PERSONALITY             = 135,
    SYS_USTAT                   = 136,
    SYS_STATFS                  = 137,
    SYS_FSTATFS                 = 138,
    SYS_SYSFS                   = 139,
    SYS_GETPRIORITY             = 140,
    SYS_SETPRIORITY             = 141,
    SYS_SCHED_SETPARAM          = 142,
    SYS_SCHED_GETPARAM          = 143,
    SYS_SCHED_SETSCHEDULER      = 144,
    SYS_SCHED_GETSCHEDULER      = 145,
    SYS_SCHED_GET_PRIORITY_MAX  = 146,
    SYS_SCHED_GET_PRIORITY_MIN  = 147,
    SYS_SCHED_RR_GET_INTERVAL   = 148,
    SYS_MLOCK                   = 149,
    SYS_MUNLOCK                 = 150,
    SYS_MLOCKALL                = 151,
    SYS_MUNLOCKALL              = 152,
    SYS_VHANGUP                 = 153,
    SYS_MODIFY_LDT              = 154,
    SYS_PIVOT_ROOT              = 155,
    SYS_NI_SYSCALL              = 156,
    SYS_PRCTL                   = 157,
    SYS_ARCH_PRCTL              = 158,
    SYS_ADJTIMEX                = 159,
    SYS_SETRLIMIT               = 160,
    SYS_CHROOT                  = 161,
    SYS_SYNC                    = 162,
    SYS_ACCT                    = 163,
    SYS_SETTIMEOFDAY            = 164,
    SYS_MOUNT                   = 165,
    SYS_UMONT                   = 166,
    SYS_SWAPON                  = 167,
    SYS_SWAPOFF                 = 168,
    SYS_REBOOT                  = 169,
    SYS_SETHOSTNAME             = 170,
    SYS_SETDOMAINNAME           = 171,
    SYS_IOPL                    = 172,
    SYS_IOPERM                  = 173,
    SYS_CREATE_MODULE           = 174,
    SYS_INIT_MODULE             = 175,
    SYS_DELETE_MODULE           = 176,
    SYS_GET_KERNEL_SYMS         = 177,
    SYS_QUERY_MODULE            = 178,
    SYS_QUOTACTL                = 179,
    SYS_NFSSERVCTL              = 180,
    SYS_GETPMSG                 = 181,
    SYS_PUTPMSG                 = 182,
    SYS_AFS_SYSCALL             = 183,
    SYS_TUXCALL                 = 184,
    SYS_SECURITY                = 185,
    SYS_GETTID                  = 186,
    SYS_READAHEAD               = 187,
    SYS_SETXATTR                = 188,
    SYS_LSETXATTR               = 189,
    SYS_FSETXATTR               = 190,
    SYS_GETXATTR                = 191,
    SYS_LGETXATTR               = 192,
    SYS_FGETXATTR               = 193,
    SYS_LISTXATTR               = 194,
    SYS_LLISTXATTR              = 195,
    SYS_FLISTXATTR              = 196,
    SYS_REMOVEXATTR             = 197,
    SYS_LREMOVEXATTR            = 198,
    SYS_FREMOVEXATTR            = 199,
    SYS_TKILL                   = 200,
    SYS_TIME                    = 201,
    SYS_FUTEX                   = 202,
    SYS_SCHED_SETAFFINITY       = 203,
    SYS_SCHED_GETAFFINITY       = 204,
    SYS_SET_THREAD_AREA         = 205,
    SYS_IO_SETUP                = 206,
    SYS_IO_DESTROY              = 207,
    SYS_IO_GETEVENTS            = 208,
    SYS_IO_SUBMIT               = 209,
    SYS_IO_CANCEL               = 210,
    SYS_GET_THREAD_AREA         = 211,
    SYS_LOOKUP_DCOOKIE          = 212,
    SYS_EPOLL_CREATE            = 213,
    SYS_EPOLL_CTL_OLD           = 214,
    SYS_EPOLL_WAIT_OLD          = 215,
    SYS_REMAP_FILE_PAGES        = 216,
    SYS_GETDENTS64              = 217,
    SYS_SET_TID_ADDRESS         = 218,
    SYS_RESTART_SYSCALL         = 219,
    SYS_SEMTIMEDOP              = 220,
    SYS_FADVISE64               = 221,
    SYS_TIMER_CREATE            = 222,
    SYS_TIMER_SETTIME           = 223,
    SYS_TIMER_GETTIME           = 224,
    SYS_TIMER_GETOVERRUN        = 225,
    SYS_TIMER_DELETE            = 226,
    SYS_CLOCK_SETTIME           = 227,
    SYS_CLOCK_GETTIME           = 228,
    SYS_CLOCK_GETRES            = 229,
    SYS_CLOCK_NANOSLEEP         = 230,
    SYS_EXIT_GROUP              = 231,
    SYS_EPOLL_WAIT              = 232,
    SYS_EPOLL_CTL               = 233,
    SYS_TGKILL                  = 234,
    SYS_UTIMES                  = 235,
    SYS_VSERVER                 = 236,
    SYS_MBIND                   = 237,
    SYS_SET_MEMPOLICY           = 238,
    SYS_GET_MEMPOLICY           = 239,
    SYS_MQ_OPEN                 = 240,
    SYS_MQ_UNLINK               = 241,
    SYS_MQ_TIMEDSEND            = 242,
    SYS_MQ_TIMEDRECEIVE         = 243,
    SYS_MQ_NOTIFY               = 244,
    SYS_MQ_GETSETATTR           = 245,
    SYS_KEXEC_LOAD              = 246,
    SYS_WAITID                  = 247,
    SYS_ADD_KEY                 = 248,
    SYS_REQUEST_KEY             = 249,
    SYS_KEYCTL                  = 250,
    SYS_IOPRIO_SET              = 251,
    SYS_IOPRIO_GET              = 252,
    SYS_INOTIFY_INIT            = 253,
    SYS_INOTIFY_ADD_WATCH       = 254,
    SYS_INOTIFY_RM_WATCH        = 255,
    SYS_MIGRATE_PAGES           = 256,
    SYS_OPENAT                  = 257,
    SYS_MKDIRAT                 = 258,
    SYS_MKNODAT                 = 259,
    SYS_FCHOWNAT                = 260,
    SYS_FUTIMESAT               = 261,
    SYS_NEWFSTATAT              = 262,
    SYS_UNLINKAT                = 263,
    SYS_RENAMEAT                = 264,
    SYS_LINKAT                  = 265,
    SYS_SYMLINKAT               = 266,
    SYS_READLINKAT              = 267,
    SYS_FCHMODAT                = 268,
    SYS_FACCESSAT               = 269,
    SYS_PSELECT6                = 270,
    SYS_PPOLL                   = 271,
    SYS_UNSHARE                 = 272,
    SYS_SET_ROBUST_LIST         = 273,
    SYS_GET_ROBUST_LIST         = 274,
    SYS_SPLICE                  = 275,
    SYS_TEE                     = 276,
    SYS_SYNC_FILE_RANGE         = 277,
    SYS_VMSPLICE                = 278,
    SYS_MOVE_PAGES              = 279,  ; sys_move_pages()
    SYS_UTIMENSAT               = 280,  ; sys_utimensat()
    SYS_EPOLL_PWAIT             = 281,  ; sys_epoll_pwait()
    SYS_SIGNALFD                = 282,  ; sys_signalfd()
    SYS_TIMERFD_CREATE          = 283,  ; sys_timerfd_create()
    SYS_EVENTFD                 = 284,  ; sys_eventfd()
    SYS_FALLOCATE               = 285,  ; sys_fallocate()
    SYS_TIMERFD_SETTIME         = 286,  ; sys_timerfd_settime()
    SYS_TIMERFD_GETTIME         = 287,  ; sys_timerfd_gettime()
    SYS_ACCEPT4                 = 288,  ; sys_accept4()
    SYS_SIGNALFD4               = 289,  ; sys_signalfd4()
    SYS_EVENTFD2                = 290,  ; sys_eventfd2()
    SYS_EPOLL_CREATE1           = 291,  ; sys_epoll_create1()
    SYS_DUP3                    = 292,  ; sys_dup3()
    SYS_PIPE2                   = 293,  ; sys_pipe2()
    SYS_INOTIFY_INIT1           = 294,  ; sys_inotify_init1()
    SYS_PREADV                  = 295,  ; sys_preadv()
    SYS_PWRITEV                 = 296,  ; sys_pwritev()
    SYS_RT_TGSIGQUEUEINFO       = 297,  ; sys_rt_tgsigqueueinfo()
    SYS_PERF_EVENT_OPEN         = 298,  ; sys_perf_event_open()
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
    SYS_SCHED_SETATTR           = 314,  ; sys_sched_setattr()
    SYS_SCHED_GETATTR           = 315,  ; sys_sched_getattr()
    SYS_RENAMEAT2               = 316,  ; sys_renameat2()
    SYS_SECCOMP                 = 317,  ; sys_seccomp()
    SYS_GETRANDOM               = 318,  ; sys_getrandom()
    SYS_MEMFD_CREATE            = 319,  ; sys_memfd_create()
    SYS_KEXEC_FILE_LOAD         = 320,  ; sys_kexec_file_load()
    SYS_BPF                     = 321,  ; sys_bpf()
    SYS_EXECVAT                 = 322,  ; sys_execveat()
    SYS_USERFAULTFD             = 323,  ; sys_userfaultfd()
    SYS_MEMBARRIER              = 324,  ; sys_membarrier()
    SYS_MLOCK2                  = 325,  ; sys_mlock2()
    SYS_COPY_FILE_RANGE         = 326,  ; sys_copy_file_range()
    SYS_PREADV2                 = 327,  ; sys_preadv2()
    SYS_PWRITEV2                = 328,  ; sys_pwritev2()
    SYS_PKEY_MPROTECT           = 329,  ; sys_pkey_mprotect()
    SYS_PKEY_ALLOC              = 330,  ; sys_pkey_alloc()
    SYS_PKEY_FREE               = 331,  ; sys_pkey_free()
    SYS_STATX                   = 332,  ; sys_statx()
    SYS_IO_PGETEVENTS           = 333,  ; sys_io_pgetevents()
    SYS_RSEQ                    = 334,  ; sys_rseq()
    SYS_PIDFD_SEND_SIGNAL       = 424,  ; sys_pidfd_send_signal()
    SYS_IO_URING_SETUP          = 425,  ; sys_io_uring_setup()
    SYS_IO_URING_ENTER          = 426,  ; sys_io_uring_enter()
    SYS_IO_URING_REGISTER       = 427,  ; sys_io_uring_register()
    SYS_OPEN_TREE               = 428,  ; sys_open_tree()
    SYS_MOVE_MOUNT              = 429,  ; sys_move_mount()
    SYS_FSOPEN                  = 430,  ; sys_fsopen()
    SYS_FSCONFIG                = 431,  ; sys_fsconfig()
    SYS_FSMOUNT                 = 432,  ; sys_fsmount()
    SYS_FSPICK                  = 433,  ; sys_fspick()
    SYS_PIDFD_OPEN              = 434,  ; sys_pidfd_open()
    SYS_CLONE3                  = 435,  ; sys_clone3()
    SYS_CLOSE_RANGE             = 436,  ; sys_close_range()
    SYS_OPENAT2                 = 437,  ; sys_openat2()
    SYS_PIDFD_GETFD             = 438,  ; sys_pidfd_getfd()
    SYS_FACCESSAT2              = 439,  ; sys_faccessat2()
    SYS_PROCESS_MADVICE         = 440,  ; sys_process_madvise()
    SYS_EPOLL_PWAIT2            = 441,  ; sys_epoll_pwait2()
    SYS_MOUNT_SETATTR           = 442,  ; sys_mount_setattr()
    SYS_QUOTACTL_FD             = 443,  ; sys_quotactl_fd()
    SYS_LANDLOCK_CREATE_RULESET = 444,  ; sys_landlock_create_ruleset()
    SYS_LANDLOCK_ADD_RULE       = 445,  ; sys_landlock_add_rule()
    SYS_LANDLOCK_RESTRICT_SELF  = 446,  ; sys_landlock_restrict_self()
    SYS_MEMFD_SECRET            = 447,  ; sys_memfd_secret()
    SYS_PROCESS_MRELEASE        = 448,  ; sys_process_mrelease()
    SYS_FUTEX_WAITV             = 449,  ; sys_futex_waitv()
    SYS_SET_MEMPOLICY_HOME_NODE = 450,  ; sys_set_mempolicy_home_node()
    SYS_CACHESTAT               = 451,  ; sys_cachestat()
    SYS_FCHMODAT2               = 452,  ; sys_fchmodat2()
    SYS_MAP_SHADOW_STACK        = 453,  ; sys_map_shadow_stack()
    SYS_FUTEX_WAKE              = 454,  ; sys_futex_wake()
    SYS_FUTEX_WAIT              = 455,  ; sys_futex_wait()
    SYS_FUTEX_REQUEUE           = 456,  ; sys_futex_requeue()

else

    SYS_RESTART_SYSCALL         = 0,
    SYS_EXIT                    = 1,
    SYS_FORK                    = 2,
    SYS_READ                    = 3,
    SYS_WRITE                   = 4,
    SYS_OPEN                    = 5,
    SYS_CREAT                   = 8,
    SYS_CLOSE                   = 6,
    SYS_WAITPID                 = 7,
    SYS_LINK                    = 9,
    SYS_UNLINK                  = 10,
    SYS_EXECVE                  = 11,
    SYS_CHDIR                   = 12,
    SYS_TIME                    = 13,
    SYS_MKNOD                   = 14,
    SYS_CHMOD                   = 15,
    SYS_LCHOWN                  = 16,
    SYS_LSEEK                   = 19,
    SYS_GETPID                  = 20,
    SYS_MOUNT                   = 21,
    SYS_UMONT                   = 22,
    SYS_SETUID                  = 23,
    SYS_GETUID                  = 24,
    SYS_PTRACE                  = 26,
    SYS_ALARM                   = 27,
    SYS_PAUSE                   = 29,
    SYS_UTIME                   = 30,
    SYS_ACCESS                  = 33,
    SYS_SYNC                    = 36,
    SYS_KILL                    = 37,
    SYS_RENAME                  = 38,
    SYS_MKDIR                   = 39,
    SYS_RMDIR                   = 40,
    SYS_DUP                     = 41,
    SYS_PIPE                    = 42,
    SYS_TIMES                   = 43,
    SYS_BRK                     = 45,
    SYS_SETGID                  = 46,
    SYS_GETGID                  = 47,
    SYS_GETEUID                 = 50,
    SYS_GETEGID                 = 50,
    SYS_ACCT                    = 51,
    SYS_IOCTL                   = 54,
    SYS_FCNTL                   = 55,
    SYS_SETPGID                 = 57,
    SYS_UMASK                   = 60,
    SYS_CHROOT                  = 61,
    SYS_USTAT                   = 62,
    SYS_DUP2                    = 63,
    SYS_GETPPID                 = 64,
    SYS_GETPGRP                 = 65,
    SYS_SETSID                  = 66,
    SYS_SETREUID                = 70,
    SYS_SETREGID                = 71,
    SYS_SETHOSTNAME             = 74,
    SYS_GETRLIMIT               = 75,
    SYS_SETRLIMIT               = 75,
    SYS_GETRUSAGE               = 77,
    SYS_GETTIMEOFDAY            = 78,
    SYS_SETTIMEOFDAY            = 79,
    SYS_GETGROUPS               = 80,
    SYS_SETGROUPS               = 81,
    SYS_SELECT                  = 82,
    SYS_SYMLINK                 = 83,
    SYS_READLINK                = 85,
    SYS_USELIB                  = 86,
    SYS_SWAPON                  = 87,
    SYS_REBOOT                  = 88,
    SYS_MMAP                    = 90,
    SYS_MUNMAP                  = 91,
    SYS_TRUNCATE                = 92,
    SYS_FTRUNCATE               = 93,
    SYS_FCHMOD                  = 94,
    SYS_FCHOWN                  = 95,
    SYS_GETPRIORITY             = 96,
    SYS_SETPRIORITY             = 97,
    SYS_STATFS                  = 99,
    SYS_FSTATFS                 = 100,
    SYS_IOPERM                  = 101,
    SYS_SOCKETCALL              = 102,
    SYS_SYSLOG                  = 103,
    SYS_SETITIMER               = 104,
    SYS_GETITIMER               = 105,
    SYS_STAT                    = 106,
    SYS_LSTAT                   = 107,
    SYS_FSTAT                   = 108,
    SYS_IOPL                    = 110,
    SYS_VHANGUP                 = 111,
    SYS_WAIT4                   = 114,
    SYS_SWAPOFF                 = 115,
    SYS_SYSINFO                 = 116,
    SYS_FSYNC                   = 118,
    SYS_CLONE                   = 120,
    SYS_SETDOMAINNAME           = 121,
    SYS_UNAME                   = 122,
    SYS_MODIFY_LDT              = 123,
    SYS_ADJTIMEX                = 124,
    SYS_MPROTECT                = 125,
    SYS_INIT_MODULE             = 128,
    SYS_DELETE_MODULE           = 129,
    SYS_QUOTACTL                = 131,
    SYS_GETPGID                 = 132,
    SYS_FCHDIR                  = 133,
    SYS_SYSFS                   = 135,
    SYS_PERSONALITY             = 136,
    SYS_SETFSUID                = 138,
    SYS_SETFSGID                = 139,
    SYS_LLSEEK                  = 140,
    SYS_GETDENTS                = 141,
    SYS_FLOCK                   = 143,
    SYS_MSYNC                   = 144,
    SYS_READV                   = 145,
    SYS_WRITEV                  = 146,
    SYS_GETSID                  = 147,
    SYS_FDATASYNC               = 148,
    SYS_MLOCK                   = 150,
    SYS_MUNLOCK                 = 151,
    SYS_MLOCKALL                = 152,
    SYS_MUNLOCKALL              = 153,
    SYS_SCHED_SETPARAM          = 154,
    SYS_SCHED_GETPARAM          = 155,
    SYS_SCHED_SETSCHEDULER      = 156,
    SYS_SCHED_GETSCHEDULER      = 157,
    SYS_SCHED_YIELD             = 158,
    SYS_SCHED_GET_PRIORITY_MAX  = 159,
    SYS_SCHED_GET_PRIORITY_MIN  = 160,
    SYS_SCHED_RR_GET_INTERVAL   = 161,
    SYS_NANOSLEEP               = 162,
    SYS_MREMAP                  = 163,
    SYS_SETRESUID               = 164,
    SYS_GETRESUID               = 165,
    SYS_POLL                    = 168,
    SYS_NFSSERVCTL              = 169,
    SYS_SETRESGID               = 170,
    SYS_GETRESGID               = 171,
    SYS_PRCTL                   = 172,
    SYS_RT_SIGRETURN            = 173,
    SYS_RT_SIGACTION            = 174,
    SYS_RT_SIGPROCMASK          = 175,
    SYS_RT_SIGPENDING           = 176,
    SYS_RT_SIGTIMEDWAIT         = 177,
    SYS_RT_SIGQUEUEINFO         = 178,
    SYS_RT_SIGSUSPEND           = 179,
    SYS_PREAD64                 = 180,
    SYS_PWRITE64                = 181,
    SYS_CHOWN                   = 182,
    SYS_GETCWD                  = 183,
    SYS_CAPGET                  = 184,
    SYS_CAPSET                  = 185,
    SYS_SIGALTSTACK             = 186,
    SYS_SENDFILE                = 187,
    SYS_VFORK                   = 190,
    SYS_TRUNCATE64              = 193,
    SYS_FTRUNCATE64             = 194,
    SYS_STAT64                  = 195,
    SYS_LSTAT64                 = 196,
    SYS_FSTAT64                 = 197,
    SYS_PIVOT_ROOT              = 217,
    SYS_MINCORE                 = 218,
    SYS_MADVISE                 = 219,
    SYS_GETDENTS64              = 220,
    SYS_GETTID                  = 224,
    SYS_READAHEAD               = 225,
    SYS_SETXATTR                = 226,
    SYS_LSETXATTR               = 227,
    SYS_FSETXATTR               = 228,
    SYS_GETXATTR                = 229,
    SYS_LGETXATTR               = 230,
    SYS_FGETXATTR               = 231,
    SYS_LISTXATTR               = 232,
    SYS_LLISTXATTR              = 233,
    SYS_FLISTXATTR              = 234,
    SYS_REMOVEXATTR             = 235,
    SYS_LREMOVEXATTR            = 235,
    SYS_FREMOVEXATTR            = 237,
    SYS_TKILL                   = 238,
    SYS_SENDFILE64              = 239,
    SYS_FUTEX                   = 240,
    SYS_SCHED_GETAFFINITY       = 242,
    SYS_SET_THREAD_AREA         = 243,
    SYS_GET_THREAD_AREA         = 244,
    SYS_IO_SETUP                = 245,
    SYS_IO_DESTROY              = 246,
    SYS_IO_GETEVENTS            = 247,
    SYS_IO_SUBMIT               = 248,
    SYS_IO_CANCEL               = 249,
    SYS_FADVISE64               = 250,
    SYS_EXIT_GROUP              = 252,
    SYS_LOOKUP_DCOOKIE          = 253,
    SYS_EPOLL_CREATE            = 254,
    SYS_EPOLL_CTL               = 255,
    SYS_EPOLL_WAIT              = 256,
    SYS_REMAP_FILE_PAGES        = 257,
    SYS_SET_TID_ADDRESS         = 258,
    SYS_TIMER_CREATE            = 259,
    SYS_TIMER_SETTIME           = 260,
    SYS_TIMER_GETTIME           = 261,
    SYS_TIMER_GETOVERRUN        = 262,
    SYS_TIMER_DELETE            = 263,
    SYS_CLOCK_SETTIME           = 264,
    SYS_CLOCK_GETTIME           = 265,
    SYS_CLOCK_GETRES            = 266,
    SYS_CLOCK_NANOSLEEP         = 267,
    SYS_TGKILL                  = 270,
    SYS_UTIMES                  = 271,
    SYS_MBIND                   = 274,
    SYS_GET_MEMPOLICY           = 275,
    SYS_SET_MEMPOLICY           = 276,
    SYS_MQ_OPEN                 = 277,
    SYS_MQ_UNLINK               = 278,
    SYS_MQ_TIMEDSEND            = 279,
    SYS_MQ_TIMEDRECEIVE         = 280,
    SYS_MQ_NOTIFY               = 281,
    SYS_MQ_GETSETATTR           = 282,
    SYS_KEXEC_LOAD              = 283,
    SYS_WAITID                  = 284,
    SYS_ADD_KEY                 = 286,
    SYS_REQUEST_KEY             = 287,
    SYS_KEYCTL                  = 288,
    SYS_IOPRIO_SET              = 289,
    SYS_IOPRIO_GET              = 290,
    SYS_INOTIFY_INIT            = 291,
    SYS_INOTIFY_ADD_WATCH       = 292,
    SYS_INOTIFY_RM_WATCH        = 293,
    SYS_MIGRATE_PAGES           = 294,
    SYS_OPENAT                  = 295,
    SYS_MKDIRAT                 = 296,
    SYS_MKNODAT                 = 297,
    SYS_FCHOWNAT                = 298,
    SYS_FUTIMESAT               = 299,
    SYS_NEWFSTATAT              = 300,
    SYS_UNLINKAT                = 301,
    SYS_RENAMEAT                = 302,
    SYS_LINKAT                  = 303,
    SYS_SYMLINKAT               = 304,
    SYS_READLINKAT              = 305,
    SYS_FCHMODAT                = 306,
    SYS_FACCESSAT               = 307,
    SYS_PSELECT6                = 308,
    SYS_PPOLL                   = 309,
    SYS_UNSHARE                 = 310,
    SYS_SET_ROBUST_LIST         = 311,
    SYS_GET_ROBUST_LIST         = 312,
    SYS_SPLICE                  = 313,
    SYS_SYNC_FILE_RANGE         = 314,
    SYS_TEE                     = 315,
    SYS_VMSPLICE                = 316,

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
sys_close proto :int_t {
    mov eax,SYS_CLOSE
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
sys_poll proto :ptr, :uint_t, :int_t {
    mov eax,SYS_POLL
    syscall
    }
sys_lseek proto :int_t, :size_t, :uint_t {
    mov eax,SYS_LSEEK
    syscall
    }
sys_mmap proto :ptr, :size_t, :size_t, :size_t, :size_t, :size_t {
    mov r10,rcx
    mov rcx,rsi
    mov eax,SYS_MMAP
    syscall
    }
sys_mprotect proto :ptr, :size_t, :ulong_t {
    mov eax,SYS_MPROTECT
    syscall
    }
sys_munmap proto :ptr, :size_t {
    mov eax,SYS_MUNMAP
    syscall
    }
sys_brk proto :ptr {
    mov eax,SYS_BRK
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
sys_ioctl proto :int_t, :int_t, :ptr {
    mov eax,SYS_IOCTL
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
sys_readv proto :ulong_t, :ptr, :ulong_t {
    mov eax,SYS_READV
    syscall
    }
sys_writev proto :ulong_t, :ptr, :ulong_t {
    mov eax,SYS_WRITEV
    syscall
    }
sys_access proto :string_t, :int_t {
    mov eax,SYS_ACCESS
    syscall
    }
sys_pipe proto :ptr int_t {
    mov eax,SYS_PIPE
    syscall
    }
sys_select proto :int_t, :ptr, :ptr, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_SELECT
    syscall
    }
sys_sched_yield proto {
    mov eax,SYS_SCHED_YIELD
    syscall
    }
sys_mremap proto :ptr, :ulong_t, :ulong_t, :ulong_t, :ptr {
    mov r10,rcx
    mov eax,SYS_MREMAP
    syscall
    }
sys_msync proto :ptr, :size_t, :int_t {
    mov eax,SYS_MSYNC
    syscall
    }
sys_mincore proto :ptr, :size_t, :ptr {
    mov eax,SYS_MINCORE
    syscall
    }
sys_madvise proto :ptr, :size_t, :int_t {
    mov eax,SYS_MADVISE
    syscall
    }
sys_shmget proto :int_t, :size_t, :int_t {
    mov eax,SYS_SHMGET
    syscall
    }
sys_shmat proto :int_t, :ptr, :int_t {
    mov eax,SYS_SHMAT
    syscall
    }
sys_shmctl proto :int_t, :int_t, :ptr {
    mov eax,SYS_SHMCTL
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
sys_pause proto {
    mov eax,SYS_PAUSE
    syscall
    }
sys_nanosleep proto :ptr, :ptr {
    mov eax,SYS_NANOSLEEP
    syscall
    }
sys_getitimer proto :int_t, :ptr {
    mov eax,SYS_GETITIMER
    syscall
    }
sys_alarm proto :uint_t {
    mov eax,SYS_ALARM
    syscall
    }
sys_setitimer proto :int_t, :ptr, :ptr {
    mov eax,SYS_SETITIMER
    syscall
    }
sys_getpid proto {
    mov eax,SYS_GETPID
    syscall
    }
sys_sendfile64 proto :int_t, :int_t, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_SENDFILE
    syscall
    }
sys_socket proto :int_t, :int_t, :int_t {
    mov eax,SYS_SOCKET
    syscall
    }
sys_connect proto :int_t, :ptr, :int_t {
    mov eax,SYS_CONNECT
    syscall
    }
sys_accept proto :int_t, :ptr, :int_t {
    mov eax,SYS_ACCEPT
    syscall
    }
sys_sendto proto :int_t, :ptr, :size_t, :uint_t, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_SENDTO
    syscall
    }
sys_recvfrom proto :int_t, :ptr, :size_t, :uint_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_RECVFROM
    syscall
    }
sys_sendmsg proto :int_t, :ptr, :uint_t {
    mov eax,SYS_SENDMSG
    syscall
    }
sys_recvmsg proto :int_t, :ptr, :uint_t {
    mov eax,SYS_RECVMSG
    syscall
    }
sys_shutdown proto :int_t, :int_t {
    mov eax,SYS_SHUTDOWN
    syscall
    }
sys_bind proto :int_t, :ptr, :int_t {
    mov eax,SYS_BIND
    syscall
    }
sys_listen proto :int_t, :int_t {
    mov eax,SYS_LISTEN
    syscall
    }
sys_getsockname proto :int_t, :ptr, :ptr {
    mov eax,SYS_GETSOCKNAME
    syscall
    }
sys_getpeername proto :int_t, :ptr, :ptr {
    mov eax,SYS_GETPEERNAME
    syscall
    }
sys_socketpair proto :int_t, :int_t, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_SOCKETPAIR
    syscall
    }
sys_setsockopt proto :int_t, :int_t, :int_t, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_SETSOCKOPT
    syscall
    }
sys_getsockopt proto :int_t, :int_t, :int_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_GETSOCKOPT
    syscall
    }
sys_clone proto :size_t, :size_t, :ptr int_t, :size_t, :ptr int_t {
    mov r10,rcx
    mov eax,SYS_CLONE
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
sys_exit proto :int_t {
    mov eax,SYS_EXIT
    syscall
    }
sys_wait4 proto :int_t, :ptr int_t, :int_t, :ptr rusage {
    mov r10,rcx
    mov eax,SYS_WAIT4
    syscall
    }
sys_kill proto :int_t, :int_t {
    mov eax,SYS_KILL
    syscall
    }
sys_newuname proto :ptr {
    mov eax,SYS_UNAME
    syscall
    }
sys_semget proto :int_t, :int_t, :int_t {
    mov eax,SYS_SEMGET
    syscall
    }
sys_semop proto :int_t, :ptr, :uint_t {
    mov eax,SYS_SEMOP
    syscall
    }
sys_semctl proto :int_t, :int_t, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_SEMCTL
    syscall
    }
sys_shmdt proto :ptr {
    mov eax,SYS_SHMDT
    syscall
    }
sys_msgget proto :int_t, :int_t {
    mov eax,SYS_MSGGET
    syscall
    }
sys_msgsnd proto :int_t, :ptr, :size_t, :int_t {
    mov r10,rcx
    mov eax,SYS_MSGSND
    syscall
    }
sys_msgrcv proto :int_t, :ptr, :size_t, :long_t, :int_t {
    mov r10,rcx
    mov eax,SYS_MSGRCV
    syscall
    }
sys_msgctl proto :int_t, :int_t, :ptr {
    mov eax,SYS_MSGCTL
    syscall
    }
sys_fcntl proto :int_t, :int_t, :int_t {
    mov eax,SYS_FCNTL
    syscall
    }
sys_flock proto :uint_t, :uint_t {
    mov eax,SYS_FLOCK
    syscall
    }
sys_fsync proto :int_t {
    mov eax,SYS_FSYNC
    syscall
    }
sys_fdatasync proto :int_t {
    mov eax,SYS_FDATASYNC
    syscall
    }
sys_truncate proto :ptr, :int64_t {
    mov eax,SYS_TRUNCATE
    syscall
    }
sys_ftruncate proto :uint_t, :int64_t {
    mov eax,SYS_FTRUNCATE
    syscall
    }
sys_getdents proto :int_t, :ptr, :uint_t {
    mov eax,SYS_GETDENTS
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
sys_fchdir proto :int_t {
    mov eax,SYS_FCHDIR
    syscall
    }
sys_rename proto :string_t, :string_t {
    mov eax,SYS_RENAME
    syscall
    }
sys_mkdir proto :string_t, :int_t {
    mov eax,SYS_MKDIR
    syscall
    }
sys_rmdir proto :string_t {
    mov eax,SYS_RMDIR
    syscall
    }
sys_creat proto :string_t, :uint_t {
    mov eax,SYS_CREAT
    syscall
    }
sys_link proto :string_t, :string_t {
    mov eax,SYS_LINK
    syscall
    }
sys_unlink proto :string_t {
    mov eax,SYS_UNLINK
    syscall
    }
sys_symlink proto :string_t, :string_t {
    mov eax,SYS_SYMLINK
    syscall
    }
sys_readlink proto :string_t, :string_t, :int_t {
    mov eax,SYS_READLINK
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
sys_chown proto :string_t, :uint_t, :uint_t {
    mov eax,SYS_CHOWN
    syscall
    }
sys_fchown proto :int_t, :uint_t, :uint_t {
    mov eax,SYS_FCHOWN
    syscall
    }
sys_lchown proto :string_t, :uint_t, :uint_t {
    mov eax,SYS_LCHOWN
    syscall
    }
sys_umask proto :int_t {
    mov eax,SYS_UMASK
    syscall
    }
sys_gettimeofday proto :ptr, :ptr {
    mov eax,SYS_GETTIMEOFDAY
    syscall
    }
sys_getrlimit proto :uint_t, :ptr {
    mov eax,SYS_GETRLIMIT
    syscall
    }
sys_getrusage proto :int_t, :ptr {
    mov eax,SYS_GETRUSAGE
    syscall
    }
sys_sysinfo proto :ptr {
    mov eax,SYS_SYSINFO
    syscall
    }
sys_times proto :ptr {
    mov eax,SYS_TIMES
    syscall
    }
sys_ptrace proto :long_t, :long_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_PTRACE
    syscall
    }
sys_getuid proto {
    mov eax,SYS_GETUID
    syscall
    }
sys_syslog proto :int_t, :ptr, :int_t {
    mov eax,SYS_SYSLOG
    syscall
    }
sys_getgid proto {
    mov eax,SYS_GETGID
    syscall
    }
sys_setuid proto :int_t {
    mov eax,SYS_SETUID
    syscall
    }
sys_setgid proto :int_t {
    mov eax,SYS_SETGID
    syscall
    }
sys_geteuid proto {
    mov eax,SYS_GETEUID
    syscall
    }
sys_getegid proto {
    mov eax,SYS_GETEGID
    syscall
    }
sys_setpgid proto :int_t, :int_t {
    mov eax,SYS_SETPGID
    syscall
    }
sys_getppid proto {
    mov eax,SYS_GETPPID
    syscall
    }
sys_getpgrp proto {
    mov eax,SYS_GETPGRP
    syscall
    }
sys_setsid proto {
    mov eax,SYS_SETSID
    syscall
    }
sys_setreuid proto :int_t, :int_t {
    mov eax,SYS_SETREUID
    syscall
    }
sys_setregid proto :int_t, :int_t {
    mov eax,SYS_SETREGID
    syscall
    }
sys_getgroups proto :int_t, :ptr {
    mov eax,SYS_GETGROUPS
    syscall
    }
sys_setgroups proto :int_t, :ptr {
    mov eax,SYS_SETGROUPS
    syscall
    }
sys_setresuid proto :int_t, :int_t, :int_t {
    mov eax,SYS_SETRESUID
    syscall
    }
sys_getresuid proto :ptr, :ptr, :ptr {
    mov eax,SYS_GETRESUID
    syscall
    }
sys_setresgid proto :int_t, :int_t, :int_t {
    mov eax,SYS_SETRESGID
    syscall
    }
sys_getresgid proto :ptr, :ptr, :ptr {
    mov eax,SYS_GETRESGID
    syscall
    }
sys_getpgid proto :int_t {
    mov eax,SYS_GETPGID
    syscall
    }
sys_setfsuid proto :int_t {
    mov eax,SYS_SETFSUID
    syscall
    }
sys_setfsgid proto :int_t {
    mov eax,SYS_SETFSGID
    syscall
    }
sys_getsid proto :int_t {
    mov eax,SYS_GETSID
    syscall
    }
sys_capget proto :ptr, :ptr {
    mov eax,SYS_CAPGET
    syscall
    }
sys_capset proto :ptr, :ptr {
    mov eax,SYS_CAPSET
    syscall
    }
sys_rt_sigpending proto :ptr, :size_t {
    mov eax,SYS_RT_SIGPENDING
    syscall
    }
sys_rt_sigtimedwait proto :ptr, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_RT_SIGTIMEDWAIT
    syscall
    }
sys_rt_sigqueueinfo proto :int_t, :int_t, :ptr {
    mov eax,SYS_RT_SIGQUEUEINFO
    syscall
    }
sys_rt_sigsuspend proto :ptr, :size_t {
    mov eax,SYS_RT_SIGSUSPEND
    syscall
    }
sys_sigaltstack proto :ptr, :ptr {
    mov eax,SYS_SIGALTSTACK
    syscall
    }
sys_utime proto :string_t, :ptr {
    mov eax,SYS_UTIME
    syscall
    }
sys_mknod proto :ptr, :int_t, :int_t {
    mov eax,SYS_MKNOD
    syscall
    }
sys_uselib proto {
    mov eax,SYS_USELIB
    syscall
    }
sys_personality proto :uint_t {
    mov eax,SYS_PERSONALITY
    syscall
    }
sys_ustat proto :uint_t, :ptr {
    mov eax,SYS_USTAT
    syscall
    }
sys_statfs proto :ptr, :ptr {
    mov eax,SYS_STATFS
    syscall
    }
sys_fstatfs proto :uint_t, :ptr {
    mov eax,SYS_FSTATFS
    syscall
    }
sys_sysfs proto :int_t, :uint_t, :ptr {
    mov eax,SYS_SYSFS
    syscall
    }
sys_getpriority proto :int_t, :int_t {
    mov eax,SYS_GETPRIORITY
    syscall
    }
sys_setpriority proto :int_t, :int_t, :int_t {
    mov eax,SYS_SETPRIORITY
    syscall
    }
sys_sched_setparam proto :int_t, :ptr {
    mov eax,SYS_SCHED_SETPARAM
    syscall
    }
sys_sched_getparam proto :int_t, :ptr {
    mov eax,SYS_SCHED_GETPARAM
    syscall
    }
sys_sched_setscheduler proto :int_t, :int_t, :ptr {
    mov eax,SYS_SCHED_SETSCHEDULER
    syscall
    }
sys_sched_getscheduler proto :int_t {
    mov eax,SYS_SCHED_GETSCHEDULER
    syscall
    }
sys_sched_get_priority_max proto :int_t {
    mov eax,SYS_SCHED_GET_PRIORITY_MAX
    syscall
    }
sys_sched_get_priority_min proto :int_t {
    mov eax,SYS_SCHED_GET_PRIORITY_MIN
    syscall
    }
sys_sched_rr_get_interval proto :int_t, :ptr {
    mov eax,SYS_SCHED_RR_GET_INTERVAL
    syscall
    }
sys_mlock proto :ptr, :size_t {
    mov eax,SYS_MLOCK
    syscall
    }
sys_munlock proto :ptr, :size_t {
    mov eax,SYS_MUNLOCK
    syscall
    }
sys_mlockall proto :int_t {
    mov eax,SYS_MLOCKALL
    syscall
    }
sys_munlockall proto {
    mov eax,SYS_MUNLOCKALL
    syscall
    }
sys_vhangup proto {
    mov eax,SYS_VHANGUP
    syscall
    }
sys_modify_ldt proto :int_t, :ptr, :ulong_t {
    mov eax,SYS_MODIFY_LDT
    syscall
    }
sys_pivot_root proto :ptr, :ptr {
    mov eax,SYS_PIVOT_ROOT
    syscall
    }
sys_ni_syscall proto {
    mov eax,SYS_NI_SYSCALL
    syscall
    }
sys_prctl proto :int_t, :ptr, :ptr, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_PRCTL
    syscall
    }
sys_arch_prctl proto :int_t, :ptr {
    mov eax,SYS_ARCH_PRCTL
    syscall
    }
sys_adjtimex proto :ptr {
    mov eax,SYS_ADJTIMEX
    syscall
    }
sys_setrlimit proto :uint_t, :ptr {
    mov eax,SYS_SETRLIMIT
    syscall
    }
sys_chroot proto :string_t {
    mov eax,SYS_CHROOT
    syscall
    }
sys_sync proto {
    mov eax,SYS_SYNC
    syscall
    }
sys_acct proto :string_t {
    mov eax,SYS_ACCT
    syscall
    }
sys_settimeofday proto :ptr, :ptr {
    mov eax,SYS_SETTIMEOFDAY
    syscall
    }
sys_mount proto :ptr, :ptr, :ptr, :ulong_t, :ptr {
    mov r10,rcx
    mov eax,SYS_MOUNT
    syscall
    }
sys_umount proto :ptr, :int_t {
    mov eax,SYS_UMONT
    syscall
    }
sys_swapon proto :ptr, :int_t {
    mov eax,SYS_SWAPON
    syscall
    }
sys_swapoff proto :ptr {
    mov eax,SYS_SWAPOFF
    syscall
    }
sys_reboot proto :int_t, :int_t, :uint_t, :ptr {
    mov r10,rcx
    mov eax,SYS_REBOOT
    syscall
    }
sys_sethostname proto :ptr, :int_t {
    mov eax,SYS_SETHOSTNAME
    syscall
    }
sys_setdomainname proto :ptr, :int_t {
    mov eax,SYS_SETDOMAINNAME
    syscall
    }
sys_iopl proto :int_t {
    mov eax,SYS_IOPL
    syscall
    }
sys_ioperm proto :uint64_t, :uint64_t, :int_t {
    mov eax,SYS_IOPERM
    syscall
    }
sys_init_module proto :ptr, :uint64_t, :ptr {
    mov eax,SYS_INIT_MODULE
    syscall
    }
sys_delete_module proto :ptr, :uint_t {
    mov eax,SYS_DELETE_MODULE
    syscall
    }
sys_quotactl proto :int_t, :ptr, :int_t, :ptr {
    mov eax,SYS_QUOTACTL
    syscall
    }
sys_gettid proto {
    mov eax,SYS_GETTID
    syscall
    }
sys_readahead proto :int_t, :int64_t, :size_t {
    mov eax,SYS_READAHEAD
    syscall
    }
sys_setxattr proto :ptr, :ptr, :size_t, :int_t {
    mov r10,rcx
    mov eax,SYS_SETXATTR
    syscall
    }
sys_lsetxattr proto :ptr, :ptr, :ptr, :size_t, :int_t {
    mov r10,rcx
    mov eax,SYS_LSETXATTR
    syscall
    }
sys_fsetxattr proto :int_t, :ptr, :ptr, :size_t, :int_t {
    mov r10,rcx
    mov eax,SYS_FSETXATTR
    syscall
    }
sys_getxattr proto :ptr, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_GETXATTR
    syscall
    }
sys_lgetxattr proto :ptr, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_LGETXATTR
    syscall
    }
sys_fgetxattr proto :int_t, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_FGETXATTR
    syscall
    }
sys_listxattr proto :ptr, :ptr, :size_t {
    mov eax,SYS_LISTXATTR
    syscall
    }
sys_llistxattr proto :ptr, :ptr, :size_t {
    mov eax,SYS_LLISTXATTR
    syscall
    }
sys_flistxattr proto :int_t, :ptr, :size_t {
    mov eax,SYS_FLISTXATTR
    syscall
    }
sys_removexattr proto :ptr, :ptr {
    mov eax,SYS_REMOVEXATTR
    syscall
    }
sys_lremovexattr proto :ptr, :ptr {
    mov eax,SYS_LREMOVEXATTR
    syscall
    }
sys_fremovexattr proto :int_t, :ptr {
    mov eax,SYS_FREMOVEXATTR
    syscall
    }
sys_tkill proto :int_t, :int_t {
    mov eax,SYS_TKILL
    syscall
    }
sys_time proto :ptr {
    mov eax,SYS_TIME
    syscall
    }
sys_futex proto :ptr, :int_t, :uint_t, :ptr, :ptr, :uint_t {
    mov r10,rcx
    mov eax,SYS_FUTEX
    syscall
    }
sys_sched_setaffinity proto :int_t, :uint_t, :ptr {
    mov eax,SYS_SCHED_SETAFFINITY
    syscall
    }
sys_sched_getaffinity proto :int_t, :uint_t, :ptr {
    mov eax,SYS_SCHED_GETAFFINITY
    syscall
    }
sys_io_setup proto :uint_t, :ptr {
    mov eax,SYS_IO_SETUP
    syscall
    }
sys_io_destroy proto :ptr {
    mov eax,SYS_IO_DESTROY
    syscall
    }
sys_io_getevents proto :ptr, :long_t, :long_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_IO_GETEVENTS
    syscall
    }
sys_io_submit proto :ptr, :long_t, :ptr {
    mov eax,SYS_IO_SUBMIT
    syscall
    }
sys_io_cancel proto :ptr, :ptr, :ptr {
    mov eax,SYS_IO_CANCEL
    syscall
    }
sys_epoll_create proto :int_t {
    mov eax,SYS_EPOLL_CREATE
    syscall
    }
sys_remap_file_pages proto :ulong_t, :ulong_t, :ulong_t, :ulong_t, :ulong_t {
    mov r10,rcx
    mov eax,SYS_REMAP_FILE_PAGES
    syscall
    }
sys_getdents64 proto :int_t, :ptr, :uint_t {
    mov eax,SYS_GETDENTS64
    syscall
    }
sys_set_tid_address proto :ptr {
    mov eax,SYS_SET_TID_ADDRESS
    syscall
    }
sys_restart_syscall proto {
    mov eax,SYS_RESTART_SYSCALL
    syscall
    }
sys_semtimedop proto :int_t, :ptr, :uint_t, :ptr {
    mov r10,rcx
    mov eax,SYS_SEMTIMEDOP
    syscall
    }
sys_fadvise64 proto :int_t, :int64_t, :size_t, :int_t {
    mov r10,rcx
    mov eax,SYS_FADVISE64
    syscall
    }
sys_timer_create proto :int_t, :ptr, :ptr {
    mov eax,SYS_TIMER_CREATE
    syscall
    }
sys_timer_settime proto :int_t, :int_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_TIMER_SETTIME
    syscall
    }
sys_timer_gettime proto :int_t, :ptr {
    mov eax,SYS_TIMER_GETTIME
    syscall
    }
sys_timer_getoverrun proto :int_t {
    mov eax,SYS_TIMER_GETOVERRUN
    syscall
    }
sys_timer_delete proto :int_t {
    mov eax,SYS_TIMER_DELETE
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
sys_exit_group proto :int_t {
    mov eax,SYS_EXIT_GROUP
    syscall
    }
sys_epoll_wait proto :int_t, :ptr, :int_t, :int_t  {
    mov r10,rcx
    mov eax,SYS_EPOLL_WAIT
    syscall
    }
sys_epoll_ctl proto :int_t, :int_t, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_EPOLL_CTL
    syscall
    }
sys_tgkill proto :int_t, :int_t, :int_t {
    mov eax,SYS_TGKILL
    syscall
    }
sys_utimes proto :ptr, :ptr {
    mov eax,SYS_UTIMES
    syscall
    }
sys_mbind proto :ulong_t, :ulong_t, :ulong_t, :ptr, :ulong_t, :ulong_t {
    mov r10,rcx
    mov eax,SYS_MBIND
    syscall
    }
sys_set_mempolicy proto :int_t, :ptr, :ulong_t {
    mov eax,SYS_SET_MEMPOLICY
    syscall
    }
sys_get_mempolicy proto :ptr, :ulong_t, :ulong_t, :ulong_t {
    mov eax,SYS_GET_MEMPOLICY
    syscall
    }
sys_mq_open proto :ptr, :int_t, :int_t, :ptr {
    mov eax,SYS_MQ_OPEN
    syscall
    }
sys_mq_unlink proto :ptr {
    mov eax,SYS_MQ_UNLINK
    syscall
    }
sys_mq_timedsend proto :int_t, :ptr, :size_t, :uint_t, :ptr {
    mov r10,rcx
    mov eax,SYS_MQ_TIMEDSEND
    syscall
    }
sys_mq_timedreceive proto :int_t, :ptr, :size_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_MQ_TIMEDRECEIVE
    syscall
    }
sys_mq_notify proto :int_t, :ptr {
    mov eax,SYS_MQ_NOTIFY
    syscall
    }
sys_mq_getsetattr proto :int_t, :ptr, :ptr {
    mov eax,SYS_MQ_GETSETATTR
    syscall
    }
sys_kexec_load proto :ulong_t, :ulong_t, :ptr, :ulong_t {
    mov r10,rcx
    mov eax,SYS_KEXEC_LOAD
    syscall
    }
sys_waitid proto :int_t, :int_t, :ptr, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_WAITID
    syscall
    }
sys_add_key proto :ptr, :ptr, :ptr, :size_t, :ptr {
    mov r10,rcx
    mov eax,SYS_ADD_KEY
    syscall
    }
sys_request_key proto :ptr, :ptr, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_REQUEST_KEY
    syscall
    }
sys_keyctl proto :int_t, :ptr, :ptr, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_KEYCTL
    syscall
    }
sys_ioprio_set proto :int_t, :int_t, :int_t {
    mov eax,SYS_IOPRIO_SET
    syscall
    }
sys_ioprio_get proto :int_t, :int_t {
    mov eax,SYS_IOPRIO_GET
    syscall
    }
sys_inotify_init proto {
    mov eax,SYS_INOTIFY_INIT
    syscall
    }
sys_inotify_add_watch proto :int_t, :ptr, :uint_t {
    mov eax,SYS_INOTIFY_ADD_WATCH
    syscall
    }
sys_inotify_rm_watch proto :int_t, :int_t {
    mov eax,SYS_INOTIFY_RM_WATCH
    syscall
    }
sys_migrate_pages proto :int_t, :uint64_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_MIGRATE_PAGES
    syscall
    }
sys_openat proto :int_t, :ptr, :int_t, :int_t {
    mov r10,rcx
    mov eax,SYS_OPENAT
    syscall
    }
sys_mkdirat proto :int_t, :ptr, :int_t {
    mov eax,SYS_MKDIRAT
    syscall
    }
sys_mknodat proto :int_t, :ptr, :int_t {
    mov eax,SYS_MKNODAT
    syscall
    }
sys_fchownat proto :int_t, :ptr, :int_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_FCHOWNAT
    syscall
    }
sys_futimesat proto :int_t, :ptr, :int_t, :int_t, :int_t {
    mov r10,rcx
    mov eax,SYS_FUTIMESAT
    syscall
    }
sys_newfstatat proto :int_t, :ptr, :ptr {
    mov eax,SYS_NEWFSTATAT
    syscall
    }
sys_unlinkat proto :int_t, :ptr, :int_t {
    mov eax,SYS_UNLINKAT
    syscall
    }
sys_renameat proto :int_t, :ptr, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_RENAMEAT
    syscall
    }
sys_linkat proto :int_t, :ptr, :int_t, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_LINKAT
    syscall
    }
sys_symlinkat proto :ptr, :int_t, :ptr {
    mov eax,SYS_SYMLINKAT
    syscall
    }
sys_readlinkat proto :int_t, :ptr, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_READLINKAT
    syscall
    }
sys_fchmodat proto :int_t, :ptr, :int_t {
    mov eax,SYS_FCHMODAT
    syscall
    }
sys_faccessat proto :int_t, :ptr, :ptr {
    mov eax,SYS_FACCESSAT
    syscall
    }
sys_pselect6 proto :int_t, :ptr, :ptr, :ptr, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_PSELECT6
    syscall
    }
sys_ppoll proto :ptr, :uint_t, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_PPOLL
    syscall
    }
sys_unshare proto :uint_t {
    mov eax,SYS_UNSHARE
    syscall
    }
sys_set_robust_list proto :ptr, :size_t {
    mov eax,SYS_SET_ROBUST_LIST
    syscall
    }
sys_get_robust_list proto :int_t, :ptr, :ptr {
    mov eax,SYS_GET_ROBUST_LIST
    syscall
    }
sys_splice proto :int_t, :ptr, :int_t, :ptr, :size_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_SPLICE
    syscall
    }
sys_tee proto :int_t, :int_t, :size_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_TEE
    syscall
    }
sys_sync_file_range proto :int_t, :int64_t, :int64_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_SYNC_FILE_RANGE
    syscall
    }
sys_vmsplice proto :int_t, :ptr, :ulong_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_VMSPLICE
    syscall
    }

;;;;;;;;;;;;;;;;;;;;;;

sys_move_pages proto :int_t, :ptr, :ptr, :ptr, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_MOVE_PAGES
    syscall
    }
sys_utimensat proto :int_t, :ptr, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_UTIMENSAT
    syscall
    }
sys_epoll_pwait proto :int_t, :ptr, :int_t, :int_t, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_EPOLL_PWAIT
    syscall
    }
sys_signalfd proto :int_t, :ptr, :size_t {
    mov eax,SYS_SIGNALFD
    syscall
    }
sys_timerfd_create proto :int_t, :int_t {
    mov eax,SYS_TIMERFD_CREATE
    syscall
    }
sys_eventfd proto :uint_t {
    mov eax,SYS_EVENTFD
    syscall
    }
sys_fallocate proto :int_t, :int_t, :int64_t, :int64_t {
    mov r10,rcx
    mov eax,SYS_FALLOCATE
    syscall
    }
sys_timerfd_settime proto :int_t, :int_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_TIMERFD_SETTIME
    syscall
    }
sys_timerfd_gettime proto :int_t, :ptr {
    mov eax,SYS_TIMERFD_GETTIME
    syscall
    }
sys_accept4 proto :int_t, :ptr, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_ACCEPT4
    syscall
    }
sys_signalfd4 proto :int_t, :ptr, :size_t, :int_t {
    mov r10,rcx
    mov eax,SYS_SIGNALFD4
    syscall
    }
sys_eventfd2 proto :uint_t, :int_t {
    mov eax,SYS_EVENTFD2
    syscall
    }
sys_epoll_create1 proto :int_t {
    mov eax,SYS_EPOLL_CREATE1
    syscall
    }
sys_dup3 proto :int_t, :int_t, :int_t {
    mov eax,SYS_DUP3
    syscall
    }
sys_pipe2 proto :ptr, :int_t {
    mov eax,SYS_PIPE2
    syscall
    }
sys_inotify_init1 proto :int_t {
    mov eax,SYS_INOTIFY_INIT1
    syscall
    }
sys_preadv proto :uint64_t, :ptr, :uint64_t, :uint64_t, :uint64_t {
    mov r10,rcx
    mov eax,SYS_PREADV
    syscall
    }
sys_pwritev proto :uint64_t, :ptr, :uint64_t, :uint64_t, :uint64_t {
    mov r10,rcx
    mov eax,SYS_PWRITEV
    syscall
    }
sys_rt_tgsigqueueinfo proto :int_t, :int_t, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_RT_TGSIGQUEUEINFO
    syscall
    }
sys_perf_event_open proto :ptr, :int_t, :int_t, :int_t, :int_t {
    mov r10,rcx
    mov eax,SYS_PERF_EVENT_OPEN
    syscall
    }
sys_recvmmsg proto :int_t, :ptr, :int_t, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_RECVMMSG
    syscall
    }
sys_fanotify_init proto :uint_t, :uint_t {
    mov eax,SYS_FANOTIFY_INIT
    syscall
    }
sys_fanotify_mark proto :int_t, :int_t, :uint64_t, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_FANOTIFY_MARK
    syscall
    }
sys_prlimit64 proto :int_t, :int_t, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_PRLIMIT64
    syscall
    }
sys_name_to_handle_at proto :int_t, :ptr, :ptr, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_NAME_TO_HANDLE_AT
    syscall
    }
sys_open_by_handle_at proto :int_t, :ptr, :int_t {
    mov eax,SYS_OPEN_BY_HANDLE_AT
    syscall
    }
sys_clock_adjtime proto :int_t, :ptr {
    mov eax,SYS_CLOCK_ADJTIME
    syscall
    }
sys_syncfs proto :int_t {
    mov eax,SYS_SYNCFS
    syscall
    }
sys_sendmmsg proto :int_t, :ptr, :int_t, :int_t {
    mov r10,rcx
    mov eax,SYS_SENDMMSG
    syscall
    }
sys_setns proto :int_t, :int_t {
    mov eax,SYS_SETNS
    syscall
    }
sys_getcpu proto :ptr, :ptr, :ptr {
    mov eax,SYS_GETCPU
    syscall
    }
sys_process_vm_readv proto :int_t, :ptr, :ptr, :int64_t, :int64_t {
    mov r10,rcx
    mov eax,SYS_PROCESS_VM_READV
    syscall
    }
sys_process_vm_writev proto :int_t, :ptr, :ulong_t, :ptr, :ulong_t, :ulong_t {
    mov r10,rcx
    mov eax,SYS_PROCESS_VM_WRITEV
    syscall
    }
sys_kcmp proto :int_t, :int_t, :int_t, :ulong_t, :ulong_t {
    mov r10,rcx
    mov eax,SYS_KCMP
    syscall
    }
sys_finit_module proto :int_t, :ptr, :int_t {
    mov eax,SYS_FINIT_MODULE
    syscall
    }
sys_sched_setattr proto :int_t, :ptr, :int_t {
    mov eax,SYS_SCHED_SETATTR
    syscall
    }
sys_sched_getattr proto :int_t, :ptr, :int_t, :int_t {
    mov r10,rcx
    mov eax,SYS_SCHED_GETATTR
    syscall
    }
sys_renameat2 proto :int_t, :ptr, :int_t, :ptr, :uint_t {
    mov r10,rcx
    mov eax,SYS_RENAMEAT2
    syscall
    }
sys_seccomp proto :uint_t, :uint_t, :ptr {
    mov eax,SYS_SECCOMP
    syscall
    }
sys_getrandom proto :ptr, :size_t, :uint_t {
    mov eax,SYS_GETRANDOM
    syscall
    }
sys_memfd_create proto :ptr, :uint_t {
    mov eax,SYS_MEMFD_CREATE
    syscall
    }
sys_kexec_file_load proto :int_t, :int_t, :ulong_t, :ptr, :ulong_t {
    mov r10,rcx
    mov eax,SYS_KEXEC_FILE_LOAD
    syscall
    }
sys_bpf proto :int_t, :ptr, :size_t {
    mov eax,SYS_BPF
    syscall
    }
sys_execveat proto :int_t, :ptr, :ptr, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_EXECVAT
    syscall
    }
sys_userfaultfd proto :int_t {
    mov eax,SYS_USERFAULTFD
    syscall
    }
sys_membarrier proto :int_t, :int_t, :int_t {
    mov eax,SYS_MEMBARRIER
    syscall
    }
sys_mlock2 proto :ulong_t, :size_t, :int_t {
    mov eax,SYS_MLOCK2
    syscall
    }
sys_copy_file_range proto :int_t, :ptr, :uint64_t, :ptr, :size_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_COPY_FILE_RANGE
    syscall
    }
sys_preadv2 proto :ulong_t, :ptr, :ulong_t, :ulong_t, :ulong_t, :int_t {
    mov r10,rcx
    mov eax,SYS_PREADV2
    syscall
    }
sys_pwritev2 proto :ulong_t, :ptr, :ulong_t, :ulong_t, :ulong_t, :int_t {
    mov r10,rcx
    mov eax,SYS_PWRITEV2
    syscall
    }
sys_pkey_mprotect proto :ulong_t, :size_t, :ulong_t, :int_t {
    mov r10,rcx
    mov eax,SYS_PKEY_MPROTECT
    syscall
    }
sys_pkey_alloc proto :ulong_t, :ulong_t {
    mov eax,SYS_PKEY_ALLOC
    syscall
    }
sys_pkey_free proto :int_t {
    mov eax,SYS_PKEY_FREE
    syscall
    }
sys_statx proto :int_t, :ptr, :uint_t, :uint_t, :ptr {
    mov r10,rcx
    mov eax,SYS_STATX
    syscall
    }
sys_io_pgetevents proto :int_t, :long_t, :long_t, :ptr, :ptr, :ptr {
    mov r10,rcx
    mov eax,SYS_IO_PGETEVENTS
    syscall
    }
sys_rseq proto :ptr, :uint_t, :int_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_RSEQ
    syscall
    }
sys_pidfd_send_signal proto :int_t, :int_t, :ptr, :uint_t {
    mov r10,rcx
    mov eax,SYS_PIDFD_SEND_SIGNAL
    syscall
    }
sys_io_uring_setup proto :uint_t, :ptr {
    mov eax,SYS_IO_URING_SETUP
    syscall
    }
sys_io_uring_enter proto :uint_t, :uint_t, :uint_t, :uint_t, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_IO_URING_ENTER
    syscall
    }
sys_io_uring_register proto :uint_t, :uint_t, :ptr, :uint_t {
    mov r10,rcx
    mov eax,SYS_IO_URING_REGISTER
    syscall
    }
sys_open_tree proto :int_t, :ptr, :uint_t {
    mov eax,SYS_OPEN_TREE
    syscall
    }
sys_move_mount proto :int_t, :ptr, :int_t, :ptr, :uint_t {
    mov r10,rcx
    mov eax,SYS_MOVE_MOUNT
    syscall
    }
sys_fsopen proto :ptr, :int_t {
    mov eax,SYS_FSOPEN
    syscall
    }
sys_fsconfig proto :int_t, :uint_t, :ptr, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_FSCONFIG
    syscall
    }
sys_fsmount proto :int_t, :uint_t, :uint_t {
    mov eax,SYS_FSMOUNT
    syscall
    }
sys_fspick proto :int_t, :ptr, :uint_t {
    mov eax,SYS_FSPICK
    syscall
    }
sys_pidfd_open proto :int_t, :uint_t {
    mov eax,SYS_PIDFD_OPEN
    syscall
    }
sys_clone3 proto :ptr, :size_t {
    mov eax,SYS_CLONE3
    syscall
    }
sys_close_range proto :uint_t, :uint_t, :uint_t {
    mov eax,SYS_CLOSE_RANGE
    syscall
    }
sys_openat2 proto :int_t, :ptr, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_OPENAT2
    syscall
    }
sys_pidfd_getfd proto :int_t, :int_t, :uint_t {
    mov eax,SYS_PIDFD_GETFD
    syscall
    }
sys_faccessat2 proto :int_t, :ptr, :int_t, :int_t {
    mov r10,rcx
    mov eax,SYS_FACCESSAT2
    syscall
    }
sys_process_madvise proto :int_t, :ptr, :size_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_PROCESS_MADVICE
    syscall
    }
sys_epoll_pwait2 proto :int_t, :ptr, :int_t, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_EPOLL_PWAIT2
    syscall
    }
sys_mount_setattr proto :int_t, :ptr, :uint_t, :ptr, :size_t {
    mov r10,rcx
    mov eax,SYS_MOUNT_SETATTR
    syscall
    }
sys_quotactl_fd proto :uint_t, :uint_t, :int_t, :ptr {
    mov r10,rcx
    mov eax,SYS_QUOTACTL_FD
    syscall
    }
sys_landlock_create_ruleset proto :ptr, :size_t, :uint_t {
    mov eax,SYS_LANDLOCK_CREATE_RULESET
    syscall
    }
sys_landlock_add_rule proto :int_t, :int_t, :ptr, :uint_t {
    mov r10,rcx
    mov eax,SYS_LANDLOCK_ADD_RULE
    syscall
    }
sys_landlock_restrict_self proto :int_t, :uint_t {
    mov eax,SYS_LANDLOCK_RESTRICT_SELF
    syscall
    }
sys_memfd_secret proto :uint_t {
    mov eax,SYS_MEMFD_SECRET
    syscall
    }
sys_process_mrelease proto :int_t, :uint_t {
    mov eax,SYS_PROCESS_MRELEASE
    syscall
    }
sys_futex_waitv proto :ptr, :uint_t, :uint_t, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_FUTEX_WAITV
    syscall
    }
sys_set_mempolicy_home_node proto :ulong_t, :ulong_t, :ulong_t, :ulong_t {
    mov r10,rcx
    mov eax,SYS_SET_MEMPOLICY_HOME_NODE
    syscall
    }
sys_cachestat proto :uint_t, :ptr, :ptr, :uint_t {
    mov r10,rcx
    mov eax,SYS_CACHESTAT
    syscall
    }
sys_fchmodat2 proto :int_t, :ptr, :int_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_FCHMODAT2
    syscall
    }
sys_map_shadow_stack proto :ulong_t, :ulong_t, :uint_t {
    mov eax,SYS_MAP_SHADOW_STACK
    syscall
    }
sys_futex_wake proto :ptr, :ulong_t, :int_t, :uint_t {
    mov r10,rcx
    mov eax,SYS_FUTEX_WAKE
    syscall
    }
sys_futex_wait proto :ptr, :ulong_t, :ulong_t, :uint_t, :ptr, :int_t {
    mov r10,rcx
    mov eax,SYS_FUTEX_WAIT
    syscall
    }
sys_futex_requeue proto :ptr, :uint_t, :int_t, :int_t {
    mov r10,rcx
    mov eax,SYS_FUTEX_REQUEUE
    syscall
    }

else

.template mmap_arg_struct
    m_addr   dd ? ; Address where pages will be mapped (0)
    m_len    dd ?
    m_prot   dd ? ; PROT_EXEC, PROT_READ, PROT_WRITE
    m_flags  dd ?
    m_fd     dd ?
    m_offset dd ? ; ignored if MAP_ANON
   .ends

sys_call macro id, _1, _2, _3, _4, _5, _6
ifnb <_6>
    push    ebp
endif
ifnb <_5>
    push    edi
endif
ifnb <_4>
    push    esi
endif
ifnb <_1>
    push    ebx
endif
ifnb <_5>
ifdif <_5>,<edi>
    mov     edi,_5
endif
endif
ifnb <_4>
ifdif <_4>,<esi>
    mov     esi,_4
endif
endif
ifnb <_6>
ifdif <_6>,<ebp>
    mov     ebp,_6
endif
endif
ifnb <_1>
ifdif <_1>,<ebx>
    mov     ebx,_1
endif
endif
ifnb <_2>
ifdif <_2>,<ecx>
    mov     ecx,_2
endif
endif
ifnb <_3>
ifdif <_3>,<edx>
    mov     edx,_3
endif
endif
    mov     eax,id
    int     0x80
ifnb <_1>
    pop     ebx
endif
ifnb <_4>
    pop     esi
endif
ifnb <_5>
    pop     edi
endif
ifnb <_6>
    pop     ebp
endif
    retm   <eax>
    endm

sys_restart_syscall proto fastcall {
    sys_call(SYS_RESTART_SYSCALL)
    }
sys_exit proto fastcall :int_t {
    sys_call(SYS_EXIT, _1)
    }
sys_fork proto fastcall {
    sys_call(SYS_FORK)
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
sys_waitpid proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_WAITPID, _1, _2, _3)
    }
sys_link proto fastcall :string_t, :string_t {
    sys_call(SYS_LINK, _1, _2)
    }
sys_unlink proto fastcall :string_t {
    sys_call(SYS_UNLINK, _1)
    }
sys_execve proto fastcall :string_t, :array_t, :abs {
    sys_call(SYS_EXECVE, _1, _2, _3)
    }
sys_chdir proto fastcall :string_t {
    sys_call(SYS_CHDIR, _1)
    }
sys_time proto fastcall :ptr {
    sys_call(SYS_TIME, _1)
    }
sys_mknod proto fastcall :ptr, :int_t, :abs {
    sys_call(SYS_MKNOD, _1, _2, _3)
    }
sys_chmod proto fastcall :string_t, :int_t {
    sys_call(SYS_CHMOD, _1, _2)
    }
sys_lchown proto fastcall :string_t, :uint_t, :abs {
    sys_call(SYS_LCHOWN, _1, _2, _3)
    }
sys_lseek proto fastcall :int_t, :size_t, :abs {
    sys_call(SYS_LSEEK, _1, _2, _3)
    }
sys_getpid proto fastcall {
    sys_call(SYS_GETPID)
    }
sys_mount proto fastcall :ptr, :ptr, :abs, :abs, :abs {
    sys_call(SYS_MOUNT, _1, _2, _3, _4, _5)
    }
sys_umount proto fastcall :ptr, :int_t {
    sys_call(SYS_UMONT, _1, _2)
    }
sys_setuid proto fastcall :int_t {
    sys_call(SYS_SETUID, _1)
    }
sys_getuid proto fastcall {
    sys_call(SYS_GETUID)
    }
sys_ptrace proto fastcall :long_t, :long_t, :abs, :abs {
    sys_call(SYS_PTRACE, _1, _2, _3, _4)
    }
sys_alarm proto fastcall :uint_t {
    sys_call(SYS_ALARM, _1)
    }
sys_pause proto fastcall {
    sys_call(SYS_PAUSE)
    }
sys_utime proto fastcall :string_t, :ptr {
    sys_call(SYS_UTIME, _1, _2)
    }
sys_access proto fastcall :string_t, :int_t {
    sys_call(SYS_ACCESS, _1, _2)
    }
sys_sync proto fastcall {
    sys_call(SYS_SYNC)
    }
sys_kill proto fastcall :int_t, :int_t {
    sys_call(SYS_KILL, _1, _2)
    }
sys_rename proto fastcall :string_t, :string_t {
    sys_call(SYS_RENAME, _1, _2)
    }
sys_mkdir proto fastcall :string_t, :int_t {
    sys_call(SYS_MKDIR, _1, _2)
    }
sys_rmdir proto fastcall :string_t {
    sys_call(SYS_RMDIR, _1)
    }
sys_dup proto fastcall :int_t {
    sys_call(SYS_DUP, _1)
    }
sys_pipe proto fastcall :ptr int_t {
    sys_call(SYS_PIPE, _1)
    }
sys_times proto fastcall :ptr {
    sys_call(SYS_TIMES, _1)
    }
sys_brk proto fastcall :ptr {
    sys_call(SYS_BRK, _1)
    }
sys_setgid proto fastcall :int_t {
    sys_call(SYS_SETGID, _1)
    }
sys_getgid proto fastcall {
    sys_call(SYS_GETGID)
    }
sys_geteuid proto fastcall {
    sys_call(SYS_GETEUID)
    }
sys_getegid proto fastcall {
    sys_call(SYS_GETEGID)
    }
sys_acct proto fastcall :string_t {
    sys_call(SYS_ACCT, _1)
    }
sys_ioctl proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_IOCTL, _1, _2, _3)
    }
sys_fcntl proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_FCNTL, _1, _2, _3)
    }
sys_setpgid proto fastcall :int_t, :int_t {
    sys_call(SYS_SETPGID, _1, _2)
    }
sys_umask proto fastcall :int_t {
    sys_call(SYS_UMASK, _1)
    }
sys_chroot proto fastcall :string_t {
    sys_call(SYS_CHROOT, _1)
    }
sys_ustat proto fastcall :uint_t, :ptr {
    sys_call(SYS_USTAT, _1, _2)
    }
sys_dup2 proto fastcall :int_t, :int_t {
    sys_call(SYS_DUP2, _1, _2)
    }
sys_getppid proto fastcall {
    sys_call(SYS_GETPPID)
    }
sys_getpgrp proto fastcall {
    sys_call(SYS_GETPGRP)
    }
sys_setsid proto fastcall {
    sys_call(SYS_SETSID)
    }
sys_setreuid proto fastcall :int_t, :int_t {
    sys_call(SYS_SETREUID, _1, _2)
    }
sys_setregid proto fastcall :int_t, :int_t {
    sys_call(SYS_SETREGID, _1, _2)
    }
sys_sethostname proto fastcall :ptr, :int_t {
    sys_call(SYS_SETHOSTNAME, _1, _2)
    }
sys_getrlimit proto fastcall :uint_t, :ptr {
    sys_call(SYS_GETRLIMIT, _1, _2)
    }
sys_setrlimit proto fastcall :uint_t, :ptr {
    sys_call(SYS_SETRLIMIT, _1, _2)
    }
sys_getrusage proto fastcall :int_t, :ptr {
    sys_call(SYS_GETRUSAGE, _1, _2)
    }
sys_gettimeofday proto fastcall :ptr, :ptr {
    sys_call(SYS_GETTIMEOFDAY, _1, _2)
    }
sys_settimeofday proto fastcall :ptr, :ptr {
    sys_call(SYS_SETTIMEOFDAY, _1, _2)
    }
sys_getgroups proto fastcall :int_t, :ptr {
    sys_call(SYS_GETGROUPS, _1, _2)
    }
sys_setgroups proto fastcall :int_t, :ptr {
    sys_call(SYS_SETGROUPS, _1, _2)
    }
sys_select proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_SELECT, _1, _2, _3, _4, _5)
    }
sys_symlink proto fastcall :string_t, :string_t {
    sys_call(SYS_SYMLINK, _1, _2)
    }
sys_readlink proto fastcall :string_t, :string_t, :abs {
    sys_call(SYS_READLINK, _1, _2, _3)
    }
sys_uselib proto fastcall {
    sys_call(SYS_USELIB)
    }
sys_swapon proto fastcall :ptr, :int_t {
    sys_call(SYS_SWAPON, _1, _2)
    }
sys_reboot proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_REBOOT, _1, _2, _3, _4)
    }
sys_mmap proto fastcall :ptr, :size_t, :abs, :abs, :abs, :abs {
   .new mmap:mmap_arg_struct
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
sys_truncate proto fastcall :ptr, :int_t {
    sys_call(SYS_TRUNCATE, _1, _2)
    }
sys_ftruncate proto fastcall :uint_t, :int_t {
    sys_call(SYS_FTRUNCATE, _1, _2)
    }
sys_fchmod proto fastcall :int_t, :int_t {
    sys_call(SYS_FCHMOD, _1, _2)
    }
sys_fchown proto fastcall :int_t, :uint_t, :abs {
    sys_call(SYS_FCHOWN, _1, _2, _3)
    }
sys_getpriority proto fastcall :int_t, :int_t {
    sys_call(SYS_GETPRIORITY, _1, _2)
    }
sys_setpriority proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_SETPRIORITY, _1, _2, _3)
    }
sys_statfs proto fastcall :ptr, :ptr {
    sys_call(SYS_STATFS, _1, _2)
    }
sys_fstatfs proto fastcall :uint_t, :ptr {
    sys_call(SYS_FSTATFS, _1, _2)
    }
sys_ioperm proto fastcall :uint_t, :uint_t, :abs {
    sys_call(SYS_IOPERM, _1, _2, _3)
    }
sys_syslog proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_SYSLOG, _1, _2, _3)
    }
sys_setitimer proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_SETITIMER, _1, _2, _3)
    }
sys_getitimer proto fastcall :int_t, :ptr {
    sys_call(SYS_GETITIMER, _1, _2)
    }
sys_newstat proto fastcall :string_t, :ptr {
    sys_call(SYS_STAT, _1, _2)
    }
sys_newlstat proto fastcall :string_t, :ptr {
    sys_call(SYS_LSTAT, _1, _2)
    }
sys_newfstat proto fastcall :int_t, :ptr {
    sys_call(SYS_FSTAT, _1, _2)
    }
sys_iopl proto fastcall :int_t {
    sys_call(SYS_IOPL, _1)
    }
sys_vhangup proto fastcall {
    sys_call(SYS_VHANGUP)
    }
sys_wait4 proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_WAIT4, _1, _2, _3, _4)
    }
sys_swapoff proto fastcall :ptr {
    sys_call(SYS_SWAPOFF, _1)
    }
sys_sysinfo proto fastcall :ptr {
    sys_call(SYS_SYSINFO, _1)
    }
sys_fsync proto fastcall :int_t {
    sys_call(SYS_FSYNC, _1)
    }
sys_clone proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_CLONE, _1, _2, _3, _4, _5)
    }
sys_setdomainname proto fastcall :ptr, :int_t {
    sys_call(SYS_SETDOMAINNAME, _1, _2)
    }
sys_newuname proto fastcall :ptr {
    sys_call(SYS_UNAME, _1)
    }
sys_modify_ldt proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_MODIFY_LDT, _1, _2, _3)
    }
sys_adjtimex proto fastcall :ptr {
    sys_call(SYS_ADJTIMEX, _1)
    }
sys_mprotect proto fastcall :ptr, :size_t, :abs {
    sys_call(SYS_MPROTECT, _1, _2, _3)
    }
sys_init_module proto fastcall :ptr, :uint_t, :abs {
    sys_call(SYS_INIT_MODULE, _1, _2, _3)
    }
sys_delete_module proto fastcall :ptr, :uint_t {
    sys_call(SYS_DELETE_MODULE, _1, _2)
    }
sys_quotactl proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_QUOTACTL, _1, _2, _3, _4)
    }
sys_getpgid proto fastcall :int_t {
    sys_call(SYS_GETPGID, _1)
    }
sys_fchdir proto fastcall :int_t {
    sys_call(SYS_FCHDIR, _1)
    }
sys_sysfs proto fastcall :int_t, :uint_t, :abs {
    sys_call(SYS_SYSFS, _1, _2, _3)
    }
sys_personality proto fastcall :uint_t {
    sys_call(SYS_PERSONALITY, _1)
    }
sys_setfsuid proto fastcall :int_t {
    sys_call(SYS_SETFSUID, _1)
    }
sys_setfsgid proto fastcall :int_t {
    sys_call(SYS_SETFSGID, _1)
    }
sys_llseek proto fastcall :int_t, :uint_t, :abs, :abs, :abs {
    sys_call(SYS_LLSEEK, _1, _2, _3, _4, _5)
    }
sys_getdents proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_GETDENTS, _1, _2)
    }
sys_flock proto fastcall :uint_t, :uint_t {
    sys_call(SYS_FLOCK, _1, _2)
    }
sys_msync proto fastcall :ptr, :size_t, :abs {
    sys_call(SYS_MSYNC, _1, _2, _3)
    }
sys_readv proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_READV, _1, _2, _3)
    }
sys_writev proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_WRITEV, _1, _2, _3)
    }
sys_getsid proto fastcall :int_t {
    sys_call(SYS_GETSID, _1)
    }
sys_fdatasync proto fastcall :int_t {
    sys_call(SYS_FDATASYNC, _1)
    }
sys_mlock proto fastcall :ptr, :size_t {
    sys_call(SYS_MLOCK, _1, _2)
    }
sys_munlock proto fastcall :ptr, :size_t {
    sys_call(SYS_MUNLOCK, _1, _2)
    }
sys_mlockall proto fastcall :int_t {
    sys_call(SYS_MLOCKALL, _1)
    }
sys_munlockall proto fastcall {
    sys_call(SYS_MUNLOCKALL)
    }
sys_sched_setparam proto fastcall :int_t, :ptr {
    sys_call(SYS_SCHED_SETPARAM, _1, _2)
    }
sys_sched_getparam proto fastcall :int_t, :ptr {
    sys_call(SYS_SCHED_GETPARAM, _1, _2)
    }
sys_sched_setscheduler proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_SCHED_SETSCHEDULER, _1, _2, _3)
    }
sys_sched_getscheduler proto fastcall :int_t {
    sys_call(SYS_SCHED_GETSCHEDULER, _1)
    }
sys_sched_get_priority_max proto fastcall :int_t {
    sys_call(SYS_SCHED_GET_PRIORITY_MAX, _1)
    }
sys_sched_get_priority_min proto fastcall :int_t {
    sys_call(SYS_SCHED_GET_PRIORITY_MIN, _1)
    }
sys_sched_rr_get_interval proto fastcall :int_t, :ptr {
    sys_call(SYS_SCHED_RR_GET_INTERVAL, _1, _2)
    }
sys_nanosleep proto fastcall :ptr, :ptr {
    sys_call(SYS_NANOSLEEP, _1, _2)
    }
sys_mremap proto fastcall :ptr, :size_t, :abs, :abs, :abs {
    sys_call(SYS_MREMAP, _1, _2, _3, _4, _5)
    }
sys_setresuid proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_SETRESUID, _1, _2, _3)
    }
sys_getresuid proto fastcall :ptr, :ptr, :abs {
    sys_call(SYS_GETRESUID, _1, _2, _3)
    }
sys_poll proto fastcall :ptr, :uint_t, :abs {
    sys_call(SYS_POLL, _1, _2, _3)
    }
sys_setresgid proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_SETRESGID, _1, _2, _3)
    }
sys_getresgid proto fastcall :ptr, :ptr, :abs {
    sys_call(SYS_GETRESGID, _1, _2, _3)
    }
sys_prctl proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_PRCTL, _1, _2, _3, _4, _5)
    }
sys_rt_sigreturn proto fastcall {
    sys_call(SYS_RT_SIGRETURN)
    }
sys_rt_sigaction proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_RT_SIGACTION, _1, _2, _3, _4)
    }
sys_rt_sigprocmask proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_RT_SIGPROCMASK, _1, _2, _3, _4)
    }
sys_rt_sigpending proto fastcall :ptr, :size_t {
    sys_call(SYS_RT_SIGPENDING, _1, _2)
    }
sys_rt_sigtimedwait proto fastcall :ptr, :ptr, :abs, :abs {
    sys_call(SYS_RT_SIGTIMEDWAIT, _1, _2, _3, _4)
    }
sys_rt_sigqueueinfo proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_RT_SIGQUEUEINFO, _1, _2, _3)
    }
sys_rt_sigsuspend proto fastcall :ptr, :size_t {
    sys_call(SYS_RT_SIGSUSPEND, _1, _2)
    }
sys_pread64 proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_PREAD64, _1, _2, _3, _4, _5)
    }
sys_pwrite64 proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_PWRITE64, _1, _2, _3, _4, _5)
    }
sys_chown proto fastcall :string_t, :uint_t, :abs {
    sys_call(SYS_CHOWN, _1, _2, _3)
    }
sys_getcwd proto fastcall :string_t, :int_t {
    sys_call(SYS_GETCWD, _1, _2)
    }
sys_capget proto fastcall :ptr, :ptr {
    sys_call(SYS_CAPGET, _1, _2)
    }
sys_capset proto fastcall :ptr, :ptr {
    sys_call(SYS_CAPSET, _1, _2)
    }
sys_sigaltstack proto fastcall :ptr, :ptr {
    sys_call(SYS_SIGALTSTACK, _1, _2)
    }
sys_sendfile64 proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_SENDFILE, _1, _2, _3, _4)
    }
sys_vfork proto fastcall {
    sys_call(SYS_VFORK)
    }
sys_newstat64 proto fastcall :string_t, :ptr {
    sys_call(SYS_STAT64, _1, _2)
    }
sys_newlstat64 proto fastcall :string_t, :ptr {
    sys_call(SYS_LSTAT64, _1, _2)
    }
sys_newfstat64 proto fastcall :int_t, :ptr {
    sys_call(SYS_FSTAT64, _1, _2)
    }
sys_pivot_root proto fastcall :ptr, :ptr {
    sys_call(SYS_PIVOT_ROOT, _1, _2)
    }
sys_mincore proto fastcall :ptr, :size_t, :abs {
    sys_call(SYS_MINCORE, _1, _2, _3)
    }
sys_madvise proto fastcall :ptr, :size_t, :abs {
    sys_call(SYS_MADVISE, _1, _2, _3)
    }
sys_getdents64 proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_GETDENTS64, _1, _2)
    }
sys_gettid proto fastcall {
    sys_call(SYS_GETTID)
    }
sys_readahead proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_READAHEAD, _1, _2, _3)
    }
sys_setxattr proto fastcall :ptr, :ptr, :abs, :abs {
    sys_call(SYS_SETXATTR, _1, _2, _3, _4)
    }
sys_lsetxattr proto fastcall :ptr, :ptr, :abs, :abs, :abs {
    sys_call(SYS_LSETXATTR, _1, _2, _3, _4, _5)
    }
sys_fsetxattr proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_FSETXATTR, _1, _2, _3, _4, _5)
    }
sys_getxattr proto fastcall :ptr, :ptr, :abs, :abs {
    sys_call(SYS_GETXATTR, _1, _2, _3, _4)
    }
sys_lgetxattr proto fastcall :ptr, :ptr, :abs, :abs {
    sys_call(SYS_LGETXATTR, _1, _2, _3, _4)
    }
sys_fgetxattr proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_FGETXATTR, _1, _2, _3, _4)
    }
sys_listxattr proto fastcall :ptr, :ptr, :abs {
    sys_call(SYS_LISTXATTR, _1, _2, _3)
    }
sys_llistxattr proto fastcall :ptr, :ptr, :abs {
    sys_call(SYS_LLISTXATTR, _1, _2, _3)
    }
sys_flistxattr proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_FLISTXATTR, _1, _2, _3)
    }
sys_removexattr proto fastcall :ptr, :ptr {
    sys_call(SYS_REMOVEXATTR, _1, _2)
    }
sys_lremovexattr proto fastcall :ptr, :ptr {
    sys_call(SYS_LREMOVEXATTR, _1, _2)
    }
sys_fremovexattr proto fastcall :int_t, :ptr {
    sys_call(SYS_FREMOVEXATTR, _1, _2)
    }
sys_tkill proto fastcall :int_t, :int_t {
    sys_call(SYS_TKILL, _1, _2)
    }
sys_futex proto fastcall :ptr, :int_t, :abs, :abs, :abs, :abs {
    sys_call(SYS_FUTEX, _1, _2, _3, _4, _5, _6)
    }
sys_sched_getaffinity proto fastcall :int_t, :uint_t, :abs {
    sys_call(SYS_SCHED_GETAFFINITY, _1, _2, _3)
    }
sys_io_setup proto fastcall :uint_t, :ptr {
    sys_call(SYS_IO_SETUP, _1, _2)
    }
sys_io_destroy proto fastcall :ptr {
    sys_call(SYS_IO_DESTROY, _1)
    }
sys_io_getevents proto fastcall :ptr, :long_t, :abs, :abs, :abs {
    sys_call(SYS_IO_GETEVENTS, _1, _2, _3, _4, _5)
    }
sys_io_submit proto fastcall :ptr, :long_t, :abs {
    sys_call(SYS_IO_SUBMIT, _1, _2, _3)
    }
sys_io_cancel proto fastcall :ptr, :ptr, :abs {
    sys_call(SYS_IO_CANCEL, _1, _2, _3)
    }
sys_fadvise64 proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_FADVISE64, _1, _2, _3, _4)
    }
sys_exit_group proto fastcall :int_t {
    sys_call(SYS_EXIT_GROUP, _1)
    }
sys_epoll_create proto fastcall :int_t {
    sys_call(SYS_EPOLL_CREATE, _1)
    }
sys_epoll_ctl proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_EPOLL_CTL, _1, _2, _3, _4)
    }
sys_epoll_wait proto fastcall :int_t, :ptr, :abs, :abs  {
    sys_call(SYS_EPOLL_WAIT, _1, _2, _3, _4)
    }
sys_remap_file_pages proto fastcall :ulong_t, :ulong_t, :abs, :abs, :abs {
    sys_call(SYS_REMAP_FILE_PAGES, _1, _2, _3, _4, _5)
    }
sys_set_tid_address proto fastcall :ptr {
    sys_call(SYS_SET_TID_ADDRESS, _1)
    }
sys_timer_create proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_TIMER_CREATE, _1, _2, _3)
    }
sys_timer_settime proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_TIMER_SETTIME, _1, _2, _3, _4)
    }
sys_timer_gettime proto fastcall :int_t, :ptr {
    sys_call(SYS_TIMER_GETTIME, _1, _2)
    }
sys_timer_getoverrun proto fastcall :int_t {
    sys_call(SYS_TIMER_GETOVERRUN, _1)
    }
sys_timer_delete proto fastcall :int_t {
    sys_call(SYS_TIMER_DELETE, _1)
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
sys_tgkill proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_TGKILL, _1, _2, _3)
    }
sys_utimes proto fastcall :ptr, :ptr {
    sys_call(SYS_UTIMES, _1, _2)
    }
sys_mbind proto fastcall :ulong_t, :ulong_t, :abs, :abs, :abs, :abs {
    sys_call(SYS_MBIND, _1, _2, _3, _4, _5, _6)
    }
sys_set_mempolicy proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_SET_MEMPOLICY, _1, _2, _3)
    }
sys_get_mempolicy proto fastcall :ptr, :ulong_t, :abs, :abs {
    sys_call(SYS_GET_MEMPOLICY, _1, _2, _3, _4)
    }
sys_mq_open proto fastcall :ptr, :int_t, :abs, :abs {
    sys_call(SYS_MQ_OPEN, _1, _2, _3, _4)
    }
sys_mq_unlink proto fastcall :ptr {
    sys_call(SYS_MQ_UNLINK, _1)
    }
sys_mq_timedsend proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_MQ_TIMEDSEND, _1, _2, _3, _4, _5)
    }
sys_mq_timedreceive proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_MQ_TIMEDRECEIVE, _1, _2, _3, _4, _5)
    }
sys_mq_notify proto fastcall :int_t, :ptr {
    sys_call(SYS_MQ_NOTIFY, _1, _2)
    }
sys_mq_getsetattr proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_MQ_GETSETATTR, _1, _2, _3)
    }
sys_kexec_load proto fastcall :ulong_t, :ulong_t, :abs, :abs {
    sys_call(SYS_KEXEC_LOAD, _1, _2, _3, _4)
    }
sys_waitid proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_WAITID, _1, _2, _3, _4, _5)
    }
sys_add_key proto fastcall :ptr, :ptr, :abs, :abs, :abs {
    sys_call(SYS_ADD_KEY, _1, _2, _3, _4, _5)
    }
sys_request_key proto fastcall :ptr, :ptr, :abs, :abs {
    sys_call(SYS_REQUEST_KEY, _1, _2, _3, _4)
    }
sys_keyctl proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_KEYCTL, _1, _2, _3, _4, _5)
    }
sys_ioprio_set proto fastcall :int_t, :int_t, :abs {
    sys_call(SYS_IOPRIO_SET, _1, _2, _3)
    }
sys_ioprio_get proto fastcall :int_t, :int_t {
    sys_call(SYS_IOPRIO_GET, _1, _2)
    }
sys_inotify_init proto fastcall {
    sys_call(SYS_INOTIFY_INIT)
    }
sys_inotify_add_watch proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_INOTIFY_ADD_WATCH, _1, _2, _3)
    }
sys_inotify_rm_watch proto fastcall :int_t, :int_t {
    sys_call(SYS_INOTIFY_RM_WATCH, _1, _2)
    }
sys_migrate_pages proto fastcall :int_t, :uint_t, :abs, :abs {
    sys_call(SYS_MIGRATE_PAGES, _1, _2, _3, _4)
    }
sys_openat proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_OPENAT, _1, _2, _3, _4)
    }
sys_mkdirat proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_MKDIRAT, _1, _2, _3)
    }
sys_mknodat proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_MKNODAT, _1, _2, _3)
    }
sys_fchownat proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_FCHOWNAT, _1, _2, _3, _4)
    }
sys_futimesat proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_FUTIMESAT, _1, _2, _3, _4, _5)
    }
sys_newfstatat proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_NEWFSTATAT, _1, _2, _3)
    }
sys_unlinkat proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_UNLINKAT, _1, _2, _3)
    }
sys_renameat proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_RENAMEAT, _1, _2, _3, _4)
    }
sys_linkat proto fastcall :int_t, :ptr, :abs, :abs, :abs {
    sys_call(SYS_LINKAT, _1, _2, _3, _4, _5)
    }
sys_symlinkat proto fastcall :ptr, :int_t, :abs {
    sys_call(SYS_SYMLINKAT, _1, _2, _3)
    }
sys_readlinkat proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_READLINKAT, _1, _2, _3, _4)
    }
sys_fchmodat proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_FCHMODAT, _1, _2, _3)
    }
sys_faccessat proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_FACCESSAT, _1, _2, _3)
    }
sys_pselect6 proto fastcall :int_t, :ptr, :abs, :abs, :abs, :abs {
    sys_call(SYS_PSELECT6, _1, _2, _3, _4, _5, _6)
    }
sys_ppoll proto fastcall :ptr, :uint_t, :abs, :abs, :abs {
    sys_call(SYS_PPOLL, _1, _2, _3, _4, _5)
    }
sys_unshare proto fastcall :uint_t {
    sys_call(SYS_UNSHARE, _1)
    }
sys_set_robust_list proto fastcall :ptr, :size_t {
    sys_call(SYS_SET_ROBUST_LIST, _1, _2)
    }
sys_get_robust_list proto fastcall :int_t, :ptr, :abs {
    sys_call(SYS_GET_ROBUST_LIST, _1, _2, _3)
    }
sys_splice proto fastcall :int_t, :ptr, :abs, :abs, :abs, :abs {
    sys_call(SYS_SPLICE, _1, _2, _3, _4, _5, _6)
    }
sys_tee proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_TEE, _1, _2, _3, _4)
    }
sys_sync_file_range proto fastcall :int_t, :int_t, :abs, :abs {
    sys_call(SYS_SYNC_FILE_RANGE, _1, _2, _3, _4)
    }
sys_vmsplice proto fastcall :int_t, :ptr, :abs, :abs {
    sys_call(SYS_VMSPLICE, _1, _2, _3, _4)
    }

endif
endif
