#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import socket
import sys
import argparse
import re
import time
import outils

from outils import receive_response
from outils import send_message

"""
## AI

1. Infrastructure commandes
2. Infrastructure multi-commandes (queue)
3. gérer réponses serveur

"""

resources = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

# vision_levels = {
#     1: [[0], [1, 2, 3]],
#     2: [[0], [1, 2, 3], [4, 5, 6, 7, 8]],
#     3: [[0], [1, 2, 3], [4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15]]
#     4: [[0], [1, 2, 3], [4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15]]
#     5: [[0], [1, 2, 3], [4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15]]
#     6: [[0], [1, 2, 3], [4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15]]
#     7: [[0], [1, 2, 3], [4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15]]
#     8: [[0], [1, 2, 3], [4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15]]
#     }

medianes = [0, 2, 6, 12, 20, 30, 42, 56, 72]

incantation_levels = {
    2: {"players": 1, "linemate": 1, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    3: {"players": 2, "linemate": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    4: {"players": 2, "linemate": 2, "sibur": 0, "mendiane": 0, "phiras": 2, "thystame": 0},
    5: {"players": 4, "linemate": 1, "sibur": 1, "mendiane": 0, "phiras": 1, "thystame": 0},
    6: {"players": 4, "linemate": 1, "sibur": 2, "mendiane": 3, "phiras": 0, "thystame": 0},
    7: {"players": 6, "linemate": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    8: {"players": 6, "linemate": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
}

class AI:
    def __init__(self, teamname, socket, c_nbr, map_x, map_y):
        # Initial arguments
        self.socket = socket
        self.team = teamname
        self.connect_nbr = c_nbr
        self.map_x = map_x
        self.map_y = map_y

        self.level = 1
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.look = []

        self.command_queue = []
        self.sent_queue = []

        self.incantation_done = False

    def parse_look(self, look_str):
        look_str = look_str.strip('[]')
        tile_strings = re.split(r',\s*', look_str)

        result = []
        for tile in tile_strings:
            elements = tile.split()
            tile_dict = {}
            for element in elements:
                if element in tile_dict:
                    tile_dict[element] += 1
                else:
                    tile_dict[element] = 1
            result.append(tile_dict)
        return result

    def parse_inventory(self, inv_str):
        print("_____STR INV", inv_str)
        pairs = re.findall(r'(\w+)\s(\d+)', inv_str)

        result_dict = {key: int(value) for key, value in pairs}
        print("_____PARSED INV", result_dict)
        return result_dict

    def reset_commands(self):
        self.command_queue = []

    def append_command(self, cmd, arg, multiplier):
        if cmd == "Broadcast" or cmd == "Take" or cmd == "Set":
            for i in range(multiplier):
                self.command_queue.insert(0, cmd + " " + arg)
        else:
            for i in range(multiplier):
                self.command_queue.insert(0, cmd)

    def urgent_command(self, cmd, arg, multiplier):
        if cmd == "Broadcast" or cmd == "Take" or cmd == "Set":
            for i in range(multiplier):
                self.command_queue.append(cmd + " " + arg)
        else:
            for i in range(multiplier):
                self.command_queue.append(cmd)
    
    def append_sent(self, cmd):
        self.sent_queue.insert(0, cmd)

    def send_command(self):
        # take a command from the command queue
        if len(self.command_queue) != 0:
            cmd = self.command_queue.pop()

            # send this command to server
            send_message(self.socket, cmd)

            # add sent action to the sent queue
            self.append_sent(cmd)
            return 0
        else:
            print("Command queue: no more commands left")
            time.sleep(2)
            return 1

    def receive_command(self):
        response = receive_response(self.socket)
        if response == "dead" or not response:
            # TODO: implement death mechanism
            print("We are dead")
            exit()
            return
        print(f"        Received response   [<-]: {response}")
        cmd = self.sent_queue.pop()
        cmd_name, cmd_arg = "", ""
        if len(cmd.split(" ")) == 2:
            cmd_name, cmd_arg = cmd.split(" ")
        else:
            cmd_name = cmd

        if cmd_name == "Forward" or cmd_name == "Right" or cmd_name == "Left" or cmd_name == "Fork" or cmd_name == "Broadcast":
            if response == "ok":
                print(cmd_name + ": OK")
            else:
                print(f"Received an unexpected response from {cmd_name} command: ", response)

        elif cmd_name == "Look":
            if response[0] != '[':
                print(f"Received an unexpected response from {cmd_name} command: ", response)
            else:
                self.look = self.parse_look(response)

        elif cmd_name == "Inventory":
            if response[0] != '[':
                print(f"Received an unexpected response from {cmd_name} command: ", response)
            else:
                self.inventory = self.parse_inventory(response)

        elif cmd_name == "Connect_nbr":
            try:
                self.connect_nbr = int(response)
            except ValueError:
                print(f"Received an unexpected response from {cmd_name} command: ", response)
                self.connect_nbr = 0

        elif cmd_name == "Eject":
            if response == "ko":
                print("Failed to eject")
            elif response == "ok":
                print("Eject successful")

        elif cmd_name == "Incantation":
            if response == "ko":
                print("Incantation failed")
            else:
                self.level += 1
                self.incantation_done = True
                # return response
                print(response)
                response = receive_response(self.socket)
                print(response)
                # response = receive_response(self.socket)
                # print(response)
                

        elif cmd_name == "Take":
            if response == "ok":
                self.inventory[cmd_arg] += 1
            elif response == "ko":
                print(f"Couldn't take {cmd_arg}")

        elif cmd_name == "Set":
            if response == "ok":
                self.inventory[cmd_arg] -= 1
            elif response == "ko":
                print(f"Couldn't set {cmd_arg}")

    def manage_queue(self):
        while len(self.sent_queue) < 3:
            if self.send_command() == 1:
                break

    def look_strategy(self):
        for el in self.look:
            if "thystame" in el:
                print("hehe")

    def do_inventory(self, urgent):
        if urgent:
            self.urgent_command("Inventory", "", 1)
        else:
            self.append_command("Inventory", "", 1)

    def do_look(self, urgent):
        if urgent:
            self.urgent_command("Look", "", 1)
        else:
            self.append_command("Look", "", 1)
        
    @staticmethod
    def get_tile_lvl(tile_nb):
        if tile_nb == 0:
            return 0
        if tile_nb <= 3:
            return 1
        if tile_nb <= 8:
            return 2
        if tile_nb <= 15:
            return 3
        if tile_nb <= 24:
            return 4
        if tile_nb <= 35:
            return 5
        if tile_nb <= 48:
            return 6
        if tile_nb <= 63:
            return 7
        if tile_nb <= 80:
            return 8
        
    def do_walk(self, tile_nb, urgent):
        forward_lvl = self.get_tile_lvl(tile_nb)
       
        if urgent:
            self.urgent_command("Forward", "", forward_lvl)
        else:
            self.append_command("Forward", "", forward_lvl)
        
        if tile_nb in medianes:
            return

        left_or_right = tile_nb - medianes[forward_lvl]
        # print(f"____TILE NB: {tile_nb} and FORWARD LVL {forward_lvl} and LEFT OR RIGHT {abs(left_or_right)}")
        
        if left_or_right > 0:
            if urgent:
                self.urgent_command("Right", "", 1)
            else:
                self.append_command("Right", "", 1)
        elif left_or_right < 0:
            if urgent:
                self.urgent_command("Left", "", 1)
            else:
                self.append_command("Left", "", 1)
        if urgent:
            self.urgent_command("Forward", "", abs(left_or_right))
        else:
            self.append_command("Forward", "", abs(left_or_right))
    
    def do_take(self, obj_string, obj_nb, urgent):
        if urgent:
            self.urgent_command("Take", obj_string, obj_nb)
        else:
            self.append_command("Take", obj_string, obj_nb)

    def search_object(self, obj_string):
        for i in range(0, len(self.look)):
            if obj_string in self.look[i].keys():
                # returns a tile and quantity
                return i, self.look[i][obj_string]
        return "UNKNOWN", "UNKNOWN"

    def do_incantation(self):
        # if inventory has at least the same amount of items as incantation_levels[self.level] has,
        # for level 1 drop needed objects and start incantation
        if self.level == 1:
            conditions_dict = incantation_levels[self.level + 1]
            if "player" in self.look[0] and self.inventory["linemate"] >= 1:
                self.urgent_command("Set", "linemate", 1)
                self.send_command()
                self.receive_command()
                self.urgent_command("Incantation", "", 1)
                self.send_command()
                self.receive_command()

            
    def get_linemate(self, amount):
        curr_fwd = 0
        self.reset_commands()
        while self.inventory["linemate"] < amount:
            # if food < 3:
            #    get_food(5)

            print("__HERE 1")
            self.do_look(True)
            self.send_command()
            self.receive_command()
            tile_nb, obj_nb = self.search_object("linemate")
            if tile_nb == "UNKNOWN" or obj_nb == "UNKNOWN":
                if curr_fwd >= self.map_x or curr_fwd >= self.map_y:
                    print("__RIGHT UNKNOWN")
                    self.urgent_command("Right", "", 1)
                    self.send_command()
                    self.receive_command()
                    curr_fwd = 0
                else:
                    print("__FORWARD UNKNOWN")
                    self.urgent_command("Forward", "", 1)
                    curr_fwd += 1
                    self.send_command()
                    self.receive_command()
            else:
                print("__GOING NORMAL")
                self.reset_commands()
                self.do_walk(tile_nb, False)
                while len(self.command_queue) > 0:
                    self.manage_queue()
                    self.receive_command()
                self.do_take("linemate", 1, True)
                self.send_command()
                self.receive_command()
    
    def lvl2(self):
        self.do_look(False)
        self.do_look(False)
        self.get_linemate(1)
        # self.manage_queue()
        # self.receive_command()
        # print(f"[SENT] Queue: {self.sent_queue}")
        # print(f"[CMD] Queue: {self.command_queue}")
        while self.level < 2:
            self.do_incantation()
            if self.incantation_done:
                self.level += 1
                print(f"______FINAL LVL {self.level}")
                return

    def launch_loop(self):
        i = 0
        # self.append_command("Forward", "", 1)
        while True:
            self.do_look(False)
            self.do_inventory(False)
            # if i == 0:
            #     self.do_walk(3, False)
            #     self.do_walk(1, False)

            # i += 1
            # self.manage_queue()
            # self.receive_command()
            # time.sleep(3)
            # self.manage_food()
            # time.sleep(3)
            self.manage_queue()
            self.receive_command()
            print(f"[SENT] Queue: {self.sent_queue}")
            print(f"[CMD] Queue: {self.command_queue}")
            # self.reset_commands()