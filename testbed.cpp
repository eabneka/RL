#include <iostream>
#include <vector>
#include <random>
#include <array>
#include <algorithm>
#include <iterator>

constexpr auto K = 10;

struct k_armed_bandit_storage {
	std::array<double, K> true_value{};
	std::array<double, K> expected_value{};
	std::array<int, K> selected{};
};

struct double_{

};

struct epsilon {
	epsilon() = default;
	explicit epsilon(double epsilon) : e{ epsilon } {}
	const double getE() {
		return e;
	}
	const double getDiminish() {
		return diminish;
	}

private:
	double e{ 0.1 };
	double diminish{ 0 };
};

double rewarding(std::array<double, K> v, int action) {
	std::random_device rd {};
	std::mt19937 gen{rd()};

	std::normal_distribution<double> nd {v.at(action), 1};

	return nd(gen);
}

int action_selection(std::array<double, K> v, epsilon eps) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0, 1.0);
	std::uniform_int_distribution<int> disint(0, 9);
	//
	if (double random_number = disint(gen); random_number >= eps.getE())
		return std::distance(v.begin(), std::max_element(v.begin(), v.end()));
	else
		return disint(gen);
}

class summary {
public:


private:

};

struct environment {
	int episode{ 100 };
	int step{ 1000 };
};

int main() {
	const epsilon my_agent;
	const environment env;
	{
		k_armed_bandit_storage bv;
		std::random_device rd {};
		std::mt19937 gen {rd()};
		std::normal_distribution<double> nd {0, 1};

		for (int run = 0; run < env.episode; ++run, bv = k_armed_bandit_storage()) {


			for (int i = 0; i < K; ++i) {
				bv.true_value.at(i) = (nd(gen));
			}

			for (int i = 0; i < env.step; ++i) {
				int action = action_selection(bv.expected_value, my_agent);

				double reward = rewarding(bv.true_value, action);
				++bv.selected.at(action);
				bv.expected_value.at(action) += (reward - bv.expected_value.at(action)) / bv.selected.at(action);
			}
		}
	}

}
