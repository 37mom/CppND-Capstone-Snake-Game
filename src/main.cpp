#include <iostream>
#include "controller.h"
#include "game.h"
#include "GameManager.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  GameManager MngrObj;
  GameUser usrObj;
  std::map<string, int> His;
  string name ;
  int Score ;
  int Size;
  

  
  while (true)
  {
    int state = MngrObj.GMA_Initialize();
    MngrObj.GMA_Handler(state , &usrObj);
    
    if(state == 1 || state == 2)
    {
      // Game Start
      Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
      Controller controller;
      Game game(kGridWidth, kGridHeight,MngrObj.Difficulty);
    
      game.Run(controller, renderer, kMsPerFrame);

      string name = usrObj.GUS_getUserName();
      int Score = game.GetScore();
      int Size = game.GetSize();
      cout << "-----------------------------------" << endl;
      cout << "Game has terminated successfully!\n";

      cout << "Player : " << name << endl;
      cout << "Score: " << Score << "\n";
      cout << "Snake Size: " << Size << "\n";
      His.insert(make_pair(name, Score));
      usrObj.GUS_WriteUsersHistory(His);
    }
    else if(state == 3)
    {
      if(name != "")
      {
        His.insert(make_pair(name, Score));
        usrObj.GUS_WriteUsersHistory(His);
      }

      // Game end 
      return 0;
    }
    
    if (MngrObj.endGameFlag == true)
    {
      // Game end 
      return 0;
    }

    
  }
  
  return 0;
}
