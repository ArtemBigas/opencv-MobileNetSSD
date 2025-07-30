# opencv-MobileNetSSD
Presentation project on the work of the camera and the trained model

The code is a simple example of how the camera and machine vision work together. The camera is the built-in camera of the laptop, and the model is MobileNetSSD.

1) Download MobileNetSSD_deploy.caffemodel (https://github.com/chuanqi305/MobileNet-SSD?ysclid=mdppm9h6y7813827224) and MobileNetSSD_deploy.prototxt (https://gist.github.com/mm-aditya/797a3e7ee041ef88cd4d9e293eaacf9f) and place them next to the executable file.

2) The code assumes that an alert.wav sound signal is generated using the Playsound library when the number of objects changes

Код является простым примером работы взаимодействия камеры и машинного зрения. В качестве камеры выступает встроенная камера ноутбука, а модель MobileNetSSD.

1) Скачиваются MobileNetSSD_deploy.caffemodel(https://github.com/chuanqi305/MobileNet-SSD?ysclid=mdppm9h6y7813827224) и MobileNetSSD_deploy.prototxt(https://gist.github.com/mm-aditya/797a3e7ee041ef88cd4d9e293eaacf9f) и кладутся рядом с исполняемым файлом. 

2) Код подразумевает подачу звукого сигнала alert.wav при помощи библиотеки Playsound, при изменении количества объектов
