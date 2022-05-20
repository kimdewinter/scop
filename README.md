# Scop
This was a school project which explores how to render things in OpenGL, including manual parsing of .obj files, manual implementation of transformation matrices, camera movement, texture application, etcetera.

Written in C, tested and compatible with macOS 10.14.6 and Ubuntu 21.04<br/>

## Quick Start (download & run)
- go to the latest release
- download and unzip the source code
- download and unzip the executables ("asm" and "corewar") into the root folder of the unzipped source code
- navigate to it in your command shell
- if necessary, set permissions on the executables, eg:
>chmod 777 asm corewar
- assemble the champions with:
>./asm champs/kire_carpetbomber.s<br/>
>./asm champs/zork.s
- if you run into difficulties, try installing [the ncurses library](https://ostechnix.com/how-to-install-ncurses-library-in-linux/ "the ncurses library")
- make it fight in the arena with:
>./corewar champs/kire_carpetbomber.cor champs/zork.cor

## Quick Start (compile & run)
- install Make and GCC
- clone the repository
- navigate to it in your command shell
- compile the assembler and virtual machine with:
>make 
- if you run into difficulties, try installing [the ncurses library](https://ostechnix.com/how-to-install-ncurses-library-in-linux/ "the ncurses library")
- assemble the champions with:
>./asm champs/kire_carpetbomber.s<br/>
>./asm champs/zork.s
- make it fight in the arena with:
>./corewar champs/kire_carpetbomber.cor champs/zork.cor

### Compilation options
>make<br/>
>make re<br/>
>make clean<br/>
>make fclean<br/>

## Corewar virtual machine flags
Dump memory after N cycles then exits:
>./corewar -dump 1000 champs/kire_carpetbomber.cor champs/zork.cor

Print output from "aff" (Default is to hide it):
>./corewar -a champs/kire_carpetbomber.cor champs/zork.cor

## Extended Explanation
This project consists out of two modules, the ASM assembler and the Corewar virtual machine.<br/>
ASM can take a champion's code, written in (pseudo)assembly, and convert it into (pseudo)machinecode.

Champion code looks like this example champion, *zork.s*
>.name "zork"<br/>
>.comment "I'M ALIIIIVE"<br/>
><br/>
>l2:	sti r1, %:live, %1<br/>
>		and r1, %0, r1<br/>
><br/>
>live:	live %1<br/>
>		zjmp %:live

It is a kind of pseudo-assembly that can contain one of about a dozen instructions.<br/>
It can range from something as simple as reporting to the *Corewar* VM that the champion is still alive,<br/>
to something as complex as cloning the champion-process("cursor") onto another position in the arena.<br/>

The ASM then assembles the *zork.s* into a *zork.cor*.<br/>
When we run it without an opponent like `./corewar -dump 1000 zork.cor`,<br/>
and make it dump the core(memory arena) after 1000 cycles,<br/>
it will look like this:<br/>
![](https://i.imgur.com/UOJW6ot.png)
The code on the first line is *zork.s*' s assembly code,<br/>
converted into *zork.cor*'s hexadecimal bytecode,<br/>
which can be read and executed by the *corewar* virtual machine.<br/>
The virtual machine reads the code from left to right, and executes it accordingly.<br/>
Code can also jump back to the left with a `zjump` command, which forms a loop.<br/>

The syntax on how to write a champion and how to understand and interpret bytecode is somewhat complex.<br/>
For more information you can read through the assignment PDF, included in the root of the repository.
