
DZEMM is an Expanded Memory Manager (EMM), and the source is released
under the GNU General Public License. See the LICENSE file for details.

To install the manager, copy the files DZEMM.SYS and DZEMM.DLL
to a directory in your %PATH% (%SystemRoot%\SYSTEM32 preferred).

You need to edit the file CONFIG.NT in %SystemRoot%\SYSTEM32
(or a separate config.nt for a specific shortcut (.pif file))
and add the line (change C: to your Windows drive):

  device=C:\windows\system32\dzemm.sys

The CONFIG.NT file I used for testing in WinXP:

  dos=high, umb
  device=C:\windows\system32\himem.sys
  device=C:\windows\system32\dzemm.sys
  files=40

For more information on the Lotus/Intel/Microsoft (LIM) Expanded Memory
Specification, see: http://www.phatcode.net/res/218/files/limems40.txt
