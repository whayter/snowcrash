## level05

A message appears in the terminal, informing that I have a new email. Every GNU/Linux system includes a mailbox in the "mbox" format that can be found at /var/mail.

```less /var/mail/level05```: */2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05

The first characters of the file ("*/2 * * * *") correspond to a crontab table. Crontab is a tool that allows the planning of repeated tasks in time. Here, ```sh /usr/sbin/openarenaserver``` will be executed by the super user every two minutes. This script executes and deletes each executable in /opt/openarenaserver.

```printf '#!/bin/sh\ngetflag > /tmp/flag.txt\n' > /opt/openarenaserver/fl ; chmod +x /opt/openarenaserver/fl```

As soon as my script is executed, I will find my flag using ```cat /tmp/flag.txt```.