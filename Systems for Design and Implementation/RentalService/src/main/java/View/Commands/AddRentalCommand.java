package View;

import Domain.Rental;
import Domain.Validators.ValidatorException;
import Service.RentalService;
import Utility.Utility;
import javafx.util.Pair;

import java.util.Scanner;

public class AddRentalCommand extends MenuCommand
{
    private RentalService rentalService;
    private Scanner inputStream;

    public AddRentalCommand(String description, String index, RentalService rentalService)
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
            Rental rental = new Rental();
            rental.setID(new Pair<>(clientID, rentedMovieID));
            rentalService.addRental(rental);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}