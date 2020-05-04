package View.Commands;

import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.RentalService;
import Utility.Utility;
import javafx.util.Pair;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;

public class DeleteRentalCommand extends MenuCommand
{
    private RentalService rentalService;

    public DeleteRentalCommand(String description, String index, RentalService rentalService)
    {
        super(description, index);
        this.rentalService = rentalService;
    }

    @Override
    public void execute()
    {
        int id = Utility.readNextIntFromConsole("Enter client ID.");
        try
        {
            rentalService.deleteRental(id);
        }
        catch (ValidatorException | RepositoryException | IOException | ParserConfigurationException | TransformerException | SAXException | SQLException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
