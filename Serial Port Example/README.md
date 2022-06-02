## Screenshot Of Program
<img src="image/image.png"/>


During process of making this application, i encountered a problem.QSerialPort doesn't guarantee that the received message will arrive at once.It mostly comes part by part.Sometimes it comes completely.But it is not guarantee.I tried to solve this issue by giving message a code.I stored every received message in buffer. Whenever i store message in my buffer,i searched my code in buffer.If it is found,i display the part of the message until the code. And i remove that message from buffer.If it is not found i keep storing received message in buffer.

## Video 
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/jrLNwrOf7wM/0.jpg)](https://youtu.be/jrLNwrOf7wM)
