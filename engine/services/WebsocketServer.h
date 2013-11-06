#pragma once
#include <set>
#include <vector>
#include <sstream>
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include <boost/shared_ptr.hpp>
#include "../Logger.h"

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
        server.init_asio();
                
        server.set_open_handler(bind(&WebsocketServer::on_open,this,::_1));
        server.set_close_handler(bind(&WebsocketServer::on_close,this,::_1));
//        server.set_message_handler(bind(&WebsocketServer::on_message,this,::_1,::_2));

          this->manager=con_msg_man_type::ptr(new con_msg_man_type());
    }
    
    void on_open(connection_hdl hdl) {
        m_connections.insert(hdl);
    }
    
    void on_close(connection_hdl hdl) {
        m_connections.erase(hdl);
    }
    
    // void on_message(connection_hdl hdl, server_t::message_ptr msg) {
    //     //for (auto it : m_connections) {
    //     for(con_list::iterator it=m_connections.begin(); it!=m_connections.end(); ++it){
    //         server.send(*it,msg);
    //     }
    // }

    void broadcast_payload(void* payload, size_t len){

        // std::stringstream s;
        // s << "message is " << len << "bytes";
        // logger->notice(s.str());

        // Create a message
        message_type::ptr msg = this->manager->get_message(websocketpp::frame::opcode::BINARY,len);
        msg->set_payload((const void*)payload, len);


        // Send to all connections
        for(con_list::iterator it=m_connections.begin(); it!=m_connections.end(); ++it){
            
            logger->notice("Broadcasting moxels to connection");
           server.send(*it, msg);         
        }

    }

    void run(uint16_t port) {
        server.listen(port);
        server.start_accept();
        server.run();
    }

    void stop() {
        server.stop();
    }

private:
    typedef std::set<connection_hdl> con_list;

    server_t server;
    con_list m_connections;
    con_msg_man_type::ptr manager;
};










