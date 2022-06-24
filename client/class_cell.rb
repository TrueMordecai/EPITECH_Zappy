module Items
    FOOD = 0
    LINEMATE = 1    
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6
end

class Cell
    attr_accessor :posX, :posY, :Food, :Linemate, :Deraumere, :Sibur, :Mendiane, :Phiras, :Thysame, :playerNbr, :Counter

    # Replace the food of the cell
    # @param x [Int] x pos of the cell 
    # @param y [Int] y pos of the cell 
    # return [Void]
    def initialize(x, y)
        @posX = x
        @posY = y
        @Food = -1
        @Linemate = -1
        @Deraumere = -1
        @Sibur = -1
        @Mendiane = -1
        @Phiras = -1
        @Thysame = -1
        @playerNbr = -1
        @Counter = 0
    end

    # Replace the food of the cell
    # @param * [Int] quantity of item in the cell 
    # return [Void]
    def changeItemsPool(qFOOD, qLINEMATE, qDERAUMERE, qSIBUR, qMENDIANE, qPHIRAS, qTHYSTAME, playerNbr)
        @Food = qFOOD
        @Linemate = qLINEMATE
        @Deraumere = qDERAUMERE
        @Sibur = qSIBUR
        @Mendiane = qMENDIANE
        @Phiras = qPHIRAS
        @Thysame = qTHYSTAME
        @playerNbr = playerNbr
    end

    # Count the unity of food find in this cell, if unitialize return -1
    # return [Int]
    def countItemsTotal()
        #puts ("I count #{@Food + @Linemate + @Deraumere + @Sibur + @Mendiane + @Phiras + @Thysame}, (food #{@Food})")
        if (@Food == -1)
            return -1
        end
        return @Food + @Linemate + @Deraumere + @Sibur + @Mendiane + @Phiras + @Thysame
    end

    # Set contents in cur tile
    # @params [String] String containing elements separated by a space like "player food food", useful for "Look" command
    # return [Void]
    def setContents(content)
        @Food = 0
        @Linemate = 0
        @Deraumere = 0
        @Sibur = 0
        @Mendiane = 0
        @Phiras = 0
        @Thysame = 0
        @playerNbr = 0
        @Counter = 0
        for c in content.split(" ")
            if (c == "food")
                @Food += 1
            end
            if (c == "linemate")
                @Linemate += 1
            end
            if (c == "deraumere")
                @Deraumere += 1
            end
            if (c == "sibur")
                @Sibur += 1
            end
            if (c == "mendiane")
                @Mendiane += 1
            end
            if (c == "phiras")
                @Phiras += 1
            end
            if (c == "thystame")
                @Thysame += 1
            end
            if (c == "player")
                @playerNbr += 1
            end
        end
    end

    # Remove one items from cell
    # @params [String] items to remove
    # return [Void]
    def decreaseItem(item)
        if (item == "food")
            @Food = @Food - 1
        end
        if (item == "linemate")
            @Linemate = @Linemate - 1
        end
        if (item == "deraumere")
            @Deraumere = @Deraumere - 1
        end
        if (item == "sibur")
            @Sibur = @Sibur - 1
        end
        if (item == "mendiane")
            @Mendiane = @Mendiane - 1
        end
        if (item == "phiras")
            @Phiras = @Phiras - 1
        end
        if (item == "thystame")
            @Thysame = @Thysame - 1
        end
    end
    
    # Return the quantity of an specified item
    # @param [String] item to check
    # return [Void]
    def getItem(item)
        if (item == "food")
            return @Food
        end
        if (item == "linemate")
            return @Linemate
        end
        if (item == "deraumere")
            return @Deraumere
        end
        if (item == "sibur")
            return @Sibur
        end
        if (item == "mendiane")
            return @Mendiane
        end
        if (item == "phiras")
            return @Phiras
        end
        if (item == "thystame")
            return @Thysame
        end
    end
    
    # Forget a cell, clean all about it but the position of course
    # Return [Void]
    def forget()
        @Food = -1
        @Linemate = -1
        @Deraumere = -1
        @Sibur = -1
        @Mendiane = -1
        @Phiras = -1
        @Thysame = -1
        @playerNbr = -1
    end
    
    # Update the cell counter and forget it if necessary
    # return [Bool] True if forgetted false otherwise
    def updateCell()
        @Counter += 1
        if (@Counter >= 15)
            forget()
            return true
        end
        return false
    end
end