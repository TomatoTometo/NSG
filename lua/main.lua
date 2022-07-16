#!/usr/bin/env lua54

local dog = require("doggo");

-- Wait function
function wait(msec)
  local t = os.clock()
  repeat
  until os.clock() > t + msec * 1e-3
end

-- Start the ritualB
dance = dog:startDance()

-- Main loop
while true do

  -- Get the next frame in the dance
  frame = dance()
  
  if (frame ~= nil) then
    -- If good, print
    print(frame)
  else
    -- If bad, exit
    print("Invalid frame :(")
    os.exit()
  end
  
  -- sleep
  wait(100)
  -- clear
  os.execute("clear")
end
