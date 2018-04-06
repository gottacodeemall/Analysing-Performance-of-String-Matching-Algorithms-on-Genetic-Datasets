#include<bits/stdc++.h>
using namespace std;
 
#define d 256
#define ll long long 
 
void rabin(string txt,string pat,ll prime){
	ll plen=pat.length(),tlen=txt.length();
	ll p=0,t=0;
	for(ll i=0;i<plen;i++){
		p = (d*p + pat[i])%prime;
        t = (d*t + txt[i])%prime;
	}
	//cout<<p<<" "<<t<<endl;
	ll h=pow(d,plen-1);
	h=h%prime;
	if(h<0){
	    h+=prime;
	}
	for (ll i = 0; i <= tlen - plen; i++)
    {
        if ( p == t )
        {
            ll j;
            for ( j = 0; j < plen; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
            if (j == plen)
                cout<<"Pattern found at index "<<i<<endl;
        }
        if ( i < tlen - plen )
        {
            t = (d*(t - txt[i]*h) + txt[i+plen])%prime;
            if (t < 0)
            t = (t + prime);
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
	ll prime=101;
    for(ll i=0;i<10;i++){
    rabin(content,arr[i],prime);
    }
	
    cout<<"Execution Time = "<<((double)(clock() - tStart)/CLOCKS_PER_SEC)<<endl;
}