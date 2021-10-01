/*
 * File:   newmain.c
 * Author: BEV
 *
 * Created on 1 de Outubro de 2021, 08:41
 */


#include <xc.h>
#define F_CPU 32768UL //informa a frequência do clock utilizado
#define DEBOUNCE_TIME 25
#include <util/delay.h>
#include <stdio.h>


void ini_io(){
    
    PORTC.DIR  |= PIN6_bm; //definindo porta PC6 como output
    PORTC.OUT  |= PIN6_bm; //definindo led como apagado no início
    
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSC32K_gc); //Escolhe a fonte do clock principal
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, CLKCTRL_PEN_bm | CLKCTRL_PDIV_64X_gc); //ligar o prescaler e escolher divisão
    //_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_64X_gc); //divisão do prescaler
    
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm){
 ;
}

}

void pwm_tcb(){
    
    TCB3.CTRLA |= TCB_ENABLE_bm;
    TCB3.CTRLA |= TCB_CLKSEL_DIV2_gc;
    PORTMUX.TCBROUTEA = 0x00;
    TCB3.CTRLB |= TCB_CCMPEN_bm;
    TCB3.CTRLB |= TCB_CNTMODE_PWM8_gc;
    TCB3.CCMP = 0x80FF;
    
}

void duty_75(){
    
    TCB3.CCMP = 0xC0FF;
    
}

void duty_25(){
    
    TCB3.CCMP = 0x40FF;
    
}

void duty_50(){
    
    TCB3.CCMP = 0x80FF;
    
}

unsigned char button_state() { // Função que verifica se o botão está ou não ativado
   //Bitset(PORTC, 0x06);
   int a = PORTC.IN; //Faz com que a variável a seja igual ao estado lógico das portas C.
   a = a - 0b10000000; //verficiação se o botão está ou não ativado
    if (a < 0) {
    //if (PORTC.IN.PIN7 == 0){
        //if ((PORTC.IN == 0b00000011)||(PORTC.IN == 0b01000011)){
        _delay_ms(DEBOUNCE_TIME); //Processo de debouncing
        if (a < 0) {
        //if (PORTC.IN.PIN6 == 0){
            //if ((PORTC.IN == 0b00000011)||(PORTC.IN == 0b01000011)){
            //_delay_ms(DEBOUNCE_TIME); //Processo de debuncing
            return 1; //informar que o botão foi apertado

        }
    }
    return 0;
}

void main(void) {
    
    ini_io();
    pwm_tcb();
    int i =0;
    PORTC.PIN7CTRL = 0b00001000; //Ativando função pull-up para uso do botão
    PORTC.DIR = 0b01000000; //Pino PC6 como output e o pino PC7 como input
    PORTC.OUT &= 0x00; //Acende o LED
    while(1){
         if (button_state()){
             i++;
            // _delay_ms(500);
             PORTC.OUTTGL = 0b01000000;
             if ( i == 3){
                 duty_25();
                 i = 0;
             }
             
             else if (i == 2){
                 duty_50();
             }
             
             else if (i == 1){
                 duty_75();
             }
             do {

            } while (button_state()); //Espera o botão parar de ser apertado
             
         }
    }
    
    return;
}
