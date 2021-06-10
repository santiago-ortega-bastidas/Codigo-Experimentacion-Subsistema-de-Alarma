//Se incluye la libreria
#include <CapacitiveSensor.h>

//Crear e indicar pines del sensor capasitivo
//Envia la señal en este caso pin numero 4
//Recibe la señal en este caso el pin numero 3
CapacitiveSensor   sensor = CapacitiveSensor(4,3);

//Se crea una variable con el objetivo de encender el motor y Led
int encender = 0;

//Frecuencias que corresponden a las notas musicales, definiendo estas notas como constantes
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

//Definimos el pin 12 como PIN_LED
#define PIN_LED 12
//Definimos el pin 10 como PIEZO
#define PIEZO 10

//Definimos una variable melody[ ] conformada por un conjunto de valores definidos anteriormente
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
//Definir la duración de las notas musicales 
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {

pinMode(PIN_LED,OUTPUT); //Define el pin numero 12 como salida
pinMode(PIEZO, OUTPUT); // Definimos el pin 10 como salida

// Inicializa la comunicación serial a 9600 bits
Serial.begin (9600);

}

void loop() {
  
//Almacenar lectura del sensor en una variable 
long lectura =  sensor.capacitiveSensor(30);//Obtiene el valor del sensor

//Condicional donde comparamos el valor obtenido en sensor.capacitiveSensor(30); con el numero uno
if(lectura > 2)//Si es mayor que uno entra al condicional
{
  
  digitalWrite(PIN_LED,HIGH);//Enciende el Led
  encender=1;//Le damos el valor de uno a la variable encender

  // Lee el pin de entrada analógica 0 muestra 0-1023:
  int SensorValue = analogRead (A0);
  
  // Puede hacer cambios para mostrar en Amperaje 
  // El siguiente código le dice al Arduino que el valor leído por el sensor 
  // debe estar activado de 0-1.023 entre -30 a +30.
  
  int OutputValue = map (SensorValue, 0, 1023, -30, 30);
  // Mostrar valor leído por el sensor:
  
  Serial.print ("Sensor: ");
  Serial.print (SensorValue);
  
  // valor transformado en amperios:
  Serial.print (" Valor en Amperios: ");
  Serial.println (OutputValue);
  
  if (OutputValue<=-4)//Si el valor obtenido es mayor que 4, suena la alarma
  {
    for (int thisNote = 0; thisNote < 8; thisNote++) 
    {
    //noteDuration toma los valores uno a uno cada vez que se hace el bucle
    int noteDuration = 1000 / noteDurations[thisNote];//Mil milisegundos entre la duracion de la nota
    
    //En el pin número 10, usamos la variable melody[] donde están las notas musicales y posteriormente se pone la duración de la nota definida anteriormente
    tone(PIEZO, melody[thisNote], noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.30;//Se almacena en pauseNotas el treinta por ciento de la duración de la nota
    delay(pauseBetweenNotes);//Tiempo de espera para que suene la nota que será del treinta porciento 

    noTone(10);//Detiene el sonido
    }}  
  
}else{

  digitalWrite(PIN_LED,LOW);//Apaga el Led 
  delay(10); //Espera para que se apague después de un tiempo
  
  }
 }

  
