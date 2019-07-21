/*
   MulticopterSim VideoManager class implementation

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/VideoManager.hpp"

#include <opencv2/highgui/highgui.hpp>

class FExampleVideoManager : public FVideoManager {

    protected:

        virtual void processImage(cv::Mat image) override
        {
            cv::imshow("MulticopterSim", image);
            cv::waitKey(1);
        }

    public:

        FExampleVideoManager(UTextureRenderTarget2D * cameraRenderTarget) :
            FVideoManager(cameraRenderTarget)

        {
        }

        ~FExampleVideoManager()
        {
        }
}; 

static FExampleVideoManager * _videoManager;

FLIGHTMODULE_API void videoManagersStart(UTextureRenderTarget2D * cameraRenderTarget1,UTextureRenderTarget2D * cameraRenderTarget2)
{
    _videoManager = new FExampleVideoManager(cameraRenderTarget1);

    (void)cameraRenderTarget2;
}

FLIGHTMODULE_API void videoManagersStop(void)
{
    _videoManager = (FExampleVideoManager *)FThreadedWorker::stopThreadedWorker(_videoManager);

}

FLIGHTMODULE_API void videoManagersGrabImages(void)
{
    _videoManager->grabImage();
}
