package View;

import Domain.Validators.ValidatorException;
import Service.ClientService;
import Utility.Utility;

public class DeleteClientCommand extends MenuCommand
{
    private ClientService clientService;

    public DeleteClientCommand(String description, String index, ClientService clientService)
    {
        super(description, index);
        this.clientService = clientService;
    }

    @Override
    public void execute()
    {
        int id = Utility.readNextIntFromConsole("Enter client ID.");
        try
        {
            clientService.deleteClient(id);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
