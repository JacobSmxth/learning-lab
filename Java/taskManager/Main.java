import java.util.ArrayList;


public class Main {
  public static void main(String[] args) {
    System.out.println("Hello, World!");
    TaskManager tm = new TaskManager();
    tm.addTask("Walk around");
    tm.listTasks();
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
  private ArrayList<Task> tasks = new ArrayList<>();

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
}
