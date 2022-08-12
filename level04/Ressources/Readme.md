## level04

There is a level04.pl executable in the current directory. It's a small perl script that takes a variable x as a parameter and displays it in a web page on port 4747. In a browser, `ip:4747?x=ok` will display "ok". If we set x to "$(getflag)", the variable is interpreted and the getflag command is executed by the super user.