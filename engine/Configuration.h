#pragma once
#include <string>
#include "Logger.h"
#include <boost/shared_ptr.hpp>
#include "INIReader.h"

using namespace std;
using boost::shared_ptr;

extern shared_ptr<Logger> logger;


class Configuration {

public:
	Configuration(string filename){

		this->_is_valid=false;

		// Read the config file
		INIReader reader(filename.c_str());
		if (reader.ParseError() < 0) {
			logger->err("Can't read "+filename);
		}

		// Set config parameters
		ip_port = reader.GetInteger("aether","ip-port",9090);
		worker_threads = reader.GetInteger("aether","worker-threads",16);
		user= reader.Get("aether","user","aether");
		group= reader.Get("aether","group","aether");
		pid_file_name= reader.Get("aether","pidfile","/var/run/aether.pid");

		// We're now valid
		this->_is_valid=true;

	};

	bool is_valid() {

		return this->_is_valid;
	};

	int ip_port;
	int worker_threads;
	string user;
	string group;
	string pid_file_name;

protected:

	bool _is_valid;


};

