**Introducing AWTRIX-Nodes**

AWTRIX Nodes are smart devices (based on ESP8266) that send their data directly to AWTRIX 2.0 and display it in the form of an app. For example, an AWTRIX node can measure temperature  with a DHT22 and send it to AWTRIX.

This is especially intended for users who do not have their own smarthome server like IOBroker, FHEM etc.

Download the template firmware for an AWTRIX Node, edit the node-conf.h and modify it in doJob to send a custom text and IconID. 

AWTRIX displays each node at the end of the apploop. After that, AWTRIX deletes the data. So if the node is offline or doesnt sends any data, the node is not longer displayed.
