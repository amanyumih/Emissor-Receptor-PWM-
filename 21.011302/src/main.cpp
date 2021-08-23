#include "names.h"

/******************* SETUP *******************/
void setup() {

  // ---- Definição dos IO's do Arduino. ----

  pinMode(SETPOINT_DISP1, INPUT_PULLUP);
  pinMode(SETPOINT_DISP2, INPUT_PULLUP);

  // pinMode(SEND_PWM_1, OUTPUT);
  // pinMode(SEND_PWM_2, OUTPUT);

  pinMode(PACK_TRIGGER_DISP1, INPUT_PULLUP);
  pinMode(PACK_TRIGGER_DISP2, INPUT_PULLUP);

  pinMode(CONST_TRIGGER_DISP1, INPUT_PULLUP);
  pinMode(CONST_TRIGGER_DISP2, INPUT_PULLUP);

  pinMode(RESERVE1, INPUT_PULLUP);
  pinMode(RESERVE2, INPUT_PULLUP);

  pinMode(STATUS_DISP1, OUTPUT);
  pinMode(STATUS_DISP2, OUTPUT);

  // Interrompe o ciclo e chama a função de leitura dos pulsos. Dispositivo 1.
  attachInterrupt(digitalPinToInterrupt(SETPOINT_DISP1), SetPoint1 , CHANGE);

  // Interrompe o ciclo e chama a função de leitura dos pulsos. Dispositivo 2.
  attachInterrupt(digitalPinToInterrupt(SETPOINT_DISP2), SetPoint2, CHANGE);

  //----- Lib PinChaged. Transforma um pino em interrupção. -----
  // Interrompe o loop
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(PACK_TRIGGER_DISP1), PackTrigger1, FALLING);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(PACK_TRIGGER_DISP2), PackTrigger2, FALLING);

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(SEND_PWM_1), SendPWM1, FALLING);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(SEND_PWM_2), SendPWM2, FALLING);

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(CONST_TRIGGER_DISP1), ConstantTriggerChange1, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(CONST_TRIGGER_DISP2), ConstantTriggerChange2, CHANGE);

  //Configurações do interrupção por tempo 
  Timer1.initialize(2000000);             //Inicializa o Timer1
  Timer1.attachInterrupt(ResetMeasuring); //ResetMeasuring to run every 2 sec

  // Inicia monitor serial.
  Serial.begin(9600);

  // for PWM frequency of 7812.50 Hz PIN D5 and D6
  TCCR0B = ((TCCR0B & B11111000) | B00000010);
}

/******************* LOOP *******************/
void loop() {

  if (status_disp1_toggle){
    digitalWrite(STATUS_DISP1, !digitalRead(STATUS_DISP1));
  }
  
  if (status_disp2_toggle){
    digitalWrite(STATUS_DISP2, !digitalRead(STATUS_DISP2));
  }

  delay(2000);
  
}