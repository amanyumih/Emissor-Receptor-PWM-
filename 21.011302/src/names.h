#ifndef NOMES_H_ALKDSADFGDFGJFLIAWUEFKJSDFL_    /* Para evitar reinclusão do arquivo header */
#define NOMES_H_ALKDSADFGDFGJFLIAWUEFKJSDFL_

/******************* BIBLIOTECAS *******************/

#include <Arduino.h>                    // Lib padrão do Arduino.
#include "TimerOne.h"                   // Lib para interrupção por tempo.
#include "PinChangeInterrupt.h"         // Lib para transformar alguns pins em interrupção. 

/******************* DEFINIÇÕES *******************/

// IO's do arduino
#define SETPOINT_DISP1          2       // I D02
#define SETPOINT_DISP2          3       // I D03
#define PACK_TRIGGER_DISP1      4       // I D04
#define SEND_PWM_1              5       // O D05
#define SEND_PWM_2              6       // O D06
#define PACK_TRIGGER_DISP2      7       // I D07
#define CONST_TRIGGER_DISP1     8       // I D08
#define CONST_TRIGGER_DISP2     9       // I D09
#define RESERVE1                10      // I D10
#define RESERVE2                11      // I D11
#define STATUS_DISP1            13      // O D13
#define STATUS_DISP2            12      // O D12

//Definições de ciclo
#define TOLERANCE               0.9     // Define uma tolerância dos ruídos dos sinais enviados pelo CLP.
#define READING_TIME_RESET      2000    // Tempo minino para resetar medição.

#define SCALE_IN_DIF_MIN        100000  // Define a diferencia minima de pulso recebidas.
#define SCALE_IN_DIF_MAX        300000  // Define a diferencia maxima de pulso recebidas.
#define SCALE_OUT_DIF_MIN       1000    // Define a diferencia minima de pulso p/ enviar.
#define SCALE_OUT_DIF_MAX       120     // Define a diferencia maxima de pulso p/ enviar.
#define SCALE_IN_TOLERANCE      5000    // Define uma tolerância para os 4 #defines anteriores. 


/******************* FUNÇÕES *******************/

// Função salva sinais de pulso enviados pelo CLP do Disp1 e Disp2
void SetPoint1();
void SetPoint2();

// Função para filtro de pulsos enviados pelo CLP.
void FilterSetPoint(unsigned long dif[], unsigned long period[], int pin, float val_max, float val_min, bool chooseDisp1or2);

//Função para reset da contagem de medição.
void ResetMeasuring();

// Função que recebe aviso para enviar pacote de trigger.
void PackTrigger1();
void PackTrigger2();

// Função para enviar pacote de trigger ao CLP.
void SendPWM1();
void SendPWM2();

// Função para enviar pacote de trigger constante ao CLP.
void ConstantTriggerChange1();
void ConstantTriggerChange2();

// Função principal
void setup();
void loop();

/******************* VARIÁVEIS *******************/

// Faz a medição das bordas de subida e descida. Sendo impares subida e pares descida.
extern uint8_t medicao_disp1;
extern uint8_t medicao_disp2;

// Armazena os valores que vieram nas bordas de subida e descida no array. SetPoint.
extern unsigned long periodos_disp1[];
extern unsigned long periodos_disp2[];

// Armazena o calculo das diferenças de periodos de pulsos enviados pelo clp. SetPoint.
extern unsigned long diferencas_valores1[];
extern unsigned long diferencas_valores2[];

// Valores máximos e minimos das diferenças de periodos Dispositivo 1.
extern float minimo_valor_disp1;
extern float maximo_valor_disp1;

// Valores máximos e minimos das diferenças de periodos Dispositivo 2.
extern float minimo_valor_disp2;
extern float maximo_valor_disp2;

// Variável para sinalizar falha no sinal.
extern byte status_disp1_toggle;
extern byte status_disp2_toggle;

// Variável para armazenar média das diferenças de sinais enviados pelo CLP.
extern unsigned long long val_average_dif1;
extern unsigned long long val_average_dif2;

// Variável para armazenar quatidade de pulsos que deve-se enviar para o motor de passo.
extern uint16_t qty_pulses_1;
extern uint16_t qty_pulses_2;

// Verificador de pulsos enviados para o Motor de Passo.
extern uint16_t pulses_sent_1;
extern uint16_t pulses_sent_2;

// Validação para saber se pode iniciar envio de pulsos.
extern bool running_pulses_1;
extern bool running_pulses_2;

// Variável para verificação de ruídos na chamada de um pacote de pulsos.
extern bool noises_pack_trigger1;
extern bool noises_pack_trigger2;

#endif