sdl2 = -F/Library/Frameworks/SDL2.framework/Headers -framework SDL2
sdl2_image = -F/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image
sdl2_net = -F/Library/Frameworks/SDL2_net.framework/Headers -framework SDL2_net

main: main.o BoardField.o ChessPiece.o ConsoleWriter.o GameMenu.o IGame.o NetGame.o SDL_Manager.o SimpleGame.o UDPConnection.o MatchmakingGame.o ClientTCPConnection.o NetworkManager.o
	g++ main.o BoardField.o ChessPiece.o ConsoleWriter.o GameMenu.o IGame.o NetGame.o SDL_Manager.o SimpleGame.o UDPConnection.o MatchmakingGame.o ClientTCPConnection.o NetworkManager.o -o app $(sdl2) $(sdl2_image) $(sdl2_net)

main.o: main.cpp
	g++ main.cpp -c -std=c++11

BoardField.o: BoardField/BoardField.cpp
	g++ BoardField/BoardField.cpp -c -std=c++11

ChessPiece.o: BoardField/ChessPiece.cpp
	g++ BoardField/ChessPiece.cpp -c -std=c++11

ConsoleWriter.o: ConsoleWriter.cpp
	g++ ConsoleWriter.cpp -c -std=c++11

GameMenu.o: Games/GameMenu.cpp
	g++ Games/GameMenu.cpp -c -std=c++11

IGame.o: Games/IGame.cpp
	g++ Games/IGame.cpp -c -std=c++11

NetGame.o: Games/NetGame.cpp
	g++ Games/NetGame.cpp -c -std=c++11

SDL_Manager.o: SDL_Manager.cpp
	g++ SDL_Manager.cpp -c -std=c++11

MatchmakingGame.o: Games/MatchmakingGame.cpp
	g++ Games/MatchmakingGame.cpp -c -std=c++11

UDPConnection.o: UDP/UDPConnection.cpp
	g++ UDP/UDPConnection.cpp -c -std=c++11

ClientTCPConnection.o: TCP/ClientTCPConnection.cpp
	g++ TCP/ClientTCPConnection.cpp -c -std=c++11

NetworkManager.o: TCP/NetworkManager.cpp
	g++ TCP/NetworkManager.cpp -c -std=c++11

SimpleGame.o: Games/SimpleGame.cpp
	g++ Games/SimpleGame.cpp -c -std=c++11