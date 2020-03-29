# TimbermanDotIno

## What is this?
It's a firmware for the Arduino platform that plays the game Timberman just reading a LDR and controlling two electrodes.

## And how does it work?
### Hardware
The hardware consists of a P2 jack, a push-button, a LDR sensor and two electrodes (it can be a piece of aluminium foil).

A piece of wire was welded to the ground of the P2 jack (which is connected to the innermost contact of the jack). The wire was connected to the GND pin of the Arduino and the P2 jack to the headphone input of the smartphone.

Each electrode was connect to a digital input of the Arduino through a wire.

One leg of the LDR was connected to the GND and the another one to the 5V through a 10kOhm resistor. The node with the LDR and the resistor was connected to an analog input of the Arduino.

One leg of the push-button was connected to a digital input (with the PULLUP option set when defining the pinMode in the software) of the Arduino and the another one to the GND. 

### Software

The software basically uses a fifo buffer to store the presence or not of a branch, reading the LDR, and process the buffer activating or not the electrodes.

For the electrode to simulate a touch on the screen, the firmware set it as "LOW", connecting it to the ground of the smartphone, waiting some time and then set it as INPUT, to put it in a high-z state (high impedance, or (almost) connected to nothing). This makes the screen changes its electric field in the area that the electrode is in touch, thus simulating a finger touch. Cool, isn't it? :grin:
```CPP
void GameActions::triggElec(int pin, int t){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(t);
  pinMode(pin, INPUT);
}
```

## Usage

Dispose the electrodes one at each side of the screen and the LDR at some point in the left that the branch will stop at (see the video below as reference). You will have to specify the LDR position when creating the GameActions object as shown below:

```CPP
/*  
    Constructor
    @param pin: Sensor input pin
    @param el: Left electrode pin
    @param er: Right electrode pin
    @param offset: Position of the sensor (Character's position: 0, above position: 1 ...)
*/
GameActions::GameActions(int pin, int el, int er, int offset){
  sensor_pin = pin;
  el_right = er;
  el_left = el;
  h_offset = offset;
}

/* ... */

GameActions ga(ldr, e1, e2, 2);
```

Now you're just going to have to press the play button in the game and press the push button. Voilà, the magic is now happening.

A short video showing it running can be seen [here](https://www.youtube.com/watch?v=YXvhhirm1ys)!


I hope you all enjoy it!