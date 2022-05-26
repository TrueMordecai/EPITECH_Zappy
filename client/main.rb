#!/usr/bin/env ruby
#coding: utf-8

require_relative 'parsing.rb'
require_relative 'network.rb'
require_relative 'map.rb'

options = {}
options[:host] = "localhost"
for i in 0..ARGV.size - 1 do
    for opt in [["-p", "port"], ["-n", "name"], ["-h", "host"]]
        if (ARGV[i] == opt[0] and i + 1 <= ARGV.size - 1 and !ARGV[i + 1].include?('-'))
            options[opt[1]] = ARGV[i + 1]
        end
    end
end
if (options["port"].nil? or options["name"].nil?)
    STDERR.print("ERROR : No port or name specified\n")
    exit (84)
end

s = TCPSocket.open(options["host"], options["port"])

while line = s.gets     # Read lines from the socket
   puts line.chop       # And print with platform line terminator
end
