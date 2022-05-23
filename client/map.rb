require_relative 'cell.rb'
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
end

class Map
    attr_accessor :map
    
    # Initialize map
    # @param *Size [Int] size of the map.
    # @param argumentCount [Int] argument needed by the command.
    def initialize(xSize, ySize)
        @map = []

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
        puts ('---' * @map[0].size + '-')
        for line in @map
            print '|'
            for c in line 
                print ("#{(c.countFoodTotal.to_s + "       ")[0, 2].red}|")
            end
            puts
            print '|'
            for c in line 
                print ("  |")
            end
            puts
            print '-'
            for c in line 
                print ("---")
            end
            puts
        end
    end
end