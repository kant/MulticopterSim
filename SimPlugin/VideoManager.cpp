/*
   MulticopterSim VideoManager class implementation

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MulticopterSim/VideoManager.hpp"

#include <opencv2/highgui/highgui.hpp>

class FExampleVideoManager : public FVideoManager {

    protected:

        virtual void processImage(cv::Mat image) override
        {
            cv::Mat flipped;
            cv::flip(image, flipped, -1);
            cv::imshow("MulticopterSim", flipped);
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


// Factory method for VideoManager class
SIMPLUGIN_API FVideoManager * createVideoManager(UTextureRenderTarget2D * cameraRenderTarget) 
{
    return new FExampleVideoManager(cameraRenderTarget);
}
