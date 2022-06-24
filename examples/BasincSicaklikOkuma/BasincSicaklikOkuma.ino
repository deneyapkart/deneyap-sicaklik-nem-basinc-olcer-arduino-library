/*
 *   Basınç Sıcaklık Okuma örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Sesmörden basınç ve Sıcaklık verilerimi okumaktadır. Saniyede bir bu verileri seri terminale yazdırmaktadır.
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap Basınç Ölçer için oluşturulmuştur
 *      ------> www.....com <------ //docs
 *      ------> https://github.com/deneyapkart/deneyap-sicaklik-nem-basinc-olcer-arduino-library <------
 *
 */

#include <Deneyap_BasincOlcer.h>                               // Deneyap_BasincOlcer.h kütüphanesi eklendi

AtmosphericPressure BaroSensor;                                // AtmosphericPressure için class tanımlanması

float basinc;
float sicaklik;

void setup() {
    Serial.begin(115200);                                      // Seri terminal başlatıldı
    BaroSensor.begin(0x76);                                    // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatıldı
}

void loop() {     
    basinc = BaroSensor.getPressure();                         // Basınç değeri okundu
    Serial.print("Basinc: ");
    Serial.println(basinc);                                    // Basınç değeri seri terminale yazdırıldı

    sicaklik = BaroSensor.getTemp();                           // Sıcaklık değeri okundu
    Serial.print("Sicaklik: ");
    Serial.println(sicaklik);                                  // Sıcaklık değeri seri terminale yazdırıldı
    delay(1000);                                               // 1 saniye bekleme süresi
}
