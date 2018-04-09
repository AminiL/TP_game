#pragma once
#include "Player.h"
template < typename T>
void get_ans(T factory, Player &P) {
	factory.make_units();
	factory.print();
	std::cout << "are you agree?\n";
	std::string s;
	while (true) {
		std::cin >> s;
		if (s == "yes") {
			P.update(factory);
			return;
		}
		if (s == "no")
			return;
		std::cout << "try again\n";
	}
}
struct query {
	std::string who;
	int money;
	void get_who() {
		std::cout << "who?\n";
		std::cin >> who;
	}
	void get_money(Player &P) {
		std::cout << "what about money?\n";
		std::cin >> money;
		if (money > P.show("money")) {
			std::cout << "you dont have enough money. try again\n";
			get_money(P);
		}
		if (money < 0) {
			std::cout << "money must be more then 0\ntry again\n";
			get_money(P);
		}
	}
	query(Player &P) {
		get_who();
		if (who == "ordinary_soldier") {
			get_money(P);
			get_ans<ordinary_soldier>(ordinary_soldier(money), P);
			return;
		}
		if (who == "defender") {
			get_money(P);
			get_ans<defender>(defender(money), P);
			return;
		}
		std::cout << "no units of such type. try again\n";
	}
};

void ask(Player& p) {
	while (true) {
		std::cout << "what do you want\n";
		std::string s;
		std::cin >> s;
		if (s == "stop") {
			break;
		}
		if (s == "stat") {
			p.show_stat();
			continue;
		}
		if (s == "make_units") {
			query q(p);
			continue;
		}
		std::cout << "wrong command\n";
	}
}