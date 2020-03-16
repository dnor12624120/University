package View;

import View.Commands.MenuCommand;

import java.util.Map;
import java.util.Scanner;

public class ConsoleMenu
{
    private Map<String, MenuCommand> commands;
    private boolean running;
    private Scanner inputStream;


    public ConsoleMenu(Map<String, MenuCommand> commands, boolean running)
    {
        this.commands = commands;
        this.running = running;
        this.inputStream = new Scanner(System.in);
    }

    private void printMenu()
    {
        commands.forEach((key, value) -> System.out.println(key + ". " + value.getDescription()));
    }

    public void run()
    {
        running = true;
        while(running)
        {
            printMenu();
            System.out.print(">");
            String userInput = inputStream.nextLine();
            if(commands.get(userInput) == null)
            {
                System.out.println("Invalid command.");
            }
            else
            {
                commands.get(userInput).execute();
            }
        }
    }
}
