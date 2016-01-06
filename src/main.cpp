#include "linearRegression.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

//
// Non-Blocking GetLine:
//    Gets a line of characters from a stream, until it finds a delimiter or the timeout passes
//
void nb_getline(std::istream& in, std::string& str,
                char delim = '\n', unsigned timeout = 3) {
    std::stringstream ss;
    char c = 0;

    // Timeout needs to be incremented +1, 'cause 0 does not count
    if (timeout + 1 != 0) timeout++;

    // Read characters while we do not found delimiter or we run out of time
    while ( timeout > 0 && c != delim ) {
        // Get next character (instream should be non-blocking!)
        in.clear();
        in.get(c);

        if (!in.eof()) {
            // Next character found, put it in provisional stream
            if (c != delim) ss << c;
        } else if (ss.str().length() > 0) {
            // Found eof, and we are in the middle of the line
            while (in.eof() && ss.str().length() > 0 && timeout > 0) {
                // Sleep 1 millisecond and try again
                usleep(1000);
                in.clear();
                timeout--;
            }

        // Nothing ready to be read, let's exit
        } else break;
    }

    str = ss.str();
}

int
main(void){
    // Trainning
	Trainning_Set train("train.csv");
	LinearReg reg(train.get_dim(),0.00000001);
	//train.normalize();
	reg.normal_equation(train);

    std::string s = "", subs;

    // Wait for INITIALIZE command
    while (s != "INITIALIZE") {
      nb_getline(std::cin, s);
      usleep(200000);      // Sleep for 0.2 seconds (5 times per second)
    }

    // Register into the match
    std::stringstream ss;
    srand(time(NULL));
    ss << "ply" << 1;//rand() % 1000;
    std::cout << "REGISTER " << ss.str() << std::endl;

    // Wait for START command
    subs = "";
    do {
      nb_getline(std::cin, s);
      if (s.length() > 5) {
        subs = s.substr(0, 5);
        std::cerr << "SUBSTR: [" << subs << "]\n";
      }
      usleep(200000);      // Sleep for 0.2 seconds (5 times per second)
    } while (subs != "START");

    // Interpret START command
    ss.clear(); ss.str(s);
    unsigned mode, duration, candletime;
    double initfiat;
    ss >> s >> mode >> duration >> candletime >> initfiat;
    std::cerr << "START " << mode << duration << candletime << initfiat;

    // Until the end of the simulation, BUY and SELL
    while (s != "END") {
        nb_getline(std::cin, s);
        if (s != "")
            std::cerr << "Recibido: (" << s << ")" << std::endl;
        //sendRandomCommand();
        usleep(50000);      // Sleep for 0.05 seconds (20 times per second)
    }

	return 1;
}
