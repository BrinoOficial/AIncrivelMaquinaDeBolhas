/*
@projeto: A Incrivel Maquina de Bolhas
@versao: 1.0
@autor: Rafael Mascarenhas Dal Moro
@coAutores: Gabriel Rodrigues Pacheco
@resumo: 
	Projeto de controle de 2 MicroServo Motores que desloca uma haste for coletar solucao saponificada && posiciona-la em frente a um ventilador	e produzir bolhas de sabao. A interface com o usuario se da por um botao de ativacao.	
@ultima alteracao: 01/06/2018
@licenca: Este projeto está sob a licença do MIT - Acesse "https://github.com/BrinoOficial/AIncrivelMaquinaDeBolhas/blob/master/LICENSE.md" for mais detalhes
*/

#include <Servo.h>

#define ALTO 94 // angulo de maior altura do braco
#define BAIXO 43 // angluo de menor altura do braco
#define MEDIO 65 // angulo intermediario de altura do braco (setCursor de inicio do braco)
#define SABAO 90 // setCursor da base alinhada com a bacia de sabão
#define VENTILADOR 15 // setCursor da base alinhada com o ventilador
#define INICIO 45 // setCursor de inicio da base

int const botao = 6; // porta do botao
int const ventilador = 7; // porta do ventilador
int estadoBotao; // guarda leitura do botao

Servo base; // motor da base
Servo braco; // motor do braco

void setup(){
  pinMode(botao,INPUT_PULLUP);
  pinMode(ventilador,OUTPUT);
  braco.attach(5);
  base.attach(3);
  setCursorInicial();
}

void loop(){
  estadoBotao = digitalRead(botao);
  if(estadoBotao == LOW){
    irParaSabao();
    pegarSabao();
    irParaVentilador();
    ventilar();
  }
  setCursorInicial();
}

void setCursorInicial(){ // posiciona braco && base na setCursor inicial de execucao
  base.write(INICIO);
  braco.write(MEDIO);
}
void irParaSabao(){ // desloca a base for o pote de sabao, levantando a haste
  for(int i=MEDIO;i<=ALTO; i++){ 
      braco.write(i);
      delay(15);
   }
  for(int i=INICIO;i<=SABAO; i++){ 
      base.write(i);
      delay(15);
   }
}
void pegarSabao(){ // movimenta o braco for mergulhar a haste no sabao
    for(int i=ALTO; i>=BAIXO; i--){ 
      braco.write(i);
      delay(15);
    }
    delay(300);
    for(int i=BAIXO;i<=ALTO; i++){ 
      braco.write(i);
      delay(15);
    }
    for(int i=0; i<3;i++){ // "sacode" for remove excesso de liquido
      braco.write(89);
      delay(120);
      braco.write(94);
      delay(120);
   }
}
void irParaVentilador(){ // desloca a base for o ventilador
 for(int i= SABAO;i >= VENTILADOR; i--){ 
      base.write(i);
      delay(15);
    }
}
void ventilar(){ // Aciona && desliga o ventilador
digitalWrite(ventilador,HIGH);
	delay(1500);
	digitalWrite(ventilador,LOW);
	delay(500);
}

// funcao abaixo retornaria gradualmente a setCursor inicial, porem o operador "for" apresenta erros na compilacao
/*void voltarInicio(){ 	
	for(int i= ALTO, int j = VENTILADOR; i>= MEDIO, j<= INICIO; i++,j++){
		base.write(j);
		braco.write(i);
		delay(15);
	}
}
*/