///////////////////////////////////////////////////////////////////////////////////
//
//	Braeden Timlin
//	
//	Assignment 4
//
//	Objective:
//		The program is to be a banking system that contains a Transaction class
//		and 3 classes that inheret from the Transaction class: Withdraw, Deposit,
//		and Transfer.  The child classes overide the Transaction class' Report 
//		function, therefore the Transaction class Report function is a virtual 
//		void function.
//	
//	Pseudo-Code:
//		Transaction class
//			integer variable userID
//			float variable amout
//			virtual void function named Report
//
//		Withdraw class, child of transaction
//			Report function - prints the userID and the amount witdrawn
//
//		Deposit class, child of transaction
//			Report function - prints the userID and the amount deposited
//
//		Transfer class, child of transaction
//			Report function - prints the userID and the amount transferred
//
//		User class
//			integer id - the id the user inputs
//			integer numTrans
//			array named tr of 100 pointers to the Transaction class
//			Report function - prints the number of transactions that specific user has done
//			Constructor sets user id to -1 by default and numTrans to 0
//
//		main function
//			array of 100 pointers of the User class
//			integer variable numUsers set to 0
//			integer variable current user - current user in the array
//			boolean variable usrExist - determines whether the id the user inputs corresponds to an existing user
//			boolean variable exit set to false - used to exit the program
//			float variable a
//			integer variable t
//			integer variable u
//
//			create new user in first spot in array
//
//			while variable exit is false, loop
//				set usrExist to false
//				print "Enter user id" and set input to variable u
//				
//				for loop from 0 to the number of Users that exist
//					check if the input id matches any of the existing user IDs
//						if so set the current user to the current position in the for loop, set usrExist to true, print "Login Successful"
//
//					if usrExist is false, 
//						set current user to numUsers, so that the current user is the latest spot in the array
//						if numUsers does not equal 0,
//							create a new user at place numUser
//					set id to user input id
//					print "New User Created"
//					increment numUsers by 1
//
//				if the number of transactions is less than orequal to 100
//					print the transaction options, and the exit option
//					set user input to variable t
//
//						check value of t,
//							if it is 1
//								create new Withdraw object at the current place in the transaction array
//							if it is 2
//								create new Deposit object at the current place in the transaction array
//							if it is 3
//								create new Transfer object at the current place in the transaction array
//							if it is 4
//								set exit to equal true
//
//						if exit is false
//							print "Enter Amount", set input value to variable a
//							set transaction amount to be variable a
//							set transaction userID to variable u
//							increment numTrans by 1, print new line
//							for loop from 0 to the number of transactions,
//								call report function, print all previous transactions for that specific user
//							print new line
//						else 
//							break
///////////////////////////////////////////////////////////////////////////////////

#include "time.h"
#include "stdio.h"
#include "math.h"
#include "iostream"
using namespace std;

// Classes

class Transaction
{
public:
	int userID;
	float amount; //float because money has cents and dollars eg. '$11.02'
	virtual void Report()
	{}
};

class Withdraw : public Transaction
{
public:
	Withdraw()
	{}
	void Report();
};

void Withdraw::Report()
{
	cout << "UserID: " << userID << "\nWithdrawn Amount: $" << amount << "\n";
}


class Deposit : public Transaction
{
public:
	Deposit()
	{}
	void Report();
};

void Deposit::Report()
{
	cout << "UserID: " << userID << "\nDeposited Amount: $" << amount << "\n";
}


class Transfer : public Transaction
{
public:
	Transfer()
	{}
	void Report();
};

void Transfer::Report()
{
	cout << "UserID: " << userID << "\nTransferred Amount: $" << amount << "\n";
}

class User
{
public:
	int id;
	int numTrans;
	Transaction* tr[100];
	float accBal;
	void Report();
	User()
	{
		accBal = 10;
		id = -1;
		numTrans = 0;
	}
};

void User::Report()
{
	cout << "Account Balance: $" << accBal << "\nNumber of Transactions: " << numTrans << "\n";
}


void CreateRandAccount(User* o1, int* curUser){
	o1 = new User();
	o1->id = rand() % 1000 + 1000;
	cout << "User" << curUser+1 << " ID: " << o1->id << "\n";
}

void startTrans(User* o1){
	o1->tr[users[curUser]->numTrans]->amount = a;
	o1->tr[users[curUser]->numTrans]->userID = u;
	o1->numTrans++; // increment number of transactions done by that user
	cout << "\n";	
}

void main()
{
	User* users[100];
	int numUsers = 5; // number of users that exist
	bool usrExist;
	int curUser;
	bool exit = false;
	float a; // user input amount
	int t; // user input transaction choice
	int u; // user input user id
	bool valid;
	srand(time(NULL));

	for (int i = 0; i < numUsers; i++)
	{
		CreateRandAccount(users[i], curUser);
		curUser++;
	}

	while (exit == false)
	{
		valid = false;
		while (valid == false)
		{
			usrExist = false;

			cout << "Enter user id: ";
			cin >> u;

			for (int i = 0; i < numUsers; i++)
			{
				if (u == users[i]->id)
				{
					curUser = i;
					usrExist = true;
					cout << "\n*Login Successful*\n\n";
					valid = true;
					break;
				}
			}
			if (usrExist == false && u >= 1000 && u <= 2000)
			{
				curUser = numUsers;
				if (numUsers != 0)
					users[curUser] = new User();
				users[curUser]->id = u;
				cout << "\n*New User Created*\n\n";
				numUsers++;
				valid = true;
			}
			else if (u < 1000 || u > 2000)
			{
				cout << "User ID Invalid\n";
			}
		}
		if (users[curUser]->numTrans <= 100)
		{
			valid = false;
			while (valid == false)
			{
				cout << "Enter Task From Following List: \n1) Withdraw\n2) Deposit\n3) Transfer\n4) Exit\n>";
				cin >> t;

				//create new object corresponding to action chosen
				switch (t)
				{
				case 4:
					exit = true;
					valid = true;
					break;
				}
				
				if (exit == false)
				{
					cout << "Enter Amount: ";
					cin >> a;
					switch (t)
					{
					case 1:
						if (users[curUser]->accBal - a > 10)
						{
							users[curUser]->tr[users[curUser]->numTrans] = new Withdraw();
							users[curUser]->accBal -= a;
							valid = true;
						}
						else
							cout << "Invalid Transaction\n";
						break;
					case 2:
						users[curUser]->tr[users[curUser]->numTrans] = new Deposit();
						users[curUser]->accBal += a;
						valid = true;
						break;
					case 3:
						if (users[curUser]->accBal - a > 10)
						{
							users[curUser]->tr[users[curUser]->numTrans] = new Transfer();
							users[curUser]->accBal -= a;
							valid = true;
						}
						else
							cout << "Invalid Transaction\n";
						break;
					}
				}
			}
			if (exit == false)
			{
				//set transaction amount and transaction user ID
				StartTrans(users[curUser]);
				for (int i = 0; i < users[curUser]->numTrans; i++)
				{
					users[curUser]->tr[i]->Report();
				}

				users[curUser]->Report();
				cout << "\n";
			}
		}
		else
			break;


	}
}
