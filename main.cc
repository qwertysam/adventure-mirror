#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <memory>

#include "DungeonMap.h"
#include "BaseCharacter.h"
#include "CharacterDecorator.h"
#include "NullDecorator.h"
#include "DrowRace.h"
#include "GoblinRace.h"
#include "ShadeRace.h"
#include "TrollRace.h"
#include "VampireRace.h"
#include "BelungaRace.h"

#include "BoostAtkEffect.h"
#include "BoostDefEffect.h"

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

	// Initializes the random number generator
	srand(time(NULL));

	string input;
	string output;
	bool quit = false;

	while (!quit && cout << "Race selection ((s)hade, (d)row, (v)ampire, (g)oblin, (t)roll): " && cin >> input) {
		// race is one of (s, d, v, g, t)
		shared_ptr<CharacterDecorator> player;
		if (input == "d") {
			player = shared_ptr<CharacterDecorator>(new NullDecorator(shared_ptr<Character> (new DrowRace(0, 0))));
		}
		else if (input == "v") {
			player = shared_ptr<CharacterDecorator>(new NullDecorator(shared_ptr<Character> (new VampireRace(0, 0))));
	}
		else if (input == "g") {
			player = shared_ptr<CharacterDecorator>(new NullDecorator(shared_ptr<Character> (new GoblinRace(0, 0))));
		}
		else if (input == "t") {
			player = shared_ptr<CharacterDecorator>(new NullDecorator(shared_ptr<Character> (new TrollRace(0, 0))));
		}
		else if (input == "b") {
			player = shared_ptr<CharacterDecorator>(new NullDecorator(shared_ptr<Character> (new BelungaRace(0, 0))));
		}
		else { // default race
			player = shared_ptr<CharacterDecorator>(new NullDecorator(shared_ptr<Character> (new ShadeRace(0, 0))));
		}
        //set the random seed for random generation
        srand(time(NULL));
		const char *defaultMap = {"cc3kfloor.txt"};
		DungeonMap map{defaultMap, player, true};
		if (argc > 1) {
			map = DungeonMap(argv[1], player, false);
		}
		cout << map << endl;
		cout << "Action: Player character has spawned." << endl;
		// init map, enemies, items, etc here
		while (!player->deathCheck() && !map.wonGame() && cin >> input) {
			bool doTick = true;
			// main game loop
			if (input == "q") {
				quit = true;
				break;
			}
			else if (input == "u") {
				cin >> input;
				Direction d = Direction::getDirection(input);
				if (d == Direction::Invalid) {
					output = "Invalid direction. Please enter another command.";
					doTick = false;
				} else {
					output = "Action: ";
					map.playerPotion(d, output);
					output += ". ";
				}
			}
			else if (input == "a") {
				cin >> input;
				Direction d = Direction::getDirection(input);
				if (d == Direction::Invalid) {
					output = "Invalid direction. Please enter another command.";
					doTick = false;
				}
				else {
					map.playerAttack(d, output);
				}
				// player.attack(d);
			}
			else if (input == "f") {
				// toggles stopping enemies from moving
				// map.toggleStopEnemies()
				map.toggleFlag(map.MapFlags::EnemiesFrozen);
				if (map.getFlag(map.MapFlags::EnemiesFrozen)) {
					output = "Action: All enemies appear to be frozen to the arena floor and cannot move!";
				}
				else {
					output = "Action: All enemies have become unstuck from the arena floor and are itching to move!";
				}
				doTick = false;
			}
			else if (input == "r") {
				cout << "Restarting Game" << endl;
				// TODO make sure we manage memory of previous player and stuff
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
				output += "\nh: displays this message\n";
				output += "~~~~Debugging Commands~~~~\n";
				output += "v: validates the map\n";
				output += "cs: outputs character stats\n";
				output += "is: outputs item stats\n";
                output += "op: makes you overpowered\n";
				output += "super secret: try inputting 'b' in the race selection prompt";
				doTick = false;
			}
			else if (input == "v") {
				output = map.validate();
				doTick = false;
			}
			else if (input == "cs") {
				output = map.characterStats();
				doTick = false;
			}
			else if (input == "is") {
				output = map.itemStats();
				doTick = false;
			}
            else if (input == "op") {
                shared_ptr<CharacterDecorator> boostAtk;
                boostAtk = shared_ptr<CharacterDecorator>(new BoostAtkEffect());
                boostAtk->setActiveFloor(player->getFloor());
                boostAtk->setMultiplier(10);
                shared_ptr<CharacterDecorator> boostDef;
                boostDef = shared_ptr<CharacterDecorator>(new BoostDefEffect());
                boostDef->setActiveFloor(player->getFloor());
                boostDef->setMultiplier(10);
                player->decorate(boostAtk);
                player->decorate(boostDef);
                output = "You feel more overpowered than before!";
                doTick = false;
            }
			else {
				Direction d = Direction::getDirection(input);
				if (d == Direction::Invalid) {
					output = "Invalid command. Try 'h' (without quotes) for help on commands.";
					doTick = false;
				}
				else {
					doTick = map.playerMove(d, output);
				}
			}
			if (doTick) {
				map.tick(output);
			}
			cout << map << endl; // maybe this could go in map.tick?
			cout << output << endl;
			// map.tick
		}
		if (map.wonGame()) {
			cout << "Executing Command: sudo rm -rf /enemies --no-preserve-root" << endl;
			cout << "You beat the game! Score: " << player->score() << endl;
			cout << "Play again? (y/n): ";
			if (cin >> input && input == "y") {
				cout << "Restarting Game" << endl;
				// TODO: make sure we manage memory of previous player and stuff
			}
			else {
				break;
			}

        } else if (player->deathCheck()) {
			cout << "Oof, you died. Score: " << player->score() << endl;
			cout << "Play again? (y/n): ";
			if (cin >> input && input == "y") {
				cout << "Restarting Game" << endl;
				// TODO: make sure we manage memory of previous player and stuff
			}
			else {
				break;
			}
		}
	}
	cout << "Thank you for playing CC3K!" << endl;
}
