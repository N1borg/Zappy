#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import socket
import sys
import argparse
import re

"""
## AI

1. Infrastructure commandes
2. Infrastructure multi-commandes (queue)
3. gérer réponses serveur

"""

# 10 requests max

resources = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

cmd_noarg = ["Forward", "Right", "Left", "Look"]

class AI:
    def __init__(self, teamname):
        self.level = 1
        self.team = teamname
        self.inventory = {"food": 0,"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.command_queue = []
        self.connect_nbr = 0
        self.look = []

    def append_cmd(self, cmd, arg):
        if len(self.command_queue) == 10:
            print("Queue is full, wait for a couple of instants...")
        else:
            if cmd == "Broadcast" or cmd == "Take" or cmd == "Set":
                self.command_queue.insert(0, [cmd, arg])
            else:
                self.command_queue.insert(0, cmd)

    def parse_look(self, look_str):
        tile_strings = look_str.split(', ')

        result = []
        for tile in tile_strings:
            pairs = re.findall(r'(\w+)\s(\d+)', tile)
            tile_dict = {key: int(value) for key, value in pairs}
            result.append(tile_dict)
        return result

    def parse_inventory(self, inv_str):
        pairs = re.findall(r'(\w+)\s(\d+)', inv_str)

        result_dict = {key: int(value) for key, value in pairs}
        return result_dict

    def manage_queue(self):
        cmd_arr = self.command_queue.pop()
        cmd = cmd_arr[0]

        send_message(cmd if len(cmd_arr) == 1 else cmd + cmd_arr[1])
        response = receive_response()

        if response == "dead":
            # TODO: implement death mechanism
            return
        if cmd == "Forward" or cmd == "Right" or cmd == "Left" or cmd == "Fork" or cmd == "Broadcast":
            if response == "ok":
                print(cmd + ": OK")
            else:
                print(f"Received an unexpected response from {cmd} command: ", response)


        elif cmd == "Look":
            if response[0] != '[':
                print(f"Received an unexpected response from {cmd} command: ", response)
            self.look = self.parse_look(response)

        elif cmd == "Inventory":
            if response[0] != '[':
                print(f"Received an unexpected response from {cmd} command: ", response)
            self.inventory = self.parse_inventory(response)

        elif cmd == "Connect_nbr":
            try:
                self.connect_nbr = int(response)
            except ValueError:
                print(f"Received an unexpected response from {cmd} command: ", response)
                self.connect_nbr = 0

        elif cmd == "Eject":
            if response == "ko":
                print("Failed to eject")
            elif response == "ok":
                print("Eject successful")

        elif cmd == "incantation":
            if response == "ko":
                print("Incantation failed")
            else:
                print(response)

        elif cmd == "Take":
            if response == "ok":
                self.inventory[cmd_arr[1]] += 1
            elif response == "ko":
                print(f"Couldn't take {cmd_arr[1]}")

        elif cmd == "Set":
            if response == "ok":
                self.inventory[cmd_arr[1]] -= 1
            elif response == "ko":
                print(f"Couldn't set {cmd_arr[1]}")


    # def launch_loop(self):
    #     # response = receive_response()
    #     while response != "dead":
    #         response = receive_response()



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
    print(f'Sent message: {message}')


# Receive a response from the server and throw an error if the response is 'ko\n'.
def receive_response(sock):
    response = sock.recv(1024).decode().strip()
    if response == "ko":
        raise ValueError("Received 'ko' from server")
    return response


def main():
    args = parse_arguments()
    print(type(args))

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

            # Receive the number of available slots
            try:
                response = receive_response(s)
                slots = int(response)
                print(f'Received slots: {slots}')
            except ValueError:
                print(f'Unexpected response for slots from server: {response}')
                return

            # Receive the position (X, Y)
            response = receive_response(s)
            parts = response.split()
            if len(parts) == 2:
                x, y = parts
                print(f'Received position: ({x}, {y})')
            else:
                print(f'Unexpected response for position from server: {response}')

    except Exception as e:
        print(f'{host}:{port} - {e}')



if __name__ == "__main__":
    if len(sys.argv) == 1 or sys.argv[1] == '-help':
        print(f"USAGE: {sys.argv[0]} -p port -n name -h machine")
    else:
        main()
