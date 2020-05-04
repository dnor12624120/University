package View.Commands;

import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.ClientService;
import Utility.Utility;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;

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
        catch (ValidatorException | RepositoryException | IOException | TransformerException | SAXException | ParserConfigurationException | SQLException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
