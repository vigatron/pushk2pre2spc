#include <iostream>
#include <filesystem>

#include "mods/argspars.hpp"
#include "mods/memarrblk.hpp"

enum enErr {
	enErr_ok = 0,
	enErr_unk,
	enErr_srcfile_missed,
	enErr_srcfile_bounds
};

//

bool fileExists(const std::string& path) {
	try {
		return std::filesystem::exists(path) &&
			std::filesystem::is_regular_file(path);
	} catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Ошибка доступа: " << e.what() << '\n';
		return false; } }

//

int runproc( std::string mode , std::string fname , uint32_t offs, uint16_t length ) {

	MemArrBlk mblk;

	if( ! fileExists ( fname ) )
		return enErr_srcfile_missed;

	if( ! mblk.load( fname , offs , length ) ) 
		return enErr_srcfile_bounds;

	uint8_t fng[256] = {0};

	for( int i = 0 ; i < mblk.size() ; i++ ) {
		uint8_t sym = mblk.data()[i];
		if ( ! fng[sym] ) fng[sym] = 1; }

	if( mode.find("t") != std::string::npos ) {
		for( int i = 0; i < 256 ; i++ ) {
			uint8_t v = fng[i] ? '#' : '.' ;
			bool sep = (i % 16) == 15;
			std::cout << v; if( sep ) std::cout << '\n'; } }

	return enErr_ok; }

//

int main(int argc, char* argv[]) {

	int r = EXIT_SUCCESS;

	try {

		auto params = ArgsParser::parse(argc, argv);

		std::cout
				<< "Mode: "   << params.mode      << "\n"
				<< "File: "   << params.file_name << "\n"
				<< "Offset: " << params.offset    << "\n"
				<< "Length: " << params.length    << "\n";

		r = runproc( params.mode , params.file_name , params.offset , params.length );
		
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << "\n";
		return EXIT_FAILURE;
	}

	return r;
}