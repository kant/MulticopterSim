/*
   MulticopterSim FlightManager class implementation that just does takeoff and hover

   Rises to a few meters then cuts motors

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#include "../MainModule/FlightManager.hpp"

class FHoverFlightManager : public FFlightManager {

    private:


        // Target
        static constexpr double ALTITUDE_TARGET = 10;

        // PID params
        static constexpr double ALT_P = 1.0;
        static constexpr double VEL_P = 1.0;

        // Velocity tracking
        double _zprev = 0;
        double _tprev = 0;

        static double min(double a, double b) 
        {
            return a < b ? a : b;
        }

        static double max(double a, double b) 
        {
            return a > b ? a : b;
        }

    public:

        // Constructor
        FHoverFlightManager(MultirotorDynamics * dynamics) 
            : FFlightManager(dynamics) 
        {
            _zprev = 0;
            _tprev = 0;
        }

        virtual ~FHoverFlightManager(void)
        {
        }

        virtual void getMotors(const double time, const MultirotorDynamics::state_t & state, double * motorvals) override
        {
            double z = -state.pose.location[2]; // NED

            // Compute dzdt setpoint and error
            double velTarget = (ALTITUDE_TARGET - z) * ALT_P;

            double velError = 0;

            if (_tprev > 0) {

                double dt = time - _tprev;
                double vel = (z-_zprev) / dt;
                velError = velTarget - vel;
            }

            _tprev = time;
            _zprev = z;

            double u = VEL_P * velError;

            u = min(max(u, 0), 1);

            FPlatformProcess::Sleep(.001);

            for (uint8_t i=0; i<_motorCount; ++i) {
                motorvals[i] = u;
            }
        }

}; // HoverFlightManager
