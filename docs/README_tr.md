# Deneyap Sıcaklık&Nem, Basınç Ölçer SHT4x Arduino Kütüphanesi

***** Fotoğraf eklenecek ****

Deneyap Sıcaklık&Nem, Basınç Ölçer SHT4x için Arduino kütüphanesidir.

## :mag_right:Özellikler 
- `Ürün ID` **M24**, **mpv1.0**
- `MCU` SHT4x, MS563702BA03
- `Ağırlık`
- `Modul Boyutları`
- `I2C Adres` 0x44, 0x76

| Adres |  | 
| :---  | :---     |
| 0x44 | varsayılan adres |
| 0x76 | varsayılan adres |

## :closed_book:Dokümanlar
Deneyap Sıcaklık&Nem, Basınç Ölçer SHT4x

[SHT4x datasheet](http://download.mikroe.com/documents/datasheets/SHT40%20Datasheet.pdf)

[MS563702BA03-datasheet](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=MS5637-02BA03&DocType=Data+Sheet&DocLang=English)

[Arduino Kütüphanesi Nasıl İndirilir](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

### :paperclips:Bağlı Olduğu Kütüphane
[Deneyap Basinc Olcer](https://github.com/deneyapkart/deneyap-basinc-olcer-arduino-library)

## :pushpin:Deneyap Sıcaklık&Nem, Basınç Ölçer SHT4x
Bu Arduino kütüphanesi Deneyap Deneyap Sıcaklık&Nem, Basınç Ölçer SHT4x I2C çevre birimi ile kullanılmasını sağlar. Arduino ile uyumlu, I2C çevre birimine sahip herhangi bir geliştirme kartı ile bu kütüphaneyi projelerinizde kullanabilirsiniz.

[Basınç Ölçer: MS563702BA03](https://github.com/deneyapkart/deneyap-basinc-olcer-arduino-library)

## :globe_with_meridians:Repo İçeriği
- `/docs` README_tr.md ve ürün fotoğrafları
- `/examples` .ino uzantılı örnek uygulamalar
- `/src` kütüphane için .cpp ve .h uzantılı dosyalar
- `keywords.txt` Arduino IDE'de vurgulanacak anahtar kelimeler
- `library.properties` Arduino yöneticisi için genel kütüphane özellikleri

## Sürüm Geçmişi
1.0.0 - ilk sürüm

## :rocket:Donanım Bağlantıları
- Deneyap Sıcaklık&Nem, Basınç Ölçer ile kullanılan geliştirme kartı I2C kablosu ile bağlanabilir
- veya jumper kablolar ile ile 3V3, GND, SDA ve SCL bağlantıları yapılabilir. 

| Sıcaklık&Nem, Basınç Ölçer | Fonksiyon| Kart pinleri |
| :---     | :---   |   :---  |
| 3.3V     | Güç    | 3.3V    |
| GND      | Toprak |GND      |
| SDA      | I2C Data  | SDA pini |
| SCL      | I2C Clock | SCL pini|
| NC       | bağlantı yok |   |

## :bookmark_tabs:Lisans Bilgisi 
Lisans bilgileri için [LICENSE](https://github.com/deneyapkart/deneyap-sicaklik-nem-basinc-olcer-arduino-library/blob/master/LICENSE) dosyasını inceleyin.