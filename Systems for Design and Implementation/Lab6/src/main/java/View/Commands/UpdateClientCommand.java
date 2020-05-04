package View.Commands;

import Domain.Entities.Client;
import Domain.Validators.ValidatorException;
import Service.ClientService;
import Utility.Utility;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;

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
            clientService.updateClient(client);
        }
        catch (ValidatorException | IOException | TransformerException | SQLException | ParserConfigurationException | SAXException exception)
        {
            System.out.println(exception.getMessage());
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        }
    }
}
