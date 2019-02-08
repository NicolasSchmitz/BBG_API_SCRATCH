/*Goal is to:
1. setup subscription & request from scratch 
2. treat data returned in a clean manner
3. generate file/database that will be used later to generate tradings ideas
*/

/*In Utils.h we define our own constants, classes, prototypes*/
#include "Utils.h"

#include <blpapi_defs.h>
#include <blpapi_session.h>
#include <blpapi_sessionoptions.h>
#include <blpapi_correlationid.h>
#include <blpapi_event.h>


using namespace BloombergLP;
using namespace blpapi;

int main() {
	//std::string subtest = "SX5E 3/15/19 P3000 Index";
	std::vector<std::string> mysecurities{ "SPX 6/21/19 C2700 Index", "SX5E 6/21/19 P3000 Index" };
	std::vector<std::string> myfields{ "IVOL_MID_RT" };
	//std::vector<std::vector<OptionVal>> data;
	std::map<std::string, blpapi::CorrelationId> sec_corr;
	std::map<std::string, std::vector<OptionVal>> data;
	std::string myfields_s{ fields_string(myfields) };
	std::vector<CorrelationId> correls;
	std::string dummy;

	//opening data file
	std::ofstream ofs;
	ofs.open("bbg_data.csv", std::ofstream::out | std::ofstream::app);

	//empty sessionOptions & initialization
	blpapi::SessionOptions sessionOptions;
	sessionOptions.setServerHost(d_host.c_str());
	sessionOptions.setServerPort(d_port);
	
	std::cout << "Connecting..." << std::endl;
	blpapi::Session session(sessionOptions);
	//session start
	if (!session.start()) {
		std::cerr << "Failed to start session" << std::endl;
		return 1;
	}
	else
		std::cout<<"Connected!" << std::endl;
	//open //blp/mktdata
	if (!session.openService("//blp/mktdata")) {
		std::cerr << "Failed to open service //blp/mktdata" << std::endl;
		return 2;
	}
	else
		std::cout << "//blp/mktdata open" << std::endl;
	//creating subscriptions list
	//no way to go around C-style strings in the arguments list at the moment!!
	blpapi::SubscriptionList subscriptions;

	//going  for a securities vector
	
	for (const auto &sec : mysecurities) {
		CorrelationId c = blpapi::CorrelationId((char *)sec.c_str());
		subscriptions.add(
			sec.c_str(),
			myfields_s.c_str(),
			"interval=5",
			c); 
		sec_corr[sec] = c;
		correls.push_back(c);
	}
	//launching subscription
	std::cout << "Launching subscription...  ";
	session.subscribe(subscriptions);

	while (true) {
		Event event = session.nextEvent();
		/*filtering SUBSCRIPTION_DATA Events as they are the containers of our 
		requested data*/
		if (event.eventType() == Event::SUBSCRIPTION_DATA) {
			MessageIterator msgIter(event);
			while (msgIter.next()) {
				Message msg = msgIter.message();
				/*Filtering on the CorrelationId generated for the security we are looking at*/
				int count{ 0 };
				for (auto const &sec : mysecurities) {
					if (msg.correlationId() == sec_corr[sec]) {
						std::cout << "CorrelationID matched" << std::endl;
						Element MyElem = msg.asElement();
						/*if (MyElem.isComplexType())
							std::cout << "Element is complex type" << std::endl;
						if (MyElem.isArray())
							std::cout << "Element is array type" << std::endl;*/
						size_t nb = MyElem.numElements();
						std::cout << "Element has " << nb << " elements" << std::endl;
						for (const auto &s : myfields) {
							if (MyElem.hasElement(s.c_str())) {
								data[sec].push_back(OptionVal::OptionVal(sec, MyElem.getElement(s.c_str()).getValueAsFloat64()));
								std::cout << mysecurities.at(count) << " ";
								MyElem.getElement(s.c_str()).print(std::cout);

								if (data[sec].size() == MAX_PACKETS) {
									for (size_t i = 0; i < data[sec].size(); ++i)
										ofs << sec << ";" << data[sec][i].get_time() << ";" << data[sec][i].get_val() << std::endl;
									data[sec].clear();
								}
							}
						}
						//for (size_t i = 0; i < nb; ++i) {
						//	//print element in any case in the console
						//	//MyElem.getElement(i).print(std::cout);
						//	//print element in any case in file linked to stream ofs
						//	MyElem.getElement(i).print(ofs);
						//	int myelemtype{ MyElem.getElement(i).datatype() };
						//	//printElem( ofs,MyElem.getElement(i), myelemtype);
						//}
					}
					++count;
				}
			}
			}
		}
	ofs.close();
	std::cin >> dummy;
	return 0;
	}