#include <explicit_server.h>

class RemoteParabaloid : ExplicitServer
{
public:
    // Constructor
    RemoteParabaloid() = default;

    // Destructor
    ~RemoteParabaloid() = default;

private:
    // Defines the variables for the discipline
    void Setup()
    {
        DefineInput("x", {1}, "m");
        DefineInput("y", {1}, "m");

        DefineOutput("f_xy", {1}, "m**2");
    }

    // Defines the partials for the discipline
    void SetupPartials()
    {
        DefinePartials("f_xy", "*");
    }

    // Computes
    philote::Variables Compute(const philote::Variables &inputs)
    {
        philote::Variables outputs;

        double &x = inputs['x'];
        double &y = inputs['y'];

        outputs['f_xy '] = pow(x - 3.0, 2) + x * y + pow(y + 4.0, 2) - 3.0;

        return outputs;
    }

    philote::Partials ComputePartials(const philote::Variables &inputs)
    {
        philote::Partials jac;

        double &x = inputs['x'];
        double &y = inputs['y'];

        jac['f_xy ', 'x'] = 2.0 * x - 6.0 + y;
        jac['f_xy ', 'y'] = 2.0 * y + 8.0 + x;

        return jac;
    }
};