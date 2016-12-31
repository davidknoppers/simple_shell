# Holberton School - Holberton Shell(hsh)
Code a simple shell for [Holberton School](https://www.holbertonschool.com/). This assignment incorporates all topics covered so far, and marks the conclusion of the section of the course that is strictly about learning C programming.
<em>If you want to know how it works, build it yourself.</em>

### Prerequisites
Only use the following functions and system calls:
```
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
fork (man 2 fork)
free (man 3 free)
fstat (man 2 fstat)
getcwd (man 3 getcwd)
getline (man 3 getline)
kill (man 2 kill)
lstat (man 2 lstat)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (man 2 stat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)
_exit (man 2 _exit)
```

### Installing
Compile like this:
```
gcc -Wall -Wextra -Werror -pedantic -g *.c -o hsh
```
The ``-g`` is for tracing Valgrind errors

## Usage
Currently, when run, it looks like this:
```
vagrant:simple_shell $ ./hsh
and baby says: cat dummy.c
int main(void)
{
	return(0);
}
and baby says: exit 
vagrant:simple_shell$ 
```

## Description of File Structure
1. [builtins.c](builtins.c) - Includes builtin functions: 
  * ``is_builtin()`` - checks to see if the command is a builtin, then returns a function pointer to one of the following functions:
  * ``_exit_with_grace`` - exits the shell and frees any malloc'd space.
  * ``_env()`` - prints the current environment.
  * ``_cd()`` - change pwd. Can be used without arguments. ``cd -`` takes the user to the last directory. ``cd ~`` takes the user home.
  * ``help()`` - Prints help for builtin commands.<em>Not yet built</em> 
2. [builtins_2.c](builtins_2.c) - Second file with builtin functions: 
  * ``_setenv_usr()`` - User creates or modifies an environment variable.
  * ``_unsetenv_usr()`` - User deletes an environment variable.<em>Not yet built</em>
  * ``_alias`` - Sets, modifies or prints an alias. <em>Not yet built</em>
  * ``_history`` - Prints the history. Clear history with -c flag. <em>Not yet built</em>
3. [env_operations.c](env_operations.c)
  * ``_getenv()`` - recreation of ``getenv()`` from ``<stdlib.h>``. Gets the value of the provided key. Returns NULL if not found or on error.
  * ``_unsetenv()`` - Unsets an environmental variable. <em>Not yet built. Currently, just returns the output from the standard library.</em>
  * ``_setenv()`` - Adds or modifies an environmental variable. <em>Not yet built. Currently, just returns the output from the standard library.</em>
4. [environment.c](environment.c) - Includes all functions that deal with the environment and linked lists:
  * ``list_from_path`` - creates a linked list from the PATH variable
  * ``environ_linked_list`` - creates a linked list from the ``environ`` variable. <em>Built, but is not in use yet. Still going to implement.</em>
  * ``search_os()`` - Search the absolute path provided, search current directory, or search in PATH``
5. [executor.c](executor.c) - Includes only one function that is essential to the core functionality
  * ``executor()`` - Executes a command
6. [linked_list_operations.c](linked_list_operations.c) - Includes general utilities for creating and maintaining linked lists.
  * ``add_node()`` - Adds a node to a linked list of struct type ``env_t``
  * ``free_list()`` - Frees a linked list
  * ``print_list()`` - Prints a linked list
7. [main.c](main.c) - Entry point to program, contains only the opening message and a call to the reader() function.
8. [memory_management.c](memory_management.c) - General utilities related to memory management.
  * ``_realloc`` - Recreation of ``realloc`` from ``<stdlib.h>``. Reallocates space as necessary. Currently works from smaller spaces to larger spaces, or allocates space if NULL is passed. Also sets the unitialized space to '\0'.
  * ``_memset`` - Fills a memory location with a value for n bytes. 
  * ``_memcpy`` - Copies characters from one place in memory to another for n bytes.
9. [parser.c](parser.c) - Includes all string parsing related functions, and includes functions critical to the basic functionality:
  * ``_getline()`` - Recreation of ``getline()`` from ``<stdio.h>``. Gets a line from stdin, delimited by a ``\n`` character. Also handles ``EOF``. Returns the line, or NULL on error. 
  * ``parser()`` - Parses a string into tokens. Returns a double pointer.
  * ``is_alias`` - Filler function for handling aliases. Currently does not do anything. <em> This functionality has not been built.</em>
  * global variable ``flag`` for ``signalhandler()`` - Triggers when ``^C`` is hit, then turns off.
  * `sighandler`` - Interrupts the running process if it is not a builtin then prints the prompt again.
  * ``reader()`` - Reads user input, turns it into a string and parses it into tokens. Then it performs actions based on the first token.
10. [shell.h](shell.h) - Header file: Contains all struct definitions, macros, standard library includes, and function prototypes.
11. [string_operations.c](string_operations.c) - Includes all utility functions that deal with string operations:
  * ``_strlen()`` - Returns the length of a string. Recreation of ``strlen()`` from ``<string.h>``
  * ``_strncmp()`` - Compares two strings for n bytes, and returns the value of the first difference found. Returns 0 when the last value is the same. Recreation of ``strncmp()`` from ``<string.h>``
  * ``_strdup()`` - Duplicates a string. Recreation of ``strdup()`` from ``<string.h>``
  * ``_strcat_realloc()`` - Concatenates two strings and reallocs a space if either one of the strings are too big to fit in the destination.
  * ``_atoi()`` - Turns a string into an integer. Recreation of ``atoi()`` from ``<stdlib.h>``
12. [string_operations_2.c](string_operations_2.c) - Second file that includes all utility functions that deal with string operations:
  * ``word_count()`` - Counts words in a string as delimited
  * ``_strlen_const()`` - same thing as strlen, but accepts const strings.
  * ``simple_print()`` - Writes to stdout, accepts a const string.
  * ``_isdigit()`` - Checks to see if a char is a digit. Recreation of ``isdigit()`` from ``<ctype.h>``
13. [strtok.c](strtok.c) - Includes the strtok function, as well as helper functions that do not need to be referenced elsewhere
  * ``_strchr()`` - Checks for a char in a string. Returns the string on success, and NULL on failure. Recreation of ``strchr()`` from ``<string.h>``
  * ``_strspn()`` - Gets the length of a substring. Recreation of ``strspn()`` from ``<string.h>`` with a different return type.
  * ``_strpbrk() - search a string for any set of bytes. Recreation of ``strpbrk()`` from ``<string.h>``
  * ``_strtok_r()`` - Split a string into tokens, and alters the string in the process. Recreation of ``strtok`` from ``<string.h>``
14. [AUTHORS](AUTHORS) - List of contributors.
15. [LINKS.md](LINKS.md) - List of links used for learning how to make this project.
16. [man_1_simple_shell](man_1_simple_shell) - Basic manual page.
17. [bowie](bowie.txt) - ASCII art of David Bowie.

## TODO
### Main Algorithm design
- [x] Program flow design
- [x] Shell builtin incorporation
- [x] Command Execution ``/bin/ls``
- [x] Command argument handling ``/bin/ls -la``
- [x] Command Execution without absolute paths ``ls -la``
- [x] Environment
  - [x] ``$PATH``
  - [ ] Other elements of the environment
- [x] Signal Handling
- [ ] Input files
- [x] Interactive mode
- [x] Non-interactive mode
- [ ] Expansion
- [ ] Aliases

### Parsing 
- [x] Handle common white spaces: ``\t`` and spaces
- [ ] Handle uncommon white spaces: ``\f`` (form feed), ``\r`` (carriage return), ``\v`` (vertical tab)
- [x] Parser splits strings into tokens.

#### Control Operators
- [x] EOF
- [x] ``\n``
- [x] ``;``
- [ ] ``;;``
- [ ] logical operators: ``&&``, and ``||``
- [ ] grouping operators: ``|``, and ``&`` - Pipelines
- [ ] combined grouping operators: ``|&``
- [ ] comments: ``#``

### Recreate standard library functions
- [x] getline
- [x] strtok
- [x] getenv
- [ ] setenv
- [ ] unsetenv
- [ ] More to come

### Shell Builtins
- [x] register builtins before executing commands
- [x] cd
- [x] env
- [ ] help
- [ ] history
- [x] exit
  - [x] exit handles numeric argument for custom exit status
  - [x] Exiting frees malloc'd memory
- [ ] ``:`` - Null Command
- [ ] alias
- [ ] unalias
- [ ] cat
- [ ] echo
- [ ] type
- [ ] jobs
- [ ] fg
- [ ] bg
- [ ] kill
- [ ] pwd
- [ ] pushd
- [ ] popd
- [ ] dirs

### Expansions
- [ ] Brace expansion
  - [ ] ``{ }`` - ``mkdir /home/username/{old,new,gold,blue}``
- [ ] Tilde expansion - ``echo ~+``, echo ~-``
- [ ] Variables ``TEST="hello!"``
  - [ ] Special expansions
    - [ ] ``$?`` - Exit status of last process
    - [ ] ``$-`` - Flags used on shell invocation
    - [ ] ``$$`` - Current PID of the shell
    - [ ] ``$0`` - Name of the shell or shell script
- [ ] Command substitution ``$( )`` or backticks
- [ ] Arithmetic Expansion ``$(( ))``
- [ ] Word Splitting
- [ ] Filename Expansion
  - [ ] ``*`` - ``cat *.c`` - matches any string
  - [ ] ``?`` - matches any single character
  - [ ] ``[...]`` - ``ls [0-9][0-9]``
- [ ] Escaping backslash``\{\ \}`` - Preserves the literal value of the next character that follows. 
- [ ] Single quotes - Preserves the literal value of each character within the quote pair.
- [ ] Double quotes - Preserves the literal value of each character within the quote pair, except for the characters $, ', \, and !.

### Redirection
- [ ] output redirection: ``gcc dummy.c -o dummy 2> /dev/null``, ``exec 1> /dev/null``
- [ ] appended output redirection: ``cat main.c test.c >> maintest.c``
- [ ] input redirection ``sed 's|http://|https://|' << EOL``
- [ ] Remove redirection symbols and control operators from argument list

### Startup Files
- [ ] Scripts as input
- [ ] Colors
- [ ] Profile

### Signals
- [x] Stopping Jobs: ``^C``
- [ ] Job handling: ``^Z`` suspends processes with ``wait()`` and ``kill()``
- [ ] Clearing the Screen: ``^L``
- [ ] reverse i-search: ``^R`` 

### Interactive Mode
- [ ] Cursor Movement
- [ ] Auto-complete with ``<tab>``

### Advanced Features
- [ ] Shell Functions
- [ ] Looping Constructs
  - [ ] Reserved Keywords
    - [ ] time
    - [ ] for ``for name [ [in [words ...] ] ; ] do commands; done``, ``for (( expr1; expr2; expr3 )) ; do commands; done
    - [ ] do
    - [ ] while ``while test-commands; do consequent-commands; done``
    - [ ] until ``until test-commands; do consequent-commands; done``
    - [ ] done
  - [ ] Builtins
    - [ ] break
    - [ ] continue
- [ ] Conditional Constructs
  - [ ] Reserved Keywords
    - [ ] if
    - [ ] then
    - [ ] elif
    - [ ] else
    - [ ] fi
    - [ ] case
    - [ ] esac
  - [ ] Builtins

## Bugs
- [x] When ``enter`` is hit, it segfaults
- [x] When ``^C`` is hit, it stays on one line.
- [x] EOF (``^D``) it segfaults
- [x] Two unfreed mallocs somewhere. (Check with Valgrind.)
- [x] Only delimiters handled are spaces and newlines.
- [ ] In ``_getline()``, ``read()`` fails the second time, because read happens before the buffer is reallocated. Need to rework the logic.

## Optimizations
- [ ] Change the linked list for path to an array of strings

## Links
For a list of resources and commands used, refer to [LINKS.md](LINKS.md)

## Authors
* **Ian Liu-Johnston** [Personal Website:](http://ianxaunliu-johnston.com) || [Twitter](https://twitter.com/Concativerse)
* **David Knoppers** [LinkedIn](https://www.linkedin.com/in/dknoppers) || [Twitter](https://twitter.com/dxknoppers)
