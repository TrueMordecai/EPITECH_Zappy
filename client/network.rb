require 'socket'

class Network
    attr_accessor :hostname, :port, :socket

    # Initialize method
    # @param hName [String], ip of the machine
    # @param p [Int] port of the server
    # return [Void]
    def initialize(hName = "127.0.0.1", p = 33000)
        @hostname = hName
        @port = port
        @socket = TCPSocket.open(@hostname, @port)
    end
end