/****************************************************
* Executable:   Linear_hash_table

*
*
* DO NOT EDIT THIS FILE
*
* Create an instance of the Double_hash_table_tester class
* and call the member function run().
*
* The member function run() will interpret the
* input appropriately and exit when the interpreter
* receives either the command 'exit' or and
* end-of-file.
****************************************************/

#include <iostream>
#include "Linear_hash_table_tester.h"

int main() {
	Linear_hash_table_tester<int> tester;

	std::cout << "Starting Test Run" << std::endl;

	tester.run();

	std::cout << "Finishing Test Run" << std::endl;

	return 0;
}