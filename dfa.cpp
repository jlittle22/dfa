#include "dfa.h"

DFA::DFA(initializer_list<string> q,
	     initializer_list<char> alphabet,
	     initializer_list<pair<pair<string, char>, string>> d,
	     initializer_list<string> finals,
	     string start
	    ) {
    curr_state = start;
    start_state = start;

    // set Q
    for (const string& q_i : q) {
    	if (states.find(q_i) == states.end()) {
    	    states.insert(q_i);
        } else {
        	throw runtime_error("could not insert " + q_i + " into States since it already exists");
        }
    }

    // set Sigma
    for (const char& w : alphabet) {
    	if (sigma.find(w) == sigma.end()) {
    	    sigma.insert(w);
        } else {
        	throw runtime_error("could not insert " + string(1, w) + " into Sigma since it already exists");
        }
    }

    // set Delta
    for (const pair<pair<string, char>, string>& transition : d) {
    	auto[args, dest] = transition;
    	auto[state, c] = args;
    	string c_str = string(1, c);
    	const string Key = state + c_str;
    	if (states.find(dest) == states.end()) {
    		throw runtime_error("cannot add state '" + dest + "' to Delta. it does not exist in this machine.");
    	} else if (states.find(state) == states.end()) {
    		throw runtime_error("cannot add state '" + state + "' to Delta. itdoes not exist in this machine.");
    	} else if (delta.find(Key) == delta.end()) {
    	    delta[Key] = dest;
    	} else {
    		throw runtime_error("could not insert (" + state + ", " + c_str + ") -> " + dest + " into Delta because a mapping for (" + state + ", " + c_str + ") already exists.");
    	}
    }

    // set Final states
    for (const string& f_i : finals) {
    	if (final_states.find(f_i) == final_states.end()){
    	    final_states.insert(f_i);
        } else {
        	throw runtime_error("could not insert " + f_i + "into Final States because it already exists."); 
        }
    }
}

DFA::~DFA() {
    // do nothing :)
}

void DFA::reset() {
	curr_state = start_state;
}

void DFA::readSymbol(char input) {
    step(input);
}

void DFA::readString(string input) {
	const unsigned len = input.length();
	for (unsigned i = 0; i < len; i++) {
		readSymbol(input[i]);
	}
}

bool DFA::isAccepting() {
    return final_states.find(curr_state) != final_states.end();
}

string DFA::getCurrentState() {
	cout << curr_state << endl;
	return curr_state;
}

void DFA::step(char input) {
	if (sigma.find(input) == sigma.end()) {
		throw runtime_error("symbol '" + string(1, input) + "' is not in Sigma.");
	}
	string key = curr_state + input;
	curr_state = delta[key];
}
