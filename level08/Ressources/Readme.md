## level08

There is in the current directory a level08 executable and a file named token for which I don't have read rights.

Using the strings command on the level08 file, I can see that the program is written in C, and uses the functions open, read, write, printf, strstr... The program takes the path of a file as a parameter and seems to simply display its contents.

If I run the program passing the token file as parameter, I get an error message telling me that I "may not access 'token'". It doesn't look like a bash error but rather seems to come from the program. So I'll take a closer look with gdb.

```gdb ./level08 token```
```disass main```

The first part of the program simply checks the parameter. If no parameter is passed, the program displays how it should be used before exiting.

[...]
0x080485a6 <+82>:    mov    0x1c(%esp),%eax
0x080485aa <+86>:    add    $0x4,%eax
0x080485ad <+89>:    mov    (%eax),%eax
0x080485af <+91>:    movl   $0x8048793,0x4(%esp)            // x/s 0x8048793: "token"
0x080485b7 <+99>:    mov    %eax,(%esp)
0x080485ba <+102>:   call   0x8048400 <strstr@plt>
0x080485bf <+107>:   test   %eax,%eax
0x080485c1 <+109>:   je     0x80485e9 <main+149>
0x080485c3 <+111>:   mov    0x1c(%esp),%eax
0x080485c7 <+115>:   add    $0x4,%eax
0x080485ca <+118>:   mov    (%eax),%edx
0x080485cc <+120>:   mov    $0x8048799,%eax                 // x/s 0x8048799: "You may not access '%s'\n"
0x080485d1 <+125>:   mov    %edx,0x4(%esp)
0x080485d5 <+129>:   mov    %eax,(%esp)
0x080485d8 <+132>:   call   0x8048420 <printf@plt>
0x080485dd <+137>:   movl   $0x1,(%esp)
0x080485e4 <+144>:   call   0x8048460 <exit@plt>
[...]

Here it is clear that the name of the file given as a parameter is compared with the string "token" using the strstr() function. If the strings are equal, the program displays the error message before exiting. Otherwise, the file is opened, its content is read, saved, and displayed using the write() function.

So the problem is not that I don't have read rights on the token file, but simply that the file is called token. I can try to create a symbolic link to get around this issue : ```ln -s /home/user/level08/token /tmp/tok ; ./level08 /tmp/tok``` displays "quif5eloekouj29ke0vouxean". Bingo.

The ```su flag08``` command works with this password and I can now run the ```getflag``` command and go to the next level.