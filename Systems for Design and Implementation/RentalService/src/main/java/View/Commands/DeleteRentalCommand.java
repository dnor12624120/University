package View;

import Domain.Validators.ValidatorException;
import Service.RentalService;
import Utility.Utility;
import javafx.util.Pair;

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
        int clientID = Utility.readNextIntFromConsole("Enter client ID.");
        int rentedMovieID = Utility.readNextIntFromConsole("Enter rented movie ID.");
        try
        {
            rentalService.deleteRental(new Pair<>(clientID, rentedMovieID));
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
