/*
   MulticopterSim FlightManager class implementation using Matlab over UDP

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MulticopterSim/FlightManager.hpp"
#include "sockets/UdpServerSocket.hpp"

class FMatlabManager : public FFlightManager {

    private:

        const short PORT = 5000;

        UdpServerSocket * _motorServer = NULL;

        uint32_t _count = 0;

    public:

        FMatlabManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation) : 
            FFlightManager(dynamics, initialLocation, initialRotation)
        {
            _motorServer = new UdpServerSocket(PORT);
            _count = 0;
        }
		
        ~FMatlabManager()
        {
            _motorServer->closeConnection();
            delete _motorServer;
            _motorServer = NULL;

        }

        virtual void update(const double time, const MultirotorDynamics::state_t & state, double * motorvals) override
        {
            // Avoid null-pointer exceptions at startup
            if (!_motorServer) {
                return;
            }

            double tmp = 0;
            _motorServer->receiveData((void *)&tmp, 8);

            dbgprintf("%f", tmp);
        }

        virtual void getGimbal(float & roll, float &pitch, float & fov) override
        { 
            // For now, we just keep camera pointing forward
            roll = 0; 
            pitch = 0; 
            fov = 90;
        }

}; // MatlabManager


// Factory method for FlightManager class
FLIGHTMODULE_API FFlightManager * createFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation)
{
    return new FMatlabManager(dynamics, initialLocation, initialRotation);
}
