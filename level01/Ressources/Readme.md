## level01

I found earlier a readable password for flag01 in the file `/etc/passwd` ("flag01:42hDRfypTqqnw"). Obviously, it is encrypted. A quick look at the [dcode tool](https://dcode.fr) does not give anything convincing.

The password has probably being hashed, so I will use the John The Ripper tool to break it. I installed the software on my machine (using homebrew) and ran the commands: `echo "flag01:42hDRfypTqqnw" > pwd; john --show pwd`, which gave me "flag01:abcdefg".

The `su flag01` command works with this password and I can now run the `getflag` command and go to the next level.