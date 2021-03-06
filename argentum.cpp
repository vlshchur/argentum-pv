/*(c) Vladimir Shchur, Wellcome Trust Sanger Institute, 2015*/
#include "ARG.h"

void PerformTest(){
	int i;
//	int xa[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
	int xa[] = {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0};
	std::vector<int> x;
//	double da[] = {0, 4, 3, 5, 2, 3, 5, 4, 1, 2};
	double da[] = {0, 5, 4, 3, 4, 2, 5, 5, 1, 4, 4, 4};
	std::vector<double> dFunc;
	int len = sizeof(xa)/sizeof(xa[0]);
    if (len != sizeof(da)/sizeof(da[0]) ){
        std::cout << "Test cannot be run: test arrays' lengths are non-equal." << std::endl;
		exit (EXIT_FAILURE);
	}
	for (i = 0; i < len; i++){
		x.push_back(xa[i]);
		dFunc.push_back(da[i]);
	}
//	int x[] = {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1};
//	double dFunc[] = {0, 4, 4, 3, 4, 4, 2, 5, 4, 4, 5, 3, 5, 4, 5, 4, 5, 4, 5, 1, 4, 2, 5, 3, 6, 5, 3, 3, 5, 6, 3, 5, 6};
	std::cout << "Perform test." << std::endl;
    Argentum ARG (len);
	ARG.SetTree(dFunc);
    ARG.FeedSite(x);
	ARG.PrintTree();
}
    
void Help(){
    std::cout << "Help: to be developed." << std::endl;
}

int main(int argc, char *argv[]){
/*	PerformTest();
	return 1;*/
	if (argc < 3){
		cout << "Missing input file and number of haplotypes in the file. Example:\n\t./argentum input.dat 100." << endl;
		return 1;
	}
	bool similarity_out = true;
	if (argc == 4){
		std::string par = argv[3];
		if ( par == "-d")
			similarity_out = false;
	}
	
	ReadFile(argv[1], atoi(argv[2]), similarity_out);
	return 0;
}
