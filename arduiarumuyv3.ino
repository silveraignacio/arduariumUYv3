/*-----( Importar Librerias Necesarias )-----*/
#include <Wire.h>  // Viene con el IDE de Arduino
//Importamos la libreria de LCD
#include <LiquidCrystal_I2C.h>
//Import la libreria de RTC
#include "RTClib.h"


#include <OneWire.h>

#include <DallasTemperature.h>
 
#define Pin 2 //Se declara el pin donde se conectará la DATA
 
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
 
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature



//Defino el RTC

RTC_DS1307 RTC;

/*-----( Declaracion De Constantes )-----*/
int analog_pin = 1;
float temperatura;



 /*-----( Declaracion de objetos )-----*/
// Setear la direccion LCD a 0x27 para 20 caracteres 4 lineas
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declaracion de Variables )-----*/
//NONE


void setup()   /*----( SETUP: Corre una Vez )----*/
{
  //Inicio el sensor de temp
 sensors.begin(); //Se inician los sensores
 
  
  // Instantiate the RTC
  Wire.begin();
  RTC.begin();
 
  // Check if the RTC is running.
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running");
  }

  // This section grabs the current datetime and compares it to
  // the compilation time.  If necessary, the RTC is updated.
  DateTime now = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime()) {
    Serial.println("RTC is older than compile time! Updating");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
 
  Serial.println("Setup complete.");
  
  
  Serial.begin(9600);  // Used to type in characters
  lcd.begin(20,4);   // initialize the lcd for 20 chars 4 lines, turn on backlight

// ------- 3 parpadeos de BackLight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // Finzaliza dejando prendido el BackLight

//-------- Escribir Caracteres ------------------
// NOTE: La posicion de cursor: (Caracter, Linea) empieza en 0  
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Arduarium UY V2");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("--------------------"); // 
  delay(1000);
  lcd.setCursor(0,2);
  lcd.print("Hecho por"); //
  delay(1000);
  lcd.setCursor(0,3);
  lcd.print("Ignacio Silvera");
  delay(8000);  //esperar

  lcd.clear(); //limpiar pantalla

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  sensors.requestTemperatures(); //Prepara el sensor para la lectura
  
  DateTime now = RTC.now();   
  
  lcd.setCursor(0,0);
  lcd.print("Fecha");
  lcd.setCursor(0,1);
  lcd.print(now.day(), DEC);
  lcd.print('/');
   lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  lcd.print(' ');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.setCursor(0,2);
  lcd.print("Temp: ");
  lcd.print(sensors.getTempCByIndex(0)); //Se lee e imprime la temperatura en grados Celsius
  lcd.print("C");
  //lcd.print("Temp: ");
   //lcd.print(temperatura);
   //lcd.print("C");
   //lcd.print((char)223);
   //Serial.print(temperatura);
   delay(2000);
   
  
}/* --(end main loop )-- */


/* ( THE END ) */
