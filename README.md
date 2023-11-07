# simple crossplatform TCP client server Application

```
dmytrouglach@d cmake-build-debug % ./server
Waiting for client to connect on localhost:5001
connected
hello
quit
Disconnected 5
Disconnected 3
```

```
dmytrouglach@d cmake-build-debug % ./client
Go ahead, say something, server awaits
server:
client: hello
server: hello response!
client: quit
server: bye
client: Disconnected 3
```
