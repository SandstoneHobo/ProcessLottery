#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

//class for processes
class Process {
	//class variables to define the propeties of each process
	int _pid;
	std::vector<int> _tickets;

public:
	//constructor
	Process(int pid) {
		_pid = pid;
	}

	//gives the process the given lottery ticket number
	void addLotteryTicket(int ticket) {
		_tickets.push_back(ticket);
	}

	//removes the given lottery number from this process
	void removeLotteryTicket(int ticket) {
		for (int i = 0; i < _tickets.size(); i++) {
			if (_tickets.at(i) == ticket) {
				_tickets.at(i) = _tickets.back();
				_tickets.pop_back();
				break;
			}
		}
	}

	//returns the process id of this process
	int getPid() {
		return _pid;
	}

	//function returns a boolean value to indicate whether the given lottery ticket is assigned to this process
	bool hasTicket(int ticketNumber) {
		for (int i = 0; i < _tickets.size(); i++) {
			if (_tickets.at(i) == ticketNumber) {
				return true;
			}
		}
		return false;
	}
};


//class for scheduler
class Scheduler {
	std::vector<Process> _processes;
	int _pidIdx;

	//function finds the index of the given pid
	int findPid(int pid) {
		for (int i = 0; i < _processes.size(); i++) {
			if (_processes.at(i).getPid() == pid) {
				return i;
			}
		}
		return -1;
	}

public:
	//functions adds a process to the list of process the scheduler has
	void addProcess(int pid) {
		//checks if the given pid is already in use
		bool inList = false;
		for (int i = 0; i < _processes.size(); i++) {
			if (pid == _processes.at(i).getPid()) {
				inList = true;
			}
		}
		//adds the process to the scheduler
		if (!inList) {
			Process proc(pid);
			_processes.push_back(proc);
		}
		else {
			std::cout << "That process id is already used in this scheduler" << std::endl;
		}
	}

	//function to remove a process from the scheduler
	void removeProcess(int pid) {
		int process = findPid(pid);
		if (process != -1) {
			_processes.at(process) = _processes.back();
			_processes.pop_back();
		}
		else {
			std::cout << "Process " << pid << " not found during removal";
		}
	}

	//function divides 100 lottery tickets evenly between the processes it manages
	void alocTickets() {
		for (int i = 1; i < 101; i++) {
			_processes.at(_pidIdx).addLotteryTicket(i);
			nextProc();
		}
	}

	//increases the index to move to the next process
	void nextProc() {
		if (_pidIdx >= _processes.size() - 1) {
			_pidIdx = 0;
		}
		else {
			_pidIdx++;
		}
	}

	//checks which process has the given ticket
	int findWinner(int ticketNumber) {
		for (int i = 0; i < _processes.size(); i++) {
			if (_processes.at(i).hasTicket(ticketNumber)) {
				return _processes.at(i).getPid();
			}
		}
	}
};

int main() {
	Scheduler mySchedule;

	mySchedule.addProcess(1);
	mySchedule.addProcess(2);
	mySchedule.addProcess(3);
	mySchedule.addProcess(4);

	mySchedule.alocTickets();

	//generates a seed for random number generation and generates a random number for the winning ticket
	srand((unsigned)time(NULL));
	int winningTicket = 1 + (rand() % 100);

	std::cout << "Process " << mySchedule.findWinner(winningTicket) << " has won the lottery!";


	return 0;
}
