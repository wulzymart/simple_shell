# ALX Project: `simple_shell`

The aim is to develop a simple unix command interpreter in operation to `/bin/sh` with the exact same error output. 

## Features:

**Task 02**
- Handle command lines with arguments
---

**Task 03**
- Handle the `path`
- `fork` is not called if the command doesn't exist.
---

**Task 04**
- implements the `exit` built-in, that exits the shell
- usage: `exit`
---

**Task 05** 
- implement the `env` built-in, that prints the current environment.
---

**Task 06** (advanced)
- Developed a `getline` function
- Use a buffer to read many chars at once and call the least possible the `read` system call
- Used static varibles
- Removed the use of `getline`
---

**Task 07** (advanced)
- Removed the use of `strtok`.
- Developed `_strtok` as a replacement
---

**Task 08. setenv, unsetenv** (advanced)
- Handle areguments for the built-in `exit`
- Usage: `exit status`, where `status` is an integer used to exit the shell.
---

**Task 09** (advanced)
- implement the `setenv` and `unsetenv` builtin commands
`setenv`:
	- Initialize a new environment variable, or modif an existing one.
	- Command syntax: `setenv VARIABLE VALUE`
`unsetenv`:
	- Remove an environment variable
	- Command syntax: `unsetenv VARIABLE`
	- Should print something on stderr on failure.
---

**Task 10. cd** (advanced)
- Implement builtin command `cd`:
	- Changes the current directory of the process.
	- Command syntax: `cd [DIRECTORY]`
	- If no argument is given to `cd`, the command is interpreted as `cd $HOME`
	- Handles the command `cd -`
	- Update the environment variable `PWD' when directory changes.
---

**Task 11. ;** (advanced)
- Handle the commands separator `;`
---

**Task 12. && and ||** (advanced)
- handle the `&&` and `||` shell logical operators
---

**Task 13. alias** (advanced)
- implement the `alias` builtin command.
- Usage: `alias [name[='value'] ...]`
---

**Task 14. variables** (advanced)
- Handles variables replacement
- Handles the `$?` variable
- Handles the `$$` variable


**Task 15. Comments** (advanced)
- Handle comments (#)
---

**Taask 16. File as input**
- Usage: `simple_shell [filename]`
- Can take a file as a command line argument.
- The file contains all the commands that the shell should run before exiting
- The file contains one command per line.
- In this mode, the shell should not print a prompt and should read from `stdin`
---


