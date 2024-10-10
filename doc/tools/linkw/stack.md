Asmc Linker Reference

## /STACK

**/STACK**:_reserve_[,_commit_]

The /STACK linker option sets the size of the stack in bytes. Use this option only when you build an .exe file. The /STACK option is ignored when applied to .dll files.

The reserve value specifies the total stack allocation in virtual memory. For x86 and x64 machines, the default stack size is 1 MB.

The _commit_ value is subject to interpretation by the operating system. In WindowsRT, it specifies the amount of physical memory to allocate at a time. Committed virtual memory causes space to be reserved in the paging file. A higher commit value saves time when the application needs more stack space, but increases the memory requirements and possibly the startup time. For x86 and x64 machines, the default commit value is 4 KB.

Specify the reserve and commit values in decimal or C-language hexadecimal notation (use a 0x prefix).

#### See Also

[Asmc Linker Reference](readme.md) | [/HEAP](heap.md)
