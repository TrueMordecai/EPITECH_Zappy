require_relative("class_map.rb")

class Player
    attr_accessor :teamName, :position, :stage, :inventory, :orientation, :lastCommand, :map, :isReady

    def initialize(teamName)
        @teamName = teamName
        @isReady = false
        @stageRequirement = [[1, "l"], [2, "lds"], [2, "llspp"], [4, "ldssp"], [4, "lddsmmm"], [6, "lddsss"], [6, "llddssmmppt"]]
        @inventory = ""
        @stage = 1
        @c = 0
        @force = ""
        @orientation = -10
        @position = [0, 0]
        @lastCommand = ""
        @commandCount = 0
        @GFood = [-999, -999] # Nearest food (-1, -1) if not any.        
        @GRock = [-999, -999 , "none"]
        @life = 1260
    end

    def setPosition(pos)
        @position = [pos[0], pos[1]];
        @orientation = pos[2]
        @isReady = true;
    end

    def setMap(size)
        @map = Map.new(size[0], size[1]);
    end

    # Functiuns that count the number of unexplored cell that can be check by a player Look
    # return [Int] The count
    def countUnknownCell()
        x = 0
        y = 0
        c = [0, 4, 9, 16, 25, 36, 49, 64, 81] ## Number of cell to check, stage 0 == 0 cells
        res = 0

        for ite in 0..(c[@stage] -1)
            if (@position[0] + x < @map.sizeX and @position[1] + y < @map.sizeY)
                if (@map.getCell(x + @position[0], y + @position[1]).countItemsTotal() == -1)
                    res += 1
                end
            end
            if (@orientation == 0) # Orientation is north
                if (x * -1 == y) 
                    y -= 1
                    x = y
                else
                    x += 1
                end
            end
            if (@orientation == 1) # Orientation is east
                if (x == y)
                    x += 1
                    y = -(x)
                else 
                    y += 1
                end
            end
            if (@orientation == 2) # Orientation is south
                if (x == y * -1) 
                    y += 1
                    x = y
                else
                    x -= 1
                end
            end
            if (@orientation == 3) # Orientation is weast
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
        if (goal == "north" and @orientation == 0)
            return ("Aligned")
        end
        if (goal == "east" and @orientation == 1)
            return ("Aligned")
        end
        if (goal == "south" and @orientation == 2)
            return ("Aligned")
        end
        if (goal == "west" and @orientation == 3)
            return ("Aligned")
        end
        if (goal == "north")
            if (@orientation == 3)
                return ("Right")
            else
                return ("Left")
            end
        end
        if (goal == "east")
            if (@orientation == 0)
                return ("Right")
            else
                return ("Left")
            end
        end
        if (goal == "south")
            if (@orientation == 1)
                return ("Right")
            else
                return ("Left")
            end
        end
        if (goal == "west")
            if (@orientation == 2)
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
        if (x == -999 and y == -999)
            puts ("RANDOMIZING !!")
            x = rand() % @map.sizeX
            x = rand() % @map.sizeX
        end
        
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

    def gotRitualRequirement()
        req = @stageRequirement[@stage - 1][1]
        save = true
        for c in req.split('').uniq
            if (@inventory.count(c) < req.count(c))
                save = false  
            end
        end
        return (save)
    end

    # Function that compute the ai next move
    # If (too much unknown cell in front of me) Return "Look"
    # If (im low hp and im not on a food tile) return ($PathToFood) 
    # If (im low hp and im on a food tile) return (Take food)
    # If (i can take needed rocks) return (Take $Rocks)
    # return [String] with the next move
    def computeIa()
        bfr = ""
        ca = [0, 4, 9, 16, 25, 36, 49, 64, 81]
        @map.updateCounter()
        puts ("COMPUTE AI : Im in #{@position} Looking at #{orientationToString(@orientation)}. Inventory : (#{@inventory}). HP #{@life}, cc #{@commandCount}")
        puts (countUnknownCell().to_f)
        if (countUnknownCell().to_f > ca[stage].to_f * 0.4) # If there is more unknown cell than know one, then Look arround !
            return ("Look")
        end
        if (@commandCount % 5 == 0)
            return ("Inventory")
        end 
        
        if (gotRitualRequirement() and @life > 300 and @stage == 1)
            puts ("INCANTATION TIME")
            return ("Incantation")
        end

        if (@life <= 800) # Life threshold
            bfr = fastWay(@GFood[0], @GFood[1])
            puts ("Im goind to #{@GFood}, doing #{bfr}")
            if (bfr == "Arrived")
                return ("Take food")
            end
            return (bfr)
        end
        

        bfr = fastWay(@GRock[0], @GRock[1])
        puts ("Im goind to #{@GRock}, doing #{bfr}")
        if (bfr == "Arrived")
            return ("Take #{@GRock[2]}")
        end
        return (bfr)
    end

    # Ask the player what is the next move, set @lastcommand to it
    # return [String] containing the command.
    def getNextMove()
        if (!@isReady)
            return ("")
        end
        if (@force == "") 
            @lastCommand = computeIa()
        else 
            puts ("FORCING #{@force}")
            @lastCommand = @force
            @force = ""
        end
        @commandCount += 1
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
            @map.update_cell(y + @position[1], x + @position[0], cells_content)
            #####################
            if (@orientation == 0) # Orientation is north
                if (x * -1 == y) 
                    y -= 1
                    x = y
                else
                    x += 1
                end
            end
            #####################
            if (@orientation == 1) # Orientation is east
                if (x == y)
                    x += 1
                    y = -(x)
                else 
                    y += 1
                end
            end
            #####################
            if (@orientation == 2) # Orientation is south
                if (x == y * -1) 
                    y += 1
                    x = y
                else
                    x -= 1
                end
            end
            #####################
            if (@orientation == 3) # Orientation is weast
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
                if (@map.getCell(ite_posX, ite_posY).getItem("food") >= 1)
                    if ((@position[0] - ite_posX).abs + (@position[1] - ite_posY).abs < (@position[0] - save[0]).abs + (@position[1] - save[1]).abs)
                        #puts ("Found food in #{ite_posX}/#{ite_posY}")
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

    # Functiuns that compute the needed rocks from inventory
    # Return [String] Containing whats is needed
    def computeNeededRocks()
        bfr = ""
        for i in (@stage - 1)..(@stageRequirement.size - 1)
            bfr += @stageRequirement[i][1]
        end
        for c in @inventory.split('')
            bfr.sub!(c, "")
        end
        return bfr
    end

    def levelUp()
        puts ("Level Up !")
        if (@stage < 8)
            @stage += 1;
        end
    end

    # Return a comprehensive string of a direction : 0 -> "north"
    # @param dir [Int] [0, 1, 2, 3].include?(dir) must be true
    # return [String]
    def orientationToString(dir)
        if (![0, 1, 2, 3].include?(dir))
            return ("ERROR")
        end
        if (dir == 0)
            return ("North")
        end
        if (dir == 1)
            return ("East")
        end
        if (dir == 2)
            return ("South")
        end
        if (dir == 3)
            return ("West")
        end
    end

    # Return a comprehensive string of an item : "l" -> "linemate"
    # @param char [String] String of size 1
    # return [String]
    def itemToString(char)
        if (char == "l")
            return "linemate"
        end
        if (char == "d")
            return "deraumere"
        end
        if (char == "s")
            return "sibur"
        end
        if (char == "m")
            return "mendiane"
        end
        if (char == "p")
            return "phiras"            
        end
        if (char == "t")
            return "thystame"
        end
        return ("nothing")
    end

    # Update GRock position
    # return [Void]
    def updateGRock()
        ite_posX = 0
        ite_posY = 0
        save = [-999, -999, "none"]
        if (!@map)
            return
        end
        needed = computeNeededRocks()
        while ite_posY != @map.sizeY 
            while ite_posX != @map.sizeY
                for c in needed.split('')
                    if (@map.getCell(ite_posX, ite_posY).getItem(itemToString(c)) >= 1)
                        if ((@position[0] - ite_posX).abs + (@position[1] - ite_posY).abs < (@position[0] - save[0]).abs + (@position[1] - save[1]).abs)
                            save = [ite_posX, ite_posY, itemToString(c)]
                        end
                    end
                end
                ite_posX += 1
            end
            ite_posX = 0
            ite_posY += 1
        end
        @GRock = save
    end

    # Functiuns that absolutely need to be call at the end of the main loop, please i beg you, call me baybe. Update a lot of this
    # return [Void]
    def update()
        updateGFood()
        updateGRock()
    end
    

    # Update orientation if move was either "Left" or "Right"
    # @params [String] ori either "Left" or "Right"
    # @params [Bool] debug
    # return [Void]
    def updateOrientation(ori, debug = false)
        if (debug)
            print ("@orientation update from #{@orientation} -> ")
        end
        if (ori == -10)
            return
        end
        if (ori == "Right")
            @orientation += 1
        end
        if (ori == "Left")
            @orientation -= 1
        end
        if (@orientation < 0)
            @orientation = 3
        end
        if (@orientation > 3)
            @orientation = 0
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
        if (@orientation == 0)
            @position[1] -= 1
        end
        if (@orientation == 1)
            @position[0] += 1
        end
        if (@orientation == 2)
            @position[1] += 1
        end
        if (@orientation == 3)
            @position[0] -= 1
        end
        if debug
            puts (@position)
        end
    end

    # Functiuns that update inventory and life
    # @params inv [Array] containing inventory [$item $quantity]
    # return [Bool] treu if the inventory was well tracked, false otherwise
    def updateInventory(inv)
        invbfr = ""
        for i in inv
            if (i.split[0] == "food")
                @life = i.split[1].to_i
            else 
                invbfr += i.split(" ")[0][0].to_s * i.split[1].to_i
            end
        end
        if (@inventory.split().sort().join != invbfr.split().sort().join)
            return (false)
        end
        return (true)
    end

    # Functiun that remove item from mind map
    # @params [Bool] debug
    # return [Void]
    def takeItem(debug = false)
        if (debug)
            puts ("Removing #{@lastCommand.split[1]} from #{@position[0]}, #{@position[1]}")
        end
        if (@lastCommand.split[1] != "food")
            @inventory += @lastCommand.split[1][0]
        end
        @map.removeItem(@position[0], @position[1], @lastCommand.split[1])
    end

    # Functiuns that force the next move
    # @params [String] Next move to force
    def forceNextMove(move)
        @force = move
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