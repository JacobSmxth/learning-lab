# Pomodoro Timer

import time
import math
import os


def displayTimer(length):
    try:
        for i in range(length*60, 0, -1):
            minutes = math.floor(i/60)
            seconds = i % 60
            print(f'\r{minutes:02}:{seconds:02}', end='', flush=True)
            time.sleep(1)
    except KeyboardInterrupt:
        print(" ")
        print("Session Cancelled.")
        os.system("paplay error.mp3")
        exit(0)


def askLength():
    validInput = False
    while (not validInput):    
        length = input("How long are you working? (minutes): ")
        if (not length.isnumeric()):
            print("Please enter a number.")
        else:
            length = int(length)
            validInput = True
    print(f'You picked a time of {length} minutes')
    
    workRounds = math.floor(length / 30)
    lastRound = length % 30
    
    print(f'Session will include {workRounds} Pomodoro(s) of 25/5 split.')
    if lastRound:
        print(f'Plus a final {lastRound}-minute round.')

    aPause = input("Press ENTER to begin...")

    return {
        "wr": workRounds,
        "last": lastRound
    }


def operationTimer(data):
    extraRound = False
    if (data["last"] > 0):
        extraRound = True 
    os.system("paplay start.mp3")
    print("Begin")

    for j in range(0, data["wr"]):
        print(f'---------- Round {j+1} | WORK -----------')
        displayTimer(25)
        os.system("paplay work.mp3")
        if (j != data["wr"] - 1):
            print(f'---------- Round {j+1} | BREAK -----------')
            displayTimer(5)
            os.system("paplay breakOver.mp3")
    if (extraRound):
        print(f'---------- FINAL ROUND [{data["last"]} minutes] ---------------')
        displayTimer(data["last"])

    print(" ")
    print("Session complete. Great Work!")
    os.system("paplay AllDone.mp3")

isRunning = True
while (isRunning):
    validInput = False
    while(not validInput):
        userChoice = input("Would you like to start a session? (y/n):")
        if (not userChoice.isnumeric() and (userChoice.lower().startswith('y'))):
            validInput = True
            operationTimer(askLength())
        elif (not userChoice.isnumeric() and (userChoice.lower().startswith('n'))):
            validInput = True
            isRunning = False
        else:
            validInput = False

