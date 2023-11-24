#include <NewPing.h>
#define PIN_CNY_CENTRO A5
#define ENA_PIN 3
#define IN1_PIN 2
#define IN2_PIN 4
#define ENB_PIN 6
#define IN3_PIN 5
#define IN4_PIN 7
#define SONAR_NUM 3       // Numero de sensores.
#define MAX_DISTANCE 200  // Distancia maxima em cm.
#define PING_INTERVAL 33  // Millisegundos entre pings.
#define PIN_SENSOR_TREGGER 9
#define PIN_SENSOR_IZQUIERDO 10
#define PIN_SENSOR_CENTRO 11
#define PIN_SENSOR_DERECHO 12
//#define PIN_PULSADOR 13
#define DEBUG 1
enum {
ADELANTE,
IZQUIERDA,
DERECHA,
ATACAR,
ESQUIVAR,
BUSQUEDA,
}estados;





#define sensor_derecho 0
#define sensor_centro 1
#define sensor_izquierdo 2
int Lectura_CNY_CENTRO;
unsigned long pingTimer[SONAR_NUM];  // Quando cada pings.
unsigned int cm[SONAR_NUM];          // Armazena distâncias do ping.
uint8_t currentSensor = 0;           // Que sensor é ativo.
char *Sensores[] = { "Sensor_Derecho", "Sensor_central", "Sensor_izquierdo" };
NewPing sonar[SONAR_NUM] = {
  // Declaração dos pins de cada sensor.
  NewPing(PIN_SENSOR_TREGGER, PIN_SENSOR_IZQUIERDO, MAX_DISTANCE),
  NewPing(PIN_SENSOR_TREGGER, PIN_SENSOR_CENTRO, MAX_DISTANCE),
  NewPing(PIN_SENSOR_TREGGER, PIN_SENSOR_DERECHO, MAX_DISTANCE),

};

void setup() {
//  pinMode(PIN_PULSADOR, INPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(PIN_CNY_CENTRO, INPUT);



  Serial.begin(115200);
  pingTimer[0] = millis() + 75;  // O primeiro ping é iniciado em ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;

 /*while(switch){
  switch = digitalRead(PIN_PULSADOR);
  delay(50);
}
  delay(5000);*/
estados = BUSQUEDA;

  
}
void loop() {


  Lectura_CNY_CENTRO = analogRead(PIN_CNY_CENTRO);
  if(DEBUG)Serial.print("      Lectura: ");
  if(DEBUG)Serial.print(Lectura_CNY_CENTRO);

  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1)
        oneSensorCycle();  // Faz alguma coisa com os resultados.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);


    } }
  
 


 switch (estados){  
 case ATACAR :   
                if (distancias() < 5)   {
            detenerMovimiento();  
            
                     estados = ADELANTE; 
             }
   break;
    case ADELANTE:
                   if (estados == ADELANTE )
                      deteccion_colision ();   

                      else 
                      estados = BUSQUEDA;

      break;
 //   case ATRAS:
          //do something when var equals 2
   //   break;
    case BUSQUEDA:{
      ontas();

    if (distancias() == 4)   {
            detenerMovimiento();  
               estados = DERECHA;
            }
      else  if (distancias() == 3) {  
            detenerMovimiento();  
              estados = IZQUIERDA ;

            }
      else  if (distancias() == 5)   {
            detenerMovimiento();
              estados = ATACAR ;
    
            }   
      //do something when var equals 2
 }break;
    case IZQUIERDA:   
            espera_atacke_izquierda ();
      if (estados = IZQUIERDA )   {
                   
                 }
     else  {
       detenerMovimiento();
            estados = BUSQUEDA ;
     }
      break;
       case DERECHA:   
                  
                 if (estados = DERECHA )   {
                   espera_atacke_derecho ();
                 }
     else {
       detenerMovimiento();
            estados = BUSQUEDA ;
     }

      break;
    default: 

     Serial.println("ERROR CRITICO NO ENTRA EN NINGUN ESTADO ");
      break;

}


  }
void echoCheck() {  //Se existir um ping o valor será registado no array
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() {  // Faz alguma coisa com os resultados.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if(DEBUG){
    Serial.print(Sensores[i]);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.println("cm ");}

  }
  if(DEBUG)Serial.println();
}



void moverIzquierda() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENA_PIN, 255);
  analogWrite(ENB_PIN, 255);
}

// Función para mover hacia la derecha
void moverDerecha() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENA_PIN, 255);
  analogWrite(ENB_PIN, 255);
}

// Función para mover hacia adelante
void moverAdelante() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENA_PIN, 255);
  analogWrite(ENB_PIN, 255);
}

// Función para mover hacia atrás
void moverAtras() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENA_PIN, 255);
  analogWrite(ENB_PIN, 255);
}

// Función para detener el movimiento
void detenerMovimiento() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}
void ontas ()
{
 digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENA_PIN, 100);
  analogWrite(ENB_PIN, 100);
}
void esquivar() {
  moverAtras();
  delay(500);
  moverDerecha();
  delay(500);
}
int distancias ()
{
  int x =0;
if (cm[sensor_centro] < 20    )
{
  x == 2;
} 

if (cm[sensor_izquierdo] < 20   )
{
  x == 3;
} 
if (cm[sensor_derecho] < 20   )
{
  x == 4;
} 

if (cm[sensor_centro] > 10    )
{
  x == 5;
} 
return x;
}

void espera_atacke_izquierda (){

  if  (cm[sensor_izquierdo] < 20 && cm[sensor_izquierdo] > 10 )
               detenerMovimiento() ;
               else if  (cm[sensor_izquierdo] > 20 &&  cm[sensor_izquierdo] > 10 )
                  detenerMovimiento() ;
                     else  if  (cm[sensor_izquierdo] > 5 )
                       {   moverAtras() ;
                           delay(600);
                                if (cm[sensor_centro] >10  )
                                  moverAdelante();
                                      else 
                                         ontas ();  
                                          }
                                          
}
void espera_atacke_derecho (){


  if  (cm[sensor_derecho] < 20 && cm[sensor_derecho] < 10 )
               detenerMovimiento() ;
               else if  (cm[sensor_derecho] > 20 &&  cm[sensor_derecho] < 10 )
                  detenerMovimiento() ;
                     else  if  (cm[sensor_derecho] > 5 )
                       {   moverAtras() ;
                           delay(600);
                                if (cm[sensor_centro] >10  )
                                  moverAdelante();
                                      else 
                                         ontas ();  
                                          } 
}

void  deteccion_colision ()   {

          if (cm[sensor_centro] >  10   &&  cm[sensor_centro] > 4 && cm[sensor_centro]  != 0  )
                                  moverAdelante();
        else 
            detenerMovimiento() ;  
                
}