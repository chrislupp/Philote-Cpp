
#include <cmath>
#include <Philote/explicit_server.h>

using philote::ExplicitServer;
using std::pow;

class RemoteParabaloid : public ExplicitServer
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
        AddInput("x", {1}, "m");
        AddInput("y", {1}, "m");

        AddOutput("f_xy", {1}, "m**2");
    }

    // Defines the partials for the discipline
    void SetupPartials()
    {
        DeclarePartials("f_xy", "x");
        DeclarePartials("f_xy", "y");
    }

    // Computes
    philote::Variables Compute(const philote::Variables &inputs)
    {
        philote::Variables outputs;

        double x = inputs.at("x")(0);
        double y = inputs.at("y")(0);

        outputs.at("f_xy")(0) = pow(x - 3.0, 2.0) + x * y +
                                pow(y + 4.0, 2.0) - 3.0;

        return outputs;
    }

    // philote::Partials ComputePartials(const philote::Variables &inputs)
    // {
    //     philote::Partials jac;

    //     double &x = inputs['x'];
    //     double &y = inputs['y'];

    //     jac['f_xy ', 'x'] = 2.0 * x - 6.0 + y;
    //     jac['f_xy ', 'y'] = 2.0 * y + 8.0 + x;

    //     return jac;
    // }
};

int main()
{
    return 0;
}