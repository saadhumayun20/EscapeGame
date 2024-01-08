#include <stdio.h>

#include "defs.h"

void viewEscape(char *);

/*
  Purpose:  send connection request to server at given IP
       in:  server IP
   return:
*/

void viewEscape(char *serverIP)
{
    int clientSocket;
    char buffer[MAX_BUFF];

    setupClientSocket(&clientSocket, serverIP);

    while (1)
    {
        int bytesReceived = rcvData(clientSocket, buffer);
        if (bytesReceived <= 0)
        {
            printf("Connection closed by the server.\n");
            break;
        }

        printf("%s", buffer);

        if (strcmp(buffer, "QUIT\n") == 0)
        {
            printf("Quit message received. Exiting.\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
    }

    close(clientSocket);
}
