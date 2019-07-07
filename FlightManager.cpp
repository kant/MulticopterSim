/*
   MulticopterSim FlightManager class implementation using a stub

   Just spins propellers

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MulticopterSim/FlightManager.hpp"

class FNullFlightManager : public FFlightManager {

    public:

        // Constructor
        FNullFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation) 
            : FFlightManager(dynamics, initialLocation, initialRotation) 
        {
        }

        virtual ~FNullFlightManager(void)
        {
        }

        virtual void getMotors(const double time, const MultirotorDynamics::state_t & state, double * motorvals) override
        {
            for (uint8_t i=0; i<_motorCount; ++i) {
                motorvals[i] = 0.1;
            }
        }

}; // NullFlightManager


// Factory method for FlightManager class
FLIGHTMODULE_API FFlightManager * createFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation)
{
    return new FNullFlightManager(dynamics, initialLocation, initialRotation);
}
