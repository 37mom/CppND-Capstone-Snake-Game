#ifndef MNGR_H_
#define MNGR_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "GameUser.h"



class GameManager
{

public:
	GameManager(){};

  int  GMA_Initialize();
  void GMA_Handler(int &State , GameUser * Usr);
  void GMA_AddPlayer(GameUser *);

  static bool endGameFlag;
  int Difficulty;

private:
  GameUser usr;
  int getPressedKey(void);
};


#endif
