#!/usr/bin/env ruby
# coding: utf-8

require_relative 'class_command.rb'

class Parsing

    EXPECT_NO_FIXED_SIZE = -99
    UNKNOWN_COMMAND = Command.new("", -1)
    attr_accessor :debug

    # Initilize all the functiuns needed for the program to work
    # @param dg [Bool] Add some debug on some functiuns. Can be change at any time thank to attr accesor
    def initialize(dg = false)
        @debug = dg
        @commandsAvailible = []
        addCommand("msz", 2)
        addCommand("bct", 9)
        addCommand("bct", EXPECT_NO_FIXED_SIZE)
        addCommand("tna", EXPECT_NO_FIXED_SIZE)
        addCommand("pnw", 6)
        addCommand("ppo", 4)
        addCommand("plv", 2)
        addCommand("pin", 10)
        addCommand("pex", 1)
        addCommand("pbc", 2)
        addCommand("pic", EXPECT_NO_FIXED_SIZE)
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
        for c in @commandsAvailible
            if command == c.name and argumentNeeded == c.argCount
                if (@debug)
                    puts ("Commands #{command.name} is already added")
                end
                return false
            end
        end
        @commandsAvailible.append(Command.new(command, argumentNeeded))
        if @debug 
           puts ("Command n°#{@commandsAvailible.size()} [#{@commandsAvailible[-1].name}] were added.")
        end
        return true
    end 
    private :addCommand

    # Check validity of a unparsed command
    # @param unparsedCommand [String] command name, can't be empty.
    # return [Command] the command found or an unknow command 
    def checkCommand(unparsedCommand)
        command = unparsedCommand.chomp.split
        for c in @commandsAvailible
            if (command[0] == c.name) and ((command.size() - 1 == c.argCount) or (c.argCount == EXPECT_NO_FIXED_SIZE))
                return (c)
            end
            print ("#{c.name} != #{command[0]}, #{c.argCount} != #{command.size}\n")
        end
        return (UNKNOWN_COMMAND)
    end

    # Print commands list for debug purpose only
    # return [Void]
    def printCommandsList()
        for c in @commandsAvailible
            if (c.argCount != EXPECT_NO_FIXED_SIZE)
                puts("Commands #{c.name}, #{c.argCount} are needed")
            else
                puts("Commands #{c.name}, a lot of arguments are required")
            end
        end
    end

    # Translate an unparsed command to an already known command and his arguments.
    # If the command should give multiple line of date, this functiusn handle it
    # @param unparsedCommand [String] command name, can't be empty
    # return [Command, (Void, String, Array)] 
    def toCommand(unparsedCommand)
        c = checkCommand(unparsedCommand)
        if c == UNKNOWN_COMMAND
            return [c]
        end
        if c.argCount == EXPECT_NO_FIXED_SIZE
            return (unparsedCommand.split.drop(1).join(" ").split("\n"))
        end
        if c.argCount == 0
            return [c]
        end
        return ([c, unparsedCommand.split.drop(1)])
    end 
end