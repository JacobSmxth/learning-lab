taskList = []

def addTask(task):
    newTask = {
        "name": task,
        "completed": False 
    }
    taskList.append(newTask)

def viewTasks():

    print("------------------------------------------")
    print(f'Your tasks [{len(taskList)}]:')
    for task in taskList:
        print(f'{task["name"]}: {"Completed" if task["completed"] else "Incompleted"}')
        print("      ")

def delTask(bye):
    potentialChoices = [];
    index = 0
    num = 1
    for task in taskList:
        if bye.lower() in task["name"].lower():
            potentialChoices.append({
                "choice": num,
                "name": task["name"],
                "index": index
            })
            num += 1
        index += 1
    if len(potentialChoices) > 0:
        if len(potentialChoices) == 1:
            validInput = False
            while (not validInput):
                userChoice = input(f'Do you want to remove "{potentialChoices[0]["name"]}"?: ')
                if (userChoice.isnumeric()):
                    validInput = False
                elif userChoice.startswith('y') or userChoice.startswith('Y'):
                    taskList.pop(potentialChoices[0]["index"])
                    validInput = True
                else:
                    validInput = True
        elif len(potentialChoices) > 1:
            validInput = False
            for choice in potentialChoices:
                print(f'{choice["choice"]}. {choice["name"]}')
            print(f'{len(potentialChoices) + 1}. Forget about it')

            while (not validInput):
                userChoice = input('Did you mean any of these? If so select the corresponding number: ')
                if (not userChoice.isnumeric()):
                    validInput = False
                else:
                    userChoice = int(userChoice)
                    if (userChoice == len(potentialChoices) + 1):
                        validInput = True
                        print("No task removed")
                        break
                    for choice in potentialChoices:
                        if (choice["choice"] == userChoice):
                            taskList.pop(choice["choice"]["index"])
                            print("Removed it.")
                            validInput = True
    else:
        print(f'No task contains "{bye}".')


def completeTask(cTask):
    potentialChoices = [];
    index = 0
    num = 1
    for task in taskList:
        if cTask.lower() in task["name"].lower() and task["completed"] != True:
            potentialChoices.append({
                "choice": num,
                "name": task["name"],
                "index": index
            })
            num += 1
        index += 1
    if len(potentialChoices) > 0:
        if len(potentialChoices) == 1:
            validInput = False
            while (not validInput):
                userChoice = input(f'Do you want to complete "{potentialChoices[0]["name"]}"?: ')
                if (userChoice.isnumeric()):
                    validInput = False
                elif userChoice.startswith('y') or userChoice.startswith('Y'):
                    taskList[potentialChoices[0]["index"]]["completed"] = True
                    validInput = True
                else:
                    validInput = True
        elif len(potentialChoices) > 1:
            validInput = False
            for choice in potentialChoices:
                print(f'{choice["choice"]}. {choice["name"]}')
            print(f'{len(potentialChoices) + 1}. Forget about it')

            while (not validInput):
                userChoice = input('Did you mean any of these? If so select the corresponding number: ')
                if (not userChoice.isnumeric()):
                    validInput = False
                else:
                    userChoice = int(userChoice)
                    if (userChoice == len(potentialChoices) + 1):
                        validInput = True
                        print("No task completed")
                        break
                    for choice in potentialChoices:
                        if (choice["choice"] == userChoice):
                            taskList[potentialChoices[userChoice - 1]["index"]]["completed"] = True
                            print("Completed it.")
                            validInput = True
    else:
        print(f'No task contains "{cTask}".')




print("Welcome to the To-Do App")

isRunning = True
while (isRunning):
    tasksPresent = False
    print("------------------------------------------")
    print("1. Add Task")
    if len(taskList) > 0:
        tasksPresent = True
        print("2. View Tasks")
        print("3. Delete Task")
        print("4. Complete Task")
        print("5. Exit Program")
    else:
        print("2. Exit Program")

    userChoice = input("Make a choice: ")
    if (userChoice.isnumeric()):
        userChoice = int(userChoice)
        match (userChoice):
            case 1:
                newTask = input("What task would you like to add? \n> ")
                addTask(newTask)
            case 2:
                if (tasksPresent):
                    viewTasks()
                else:
                    isRunning = False
            case 3:
                if (tasksPresent):
                    theTask = input("What task would you like to delete? \n> ")
                    delTask(theTask)
                else:
                    print("Please pick a number that is present.")
            case 4:
                if (tasksPresent):
                    theTask = input("What task would you like to complete? \n> ")
                    completeTask(theTask)
                else:
                    print("Please pick a number that is present.")
            case 5:
                if (tasksPresent):
                    isRunning = False
                else:
                    print("Please pick a number that is present.")






