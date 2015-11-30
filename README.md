# Pulse : a musical example for the Slate
By Pierre Schefler for iskn.

## General information

### Description
In this demo, we use the slate as a 3D sensor to track the pen as a drum stick.  
The user first learns to keep the beat and then is allowed to play drums on top of a song.

### Installation
1. Download openframeworks here: http://openframeworks.cc/download/ (on windows, prefer visual studio to qt creator for OF but both should work fine).
2. Copy the 'Pulse' folder inside 'apps/myApps'.
3. Try to start the project corresponding to your IDE and platform (linux : qt creator ; win : visual studio ; os x : xcode).
4. If the project doesn't compile or if the one you need doesn't exist, just create it:
  1. copy the addons you will find in 'Addons' to openframeworks/addons
  2. try openframeworks' project generator (don't forget to tick the addons) or create a raw project and include all of OF sources and the project's sources
  3. add the include folder of the API corresponding to your platform (Pulse\src\Slate\ISKN_API) to the include directories of your project
  4. link to iskn API (Pulse\src\Slate\ISKN_API) and don't forget to copy the shared lib to your PATH or next to the binary
 
### How to use
Compile and run. Read further how to place the Slate.  
If you want to change the song, go to Pulse/bin/data and edit settings.ini.

### Remarks about changing the song
There are a few things you should take care of when setting up another song:
* It should have a constant tempo (only for level 1)
* You must know the tempo (only for level 1)
* The format should be mp3, aif or wav (refer to the openFrameworks documentation for more information)
* The audio file should start on a "beat", meaning that it shouldn't have a few milliseconds of silence or noise for example, or the score might not be correctly evaluated (only for level 1)

### License
This example is licensed under the Do What The Fuck You Want Public License.

### TODO
* Finish commenting stuff
* Set the OS X project up and make a release version
* Make a small tool to change the song, detect its tempo and synchronize it with a simple GUI

## How it works

### Slate input and HMI
The user can navigate inside the software using the Slate only (with a pen or any magnet). The magnet's orientation is detected and the program makes a projection of the magnet's position along its orientation 
so that user feels like he has a pointer. Using this pointer, the user can easily interact with any element of the GUI.  
For instance, how do you click a button in 3D ? You can't. Instead, and that's what's being done here, you have to place your pointer on a button and wait long enough for it to be "clicked".  
  
About the Slate, openFrameworks uses an event and listeners system which allows us to send messages back from an object to the class containing it. This was however replaced by a call at each frame to reduce latency
since events usually take quite some time to be delivered.

### Levels and parts
The software is divided into "parts": the menu, level 1, level2.  
Each part is called a "scene", because it always contain the same basic things such as the pointer, buttons, etc. Then, a "level" inherits a "scene", adding a few more things like an intro, an outro, score, etc. 
This simple inheritance structure allows us to easily add or remove a part (especially a level) but also change the currently displayed part.

### Drums
A drum is represented by a rectangular zone sliced by a voronoi algorithm and animated by a shader which makes the drum "bounce" when the pointer hovers it. When the pointer crosses the drum going downwards, a "hit" is fired.
When a hit is fired, the drum plays the sound that is associated with it. In the first level, the hit is used by the level to evaluate the score. In the second level, it is simply ignored because we only want to play the sound.

### Score evaluation in level 1
The length of a "beat" is defined by the tempo written in the settings file. It could be a half note or a quarter note, depending on what you want.  
When the level starts, a timer also starts and keeps track of when are the beats. Hence, when a hit is fired by the "stick", we exactly know the gap between the hit and the previous or next beat. 
The earliest you can hit a beat is half a beat before and the latest is half a beat after. The score function simply is a gaussian centered on the beat and going from -1/2 beat to +1/2 beat.  
Also, a bonus is given if you're (almost) perfectly on the beat and a malus is attributed if you fire multiple hits during one beat (it means you're probably cheating).
