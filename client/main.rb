#!/usr/bin/env ruby
#coding: utf-8

require_relative 'class_parsing.rb'
require_relative 'class_network.rb'
require_relative 'class_map.rb'
require_relative 'optionCheck.rb'

STDOUT.sync = true # in case of...

options = optionsCheck(a = ARGV)
net = Network.new(options["host"], options["port"])
parser = Parsing.new()
loop do
    commands = ""
    commands = net.getServerCommmand()
    print commands
    if (commands == "WELCOME\n")
        net.sendCommand(options["name"], true)
    end
    if (commands == "dead\n")
        puts("I juste died :(");
        exit(0)
    end
end