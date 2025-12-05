#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>


using namespace std;

// the cardinal directions constants 
const int north = 0;
const int south = 1;
const int east = 2;
const int west = 3;

// more constants
const int inventoryMAX = 5;
const int wall = -1;
const int roomnum = 8;

struct room {
    string name; // room name obvi
    string description; // describe the room as best as possible 
    string item; // empty = no items :(
    string event; // none = boring, no events
    bool locked; // for the gate ig
    int exits[4]; // 4 as in the 4 cardinal directions (N, S, E, W)
};

struct player {
    string name; // y/n :)
    int health; // intitially 100, instant death if you reach 0, nub
    int roomindex; // for location basically
    string inventory[inventoryMAX]; //intially empty
    int inventoryitems; // initially 0

};
room dungeon[roomnum];
player player1;
void initialdungeon(room dungeon[])
{
    dungeon[0] = {
        "Enterance Hall",
        "You Wake Up to Find Yourself in a Damp and Dimly Lit Room, This is Your Starting Point for Today's Adventure to Escape the Forgotten Dungeon!",
        "torch", // used to see
        "none", // boring
        false,
        {1, wall, wall, wall} // (N, S, E, W)
    };

    dungeon[1] = { 
        "Dark Hallway",
        "You Walk Out Into a Long, and Cold, Confusing Corridor Connected to Rooms in Every Direction.",
        "empty",
        "none",
        false,
        {4, 0, 6, 2} // (N, S, E, W)
    };

    dungeon[2] = {
        "Dark Cellar",
        "You Find Yourself in Pitch Black Room Where the Air is Stale.",
        "health potion",
        "none",
        false,
    {3, 7, 1, wall} // (N, S, E, W)
    };

    dungeon[3] = {
        "Trap Room 1",
        "You Found a Small Hidden Room.",
        "empty",
        "trap", // oops
        false,
        {wall, 2, 4, wall} // (N, S, E, W)
    };

    dungeon[4] = {
        "Armory",
        "You Walk Into a Room Where Rusty, But Deadily, Weapons Line the Wall.",
        "sword", // will be needed later
        "none",
        false,
        {wall, 1, wall, 3} // (N, S, E, W)
    };

    dungeon[5] = {
        "Treasure Room",
        "You Walk Into a Dark Room With a Faint Golden Glimmer, You Follow the Glimmer to Find an Open Golden Chest... Something Lingers Inside.",
        "key", // almost out 
        "none",
        false,
        {wall, 6, wall, wall} // (N, S, E, W)
    };

    dungeon[6] = {
        "Boss Fight",
        "You Walk Into Some Stinky and Moist Room.", 
        "empty",
        "fight", // no sword = -100 hp, sword = hit = kill troll
        false, 
        {5, wall, wall, 1} // (N, S, E, W)
    };

    dungeon[7] = {
        "Gate",
        "You Regain a Glimpse of Hope, a Small Gate Amidst the Stone is All You Need to Escape! Better be Open...", // if ley = open if no key = no open
        "empty",
        "locked gate",
        true, // the only locked room
        {2, wall, wall, wall} // (N, S, E, W)
    };
}
void initialplayer(player &p)
{
    p.name = "player one"; // npc ngl 
    p.health = 100;
    p.roomindex = 0; // you wake up in dungeon 0 
    for (int i = 0; i < inventoryMAX; i++)
    {
        p.inventory[i] = "empty"; // makes sure all slots are empty
    }
    p.inventoryitems = 0; // 0 items 
}

void printroom(const room &r) // to print the room data
{
    srand(time(0));
    cout << "\n-------------------------------------------------------------------" << endl;
    cout << "Current Location: " << r.name << endl; // where you at
    cout << r.description << endl; // the very grammatically correct description
    if (r.item != "empty")
    {
        if (r.item == "torch")
        {
            cout << endl << "You See a Fiery Torch Lighting Up The Room.";
        }
        if (r.item == "sword")
        {
            cout << endl << "The Silver Sword Hanging on the Wall Catches Your Eye.";
        }
        if (r.item == "key")
        {
            cout << endl << "You Sigh in Relief as You Sight a Golden Key!";
        }
        if (r.item == "health potion")
        {
            cout << endl << "A Med-Kit is Found Laying Around!";
        }

    }

    
    cout << endl << "Exits: ";
    if (r.exits[north] != wall) cout << "North ";
    if (r.exits[south] != wall) cout << "South ";
    if (r.exits[east] != wall) cout << "East ";
    if (r.exits[west] != wall) cout << "West ";
    cout << endl;

    cout << "-------------------------------------------------------------------" << endl;

}

bool hasitem(player& p, string item) // this is just to check whether or not you have the item or not
{
    for (int i = 0; i < inventoryMAX; i++) {
        if (p.inventory[i] == item) {
            return true; // you either have it or you dont 
        }
    }
    return false;
}

void takeitem(player & p, room &r) 
{
    if (r.item == "empty") // no items... sad 
    {
       
        
        cout << "This is an empty Room, Nothing to Take." << endl;
        return;
            
        
    }

    if (p.inventoryitems >= inventoryMAX) {
        cout << "Your inventory is full!" << endl; // no more pciking up stuff from the ground
        return;
    }

    
    for (int i = 0; i < inventoryMAX; i++) // add to inventory
    {
        if (p.inventory[i] == "empty") {
            p.inventory[i] = r.item;
            p.inventoryitems++;
            cout << "You picked up the " << r.item << "!" << endl;
            r.item = "empty"; // empties out teh room 
            return;
        }
    }
}
void showinventory(player& p) // shows you hp and your items
{
    cout << "--- INVENTORY ---" << endl;
    cout << "Health: " << p.health << "%" << endl;
    cout << "Items: ";
    if (p.inventoryitems == 0) {
        cout << "(empty)";
    }
    else {
        for (int i = 0; i < inventoryMAX; i++) {
            if (p.inventory[i] != "empty") {
                cout << "[" << p.inventory[i] << "] ";
            }
        }
    }
    cout << endl;
}

int main()
{
    room dungeon[roomnum];  
    player player1;
    
    initialdungeon(dungeon);
    initialplayer(player1);

    cout << "ENTER YOUR NAME: ";
    cin >> player1.name;

    bool gamerunning = true;

    cout << "Welcome " << player1.name << " to the Dungeon Escape!" << endl;
    cout << "Commands: north, south, east, west, take, inventory, quit, attack, heal, look" << endl;

    bool showRoom = true;
    bool torch = true;

    while (gamerunning && player1.health != 0) // main game loop 
    {
        room &currentroom = dungeon[player1.roomindex]; // finds out where you are rn 

       
        

        if (showRoom == true)
        {
            printroom(currentroom);
            showRoom = false; // Stop it from printing next time!
        }

        if (currentroom.event == "trap")
        {
            cout << "YOU HAVE AWAKEN THE MICE! THEY HAVE ATTACKED YOU!" << endl;
            player1.health -= 25;
            cout << "You took 25 damage! Health is now: " << player1.health << endl;
            currentroom.event = "none"; // so that the trap doesnt trigger again
            if (player1.health <= 0) break; // nub. you are dead
        }
        if (currentroom.event == "fight")
        {
            cout << "You Stumble Upon an Ugly Troll... Prepare to Fight" << endl;
            string command;
            cout << "Enter Command, \"Attack\" to Fight, \"Quit\" to Exit" << endl;
            cin >> command;
            if (command == "quit" || command == "Quit")
            {
                break;
            }
            if (command == "attack" || command == "Attack") 
            {
                bool sword = false;
                for (int i = 0; i < inventoryMAX; i++)
                {
                    if (player1.inventory[i] == "sword")
                    {
                        sword = true;
                        cout << "You have Slain the boss";
                        currentroom.event = "none";
                    }
                    
                }
                if (sword == false)
                {
                    cout << "You Couldn't Defeat the Troll, You have Died!";
                    player1.health = 0;
                    break;
                }

            }
            
      
        }

        

        string command; // the commands used to control your character 
        cout << endl << "Enter Command: ";
        cin >> command;
        cout << endl;

        int direction = -1;
        if (command == "north")
        {
            direction = north;
            showRoom = true;
            
        }
        else if (command == "south")
        {
            direction = south;
            showRoom = true;
        }
        else if (command == "east")
        {
            direction = east;
            showRoom = true;
        }
        else if (command == "west")
        {
            direction = west;
            showRoom = true;
        }
            
        else if (command == "take") 
        {
            takeitem(player1, currentroom);
            showRoom = false;
            continue; 
        }
        else if (command == "inventory") {
            showinventory(player1);
            showRoom = false;
            continue;
        }
        else if (command == "quit") 
        {
            break;
        }
        else if (command == "heal")
        {
            bool medkit = false;
            for (int i = 0; i < inventoryMAX; i++)
            {
                if (player1.inventory[i] == "sword")
                {
                    medkit = true;
                    cout << "You Have Restored Your Health";
                    player1.inventory[i] = "empty";
                    player1.health = 100;
                    cout << "Your Health Now is " << player1.health;
                }
            }
            if (medkit == false)
            {
                cout << "You Don't Have a Medkit on You!";
            }
            showRoom = false;
        }
        else if (command == "look")
        {
            showRoom = true;
        }
        else {
            cout << "Unknown command." << endl;
            continue;
        }

        torch = false;
        for (int i = 0; i < inventoryMAX; i++)
        {
            
            if (player1.inventory[i] == "torch")
            {
                torch = true;
            }
            
        }
        if (torch == false)
            {
                cout << "You Cannot See in The Dark";
                direction = wall;

            }
        if (direction != -1) 
        {
            int nextRoomIndex = currentroom.exits[direction];

            if (nextRoomIndex == wall) 
            {
                cout << "You can't go that way." << endl;
            }
            else {
                // Check if the NEXT room is the Locked Exit
                if (dungeon[nextRoomIndex].event == "locked gate") {
                    if (hasitem(player1, "key")) {
                        cout << "You Insert The Golden Key..." << endl;
                        cout << "CLICK! The door opens!" << endl;
                        cout << "YOU ESCAPED THE DUNGEON! YOU WIN!" << endl;
                        gamerunning = false;
                    }
                    else {
                        cout << "The door is locked solid. You see a golden keyhole." << endl;
                        cout << "You need a key to pass." << endl;
                    }
                }
                else {
                    // Normal Move
                    player1.roomindex = nextRoomIndex;
                }
            }
        }
    }
    if (player1.health <= 0) {
        cout << "\n--- GAME OVER ---" << endl;
        cout << "You succumbed to the dangers of the dungeon." << endl;
    }
}