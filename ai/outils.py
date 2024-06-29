#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

# Send a given string followed by a newline to the server.
def send_message(sock, message):
    message_with_newline = message + '\n'
    if sock:
        sock.sendall(message_with_newline.encode())
        print(f'[->]    Sent message: {message}')
    else:
        print("Error with socket")


# Receive a response from the server and throw an error if the response is 'ko\n'.
def receive_response(sock):
    response = sock.recv(1024).decode().strip()
    return response
