## level14

This time, I don't have anything in the current directory. I have looked everywhere and I see nothing to exploit. The only thing I have to do is to see if I can't exploit the getflag command itself. So I will check its assembler code with gdb.

Since the assembly code of the main() function is quite long, I will put it in a [separate file](getflag.s) and analyze it in this file. First of all, there are a variety of protections in the program: 
* from main+13 to main+26 and main+1388 to main+1404, there is the use of a stack canary which protects the program against buffer overflow attacks (the program has been compiled with the `-fstack-protector` gcc flag).
* from main+36, the use of ptrace(PTRACE_TRACEME, 0, 1, 0) allows the program to know if it is followed by a debugger for example.
* The program also checks that there is no injection via the environment variable LD_PRELOAD.

After these few checks, the program makes a call to getuid() to get the uid of the calling process. This uid is then compared in a switch. For each case, we find in the code the hash of the password which is passed to the dehash function ft_des(). One thing to note: the expected range of uids in the program is from 3000 to 3014. My uid is currently 2014. The command `cat /etc/passwd` allows to understand better: uid 2000 to 2014 correspond to users level00 to level14, and uid 3000 to 3014 correspond to users flags00 to flags14.

I will not be able to repeat my level13 exploit, by modifying the return of getuid() in the debugger because of the ptrace() command: the program will simply display "You should not reverse this" and return (see [main+76](getflag.s)). What I can do, however, is place a breakpoint just before the call to ptrace(), then use the command `ju *[addr]` to jump to a specified address in the program. Here, I want to jump to main+1183, i.e. before the ft_des() call with the corresponding hash string if the 3014 uid:

```
flag14@SnowCrash:~$ gdb getflag
[...]
(gdb) b *main+36
Breakpoint 1 at 0x804896a
(gdb) r
Starting program: /bin/getflag 

Breakpoint 1, 0x0804896a in main ()
(gdb) ju *main+1183
Continuing at 0x8048de5.
7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
[Inferior 1 (process 6593) exited normally]
```

```
flag14@SnowCrash:~$ su flag14
Password: 
Congratulation. Type getflag to get the key and send it to me the owner of this livecd :)
flag14@SnowCrash:~$ getflag
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```