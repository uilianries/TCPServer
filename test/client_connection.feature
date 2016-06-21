Feature: I want to bind on port 30000 by TCP connection

  Scenario: The host machine
    Given tcp-server is running
     When I bind to port 30000
      And I use a stream socket
     Then I receive a connection event from server
     When I send' "foobar" to server
     Then I read "foobar" at /var/log/tcp-server.log