#include <cgame.h>
#include <cfiredoor.h>
#include <string>
#include <iostream>
#include <trainningSet.h>
#include <logRegression.h>

using namespace FireDoorEscaper;
using namespace std;

// Print Game Status Values
void
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
}

int
main(int argc,char** argv) {
    //Algorithm::Trainning_Set train;
    vector<string> trainningVector;
    double confianza = 0.4;
    //char* aa;
    //Algorithm::Trainning_Set train(aa);
    // Create a new game starting at level 0, and staying at the same level all the time.
    // Use GDM_LEVELUP for increasing level of difficulty
    CGame *game = new CGame(0);
    game->setGameDifficultyMode(CGame::GDM_SAMELEVEL);

    

    // Main loop: stay will the game is on (i.e. the player is alive)
    while (game->getGameStatus() == CGame::GS_PLAYING) {
        const CFireDoor& fd = game->getCurrentFireDoor();
        // Do some game steps and print values
        /*for (unsigned i=0; i < 5; i++) {
            printGameStatus(*game);
            game->nextStep();
        }*/

        for(unsigned i=0;i<20;i++){
            string str;
            // Get next input
            const CFireDoor::TVecDoubles& inp = fd.getNextStepInputs();
            for (unsigned i=0; i < inp.size(); i++){
                double aa = inp[i];
                str += to_string(aa) + ",";
            }

            // Let pass a door
            game->nextStep();

            const CFireDoor& fd = game->getCurrentFireDoor();

            str += to_string(fd.isOnFire());
            cout << str << endl;

            trainningVector.push_back(str);

        }
        Algorithm::Trainning_Set train(trainningVector);
        //cout << train << endl;
        /*for(unsigned i=0;i<train.size();++i){
            cout << i << endl;
            for(unsigned j=0;j<=train.get_dim();++j){
                cout << train.get_x(i,j) << ",";
            }
            cout << train.get_y(i);
            cout << endl;
        }*/

        Algorithm::LogRegression logRegression(train.get_dim(),0.01);
        cout << "ANTES DE LA NORMALIZACION EL TRAIN" << endl;
        cout << train << endl;
        train.normalize();
        cout << "despues de normailzar" << endl;
        cout << train << endl;
        
        //int kk;
        //cin >> kk;
        logRegression.train(train);

        double* aa;
        aa = logRegression.getTheta();
        cout << "pesos: ";
        for(unsigned j=0;j<=train.get_dim();j++){
            cout << aa[j] << ",";
        }
        cout << endl;
        
        std::cout << "**** TRYING TO CROSS THE DOOR ****\n";
        vector<double> inputsDoor;

        unsigned contador = 0;
        //Con 0 en fire no estara quemando la puerta
        do{
            /*contador++;
            if(contador > 500){
                contador = 0;
                confianza = 0.4;
            }*/
            // Let pass a door
            game->nextStep();
            const CFireDoor& fd = game->getCurrentFireDoor();
            inputsDoor.clear();
            const CFireDoor::TVecDoubles& inp = fd.getNextStepInputs();
            string str;
            //vector<string> trainningVector;
            for (unsigned i=0; i < inp.size(); i++){
                double aa = inp[i];
                str += to_string(aa) + ",";
            }
            cout << "input: ";
            for (unsigned i=0; i < inp.size(); i++)
                std::cout << inp[i] << " ";
            cout << endl;
            
            //es para la salida, este valor se ignorara
            str+="1";
            trainningVector.push_back(str);
            //str = "1,1";
            //trainningVector.push_back(str);
            //cout <<"aaaaaaaaaaaaBefore: " << train.size() << endl;
            Algorithm::Trainning_Set train(trainningVector);
            //cout << " train: " << train.get_x(0,1) << endl;
            //cout << " train Salida: " << train.get_y(0) << endl;
            train.normalize();

            cout << "input normalizado: ";
            for(int i=0;i<=train.get_dim();++i){
                cout << train.get_x(train.size()-1,i) << ",";
            }
            cout << endl;

            int kk;
            cin >> kk;

            for(int i=0;i<=train.get_dim();++i){
                inputsDoor.push_back(train.get_x(train.size()-1,i));    
            }
            
            //cout << "str: " << str << endl;
            /*cout << "inputsDoor: ";
            for(unsigned i=0;i<inputsDoor.size();i++){
                cout << inputsDoor[i] << ",";
            }
            cout << endl;*/
            //cout <<"aaaaaaaaaaaaAfter: " << train.size() << endl;
            //cout << "VALOR: " << logRegression.evaluate(inputsDoor) << endl;

            //int kk;
            //cin >> kk;
            if(logRegression.evaluate(inputsDoor)>confianza){
                //cout << "last: " << train.get_x(train.size()-1,1) << endl;
                train.delete_last();
                //cout << "last: " << train.get_x(train.size()-1,1) << endl;
            }
            /*if(contador==500){
                cout << "excedido" << endl;
                //contador = 0;
                //break;
                confianza+=0.1;
            }*/

        }while(logRegression.evaluate(inputsDoor)>confianza);
        game->crossFireDoor();
        
        if (game->getGameStatus() != CGame::GS_PLAYING)
            std::cout << "!!!!!!!!!!! PLAYER GOT BURNED OUT !!!!!!!!!!!!!!\n";
        else
            std::cout << "****** DOOR PASSED *****\n";
        //double* pesos;
        //pesos = logRegression.getTheta();
        //double h = logRegression.evaluate();
        //cout << "pesos: " << pesos[0] << "," << pesos[1] << endl;
        /*for (unsigned i=0; i < 5; i++) {
            printGameStatus(*game);
            game->nextStep();
        }*/
        //int kk;
        //cin >> kk;

        // Try to cross the current FireDoor
        printGameStatus(*game);
        
        
    }

    // Game Over
    delete game;
    return 1;
}
