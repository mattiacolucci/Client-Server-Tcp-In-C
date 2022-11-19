#include "libraryForSocketFunctions.h"

void readChoice(char* str);

int main(void) {
	/*int serverPort;
	char serverAddr[20];*/

	#if defined WIN32   //if I am in windows
		WSADATA wsa_data; //I initialize the struct that let me use socket from library wsock32
		int result=WSAStartup(MAKEWORD(2,2),&wsa_data);
		if(result!=NO_ERROR){
			puts("error at WSAstartup");
			return -1;
		}

		//the library wsock32 is accessible
		puts("no error occurred");
	#endif

	int clientSocket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);  //create the socket of client; the socket function return an integer representing the socket created
	if(clientSocket<0){
		puts("error in client socket creation");
		clearwinsock();
		return -1;
	}

	struct sockaddr_in serverAddress;  //struct that represents server's port and address
	serverAddress.sin_family=AF_INET;  //setting server's protocol family
	serverAddress.sin_addr.s_addr=inet_addr(DEFAULT_IP);  //setting server's ip address
	serverAddress.sin_port=htons(DEFAULT_PORT);  //setting server's port

	if(connect(clientSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){  //sending connection request to the server
		//three-ways handshake process begins..
		puts("error in connection");
		return -1;
	}

	//connection established
	char recvBuff[BUFFERSIZE];  //receive buffer
	char choice[20];  //string representing user operation chosen

	puts("Insert '=' to exit\n");
	readChoice(choice);
	while(choice[0]!='='){  //cicle until user insert a string that begins with =
		sendMex(clientSocket,choice);  //function that send the string insert from the user at the server

		if(recvMex(clientSocket,recvBuff)<0){  //receive the operation's result from the server
			closeAll(clientSocket);
			return -1;
		}

		if(recvBuff[0]=='E'){  //if the server's response begins with "E", it indicates an error
			puts("Error during the operation:");
			printf("%s\n",recvBuff);
		}else{
			printf("result of the Operation is: %.2lf\n",atof(recvBuff));
		}
		readChoice(choice);
	}
	sendMex(clientSocket,choice);
	closeAll(clientSocket);
	return EXIT_SUCCESS;
}

void readChoice(char* str){
	do{
		puts("Insert the operation to do, with the following syntax:\noperator number1 number2\npossible operations are: + (sum), - (subtraction), / (division), x (moltiplication)");
		memset(str,0,20);
		fflush(stdin);
		gets(str);
	}while(strcmp(str,"")==0);
}
