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
    attr_accessor :posX, :posY, :Food, :Linemate, :Deraumere, :Sibur, :Mendiane, :Phiras, :Thysame, :playerNbr

    # Replace the food of the cell
    # @param x [Int] x pos of the cell 
    # @param y [Int] y pos of the cell 
    # return [Void]
    def initialize(x, y)
        @posX = x
        @posY = y
        @Food = 0
        @Linemate = 0
        @Deraumere = 0
        @Sibur = 0
        @Mendiane = 0
        @Phiras = 0
        @Thysame = 0
        @playerNbr = 0
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

    # Count the unity of food find in this cell
    # return [Int]
    def countItemsTotal()
        return (@Food + @Linemate + @Deraumere + @Sibur + @Mendiane + @Phiras + @Thysame)
    end

    def setContents(content)
        @Food = 0
        @Linemate = 0
        @Deraumere = 0
        @Sibur = 0
        @Mendiane = 0
        @Phiras = 0
        @Thysame = 0
        @playerNbr = 0
        for c in content.split(" ")
            if (c == "Food")
                @Food += 1
            end
            if (c == "Linemate")
                @Linemate += 1
            end
            if (c == "Deraumere")
                @Deraumere += 1
            end
            if (c == "Sibur")
                @Sibur += 1
            end
            if (c == "Mendiane")
                @Mendiane += 1
            end
            if (c == "Phiras")
                @Phiras += 1
            end
            if (c == "Thysame")
                @Thysame += 1
            end
            if (c == "player")
                @playerNbr += 1
            end
        end
    end
end