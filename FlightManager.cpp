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

    public:

        FMatlabManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation) : 
            FFlightManager(dynamics, initialLocation, initialRotation)
        {
            _motorServer = new UdpServerSocket(PORT);
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

            int8_t tmp[4];

            _motorServer->receiveData((void *)tmp, 4);

            dbgprintf("%d %d %d %d", tmp[0], tmp[1], tmp[2], tmp[3]);

            motorvals[0] = 0;
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
