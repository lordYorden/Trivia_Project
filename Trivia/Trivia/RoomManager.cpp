#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser admin, RoomData metadata)
{
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
		//todo
	}
}

Room::Room(LoggedUser admin, RoomData metadata):
	m_metadata(metadata)
{
	addUser(admin);
}
