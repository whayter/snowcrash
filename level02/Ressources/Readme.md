## level02

There is a file level02.pcap in the current directory. It is a file from a network flow sniffer. I used the scp command to transfer the file to my machine: ```scp -P 4242 level02@SnowCrash:level02.pcap .```.

Once the file is recovered, I can change the rights with the chmod command then open it with the Wireshark software. There are a number of TCP packages that can be followed (ctrl click > follow > TCP stream). Here we find a password interspersed with dots ("ft_wandr...NDRel.L0L").

If I filter the packets to keep only those sent by the client, and display the data hexdump, I notice that the dots correspond to 8f, which is del in the ascii table. Applying all the del's to the found password, we finally get "ft_waNDReL0L".

The ```su flag02``` command works with this password and I can now run the ```getflag``` command and go to the next level.