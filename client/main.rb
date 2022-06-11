#!/usr/bin/env ruby
#coding: utf-8

class String
    def is_integer?
        self.to_i.to_s == self
    end
end

require_relative 'class_parsing.rb'
require_relative 'class_network.rb'
require_relative 'class_map.rb'
require_relative 'class_player.rb'
require_relative 'optionCheck.rb'

STDOUT.sync = true # in case of...

options = optionsCheck(a = ARGV)
net = Network.new(options["host"], options["port"])
parser = Parsing.new()
player = Player.new(options["name"])
mapSize = []

loop do
    commands = ""
    commands = net.getServerCommmand()
    if (commands == "WELCOME\n")
        net.sendCommand(options["name"], false)
    end
    if (commands.split.all? {|i| i.is_integer?} and commands.split.size == 2 and mapSize.size != 0)
        puts ("set Position too #{commands.split.map(&:to_i)}")
        player.setPosition(commands.split.map(&:to_i))
    end
    if (commands.split.all? {|i| i.is_integer?} and commands.split.size == 2 and mapSize.size == 0)
        puts ("map size = #{commands.split.map(&:to_i)}")
        mapSize = commands.split.map(&:to_i)
    end
    if (commands == "dead\n")
        puts("I juste died :(");
        exit(0)
    end    
    #net.sendCommand(player.getNextMove(), true)
end