package View.Commands;

import Domain.Validators.ValidatorException;
import Service.ClientService;

import java.sql.SQLException;

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
        catch (ValidatorException | IllegalAccessException | SQLException | NoSuchFieldException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
