Asmc Macro Assembler Reference

## Escape Sequences

Character combinations consisting of a backslash (\) followed by a letter or by a combination of digits are called "escape sequences." To represent a newline character, single quotation mark, or certain other characters in a character constant, you must use escape sequences. An escape sequence is regarded as a single character and is therefore valid as a character constant.

Escape sequences are typically used to specify actions such as carriage returns and tab movements on terminals and printers. They are also used to provide literal representations of nonprinting characters and characters that usually have special meanings, such as the double quotation mark ("). The following table lists the ANSI escape sequences and what they represent.

<table>
<tr><td><b>Escape Sequence</b></td><td><b>Represents</b></td><td><b>Description</b></td></tr>
<tr><td>\a</td><td>Bell (alert)</td><td>Triggers a system beep or alert sound (mostly obsolete on modern systems)</td></tr>
<tr><td>\b</td><td>Backspace</td><td>Moves the cursor back by one position</td></tr>
<tr><td>\f</td><td>Form feed</td><td>Advances to the next page (originally used for printers)</td></tr>
<tr><td>\n</td><td>New line</td><td>Moves the cursor back to the beginning of the current line</td></tr>
<tr><td>\<i>ooo</i></td><td>Octal Escape Sequence</td><td>ASCII character in octal notation</td></tr>
<tr><td>\r</td><td>Carriage return</td><td>Moves the cursor back to the beginning of the current line</td></tr>
<tr><td>\t</td><td>Horizontal tab</td><td>Inserts a standard horizontal tab space for alignment</td></tr>
<tr><td>\u<i>hhhh</i></td><td>Universal Character Names</td><td>Represents a Unicode character using a 16-bit hexadecimal value</td></tr>
<tr><td>\U<i>hhhhhhhh</i></td><td>Universal Character Names</td><td>Represents a Unicode character using a 32-bit hexadecimal value</td></tr>
<tr><td>\v</td><td>Vertical Tab</td><td>Moves the cursor vertically downwards</td></tr>
<tr><td>\x<i>hh</i></td><td>Hexadecimal Escape Sequence</td><td>ASCII character in hexadecimal notation</td></tr>
<tr><td>\x<i>hhhh</i></td><td>Hexadecimal Escape Sequence</td><td>Unicode character in hexadecimal notation if this escape sequence is used in a wide-character constant or a Unicode string literal</td></tr>
<tr><td>\\</td><td>Backslash</td><td>Prints a literal backslash character</td></tr>
<tr><td>\?</td><td>Question Mark</td><td>Used to prevent unintentional interpretation of trigraphs</td></tr>
<tr><td>\0</td><td>Null Character</td><td>Represents the value 0; used to mark the termination of strings</td></tr>
<tr><td>\'</td><td>Single Quote</td><td>Embeds a single quote inside a character literal</td></tr>
<tr><td>\"</td><td>Double Quote</td><td>Embeds a literal double quote inside a string literal</td></tr>
</table>

Escape sequences allow you to send nongraphic control characters to a display device. For example, the ESC character (\\033) is often used as the first character of a control command for a terminal or printer. Some escape sequences are device-specific. For instance, the vertical tab and form feed escape sequences (\\v and \\f) do not affect screen output, but they do perform appropriate printer operations.

You can also use the backslash (\\) as a continuation character. When a newline character (equivalent to pressing the RETURN key) immediately follows the backslash, the assembler ignores the backslash and the newline character and treats the next line as part of the previous line. This is useful primarily for preprocessor definitions longer than a single line.

#### See Also

[Directives Reference](readme.md) | [String Literals](string-literals.md)
