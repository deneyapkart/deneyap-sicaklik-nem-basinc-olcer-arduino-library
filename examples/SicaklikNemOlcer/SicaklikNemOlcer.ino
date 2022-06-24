/*
 *   Sıcaklık Nem Okuma örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Sensörden Sıcaklık ve Bağıl nem değerleri okunmaktadır. Saniyede bir seri terminale yazdırmaktadır.
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap Sıcaklık&Nem, Basınç Ölçer için oluşturulmuştur
 *      ------> www.....com <------ //docs
 *      ------> https://github.com/deneyapkart/deneyap-sicaklik-nem-basinc-olcer-arduino-library <------
 *
*/
#include <Deneyap_SicaklikNemBasincOlcer.h>             // Deneyap_SicaklikNemBasincOlcer.h kütüphanesi eklendi

SHT4x TempHum;                                          // SHT4x icin class tanımlamasi

float sicaklik;
float nem;

void setup() {
    Serial.begin(115200);                                // Seri terminal başlatıldı
    if (!TempHum.begin(0X44)) {                          // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatıldı
        Serial.println("I2C bağlantısı başarısız ");     // I2C bağlantısı başarısız olursa seri terminale yazdırıldı
        while (1);
    }
}

void loop() {
    TempHum.measure();                                   // Ayarlanmış ölçüm modu ile ölçülmesi
    sicaklik = TempHum.TtoDegC();                        // Fahrenheit dereceleri için bunun yerine TtoDegF işlevini kullanın
    Serial.print("\nSıcaklık: ");
    Serial.print(sicaklik);                              // Sıcaklığı Santigrat(Celsius) derece olarak seri terminale yazdırma
    Serial.println(" °C");

    nem = TempHum.RHtoPercent();                         // Bağıl nem değerlerini okuma
    Serial.print("Bağıl nem: "); 
    Serial.print(nem);                                   // Bağıl nemi seri terminale yazdırma
    Serial.println("%");
    delay(1000);                                         // 1 saniye bekleme süresi
}
