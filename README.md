# Unix-shell
This project was created as part of the OS class

The aim of this project is to design and develop a shell interface using C program.The eventual goal is to understand how parent and child processes work in a operating systems.This shell interface accepts user command and then executes each command in a separate process.The history feature in our UNIX shell allows user to see upto 10 recently used commands. It allows a command of max upto 256 characters.A buffer is maintained in a circular fashion where each entry occupies one place in the buffer. If an entry exceeds the size of the buffer, then the least recently used history is removed and replaced by the new entry.

Compile on linux machine using gcc compiler and directly execute using the executable shell file.Some commonly known commands that can work with this shell include but not limited to ls, pwd, date, history, exit
