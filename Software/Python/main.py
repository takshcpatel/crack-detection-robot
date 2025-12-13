from crackDetector import detect_edges
import pygame
import socket
import struct
import cv2
import numpy as np
import time

pygame.joystick.init()
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
my_joystick = joysticks[0]
HOST = "192.168.4.1"
PORT = 3333

def get_and_show_feed():
    time.sleep(0.05)
    s.sendall(b"sframe\n") # SEND GET FRAME CMD

    # read the 4byte data
    size_bytes = s.recv(4)
    img_size = struct.unpack("<I", size_bytes)[0]
    print("image size: ", img_size)

    # get img bytes
    img_data = b""
    while len(img_data) < img_size:
        chunk = s.recv(4096)
        img_data += chunk

    np_arr = np.frombuffer(img_data, dtype=np.uint8)
    uncompressed = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
    final = detect_edges(uncompressed)

    return uncompressed

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

pygame.init()

try:
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                break

            if event.type == pygame.JOYBUTTONDOWN:
                if pygame.joystick.Joystick(0).get_button(3):
                    print("getting image...")
                    img = get_and_show_feed()
                    processed = detect_edges(img)
                    cv2.imshow("cam feed", img)
                    cv2.imshow("processed feed", processed)    
            
                else:
                    cv2.destroyAllWindows()

                if pygame.joystick.Joystick(0).get_button(6):
                    final_cmd = f"{"f_on"}\n".encode()
                    s.sendall(final_cmd)
                
                if pygame.joystick.Joystick(0).get_button(7):
                    final_cmd = f"{"f_off"}\n".encode()
                    s.sendall(final_cmd)

                if pygame.joystick.Joystick(0).get_button(1):
                    final_cmd = f"{"right"}\n".encode()
                    s.sendall(final_cmd)
                else:
                    final_cmd = f"{"stop"}\n".encode()
                    s.sendall(final_cmd)
                    
                if pygame.joystick.Joystick(0).get_button(2):
                    final_cmd = f"{"left"}\n".encode()
                    s.sendall(final_cmd)
                else:
                    final_cmd = f"{"stop"}\n".encode()
                    s.sendall(final_cmd)

                if pygame.joystick.Joystick(0).get_button(4):
                    final_cmd = f"{"bck"}\n".encode()
                    s.sendall(final_cmd)
                else:
                    final_cmd = f"{"stop"}\n".encode()
                    s.sendall(final_cmd)

                if pygame.joystick.Joystick(0).get_button(5):
                    final_cmd = f"{"fwd"}\n".encode()
                    s.sendall(final_cmd)

                if pygame.joystick.Joystick(0).get_button(8):
                    final_cmd = f"{"stop"}\n".encode()
                    s.sendall(final_cmd)
                else:
                    final_cmd = f"{"stop"}\n".encode()
                    s.sendall(final_cmd)

except KeyboardInterrupt:
    s.close()

finally:
    s.close()
