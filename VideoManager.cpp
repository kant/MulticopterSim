/*
   MulticopterSim VideoManager class implementation

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/VideoManager.hpp"

#include <opencv2/highgui/highgui.hpp>

class ExampleVideoManager : public VideoManager {

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

        ExampleVideoManager(UTextureRenderTarget2D * cameraRenderTarget, uint32_t index) : VideoManager(cameraRenderTarget)
        {
            _index = index;
        }

        ~ExampleVideoManager()
        {
        }
}; 

static ExampleVideoManager * _videoManager;

FLIGHTMODULE_API void videoManagersStart(UTextureRenderTarget2D * cameraRenderTarget1,UTextureRenderTarget2D * cameraRenderTarget2)
{
    static uint32_t index;

    _videoManager = new ExampleVideoManager(cameraRenderTarget1, index);

    (void)cameraRenderTarget2;

    index++;
}

FLIGHTMODULE_API void videoManagersStop(void)
{
    delete _videoManager;
    _videoManager = NULL;

}

FLIGHTMODULE_API void videoManagersGrabImages(void)
{
    _videoManager->grabImage();
}
