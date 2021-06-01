#include "RoomManager.h"

/*
* RoomManager Constructor
* input: none
* output: none
*/
RoomManager::RoomManager()
{
}

/*
* RoomManager Distructor
* input: none
* output: none
*/
RoomManager::~RoomManager()
{
	this->m_rooms.clear();
}

/*
* create a room and adds it to existing rooms list
* input: admin - the user who created the room (LoggedUser)
*		,metadata - room's settings (RoomData)
* output: none
*/
void RoomManager::createRoom(LoggedUser admin, RoomData metadata)
{
	if (this->m_rooms.find(metadata.id) != this->m_rooms.end())
	{
		throw ExceptionHandler("Error....Room already exist");
	}
	Room newRoom = Room(admin, metadata);
	this->m_rooms.insert(std::pair<int, Room>(metadata.id, newRoom));
}

/*
* deletes an existing room
* input: roomID - room to delete (int)
* output: none
*/
void RoomManager::deleteRoom(int roomID)
{
	this->m_rooms.erase(roomID);
}

/*
* return whether the room is currently played or not
* input: roomID - room to check (int)
* output: roomState -  whether the room is currently played or not (bool)
*/
bool RoomManager::getRoomState(int roomID)
{
	std::map<int,Room>::iterator it = this->m_rooms.find(roomID);
	if (it != this->m_rooms.end())
	{
		return it->second.getMetadata().isActive;
	}
	throw ExceptionHandler("Error....Room wasn't found");
}

/*
* return all rooms exsist
* input: none
* output: rooms - all of the exsisting rooms (sdt::vector<RoomData>)
*/
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	std::map<int, Room>::iterator it = this->m_rooms.begin();
	for (; it != this->m_rooms.end(); it++)
	{
		rooms.push_back(it->second.getMetadata());
	}
	return rooms;
}

/*
* return the room given its ID
* input: roomID - the room identifier (int)
* output: room - the room with th given id (Room)
*/
Room& RoomManager::getRoomById(int roomID)
{
	std::map<int, Room>::iterator it = this->m_rooms.find(roomID);
	if (it != m_rooms.end())
	{
		return it->second;
	}
	throw ExceptionHandler("Error....Room dose not exist");
}

/*
* Room Constructor
* input: admin - the user who created the room (LoggedUser)
*		,metadata - room's settings (RoomData)
* output: none
*/
Room::Room(LoggedUser admin, RoomData metadata):
	m_metadata(metadata)
{
	addUser(admin);
}

/*
* Room Distructor
* input: none
* output: none
*/
Room::~Room()
{
	m_users.clear();
}

/*
* joins the user into the room
* input: user - the user to add to the room (LoggedUser)
* output: none
*/
void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

/*
* removes the user into the room
* input: user - the user to remove from the room (LoggedUser)
* output: none
*/
void Room::removeUser(LoggedUser user)
{
	this->m_users.erase(std::remove(this->m_users.begin(), this->m_users.end(), user), this->m_users.end());
}

/*
* return all of the usernames currently in the room
* input: none
* output: users - the users in the room (std::vector<std::string>)
*/
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> users;
	std::vector<LoggedUser>::iterator it = this->m_users.begin();
	for (; it != this->m_users.end(); it++)
	{
		users.push_back(it->getUsername());
	}
	return users;
}

/*
* returns the room's settings
* input: none
* output: metadata - the room's settings (RoomData)
*/
RoomData Room::getMetadata() const
{
	return this->m_metadata;
}

/*
* sets the room is Active metadata
* input: isActive - whether a game has started or not (bool)
* output: void
*/
void Room::setRoomState(bool isActive)
{
	this->m_metadata.isActive = isActive;
}
