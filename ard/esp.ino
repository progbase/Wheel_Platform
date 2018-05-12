#include <SoftwareSerial.h> //Подключаем библиотеку работы с Последовательным портом
SoftwareSerial mySerial(9, 10); // RX, TX (Создаем виртуальный порт Esp. подключаем на цифровые пины 9 и 10 порты TX, RX от Esp)
 
void setup()
{// Открываем последовательный порт компьютера, устанавливаем скорость 9600
Serial.begin(9600);
while (!Serial) {
; // Ожидаем подключение в сериального порта. Необходимо только для Leonardo.
}
 
// set the data rate for the SoftwareSerial port
mySerial.begin(9600); //Открываем последовательный порт Esp, устанавливаем скорость 9600. Внимание!! убедитесь что Esp работает именно на этой скорости!!
mySerial.println("AT"); // Отправляем тестовую команду АТ в созданный порт, если всё работает в ответе должно прийти ОК
}
 
void loop() // run over and over
{
if (mySerial.available()) //Если есть данные в порте Esp, то передать их в последовательный порт компьютера
Serial.write(mySerial.read());
if (Serial.available()) //Если есть данные в порте компьютера, то передать их в последовательный порт Esp
mySerial.write(Serial.read());
 
}
 
