#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, std::vector<SDL_Point> const &ObstaclePos, SDL_Point const &bonusFood)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  auto ObstacleTask = std::async(&Renderer::RenderObstacle, this, ObstaclePos);
  auto FoodTask = std::async(&Renderer::RenderFood, this, food);
  auto BonusFoodTask = std::async(&Renderer::RenderBonusFood, this, bonusFood);
  auto SnakeTask = std::async(&Renderer::RenderSnake, this, snake);

  ObstacleTask.wait();
  FoodTask.wait();
  BonusFoodTask.wait();
  SnakeTask.wait();

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderObstacle(std::vector<SDL_Point> const &ObstaclePos)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  std::unique_lock<std::mutex> lock(_mutex);
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : ObstaclePos)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  lock.unlock();
}

void Renderer::RenderSnake(Snake const snake)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  std::unique_lock<std::mutex> lock(_mutex);
  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  lock.unlock();
  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive)
  {
    lock.lock();
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  }
  else
  {
    lock.lock();
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
  lock.unlock();
}

void Renderer::RenderFood(SDL_Point const &food)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render food
  std::unique_lock<std::mutex> lock(_mutex);
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  lock.unlock();
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  lock.lock();
  SDL_RenderFillRect(sdl_renderer, &block);
}
void Renderer::RenderBonusFood(SDL_Point const &Bonusfood)
{
  SDL_Rect block;
  const int bonusSeconds = 1;
  static auto startTime = std::chrono::high_resolution_clock::now();
  auto current_Time = std::chrono::high_resolution_clock::now();
  auto elapsed_Seconds = std::chrono::duration_cast<std::chrono::seconds>(current_Time - startTime).count();
  static bool Counter = true;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  block.x = Bonusfood.x * block.w;
  block.y = Bonusfood.y * block.h;
  // Render bonus food
  if ((!((Bonusfood.x == 500) && (Bonusfood.y == 500))) && (true))
  {
    std::unique_lock<std::mutex> lock(_mutex);
    if (elapsed_Seconds >= bonusSeconds)
    {
      Counter = !Counter;
      startTime = std::chrono::high_resolution_clock::now();
    }
    lock.unlock();
      if (Counter ==true)
      {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
      }
      else
      {
         SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
      }
    
    
    lock.lock();
    SDL_RenderFillRect(sdl_renderer, &block);
  }
}
