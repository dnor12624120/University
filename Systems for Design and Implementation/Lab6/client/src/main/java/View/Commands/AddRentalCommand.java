package View.Commands;

import Domain.Entities.Rental;
import Domain.Validators.ValidatorException;
import Service.RentalService;
import Utility.Utility;
import java.util.Scanner;

public class AddRentalCommand extends MenuCommand
{
    private final RentalService rentalService;

    public AddRentalCommand(String description, String index, RentalService rentalService)
    {
        super(description, index);
        this.rentalService = rentalService;
    }

    @Override
    public void execute()
    {
        int id = Utility.readNextIntFromConsole("Enter rental ID.");
        int clientID = Utility.readNextIntFromConsole("Enter client ID.");
        int rentedMovieID = Utility.readNextIntFromConsole("Enter rented movie ID.");
        try
        {
            Rental rental = new Rental(clientID, rentedMovieID);
            rental.setID(id);
            rentalService.addRental(rental);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
