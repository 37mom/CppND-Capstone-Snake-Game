#include <map>
#include <string>
#include "GameManager.h"


using namespace std;
bool GameManager::endGameFlag = false;

int GameManager::GMA_Initialize()
{
  
  int pressedkey;
  cout << " ### WELCOME TO SNAKE GAME ###" << endl;
  cout << "   " << std::endl;
  cout << " 1. New Game" << endl;
  cout << " 2. Scores" << endl;
  cout << " 3. Exit" << endl;
  cout << " your choice --> ";

  endGameFlag = false;
  return getPressedKey() ;

}

void GameManager::GMA_Handler(int &State , GameUser * Usr)
{
  std::map<string, int> History;
  int pressedkey =0;
	switch (State)
    {
        case 1:
        GMA_AddPlayer(Usr);
        endGameFlag = false;
        cout<< "Please choose Difficulty from 1-> Easy ,2-> Medium ,3-> Hard : " <<endl;
        pressedkey = getPressedKey();
        if ((pressedkey >= 1) || (pressedkey <= 3))
        {
        	Difficulty = pressedkey;
        }
        break;
        
    	case 2:
        endGameFlag = false;
        //Retrive Data
        History = usr.GUS_ReadUsersHistory();
        usr.GUS_DisplayGameHistory(History);
        GMA_AddPlayer(Usr);
        
        break;
        
    	case 3:
        cout << "end the game" <<endl;
        endGameFlag = true;
        break;
    }

}

void GameManager::GMA_AddPlayer(GameUser *Usr)
{

    Usr->GUS_setUserName();
}

int GameManager::getPressedKey() {
    int pressedKey;
    bool validInput = false;

    while (!validInput) {
        if (std::cin >> pressedKey) {
            if (pressedKey >= 1 && pressedKey <= 3) {
                validInput = true;
            } else {
                std::cout << "FAILED. Please enter a correct number!" << std::endl;
            }
        } else {
            std::cout << "FAILED. Please enter a valid number!" << std::endl;
            // Clear the error flag on cin
            std::cin.clear();
        }
        // Clear the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return pressedKey;
}
