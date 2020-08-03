#include "Tests.h"

int main() {

	bool res{ true };
	
	res &= test_acculmulate();
	res &= test_max_element();
	res &= test_min_element();
	//res &= test_all_of();
	//res &= test_any_of();

	return (res ? 0 : -1);

}