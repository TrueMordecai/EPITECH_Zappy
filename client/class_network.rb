require 'socket'
class IO
    def readline_nonblock
        rlnb_buffer = ""
        while ch = self.read_nonblock(1) 
            rlnb_buffer << ch
            if ch == "\n" then
                result = rlnb_buffer
                return result
            end
        end     
    end
end

class Network
    attr_accessor :hostname, :port, :socket, :commands

    # Initialize method
    # @param hName [String], ip of the machine
    # @param p [Int] port of the server
    # return [Void]
    def initialize(hName, p)
        @commands = []
        @hostname = hName
        @port = p
        @socket = TCPSocket.open(@hostname, @port)
    end

    # Get all the last server command still unread, in fact read to the \n
    # return [String] of string not \n terminated
    def getServerCommmand()
        bfr = ""         
        begin 
            bfr = @socket.readline_nonblock
        rescue
            bfr = ""
        end
        return (bfr)
    end

    # Send a command to the server.
    # @param command [String] The command sent to the server
    # return [Void]
    def sendCommand(command, debug = false)
        if (debug)
            print ("Command sent to the server : '#{command}'")
        end
        if (command[-1] != '\n')
            if (debug)
                print " + \\n "
            end
            command = command + "\n"
        end
        if (debug)
            puts
        end
        print "'#{command}'"
        @socket.write(command)
    end
end