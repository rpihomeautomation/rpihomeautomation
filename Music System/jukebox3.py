#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  jukebox1.py
#  
#  Copyright 2014 Deepak J Puthukkaden <deepakjputhukkaden.mec@gmail.com>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  


#import libraries
import glob, random, sys, vlc  #glob-load the mp3 files names
                               #random-shuffle the tracks
                               #sys-for exit()
                               #vlc-music player
import RPi.GPIO as GPIO  #gpio buttons
from Adafruit_CharLCD import *

#cli arguments check
if len(sys.argv) <= 1:  #to exit if no input folder is present
	print("Please specify a folder with mp3 files")
	sys.exit(1)
	
folder = sys.argv[1]
files = glob.glob(folder+"/*.mp3")
if len(files) == 0:  #checks for mp3 file are present or not
	print("No mp3 files in directory", folder, "..exiting")
	sys.exit(1)

random.shuffle(files)

#vlc setup
player = vlc.MediaPlayer()
 medialist = vlc.MediaList(files) #medialist-playlist player
mlplayer = vlc.MediaListPlayer()
mlplayer.set_media_player(player)
mlplayer.set_media_list(medialist)

#gpio setup
GPIO.setmode(GPIO.BCM)
PLAY_BUTTON=11
STOP_BUTTON=7
BACK_BUTTON=4
FORWARD_BUTTON=10
GPI0.setup(PLAY_BUTTON, GPIO,IN)
GPIO.setup(STOP_BUTTON, GPIO.IN)
GPIO.setup(BACK_BUTTON, GPIO.IN)
GPIO.setup(FORWARD_BUTTON, GPIO.IN)

#lcd setup
lcd = Adafruit_CharLCD()
lcd.clear()
lcd.message("Hit play!")

def handle_changed_track(event, player):
	media = player.get_media()
	media.parse()
	artist = media.get_meta(vlc.Meta.Artist) or "Unknown artist"
	title = media.get_meta(vlc.Meta.Title) or "Unknown song title"
	album = media.get_meta(vlc.Meta.Title) or "Unknown song"
	lcd.clear()
	lcd.message(title+"\n"+artist+"-"+album)
	playerem = player.event_manager()
	playerm.event_attach(vlc.EventType.MediaPlayerMediaChanged,handle_changed_track, player)
			
#while loop
while True:
	#button = input("Hit a button")
	if GPIO.input(PLAY_BUTTON):
		print("Pressed play button")
		if mlplayer.is_playing():
			mlplayer.pause()
		else:
			mlplayer.play()
	elif GPIO.input(STOP_BUTTON):
		print("Pressed stop button")
		mlplayer.stop()		
		random.shuffle(files)
		medialist = vlc.MediaList(files)
		mlplayer.set_media_list(medialist)
	elif GPIO.input(BACK_BUTTON):
		print("Pressed back button")
		mlplayer.previous()
	elif GPIO.input(FORWARD_BUTTON):
		print("Pressed forward button")
		mlplayer.next()
	#else:
	#	print("Unrecognised input")
	time.sleep(0.3)
	lcd.scrollDisplayLeft()
