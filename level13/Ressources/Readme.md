## level13

This time there is a 32-bit ELF LSB executable. At runtime, the program displays only "UID 2013 started us but we we expect 4242". So apparently, I have the wrong UID. I'll get the assembly code of the main() function with the `disas main` command in gdb to see what happens.

```
; prologue

0x0804858c <+0>:     push   %ebp
0x0804858d <+1>:     mov    %esp,%ebp
0x0804858f <+3>:     and    $0xfffffff0,%esp
0x08048592 <+6>:     sub    $0x10,%esp

; if (getuid() != 4242)

0x08048595 <+9>:     call   0x8048380 <getuid@plt>
0x0804859a <+14>:    cmp    $0x1092,%eax
0x0804859f <+19>:    je     0x80485cb <main+63>
0x080485a1 <+21>:    call   0x8048380 <getuid@plt>

; then printf("UID %d started us but we we expect %d\n", getuid(), 4242);

0x080485a6 <+26>:    mov    $0x80486c8,%edx
0x080485ab <+31>:    movl   $0x1092,0x8(%esp)
0x080485b3 <+39>:    mov    %eax,0x4(%esp)
0x080485b7 <+43>:    mov    %edx,(%esp)
0x080485ba <+46>:    call   0x8048360 <printf@plt>

; and exit(1)

0x080485bf <+51>:    movl   $0x1,(%esp)
0x080485c6 <+58>:    call   0x80483a0 <exit@plt>

; else printf("your token is %s\n", ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I"));

0x080485cb <+63>:    movl   $0x80486ef,(%esp)
0x080485d2 <+70>:    call   0x8048474 <ft_des>
0x080485d7 <+75>:    mov    $0x8048709,%edx
0x080485dc <+80>:    mov    %eax,0x4(%esp)
0x080485e0 <+84>:    mov    %edx,(%esp)
0x080485e3 <+87>:    call   0x8048360 <printf@plt>

; return (0)

0x080485e8 <+92>:    leave  
0x080485e9 <+93>:    ret
```

At line +14, the result of getduid(), placed in the eax register, is compared to 0x192 (i.e. 4242 in hexadecimal). If the values are equal, then a ft_des() function is called with "boe]!ai0FB@.:|L6l@A?>qJ}I" as parameter. This string is probably the hash of the flag we are looking for, and the ft_des() function is probably a dehashing function.

I don't need to look further into the ft_des() function, because I found a simple way to override the UID control: just place a breakpoint in gdb at line +14, and modify the value contained in eax just before it is compared. 

```
(gdb) b *main+14
Breakpoint 1 at 0x804859a
(gdb) r
Starting program: /home/user/level13/level13 

Breakpoint 1, 0x0804859a in main ()
(gdb) set $eax=4242
(gdb) n
Single stepping until exit from function main,
which has no line number information.
your token is 2A31L79asukciNyi8uppkEuSx
```

I can now run the `su level14` command and go to the next level using that password.