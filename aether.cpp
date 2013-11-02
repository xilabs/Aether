#include <iostream>
#include <fstream>
#include <string>
#include <syslog.h>
#include <signal.h>
#include <unistd.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "Eigen/Dense"
#include <boost/shared_ptr.hpp>
#include "classes/Moxel.h"
#include "classes/Voxel.h"
#include "classes/MoxelManager.h"
#include "gen-cpp/Aether.h"
#include "INIReader.h"
#include "ServiceHandler.h"
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

using namespace std;
using namespace Eigen;
using boost::shared_ptr;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;

// Functions
void thrift_logger(const char* str);
void writelog(int level, string message) ;
void closeup (int retval);
void fatal(string message);
void log_err(string message);
void log_notice(string message);
void signal_handler(int signum);	// Catch SIGHUP, etc

// Globals
shared_ptr<TNonblockingServer> nb_server;
bool daemonized=false;
shared_ptr<Voxel> voxel;

int main(int argc, char **argv) {

	// Create a voxel
	voxel=shared_ptr<Voxel>(new Voxel(Vector3f(0,0,0)));


	// Create 3 moxels, and add them to the Voxel
	shared_ptr<Moxel> m1=shared_ptr<Moxel>(new Moxel(Vector3f(1,1,0)));
	shared_ptr<Moxel> m2=shared_ptr<Moxel>(new Moxel(Vector3f(2,1,0)));
	shared_ptr<Moxel> m3=shared_ptr<Moxel>(new Moxel(Vector3f(3,1,0)));
	voxel->add_moxel(m1);
	voxel->add_moxel(m2);
	voxel->add_moxel(m3);

	// Add bonds: m1<->m2
	m1->bind(m2);
	m2->bind(m1);

	// Add bonds: m2<->m3
	m2->bind(m3);
	m3->bind(m2);

	// Read the config file
	INIReader reader("aether.cfg");
	if (reader.ParseError() < 0) {
		fatal("Can't read aether.cfg");
	}

	// Set config parameters
	int ip_port = reader.GetInteger("aether","ip-port",9090);
	int worker_threads = reader.GetInteger("aether","worker-threads",16);
	string user= reader.Get("aether","user","aether");
	string group= reader.Get("aether","group","aether");
	string pid_file_name= reader.Get("aether","pidfile","/var/run/aether.pid");

	// Daemonize and setup logging 
	if(argc==2 && 0==strcmp(argv[1],"-d")) { 

		// -d set.	Don't daemonize
		writelog(LOG_NOTICE,"-d set.	Not daemonizing.");

	} else {

		if(daemon(0,0)!=0) {

			fatal("Error daemonizing! Exiting...");
		}
		daemonized=true;
		openlog("aether",0,LOG_DAEMON);
	}

	// Install signal handlers
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);


	// Write PID.	 Do this before dropping root in case dir is not writeable by daemon user.
	ofstream pidfile;
	pidfile.open(pid_file_name.c_str());
	pidfile << getpid();
	pidfile.close();
	if(pidfile.fail()){

		fatal("Unable to write pid to \""+pid_file_name+"\"");
	}

	// Drop root
	if (getuid() == 0) {

		// Get uid and gid info 
		struct passwd* p=getpwnam(user.c_str());		// according to getpwnam(3), this should not be free()d
		struct group* g=getgrnam(group.c_str());

		if (p==NULL || g==NULL || setgid(g->gr_gid) != 0 || setuid(p->pw_uid) != 0) {

			fatal("Unable to change user / group to "+user+"/"+group);
		}
	}


	try {

		shared_ptr<AetherHandler> handler(new AetherHandler());
		shared_ptr<TProcessor> processor(new AetherProcessor(handler));
		shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
		shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(worker_threads);
		shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
		threadManager->threadFactory(threadFactory);
		threadManager->start();
		nb_server=shared_ptr<TNonblockingServer>(new TNonblockingServer(processor, protocolFactory, ip_port, threadManager));
		GlobalOutput.setOutputFunction(thrift_logger);		 // Redirect logging output to our function

	} catch (exception& e){

		fatal(e.what());
	}

	// Go!
	stringstream ss; 
	ss << "Starting server" << endl;
	ss << "    pid            : " << getpid() << endl; 
	ss << "    worker threads : " << worker_threads << endl;
	ss << endl;
	writelog(LOG_NOTICE, ss.str());
	nb_server->serve();


	closeup(0);
	return 0;
}


void fatal(string message) {

	writelog(LOG_ERR, "fatal: " + message);
	closeup(1);
}

void log_notice(string message) {

	writelog(LOG_NOTICE,message);

}

void log_err(string message) {

	writelog(LOG_ERR,message);

}

void writelog(int level, string message) {

	// If we are a daemon, syslog it
	if(daemonized){

		syslog(level, message.c_str());

	} else {

		switch(level){
			case LOG_ERR:
				cout << "error: ";
				break;
			case LOG_WARNING:
				cout << "warning: ";
				break;
		}

		cout << message << endl;
	}
}

void closeup (int retval) {

	// Stop the server
	if(nb_server) {

		nb_server->stop();
		nb_server.reset(); // Release the object, since it was global
	}

	if(daemonized){

		closelog();
	}

	exit(retval);
}

void signal_handler(int signum){

	if(signum==SIGTERM || signum==SIGINT){

		writelog(LOG_NOTICE,string("caught signal. Closing..."));
	// Stop the server
		if(nb_server) {

			nb_server->stop();
			nb_server.reset(); // Release the object, since it was global
		} 
	 }

}


void thrift_logger (const char* str) {	

	writelog(LOG_NOTICE,string(str)); 
}


