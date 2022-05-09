#include <iostream>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/numeric/odeint.hpp>
void f(const double x, double &dxdt, const double t)
{
    dxdt = 3.0/(2.0*t*t) + x/(2.0*t);
}
int main()
{
    double deltatini=1.e-3; //paso de tiempo de inicio
    double abstol=1.e-6; //precisión absoluta requerida
    double reltol=0.0;   //precisión relativa (0.0 significa que no la revisa)
    double tini=1.0;   //tiempo inicial
    double tfin=10.0;    //tiempo final
    int npuntos=1000;     //número de puntos de salida
    using namespace boost::numeric::odeint;
    typedef runge_kutta_cash_karp54<double> stepper_type;
    auto stepper = make_controlled(abstol, reltol, stepper_type());
    double t = tini;
    double x = 0.0;
    for (int i = 1; i <= npuntos; i++)
    {
        double ti = tini + (i * (tfin-tini)) / npuntos;
        try {
            integrate_adaptive(stepper, f, x, t, ti, deltatini);
            t = ti;
        }
        catch (boost::exception& e) {
            std::cout << boost::diagnostic_information(e) << std::endl;
            break;
        }
        std::cout << t << " " << x << std::endl;
    }
}