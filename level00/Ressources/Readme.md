## level00

Naturally, I started by looking at the contents of /etc/passwd. No luck, the password associated to flag00 is encrypted. I note on the other hand a cleartext password for flag01, I will come back to that.

I then look for anything that might belong to the flag00 user with ```find / -user flag00 2>/dev/null```. I find two files, /usr/sbin/john and /rofs/usr/sbin/john that have the same content: "cdiiddwpgswtgt". I tried ```su flag00``` with this password, but the authentication failed. The password must be encrypted.

I went on https://dcode.fr to identify the encryption method used: the affine cipher (monoalphabetic substitution cipher, where each letter in an alphabet is mapped to its numeric equivalent, encrypted using a simple mathematical function, and converted back to a letter). I then find the decrypted password: "nottoohardhere".

The ```su flag00``` command works with this password and I can now run the ```getflag``` command and go to the next level.