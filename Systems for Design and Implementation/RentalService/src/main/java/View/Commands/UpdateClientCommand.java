package View;

import Domain.Client;
import Domain.Validators.ValidatorException;
import Service.ClientService;
import Utility.Utility;

public class UpdateClientCommand extends MenuCommand
{
    private ClientService clientService;

    public UpdateClientCommand(String description, String index, ClientService clientService)
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
