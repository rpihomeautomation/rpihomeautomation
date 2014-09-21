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



import glob, random, sys, vlc  #glob-load the mp3 files names
                               #random-shuffle the tracks
                               #sys-for exit()
                               #vlc-music player

if len(sys.argv) <= 1:  #to exit if no input folder is present
	print("Please specify a folder with mp3 files")
	sys.exit(1)
	
folder = sys.argv[1]
files = glob.glob(folder+"/*.mp3")
if len(files) == 0:  #checks for mp3 file are present or not
	print("No mp3 files in directory", folder, "..exiting")
	sys.exit(1)

random.shuffle(files)

player = vlc.MediaPlayer()
 medialist = vlc.MediaList(files) #medialist-playlist player
mlplayer = vlc.MediaListPlayer()
mlplayer.set_media_player(player)
mlplayer.set_media_list(medialist)

while True:
	button = input("Hit a button")
	if button = '1':
		print("Pressed play button")
		if mlplayer.is_playing():
			mlplayer.pause()
		else:
			mlplayer.play()
	elif button == "2":
		print("Pressed stop button")
		mlplayer.stop()		
		random.shuffle(files)
		medialist = vlc.MediaList(files)
		mlplayer.set_media_list(medialist)
	elif button == "3":
		print("Pressed back button")
		mlplayer.previous()
	elif button == "4":
		print("Pressed forward button")
		mlplayer.next()
	else:
		print("Unrecognised input")
