# Inteligentný parkovací asistent

**Hardvér:**

- STM32F303K8TX

- Ultrazvukový senzor vzdialenosti HC-SR04

- Display LCD 1602A

- Bzučiak TMB12A05

- RGB LED

**Ciele:**

Cieľom projektu je návrh a realizácia parkovacieho asistenta, ktorý meria vzdialenosť vozidla od prekážky pomocou ultrazvukového senzora a túto informáciu poskytuje vodičovi prostredníctvom LED indikácie a zvukovej signalizácie. Taktiež bude vypísaná nameraná vzdialenosť senzora na displeji. 

## Meranie vzdialenosti

Senzor HC-SR04 meria vzdialenosť na základe času letu ultrazvukovej vlny. Mikrokontrolér vyšle na pin TRIG krátky impulz v logickej 1 s dĺžkou minimálne 10 µs, čím sa spustí meranie. Senzor následne vyšle ultrazvukový signál smerom dopredu a čaká na jeho odraz od prekážky. Počas tohto merania je na pine ECHO generovaný impulz, ktorého dĺžka v stave HIGH predstavuje čas, za ktorý sa zvuková vlna dostala k prekážke a späť k senzoru. Vzdialenosť potom počítame ako:

$$
d = \frac{t \cdot v}{2}
$$

- d je vzdialenosť od prekážky,
- t je dĺžka impulzu ECHO 
- v je rýchlosť zvuku vo vzduchu

## Piny HC-SR04 senzora
![Piny HC-SR04 senzora](images/Ultrasonic-sensor-pinout.png)

## Schéma zapojenia periférií
![Schéma zarpojenia periférií](images/circuit_image.png)

**Členovia tímu:**

Martin Brandobur  
Boris Šupák  
Ivan Vanca

**Rozdelenie úloh:**

Boris Šupák - IOC a logika LCD displeja  
Ivan Vanca - Logika snímača a časovač  
Martin Brandobur - Poskytnutie informácií vodičovi o vzdialenosti vozidla od prekážky 
