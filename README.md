# customclock

This is an arduino project that I created to drive a dot matrix display.  It's set up to run as a timer, but could easily be extended to display whatever you want on the dot matrix.

All parts for this project came from these kits-

[dot matrix](https://www.amazon.com/WGCD-MAX7219-Display-Arduino-Microcontroller/dp/B07FT6MZ7R/ref=asc_df_B07FT6MZ7R/?tag=hyprod-20&linkCode=df0&hvadid=295668195801&hvpos=1o2&hvnetw=g&hvrand=17697394606262929734&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9053098&hvtargid=pla-528229147177&psc=1)

[arduino uno starter kit](https://www.amazon.com/Elegoo-EL-KIT-004-Project-Starter-Tutorial/dp/B01DGD2GAO/ref=sr_1_9?ie=UTF8&qid=1539102624&sr=8-9&keywords=arduino+uno+starter+kit)

[arcade button (optional)](https://www.amazon.com/Easyget-Shaped-Illuminated-Self-resetting-Projects/dp/B00XRC9URW/ref=sr_1_6?ie=UTF8&qid=1539102698&sr=8-6&keywords=arcade+button)

The following screens show how I wired this up.  Note that the red and green LED's are not connected to anything, and can be ignored.  The three buttons on the breadboard, from top to bottom are-

reset

add 5 min

add 1 min

The arcade button starts / stops the clock.  If the timer has been reset to 0, it will count up.  Otherwise, it will count down from the specified time.

#### Full Project Setup
![alt text](https://github.com/codersblock/customclock/blob/master/screens/full.jpg "full project setup")

#### Breadboard
![alt text](https://github.com/codersblock/customclock/blob/master/screens/breadboard.jpg "breadboard")

#### Microprocessor
![alt text](https://github.com/codersblock/customclock/blob/master/screens/micro.jpg "microprocessor")
