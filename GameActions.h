#ifndef ACTIONS_H
#define ACTIONS_H

extern "C"{
  #include "fifo.h"
}

#define TRIGG_TIME 20 /* Amount of time to activate the electrode */

/* Level type */
enum lvlType {
  MORNING = 0,
  AFTERNOON,
  NIGHT,
  SNOW
};

/* Light range */
enum lightRange {
  MIN = 0,
  CENTER,
  MAX
};

/* Light range of each level (MIN, CENTER, MAX) */
const int night[3]      = {700, 730, 800};
const int snow[3]       = {515, 590, 661};
const int afternoon[3]  = {450, 520, 700};
const int morning[3]    = {432, 500, 650};

class GameActions{
public:
  GameActions(int pin, int er, int el, int offset); /* Constructor */
  void initGame(int t); /* Initialize the game */
  int readSensor(int pin); /* Read the sensor */
  int setLevel(); /* Set the level type */
  void triggElec(int pin, int t); /* Trigger the electrode */
  void deactElec(int pin); /* Deactivate the electrode output */
  int checkPresence(int val); /* Check the presence of a branch */
  void processGame(int t); /* Process the game */
  void endGame(int t); /* End the game */

private:
  int sensor_pin;
  int lvl;
  int presence_counter;
  int el_right;
  int el_left;
  int h_offset;  
  fifo_t* fifo;
};

#endif
