import pygame

pygame.joystick.init()
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
my_joysticks = joysticks[0]
pygame.init()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            break
        
        if event.type == pygame.JOYBUTTONDOWN:
            print(event)

        # if my_joysticks.get_button(0):
        #     # pass
        #     print("button held")
        # else:
        #     # pass
        #     print("button released")
        
    