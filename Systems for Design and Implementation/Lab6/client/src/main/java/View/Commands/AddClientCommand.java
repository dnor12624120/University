package View.Commands;

import Domain.Entities.Client;
import Domain.Validators.CommunicationException;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.ClientService;

public class AddClientCommand extends MenuCommand
{
    private final ClientService clientService;

    public AddClientCommand(String description, String index, ClientService clientService)
    {
        super(description, index);
        this.clientService = clientService;
    }

    @Override
    public void execute()
    {
        int id = Utility.Utility.readNextIntFromConsole("Enter client ID.");
        String name = Utility.Utility.readNextLineFromConsole("Enter client name.");
        int age = Utility.Utility.readNextIntFromConsole("Enter client age.");
        try
        {
            Client client = new Client(name, age);
            client.setID(id);
            clientService.addClient(client);
        }
        catch (RepositoryException | ValidatorException | CommunicationException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
