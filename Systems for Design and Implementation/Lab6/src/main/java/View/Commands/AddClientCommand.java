package View.Commands;

import Domain.Entities.Client;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.ClientService;
import Utility.Utility;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.Scanner;

public class AddClientCommand extends MenuCommand
{
    private ClientService clientService;

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
        catch (TransformerException | RepositoryException | SAXException | ParserConfigurationException | SQLException | ValidatorException | IOException exception)
        {
            System.out.println(exception.getMessage());
        } catch (IllegalAccessException | NoSuchFieldException e) {
            e.printStackTrace();
        }
    }
}
