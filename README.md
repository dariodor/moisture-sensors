# Moisture Sensors #

A moisture sensor controller for the Arduino platform

This program read 3 moisture sensors and upload the data to xively.com

## How to make a cheap soil moisture sensor ##

Follow this http://www.cheapvegetablegardener.com/how-to-make-cheap-soil-moisture-sensor-2/

## Schema ##

http://upload.wikimedia.org/wikipedia/commons/d/db/Resistive_divider.png

R1 = 1kΩ

R2 = moisture sensor

Vin = 5v

## compatibility issues ##

WifiShield R3 doesn't work with IDE 1.0.5, 1.0.3 https://github.com/arduino/Arduino/issues/1840 - I switched to 1.0.4