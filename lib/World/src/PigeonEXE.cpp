#include <PigeonEXE.h>
#include <algorithm>
#include <iostream>

PigeonEXE::DirectionDistance PigeonEXE::getShortestDirection(ID fromRoom, ID toRoom) {
    auto toMap = this->shortestMap.find(fromRoom);
    if( toMap == shortestMap.end() || toMap->second.find(toRoom) == toMap->second.end() ) {
        calculate(fromRoom, toRoom);
        toMap = shortestMap.find(fromRoom);
        if( toMap != shortestMap.end() ) {
            auto roomItr = toMap->second.find(toRoom);
            if( roomItr != toMap->second.end() ) {
                return roomItr->second;
            }
        }
        return std::make_pair(std::string{}, 0);
    }
    return shortestMap[fromRoom][toRoom];
}

int PigeonEXE::calculate(ID fromRoom, ID toRoom) {
    if( _roomController == nullptr ) {
        return -1;
    }
    auto room = _roomController->searchRoom(fromRoom);
    if( room == nullptr ) {
        return 0;
    }

    if( fromRoom == toRoom ) {
        auto fromMap = &shortestMap.emplace(fromRoom, std::unordered_map<ID, DirectionDistance>{}).first->second;
        fromMap->emplace(toRoom, std::make_pair("", 0));
        return 0;
    }

    // std::cout << fromRoom << " : " << toRoom << std::endl;
    std::vector<DirectionDistance> directionDistances{};

    auto fromMap = &shortestMap.emplace(fromRoom, std::unordered_map<ID, DirectionDistance>{}).first->second;
    fromMap->emplace(toRoom, std::make_pair("", -1));
    auto doorList = room->getDoorList();
    for( auto& door : doorList ) {
        auto direction = door.getDirection();
        auto toRoomID = door.getDesignatedRoomId();
        fromMap->insert_or_assign(toRoomID, std::make_pair(direction, 1));
        auto toRoomItr = shortestMap.find(toRoomID);
        if( toRoomItr != shortestMap.end() &&
            toRoomItr->second.find(fromRoom) != toRoomItr->second.end() ) {
            if( toRoomItr->second.find(toRoom) != toRoomItr->second.end() ) {
                if( toRoomItr->second[toRoom].second != -1 ) {
                    directionDistances.emplace_back(direction, shortestMap[toRoomID][toRoom].second + 1);
                }
                continue;
            }
        }
        if( toRoomID == toRoom ) {
            directionDistances.emplace_back(direction, 1);
            fromMap->insert_or_assign(toRoom, directionDistances.back());
            return 1;
        }
        // std::cout << "Calculating: " << fromRoom << " : " << toRoomID << std::endl;
        int distance = calculate(toRoomID, toRoom);
        if( distance ) {
            directionDistances.emplace_back(direction, distance + 1);
        }
    }

    if( !directionDistances.empty() ) {
        auto min = std::min_element(directionDistances.begin(), directionDistances.end(),
            [](const DirectionDistance& a, const DirectionDistance& b) {
                return a.second < b.second;
            });
        // std::cout << fromRoom << std::endl;
        // std::cout << "Added: " << toRoom << " " << min->first << " " << min->second << std::endl;
        fromMap->insert_or_assign(toRoom, *min);
        return min->second;
    } else if( shortestMap[fromRoom][toRoom].second == -1 ) {
        shortestMap[fromRoom].erase(toRoom);
    }

    return 0;
}
