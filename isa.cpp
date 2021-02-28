#include "isa.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

void error(const std::string& s){
	throw std::runtime_error(s);
}

void error(const std::string& s1, const std::string& s2){
	throw std::runtime_error(s1 + s2);
}

double gravitational_accel( double geometric_height){
	double absolute_height = Earth::radius + geometric_height;
	return Earth::surface_g_accel * (Earth::radius / absolute_height) * (Earth::radius / absolute_height);
}

double geopotential_height( double geometric_height ){
	return (Earth::radius / (Earth::radius + geometric_height)) * geometric_height;
}

double isa_temperature( double geometric_height) {
	Layer layer = get_layer(geometric_height);

	switch(layer)
	{
		case Layer::isothermal_one:
			return isa_isothermal_temperature(layer);
		case Layer::isothermal_two:
			return isa_isothermal_temperature(layer);
		case Layer::isothermal_three:
			return isa_isothermal_temperature(layer);
		case Layer::gradient_one:
			return isa_gradient_temperature(geometric_height, layer);
		case Layer::gradient_two:
			return isa_gradient_temperature(geometric_height, layer);
		case Layer::gradient_three:
			return isa_gradient_temperature(geometric_height, layer);
		case Layer::gradient_four:
			return isa_gradient_temperature(geometric_height, layer);
		default:
			break;
	}
	return 0; //just for compiler warnings
}

double isa_isothermal_temperature(Layer layer){
	switch(layer)
	{
		case Layer::isothermal_one:
			return Earth::Air::isothermal_layer_one_temperature;
		case Layer::isothermal_two:
			return Earth::Air::isothermal_layer_two_temperature;
		case Layer::isothermal_three:
			return Earth::Air::isothermal_layer_three_temperature;
		default:
			break;
	}

	return 0; // Just for compiler warnings	
}

double isa_gradient_temperature(double geometric_height, Layer layer){
	double T1;
	double a;
	double h = geopotential_height(geometric_height);
	double h1;

	switch(layer)
	{
		case Layer::gradient_one:
			a = Earth::Air::lapse_rate_layer_one;
			T1 = Earth::Air::layer_one_start_temperature;
			h1 = Earth::Air::layer_one_start_height;
			break;
		case Layer::gradient_two:
			a = Earth::Air::lapse_rate_layer_two;
			T1 = Earth::Air::layer_two_start_temperature;
			h1 = Earth::Air::layer_two_start_height;
			break;
		case Layer::gradient_three:
			a = Earth::Air::lapse_rate_layer_three;
			T1 = Earth::Air::layer_three_start_temperature;
			h1 = Earth::Air::layer_three_start_height;
			break;
		case Layer::gradient_four:
			a = Earth::Air::lapse_rate_layer_four;
			T1 = Earth::Air::layer_four_start_temperature;
			h1 = Earth::Air::layer_four_start_height;
			break;
		default:
			break;
	}

	return T1 + ( a * (h - h1));
}

double isa_pressure(double geometric_height){
	Layer layer = get_layer(geometric_height);
	switch(layer)
	{
		case Layer::isothermal_one:
			return isa_isothermal_pressure(geometric_height, layer);
		case Layer::isothermal_two:
			return isa_isothermal_pressure(geometric_height, layer);
		case Layer::isothermal_three:
			return isa_isothermal_pressure(geometric_height, layer);
		case Layer::gradient_one:
			return isa_gradient_pressure(geometric_height, layer);
		case Layer::gradient_two:
			return isa_gradient_pressure(geometric_height, layer);
		case Layer::gradient_three:
			return isa_gradient_pressure(geometric_height, layer);
		case Layer::gradient_four:
			return isa_gradient_pressure(geometric_height, layer);
		default:
			break;
	}
	return 0; // program execution will never reached this statement. Just for suppressing the compiler warning
}

// p / p1 = pow(e,(-g0/RT)(h-h1))
double isa_isothermal_pressure(double geometric_height, Layer layer){
	double h = geopotential_height(geometric_height);

	double T;	// isothermal temperature
	double h1;	// isothermal layer start geopotential height
	double p1;	// isothermal layer start pressure
	switch(layer)
	{
		case Layer::isothermal_one:
			T = Earth::Air::isothermal_layer_one_temperature;
			h1 = Earth::Air::layer_one_end_height;
			p1 = Earth::Air::isothermal_one_start_pressure;
			break;
		case Layer::isothermal_two:
			T = Earth::Air::isothermal_layer_two_temperature;
			h1 = Earth::Air::layer_two_end_height;
			p1 = Earth::Air::isothermal_two_start_pressure;
			break;
		case Layer::isothermal_three:
			T = Earth::Air::isothermal_layer_three_temperature;
			h1 = Earth::Air::layer_three_end_height;
			p1 = Earth::Air::isothermal_three_start_pressure;
			break;
		default:
			break;
	}
	return pow(Earth::Air::euler_number, ((-Earth::surface_g_accel / ( Earth::Air::perfect_gas_constant * T)) * (h - h1))) * p1;
}

double isa_gradient_pressure(double geometric_height, Layer layer){
	double p1;
	double T;
	double T1;
	double a;

	switch(layer)
	{
		case Layer::gradient_one:
			T1 = Earth::Air::sea_level_temperature;
			T = isa_temperature(geometric_height);
			a = Earth::Air::lapse_rate_layer_one;
			p1 = Earth::Air::grad_one_start_pressure;
			break;
		case Layer::gradient_two:
			T1 = Earth::Air::layer_two_start_temperature;
			T = isa_temperature(geometric_height);
			a = Earth::Air::lapse_rate_layer_two;
			p1 = Earth::Air::grad_two_start_pressure;
			break;
		case Layer::gradient_three:
			T1 = Earth::Air::layer_three_start_temperature;
			T = isa_temperature(geometric_height);
			a = Earth::Air::lapse_rate_layer_three;
			p1 = Earth::Air::grad_three_start_pressure;
			break;
		case Layer::gradient_four:
			T1 = Earth::Air::layer_four_start_temperature;
			T = isa_temperature(geometric_height);
			a = Earth::Air::lapse_rate_layer_four;
			p1 = Earth::Air::grad_four_start_pressure;
			break;
		default:
			break;
	}

	return pow(T / T1, (-Earth::surface_g_accel / (a * Earth::Air::perfect_gas_constant))) * p1;
}

Layer get_layer(double geometric_height){
	double h = geopotential_height(geometric_height);
	Layer layer;
	int diff = 10;
	using namespace Earth::Air;
	if( h < (layer_one_end_height + 20))
	{
		layer = Layer::gradient_one;
	}
	else if( h > layer_one_end_height && h < (layer_two_start_height + diff))
	{
		layer = Layer::isothermal_one;
	}
	else if(h > layer_two_start_height && h < (layer_two_end_height + diff))
	{
		layer = Layer::gradient_two;
	}
	else if( h > layer_two_end_height && h < (layer_three_start_height + diff))
	{
		layer = Layer::isothermal_two;
	}
	else if( h > layer_three_start_height && h < ( layer_three_end_height + diff))
	{
		layer = Layer::gradient_three;
	}
	else if(h > layer_three_end_height && h < ( layer_four_start_height + diff))
	{
		layer = Layer::isothermal_three;
	}
	else if(h > layer_four_start_height && h < (layer_four_end_height + diff))
	{
		layer = Layer::gradient_four;
	}
	else
		error("Unable to calculate at such height, maximum height is [105 x 10^3] meter geopotential altitude", std::to_string(h));
	return layer;
}


double isa_density(double geometric_height){
	Layer layer = get_layer(geometric_height);
	switch(layer)
	{
		case Layer::isothermal_one:
			return isa_isothermal_density(geometric_height, layer);
		case Layer::isothermal_two:
			return isa_isothermal_density(geometric_height, layer);
		case Layer::isothermal_three:
			return isa_isothermal_density(geometric_height, layer);
		case Layer::gradient_one:
			return isa_gradient_density(geometric_height, layer);
		case Layer::gradient_two:
			return isa_gradient_density(geometric_height, layer);
		case Layer::gradient_three:
			return isa_gradient_density(geometric_height, layer);
		case Layer::gradient_four:
			return isa_gradient_density(geometric_height, layer);
		default:
			break;
	}
	return 0; // program execution will never reached this statement. Just for suppressing the compiler warning
}

double isa_gradient_density(double geometric_height, Layer layer){
	double T = isa_temperature(geometric_height); // current height temperature
	double T1 = {}; // temperature at the start of thermal gradient
	double rho1 = {}; // density at the start of thermal gradient
	double a = {}; // lapse rate for thermal gradient

	switch(layer)
	{
		case Layer::gradient_one:
			T1 = Earth::Air::layer_one_start_temperature;
			rho1 = Earth::Air::grad_one_start_density;
			a = Earth::Air::lapse_rate_layer_one;
			break;
		case Layer::gradient_two:
			T1 = Earth::Air::layer_two_start_temperature;
			rho1 = Earth::Air::grad_two_start_density;
			a = Earth::Air::lapse_rate_layer_two;
			break;
		case Layer::gradient_three:
			T1 = Earth::Air::layer_three_start_temperature;
			rho1 = Earth::Air::grad_three_start_density;
			a = Earth::Air::lapse_rate_layer_three;
			break;
		case Layer::gradient_four:
			T1 = Earth::Air::layer_four_start_temperature;
			rho1 = Earth::Air::grad_four_start_density;
			a = Earth::Air::lapse_rate_layer_four;
			break;
		default:
			break;
	}

	return pow( T / T1 , -( (Earth::surface_g_accel / ( a * Earth::Air::perfect_gas_constant)) + 1 ) ) * rho1;
}

double isa_isothermal_density(double geometric_height, Layer layer){
	double T = {}; // const temperature for isothermal region
	double h = geopotential_height(geometric_height);
	double h1 = {};
	double rho1 = {};

	switch(layer)
	{
		case Layer::isothermal_one:
			T = Earth::Air::isothermal_layer_one_temperature;
			h1 = Earth::Air::layer_one_end_height;
			rho1 = Earth::Air::isothermal_one_start_density;
			break;
		case Layer::isothermal_two:
			T  = Earth::Air::isothermal_layer_two_temperature;
			h1 = Earth::Air::layer_two_end_height;
			rho1 = Earth::Air::isothermal_two_start_density;
			break;
		case Layer::isothermal_three:
			T = Earth::Air::isothermal_layer_three_temperature;
			h1 = Earth::Air::layer_three_end_height;
			rho1 = Earth::Air::isothermal_three_start_density;
			break;
		default:
			break;
	}

	return pow( Earth::Air::euler_number, ( (-Earth::surface_g_accel / (Earth::Air::perfect_gas_constant * T) )*(h - h1) ) ) * rho1;
}
