bool test_acculmulate();
bool test_max_element();

int main() {

	bool res{ true };
	
	res &= test_acculmulate();
	res &= test_max_element();

	return (res ? 0 : -1);

}