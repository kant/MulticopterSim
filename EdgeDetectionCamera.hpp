/*
   MulticopterSim OpenCVCamera subclass using edge detection

   Copyright(C) 2019 Simon D. Levy

   MIT License
   */

#pragma once

#include "../MainModule/OpenCVCamera.hpp"

#include <opencv2/highgui.hpp>

class EdgeDetectionCamera : public OpenCVCamera {

    private:

        static constexpr float FOV        = 135;
        static constexpr Resolution_t RES = RES_640x480;

    protected:

        virtual void processImage(cv::Mat image) override
        {
            char windowName[100];
            //sprintf_s(windowName, "MulticopterSim%d", _windowIndex);
            sprintf_s(windowName, "MulticopterSim");
            cv::imshow(windowName, image);
            cv::waitKey(1);
        }

    public:

        EdgeDetectionCamera(void) 
            : OpenCVCamera(FOV, RES)
        {
        }

}; 
