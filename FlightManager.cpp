/*
   MulticopterSim FlightManager class implementation using UDP sockets 

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MulticopterSim/FlightManager.hpp"
#include "../../Extras/sockets/UdpServerSocket.hpp"
#include "../../Extras/sockets/UdpClientSocket.hpp"

class FSocketManager : public FFlightManager {

    private:

		const char * HOST = "127.0.0.1";
        const short MOTOR_PORT = 5000;
		const short TELEM_PORT = 5001;

        UdpServerSocket * _motorServer = NULL;
		UdpClientSocket * _telemClient = NULL;


        uint32_t _count = 0;

        static void copy(double * dst, uint8_t pos, const double * src, uint8_t n)
        {
            for (uint8_t i=0; i<n; ++i) {
                dst[pos+i] = src[i];
            }
        }

    public:

        FSocketManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation) : 
            FFlightManager(dynamics, initialLocation, initialRotation)
        {
            _motorServer = new UdpServerSocket(MOTOR_PORT);
			_telemClient = new UdpClientSocket(HOST, TELEM_PORT);
            _count = 0;
        }
		
        ~FSocketManager()
        {
            _motorServer->closeConnection();
            delete _motorServer;
            _motorServer = NULL;

			_telemClient->closeConnection();
			delete _telemClient;
			_telemClient = NULL;

        }

        virtual void update(const double time, const MultirotorDynamics::state_t & state, double * motorvals) override
        {
            // Avoid null-pointer exceptions at startup
            if (!_motorServer || !_telemClient) {
                return;
            }

            _motorServer->receiveData(motorvals, 8*_motorCount);

            // Time Gyro, Quat, Location
            double telemetry[11] = {0};

            telemetry[0] = time;
            copy(telemetry, 1, state.angularVel, 3);
            copy(telemetry, 4, state.quaternion, 4);
            copy(telemetry, 8, state.pose.location, 3);

            _telemClient->sendData(telemetry, sizeof(telemetry));

        }

        virtual void getGimbal(float & roll, float &pitch, float & fov) override
        { 
            // For now, we just keep camera pointing forward
            roll = 0; 
            pitch = 0; 
            fov = 90;
        }

}; // FSocketManager


// Factory method for FlightManager class
FLIGHTMODULE_API FFlightManager * createFlightManager(MultirotorDynamics * dynamics, FVector initialLocation, FRotator initialRotation)
{
    return new FSocketManager(dynamics, initialLocation, initialRotation);
}
