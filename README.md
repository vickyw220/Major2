CSCE 3600 – Major Assignment 2: Custom Shell (`newshell`)

 Team Members

Vicky Wainaina – Responsible for newshell.c -main shell logic, redirection.

Muhammud Elsell – Responsible for Exit command

Emmanuel Moonga – Responsible for cd & path command integration

Dustin Dowell – Responsible for myhistory command

---

Organization of the Project

newshell.c– Main shell loop, process creation, and function dispatch

builtins.c / builtins.h – Handles built-in commands (`cd`, `exit`, `myhistory`)

pipeline.c / pipeline.h – Manages pipe parsing, command piping, and I/O redirection (`>`, `<`)

path.c / path.h –  Manages internal PATH variable list, with support for adding/removing/searching custom paths

history.c / history.h – Stores and prints command history (`myhistory`)

Makefile – Compiles the project and builds the `newshell` executable

**README.md – Describes team roles, file structure, and known issues

Each team member was responsible for writing and testing their own module. In addition:

All members contributed to integrating their functions into `newshell.c`

Collaboration included debugging pipe handling, command tokenization, and build issues

---

Known Bugs or Problems

-Pipe execution not fully implemented – Placeholder logic exists for parsing pipes, but executing piped commands across multiple processes needs refinement.

Limited redirection: Only output redirection using `>` is supported at this time.

No aliasing or advanced scripting** – Not yet implemented due to time constraints.

Some error messages may be generic and do not reflect the specific cause.

Testing was done with basic shell commands.

Basic error reporting.
