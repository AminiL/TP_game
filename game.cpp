#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
class UNIT {
protected:
	double rate_of_money;
	int money;
	int cost_of_one;
	int comission;
	int real_money;
	int change;
	int cnt;
	virtual void make_units() = 0;
	virtual void cancel() = 0;
	virtual std::string to_string() = 0;
	virtual std::pair < int, int > issue() = 0;
};
class soldier :UNIT {
protected:
	int cost;
	soldier(int money_, int cost_) {
		cost = cost_;
		rate_of_money = double(rand() % 10 + 1) / 10.0;
		money = money_;
		cost_of_one = cost;
		real_money = double(money) * rate_of_money;
		comission = money - real_money;
	}
	void make_units() {
		cnt = real_money / cost_of_one;
		change = real_money - cnt * cost_of_one;
	}
	void cancel() {
		cnt = 0;
		change = money;
	}
	void print() {
		std::cout << "comission = " << comission << "\nwe can give you " << cnt << " soldiers\nyour change is " << change << '\n';
	}
	int get_cnt() {
		return cnt;
	}
	int lose() {
		return money - change;
	}
	std::pair < int, int > issue() {
		return std::make_pair(cnt, change);
	}
};
class ordinary_soldier : soldier {
private:
	static const int magic_const = 10;
public:
	//using soldier::soldier;
	using soldier::make_units;
	using soldier::cancel;
	using soldier::issue;
	using soldier::print;
	using soldier::get_cnt;
	using soldier::lose;
	std::string to_string() {
		return "ordinary_soldier";
	}
	ordinary_soldier(int money_) : soldier(money_, magic_const) {}
};
class defender : soldier {
private:
	static const int magic_const = 20;
public:
	//using soldier::soldier;
	using soldier::make_units;
	using soldier::cancel;
	using soldier::issue;
	using soldier::print;
	using soldier::get_cnt;
	using soldier::lose;
	std::string to_string() {
		return "defender";
	}
	defender(int money_) : soldier(money_, magic_const) {}
};
class spy : soldier {
private:
	static const int magic_const = 30;
public:
	//using soldier::soldier;
	using soldier::make_units;
	using soldier::cancel;
	using soldier::issue;
	using soldier::print;
	using soldier::get_cnt;
	using soldier::lose;
	std::string to_string() {
		return "spy";
	}
	spy(int money_) : soldier(money_, magic_const) {}
};
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
int main() {
	srand(time(NULL));
	Player P(1000000);
	ask(P);
}