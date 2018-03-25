# The Jester

The Jester is a gesture-controlled wheelchair developed for The College of William & Mary [TribeHacks IV](http://tribehacks.com).

## Requirements

- [Myo Armband](https://www.myo.com)
- [PyoConnect](http://www.fernandocosentino.net/pyoconnect/)
- [Arduino](https://www.arduino.cc/)
- [Adafruit Motor Shield v2.0](https://www.adafruit.com/product/1438)
- 2 Motors

## Setup

1. Connect the Arduino with the motor shield and motors per the guidance provided with the motor shield.
2. Upload the sketch from this repository to the Arduino.
3. Place `thejester.py` into PyoConnect's `scripts` directory.
4. Run PyoConnect (Enable the Jester plugin)
5. Perform the Myo's unlock gesture (finger tap by default).

## Controls

Out of the box, The Jester offers the following controls:

Make a fist to move forward, release the fist to stop.

While moving forward, the chair's speed and direction can be controlled by adjusting where your arm is pointing.

While stationary, turning can also be accomplished by rotating your wrist to point your hand in the direction desired (Myo's `waveIn` and `waveOut` gestures).

## Contributors

- Erik Stevenson
- Rozda Askari
