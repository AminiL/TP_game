#pragma once
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