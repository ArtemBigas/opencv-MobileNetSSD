#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")  // линкуем winmm.lib для PlaySound

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

int main() {
    cv::dnn::Net net = cv::dnn::readNetFromCaffe("MobileNetSSD_deploy.prototxt",
        "MobileNetSSD_deploy.caffemodel");
    if (net.empty()) {
        std::cerr << "Ошибка загрузки модели!" << std::endl;
        return -1;
    }

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Не удалось открыть камеру!" << std::endl;
        return -1;
    }

    std::vector<std::string> classNames = {
        "background", "aeroplane", "bicycle", "bird", "boat", "bottle", "bus",
        "car", "cat", "chair", "cow", "diningtable", "dog", "horse",
        "motorbike", "person", "pottedplant", "sheep", "sofa", "train", "tvmonitor"
    };

    int prevCount = 0;

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) break;

        cv::Mat inputBlob = cv::dnn::blobFromImage(frame, 0.007843,
            cv::Size(300, 300),
            cv::Scalar(127.5, 127.5, 127.5),
            false);
        net.setInput(inputBlob);
        cv::Mat detection = net.forward();

        int personCount = 0;
        for (int i = 0; i < detection.size[2]; ++i) {
            float confidence = detection.ptr<float>(0, 0, i)[2];
            int classId = static_cast<int>(detection.ptr<float>(0, 0, i)[1]);
            if (confidence > 0.2 && classId == 15) {
                personCount++;
                int left = int(detection.ptr<float>(0, 0, i)[3] * frame.cols);
                int top = int(detection.ptr<float>(0, 0, i)[4] * frame.rows);
                int right = int(detection.ptr<float>(0, 0, i)[5] * frame.cols);
                int bottom = int(detection.ptr<float>(0, 0, i)[6] * frame.rows);
                cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom),
                    cv::Scalar(0, 255, 0), 2);
            }
        }

        if (personCount != prevCount) {
            std::cout << "Обнаружено людей: " << personCount << std::endl;
            prevCount = personCount;
            // Воспроизвести звук alert.wav (асинхронно)
            PlaySound(TEXT("alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }

        cv::imshow("Detection", frame);
        int key = cv::waitKey(1);
        if (key == 27) {  // код ESC — 27
            std::cout << "Выход по ESC" << std::endl;
            break;
        }
    }

    return 0;
}
