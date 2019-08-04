/*
   Event camera simulation thread

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

/*
#include "../MainModule/ThreadedWorker.hpp"
#include <opencv2/highgui/highgui.hpp>

class FEventCameraManager : public FThreadedWorker {

    private:

        uint32_t _index = 0;

        const uint16_t COLS = 346;
        const uint16_t ROWS = 260;

        cv::Mat _image;

    public:

        FEventCameraManager(uint32_t index)
        {
            _image = cv::Mat::zeros(ROWS, COLS, CV_8UC3);

            _index = index;
        }

        void performTask(double currentTime)
        {
            char windowName[100];
            sprintf_s(windowName, "MulticopterSim%d", _index);
            cv::imshow(windowName, _image);
            cv::waitKey(1);
        }
}; 
*/
