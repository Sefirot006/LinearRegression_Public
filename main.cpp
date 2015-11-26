#include <cgame.h>
#include <cfiredoor.h>
#include <iostream>
#include <list>
#include <utility>
#include <cmath>
#include <string>

using namespace FireDoorEscaper;
using namespace std;

int num_learn;

// Print Game Status Values
bool
printGameStatus(const CGame& g) {
    const CFireDoor& fd = g.getCurrentFireDoor();
    const CFireDoor::TVecDoubles& inp = fd.getNextStepInputs();
    std::cout   << "Lvl: " << g.getLevel()
                << " | Steps: " << g.getSteps()
                << " | Score: " << g.getScore()
                << " | Door: " << g.getDoorsPassed() + 1
                << " | DSteps: " << fd.getSteps()
                << " | OnFire?: " << ((fd.isOnFire()) ? "yes" : "no")
                << std::endl
                << "=========================================================================\n"
                << "Next Inputs: [ ";
    for (unsigned i=0; i < inp.size(); i++)
        std::cout << inp[i] << " ";
    std::cout << "] \n";
    return fd.isOnFire();
}

void printList(list<pair<CFireDoor::TVecDoubles,bool> >& lista){
	for(pair<CFireDoor::TVecDoubles,bool> p:lista){
		for(unsigned i=0;i<p.first.size();++i)
			cout << p.first[i] <<" ";
		cout << "\t"<< p.second << endl;
	}
}

void
insert(CGame* g,list<pair<CFireDoor::TVecDoubles,bool> >& lista){
	const CFireDoor& fd=g->getCurrentFireDoor();

	if(lista.size()>0)
		lista.back().second=fd.isOnFire();
	lista.push_back(std::make_pair(fd.getNextStepInputs(),true));
}


void
learnFunc(CGame* g,list<pair<CFireDoor::TVecDoubles,bool> >& lista) {

	if(lista.size()<num_learn){
		for(unsigned i=0;i<num_learn;++i){
			//printGameStatus(*g);
			insert(g,lista);
			g->nextStep();
		}
	}
	printList(lista);
}

int
main(int argc,char** argv) {
	int level=0;
	if(argc<2 || argc >3){
		cerr << "Incorrect number of arguments (2)" << endl
			<< "./main <num_examples_learning> [level=0]" << endl;
		return 0;
	}else if(argc==3)
		level=stoi(argv[2]);
	num_learn=stoi(argv[1]);

	list<pair<CFireDoor::TVecDoubles,bool> > lista;
	// Create a new game starting at level 0, and staying at the same level all the time.
	// Use GDM_LEVELUP for increasing level of difficulty
	CGame *game = new CGame(level);
	game->setGameDifficultyMode(CGame::GDM_LEVELUP);

	// Main loop: stay will the game is on (i.e. the player is alive)
	while (game->getGameStatus() == CGame::GS_PLAYING) {
		// Do some game steps and print values

		/*for (unsigned i=0; i < 20; i++) {
		    //printGameStatus(*game);
		    game->nextStep();
		}*/
		lista.clear();
		learnFunc(game,lista);

		// Try to cross the current FireDoor
		printGameStatus(*game);

		std::cout << "**** TRYING TO CROSS THE DOOR ****\n";
		game->crossFireDoor();
		if (game->getGameStatus() != CGame::GS_PLAYING)
		    std::cout << "!!!!!!!!!!! PLAYER GOT BURNED OUT !!!!!!!!!!!!!!\n";
		else
		    std::cout << "****** DOOR PASSED *****\n";
	}

	// Game Over
	delete game;
	return 1;
}
