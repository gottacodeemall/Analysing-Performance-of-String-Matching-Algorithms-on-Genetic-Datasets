//eg: txt: AAAAABAAABA pat: AAAA

#include<bits/stdc++.h>
using namespace std;
#define ll long long 

void preprocess(string pat,ll *lps){
	//eg: ACACB
	//
	ll plen=pat.length();
	//finding the longest proper prefix and suffix for every index of pattern an dstore it in lps.
	lps[0]=0;
	ll i=1;
	ll len=0;
	//len stores the lps of the previous index
	while(i<plen){
		if(pat[i]==pat[len]){
			len++;
			lps[i]=len;
			i++;
		}
		else{
			if(len==0){
				lps[i]=0;
				i++;
			}
			else{
				len=lps[len-1];
			}
		}
	}
}


void KMP(string txt,string pat){
	ll plen=pat.length(),tlen=txt.length();
	ll lps[plen];
	preprocess(pat,lps);
	for(ll i=0;i<plen;i++){
		cout<<lps[i]<<" ";
	}
	cout<<endl;
	ll i=0,j=0;
	while(i<tlen){
		if(pat[j]==txt[i]){
			i++;
			j++;

		}

		if(j==plen){
			cout<<"Found pattern at index "<<i-j<<endl;
			j=lps[j-1];
			//inceremented j find lps at the pattern found index and continue
		}
		else if(i<tlen && pat[j]!=txt[i]){
			if(j!=0){
				j=lps[j-1];
			}
			else{
				i++;
			}
		}
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
    for(ll i=0;i<10;i++){
    	KMP(content,arr[i]);
    }
    cout<<"Execution Time = "<<((double)(clock() - tStart)/CLOCKS_PER_SEC)<<endl;
	return 0;
}
