#!/usr/bin/env ruby
#coding: utf-8

require_relative 'parsing.rb'
require_relative 'network.rb'
require_relative 'map.rb'

n = Network.new("127.0.0.1", 33000)

while line = s.gets     # Read lines from the socket
    puts line.chop       # And print with platform line terminator
end