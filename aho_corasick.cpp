using namespace std;
#include <bits/stdc++.h>
#define ll long long 
// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
const ll MAXS = 500;
 
// Maximum number of characters in input alphabet
const ll MAXC = 26;
 
// Bit i in this mask is one if the word with index i
// appears when the machine enters this state.
ll out[MAXS];
 
// FAILURE FUNCTION IS IMPLEMENTED USING f[]
ll f[MAXS];
 
// GOTO FUNCTION (OR TRIE) IS IMPLEMENTED USING g[][]
ll g[MAXS][MAXC];
 
// Builds the string matching machine.
// arr -   array of words. The index of each keyword is important:
//         "out[state] & (1 << i)" is > 0 if we just found word[i]
//         in the text.
// Returns the number of states that the built machine has.
// States are numbered 0 up to the return value - 1, inclusive.
ll buildMatchingMachine(string arr[], ll k)
{
    // Initialize all values in output function as 0.
    memset(out, 0, sizeof out);
 
    // Initialize all values in goto function as -1.
    memset(g, -1, sizeof g);
 
    // Initially, we just have the 0 state
    ll states = 1;
 
    // Construct values for goto function, i.e., fill g[][]
    // This is same as building a Trie for arr[]
    for (ll i = 0; i < k; ++i)
    {
        const string &word = arr[i];
        ll currentState = 0;
 
        // Insert all characters of current word in arr[]
        for (ll j = 0; j < word.size(); ++j)
        {
            ll ch = word[j] - 'A';
 
            // Allocate a new node (create a new state) if a
            // node for ch doesn't exist.
            if (g[currentState][ch] == -1)
                g[currentState][ch] = states++;
 
            currentState = g[currentState][ch];
        }
 
        // Add current word in output function
        out[currentState] |= (1 << i);
    }
 
    // For all characters which don't have an edge from
    // root (or state 0) in Trie, add a goto edge to state
    // 0 itself
    for (ll ch = 0; ch < MAXC; ++ch)
        if (g[0][ch] == -1)
            g[0][ch] = 0;
 
    // Now, let's build the failure function
 
    // Initialize values in fail function
    memset(f, -1, sizeof f);
 
    // Failure function is computed in breadth first order
    // using a queue
    queue<ll> q;
 
     // Iterate over every possible input
    for (ll ch = 0; ch < MAXC; ++ch)
    {
        // All nodes of depth 1 have failure function value
        // as 0. For example, in above diagram we move to 0
        // from states 1 and 3.
        if (g[0][ch] != 0)
        {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }
 
    // Now queue has states 1 and 3
    while (q.size())
    {
        // Remove the front state from queue
        ll state = q.front();
        q.pop();
 
        // For the removed state, find failure function for
        // all those characters for which goto function is
        // not defined.
        for (ll ch = 0; ch <= MAXC; ++ch)
        {
            // If goto function is defined for character 'ch'
            // and 'state'
            if (g[state][ch] != -1)
            {
                // Find failure state of removed state
                ll failure = f[state];
 
                // Find the deepest node labeled by proper
                // suffix of string from root to current
                // state.
                while (g[failure][ch] == -1)
                      failure = f[failure];
 
                failure = g[failure][ch];
                f[g[state][ch]] = failure;
 
                // Merge output values
                out[g[state][ch]] |= out[failure];
 
                // Insert the next level node (of Trie) in Queue
                q.push(g[state][ch]);
            }
        }
    }
 
    return states;
}
 
// Returns the next state the machine will transition to using goto
// and failure functions.
// currentState - The current state of the machine. Must be between
//                0 and the number of states - 1, inclusive.
// nextInput - The next character that enters into the machine.
ll findNextState(ll currentState, char nextInput)
{
    ll answer = currentState;
    ll ch = nextInput - 'A';
 
    // If goto is not defined, use failure function
    while (g[answer][ch] == -1)
        answer = f[answer];
 
    return g[answer][ch];
}
 
// This function finds all occurrences of all array words
// in text.
void searchWords(string arr[], ll k, string text)
{
    // Preprocess patterns.
    // Build machine with goto, failure and output functions
    buildMatchingMachine(arr, k);
 
    // Initialize current state
    ll currentState = 0;
 
    // Traverse the text through the nuilt machine to find
    // all occurrences of words in arr[]
    for (ll i = 0; i < text.size(); ++i)
    {
        currentState = findNextState(currentState, text[i]);
 
        // If match not found, move to next state
        if (out[currentState] == 0)
             continue;
 
        // Match found, print all matching words of arr[]
        // using output function.
        for (ll j = 0; j < k; ++j)
        {
            if (out[currentState] & (1 << j))
            {
                cout << "Word " << arr[j] << " appears from "
                     << i - arr[j].size() + 1 << " to " << i << endl;
            }
        }
    }
}
 
// Driver program to test above
/*int main()
{
    string arr[] = {"he", "she", "hers", "his"};
    string text = "ahishers";
    int k = sizeof(arr)/sizeof(arr[0]);
 
    searchWords(arr, k, text);
 
    return 0;
}
*/
 
int main( int argc, char **argv ){
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
    searchWords(arr, 10, content);
    cout<<"Execution Time = "<<((double)(clock() - tStart)/CLOCKS_PER_SEC)<<endl;
    return 0;
}