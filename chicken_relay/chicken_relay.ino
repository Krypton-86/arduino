#include <Time.h>       // время и текущая дата
#include <TimeLord.h>   // вычисление времени заката и рассвета
#include <DS1307RTC.h>  // библиотека RTC возвращает time как time_t, работает как с DS1307 так и с DS3231

#define REL 2           // выход управления реле
#define DEBUG 0         // 1 включает сообщения отладки в монитор серийного порта. Скорость 115200

const int TIMEZONE = +2;                          // установка часового пояса
const float LATITUDE = 50.58, LONGITUDE =30.81 ;  // установка координат: широта, долгота
const int mornT=300;//5:00 вкл зранку
const int afteT=1200;//20:00 вимк вечері
TimeLord myLord;                                            // переменные TimeLord
byte sunTime[6] ;                        // вместо 30 07 16 поставить свою дату число/месяц/год
int minNow, minLast = -1, hourNow, hourLast = -1, minOfDay; // -1 отрабатывает при первом запуске
int mSunrise, mSunset;                                      //время рассвета и заката в минутах от начала дня (0-1439)

// настройка
  void setup()  
{
  pinMode(REL, OUTPUT);                   // инициализируем порт для канала реле как выход
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(REL, HIGH);
  delay(500);
  digitalWrite(REL, LOW);
  delay(500);
  digitalWrite(REL, HIGH);
  delay(1000);
  digitalWrite(REL, LOW);

//TinyWireM.begin();////////////////////////////////////////////
  
  Serial.begin(115200);                   // старт соединенияи и установка скорости
  pinMode(REL, OUTPUT);                   // инициализируем порт для канала реле как выход
  digitalWrite(REL ,HIGH);                // устанавливаем на входе релейного модуля высокий уровень - реле выключено
  myLord.TimeZone(TIMEZONE * 60);
  myLord.Position(LATITUDE, LONGITUDE);
  
  setSyncProvider(RTC.get);               // синхронизация времени с RTC
  if (timeStatus() != timeSet) 
     Serial.println("Unable to sync, load time to RTC");
  else
     Serial.println("RTC has set the system time");
}

// основной цикл
void loop()
{   
  if (timeStatus()!= timeNotSet) 
  {
    minNow = minute();
    if (minNow != minLast) 
    {
        minLast = minNow;
        hourNow = hour();
        minOfDay = hourNow * 60 + minNow; //текущая минута дня 0-1439
        #if DEBUG == 1
          Serial.print("TimeNow: ");
          Serial.print(hourNow);
          Serial.print("-");
          Serial.print(minNow);
          Serial.print(" minOfDay:");
          Serial.print(minOfDay);
          Serial.print(" minLast:");
          Serial.print(minLast);
          Serial.print(" hourLast:");
          Serial.print(hourLast);
          Serial.println();
        #endif
        if (hourNow != hourLast) // расчет времени рассвета и заката при изменении часа (раз в час)
        {    
      
      //Время рассвета и заката в минутах от начала дня
      sunTime[3] = day();                           // текущая дата от библиотеки Time
      sunTime[4] = month();
      sunTime[5] = year()-2000;
      myLord.SunRise(sunTime);                      // расчетные данные рассвета из TimeLord
      mSunrise = sunTime[2] * 60 + sunTime[1] - 40; // где "+0" задержка выключения реле утром в минутах
      myLord.SunSet(sunTime);                       // расчетные данные заката из TimeLord
      mSunset = sunTime[2] * 60 + sunTime[1] + 50;  // +0 задержка вкл реле вечером
         #if DEBUG == 1
           Serial.print("DATE: ");
           Serial.print( sunTime[3]);
           Serial.print("/");
           Serial.print( sunTime[4]);
           Serial.print("/");
           Serial.print( sunTime[5]);
           Serial.print("  SUNRISE OFF:");
           Serial.print(mSunrise);
           Serial.print("  SUNSET ON:");
           Serial.print(mSunset);
           Serial.println();
         #endif

         hourLast = hourNow;
        }
        
        //управляем реле
         if ((minOfDay < mSunrise &&  minOfDay >= mornT)||(minOfDay>=mSunset && minOfDay<afteT)) // если минут с начала суток  меньше, чем время рассвета , но больше, чем время вкл утром
          {digitalWrite(REL, HIGH);                         // то устанавливаем на входе релейного модуля низкий уровень уровень - реле срабатывает
         Serial.println("RELAY ON");
         }
         else                                       // во всех остальных случаях
         { digitalWrite(REL, LOW);
          Serial.println("RELAY OFF");
          } 
          #if DEBUG == 1
          Serial.print("temno:");
          Serial.println(minOfDay < mSunrise || minOfDay >= mSunset);
          Serial.println();
        #endif
                
    } // End: if (minNow != minLast)
  } // End:  if (timeStatus()!= timeNotSet)
} // End loop()

byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );}
