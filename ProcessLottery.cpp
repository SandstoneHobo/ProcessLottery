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

	int findPid(int pid) {
		for (int i = 0; i < _processes.size(); i++) {
			if (_processes.at(i).getPid() == pid) {
				return i;
			}
		}
	}

public:
	void addProcess(int pid) {
		Process proc(pid);
		_processes.push_back(proc);
	}

	void removeProcess(int pid) {
		_processes.at(findPid(pid)) = _processes.back();
		_processes.pop_back();
	}

	void alocTickets() {
		for (int i = 1; i < 101; i++) {
			_processes.at(_pidIdx).addLotteryTicket(i);
			nextProc();
		}
	}

	void nextProc() {
		if (_pidIdx >= _processes.size() - 1) {
			_pidIdx = 0;
		}
		else {
			_pidIdx++;
		}
	}

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

	srand((unsigned)time(NULL));
	int winningTicket = 1 + (rand() % 100);

	std::cout << "Process " << mySchedule.findWinner(winningTicket) << " has won the lottery!";


	return 0;
}
