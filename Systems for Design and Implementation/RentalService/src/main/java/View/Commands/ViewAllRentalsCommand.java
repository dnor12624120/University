package View;

import Domain.Validators.ValidatorException;
import Service.RentalService;

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
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
