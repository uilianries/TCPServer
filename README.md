# TCPServer [![Build Status](https://travis-ci.org/uilianries/TCPServer.svg?branch=master)](https://travis-ci.org/uilianries/TCPServer) [![codecov.io](https://codecov.io/github/uilianries/TCPServer/coverage.svg?branch=master)](https://codecov.io/github/uilianries/TCPServer=master) [![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

Simple Asynchronous TCP server.

This server listen a port and log each received message in a log file.

## Usage
Run as daemon:

_tcp-server --daemon_

The application read the file /etc/tcp-server/tcp-server-config.json as
 configuration.

All messages receives on server are logged at /tmp/tcp-server-message.log
All application information are logged at /tmp/tcp-server-app.log

## Features
- Select port to listen
- Select file log size for data stream
- Select log root directory

## install

Execute install.sh

or

Follow the steps:

_mkdir build_

_cd build_

_conan install .._

_cmake .._

_cmake --build . --config release_

_sudo make install_


## Prerequisite
- cmake 3.0.2
- conan.io 0.9.4
