#include "names.h"

/******************* VARIÁVEIS GLOBAIS *******************/

// Variável p/ auxiliar no estágio de medição. Sendo nº impares para borda subida e nº pares para borda descida.
uint8_t medicao_disp1 = 0;
uint8_t medicao_disp2 = 0;

// Variável p/ Armazena o tempo (micro) enviado pelo CLP, tanto na borta de subida como descida.
unsigned long periodos_disp1[7]{0, 0, 0, 0, 0, 0, 0};
unsigned long periodos_disp2[7]{0, 0, 0, 0, 0, 0, 0};

// Variável p/ Armazena a diferença dos valores da borda de subida e descida. 
unsigned long diferencas_valores1[6]{0,0,0,0,0,0};
unsigned long diferencas_valores2[6]{0,0,0,0,0,0};

// Valores máximos e minimos das diferenças de periodos Dispositivo 1.
float minimo_valor_disp1 = 0;
float maximo_valor_disp1 = 0;

// Valores máximos e minimos das diferenças de periodos Dispositivo 2.
float minimo_valor_disp2 = 0;
float maximo_valor_disp2 = 0;

// Média dos pulsos enviados pelo CLP.
unsigned long long val_average_dif1 = 0;
unsigned long long val_average_dif2 = 0;

// Sinal de falha no recebimento dos pulsos.
byte status_disp1_toggle = 0;
byte status_disp2_toggle = 0;

// Armazena a qtd de pulsos que devemos enviar para o motor de passo depois.
uint16_t qty_pulses_1 = 15;
uint16_t qty_pulses_2 = 18;

// Verificador de pulsos enviados para o Motor de Passo.
uint16_t pulses_sent_1 = 0;
uint16_t pulses_sent_2 = 0;

// Validação para saber que os pulsos já estão sendo enviados.
bool running_pulses_1 = 0;
bool running_pulses_2 = 0;

// Variável para verificação de ruídos na chamada de um pacote de pulsos.
bool noises_pack_trigger1 = 0;
bool noises_pack_trigger2 = 0;