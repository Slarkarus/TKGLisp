#ifndef TKG_CONFIG_HPP
#define TKG_CONFIG_HPP

namespace tkg
{
    const double DOUBLE_PRECISION = 1e-12;

    inline double operator_percent_between_doubles(double left, double right)
    {
        return right - left * ((int)(right / left));
    }

    const bool DEBUG = true;
}

#endif // TKG_CONFIG_HPP
