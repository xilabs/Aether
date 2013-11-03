#pragma once
#include "../Logger.h"
#include "WebsocketServer.h"
#include <boost/detail/atomic_count.hpp>

using boost::shared_ptr;
using boost::detail::atomic_count;

extern shared_ptr<Logger> logger;



class ServiceManager {

public:
	ServiceManager(){


	};

	void run(){

		running=shared_ptr<atomic_count>(new atomic_count(1));
		websocket_server=shared_ptr<WebsocketServer>(new WebsocketServer());
		websocket_server->run(9002);
//		while(*running!=0) { sleep(1); }

	};

	void stop(){

		--(*running);
		websocket_server->stop();

	};

protected:

	// Counter for thread runloop.
	shared_ptr<atomic_count> running;
	shared_ptr<WebsocketServer>websocket_server;

};