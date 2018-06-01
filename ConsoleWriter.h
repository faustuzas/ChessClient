#pragma once

#include <iostream>
#include <iomanip> 
#include <string>

class ConsoleWriter
{
public:
	static void print_header();
	static int get_game_type();
	static void print_dash(int amount);
	static void print_dash();
	static void print_goodbye();
	static void salute(bool white_won);
	static void you_lost();
	static void you_won();
	static bool ask_to_load_save();
	static std::string get_ip();
};