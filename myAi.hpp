#ifndef MYAI_HPP
#define MYAI_HPP
#include <vector>
#include "OthelloAI.hpp"

namespace rnip
{
	class myOthelloAI : public OthelloAI{
	public:
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);

	};
}

int search(const OthelloGameState& state, int depth, bool myturn);
std::pair<int, int> get_pair(int max, std::vector<std::pair<std::pair<int,int>, int>> coord);
bool choose_color(const OthelloGameState& state);
std::pair<int, int> get_pair(int max, std::vector<std::pair<std::pair<int,int>, int>> coord);

#endif // MYAI_HPP
