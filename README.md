# Inteligentný parkovací asistent

**Hardvér:**

- STM32F303K8TX

- Ultrazvukový senzor vzdialenosti HC-SR04

- Display LCD 16 x 2

- Bzučiak VYS7940

- RGB LED

**Ciele:**

Cieľom projektu je návrh a realizácia parkovacieho asistenta, ktorý meria vzdialenosť vozidla od prekážky pomocou ultrazvukového senzora a túto informáciu poskytuje vodičovi prostredníctvom LED indikácie a zvukovej signalizácie. Taktiež bude vypísaná nameraná vzdialenosť senzora na displeji. 

## Meranie vzdialenosti

Na meranie vzdialenosti je použitý ultrazvukový senzor HC-SR04. Funguje na princípe vysielania zvuku vpred, ktorý sa odráža od okolitých objektov. Senzor následne počúva návrat ozveny od objektu. Podľa toho koľko dlho trvalo ozvene prejsť od senzoru k objektu a naspäť, vieme vypočítať v akej vzdialenosti sa objekt nachádza. 

## Piny HC-SR04 senzora
![Piny HC-SR04 senzora](images/Ultrasonic-sensor-pinout.png)

## Schéma zapojenia periférií
![Schéma zarpojenia periférií](images/circuit_image.png)

**Členovia tímu:**

Martin Brandobur  
Boris Šupák  
Ivan Vanca

**Rozdelenie úloh:**

Boris Šupák - Logika snímača a LCD displeja  
Ivan Vanca - Komunikácia  
Martin Brandobur - Poskytnutie informácií vodičovi o vzdialenosti vozidla od prekážky 
