/*
 * Copyright (c) 2014, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef WEBSOCKETPP_CONFIG_ASIO_HPP
#define WEBSOCKETPP_CONFIG_ASIO_HPP

#include <websocketpp/config/core.hpp>
#include <websocketpp/transport/asio/endpoint.hpp>

namespace websocketpp {
namespace config {

/// Server config with asio transport and TLS disabled
struct asio : public core {
    using type = asio;
    using base = core;

    using concurrency_type = base::concurrency_type;

    using request_type = base::request_type;
    using response_type = base::response_type;

    using message_type = base::message_type;
    using con_msg_manager_type = base::con_msg_manager_type;
    using endpoint_msg_manager_type = base::endpoint_msg_manager_type;

    using alog_type = base::alog_type;
    using elog_type = base::elog_type;

    using rng_type = base::rng_type;

    struct transport_config : public base::transport_config {
        using concurrency_type = type::concurrency_type;
        using alog_type = type::alog_type;
        using elog_type = type::elog_type;
        using request_type = type::request_type;
        using response_type = type::response_type;
        using socket_type = websocketpp::transport::asio::basic_socket::endpoint;
    };

    using transport_type = websocketpp::transport::asio::endpoint<transport_config>;
};

} // namespace config
} // namespace websocketpp

#endif // WEBSOCKETPP_CONFIG_ASIO_HPP
