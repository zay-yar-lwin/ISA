#include <iostream>
#include "isa.hpp"
#include <iomanip>
#include <fstream>

int main(){
	double h;
	std::cout << "Enter geometric altitude";
	try{
		while(true)
		{
			std::cin >> h;
			std::cout << std::setw(12) << h << std::setw(12) << geopotential_height(h)
				<< std::setw(12) << isa_temperature(h) << std::setw(12) << isa_pressure(h)
				<< std::setw(12) << isa_density(h) << std::endl; 
		}
	} catch ( std::runtime_error &e)
	{
		std::cerr << "Runtime error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
