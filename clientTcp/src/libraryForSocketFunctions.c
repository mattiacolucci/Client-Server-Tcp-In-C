#include "libraryForSocketFunctions.h"

int sendMex(int socketDiConnessione, char* mex){
	if(send(socketDiConnessione,mex,strlen(mex),0)!=strlen(mex)){  //se ho inviato un numero di buyte diverso da quello che intendevo inviare, allora si è verifiato un errore
		puts("send failed");
		return -1;
	}
	return 0;
}

int recvMex(int socketDiConnessione,char* buff){
	memset(buff,0,BUFFERSIZE);  //imposto il buffer per la ricezioni dei messaggi a \0, cioè al carattere di fine strinza
	int bytes_rcvd=recv(socketDiConnessione,buff,BUFFERSIZE-1,0);  //ricevo il messaggio dal server; la funzione recv ritorna il numero di byte ricevuti, e concatena all'ultimo elemento del buffer, il messaggio ricevuto
	if(bytes_rcvd<=0){  //se i byte ricevuti sono 0 o meno, allora ce stato un errore
		puts("error in recv mex from server");
		return -1;
	}
	return 0;
}

int recvMexInMultipleSent(int socketDiConnessione, char* buff, int mexlen){
	int bytes_rcvd=0; //numero byte ricevuti
	int total_bytes_rcvd=0;  //numero complessivo di byte ricevuti
	memset(buff,'\0',BUFFERSIZE);  //imposto il buffer per la ricezioni dei messaggi a \0, cioè al carattere di fine strinza
	while(total_bytes_rcvd<mexlen){  //fino a quando non ricevo tanti byte, quanti sono quelli di cui è comporto il mio messaggio
		bytes_rcvd=recv(socketDiConnessione,buff,BUFFERSIZE-1,0);  //ricevo il messaggio dal server; la funzione recv ritorna il numero di byte ricevuti, e concatena all'ultimo elemento del buffer, il messaggio ricevuto
		if(bytes_rcvd<=0){  //se i byte ricevuti sono 0 o meno, allora ce stato un errore
			puts("error in recv mex from server");
			return -1;
		}
		total_bytes_rcvd+=bytes_rcvd;  //aggiungo il numero di byte letti attualemnte al numero di byte letti in totale
	}
	return 0;
}

void closeAll(int sock){
	closesocket(sock);
	clearwinsock();
}

void clearwinsock(){
	#if defined WIN32  //se compilo su windows
		WSACleanup();
	#endif
}
