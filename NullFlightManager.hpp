/*
   MulticopterSim FlightManager class implementation using a stub

   Rises to a few meters then cuts motors

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/FlightManager.hpp"

class FNullFlightManager : public FFlightManager {

    public:

        // Constructor
        FNullFlightManager(MultirotorDynamics * dynamics) 
            : FFlightManager(dynamics) 
        {
        }

        virtual ~FNullFlightManager(void)
        {
        }

        virtual void getMotors(const double time, const MultirotorDynamics::state_t & state, double * motorvals) override
        {
            bool high = state.pose.location[2] < -3; // NED!

            for (uint8_t i=0; i<_motorCount; ++i) {
                motorvals[i] = high ? 0 : 0.6;
            }
        }

}; // NullFlightManager
