#include "Jug.h"

int Jug::getCost(int action) const{
    //0 means fillA, 1 means fillB, 2 means emptyA, 3 means emptyB, 4 means pourAtoB, 5 means pourBtoA
    if(action == 0)
    {
        //returns the cost of filling A
        return costFillA;
    }
    else if(action == 1)
    {
        //returns the cost of filling B
        return costFillB;
    }
    else if(action == 2)
    {
        //returns the cost of emptying A
        return costEmptyA;
    }
    else if(action == 3)
    {
        //returns the cost of emptying B
        return costEmptyB;
    }
    else if(action == 4)
    {
        //returns the cost of pouring A to B
        return costPourAB;
    }
    else if(action == 5)
    {
        //returns the cost of pouring B to A
        return costPourBA;
    }
    else
    {
        //if the action is invalid, return -1
        return -1;
    }
}

int Jug::getAdjState(int action, const State &currentState) const{
    //0 means fillA, 1 means fillB, 2 means emptyA, 3 means emptyB, 4 means pourAtoB, 5 means pourBtoA
            if(action == 0){
                //returns the state number of the state that results from filling A
                return currentState.fillA;
            }
            else if(action == 1)
            {
                //returns the state number of the state that results from filling B
                return currentState.fillB;
            }
            else if(action == 2)
            {
                //returns the state number of the state that results from emptying A
                return currentState.emptyA;
            }
            else if(action == 3)
            {
                //returns the state number of the state that results from emptying B
                return currentState.emptyB;
            }
            else if(action == 4)
            {
                //returns the state number of the state that results from pouring A to B
                return currentState.AtoB;
            }
            else if(action == 5)
            {
                //returns the state number of the state that results from pouring B to A
                return currentState.BtoA;
            }
            else
            {
                //if the action is invalid, return -1
                return -1;
            }

        }


//these are operators to see if states are equal or not and used to save some time by creating only one comparison needed instead of two in solve()
bool operator!=(State const& lhs, State const& rhs) {
  return lhs.a != rhs.a || lhs.b != rhs.b;
}

bool operator==(State const& lhs, State const& rhs) {
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

bool Jug::validInputs() const{
    //self explanatory
    if(0 < capA && capA <= capB && goal <= capB && capB <= 1000 && costEmptyA >= 0 && costEmptyB >= 0 && costFillA >= 0 && costFillB >= 0 && costPourAB >= 0 && costPourBA >= 0){
        return true;
    }
    return false;
}

int Jug::solve(string& solution){
    //if the inputs are valid, solve the problem
    if(validInputs()){
        //initialize the states
        int goalState = state_number(0, goal, capA, capB);
        states.at(0).distance = 0;
        states.at(0).previous = 0;
        //initialize the queue that will hold the states that need to be visited
        deque<State> unvisited;

        //first state should be the starting state, this also jumpstarts the while loop to begin
        unvisited.push_back(states.at(0));

        while (!unvisited.empty()) {
            //State& allows us to edit the state instead of a copy
            //take the top state from the queue
            State& currentState = unvisited.front();
            unvisited.pop_front();
            //set the state to visited so it doesn't reenter the queue
            currentState.visited = true;

            //check all adjacent states
            for (int j = 0; j < 6; ++j) {
                //gets the adjacent state associated with j
                State& adjState = states.at(getAdjState(j, currentState));
                //get the cost for doing this action
                int cost = getCost(j);
                //calculate the distance to the adjacent state
                int alternativePathDistance = currentState.distance + cost;

                //if the adjacent state isn't the current state and the alternative path is shorter
                //than the current distance to the adjacent state, update the distance and previous
                if (currentState != adjState && alternativePathDistance < adjState.distance) {
                    adjState.distance = alternativePathDistance;
                    adjState.previous = state_number(currentState.a, currentState.b, capA, capB);
                    //if the adjacent state hasn't been visited, add it to the queue
                    if (!adjState.visited) {
                        unvisited.push_back(adjState); // Enqueue adjacent states in a Depth First TraversAL
                    }
                }
            }
        }

        //backtrack to find the solution
        //in some cases, my code changes the starting state and I can't find out why
        //this is my stop gap measure to fix the starting state
        State dummyState(0, 0, state_number(capA, 0, capA, capB), state_number(0, capB, capA, capB), state_number(0, 0, capA, capB), state_number(0, 0, capA, capB), state_number(0, 0, capA, capB),state_number(0, 0, capA, capB));
        dummyState.distance = 0;
        dummyState.previous = 0;
        states.at(0) = dummyState;

        //backtrack this like a linked list to get the solution
        //initialize the curr and previous state numbers
        int curr = goalState;
        int previousState = states.at(goalState).previous;
        //checks if there is no solution
        if(previousState == infinity){
            solution = "";
            return 0;
        }
        //if we get here, there is a solution
        while (curr != 0){
            //determine the action that was taken to get to the current state
            if(getAdjState(0, states.at(previousState)) == curr){
                solution = "fill A\n" + solution;
            }
            else if(getAdjState(1, states.at(previousState)) == curr){
                solution = "fill B\n" + solution;
            }
            else if(getAdjState(2, states.at(previousState)) == curr){
                solution = "empty A\n" + solution;
            }
            else if(getAdjState(3, states.at(previousState)) == curr){
                solution = "empty B\n" + solution;
            }
            else if(getAdjState(4, states.at(previousState)) == curr){
                solution = "pour A B\n" + solution;
            }
            else if(getAdjState(5, states.at(previousState)) == curr){
                solution = "pour B A\n" + solution;
            }
            //update the current and previous state numbers
            curr = previousState;
            previousState = states.at(previousState).previous;
        }
        //the goalState's distance is the total distance needed to reach the goal
        int totalDistance = states.at(goalState).distance;
        //zybooks wants this
        solution = solution + "success " + to_string(totalDistance);
        return 1;
    }
    //if the inputs are invalid, return -1
    else
    {
        solution = "";
        return -1;
    }
}