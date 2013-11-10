#pragma once
#include <set>
#include <vector>
#include <sstream>
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include "../Logger.h"
#include "User.h"

extern boost::shared_ptr<Logger> logger;


typedef websocketpp::server<websocketpp::config::asio> server_t;
typedef websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> message_type;
typedef websocketpp::message_buffer::alloc::con_msg_manager<message_type> con_msg_man_type;

con_msg_man_type::ptr manager(new con_msg_man_type());

using boost::shared_ptr;
using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class WebsocketServer {

public:
    WebsocketServer() {

        // Logging
//        server.set_access_channels(websocketpp::log::alevel::all);
//        server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        server.clear_access_channels(websocketpp::log::alevel::all);

        server.init_asio();
                
        server.set_open_handler(bind(&WebsocketServer::on_open,this,::_1));
        server.set_close_handler(bind(&WebsocketServer::on_close,this,::_1));
        server.set_message_handler(bind(&WebsocketServer::on_message,this,::_1,::_2));

          this->manager=con_msg_man_type::ptr(new con_msg_man_type());
    }
    
    void on_open(connection_hdl hdl) {

        // Add a new connection to our list
        {
            boost::mutex::scoped_lock con_list_lock(con_list_guard);
            m_connections.insert(hdl);
        }

        // Add a new user
        shared_ptr<User> user=shared_ptr<User>(new User());
        {
            boost::mutex::scoped_lock users_lock(users_guard);
            users.insert(std::pair<connection_hdl, shared_ptr<User> >(hdl, user));
        }

        // Send welcome message
        std::string welcome="["+user->username+"] JOIN";
        broadcast_string(welcome);
    }
    
    void on_close(connection_hdl hdl) {


        // Remove the connection
        {
            boost::mutex::scoped_lock con_list_lock(con_list_guard);
            m_connections.erase(hdl);
        }

        // Get the user who left
        shared_ptr<User>user;
        {
            boost::mutex::scoped_lock users_lock(users_guard);
            user=users[hdl];
        }

        // Send goodbye message
        std::string goodbye="["+user->username+"] SCAT";
        broadcast_string(goodbye);

        // Erase connection handle
        users.erase(hdl);
    }
    
    void on_message(connection_hdl hdl, server_t::message_ptr msg) {


        // Only accept text messages
        if(msg->get_opcode()==websocketpp::frame::opcode::BINARY)
            return;

        // Get the user who sent this message
        shared_ptr<User>user;
        {
            boost::mutex::scoped_lock lock(users_guard);
            user=users[hdl];
        }

        // Was this a command?
        if(msg->get_payload() == "where"){

            server.send(hdl, user->get_velocity(), websocketpp::frame::opcode::TEXT);
            return;
        }

        // Get the message
        std::string message = "[" + user->username + "] " + msg->get_payload();

        // Broadcast it
        broadcast_string(message);
    }

    void broadcast_payload(void* payload, size_t len){

        boost::mutex::scoped_lock lock(con_list_guard);

        // Create a message
        message_type::ptr msg = this->manager->get_message(websocketpp::frame::opcode::BINARY,len);
        msg->set_payload((const void*)payload, len);


        // Send to all connections
        for(con_list::iterator it=m_connections.begin(); it!=m_connections.end(); ++it){
            
           server.send(*it, msg);         
        }

    }

    void broadcast_string(string str){

        // Log the message
        logger->notice(str);


        message_type::ptr msg = this->manager->get_message(websocketpp::frame::opcode::TEXT, str.length());
        msg->set_payload(str);

        // Send to all connections
        boost::mutex::scoped_lock lock(con_list_guard);
        for(con_list::iterator it=m_connections.begin(); it!=m_connections.end(); ++it){
            
           server.send(*it, msg);         
        }
    }

    void run(uint16_t port) {
        server.listen(port);
        server.start_accept();
        server.run();
    }

    void stop() {
        broadcast_string("*** END OF UNIVERSE ***");
        server.stop();
    }

private:
    typedef std::set<connection_hdl> con_list;      
    boost::mutex con_list_guard;
    server_t server;
    con_list m_connections;
    std::map<connection_hdl,shared_ptr<User> > users;
    boost::mutex users_guard;
    con_msg_man_type::ptr manager;
};










