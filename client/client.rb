#!/usr/bin/env ruby
#coding: utf-8

bfr = "Test"
puts "You can also put forked code in a block pid: #{Process.pid}"
i = 0
i = fork()
if (i == nil)
    puts ("Pid is nil")
else
    puts "Pid is #{i}"
    bfr += " child"
end
puts "This process is : #{Process.pid}"
puts bfr