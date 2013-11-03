#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "Logger.h"
#include "services/ServiceManager.h"
#include "universe/Universe.h"
#include "Configuration.h"

using namespace std;
using boost::shared_ptr;

// Functions
void closeup (int retval);
void fatal(string message);
void signal_handler(int signum);	// Catch SIGHUP, etc

// Globals
bool daemonized=false;
shared_ptr<Universe> universe;
shared_ptr<Logger> logger;
shared_ptr<Configuration> config;
shared_ptr<ServiceManager> service_manager;

int main(int argc, char **argv) {

	// Create logger
	logger=shared_ptr<Logger>(new Logger("aether"));

	// Get config
	config=shared_ptr<Configuration>(new Configuration("aether.cfg"));

	// Should we daemonize?
	if(argc==2 && 0==strcmp(argv[1],"-d")) { 

		// -d set.	Don't daemonize
		logger->notice("-d set.	Not daemonizing.");

	} else {

		if(daemon(0,0)!=0) {

			fatal("Error daemonizing! Exiting...");
		}
		daemonized=true;
		logger->open_syslog();		// Further logging goes to syslog
	}

	logger->notice("Aether starting");

	// Install signal handlers
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);


	// Write PID.	 Do this before dropping root in case dir is not writeable by daemon user.
	logger->notice("writing PID");
	ofstream pidfile;
	pidfile.open(config->pid_file_name.c_str());
	pidfile << getpid();
	pidfile.close();
	if(pidfile.fail()){

		fatal("Unable to write pid to \""+config->pid_file_name+"\"");
	}

	// Drop root
	logger->notice("changing user");
	if (getuid() == 0) {

		// Get uid and gid info 
		struct passwd* p=getpwnam(config->user.c_str());		// according to getpwnam(3), this should not be free()d
		struct group* g=getgrnam(config->group.c_str());

		if (p==NULL || g==NULL || setgid(g->gr_gid) != 0 || setuid(p->pw_uid) != 0) {

			fatal("Unable to change user / group to "+config->user+"/"+config->group);
		}
	}

	try {

		// Launch the universe
		universe=shared_ptr<Universe>(new Universe());
		logger->notice("universe started successfully");

		// Launch the service manager
		service_manager=shared_ptr<ServiceManager>(new ServiceManager());
		service_manager->run();		// Will block forever

	} catch (exception& e){

		fatal(e.what());
	}

	closeup(0);
	return 0;
}


void fatal(string message) {

	logger->err("fatal: " + message);
	closeup(1);
}


void closeup (int retval) {

	logger->notice("engine closing");
	exit(retval);
}

void signal_handler(int signum){

	if(signum==SIGTERM || signum==SIGINT){

		logger->notice("caught signal. Closing...");
		if(service_manager){

			service_manager->stop();
		}
	 }

}



