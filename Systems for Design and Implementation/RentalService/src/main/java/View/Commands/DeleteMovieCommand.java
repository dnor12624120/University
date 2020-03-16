package View;

import Domain.Validators.ValidatorException;
import Service.MovieService;
import Utility.Utility;

public class DeleteMovieCommand extends MenuCommand
{
    private MovieService movieService;

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
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
