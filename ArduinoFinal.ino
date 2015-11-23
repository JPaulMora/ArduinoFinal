/* Proyecto final de Taller de Introduccion a la Mecatronica
*   Juan Pablo Mora 15799, 
*   Irvin R. Oliva 15816
*   Universidad del Valle Guatemala
*/


#include <Servo.h>

//Servo
Servo Serv; //Objeto Servo.
int potps, val; //inicializacion de variables sin valor (para usar despues).

//LEDS
int led3 = 3;
int led5 = 5;
int led6 = 6;
int led11 = 11;

//Dips
int dip1 = 7;
int dip2 = 8;

//Push
int push1=2; //variables de los Push, son = al # de pin. (ver Breadboard).
int push2=4;

//Other
int pot = 0;

void setup() {
  Serial.begin(9600);
  Serv.attach(9);  //Pin donde se encuentra el Servo
           /*-----Inicializacion de LEDs -------*/
  pinMode(led3, OUTPUT);//LED1
  pinMode(led5, OUTPUT);//LED2   
  pinMode(led6, OUTPUT);//LED3
  pinMode(led11, OUTPUT);//LED4
  pinMode(2,INPUT);//PUSH 1
  pinMode(4,INPUT);//PUSH 2
  

           /*-----Inicializacion de Dips -------*/
  pinMode(dip1, INPUT_PULLUP);
  pinMode(dip2, INPUT_PULLUP);   //INPUT_PULLUP: El estado natural del pin es HIGH.


          /*-----Inicializacion de Push -------*/
  pinMode(push1,INPUT_PULLUP);
  pinMode(push2,INPUT_PULLUP);  //tenes que decirle al Arduino como usarlos.
                                //usamos INPUT_PULLUP Y NO INPUT, porque no tenemos 2k resistores (entonces usamos el interno como en los dip).

}

/************** Funciones ********************/

int funcNum()
{
  int suma = 4; //Dipswitch conecta pins a GND para ponerlos en LOW, hacemos conteo en reversa (if HIGH, restar a 'suma').
  if (digitalRead(dip1) == HIGH){
    suma -= 1; // si dip1 == HIGH (switch off), suma = 4 -1 = 3; correr funcion 3.
  }
  if (digitalRead(dip2) == HIGH){
    suma -= 2; // Si dip2 == HIGH, suma = 4 -2 = 2 correr funcion 2.
  }                       
  return suma;  //si Ningun pin esta conectado a GND, significa que los 2 dipswitches estan en 'OFF' y el resultado de 4 -2-1 = 1; entonces correr funcion 1.
               //si los 2 switches estan en LOW (switches ON), significa que a 'suma' no se le resta nada y 4 -0 = 4; correr funcion 4.
}

/************ Fin Funciones ******************/

void loop() 
{
  Serial.println(funcNum());
  int iVal1=digitalRead(push1); //podemos iniciar las variables localmente.
  int iVal2=digitalRead(push2); //Apachado ahora conecta a low  o negativo (ver Breadboard).
  //Funcion 1
  //DIP1==HIGH, DIP2==HIGH;
  if (funcNum() == 1){
  val = analogRead(pot); //Leer voltaje del potenciometro {0,1023} 
  val = map(val,0,1023,0,180); //convertir voltaje del potenciometro 'pot' {0,1023} -> {0,180}

  //LEDS
  if (val <= 45 && val > 0){ // Activado si 'val' entre (0,45}.
    int valocal = map(val,0,45,0,180); //Variable local, convierte 'val' entre {0,45} -> {0,180}
    analogWrite(led3,valocal);
    digitalWrite(led5,LOW);
    digitalWrite(led6,LOW);
    digitalWrite(led11,LOW);
  }else if (val > 45 && val <= 90){ // Activado si 'val' entre (45,90}.
    int valocal = map(val,46,90,0,180);
    digitalWrite(led3,HIGH);
    analogWrite(led5,valocal);
    digitalWrite(led6,LOW);
    digitalWrite(led11,LOW);
  }else if(val > 90 && val <= 135){ // Activado si 'val' entre (90,135}.
    int valocal = map(val,90,135,0,180);
    digitalWrite(led3,HIGH);
    digitalWrite(led5,HIGH);
    analogWrite(led6,valocal);
    digitalWrite(led11,LOW);
  } else if(val >135 && val <= 180){ // Activado si 'val' entre (135,180}.
    int valocal = map(val,135,180,0,180);
    digitalWrite(led3,HIGH);
    digitalWrite(led5,HIGH);
    digitalWrite(led6,HIGH);
    analogWrite(led11,valocal);
  }else{     //       /      /      /  Si 'val' == 0 apagar todos los LEDs
    digitalWrite(led3,LOW);
    digitalWrite(led5,LOW);
    digitalWrite(led6,LOW);
    digitalWrite(led11,LOW);
  }
  Serv.write(val); //Enviar posicion de 'val' (0-180) al servo.

  //Funcion 2
    //Dip1==LOW; Dp2==High; 0 + 2 = 2
  }
  else if(funcNum() == 2)
  {
    if(iVal1==LOW && iVal2 == HIGH)   //Asegurarnos que **SOLO 1** se esta apachando o las dos condiciones se vuelven 'true'
                  //mientras el push esta apachado, es LOW 
                  //DigitalRead se tiene que comparar con HIGH o LOW, analog se compara con numeros.
  {
    digitalWrite(led3,HIGH);
    digitalWrite(led5,HIGH);
    digitalWrite(led6,HIGH);
    digitalWrite(led11,HIGH);
    delay(100);
  
  // LEDs estaran encendidos por 100ms, hay que apagarlos por 100ms para que 'titilen'. 
  
    digitalWrite(led3,LOW);
    digitalWrite(led5,LOW);
    digitalWrite(led6,LOW);
    digitalWrite(led11,LOW);
    delay(100);
  }
    else if(iVal2==LOW && iVal1==HIGH)
  {
    digitalWrite(led3,LOW);
    digitalWrite(led5,HIGH);
    digitalWrite(led6,LOW);
    digitalWrite(led11,HIGH);
    delay(100);
  
    digitalWrite(led3,HIGH);
    digitalWrite(led5,LOW);
    digitalWrite(led6,HIGH);
    digitalWrite(led11,LOW);
    delay(100);
  }
    else//mientras no pasada nada, todo apagado(high)
  {
    digitalWrite(led3,LOW);
    digitalWrite(led5,LOW);
    digitalWrite(led6,LOW);
    digitalWrite(led11,LOW);
  }
  
  }
  //Funcion 3
    //Dip1==HIGH;Dip2==Low; 4-1-0=3;
  else if(funcNum() == 3)
  {
    if (iVal1==LOW && iVal2==HIGH)
    //mientras push1 sea precionado, cumplira con la condicion
    {
      val=analogRead(pot);//Lee potenciometro de 0-1023;
      digitalWrite(led3,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led11,HIGH);
      delay(val);
  
  // LEDs estaran encendidos por el valor del potenciometro y se apagaran por el valor del potenciometro 
  
      digitalWrite(led3,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led11,LOW);
      delay(val);
    }
    else if(iVal1==HIGH && iVal2==LOW)
    //Mientras Push2 sea precionado, cumplira con la siguiente condicion
    {
      val=analogRead(pot);
      val=map(val,0,1023,0,180);//conviete val de 0-1023 a 0-180
      digitalWrite(led3,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led11,HIGH);
      Serv.write(val); //Enviar posicion de 'val' (0-180) al servo.
    }
    else//si ambos push==HIGH, mantener todo apagado
     {
      digitalWrite(led3,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led11,LOW);
     }
  }
  //funcion 4
  else
  {
    int i=15;//Valor de intensidad para los leds. Empezar intensidad al 50%
    //settea la intensidad a 15
    analogWrite(led3,i);
    analogWrite(led5,i);
    analogWrite(led6,i);
    analogWrite(led11,i);
    //Push 1 presionado, iniciara un conteo regresivo para quitarle intensidad al LED
    if(iVal1==LOW && iVal2==HIGH)
    {
      for(i=15;i>=0;i-=1)
      {
        analogWrite(led3,i);
        analogWrite(led5,i);
        analogWrite(led6,i);
        analogWrite(led11,i);
        delay(100);
      }
    }
    //push2 presionado, iniciara un conteo para aumentar el birllo del LED
    else if(iVal1==HIGH && iVal2==LOW)
    {
      for(i=15;i<=45;i++)
      {
        analogWrite(led3,i);
        analogWrite(led5,i);
        analogWrite(led6,i);
        analogWrite(led11,i);
        delay(100);
      }
    }
    
  }
  delay(15);  //Esperara 15ms antes de reiniciar loop.
}
