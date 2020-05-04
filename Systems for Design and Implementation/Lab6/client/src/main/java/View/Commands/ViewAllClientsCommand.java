package View.Commands;

import Domain.Validators.ValidatorException;
import Service.ClientService;
import java.util.concurrent.ExecutionException;

public class ViewAllClientsCommand extends MenuCommand
{
    private final ClientService clientService;

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

            clientService.getAllClients().get().forEach(System.out::println);
        }
        catch (ValidatorException | InterruptedException | ExecutionException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
