#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import socket
import sys
import argparse

def parse_arguments():
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

    host = args.host
    port = args.port
    name = args.name

    if name == "GRAPHIC":
        print("Team name not available.")
        exit()

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
            response = receive_response(s)
            try:
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
