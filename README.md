**Dew Point Monitor with LED Indicator**

A small embedded project built for the Measurements and Mechatronics course. The device reads temperature and relative humidity from a DHT11 sensor connected to an Arduino, calculates the dew point in real time using the Magnus formula, and signals the current condensation risk through a three-colour LED indicator.

**How it works**

Every 2 seconds the microcontroller polls the DHT11 sensor over a single-wire interface. The raw temperature (°C) and relative humidity (%) values are passed to a calculation function that applies the Magnus approximation:

```
α = (17.27 · T) / (237.7 + T) + ln(RH / 100)
Td = (237.7 · α) / (17.27 − α)
```

The resulting dew point is printed to the serial monitor and used to drive one of three LEDs wired to the GPIO pins:

| LED | Condition | Meaning |
|---|---|---|
| 🟢 green | Td < 28 °C | Safe — condensation unlikely |
| 🟡 yellow | 28 °C ≤ Td ≤ 30 °C | Caution — approaching condensation |
| 🔴 red | Td > 30 °C | Warning — condensation risk is high |

All three LEDs are turned off at the start of each cycle before the appropriate one is switched on, ensuring a clean state with no overlap between readings.

**Components used**

- Arduino (ATmega328-based board)
- DHT11 temperature and humidity sensor
- Green, yellow, and red LEDs on digital pins 8, 7, and 4
