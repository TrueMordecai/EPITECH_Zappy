

class Player
    attr_accessor :teamName, :position, :stage, :inventory, :orientation, :lastCommand

    def initialize(teamName)
        @teamName = teamName
        @isReady = false
        @stage = 1
        @c = 0
    end

    def setPosition(pos)
        @position = pos;
        puts ("My position is set");
        @isReady = true;
    end

    def computeIa()
        if (@lastCommand == "Forward")
            return ("Left")
        end
        return ("Forward")
    end

    def getNextMove()
        if (!@isReady)
            return ("")
        end
        @lastCommand = (computeIa())
        @isReady = false
        return (lastCommand)
    end

    def setReady()
        @isReady = true
    end
end