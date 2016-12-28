#include <iostream>
#include "fixed_point/fixed_point.hpp"

void simulate();
void control_fixp();
void print();
using std::cout;
using std::endl;

double real_value = 0.0;
int u_control;
int r_setpoint;
int16_t sensordata;

using namespace has_castle::fixed_point;
const auto Kp = fp32_t<2>{10.25};
const auto Sens_conv = fp32_t<12>{1. / 45.5};

int main()
{
    cout << "Sens_conv: " << Sens_conv
        << "\tKp: " << Kp << endl << endl;
    for (auto i = 0; i < 10; i++)
    {
        if (1 <= i)
            r_setpoint = 100;
        simulate();
        print();
        control_fixp();
    }
    return 0;
}

void control_fixp()
{
    auto y = Sens_conv * sensordata;
    auto e = fp32_t<12>{r_setpoint} - y;
    auto u = e * Kp;
    u_control = static_cast<int>(u);

    cout << "\t-- CONTROL ::";
    cout << "\ty: " << y;
    cout << "  \te: " << e;
    cout << "   \tu: " << u << endl;
}

void simulate()
{
    // Simple model of a dynamic system with a nontrivial relation between
    // the control signal (u) and a sensor reading in nonstandard units.
    real_value = 0.95 * real_value + 0.15 * u_control;
    sensordata = real_value * 45.5;
}

void print()
{
    cout << "SIM ::";
    cout << "\tcontrol " << u_control;
    cout << "\tvalue: " << real_value;
    cout << "\tsensor: " << sensordata;
}
