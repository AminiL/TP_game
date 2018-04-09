#pragma once
#include "UNITS.h"
class Player {
private:
	std::map < std::string, int > feature;
	static void print_pair(std::pair <std::string, int > p) {
		std::cout << p.first << " = " << p.second << '\n';
	}
public:
	Player(int money_) {
		feature["money"] = money_;
		feature["ordinary_soldier"] = 0;
		feature["defender"] = 0;
	}
	void show_stat() {
		for (auto it : feature) print_pair(it);
	}
	int show(std::string s) {
		return feature[s];
	}
	template < typename T>
	void update(T factory) {
		feature[factory.to_string()] += factory.get_cnt();
		feature["money"] -= factory.lose();
	}
};
