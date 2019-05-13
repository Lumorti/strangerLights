# strangerLights
An Arduino-Python interface for controlling a set of 26 LEDs above different letters on a wall.

### Dependencies
The Python control script requires pyserial.

### Setting up
This requires quite a lot of wire, about £20 worth. Each LED needs to be connected (with a resistor) to one of the digital i/o pins from 22 to 48 on the Arduino, where 22 is "a", 23 is "b" and so on. A reccomended setup is to have a Raspberry Pi connected which has SSH capabilities, that way you can use your phone to change the lights.

### Installing
 - flash the Arduino firmware to an Arduino Mega (Mega because it has more  digital i/o pins)
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

You can also change the oN and ofF timers in milliseconds by using:
```
#n1000
#f100
```
