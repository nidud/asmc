Asmc Linker Reference

## /ENTRY

**/ENTRY**:_function_

The /ENTRY option specifies an entry point function as the starting address for an .exe file or DLL.

By default, the starting address is a function name from the C run-time library. The linker selects it according to the attributes of the program, as shown in the following table.

<table>
<tr><td><b>Function name</b></td><td><b>Default for</b></td></tr>
<tr><td>mainCRTStartup (or wmainCRTStartup)</td><td>An application that uses /SUBSYSTEM:CONSOLE; calls main (or wmain)</td></tr>
<tr><td>WinMainCRTStartup (or wWinMainCRTStartup)</td><td>An application that uses /SUBSYSTEM:WINDOWS; calls WinMain (or wWinMain), which must be defined to use WINAPI-call</td></tr>
<tr><td>_DllMainCRTStartup</td><td>A DLL; calls DllMain if it exists, which must be defined to use WINAPI-call</td></tr>
</table>

If the [/DLL](dll.md) or [/SUBSYSTEM](subsystem.md) option is not specified, the linker selects a subsystem and entry point depending on whether main or WinMain is defined.

The functions main, WinMain, and DllMain are the three forms of the user-defined entry point.

#### See Also

[Asmc Linker Reference](readme.md)
