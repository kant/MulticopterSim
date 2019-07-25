/*
   MulticopterSim OpenCVManager class implementation using a simple display

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/OpenCVManager.hpp"

#include <opencv2/highgui/highgui.hpp>

class ExampleVideoManager : public OpenCVManager {

    private:

        uint32_t _index;

    protected:

        virtual void processImage(cv::Mat image) override
        {
            char windowName[100];
            sprintf_s(windowName, "MulticopterSim%d", _index);
            cv::imshow(windowName, image);
            cv::waitKey(1);
        }

    public:

        ExampleVideoManager(UTextureRenderTarget2D * cameraRenderTarget, uint32_t index) : OpenCVManager(cameraRenderTarget)
        {
            _index = index;
        }

        ~ExampleVideoManager()
        {
        }
}; 

FLIGHTMODULE_API VideoManager * createVideoManager(UTextureRenderTarget2D * renderTarget, uint8_t id)
{
    (void)id;

    static uint8_t index;

    return new ExampleVideoManager(renderTarget, index++);
}
