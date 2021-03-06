#include "ARG.h"


void UpString(char *str, char **out){ //Input string 'str', the result is an uppercase string in 'out'
	int i = 0;
	*out = strdup(str);
	while(str[i]){
		*out[i] = (char)toupper(str[i]);
		i++;
	}
}

void ReadFile (char *filename, int N, bool similarity_out){
	char c;
	int i;
	time_t t1, t2;
	t1 = time(NULL);
	std::vector<int> x;

	//Open the file with scrm output
//	int N = 100; //Find the number of haplotypes in the file, e.g. from the first line as it is of the form "scrm NUMBER_OF_HAPLOTYPES ........."
	std::cout << "Reading from " << filename << ". File contains " << N << " samples." << std::endl;
	Argentum ARG(N);//construct ARG class with N haplotypes
	for (i = 0; i < ARG.GetSize(); i++)//initialise vector of length N
		x.push_back(0);
	
	ifstream myfile(filename);

	char first;

	if ( !myfile.is_open()) {
		cerr << "There was an error opening the input file " << filename << "." << endl;
		exit(1);
	}

	int siteNum = 0;
	int j = 0;
	bool is_snp = false;
	while(myfile.get(first)){
		if (first == '\n'){
			ARG.SetSiteNumber(siteNum);
			if (i == -1) {
				ARG.PrintTreeForTest(x);
			}
			if (is_snp)
				ARG.FeedSite(x);
			ARG.PrintTree(similarity_out);
			siteNum++;
			j = 0;
			is_snp = false;
			continue;
		}
		x[j] = first - '0';
		if (x[j] == 1)
			is_snp = true;
		j++;
	}

/*	for (i=0; i<numLines; i++){
		for (int j=0; j<N; j++) {
			myfile.get(first); //read symbol
			x[j] = first - '0'; //convert char into int			
			
		}
		myfile.ignore(1);
		
		
		ARG.SetSiteNumber(i);
		if (i == -1) {
			ARG.PrintTreeForTest(x);
		} 
		ARG.FeedSite(x);
	}*/
	cout << "Reading Complete. " << std::endl;
	myfile.close();
}

void Argentum::PrintTree(bool similarity){
	double maxVal;
//	std::cout << "Tree with " << M << " leaves." << std::endl;
	for (int i = 0; i <M; i++){
		std::cout << a[i];
		if (i != M-1)
			std::cout << ",";
	}
	std::cout << std::endl;
	if (not similarity)
		maxVal = *std::max_element(d+1, d+M-1);
	for (int i = 1; i <M; i++){
		if (similarity)
			std::cout << d[i];
		else
			std::cout << maxVal + 1 - d[i];
		if (i != M-1)
			std::cout << ",";
	}
	std::cout << std::endl;
//	std::cout << std::endl;
//		std::cout << i << '\t' << d[i] << '\t' << a[i] << std::endl;
}

void Argentum::PrintReducedTree(){
	int i;
	std::cout << "Reduced tree with " << rM << " leaves." << std::endl;
	for (i = 0; i < rM; i++)
		std::cout << i << "\t" << rd[i] << "\t L = " << rPack[i].el[0] << ", R = " << rPack[i].el[1] << ", val = " << rPack[i].el[2] << ", node = " << rPack[i].el[3] << std::endl;
}

void Argentum::PrintReducedTree1(){
	int i;
	std::cout << "Reduced tree with " << rM1 << " leaves." << std::endl;
	for (i = 0; i < rM1; i++)
		std::cout << i << "\t" << rd1[i] << "\t L = " << rPack1[i].el[0] << ", R = " << rPack1[i].el[1] << ", val = " << rPack1[i].el[2] << ", node = " << rPack1[i].el[3] << std::endl;
}
