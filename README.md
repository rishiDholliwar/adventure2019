README

How to run the server:

	./build.sh 

additional options are available with:
	
	./build.sh -h/--help

	Usage:
	./build.sh [PORT=####] [JOBS=#] [SERVER=FALSE] [CLEAN=TRUE]
	PORT 	 - Set the server port
	         DEFAULT: 4000
	JOBS 	 - Builds faster, sets the number of cores to use when building
	         DEFAULT: 0
	SERVER - Set it to FALSE to not run server at the end
	         DEFAULT: TRUE
	CLEAN  - Removes previous networkbuild directory before building
	         DEFAULT: FALSE
	Example: ./build.sh PORT=9999 JOBS=4

Accessing the client:
	
	- you can access the client through the webpage at:

		localhost:4000

Alternatively, you could access the client through the terminal by running the following in another terminal from the server:

	- networkbuild/bin/chatclient localhost 4000

Initial start:

You want to run the signup command as follows:
	
	/signup [username] [password]

		- This resisters your user in the game and you can log back in another time using the login command

	/login [username] [password]

		- This restores the last saved version of your character and you may continue where you left off.

Once in the game you may use the help command to see the commands available to you:
	
	/help

	Commands:
		/login [username] [password] - login as user with password
		/logout - logout user
		/signup [username] [password] - signup as user with password
		/say [message] - sends message to other players in the room
		/tell [target] [message] - Send a message to a specific player in the world
		/whisper [target] [message] - Send a message to a specific player in the world ... but beware of prying ears
		/move [direction] - move to the target direction
		/help - 911 what is your emergency?
		/look [target] - get short description of the target, or use /look to get short description about the room.
		/examine [target] - get detailed description of the target.
		/inventory - displays your inventory
		/give [target's character name] [item name] - give item to a player
		/PigeonMail deliver [target name] [item] - delivers an item to the target
		/PigeonMail status [tracking number] - track your package
		/swap [target username] - swap with the target character with this username
		/confuse [target] - confuses a target and they see weird things


You are all set to go!
\
\
\
Edit (ReadMe made before these changes):
`Master` branch also contains
	- Combat
	- MiniGame (Tic Tac Toe, and Tic Tac Toe Terminal)
	- Login/Signup GUI (Does not work with internalization)

`64-drop-to-room` branch:
	- /Drop [item] - drops an item from your inventory

`44-refactor-yell` branch:
	- /Yell [message] - Adjacent rooms can hear you screaming
\
\
\
Last thorough tested commit id: `28c8db0b95dfbab1c30c2639055b827db8a5bbeb`
(We do not have automated tests)

Known issues:
1. Multiple swaps fail with NPCs of the same name
	- Solution: swap by unique ID

2. Look and examine does not work properly when swapped
	- Shows swapped person's descriptions `NPC only`
	- Solution: search by character name instead of username in look/examine

3. Swapping with Pigeon (pigeon mail carrier) `SEG FAULT`
	- Solution: Don't murder the pigeon until after unswap happens
				Pigeon is removed from the game and the player cannot unswap

4. Closing the window while swapped does not allow the user to log back in until 	unswapped. 
	- This was originally a feature (Not a great one to the user but to developers)
	- Solution: Allow user to log back in but do not load their character

5. Clicking connect multiple times allows the user to log in as multiple people `Web client`
	- Solution: Remove the connect button 
