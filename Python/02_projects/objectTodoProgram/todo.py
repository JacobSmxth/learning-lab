# USING OBJECTS (Classes) TO MAKE A TASK MANAGER

import time
import json

class Task:
    def __init__(self, name, desc, completed = False, created = None):
        self.name = name
        self.desc = desc
        self.completed = bool(completed)
        self.created = created or time.ctime()

    def to_dict(self):
        return {
            "name": self.name,
            "desc": self.desc,
            "completed": self.completed,
            "created": self.created
        }

    def __repr__(self):
        return f"Task({self.name!r}, {self.desc!r} : {self.completed!r})"

    def __str__(self):
        return f'[{self.created}] {self.name}: {self.desc} ({"Complete" if self.completed else "Incomplete"})'

class TaskManager:
    def __init__(self):
        self.tasks = []

    def taskCount(self):
        return len(self.tasks)

    def save(self):
        with open('data.json', 'w') as f:
            data = []
            for i in self.tasks:
                data.append(i.to_dict())
            json.dump({"data": data}, f)

    def load(self):
        with open('data.json', 'r') as f:
            data = json.load(f)
            for d in data["data"]:
                self.addTask(d["name"], d["desc"], d["completed"], d["created"])

    def addTask(self, name, desc, completed = None, created = None):
        self.tasks.append(Task(name, desc, completed, created))
        self.save()

    def viewTasks(self):
        for task in self.tasks:
            print(task)

    def clearTasks(self):
        self.tasks.clear()
        self.save()

    def findTasks(self, attempt):
        possible = []
        for index, task in enumerate(self.tasks):
            if attempt.lower() in task.name.lower():
                possible.append({
                    "name": task.name,
                    "index": index
                })
        return possible # Always return list 
       
    def deleteTask(self, index):
        if 0 <= index and index < len(self.tasks):
            del self.tasks[index]
            self.save()
        else:
            print("Invalid Index")

    def toggleCompletion(self, index):
        if 0 <= index and index < len(self.tasks):
            self.tasks[index].completed = not self.tasks[index].completed
            self.save()
        else:
            print("Invalid Index")



def main():
    tm = TaskManager()
    tm.load()
    tm.viewTasks()
if __name__ == "__main__": # Allows this to be imported without all the TaskManager functions running (FOR THE GUI EVENTUALLY)
    main()




