# Photon Electron http

Eletron particle example to connect to http://thethings.iO, using the http library, provided by particle.

Clone this repository and copy all the code from the .ino file to the Particle IDE.

Remember to change "YOURTOKEN" with your actual thing token.
```
request.path = "/v2/things/YOURTOKEN";
```

Add values and send them using the addValue and send function.
```
addValue("Hello", "1"); 
send();
```