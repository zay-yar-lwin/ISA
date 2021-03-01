#include <iostream>
#include "isa.hpp"
#include <iomanip>
#include <fstream>
#include <string>

void draw_table();
int main(){
	draw_table();
	return 0;
}

void draw_table(){
	std::string filename;
	std::cout << "Enter filename to draw table ";
	std::cin >> filename;
	std::ofstream out{filename};

	if(!out)
	{
		std::cerr << "can't open file: " << filename << std::endl;
		exit(1);
	}

	double end_height;
	double interval;

	std::cout << "Enter table end geometric height ";
	std::cin >> end_height;
	std::cout << "Enter interval between two height ";
	std::cin >> interval;
	char seperator = ',';
	out << "Geometric height" << seperator << "Geopotential height" << seperator << "temperature"
		<< seperator << "pressure" << seperator << "density" << std::endl;

	double height = 0;
	while(true)
	{
		out << height << seperator << geopotential_height(height) << seperator << isa_temperature(height) << seperator
			<< isa_pressure(height) << seperator << isa_density(height) << std::endl;
		height += interval;
		if(static_cast<int>(height) > static_cast<int>(end_height))
		{
			break;
		} 
	}
}
