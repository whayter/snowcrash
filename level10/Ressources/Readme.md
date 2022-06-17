## level10

There is a level10 executable file and a token file for which I don't have read rights.


Running the binary file gives me some informations:
```
level10@SnowCrash:~$ ./level10 
./level10 file host
        sends file to host if you have access to it

level10@SnowCrash:~$ ./level10 token 127.0.0.1
You don't have access to token
```

Thanks to the strings command, I can see that the program opens a socket on port 6969 to send the file. So I will use netcat to receive that file. Of course, I still have to find a way to trick the program into thinking that I have rights over the token file.

I notice the use in the program of the access() function. I don't know this function, but I guess it checks whether the calling process can access the given file. I confirm my intuition by reading the man, and I even find the solution to my problem. Here is the extract that interests me:

```
Warning: Using these calls to check if a user is authorized to, for example, open a file before actually doing so using open(2) creates a security hole, because the user might exploit the short time interval between checking and opening the file to manipulate it.  For this reason, the use of this system call should be avoided.
```
