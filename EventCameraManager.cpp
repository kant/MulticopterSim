/*
   Event camera simulation thread

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

/*

#include "../MainModule/target/TargetManager.hpp"
#include <opencv2/highgui/highgui.hpp>

class FLorenzTargetManager : public FTargetManager {

    private:

        uint32_t _index = 0;

        const uint16_t COLS = 346;
        const uint16_t ROWS = 260;

        cv::Mat _image;

        static constexpr float S = 10;
        static constexpr float R = 28;
        static constexpr float B = 2.667;

        // meters
        static constexpr float X_OFFSET = 20;
        static constexpr float Y_OFFSET =  0;
        static constexpr float Z_OFFSET =  5;

        static constexpr float SLOWDOWN  = 3;
        static constexpr float SCALEDOWN = 5;

        float _x = 0;
        float _y = 0;
        float _z = 0;

        double _previousTime = 0;

    public:

        FLorenzTargetManager(uint32_t index)
        {
            _x = 0;
            _y = 1;
            _z = 1.05;

            _previousTime = 0;

            _image = cv::Mat::zeros(ROWS, COLS, CV_8UC3);

            _index = index;
        }

        virtual void computeLocation(double currentTime) override
        {
            double dt = (currentTime - _previousTime) / SLOWDOWN;

            _previousTime = currentTime;

            float xdot = S * (_y - _x);
            float ydot = R*_x - _y - _x*_z;
            float zdot = _x*_y - B*_z;

            _x += dt * xdot;
            _y += dt * ydot;
            _z += dt * zdot;

            _location.X = _x / SCALEDOWN + X_OFFSET;
            _location.Y = _y / SCALEDOWN + Y_OFFSET;
            _location.Z = _z / SCALEDOWN + Z_OFFSET;

            char windowName[100];
            sprintf_s(windowName, "MulticopterSim%d", _index);
            cv::imshow(windowName, _image);
            cv::waitKey(1);
        }
}; 

// Factory method for TargetManager class
FLIGHTMODULE_API FTargetManager * createTargetManager(void)
{
    static uint32_t index;

    return new FLorenzTargetManager(index);

    index++;
}


*/
