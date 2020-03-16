package View;

import Domain.Validators.ValidatorException;
import Service.ClientService;

public class ViewAllClientsCommand extends MenuCommand
{
    private ClientService clientService;

    public ViewAllClientsCommand(String description, String index, ClientService clientService)
    {
        super(description, index);
        this.clientService = clientService;
    }

    @Override
    public void execute()
    {
        try
        {
            clientService.getAllClients().forEach(System.out::println);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
