#ifndef DFA_H
#define DFA_H

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>

using namespace std;

class DFA {
  public:
    // initialize with q, sigma, finals, start (optionally delta?)
    DFA(initializer_list<string> q, initializer_list<char> alphabet, initializer_list<pair<pair<string, char>, string>> delta, initializer_list<string> finals, string start);
    ~DFA();

    // receive input 
    void readSymbol(char input);

    void readString(string input);

    // isAccepted
    bool isAccepting();

    // get curr state
    string getCurrentState();

    void reset();

  private:
    string curr_state;
    string start_state;
    unordered_set<string> states;
    unordered_set<char> sigma;
    unordered_map<string, string> delta;
    unordered_set<string> final_states;

    void step(char input);
};

#endif