# strangerLights
An Arduino-Python interface for controlling a set of 26 LEDs above different letters on a wall.

Features:
 - can do words or patterns
 - can set presets to quickly swap between patterns
 - can change how long the LEDs spend on/off

### Dependencies
The Python control script requires pyserial.

### Setting up
This requires quite a lot of wire, about £20 worth. Each LED needs to be connected (with a resistor) to one of the digital i/o pins from 22 to 48 on the Arduino, where 22 is "a", 23 is "b" and so on. A recommended setup is to have a Raspberry Pi connected which has SSH capabilities, that way you can use your phone to change the lights.

### Installing
 - flash the Arduino firmware to an Arduino Mega (Mega because it has more digital i/o pins and flash memory for storing patterns)
 - connect a device with Python installed to the serial port of the Arduino
 - run the Python script

### Usage
The control script accepts single line commands once ran.

The following will cause the LEDs to flash the word testing:
```
testing
```

The following will cause the LEDs to alternate between flashing "a" and "b" at the same time, followed by "c" and "d":
```
a,bc,d
```

The comma is used to add an extra letter to that display section, can be chained as many times as you want. For example, the following will flash between alternate letters:
```
a,c,e,g,i,k,m,o,q,s,u,w,yb,d,f,h,j,l,n,p,r,t,v,x,z
```

Be sure to add a space at the end if you want there to be a break before looping. Sometimes this won't be needed, especially if doing a pattern rather than a word.

You can change the oN and ofF timers in milliseconds by using:
```
#n1000
#f100
```

Presets can set using the "#p" command, such that the following will set preset 1 to be the words "preset test":
```
#p1preset test
```

This preset can then be accessed using a ".1", such that the following becomes "this is a preset test":
```
this is a .1
```

By default there are a maximum of 10 presets, where the last 5 have preset patterns:

6) half on and half off, then vice versa
7) the light bounces from the top left corner, like the DVD logo
8) a vertical line moving from the right to the left and looping
9) tetris
10) a sine wave travelling to the right
