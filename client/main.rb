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
    ## SET PLAYER POS If command is 2 integer split by a space and map size have been given
    if (commands.split[0] == "ppo" and mapSize.size != 0)
        cbfr = commands.split.drop(1)
        puts ("set Position too #{cbfr.map(&:to_i)}")
        player.setPosition(cbfr.map(&:to_i))
    end

    ## SET MAP SIZE If command is 2 integer split by a space and map size havn't been given
    if (commands.split[0] == "msz" and mapSize.size == 0)
        cbfr = commands.split.drop(1)
        player.setMap(cbfr.map(&:to_i))
        puts ("map size = #{cbfr.map(&:to_i)}")
        mapSize = cbfr.map(&:to_i)
    end

    ## If the player die
    if (commands == "dead\n")
        puts("I juste died :(");
        exit(0)
    end
    
    ## If player wait for a response of look
    if (player.lastCommand == "Look")
        player.updateMap("player Sibur,player,player,player")
        player.map.printMap()
        player.isReady = true
    end
    
    ## If commands have been well executed
    if (commands == "ok\n")
        player.setReady() ##TEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEMP
    end
    net.sendCommand(player.getNextMove(), true)
end