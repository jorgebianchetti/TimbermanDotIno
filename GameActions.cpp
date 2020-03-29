#include "Arduino.h"
#include "GameActions.h"

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

/*  
    Initialize the game
    @param t: Delay time
*/
void GameActions::initGame(int t){
  fifo = create_fifo();
  presence_counter = 0;

  delay(t);
}

/*  
    Read the sensor
    @param pin: Sensor input pin
    @return Sensor read value
*/
int GameActions::readSensor(int pin){
  return analogRead(pin);
}

/*  
    Set the level type
    @return Level type
*/
int GameActions::setLevel(){
  int read_sensor = readSensor(sensor_pin);
  if(read_sensor < (morning[MIN] + 10)) lvl = MORNING;
  else if(read_sensor < (afternoon[MIN] + 10)) lvl = AFTERNOON;
  else if(read_sensor < (snow[MIN] + 10)) lvl = SNOW;
  else if(read_sensor < (night[MIN] + 10)) lvl = NIGHT;

  return lvl;
}

/*  
    Trigger the electrode
    @param pin: Electrode pin
    @param t: Delay time
*/
void GameActions::triggElec(int pin, int t){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(t);
  pinMode(pin, INPUT);
}

/*  
    Deactivate the electrode output (set it as input)
    @param pin: Electrode pin
*/
void GameActions::deactElec(int pin){
  pinMode(pin, INPUT);
}

/*  
    Check the presence of a branch
    @param val: Amount of light
    @return Presence or not (1: presence, 0: no presence)
*/
int GameActions::checkPresence(int val){
  if(lvl == MORNING){
    if(val >= morning[CENTER]) return 1;
    else return 0;
  }
  else if(lvl == AFTERNOON){
    if(val >= afternoon[CENTER]) return 1;
    else return 0;
  }
  else if(lvl == NIGHT){
    if(val >= night[CENTER]) return 1;
    else return 0;
  }
  else if(lvl == SNOW){
    if(val >= snow[CENTER]) return 1;
    else return 0;
  }
}

/*  
    Process the game
    @param t: Delay time
*/
void GameActions::processGame(int t){
  int light = readSensor(sensor_pin);

  int presence = checkPresence(light);

  put_fifo(fifo, presence, h_offset);

  stat_t s = read_fifo(fifo);

  if(s.height == 1){
    if(s.presence == 1){
      presence_counter = 1;
      triggElec(el_right, TRIGG_TIME);
    }else{
      if(presence_counter == 1){
        presence_counter = 0;
        triggElec(el_right, TRIGG_TIME);
      }else{
        triggElec(el_left, TRIGG_TIME);
      }
    }

    delete_first_fifo(fifo);
  }else{
    triggElec(el_left, TRIGG_TIME);
  }

  dec_height_fifo(fifo);

  delay(t);
}

/*  
    End the game
    @param t: Delay time
    @return Sensor read valu
*/
void GameActions::endGame(int t){
  delete_fifo(fifo);

  delay(t);
}
