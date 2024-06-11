# Zappy

## Description
Zappy is an AI simulation with each AI a different client (The leader of the team join with his client and the process will split to increase the theam size)
The goal of each team is to elevate each member to the level maximum

This version use the art of The Binding Of Isaac Rebirth

## Requisites
Not supposed to work on Windows
SFML
Makfiles

## Usage

### Build 

Use make on graphics and server folder, client is on ruby

### Server
Launch the server 
> ./zappy_server -p 88844 -x 20 -y 20 -n Jean -c 8 -f 10

USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
	port		 is the port number
	width		 is the width of the world
	height		 is the height of the world
	nameX		 is the name of the team X
	clientsNb	 is the number of authorized clients per team
	freq		 is the reciprocal of time unit for execution of actions

### Graphics 
GUI is also a client who use his own protocole
Launch the graphics
> ./zappy_gui

in the settings connect to the right port, you can check if your connected with the text on the top right corner
Pree Q to quit it.
Include a command line that can do with the character (local only)

### Client
Launch each client
Port should match the server and the -h is mandatory. However i don't think it would work on 
> ruby main.rb -p 88844 -n Jean -h localhost
  

## Preview
![image](https://github.com/TrueMordecai/EPITECH_Zappy/assets/60859370/9380fb0a-0595-4b1e-a252-a30e3dfc5a52)
![image](https://github.com/TrueMordecai/EPITECH_Zappy/assets/60859370/933c594e-151e-459f-ac75-5423cad06cda)


