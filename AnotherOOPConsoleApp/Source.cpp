//Object Oriented Programing - Console App - auto dealer(who sells cars and lorries).//

#include<iostream>
#include<conio.h>
#include<string>

using namespace std;

class Lista;

class AutoDealer {                          // base/parent class
protected:                                    
	int type;
	string brand;
	string model;
	int price;
	float consumption;
	AutoDealer* next;
public:
	// constructor 
	AutoDealer(int type, string brand, string model, int price, float consumption)            
	{
		AutoDealer::type = type;
		AutoDealer::brand = brand;
		AutoDealer::model = model;
		AutoDealer::price = price;
		AutoDealer::consumption = consumption;
	}

	//virtual function for display on screen

	virtual void displayOnScreen()                                             
	{
		cout << "-----------------------------------------------" << endl;
		cout << "Auto brand:" << brand << endl;
		cout << "Model:" << model << endl;
		cout << "Price is:" << price << " EURO" << endl;
		cout << "Auto Consumption(l/100km):" << consumption << endl;
	}
	friend class Lista;
};


//derrived/child class 1

class Cars : public AutoDealer {                      
	int AC;                                      
	int fuelType;
	int four_x_four;
public:

	//Constructor

	Cars(int type, string brand, string model, int price, float consumption, int AC, int fuelType, int four_x_four) :
		AutoDealer(type, brand, model, price, consumption)
	{
		Cars::AC = AC;                           
		Cars::fuelType = fuelType;
		Cars::four_x_four = fuelType;
	}

	//overloading display on screen

	void displayOnScreen()                                    
	{
		AutoDealer::displayOnScreen();
		cout << "Does car have AC unit?(0-NO;1-YES):" << AC << endl;
		cout << "Car fuel type (0-Diesel;1-Petrol):" << fuelType << endl;
		cout << "Does car have 4x4 drive(0-NO;1-YES):" << four_x_four << endl;
	}
	friend class Lista;
};


//2nd child/derrived class

class Lorries :public AutoDealer {             
	int cargoCapacity;
	int nrOfSeats;
public:

	//constructor

	Lorries(int type, string brand, string model, int price, float consumption, int cargoCapacity, int nrOfSeats) :
		AutoDealer(type, brand, model, price, consumption) {                              
		Lorries::cargoCapacity = cargoCapacity;
		Lorries::nrOfSeats = nrOfSeats;
	}

	//2nd display on screen overloading

	void displayOnScreen() {                                
		AutoDealer::displayOnScreen();
		cout << "Lorrie cargo volume(l):" << cargoCapacity << " L" << endl;
		cout << "Nr of seats(including driver):" << nrOfSeats << endl;
	}
	friend class Lista;                 
};

class MyException {                     
public:
	string str_what;
	int what;
	MyException() { str_what = ""; what = 0; }
	MyException(string s, int e) {
		str_what = s;
		what = e;
	}
};

class MyException1 {                     
public:
	string str_what;
	int what;
	MyException1() { str_what = ""; what = 0; }
	MyException1(string s, int e) {
		str_what = s;
		what = e;
	}
};

//list class

class Lista {                   
public:
	AutoDealer* head;
	void insertIntoList(AutoDealer* a);
	void displayList();
	void displayList1();
	void displayList2();
};

//insert into list

void Lista::insertIntoList(AutoDealer* a) {
	AutoDealer* p;
	p = head;
	if (p)
	{
		if (a->brand < p->brand) {
			a->next = head;
			head = a;
		}
		else {
			while (p->next && (p->next)->brand < a->brand)
				p = p->next;
			a->next = p->next;
			p->next = a;
		}
	}
	else
		head = a;
}

//display functions/methods for list

void Lista::displayList() {
	AutoDealer* a;
	a = head;
	if (!a)
		cout << "Empty list!";
	else
		while (a) {
			a->displayOnScreen();
			a = a->next;
			_getch();
		}
}

//display by category

void Lista::displayList1() {
	AutoDealer* a;
	a = head;
	if (!a)
		cout << "Empty list!";
	else
		while (a) {
			if (a->type == 0) {       
				a->displayOnScreen();
				a = a->next;
			}
			_getch();
		}
}
void Lista::displayList2() {
	AutoDealer* a;
	a = head;
	if (!a)
		cout << "Empty list!";
	else
		while (a) {
			if (a->type == 1) {  
				a->displayOnScreen();
				a = a->next;
			}
			_getch();
		}
}
void insertion(Lista& l, int x) {             
	string brand, model;
	int price, AC, fuelType, four_x_four, cargoCapacity, nrOfSeats, brand1;
	float consumption;
	AutoDealer* a;
	cin.ignore();
	do {                                                        //Some exception handlying
		try {
			cout << "Insert auto brand(MAXIM 10 CHR.):"; getline(cin, brand);
			brand1 = brand.length();
			if (brand1 > 10)
				throw MyException1("Brand to long!", brand1);
		}
		catch (MyException1 f)
		{
			cout << f.str_what << ":";
			cout << f.what << endl;
		}
	} while (brand1 > 10);
	cout << "Introduceti model auto:"; getline(cin, model);
	do {                                                        //Another exception handlying
		try {
			cout << "Insert auto price:"; cin >> price;
			if (price < 0)
				throw MyException("Negativ price!", price);
		}
		catch (MyException e)
		{
			cout << e.str_what << ":";
			cout << e.what << endl;
		}
	} while (price < 0);
	cout << "Insert auto consumption(l/100km):"; cin >> consumption;

	// checking for car or lorrie (0-car / 1-lorrie)

	if (x == 0)                                           
	{
		Cars* car;
		cout << "Does the car have AC unit?[0-NO/1-YES]:"; cin >> AC;
		cout << "Insert type of fuel(0-DIESEL/1-PETROL)[0/1]:"; cin >> fuelType;
		cout << "Does the car have 4x4 drive?[0-NO/1-YES]:"; cin >> four_x_four;
		car = new Cars(1, brand, model, price, consumption, AC, fuelType, four_x_four);
		a = car;
		l.insertIntoList(a);
	}
	else
		if (x == 1)
		{
			Lorries* lorrie;
			cout << "Insert lorrie cargo capacity(in L):"; cin >> cargoCapacity;
			cout << "Insert number of seats(including driver):"; cin >> nrOfSeats;
			lorrie = new Lorries(2, brand, model, price, consumption, cargoCapacity, nrOfSeats);
			a = lorrie;
			l.insertIntoList(a);
		}
}

// main function

void main()                       
{
	int opt;
	Lista l;
	l.head = NULL;
	do {
		cout << "1. Insert car offer" << endl;
		cout << "2. Insert lorrie offer" << endl;
		cout << "3. Display available cars/lorries" << endl;
//		cout << "4.Display by category(cars or lorries)" << endl;
		cout << "0.Exit" << endl;
		cout << "Insert Option:"; cin >> opt;
		switch (opt)
		{
		case 1:
			insertion(l, 0);
			break;
		case 2:
			insertion(l, 1);
			break;
		case 3:
			l.displayList();
			break;
		case 4:
			int y;
			cout << "Pentru ce categorie doriti sa vedeti oferte(1-pentru masini/2-pentru autoutilitare)?"; cin >> y;
			if (y == 1) { l.displayList1(); }
			else
				if (y == 2) { l.displayList2(); }
				else
					cout << "Wrong option!";
			break;
		case 0:
			break;
		default:
			cout << "Wrong option!";
			break;

		}
	} while (opt != 0);
}