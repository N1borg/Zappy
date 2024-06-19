#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import socket
import sys
import argparse
import re
import time

"""
## AI

1. Infrastructure commandes
2. Infrastructure multi-commandes (queue)
3. gérer réponses serveur

"""

# inventaire partage
# team name

resources = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

cmd_noarg = ["Forward", "Right", "Left", "Look"]

class AI:
    def __init__(self, teamname, socket, c_nbr, map_x, map_y):
        # Initial arguments
        self.socket = socket
        self.team = teamname
        self.connect_nbr = c_nbr
        self.map_x = map_x
        self.map_y = map_y

        self.level = 1
        self.inventory = {"food": 0,"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.look = []

        self.command_queue = []
        self.sent_queue = []

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

    def append_command(self, cmd, arg):
        if cmd == "Broadcast" or cmd == "Take" or cmd == "Set":
            self.command_queue.insert(0, cmd + " " + arg)
        else:
            self.command_queue.insert(0, cmd)

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
        else:
            print("Command queue: no more commands left")
            time.sleep(5)

    def receive_command(self):
        response = receive_response(self.socket)
        if response == "dead":
            # TODO: implement death mechanism
            return
        print(f"        Received response   [<-]: {response}")
        cmd = self.sent_queue.pop()
        cmd_name, cmd_arg = "", ""
        if len(cmd.split(" ")) == 2:
            cmd_name, cmd_arg = cmd.split(" ")
            # print(f"Received a: {cmd_name} {cmd_arg}")
        else:
            cmd_name = cmd
            # print(f"Received a: {cmd_name}")

        if cmd_name == "Forward" or cmd_name == "Right" or cmd_name == "Left" or cmd_name == "Fork" or cmd_name == "Broadcast":
            if response == "ok":
                print(cmd_name + ": OK")
            else:
                print(f"Received an unexpected response from {cmd_name} command: ", response)

        elif cmd_name == "Look":
            if response[0] != '[':
                print(f"Received an unexpected response from {cmd_name} command: ", response)
            self.look = self.parse_look(response)
            # print(self.look)

        elif cmd_name == "Inventory":
            if response[0] != '[':
                print(f"Received an unexpected response from {cmd_name} command: ", response)
            self.inventory = self.parse_inventory(response)
            # print(self.inventory)

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
                print(response)

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
        while len(self.sent_queue) < 2:
            self.send_command()

    def launch_loop(self):
        i = 0
        while True:
            if i == 0:
                self.append_command("Look", "")
                self.append_command("Inventory", "")
                self.append_command("Broadcast", "A1")
                self.append_command("Look", "")
                self.append_command("Inventory", "")
                self.append_command("Broadcast", "AA2")
                self.append_command("Look", "")
                self.append_command("Inventory", "")
                self.append_command("Broadcast", "AAA3")
                i += 1
            self.manage_queue()
            self.receive_command()
            self.manage_queue()
            print(f"[SENT] Queue: {self.sent_queue}")
            print(f"[CMD] Queue: {self.command_queue}")



def parse_arguments():
    """
    A function which takes the arguments from the command line.

    Returns:
        A namespace argparse from which information can be easily taken.
    """
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument('-p', '--port', type=int, required=True)
    parser.add_argument('-n', '--name', type=str, required=True)
    parser.add_argument('-h', '--host', type=str, default='localhost')
    return parser.parse_args()


# Send a given string followed by a newline to the server.
def send_message(sock, message):
    message_with_newline = message + '\n'
    sock.sendall(message_with_newline.encode())
    print(f'[->]    Sent message: {message}')


# Receive a response from the server and throw an error if the response is 'ko\n'.
def receive_response(sock):
    response = sock.recv(1024).decode().strip()
    if response == "ko":
        raise ValueError("Received 'ko' from server")
    return response

def parse_slots_and_map(str):
    parts = str.split('\n')

    numbers = []
    for part in parts:
        numbers.extend(part.split())

    integers = [int(num) for num in numbers]
    return integers

def main():
    args = parse_arguments()

    host = args.host
    port = args.port
    name = args.name

    if name == "GRAPHIC":
        print("Team name not available.")
        exit(84)

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            print(f'Connected to {host}:{port}')

            # Wait for "WELCOME\n" from the server
            welcome_message = receive_response(s)
            if welcome_message != "WELCOME":
                print(f'Unexpected message from server: {welcome_message}')
                return

            print(f'Received: {welcome_message}')

            # Send the name to the server
            send_message(s, name)

            already_parced = False
            # Receive the number of available slots
            try:
                response = receive_response(s)
                slots = int(response)
                print(f'Received slots: {slots}')
            except ValueError:
                print(f'Unexpected response for slots from server: {response}')
                parced = parse_slots_and_map(response)
                slots = parced[0]
                x, y = parced[1], parced[2]
                already_parced = True

            # Receive the position (X, Y)
            if not already_parced:
                response = receive_response(s)
                parts = response.split()
                if len(parts) == 2:
                    x, y = parts
                    print(f'Received map size: ({x}, {y})')
                else:
                    print(f'Unexpected response for map size from server: {response}')

            ai = AI(name, s, slots, x, y)
            ai.launch_loop()

    except Exception as e:
        print(f'{host}:{port} - {e}')



if __name__ == "__main__":
    if len(sys.argv) == 1 or sys.argv[1] == '-help':
        print(f"USAGE: {sys.argv[0]} -p port -n name -h machine")
    else:
        main()
