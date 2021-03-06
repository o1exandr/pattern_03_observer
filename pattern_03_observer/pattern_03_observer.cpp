/*
Завдання 3. Створити програму з використанням патерну Спостерігач(Observer).  
Предмет спостереження – курс долару(чи євро). Спостерігачі – клієнти(банк, брокер). 
При збільшенні(зменшенні) курсу спостерігачі продають(купляють) валюту.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>


using namespace std;

class Observer;

class Currency
{
private:
 
	double cost;
	list<Observer*> buyers;

public:

	Currency(double c)
	{
		cost = c;
	}


public:
	//  додаємо конкретного покупця
	void attach(Observer* pBuyer)
	{
		buyers.push_back(pBuyer);
	}

	// видаляємо конкретного покупця
	void detach(Observer* pBuyer)
	{

		for (auto it = buyers.begin(); it != buyers.end(); it++)
		{
			if (*it == pBuyer)
			{
				buyers.erase(it);
			}
		}
	}

	// повідомляємо покупцям про зміну ціни
	void notify();


	double getCost() const
	{
		return cost;
	}

	// встановлюємо нову ціну
	void setCost(double c)
	{
		if (cost != c)
		{
			cost = c;
			notify();
		}
	}
};


// класс потенційного покупця
class Observer
{
public:
	// інформування про зміни
	virtual void update(Currency*) = 0;
};


class BankBroker :public Observer
{
private:
	Currency * ptr;
	string name;
public:

	BankBroker(string pName)
	{
		name = pName;
	}

	Currency* getProduct() const
	{
		return ptr;
	}

	void setProduct(Currency* pProduct)
	{
		ptr = pProduct;
	}

	void update(Currency* pProduct)
	{
		cout << "\nInfo for " << name << " about changes cost of dollar: " << pProduct->getCost();
	}
};


class Dollar :public Currency
{
public:
	Dollar(double cost) :Currency(cost) 
	{}
};

int main() {
	// створили курс долара
	Dollar* dollar = new Dollar(28.15);

	// стоврили потенційних покупців
	BankBroker* firstBuyer = new BankBroker("Broker");
	BankBroker* secondBuyer = new BankBroker("Bank");

	// покупці цікавляться конкретною валютою
	dollar->attach(firstBuyer);
	dollar->attach(secondBuyer);

	// зміна курсу, покупці інформуються
	dollar->setCost(29.99);


	delete firstBuyer;
	delete secondBuyer;
	delete dollar;


	cout << endl;
	system("pause");
	return 0;
}

// повідомляємо покупцям про зміну ціни
inline void Currency::notify()
{
	for (auto elem : buyers)
		elem->update(this);
	cout << endl;
}
