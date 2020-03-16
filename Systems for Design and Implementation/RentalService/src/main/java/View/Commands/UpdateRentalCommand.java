package View;

import Domain.Rental;
import Domain.Validators.ValidatorException;
import Service.RentalService;
import Utility.Utility;
import javafx.util.Pair;

public class UpdateRentalCommand extends MenuCommand
{
    private RentalService rentalService;

    public UpdateRentalCommand(String description, String index, RentalService rentalService)
    {
        super(description, index);
        this.rentalService = rentalService;
    }

    @Override
    public void execute()
    {
        int clientID = Utility.readNextIntFromConsole("Enter client ID.");
        int movieID = Utility.readNextIntFromConsole("Enter movie ID.");

        try
        {
            Rental rental = new Rental();
            rental.setID(new Pair<>(clientID, movieID));
            rentalService.updateRental(rental);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
