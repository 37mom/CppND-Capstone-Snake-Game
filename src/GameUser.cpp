#include "GameUser.h"


GameUser::GameUser(string UsrName, int UsrScore)
{
    this->UserName = UsrName;
    this->UserScore = UsrScore;
}
void GameUser::GUS_setUserName()
{
    string name;
    cout<<"Enter Player Name : ";
    cin >> name;
    this->UserName = name;
}

void GameUser::GUS_setUserScore(int Score)
{
    this->UserScore = Score;

}

string GameUser::GUS_getUserName()
{
    return UserName;
}

int GameUser::GUS_getUserScore()
{   
    return UserScore;
}

map<string, int> GameUser::GUS_ReadUsersHistory()
{
  string line ,userName;
  int UserScore;
  map<string, int> UsersMap;
  
  ifstream filestream("DS.txt");
  if (filestream.is_open())
  {
    while (getline(filestream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> userName >> UserScore)
      {
		//Create the map
        UsersMap.insert(make_pair(userName, UserScore));
      }

    }
    // Close the file
    filestream.close();
    cout << "finishing reading History ..." << endl;
    return UsersMap;
  }
  else
  {
    ofstream outfile("DS.txt");
    cout << "History file not exist. New one created." << endl;
  }

}

void GameUser::GUS_DisplayGameHistory(std::map<string, int> &GameHistory)
{

  int cnt = 0;

  for (std::pair<std::string, int> element : GameHistory)
  {
    cout << cnt << ". player : " << element.first << ", score : " << element.second << endl;
    cnt++;
  }
}

void GameUser::GUS_WriteUsersHistory(map<string, int> History)
{
  map<string, int>::iterator element;

  ofstream Data;

  Data.open("DS.txt", ios::in | ios::out | ios::app);
  
  if (!Data.is_open())
  {
    cout << " FileNotExists|Can't Open" << endl;
  }
  else
  {

    for (element = History.begin(); element != History.end(); element++)
    {

      Data << (*element).first << " " << (*element).second << "\n";
    }

    Data.close();
  }

}
    






