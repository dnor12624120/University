package View.Commands;

import Domain.Validators.ValidatorException;
import Service.MovieService;
import java.util.concurrent.ExecutionException;

public class ViewAllMoviesCommand extends MenuCommand
{
    private final MovieService movieService;

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
            movieService.getAllMovies().get().forEach(System.out::println);
        }
        catch (ValidatorException | InterruptedException | ExecutionException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
