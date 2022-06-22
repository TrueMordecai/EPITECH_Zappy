require_relative 'class_cell.rb'
class String
    # colorization
    def colorize(color_code)
      "\e[#{color_code}m#{self}\e[0m"
    end
  
    def red
      colorize(31)
    end
  
    def green
      colorize(32)
    end
  
    def yellow
      colorize(33)
    end
  
    def blue
      colorize(34)
    end
  
    def pink
      colorize(35)
    end
  
    def light_blue
      colorize(36)
    end

    def color(a)
      colorize(a)
    end
end

class Map
    attr_accessor :map, :sizeX, :sizeY
    
    # Initialize map
    # @param *Size [Int] size of the map.
    # @param argumentCount [Int] argument needed by the command.
    def initialize(xSize, ySize)
        @map = []
        @sizeX = xSize
        @sizeY = ySize
        for y in 0..ySize - 1
            tmp = []
            for x in 0..xSize - 1
                tmp.append(Cell.new(x, y))
            end
            t = tmp
            @map.append(tmp.dup)
            tmp.clear
        end
    end

    # Print the map, for debug purpose
    # return [Void]
    def printMap()
        puts ('------' * @map[0].size + '-') # First "----" line
        for line in @map

            print '|' # First block line
            for c in line            
              if (c.countItemsTotal < 0) #First line cells
                print ("#{("?       ")[0, 5].red}|")
              else
                print ("#{(c.countItemsTotal.to_s + "       ")[0, 5].green}|")
              end
            end
            puts

            print '|' # Seconde line cells
            for c in line 
                print ("x=#{(c.posX.to_s + "        ")[0, 3]}|")
            end
            puts

            print '|' # Seconde line cells
            for c in line 
                print ("y=#{(c.posY.to_s + "        ")[0, 3]}|")
            end
            puts

            print '|' # Seconde line cells
            for c in line 
              if (c.playerNbr > 0)  
                print ("#{(c.playerNbr.to_s + " pl        ")[0, 5]}|".blue)
              else
                print ("#{("?pl        ")[0, 5]}|")
              end
            end
            puts
            
            for c in line # Last line
                print ("------")
            end
            puts '-'
        end
    end
    
    # Update the cell
    # @param [Int] posX
    # @param [Int] posX
    # @param [String] Content of the tile
    # return [Void]
    def update_cell(posX, posY, content)
      if (@map == nil or content == nil)
        return
      end
      while (posX < 0)
        posX = @sizeX - posX
      end
      while (posY < 0)
        posY = @sizeY - posY
      end
      while (posX > sizeX)
        posX -= sizeX
      end
      while (posY > sizeY)
        posY -= sizeY
      end
      @map[posX][posY].setContents(content)
    end

    # Getter for a cell at certain coords, check map overflow
    # @param posX = x pos
    # @param posY = y pos
    # return [Cell]
    def getCell(posX, posY)
      while (posX < 0)
        posX = @sizeX - posX
      end
      while (posY < 0)
        posY = @sizeY - posY
      end
      while (posX > sizeX)
        posX -= sizeX
      end
      while (posY > sizeY)
        posY -= sizeY
      end
      return @map[posY][posX]
    end
  
    def get
  end