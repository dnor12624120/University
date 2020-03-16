package View;

import Domain.Validators.ValidatorException;
import Service.MovieService;

public class ViewAllMoviesCommand extends MenuCommand
{
    private MovieService movieService;

    public ViewAllMoviesCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        try
        {
            movieService.getAllMovies().forEach(System.out::println);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
