#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <deque>

using namespace std;

const unsigned infinity = numeric_limits<int>::max();

struct State {
  int a; // Amount in jug A
  int b; // Amount in jug B

  // Where to go on each of the six actions
  int fillA;
  int fillB;
  int emptyA;
  int emptyB;
  int AtoB;
  int BtoA;

  int previous;
  int distance;
  bool visited;

  State(int a,
	int b,
	int fillA,
	int fillB,
	int emptyA,
	int emptyB,
	int AtoB,
	int BtoA)
    : a(a),
      b(b),
      fillA(fillA),
      fillB(fillB),
      emptyA(emptyA),
      emptyB(emptyB),
      AtoB(AtoB),
      BtoA(BtoA),
      previous(infinity),
      distance(infinity),
      visited(false)
  {}
};

class Jug {
    public:

        //Constructor
        Jug(int Ca,int Cb,int goal,int cfA,int cfB,int ceA,int ceB,int cpAB,int cpBA):
            capA(Ca),
            capB(Cb),
            goal(goal),
            costFillA(cfA),
            costFillB(cfB),
            costEmptyA(ceA),
            costEmptyB(ceB),
            costPourAB(cpAB),
            costPourBA(cpBA)
        {
            for(int i = 0; i <= capA; ++i){
                for(int j = 0; j <= capB; ++j){
                    State thisState(
                        i,
                        j,
                        state_number(Ca,j,Ca,Cb),
                        state_number(i,Cb,Ca,Cb), // Added opening parentheses
                        state_number((int)0,j,Ca,Cb),
                        state_number((int)i,0,Ca,Cb),
                        state_number((int)max(0,i+j-Cb),min(Cb,i+j),Ca,Cb),
                        state_number((int)min(Ca,i+j),max(0,i+j-Ca),Ca,Cb) // Added closing parentheses
                    );
                    states.push_back(thisState);
                }
            }
        }

        //nothing is declared in the heap, thus no need for Rule of 3

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string& solution);
    private:
        vector<State> states;
        int capA;
        int capB;
        int goal;
        int costFillA;
        int costFillB;
        int costEmptyA;
        int costEmptyB;
        int costPourAB;
        int costPourBA;

        //returns the state number of the state given the amount of water in each jug
        int state_number(int a, int b, int Ca, int Cb) {
            return a*(Cb+1)+b;
        }
        //gets the cost of the action
        int getCost(int action) const;
        //gets the state number of the adjacent state using action as an index
        int getAdjState(int action, const State &currentState) const;
        //function that checks if the inputs are valid
        bool validInputs() const;
};