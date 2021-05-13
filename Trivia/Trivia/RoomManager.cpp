#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser admin, RoomData metadata)
{
	if (this->m_rooms.find(metadata.id) != this->m_rooms.end())
	{
		throw ExceptionHandler("Error....Room already exist");
	}
	Room newRoom = Room(admin, metadata);
	this->m_rooms.insert(std::pair<int, Room>(metadata.id, newRoom));
}

void RoomManager::deleteRoom(int roomID)
{
	this->m_rooms.erase(roomID);
}

bool RoomManager::getRoomState(int roomID)
{
	std::map<int,Room>::iterator it = this->m_rooms.find(roomID);
	if (it != this->m_rooms.end())
	{
		return it->second.getMetadata().isActive;
	}
	throw ExceptionHandler("Error....Room wasn't found");
}

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

Room::Room(LoggedUser admin, RoomData metadata):
	m_metadata(metadata)
{
	addUser(admin);
}

Room::~Room()
{
	m_users.clear();
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	this->m_users.erase(std::remove(this->m_users.begin(), this->m_users.end(), user), this->m_users.end());
}

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

RoomData Room::getMetadata() const
{
	return this->m_metadata;
}
