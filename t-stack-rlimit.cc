
#include <sys/resource.h>
#include <iostream>
using  namespace std;


int main(int argc, char *argv[]) {

	struct rlimit *rlim;
	getrlimit(RLIMIT_STACK, rlim);
		cout << "cur=" << rlim->rlim_cur << endl;
		cout << "max=" << rlim->rlim_max << endl;

	{
	struct rlimit new_rlim = {rlim->rlim_max, rlim->rlim_max};
	int rc= setrlimit(RLIMIT_STACK, &new_rlim);
		cout << "rc=" << rc << endl;
	}

	getrlimit(RLIMIT_STACK, rlim);
		cout << "cur=" << rlim->rlim_cur << endl;
		cout << "max=" << rlim->rlim_max << endl;

	return 0;
}
