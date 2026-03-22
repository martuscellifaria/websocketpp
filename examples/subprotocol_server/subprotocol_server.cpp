#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using std::placeholders::_1;
using std::placeholders::_2;
using std::bind;
using std::ref;


bool validate(server & s, connection_hdl hdl) {
    server::connection_ptr con = s.get_con_from_hdl(hdl);

    std::cout << "Cache-Control: " << con->get_request_header("Cache-Control") << std::endl;

    const std::vector<std::string> & subp_requests = con->get_requested_subprotocols();
    std::vector<std::string>::const_iterator it;

    for (it = subp_requests.begin(); it != subp_requests.end(); ++it) {
        std::cout << "Requested: " << *it << std::endl;
    }

    if (subp_requests.size() > 0) {
        con->select_subprotocol(subp_requests[0]);
    }

    return true;
}

int main() {
    try {
        server s;

        s.set_validate_handler(bind(&validate,ref(s),::_1));

        s.init_asio();
        s.listen(9005);
        s.start_accept();

        s.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}
