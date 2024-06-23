/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include "Commands/Commands.hpp"
#include "Game/Game.hpp"

// Accueille le client et initialise les messages de communication.
void Commands::validateWelcome(const std::string &params, Game &game)
{
    std::cout << "Welcome to Zappy!" << params << std::endl;
    game.getSocket()->sendMessage("GRAPHIC\n");
    game.getSocket()->sendMessage("sgt\n");
    game.getSocket()->sendMessage("msz\n");
    game.setWelcomeReceived(true);
}

// Définit la taille de la carte basée sur les paramètres reçus.
void Commands::getMapSize(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int width, height;
    iss >> width >> height;

    // // Create map
    // Map map(mapWidth, mapHeight);
    // std::vector<std::vector<Tile_t>> tiles = map.getTiles();

    // window.setCameraPosition({(mapWidth / 2.0f) * 10.0f, 20, (mapHeight / 2.0f) * 10.0f});

    // map.setPlayer(1, 3, true);
    // map.setPlayer(1, 8, true);
    // map.setPlayer(4, 8, true);
    // map.setPlayer(5, 1, true);
    // map.setFood(2, 3, true);
    // map.setFood(1, 5, true);
    // map.setFood(4, 2, true);
    // map.setFood(5, 1, true);
    // map.setEgg(4, 3, true);
    // map.setEgg(3, 5, true);
    // map.setLinemate(1, 1, true);
    // map.setDeraumere(2, 2, true);
    // map.setSibur(3, 3, true);
    // map.setMendiane(4, 4, true);
    // map.setPhiras(5, 5, true);
    // map.setThystame(6, 6, true);

    game.setMapSizeReceived(true);
}

// Met à jour la position du joueur sur la carte.
void Commands::getPlayerPosition(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, x, y, orientation;
    iss >> playerNumber >> x >> y >> orientation;
    std::cout << "Player #" << playerNumber << " is at (" << x << ", " << y << ") facing orientation " << orientation << std::endl;
}

// Affiche le contenu de la tuile spécifiée.
void Commands::getTileContent(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    std::cout << "Tile at (" << x << ", " << y << ") has resources: Food=" << q0 << ", Linemate=" << q1 << ", Deraumere=" << q2 << ", Sibur=" << q3 << ", Mendiane=" << q4 << ", Phiras=" << q5 << ", Thystame=" << q6 << std::endl;
}

// Récupère et affiche les noms des équipes du jeu.
void Commands::getTeamsName(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    std::string teamName;
    while (iss >> teamName) {
        std::cout << "Team name: " << teamName << std::endl;
    }
}

// Gère la connexion d'un nouveau joueur au jeu.
void Commands::getConnectionNewPlayer(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, x, y, orientation, level;
    std::string teamName;
    iss >> playerNumber >> x >> y >> orientation >> level >> teamName;
    std::cout << "New player #" << playerNumber << " from team " << teamName << " at (" << x << ", " << y << ") facing " << orientation << " at level " << level << std::endl;
}

// Met à jour le niveau d'un joueur.
void Commands::getPlayerLevel(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, level;
    iss >> playerNumber >> level;
    std::cout << "Player #" << playerNumber << " is at level " << level << std::endl;
}

// Récupère et affiche l'inventaire d'un joueur.
void Commands::getPlayerInventory(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    std::string teamName;
    while (iss >> teamName) {
        std::cout << "Team name: " << teamName << std::endl;
    }
}

// Signale l'expulsion d'un joueur.
void Commands::getExpulsion(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has been expelled." << std::endl;
}

// Traite et diffuse un message d'un joueur.
void Commands::getBroadcast(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    std::string message;
    iss >> playerNumber;
    std::getline(iss, message);
    std::cout << "Player #" << playerNumber << " broadcasts: " << message << std::endl;
}

// Indique le début d'une incantation.
void Commands::getStartOfIncantation(const std::string &params, Game &game)
{
    std::cout  << "Start of Incantation: " << params << std::endl;
}

// Signale la fin d'une incantation et son résultat.
void Commands::getEndOfIncantation(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int x, y, result;
    iss >> x >> y >> result;
    std::cout << "Incantation at (" << x << ", " << y << ") ended with result: " << (result ? "Success" : "Failure") << std::endl;
}

// Gère la ponte d'un œuf par un joueur.
void Commands::getLayingEggByPlayer(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has laid an egg." << std::endl;
}

// Gère la chute de ressources par un joueur.
void Commands::getResourceDropping(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, resourceIndex;
    iss >> playerNumber >> resourceIndex;
    std::cout << "Player #" << playerNumber << " dropped resource " << resourceIndex << std::endl;
}

// Gère la collecte de ressources par un joueur.
void Commands::getResourceCollecting(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber, resourceIndex;
    iss >> playerNumber >> resourceIndex;
    std::cout << "Player #" << playerNumber << " collected resource " << resourceIndex << std::endl;
}

// Signale la mort d'un joueur.
void Commands::getPlayerDeath(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int playerNumber;
    iss >> playerNumber;
    std::cout << "Player #" << playerNumber << " has died." << std::endl;
}

// Gère la ponte d'un œuf par un joueur.
void Commands::getEggLaidByPlayer(const std::string &params, Game &game)
{
     std::istringstream iss(params);
    int eggNumber, playerNumber, x, y;
    iss >> eggNumber >> playerNumber >> x >> y;
    std::cout << "Egg #" << eggNumber << " laid by Player #" << playerNumber << " at (" << x << ", " << y << ")." << std::endl;
}

// Gère la connexion d'un joueur à partir d'un œuf.
void Commands::getPlayerConnectionInEgg(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int eggNumber;
    iss >> eggNumber;
    std::cout << "Player connected from Egg #" << eggNumber << "." << std::endl;
}

// Signale la mort d'un œuf.
void Commands::getEggDeath(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int eggNumber;
    iss >> eggNumber;
    std::cout << "Egg #" << eggNumber << " has died." << std::endl;
}

// Demande de modification de l'unité de temps du jeu.
void Commands::getTimeUnitRequest(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    std::string timeUnitReq, timeUnitStr;
    int timeUnit;

    try {
        iss >> timeUnitReq >> timeUnitStr;
        timeUnit = std::stoi(timeUnitStr);
        game.setTimeUnit(timeUnit);
    } catch (const std::exception &e) {
        RaylibWrapper::log(LOG_ERROR, "INIT: Invalid frequence");
    }
}

// Demande de modification de l'unité de temps du jeu.
void Commands::getTimeUnitModification(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    int newTimeUnit;
    iss >> newTimeUnit;
    std::cout << "Time unit modified to: " << newTimeUnit << std::endl;
}

// Annonce la fin du jeu et l'équipe gagnante.
void Commands::getEndOfGame(const std::string &params, Game &game)
{
    std::istringstream iss(params);
    std::string teamName;
    iss >> teamName;
    std::cout << "Game over! Winning team: " << teamName << std::endl;
}

// Affiche un message du serveur.
void Commands::getServerMessage(const std::string &params, Game &game)
{
    std::cout  << "Server Message: " << params << std::endl;
}

// Signale la réception d'une commande inconnue.
void Commands::getUnknownCommand(const std::string &params, Game &game)
{
    std::cout  << "Unknown Command: " << params << std::endl;
}

// Affiche les paramètres d'une commande reçue.
void Commands::getCommandParameter(const std::string &params, Game &game)
{
    std::cout  << "Command Parameter: " << params << std::endl;
}
