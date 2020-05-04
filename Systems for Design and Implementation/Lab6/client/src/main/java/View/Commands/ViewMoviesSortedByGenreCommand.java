package View.Commands;

import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.MovieService;
import java.util.concurrent.ExecutionException;


public class ViewMoviesSortedByGenreCommand extends MenuCommand
{
    private final MovieService movieService;

    public ViewMoviesSortedByGenreCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        try
        {
            movieService.getMoviesSortedByGenre().get().forEach(System.out::println);
        }
        catch (ValidatorException | RepositoryException | InterruptedException | ExecutionException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
