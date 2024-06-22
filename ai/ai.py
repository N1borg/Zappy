#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import socket
import sys
import argparse
import re
import time
import outils
import threading

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
    2: {"player": 1, "linemate": 1, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    3: {"player": 2, "linemate": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    4: {"player": 2, "linemate": 2, "sibur": 0, "mendiane": 0, "phiras": 2, "thystame": 0},
    5: {"player": 4, "linemate": 1, "sibur": 1, "mendiane": 0, "phiras": 1, "thystame": 0},
    6: {"player": 4, "linemate": 1, "sibur": 2, "mendiane": 3, "phiras": 0, "thystame": 0},
    7: {"player": 6, "linemate": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    8: {"player": 6, "linemate": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
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
        self.prev_look = self.look

        self.queue = []
        self.sent_queue = []

        self.incantation_done = False

        self.names = ["Rom", "Rob", "Ana", "Val", "Vic", "Jul", "Idk", "Lol", "Kek", "Uwu"]
        self.name = self.names[0]

        self.broadcast_dir = 0
        self.proposed_incantation = False
        self.success_incantation = False
        self.responses_count = 0
        
        self.lock = threading.Lock()
        self.grace = threading.Event()

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
        pairs = re.findall(r'(\w+)\s(\d+)', inv_str)

        result_dict = {key: int(value) for key, value in pairs}
        return result_dict

    def broadcast_receive(self, response):
        inc_list = ["inc2", "inc3", "inc4", "inc5", "inc6", "inc7"]
        response = response[8:] if response[:8] == "message " else response
        print(response)
        self.direction, message = response.split(", ")

        int(self.direction)
        message = message.split("/!/")
        if isinstance(message, list) and len(message) == 3:
            team, name, cmd = message[0], message[1], message[2]
        else:
            print("Other team broadcast, ignoring")
            return 1
        if self.team != team:
            print("Other team broadcast, ignoring")
            return 1

        # if cmd == "qiela":
        #     self.urgent_command("Broadcast", f"{self.team}/!/{self.name}/!/cmoi", 1)
        #     self.command()
        #     self.receive_command("")
        # elif cmd == "cmoi":
        #     self.name = self.names[self.responses_count + 1]
        # elif cmd == "suila":
        #     pass
        # elif cmd in inc_list:
        #     self.find_incantation()
        # elif cmd == "oute" and self.proposed_incantation:
        #     self.urgent_command("Broadcast", f"{self.team}/!/{self.name}/!/icila", 1)
        #     self.command()
        #     self.receive_command("")
            

 
    def command(self, cmd, arg):
        command = cmd if arg == "" else cmd + " " + arg
        self.queue.insert(0, command)
        # send_message(self.socket, command)
        # self.command_response(cmd, arg)
                
    def command_response(self):
        cmd_okko = ["Incantation", "Fork", "Eject", "Take", "Set"]
        response = receive_response(self.socket)
        
        if self.grace.is_set():
            return
            
        cmd = self.sent_queue.pop().split(" ")[0]
        print(f"        Received response   [<-]: {response}")

        if response == "dead" or not response:
            print("We are dead")
            exit()
            return
        
        if response[:8] == "message ":
            self.broadcast_receive(response)
            response = receive_response(self.socket)
            print(f"        Received response   [<-]: {response}")

        if response[0] == "[":
            if cmd == "Inventory":
                
                self.inventory = self.parse_inventory(response)
                # print(f"_________INV {response} vs {self.inventory}")
            elif cmd == "Look":
                self.look = self.parse_look(response)
                if self.look:
                    self.prev_look = self.look
                elif not self.look:
                    self.look = self.prev_look

        elif response == "ko":
            if cmd in cmd_okko:
                print(f"{cmd} failed.")
            else:
                print(f"Unexpected response from {cmd} command: {response}")

        elif response == "ok":
            if cmd == "Incantation":
                response = receive_response(self.socket)
                print(response)
                response = receive_response(self.socket)
                print(response)
                self.level = int(response.split("Current level: ")[1])
                # print("____LVL ", self.level)
                self.incantation_done = True

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

    def walk(self, tile_nb):
        with self.lock:
            self.queue = []
        # print(self.queue)
        fwd_lvl = self.get_tile_lvl(tile_nb)

        for i in range(fwd_lvl):
            self.command("Forward", "")
        
        if tile_nb in medianes:
            return
        
        left_or_right = tile_nb - medianes[fwd_lvl]
        
        if left_or_right > 0:
            self.command("Right", "")
        elif left_or_right < 0:
            self.command("Left", "")

        for i in range(abs(left_or_right)):
            self.command("Forward", "")
    
                
    def search_object(self, obj_string):
        # self.command("Look", "")
        # print(self.look if self.look else "heyr")
        for i in range(0, len(self.look)):
            if obj_string in self.look[i].keys():
                # returns a tile and quantity
                return i, self.look[i][obj_string]
        return False, False

    def get_object(self, obj_name, amount):
        curr_fwd = 0
        with self.lock:
            self.queue = []
        
        while self.inventory[obj_name] < amount:
            # self.queue = []
            # print(self.look)
            # self.command("Look", "")
            # print(self.look)
            # tile_nb, obj_nb = -1, -1
            if self.grace.is_set():
                with self.lock:
                        self.queue = []
                # print("Graceful shutdown initiated. Exiting get_object.")
                break
            if obj_name in self.look[0]:
                with self.lock:
                    self.queue = []
                # print(f"____INV {self.inventory}")
                for i in range(self.look[0][obj_name]):
                    self.command("Take", obj_name)
                # self.grace.wait(2.0)
            # self.command("Inventory", "")
            if self.inventory[obj_name] >= amount:
                # print("here")
                with self.lock:
                    self.queue = []
                break
            if self.inventory['food'] < 4:
                self.get_object('food', 7)

            tile_nb, obj_nb = self.search_object(obj_name)
            if tile_nb and obj_nb:
                # print("_______NORMAL")
                with self.lock:
                    self.queue = []
                self.walk(tile_nb)
                for i in range(obj_nb):
                    self.command("Take", obj_name)
                    # self.command("Inventory", "")
                # print(self.queue)
                self.grace.wait(0.5)
            # print(f"______________AMOUNT EXIT: {self.inventory[obj_name] >= amount} with {self.inventory[obj_name]} and {amount}\n_________WITH {self.inventory}") 
            elif not tile_nb and not obj_nb:
                if curr_fwd >= self.map_x or curr_fwd >= self.map_y:
                    with self.lock:
                        self.queue = []
                    self.command("Right", "")
                    # print("_______NO OBJ ROW")
                    for i in range(3):
                        self.command("Forward", "")
                    self.command("Left", "")
                    curr_fwd = 0
                else:
                    with self.lock:
                        self.queue = []
                        self.command("Forward", "")
                    # print("_______NO OBJ")
                    # self.command("Look", "")
                    curr_fwd += 1
            if self.inventory[obj_name] >= amount:
                # print("___________HERE")
                with self.lock:
                    self.queue = []
                break
        with self.lock:
            self.queue = []
            
    
    def incantate(self):
        # self.command("Look", "")
        old_lvl = self.level
        while True:
            # if self.grace.is_set():
            #     print("Graceful shutdown initiated. Exiting incantate.")
            #     return
            if self.level != old_lvl:
                break
            if self.level + 1 == 2 and self.proposed_incantation == False:
                conditions_dict = incantation_levels[self.level + 1]
                if self.inventory['linemate'] >= 1:
                    # print("Im going here without mom's permission")
                    self.command("Set", "linemate")
                    self.command("Incantation", "")
                    self.proposed_incantation = True
            
                # time.sleep(1)
        print("BROKEEEEEEEEEEEE")

    def receive_management(self):
        while not self.grace.is_set():
            # print("BBBBBBBBBBbb")
            self.command_response()
            if self.grace.is_set():
                break
        print("Outside the BBBB loop")
        
    def send_management(self):
        while not self.grace.is_set():
            with self.lock:
                if len(self.sent_queue) < 3:
                    count = 2
                    while self.queue and count > 0: 
                        action = self.queue.pop()
                        self.sent_queue.insert(0, action)
                        send_message(self.socket, action)
                        count -= 1
            if not self.queue:
                self.grace.wait(0.02)
            if self.grace.is_set():
                break
                    
                # print("AAAAAAAAAAA")
                # time.sleep(1)
        print("Outside the AAAA loop")
        
    
    def stop(self):
        self.grace.set()
        
    def look_management(self):
        while not self.grace.is_set():
            # self.queue = []
            # self.command("Look", "")
            if "Look" not in self.sent_queue:
                self.sent_queue.insert(0, "Look")
                send_message(self.socket, "Look")
            if "Inventory" not in self.sent_queue:
                self.sent_queue.insert(0, "Inventory")
                send_message(self.socket, "Inventory")
            self.grace.wait(0.1)

            if self.grace.is_set():
                break
            
    
    def inv_management(self):
        while not self.grace.is_set():
            self.command("Inventory", "")
            # self.command("Look", "")
            # self.grace.wait(0.3)
            time.sleep(5)
            if self.grace.is_set():
                break
    
    def launch_loop(self):
        t_send = threading.Thread(target=self.send_management, args=())
        t_receive = threading.Thread(target=self.receive_management, args=())
        t_look = threading.Thread(target=self.look_management, args=())
        # t_inv = threading.Thread(target=self.inv_management, args=())

        t_receive.start()
        t_send.start()
        t_look.start()
        # t_inv.start()
        
        # active = threading.active_count()
        # print("THREADS ACTIVE: ", active)
        # time.sleep(5)
        try:
            self.lvl2()
        # try:
        #     self.incantate()
        #     # self.command("Take", "linemate")
        #     # self.command("Look", "")
        #     # self.command("Forward","")
        #     # time.sleep(5)
            
        except KeyboardInterrupt:
            print("Interrupted by user. Stopping threads...")
        
        # t_inv.join()
        # while not self.grace.is_set():
        self.stop()
        self.stop()
        self.stop()
        self.stop()
        t_look.join()
        t_send.join()
        t_receive.join()
    
    def lvl2(self):
        # self.command("Look", "")
        while not self.look:
            self.command("Look", "")
        self.get_object("linemate", 1)
        with self.lock:
            self.queue = []
  
        self.incantate()
        print("_________EXIT")
        return


