# This is my test file to test out new things i'm learning and to show my thought process
#

import json

# First Object
#
class testClass:
    x = 5

firstObj = testClass()


# print(firstObj)



# Class with dunders
#
class Person:
    all_people = []
    # __init__ is necessary for creating new real objects like in my task manager
    def __init__(self, name, age):
        self.name = name
        self.age = age
        Person.all_people.append(self)

    def __str__(self):
        return f"{self.name}({self.age})"

    def __repr__(self):
        return f"Person({self.name!r}, {self.age!r})"

    def destroy(self):
        Person.all_people.remove(self)
        del self

    def greet(self):
        print(f"Hello there {self.name!s}!")

    def to_diction(self):
        return {
            "name": self.name,
            "age": self.age
        }
def view():
    for p in Person.all_people:
        print(p)

def save():
    data = []
    for person in Person.all_people:
        data.append(person.to_diction())
    with open("test.json", "w") as f:
        json.dump({"data": data}, f)

def load():
    with open("test.json", "r") as f:
        data = json.load(f)
        for d in data["data"]:
            # print(d)
            person = Person(d["name"], d["age"])


           


p1 = Person("Jacob", 19)

print(p1.name)
print(p1.age)
print("Changed age to 22.")
p1.age = 22
print(p1)

print("Delete Object")

p1.destroy()

try:
    print(p1)
except:
    print("No Object Anymore")

load()

view()
