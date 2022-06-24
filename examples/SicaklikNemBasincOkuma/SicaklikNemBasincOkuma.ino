/*
 *   Sıcaklık Nem Basınç Okuma örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Sensörlerden gelen Sıcaklık, Bağıl Nem ve Basınç değerleri okumaktadır. 
 *   Saniyede bir bu verileri seri terminale yazdırmaktadır.
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap Sıcaklık&Nem, Basınç Ölçer için oluşturulmuştur
 *      ------> www.....com <------ //docs
 *      ------> https://github.com/deneyapkart/deneyap-sicaklik-nem-basinc-olcer-arduino-library <------
 *      ------> www.....com <------ //docs
 *      ------> https://github.com/deneyapkart/deneyap-basinc-olcer-arduino-library <------
 *
*/
#include <Deneyap_BasincOlcer.h>                               // Deneyap_BasincOlcer.h kütüphanesi eklendi
#include <Deneyap_SicaklikNemBasincOlcer.h>                    // Deneyap_SicaklikNemBasincOlcer.h kütüphanesi eklendi

AtmosphericPressure Pressure;                                  // AtmosphericPressure için class tanımlanması
SHT4x TempHum;                                                 // SHT4x icin class tanımlamasi

float basinc;
float sicaklik;
float nem;

void setup() {
    Serial.begin(115200);                                     // Seri terminal başlatıldı
    Pressure.begin(0x76);                                     // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatıldı
    if (!TempHum.begin(0X44)) {                               // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatıldı
        Serial.println("I2C bağlantısı başarısız ");          // I2C bağlantısı başarısız olursa seri terminale yazdırıldı
        while (1);
    }
}

void loop() {  
    TempHum.measure();                                       // Ayarlanmış ölçüm modu ile ölçülmesi
    sicaklik = TempHum.TtoDegC();                            // Fahrenheit dereceleri için bunun yerine TtoDegF işlevini kullanın
    Serial.print("\nSıcaklık: ");
    Serial.print(sicaklik);                                  // Sıcaklığı Santigrat(Celsius) derece olarak seri terminale yazdırma
    Serial.println(" °C");

    nem = TempHum.RHtoPercent();                             // Bağıl nem değerlerini okuma
    Serial.print("Bağıl nem: "); 
    Serial.print(nem);                                       // Bağıl nemi seri terminale yazdırma
    Serial.println("%");    
      
    basinc = Pressure.getPressure();                         // Basınç değeri okundu
    Serial.print("Basinc: ");
    Serial.println(basinc);                                  // Basınç değeri seri terminale yazdırıldı                                            
    delay(1000);                                             // 1 saniye bekleme süresi
}
