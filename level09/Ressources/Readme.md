## level09

Here again, I got a level09 executable and a token file but this time, I have the read rights on it. Its content seems to be encrypted though. The execution of the level09 program displays "You need to provied only one arg.".

`./level09 token` gives me "tpmhr". 

The program seems to perform some king of a transformation on the content of the file passed in parameter but something is wrong: the length of the string returned does not match the content of the file. Making some tests, I notice that the length of the returned string corresponds in fact to the length of the parameter itself. OK so my first guess was wrong, the program does not read the content of a file, but only takes a string as parameter.

I finally understand the encryption system: s[i] = s[i] + i. For exemple; `./level09 aaaaaa` gives me "abcdef". I wrote a little script to reverse this (cf main.c) and I got "f3iji1ju5yuevaus41q1afiuq" by passing the content of the token file as parameter.

The `su flag09` command works with this password and I can now run the `getflag` command and go to the next level.