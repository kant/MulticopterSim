/*
   MulticopterSim VideoManager class implementation

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/VideoManager.hpp"

#include <opencv2/highgui/highgui.hpp>

class FExampleVideoManager : public FVideoManager {

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

        FExampleVideoManager(UTextureRenderTarget2D * cameraRenderTarget, uint32_t index) : FVideoManager(cameraRenderTarget)
        {
            _index = index;
        }

        ~FExampleVideoManager()
        {
        }
}; 

static FExampleVideoManager * _videoManager;

FLIGHTMODULE_API void videoManagersStart(UTextureRenderTarget2D * cameraRenderTarget1,UTextureRenderTarget2D * cameraRenderTarget2)
{
    static uint32_t index;

    _videoManager = new FExampleVideoManager(cameraRenderTarget1, index);

    (void)cameraRenderTarget2;

    index++;
}

FLIGHTMODULE_API void videoManagersStop(void)
{
    _videoManager = (FExampleVideoManager *)FThreadedWorker::stopThreadedWorker(_videoManager);

}

FLIGHTMODULE_API void videoManagersGrabImages(void)
{
    _videoManager->grabImage();
}
