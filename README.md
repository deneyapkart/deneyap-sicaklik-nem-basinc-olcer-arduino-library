# Deneyap Temperature&Humidity, Barometer Sensor SHT4X Arduino Library
[FOR TURKISH VERSION](docs/README_tr.md) ![trflag](https://github.com/deneyapkart/deneyapkart-arduino-core/blob/master/docs/tr.png)

***** Add photo ****

Arduino library for Deneyap Temperature&Humidity, Barometer SHT4X

## :mag_right:Specifications 
- `Product ID` **M24**, **mpv1.0**
- `MCU` SHT4x, MS563702BA03
- `Weight` 
- `Module Dimension`
- `I2C address` 0x44, 0x76

| Address |  | 
| :---    | :---     |
| 0x44 | default address |
| 0x76 | default address |

## :closed_book:Documentation
Deneyap Temperature&Humidity, Barometer SHT4X

[SHT4x datasheet](http://download.mikroe.com/documents/datasheets/SHT40%20Datasheet.pdf)

[MS563702BA03-datasheet](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=MS5637-02BA03&DocType=Data+Sheet&DocLang=English)

[How to install a Arduino Library](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

### :paperclips:Dependencies
[Deneyap Basinc Olcer](https://github.com/deneyapkart/deneyap-basinc-olcer-arduino-library)

## :pushpin:Deneyap Temperature&Humidity, Barometer SHT4X
This Arduino library allows you to use Deneyap Temperature&Humidity, Barometer SHT4X with I2C peripheral. You can use this library in your projects with any Arduino compatible board with I2C peripheral.

## :globe_with_meridians:Repository Contents
- `/docs ` README_tr.md and product photos
- `/examples ` Examples with .ino extension sketches
- `/src ` Source files (.cpp .h)
- `keywords.txt ` Keywords from this library that will be highlighted in the Arduino IDE
- `library.properties ` General library properties for the Arduino package manager

## Version History
1.0.0 - initial release

## :rocket:Hardware Connections
- Deneyap Temperature&Humidity, Barometer and Board can be connected with I2C cable
- or 3V3, GND, SDA and SCL pins can be connected with jumper cables

|Temperature&Humidity, Barometer| Function | Board pins | 
|:--- |   :---  | :---|
|3.3V | Power   |3.3V |      
|GND  | Ground  | GND | 
|SDA  | I2C Data  | SDA pin |
|SCL  | I2C Clock | SCL pin |
|NC   | no connection|      |

## :bookmark_tabs:License Information
Please review the [LICENSE](https://github.com/deneyapkart/deneyap-sicaklik-nem-basinc-olcer-arduino-library/blob/master/LICENSE) file for license information.