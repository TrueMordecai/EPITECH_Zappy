#!/usr/bin/env ruby
# coding: utf-8

require_relative 'command.rb'



class Parsing

    EXPECT_NO_SIZE = -99
    
    def initialize()
        @commandsList = []
        addCommand("msz", 2)
        addCommand("bct", 9)
        addCommand("tna", EXPECT_NO_SIZE)
        addCommand("pnw", 6)
        addCommand("ppo", 4)
        addCommand("plv", 2)
        addCommand("pin", 10)
        addCommand("pex", 1)
        addCommand("pbc", 2)
        addCommand("pic", EXPECT_NO_SIZE)
        addCommand("pie", 3)
        addCommand("pfk", 1)
        addCommand("pdr", 2)
        addCommand("pgt", 2)
        addCommand("pdi", 1)
        addCommand("enw", 4)
        addCommand("eht", 1)
        addCommand("ebo", 1)
        addCommand("edi", 1)
        addCommand("sgt", 1)
        addCommand("sst", 1)
        addCommand("seg", 1)
        addCommand("suc", 1)
        addCommand("smg", 1)
    end
    
    # Add a command, add them to ... Should be only called one times per command
    # @param name [String] command name, can't be empty.
    # @param argumentNeeded [Int] argument needed by the command.
    # return [Bool]. True if command is added false otherwise.
    def addCommand(command, argumentNeeded)
        for c in @commandsList
            if command == c.name
                return false
            end
        end

        @commandsList.append(Command.new(command, argumentNeeded))
    end 
    private :addCommand

    # Check validity of a unparsed command
    # @param unparsedCommand [String] command name, can't be empty.
    # return [Bool]
    def checkCommand(unparsedCommand)
        command = unparsed.chomp.split
        for c in commandsList
            if (command[0] == c.name) and ((command.size() - 1 == c.argCount) or (c.argCount == EXPECT_NO_SIZE  ))
                return (true)
            end
        end
        return (false)
    end

    # Print commands list for debug purpose only
    # return [Void]
    def printCommandsList()
        for c in @commandsList
            if !c.argCount == -99
                puts("Commands #{c.name}, #{c.argCount} are needed")
            else
                puts("Commands #{c.name}, a lot of arguments are required")
            end
        end
    end

end