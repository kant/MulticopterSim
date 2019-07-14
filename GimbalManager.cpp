/*
   MulticopterSim GimbalManager class implementation using a stub

   Just spins propellers

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/GimbalManager.hpp"

class FNullGimbalManager : public FGimbalManager {

    public:

        // Constructor
        FNullGimbalManager() : FGimbalManager() 
        {
        }

        virtual ~FNullGimbalManager(void)
        {
        }

        virtual void set(double currentTime, float & roll, float & pitch, float & yaw, float & fov) override
        {
            roll  = 0;
            pitch = 0;
            yaw   = 0;
            fov   = 90;
        }

}; // NullGimbalManager


// Factory method for GimbalManager class
FLIGHTMODULE_API FGimbalManager * createGimbalManager(void)
{
    return new FNullGimbalManager();
}
