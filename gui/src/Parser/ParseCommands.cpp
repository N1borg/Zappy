/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParseCommands
*/

#include "Parser/ParseCommands.hpp"

// Initialise la carte de correspondance des commandes aux fonctions.
ParseCommands::ParseCommands()
{
    _commandMap["WELCOME\n"] = &Commands::validateWelcome;
    _commandMap["msz"] = &Commands::getMapSize;
    _commandMap["bct"] = &Commands::getTileContent;
    _commandMap["tna"] = &Commands::getTeamsName;
    _commandMap["pnw"] = &Commands::getConnectionNewPlayer;
    _commandMap["ppo"] = &Commands::getPlayerPosition;
    _commandMap["plv"] = &Commands::getPlayerLevel;
    _commandMap["pin"] = &Commands::getPlayerInventory;
    _commandMap["pex"] = &Commands::getExpulsion;
    _commandMap["pbc"] = &Commands::getBroadcast;
    _commandMap["pic"] = &Commands::getStartOfIncantation;
    _commandMap["pie"] = &Commands::getEndOfIncantation;
    _commandMap["pfk"] = &Commands::getLayingEggByPlayer;
    _commandMap["pdr"] = &Commands::getResourceDropping;
    _commandMap["pgt"] = &Commands::getResourceCollecting;
    _commandMap["pdi"] = &Commands::getPlayerDeath;
    _commandMap["enw"] = &Commands::getEggLaidByPlayer;
    _commandMap["ebo"] = &Commands::getPlayerConnectionInEgg;
    _commandMap["edi"] = &Commands::getEggDeath;
    _commandMap["sgt"] = &Commands::getTimeUnitRequest;
    _commandMap["sst"] = &Commands::getTimeUnitModification;
    _commandMap["seg"] = &Commands::getEndOfGame;
    _commandMap["smg"] = &Commands::getServerMessage;
    _commandMap["suc"] = &Commands::getUnknownCommand;
    _commandMap["sbp"] = &Commands::getCommandParameter;
}

// Analyse le message reçu et exécute la commande correspondante.
void ParseCommands::parse(const std::string &msg, Game &game)
{
    std::string command, params;
    size_t pos = msg.find(' ');
    if (pos != std::string::npos) {
        command = msg.substr(0, pos);
        params = msg.substr(pos + 1);
    } else {
        command = msg;
    }

    auto it = _commandMap.find(command);
    if (it != _commandMap.end())
        std::invoke(it->second, Commands(), params, game);
    else
        std::cerr << "Commande inconnue: " << command << std::endl;
}
