#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>




using namespace std;

class GameUser
{

public:
	GameUser() {};
	GameUser(string UserName, int UserScore);
	~GameUser(){};

	void GUS_setUserName();
	void GUS_setUserScore(int);

	string GUS_getUserName();
	int GUS_getUserScore();

	map<string, int> GUS_ReadUsersHistory();
	void GUS_DisplayGameHistory(std::map<string, int> &GameHistory);
	void GUS_WriteUsersHistory(map<string, int> History);
    
    

private:
    string UserName;
    int UserScore;

    vector<GameUser *> UserVector;
};

#endif
