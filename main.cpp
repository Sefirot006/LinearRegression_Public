#include <cgame.h>
#include <cfiredoor.h>
#include <iostream>
#include <list>
#include <utility>
#include <cmath>
#include <string>

using namespace FireDoorEscaper;
using namespace std;

int alpha;
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
		//lista.back().second=fd.isOnFire();
		lista.back().second=g->getCurrentFireDoor().isOnFire();
	}
	printList(lista);
}

/*
bool
getDecision(CGame* g,list<pair<CFireDoor::TVecDoubles,bool> >& lista) {
	double theta_0 = 0;
	double theta_1 = 0;
	double temp_0, temp_1;
	double aux_0,  aux_1;
	double intParentSum;

	mientras no hay convergencia { (aux_0 != 0)	//No necesitamos aux_N
		for (elementos lista) {
			THETA 0

			h_0(x_i) -> elem_i.fire
			temp_0 =

			THETA 1
			h_0(x_i) -> elem_i.fire
			*x
			temp_1 =
		}

		realizar cálculos de fuera de sumatorio



		actualizar thetas.
			theta_0 = temp_0;
			theta_1 = temp_1;
	}

}
*/

bool
getDecision(CGame* g,list<pair<CFireDoor::TVecDoubles,bool> >& lista) {
	double theta_0 = 0;
	double theta_1 = 0;
	double temp_0, temp_1;

	//mientras no hay convergencia.
	while (temp_0 != 0){ //No necesitamos aux_N
		temp_0=temp_1=0;
		//for (elementos lista) {
		for (list<pair<CFireDoor::TVecDoubles,bool> >::const_iterator it=lista.begin();it!=lista.end();it++){
			// sum( h(x_i)+y_i )
			temp_0 += (theta_0*(it->first[0]) + theta_1) - it->second;
			// sum( h(x_i)+y_i )
			temp_1 += ((theta_0*(it->first[0]) + theta_1) - it->second)*(it->first[0]);
		}
		//actualizar thetas.
		theta_0 = theta_0 - (alpha/num_learn)*temp_0;
		theta_1 = theta_1 - (alpha/num_learn)*temp_1;
	}

}

int
main(int argc,char** argv) {
	int level=0;
	if(argc<3 || argc >4){
		cerr << "Incorrect number of arguments (2)" << endl
			<< "./main <num_examples_learning> <alpha>[level=0]" << endl;
		return 0;
	}else if(argc==4){
		level=stoi(argv[3]);
	}
		alpha=stoi(argv[2]);
	num_learn=stoi(argv[1]);

	list<pair<CFireDoor::TVecDoubles,bool> > lista;
	// Create a new game starting at level 0, and staying at the same level all the time.
	// Use GDM_LEVELUP for increasing level of difficulty
	CGame *game = new CGame(level);
	game->setGameDifficultyMode(CGame::GDM_LEVELUP);

	// Main loop: stay will the game is on (i.e. the player is alive)
	while (game->getGameStatus() == CGame::GS_PLAYING) {
		// Do some game steps and print values /*for (unsigned i=0; i < 20; i++) {//printGameStatus(*game); game->nextStep();}*/
		lista.clear();
		// Get some data of the doors to learn.
		learnFunc(game,lista);

		// Get decision.
		while (getDecision(game,lista)) {
			//**** AVOIDING TO CROSS THE DOOR ****
            std::cout << "**** AVOIDING TO CROSS THE DOOR ****\n";
            game->nextStep();
		}

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
