/*
 *   Sıcaklık Nem Okuma örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   SHT4x çip türünü ve ölçmüm modunu ayarlamaktadır. Ölçüm sağlama hataları olursa seri terminale yazdırmaktadır.
 *   Sensörden Sıcaklık ve Bağıl nem değerleri okunmaktadır. Saniyede bir seri terminale yazdırmaktadır.
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap Sıcaklık&Nem, Basınç Ölçer için oluşturulmuştur
 *      ------> www.....com <------ //docs
 *      ------> https://github.com/deneyapkart/deneyap-sicaklik-nem-basinc-olcer-arduino-library <------
 *
*/
#include <Deneyap_SicaklikNemBasincOlcer.h>          // Deneyap_SicaklikNemBasincOlcer.h kütüphanesi eklendi

SHT4x TempHum;

void setup() {
    Serial.begin(115200);                            // Seri terminal başlatıldı
    if (!TempHum.begin(0X44)) {                      // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatıldı
        Serial.println("I2C bağlantısı başarısız "); // I2C bağlantısı başarısız olursa seri terminale yazdırıldı
        while (1);
    }

    TempHum.setChipType(SHT4X_CHIPTYPE_A);           // SHT4x çip türünü ayarlayın
    TempHum.setMode(SHT4X_CMD_MEAS_HI_PREC);         // SHT4x ölçüm modunu ayarlayın

    if (TempHum.checkSerial() == SHT4X_STATUS_OK) {  // Seri numarasının okunabildiğini ve beklentilere uygun olduğunu kontrol edin
        Serial.print("Cihaz seri numarısı: 0x");
        Serial.print(TempHum.serial[0], HEX);
        Serial.print(TempHum.serial[1], HEX);
        Serial.println();
    }
    else {
        Serial.println("Seri okunamadı veya seri sağlama toplamı yanlış.");
    }
}

void loop() {
    if (TempHum.measure() != SHT4X_STATUS_OK) {     // Ayarlanmış ölçüm modu ile ölçün
        Serial.println("Ölçüm başarısız!");
    }

    if (TempHum.TcrcOK) {                            // Verilerin doğru olup olmadığını kontrol edin ve doğruysa yazdırın
        Serial.print("Sıcaklık: ");
        /* Fahrenheit dereceleri için bunun yerine TtoDegF işlevini kullanın */
        Serial.print(TempHum.TtoDegC());             // Sıcaklığı Santigrat(Celsius) değerlerini okuma
        Serial.println(" °C");
    }
    else {
        Serial.println("Sıcaklık sağlama toplamı yanlış!");
    }

    if (TempHum.RHcrcOK) {
        Serial.print("Bağıl nem: ");
        Serial.print(TempHum.RHtoPercent());        // Bağıl nem değerlerini okuma
        Serial.println("%");
    }
    else {
        Serial.println("Bağıl nem sağlama toplamı yanlış!");
    }
    delay(1000);
}
