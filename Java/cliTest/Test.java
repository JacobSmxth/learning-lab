public class Test {
  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("No args provided");
      System.out.println("Usage: java Test <name> <occupation>");
      return;
    }

    String name = args[0];
    String occupation = args[1];

    System.out.println("Hello I am " + name + ", and I am a " + occupation);
  }
}
