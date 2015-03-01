#include "Queue.h"
#include <vector>
#include <sstream>
using namespace std;

bool customersLeft(vector<Queue<int>*> vec);

void getFileName(ifstream & fin, string& filename);

void qMain(string & filename, ifstream& fin, int master);

int main()
{
	ifstream fin;

	string filename;

	getFileName(fin, filename);
		
	for (int i = 1; i < 4; i++)
	{
		qMain(filename, fin, i);

		fin.open(filename);
	}

	system("PAUSE");
	return 0;
}


void getFileName(ifstream & fin, string& filename)
{
	
	while (true)
	{
		cout << "What is the Checkout FileName: ";

		cin >> filename;

		fin.open(filename);

		if (fin.good())
			break;
		else
		{
			cout << "\nBad Filename, Please Re-Enter." << endl;
		}

	}
	
}

void qMain(string& filename, ifstream& fin, int master)
{
	string line, command;

	int customers, minute, registerCount;

	vector<Queue<int>*> qVec;

	vector<Queue<int>*>::iterator iter;

	vector<int> timeReg;

	int index = 0,    totalCust = 0,    startRegisters = 0;
	

	while (true)
	{
		getline(fin, line);

		stringstream sstream;

		sstream << line;

		sstream >> command;	

		if (command == "Cashiers")
		{
			sstream >> registerCount;

			startRegisters = registerCount;

			for (int i = 0; i < registerCount; i++)
			{
				Queue<int>* q;
				q = new Queue < int >;
				qVec.push_back(q);
			}
		}

		if (command == "Time")
		{
			sstream >> minute >> customers;
			int count = 0;

			totalCust += customers;

			while (count < customers)
			{
				if (master == 3)
					qVec[0]->enqueue(minute); //add to que 0 instead of index
				else
					qVec[index]->enqueue(minute);

				count++;
				index++;
				if (index == registerCount)
					index = 0;
			}
		}
		if (command == "OpenRegister" && master == 2)
		{
			timeReg.push_back(minute);
		}
		if (command == "CloseStore")
			break;
	}

	int minCount = 0;

	double average = 0.0,   totalTime = 0.0;	

	while (customersLeft(qVec)) //customers left waiting in line
	{
		int totalIters = 0,    countIndex = 0;
		
		for (int i = 0; i < registerCount; i++)
		{
			for (unsigned int k = 0; k < qVec.size(); k++)
			{
				if (qVec[k]->getSize() != 0 && (minCount - qVec[k]->seeTop() >= 1))
				{

					totalTime += minCount - qVec[k]->dequeue();
					
					totalIters++;
					countIndex++;
					
					if (countIndex == registerCount)
					{
						break;
					}
				}

			}
			if (countIndex == registerCount)
			{
				break;
			}
		}
		if (master == 2) //for section 2 
		{
			if (totalIters < 1 && minCount > 1)
			{
				registerCount = 1;
			}

			if ((totalIters < registerCount) && (minCount > 1))
			{
				
				registerCount = registerCount - (registerCount - totalIters);
				
				if (registerCount == 0)
					registerCount = 1;
			}

			for (unsigned int i = 0; i < timeReg.size(); i++)
			{
				if (timeReg[i] == minCount)
				{
					
					registerCount++;
				}
			}
		}
		minCount++;
	}
	
	switch (master)
	{
	case 1: cout << "PART 1 - Separate Cashiers with Separate Queues"<< endl; break;
	case 2: cout << "PART 2 - Separate Cashiers/Queues with Opening/Closing Registers." << endl; break;
	case 3: cout << "PART 3 - Separate Cashiers Sharing One Queue" << endl; break;
	}

	
	cout << "Starting Registers: " << startRegisters << endl
		 << "Total Customers: " << totalCust << endl
		 << "Average Checkout Time: " << totalTime / totalCust << endl << endl;

	fin.close();
}

bool customersLeft(vector<Queue<int>*> vec)
{
	int sum = 0;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		sum += vec[i]->getSize();
	}
	return sum > 0;
}
