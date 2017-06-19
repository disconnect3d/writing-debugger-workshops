## "Writing a debugger" workshops

Materials for "Writing a debugger" workshops lead by Disconnect3d at AGH UST thx to [KNI Kernel scietific circle](http://kernel.fis.agh.edu.pl/).

Below you can find a kind of short summary of each meeting; knowledge is free; enjoy.

The workshops has been done in polish, so don't expect everything below is in english.

### First meeting 14.06.2017 17:00-20:00

##### tracers

* strace - system call tracer
* ltrace - dynamic library calls tracer
* both commands can follow and trace children processes (`-f` or multiple `f` flag)
* you can filter output with predefined groups or syscall/function name (`-e` flag)
* What happens when we launch `rm *` aka "just strace it" (see also [Back To The Future: Unix Wildcards Gone Wild](https://www.defensecode.com/public/DefenseCode_Unix_WildCards_Gone_Wild.txt))

...see `man strace` or `man ltrace` for more.

##### gdb

Random notes:

* to debug with source code don't forget to compile with debugging symbols (e.g. `-g` or `-ggdb` flag in GCC)
* source code debugging uses real source code files to show code lines, so gdb displays the latest code, even if binary was compiled before some changes
* program that makes `Segmentation fault` can be told to generate a core dump file (by doing `ulimit -c unlimited`) - this file can be used for post mortem debugging in gdb (e.g. `gdb ./binary corefile`)
* when stepping through stack frames - don't forget you can just inspect the latest state of program - going up or down won't hold previous global variables (e.g. function static variables) and so on (relates to `up`, `down` and `backtrace` gdb commands)
* gdb uses `ptrace` (see below)
* gdb can be scripted with gdbscript or Python

Some of the functionalities/commands described about gdb:

* `gdb ./binary` - loads the binary under gdb
* `help [<command>]` helps a lot ;)
* `run` or `r` will launch the binary, you can also specify arguments afterwards (e.g. `run 1 2 3`)
* `break function` or `break *0x1234` let us set a breakpoint under given function (if we have symbols) or address; the shorter name is `b`
* `info breakpoints` or `i b` will show us current breakpoints (or watchpoints/catchpoints)
* `delete <X>` or `d <X>` - deletes breakpoint with number X
* `continue` or `c` will continue execution till next breakpoint
* `info registers` or `i r` will show registers
* `info proc mappings` will show process memory mappings; it is an equivalent of `cat /proc/<pid>/maps`
* `print` or `p` let us print stuff - registers (`p $eax`), memory content (`p *(int*)(0x1234)`), even variables/symbols (`p main`) and structures (try to print a dereferenced `FILE*`)
* `x` stands for eXamine and let us examine memory in various ways - e.g. `x/10i $rip` will display next 10 instructions, `x/20xw $rsp` will display stack content; sky is the limit, check out `help x` for more formats
* `backtrace` shows a trace of stack frames/functions that called the place we are on (so functions that we should go back to after returning from current function) 
* `backtrace <X>`, `up` and `down` let us select a stack frame or move up/down
* `layout` command let us change view and see assembly (`layout asm`) or source code (`layout src`) - the latter requires debugging symbols
* `set disssembly-flavor intel` - changing gdb asm syntax to intel, you can set it persistently by putting it in `~/.gdbinit`

Assembly stepping commands:
* `si` - step instruction - goes into next instruction; if we are on a `call ...` it will jump into
* `ni` - next instruction - jumps OVER a call

Source code stepping:
* `step` or `s` - steps into next code line (or into a function)
* `next` or `n` - steps over next code line (don't step into functions)

##### binutils: readelf, objdump

* looking over ELF files - `readelf -h ./binary`, `readelf -r ./binary` (relocations, so e.g. functions from shared libraries)
* deassembling binary to asm - `objdump -d -Mintel ./binary`

##### low level

We have learned a bit of x86/x86-64 assembly, mostly from slides 5-17 from [this presentation](https://docs.google.com/presentation/d/1HKuW69NFD2IFSdkdD7ul3aWriHXHDLfPOvJV0wsiwH0/edit#slide=id.g212fc02393_0_0) (this is in polish).

This covered topics like:
* processor registers (also x86 vs x86-64 e.g. eax vs rax), FLAGS/EFLAGS/RFLAGS
* asm syntax - AT&T vs Intel
* some basic assembly instructions
* "basic" instructions
* mechanics of calling functions, also a bit of calling conventions (see also [Agner Fog "Calling conventions"](www.agner.org/optimize/calling_conventions.pdf))


##### coding

All of the
We have described a bit of `fork`, pipes, `execv` and `ptrace` - then started working a bit on `3_ptrace` ending up with what is in `3_ptrace` directory.
