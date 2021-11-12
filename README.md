# ON7WP-single-axis-WIFI-rotator-controller-based-on-Wemos-D1-R1

A WiFi remote controlled rotator interface for any brand DC rotator 

This article may be freely copied as long as the reference to the author is kept intact

A very cheap Wireless controller that can be used from anywhere in the world using a Blynk app on your phone.
The Hardware are 2 cheap Chinese boards:
•	A Wemos Mini D1 ESP8266 based microcontroller
•	A L298N Dual motor driver bridge

The software offers remote feedback of the actual rotor position and uses smart motor drive control, slowing down the speed in three steps when the target is almost reached.
The unit can drive any DC motor (Yaesu, Create,….)  An AC version is in development.
The Dual motor drives are used in Parallel so the unit can drive up to 3 A motor current.
