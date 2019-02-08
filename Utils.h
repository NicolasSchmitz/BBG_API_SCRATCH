#pragma once
#include <string>
#include <limits.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <time.h>
#include <ctime>
#include <memory>
#include <map>

#include <blpapi_defs.h>
#include <blpapi_session.h>
#include <blpapi_sessionoptions.h>
#include <blpapi_correlationid.h>
#include <blpapi_event.h>

using namespace BloombergLP;
using namespace blpapi;

class OptionVal {
protected:
	std::string OptionName;
	tm mytime; 
	double value;
public:
	OptionVal(const std::string &optname,const  double &val)
		:OptionName{ optname }, value{ val } {
		std::time_t t = std::time(0);
		mytime = *localtime(&t);
	}
	void set_val(const double &inpval) { value = inpval; }
	std::string get_time() { return std::to_string(mytime.tm_hour) + ":" + std::to_string(mytime.tm_min) + ":" + std::to_string(mytime.tm_sec); }
	double get_val() const { return value; }
	~OptionVal() {};
};



static const std::string d_host ="localhost";
static const int d_port = 8194;
static const int d_maxEvents = INT_MAX;
static const int MAX_PACKETS = 10;

std::string ElementTypeString(const int &input);

void printElem(std::fstream &os, const blpapi::Element &e, const int &elemtype);
std::ostream &printElem(std::ostream &os,const  blpapi::Element &e, const int &elemtype);
void printElem(const blpapi::Element &e, const int elemtype);

std::string fields_string(const std::vector<std::string> &vec);

