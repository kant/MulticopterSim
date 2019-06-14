/*
   MulticopterSim VideoManager class implementation

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MulticopterSim/VideoManager.hpp"

#include <opencv2/videoio.hpp>

class FExampleVideoManager : public FVideoManager {

    protected:

        virtual void processImage(cv::Mat image) override
        {
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


// Factory method for VideoManager class
SIMPLUGIN_API FVideoManager * createVideoManager(UTextureRenderTarget2D * cameraRenderTarget) 
{
    return new FExampleVideoManager(cameraRenderTarget);
}
