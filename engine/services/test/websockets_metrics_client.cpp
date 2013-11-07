
/**
 *  websockets_metrics_client
 *
 * Connect to aether over websockets, and print some stats
 *
 * Shamelessly ripped from the websocketspp example "sip_client"
 */

// Clock source
#define CLOCKSRC CLOCK_MONOTONIC_RAW


//#include <condition_variable>
#include "../websocketpp/websocketpp/config/asio_no_tls_client.hpp"
#include "../websocketpp/websocketpp/client.hpp"
#include <iostream>
#include <cmath>
#include <boost/thread/thread.hpp>
#include <time.h>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

// Create a server endpoint
client aether_client;


struct timespec ts;
double last_time;

double total_time;
unsigned int total_time_samples;
double total_deviation;
unsigned int suspicious;

void on_open(client* c, websocketpp::connection_hdl hdl) {

    std::cout << "connection open" << std::endl;

    // Start the timer
    clock_gettime(CLOCKSRC, &ts);
    last_time=(1000*(double)ts.tv_sec)+((double)ts.tv_nsec/1000000.0);


}

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {


//    std::cout << "Received a reply:" << std::endl;
    // Get elapsed time
    clock_gettime(CLOCKSRC, &ts);
    double current_time=(1000*(double)ts.tv_sec)+((double)ts.tv_nsec/1000000.0);
    double elapsed_time=current_time-last_time;

    // Calculate the averages
    total_time+=elapsed_time;
    total_time_samples++;
    double average_time=total_time/(double)total_time_samples;
    double deviation=fabs(elapsed_time-average_time);
    total_deviation+=deviation;
    double average_deviation=total_deviation/(double)total_time_samples;
    double fps=1000/average_time;

    // If a frame comes in less than 10ms after the last one, it is suspicious.
    if(elapsed_time < 10) suspicious++;

    // Print results
    std::cout << std::fixed << "\r(" << total_time_samples << ")\t last: " << elapsed_time << "\t average: " << average_time << "\t sigma: " << average_deviation << "\t (" << fps << " FPS, "<< suspicious <<" suspicious)                       " << std::flush;

    // Get ready for next time
    last_time=current_time;
}

int main(int argc, char* argv[]) {

    // Setup cout
    std::cout.precision(2);


	std::string uri = "ws://localhost:9002";

	if (argc == 2) {
	    uri = argv[1];
	}

	try {
        // We expect there to be a lot of errors, so suppress them
        aether_client.clear_access_channels(websocketpp::log::alevel::all);
        aether_client.clear_error_channels(websocketpp::log::elevel::all);

        // Initialize ASIO
        aether_client.init_asio();

        // Register our handlers
        aether_client.set_open_handler(bind(&on_open,&aether_client,::_1));
        aether_client.set_message_handler(bind(&on_message,&aether_client,::_1,::_2));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = aether_client.get_connection(uri, ec);

        aether_client.connect(con);

	    // Start the ASIO io_service run loop
        aether_client.run();

        // while(!received) {
        //     boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        // }

        std::cout << std::endl << "done (" << total_time_samples << " samples gathered)" << std::endl;

    } catch (const std::exception & e) {

        std::cout << e.what() << std::endl;

    } catch (websocketpp::lib::error_code e) {

        std::cout << e.message() << std::endl;

    } catch (...) {

        std::cout << "other exception" << std::endl;

    }
}
