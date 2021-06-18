# Homebrew Yeast Activity Monitor

## Description
Attach a liquid level sensor to the airlock of your fermenting beer/wine/cider so that you can plot the CO2 activity.

## Tools Needed
- Arduino Uno 
- XKC-Y26A-NPN Liquid Sensor to attach to Carboy Airlock with a "U" Bend
- Grove Base Sheild (A0)
- Grove Temperature Sensor (A3)
- Grove-LCD RGB Backlight (I2C)

## Liquid Level Sensor Wiring Instructions
https://trumsense.com/products/xkc-y26a-v-contactless-water-level-sensor-1
###### Liquid Sensor (Left) Grove cable (Right)
- Black ---> Not connected
- Brown ---> Red
- Blue ---> Black
- Yellow ---> Yellow
- Yellow ---> LED ---> Black
- Not connected <--- White

## Instructions
- Boil your barley and hops. Squeeze your apples. Step on your grapes. 
- Transfer to carboy and pitch your yeast.
- Add water to the airlock so water will reach the upper stem when it bubbles.
- Gentaly shake 5-10 minutes.
- Clip the liquid sensor to the top section of your airlock. If you attach it to the bottom "U" section you will get false positives when the water rocks back and forth after each CO2 bubble.
- Open the Serial Monitor on your computer and copy and paste to excel to create your line chart.
- Post your recipe and line chart.



