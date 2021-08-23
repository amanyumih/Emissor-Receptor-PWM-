#include "names.h"

/******************* DISPOSITIVO 1 *******************/

// Toda a vez que o CLP enviar pulsos no SETPOINT, verificaremos cada 3 pulso enviado. (Filtro) Dispositivo 1.
void SetPoint1() {

    Timer1.detachInterrupt();
    Timer1.restart();
    Timer1.attachInterrupt(ResetMeasuring);

    if (medicao_disp1 == 0){
        periodos_disp1[0] = micros();
        medicao_disp1++;
        status_disp1_toggle = 0;
        digitalWrite(STATUS_DISP1, LOW);
    } else if (medicao_disp1 == 1){
        periodos_disp1[1] = micros();
        medicao_disp1++;
    }else if (medicao_disp1 == 2){
        periodos_disp1[2] = micros();
        medicao_disp1++;
    }else if (medicao_disp1 == 3){
        periodos_disp1[3] = micros();
        medicao_disp1++;
    }else if (medicao_disp1 == 4){
        periodos_disp1[4] = micros();
        medicao_disp1++;
    }else if (medicao_disp1 == 5){
        periodos_disp1[5] = micros();
        medicao_disp1++;
    }else if(medicao_disp1 == 6){
        periodos_disp1[6] = micros();
        medicao_disp1++;
    }else {
        FilterSetPoint(diferencas_valores1, periodos_disp1, STATUS_DISP1, maximo_valor_disp1, minimo_valor_disp1, 0);
    }
}

// Sinal do CLP avisando que precisa dos pulsos. Dispositivo 1.
void PackTrigger1(){
    
    disablePinChangeInterrupt(PACK_TRIGGER_DISP1);
    noInterrupts();

    //Filtro para garantir que é um sinal do CLP e não um ruído.
    for(int i = 0; i <= 20; i++){
        if(!digitalRead(PACK_TRIGGER_DISP1)){
            delayMicroseconds(500);
            noises_pack_trigger1 = 0;
        } else{
            noises_pack_trigger1 = 1;
            break;
        }
    }

    enablePinChangeInterrupt(PACK_TRIGGER_DISP1);
    interrupts();

    // Verifica se foi um sinal recente e se não é um ruído para iniciar contagem.
    if(!running_pulses_1 && !noises_pack_trigger1){
        running_pulses_1 = 1;
        analogWrite(SEND_PWM_1, 127);
    }
}

// Função para enviar pulsos pwm para Motor de passo. Dispositivo 1.
void SendPWM1(){

    disablePinChangeInterrupt(PACK_TRIGGER_DISP1);
    noInterrupts();

    // Verifica se os pulsos que já foram enviados.
    if(running_pulses_1){        
        pulses_sent_1++;

        if (pulses_sent_1 >= qty_pulses_1){
            analogWrite(SEND_PWM_1, 0);
            running_pulses_1 = 0;
            pulses_sent_1 = 0;
        }

    }

    enablePinChangeInterrupt(PACK_TRIGGER_DISP1);
    interrupts();
}

// Função para enviar pulsos continuous pwm para Motor de passo. Dispositivo 1.
void ConstantTriggerChange1(){

    uint8_t cycle = 0;

    //Filtro para garantir que é um sinal do CLP e não um ruído.
    for(int i = 0; i <= 20; i++){
        if(!digitalRead(CONST_TRIGGER_DISP1)){
            delayMicroseconds(500);
            noises_pack_trigger1 = 0;
        } else{
            noises_pack_trigger1 = 1;
            break;
        }
    }

    if(!digitalRead(CONST_TRIGGER_DISP1) && noises_pack_trigger1){
        cycle = 127;
    }

    analogWrite(SEND_PWM_1, cycle);
}

/******************* DISPOSITIVO 2 *******************/

// Toda a vez que o CLP enviar pulsos no SETPOINT, verificaremos cada 3 pulso enviados. (Filtro) Dispositivo 2.
void SetPoint2(){

    Timer1.detachInterrupt();
    Timer1.restart();
    Timer1.attachInterrupt(ResetMeasuring);

    if (medicao_disp2 == 0){
        periodos_disp2[0] = micros();
        medicao_disp2++;
        status_disp2_toggle = 0;
        digitalWrite(STATUS_DISP2, LOW);
    } else if (medicao_disp2 == 1){
        periodos_disp2[1] = micros();
        medicao_disp2++;
    } else if (medicao_disp2 == 2){
        periodos_disp2[2] = micros();
        medicao_disp2++;
    } else if (medicao_disp2 == 3){
        periodos_disp2[3] = micros();
        medicao_disp2++;
    } else if (medicao_disp2 == 4){
        periodos_disp2[4] = micros();
        medicao_disp2++;
    } else if (medicao_disp2 == 5){
        periodos_disp2[5] = micros();
        medicao_disp2++;
    } else if (medicao_disp2 == 6){
        periodos_disp2[6] = micros();
        medicao_disp2++;
    } else {
        FilterSetPoint(diferencas_valores2, periodos_disp2, STATUS_DISP2, maximo_valor_disp2, minimo_valor_disp2, 1);
    }
}

// Sinal do CLP avisando que precisa dos pulsos. Dispositivo 2.
void PackTrigger2(){
    disablePinChangeInterrupt(PACK_TRIGGER_DISP2);
    noInterrupts();

    //Filtro para garantir que é um sinal do CLP e não um ruído.
    for(int i = 0; i <= 20; i++){
        if(!digitalRead(PACK_TRIGGER_DISP2)){
            delayMicroseconds(500);
            noises_pack_trigger2 = 0;
        } else{
            noises_pack_trigger2 = 1;
            break;
        }
    }

    enablePinChangeInterrupt(PACK_TRIGGER_DISP2);
    interrupts();

    // Verifica se foi um sinal recente e se não é um ruído para iniciar contagem.
    if(!running_pulses_2 && !noises_pack_trigger2){
        running_pulses_2 = 1;
        analogWrite(SEND_PWM_2, 127);
    }
}

// Função para enviar pulsos pwm para Motor de passo. Dispositivo 2.
void SendPWM2(){

    disablePinChangeInterrupt(PACK_TRIGGER_DISP2);
    noInterrupts();

    // Verifica se os pulsos que já foram enviados.
    if(running_pulses_2){
        pulses_sent_2++;

        if (pulses_sent_2 >= qty_pulses_2){
            analogWrite(SEND_PWM_2, 0);
            running_pulses_2 = 0;
            pulses_sent_2 = 0;
        }

    }

    enablePinChangeInterrupt(PACK_TRIGGER_DISP2);
    interrupts();
}

// Função para enviar pulsos continuous pwm para Motor de passo. Dispositivo 2.
void ConstantTriggerChange2(){
    uint8_t cycle = 0;

    //Filtro para garantir que é um sinal do CLP e não um ruído.
    for(int i = 0; i <= 20; i++){
        if(!digitalRead(CONST_TRIGGER_DISP2)){
            delayMicroseconds(500);
            noises_pack_trigger2 = 0;
        } else{
            noises_pack_trigger2 = 1;
            break;
        }
    }

    if(!digitalRead(CONST_TRIGGER_DISP2) && !noises_pack_trigger2){
        cycle = 127;
    }

    analogWrite(SEND_PWM_2, cycle);  
}

/******************* AMBOS DISPOSITIVOS *******************/

//Filtro de leitura de pulsos. chooseDisp1or2 -> Disp1 = 0. Disp2 = 1.
void FilterSetPoint(unsigned long dif[6], unsigned long period[6], int pin, float val_max, float val_min, bool chooseDisp1or2){
    
    // Calcula de diferenças dos periodos dos pulsos de subida e descida para saber o tempo a prox. dos de pulsos.
    dif[0] = period[1] - period[0];
    dif[1] = period[2] - period[1];
    dif[2] = period[3] - period[2];
    dif[3] = period[4] - period[3];
    dif[4] = period[5] - period[4];
    dif[5] = period[6] - period[5];

    //Calculo para descobrir valor máximo e minino de pulso recebido.
    val_max = dif[0];
    val_min = dif[0];

    for (int i = 0; i < 5; i++){
        if(dif[i] < val_min){
            val_min = dif[i];
        }
        if(dif[i] > val_max){
            val_max = dif[i];
        }
    }

    //Calcula porcentagem de tolerância para garantir recebimento de pulsos correto. 
    if((val_min/val_max) >= TOLERANCE){
        //Se for dispositivo 1
        if(!chooseDisp1or2) {

            //Calcula a média das dos pulsos recebidos (alteração no PWM faz com que todos os tempos fossem diminuidos 8 vezes)
            val_average_dif1 = (dif[0] + dif[1] + dif[2] + dif[3] + dif[4] + dif[5]) / 48;

            // Calculo para garantir que a das diferenças estejam dentro da tolerância máxima e mínina. Se são pulsos previstos para a aplicação.
            if ((val_average_dif1 > (SCALE_IN_DIF_MIN - SCALE_IN_TOLERANCE)) && (val_average_dif1 < (SCALE_IN_DIF_MAX + SCALE_IN_TOLERANCE))){
                
                status_disp1_toggle = 0;
                digitalWrite(pin, HIGH);
                
                // Calculo para calcular os pulsos enviados do disp1.
                qty_pulses_1 = (int)((float)((float)((float)val_average_dif1 - (float)SCALE_IN_DIF_MIN) / (float)((float)SCALE_IN_DIF_MAX - (float)SCALE_IN_DIF_MIN)) * (float)((float)SCALE_OUT_DIF_MAX - (float)SCALE_OUT_DIF_MIN) + (float)SCALE_OUT_DIF_MIN);

            }else{
                medicao_disp1 = 0;
                status_disp1_toggle = 1;
            }
        }
        // Se for dispositivo 2.
        else{

            //Calcula a média das dos pulsos recebidos (alteração no PWM faz com que todos os tempos fossem diminuidos 8 vezes)
            val_average_dif2 = (dif[0] + dif[1] + dif[2] + dif[3] + dif[4] + dif[5]) / 48;

            // Calculo para garantir que a das diferenças estejam dentro da tolerância máxima e mínina. Se são pulsos previstos para a aplicação.
            if ((val_average_dif2 > (SCALE_IN_DIF_MIN - SCALE_IN_TOLERANCE)) && (val_average_dif2 < (SCALE_IN_DIF_MAX + SCALE_IN_TOLERANCE))){
                
                status_disp2_toggle = 0;
                digitalWrite(pin, HIGH);
                
                // Calculo para calcular os pulsos enviados do disp1.
                qty_pulses_2 = (int)((float)((float)((float)val_average_dif2 - (float)SCALE_IN_DIF_MIN) / (float)((float)SCALE_IN_DIF_MAX - (float)SCALE_IN_DIF_MIN)) * (float)((float)SCALE_OUT_DIF_MAX - (float)SCALE_OUT_DIF_MIN) + (float)SCALE_OUT_DIF_MIN);

            }else{
                medicao_disp2 = 0;
                status_disp2_toggle = 1;
            }
        }
    }
    else{
        if(!chooseDisp1or2) {     
            medicao_disp1 = 0;
            status_disp1_toggle = 1;
        }
        else{                     
            medicao_disp2 = 0;
            status_disp2_toggle = 1;
        }
    }
}

//Reset a contagem para possível recontagem de pulsos do CLP.
void ResetMeasuring(){
    medicao_disp1 = 0;
    medicao_disp2 = 0;
}