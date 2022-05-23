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
    attr_accessor :posX, :posY, :Food, :Linemate, :Deraumere, :Sibur, :Mendiane, :Phiras, :Thysame

    # Replace the food of the cell
    # @param x [Int] x pos of the cell 
    # @param y [Int] y pos of the cell 
    # return [Void]
    def initialize(x, y)
        if x * y == 0
            STDERR.print("ERROR Map is too small\n")
            exit 84
        end
        @posX = x
        @posX = y
        @Food = 0
        @Linemate = 0
        @Deraumere = 0
        @Sibur = 0
        @Mendiane = 0
        @Phiras = 0
        @Thysame = 0
    end

    # Replace the food of the cell
    # @param * [Int] quantity of item in the cell 
    # return [Void]
    def changeItemsPool(qFOOD, qLINEMATE, qDERAUMERE, qSIBUR, qMENDIANE, qPHIRAS, qTHYSTAME)
        @Food = qFOOD
        @Linemate = qLINEMATE
        @Deraumere = qDERAUMERE
        @Sibur = qSIBUR
        @Mendiane = qMENDIANE
        @Phiras = qPHIRAS
        @Thysame = qTHYSTAME
    end

    # Count the unity of food find in this cell
    # return [Int]
    def countFoodTotal()
        return (@Food + @Linemate + @Deraumere + @Sibur + @Mendiane + @Phiras + @Thysame)
    end
end