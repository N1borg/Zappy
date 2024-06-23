/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Parser
*/

#include "Parser/ParseArguments.hpp"

// Constructeur qui initialise les arguments de la ligne de commande.
ParseArguments::ParseArguments(int argc, char *argv[]) : _argc(argc), _argv(argv) {}

// Parse les arguments de la ligne de commande pour extraire le port et l'adresse de la machine.
void ParseArguments::parse()
{
    if (_argc != 5)
        throw std::runtime_error("Error: Invalid arguments");

    try {
        if (std::string(_argv[1]) == "-p" && std::string(_argv[3]) == "-h") {
            _port = std::stoi(_argv[2]);
            _machine = std::string(_argv[4]);
        }
        if (std::string(_argv[1]) == "-h" && std::string(_argv[3]) == "-p") {
            _port = std::stoi(_argv[4]);
            _machine = std::string(_argv[2]);
        }
    } catch (const std::exception &e) {
        throw std::runtime_error("Error: Invalid arguments");
    }
}

// Valide si le message reçu est le message de bienvenue.
bool ParseArguments::validateConnection(std::string msg)
{
    return msg == "WELCOME\n";
}

// Définit le port sur lequel le serveur doit écouter.
void ParseArguments::setPort(int port)
{
    _port = port;
}

// Renvoie le port sur lequel le serveur écoute.
int ParseArguments::getPort() const
{
    return _port;
}

// Définit l'adresse de la machine hôte.
void ParseArguments::setMachine(std::string machine)
{
    _machine = machine;
}

// Renvoie l'adresse de la machine hôte.
std::string ParseArguments::getMachine() const
{
    return _machine;
}
