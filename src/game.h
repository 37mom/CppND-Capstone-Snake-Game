#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

  
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height,int Diffi);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
  std::vector<SDL_Point> ObstaclePosition;
 private:
  Snake snake;
  SDL_Point food;
  SDL_Point bonusFoodPoint;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  int score{0};
  int Difficulty{1} ;
  void PlaceFood();
  void PlaceBonusFood();
  void Update();

  void PlaceObstacle();
  bool ObstacleCell(int x, int y); 
  bool is_bonus_food_active{false};
  
  std::mutex mutex; // Mutex
  std::condition_variable condition_var;
  std::thread bonusFoodThread;
  void BonusFoodTimer();
};

#endif
