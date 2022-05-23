class Command
    attr_accessor :name, :argCount

    # Add a new command
    # @param name [String] command name, can't be empty.
    # @param argumentCount [Int] argument needed by the command.
    # return [Void]
    def initialize(name, argCount)
        @name = name
        @argCount = argCount
    end
end