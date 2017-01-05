#include <sys/types.h>  
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include "../Fib2584/Typedefs.h"
#include "../Fib2584/Statistic.h"
#include "../Fib2584Ai.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 3) {
		cout << "Please use: ./exec [student id] [pass phrase]" << endl;
		return 0;
	}

	// create and initialize AI
    Fib2584Ai ai;
    ai.initialize(argc, argv);
    cout << "AI initialized\n";

	int sockfd;
	struct sockaddr_in dest;

	/* create socket */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	/* initialize value in dest */
	bzero(&dest, sizeof(dest));
	dest.sin_family = PF_INET;
	dest.sin_port = htons(21684);
//	dest.sin_addr.s_addr = inet_addr("140.113.194.120");	
	dest.sin_addr.s_addr = inet_addr("140.113.167.52");
	//dest.sin_addr.s_addr = inet_addr("140.113.66.97");

	/* Connecting to server */
	int status = connect(sockfd, (struct sockaddr*)&dest, sizeof(dest));
	if(status == -1) {
		cout << "Connection failed: " << strerror(errno) <<  endl;
		return 0;
	}
	cout << "Connect to game server\n";
	/* Receive message from the server and print to screen */
	string sStudentID = argv[1];
	string sPassPhrase = argv[2];
	cout << "Student ID: " << sStudentID << endl;
	cout << "Pass phrase: " << sPassPhrase << endl;

	int tempStdinFd = dup(0);
	int tempStdoutFd = dup(1);

	dup2(sockfd, 1);
	cout << "AI " << sStudentID << "\n" << "init " << sPassPhrase << "\n\n" << flush;
	dup2(tempStdoutFd, 1);

	// handle genmove commands
    while(true)
    {
        int arrayBoard[4][4];
		int iJId;
        agent role;

        string sInput;
        cout << "Waiting message\n";
        dup2(sockfd, 0);
        getline(cin, sInput);
        dup2(tempStdinFd, 0);
		if(sInput == "")
		{
			cout << "Server has closed the connection." << endl;
			break;
		}
        cout << "Receive command: " << sInput << endl;
        
        // handle all genmoves
        if(sInput.find("genmove") != string::npos)
        {
            size_t playStringPos = sInput.find(" play");
            size_t evilStringPos = sInput.find(" evil");
			size_t jobIdPos = sInput.find(" jid:");

            size_t boardStringPos;
            if(playStringPos != string::npos)
            {
                boardStringPos = playStringPos + 5;
                role = PLAYER;
            }
            else if(evilStringPos != string::npos)
            {
                boardStringPos = evilStringPos + 5;
                role = EVIL;
            }
            else
            {
                cout << "genmove needs to know who is playing! (player or evil)\n";
                continue;
            }

			if(jobIdPos != string::npos)
			{
				iJId = atoi(sInput.substr(jobIdPos + 5).c_str());
			}

            string sBoardString = sInput.substr(boardStringPos, jobIdPos - boardStringPos);
            stringstream ss(sBoardString);
            int gridValue;
            int index = 0;
            while(ss >> gridValue)
            {
                arrayBoard[index/4][index%4] = gridValue;
                index++;
            }
            //assert(index == 16);
            
            string sOutput;

            if(role == PLAYER)
            {
                MoveDirection moveDirection = ai.generateMove(arrayBoard);
                if(moveDirection == MOVE_UP)
                    sOutput = "0";
                else if(moveDirection == MOVE_RIGHT)
                    sOutput = "1";
                else if(moveDirection == MOVE_DOWN)
                    sOutput = "2";
                else if(moveDirection == MOVE_LEFT)
                    sOutput = "3";
            }
            else if(role == EVIL)
            {
                int newTileIndex = ai.generateEvilMove(arrayBoard);
                char sIndex[10];
                sprintf(sIndex, "%d", newTileIndex);
                sOutput = sIndex;
            }
            dup2(sockfd, 1);
            cout << "AI " << sStudentID << "\n" << sOutput << " jid:" << iJId << "\n\n" << flush;
            dup2(tempStdoutFd, 1);
            cout << "Send Job " << iJId << " response: " << "AI " << sStudentID << "\n" << sOutput << "\n";
        }
        else if(sInput.find("gameover") != string::npos)
        {
            break;
        }
        //statistic.increaseOneMove();
    }
	

	/* Close connection */
	close(sockfd);

	return 0;
}
