#include <iostream>
#include "Main.h"


int main() {
    std::cout << "Hello" << std::endl;
	// initialize the database
	Database::initialize();

	// This logic is highly simplified based on iteration 1 requirements and 
	// the assumption that the programs are valid.
	string procedureName = "User";

	// insert the procedure into the database
	Database::insertProcedure(procedureName);

    return 0;
}