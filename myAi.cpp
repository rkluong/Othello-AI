#include "myAi.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "OthelloCell.hpp"
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, rnip::myOthelloAI, "Randy's AI(Required)");

//returns true if your black and false if your white
bool choose_color(const OthelloGameState& state){
	return state.isBlackTurn();
}

//gets the pair corresponding with the max key
std::pair<int, int> get_pair(int max, std::vector<std::pair<std::pair<int,int>, int>> coord){
	for(auto it:coord)
		if(it.second == max) 
			return it.first;
}

//evaluate the gamestate
int evaluate(const OthelloGameState& state, bool color){
	if(color)
		return state.blackScore() - state.whiteScore();
	return state.whiteScore() - state.blackScore();
}

int search(const OthelloGameState& state, int depth, bool mycolor){
	int value;
	std::unique_ptr<OthelloGameState> copy(state.clone());
	if(depth == 0){
		return evaluate(state, mycolor);
	}
	else{
		//mycolor = true
		if(mycolor == state.isBlackTurn()){
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					if(copy->isValidMove(i,j)){
						copy->makeMove(i,j);
						value = search(*copy, depth - 1, mycolor);
					}
				}
			}
			return std::max(evaluate(state, mycolor), value);
		}
		else{
			//opponents
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					if(copy->isValidMove(i,j)){
						copy->makeMove(i,j);
						value = search(*copy, depth - 1, mycolor);
					}
				}
			}
			return std::min(evaluate(state, mycolor), value);
		}

	}
}

std::pair<int, int> rnip::myOthelloAI::chooseMove(const OthelloGameState& state)
{
	int value;
	std::vector<std::pair<std::pair<int,int>, int>> coord;
	std::vector<int> list;
	
	//mycolor = false if im white and black if its true
	bool mycolor = choose_color(state);
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(state.isValidMove(i,j)){
				std::unique_ptr<OthelloGameState> copy(state.clone());
				copy->makeMove(i,j);
				value = search(*copy, 3, mycolor);
				list.push_back(value);
				coord.push_back(std::make_pair(std::make_pair(i,j), value));
			}
		}
	}
	
	return get_pair(*std::max_element(list.begin(), list.end()), coord);
	
}