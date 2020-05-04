package View.Commands;

import Utility.Utility;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.MovieService;

public class DeleteMovieCommand extends MenuCommand
{
    private final MovieService movieService;

    public DeleteMovieCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        int id = Utility.readNextIntFromConsole("Enter movie ID.");
        try
        {
            movieService.deleteMovie(id);
        }
        catch (ValidatorException | RepositoryException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
