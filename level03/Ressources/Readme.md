## level03

There is a level03 executable in the current directory that displays "exploit me" on the standard output.

Using the strings command, I see that the program makes a call to `/usr/bin/env echo`. I will be able to exploit this by creating a false echo executable and redefining the PATH environment variable.

```cd /tmp ; echo "int main(){system(\"getflag\");}" > echo.c ; gcc echo.c -o echo ; export PATH=/tmp:$PATH```

I did this in `/tmp` because that's where I have rights to create and compile files. 

Now, when I execute level03, a system call to getflag is made by the super user, so I can get the flag.