#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import socket
import sys
import argparse
import re
import time
import traceback

from ai import AI
from outils import receive_response
from outils import send_message

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

def parse_slots_and_map(str):
    parts = str.split('\n')

    numbers = []
    for part in parts:
        numbers.extend(part.split())

    integers = [int(num) for num in numbers]
    # print(str, integers)
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
            slots = -1
            x, y = -1, -1
            # Receive the number of available slots and map coordinates
            try:
                response = receive_response(s)
                if response == "ko":
                    exit(84)
                if response == "dead":
                    exit()
                slots = int(response)
                print(f'Received slots: {slots}')
            except ValueError:
                print(f'Unexpected response for slots from server: {response}')
                if response:
                    parced = parse_slots_and_map(response)
                    slots = parced[0]
                    x, y = parced[1], parced[2]
                    already_parced = True

            if not already_parced:
                response = receive_response(s)
                parts = response.split()
                if len(parts) == 2:
                    x, y = parts
                    print(f'Received map size: ({x}, {y})')
                else:
                    print(f'Unexpected response for map size from server: {response}')

            ai = AI(name, s, slots, int(x), int(y))
            ai.launch_loop()

    except Exception as e:
        print(f'{host}:{port} - {e}')
        print(traceback.format_exc())



if __name__ == "__main__":
    if len(sys.argv) == 1 or sys.argv[1] == '-help':
        print(f"USAGE: {sys.argv[0]} -p port -n name -h machine")
    else:
        main()
