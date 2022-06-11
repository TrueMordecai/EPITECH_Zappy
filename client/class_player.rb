

class Player
    attr_accessor :teamName, :position, :stage, :inventory, :orientation

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

    def getNextMove()
        if (!@isReady)
            return ("")
        end
        if @c < 10
            @c = @c + 1
            return ("Forward")
        end
    end
end