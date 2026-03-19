WebSocket++ (0.8.2.1)
==========================

Note from the "Forker" Author
=================================
**The official WebSocket++ hasn't got any updates since 2020**
This is a personal fork and addresses a few outdated stuff, asio support and so on.
I plan to maintain a bit here and there, but I have a full time job, so it may not
be that easy. I want to try to port it to C++ 23 and ditch boost, and a few
opinionated stuff here and there. This is too good to be deprecated.


Official WebSocket++ readme
==============================
WebSocket++ is a header only C++ library that implements RFC6455 The WebSocket
Protocol. It allows integrating WebSocket client and server functionality into
C++ programs. It uses interchangeable network transport modules including one
based on raw char buffers, one based on C++ iostreams, and one based on Asio 
(either via Boost or standalone). End users can write additional transport
policies to support other networking or event libraries as needed.

Major Features
==============
* Full support for RFC6455
* Partial support for Hixie 76 / Hybi 00, 07-17 draft specs (server only)
* Message/event based interface
* Supports secure WebSockets (TLS), IPv6, and explicit proxies.
* Flexible dependency management (C++11 Standard Library or Boost)
* Interchangeable network transport modules (raw, iostream, Asio, or custom)
* Portable/cross platform (Posix/Windows, 32/64bit, Intel/ARM/PPC)
* Thread-safe

Get Involved
============

[![Build Status](https://travis-ci.org/zaphoyd/websocketpp.png)](https://travis-ci.org/zaphoyd/websocketpp)

**Project Website**
http://www.zaphoyd.com/websocketpp/

**User Manual**
http://docs.websocketpp.org/

**Parent GitHub Repository**
https://github.com/zaphoyd/websocketpp/

Author
======
Peter Thorson - websocketpp@zaphoyd.com
