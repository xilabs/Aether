#pragma once
#include "../Logger.h"
#include "WebsocketServer.h"
#include "../universe/Universe.h"
#include <boost/detail/atomic_count.hpp>
#include <vector>
#include <boost/thread.hpp>
#include <sstream>

using boost::shared_ptr;
using boost::detail::atomic_count;

extern shared_ptr<Logger> logger;

extern shared_ptr<Universe> universe;


class ServiceManager {

public:
	ServiceManager(){


	};

	~ServiceManager(){

	};

	void run(){

		// Start up the manager thread
		this->manager_run=shared_ptr<atomic_count>(new atomic_count(1));
		this->manager=shared_ptr<boost::thread>(new boost::thread(&ServiceManager::manage, this));

		websocket_server=shared_ptr<WebsocketServer>(new WebsocketServer());
		websocket_server->run(9002);

	};


	void send_moxel_message() {

		// Create a moxel package
		shared_ptr<MoxelMessage>message=shared_ptr<MoxelMessage>(new MoxelMessage(universe->voxel));
		websocket_server->broadcast_payload(message->blob, message->blob_size);

	};

	void stop(){

		// Retire the manager
		--(*this->manager_run);
		websocket_server->stop();
		this->manager->interrupt();
		this->manager->join();

	};

protected:

	/**
	 * We are the manager thread
	 *
	 * Send periodic messages, etc
	 */
	void manage(){

		while(*this->manager_run) {

			try {

				// Snooze a little
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
				this->send_moxel_message();

			} catch(boost::thread_interrupted& e) {

				// We were asked to leave?
				return;

			} catch(std::exception& e) {

				// TODO... something bad happened in the curator thread
			}
		}
	};

	// Counter for thread runloop.
//	shared_ptr<atomic_count> running;
	shared_ptr<boost::thread>manager;
	shared_ptr<atomic_count>manager_run;
	shared_ptr<WebsocketServer>websocket_server;

};