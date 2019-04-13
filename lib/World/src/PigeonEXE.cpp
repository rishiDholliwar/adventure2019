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
        return 1;
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
        if( toRoomItr != shortestMap.end() ) {
            if( toRoomItr->second.find(toRoom) != toRoomItr->second.end() ) {
                auto toDirection = toRoomItr->second[toRoom].first;
                auto toDistance = toRoomItr->second[toRoom].second;
                if(toDirection.empty())
                {
                    continue;
                }
                auto toID = _roomController->searchDoor(toRoomID, toDirection)->getDesignatedRoomId();
                if( toDistance != -1 && toID != fromRoom ) {
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
        fromMap->insert_or_assign(toRoom, *min);
        for( auto& door : doorList ) {
            auto toRoomID = door.getDesignatedRoomId();
            auto itr = shortestMap.find(toRoomID);
            int distance = 0;
            if( itr != shortestMap.end() ) {
                if( itr->second.find(toRoom) != itr->second.end() ) {
                    distance = shortestMap[toRoomID][toRoom].second;
                }
            }
            if( distance > min->second + 1 ) {
                // std::cout << toRoomID << std::endl;
                calculate(toRoomID, toRoom);
            }
        }
        return min->second;
    } else if( shortestMap[fromRoom][toRoom].second == -1 ) {
        std::cout << "fromRoom: " << fromRoom << std::endl;
        shortestMap[fromRoom].erase(toRoom);
    }

    return 0;
}

void PigeonEXE::printDistances() {
    for( auto [fromRoom, toRoomMap] : shortestMap ) {
        for( auto [toRoom, directionDistance] : toRoomMap ) {
            std::cout << fromRoom << " -> " << toRoom << ": " << directionDistance.first << ", " << directionDistance.second << std::endl;
        }
    }
}
