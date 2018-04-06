
#include<bits/stdc++.h>
using namespace std;

#define ll long long     
  
void naive(string pattern, string text)
{
   //get the length of both arrays
    ll pLength = pattern.length();
    ll tLength = text.length();
   
   
    
    for (ll i = 0; i <= tLength - pLength; i++)
    {
        ll j;
   
        /* Starting comparison */
        for (j = 0; j < pLength; j++)
            if (text[i+j] != pattern[j])
                break;
  
        /*If there is no more character left in pattern
to compare. */
        if (j == pLength)  
          std::cout<<"Pattern found after shift "<< i<<endl;
    }
}
   
int main(int argc, char **argv){
    clock_t tStart = clock();
    if( argc <= 1 ){
    std::cerr << "Usage: "<<argv[0]<<" [infile]" << std::endl;
    return -1;
    }
 
    std::ifstream input(argv[1]);
    if(!input.good()){
        std::cerr << "Error opening '"<<argv[1]<<"'. Bailing out." << std::endl;
        return -1;
    }
 
    std::string line, name, content;
    while( std::getline( input, line ).good() ){
        if( line.empty() || line[0] == '>' ){ // Identifier marker
            if( !name.empty() ){ // Print out what we read from the last entry
                std::cout << name << " : " << content << std::endl;
                name.clear();
            }
            if( !line.empty() ){
                name = line.substr(1);
            }
            content.clear();
        } else if( !name.empty() ){
            if( line.find(' ') != std::string::npos ){ // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            } else {
                content += line;
            }
        }
    }
	string arr[] = {"TAGA", "TCAT", "GAAT","AGAT","AGAA","GATA","TATC","CTTT","TCTG","TCTA"};
	ll prime=101;
    for(ll i=0;i<10;i++){
    	naive(arr[i],content);
    }
	
    cout<<"Execution Time = "<<((double)(clock() - tStart)/CLOCKS_PER_SEC)<<endl;
}