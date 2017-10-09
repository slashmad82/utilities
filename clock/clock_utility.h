#pragma once
#include <chrono>
#include <iostream>
#include <utility>
using namespace std;

struct elaps {
	chrono::duration<int,milli> elapsed;	
	chrono::duration<int,milli> elapsed_from_epoc;	
};

class clock_utility
{
	public:
		clock_utility(bool dolog, const string task_name) : 
			log_(dolog),
			task_name_(task_name),
			last_(chrono::high_resolution_clock::now()),
			start_(chrono::high_resolution_clock::now()) 
			{}

		elaps GetElapsed(const string & job) {
			auto now = chrono::high_resolution_clock::now();
			elaps e;
			e.elapsed = chrono::duration_cast<chrono::milliseconds>(now - last_);
			e.elapsed_from_epoc = chrono::duration_cast<chrono::milliseconds>(now - start_);
			last_ = now;

			if(log_) {
				cout << "::clock_utility:: " << task_name_ << " -> ["<< job << "] -->";
				cout << " °°°MILLISEC_ELAPSED_FROM_LAST_CALL: "<< e.elapsed.count() << "[ms]";
				cout << " °°°MILLISEC_FROM_EPOC: " << e.elapsed_from_epoc.count() <<"[ms]"<< endl;
			}

			return e;
		}

	private:
		bool log_{true};
		string task_name_;
		chrono::system_clock::time_point last_;
		chrono::system_clock::time_point start_;
		

};
