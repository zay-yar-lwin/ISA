#ifndef International_Standard_Atmosphere_H
#define International_Standard_Atmosphere_H

//	In this atmosphere model, maximum calculable height is 105e3 meter [geopotential altitude]
//	There are four thermal gradient layers and three isothermal layers. A total of seven layers.
//	
//
//
//

namespace Earth{
	const double radius = 6.371e6;	// earth's radius = 6371[km]
	const double surface_g_accel = 9.80665;	// g = 9.80665 [m/s^2]
};
namespace Earth::Air {
	const double sea_level_pressure = 1.01325e5;	// p = 1.01325e5 [N/m^2]
	const double sea_level_density = 1.225;	// density = 1.225 [kg/m^3]
	const double sea_level_temperature = 288.16;	//temperature = 288.16[K]
	const double perfect_gas_constant = 287.053;	//R = 287.053 [ J/kg K]
	const double euler_number = 2.718281828459045;	//e = 2.7182818284590452353602874713527

	//lapse rate for temperature gradient layers for std atmosphre
	const double lapse_rate_layer_one = -6.5e-3;	// a1 = -6.5e-3[K/m]
	const double lapse_rate_layer_two = 3e-3;
	const double lapse_rate_layer_three = -4.5e-3;
	const double lapse_rate_layer_four = 4e-3;

	//temperature gradient regions start and end geopotential height
	const int layer_one_start_height = 0;
	const int layer_one_end_height = 11e3;
	const int layer_two_start_height = 25e3;
	const int layer_two_end_height = 47e3;
	const int layer_three_start_height = 53e3;
	const int layer_three_end_height = 79e3;
	const int layer_four_start_height = 90e3;
	const int layer_four_end_height = 105e3;

	//temperature at start and end of temperature gradient regions
	const double layer_one_start_temperature = 288.16;
	const double layer_one_end_temperature = 216.66;
	const double layer_two_start_temperature = layer_one_end_temperature;
	const double layer_two_end_temperature = 282.66;
	const double layer_three_start_temperature = layer_two_end_temperature;
	const double layer_three_end_temperature = 165.66;
	const double layer_four_start_temperature = layer_three_end_temperature;
	const double layer_four_end_temperature = 225.66;

	//temperature for constant temperature region
	const double isothermal_layer_one_temperature = 216.66;
	const double isothermal_layer_two_temperature = 282.66;
	const double isothermal_layer_three_temperature = 165.66;

	//pressures for standard atmosphere layers
	const double grad_one_start_pressure = Earth::Air::sea_level_pressure;
	const double isothermal_one_start_pressure = 22633.4;
	const double grad_two_start_pressure = 2489.02;
	const double isothermal_two_start_pressure = 120.478;
	const double grad_three_start_pressure = 58.3372;
	const double isothermal_three_start_pressure = 1.00992;
	const double grad_four_start_pressure = 0.104488;

	//density
	const double grad_one_start_density = Earth::Air::sea_level_density;
	const double grad_two_start_density = 0.0400225;
	const double grad_three_start_density = 0.000719015;
	const double grad_four_start_density = 2.19739e-06;
	const double isothermal_one_start_density = 0.363937;
	const double isothermal_two_start_density = 0.00148491;
	const double isothermal_three_start_density = 2.12387e-05;
};

enum class Layer{
	isothermal_one,
	isothermal_two,
	isothermal_three,
	gradient_one,
	gradient_two,
	gradient_three,
	gradient_four
};

Layer get_layer(double geometric_height);
double gravitational_accel( double geometric_height );
double geopotential_height( double geometric_height );

double isa_temperature( double geometric_height );
double isa_pressure( double geometric_height );
double isa_isothermal_pressure( double geometric_height, Layer layer);
double isa_gradient_pressure( double geometric_height, Layer layer);
double isa_density( double geometric_height );
double isa_isothermal_density(double geometric_height, Layer layer);
double isa_gradient_density(double geometric_height, Layer layer);


#endif
