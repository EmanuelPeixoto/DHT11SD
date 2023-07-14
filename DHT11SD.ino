 #include <DHT.h>        
 #include <SPI.h>
 #include <SD.h>
 #define DHTPIN 1          
 #define DHTTYPE DHT11
 int i = 1;
 bool led = 0;

 
    DHT dht(DHTPIN, DHTTYPE);
    const int chipSelect = 4;
 
    void setup()
    {
      Serial.begin(9600);     
      dht.begin();          
      pinMode(LED_BUILTIN, OUTPUT);
      if (!SD.begin(chipSelect)) {
      return;
  }
    }
 
    void loop()
    {
        int t = dht.readTemperature();  
        int h = dht.readHumidity();     
 
      if (t==0 || h==0)
      {
        Serial.println(">>>>>>>>>>>>>>>>>>>>Erro de leitura do sensor!");
      }
      else
      {
          File dataFile = SD.open("/DATALOG.TXT", FILE_WRITE);
          
            if (dataFile) {
              if (i >= 60){
              dataFile.print("Umidade: ");
              dataFile.print(h);
              dataFile.print(" % ");
              dataFile.print("Temperatura: ");
              dataFile.print(t);
              dataFile.println(" *C");
              i = 1;
              }
              led = !led;
              dataFile.close();
              Serial.print("Temperatura: ");
              Serial.print(t); //Imprime no monitor serial o valor da temperatura lida
              Serial.println("ºC");
              Serial.print("Umidade: ");
              Serial.print(h); //Imprime no monitor serial o valor da umidade lida
              Serial.print("%");
              Serial.print(" i: ");
              Serial.println(i);
              
          }
          // if the file isn't open, pop up an error:
          else {
            Serial.println("error opening datalog.txt");
          }
      }
 
      delay(1000);
      digitalWrite(LED_BUILTIN, led);
      i++;
    }
