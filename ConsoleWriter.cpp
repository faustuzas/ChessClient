#include "ConsoleWriter.h"
#include <chrono>
#include <thread>

void ConsoleWriter::print_header()
{
	std::cout
		<< "\n======================================================\n"
		<< std::setw(35) << "Welcome to CHESS"
		<< "\n======================================================\n";
}

void ConsoleWriter::salute(bool white_won)
{
	print_dash();
	std::cout << "\nCongratulations! ";
	if (white_won) {
		std::cout << "White ";
	} else { 
		std::cout << "Black ";
	}
	std::cout << "won!!!" << std::endl;
	print_dash();
}

void ConsoleWriter::you_lost()
{
	print_dash();
	std::cout << "\nYou lost! :(\n";
	print_dash();
}

void ConsoleWriter::you_won()
{
	print_dash();
	std::cout << "\nCongratulations! You won!\n";
	print_dash();
}

int ConsoleWriter::get_game_type()
{
	std::cout
		<< "Select game mode:"
		<< "\n  1. On single computer    : Game saving is enabled for this option and ability to load game later."
		<< "\n  2. On multiple computers : Connect to your friend through the network (UDP)"
		<< "\n  3. Exit.";

	while (true)
	{
		int choice;
		std::cout << "\nYour choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		case 2:
		case 3:
			return choice;
		default:
			std::cout << "Option not available" << std::endl;
		}
	}
}

void ConsoleWriter::print_dash(int amount)
{
	std::cout << std::endl;
	for (int i = 0; i < amount; i++)
		std::cout << "=";
	std::cout << std::endl;
}

void ConsoleWriter::print_dash()
{
	print_dash(20);
} 

void ConsoleWriter::print_goodbye()
{
	std::cout
		<< "\n======================================================\n"
		<< std::setw(30) << "GOODBYE"
		<< "\n======================================================\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

bool ConsoleWriter::ask_to_load_save()
{
	std::string choice;

	std::cout << std::endl << "Old game was found. Do you want to continue? Y/N ";
	std::cin >> choice;

	if (choice[0] == 'Y' || choice[0] == 'y') {
		return true;
	} else {
		return false;
	}
}

std::string ConsoleWriter::get_ip()
{
	std::string ip;

	std::cout << "Do you want play local? Y/N ";
	std::string choice;
	std::cin >> choice;

	if (choice[0] == 'Y' || choice[0] == 'y')
	{
		ip = "127.0.0.1";
	}
	else {
		std::cout << "Enter remote IP: ";
		std::cin >> ip;
	}

	return ip;
}