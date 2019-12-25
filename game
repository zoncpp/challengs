//
#include <iostream>
#include <thread>
#include<string>

using namespace std;

class Player
{
	int healthPoint;
	string name;
public:
	Player(string sName, int iHealthPoint) :name(sName), healthPoint(iHealthPoint) {};
	~Player() {}
	string getName() const { return name; }
	int getHealth() const { return healthPoint; }
	void attacked(int iPoint)
	{
		if (healthPoint > 0)
		{
			healthPoint -= iPoint;
			if (healthPoint <= 0)
				cout << name.c_str() << " is died";
		}
	}
};

int main()
{
	Player orc("Orc", 7);
	Player dragon("Dragon", 20);
	Player _hero("Hero", 40);

	//--- monsters attack to hero
	auto monsters_attack = [&]()
	{
		int attack_time_orc = 0;
		int attack_time_dragon = 0;
		do
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			if (orc.getHealth() > 0 && ++attack_time_orc >= 13)
			{
				_hero.attacked(1);
				attack_time_orc = 0;
			}
			if (dragon.getHealth() > 0 && ++attack_time_dragon >= 25)
			{
				_hero.attacked(3);
				attack_time_dragon = 0;
			}
		} while (_hero.getHealth() > 0 && (orc.getHealth() > 0 || dragon.getHealth() > 0));
	};
	thread t1(monsters_attack);
	
	string s;
	while (_hero.getHealth() > 0 && (orc.getHealth() > 0 || dragon.getHealth() > 0))
	{//--- hero attacks to monsters
		s = "";
		getline(cin, s);
		if (strcmp(s.c_str(), "attack orc") == 0)
			orc.attacked(2);
		else if (strcmp(s.c_str(), "attack dragon") == 0)
			dragon.attacked(2);
	}
	cout << endl;
	t1.join();

	//--- show info
	if (_hero.getHealth() > 0)
		cout << "Hero Wins  ... points: " << _hero.getHealth() << endl;
	cout << "Orc's Health is : " << orc.getHealth() << std::endl;
	cout << "Dragon's Health is : " << dragon.getHealth() << std::endl;

	cout << "Press any key... ";
	getline(cin, s);

    return 0;
}
