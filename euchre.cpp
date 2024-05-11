//
//  euchre.cpp
//  p3-euchre
//
//  Created by Bends on 5/9/24.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

static void Euchre_print_failure();

int main(int argc, char *argv[]) {
    string error = "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4\n";

    if (argc == 12) {
        if (strcmp("euchre.exe", argv[0])) {
            Euchre_print_failure();
        }
        string filename = argv[1];
        ifstream fin;
        fin.open(filename.c_str());
        if (!fin.is_open()) {
            // Assume pack_filename is a variable containing
            // the specified pack filename from argv
            cout << "Error opening " << filename << endl;
        }
        if (strcmp("shuffle", argv[2]) && strcmp("noshuffle", argv[2])) {
            Euchre_print_failure();
        }
        if ((atoi(argv[3]) > 100 || atoi(argv[3]) < 1)) {
            Euchre_print_failure();
        }
        for (int i = 5; i < 12; i = i+2) {
            if (strcmp(argv[i], "Human") && strcmp(argv[i], "Simple")) {
                Euchre_print_failure();
            }
        }
    }
    else {
        cout << error;
    }
    
    cout << "
    //Game game(__________________________);
    //game.play();
    
    
    
}

static void Euchre_print_failure()
{
    cout << "Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 NAME2 NAME3 NAME4" << endl;

    exit(EXIT_FAILURE);
}
