#include <cstdlib>
#include <Room.h>
#include <iostream>
#include <RoomController.h>
#include <PigeonEXE.h>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>

constexpr int ROWS = 10;
constexpr int COLS = 10;
constexpr int SIZE = ROWS * COLS;

enum directions {
    Left = -1,
    Right = 1,
    Up = -ROWS,
    Down = ROWS
};

const std::pair<directions, std::string>
directionsList[4] = {{directions::Left, "Left"},
                     {directions::Right, "Right"},
                     {directions::Up, "Up"},
                     {directions::Down, "Down"}};

const std::pair<directions, std::string>
reverseDirectionsList[4] = {{directions::Left, "Right"},
                     {directions::Right, "Left"},
                     {directions::Up, "Down"},
                     {directions::Down, "Up"}};

int main(){
    srand(time(nullptr));
    Room rooms[SIZE];
    std::vector<int> unvisited(SIZE);
    std::iota(unvisited.begin(), unvisited.end(), 0);
    // Initialize rooms and unvisited vector
    std::generate(std::begin(rooms), std::end(rooms), [n = 0, &rooms] () mutable { return Room(n++); });

    while( unvisited.size() > 1 )
    {
        int i = rand() % unvisited.size();
        int roomID = unvisited[i];
        std::iter_swap(unvisited.begin() + i, unvisited.end());
        unvisited.pop_back();
        int numDoorsToTry = rand() % 5;
        for(int tryNum = 0; tryNum <= numDoorsToTry; tryNum++)
        {
            int roll = rand() % 4;
            auto [distance, direction] = directionsList[roll];
            if( (distance == directions::Left && roomID % COLS == 0) ||
                (distance == directions::Right && roomID % COLS == COLS - 1) ||
                (roomID + distance > SIZE -1) ||
                (roomID + distance < 0))
            {
                continue;
            }
            if( rooms[roomID].searchDoorByDirection(direction) == nullptr )
            {
                rooms[roomID].addDoor(roomID + distance, direction);
                rooms[roomID + distance].addDoor(roomID, reverseDirectionsList[roll].second);
            }
        }
    }

    std::ostringstream os;
    std::ostringstream row;
    std::ostringstream connections;
    for( auto r : rooms )
    {
        row << ((r.searchDoorByDirection("Left") == nullptr) ? " " : "-");
        row << "O";
        connections << " ";
        connections << ((r.searchDoorByDirection("Down") == nullptr) ? " " : "|");
        if( r.getId() % COLS == COLS - 1 )
        {
            os << row.str() << "\n";
            os << connections.str() << "\n";
            row.clear();
            row.str("");
            connections.clear();
            connections.str("");
        }
    }

    std::cout << "Maze paths" << std::endl;
    std::cout << os.str() << std::endl;

    std::vector<Room> v;
    for( auto& r : rooms )
    {
        v.push_back(std::move(r));
    }

    RoomController rc(v);
    PigeonEXE pigeonEXE(&rc);
    int roomID = 0;
    while(roomID != SIZE - 1)
    {
        std::cout << roomID << std::endl;
        auto [direction, distance] = pigeonEXE.getShortestDirection(roomID, SIZE - 1);
        // break;
        std::cout << direction;
        if( distance )
        {
            std::cout << ", ";
        }
        roomID = rc.getDoorDesignatedRoomId(roomID, direction);
    }
    std::cout << "now back..." << std::endl;
    while(roomID != 0)
    {
        std::cout << roomID << std::endl;
        auto [direction, distance] = pigeonEXE.getShortestDirection(roomID, 0);
        // break;
        std::cout << direction;
        if( distance )
        {
            std::cout << ", ";
        }
        roomID = rc.getDoorDesignatedRoomId(roomID, direction);
    }

    //Go back to the last room from the first room
    //This should be all done in constant time since
    //The calculations were all done above for it
    while(roomID != SIZE - 1)
    {
        std::cout << roomID << std::endl;
        auto [direction, distance] = pigeonEXE.getShortestDirection(roomID, SIZE - 1);
        // break;
        std::cout << direction;
        if( distance )
        {
            std::cout << ", ";
        }
        roomID = rc.getDoorDesignatedRoomId(roomID, direction);
    }
    std::cout << "now back..." << std::endl;
    while(roomID != 0)
    {
        std::cout << roomID << std::endl;
        auto [direction, distance] = pigeonEXE.getShortestDirection(roomID, 0);
        // break;
        std::cout << direction;
        if( distance )
        {
            std::cout << ", ";
        }
        roomID = rc.getDoorDesignatedRoomId(roomID, direction);
    }
    // pigeonEXE.printDistances();

}