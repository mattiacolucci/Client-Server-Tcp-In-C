# Client-Server-Tcp-In-C
socket communication between a client and a server, directed by TCP protocol, in C programming language

Follow the following steps to communicate between client and server:
- start the server from path "serverTcp/debug/serverTcp.exe"
- start the client from path "clientTcp/debug/clientTcp.exe"
- client and server will automatically connect together; client will make a connection request at server socket on DEFAULT_IP and DEFAULT_PORT secified in the header file "libraryForSocketFunctions.h"

This program allows client to make some easy math calculations (addition, subtraction, moltiplication, division) between integer numbers; the cient program ask the user to enter the operation to do from the command line, with this syntax: <operator> <operand1> <operand2>   (ex: + 3 5)
this string will be sent to the server, who will extract the single parts of the string and make the requested operation, sending the result to the client

To end the client process, the user has to enter "="

Enjoy!
