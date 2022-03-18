
<p>
    <img src="Screenshot/ScreenShot of Gui.png"  />
</p>

During process of making this program, i encountered a problem.Library of QSerialPort does not guarantee that received message comes at once.For example;
I constantly send a message which is "Hello World" from my STM32 Discovery board using Uart.

It comes like that.


"Hello" 
"  "
"Wor"
"ld"


Sometimes it comes completely.But it is not guarantee.

I tried to solve this issue by giving message a code.My code was " #%?". Message to send was "Hello World #%?". I stored every received message in buffer. Whenever i store message in my buffer , i searched my code in buffer.If it is found , i display the part of the message until the code. And i remove that message from buffer. If it is not found i keep storing received message in buffer.
