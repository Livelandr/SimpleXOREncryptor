#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <bitset>
#include <thread>
#include <chrono>

#include "color.hpp"

std::ostream& operator<< (std::ostream& os, std::byte b) {
	return os << std::bitset<8>(std::to_integer<int>(b));
}

std::string helloText = R"(
  _      _           _                 _      _      __   ______  _____    ______                             _             
 | |    (_)         | |               | |    ( )     \ \ / / __ \|  __ \  |  ____|                           | |            
 | |     ___   _____| | __ _ _ __   __| |_ __|/ ___   \ V / |  | | |__) | | |__   _ __   ___ _ __ _   _ _ __ | |_ ___  _ __ 
 | |    | \ \ / / _ \ |/ _` | '_ \ / _` | '__| / __|   > <| |  | |  _  /  |  __| | '_ \ / __| '__| | | | '_ \| __/ _ \| '__|
 | |____| |\ V /  __/ | (_| | | | | (_| | |    \__ \  / . \ |__| | | \ \  | |____| | | | (__| |  | |_| | |_) | || (_) | |   
 |______|_| \_/ \___|_|\__,_|_| |_|\__,_|_|    |___/ /_/ \_\____/|_|  \_\ |______|_| |_|\___|_|   \__, | .__/ \__\___/|_|   
                                                                                                   __/ | |                  
                                                                                                  |___/|_|      

)";

int main()
{
	
	std::cout << dye::red(helloText) << std::endl;

	std::string targetFile;
	std::string keyFile;
	std::string outputFilus;


	std::cout << dye::aqua("Input target file: ") << std::endl;
	std::getline(std::cin, targetFile);

	std::cout << std::endl;

	std::cout << dye::aqua("Input key file: ") << std::endl;
	std::getline(std::cin, keyFile);

	std::cout << std::endl;

	std::cout << dye::aqua("Input output file: ") << std::endl;
	std::getline(std::cin, outputFilus);

	std::cout << std::endl;



	std::basic_ifstream<std::byte> input(targetFile, std::ios::binary | std::ios::in);
	std::basic_ifstream<std::byte> keyfile(keyFile, std::ios::binary | std::ios::in);
	std::ofstream outputFile(outputFilus, std::ios::binary | std::ios::out );


	std::vector<std::byte> file_content{ std::istreambuf_iterator<std::byte>(input), {} };
	std::vector<std::byte> key_encryption{ std::istreambuf_iterator<std::byte>(keyfile), {} };



	std::cout << dye::aqua("Encryption started...") << std::endl;
	std::cout << dye::aqua("Iterations: ") << file_content.size() << std::endl;

	std::cout << std::endl;


	auto start = std::chrono::steady_clock::now();

	std::vector<std::byte> encrypted;

	for (unsigned long long i = 0; i < file_content.size(); i++ ) {
		std::byte key = key_encryption[(i - key_encryption.size() * (i / key_encryption.size()))];

		encrypted.push_back(file_content[i] ^ key);
	}
			

	outputFile.write( (const char*) &encrypted[0], encrypted.size());

	outputFile.close();


	auto end = std::chrono::steady_clock::now();

	std::cout << dye::green("XOR encryption completed!") << std::endl;

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << dye::aqua("Elapsed time: ") << elapsed_seconds.count() << "s\n";

	system("PAUSE");


}