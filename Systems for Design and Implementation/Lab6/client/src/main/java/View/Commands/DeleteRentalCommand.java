package View.Commands;

import Utility.Utility;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.RentalService;

public class DeleteRentalCommand extends MenuCommand
{
    private final RentalService rentalService;

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
        catch (ValidatorException | RepositoryException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
