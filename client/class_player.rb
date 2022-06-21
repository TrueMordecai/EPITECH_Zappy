require_relative("class_map.rb")

class Player
    attr_accessor :teamName, :position, :stage, :inventory, :orientation, :lastCommand, :map, :isReady

    def initialize(teamName)
        @teamName = teamName
        @isReady = false
        @stage = 1
        @c = 0
        @orientation = 1
        @position = [0, 0]
        @lastCommand = ""
    end

    def setPosition(pos)
        @position = pos;
        puts ("My position is set");
        @isReady = true;
    end

    def setMap(size)
        @map = Map.new(size[0], size[1]);
        puts ("Map is generated in my mind");
    end

    def computeIa()
        if (@lastCommand == "")
            return ("Look") # TEMP
        end
        if (@lastCommand == "Forward")
            return ("Left")
        end
        return ("Forward")
    end

    def getNextMove()
        if (!@isReady)
            return ("")
        end
        @lastCommand = computeIa()
        #print "last command is "
        #puts @lastCommand
        @isReady = false
        return (@lastCommand)
    end

    def setReady()
        @isReady = true
    end

    # Repere comme en sfml
    def updateMap(command)
        x = 0
        y = 0
        counter = 0
        for cells_content in command.split(",")
            puts ("add #{cells_content} to #{x}, #{y}")
            @map.update_cell(y + @position[1], x + @position[0], cells_content)
            #####################
            if (@orientation == 1) # Orientation is north
                if (x * -1 == y) 
                    puts ("Breaking : #{x}, #{y}")
                    y -= 1
                    x = y
                    puts ("After : #{x}, #{y}")
                else
                    x += 1
                end
            end
            #####################
            if (@orientation == 2) # Orientation is east
                if (x == y)
                    x += 1
                    y = -(x)
                end
                y += 1
            end
            #####################
            if (@orientation == 3) # Orientation is south
                if (-x == y) 
                    y += 1
                    x = y
                end
                x -= 1
            end
            #####################
            if (@orientation == 4) # Orientation is weast
                if (x == y) 
                    x -= 1
                    y = -(y)
                end
                y -= 1
            end
        end 
    end

end


#   
#  38.............50
#   27...........37
#    18.........26
#     11.......17
#      9.....10
#       45678
#        123
#         0       