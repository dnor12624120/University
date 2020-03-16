package View;

import com.company.Domain.Client;
import com.company.Domain.Validators.ValidatorException;
import com.company.Service.ClientService;
import com.company.Utility.Utility;

import java.util.Scanner;

public class AddClientCommand extends MenuCommand
{
    private ClientService clientService;
    private Scanner inputStream;

    public AddClientCommand(String description, String index, ClientService clientService)
    {
        super(description, index);
        this.clientService = clientService;
    }

    @Override
    public void execute()
    {
        int id = Utility.readNextIntFromConsole("Enter client ID.");
        String name = Utility.readNextLineFromConsole("Enter client name.");
        int age = Utility.readNextIntFromConsole("Enter client age.");
        try
        {
            Client client = new Client(name, age);
            client.setID(id);
            clientService.addClient(client);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
