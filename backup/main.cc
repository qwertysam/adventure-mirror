#include <string>
#include <iostream>

#include "DungeonMap.h"
#include "BaseCharacter.h"
#include "CharacterDecorator.h"
#include "DrowRace.h"
#include "GoblinRace.h"
#include "ShadeRace.h"
#include "TrollRace.h"
#include "VampireRace.h"

using namespace std;

int main(int argc, char *argv[]) {
    /* Initially, the game will demand the player enter one of the specifed races or quit. Entering `q' or EOF (e.g.
    Ctrl-D) at the race prompt will cause the program to terminate. Supplying a valid race selection (below)
    will start that game using that race. Other values will be ignored.
    Play will continue in the specified way until the player restarts, reaches the end of floor 5, the PC dies,
    or the player quits. If the player reaches the end of the game or their character is slain, the game should
    give them the option of playing again or quitting.

    The following commands can be supplied to your command interpreter:
    * no,so,ea,we,ne,nw,se,sw: moves the player character one block in the appropriate cardinal direction.
    * u <direction>: uses the potion indicated by the direction (e.g. no, so, ea).
    * a <direction>: attacks the enemy in the specified direction, if the monster is in the immediately
    specified block (e.g. must be one block north of the @).
    * s, d, v, g, t: specifies the race the player wishes to be when starting a game.
    * f: stops enemies from moving until this key is pressed again.
    * r: restarts the game. All stats, inventory, and gold are reset. A new race should be selected.
    * q: allows the player to admit defeat and exit the game.
    Note that the board should be redrawn as appropriate every time a command is entered.*/

    string input;
    string output;
    bool quit = false;

    cout << "Race selection ((s)hade, (d)row, (v)ampire, (g)oblin, (t)roll): ";
    while (!quit && cin >> input) {
        // race is one of (s, d, v, g, t)
        CharacterDecorator *player = nullptr;
        if (input == "d") {
            player = new CharacterDecorator(new DrowRace(0, 0));
        }
        else if (input == "v") {
            player = new CharacterDecorator(new VampireRace(0, 0));
        }
        else if (input == "g") {
            player = new CharacterDecorator(new GoblinRace(0, 0));
        }
        else if (input == "t") {
            player = new CharacterDecorator(new TrollRace(0, 0));
        }
        else { // default race
            player = new CharacterDecorator(new ShadeRace(0, 0));
        }

        const char *defaultMap = {"cc3kfloor.txt"};
        DungeonMap map{defaultMap, player};
        if (argc > 1) {
            map = DungeonMap(argv[1], player);
        }
        cout << map << endl;
        cout << "Action: Player character has spawned." << endl;
        // init map, enemies, items, etc here
        while (cin >> input) {
            bool doTick = true;
            // main game loop
            if (input == "q") {
                cout << "Thank you for playing CC3K!" << endl;
                quit = true;
                break;
            }
            else if (input == "u") {
                // yeah we might want to make a helper function to get direction
                // Direction d;
                // cin >> d;
                // player.use(d);
                output = "Action: PC uses [AB].";
            }
            else if (input == "a") {
                // Direction d;
                // cin >> d;
                // player.attack(d);
                output = "Action: PC deals x damage to Y (123 HP). Y deals z damage to PC.";
            }
            else if (input == "f") {
                // toggles stopping enemies from moving
                // map.toggleStopEnemies()
                output = "Action: All enemies appear to be frozen to the arena floor and cannot move!";
            }
            else if (input == "r") {
                cout << "Restarting Game" << endl;
                // make sure we manage memory of previous player and stuff
                cout << "Race selection (Shade, Drow, Vampire, Goblin, Troll): ";
                break;
            }
            else if (input == "h") {
                output = "~~~~ChamberCrawler 3000 Commands~~~~\n";
                output += "(no)rth, (so)uth, (ea)st, (we)st, ne, nw, se, sw: movement\n";
                output += "u <direction>: uses potion in specified cardinal direction\n";
                output += "a <direction>: attacks enemy one block away in specified direction\n";
                output += "f: toggles enemy movement (but not attacking)\n";
                output += "r: restarts the game\n";
                output += "q: quits the game\n";
                output += "\nh: displays this message";
                doTick = false;
            }
            else {
                Direction d = Direction::getDirection(input);
                if (d == Direction::Invalid) {
                    output = "Invalid command. Try 'h' (without quotes) for help on commands.";
                    doTick = false;
                }
                else {
                    map.movePlayer(d, output);
                }
            }
            if (doTick) {
                map.tick(output);
            }
            cout << map << endl; // maybe this could go in map.tick?
            cout << output << endl;
            // map.tick
        }
    }
}