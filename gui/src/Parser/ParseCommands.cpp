/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParseCommands
*/

#include "Parser/ParseCommands.hpp"

ParseCommands::ParseCommands()
{
    _commandMap["msz"] = &Commands::getMapSize;
    _commandMap["mct"] = &Commands::getMapContent;
    _commandMap["ppo"] = &Commands::getPlayerPosition;
    _commandMap["bct"] = &Commands::getTileContent;
    _commandMap["tna"] = &Commands::getTeamName;
    _commandMap["pnw"] = &Commands::getConnectionNewPlayer;
    _commandMap["plv"] = &Commands::getPlayerLevel;
    _commandMap["pin"] = &Commands::getPlayerInventory;
    _commandMap["pex"] = &Commands::getPlayerExpulsion;
    _commandMap["pbc"] = &Commands::getBroadcast;
    _commandMap["pic"] = &Commands::getStartofIncantation;
    _commandMap["pie"] = &Commands::getEndofIncantation;
    _commandMap["pfk"] = &Commands::getLayingEggbyPlayer;
    _commandMap["pdr"] = &Commands::getResourceDropping;
    _commandMap["pgt"] = &Commands::getResourceCollecting;
    _commandMap["pdi"] = &Commands::getPlayerDeath;
    _commandMap["enw"] = &Commands::getLaidEggbyPlayer;
    _commandMap["ebo"] = &Commands::getPlayerConnectioninEgg;
    _commandMap["edi"] = &Commands::getEggDeath;
    _commandMap["sgt"] = &Commands::getTimeUnitRequest;
    _commandMap["sst"] = &Commands::getTimeUnitModification;
    _commandMap["seg"] = &Commands::getEndofGame;
    _commandMap["smg"] = &Commands::getServerMessage;
    _commandMap["suc"] = &Commands::getUnknownCommand;
    _commandMap["sbp"] = &Commands::getCommandParameter;
}

void ParseCommands::parse(std::string msg)
{
    std::string command, params;
    size_t pos = msg.find(' ');
    if (pos != std::string::npos) {
        command = msg.substr(0, pos);
        params = msg.substr(pos + 1);
    } else
        command = msg;

    auto it = _commandMap.find(command);
    if (it != _commandMap.end())
        std::invoke(it->second, Commands(), params);
    else
        std::cerr << "Commande inconnue: " << command << std::endl;
}
