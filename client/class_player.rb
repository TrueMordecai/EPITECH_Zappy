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
        @GFood = [-999, -999] # Nearest food (-1, -1) if not any.        
        @life = 1260
    end

    def setPosition(pos)
        @position = [pos[0], pos[1]];
        @orientation = pos[2] + 1
        puts ("My position is set");
        @isReady = true;
    end

    def setMap(size)
        @map = Map.new(size[0], size[1]);
        puts ("Map is generated in my mind");
    end

    # Functiuns that count the number of unexplored cell that can be check by a player Look
    # return [Int] The count
    def countUnknownCell()
        x = 0
        y = 0
        c = [0, 4, 9, 16, 25, 36, 49, 64, 81] ## Number of cell to check, stage 0 == 0 cells
        res = 0

        for ite in 0..(c[@stage] -1)
            if (@map.getCell(x + @position[0], y + @position[1]).countItemsTotal() == -1)
                res += 1
            end
            if (@orientation == 1) # Orientation is north
                if (x * -1 == y) 
                    y -= 1
                    x = y
                else
                    x += 1
                end
            end
            if (@orientation == 2) # Orientation is east
                if (x == y)
                    x += 1
                    y = -(x)
                else 
                    y += 1
                end
            end
            if (@orientation == 3) # Orientation is south
                if (x == y * -1) 
                    y += 1
                    x = y
                else
                    x -= 1
                end
            end
            if (@orientation == 4) # Orientation is weast
                if (x == y) 
                    x -= 1
                    y = -(x)
                else
                    y -= 1
                end
            end
        end
        return res
    end

    # Functiuns that tells the ether left or right to go to the goal orientation, reminder 1 == north, 2 == east, 3 == south and 4 == west
    # @param [String] must be "north", "east", "south", "weast"
    # return [String] "Left", "Right" or "Aligned"
    def fastRotate(goal)
        if (goal == "north" and @orientation == 1)
            return ("Aligned")
        end
        if (goal == "east" and @orientation == 2)
            return ("Aligned")
        end
        if (goal == "south" and @orientation == 3)
            return ("Aligned")
        end
        if (goal == "west" and @orientation == 4)
            return ("Aligned")
        end
        if (goal == "north")
            if (@orientation == 4)
                return ("Right")
            else
                return ("Left")
            end
        end
        if (goal == "east")
            if (@orientation == 1)
                return ("Right")
            else
                return ("Left")
            end
        end
        if (goal == "south")
            if (@orientation == 2)
                return ("Right")
            else
                return ("Left")
            end
        end
        if (goal == "west")
            if (@orientation == 3)
                return ("Right")
            else
                return ("Left")
            end
        end    
    end

    # Functiun that return the next movement to do to go to the indicate pos
    # @param x = x goal
    # @param y = y goal
    # return [String] NOT \n terminated
    def fastWay(x, y)
        bfr = ""
        if (@position[0] == x and @position[1] == y)
            return ("Arrived")
        end
        if (x > @position[0])
            bfr = fastRotate("east")
            if (bfr == "Aligned")
                return ("Forward")
            end
            return (bfr)
        end
        if (x < @position[0])
            bfr = fastRotate("west")
            if (bfr == "Aligned")
                return ("Forward")
            end
            return (bfr)
        end
        if (y > @position[1])
            bfr = fastRotate("south")
            if (bfr == "Aligned")
                return ("Forward")
            end
            return (bfr)
        end
        if (y < @position[1])
            bfr = fastRotate("north")
            if (bfr == "Aligned")
                return ("Forward")
            end
            return (bfr)
        end
    end

    def computeIa()
        bfr = ""
        ca = [0, 4, 9, 16, 25, 36, 49, 64, 81]
        puts ("COMPUTE AI : IM IN #{@position} LOOKING #{@orientation}")
        if (@GFood.size != 2)
            print ("I WANT TO DIE, NOT CREATED\n")
        end
        puts ("#{countUnknownCell} unknown cells in front of me out of #{ca[stage]}")
        if (countUnknownCell() > ca[stage] - countUnknownCell) # If there is more unknown cell than know one, then Look arround !
            return ("Look")
        end
        if (@life <= 3000) # Life threshold
            bfr = fastWay(@GFood[0], @GFood[1])
            puts ("Im goind to #{@GFood}, doing #{bfr}")
            if (bfr == "Arrived")
                return ("Pick Food")
            end
            return (bfr)
        end
    end

    def getNextMove()
        if (!@isReady)
            return ("")
        end
        @lastCommand = computeIa()
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
        for cells_content in command.split(",")
            puts ("add #{cells_content} to #{x + @position[0]}, #{y + @position[1]}")
            @map.update_cell(y + @position[1], x + @position[0], cells_content)
            #####################
            if (@orientation == 1) # Orientation is north
                if (x * -1 == y) 
                    y -= 1
                    x = y
                else
                    x += 1
                end
            end
            #####################
            if (@orientation == 2) # Orientation is east
                if (x == y)
                    x += 1
                    y = -(x)
                else 
                    y += 1
                end
            end
            #####################
            if (@orientation == 3) # Orientation is south
                if (x == y * -1) 
                    y += 1
                    x = y
                else
                    x -= 1
                end
            end
            #####################
            if (@orientation == 4) # Orientation is weast
                if (x == y) 
                    x -= 1
                    y = -(x)
                else
                    y -= 1
                end
            end
        end 
    end
    
    # Update Gfood position
    # return [Void]
    def updateGFood()
        ite_posX = 0
        ite_posY = 0
        save = [-999, -999]
        if (!@map)
            return
        end
        while ite_posY != @map.sizeY 
            while ite_posX != @map.sizeY
                if (@map.getCell(ite_posX, ite_posY).Food >= 1)
                    if ((@position[0] - ite_posX).abs + (@position[1] - ite_posY).abs < (@position[0] - save[0]).abs + (@position[1] - save[1]).abs)
                        save = [ite_posX, ite_posY]
                    end
                end
                ite_posX += 1
            end
            ite_posX = 0
            ite_posY += 1
        end
        @GFood = save
    end

    # Functiuns that absolutely need to be call at the end of the main loop, please i beg you, call me baybe. Update a lot of this
    # return [Void]
    def update()
       updateGFood()
    end
    

    # Update orientation if move was either "Left" or "Right"
    # @params [String] ori either "Left" or "Right"
    # @params [Bool] debug
    # return [Void]
    def updateOrientation(ori, debug = false)
        if (debug)
            print ("@orientation update from #{@orientation} -> ")
        end
        if (ori == "Right")
            @orientation += 1
        end
        if (ori == "Left")
            @orientation -= 1
        end
        if (@orientation < 1)
            @orientation = 4
        end
        if (@orientation > 4)
            @orientation = 1
        end
        if debug
            puts (@orientation)
        end
    end

    
    # Update position if move was "Forward"
    # @params [Bool] debug
    # return [Void]
    def updatePosition(debug = false)
        if (debug)
            print ("@position update from #{@position} -> ")
        end
        if (@orientation == 1)
            @position[1] -= 1
        end
        if (@orientation == 2)
            @position[0] += 1
        end
        if (@orientation == 3)
            @position[1] += 1
        end
        if (@orientation == 4)
            @position[0] -= 1
        end
        if debug
            puts (@position)
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