import java.io.*;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
public class RandomName {
  static ArrayList<String> name_list;
  static String Generate() {
    if (name_list == null) {
      try {
        fillNameList();
      }
      catch(FileNotFoundException e) {
        System.out.println("File could not be found!");
        return "Aaron";
      }
    }
    Random r = new Random();
    return name_list.get(r.nextInt(name_list.size()));
  }
  static void fillNameList() throws FileNotFoundException {
    File names = new File("names.txt");
    Scanner in = new Scanner(names);
    while (in.hasNextLine()) {
      String line = in.nextLine();
      String[] splitLine = line.split("#");
      String name = splitLine[0].replaceAll(" ", "");
      if (!name.equals("")) {
        name_list.add(name);
      }
    }
    in.close();
  }
}