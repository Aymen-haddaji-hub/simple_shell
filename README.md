# Simple Shell

Simple Shell attempts to replicate some of the processes of the 'sh' shell or 'bash' shell.. It execute commands and interact with the kernel.

simplesh [script files]

## Current features

* It Runs commands in $PATH
* Environment and local variables
* $? return values, $$ pid
* $# number of args and $0-9 (not a perfect sh mimic currently though)
* Logical operators &&/|| with multi-line continuation
* ; command separator
* ~ expansion to current user's home directory
* unclosed multi-line quote continuation
* \ escaping
* Run script files, as well as commands from standard input


Built-ins:
* help
* exit [status]
* setenv
* unsetenv
* env (listing environment functionality only)
* cd
* 
* unalias
* history

## Getting started
To use this shell, you must compile it and move it into a $PATH folder like /usr/local/bin. To compile the program, clone the project, navigate to the directory, and then type:
```
gcc -o simple_shell *.c
```
The copy the output file to /usr/local/bin (you may need to add "sudo" to the front of this line):
```
cp simple_shell /usr/local/bin
```
After this you should be able to run the shell by typing "simplesh".

## Usage Examples
To start up the shell and run a simple command (in this case pwd), then exit:
```
Username@your-regular-prompt:~$ simple_shell
simple_shell:/home/username$ pwd
/home/username/
simplesh:/home/username$ exit
Username@your-regular-prompt:~$
```
pwd lists the current working directory, which is displayed in the simplesh terminal prompt. We can also run script files. If you have a script with the following:
```
#!/usr/bin/env simple_shell
echo Hello from simple shell!
```
Then execute the script you will see "Hello from simple shell!" in our terminal. We can also use command line arguments for variables. Currently, $0 is always "simplesh", $1 is the script name, and $2 and beyond are the arguments. So if we want the first argument, you would put in $2 like so:
```
#!/usr/bin/env simple_shell
echo Hello $2
```
Then if you want to pass in an argument you can do it like so:
```
Username@your-regular-prompt:~$ ./helloscript "simple shell!"
Hello simple shell!
```


## Authors
Aymen Haddaji - https://github.com/Aymen-haddaji-hub
Oumayma Bougossa - https://github.com/oumaymabg
Ons Jannet - https://github.com/OnsJannet

