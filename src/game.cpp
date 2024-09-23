#include "game.h"
#include <iostream>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height,int Diffi)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
{
  Difficulty =Diffi;
  //Invalidate the Coordinates
  bonusFoodPoint.x=500;
  bonusFoodPoint.y=500;
  PlaceFood();
  PlaceObstacle();

}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, ObstaclePosition,bonusFoodPoint);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !ObstacleCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}
void Game::PlaceBonusFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !ObstacleCell(x, y))
    {
      bonusFoodPoint.x = x;
      bonusFoodPoint.y = y;
      return;
    }
  }
}
void Game::Update()
{
  if (!snake.alive)
    return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    //Update Obstacle
    PlaceObstacle();
    PlaceFood();
    if ((!is_bonus_food_active)&& (score%2)==0)
    { // Check if bonus food is already active
      PlaceBonusFood();
      is_bonus_food_active = true;
      bonusFoodThread = std::thread(&Game::BonusFoodTimer, this);
      bonusFoodThread.detach();
      
    }
    // Grow snake and increase speed.
    snake.GrowBody();
    if (Difficulty> 2) {
    snake.speed += 0.04;
    }else{
      snake.speed += 0.02;
    }
  }else if (bonusFoodPoint.x == new_x && bonusFoodPoint.y == new_y)
  {
    score=score+2;
    bonusFoodPoint.x=0;
    bonusFoodPoint.y=0;
  }
  else if (ObstacleCell(new_x, new_y))
  {
    snake.alive = false;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::PlaceObstacle()
{

  int x;
  int y;
  SDL_Point point;

  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    ObstaclePosition.clear();

    if (Difficulty> 1) {
        for (int i = 0; i < snake.grid_width; i++)
        {
          point.y = 0;
          point.x = i;
          ObstaclePosition.push_back(point);
          point.y = snake.grid_height - 1;
          point.x = i;
          ObstaclePosition.push_back(point);
        }
        for (int i = 0; i < snake.grid_height; i++)
        {
          point.y = i;
          point.x = 0;
          ObstaclePosition.push_back(point);
          point.y = i;
          point.x = snake.grid_width - 1;
          ObstaclePosition.push_back(point);
        }
      }
      int obstacleNum ;
      if (Difficulty >2){
        obstacleNum = 15;
      }else
      {
        obstacleNum = 5;
      }
      
      
    for (int i = 0; i < obstacleNum; i++)
    {
      if ((i % 2) == 0)
      {
        point.x = fmod(y + i + snake.grid_width, snake.grid_width);
        point.y = y;
      }
      else
      {
        point.y = fmod(x + i + snake.grid_width, snake.grid_width);
        point.x = x;
      }

      ObstaclePosition.push_back(point);
    }

    if (!ObstacleCell(snake.head_x, snake.head_y))
    {
      return;
    }
  }
}

// Check snake & Obstacle toched
bool Game::ObstacleCell(int x, int y)
{
  for (auto const &item : ObstaclePosition)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}
void Game::BonusFoodTimer()
{
  const int bonusSeconds = 5;
  //SDL_Point bonusFoodPoint;
  int x,y;
  auto startTime = std::chrono::high_resolution_clock::now();
  bonusFoodPoint.x = random_w(engine);
  bonusFoodPoint.y = random_h(engine);
  std::unique_lock<std::mutex> lock(mutex);
  while (is_bonus_food_active)
  {
    lock.unlock();
    auto current_Time = std::chrono::high_resolution_clock::now();
    auto elapsed_Seconds = std::chrono::duration_cast<std::chrono::seconds>(current_Time - startTime).count();
    if (elapsed_Seconds >= bonusSeconds)
    {
      // Bonus food time is up
      is_bonus_food_active = false;
      bonusFoodPoint.x = 500;
      bonusFoodPoint.y = 500;
      break;
    }
    lock.lock();
    // Wait for a short interval or until the condition_variable is notified
    condition_var.wait_for(lock, std::chrono::milliseconds(800));
  }
}