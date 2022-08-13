## level12

There is a level12.pl file. Looking at the [source code](level12.pl), I see that the program listens on port 4646, and implements two functions: n() which takes as parameter the return of the function t() which takes itself two parameters `x` and `y`. Looking at the source code in more detail, I notice that the parameter `y` is not used for anything. In the t() function, the `x` parameter is modified using regex: alphabetic characters are changed to uppercase and everything thas follows a whitespace is removed. The function n() simply displays '..' if t() returns 1, otherwise '.'.

There is one interesting line: ``@output = `egrep "^$xx" /tmp/xd 2>&1`;``. Here, the `x` parameter is the pattern for the `egrep` command. The `/tmp/xd` file does not exists, but it's not a problem, because I will make sure that the pattern is interpreted and executed using "`[command]`". 

Obviously, I can't place my command directly to `x`, since it will be capitalized and I can't use whitespaces. But what I can do is to create an executable file in `/tmp` that will contain a call to `getflag`. Since I eventually want to read the result of my command, I will redirect this result to a file. The name of this file must not contain lowercase characters to match the `xx` variable. Also, rather than giving an absolute path, I will use a wildcard so that "/tmp" does not become "/TMP".

```
level12@SnowCrash:~$ echo 'getflag > /tmp/flag' > /tmp/EXPLOIT
level12@SnowCrash:~$ echo "getflag > /tmp/flag" > /tmp/F146 ; chmod +x /tmp/F146
level12@SnowCrash:~$ curl localhost:4646/?x='`/*/F146`'
..level12@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```

I can now reach the next level using the `su level13` command with this password.