## level06

There is a [level06.php file](level06.php) and its executable level06 in the current directory. The php script displays the result of a x() function which takes argv[1] and argv[2] as parameters. The x() function opens and saves the contents of the file specified by argv[1], then searches and replaces some characters and returns the modified contents.

After a tedious analysis of the script (thanks to Stephen Cole Kleene for having invented the regular expressions, aka regex), I notice a vulnerability in the script: the use of the `e` modifier that allows to treat as part of the program everything that will be parsed.

Fortunately, a good part of the program has no action on the contents of the file given as a parameter (even the second parameter is useless).

```$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);```

Here, everything between "[x" and "]" will be treated as part of the program. I just have to format the content of the file so that it is well interpreted in the php script: 

```echo '[x ${`getflag`}]' > /tmp/exploit ; ./level06 /tmp/exploit```

And this is how I caught the flag.