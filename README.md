# Simple Shell

Simple_Shell is our mini replicat of  the processes of the 'bash' or 'sh'  by executing commands and interacting with the kernel.



## Current features

* $PATH :  Where the commands Runs
* local and Environment variables
* $? return values, $$ pid
* $# number of arguments and $0-9 
* &&/|| as logical operators with multi-line continuation
* using ; as is the command separator
* using ~ expansion to current user's home directory
* unclosed multi-line quote continuation
* \: as escaping
* it Runs commands from the input as well as script files. 

Built-ins:
* help
* exit 
* setenv
* unsetenv
* env (listing environment functionality only)
* cd
* alias
* unalias
* history

## Getting started
you must first compile this shell into a $PATH folder like /usr/local/bin to be able to use it, And to do so you have to clone the project, navigate to the directory, and then type:
```
gcc -o simple_shell *.c
```
Then you have to copy the output file to /usr/local/bin you can always add sudo if it doesn't work
```
cp simple_shell /usr/local/bin
```
Now you'll be able to use the shell.

## Usage Examples
start by opening the shell  and running a simple command like pwd, then exit:
```
Username@your-regular-prompt:~$ simple_shell
simple_shell:/home/username$ pwd
/home/username/
simplesh:/home/username$ exit
Username@your-regular-prompt:~$
```
the command pwd lists the current working directory. We're able to also run script files. 
```
#!/usr/bin/env simple_shell
echo Hello from simple shell!
```
the output of the executed script will display  "Hello from simple shell!" in our terminal. We can use cmd line afruments for variables like in the following example :

#!/usr/bin/env simple_shell
echo Hello $2
```
let's try passing an argument we can do it like so :
```
Username@your-regular-prompt:~$ ./helloscript "simple shell!"
Hello simple shell!
```

## Usage Examples

Interactive Mode

$ cat test_ls_2
/bin/ls
/bin/ls

Non-Interactive Mode
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2

## Authors
Aymen Haddaji - https://github.com/Aymen-haddaji-hub
Oumayma Bougossa - https://github.com/oumaymabg
Ons Jannet - https://github.com/OnsJannet

