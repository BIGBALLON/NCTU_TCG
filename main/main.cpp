#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
//#include <cassert>
//#include "Fib2584/GameBoard.h"
#include "../Fib2584/Typedefs.h"
#include "../Fib2584/Statistic.h"
#include "../Fib2584Ai.h"

using namespace std;

int main(int argc, char* argv[])
{
    // create and initialize AI
    Fib2584Ai ai;
    ai.initialize(argc, argv);

    // initialize statistic data
    //Statistic statistic;
    //statistic.setStartTime();

    // handle genmove commands
    while(true)
    {
        int arrayBoard[4][4];
        agent role;

        string sInput;
        getline(cin, sInput);
        
        // handle all genmoves
        if(sInput.find("genmove") != string::npos)
        {
            size_t playStringPos = sInput.find(" play");
            size_t evilStringPos = sInput.find(" evil");

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

            string sBoardString = sInput.substr(boardStringPos);
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
                    sOutput = "up";
                else if(moveDirection == MOVE_LEFT)
                    sOutput = "left";
                else if(moveDirection == MOVE_RIGHT)
                    sOutput = "right";
                else if(moveDirection == MOVE_DOWN)
                    sOutput = "down";
            }
            else if(role == EVIL)
            {
                int newTileIndex = ai.generateEvilMove(arrayBoard);
                char sIndex[10];
                sprintf(sIndex, "%d", newTileIndex);
                sOutput = sIndex;
            }

            cout << sOutput << endl;
        }
        else if(sInput.find("gameover") != string::npos)
        {
            break;
        }
        //statistic.increaseOneMove();
    }
    //statistic.setFinishTime();

    // output statistic data
    //statistic.show();

    return 0;
}
