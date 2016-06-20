# TCPServer [![Build Status](https://travis-ci.org/uilianries/TCPServer.svg?branch=master)](https://travis-ci.org/uilianries/TCPServer) [![codecov.io](https://codecov.io/github/uilianries/TCPServer/coverage.svg?branch=master)](https://codecov.io/github/uilianries/TCPServer=master) [![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

Simple Asynchronous TCP server.

## Usage
To run as daemon:
$ tcp-server --daemon

The application uses the file at /etc/tcp-server.json as configuration.

## Features
- Select port to listen
- Select file log size for data stream

## install
- mkdir build
- cd build
- conan install ..
- cmake ..
- cmake --build . --config release
- sudo make install

## Prerequisite
- CMake 3.0.2
- Boost 1.60
- Poco 1.7.3
- Conan.io 0.9.4
- GTest 1.7