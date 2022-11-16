# :ocean: :shell: SeaShell

![seashell demo](assets/cshell_demo.gif)

cshell is an implementation of the original UNIX shell in C. It uses the POSIX API to implement a lot of the same functionality of Ken Thompson's first shell.

The API calls predominantly used are <code>read</code>, <code>write</code>, <code>fork</code>, <code>exec</code>, and <code>wait</code> to name a few.


## :feet: Challenges

Handling multiple commands in the same input (dealing with logical seperators) was a large challenge. We overcame this by building a command queue that could be built based on each input. Scanning for seperators that would split the command. This way we could handle flags and more for our commands at the same time. 

Using a queue also allowed us to easily check commands for success and failure, a doubly linked list queue could have been a possible improvement allowing for traversal in both directions. However, we ended up just setting flags as we dequeued the elements.

Some of the code could certainly be refactored to be more generic, for instance both history queues and command queues have entirely seperate data structures and functions, this could certainly be improved upon. As well as some of the ways traversal of the queues was handled.

I am still overall very happy with the net result of this project as I learned tons about memory management, string parsing, and process forking.

## :running: Getting Started

* [Ubuntu 14.04 LTS](http://releases.ubuntu.com/14.04/) - Operating system reqd.

* [GCC 4.8.4](https://gcc.gnu.org/gcc-4.8/) - Compiler used


## :warning: Prerequisites

* Must have `git` installed

* Must have repository cloned

```
$ sudo apt-get install git
```


## :arrow_down: Installing

Clone the repository into a new directory

```
$ git clone https://github.com/BennettDixon/simple_shell.git
```
Compile with the following:

```
gcc -Wall -Werror -Wextra -pedantic *.c -o seashell
```


## :clipboard: Examples

Using in Interactive && Non-Interactive Mode

![seashell modes demo](assets/cshell_demo_modes.gif)

Using `$PATH` to find custom commands (executables)

```
> echo dog
dog
> /bin/echo dog
dog
```

Using `&&` or `||` logic to run commands based on success

```
> ls -l /asdfasdf && echo this won't print!
ls: cannot access /asdfasdf: No such file or directory 
> ls -l /asdfasdf || echo this will  print!
ls: cannot access /asdfasdf: No such file or directory
this will print!
```

Using `;` to seperate commands and run regardless of success

```
> ls -l /asdfasdf ; echo printme! ; wc -l main.c
ls: cannot access /asdfasdf: No such file or directory
printme!
 21 316 main.c
```

Using `exit [status]` to exit the process with status number

```
> exit 102
vagrant@vagrant-ubuntu-trusty-64:~/simple_shell$ echo $?
102
```

Using `env` to print the environmental variables

```
> env
XDG_SESSION_ID=30
TERM=ansi
SHELL=/home/vagrant/simple_shell/seashell
...
...
```
## :books: Coding Style Tests

Strictly followed `Betty` style guide. To install

```
$ git clone https://github.com/holbertonschool/Betty.git

$ cd Betty; ./install.sh
```


## :pencil: Version

* 0.1.0



## :blue_book: Authors

* **Connor Brereton** - [@ConnorBrereton](https://github.com/ConnorBrereton/printf)

* **Bennett Dixon** - [@BennettDixon](https://github.com/BennettDixon)



## :mag: License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details



## :mega: Acknowledgments
* Holberton School (providing guidance)
* Stack Overflow (help on various memory errors (not leaks))
