package View.Commands;

import Domain.Validators.ValidatorException;
import Service.RentalService;

import java.sql.SQLException;

public class ViewAllRentalsCommand extends MenuCommand
{
    private RentalService rentalService;

    public ViewAllRentalsCommand(String description, String index, RentalService rentalService)
    {
        super(description, index);
        this.rentalService = rentalService;
    }

    @Override
    public void execute()
    {
        try
        {
            rentalService.getAllRentals().forEach(System.out::println);
        }
        catch (IllegalAccessException | SQLException | NoSuchFieldException | ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
