#! /usr/bin/python3
import serial
import io
import threading
import time
import math



# Enter your details here (note, client secret is not your password)
username = ""
client_secret = "" 



redirect_uri = 'http://localhost/'
scope = 'user-read-currently-playing user-read-playback-state'
client_id = 'ac6e3b42aaf64b44a83a48071c983f45'
useSpotify = False
currentSongName = "";

with serial.serial_for_url('/dev/ttyACM0', timeout=1) as ser:

	sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

	def readLoop():

		while True:

			if ser.in_waiting > 0:

				print(ser.readline().decode("utf-8").replace("\n",""))

			time.sleep(0.1)

	def spotLoop():

		global currentSongName
		global token

		while True:

			if useSpotify:

				obj = None
				try:
					obj = sp.currently_playing()
				except e as Exception:
					pass

				if obj is not None:

					track = obj["item"]
					uri = track["uri"]
					name = track["name"]
					features = sp.audio_features([uri])
					tempo = features[0]["tempo"]

					if name != currentSongName:

						currentSongName = name
						sio.write(str("#b" + str(math.ceil(tempo)) + "\n"))
						sio.flush() 

				token = util.prompt_for_user_token(username,scope,client_id,client_secret,redirect_uri)

			time.sleep(1)

	threading.Thread(target=readLoop).start()
	threading.Thread(target=spotLoop).start()
	while True:

		userInput = input("")
		
		if userInput == "#spot":

			if not useSpotify:

				print("Enabling Spotify integration")
				import spotipy
				import spotipy.util as util

				token = util.prompt_for_user_token(username,scope,client_id,client_secret,redirect_uri)

				if not token:
					print ("Can't get token for " + username)
					raise SystemExit
				
				sp = spotipy.Spotify(auth=token)			

				useSpotify = True

			else: 

				useSpotify = False

		else:
			
			sio.write(str(userInput + "\n"))
			sio.flush() 
