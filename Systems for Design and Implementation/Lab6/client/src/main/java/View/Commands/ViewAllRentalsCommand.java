package View.Commands;

import Domain.Validators.ValidatorException;
import Service.RentalService;
import java.util.concurrent.ExecutionException;

public class ViewAllRentalsCommand extends MenuCommand
{
    private final RentalService rentalService;

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
            rentalService.getAllRentals().get().forEach(System.out::println);
        }
        catch (ValidatorException | InterruptedException | ExecutionException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
