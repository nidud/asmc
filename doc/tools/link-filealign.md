Asmc Linker Reference

## /FILEALIGN

**/FILEALIGN**:_size_

The section alignment _size_ in bytes, which must be a power of two.

The /FILEALIGN option causes the linker to align each section in the output file on a boundary that is a multiple of the size value. By default, the linker does not use a fixed alignment size.

The /FILEALIGN option can be used to make disk utilization more efficient, or to make page loads from disk faster. A smaller section size may be useful for apps that run on smaller devices, or to keep downloads smaller. Section alignment on disk does not affect alignment in memory.

Use DUMPBIN to see information about sections in your output file.

#### See Also

[Asmc Linker Reference](link.md)
