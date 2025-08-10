import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class Main {
    public static void print(String text) {  // I don't like typing System.out.println over and over
    System.out.println(text);
  }


  public static void main(String[] args) {
    System.out.println("Hello, World!");
    TaskManager tm = new TaskManager();
    tm.addTask("Walk around");
    tm.listTasks();
    tm.completeTask(0);
    tm.listTasks();


    boolean isRunning = true;
    Scanner scanner = new Scanner(System.in);

    while(isRunning) {

      print("Task Manager");
      print("1. Add Task");
      print("2. View Tasks");
      print("3. Complete Task");
      print("4. Quit");

      System.out.print("Make your choice: ");
      String line = scanner.nextLine().trim();

      int choice;
      try {
        choice = Integer.parseInt(line);
      } catch (NumberFormatException e) {
        print("Enter a number 1-3.");
        continue;
      }

      switch (choice) {
        case 1 -> {
        print("Whats the new task?: ");
        String taskName = scanner.nextLine().trim();
        if (taskName.isEmpty()) {
          print("Task name cant't be empty.");
          continue;
        }
        tm.addTask(taskName);
        tm.listTasks();
        }
        case 2 -> {
          tm.listTasks();
        }
        case 3 -> {
          try {
            int index = Integer.parseInt(scanner.nextLine().trim());
            if (index < 1 || index > tm.amount()) {
              print("Bad");
            } else {
              tm.completeTask(index - 1);
              tm.listTasks();
          }
          } catch (NumberFormatException e) {
              print("Enter a number between 1 and " + tm.amount());
          }

        }
        case 4 -> {
          isRunning = false;
        }
        default -> {
          print("Make a better choice");
        }
      }
    }
    scanner.close();

  }
}



class Task {
  private String name;
  private boolean completed;

  public Task(String name) {
    this.name = name;
    this.completed = false;
  }

  public String getName() {
    return name;
  }
  public boolean isCompleted() {
    return completed;
  }
  public void markCompleted() {
    this.completed = true;
  }

  public String toString() {
    return (completed ? "[X] " : "[ ] ") + name;
  }
}

class TaskManager {
  private List<Task> tasks = new ArrayList<>();

  public void addTask(String name) {
    tasks.add(new Task(name));
  }

  public void listTasks() {
    if (tasks.isEmpty()) {
      System.out.println("No tasks yet.");
      return;
    }
    for (int i = 0; i < tasks.size(); i++) {
      System.out.println((i + 1) + ". " + tasks.get(i));
    }
  }

  public int amount() {
    return tasks.size();
  }

  public void completeTask(int index) {
    if ( index >= 0 && index < tasks.size()) {
      tasks.get(index).markCompleted();
    } else {
      System.out.println("No task in that index.");
    }
  }
}
