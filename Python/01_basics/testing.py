from datetime import datetime

now = datetime.now();

testDictionary = {
    "name": "Jacob Smith",
    "age": 19,
    "athletic": False
}

print(testDictionary)

if (testDictionary["athletic"]):
    print("He is athletic")
else:
    print("He is not athletic")


taskList = []

def addTask(task):
    newTask = {
        "name": task,
        "completed": False,
        "lastEdit": now.time(),
        "createdAt": now.time()
    }
    taskList.append(newTask)


addTask("Play Fortnite")
addTask("Play Minecraft")
addTask("Code Something")
addTask("Test a game")

for task in taskList:
    print(task["name"])
