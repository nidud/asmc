Asmc Linker Reference

## /HEAP

**/HEAP**:reserve[,commit]

The /HEAP option sets the size of the heap in bytes. This option is only for use when building an .exe file.

The reserve argument specifies the total heap allocation in virtual memory. The default heap size is 1 MB. The linker rounds up the specified value to the nearest 4 bytes.

The optional commit argument specifies the amount of physical memory to allocate at a time. Committed virtual memory causes space to be reserved in the paging file. A higher commit value saves time when the application needs more heap space, but increases the memory requirements and possibly the startup time.

Specify the reserve and commit values in decimal or C-language notation.

#### See Also

[Asmc Linker Reference](link.md)
