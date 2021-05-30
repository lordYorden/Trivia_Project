#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "LoggedUser.h"
#include "ExceptionHandler.h"

typedef struct RoomData 
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
}RoomData;

class Room 
{
public:
	Room(LoggedUser admin, RoomData metadata);
	~Room();
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	RoomData getMetadata() const;
	void setRoomState(bool isActive);
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

class RoomManager
{
public:
	RoomManager();
	~RoomManager();
	void createRoom(LoggedUser admin, RoomData metadata);
	void deleteRoom(int roomID);
	bool getRoomState(int roomID);
	std::vector<RoomData> getRooms();
	Room& getRoomById(int roomID);
private:
	std::map<int, Room> m_rooms;
};