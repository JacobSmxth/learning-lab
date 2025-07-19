from todo import Task,  TaskManager

def display_menu():
    zeroTask = True
    print("========Task Manager========")
    if tm.taskCount() < 1:
        print("1. Add Task")
        print("2. Exit Program")
    else:
        zeroTask = False
        print("1. Add Task")
        print("2. Delete Task")
        print("3. Complete Task")
        print("4. View Tasks")
        print("5. Clear Tasks")
        print("6. Exit Program")
    print("============================")

    validInput = False
    while(not validInput):
        userChoice = input("Make a choice\n> ")
        if userChoice[0].isnumeric():
            userChoice = int(userChoice[0])
        else:
            print("Numbers only please")
            continue


        choiceRange = 2 if zeroTask else 6
        if (0 <= userChoice <= choiceRange):
            validInput = True
        else:
            print(f"Please select a number within the range of 1-{choiceRange}")
    return {
        "choice": userChoice,
        "zeroType": zeroTask
    }


def check_menu_choice(choice):
    mType = choice["zeroType"]
    choice = choice["choice"]

    if mType:
        if (choice == 2):
            exit(0)
        else:
            add()
    else:
        match(choice):
            case 1:
                add()
            case 2:
                delete()
            case 3:
                print("To be implemented")
            case 4:
                view()
            case 5:
                print("To be implemented")
            case 6:
                exit(0)

def add():
    taskName = input("What would you like to add?\n> ")
    taskDesc = input("Describe it.\n> ")
    tm.addTask(taskName, taskDesc)

def find(type: str):
    question = 'empty'
    if type == 'd':
        question = "What would you like to delete?\n> "
    elif type == 't':
        question = "What would you like to complete?\n> "
    else:
        print("Invalid Type")
        return
    return tm.findTasks(input(question))

def delete():
    possible = find("d")
    if possible:
        if len(possible) == 1:
            validInput = False
            while(not validInput):
                userChoice = input(f"Are you sure you want to delete {possible[0]["name"]}?\n> ").lower()
                if (not userChoice[0].isnumeric() and userChoice.startswith('y')):
                    tm.deleteTask(possible[0]["index"])
                    validInput = True
                elif(not userChoice[0].isnumeric() and userChoice.startswith('n')):
                    validInput = True
                    print("Delete Cancelled")
                else:
                    print("Please enter a valid input (y/n)")


def view():
    print("Task List:")
    tm.viewTasks()


tm = TaskManager()
try: 
    tm.load()
    print(f"{tm.taskCount()} {"tasks" if tm.taskCount() > 1 else "task"} loaded.")
except FileNotFoundError:
    print("No tasks loaded.")

while(True):
    check_menu_choice(display_menu())




