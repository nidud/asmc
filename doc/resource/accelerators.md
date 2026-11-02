Asmc Macro Assembler Reference

## ACCELERATORS

Defines one or more accelerators for an application. An accelerator is a keystroke defined by the application to give the user a quick way to perform a task.

syntax:

```
ACCELERATORS {event, idvalue, [type] [options]... }
```

#### Parameters

_event_

Keystroke to be used as an accelerator. It can be any one of the following character types.

<table>
<tr><td><i>"char"</i></td><td>A single character enclosed in double quotation marks ("). The character can be preceded by a caret (^), meaning that the character is a control character.</td></tr>
<tr><td><i>Character</i></td><td>An integer value representing a character. The type parameter must be ASCII.</td></tr>
<tr><td><i>virtual-key character</i></td><td>An integer value representing a virtual key. The virtual key for alphanumeric keys can be specified by placing the uppercase letter or number in double quotation marks (for example, "9" or "C"). The type parameter must be VIRTKEY.</td></tr>
</table>

_idvalue_

a 16-bit unsigned integer value that identifies the accelerator.

_type_

Required only when the _event_ parameter is a _character_ or a _virtual-key character_. The type parameter specifies either ASCII or VIRTKEY; the integer value of _event_ is interpreted accordingly. When VIRTKEY is specified and _event_ contains a string, _event_ must be uppercase.

_options_

options that define the accelerator. This parameter can be one or more of the following values.

<table>
<tr><td>NOINVERT</td><td>Specifies that no top-level menu item is highlighted when the accelerator is used. This is useful when defining accelerators for actions such as scrolling that do not correspond to a menu item. If NOINVERT is omitted, a top-level menu item will be highlighted (if possible) when the accelerator is used. This attribute is obsolete and retained only for backward compatibility with resource files designed for 16-bit Windows.</td></tr>
<tr><td>ALT</td><td>Causes the accelerator to be activated only if the ALT key is down. Applies only to virtual keys.</td></tr>
<tr><td>SHIFT</td><td>Causes the accelerator to be activated only if the SHIFT key is down. Applies only to virtual keys</td></tr>
<tr><td>CONTROL</td><td>Defines the character as a control character (the accelerator is only activated if the CONTROL key is down). This has the same effect as using a caret (^) before the accelerator character in the event parameter. Applies only to virtual keys</td></tr>
</table>


#### Example

```
ACCELERATORS {
  "^C",  1001,                          ; control C
  "K",   1002,                          ; shift K
  "k",   1003, ALT,                     ; alt k
  98,    1004, ASCII,                   ; b
  66,    1005, ASCII,                   ; B (shift b)
  "g",   1006,                          ; g
  "G",   1007,                          ; G (shift G)
  VK_F1, 1008, VIRTKEY,                 ; F1
  VK_F1, 1009, CONTROL, VIRTKEY,        ; control F1
  VK_F1, 1010, SHIFT, VIRTKEY,          ; shift F1
  VK_F1, 1011, ALT, VIRTKEY,            ; alt F1
  VK_F2, 1012, ALT, SHIFT, VIRTKEY,     ; alt shift F2
  VK_F2, 1013, CONTROL, SHIFT, VIRTKEY, ; ctrl shift F2
  VK_F2, 1014, ALT, CONTROL, VIRTKEY    ; alt control F2
  }
```

#### See Also

[Asmc Resource Compiler](readme.md)
